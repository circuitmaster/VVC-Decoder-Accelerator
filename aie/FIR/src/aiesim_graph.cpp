#include "graph.h"
#include "coeff.h"

using namespace adf;

FIR_2PASS_GRAPH gr;

#if defined(__AIESIM__) || defined(__X86SIM__)

#include <iostream>
#include <cstdint>
#include <cstring>

static constexpr int N_ITERS = 2;
static constexpr int BATCH   = fir_h_kernel::BATCH_SIZE;
static constexpr int REF_R   = fir_h_kernel::REF_ROWS;
static constexpr int REF_C   = fir_h_kernel::REF_COLS;
static constexpr int OUT     = fir_v_kernel::OUT_SIZE;
static constexpr int NTAPS   = fir_h_kernel::NTAPS;
static constexpr int FSHIFT  = fir_h_kernel::FILTER_SHIFT;

static constexpr int BLOCKS_PER_CU = N_ITERS * N_WINDOWS * BATCH;
static constexpr int PER_CU_IN  = BLOCKS_PER_CU * REF_R * REF_C;
static constexpr int PER_CU_OUT = BLOCKS_PER_CU * OUT * OUT;

static int32_t fir_8tap(const int16_t* samples, const int16_t* coeffs) {
    int32_t sum = 0;
    for (int t = 0; t < NTAPS; ++t)
        sum += (int32_t)samples[t] * (int32_t)coeffs[t];
    return sum;
}

static int16_t clip(int32_t val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return (int16_t)val;
}

// Reference 2-pass: H then V (always, matches the 2-core pipeline)
static void compute_reference(
    const int16_t* ref,   // REF_R * REF_C
    int16_t* out,         // OUT * OUT
    int frac_x, int frac_y
){
    const int16_t* ch = (const int16_t*)&vvc_luma_coeff[frac_x * NTAPS];
    const int16_t* cv = (const int16_t*)&vvc_luma_coeff[frac_y * NTAPS];

    // H pass: all 15 rows → 15×8
    int16_t h_tmp[REF_R * OUT];
    for (int r = 0; r < REF_R; ++r)
        for (int c = 0; c < OUT; ++c) {
            int16_t samples[NTAPS];
            for (int t = 0; t < NTAPS; ++t)
                samples[t] = ref[r * REF_C + c + t];
            h_tmp[r * OUT + c] = (int16_t)((fir_8tap(samples, ch) + (1 << (FSHIFT - 1))) >> FSHIFT);
        }

    // V pass: 8 columns → 8×8
    for (int r = 0; r < OUT; ++r)
        for (int c = 0; c < OUT; ++c) {
            int16_t samples[NTAPS];
            for (int t = 0; t < NTAPS; ++t)
                samples[t] = h_tmp[(r + t) * OUT + c];
            int32_t val = (fir_8tap(samples, cv) + (1 << (FSHIFT - 1))) >> FSHIFT;
            out[r * OUT + c] = clip(val);
        }
}

int main()
{
    int test_frac_x = 4;
    int test_frac_y = 8;

    gr.init();

    int16_t *src[NUM_CU], *dst[NUM_CU], *ref[NUM_CU];

    for (int c = 0; c < NUM_CU; ++c) {
        src[c] = (int16_t*)adf::GMIO::malloc(PER_CU_IN * sizeof(int16_t));
        dst[c] = (int16_t*)adf::GMIO::malloc(PER_CU_OUT * sizeof(int16_t));
        ref[c] = (int16_t*)adf::GMIO::malloc(PER_CU_OUT * sizeof(int16_t));

        // Fill with pixel-like values [0, 199]
        for (int i = 0; i < PER_CU_IN; ++i)
            src[c][i] = (int16_t)((c * PER_CU_IN + i) % 200);

        for (int blk = 0; blk < BLOCKS_PER_CU; ++blk)
            compute_reference(
                src[c] + blk * REF_R * REF_C,
                ref[c] + blk * OUT * OUT,
                test_frac_x, test_frac_y);
    }

    // Set runtime parameters
    gr.update(gr.frac_x, test_frac_x);
    gr.update(gr.frac_y, test_frac_y);

    gr.run(N_ITERS);

    for (int c = 0; c < NUM_CU; ++c)
        gr.frame_src[c].gm2aie_nb(src[c], PER_CU_IN * sizeof(int16_t));

    for (int c = 0; c < NUM_CU; ++c)
        gr.frame_dst[c].aie2gm_nb(dst[c], PER_CU_OUT * sizeof(int16_t));

    for (int c = 0; c < NUM_CU; ++c)
        gr.frame_dst[c].wait();

    // Compare
    bool pass = true;
    int mismatch_count = 0;
    for (int c = 0; c < NUM_CU; ++c) {
        for (int i = 0; i < PER_CU_OUT; ++i) {
            if (dst[c][i] != ref[c][i]) {
                pass = false;
                if (mismatch_count < 32) {
                    int blk = i / (OUT * OUT);
                    int rem = i % (OUT * OUT);
                    int r = rem / OUT;
                    int col = rem % OUT;
                    std::cout << "cu=" << c << " blk=" << blk
                              << " r=" << r << " c=" << col
                              << " got=" << dst[c][i] << " ref=" << ref[c][i]
                              << " MISMATCH\n";
                }
                mismatch_count++;
            }
        }
    }
    if (mismatch_count > 32)
        std::cout << "... " << (mismatch_count - 32) << " more mismatches\n";

    std::cout << "frac_x=" << test_frac_x << " frac_y=" << test_frac_y << std::endl;
    std::cout << (pass ? "SIM PASS" : "SIM FAIL") << std::endl;

    for (int c = 0; c < NUM_CU; ++c) {
        adf::GMIO::free(src[c]);
        adf::GMIO::free(dst[c]);
        adf::GMIO::free(ref[c]);
    }

    gr.end();
    return pass ? 0 : 1;
}

#endif
