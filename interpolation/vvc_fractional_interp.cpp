#include "vvc_fractional_interp.h"

// ============================================================
// HLS pragma compatibility: ignored during g++ simulation
// ============================================================
#ifndef __SYNTHESIS__
  #define __SYNTHESIS_GUARD__
  // HLS pragmas are embedded as comments by g++ and simply ignored
#endif

// ============================================================
// Clip pixel to valid range [0, 255] for 8-bit depth
// ============================================================
static pel_t clip_pixel(acc_t val) {
#pragma HLS INLINE
    if (val < 0) return 0;
    if (val > 255) return 255;
    return (pel_t)val;
}

// ============================================================
// Single 8-tap FIR filter computation
// Corresponds to one instance of the reconfigurable datapath
// in Fig. 3 of the paper. Computes:
//   result = (sum of input[i] * coeff[i] for i=0..7) >> shift
// ============================================================
static acc_t fir_8tap(
    pixel_t samples[NTAPS],
    const coeff_t coeffs[NTAPS]
) {
#pragma HLS INLINE
#pragma HLS PIPELINE II=1

    acc_t sum = 0;

    // Unroll the 8-tap multiply-accumulate
    // This maps to the adders/shifters in the reconfigurable datapath (Fig. 3)
    FIR_TAP_LOOP:
    for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
        sum += (acc_t)samples[t] * (acc_t)coeffs[t];
    }

    return sum;
}

// ============================================================
// Horizontal filtering of one row
// Produces BLOCK_SIZE output pixels from (BLOCK_SIZE + NTAPS - 1) input pixels
// Corresponds to 8 parallel reconfigurable datapaths processing
// one row in one clock cycle (paper Section III)
// ============================================================
static void filter_row_horizontal(
    pixel_t row_in[REF_BLOCK_W],
    acc_t   row_out[BLOCK_SIZE],
    frac_t  frac_pos
) {
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

    coeff_t coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=coeffs complete

    // Load filter coefficients for this fractional position
    LOAD_COEFF:
    for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
        coeffs[t] = LUMA_FILTER[frac_pos][t];
    }

    // Apply 8-tap filter at each of the 8 output positions
    // This corresponds to the 8 parallel datapaths in Fig. 2
    HFILT_COL:
    for (int col = 0; col < BLOCK_SIZE; col++) {
#pragma HLS UNROLL
        pixel_t samples[NTAPS];
#pragma HLS ARRAY_PARTITION variable=samples complete

        // Gather 8 consecutive input samples starting at position col
        GATHER_SAMPLES:
        for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
            samples[t] = row_in[col + t];
        }

        row_out[col] = fir_8tap(samples, coeffs);
    }
}

// ============================================================
// Vertical filtering of one column
// Produces BLOCK_SIZE output pixels from (BLOCK_SIZE + NTAPS - 1) input values
// ============================================================
static void filter_col_vertical(
    acc_t   col_in[REF_BLOCK_H],
    acc_t   col_out[BLOCK_SIZE],
    frac_t  frac_pos
) {
#pragma HLS INLINE off
#pragma HLS PIPELINE II=1

    coeff_t coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=coeffs complete

    LOAD_COEFF_V:
    for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
        coeffs[t] = LUMA_FILTER[frac_pos][t];
    }

    VFILT_ROW:
    for (int row = 0; row < BLOCK_SIZE; row++) {
#pragma HLS UNROLL
        acc_t sum = 0;
        VFILT_TAP:
        for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
            sum += col_in[row + t] * (acc_t)coeffs[t];
        }
        col_out[row] = sum;
    }
}

// ============================================================
// CASE 1: Integer position (frac_x == 0 && frac_y == 0)
// Direct copy, no filtering needed
// Corresponds to filterCopy() in the software
// ============================================================
static void interp_integer(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE]
) {
#pragma HLS INLINE off

    INT_ROW:
    for (int r = 0; r < BLOCK_SIZE; r++) {
#pragma HLS PIPELINE II=1
        INT_COL:
        for (int c = 0; c < BLOCK_SIZE; c++) {
#pragma HLS UNROLL
            // Integer pixels start at offset (3,3) due to the 8-tap filter margin
            out_block[r][c] = clip_pixel((acc_t)ref_block[r + 3][c + 3]);
        }
    }
}

// ============================================================
// CASE 2: Horizontal half-pixel only (frac_x != 0, frac_y == 0)
// One-pass horizontal FIR filtering
// Corresponds to filterHor() in the software
// The paper: "If either x fraction or y fraction is zero,
//             only necessary half-pixels are interpolated"
// ============================================================
static void interp_horizontal(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE],
    frac_t  frac_x
) {
#pragma HLS INLINE off

    HONLY_ROW:
    for (int r = 0; r < BLOCK_SIZE; r++) {
#pragma HLS PIPELINE II=1

        coeff_t coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=coeffs complete

        for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
            coeffs[t] = LUMA_FILTER[frac_x][t];
        }

        HONLY_COL:
        for (int c = 0; c < BLOCK_SIZE; c++) {
#pragma HLS UNROLL
            pixel_t samples[NTAPS];
#pragma HLS ARRAY_PARTITION variable=samples complete

            for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
                // Row offset is r+3 (skip 3 margin rows for vertical centering)
                samples[t] = ref_block[r + 3][c + t];
            }

            acc_t sum = fir_8tap(samples, coeffs);
            // Single-pass: apply final shift and clip
            acc_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
            out_block[r][c] = clip_pixel(val);
        }
    }
}

// ============================================================
// CASE 3: Vertical half-pixel only (frac_x == 0, frac_y != 0)
// One-pass vertical FIR filtering
// Corresponds to filterVer() in the software
// ============================================================
static void interp_vertical(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE],
    frac_t  frac_y
) {
#pragma HLS INLINE off

    VONLY_COL:
    for (int c = 0; c < BLOCK_SIZE; c++) {
#pragma HLS PIPELINE II=1

        coeff_t coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=coeffs complete

        for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
            coeffs[t] = LUMA_FILTER[frac_y][t];
        }

        VONLY_ROW:
        for (int r = 0; r < BLOCK_SIZE; r++) {
#pragma HLS UNROLL
            pixel_t samples[NTAPS];
#pragma HLS ARRAY_PARTITION variable=samples complete

            for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
                // Column offset is c+3 (skip 3 margin columns)
                samples[t] = ref_block[r + t][c + 3];
            }

            acc_t sum = fir_8tap(samples, coeffs);
            acc_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
            out_block[r][c] = clip_pixel(val);
        }
    }
}

// ============================================================
// CASE 4: Quarter-pixel (frac_x != 0 && frac_y != 0)
// Two-pass filtering: horizontal first, then vertical
// This corresponds to the main pipeline in the paper:
//   1. Horizontal FIR on 15x15 input → 8x15 intermediate (stored in transpose memory)
//   2. Vertical FIR on 8x15 intermediate → 8x8 output
// Corresponds to filterWxH_N8() in the software
// ============================================================
static void interp_quarter(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE],
    frac_t  frac_x,
    frac_t  frac_y
) {
#pragma HLS INLINE off

    // --------------------------------------------------------
    // Transpose memory: stores intermediate horizontal half-pixels
    // Dimensions: 15 rows x 8 cols (15 rows needed for vertical 8-tap filter)
    // This corresponds to the 15x8x8 transpose memory in Fig. 2
    // --------------------------------------------------------
    acc_t transpose_mem[REF_BLOCK_H][BLOCK_SIZE];
#pragma HLS ARRAY_PARTITION variable=transpose_mem complete dim=2

    // Internal precision parameters (matching software's isFirst/isLast logic)
    const int headroom = INTERNAL_PREC - BIT_DEPTH;  // 14 - 8 = 6
    const int shift1   = FILTER_PREC - headroom;     // 6 - 6 = 0 for 8-bit
    const int offset1  = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
    const int shift2   = FILTER_PREC + headroom;     // 6 + 6 = 12 for 8-bit
    const int offset2  = (1 << (shift2 - 1));

    // --------------------------------------------------------
    // Pass 1: Horizontal filtering
    // Filter all 15 rows horizontally to produce 15x8 intermediate values
    // Paper: "15x8 horizontal half-pixels are interpolated using
    //         the integer pixels in 15 clock cycles"
    // --------------------------------------------------------
    coeff_t h_coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=h_coeffs complete

    for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
        h_coeffs[t] = LUMA_FILTER[frac_x][t];
    }

    HPASS_ROW:
    for (int r = 0; r < REF_BLOCK_H; r++) {
#pragma HLS PIPELINE II=1
        HPASS_COL:
        for (int c = 0; c < BLOCK_SIZE; c++) {
#pragma HLS UNROLL
            pixel_t samples[NTAPS];
#pragma HLS ARRAY_PARTITION variable=samples complete

            for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
                samples[t] = ref_block[r][c + t];
            }

            acc_t sum = fir_8tap(samples, h_coeffs);
            // First pass: shift to internal precision, no clipping
            if (shift1 >= 0) {
                transpose_mem[r][c] = (sum + offset1) >> shift1;
            } else {
                transpose_mem[r][c] = sum << (-shift1);
            }
        }
    }

    // --------------------------------------------------------
    // Pass 2: Vertical filtering
    // Filter 8 columns vertically using the 15x8 intermediate values
    // Paper: "8x8 quarter-pixels are interpolated using these
    //         horizontal half-pixels in 8 clock cycles"
    // --------------------------------------------------------
    coeff_t v_coeffs[NTAPS];
#pragma HLS ARRAY_PARTITION variable=v_coeffs complete

    for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
        v_coeffs[t] = LUMA_FILTER[frac_y][t];
    }

    VPASS_ROW:
    for (int r = 0; r < BLOCK_SIZE; r++) {
#pragma HLS PIPELINE II=1
        VPASS_COL:
        for (int c = 0; c < BLOCK_SIZE; c++) {
#pragma HLS UNROLL
            acc_t sum = 0;

            VPASS_TAP:
            for (int t = 0; t < NTAPS; t++) {
#pragma HLS UNROLL
                sum += transpose_mem[r + t][c] * (acc_t)v_coeffs[t];
            }

            // Second pass: final shift with rounding and clip
            acc_t val = (sum + offset2) >> shift2;
            out_block[r][c] = clip_pixel(val);
        }
    }
}

// ============================================================
// TOP-LEVEL FUNCTION
// ============================================================
// This is the synthesizable top function for Vitis HLS.
// It takes a 15x15 reference pixel window and produces an
// 8x8 interpolated output block based on fractional positions.
//
// This maps to the complete hardware in Fig. 2 of the paper:
//   - Integer Pixels Registers (ref_block input)
//   - 8 Parallel Reconfigurable Datapaths
//   - Transpose Memory (internal buffer for quarter-pel)
//   - Output Memory (out_block output)
//
// For the motion compensation use case, only ONE fractional
// position is needed per block (determined by the motion vector).
// ============================================================
void vvc_fractional_interp(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE],
    frac_t  frac_x,
    frac_t  frac_y
) {
    // --------------------------------------------------------
    // Interface pragmas
    // --------------------------------------------------------
    // Use AXI interfaces for block data transfer (matching paper's AXI-4 bus in Fig. 4)
#pragma HLS INTERFACE m_axi port=ref_block offset=slave bundle=INPUT  depth=225
#pragma HLS INTERFACE m_axi port=out_block offset=slave bundle=OUTPUT depth=64
#pragma HLS INTERFACE s_axilite port=frac_x
#pragma HLS INTERFACE s_axilite port=frac_y
#pragma HLS INTERFACE s_axilite port=return

    // --------------------------------------------------------
    // Local buffers for burst transfer
    // --------------------------------------------------------
    pixel_t ref_local[REF_BLOCK_H][REF_BLOCK_W];
#pragma HLS ARRAY_PARTITION variable=ref_local complete dim=2

    pel_t out_local[BLOCK_SIZE][BLOCK_SIZE];
#pragma HLS ARRAY_PARTITION variable=out_local complete dim=2

    // --------------------------------------------------------
    // Burst read reference block into local memory
    // --------------------------------------------------------
    LOAD_REF_ROW:
    for (int r = 0; r < REF_BLOCK_H; r++) {
#pragma HLS PIPELINE II=1
        LOAD_REF_COL:
        for (int c = 0; c < REF_BLOCK_W; c++) {
            ref_local[r][c] = ref_block[r][c];
        }
    }

    // --------------------------------------------------------
    // Dispatch based on fractional position
    // Paper Section II: "If either x fraction or y fraction is zero,
    // only necessary half-pixels are interpolated."
    // --------------------------------------------------------
    if (frac_x == 0 && frac_y == 0) {
        // Integer position: direct copy
        interp_integer(ref_local, out_local);
    }
    else if (frac_y == 0) {
        // Horizontal half-pixel only
        interp_horizontal(ref_local, out_local, frac_x);
    }
    else if (frac_x == 0) {
        // Vertical half-pixel only
        interp_vertical(ref_local, out_local, frac_y);
    }
    else {
        // Quarter-pixel: two-pass (horizontal then vertical)
        interp_quarter(ref_local, out_local, frac_x, frac_y);
    }

    // --------------------------------------------------------
    // Burst write output block
    // --------------------------------------------------------
    STORE_OUT_ROW:
    for (int r = 0; r < BLOCK_SIZE; r++) {
#pragma HLS PIPELINE II=1
        STORE_OUT_COL:
        for (int c = 0; c < BLOCK_SIZE; c++) {
            out_block[r][c] = out_local[r][c];
        }
    }
}