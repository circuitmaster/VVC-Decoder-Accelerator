#include <cmath>
#include <cstdint>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <vector>
//#include <time.h>
#include <cstdlib>
#include <chrono>

//#include "ap_fixed.h"
//#include "ap_int.h"

#include "xrt/xrt_bo.h"
#include "xrt/xrt_device.h"
#include "xrt/xrt_kernel.h"

#include "IDCT_Comb.hpp"

static std::vector<char> load_xclbin(const std::string &xclbin_path) {
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
    const size_t align = 4096;
    return (bytes % align == 0) ? bytes : align * ((bytes + align - 1) / align);
}

int main(int argc, char **argv) {
    // initialize random seed with time
    std::srand(static_cast<unsigned int>(time(nullptr)));
    if (argc != 9) {
        std::cout << "Usage: " << argv[0]
                  << " <xclbin> <block_size> <size> <shift> <output_min> <output_max> <skip_in_lines> <selector>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string xclbin_path = argv[1];
    const int block_size = std::stoi(argv[2]);
    const size_t blocks = static_cast<size_t>(std::stoul(argv[3]));
    const int shift = std::stoi(argv[4]);
    const int output_min = std::stoi(argv[5]);
    const int output_max = std::stoi(argv[6]);
    const int skip_in_lines = std::stoi(argv[7]);
    const int selector = std::stoi(argv[8]);

    try {
        // Device / xclbin / kernel setup
        auto device = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin = xrt::xclbin(xclbin_data);
        auto uuid = device.load_xclbin(xclbin);
        auto kernel = xrt::kernel(device, uuid, "IDCTComb");
        std::cout << "xclbin load successfull" << std::endl;
        // Buffer sizes for `blocks` entries of ap_uint<1024>
        const size_t input_bytes = align_to_4096(blocks * sizeof(ap_uint<1024>));
        const size_t output_bytes = align_to_4096(blocks * sizeof(ap_uint<1024>));

        // Allocate buffers on appropriate banks
        auto g_in = kernel.group_id(0);
        auto g_out = kernel.group_id(1);
	
	    std::cout << "test1" << std::endl;

        xrt::bo input_bo(device, input_bytes, xrt::bo::flags::normal, g_in);
        xrt::bo output_bo(device, output_bytes, xrt::bo::flags::normal, g_out);
	
	    std::cout << "test2" << std::endl;

        ap_uint<1024> *input_ptr = input_bo.map<ap_uint<1024> *>();
        ap_uint<1024> *output_ptr = output_bo.map<ap_uint<1024> *>();
	
        std::cout << "test3" << std::endl;

        // Prepare host-side inputs
        std::vector<ap_int<1024>> host_in(blocks);
        for (size_t b = 0; b < blocks; ++b) {
            ap_int<1024> blk = 0;
            for (size_t i = 0; i < 32; ++i) {
                ap_uint<32> val = static_cast<ap_uint<32>>(rand() % 100); // Random 32-bit value
                blk.range((i + 1) * 32 - 1, i * 32) = val.range(31, 0);
            }
            host_in[b] = blk;
            input_ptr[b] = blk;
        }

        // warm up run
        auto run_warmup = kernel(input_bo, output_bo,
                          block_size, skip_in_lines, static_cast<int>(blocks), shift, output_min, output_max, selector);
        run_warmup.wait();

        // measure total time for data transfer + kernel execution + data transfer back
        auto start = std::chrono::high_resolution_clock::now();

        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
        
        auto end_input = std::chrono::high_resolution_clock::now();

        // Launch kernel
        auto run = kernel(input_bo, output_bo,
                          block_size, skip_in_lines, static_cast<int>(blocks), shift, output_min, output_max, selector);
        run.wait();

        auto end_kernel = std::chrono::high_resolution_clock::now();

        //std::cout << "run finished" << std::endl;
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::chrono::duration<double> input_time = end_input - start;
        std::chrono::duration<double> kernel_time = end_kernel - end_input;
        std::chrono::duration<double> output_time = end - end_kernel;
        std::cout << "Total execution time (including data transfer): " << elapsed.count() << " seconds" << std::endl;
        std::cout << "Input data transfer time: " << input_time.count() << " seconds" << std::endl;
        std::cout << "Kernel execution time: " << kernel_time.count() << " seconds" << std::endl;
        std::cout << "Output data transfer time: " << output_time.count() << " seconds" << std::endl;

        // Golden model execution
        std::vector<ap_int<1024>> golden_out(blocks);
        IDCTComb(host_in.data(), golden_out.data(),
              block_size, skip_in_lines, static_cast<int>(blocks), shift, output_min, output_max, selector);

        // Compare results
        bool mismatch = false;
        for (size_t b = 0; b < blocks; ++b) {
            ap_uint<1024> hw_out = output_ptr[b];
            for (size_t i = 0; i < 32; ++i) {
                int32_t golden_val = golden_out[b].range((i + 1) * 32 - 1, i * 32);
                uint32_t hw_val = hw_out.range((i + 1) * 32 - 1, i * 32);
                if (static_cast<int64_t>(golden_val) != static_cast<int64_t>(hw_val)) {
                    std::cout << "Mismatch block " << b << " elem " << i
                              << " golden=" << golden_val << " hw=" << hw_val << std::endl;
                    mismatch = true;
                }
            }
        }

        if (!mismatch) {
            std::cout << "Golden model match: all outputs identical." << std::endl;
        }

        // Optional print of first block for quick inspection
        if (blocks > 0) {
            std::cout << "First block HW out values:" << std::endl;
            for (size_t i = 0; i < 32; ++i) {
                uint32_t value = output_ptr[0].range((i + 1) * 32 - 1, i * 32);
                std::cout << "Value " << i << ": " << value << std::endl;
            }
        }

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
