#pragma once

#include <adf.h>
#include <aie_api/aie.hpp>

using namespace adf;

// ============================================================
// AIE-ML 16b×16b sliding_mul constraint:
//   Lanes=16, Points=4, CoeffStep=1,2, DataStepX=1,2, DataStepY=1,2
//
// For 8-tap FIR: split into two 4-tap passes (mul + mac)
// Lanes=16 produces 16 outputs per call
// ============================================================

// ============================================================
// Horizontal FIR kernel: 15×16 input → 15×8 intermediate
// Lanes=16 → 16 outputs per call, we use 8 (one row)
// Two 4-tap passes per row for 8-tap FIR
// ============================================================
class fir_h_kernel {
public:
    typedef int16   TT_DATA;
    typedef int16   TT_COEFF;
    typedef acc32   TT_ACC;

    static constexpr int NTAPS     = 8;
    static constexpr int HALF_TAPS = 4;
    static constexpr int NFRAC     = 16;
    static constexpr int COEFF_DEPTH = NFRAC * NTAPS;  // 128

    static constexpr int LANES      = 16;   // AIE-ML fixed for 16b×16b
    static constexpr int OUT_SIZE   = 8;
    static constexpr int REF_ROWS   = 15;
    static constexpr int REF_COLS   = 16;

    static constexpr int FILTER_SHIFT = 6;

    static constexpr int BATCH_SIZE = 64;

    static constexpr int IN_ELEMS  = BATCH_SIZE * REF_ROWS * REF_COLS;   // 15360
    static constexpr int OUT_ELEMS = BATCH_SIZE * REF_ROWS * OUT_SIZE;    // 7680

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    fir_h_kernel(TT_COEFF (&c)[COEFF_DEPTH]) : coeff(c) {}

    void run(input_buffer<TT_DATA, extents<IN_ELEMS>>& __restrict in,
             output_buffer<TT_DATA, extents<OUT_ELEMS>>& __restrict out,
             const int frac_x);

    static void registerKernelClass() {
        REGISTER_FUNCTION(fir_h_kernel::run);
        REGISTER_PARAMETER(coeff);
    }
};

// ============================================================
// Vertical FIR kernel: 15×8 intermediate → 8×8 output
// Uses DataStepX=1, DataStepY=1 with pre-transposed data
// (columns gathered into rows for contiguous access)
// Two 4-tap passes per column group for 8-tap FIR
// ============================================================
class fir_v_kernel {
public:
    typedef int16   TT_DATA;
    typedef int16   TT_COEFF;
    typedef acc32   TT_ACC;

    static constexpr int NTAPS     = 8;
    static constexpr int HALF_TAPS = 4;
    static constexpr int NFRAC     = 16;
    static constexpr int COEFF_DEPTH = NFRAC * NTAPS;  // 128

    static constexpr int LANES      = 16;
    static constexpr int OUT_SIZE   = 8;
    static constexpr int IN_ROWS    = 15;
    static constexpr int IN_COLS    = 8;

    static constexpr int FILTER_SHIFT = 6;

    static constexpr int BATCH_SIZE = 64;

    static constexpr int IN_ELEMS  = BATCH_SIZE * IN_ROWS * IN_COLS;     // 7680
    static constexpr int OUT_ELEMS = BATCH_SIZE * OUT_SIZE * OUT_SIZE;    // 4096

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    fir_v_kernel(TT_COEFF (&c)[COEFF_DEPTH]) : coeff(c) {}

    void run(input_buffer<TT_DATA, extents<IN_ELEMS>>& __restrict in,
             output_buffer<TT_DATA, extents<OUT_ELEMS>>& __restrict out,
             const int frac_y);

    static void registerKernelClass() {
        REGISTER_FUNCTION(fir_v_kernel::run);
        REGISTER_PARAMETER(coeff);
    }
};
