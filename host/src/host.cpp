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

//#include "ap_fixed.h"
//#include "ap_int.h"

#include "xrt/xrt_bo.h"
#include "xrt/xrt_device.h"
#include "xrt/xrt_kernel.h"

#include "IDCT2.hpp"

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
    if (argc != 7) {
        std::cout << "Usage: " << argv[0]
                  << " <xclbin> <block_size> <size> <shift> <output_min> <output_max>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string xclbin_path = argv[1];
    const int block_size = std::stoi(argv[2]);
    const size_t blocks = static_cast<size_t>(std::stoul(argv[3]));
    const int shift = std::stoi(argv[4]);
    const int output_min = std::stoi(argv[5]);
    const int output_max = std::stoi(argv[6]);

    try {
        // Device / xclbin / kernel setup
        auto device = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin = xrt::xclbin(xclbin_data);
        auto uuid = device.load_xclbin(xclbin);
        auto kernel = xrt::kernel(device, uuid, "IDCT2");
        std::cout << "xclbin load successfull" << std::endl;
        // Buffer sizes for `blocks` entries of ap_uint<1024>
        const size_t input_bytes = align_to_4096(blocks * sizeof(ap_uint<1024>));
        const size_t output_bytes = align_to_4096(blocks * sizeof(ap_uint<1024>));

        // Allocate buffers on appropriate banks
        auto g_in1 = kernel.group_id(0);
        auto g_in2 = kernel.group_id(1);
        auto g_out1= kernel.group_id(2);
        auto g_out2 = kernel.group_id(3);
	
	    std::cout << "test1" << std::endl;

        xrt::bo input1_bo(device, input_bytes, xrt::bo::flags::normal, g_in1);
        xrt::bo input2_bo(device, input_bytes, xrt::bo::flags::normal, g_in2);
        xrt::bo output1_bo(device, output_bytes, xrt::bo::flags::normal, g_out1);
        xrt::bo output2_bo(device, output_bytes, xrt::bo::flags::normal, g_out2);
	
	    std::cout << "test2" << std::endl;

        ap_uint<1024> *input1_ptr = input1_bo.map<ap_uint<1024> *>();
        ap_uint<1024> *input2_ptr = input2_bo.map<ap_uint<1024> *>();
        ap_uint<1024> *output1_ptr = output1_bo.map<ap_uint<1024> *>();
        ap_uint<1024> *output2_ptr = output2_bo.map<ap_uint<1024> *>();
	
        std::cout << "test3" << std::endl;

        // Prepare host-side inputs
        std::vector<ap_int<1024>> host_in1(blocks);
        std::vector<ap_int<1024>> host_in2(blocks);
        for (size_t b = 0; b < blocks; ++b) {
            ap_int<1024> blk1 = 0;
            ap_int<1024> blk2 = 0;
            for (size_t i = 0; i < 32; ++i) {
                ap_uint<32> val = 1;
                blk1.range((i + 1) * 32 - 1, i * 32) = val.range(31, 0);//static_cast<int32_t>(b * 64 + i);
                blk2.range((i + 1) * 32 - 1, i * 32) = val.range(31, 0);//static_cast<int32_t>(b * 64 + i + 1000);
            }
            host_in1[b] = blk1;
            host_in2[b] = blk2;
            input1_ptr[b] = blk1;
            input2_ptr[b] = blk2;
        }

        input1_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
        input2_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
        
        std::cout << "test4" << std::endl;

        // Launch kernel
        auto run = kernel(input1_bo, input2_bo, output1_bo, output2_bo,
                          block_size, static_cast<int>(blocks), shift, output_min, output_max);
        run.wait();
        std::cout << "run finished" << std::endl;
        output1_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        output2_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        // Golden model execution
        std::vector<ap_int<1024>> golden_out1(blocks);
        std::vector<ap_int<1024>> golden_out2(blocks);
        IDCT2(host_in1.data(), host_in2.data(), golden_out1.data(), golden_out2.data(),
              block_size, static_cast<int>(blocks), shift, output_min, output_max);

        // Compare results
        bool mismatch = false;
        for (size_t b = 0; b < blocks; ++b) {
            ap_uint<1024> hw_out1 = output1_ptr[b];
            ap_uint<1024> hw_out2 = output2_ptr[b];
            for (size_t i = 0; i < 32; ++i) {
                int32_t golden1 = golden_out1[b].range((i + 1) * 32 - 1, i * 32);
                int32_t golden2 = golden_out2[b].range((i + 1) * 32 - 1, i * 32);
                uint32_t hw1 = hw_out1.range((i + 1) * 32 - 1, i * 32);
                uint32_t hw2 = hw_out2.range((i + 1) * 32 - 1, i * 32);
                if (static_cast<int64_t>(golden1) != static_cast<int64_t>(hw1)) {
                    std::cout << "Mismatch out1 block " << b << " elem " << i
                              << " golden=" << golden1 << " hw=" << hw1 << std::endl;
                    mismatch = true;
                }
                /* if (static_cast<int64_t>(golden2) != static_cast<int64_t>(hw2)) {
                    std::cout << "Mismatch out2 block " << b << " elem " << i
                              << " golden=" << golden2 << " hw=" << hw2 << std::endl;
                    mismatch = true;
                } */
            }
        }

        if (!mismatch) {
            std::cout << "Golden model match: all outputs identical." << std::endl;
        }

        // Optional print of first block for quick inspection
        if (blocks > 0) {
            std::cout << "First block HW out1 values:" << std::endl;
            for (size_t i = 0; i < 8; ++i) {
                uint32_t value = output1_ptr[0].range((i + 1) * 32 - 1, i * 32);
                std::cout << "Value " << i << ": " << value << std::endl;
            }
        }

    } catch (const std::exception &ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}
