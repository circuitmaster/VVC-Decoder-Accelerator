#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vvc_fractional_interp.h"

// ============================================================
// Software reference implementation
// Matches the filter<8,...>() function from InterpolationFilter.cpp
// ============================================================
static int sw_fir_8tap(int samples[NTAPS], int frac_pos) {
    int sum = 0;
    for (int t = 0; t < NTAPS; t++) {
        sum += samples[t] * (int)LUMA_FILTER[frac_pos][t];
    }
    return sum;
}

static int clip(int val, int min_v, int max_v) {
    if (val < min_v) return min_v;
    if (val > max_v) return max_v;
    return val;
}

// Software reference: single-pass horizontal
static void sw_interp_horizontal(int ref[REF_BLOCK_H][REF_BLOCK_W],
                                  int out[BLOCK_SIZE][BLOCK_SIZE],
                                  int frac_x) {
    for (int r = 0; r < BLOCK_SIZE; r++) {
        for (int c = 0; c < BLOCK_SIZE; c++) {
            int samples[NTAPS];
            for (int t = 0; t < NTAPS; t++)
                samples[t] = ref[r + 3][c + t];
            int sum = sw_fir_8tap(samples, frac_x);
            int val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
            out[r][c] = clip(val, 0, 255);
        }
    }
}

// Software reference: single-pass vertical
static void sw_interp_vertical(int ref[REF_BLOCK_H][REF_BLOCK_W],
                                int out[BLOCK_SIZE][BLOCK_SIZE],
                                int frac_y) {
    for (int r = 0; r < BLOCK_SIZE; r++) {
        for (int c = 0; c < BLOCK_SIZE; c++) {
            int samples[NTAPS];
            for (int t = 0; t < NTAPS; t++)
                samples[t] = ref[r + t][c + 3];
            int sum = sw_fir_8tap(samples, frac_y);
            int val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
            out[r][c] = clip(val, 0, 255);
        }
    }
}

// Software reference: two-pass quarter-pixel
static void sw_interp_quarter(int ref[REF_BLOCK_H][REF_BLOCK_W],
                               int out[BLOCK_SIZE][BLOCK_SIZE],
                               int frac_x, int frac_y) {
    const int headroom = INTERNAL_PREC - BIT_DEPTH;
    const int shift1 = FILTER_PREC - headroom;
    const int offset1 = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
    const int shift2 = FILTER_PREC + headroom;
    const int offset2 = (1 << (shift2 - 1));

    // Pass 1: horizontal
    int intermediate[REF_BLOCK_H][BLOCK_SIZE];
    for (int r = 0; r < REF_BLOCK_H; r++) {
        for (int c = 0; c < BLOCK_SIZE; c++) {
            int samples[NTAPS];
            for (int t = 0; t < NTAPS; t++)
                samples[t] = ref[r][c + t];
            int sum = sw_fir_8tap(samples, frac_x);
            if (shift1 >= 0)
                intermediate[r][c] = (sum + offset1) >> shift1;
            else
                intermediate[r][c] = sum << (-shift1);
        }
    }

    // Pass 2: vertical
    for (int r = 0; r < BLOCK_SIZE; r++) {
        for (int c = 0; c < BLOCK_SIZE; c++) {
            int sum = 0;
            for (int t = 0; t < NTAPS; t++)
                sum += intermediate[r + t][c] * (int)LUMA_FILTER[frac_y][t];
            int val = (sum + offset2) >> shift2;
            out[r][c] = clip(val, 0, 255);
        }
    }
}

// ============================================================
// Testbench Main
// ============================================================
int main() {
    printf("==============================================\n");
    printf("VVC Fractional Interpolation HLS Testbench\n");
    printf("==============================================\n\n");

    int errors = 0;
    int total_tests = 0;

    // Generate a deterministic reference block with realistic pixel values
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W];
    int     ref_int[REF_BLOCK_H][REF_BLOCK_W];

    srand(42);
    for (int r = 0; r < REF_BLOCK_H; r++) {
        for (int c = 0; c < REF_BLOCK_W; c++) {
            int val = 50 + (rand() % 156);  // Range [50, 205]
            ref_block[r][c] = (pixel_t)val;
            ref_int[r][c] = val;
        }
    }

    pel_t hw_out[BLOCK_SIZE][BLOCK_SIZE];
    int   sw_out[BLOCK_SIZE][BLOCK_SIZE];

    // --------------------------------------------------------
    // Test all 16x16 = 256 fractional position combinations
    // --------------------------------------------------------
    for (int fy = 0; fy < NUM_FRAC_POS; fy++) {
        for (int fx = 0; fx < NUM_FRAC_POS; fx++) {
            total_tests++;

            // Run HLS function
            vvc_fractional_interp(ref_block, hw_out, (frac_t)fx, (frac_t)fy);

            // Run software reference
            if (fx == 0 && fy == 0) {
                // Integer: direct copy
                for (int r = 0; r < BLOCK_SIZE; r++)
                    for (int c = 0; c < BLOCK_SIZE; c++)
                        sw_out[r][c] = clip(ref_int[r + 3][c + 3], 0, 255);
            } else if (fy == 0) {
                sw_interp_horizontal(ref_int, sw_out, fx);
            } else if (fx == 0) {
                sw_interp_vertical(ref_int, sw_out, fy);
            } else {
                sw_interp_quarter(ref_int, sw_out, fx, fy);
            }

            // Compare
            bool mismatch = false;
            for (int r = 0; r < BLOCK_SIZE; r++) {
                for (int c = 0; c < BLOCK_SIZE; c++) {
                    if ((int)hw_out[r][c] != sw_out[r][c]) {
                        if (!mismatch) {
                            printf("MISMATCH at frac_x=%d, frac_y=%d:\n", fx, fy);
                            mismatch = true;
                        }
                        printf("  [%d][%d]: HW=%d, SW=%d\n",
                               r, c, (int)hw_out[r][c], sw_out[r][c]);
                        errors++;
                    }
                }
            }

            if (!mismatch && (fx == 0 || fy == 0 || (fx == 8 && fy == 8))) {
                printf("PASS: frac_x=%2d, frac_y=%2d\n", fx, fy);
            }
        }
    }

    printf("\n==============================================\n");
    printf("Total tests:  %d\n", total_tests);
    printf("Total errors: %d\n", errors);
    printf("Result: %s\n", (errors == 0) ? "ALL PASSED" : "FAILED");
    printf("==============================================\n");

    return (errors == 0) ? 0 : 1;
}