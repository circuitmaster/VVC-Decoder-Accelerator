#pragma once
#include <adf.h>

// VVC 8-tap luma interpolation filter coefficients (int16)
// 16 fractional positions × 8 taps, stored flat: coeff[frac * 8 + tap]
// Values range [-11, 63], stored as int16 for 16b×16b sliding_mul

inline const int16 vvc_luma_coeff[16 * 8] = {
    // pos 0: integer (passthrough)
     0,  0,   0, 64,  0,   0,  0,  0,
    // pos 1
     0,  1,  -3, 63,  4,  -2,  1,  0,
    // pos 2
    -1,  2,  -5, 62,  8,  -3,  1,  0,
    // pos 3
    -1,  3,  -8, 60, 13,  -4,  1,  0,
    // pos 4
    -1,  4, -10, 58, 17,  -5,  1,  0,
    // pos 5
    -1,  4, -11, 52, 26,  -8,  3, -1,
    // pos 6
    -1,  3,  -9, 47, 31, -10,  4, -1,
    // pos 7
    -1,  4, -11, 45, 34, -10,  4, -1,
    // pos 8: half-pixel (symmetric)
    -1,  4, -11, 40, 40, -11,  4, -1,
    // pos 9
    -1,  4, -10, 34, 45, -11,  4, -1,
    // pos 10
    -1,  4, -10, 31, 47,  -9,  3, -1,
    // pos 11
    -1,  3,  -8, 26, 52, -11,  4, -1,
    // pos 12
     0,  1,  -5, 17, 58, -10,  4, -1,
    // pos 13
     0,  1,  -4, 13, 60,  -8,  3, -1,
    // pos 14
     0,  1,  -3,  8, 62,  -5,  2, -1,
    // pos 15
     0,  1,  -2,  4, 63,  -3,  1,  0,
};
