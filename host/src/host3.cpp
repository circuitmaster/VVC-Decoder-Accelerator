#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

#include <ap_int.h>

#include "xrt/xrt_bo.h"
#include "xrt/xrt_device.h"
#include "xrt/xrt_kernel.h"

namespace {

constexpr int REF_BLOCK_H = 15;
constexpr int REF_BLOCK_W = 15;
constexpr int BLOCK_SIZE = 8;
constexpr int NTAPS = 8;
constexpr int NUM_FRAC_POS = 16;
constexpr int FILTER_PREC = 6;
constexpr int BIT_DEPTH = 8;
constexpr int INTERNAL_PREC = 14;
constexpr int OUTPUT_SIZE = BLOCK_SIZE * BLOCK_SIZE;

using input_word_t = ap_uint<256>;
using output_byte_t = uint8_t;

static const int16_t LUMA_FILTER[NUM_FRAC_POS][NTAPS] = {
    {  0,  0,   0, 64,  0,   0,  0,  0 },
    {  0,  1,  -3, 63,  4,  -2,  1,  0 },
    { -1,  2,  -5, 62,  8,  -3,  1,  0 },
    { -1,  3,  -8, 60, 13,  -4,  1,  0 },
    { -1,  4, -10, 58, 17,  -5,  1,  0 },
    { -1,  4, -11, 52, 26,  -8,  3, -1 },
    { -1,  3,  -9, 47, 31, -10,  4, -1 },
    { -1,  4, -11, 45, 34, -10,  4, -1 },
    { -1,  4, -11, 40, 40, -11,  4, -1 },
    { -1,  4, -10, 34, 45, -11,  4, -1 },
    { -1,  4, -10, 31, 47,  -9,  3, -1 },
    { -1,  3,  -8, 26, 52, -11,  4, -1 },
    {  0,  1,  -5, 17, 58, -10,  4, -1 },
    {  0,  1,  -4, 13, 60,  -8,  3, -1 },
    {  0,  1,  -3,  8, 62,  -5,  2, -1 },
    {  0,  1,  -2,  4, 63,  -3,  1,  0 },
};

static std::vector<char> load_xclbin(const std::string& xclbin_path) {
    std::ifstream stream(xclbin_path, std::ios::binary | std::ios::ate);
    if (!stream) {
        throw std::runtime_error("Failed to open xclbin: " + xclbin_path);
    }
    std::streamsize size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!stream.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read xclbin: " + xclbin_path);
    }
    return buffer;
}

static size_t align_to_4096(size_t bytes) {
    constexpr size_t align = 4096;
    return (bytes % align == 0) ? bytes : align * ((bytes + align - 1) / align);
}

static uint8_t random_binary_frac() {
    return static_cast<uint8_t>(std::rand() & 1);
}

static uint16_t random_pixel() {
    return static_cast<uint16_t>(std::rand() % 256);
}

static input_word_t pack_ref_row(const std::array<uint16_t, REF_BLOCK_W>& row_vals) {
    input_word_t packed = 0;
    for (int c = 0; c < REF_BLOCK_W; ++c) {
        packed.range((c + 1) * 16 - 1, c * 16) = row_vals[c];
    }
    return packed;
}

static void fill_random_ref_block(std::array<input_word_t, REF_BLOCK_H>& packed_rows) {
    for (int r = 0; r < REF_BLOCK_H; ++r) {
        std::array<uint16_t, REF_BLOCK_W> row_vals{};
        for (int c = 0; c < REF_BLOCK_W; ++c) {
            row_vals[c] = random_pixel();
        }
        packed_rows[r] = pack_ref_row(row_vals);
    }
}

static uint64_t output_checksum(const output_byte_t* out_ptr) {
    uint64_t sum = 0;
    for (int i = 0; i < OUTPUT_SIZE; ++i) {
        sum += out_ptr[i];
    }
    return sum;
}

static void print_fps_metrics(int iterations, double elapsed_seconds) {
    if (elapsed_seconds <= 0.0 || iterations <= 0) {
        std::cout << "FPS 1080p (15x15 blocks): N/A" << std::endl;
        std::cout << "FPS 4K (15x15 blocks): N/A" << std::endl;
        return;
    }

    constexpr int width_1080p = 1920;
    constexpr int height_1080p = 1080;
    constexpr int width_4k = 3840;
    constexpr int height_4k = 2160;

    const int blocks_1080p = ((width_1080p + REF_BLOCK_W - 1) / REF_BLOCK_W) *
                             ((height_1080p + REF_BLOCK_H - 1) / REF_BLOCK_H);
    const int blocks_4k = ((width_4k + REF_BLOCK_W - 1) / REF_BLOCK_W) *
                          ((height_4k + REF_BLOCK_H - 1) / REF_BLOCK_H);

    const double blocks_per_second = static_cast<double>(iterations) / elapsed_seconds;
    const double fps_1080p = blocks_per_second / static_cast<double>(blocks_1080p);
    const double fps_4k = blocks_per_second / static_cast<double>(blocks_4k);

    std::cout << "FPS 1080p (15x15 blocks): " << fps_1080p << std::endl;
    std::cout << "FPS 4K (15x15 blocks): " << fps_4k << std::endl;
}

static void fill_binary_frac_bank(
    std::vector<uint8_t>& frac_x_bank,
    std::vector<uint8_t>& frac_y_bank,
    int iterations
) {
    for (int it = 0; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);
        frac_x_bank[idx] = random_binary_frac();
        frac_y_bank[idx] = random_binary_frac();
    }
}

static uint8_t clip_pixel_sw(int32_t val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return static_cast<uint8_t>(val);
}

static int32_t fir_8tap_sw(
    const int16_t samples[NTAPS],
    const int16_t coeffs[NTAPS]
) {
    int32_t sum = 0;
    for (int t = 0; t < NTAPS; ++t) {
        sum += static_cast<int32_t>(samples[t]) * static_cast<int32_t>(coeffs[t]);
    }
    return sum;
}

static void unpack_ref_block(
    const std::array<input_word_t, REF_BLOCK_H>& packed_rows,
    int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W]
) {
    for (int r = 0; r < REF_BLOCK_H; ++r) {
        for (int c = 0; c < REF_BLOCK_W; ++c) {
            ref_block[r][c] = static_cast<int16_t>(packed_rows[r].range((c + 1) * 16 - 1, c * 16));
        }
    }
}

static void vvc_fractional_interp_sw(
    const std::array<input_word_t, REF_BLOCK_H>& ref_packed,
    std::array<output_byte_t, OUTPUT_SIZE>& out_flat,
    uint8_t frac_x,
    uint8_t frac_y
) {
    int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W] = {};
    uint8_t out_block[BLOCK_SIZE][BLOCK_SIZE] = {};
    unpack_ref_block(ref_packed, ref_block);

    if (frac_x == 0 && frac_y == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                out_block[r][c] = clip_pixel_sw(ref_block[r + 3][c + 3]);
            }
        }
    } else if (frac_y == 0) {
        int16_t coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) coeffs[t] = LUMA_FILTER[frac_x][t];

        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r + 3][c + t];
                }
                const int32_t sum = fir_8tap_sw(samples, coeffs);
                const int32_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    } else if (frac_x == 0) {
        int16_t coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) coeffs[t] = LUMA_FILTER[frac_y][t];

        for (int c = 0; c < BLOCK_SIZE; ++c) {
            for (int r = 0; r < BLOCK_SIZE; ++r) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r + t][c + 3];
                }
                const int32_t sum = fir_8tap_sw(samples, coeffs);
                const int32_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    } else {
        int32_t transpose_mem[REF_BLOCK_H][BLOCK_SIZE] = {};
        const int headroom = INTERNAL_PREC - BIT_DEPTH;
        const int shift1 = FILTER_PREC - headroom;
        const int offset1 = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
        const int shift2 = FILTER_PREC + headroom;
        const int offset2 = (1 << (shift2 - 1));

        int16_t h_coeffs[NTAPS] = {};
        int16_t v_coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) {
            h_coeffs[t] = LUMA_FILTER[frac_x][t];
            v_coeffs[t] = LUMA_FILTER[frac_y][t];
        }

        for (int r = 0; r < REF_BLOCK_H; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r][c + t];
                }

                const int32_t sum = fir_8tap_sw(samples, h_coeffs);
                if (shift1 >= 0) {
                    transpose_mem[r][c] = (sum + offset1) >> shift1;
                } else {
                    transpose_mem[r][c] = sum << (-shift1);
                }
            }
        }

        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t) {
                    sum += transpose_mem[r + t][c] * static_cast<int32_t>(v_coeffs[t]);
                }
                const int32_t val = (sum + offset2) >> shift2;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    }

    for (int r = 0; r < BLOCK_SIZE; ++r) {
        for (int c = 0; c < BLOCK_SIZE; ++c) {
            out_flat[static_cast<size_t>(r) * BLOCK_SIZE + c] = out_block[r][c];
        }
    }
}

static void run_kernel_warmup(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr
) {
    std::array<input_word_t, REF_BLOCK_H> warmup_input{};
    fill_random_ref_block(warmup_input);
    std::copy(warmup_input.begin(), warmup_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    for (int i = 0; i < 10; ++i) {
        const uint8_t frac_x = random_binary_frac();
        const uint8_t frac_y = random_binary_frac();
        auto run = kernel(input_bo, output_bo, frac_x, frac_y);
        run.wait();
    }
}

static bool run_golden_verification(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_byte_t* output_ptr,
    int iterations
) {
    std::cout << "\n[Golden Check] Hardware vs software model" << std::endl;

    std::vector<std::array<input_word_t, REF_BLOCK_H>> cpu_input_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(iterations));
    std::vector<std::array<output_byte_t, OUTPUT_SIZE>> sw_outputs(static_cast<size_t>(iterations));

    for (int it = 0; it < iterations; ++it) {
        fill_random_ref_block(cpu_input_bank[static_cast<size_t>(it)]);
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, iterations);

    bool mismatch = false;
    size_t mismatch_count = 0;

    for (int it = 0; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);

        vvc_fractional_interp_sw(cpu_input_bank[idx], sw_outputs[idx], frac_x_bank[idx], frac_y_bank[idx]);

        std::copy(cpu_input_bank[idx].begin(), cpu_input_bank[idx].end(), input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx]);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        for (int i = 0; i < OUTPUT_SIZE; ++i) {
            const uint8_t hw = output_ptr[i];
            const uint8_t sw = sw_outputs[idx][static_cast<size_t>(i)];
            if (hw != sw) {
                if (mismatch_count < 20) {
                    std::cout << "Mismatch iter=" << it
                              << " frac_x=" << static_cast<int>(frac_x_bank[idx])
                              << " frac_y=" << static_cast<int>(frac_y_bank[idx])
                              << " idx=" << i
                              << " sw=" << static_cast<int>(sw)
                              << " hw=" << static_cast<int>(hw)
                              << std::endl;
                }
                mismatch = true;
                ++mismatch_count;
            }
        }
    }

    if (!mismatch) {
        std::cout << "Golden model match: all outputs identical." << std::endl;
    } else {
        std::cout << "Golden model mismatch count: " << mismatch_count << std::endl;
    }

    return !mismatch;
}

static void run_scenario_1(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_byte_t* output_ptr,
    int iterations
) {
    std::cout << "\n[Scenario 1] Fixed input, random binary frac_x/frac_y each iteration" << std::endl;

    std::array<input_word_t, REF_BLOCK_H> fixed_input{};
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(iterations));

    fill_random_ref_block(fixed_input);
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, iterations);
    std::copy(fixed_input.begin(), fixed_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    uint64_t checksum_acc = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);
        const uint8_t frac_x = frac_x_bank[idx];
        const uint8_t frac_y = frac_y_bank[idx];

        auto run = kernel(input_bo, output_bo, frac_x, frac_y);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        checksum_acc += output_checksum(output_ptr);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per iteration: " << (elapsed.count() / std::max(1, iterations)) << " s" << std::endl;
    print_fps_metrics(iterations, elapsed.count());
    std::cout << "Output checksum accumulator: " << checksum_acc << std::endl;
}

static void run_scenario_2(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_byte_t* output_ptr,
    int iterations
) {
    std::cout << "\n[Scenario 2] Prefilled CPU random input bank, per-iteration copy+sync+run+sync" << std::endl;

    std::vector<std::array<input_word_t, REF_BLOCK_H>> cpu_input_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(iterations));
    std::vector<std::array<output_byte_t, OUTPUT_SIZE>> cpu_output_bank(static_cast<size_t>(iterations));

    for (int it = 0; it < iterations; ++it) {
        fill_random_ref_block(cpu_input_bank[static_cast<size_t>(it)]);
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, iterations);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);

        std::copy(cpu_input_bank[idx].begin(), cpu_input_bank[idx].end(), input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx]);
        run.wait();

        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        std::copy(output_ptr, output_ptr + OUTPUT_SIZE, cpu_output_bank[idx].begin());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    uint64_t checksum_acc = 0;
    for (const auto& out : cpu_output_bank) {
        checksum_acc += std::accumulate(out.begin(), out.end(), static_cast<uint64_t>(0));
    }

    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per iteration: " << (elapsed.count() / std::max(1, iterations)) << " s" << std::endl;
    print_fps_metrics(iterations, elapsed.count());
    std::cout << "Output checksum accumulator: " << checksum_acc << std::endl;
}

static void run_scenario_3(
    xrt::kernel& kernel,
    xrt::device& device,
    int g_in,
    int g_out,
    int iterations
) {
    std::cout << "\n[Scenario 3] Double-buffer input ping-pong with overlapped host fill" << std::endl;

    std::vector<std::array<input_word_t, REF_BLOCK_H>> cpu_input_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(iterations));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(iterations));
    std::vector<std::array<output_byte_t, OUTPUT_SIZE>> cpu_output_bank(static_cast<size_t>(iterations));

    for (int it = 0; it < iterations; ++it) {
        fill_random_ref_block(cpu_input_bank[static_cast<size_t>(it)]);
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, iterations);

    const size_t input_bytes = align_to_4096(sizeof(input_word_t) * REF_BLOCK_H);
    const size_t output_bytes = align_to_4096(sizeof(output_byte_t) * OUTPUT_SIZE);

    std::array<xrt::bo, 2> input_bo = {
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in),
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in)
    };

    std::array<xrt::bo, 2> output_bo = {
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out),
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out)
    };

    std::array<input_word_t*, 2> input_ptr = {
        input_bo[0].map<input_word_t*>(),
        input_bo[1].map<input_word_t*>()
    };

    std::array<output_byte_t*, 2> output_ptr = {
        output_bo[0].map<output_byte_t*>(),
        output_bo[1].map<output_byte_t*>()
    };

    int cur = 0;
    int nxt = 1;

    std::copy(cpu_input_bank[0].begin(), cpu_input_bank[0].end(), input_ptr[cur]);
    input_bo[cur].sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto start = std::chrono::high_resolution_clock::now();

    auto run = kernel(input_bo[cur], output_bo[cur], frac_x_bank[0], frac_y_bank[0]);

    for (int it = 1; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);

        std::copy(cpu_input_bank[idx].begin(), cpu_input_bank[idx].end(), input_ptr[nxt]);
        input_bo[nxt].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        run.wait();
        output_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        std::copy(output_ptr[cur], output_ptr[cur] + OUTPUT_SIZE,
                  cpu_output_bank[static_cast<size_t>(it - 1)].begin());

        run = kernel(input_bo[nxt], output_bo[nxt], frac_x_bank[idx], frac_y_bank[idx]);
        std::swap(cur, nxt);
    }

    run.wait();
    output_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    std::copy(output_ptr[cur], output_ptr[cur] + OUTPUT_SIZE,
              cpu_output_bank[static_cast<size_t>(iterations - 1)].begin());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    uint64_t checksum_acc = 0;
    for (const auto& out : cpu_output_bank) {
        checksum_acc += std::accumulate(out.begin(), out.end(), static_cast<uint64_t>(0));
    }

    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per iteration: " << (elapsed.count() / std::max(1, iterations)) << " s" << std::endl;
    print_fps_metrics(iterations, elapsed.count());
    std::cout << "Output checksum accumulator: " << checksum_acc << std::endl;
}

} // namespace

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <xclbin> <iterations>" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string xclbin_path = argv[1];
    const int iterations = std::stoi(argv[2]);

    if (iterations <= 0) {
        std::cerr << "Iterations must be > 0." << std::endl;
        return EXIT_FAILURE;
    }

    try {
        auto device = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin = xrt::xclbin(xclbin_data);
        auto uuid = device.load_xclbin(xclbin);

        auto kernel = xrt::kernel(device, uuid, "vvc_fractional_interp");
        std::cout << "xclbin load successful" << std::endl;

        const size_t input_bytes = align_to_4096(sizeof(input_word_t) * REF_BLOCK_H);
        const size_t output_bytes = align_to_4096(sizeof(output_byte_t) * OUTPUT_SIZE);

        auto g_in = kernel.group_id(0);
        auto g_out = kernel.group_id(1);

        xrt::bo input_bo(device, input_bytes, xrt::bo::flags::normal, g_in);
        xrt::bo output_bo(device, output_bytes, xrt::bo::flags::normal, g_out);

        input_word_t* input_ptr = input_bo.map<input_word_t*>();
        output_byte_t* output_ptr = output_bo.map<output_byte_t*>();

        run_kernel_warmup(kernel, input_bo, output_bo, input_ptr);

        run_scenario_1(kernel, input_bo, output_bo, input_ptr, output_ptr, iterations);
        run_scenario_2(kernel, input_bo, output_bo, input_ptr, output_ptr, iterations);
        run_scenario_3(kernel, device, g_in, g_out, iterations);
        run_golden_verification(kernel, input_bo, output_bo, input_ptr, output_ptr, iterations);

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
