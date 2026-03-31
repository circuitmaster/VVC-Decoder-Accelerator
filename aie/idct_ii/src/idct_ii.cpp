#include <stdio.h>
#include <array>
#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>

#include "idct_ii.h"


void idct_ii_b4::run(input_stream<TT_DATA>* __restrict in, 
                     output_stream<TT_DATA>* __restrict out,
                     const int SIZE,
                     const int SHIFT)
{
    static_assert(UNROLL_FACTOR == 4, "This version assumes UNROLL_FACTOR=4");
    static_assert(COEFF_DEPTH   == 16, "Direct 4x4 mmul needs 16 coeffs");
    
    using MMUL = aie::mmul<4, 4, 4, TT_COEFF, TT_DATA, TT_ACCUM>;

    // vector access to 4x4 coeffs matrix (256-bit vector register)
    auto iter_coeffs = aie::begin_restrict_vector<COEFF_DEPTH>(coeff);
    aie::vector<TT_COEFF, COEFF_DEPTH> vCoeffs = *iter_coeffs;

    // rounding bias
    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    for (int i = 0; i < SIZE/(UNROLL_FACTOR); i++) 
        chess_loop_range(4,)
        chess_prepare_for_pipelining
    {

        // 256-bit vector register that holds UNROLL_FACTOR lines
        aie::vector<TT_DATA, 4 * UNROLL_FACTOR> samples;
        samples = readincr_v<4 * UNROLL_FACTOR>(in);

        MMUL transform;

        transform.mac(vCoeffs, aie::transpose(samples, 4, UNROLL_FACTOR));

        // add bias
        auto acc = aie::add(transform.to_accum(), bias);

        // shift
        auto x = acc.to_vector<TT_DATA>(SHIFT);

        // transpose to correct shape
        x = aie::transpose(x, UNROLL_FACTOR, 4);

        // write the transformed samples
        writeincr(out, x);
        
    }

}

void idct_ii_b8::run(input_stream<TT_DATA>* __restrict in,
                     output_stream<TT_DATA>* __restrict out,
                     const int SIZE,
                     const int SHIFT)
{
    static_assert(UNROLL_FACTOR == 4, "Use UNROLL_FACTOR=4 for 4x4x4 mmul blocking");
    static_assert(COEFF_DEPTH   == 64, "B8 direct coeff matrix is 8x8 -> 64 coeffs");

    using MMUL = aie::mmul<4, 4, 4, TT_COEFF, TT_DATA, TT_ACCUM>;

    // create vector iterator to access 4x4 tile of 8x8 coeff matrix
    // the 4x4 tile is assumed to be preprocessed row-major
    auto iter_coeffs = aie::begin_restrict_vector<4*4>(coeff);

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    for (int line = 0; line < (SIZE/4); ++line) {

        // transform accumulator
        MMUL top_transform,
             bot_transform;

        // Read 4 line, each is 8 samples: [y0..y7]
        // samples is S = 4x8 row-major: rows=lines
        aie::vector<TT_DATA, 4*8> samples;
        samples = readincr_v<4*8>(in);

        // Transpose S (4x8) -> B (8x4), rows become components y0..y7
        aie::vector<TT_DATA, 8 * 4> B8x4 = aie::transpose(samples, /*rows=*/8, /*cols=*/4);

        auto B0 = B8x4.extract<4*4>(0);
        auto B1 = B8x4.extract<4*4>(1);

        // coeff tile alogn transform axis
        aie::vector<TT_COEFF, 4*4> A00, A01;
        A00 = *iter_coeffs++;
        A01 = *iter_coeffs++;

        // perfrom top transform
        top_transform.mul(A00, B0); top_transform.mac(A01, B1);

        aie::vector<TT_COEFF, 4*4> A10, A11;
        A10 = *iter_coeffs++;
        A11 = *iter_coeffs++;

        // perform bottom transform
        bot_transform.mul(A10, B0); bot_transform.mac(A11, B1);

        iter_coeffs -= 4;

        auto transform = aie::concat(top_transform.to_accum(), bot_transform.to_accum());
        // add bias
        transform = aie::add(transform, bias);

        // perform shift
        auto x = transform.to_vector<TT_DATA>(SHIFT);

        // Transpose back so each row is one output block [x0..x7]
        x = aie::transpose(x, /*rows=*/4, /*cols=*/8);

        writeincr(out, x);
    }
}

// void idct_ii_b16::run(input_stream<TT_DATA>* __restrict in,
//                       output_stream<TT_DATA>* __restrict out,
//                       const int SIZE,
//                       const int SHIFT)
// {
//     static_assert(COEFF_DEPTH   == 256, "B16 direct coeff matrix is 16x16 -> 256 coeffs");

//     using MMUL = aie::mmul<4, 4, 4, TT_COEFF, TT_DATA, TT_ACCUM>;

//     const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

//     // tensor descriptor of coeff matrix
//     TT_COEFF* pCoeffs = &coeff[0];

//     auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 4*4>(
//         aie::tensor_dim(4, 1), // k dim
//         aie::tensor_dim(/*num tile*/4, /*unit stride*/4) // m dim
//     );

//     for (int line = 0; line < SIZE/4; ++line) {

//         // make new tensor bufstream each time of the loop iteration
//         auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

//         // 1024-bit vector register to hold input samples
//         aie::vector<TT_DATA, 4*16> samples;
//         samples = readincr_v<4*16>(in);

//         // reshape
//         samples = aie::transpose(samples, 16, 4);

//         // each transform will produce a 4x4 output
//         MMUL    transform0, // -> x0-x3
//                 transform1, // -> x4-x7
//                 transform2, // -> x8-x11
//                 transform3; // -> x12-x15

//         // iterate k dim
//         for (int k = 0; k < 4/*16/4*/; ++k) {

//             // coeffs tiles
//             aie::vector<TT_COEFF, 4*4> A0k, A1k, A2k, A3k;
//             A0k = Coeff_Bufstream.pop();
//             A1k = Coeff_Bufstream.pop();
//             A2k = Coeff_Bufstream.pop();
//             A3k = Coeff_Bufstream.pop();

//             // sample tile
//             auto Bk0 = samples.extract<4*4>(k);

//             // perform transforms
//             transform0.mac(A0k, Bk0);
//             transform1.mac(A1k, Bk0);
//             transform2.mac(A2k, Bk0);
//             transform3.mac(A3k, Bk0);
//         }

//         // add bias and shift
//         auto acc_tmp0 = aie::add(transform0.to_accum(), bias);
//         auto acc_tmp1 = aie::add(transform1.to_accum(), bias);
//         auto acc_tmp2 = aie::add(transform2.to_accum(), bias);
//         auto acc_tmp3 = aie::add(transform3.to_accum(), bias);

//         auto vec_tmp0 = acc_tmp0.to_vector<TT_DATA>(SHIFT);
//         auto vec_tmp1 = acc_tmp1.to_vector<TT_DATA>(SHIFT);
//         auto vec_tmp2 = acc_tmp2.to_vector<TT_DATA>(SHIFT);
//         auto vec_tmp3 = acc_tmp3.to_vector<TT_DATA>(SHIFT);

//         // transpose result to match output layout
//         auto transform = aie::concat(vec_tmp0, vec_tmp1, vec_tmp2, vec_tmp3);
//         transform = aie::transpose(transform, /*row=*/4, /*col=*/16);

//         // write to output stream
//         writeincr(out, transform);
//     }
// }

void idct_ii_b16_buffer_i32_i16_acc64::run(input_async_buffer<TT_DATA, extents<16*4>>& __restrict in,
                             output_async_buffer<TT_DATA, extents<16*4>>& __restrict out,
                             const int SIZE,
                             const int SHIFT)
{
    static_assert(COEFF_DEPTH   == 256, "B16 direct coeff matrix is 16x16 -> 256 coeffs");

    using MMUL = aie::mmul<4, 4, 4, TT_COEFF, TT_DATA, TT_ACCUM>;

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    // tensor descriptor of coeff matrix
    TT_COEFF* pCoeffs = &coeff[0];

    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 4*4>(
        aie::tensor_dim(4, 1), // k dim
        aie::tensor_dim(/*num tile*/4, /*unit stride*/4) // m dim
    );

    for (int line = 0; line < SIZE/4; ++line) {

        // make new tensor bufstream each time of the loop iteration
        auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

        // lock input buffer
        in.acquire();
        auto iter_vSamples = aie::begin_restrict_vector<4*4>(in);

        // each transform will produce a 4x4 output
        MMUL    transform0, // -> x0-x3
                transform1, // -> x4-x7
                transform2, // -> x8-x11
                transform3; // -> x12-x15

        // iterate k dim
        for (int k = 0; k < 4/*16/4*/; ++k) {

            // coeffs tiles
            aie::vector<TT_COEFF, 4*4> A0k, A1k, A2k, A3k;
            A0k = Coeff_Bufstream.pop();
            A1k = Coeff_Bufstream.pop();
            A2k = Coeff_Bufstream.pop();
            A3k = Coeff_Bufstream.pop();

            // sample tile
            aie::vector<TT_DATA, 4*4> Bk;
            Bk = *iter_vSamples++;

            // perform transforms
            transform0.mac(A0k, Bk);
            transform1.mac(A1k, Bk);
            transform2.mac(A2k, Bk);
            transform3.mac(A3k, Bk);
        }

        // free input buffer
        in.release();

        // add bias
        auto acc_tmp0 = aie::add(transform0.to_accum(), bias);
        auto acc_tmp1 = aie::add(transform1.to_accum(), bias);
        auto acc_tmp2 = aie::add(transform2.to_accum(), bias);
        auto acc_tmp3 = aie::add(transform3.to_accum(), bias);

        // lock output buffer
        out.acquire();
        auto iter_vTrans = aie::begin_restrict_vector<4*4>(out);

        // shift and save to output buffer
        *iter_vTrans++ = acc_tmp0.to_vector<TT_DATA>(SHIFT);
        *iter_vTrans++ = acc_tmp1.to_vector<TT_DATA>(SHIFT);
        *iter_vTrans++ = acc_tmp2.to_vector<TT_DATA>(SHIFT);
        *iter_vTrans++ = acc_tmp3.to_vector<TT_DATA>(SHIFT);

        // free output buffer
        out.release();
    }
}

void idct_ii_b16_buffer_i16_i8_acc32::run(
    // input and output reshape with DMA buffer descriptors
    input_async_buffer<TT_DATA, extents<(4*8)*2>>& __restrict in,
    output_async_buffer<TT_DATA, extents<(4*4)*4>>& __restrict out,
    const int SIZE,
    const int SHIFT)

{
    static_assert(COEFF_DEPTH   == 256, "B16 direct coeff matrix is 16x16 -> 256 coeffs");

    using MMUL = aie::mmul<4, 8, 4, TT_DATA, TT_COEFF, TT_ACCUM>;

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    // tensor descriptor of coeff matrix
    TT_COEFF* pCoeffs = &coeff[0];

    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 8*4>(
        aie::tensor_dim(/*N dim tile wrapper*/2, 2),
        aie::tensor_dim(/*total num tiles along K*/2, /*dim stride*/4),
        aie::tensor_dim(/*parallel fetch num tiles along N this dim*/2, /*tile stride*/1)
    );

    for (int batch_id = 0; batch_id < SIZE/4; ++batch_id) {

        // make new tensor bufstream each time of the loop iteration
        auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

        // lock input and output buffer
        in.acquire();
        out.acquire();

        // create output tile iterator
        auto iter_vTrans = aie::begin_restrict_vector<4*4>(out);

        // m=1 n=2 (wrapper loop)
        for (int mn = 0; mn < 2; ++mn)
            chess_prepare_for_pipelining
            chess_loop_count(2)
        {
            // create new sample iterator each wrapper loop
            auto iter_vSamples = aie::begin_restrict_vector<4*8>(in);

            MMUL transform[2];

            // inner tile dim
            for (int k = 0; k < 2/*16/8*/; ++k) {

                // sample tile
                aie::vector<TT_DATA, 4*8> tileA;
                tileA = *iter_vSamples++;

                // coeffs tiles
                aie::vector<TT_COEFF, 8*4> tileB[4];
                for (int tid = 0; tid < 2; ++tid)
                    chess_unroll_loop(*)
                {
                    tileB[tid] = Coeff_Bufstream.pop();
                }

                // transform computation
                for (int tid = 0; tid < 2; ++tid)
                    chess_unroll_loop(*)
                {
                    transform[tid].mac(tileA, tileB[tid]);
                }
            }

            // add bias and shift
            for (int tid = 0; tid < 2; ++tid)
                chess_unroll_loop(*)
            {
                auto tmp = aie::add(transform[tid].to_accum(), bias);
                *iter_vTrans++ = tmp.to_vector<TT_DATA>(SHIFT);
            }
        }

        // free input and output buffers
        in.release();
        out.release();
    }
}
                    

void idct_ii_b32_buffer_i32_i16_acc64::run(
    // input and output buffers are transposed by DMA buffer descriptors
    input_async_buffer<TT_DATA, extents<32*4>>& __restrict in,
    output_async_buffer<TT_DATA, extents<32*4>>& __restrict out,
    const int SIZE,
    const int SHIFT)
{
    static_assert(COEFF_DEPTH   == 1024, "B32 direct coeff matrix is 32x32 -> 1024 coeffs");

    using MMUL = aie::mmul<4, 4, 4, TT_COEFF, TT_DATA, TT_ACCUM>;

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    // tensor descriptor of coeff matrix
    TT_COEFF* pCoeffs = &coeff[0];

    // 8x8 * (4x4)tile
    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 4*4>(
        aie::tensor_dim(2, 32), // m dim wrapper
        aie::tensor_dim(8, 1), // k dim
        aie::tensor_dim(/*num tile*/4, /*unit stride*/8) // sub m dim
    );

    for (int line = 0; line < SIZE/4; ++line) {

        // create new tensor buffer stream
        auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

        // lock an input buffer and output buffer
        in.acquire();
        out.acquire();

        // create transform tile iterator of output buffer
        auto iter_vTrans = aie::begin_restrict_vector<4*4>(out);

        for (int mn = 0; mn < 2; ++mn) {

            // assume input samples are already transposed, create new iterator
            auto iter_vSamples = aie::begin_restrict_vector<4*4>(in);
        
            // instantiate accumulator
            MMUL    transform0,
                    transform1,
                    transform2,
                    transform3;

            // inner tile loop
            for (int k = 0; k < 8; ++k) {

                // coeffs tiles
                aie::vector<TT_COEFF, 4*4> A0k, A1k, A2k, A3k;
                A0k = Coeff_Bufstream.pop();
                A1k = Coeff_Bufstream.pop();
                A2k = Coeff_Bufstream.pop();
                A3k = Coeff_Bufstream.pop();
                
                // sample tile
                auto Bk = *iter_vSamples++;

                // perform transforms
                transform0.mac(A0k, Bk);
                transform1.mac(A1k, Bk);
                transform2.mac(A2k, Bk);
                transform3.mac(A3k, Bk);
            }

            // add bias and shift
            auto acc_tmp0 = aie::add(transform0.to_accum(), bias);
            auto acc_tmp1 = aie::add(transform1.to_accum(), bias);
            auto acc_tmp2 = aie::add(transform2.to_accum(), bias);
            auto acc_tmp3 = aie::add(transform3.to_accum(), bias);

            // save to output buffer
            *iter_vTrans++ = acc_tmp0.to_vector<TT_DATA>(SHIFT);
            *iter_vTrans++ = acc_tmp1.to_vector<TT_DATA>(SHIFT);
            *iter_vTrans++ = acc_tmp2.to_vector<TT_DATA>(SHIFT);
            *iter_vTrans++ = acc_tmp3.to_vector<TT_DATA>(SHIFT);

        }

        // free buffers
        in.release();
        out.release();
    }
}

void idct_ii_b32_buffer_i16_i8_acc32::run(
    // input and output are reshaped with DMA buffer descriptors
    input_async_buffer<TT_DATA, extents<(4*8)*4>>& __restrict in,
    output_async_buffer<TT_DATA, extents<(4*4)*8>>& __restrict out,
    const int SIZE,
    const int SHIFT)
{
    static_assert(COEFF_DEPTH   == 1024, "B32 direct coeff matrix is 32x32 -> 1024 coeffs");

    using MMUL = aie::mmul<4, 8, 4, TT_DATA, TT_COEFF, TT_ACCUM>;

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    // tensor descriptor of coeff matrix
    TT_COEFF* pCoeffs = &coeff[0];

    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 8*4>(
        aie::tensor_dim(/*N dim wrapper*/2, /*stride by tile*/4),
        aie::tensor_dim(/*num tile along K*/4, /*stride by tile*/8),
        aie::tensor_dim(/*num tile along N*/4, /*stride by tile*/1)
    );

    for (int batch_id = 0; batch_id < SIZE/4; ++batch_id) {

        // create new tensor buffer stream
        auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

        // lock input and output buffer
        in.acquire();
        out.acquire();

        auto iter_vTrans = aie::begin_restrict_vector<4*4>(out);

        for (int mn = 0; mn < 2; ++mn) {

            // create new iterator each wrapper loop
            auto iter_vSamples = aie::begin_restrict_vector<4*8>(in);

            MMUL transform[4];

            // inner tile loop
            for (int k = 0; k < 4; ++k) {

                // sample tile
                aie::vector<TT_DATA, 4*8> tileA;
                tileA = *iter_vSamples++;

                // coeffs tiles
                aie::vector<TT_COEFF, 8*4> tileB[4];
                for (int tid = 0; tid < 4; ++tid)
                    chess_unroll_loop(*)
                {
                    tileB[tid] = Coeff_Bufstream.pop();
                }

                // tranform computation
                for (int tid = 0; tid < 4; ++tid)
                    chess_unroll_loop(*)
                {
                    transform[tid].mac(tileA, tileB[tid]);
                }
            }

            // add bias and shift
            for (int tid = 0; tid < 4; ++tid)
                chess_unroll_loop(*)
            {
                auto tmp = aie::add(transform[tid].to_accum(), bias);
                *iter_vTrans++ = tmp.to_vector<TT_DATA>(SHIFT);
            }
        }

        // free buffers
        in.release();
        out.release();
    }
}

void idct_ii_b64_buffer_i16_i8_acc32::run(
    // input and output buffer are reshaped with DMA buffer descriptor
    input_async_buffer<TT_DATA, extents<(4*8)*8>>& __restrict in,
    output_async_buffer<TT_DATA, extents<(4*4)*16>>& __restrict out,
    const int SIZE,
    const int SHIFT)
{
    static_assert(COEFF_DEPTH   == 4096, "B64 direct coeff matrix is 64x64 -> 4096 coeffs");

    using MMUL = aie::mmul<4, 8, 4, TT_DATA, TT_COEFF, TT_ACCUM>;

    const TT_DATA bias = (SHIFT > 0) ? ((TT_DATA)1 << (SHIFT - 1)) : 0;

    // tensor descriptor of coeff matrix
    TT_COEFF* pCoeffs = &coeff[0];

    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, 8*4>(
        aie::tensor_dim(/*N dim wrapper*/8, /*stride by tile*/2),
        aie::tensor_dim(/*num tiles along K*/8, /*stride by tile*/16),
        aie::tensor_dim(/*num tiles along N*/2, /*stride by tile*/1)
    );

    for (int batch_id = 0; batch_id < SIZE/4; ++batch_id) {

        // create new tensor buffer stream
        auto Coeff_Bufstream = aie::make_tensor_buffer_stream(pCoeffs, tdsc_Coeffs);

        // lock input and output buffer
        in.acquire();
        out.acquire();

        auto iter_vTrans = aie::begin_restrict_vector<4*4>(out);

        // m=1 n=8 (wrapper loop)
        for (int mn = 0; mn < 8; ++mn) 
            chess_prepare_for_pipelining
            chess_loop_count(8)
        {

            // create new iterator each wrapper loop
            auto iter_vSamples = aie::begin_restrict_vector<4*8>(in);

            MMUL transform[2];

            // inner tile loop
            for (int k = 0; k < 8; ++k) 
                // chess_prepare_for_pipelining
                // chess_loop_count(8)
            {

                // sample tile
                aie::vector<TT_DATA, 4*8> tileA;
                tileA = *iter_vSamples++;

                // coeffs tiles
                aie::vector<TT_COEFF, 8*4> tileB[2];
                for (int tid = 0; tid < 2; ++tid)
                    chess_unroll_loop(*)
                {
                    tileB[tid] = Coeff_Bufstream.pop();
                }

                // transform computation
                for (int tid = 0; tid < 2; ++tid)
                    chess_unroll_loop(*)
                {
                    transform[tid].mac(tileA, tileB[tid]);
                }
            }

            // add bias and shift
            for (int tid = 0; tid < 2; ++tid)
                chess_unroll_loop(*)
            {
                auto tmp = aie::add(transform[tid].to_accum(), bias);
                *iter_vTrans++ = tmp.to_vector<TT_DATA>(SHIFT);
            }
        }

        // free buffers
        in.release();
        out.release();
    }
}

void idct_ii_b64_buffer_i16_i8_acc32_static::run(
    input_buffer<TT_DATA, extents<BATCH_SIZE*BLOCK_SIZE>>& __restrict in,
    output_buffer<TT_DATA, extents<BATCH_SIZE*BLOCK_SIZE>>& __restrict out
){
    static_assert(COEFF_DEPTH == 4096, "B64 direct coeff matrix is 64x64 -> 4096");

    using MMUL = aie::mmul<TILEdM, TILEdK, TILEdN, TT_DATA, TT_COEFF, TT_ACCUM>;;

    const int bias = 0;
    const int shift = 0;

    // create raw pointer for input and output buffer
    TT_DATA* pIn = in.data();
    TT_DATA* pOut = out.data();

    // create raw pointer for coeffs buffer
    TT_COEFF* pCoeff = &coeff[0];

    // create tensor descritpor for input sample buffer
    auto tdsc_Samples = aie::make_tensor_descriptor<TT_DATA, /*sample tilie size*/TILEdM*TILEdK>(
        aie::tensor_dim(/*M dim wrapper by parallel acces UNROLL_M tiles*/(BATCH_SIZE/TILEdM)/UNROLL_M, /*stride by tile*/UNROLL_M),
        aie::tensor_dim(/*dummy dim for inner dim rep times, equals to N dim wrapper*/(BLOCK_SIZE/TILEdN)/UNROLL_N, /*zero stride*/0),
        aie::tensor_dim(/*num sample tiles along K dim in sequence*/BLOCK_SIZE/TILEdK, /*stride by tile*/(BATCH_SIZE/TILEdM)),
        aie::tensor_dim(/*return num coeff tiles along M dim in parallel*/UNROLL_M, /*stride by tile*/1)
    );

    // create tensor descriptor for coeffs buffer (64 x 64) -> (8*4) x 128
    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, /*coeff tile size*/TILEdK*TILEdN>(
        aie::tensor_dim(/*dummy dim for rep times, equals to M dim wrapper*/(BATCH_SIZE/TILEdM)/UNROLL_M, /*zero stride*/0),
        aie::tensor_dim(/*N dim wrapper by parallel access UNROLL_N tiles*/(BLOCK_SIZE/TILEdN)/UNROLL_N, /*stride by tile*/UNROLL_N),
        aie::tensor_dim(/*num coeff tiles along K dim in sequence*/BLOCK_SIZE/TILEdK, /*stride by tile*/(BLOCK_SIZE/TILEdN)),
        aie::tensor_dim(/*return num coeff tiles along N dim in parallel*/UNROLL_N, /*stride by tile*/1)
    );

    // create tensor descriptor for output buffer
    auto tdsc_Trans = aie::make_tensor_descriptor<TT_DATA, /*transformed tile size*/TILEdM*TILEdN>(
        aie::tensor_dim((BATCH_SIZE/TILEdM)/UNROLL_M, (BLOCK_SIZE/TILEdN)*UNROLL_M),
        aie::tensor_dim(BLOCK_SIZE/TILEdN, 1),
        aie::tensor_dim(UNROLL_M, BLOCK_SIZE/TILEdN)
    );

    // create tensor buffer streams
    auto tSamples = aie::make_tensor_buffer_stream(pIn, tdsc_Samples);
    auto tCoeffs  = aie::make_tensor_buffer_stream(pCoeff, tdsc_Coeffs);
    auto tTrans   = aie::make_tensor_buffer_stream(pOut, tdsc_Trans);

    // outer loops (MN)
    // aie::pipelined_loop<(BATCH_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N))>((BATCH_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N)), [&](unsigned mn)) __aie_inline
    for (int mn = 0; mn < (BATCH_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N)); ++mn)
    {

        // MMUL instances
        MMUL AccTile[UNROLL_M][UNROLL_N];

        // inner loop (K)
        // aie::pipelined_loop<BLOCK_SIZE/TILEdK>(BLOCK_SIZE/TILEdK, [&](unsigned kk)) __aie_inline
        for (int kk = 0; kk < (BLOCK_SIZE/TILEdK); ++kk)
        {
            auto Samples_inner = tSamples.pop();
            auto Coeffs_inner = tCoeffs.pop();

            aie::vector<TT_DATA, MMUL::size_A> vSamples[UNROLL_M];
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                Samples_inner >> vSamples[m];
            }

            aie::vector<TT_COEFF, MMUL::size_B> vCoeffs[UNROLL_N];
            for (int n = 0; n < UNROLL_N; ++n)
                chess_unroll_loop(*)
            {
                Coeffs_inner >> vCoeffs[n];
            }

            // add bias if last iteration
            if (kk == (BLOCK_SIZE/TILEdK) - 1) {

                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vSamples[m], vCoeffs[n]);
                        AccTile[m][n] = aie::add(AccTile[m][n].to_accum(), bias);
                    }
                }
            } else {

                // other iterations just perform transformation
                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vSamples[m], vCoeffs[n]);
                    }
                }
            }
        }

        // stream transform result to output buffer
        for (int n = 0; n < UNROLL_N; ++n)
            chess_unroll_loop(*)
        {
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                tTrans << AccTile[m][n].to_vector<TT_DATA>(shift);
            }
        }
    }
}




void idct_ii_b64_horizontal_transform_static::run(
    input_buffer<TT_DATA, extents<BLOCK_SIZE*BLOCK_SIZE>>& __restrict in,
    output_buffer<TT_DATA, extents<BLOCK_SIZE*BLOCK_SIZE>>& __restrict x_transform
){
    static_assert(COEFF_DEPTH == 4096, "B64 direct coeff matrix is 64x64 -> 4096");

    const int bias = 0;
    const int shift = 0;

    // create raw pointer for input and output buffer
    TT_DATA* pIn = in.data();
    TT_DATA* pOut = x_transform.data();

    // create raw pointer for coeffs buffer
    TT_COEFF* pCoeff = &coeff[0];

    // create tensor descritpor for input sample buffer
    auto tdsc_Samples = aie::make_tensor_descriptor<TT_DATA, /*sample tilie size*/TILEdM*TILEdK>(
        aie::tensor_dim(/*M dim wrapper by parallel acces UNROLL_M tiles*/(BLOCK_SIZE/TILEdM)/UNROLL_M, /*stride by tile*/UNROLL_M),
        aie::tensor_dim(/*dummy dim for inner dim rep times, equals to N dim wrapper*/(BLOCK_SIZE/TILEdN)/UNROLL_N, /*zero stride*/0),
        aie::tensor_dim(/*num sample tiles along K dim in sequence*/BLOCK_SIZE/TILEdK, /*stride by tile*/(BLOCK_SIZE/TILEdM)),
        aie::tensor_dim(/*return num coeff tiles along M dim in parallel*/UNROLL_M, /*stride by tile*/1)
    );

    // create tensor descriptor for coeffs buffer (64 x 64) -> (8*4) x 128
    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, /*coeff tile size*/TILEdK*TILEdN>(
        aie::tensor_dim(/*dummy dim for rep times, equals to M dim wrapper*/(BLOCK_SIZE/TILEdM)/UNROLL_M, /*zero stride*/0),
        aie::tensor_dim(/*N dim wrapper by parallel access UNROLL_N tiles*/(BLOCK_SIZE/TILEdN)/UNROLL_N, /*stride by tile*/UNROLL_N),
        aie::tensor_dim(/*num coeff tiles along K dim in sequence*/BLOCK_SIZE/TILEdK, /*stride by tile*/(BLOCK_SIZE/TILEdN)),
        aie::tensor_dim(/*return num coeff tiles along N dim in parallel*/UNROLL_N, /*stride by tile*/1)
    );

    // create tensor descriptor for x_transform buffer, transposed tile layout
    auto tdsc_xTrans = aie::make_tensor_descriptor<TT_DATA, TILEdM*TILEdN>(
        aie::tensor_dim((BLOCK_SIZE/TILEdM)/UNROLL_M, UNROLL_M),
        aie::tensor_dim(BLOCK_SIZE/TILEdN, BLOCK_SIZE/TILEdM),
        aie::tensor_dim(UNROLL_M, 1)
    );


    // create tensor buffer streams
    auto tSamples = aie::make_tensor_buffer_stream(pIn, tdsc_Samples);
    auto tCoeffs  = aie::make_tensor_buffer_stream(pCoeff, tdsc_Coeffs);
    auto tTransx  = aie::make_tensor_buffer_stream(pOut, tdsc_xTrans);

    // outer loops (MN)
    // aie::pipelined_loop<(BLOCK_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N))>((BLOCK_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N)), [&](unsigned mn)) __aie_inline
    for (int mn = 0; mn < (BLOCK_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N)); ++mn)
    {

        // horizontal mmul instances
        MMUL_H AccTile[UNROLL_M][UNROLL_N];

        // inner loop (K)
        // aie::pipelined_loop<BLOCK_SIZE/TILEdK>(BLOCK_SIZE/TILEdK, [&](unsigned kk)) __aie_inline
        for (int kk = 0; kk < (BLOCK_SIZE/TILEdK); ++kk)
        {
            auto Samples_inner = tSamples.pop();
            auto Coeffs_inner = tCoeffs.pop();

            aie::vector<TT_DATA, MMUL_H::size_A> vSamples[UNROLL_M];
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                Samples_inner >> vSamples[m];
            }

            aie::vector<TT_COEFF, MMUL_H::size_B> vCoeffs[UNROLL_N];
            for (int n = 0; n < UNROLL_N; ++n)
                chess_unroll_loop(*)
            {
                Coeffs_inner >> vCoeffs[n];
            }

            // add bias if last iteration
            if (kk == (BLOCK_SIZE/TILEdK) - 1) {

                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vSamples[m], vCoeffs[n]);
                        AccTile[m][n] = aie::add(AccTile[m][n].to_accum(), bias);
                    }
                }
            } else {

                // other iterations just perform transformation
                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vSamples[m], vCoeffs[n]);
                    }
                }
            }
        }

        // save horizontal transform result to shared double buffer
        for (int n = 0; n < UNROLL_N; ++n)
            chess_unroll_loop(*)
        {
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                tTransx << aie::transpose(AccTile[m][n].to_vector<TT_DATA>(shift), TILEdN, TILEdM);
            }
        }
    }
}


//////


void idct_ii_b64_vertical_transform_static::run(
    input_buffer<TT_DATA, extents<BLOCK_SIZE*BLOCK_SIZE>>& __restrict x_transform,
    output_buffer<TT_DATA, extents<BLOCK_SIZE*BLOCK_SIZE>>& __restrict out
){
    static_assert(COEFF_DEPTH == 4096, "B64 direct coeff matrix is 64x64 -> 4096");

    const int bias = 0;
    const int shift = 0;

    TT_DATA* pIn  = x_transform.data();
    TT_DATA* pOut = out.data();
    TT_COEFF* pCoeff = &coeff[0];

    // Input buffer has H^T in transposed tile layout from horizontal kernel.
    // Tiles are 4×4 (IN_TILEdK × TILEdM) at positions: pos = K_tile_4 + X_tile * (BLOCK_SIZE/IN_TILEdK).
    // We read two consecutive K tiles and zip them into one 4×8 A tile for mmul<4,8,4>.

    // Tensor descriptor to read 4×4 tiles from H^T buffer.
    // Two tiles per pop (K_step*2 and K_step*2+1) for each of UNROLL_M X tiles.
    // Total pops per K step: UNROLL_M * 2 tiles = 4 tiles of 16 elements.
    // Read 4×4 tiles (IN_TILEdK=4) from H^T buffer. Two pops per K_step to form one 4×8 A tile.
    auto tdsc_Transx = aie::make_tensor_descriptor<TT_DATA, TILEdM*IN_TILEdK>(
        aie::tensor_dim((BLOCK_SIZE/TILEdM)/UNROLL_M, (BLOCK_SIZE/IN_TILEdK)*UNROLL_M),  // X_group outer: 8, stride=32
        aie::tensor_dim((BLOCK_SIZE/TILEdN)/UNROLL_N, 0),                                  // Y dummy: 4, stride=0
        aie::tensor_dim(BLOCK_SIZE/IN_TILEdK, 1),                                          // K_tile_4: 16, stride=1
        aie::tensor_dim(UNROLL_M, BLOCK_SIZE/IN_TILEdK)                                    // parallel X: 2, stride=16
    );

    // Coeff descriptor: same as horizontal kernel (8×4 tiling)
    auto tdsc_Coeffs = aie::make_tensor_descriptor<TT_COEFF, TILEdK*TILEdN>(
        aie::tensor_dim((BLOCK_SIZE/TILEdM)/UNROLL_M, 0),                    // X dummy
        aie::tensor_dim((BLOCK_SIZE/TILEdN)/UNROLL_N, UNROLL_N),             // Y_group
        aie::tensor_dim(BLOCK_SIZE/TILEdK, (BLOCK_SIZE/TILEdN)),             // K_tile_8
        aie::tensor_dim(UNROLL_N, 1)                                          // parallel Y tiles
    );

    // Output descriptor: result is 4×4, write transposed tiles
    auto tdsc_Transy = aie::make_tensor_descriptor<TT_DATA, TILEdM*TILEdN>(
        aie::tensor_dim((BLOCK_SIZE/TILEdM)/UNROLL_M, UNROLL_M),
        aie::tensor_dim(BLOCK_SIZE/TILEdN, BLOCK_SIZE/TILEdM),
        aie::tensor_dim(UNROLL_M, 1)
    );

    auto tTransx  = aie::make_tensor_buffer_stream(pIn, tdsc_Transx);
    auto tCoeffs  = aie::make_tensor_buffer_stream(pCoeff, tdsc_Coeffs);
    auto tTransy  = aie::make_tensor_buffer_stream(pOut, tdsc_Transy);

    for (int mn = 0; mn < (BLOCK_SIZE*BLOCK_SIZE)/((TILEdM*UNROLL_M)*(TILEdN*UNROLL_N)); ++mn)
    {
        MMUL_V AccTile[UNROLL_M][UNROLL_N];

        // K loop: 8 iterations (BLOCK_SIZE/TILEdK = 64/8)
        // Each iteration reads 2 consecutive 4×4 tiles per X tile, zips into 4×8
        for (int kk = 0; kk < (BLOCK_SIZE/TILEdK); ++kk)
        {
            // Pop two sets of 4×4 tiles from input (K_step*2 and K_step*2+1)
            auto Transx_lo = tTransx.pop();   // UNROLL_M tiles at K_step*2
            auto Transx_hi = tTransx.pop();   // UNROLL_M tiles at K_step*2+1

            auto Coeffs_inner = tCoeffs.pop();

            // Zip two 4×4 tiles into one 4×8 A tile per X tile
            aie::vector<TT_DATA, MMUL_V::size_A> vTransx[UNROLL_M];
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                aie::vector<TT_DATA, TILEdM*IN_TILEdK> tile_lo, tile_hi;
                Transx_lo >> tile_lo;
                Transx_hi >> tile_hi;
                // interleave_zip with chunk_size=4: groups of 4 (one row) from each tile
                // lo: [row0_k0..3, row1_k0..3, row2_k0..3, row3_k0..3]
                // hi: [row0_k4..7, row1_k4..7, row2_k4..7, row3_k4..7]
                // result lo: [row0_k0..3, row0_k4..7, row1_k0..3, row1_k4..7] = first 2 rows of 4×8
                // result hi: [row2_k0..3, row2_k4..7, row3_k0..3, row3_k4..7] = last 2 rows of 4×8
                auto [zip_lo, zip_hi] = aie::interleave_zip(tile_lo, tile_hi, IN_TILEdK);
                vTransx[m] = aie::concat(zip_lo, zip_hi);
            }

            aie::vector<TT_COEFF, MMUL_V::size_B> vCoeffs[UNROLL_N];
            for (int n = 0; n < UNROLL_N; ++n)
                chess_unroll_loop(*)
            {
                Coeffs_inner >> vCoeffs[n];
            }

            if (kk == (BLOCK_SIZE/TILEdK) - 1) {
                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vTransx[m], vCoeffs[n]);
                        AccTile[m][n] = aie::add(AccTile[m][n].to_accum(), bias);
                    }
                }
            } else {
                for (int m = 0; m < UNROLL_M; ++m)
                    chess_unroll_loop(*)
                {
                    for (int n = 0; n < UNROLL_N; ++n)
                        chess_unroll_loop(*)
                    {
                        AccTile[m][n].mac(vTransx[m], vCoeffs[n]);
                    }
                }
            }
        }

        // Write transposed output tiles (4×4 result → transpose for correct 2D layout)
        for (int n = 0; n < UNROLL_N; ++n)
            chess_unroll_loop(*)
        {
            for (int m = 0; m < UNROLL_M; ++m)
                chess_unroll_loop(*)
            {
                tTransy << aie::transpose(AccTile[m][n].to_vector<TT_DATA>(shift), TILEdM, TILEdN);
            }
        }
    }
}


