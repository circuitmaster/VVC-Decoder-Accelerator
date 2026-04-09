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

// Frame dimensions
static constexpr int FRAME_W = 1920;
static constexpr int FRAME_H = 1080;

// Kernel tile parameters (must match idct_ii.h)
static constexpr int BLOCK_SIZE  = 64;
static constexpr int BATCH_SIZE  = 128;
static constexpr int NUM_CORES   = 4;
static constexpr int N_WINDOWS   = 2;

// Block/batch layout
static constexpr int BLOCKS_PER_ROW = FRAME_W / BLOCK_SIZE;                     // 30
static constexpr int TOTAL_BLOCKS   = BLOCKS_PER_ROW * FRAME_H;                 // 32400
static constexpr int TOTAL_BATCHES  = (TOTAL_BLOCKS + BATCH_SIZE - 1) / BATCH_SIZE; // 254
static constexpr int PADDED_BATCHES = ((TOTAL_BATCHES + NUM_CORES * N_WINDOWS - 1)
                                       / (NUM_CORES * N_WINDOWS))
                                       * (NUM_CORES * N_WINDOWS);                // 256
static constexpr int N_ITERS        = PADDED_BATCHES / (NUM_CORES * N_WINDOWS); // 32

static constexpr int BATCHES_PER_CORE = PADDED_BATCHES / NUM_CORES;             // 64
static constexpr int PER_CORE         = BATCHES_PER_CORE * BATCH_SIZE * BLOCK_SIZE; // 524288
static constexpr size_t PER_CORE_BYTES = PER_CORE * sizeof(int16_t);             // 1 MB

// AIE-ML clock on VEK280 = 1 GHz
static constexpr double AIE_FREQ_GHZ = 1.25;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <idct_ii_aie.xclbin>" << std::endl;
        return 1;
    }

    auto device = xrt::device(0);
    auto uuid   = device.load_xclbin(argv[1]);
    std::cout << "xclbin loaded!" << std::endl;

    auto ghdl = xrt::graph(device, uuid, "gr");

    // --- simulate a 1920x1080 frame ---
    std::vector<int16_t> frame(FRAME_H * FRAME_W);
    for (int r = 0; r < FRAME_H; ++r)
        for (int c = 0; c < FRAME_W; ++c)
            frame[r * FRAME_W + c] = (int16_t)((r * FRAME_W + c) % 128);

    // --- reorder frame into packed blocks ---
    std::vector<int16_t> packed(PADDED_BATCHES * BATCH_SIZE * BLOCK_SIZE, 0);
    for (int r = 0; r < FRAME_H; ++r) {
        for (int cb = 0; cb < BLOCKS_PER_ROW; ++cb) {
            int block_id = r * BLOCKS_PER_ROW + cb;
            int batch    = block_id / BATCH_SIZE;
            int within   = block_id % BATCH_SIZE;
            std::memcpy(&packed[(batch * BATCH_SIZE + within) * BLOCK_SIZE],
                        &frame[r * FRAME_W + cb * BLOCK_SIZE],
                        BLOCK_SIZE * sizeof(int16_t));
        }
    }

    // --- allocate XRT AIE BOs ---
    std::vector<xrt::aie::bo> bo_in, bo_out;
    for (int i = 0; i < NUM_CORES; i++) {
        bo_in.emplace_back(device, PER_CORE_BYTES, xrt::bo::flags::normal, 0);
        bo_out.emplace_back(device, PER_CORE_BYTES, xrt::bo::flags::normal, 0);
    }

    // --- fill input BOs from packed buffer ---
    for (int i = 0; i < NUM_CORES; i++) {
        auto* src = bo_in[i].map<int16_t*>();
        std::memcpy(src, &packed[i * PER_CORE], PER_CORE_BYTES);
    }
    std::cout << "Buffers ready. "
              << PADDED_BATCHES << " batches, "
              << N_ITERS << " iterations, "
              << PER_CORE_BYTES / 1024 << " KB per core." << std::endl;

    // --- GMIO transfer helpers (sequential with per-core timing) ---
    using hrc = std::chrono::high_resolution_clock;

    auto fire_in = [&](bool verbose = false) {
        auto t_all = hrc::now();
        for (int i = 0; i < NUM_CORES; i++) {
            auto t_start = hrc::now();
            bo_in[i].async("gr.frame_src[" + std::to_string(i) + "]",
                           XCL_BO_SYNC_BO_GMIO_TO_AIE, PER_CORE_BYTES, 0);
            auto t_end = hrc::now();
            if (verbose)
                std::cout << "  GMIO IN[" << i << "]  "
                          << std::chrono::duration<double, std::micro>(t_start - t_all).count() << " -> "
                          << std::chrono::duration<double, std::micro>(t_end - t_all).count() << " us" << std::endl;
        }
        if (verbose) {
            auto t_done = hrc::now();
            std::cout << "  GMIO IN total: "
                      << std::chrono::duration<double, std::micro>(t_done - t_all).count() << " us" << std::endl;
        }
    };

    auto fire_out = [&](std::vector<std::optional<xrt::bo::async_handle>>& handles, bool verbose = false) {
        auto t_all = hrc::now();
        for (int i = 0; i < NUM_CORES; i++) {
            auto t_start = hrc::now();
            handles[i] = bo_out[i].async("gr.frame_dst[" + std::to_string(i) + "]",
                                         XCL_BO_SYNC_BO_AIE_TO_GMIO, PER_CORE_BYTES, 0);
            auto t_end = hrc::now();
            if (verbose)
                std::cout << "  GMIO OUT[" << i << "] "
                          << std::chrono::duration<double, std::micro>(t_start - t_all).count() << " -> "
                          << std::chrono::duration<double, std::micro>(t_end - t_all).count() << " us" << std::endl;
        }
        if (verbose) {
            auto t_done = hrc::now();
            std::cout << "  GMIO OUT total: "
                      << std::chrono::duration<double, std::micro>(t_done - t_all).count() << " us" << std::endl;
        }
    };

    auto run_one = [&](bool verbose = false) {
        ghdl.run(N_ITERS);
        std::vector<std::optional<xrt::bo::async_handle>> handles(NUM_CORES);
        fire_out(handles, verbose);
        fire_in(verbose);
        for (auto& h : handles) h->wait();
    };

    // --- warm-up ---
    std::cout << "Warming up..." << std::endl;
    for (int w = 0; w < 2; w++) {
        if (w > 0) ghdl.reset();
        run_one();
    }

    // --- timed run (with GMIO timing breakdown) ---
    ghdl.reset();

    std::cout << "\n--- Timed run GMIO breakdown ---" << std::endl;
    ghdl.run(N_ITERS);
    std::vector<std::optional<xrt::bo::async_handle>> out_handles(NUM_CORES);
    fire_out(out_handles, true);

    auto t0 = hrc::now();
    fire_in(true);
    for (int i = 0; i < NUM_CORES; i++) {
        auto tw0 = hrc::now();
        out_handles[i]->wait();
        auto tw1 = hrc::now();
        std::cout << "  OUT[" << i << "] wait: "
                  << std::chrono::duration<double, std::micro>(tw1 - tw0).count() << " us" << std::endl;
    }
    auto t1 = hrc::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(t1 - t0).count();
    std::cout << "---" << std::endl;

    // --- report ---
    double total_bytes = 2.0 * NUM_CORES * PER_CORE_BYTES;  // in + out
    double bw_gbs      = total_bytes / elapsed_us / 1e3;
    double fps          = 1e6 / elapsed_us;  // one frame per run

    std::cout << "Frame:      " << FRAME_W << "x" << FRAME_H << std::endl;
    std::cout << "Cores:      " << NUM_CORES << std::endl;
    std::cout << "Buffer:     " << PER_CORE_BYTES / 1024 << " KB per core" << std::endl;
    std::cout << "Total data: " << total_bytes / (1 << 20) << " MB" << std::endl;
    std::cout << "Latency:    " << elapsed_us << " us" << std::endl;
    std::cout << "Bandwidth:  " << bw_gbs << " GB/s" << std::endl;
    std::cout << "FPS:        " << fps << std::endl;

    return 0;
}
