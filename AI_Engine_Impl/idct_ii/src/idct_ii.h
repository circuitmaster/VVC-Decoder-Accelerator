// forward_b4.h  (FFT-template style)
#pragma once

#include <adf.h>
#include <aie_api/aie.hpp>

using namespace adf;


// class forward_b4 {
// public:

//     typedef int16  TT_DATA;   // input samples (TCoeff-like)
//     typedef int16  TT_COEFF;   // matrix coeffs (TMatrixCoeff-like)
//     typedef acc32  TT_ACC;    // accumulator

//     // ----------------------------
//     // Compile-time configuration
//     // ----------------------------
//     // LINE: how many 4-sample vectors processed per invocation.
//     // SHIFT: fixed-point normalization shift.
//     static constexpr unsigned LINE      = 32;
//     static constexpr unsigned SHIFT     = 6;

//     static constexpr unsigned NSAMP_I = 4 * LINE;
//     static constexpr unsigned NSAMP_O = 4 * LINE;

//     static constexpr unsigned COEFF_DEPTH = 8;

// private:
//     alignas(16) TT_COEFF (&coeff)[COEFF_DEPTH];

// public:

//     // constructor
//     forward_b4(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}


//     void run(input_buffer<TT_DATA, extents<NSAMP_I> >& __restrict sig_i,
//              output_buffer<TT_DATA, extents<NSAMP_O> >& __restrict sig_o,
//              int iSkipLine);


//     static void registerKernelClass(void){
//         REGISTER_FUNCTION(forward_b4::run);
//         REGISTER_PARAMETER(coeff);
//     }
// };

// class idct_ii_b2 {
// public:

//     typedef int16       TT_DATA;
//     typedef int16       TT_COEFF;
//     typedef acc32       TT_ACCUM;

//     static constexpr unsigned COEFF_DEPTH = 8;
//     static constexpr unsigned UNROLL_FACTOR = 8;

// private:
//     alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

// public:
//     // constructor
//     idct_ii_b2(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

//     void run (input_stream<TT_DATA>* in,
//               output_stream<TT_DATA>* out,
//               const int NUM_LINE,
//               const int SHIFT);

//     static void registerKernelClass(){
//         REGISTER_FUNCTION(idct_ii_b2::run);
//         REGISTER_PARAMETER(coeff);
//     }

// };

class idct_ii_b4 {
public:

    typedef int16       TT_DATA;
    typedef int16       TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 16;
    static constexpr unsigned UNROLL_FACTOR = 4;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b4(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_stream<TT_DATA>* __restrict in, 
             output_stream<TT_DATA>* __restrict out,
             const int SIZE,
             const int SHIFT);

    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b4::run);
        REGISTER_PARAMETER(coeff);
    }
};

class idct_ii_b8 {
public:

    typedef int16       TT_DATA;
    typedef int16       TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 64;
    static constexpr unsigned UNROLL_FACTOR = 4;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b8(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_stream<TT_DATA>* __restrict in,
             output_stream<TT_DATA>* __restrict out,
             const int SIZE,
             const int SHIFT);
            
    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b8::run);
        REGISTER_PARAMETER(coeff);
    }
};

// class idct_ii_b16 {
// public:

//     typedef int16       TT_DATA;
//     typedef int16       TT_COEFF;
//     typedef acc32       TT_ACCUM;

//     static constexpr unsigned COEFF_DEPTH = 256;
//     static constexpr unsigned UNROLL_FACTOR = 4;

// private:
//     alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

// public:
//     // constructor
//     idct_ii_b16(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

//     void run(input_stream<TT_DATA>* __restrict in,
//              output_stream<TT_DATA>* __restrict out,
//              const int SIZE,
//              const int SHIFT);
            
//     static void registerKernelClass(){
//         REGISTER_FUNCTION(idct_ii_b16::run);
//         REGISTER_PARAMETER(coeff);
//     }
// };


class idct_ii_b16_buffer_i32_i16_acc64 {
public:

    typedef int32       TT_DATA;
    typedef int16       TT_COEFF;
    typedef acc64       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 256;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b16_buffer_i32_i16_acc64(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_async_buffer<TT_DATA, extents<16*4>>& __restrict in,
             output_async_buffer<TT_DATA, extents<16*4>>& __restrict out,
             const int SIZE,
             const int SHIFT);
            
    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b16_buffer_i32_i16_acc64::run);
        REGISTER_PARAMETER(coeff);
    }
};

class idct_ii_b16_buffer_i16_i8_acc32 {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 256;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b16_buffer_i16_i8_acc32(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_async_buffer<TT_DATA, extents<(4*8)*2>>& __restrict in,
             output_async_buffer<TT_DATA, extents<(4*4)*4>>& __restrict out,
             const int SIZE,
             const int SHIFT);
            
    static void registerKernelClass(){
        REGISTER_FUNCTION( idct_ii_b16_buffer_i16_i8_acc32::run);
        REGISTER_PARAMETER(coeff);
    }
};


class idct_ii_b32_buffer_i32_i16_acc64 {
public:

    typedef int32       TT_DATA;
    typedef int16       TT_COEFF;
    typedef acc64       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 1024;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b32_buffer_i32_i16_acc64(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_async_buffer<TT_DATA, extents<32*4>>& __restrict in,
             output_async_buffer<TT_DATA, extents<32*4>>& __restrict out,
             const int SIZE,
             const int SHIFT);
            
    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b32_buffer_i32_i16_acc64::run);
        REGISTER_PARAMETER(coeff);
    }
};

class idct_ii_b32_buffer_i16_i8_acc32 {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 1024;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b32_buffer_i16_i8_acc32(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_async_buffer<TT_DATA, extents<(4*8)*4>>& __restrict in,
             output_async_buffer<TT_DATA, extents<(4*4)*8>>& __restrict out,
             const int SIZE,
             const int SHIFT);
            
    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b32_buffer_i16_i8_acc32::run);
        REGISTER_PARAMETER(coeff);
    }
};

class idct_ii_b64_buffer_i16_i8_acc32 {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr unsigned COEFF_DEPTH = 4096;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b64_buffer_i16_i8_acc32(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_async_buffer<TT_DATA, extents<(4*8)*8>>& __restrict in,
             output_async_buffer<TT_DATA, extents<(4*4)*16>>& __restrict out,
             const int SIZE,
             const int SHIFT);

    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b64_buffer_i16_i8_acc32::run);
        REGISTER_PARAMETER(coeff);
    }
};

class idct_ii_b64_buffer_i16_i8_acc32_static {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr int BLOCK_SIZE = 64;
    static constexpr int COEFF_DEPTH = 4096;
    static constexpr int BATCH_SIZE = 128;
    static constexpr int FRAME_SIZE = 512;

    static constexpr int UNROLL_N = 4;
    static constexpr int UNROLL_M = 2;

    static constexpr int TILEdM = 4;
    static constexpr int TILEdK = 8;
    static constexpr int TILEdN = 4;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

public:
    // constructor
    idct_ii_b64_buffer_i16_i8_acc32_static(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_buffer<TT_DATA, extents<BATCH_SIZE*BLOCK_SIZE>>& __restrict in,
             output_buffer<TT_DATA, extents<BATCH_SIZE*BLOCK_SIZE>>& __restrict out);

    static void registerKernelClass(){
        REGISTER_FUNCTION(idct_ii_b64_buffer_i16_i8_acc32_static::run);
        REGISTER_PARAMETER(coeff);
    }
};


class idct_ii_b64_horizontal_transform_static {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr int BLOCK_SIZE = 64;
    static constexpr int COEFF_DEPTH = 4096;
    static constexpr int WINDOW_SIZE = BLOCK_SIZE*BLOCK_SIZE;

    static constexpr int UNROLL_N = 2;
    static constexpr int UNROLL_M = 1;

    static constexpr int TILEdM = 4;
    static constexpr int TILEdK = 8;
    static constexpr int TILEdN = 4;

private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

    using MMUL_H = aie::mmul<TILEdM, TILEdK, TILEdN, TT_DATA, TT_COEFF, TT_ACCUM>;

public:
    // constructor
    idct_ii_b64_horizontal_transform_static(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_buffer<TT_DATA, extents<WINDOW_SIZE>>& __restrict in,
             output_buffer<TT_DATA, extents<WINDOW_SIZE>>& __restrict x_transform);

    static void registerKernelClass() {
        REGISTER_FUNCTION(idct_ii_b64_horizontal_transform_static::run);
        REGISTER_PARAMETER(coeff);
    }

};


class idct_ii_b64_vertical_transform_static {
public:

    typedef int16       TT_DATA;
    typedef int8        TT_COEFF;
    typedef acc32       TT_ACCUM;

    static constexpr int BLOCK_SIZE = 64;
    static constexpr int COEFF_DEPTH = 4096;
    static constexpr int WINDOW_SIZE = BLOCK_SIZE*BLOCK_SIZE;

    static constexpr int UNROLL_N = 2;
    static constexpr int UNROLL_M = 2;

    static constexpr int TILEdM = 4;
    static constexpr int TILEdK = 4;
    static constexpr int TILEdN = 8;


private:
    alignas(32) TT_COEFF (&coeff)[COEFF_DEPTH];

    using MMUL_V = aie::mmul<TILEdM, TILEdK, TILEdN, TT_DATA, TT_COEFF, TT_ACCUM>;

public:
    // constructor
    idct_ii_b64_vertical_transform_static(TT_COEFF (&coeff_i)[COEFF_DEPTH]) : coeff(coeff_i) {}

    void run(input_buffer<TT_DATA, extents<WINDOW_SIZE>>& __restrict x_transform,
             output_buffer<TT_DATA, extents<WINDOW_SIZE>>& __restrict out);

    static void registerKernelClass() {
        REGISTER_FUNCTION(idct_ii_b64_vertical_transform_static::run);
        REGISTER_PARAMETER(coeff);
    }

};



