#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <vector>
#include <xrt/xrt_device.h>
#include <xrt/xrt_kernel.h>
#include <xrt/xrt_graph.h>
#include <xrt/xrt_aie.h>

// Match kernel constants
static constexpr int NTAPS      = 8;
static constexpr int OUT_SIZE   = 8;
static constexpr int REF_SIZE   = 15;
static constexpr int REF_COLS   = 16;
static constexpr int BATCH_SIZE = 64;
static constexpr int NUM_CORES  = 4;
static constexpr int N_WINDOWS  = 2;

static constexpr int IN_ELEMS   = BATCH_SIZE * REF_SIZE * REF_COLS;
static constexpr int OUT_ELEMS  = BATCH_SIZE * OUT_SIZE * OUT_SIZE;
static constexpr int N_ITERS    = 4;

static constexpr int PER_CORE_IN  = N_ITERS * N_WINDOWS * IN_ELEMS;
static constexpr int PER_CORE_OUT = N_ITERS * N_WINDOWS * OUT_ELEMS;
static constexpr size_t PER_CORE_IN_BYTES  = PER_CORE_IN * sizeof(int16_t);
static constexpr size_t PER_CORE_OUT_BYTES = PER_CORE_OUT * sizeof(int16_t);

static constexpr double AIE_FREQ_GHZ = 1.25;

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <fir_interp_aie.xclbin>" << std::endl;
        return 1;
    }

    int test_frac_x = 4;
    int test_frac_y = 8;

    auto device = xrt::device(0);
    auto uuid   = device.load_xclbin(argv[1]);
    std::cout << "xclbin loaded!" << std::endl;

    auto ghdl = xrt::graph(device, uuid, "gr");

    // Allocate BOs
    std::vector<xrt::aie::bo> bo_in, bo_out;
    for (int i = 0; i < NUM_CORES; i++) {
        bo_in.emplace_back(device, PER_CORE_IN_BYTES, xrt::bo::flags::normal, 0);
        bo_out.emplace_back(device, PER_CORE_OUT_BYTES, xrt::bo::flags::normal, 0);
    }

    // Fill input with pixel-like values
    for (int i = 0; i < NUM_CORES; i++) {
        auto* src = bo_in[i].map<int16_t*>();
        for (int j = 0; j < PER_CORE_IN; j++)
            src[j] = (int16_t)((i * PER_CORE_IN + j) % 200);
    }

    int total_blocks = NUM_CORES * N_ITERS * N_WINDOWS * BATCH_SIZE;
    std::cout << "Buffers ready. "
              << total_blocks << " blocks, "
              << "frac=(" << test_frac_x << "," << test_frac_y << "), "
              << PER_CORE_IN_BYTES / 1024 << " KB in / "
              << PER_CORE_OUT_BYTES / 1024 << " KB out per core." << std::endl;

    // Set runtime parameters
    ghdl.update("gr.frac_x", test_frac_x);
    ghdl.update("gr.frac_y", test_frac_y);

    // GMIO helpers
    using hrc = std::chrono::high_resolution_clock;

    auto fire_in = [&]() {
        for (int i = 0; i < NUM_CORES; i++)
            bo_in[i].async("gr.frame_src[" + std::to_string(i) + "]",
                           XCL_BO_SYNC_BO_GMIO_TO_AIE, PER_CORE_IN_BYTES, 0);
    };

    auto fire_out = [&](std::vector<std::optional<xrt::bo::async_handle>>& handles) {
        for (int i = 0; i < NUM_CORES; i++)
            handles[i] = bo_out[i].async("gr.frame_dst[" + std::to_string(i) + "]",
                                         XCL_BO_SYNC_BO_AIE_TO_GMIO, PER_CORE_OUT_BYTES, 0);
    };

    auto run_one = [&]() {
        ghdl.run(N_ITERS);
        std::vector<std::optional<xrt::bo::async_handle>> handles(NUM_CORES);
        fire_out(handles);
        fire_in();
        for (auto& h : handles) h->wait();
    };

    // Warm-up
    std::cout << "Warming up..." << std::endl;
    for (int w = 0; w < 2; w++) {
        if (w > 0) ghdl.reset();
        run_one();
    }

    // Timed run
    ghdl.reset();
    ghdl.run(N_ITERS);
    std::vector<std::optional<xrt::bo::async_handle>> out_handles(NUM_CORES);
    fire_out(out_handles);

    auto t0 = hrc::now();
    fire_in();
    for (auto& h : out_handles) h->wait();
    auto t1 = hrc::now();

    double elapsed_us = std::chrono::duration<double, std::micro>(t1 - t0).count();

    // Report
    double total_in  = (double)NUM_CORES * PER_CORE_IN_BYTES;
    double total_out = (double)NUM_CORES * PER_CORE_OUT_BYTES;
    double total_bytes = total_in + total_out;
    double bw_gbs = total_bytes / elapsed_us / 1e3;
    double blocks_per_sec = (double)total_blocks / elapsed_us * 1e6;

    std::cout << "Blocks:     " << total_blocks << std::endl;
    std::cout << "Total data: " << total_bytes / 1024 << " KB" << std::endl;
    std::cout << "Latency:    " << elapsed_us << " us" << std::endl;
    std::cout << "Bandwidth:  " << bw_gbs << " GB/s" << std::endl;
    std::cout << "Throughput: " << blocks_per_sec / 1e6 << " M blocks/s" << std::endl;

    return 0;
}
