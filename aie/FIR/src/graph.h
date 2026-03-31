#pragma once
#include <adf.h>
#include <string>

#include "fir_interp.h"
#include "coeff.h"
#include "reshape.h"

class FIR_2PASS_GRAPH : public graph {

private:
    kernel krnl_h[NUM_CU];
    kernel krnl_v[NUM_CU];

public:
    input_gmio  frame_src[NUM_CU];
    output_gmio frame_dst[NUM_CU];

    // Runtime parameters: fractional positions
    input_port frac_x;
    input_port frac_y;

    shared_buffer<fir_h_kernel::TT_DATA> buf_in;
    shared_buffer<fir_v_kernel::TT_DATA> buf_out;

    FIR_2PASS_GRAPH() {

        size_t BW = 4000;

        for (int i = 0; i < NUM_CU; ++i) {
            krnl_h[i] = kernel::create_object<fir_h_kernel>(vvc_luma_coeff);
            source(krnl_h[i]) = "src/fir_interp.cpp";
            runtime<ratio>(krnl_h[i]) = 0.95;

            krnl_v[i] = kernel::create_object<fir_v_kernel>(vvc_luma_coeff);
            source(krnl_v[i]) = "src/fir_interp.cpp";
            runtime<ratio>(krnl_v[i]) = 0.95;
        }

        // Shared buffers: GMIO ↔ kernels
        buf_in = shared_buffer<fir_h_kernel::TT_DATA>::create(
            {NUM_CU * N_WINDOWS * fir_h_kernel::IN_ELEMS}, NUM_CU, NUM_CU);
        buf_out = shared_buffer<fir_v_kernel::TT_DATA>::create(
            {NUM_CU * N_WINDOWS * fir_v_kernel::OUT_ELEMS}, NUM_CU, NUM_CU);

        num_buffers(buf_in)  = 2;
        num_buffers(buf_out) = 2;

        auto gmio_wr_in   = gen_gmio_write_in();
        auto shared_rd_in  = gen_shared_in_read();
        auto shared_wr_out = gen_shared_out_write();
        auto gmio_rd_out   = gen_gmio_read_out();

        for (int i = 0; i < NUM_CU; ++i) {

            frame_src[i] = input_gmio::create("src[" + std::to_string(i) + "]", 256, BW);
            frame_dst[i] = output_gmio::create("dst[" + std::to_string(i) + "]", 256, BW);

            // GMIO → shared_buf_in → H kernel
            connect(frame_src[i].out[0], buf_in.in[i]);
            write_access(buf_in.in[i]) = gmio_wr_in[i];

            connect(buf_in.out[i], krnl_h[i].in[0]);
            read_access(buf_in.out[i]) = shared_rd_in[i];

            // H kernel → V kernel (direct L1 connection)
            connect(krnl_h[i].out[0], krnl_v[i].in[0]);

            // V kernel → shared_buf_out → GMIO
            connect(krnl_v[i].out[0], buf_out.in[i]);
            write_access(buf_out.in[i]) = shared_wr_out[i];

            connect(buf_out.out[i], frame_dst[i].in[0]);
            read_access(buf_out.out[i]) = gmio_rd_out[i];

            // Runtime parameters
            connect<parameter>(frac_x, krnl_h[i].in[1]);
            connect<parameter>(frac_y, krnl_v[i].in[1]);
        }
    }
};
