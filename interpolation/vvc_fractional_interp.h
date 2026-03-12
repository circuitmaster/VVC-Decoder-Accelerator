#ifndef VVC_FRACTIONAL_INTERP_H
#define VVC_FRACTIONAL_INTERP_H

// ============================================================
// Type system: use ap_int for HLS synthesis, plain C++ for simulation
// ============================================================
#ifdef __SYNTHESIS__
  // Vitis HLS synthesis mode
  #include <ap_int.h>
  #include <hls_stream.h>
  typedef ap_int<16>  pixel_t;
  typedef ap_int<24>  acc_t;
  typedef ap_int<10>  coeff_t;
  typedef ap_uint<4>  frac_t;
  typedef ap_uint<8>  pel_t;
#else
  // Software simulation mode (g++/MSVC)
  #include <cstdint>
  typedef int16_t   pixel_t;
  typedef int32_t   acc_t;
  typedef int16_t   coeff_t;
  typedef uint8_t   frac_t;
  typedef uint8_t   pel_t;
#endif

// ============================================================
// Constants
// ============================================================
#define BLOCK_SIZE       8    // Process 8x8 blocks (as in paper)
#define NTAPS            8    // 8-tap FIR filter
#define NUM_FRAC_POS    16    // 0 (integer) + 15 fractional positions
#define FILTER_PREC      6    // Right shift by 6 after filtering
#define BIT_DEPTH        8    // Pixel bit depth
#define INTERNAL_PREC   14    // Internal precision for intermediate results

// Input reference block dimensions:
// For 8x8 output with 8-tap filter, need 3 extra pixels on each side
// Horizontal: 8 + 7 = 15 pixels wide
// Vertical:   8 + 7 = 15 pixels tall
#define REF_BLOCK_W     15    // Reference block width  (BLOCK_SIZE + NTAPS - 1)
#define REF_BLOCK_H     15    // Reference block height (BLOCK_SIZE + NTAPS - 1)

// ============================================================
// 15 VVC 8-tap FIR Filter Coefficients (Table I from paper)
// Index 0 = integer position (passthrough)
// Index 1-15 = fractional positions
// ============================================================
static const coeff_t LUMA_FILTER[NUM_FRAC_POS][NTAPS] = {
    {  0,  0,   0, 64,  0,   0,  0,  0 },  // pos 0: integer
    {  0,  1,  -3, 63,  4,  -2,  1,  0 },  // pos 1: Filter 1
    { -1,  2,  -5, 62,  8,  -3,  1,  0 },  // pos 2: Filter 2
    { -1,  3,  -8, 60, 13,  -4,  1,  0 },  // pos 3: Filter 3
    { -1,  4, -10, 58, 17,  -5,  1,  0 },  // pos 4: Filter 4
    { -1,  4, -11, 52, 26,  -8,  3, -1 },  // pos 5: Filter 5
    { -1,  3,  -9, 47, 31, -10,  4, -1 },  // pos 6: Filter 6
    { -1,  4, -11, 45, 34, -10,  4, -1 },  // pos 7: Filter 7
    { -1,  4, -11, 40, 40, -11,  4, -1 },  // pos 8: Filter 8
    { -1,  4, -10, 34, 45, -11,  4, -1 },  // pos 9: Filter 9
    { -1,  4, -10, 31, 47,  -9,  3, -1 },  // pos 10: Filter 10
    { -1,  3,  -8, 26, 52, -11,  4, -1 },  // pos 11: Filter 11
    {  0,  1,  -5, 17, 58, -10,  4, -1 },  // pos 12: Filter 12
    {  0,  1,  -4, 13, 60,  -8,  3, -1 },  // pos 13: Filter 13
    {  0,  1,  -3,  8, 62,  -5,  2, -1 },  // pos 14: Filter 14
    {  0,  1,  -2,  4, 63,  -3,  1,  0 },  // pos 15: Filter 15
};

// ============================================================
// Top-Level Function Declaration
// ============================================================

/**
 * Top-level function: VVC Fractional Interpolation for Motion Compensation
 *
 * Processes one 8x8 block at a time (as described in the paper).
 * For larger PU sizes, caller divides PU into 8x8 sub-blocks.
 *
 * @param ref_block   Input reference pixels (15x15 window from reference frame)
 * @param out_block   Output interpolated 8x8 block
 * @param frac_x      Horizontal fractional position (0-15), 0 = integer
 * @param frac_y      Vertical fractional position (0-15), 0 = integer
 */
void vvc_fractional_interp(
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    pel_t   out_block[BLOCK_SIZE][BLOCK_SIZE],
    frac_t  frac_x,
    frac_t  frac_y
);

#endif // VVC_FRACTIONAL_INTERP_H