#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <vector>
#include <thread>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_graph.h>
#include <xrt/xrt_aie.h>

// 2D IDCT on 64×64 blocks
static constexpr int BLOCK      = 64;
static constexpr int BLOCK_ELEMS = BLOCK * BLOCK;          // 4096
static constexpr int NUM_CORES  = 4;
static constexpr int N_WINDOWS_2D = 2;

// Frame dimensions
static constexpr int FRAME_W = 1920;
static constexpr int FRAME_H = 1080;

// Blocks per frame (64×64 blocks tiled over the frame)
static constexpr int BLK_COLS    = FRAME_W / BLOCK;                        // 30
static constexpr int BLK_ROWS    = FRAME_H / BLOCK;                        // 16 (1024 rows, pad to 1080)
static constexpr int BLK_ROWS_PAD = (FRAME_H + BLOCK - 1) / BLOCK;         // 17
static constexpr int TOTAL_BLOCKS = BLK_COLS * BLK_ROWS_PAD;               // 510
static constexpr int PADDED_BLOCKS = ((TOTAL_BLOCKS + NUM_CORES * N_WINDOWS_2D - 1)
                                      / (NUM_CORES * N_WINDOWS_2D))
                                      * (NUM_CORES * N_WINDOWS_2D);         // 512
static constexpr int N_ITERS_2D  = PADDED_BLOCKS / (NUM_CORES * N_WINDOWS_2D); // 64

static constexpr int BLOCKS_PER_CORE = PADDED_BLOCKS / NUM_CORES;          // 128
static constexpr int PER_CORE        = BLOCKS_PER_CORE * BLOCK_ELEMS;      // 524288
static constexpr size_t PER_CORE_BYTES = PER_CORE * sizeof(int16_t);       // 1 MB

static constexpr double AIE_FREQ_GHZ = 1.25;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <idct_ii_2d_aie.xclbin>" << std::endl;
        return 1;
    }

    auto device = xrt::device(0);
    auto uuid   = device.load_xclbin(argv[1]);
    std::cout << "xclbin loaded!" << std::endl;

    auto ghdl = xrt::graph(device, uuid, "gr");

    // --- simulate a 1920×1080 frame ---
    std::vector<int16_t> frame(FRAME_H * FRAME_W);
    for (int r = 0; r < FRAME_H; ++r)
        for (int c = 0; c < FRAME_W; ++c)
            frame[r * FRAME_W + c] = (int16_t)((r * FRAME_W + c) % 128);

    // --- reorder frame into packed 64×64 blocks ---
    std::vector<int16_t> packed(PADDED_BLOCKS * BLOCK_ELEMS, 0);
    for (int br = 0; br < BLK_ROWS_PAD; ++br) {
        for (int bc = 0; bc < BLK_COLS; ++bc) {
            int blk_id = br * BLK_COLS + bc;
            for (int dy = 0; dy < BLOCK; ++dy) {
                int src_row = br * BLOCK + dy;
                if (src_row >= FRAME_H) break;  // zero-padded
                std::memcpy(&packed[(blk_id * BLOCK + dy) * BLOCK],
                            &frame[src_row * FRAME_W + bc * BLOCK],
                            BLOCK * sizeof(int16_t));
            }
        }
    }

    // --- allocate XRT AIE BOs ---
    std::vector<xrt::aie::bo> bo_in, bo_out;
    for (int i = 0; i < NUM_CORES; i++) {
        bo_in.emplace_back(device, PER_CORE_BYTES, xrt::bo::flags::normal, 0);
        bo_out.emplace_back(device, PER_CORE_BYTES, xrt::bo::flags::normal, 0);
    }

    for (int i = 0; i < NUM_CORES; i++) {
        auto* src = bo_in[i].map<int16_t*>();
        std::memcpy(src, &packed[i * PER_CORE], PER_CORE_BYTES);
    }
    std::cout << "Buffers ready. "
              << PADDED_BLOCKS << " blocks (" << BLK_COLS << "x" << BLK_ROWS_PAD << "), "
              << N_ITERS_2D << " iterations, "
              << PER_CORE_BYTES / 1024 << " KB per core." << std::endl;

    // --- GMIO helpers ---
    using hrc = std::chrono::high_resolution_clock;

    auto fire_in = [&]() {
        for (int i = 0; i < NUM_CORES; i++)
            bo_in[i].async("gr.frame_src[" + std::to_string(i) + "]",
                           XCL_BO_SYNC_BO_GMIO_TO_AIE, PER_CORE_BYTES, 0);
    };

    auto fire_out = [&](std::vector<std::optional<xrt::bo::async_handle>>& handles) {
        for (int i = 0; i < NUM_CORES; i++)
            handles[i] = bo_out[i].async("gr.frame_dst[" + std::to_string(i) + "]",
                                         XCL_BO_SYNC_BO_AIE_TO_GMIO, PER_CORE_BYTES, 0);
    };

    auto run_one = [&]() {
        ghdl.run(N_ITERS_2D);
        std::vector<std::optional<xrt::bo::async_handle>> handles(NUM_CORES);
        fire_out(handles);
        fire_in();
        for (auto& h : handles) h->wait();
    };

    // --- warm-up ---
    std::cout << "Warming up..." << std::endl;
    for (int w = 0; w < 2; w++) {
        if (w > 0) ghdl.reset();
        run_one();
    }

    // --- timed run ---
    ghdl.reset();

    ghdl.run(N_ITERS_2D);
    std::vector<std::optional<xrt::bo::async_handle>> out_handles(NUM_CORES);
    fire_out(out_handles);

    auto t0 = hrc::now();
    fire_in();
    for (auto& h : out_handles) h->wait();
    auto t1 = hrc::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(t1 - t0).count();

    // --- report ---
    double total_bytes = 2.0 * NUM_CORES * PER_CORE_BYTES;
    double bw_gbs      = total_bytes / elapsed_us / 1e3;
    double fps          = 1e6 / elapsed_us;

    std::cout << "Frame:      " << FRAME_W << "x" << FRAME_H << " (2D IDCT, 64x64 blocks)" << std::endl;
    std::cout << "Cores:      " << NUM_CORES << " horizontal + " << NUM_CORES << " vertical" << std::endl;
    std::cout << "Buffer:     " << PER_CORE_BYTES / 1024 << " KB per core" << std::endl;
    std::cout << "Total data: " << total_bytes / (1 << 20) << " MB" << std::endl;
    std::cout << "Latency:    " << elapsed_us << " us" << std::endl;
    std::cout << "Bandwidth:  " << bw_gbs << " GB/s" << std::endl;
    std::cout << "FPS:        " << fps << std::endl;

    return 0;
}
