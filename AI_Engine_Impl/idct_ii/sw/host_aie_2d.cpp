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

// 2D IDCT on 64×64 blocks — matches graph.h / reshape.h design
static constexpr int BLOCK       = 64;
static constexpr int BLOCK_ELEMS = BLOCK * BLOCK;            // 4096

static constexpr int NUM_ENGINE    = 4;
static constexpr int NUM_CU        = 2;
static constexpr int N_WINDOWS_2D  = 1;

#ifndef GMIO_LEVEL
#define GMIO_LEVEL 0
#endif
static constexpr int NUM_GMIO_PORTS = 1 << GMIO_LEVEL;

// Frame dimensions
static constexpr int FRAME_W = 1920;
static constexpr int FRAME_H = 1080;

// Blocks per frame (64×64 blocks tiled over the frame)
static constexpr int BLK_COLS     = FRAME_W / BLOCK;                             // 30
static constexpr int BLK_ROWS_PAD = (FRAME_H + BLOCK - 1) / BLOCK;              // 17
static constexpr int TOTAL_BLOCKS = BLK_COLS * BLK_ROWS_PAD;                     // 510

static constexpr int BLOCKS_PER_ITER = NUM_ENGINE * NUM_CU * N_WINDOWS_2D;
static constexpr int PADDED_BLOCKS   = ((TOTAL_BLOCKS + BLOCKS_PER_ITER - 1)
                                        / BLOCKS_PER_ITER) * BLOCKS_PER_ITER;
static constexpr int N_ITERS_2D      = PADDED_BLOCKS / BLOCKS_PER_ITER;

// Per-engine totals
static constexpr int BLOCKS_PER_ENGINE = N_ITERS_2D * NUM_CU * N_WINDOWS_2D;
static constexpr int PER_ENGINE        = BLOCKS_PER_ENGINE * BLOCK_ELEMS;
static constexpr size_t PER_ENGINE_BYTES = PER_ENGINE * sizeof(int16_t);

// Per-GMIO-port sizes (input: linear split; output: 2D column split)
static constexpr int ELEMS_PER_ITER      = NUM_CU * N_WINDOWS_2D * BLOCK_ELEMS;
static constexpr int IN_PER_PORT_ITER    = ELEMS_PER_ITER / NUM_GMIO_PORTS;
static constexpr int IN_PER_PORT_TOTAL   = N_ITERS_2D * IN_PER_PORT_ITER;
static constexpr size_t IN_PER_PORT_BYTES = IN_PER_PORT_TOTAL * sizeof(int16_t);

static constexpr int OUT_DIM1            = N_WINDOWS_2D * BLOCK * NUM_CU;
static constexpr int OUT_PORT_DIM1       = OUT_DIM1 / NUM_GMIO_PORTS;
static constexpr int OUT_PER_PORT_ITER   = BLOCK * OUT_PORT_DIM1;
static constexpr int OUT_PER_PORT_TOTAL  = N_ITERS_2D * OUT_PER_PORT_ITER;
static constexpr size_t OUT_PER_PORT_BYTES = OUT_PER_PORT_TOTAL * sizeof(int16_t);

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

    // --- allocate XRT AIE BOs: [engine][gmio_port] ---
    static constexpr int TOTAL_GMIO = NUM_ENGINE * NUM_GMIO_PORTS;
    std::vector<xrt::aie::bo> bo_in(TOTAL_GMIO), bo_out(TOTAL_GMIO);

    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            int idx = e * NUM_GMIO_PORTS + g;
            bo_in[idx]  = xrt::aie::bo(device, IN_PER_PORT_BYTES, xrt::bo::flags::normal, 0);
            bo_out[idx] = xrt::aie::bo(device, OUT_PER_PORT_BYTES, xrt::bo::flags::normal, 0);
        }
    }

    // --- scatter packed input into per-engine, per-port BOs ---
    // Each engine gets BLOCKS_PER_ENGINE blocks; within each iteration the data is
    // linearly split across NUM_GMIO_PORTS.
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            int idx = e * NUM_GMIO_PORTS + g;
            auto* dst = bo_in[idx].map<int16_t*>();
            for (int t = 0; t < N_ITERS_2D; ++t) {
                int iter_base = (t * NUM_ENGINE + e) * ELEMS_PER_ITER;
                std::memcpy(dst + t * IN_PER_PORT_ITER,
                            &packed[iter_base + g * IN_PER_PORT_ITER],
                            IN_PER_PORT_ITER * sizeof(int16_t));
            }
        }
    }

    std::cout << "Buffers ready. "
              << PADDED_BLOCKS << " blocks (" << BLK_COLS << "x" << BLK_ROWS_PAD << "), "
              << N_ITERS_2D << " iterations, "
              << NUM_ENGINE << " engines x " << NUM_GMIO_PORTS << " GMIO ports, "
              << IN_PER_PORT_BYTES / 1024 << " KB per input port." << std::endl;

    // --- GMIO helpers ---
    using hrc = std::chrono::high_resolution_clock;

    // Build GMIO name strings: "gr.frame_src[e][g]" / "gr.frame_dst[e][g]"
    std::vector<std::string> gmio_in_names(TOTAL_GMIO), gmio_out_names(TOTAL_GMIO);
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            int idx = e * NUM_GMIO_PORTS + g;
            gmio_in_names[idx]  = "gr.frame_src[" + std::to_string(e) + "][" + std::to_string(g) + "]";
            gmio_out_names[idx] = "gr.frame_dst[" + std::to_string(e) + "][" + std::to_string(g) + "]";
        }
    }

    auto fire_in = [&]() {
        for (int i = 0; i < TOTAL_GMIO; ++i)
            bo_in[i].async(gmio_in_names[i],
                           XCL_BO_SYNC_BO_GMIO_TO_AIE, IN_PER_PORT_BYTES, 0);
    };

    auto fire_out = [&](std::vector<std::optional<xrt::bo::async_handle>>& handles) {
        for (int i = 0; i < TOTAL_GMIO; ++i)
            handles[i] = bo_out[i].async(gmio_out_names[i],
                                         XCL_BO_SYNC_BO_AIE_TO_GMIO, OUT_PER_PORT_BYTES, 0);
    };

    auto run_one = [&]() {
        ghdl.run(N_ITERS_2D);
        std::vector<std::optional<xrt::bo::async_handle>> handles(TOTAL_GMIO);
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
    std::vector<std::optional<xrt::bo::async_handle>> out_handles(TOTAL_GMIO);
    fire_out(out_handles);

    auto t0 = hrc::now();
    fire_in();
    for (auto& h : out_handles) h->wait();
    auto t1 = hrc::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(t1 - t0).count();

    // --- report ---
    double total_bytes = (double)NUM_ENGINE * (IN_PER_PORT_BYTES + OUT_PER_PORT_BYTES) * NUM_GMIO_PORTS;
    double bw_gbs      = total_bytes / elapsed_us / 1e3;
    double fps          = 1e6 / elapsed_us;

    std::cout << "Frame:      " << FRAME_W << "x" << FRAME_H << " (2D IDCT, 64x64 blocks)" << std::endl;
    std::cout << "Engines:    " << NUM_ENGINE << " (" << NUM_CU << " H-V CU pairs each)" << std::endl;
    std::cout << "GMIO ports: " << NUM_GMIO_PORTS << " per engine (GMIO_LEVEL=" << GMIO_LEVEL << ")" << std::endl;
    std::cout << "Buffer:     " << IN_PER_PORT_BYTES / 1024 << " KB in + "
              << OUT_PER_PORT_BYTES / 1024 << " KB out per port" << std::endl;
    std::cout << "Total data: " << total_bytes / (1 << 20) << " MB" << std::endl;
    std::cout << "Latency:    " << elapsed_us << " us" << std::endl;
    std::cout << "Bandwidth:  " << bw_gbs << " GB/s" << std::endl;
    std::cout << "FPS:        " << fps << std::endl;

    return 0;
}
