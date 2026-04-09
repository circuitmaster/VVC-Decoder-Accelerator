#include "graph.h"
#include "coeff.h"

using namespace adf;

B64_STATIC gr;

#if defined(__AIESIM__) || defined(__X86SIM__)

#include <iostream>
#include <vector>
#include <cstdint>
#include <cstring>

using KernelT = idct_ii_b64_buffer_i16_i8_acc32_static;

// Frame dimensions
static constexpr int FRAME_W = 1920;
static constexpr int FRAME_H = 1080;

static constexpr int B = KernelT::BATCH_SIZE;   // 128
static constexpr int N = KernelT::BLOCK_SIZE;   // 64

// Blocks per row, total blocks, padded to multiple of (NUM_CORES * N_WINDOWS * B)
static constexpr int BLOCKS_PER_ROW = FRAME_W / N;                          // 30
static constexpr int TOTAL_BLOCKS   = BLOCKS_PER_ROW * FRAME_H;             // 32400
static constexpr int TOTAL_BATCHES  = (TOTAL_BLOCKS + B - 1) / B;           // 254
static constexpr int PADDED_BATCHES = ((TOTAL_BATCHES + NUM_CORES * N_WINDOWS - 1)
                                       / (NUM_CORES * N_WINDOWS))
                                       * (NUM_CORES * N_WINDOWS);            // 256
static constexpr int N_ITERS        = PADDED_BATCHES / (NUM_CORES * N_WINDOWS); // 32

static constexpr int BATCHES_PER_CORE = PADDED_BATCHES / NUM_CORES;         // 64
static constexpr int PER_CORE         = BATCHES_PER_CORE * B * N;           // 64 * 8192 = 524288
static constexpr size_t PER_CORE_BYTES = PER_CORE * sizeof(int16_t);        // 1 MB

// Coeff storage: tiled layout  tile(k_tile, n_tile) at byte offset
//   (k_tile * (N/TILEdN) + n_tile) * TILEdK * TILEdN
// within tile row-major: element(dk, dn) at dk*TILEdN + dn
static int8_t coeff_at(const std::vector<int8> &coeff, int k, int n)
{
    static constexpr int Tk = KernelT::TILEdK;   // 8
    static constexpr int Tn = KernelT::TILEdN;   // 4
    int k_tile = k / Tk,  dk = k % Tk;
    int n_tile = n / Tn,  dn = n % Tn;
    int idx = (k_tile * (N / Tn) + n_tile) * (Tk * Tn) + dk * Tn + dn;
    return (int8_t)coeff[idx];
}

// Reference: out[b*N + n] = sum_k ( in[b*N + k] * coeff(k,n) )
// bias=0, shift=0 (static kernel hardcodes these)
static void compute_reference(
    const int16_t          *in,
    const std::vector<int8> &coeff,
    int16_t                 *ref)
{
    for (int b = 0; b < B; ++b)
        for (int n = 0; n < N; ++n) {
            int32_t acc = 0;
            for (int k = 0; k < N; ++k)
                acc += (int32_t)in[b * N + k] * coeff_at(coeff, k, n);
            ref[b * N + n] = (int16_t)acc;
        }
}

int main()
{
    // --- simulate a 1920x1080 frame ---
    // frame[row][col] stored row-major, pixel values = synthetic pattern
    std::vector<int16_t> frame(FRAME_H * FRAME_W);
    for (int r = 0; r < FRAME_H; ++r)
        for (int c = 0; c < FRAME_W; ++c)
            frame[r * FRAME_W + c] = (int16_t)((r * FRAME_W + c) % 128);

    // --- reorder frame into packed blocks: packed[batch][within_batch][64] ---
    // zero-initialized for padding (blocks beyond 32400)
    std::vector<int16_t> packed(PADDED_BATCHES * B * N, 0);
    for (int r = 0; r < FRAME_H; ++r) {
        for (int cb = 0; cb < BLOCKS_PER_ROW; ++cb) {
            int block_id = r * BLOCKS_PER_ROW + cb;
            int batch    = block_id / B;
            int within   = block_id % B;
            std::memcpy(&packed[(batch * B + within) * N],
                        &frame[r * FRAME_W + cb * N],
                        N * sizeof(int16_t));
        }
    }

    // --- partition across 4 cores (contiguous batches) ---
    gr.init();

    int16_t *src[NUM_CORES], *dst[NUM_CORES], *ref[NUM_CORES];

    for (int c = 0; c < NUM_CORES; ++c) {
        src[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);
        dst[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);
        ref[c] = (int16_t*)adf::GMIO::malloc(PER_CORE_BYTES);

        // copy this core's slice from packed buffer
        std::memcpy(src[c], &packed[c * PER_CORE], PER_CORE_BYTES);

        // compute reference for all batches of this core
        for (int bat = 0; bat < BATCHES_PER_CORE; ++bat)
            compute_reference(src[c] + bat * B * N, idct_ii_b64_coeff_i8, ref[c] + bat * B * N);
    }

    // --- run graph ---
    gr.run(N_ITERS);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_src[c].gm2aie_nb(src[c], PER_CORE_BYTES);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_dst[c].aie2gm_nb(dst[c], PER_CORE_BYTES);

    for (int c = 0; c < NUM_CORES; ++c)
        gr.frame_dst[c].wait();

    // --- compare all elements ---
    bool pass = true;
    int mismatch_count = 0;
    for (int c = 0; c < NUM_CORES; ++c) {
        for (int i = 0; i < PER_CORE; ++i) {
            if (dst[c][i] != ref[c][i]) {
                pass = false;
                if (mismatch_count < 32) {
                    int bat = i / (B * N);
                    int rem = i % (B * N);
                    int b   = rem / N;
                    int n   = rem % N;
                    std::cout << "core=" << c << " batch=" << bat << " b=" << b << " n=" << n
                              << "  got=" << dst[c][i] << "  ref=" << ref[c][i]
                              << "  MISMATCH\n";
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
