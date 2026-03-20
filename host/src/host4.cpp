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
constexpr int OUT_ROWS_PER_BLOCK = BLOCK_SIZE;

using input_word_t = ap_uint<256>;
using output_word_t = ap_uint<128>;

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

struct FrameConfig {
    int width;
    int height;
    int blocks_w;
    int blocks_h;
    int block_count;
};

struct RunConfig {
    int total_frames;
    int frames_per_exec;
    int exec_count;
    int blocks_per_exec;
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

static FrameConfig make_frame_config(const std::string& resolution) {
    if (resolution == "fhd" || resolution == "1080p") {
        const int width = 1920;
        const int height = 1080;
        const int blocks_w = (width + REF_BLOCK_W - 1) / REF_BLOCK_W;
        const int blocks_h = (height + REF_BLOCK_H - 1) / REF_BLOCK_H;
        return {width, height, blocks_w, blocks_h, blocks_w * blocks_h};
    }
    if (resolution == "4k" || resolution == "2160p") {
        const int width = 3840;
        const int height = 2160;
        const int blocks_w = (width + REF_BLOCK_W - 1) / REF_BLOCK_W;
        const int blocks_h = (height + REF_BLOCK_H - 1) / REF_BLOCK_H;
        return {width, height, blocks_w, blocks_h, blocks_w * blocks_h};
    }
    throw std::runtime_error("Resolution must be one of: fhd, 1080p, 4k, 2160p");
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

static void fill_random_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count
) {
    const size_t words_per_frame = static_cast<size_t>(block_count) * REF_BLOCK_H;
    frame_input.resize(words_per_frame);

    for (int b = 0; b < block_count; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t row = 0;
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                row.range((c + 1) * 16 - 1, c * 16) = random_pixel();
            }
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = row;
        }
    }
}

static void print_fps_for_resolution(const FrameConfig& cfg, int iterations, double elapsed_seconds) {
    if (elapsed_seconds <= 0.0 || iterations <= 0) {
        std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): N/A" << std::endl;
        return;
    }
    const double fps = static_cast<double>(iterations) / elapsed_seconds;
    std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): " << fps << std::endl;
}

static uint8_t clip_pixel_sw(int32_t val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return static_cast<uint8_t>(val);
}

static int32_t fir_8tap_sw(const int16_t samples[NTAPS], const int16_t coeffs[NTAPS]) {
    int32_t sum = 0;
    for (int t = 0; t < NTAPS; ++t) {
        sum += static_cast<int32_t>(samples[t]) * static_cast<int32_t>(coeffs[t]);
    }
    return sum;
}

static void unpack_ref_block_from_frame(
    const std::vector<input_word_t>& frame_input,
    int block_idx,
    int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W]
) {
    const size_t base = static_cast<size_t>(block_idx) * REF_BLOCK_H;
    for (int r = 0; r < REF_BLOCK_H; ++r) {
        const input_word_t row = frame_input[base + r];
        for (int c = 0; c < REF_BLOCK_W; ++c) {
            ref_block[r][c] = static_cast<int16_t>(row.range((c + 1) * 16 - 1, c * 16));
        }
    }
}

static void interp_block_sw(
    const int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    uint8_t out_block[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t frac_x,
    uint8_t frac_y
) {
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
}

static void software_model_frame(
    const std::vector<input_word_t>& frame_input,
    std::vector<output_word_t>& frame_output,
    int block_count,
    uint8_t frac_x,
    uint8_t frac_y
) {
    frame_output.assign(static_cast<size_t>(block_count) * OUT_ROWS_PER_BLOCK, output_word_t(0));

    for (int b = 0; b < block_count; ++b) {
        int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W] = {};
        uint8_t out_block[BLOCK_SIZE][BLOCK_SIZE] = {};
        unpack_ref_block_from_frame(frame_input, b, ref_block);
        interp_block_sw(ref_block, out_block, frac_x, frac_y);

        const size_t out_base = static_cast<size_t>(b) * OUT_ROWS_PER_BLOCK;
        for (int r = 0; r < BLOCK_SIZE; ++r) {
            output_word_t packed = 0;
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                packed.range((c + 1) * 16 - 1, c * 16) = static_cast<uint16_t>(out_block[r][c]);
            }
            frame_output[out_base + r] = packed;
        }
    }
}

static void run_kernel_warmup(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    int blocks_per_exec
) {
    std::vector<input_word_t> warmup_exec_input;
    fill_random_frame_input(warmup_exec_input, blocks_per_exec);
    std::copy(warmup_exec_input.begin(), warmup_exec_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    for (int i = 0; i < 10; ++i) {
        const uint8_t fx = random_binary_frac();
        const uint8_t fy = random_binary_frac();
        auto run = kernel(input_bo, output_bo, fx, fy, blocks_per_exec);
        run.wait();
    }
}

static void run_scenario_1(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_word_t* output_ptr,
    const FrameConfig& cfg,
    const RunConfig& run_cfg
) {
    std::cout << "\n[Scenario 1] Fixed batched input, random binary frac_x/frac_y per execution" << std::endl;

    std::vector<input_word_t> fixed_exec_input;
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));

    fill_random_frame_input(fixed_exec_input, run_cfg.blocks_per_exec);
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    std::copy(fixed_exec_input.begin(), fixed_exec_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        // checksum disabled to avoid affecting timing
        (void)output_ptr;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static void run_scenario_2(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_word_t* output_ptr,
    const FrameConfig& cfg,
    const RunConfig& run_cfg
) {
    std::cout << "\n[Scenario 2] Prefilled random frame bank, per-frame copy+sync+run+sync" << std::endl;

    const size_t words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    const size_t out_words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    std::vector<input_word_t> frame_bank(static_cast<size_t>(run_cfg.exec_count) * words_per_exec);
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<output_word_t> output_bank(static_cast<size_t>(run_cfg.exec_count) * out_words_per_exec);

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> tmp;
        fill_random_frame_input(tmp, run_cfg.blocks_per_exec);
        std::copy(tmp.begin(), tmp.end(), frame_bank.begin() + static_cast<size_t>(it) * words_per_exec);
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        const auto in_off = idx * words_per_exec;
        const auto out_off = idx * out_words_per_exec;

        std::copy(frame_bank.begin() + in_off, frame_bank.begin() + in_off + words_per_exec, input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        run.wait();

        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        std::copy(output_ptr, output_ptr + out_words_per_exec, output_bank.begin() + out_off);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static void run_scenario_3(
    xrt::kernel& kernel,
    xrt::device& device,
    int g_in,
    int g_out,
    const FrameConfig& cfg,
    const RunConfig& run_cfg
) {
    std::cout << "\n[Scenario 3] Double-buffer frame ping-pong" << std::endl;

    const size_t words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    const size_t out_words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    std::vector<input_word_t> frame_bank(static_cast<size_t>(run_cfg.exec_count) * words_per_exec);
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<output_word_t> output_bank(static_cast<size_t>(run_cfg.exec_count) * out_words_per_exec);

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> tmp;
        fill_random_frame_input(tmp, run_cfg.blocks_per_exec);
        std::copy(tmp.begin(), tmp.end(), frame_bank.begin() + static_cast<size_t>(it) * words_per_exec);
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    const size_t input_bytes = align_to_4096(words_per_exec * sizeof(input_word_t));
    const size_t output_bytes = align_to_4096(out_words_per_exec * sizeof(output_word_t));

    std::array<xrt::bo, 2> in_bo = {
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in),
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in)
    };
    std::array<xrt::bo, 2> out_bo = {
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out),
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out)
    };

    std::array<input_word_t*, 2> in_ptr = {
        in_bo[0].map<input_word_t*>(),
        in_bo[1].map<input_word_t*>()
    };
    std::array<output_word_t*, 2> out_ptr = {
        out_bo[0].map<output_word_t*>(),
        out_bo[1].map<output_word_t*>()
    };

    int cur = 0;
    int nxt = 1;

    std::copy(frame_bank.begin(), frame_bank.begin() + words_per_exec, in_ptr[cur]);
    in_bo[cur].sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto start = std::chrono::high_resolution_clock::now();

    auto run = kernel(in_bo[cur], out_bo[cur], frac_x_bank[0], frac_y_bank[0], run_cfg.blocks_per_exec);

    for (int it = 1; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        const auto in_off = idx * words_per_exec;

        std::copy(frame_bank.begin() + in_off, frame_bank.begin() + in_off + words_per_exec, in_ptr[nxt]);
        in_bo[nxt].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        run.wait();
        out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        const auto out_off = static_cast<size_t>(it - 1) * out_words_per_exec;
        std::copy(out_ptr[cur], out_ptr[cur] + out_words_per_exec, output_bank.begin() + out_off);

        run = kernel(in_bo[nxt], out_bo[nxt], frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        std::swap(cur, nxt);
    }

    run.wait();
    out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    std::copy(out_ptr[cur], out_ptr[cur] + out_words_per_exec,
              output_bank.begin() + static_cast<size_t>(run_cfg.exec_count - 1) * out_words_per_exec);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static bool run_golden_verification(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_word_t* output_ptr,
    const FrameConfig& cfg,
    const RunConfig& run_cfg
) {
    std::cout << "\n[Golden Check] Hardware vs software model (frame mode)" << std::endl;

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    bool mismatch = false;
    size_t mismatch_count = 0;
    const size_t out_words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> frame_input;
        fill_random_frame_input(frame_input, run_cfg.blocks_per_exec);

        std::vector<output_word_t> sw_out;
        software_model_frame(frame_input, sw_out, run_cfg.blocks_per_exec, frac_x_bank[static_cast<size_t>(it)], frac_y_bank[static_cast<size_t>(it)]);

        std::copy(frame_input.begin(), frame_input.end(), input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo,
                          frac_x_bank[static_cast<size_t>(it)],
                          frac_y_bank[static_cast<size_t>(it)],
                          run_cfg.blocks_per_exec);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        for (size_t i = 0; i < out_words_per_exec; ++i) {
            const output_word_t hw_word = output_ptr[i];
            const output_word_t sw_word = sw_out[i];
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                const uint16_t hw = static_cast<uint16_t>(hw_word.range((c + 1) * 16 - 1, c * 16));
                const uint16_t sw = static_cast<uint16_t>(sw_word.range((c + 1) * 16 - 1, c * 16));
                if (hw != sw) {
                    if (mismatch_count < 20) {
                        std::cout << "Mismatch iter=" << it
                                  << " out_word=" << i
                                  << " lane=" << c
                                  << " frac_x=" << static_cast<int>(frac_x_bank[static_cast<size_t>(it)])
                                  << " frac_y=" << static_cast<int>(frac_y_bank[static_cast<size_t>(it)])
                                  << " sw=" << sw
                                  << " hw=" << hw
                                  << std::endl;
                    }
                    mismatch = true;
                    ++mismatch_count;
                }
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

} // namespace

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (argc != 5) {
        std::cout << "Usage: " << argv[0] << " <xclbin> <iterations(total_frames)> <resolution:fhd|4k> <frames_per_exec>" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string xclbin_path = argv[1];
    const int iterations = std::stoi(argv[2]);
    const std::string resolution = argv[3];
    const int frames_per_exec = std::stoi(argv[4]);

    if (iterations <= 0) {
        std::cerr << "Iterations must be > 0." << std::endl;
        return EXIT_FAILURE;
    }
    if (frames_per_exec <= 0) {
        std::cerr << "frames_per_exec must be > 0." << std::endl;
        return EXIT_FAILURE;
    }
    if (iterations % frames_per_exec != 0) {
        std::cerr << "iterations(total_frames) must be divisible by frames_per_exec." << std::endl;
        return EXIT_FAILURE;
    }

    try {
        const FrameConfig cfg = make_frame_config(resolution);
        const RunConfig run_cfg = {
            iterations,
            frames_per_exec,
            iterations / frames_per_exec,
            cfg.block_count * frames_per_exec
        };

        std::cout << "Frame: " << cfg.width << "x" << cfg.height
                  << ", blocks_w=" << cfg.blocks_w
                  << ", blocks_h=" << cfg.blocks_h
                  << ", block_count=" << cfg.block_count << std::endl;
        std::cout << "Run config: total_frames=" << run_cfg.total_frames
                  << ", frames_per_exec=" << run_cfg.frames_per_exec
                  << ", exec_count=" << run_cfg.exec_count
                  << ", blocks_per_exec=" << run_cfg.blocks_per_exec << std::endl;

        auto device = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin = xrt::xclbin(xclbin_data);
        auto uuid = device.load_xclbin(xclbin);

        auto kernel = xrt::kernel(device, uuid, "vvc_fractional_interp");
        std::cout << "xclbin load successful" << std::endl;

        const size_t input_words = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
        const size_t output_words = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;
        const size_t input_bytes = align_to_4096(input_words * sizeof(input_word_t));
        const size_t output_bytes = align_to_4096(output_words * sizeof(output_word_t));

        auto g_in = kernel.group_id(0);
        auto g_out = kernel.group_id(1);

        xrt::bo input_bo(device, input_bytes, xrt::bo::flags::normal, g_in);
        xrt::bo output_bo(device, output_bytes, xrt::bo::flags::normal, g_out);

        input_word_t* input_ptr = input_bo.map<input_word_t*>();
        output_word_t* output_ptr = output_bo.map<output_word_t*>();

        run_kernel_warmup(kernel, input_bo, output_bo, input_ptr, run_cfg.blocks_per_exec);

        run_scenario_1(kernel, input_bo, output_bo, input_ptr, output_ptr, cfg, run_cfg);
        run_scenario_2(kernel, input_bo, output_bo, input_ptr, output_ptr, cfg, run_cfg);
        run_scenario_3(kernel, device, g_in, g_out, cfg, run_cfg);
        run_golden_verification(kernel, input_bo, output_bo, input_ptr, output_ptr, cfg, run_cfg);

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
