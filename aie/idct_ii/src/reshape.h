#pragma once

#include <adf.h>
#include <array>

#include "idct_ii.h"

using KernelT = idct_ii_b64_buffer_i16_i8_acc32_static;

adf::tiling_parameters input_tiling_write_b16_i16 = {
    .buffer_dimension = {8, 4, 2},  // reshape 4 x 16 to 2*(4x8) small tiles
    .tiling_dimension = {8, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 8, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 2},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};

adf::tiling_parameters output_detiling_read_b16_i16 = {
    .buffer_dimension = {4, 4, 4},  // reshape 4*(4x4) small tiles to 4 x 16
    .tiling_dimension = {4, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 4, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 4},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};

adf::tiling_parameters input_tiling_write_b32_i16 = {
    .buffer_dimension = {8, 4, 4},  // reshape 4 x 32 to 4*(4x8) small tiles
    .tiling_dimension = {8, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 8, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 4},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};

adf::tiling_parameters output_detiling_read_b32_i16 = {
    .buffer_dimension = {4, 4, 8},  // reshape 8*(4x4) small tiles to 4 x 32
    .tiling_dimension = {4, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 4, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 8},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};

adf::tiling_parameters input_tiling_write_b64_i16 = {
    .buffer_dimension = {8, 4, 8},  // reshape 4 x 64 to 8*(4x8) small tiles
    .tiling_dimension = {8, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 8, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 8},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};

adf::tiling_parameters output_detiling_read_b64_i16 = {
    .buffer_dimension = {4, 4, 16}, // reshape 16*(4x4) small tiles to 4 x 64
    .tiling_dimension = {4, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = 4, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = 16},
        {.dimension = 1, .stride = 1, .wrap = 4}
    }
};


// Each core i owns N_WINDOWS=4 consecutive frames in the shared buffer.
// The 2D logical view is {BLOCK_SIZE=64, BATCH_SIZE*16=2048}: dim0=K, dim1=M_total.
// Core i's region starts at dim1 offset  i * 4 * BATCH_SIZE.
static constexpr int NUM_CORES = 1;
static constexpr int N_WINDOWS   = 2;   // frames per core per run

// GMIO[i] -> frame_buffer_in: write N_WINDOWS frames for core i (identity layout)
std::array<adf::tiling_parameters, NUM_CORES> gen_gmio_write_in_patterns() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {KernelT::BLOCK_SIZE, N_WINDOWS * KernelT::BATCH_SIZE * NUM_CORES},
            .tiling_dimension = {1, 1},
            .offset = {0, i * N_WINDOWS * KernelT::BATCH_SIZE},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = KernelT::BLOCK_SIZE},
                {.dimension = 1, .stride = 1, .wrap = N_WINDOWS * KernelT::BATCH_SIZE},
            }
        };
    }
    return p;
}

// frame_buffer_in -> kernel[i]: read one WINDOW -> {KernelT::BLOCK_SIZE, KernelT::BATCH_SIZE} for N_WINDOWS iterations
std::array<adf::tiling_parameters, NUM_CORES> gen_frame_in_buffer_read_patterns() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {KernelT::BLOCK_SIZE, N_WINDOWS * KernelT::BATCH_SIZE * NUM_CORES},
            .tiling_dimension = {KernelT::BLOCK_SIZE, KernelT::BATCH_SIZE},
            .offset = {0, i * N_WINDOWS * KernelT::BATCH_SIZE},
            .tile_traversal = {
                {.dimension = 0, .stride = KernelT::BLOCK_SIZE, .wrap = 1},
                {.dimension = 1, .stride = KernelT::BATCH_SIZE, .wrap = N_WINDOWS},
            }
        };
    }
    return p;
}

// kernel input buffer DMA pattern
adf::tiling_parameters kernel_input_tiling_write = {
    .buffer_dimension = {KernelT::TILEdK, KernelT::BATCH_SIZE, KernelT::BLOCK_SIZE/KernelT::TILEdK},
    .tiling_dimension = {KernelT::TILEdK, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = KernelT::TILEdK, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = KernelT::BLOCK_SIZE/KernelT::TILEdK},
        {.dimension = 1, .stride = 1, .wrap = KernelT::BATCH_SIZE}
    }
};

// kernel output buffer DMA pattern: linear read (tile DMA has limited BDs)
// The tile layout {16, 16, 32} is read linearly: intra-tile (dn,dm) fastest, N_tile middle, M_tile slowest.
// The memtile write pattern (gen_frame_out_buffer_write_patterns) handles the scatter to 2D.
adf::tiling_parameters kernel_output_tiling_read = {
    .buffer_dimension = {KernelT::BATCH_SIZE * KernelT::BLOCK_SIZE},
    .tiling_dimension = {1},
    .offset = {0},
    .tile_traversal = {
        {.dimension = 0, .stride = 1, .wrap = KernelT::BATCH_SIZE * KernelT::BLOCK_SIZE},
    }
};

// kernel[i] -> frame_buffer_out: scatter tile-layout stream into {BLOCK_SIZE, BATCH_SIZE} 2D layout
// Stream from kernel output (linear read): for each M_tile(0..31), N_tile(0..15), 16 elements (dn,dm interleaved).
// tiling_dimension={TILEdN, TILEdM} writes each 16-element chunk as a 4x4 tile at (N_tile*4, M_tile*4).
std::array<adf::tiling_parameters, NUM_CORES> gen_frame_out_buffer_write_patterns() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {KernelT::BLOCK_SIZE, N_WINDOWS * KernelT::BATCH_SIZE * NUM_CORES},
            .tiling_dimension = {KernelT::TILEdN, KernelT::TILEdM},
            .offset = {0, i * N_WINDOWS * KernelT::BATCH_SIZE},
            .tile_traversal = {
                // innermost: N_tile j (0..15), advance in dim0 by TILEdN
                {.dimension = 0, .stride = KernelT::TILEdN, .wrap = KernelT::BLOCK_SIZE / KernelT::TILEdN},
                // middle: M_tile (0..31), advance in dim1 by TILEdM
                {.dimension = 1, .stride = KernelT::TILEdM, .wrap = KernelT::BATCH_SIZE / KernelT::TILEdM},
                // outer: frame advance (0..N_WINDOWS-1)
                {.dimension = 1, .stride = KernelT::BATCH_SIZE, .wrap = N_WINDOWS},
            }
        };
    }
    return p;
}

// frame_buffer_out -> GMIO[i]: reconstruct {BATCH_SIZE x BLOCK_SIZE} layout for core i
std::array<adf::tiling_parameters, NUM_CORES> gen_gmio_read_out_patterns() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {KernelT::BLOCK_SIZE, N_WINDOWS * KernelT::BATCH_SIZE * NUM_CORES},
            .tiling_dimension = {1, 1},
            .offset = {0, i * N_WINDOWS * KernelT::BATCH_SIZE},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = KernelT::BLOCK_SIZE},
                {.dimension = 1, .stride = 1, .wrap = N_WINDOWS * KernelT::BATCH_SIZE},
            }
        };
    }
    return p;
}


// ============================================================
// 2D Transform DMA patterns (horizontal + vertical pipeline)
// ============================================================

using H_K = idct_ii_b64_horizontal_transform_static;
using V_K = idct_ii_b64_vertical_transform_static;

static constexpr int BLOCK = H_K::BLOCK_SIZE;
static constexpr int BLOCK_ELEMS = BLOCK * BLOCK;
static constexpr int N_WINDOWS_2D = 2;

// GMIO → shared_buf_in: linear write, per-core offset
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_gmio_write_in() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CORES * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tiling_dimension = {1},
            .offset = {(int)(i * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = N_WINDOWS_2D * BLOCK_ELEMS},
            }
        };
    }
    return p;
}

// shared_buf_in → H kernel: one BLOCK×BLOCK block per iteration
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_shared_in_read() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CORES * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tiling_dimension = {BLOCK_ELEMS},
            .offset = {(int)(i * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tile_traversal = {
                {.dimension = 0, .stride = BLOCK_ELEMS, .wrap = N_WINDOWS_2D},
            }
        };
    }
    return p;
}

// H kernel input buffer: reshape to tiled layout for tdsc_Samples
adf::tiling_parameters h_kernel_input_write = {
    .buffer_dimension = {(int)H_K::TILEdK, BLOCK, BLOCK / (int)H_K::TILEdK},
    .tiling_dimension = {(int)H_K::TILEdK, 1, 1},
    .offset = {0, 0, 0},
    .tile_traversal = {
        {.dimension = 0, .stride = (int)H_K::TILEdK, .wrap = 1},
        {.dimension = 2, .stride = 1, .wrap = BLOCK / (int)H_K::TILEdK},
        {.dimension = 1, .stride = 1, .wrap = BLOCK}
    }
};

// H kernel output buffer: linear read
adf::tiling_parameters h_kernel_output_read = {
    .buffer_dimension = {BLOCK_ELEMS},
    .tiling_dimension = {1},
    .offset = {0},
    .tile_traversal = {
        {.dimension = 0, .stride = 1, .wrap = BLOCK_ELEMS},
    }
};

// H output → shared_buf_mid: linear pass-through (tile order matches V input)
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_shared_mid_write() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CORES * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tiling_dimension = {1},
            .offset = {(int)(i * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = N_WINDOWS_2D * BLOCK_ELEMS},
            }
        };
    }
    return p;
}

// shared_buf_mid → V kernel: one BLOCK×BLOCK block per iteration
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_shared_mid_read() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {(int)(NUM_CORES * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tiling_dimension = {BLOCK_ELEMS},
            .offset = {(int)(i * N_WINDOWS_2D * BLOCK_ELEMS)},
            .tile_traversal = {
                {.dimension = 0, .stride = BLOCK_ELEMS, .wrap = N_WINDOWS_2D},
            }
        };
    }
    return p;
}

// V kernel input buffer: linear write (H output tile order matches V tdsc_Transx)
adf::tiling_parameters v_kernel_input_write = {
    .buffer_dimension = {BLOCK_ELEMS},
    .tiling_dimension = {1},
    .offset = {0},
    .tile_traversal = {
        {.dimension = 0, .stride = 1, .wrap = BLOCK_ELEMS},
    }
};

// V kernel output buffer: linear read
adf::tiling_parameters v_kernel_output_read = {
    .buffer_dimension = {BLOCK_ELEMS},
    .tiling_dimension = {1},
    .offset = {0},
    .tile_traversal = {
        {.dimension = 0, .stride = 1, .wrap = BLOCK_ELEMS},
    }
};

// V output → shared_buf_out: scatter transposed tiles into 2D {BLOCK, BLOCK}
// Tiles arrive in pos order: X_tile fastest (0..15), Y_tile slowest (0..7)
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_shared_out_write() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {BLOCK, (int)(N_WINDOWS_2D * BLOCK * NUM_CORES)},
            .tiling_dimension = {(int)V_K::TILEdM, (int)V_K::TILEdN},
            .offset = {0, (int)(i * N_WINDOWS_2D * BLOCK)},
            .tile_traversal = {
                {.dimension = 0, .stride = (int)V_K::TILEdM, .wrap = BLOCK / (int)V_K::TILEdM},
                {.dimension = 1, .stride = (int)V_K::TILEdN, .wrap = BLOCK / (int)V_K::TILEdN},
                {.dimension = 1, .stride = BLOCK, .wrap = N_WINDOWS_2D},
            }
        };
    }
    return p;
}

// shared_buf_out → GMIO: linear read
std::array<adf::tiling_parameters, NUM_CORES> gen_2d_gmio_read_out() {
    std::array<adf::tiling_parameters, NUM_CORES> p;
    for (int i = 0; i < NUM_CORES; ++i) {
        p[i] = {
            .buffer_dimension = {BLOCK, (int)(N_WINDOWS_2D * BLOCK * NUM_CORES)},
            .tiling_dimension = {1, 1},
            .offset = {0, (int)(i * N_WINDOWS_2D * BLOCK)},
            .tile_traversal = {
                {.dimension = 0, .stride = 1, .wrap = BLOCK},
                {.dimension = 1, .stride = 1, .wrap = N_WINDOWS_2D * BLOCK},
            }
        };
    }
    return p;
}