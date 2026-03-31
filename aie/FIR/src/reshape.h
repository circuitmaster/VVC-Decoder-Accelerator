#pragma once

#include <adf.h>
#include <array>

#include "fir_interp.h"

static constexpr int NUM_CU    = 1;    // number of H+V pairs
static constexpr int N_WINDOWS = 2;    // batches per CU per graph run

// --- GMIO → shared_buf_in: linear write, per-CU offset ---
std::array<adf::tiling_parameters, NUM_CU> gen_gmio_write_in() {
    std::array<adf::tiling_parameters, NUM_CU> p;
    constexpr int PER_CU = N_WINDOWS * fir_h_kernel::IN_ELEMS;
    for (int i = 0; i < NUM_CU; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CU * PER_CU)},
            .tiling_dimension = {1},
            .offset = {(int)(i * PER_CU)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = PER_CU},
            }
        };
    }
    return p;
}

// --- shared_buf_in → H kernel: one batch per iteration ---
std::array<adf::tiling_parameters, NUM_CU> gen_shared_in_read() {
    std::array<adf::tiling_parameters, NUM_CU> p;
    constexpr int PER_CU = N_WINDOWS * fir_h_kernel::IN_ELEMS;
    for (int i = 0; i < NUM_CU; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CU * PER_CU)},
            .tiling_dimension = {fir_h_kernel::IN_ELEMS},
            .offset = {(int)(i * PER_CU)},
            .tile_traversal = {
                {.dimension = 0, .stride = fir_h_kernel::IN_ELEMS, .wrap = N_WINDOWS},
            }
        };
    }
    return p;
}

// --- V kernel → shared_buf_out: linear write, per-CU offset ---
std::array<adf::tiling_parameters, NUM_CU> gen_shared_out_write() {
    std::array<adf::tiling_parameters, NUM_CU> p;
    constexpr int PER_CU = N_WINDOWS * fir_v_kernel::OUT_ELEMS;
    for (int i = 0; i < NUM_CU; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CU * PER_CU)},
            .tiling_dimension = {1},
            .offset = {(int)(i * PER_CU)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = PER_CU},
            }
        };
    }
    return p;
}

// --- shared_buf_out → GMIO: linear read, per-CU offset ---
std::array<adf::tiling_parameters, NUM_CU> gen_gmio_read_out() {
    std::array<adf::tiling_parameters, NUM_CU> p;
    constexpr int PER_CU = N_WINDOWS * fir_v_kernel::OUT_ELEMS;
    for (int i = 0; i < NUM_CU; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CU * PER_CU)},
            .tiling_dimension = {1},
            .offset = {(int)(i * PER_CU)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = PER_CU},
            }
        };
    }
    return p;
}
