#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>

#include "fir_interp.h"

// AIE-ML 16b×16b sliding_mul: Lanes=16, Points=4
// For 8-tap FIR: split into two 4-tap passes (mul + mac)
using fir_ops = aie::sliding_mul_ops<16, 4, 1, 1, 1, int16, int16, acc32>;


// ============================================================
// Horizontal FIR: 15×16 → 15×8 per block
//
// Each row has 16 int16 elements (15 valid + 1 padding).
// Lanes=16 produces 16 outputs — we only need 8 (first 8).
//
// Two passes for 8-tap FIR:
//   acc  = mul(coeff[0..3], data[0..18])   // first 4 taps
//   acc += mac(coeff[4..7], data[4..22])   // last 4 taps, data shifted by 4
//
// Data vector: need 16+4-1 = 19 elements per 4-tap pass.
// Our 16-element row suffices for the first pass (taps 0-3, outputs 0-15).
// For the second pass with coeff_start=4, data_start=4: needs data[4..19].
// With 16 elements (indices 0-15), the second pass can produce
// min(16-4-4+1, 16) = 9 outputs — enough for our 8.
// ============================================================
void fir_h_kernel::run(
    input_buffer<TT_DATA, extents<IN_ELEMS>>& __restrict in,
    output_buffer<TT_DATA, extents<OUT_ELEMS>>& __restrict out,
    const int frac_x
){
    TT_DATA* pIn  = in.data();
    TT_DATA* pOut = out.data();

    // Load 8 coefficients into a vector (only 8 used, padded in a 16-element vector)
    aie::vector<TT_COEFF, 16> vcoeff = aie::zeros<TT_COEFF, 16>();
    auto coeff8 = aie::load_v<8>(&coeff[frac_x * NTAPS]);
    vcoeff.insert(0, coeff8);

    for (int blk = 0; blk < BATCH_SIZE; ++blk)
    {
        TT_DATA* ref = pIn  + blk * REF_ROWS * REF_COLS;
        TT_DATA* dst = pOut + blk * REF_ROWS * OUT_SIZE;

        for (int r = 0; r < REF_ROWS; ++r)
        {
            // Load 16 elements from this row
            aie::vector<TT_DATA, 32> vrow = aie::zeros<TT_DATA, 32>();
            vrow.insert(0, aie::load_v<16>(ref + r * REF_COLS));

            // Pass 1: taps 0-3
            auto acc = fir_ops::mul(vcoeff, 0, vrow, 0);

            // Pass 2: taps 4-7 (coeff_start=4, data_start=4)
            acc = fir_ops::mac(acc, vcoeff, 4, vrow, 4);

            // Shift to internal precision (no clip — V kernel does final clip)
            auto res = acc.to_vector<TT_DATA>(FILTER_SHIFT);

            // Store first 8 outputs (Lanes=16, we need 8)
            aie::store_v(dst + r * OUT_SIZE, res.extract<8>(0));
        }
    }
}


// ============================================================
// Vertical FIR: 15×8 → 8×8 per block
//
// The input is 15 rows × 8 columns (row-major).
// We need to apply the FIR vertically (along columns).
//
// Strategy: transpose the 15×8 block to 8×15 (padded to 8×16),
// then apply horizontal FIR on the transposed rows.
// Each transposed "row" is one original column (15 elements + 1 pad).
// Lanes=16 → 16 outputs, we need 8.
//
// Two 4-tap passes for 8-tap FIR, same as H kernel.
// ============================================================
void fir_v_kernel::run(
    input_buffer<TT_DATA, extents<IN_ELEMS>>& __restrict in,
    output_buffer<TT_DATA, extents<OUT_ELEMS>>& __restrict out,
    const int frac_y
){
    TT_DATA* pIn  = in.data();
    TT_DATA* pOut = out.data();

    aie::vector<TT_COEFF, 16> vcoeff = aie::zeros<TT_COEFF, 16>();
    auto coeff8 = aie::load_v<8>(&coeff[frac_y * NTAPS]);
    vcoeff.insert(0, coeff8);

    for (int blk = 0; blk < BATCH_SIZE; ++blk)
    {
        TT_DATA* src = pIn  + blk * IN_ROWS * IN_COLS;
        TT_DATA* dst = pOut + blk * OUT_SIZE * OUT_SIZE;

        // Transpose 15×8 → 8×16 (each column becomes a padded row)
        alignas(32) TT_DATA transposed[IN_COLS * 16];  // 8 rows × 16 cols
        for (int c = 0; c < IN_COLS; ++c) {
            for (int r = 0; r < IN_ROWS; ++r)
                transposed[c * 16 + r] = src[r * IN_COLS + c];
            transposed[c * 16 + 15] = 0;  // pad 16th element
        }

        // Apply horizontal FIR on each transposed row (= original column)
        for (int c = 0; c < IN_COLS; ++c)
        {
            aie::vector<TT_DATA, 32> vrow = aie::zeros<TT_DATA, 32>();
            vrow.insert(0, aie::load_v<16>(transposed + c * 16));

            // Pass 1: taps 0-3
            auto acc = fir_ops::mul(vcoeff, 0, vrow, 0);

            // Pass 2: taps 4-7
            acc = fir_ops::mac(acc, vcoeff, 4, vrow, 4);

            // Final shift + clip to [0, 255]
            auto res = acc.to_vector<TT_DATA>(FILTER_SHIFT);

            // Extract first 8 outputs and clip
            auto out8 = res.extract<8>(0);
            out8 = aie::max(out8, aie::zeros<TT_DATA, 8>());
            out8 = aie::min(out8, aie::broadcast<TT_DATA, 8>(255));

            // Store as column in output: dst[r][c] for r=0..7
            for (int r = 0; r < OUT_SIZE; ++r)
                dst[r * OUT_SIZE + c] = out8[r];
        }
    }
}
