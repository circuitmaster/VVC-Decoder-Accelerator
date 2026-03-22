// Multi-block verification: SW model vs HW kernel
// Tests with increasing block counts to find where mismatches start.
//
// Usage: ./verify_single <xclbin> <frac_x> <frac_y> [max_blocks]
//   frac_x, frac_y: 0-15
//   max_blocks: optional, default 100 — tests 1, 2, 4, 8, ... up to max_blocks

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <ap_int.h>

#include "xrt/xrt_bo.h"
#include "xrt/xrt_device.h"
#include "xrt/xrt_kernel.h"

// ---- constants (same as HW header) ----
static constexpr int BLOCK_SIZE    = 8;
static constexpr int NTAPS         = 8;
static constexpr int NUM_FRAC_POS  = 16;
static constexpr int FILTER_PREC   = 6;
static constexpr int BIT_DEPTH     = 8;
static constexpr int INTERNAL_PREC = 14;
static constexpr int REF_BLOCK_W   = 15;
static constexpr int REF_BLOCK_H   = 15;

using input_word_t  = ap_uint<256>;
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

// ---- SW model ----
static uint8_t clip(int32_t v) {
    return v < 0 ? 0 : (v > 255 ? 255 : static_cast<uint8_t>(v));
}

static void sw_interp(
    int16_t ref[REF_BLOCK_H][REF_BLOCK_W],
    uint8_t out[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t fx, uint8_t fy
) {
    if (fx == 0 && fy == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c)
                out[r][c] = clip(ref[r + 3][c + 3]);
    } else if (fy == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t)
                    sum += (int32_t)ref[r + 3][c + t] * LUMA_FILTER[fx][t];
                out[r][c] = clip((sum + 32) >> 6);
            }
    } else if (fx == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t)
                    sum += (int32_t)ref[r + t][c + 3] * LUMA_FILTER[fy][t];
                out[r][c] = clip((sum + 32) >> 6);
            }
    } else {
        const int headroom = INTERNAL_PREC - BIT_DEPTH;
        const int shift1   = FILTER_PREC - headroom;
        const int offset1  = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
        const int shift2   = FILTER_PREC + headroom;
        const int offset2  = (1 << (shift2 - 1));

        int32_t tmp[REF_BLOCK_H][BLOCK_SIZE] = {};
        for (int r = 0; r < REF_BLOCK_H; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t)
                    sum += (int32_t)ref[r][c + t] * LUMA_FILTER[fx][t];
                tmp[r][c] = (shift1 >= 0) ? ((sum + offset1) >> shift1) : (sum << -shift1);
            }
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t)
                    sum += tmp[r + t][c] * LUMA_FILTER[fy][t];
                out[r][c] = clip((sum + offset2) >> shift2);
            }
    }
}

// ---- helpers ----
static std::vector<char> load_xclbin(const std::string& path) {
    std::ifstream f(path, std::ios::binary | std::ios::ate);
    if (!f) throw std::runtime_error("Cannot open xclbin: " + path);
    auto sz = f.tellg(); f.seekg(0);
    std::vector<char> buf(sz);
    f.read(buf.data(), sz);
    return buf;
}

static size_t align4k(size_t n) {
    return (n + 4095) & ~size_t(4095);
}

// Run SW + HW for `nblocks` blocks, return number of mismatched pixels.
static int test_n_blocks(
    xrt::kernel& kernel,
    xrt::device& device,
    int nblocks,
    uint8_t fx, uint8_t fy,
    bool verbose
) {
    const size_t in_words  = static_cast<size_t>(nblocks) * REF_BLOCK_H;
    const size_t out_words = static_cast<size_t>(nblocks) * BLOCK_SIZE;

    const size_t in_bytes  = align4k(in_words  * sizeof(input_word_t));
    const size_t out_bytes = align4k(out_words * sizeof(output_word_t));

    auto g_in  = kernel.group_id(0);
    auto g_out = kernel.group_id(1);

    xrt::bo in_bo (device, in_bytes,  xrt::bo::flags::normal, g_in);
    xrt::bo out_bo(device, out_bytes, xrt::bo::flags::normal, g_out);

    auto* in_ptr  = in_bo.map<input_word_t*>();
    auto* out_ptr = out_bo.map<output_word_t*>();

    // ---- Generate deterministic input for all blocks ----
    // Each block gets a different but reproducible pattern
    std::vector<int16_t> all_ref(static_cast<size_t>(nblocks) * REF_BLOCK_H * REF_BLOCK_W);
    for (int b = 0; b < nblocks; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t w = 0;
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                int16_t val = static_cast<int16_t>((b + r * REF_BLOCK_W + c) % 256);
                all_ref[static_cast<size_t>(b) * REF_BLOCK_H * REF_BLOCK_W +
                        r * REF_BLOCK_W + c] = val;
                w.range((c + 1) * 16 - 1, c * 16) = static_cast<uint16_t>(val);
            }
            in_ptr[static_cast<size_t>(b) * REF_BLOCK_H + r] = w;
        }
    }

    in_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto run = kernel(in_bo, out_bo, fx, fy, nblocks);
    run.wait();

    out_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

    // ---- SW model + compare ----
    int mismatches = 0;
    for (int b = 0; b < nblocks; ++b) {
        // Unpack ref for this block
        int16_t ref[REF_BLOCK_H][REF_BLOCK_W];
        for (int r = 0; r < REF_BLOCK_H; ++r)
            for (int c = 0; c < REF_BLOCK_W; ++c)
                ref[r][c] = all_ref[static_cast<size_t>(b) * REF_BLOCK_H * REF_BLOCK_W +
                                    r * REF_BLOCK_W + c];

        uint8_t sw_out[BLOCK_SIZE][BLOCK_SIZE] = {};
        sw_interp(ref, sw_out, fx, fy);

        // Compare against HW output
        for (int r = 0; r < BLOCK_SIZE; ++r) {
            output_word_t hw_row = out_ptr[static_cast<size_t>(b) * BLOCK_SIZE + r];
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                uint8_t hw_val = static_cast<uint8_t>(
                    static_cast<uint16_t>(hw_row.range((c + 1) * 16 - 1, c * 16)));
                if (sw_out[r][c] != hw_val) {
                    ++mismatches;
                    if (verbose && mismatches <= 10) {
                        std::cout << "  block=" << b << " [" << r << "][" << c << "]"
                                  << "  sw=" << (int)sw_out[r][c]
                                  << "  hw=" << (int)hw_val << "\n";
                    }
                }
            }
        }
    }
    return mismatches;
}

int main(int argc, char** argv) {
    if (argc < 4 || argc > 5) {
        std::cerr << "Usage: " << argv[0]
                  << " <xclbin> <frac_x 0-15> <frac_y 0-15> [max_blocks=100]\n";
        return 1;
    }
    const std::string xclbin_path = argv[1];
    const uint8_t fx = static_cast<uint8_t>(std::atoi(argv[2]));
    const uint8_t fy = static_cast<uint8_t>(std::atoi(argv[3]));
    const int max_blocks = (argc >= 5) ? std::atoi(argv[4]) : 100;

    try {
        auto device = xrt::device(0);
        auto xclbin = xrt::xclbin(load_xclbin(xclbin_path));
        auto uuid   = device.load_xclbin(xclbin);
        auto kernel = xrt::kernel(device, uuid, "vvc_fractional_interp");

        std::cout << "=== Multi-block sweep (frac_x=" << (int)fx
                  << " frac_y=" << (int)fy << ") ===\n\n";

        // Test power-of-2 block counts: 1, 2, 4, 8, ..., max_blocks
        for (int n = 1; n <= max_blocks; n *= 2) {
            int m = test_n_blocks(kernel, device, n, fx, fy, true);
            std::cout << "blocks=" << std::setw(6) << n
                      << "  pixels=" << std::setw(8) << n * BLOCK_SIZE * BLOCK_SIZE
                      << "  mismatches=" << m;
            if (m == 0)
                std::cout << "  PASS";
            else
                std::cout << "  FAIL (" << m << "/" << n * BLOCK_SIZE * BLOCK_SIZE << ")";
            std::cout << "\n";

            // If we just found the first failure, also test the midpoint
            if (m > 0 && n > 1) {
                int lo = n / 2, hi = n;
                std::cout << "\n  Binary search for first failing block count...\n";
                while (hi - lo > 1) {
                    int mid = (lo + hi) / 2;
                    int mm = test_n_blocks(kernel, device, mid, fx, fy, false);
                    std::cout << "    blocks=" << mid << "  mismatches=" << mm
                              << (mm == 0 ? "  PASS" : "  FAIL") << "\n";
                    if (mm == 0)
                        lo = mid;
                    else
                        hi = mid;
                }
                std::cout << "  First failing block count: " << hi << "\n";

                // Show detailed mismatches for that count
                std::cout << "\n  Detailed mismatches for blocks=" << hi << ":\n";
                test_n_blocks(kernel, device, hi, fx, fy, true);
                break;
            }
        }

        // Also test the exact block count for fhd if within range
        if (max_blocks >= 9216) {
            std::cout << "\n--- FHD block count (9216) ---\n";
            int m = test_n_blocks(kernel, device, 9216, fx, fy, true);
            std::cout << "blocks=9216  mismatches=" << m
                      << (m == 0 ? "  PASS" : "  FAIL") << "\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
