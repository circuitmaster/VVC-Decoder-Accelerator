#pragma once
#include <adf.h>
#include <array>
#include <utility>
#include <string>

#include "idct_ii.h"
#include "coeff.h"
#include "reshape.h"


// class B16 : public graph {

// private:
//     kernel k_idct_ii_b16;

// public:
//     input_plio plio_stream_in;
//     output_plio plio_stream_out;

//     // runtime port
//     input_port size;
//     input_port shift;

//     B16() {

//         double pl_clock = 625.0;

//         // config core
//         k_idct_ii_b16 = kernel::create_object<idct_ii_b16_buffer_i16_i8_acc32>(idct_ii_b16_coeff_i8);
//         source(k_idct_ii_b16) = "src/idct_ii.cpp";
//         runtime<ratio>(k_idct_ii_b16) = 0.95;

//         plio_stream_in = input_plio::create("plio_in", plio_64_bits, "data/in_i16.txt", pl_clock);
//         plio_stream_out = output_plio::create("plio_out", plio_64_bits, "data/out.txt", pl_clock);

//         connect(plio_stream_in.out[0], k_idct_ii_b16.in[0]);
//         write_access(k_idct_ii_b16.in[0]) = input_tiling_write_b16_i16;
//         connect(k_idct_ii_b16.out[0], plio_stream_out.in[0]);
//         read_access(k_idct_ii_b16.out[0]) = output_detiling_read_b16_i16;

//         connect<parameter>(size, k_idct_ii_b16.in[1]);
//         connect<parameter>(shift, k_idct_ii_b16.in[2]);
//     }
// };


// class B32 : public graph {

// private:
//     kernel k_idct_ii_b32;

// public:
//     input_plio plio_stream_in;
//     output_plio plio_stream_out;

//     // runtime port
//     input_port size;
//     input_port shift;

//     B32() {

//         double pl_clock = 625.0;

//         // config core
//         k_idct_ii_b32 = kernel::create_object<idct_ii_b32_buffer_i16_i8_acc32>(idct_ii_b32_coeff_i8);
//         source(k_idct_ii_b32) = "src/idct_ii.cpp";
//         runtime<ratio>(k_idct_ii_b32) = 0.95;

//         plio_stream_in = input_plio::create("plio_in", plio_64_bits, "data/in_i16.txt", pl_clock);
//         plio_stream_out = output_plio::create("plio_out", plio_64_bits, "data/out.txt", pl_clock);

//         connect(plio_stream_in.out[0], k_idct_ii_b32.in[0]);
//         write_access(k_idct_ii_b32.in[0]) = input_tiling_write_b32_i16;
//         connect(k_idct_ii_b32.out[0], plio_stream_out.in[0]);
//         read_access(k_idct_ii_b32.out[0]) = output_detiling_read_b32_i16;

//         connect<parameter>(size, k_idct_ii_b32.in[1]);
//         connect<parameter>(shift, k_idct_ii_b32.in[2]);
//     }
// };

// class B64 : public graph {

// private:
//     kernel k_idct_ii_b64;

// public:
//     input_plio plio_stream_in;
//     output_plio plio_stream_out;

//     // runtime port
//     input_port size;
//     input_port shift;

//     B64() {

//         double pl_clock = 625.0;

//         // config core
//         k_idct_ii_b64 = kernel::create_object<idct_ii_b64_buffer_i16_i8_acc32>(idct_ii_b64_coeff_i8);
//         source(k_idct_ii_b64) = "src/idct_ii.cpp";
//         runtime<ratio>(k_idct_ii_b64) = 0.95;

//         plio_stream_in = input_plio::create("plio_in", plio_64_bits, "data/in_i16.txt", pl_clock);
//         plio_stream_out = output_plio::create("plio_out", plio_64_bits, "data/out.txt", pl_clock);

//         connect(plio_stream_in.out[0], k_idct_ii_b64.in[0]);
//         write_access(k_idct_ii_b64.in[0]) = input_tiling_write_b64_i16;
//         connect(k_idct_ii_b64.out[0], plio_stream_out.in[0]);
//         read_access(k_idct_ii_b64.out[0]) = output_detiling_read_b64_i16;

//         connect<parameter>(size, k_idct_ii_b64.in[1]);
//         connect<parameter>(shift, k_idct_ii_b64.in[2]);
//     }
// };

class B64_STATIC : public graph {

private:
    using idct_b64 = idct_ii_b64_buffer_i16_i8_acc32_static;
    kernel krnl_idct_ii_b64_static[4];

public:
    input_gmio frame_src[4];
    output_gmio frame_dst[4];

    shared_buffer<idct_b64::TT_DATA> frame_buffer_in;
    shared_buffer<idct_b64::TT_DATA> frame_buffer_out;

    B64_STATIC() {

        size_t BW = 4000;

        int col = 10;
        int row_base = 0;

        // config core
        for(int i = 0; i < 4; ++i) {
            krnl_idct_ii_b64_static[i] = kernel::create_object<idct_b64>(idct_ii_b64_coeff_i8);
            source(krnl_idct_ii_b64_static[i]) = "src/idct_ii.cpp";
            runtime<ratio>(krnl_idct_ii_b64_static[i]) = 0.95;
            int row = row_base + 2*i;
            // location<kernel>(krnl_idct_ii_b64_static[i]) = tile(col, row);
            // location<buffer>(krnl_idct_ii_b64_static[i].in[0]) = {bank(col, row, 0), bank(col, row, 2)};
            // location<buffer>(krnl_idct_ii_b64_static[i].out[0]) = {bank(col, row, 1), bank(col, row, 3)};
            // location<stack>(krnl_idct_ii_b64_static[i]) = tile(col, row+1);
            // location<parameter>(krnl_idct_ii_b64_static[i]) = tile(col, row+1);
        }

        frame_buffer_in = shared_buffer<idct_b64::TT_DATA>::create({NUM_CORES*N_WINDOWS*idct_b64::BATCH_SIZE * idct_b64::BLOCK_SIZE}, 4, 4);
        frame_buffer_out = shared_buffer<idct_b64::TT_DATA>::create({NUM_CORES*N_WINDOWS*idct_b64::BATCH_SIZE * idct_b64::BLOCK_SIZE}, 4, 4);

        num_buffers(frame_buffer_in) = 2;
        num_buffers(frame_buffer_out) = 2;

        auto gmio_write_frame_buffer   = gen_gmio_write_in_patterns();
        auto dma_read_frame_buffer    = gen_frame_in_buffer_read_patterns();
        auto dma_write_frame_buffer  = gen_frame_out_buffer_write_patterns();
        auto gmio_read_frame_buffer   = gen_gmio_read_out_patterns();

        for (int i = 0; i < 4; i++) {

            frame_src[i] = input_gmio::create("src[" + std::to_string(i) + "]", 256, BW);
            frame_dst[i] = output_gmio::create("dst[" + std::to_string(i) + "]", 256, BW);

            // connect gmio to shared buffers
            connect(frame_src[i].out[0], frame_buffer_in.in[i]);
            write_access(frame_buffer_in.in[i]) = gmio_write_frame_buffer[i];
            connect(frame_buffer_out.out[i], frame_dst[i].in[0]);
            read_access(frame_buffer_out.out[i]) = gmio_read_frame_buffer[i];

            // connect shared buffers to kernel
            connect(frame_buffer_in.out[i], krnl_idct_ii_b64_static[i].in[0]);
            read_access(frame_buffer_in.out[i]) = dma_read_frame_buffer[i];
            write_access(krnl_idct_ii_b64_static[i].in[0]) = kernel_input_tiling_write;
            connect(krnl_idct_ii_b64_static[i].out[0], frame_buffer_out.in[i]);
            read_access(krnl_idct_ii_b64_static[i].out[0]) = kernel_output_tiling_read;
            write_access(frame_buffer_out.in[i]) = dma_write_frame_buffer[i];
        }
    }
};


// ============================================================
// 2D IDCT: horizontal → shared buffer → vertical (NUM_CU cores each)
// ============================================================

static constexpr int NUM_CU = NUM_CORES;  // number of compute units (H+V pairs)

class B64_2D_STATIC : public graph {

private:
    kernel krnl_h[NUM_CU];
    kernel krnl_v[NUM_CU];

public:
    input_gmio  frame_src[NUM_CU];
    output_gmio frame_dst[NUM_CU];

    shared_buffer<H_K::TT_DATA> buf_in;
    shared_buffer<V_K::TT_DATA> buf_out;

    B64_2D_STATIC() {

        size_t BW = 4000;

        // --- create kernels ---
        for (int i = 0; i < NUM_CU; ++i) {
            krnl_h[i] = kernel::create_object<H_K>(idct_ii_b64_coeff_i8);
            source(krnl_h[i]) = "src/idct_ii.cpp";
            runtime<ratio>(krnl_h[i]) = 0.95;

            krnl_v[i] = kernel::create_object<V_K>(idct_ii_b64_coeff_i8);
            source(krnl_v[i]) = "src/idct_ii.cpp";
            runtime<ratio>(krnl_v[i]) = 0.95;
        }

        // --- create shared buffers ---
        buf_in  = shared_buffer<H_K::TT_DATA>::create(
            {NUM_CU * N_WINDOWS_2D * BLOCK_ELEMS}, NUM_CU, NUM_CU);
        buf_out = shared_buffer<V_K::TT_DATA>::create(
            {NUM_CU * N_WINDOWS_2D * BLOCK_ELEMS}, NUM_CU, NUM_CU);

        num_buffers(buf_in)  = 2;
        num_buffers(buf_out) = 2;

        // --- generate DMA patterns ---
        auto gmio_wr_in     = gen_2d_gmio_write_in();
        auto shared_rd_in   = gen_2d_shared_in_read();
        auto shared_wr_out  = gen_2d_shared_out_write();
        auto gmio_rd_out    = gen_2d_gmio_read_out();

        for (int i = 0; i < NUM_CU; ++i) {

            frame_src[i] = input_gmio::create("src[" + std::to_string(i) + "]", 256, BW);
            frame_dst[i] = output_gmio::create("dst[" + std::to_string(i) + "]", 256, BW);

            // --- GMIO → buf_in → H kernel ---
            connect(frame_src[i].out[0], buf_in.in[i]);
            write_access(buf_in.in[i]) = gmio_wr_in[i];

            connect(buf_in.out[i], krnl_h[i].in[0]);
            read_access(buf_in.out[i]) = shared_rd_in[i];
            write_access(krnl_h[i].in[0]) = h_kernel_input_write;

            // --- H kernel → V kernel (direct L1 connection) ---
            connect(krnl_h[i].out[0], krnl_v[i].in[0]);

            // --- V kernel → buf_out → GMIO ---
            connect(krnl_v[i].out[0], buf_out.in[i]);
            read_access(krnl_v[i].out[0]) = v_kernel_output_read;
            write_access(buf_out.in[i]) = shared_wr_out[i];

            connect(buf_out.out[i], frame_dst[i].in[0]);
            read_access(buf_out.out[i]) = gmio_rd_out[i];
        }
    }
};