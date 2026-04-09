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

// class B64_STATIC : public graph {

// private:
//     using idct_b64 = idct_ii_b64_buffer_i16_i8_acc32_static;
//     kernel krnl_idct_ii_b64_static[4];

// public:
//     input_gmio frame_src[4];
//     output_gmio frame_dst[4];

//     shared_buffer<idct_b64::TT_DATA> frame_buffer_in;
//     shared_buffer<idct_b64::TT_DATA> frame_buffer_out;

//     B64_STATIC() {

//         size_t BW = 4000;

//         int col = 10;
//         int row_base = 0;

//         // config core
//         for(int i = 0; i < 4; ++i) {
//             krnl_idct_ii_b64_static[i] = kernel::create_object<idct_b64>(idct_ii_b64_coeff_i8);
//             source(krnl_idct_ii_b64_static[i]) = "src/idct_ii.cpp";
//             runtime<ratio>(krnl_idct_ii_b64_static[i]) = 0.95;
//             int row = row_base + 2*i;
//             // location<kernel>(krnl_idct_ii_b64_static[i]) = tile(col, row);
//             // location<buffer>(krnl_idct_ii_b64_static[i].in[0]) = {bank(col, row, 0), bank(col, row, 2)};
//             // location<buffer>(krnl_idct_ii_b64_static[i].out[0]) = {bank(col, row, 1), bank(col, row, 3)};
//             // location<stack>(krnl_idct_ii_b64_static[i]) = tile(col, row+1);
//             // location<parameter>(krnl_idct_ii_b64_static[i]) = tile(col, row+1);
//         }

//         frame_buffer_in = shared_buffer<idct_b64::TT_DATA>::create({NUM_CORES*N_WINDOWS*idct_b64::BATCH_SIZE * idct_b64::BLOCK_SIZE}, 4, 4);
//         frame_buffer_out = shared_buffer<idct_b64::TT_DATA>::create({NUM_CORES*N_WINDOWS*idct_b64::BATCH_SIZE * idct_b64::BLOCK_SIZE}, 4, 4);

//         num_buffers(frame_buffer_in) = 2;
//         num_buffers(frame_buffer_out) = 2;

//         auto gmio_write_frame_buffer   = gen_gmio_write_in_patterns();
//         auto dma_read_frame_buffer    = gen_frame_in_buffer_read_patterns();
//         auto dma_write_frame_buffer  = gen_frame_out_buffer_write_patterns();
//         auto gmio_read_frame_buffer   = gen_gmio_read_out_patterns();

//         for (int i = 0; i < 4; i++) {

//             frame_src[i] = input_gmio::create("src[" + std::to_string(i) + "]", 256, BW);
//             frame_dst[i] = output_gmio::create("dst[" + std::to_string(i) + "]", 256, BW);

//             // connect gmio to shared buffers
//             connect(frame_src[i].out[0], frame_buffer_in.in[i]);
//             write_access(frame_buffer_in.in[i]) = gmio_write_frame_buffer[i];
//             connect(frame_buffer_out.out[i], frame_dst[i].in[0]);
//             read_access(frame_buffer_out.out[i]) = gmio_read_frame_buffer[i];

//             // connect shared buffers to kernel
//             connect(frame_buffer_in.out[i], krnl_idct_ii_b64_static[i].in[0]);
//             read_access(frame_buffer_in.out[i]) = dma_read_frame_buffer[i];
//             write_access(krnl_idct_ii_b64_static[i].in[0]) = kernel_input_tiling_write;
//             connect(krnl_idct_ii_b64_static[i].out[0], frame_buffer_out.in[i]);
//             read_access(krnl_idct_ii_b64_static[i].out[0]) = kernel_output_tiling_read;
//             write_access(frame_buffer_out.in[i]) = dma_write_frame_buffer[i];
//         }
//     }
// };


// ============================================================
// 2D IDCT: horizontal → shared buffer → vertical (NUM_CU cores each)
// ============================================================

static constexpr int NUM_ENGINE = 8; // number of 2D tranform Engine (columns used)

// one B64_2D engine contains up to 4 h-v pairs (CUs) to compute 2D transform in parallel
// the h-v pairs are placed vertically (per column) with one input shared buffer and one output shared buffer
class B64_2D_STATIC_ENGINE : public graph {

private:
    static constexpr unsigned ALIGN_BYTES = 4096;
    static constexpr unsigned align_up(unsigned x) {
        return (x + ALIGN_BYTES - 1) & ~(ALIGN_BYTES - 1);
    }

private:
    kernel krnl_h_transform[NUM_CU];
    kernel krnl_v_transform[NUM_CU];

public:
    shared_buffer<H_K::TT_DATA> shared_window_buf_i;
    shared_buffer<V_K::TT_DATA> shared_window_buf_o;

    port<input> ext_window2D_in[NUM_GMIO_PORTS];
    port<output> ext_window2D_out[NUM_GMIO_PORTS];

    B64_2D_STATIC_ENGINE() {

        // instantiate engine shared buffers
        shared_window_buf_i = shared_buffer<H_K::TT_DATA>::create({NUM_CU * N_WINDOWS_2D * H_K::WINDOW_SIZE}, NUM_GMIO_PORTS, NUM_CU);
        shared_window_buf_o = shared_buffer<V_K::TT_DATA>::create({NUM_CU * N_WINDOWS_2D * V_K::WINDOW_SIZE}, NUM_CU, NUM_GMIO_PORTS);

        num_buffers(shared_window_buf_i) = 2;
        num_buffers(shared_window_buf_o) = 2;

        auto gmio_wr_in    = gen_2d_gmio_write_in_ports();
        auto gmio_rd_out   = gen_2d_gmio_read_out_ports();
        auto shared_rd_in  = gen_2d_shared_in_read();
        auto shared_wr_out = gen_2d_shared_out_write();

        // connect NUM_GMIO_PORTS external ports to shared buffers
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            connect(ext_window2D_in[g], shared_window_buf_i.in[g]);
            write_access(shared_window_buf_i.in[g]) = gmio_wr_in[g];
            connect(shared_window_buf_o.out[g], ext_window2D_out[g]);
            read_access(shared_window_buf_o.out[g]) = gmio_rd_out[g];
        }

        for (int i = 0; i < NUM_CU; ++i) {
            // config the AIE-ML core
            krnl_h_transform[i] = kernel::create_object<H_K>(idct_ii_b64_coeff_i8);
            source(krnl_h_transform[i]) = "src/idct_ii.cpp";
            runtime<ratio>(krnl_h_transform[i]) = 0.95;
            krnl_v_transform[i] = kernel::create_object<V_K>(idct_ii_b64_coeff_v_i8);
            source(krnl_v_transform[i]) = "src/idct_ii.cpp";
            runtime<ratio>(krnl_v_transform[i]) = 0.95;

            // connect input shared buffer read ports to kernel buffer write ports
            connect(shared_window_buf_i.out[i], krnl_h_transform[i].in[0]);
            read_access(shared_window_buf_i.out[i]) = shared_rd_in[i];
            write_access(krnl_h_transform[i].in[0]) = h_kernel_input_write;

            // connect pipeline stage
            connect(krnl_h_transform[i].out[0], krnl_v_transform[i].in[0]);

            // connect kernel buffer read ports to output shared buffer write ports
            connect(krnl_v_transform[i].out[0], shared_window_buf_o.in[i]);
            read_access(krnl_v_transform[i].out[0]) = v_kernel_output_read;
            write_access(shared_window_buf_o.in[i]) = shared_wr_out[i];
        }
    }

    // hard placement method
    void place(int column_id) {
        for (int i = 0; i < NUM_CU; ++i) {
            location<kernel>(krnl_h_transform[i]) = tile(column_id, 2*i); // pin h kernel at even row
            location<kernel>(krnl_v_transform[i]) = tile(column_id, 2*i+1); // pin v kernel at adjcent odd row

            // input & output buffer placement
            location<buffer>(krnl_h_transform[i].in[0]) = {bank(column_id, 2*i, 0), bank(column_id, 2*i, 1)};
            location<buffer>(krnl_h_transform[i].out[0]) = {bank(column_id, 2*i+1, 0), bank(column_id, 2*i+1, 1)};
            location<buffer>(krnl_v_transform[i].in[0]) = location<buffer>(krnl_h_transform[i].out[0]);
            location<buffer>(krnl_v_transform[i].out[0]) = {bank(column_id, 2*i+1, 2), bank(column_id, 2*i+1, 3)};

            // kernel stack placement
            location<stack>(krnl_h_transform[i]) = bank(column_id, 2*i, 2);
            location<stack>(krnl_v_transform[i]) = bank(column_id, 2*i, 3);

            // coeff buffer placement
            location<parameter>(krnl_h_transform[i].param[0]) = bank(column_id, 2*i, 2);
            location<parameter>(krnl_v_transform[i].param[0]) = bank(column_id, 2*i, 3);
        }

        // calculate shared buffer size in bytes
        constexpr unsigned BUFIN_ELEMS = NUM_CU * N_WINDOWS_2D * H_K::WINDOW_SIZE;
        constexpr unsigned BUFOUT_ELEMS = NUM_CU * N_WINDOWS_2D * V_K::WINDOW_SIZE;

        constexpr unsigned IN_BYTES = BUFIN_ELEMS * sizeof(H_K::TT_DATA);
        constexpr unsigned OUT_BYTES = BUFOUT_ELEMS * sizeof(V_K::TT_DATA);

        constexpr unsigned IN_PING_BASE = 0;
        constexpr unsigned IN_PONG_BASE = align_up(IN_BYTES);

        constexpr unsigned OUT_PING_BASE = 0;
        constexpr unsigned OUT_PONG_BASE = align_up(OUT_BYTES);

        // shared buffer placement use row0 memory tile as input buffer and row1 memory tile as output buffer
        location<buffer>(shared_window_buf_i) = {
            address(column_id, /*row = 0*/0, /*pingBuf BaseAddr*/IN_PING_BASE),
            address(column_id, /*row = 0*/0, /*pongBuf BaseAddr*/IN_PONG_BASE)
        };

        location<buffer>(shared_window_buf_o) = {
            address(column_id, /*row = 1*/1, /*pingBuf BaseAddr*/OUT_PING_BASE),
            address(column_id, /*row = 1*/1, /*pongBuf BaseAddr*/OUT_PONG_BASE)
        };
    }
};


class B64_2D_STATIC : public graph {

public:
    B64_2D_STATIC_ENGINE engine[NUM_ENGINE];

public:
    input_gmio  frame_src[NUM_ENGINE][NUM_GMIO_PORTS];
    output_gmio frame_dst[NUM_ENGINE][NUM_GMIO_PORTS];

    B64_2D_STATIC() {

        size_t BW = 4000; // gmio pre-set bandwidth MB/s
        int base_col = 2; // base column id of the engine

        for (int e = 0; e < NUM_ENGINE; ++e) {

            // place one engine per adjacent column
            engine[e].place(base_col + e);

            for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
                std::string in_name  = "src[" + std::to_string(e) + "][" + std::to_string(g) + "]";
                std::string out_name = "dst[" + std::to_string(e) + "][" + std::to_string(g) + "]";

                frame_src[e][g] = input_gmio::create(in_name, 256, BW);
                frame_dst[e][g] = output_gmio::create(out_name, 256, BW);

                connect(frame_src[e][g].out[0], engine[e].ext_window2D_in[g]);
                connect(engine[e].ext_window2D_out[g], frame_dst[e][g].in[0]);
            }
        }
    }
};

// class B64_2D_STATIC : public graph {

// private:
//     kernel krnl_h[NUM_CU];
//     kernel krnl_v[NUM_CU];

// public:
//     input_gmio  frame_src[NUM_CU];
//     output_gmio frame_dst[NUM_CU];

//     shared_buffer<H_K::TT_DATA> shared_window_buf_i;
//     shared_buffer<V_K::TT_DATA> shared_window_buf_o;

//     B64_2D_STATIC() {

//         size_t BW = 4000;

//         // --- create kernels ---
//         for (int i = 0; i < NUM_CU; ++i) {
//             krnl_h[i] = kernel::create_object<H_K>(idct_ii_b64_coeff_i8);
//             source(krnl_h[i]) = "src/idct_ii.cpp";
//             runtime<ratio>(krnl_h[i]) = 0.95;

//             krnl_v[i] = kernel::create_object<V_K>(idct_ii_b64_coeff_i8);
//             source(krnl_v[i]) = "src/idct_ii.cpp";
//             runtime<ratio>(krnl_v[i]) = 0.95;
//         }

//         // --- create shared buffers ---
//         shared_window_buf_i  = shared_buffer<H_K::TT_DATA>::create(
//             {NUM_CU * N_WINDOWS_2D * BLOCK_ELEMS}, NUM_CU, NUM_CU);
//         shared_window_buf_o = shared_buffer<V_K::TT_DATA>::create(
//             {NUM_CU * N_WINDOWS_2D * BLOCK_ELEMS}, NUM_CU, NUM_CU);

//         num_buffers(shared_window_buf_i)  = 2;
//         num_buffers(shared_window_buf_o) = 2;

//         // --- generate DMA patterns ---
//         auto gmio_wr_in     = gen_2d_gmio_write_in();
//         auto shared_rd_in   = gen_2d_shared_in_read();
//         auto shared_wr_out  = gen_2d_shared_out_write();
//         auto gmio_rd_out    = gen_2d_gmio_read_out();

//         for (int i = 0; i < NUM_CU; ++i) {

//             frame_src[i] = input_gmio::create("src[" + std::to_string(i) + "]", 256, BW);
//             frame_dst[i] = output_gmio::create("dst[" + std::to_string(i) + "]", 256, BW);

//             // --- GMIO → shared_window_buf_i → H kernel ---
//             connect(frame_src[i].out[0], shared_window_buf_i.in[i]);
//             write_access(shared_window_buf_i.in[i]) = gmio_wr_in[i];

//             connect(shared_window_buf_i.out[i], krnl_h[i].in[0]);
//             read_access(shared_window_buf_i.out[i]) = shared_rd_in[i];
//             write_access(krnl_h[i].in[0]) = h_kernel_input_write;

//             // --- H kernel → V kernel (direct L1 connection) ---
//             connect(krnl_h[i].out[0], krnl_v[i].in[0]);

//             // --- V kernel → shared_window_buf_o → GMIO ---
//             connect(krnl_v[i].out[0], shared_window_buf_o.in[i]);
//             read_access(krnl_v[i].out[0]) = v_kernel_output_read;
//             write_access(shared_window_buf_o.in[i]) = shared_wr_out[i];

//             connect(shared_window_buf_o.out[i], frame_dst[i].in[0]);
//             read_access(shared_window_buf_o.out[i]) = gmio_rd_out[i];
//         }
//     }
// };