#include "graph.h"
#include "coeff.h"

using namespace adf;

B64_2D_STATIC gr;

#if defined(__AIESIM__) || defined(__X86SIM__)

#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>

static constexpr int B = BLOCK;          // 64
static constexpr int B2 = BLOCK_ELEMS;   // 4096

// Reference 2D IDCT: horizontal then vertical
// H[m][n] = sum_k input[m][k] * C_h[k][n]
// out[y][x] = sum_k H[k][x] * C_v[k][y]
static int8_t coeff_h_at(const std::vector<int8> &coeff, int k, int n) {
    int Tk = H_K::TILEdK, Tn = H_K::TILEdN;
    int k_tile = k / Tk, dk = k % Tk;
    int n_tile = n / Tn, dn = n % Tn;
    return (int8_t)coeff[(k_tile * (B / Tn) + n_tile) * (Tk * Tn) + dk * Tn + dn];
}

static void compute_reference_2d(const int16_t *in, int16_t *ref) {
    // horizontal pass: H[m][n] = sum_k in[m][k] * C[k][n]
    int16_t H[B * B];
    for (int m = 0; m < B; ++m)
        for (int n = 0; n < B; ++n) {
            int32_t acc = 0;
            for (int k = 0; k < B; ++k)
                acc += (int32_t)in[m * B + k] * coeff_h_at(idct_ii_b64_coeff_i8, k, n);
            H[m * B + n] = (int16_t)acc;
        }
    // vertical pass: out[y][x] = sum_k H[k][x] * C[k][y]  (same coeff, same tiling)
    for (int y = 0; y < B; ++y)
        for (int x = 0; x < B; ++x) {
            int32_t acc = 0;
            for (int k = 0; k < B; ++k)
                acc += (int32_t)H[k * B + x] * coeff_h_at(idct_ii_b64_coeff_i8, k, y);
            ref[y * B + x] = (int16_t)acc;
        }
}

int main()
{
    static constexpr int N_ITERS_2D = 2;
    static constexpr int BLOCKS_PER_CORE = N_ITERS_2D * N_WINDOWS_2D;  // 4
    static constexpr int PER_CORE = BLOCKS_PER_CORE * B2;              // 16384
    static constexpr size_t PER_CORE_BYTES = PER_CORE * sizeof(int16_t);

    gr.init();

    int16_t *src[NUM_CORES], *dst[NUM_CORES], *ref[NUM_CORES];

    for (int c = 0; c < NUM_CORES; ++c) {
        src[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);
        dst[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);
        ref[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);

        for (int i = 0; i < PER_CORE; ++i)
            src[c][i] = (int16_t)((c * PER_CORE + i) % 128);

        for (int blk = 0; blk < BLOCKS_PER_CORE; ++blk)
            compute_reference_2d(src[c] + blk * B2, ref[c] + blk * B2);
    }

    gr.run(N_ITERS_2D);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_src[c].gm2aie_nb(src[c], PER_CORE_BYTES);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_dst[c].aie2gm_nb(dst[c], PER_CORE_BYTES);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_dst[c].wait();

    bool pass = true;
    int mismatch_count = 0;
    for (int c = 0; c < NUM_CORES; ++c) {
        for (int i = 0; i < PER_CORE; ++i) {
            if (dst[c][i] != ref[c][i]) {
                pass = false;
                if (mismatch_count < 32) {
                    int blk = i / B2;
                    int rem = i % B2;
                    int y = rem / B;
                    int x = rem % B;
                    std::cout << "core=" << c << " blk=" << blk
                              << " y=" << y << " x=" << x
                              << " got=" << dst[c][i] << " ref=" << ref[c][i]
                              << " MISMATCH\n";
                }
                mismatch_count++;
            }
        }
    }
    if (mismatch_count > 32)
        std::cout << "... " << (mismatch_count - 32) << " more mismatches\n";

    std::cout << (pass ? "SIM PASS" : "SIM FAIL") << std::endl;

    for (int c = 0; c < NUM_CORES; ++c) {
        adf::GMIO::free(src[c]);
        adf::GMIO::free(dst[c]);
        adf::GMIO::free(ref[c]);
    }

    gr.end();
    return pass ? 0 : 1;
}

#endif
