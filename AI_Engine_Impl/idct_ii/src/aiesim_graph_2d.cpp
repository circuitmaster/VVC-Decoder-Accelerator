// Toggle: uncomment for quick sim (4×4 blocks), comment out for full FHD
// #define QUICK_SIM

#include "graph.h"
#include "coeff.h"

using namespace adf;

B64_2D_STATIC gr;

#if defined(__AIESIM__) || defined(__X86SIM__)

#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>

static constexpr int B  = BLOCK;        // 64
static constexpr int B2 = BLOCK_ELEMS;  // 4096

// Reference 2D IDCT: horizontal then vertical
static int8_t coeff_h_at(const std::vector<int8> &coeff, int k, int n) {
    int Tk = H_K::TILEdK, Tn = H_K::TILEdN;
    int k_tile = k / Tk, dk = k % Tk;
    int n_tile = n / Tn, dn = n % Tn;
    return (int8_t)coeff[(k_tile * (B / Tn) + n_tile) * (Tk * Tn) + dk * Tn + dn];
}

static void compute_reference_2d(const int16_t *in, int16_t *ref) {
    int16_t H[B * B];

    // horizontal pass
    for (int m = 0; m < B; ++m) {
        for (int n = 0; n < B; ++n) {
            int32_t acc = 0;
            for (int k = 0; k < B; ++k) {
                acc += (int32_t)in[m * B + k] * coeff_h_at(idct_ii_b64_coeff_i8, k, n);
            }
            H[m * B + n] = (int16_t)acc;
        }
    }

    // vertical pass
    for (int y = 0; y < B; ++y) {
        for (int x = 0; x < B; ++x) {
            int32_t acc = 0;
            for (int k = 0; k < B; ++k) {
                acc += (int32_t)H[k * B + x] * coeff_h_at(idct_ii_b64_coeff_i8, k, y);
            }
            ref[y * B + x] = (int16_t)acc;
        }
    }
}

int main()
{
// Toggle: uncomment for quick sim (4×4 blocks), comment out for full FHD
#define QUICK_SIM

#ifdef QUICK_SIM
    static constexpr int FRAME_W = 4 * B;   // 256 — 16 blocks, exercises double buffering
    static constexpr int FRAME_H = 4 * B;   // 256
#else
    static constexpr int FRAME_W = 1920;    // FHD
    static constexpr int FRAME_H = 1080;
#endif
    static constexpr int BLOCKS_W = (FRAME_W + B - 1) / B;
    static constexpr int BLOCKS_H = (FRAME_H + B - 1) / B;
    static constexpr int BLOCKS_PER_FRAME = BLOCKS_W * BLOCKS_H;

    static constexpr int BLOCKS_PER_ITER = NUM_ENGINE * NUM_CU * N_WINDOWS_2D;
    static constexpr int N_ITERS_2D = (BLOCKS_PER_FRAME + BLOCKS_PER_ITER - 1) / BLOCKS_PER_ITER;

    // per engine: NUM_CU CUs × N_WINDOWS_2D windows per CU per graph iteration
    static constexpr int BLOCKS_PER_ENGINE = N_ITERS_2D * NUM_CU * N_WINDOWS_2D;
    static constexpr int PER_ENGINE = BLOCKS_PER_ENGINE * B2;
    static constexpr size_t PER_ENGINE_BYTES = PER_ENGINE * sizeof(int16_t);

    // per-iteration and per-GMIO-port sizes
    static constexpr int ELEMS_PER_ITER = NUM_CU * N_WINDOWS_2D * B2;
    static constexpr int IN_PER_PORT_ITER = ELEMS_PER_ITER / NUM_GMIO_PORTS;
    static constexpr int IN_PER_PORT_TOTAL = N_ITERS_2D * IN_PER_PORT_ITER;
    static constexpr size_t IN_PER_PORT_BYTES = IN_PER_PORT_TOTAL * sizeof(int16_t);

    // output: 2D buffer {B, N_WINDOWS_2D * B * NUM_CU}, each port reads a column slice
    static constexpr int OUT_DIM1 = N_WINDOWS_2D * B * NUM_CU;
    static constexpr int OUT_PORT_DIM1 = OUT_DIM1 / NUM_GMIO_PORTS;
    static constexpr int OUT_PER_PORT_ITER = B * OUT_PORT_DIM1;
    static constexpr int OUT_PER_PORT_TOTAL = N_ITERS_2D * OUT_PER_PORT_ITER;
    static constexpr size_t OUT_PER_PORT_BYTES = OUT_PER_PORT_TOTAL * sizeof(int16_t);

    gr.init();

    // full-engine buffers for reference generation and comparison
    int16_t *src_full[NUM_ENGINE];
    int16_t *ref[NUM_ENGINE];
    int16_t *dst_full[NUM_ENGINE];

    // per-GMIO-port buffers
    int16_t *src_port[NUM_ENGINE][NUM_GMIO_PORTS];
    int16_t *dst_port[NUM_ENGINE][NUM_GMIO_PORTS];

    // allocate and prepare inputs/reference
    // data layout: [iter0: CU0_w0][CU0_w1][CU1_w0][CU1_w1]...[iter1: ...]
    for (int e = 0; e < NUM_ENGINE; ++e) {

        src_full[e] = (int16_t*)adf::GMIO::malloc(PER_ENGINE_BYTES);
        dst_full[e] = (int16_t*)adf::GMIO::malloc(PER_ENGINE_BYTES);
        ref[e]      = (int16_t*)adf::GMIO::malloc(PER_ENGINE_BYTES);

        for (int j = 0; j < PER_ENGINE; ++j) {
            src_full[e][j] = (int16_t)((e * PER_ENGINE + j) % 128);
        }

        for (int blk = 0; blk < BLOCKS_PER_ENGINE; ++blk) {
            compute_reference_2d(src_full[e] + blk * B2, ref[e] + blk * B2);
        }

        // scatter input into per-port buffers (linear split per iteration)
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            src_port[e][g] = (int16_t*)adf::GMIO::malloc(IN_PER_PORT_BYTES);
            dst_port[e][g] = (int16_t*)adf::GMIO::malloc(OUT_PER_PORT_BYTES);
            for (int t = 0; t < N_ITERS_2D; ++t) {
                std::memcpy(src_port[e][g] + t * IN_PER_PORT_ITER,
                            src_full[e] + t * ELEMS_PER_ITER + g * IN_PER_PORT_ITER,
                            IN_PER_PORT_ITER * sizeof(int16_t));
            }
        }
    }

    gr.run(N_ITERS_2D);

    // send input buffers (one per GMIO port)
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            gr.frame_src[e][g].gm2aie_nb(src_port[e][g], IN_PER_PORT_BYTES);
        }
    }

    // receive output buffers (one per GMIO port)
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            gr.frame_dst[e][g].aie2gm_nb(dst_port[e][g], OUT_PER_PORT_BYTES);
        }
    }

    // wait for completion
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            gr.frame_dst[e][g].wait();
        }
    }

    // gather per-port output into full dst buffer for comparison
    // output port g covers column range [g*OUT_PORT_DIM1 .. (g+1)*OUT_PORT_DIM1-1]
    // in the 2D {B, OUT_DIM1} buffer, which maps to blocks [g*BPG .. (g+1)*BPG-1]
    static constexpr int BPG = NUM_CU * N_WINDOWS_2D / NUM_GMIO_PORTS; // blocks per GMIO port
    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            for (int t = 0; t < N_ITERS_2D; ++t) {
                const int16_t *gp = dst_port[e][g] + t * OUT_PER_PORT_ITER;
                for (int b = 0; b < BPG; ++b) {
                    int global_blk = t * (NUM_CU * N_WINDOWS_2D) + g * BPG + b;
                    for (int y = 0; y < B; ++y) {
                        std::memcpy(dst_full[e] + global_blk * B2 + y * B,
                                    gp + y * OUT_PORT_DIM1 + b * B,
                                    B * sizeof(int16_t));
                    }
                }
            }
        }
    }

    bool pass = true;
    int mismatch_count = 0;

    for (int e = 0; e < NUM_ENGINE; ++e) {
        for (int j = 0; j < PER_ENGINE; ++j) {
            if (dst_full[e][j] != ref[e][j]) {
                pass = false;
                if (mismatch_count < 32) {
                    int blk = j / B2;
                    int cu  = (blk / N_WINDOWS_2D) % NUM_CU;
                    int win = blk % N_WINDOWS_2D;
                    int rem = j % B2;
                    int y = rem / B;
                    int x = rem % B;
                    std::cout << "engine=" << e
                              << " cu=" << cu
                              << " win=" << win
                              << " y=" << y
                              << " x=" << x
                              << " got=" << dst_full[e][j]
                              << " ref=" << ref[e][j]
                              << " MISMATCH\n";
                }
                mismatch_count++;
            }
        }
    }

    if (mismatch_count > 32) {
        std::cout << "... " << (mismatch_count - 32) << " more mismatches\n";
    }

    std::cout << (pass ? "SIM PASS" : "SIM FAIL") << std::endl;

    for (int e = 0; e < NUM_ENGINE; ++e) {
        adf::GMIO::free(src_full[e]);
        adf::GMIO::free(dst_full[e]);
        adf::GMIO::free(ref[e]);
        for (int g = 0; g < NUM_GMIO_PORTS; ++g) {
            adf::GMIO::free(src_port[e][g]);
            adf::GMIO::free(dst_port[e][g]);
        }
    }

    gr.end();
    return pass ? 0 : 1;
}

#endif