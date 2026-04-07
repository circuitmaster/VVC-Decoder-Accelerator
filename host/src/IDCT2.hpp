#include <iostream>
#include "ap_int.h"
#include "ap_fixed.h"
#include "transform_coeffs.h"

//#define USE_SHIFT_ADD_64
//#define USE_SHIFT_ADD_32
//#define USE_SHIFT_ADD_16
//#define USE_SHIFT_ADD_8
//#define USE_SHIFT_ADD_4

#define IN_TYPE ap_int<32>
#define OUT_TYPE ap_int<32>

ap_int<16> CLIP3(ap_int<32> x, ap_int<16> outputMinimum, ap_int<16> outputMaximum){
    #pragma HLS inline
    if(x < outputMinimum) return outputMinimum;
    if(x > outputMaximum) return outputMaximum;
    return x;
}

void IDCT2B2(IN_TYPE in[2], OUT_TYPE out[2]){
    #pragma HLS inline off

    ap_int<32> sum = in[0] + in[1];
    ap_int<32> diff = in[0] - in[1];

    ap_int<32> even = sum << 6;
    ap_int<32> odd = diff << 6;

    out[0] = even;
    out[1] = odd;
}

void IDCT2B4(IN_TYPE in[4], OUT_TYPE out[4]){
    #pragma HLS inline off

    ap_int<32> evens[2];
    ap_int<32> odds[2];
    ap_int<32> odds2[2];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    IN_TYPE inputs[2];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
    inputs[0] = in[0];
    inputs[1] = in[2];

    IDCT2B2(inputs, evens);

    #ifdef USE_SHIFT_ADD_4

    ap_int<32> in1_a = in[1] << 6;
    ap_int<32> in1_b = in[1] << 5;
    ap_int<32> in1_c = in[1] << 4;
    ap_int<32> in1_d = in[1] << 3;
    ap_int<32> in1_e = in[1] << 2;
    ap_int<32> in1_f = in[1] << 1;
    ap_int<32> in1_g = in[1];

    ap_int<32> in3_a = in[3] << 6;
    ap_int<32> in3_b = in[3] << 5;
    ap_int<32> in3_c = in[3] << 4;
    ap_int<32> in3_d = in[3] << 3;
    ap_int<32> in3_e = in[3] << 2;
    ap_int<32> in3_f = in[3] << 1;
    ap_int<32> in3_g = in[3];

    ap_int<32> in1s[2];
    #pragma HLS ARRAY_PARTITION variable=in1s complete dim=0

    in1s[0] = in1_a + in1_c + in1_f + in1_g; // *83
    in1s[1] = in1_b + in1_e; // *36

    ap_int<32> in3s[2];
    #pragma HLS ARRAY_PARTITION variable=in3s complete dim=0

    in3s[0] = in3_b + in3_e; // *36
    in3s[1] = -(in3_a + in3_c + in3_f + in3_g); // *83

    odds[0] = in1s[0] + in3s[0];
    odds[1] = in1s[1] + in3s[1];
    
    #else
    odds[0] = 83*in[1] + 36*in[3];
    odds[1] = 36*in[1] - 83*in[3];
    #endif

    // print inputs for debugging
    /* std::cout << "IDCT2B4 inputs: " << in[0] << ", " << in[1] << ", " << in[2] << ", " << in[3] << std::endl;
    if(odds[0] != odds2[0] || odds[1] != odds2[1]){
        //print in1a to in1g for debugging
        std::cout << "IDCT2B4 in1a: " << in1_a << ", in1b: " << in1_b << ", in1c: " << in1_c << ", in1d: " << in1_d << ", in1e: " << in1_e << ", in1f: " << in1_f << ", in1g: " << in1_g << std::endl;
        //print in3a to in3g for debugging
        std::cout << "IDCT2B4 in3a: " << in3_a << ", in3b: " << in3_b << ", in3c: " << in3_c << ", in3d: " << in3_d << ", in3e: " << in3_e << ", in3f: " << in3_f << ", in3g: " << in3_g << std::endl;

        // print in1s and in3s results for debugging
        std::cout << "IDCT2B4 in1s: " << in1s[0] << ", " << in1s[1] << std::endl;
        std::cout << "IDCT2B4 in3s: " << in3s[0] << ", " << in3s[1] << std::endl;
        std::cout << "IDCT2B4 shift-add mismatch: " << odds[0] << " vs " << odds2[0]
                  << ", " << odds[1] << " vs " << odds2[1] << std::endl;
    } */

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[1] - odds[1];
    out[3] = evens[0] - odds[0];
}

void IDCT2B8(IN_TYPE in[8], OUT_TYPE out[8]){
    #pragma HLS inline off

    ap_int<32> evens[4];
    ap_int<32> odds[4];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    IN_TYPE inputs[4];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
    inputs[0] = in[0];
    inputs[2] = in[4];
    inputs[1] = in[2];
    inputs[3] = in[6];

    IDCT2B4(inputs, evens);

    #ifdef USE_SHIFT_ADD_8

    ap_int<32> in1_a = in[1] << 6;
    ap_int<32> in1_b = in[1] << 5;
    ap_int<32> in1_c = in[1] << 4;
    ap_int<32> in1_d = in[1] << 3;
    ap_int<32> in1_e = in[1] << 2;
    ap_int<32> in1_f = in[1] << 1;
    ap_int<32> in1_g = in[1];

    ap_int<32> in3_a = in[3] << 6;
    ap_int<32> in3_b = in[3] << 5;
    ap_int<32> in3_c = in[3] << 4;
    ap_int<32> in3_d = in[3] << 3;
    ap_int<32> in3_e = in[3] << 2;
    ap_int<32> in3_f = in[3] << 1;
    ap_int<32> in3_g = in[3];

    ap_int<32> in5_a = in[5] << 6;
    ap_int<32> in5_b = in[5] << 5;
    ap_int<32> in5_c = in[5] << 4;
    ap_int<32> in5_d = in[5] << 3;
    ap_int<32> in5_e = in[5] << 2;
    ap_int<32> in5_f = in[5] << 1;
    ap_int<32> in5_g = in[5];

    ap_int<32> in7_a = in[7] << 6;
    ap_int<32> in7_b = in[7] << 5;
    ap_int<32> in7_c = in[7] << 4;
    ap_int<32> in7_d = in[7] << 3;
    ap_int<32> in7_e = in[7] << 2;
    ap_int<32> in7_f = in[7] << 1;
    ap_int<32> in7_g = in[7];

    ap_int<32> in1s[4];
    #pragma HLS ARRAY_PARTITION variable=in1s complete dim=0

    in1s[0] = in1_a + in1_c + in1_d + in1_g; // *89
    in1s[1] = in1_a + in1_d + in1_f + in1_g; // *75
    in1s[2] = in1_b + in1_c + in1_f; // *50
    in1s[3] = in1_c + in1_f; // *18

    ap_int<32> in3s[4];
    #pragma HLS ARRAY_PARTITION variable=in3s complete dim=0

    in3s[0] = in3_a + in3_d + in3_f + in3_g; // *75
    in3s[1] = - (in3_c + in3_f); // *18
    in3s[2] = - (in3_a + in3_c + in3_d + in3_g); // *89
    in3s[3] = - (in3_b + in3_c + in3_f); // *50

    ap_int<32> in5s[4];
    #pragma HLS ARRAY_PARTITION variable=in5s complete dim=0

    in5s[0] = in5_b + in5_c + in5_f; // *50
    in5s[1] = - (in5_a + in5_c + in5_d + in5_g); // *89
    in5s[2] = in5_c + in5_f; // *18
    in5s[3] = in5_a + in5_d + in5_f + in5_g; // *75

    ap_int<32> in7s[4];
    #pragma HLS ARRAY_PARTITION variable=in7s complete dim=0

    in7s[0] = in7_c + in7_f; // *18
    in7s[1] = - (in7_b + in7_c + in7_f); // *50
    in7s[2] = in7_a + in7_d + in7_f + in7_g; // *75
    in7s[3] = - (in7_a + in7_c + in7_d + in7_g); // *89

    for(int i=0; i<4; i++){
        #pragma HLS UNROLL
        odds[i] = in1s[i] + in3s[i] + in5s[i] + in7s[i];
    }

    #else

    odds[0] = 89*in[1] + 75*in[3] + 50*in[5] + 18*in[7];
    odds[1] = 75*in[1] - 18*in[3] - 89*in[5] - 50*in[7];
    odds[2] = 50*in[1] - 89*in[3] + 18*in[5] + 75*in[7];
    odds[3] = 18*in[1] - 50*in[3] + 75*in[5] - 89*in[7];

    #endif

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[2] + odds[2];
    out[3] = evens[3] + odds[3];
    out[4] = evens[3] - odds[3];
    out[5] = evens[2] - odds[2];
    out[6] = evens[1] - odds[1];
    out[7] = evens[0] - odds[0];
}

void IDCT2B16(IN_TYPE in[16], OUT_TYPE out[16]){
    #pragma HLS inline off

    ap_int<32> evens[8];
    ap_int<32> odds[8];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    IN_TYPE inputs[8];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
    inputs[0] = in[0];
    inputs[4] = in[8];
    inputs[2] = in[4];
    inputs[6] = in[12];
    inputs[1] = in[2];
    inputs[3] = in[6];
    inputs[5] = in[10];
    inputs[7] = in[14];

    IDCT2B8(inputs, evens);

    #ifdef USE_SHIFT_ADD_16

    ap_int<32> in1_a = in[1] << 6;
    ap_int<32> in1_b = in[1] << 5;
    ap_int<32> in1_c = in[1] << 4;
    ap_int<32> in1_d = in[1] << 3;
    ap_int<32> in1_e = in[1] << 2;
    ap_int<32> in1_f = in[1] << 1;
    ap_int<32> in1_g = in[1];

    ap_int<32> in3_a = in[3] << 6;
    ap_int<32> in3_b = in[3] << 5;
    ap_int<32> in3_c = in[3] << 4;
    ap_int<32> in3_d = in[3] << 3;
    ap_int<32> in3_e = in[3] << 2;
    ap_int<32> in3_f = in[3] << 1;
    ap_int<32> in3_g = in[3];

    ap_int<32> in5_a = in[5] << 6;
    ap_int<32> in5_b = in[5] << 5;
    ap_int<32> in5_c = in[5] << 4;
    ap_int<32> in5_d = in[5] << 3;
    ap_int<32> in5_e = in[5] << 2;
    ap_int<32> in5_f = in[5] << 1;
    ap_int<32> in5_g = in[5];

    ap_int<32> in7_a = in[7] << 6;
    ap_int<32> in7_b = in[7] << 5;
    ap_int<32> in7_c = in[7] << 4;
    ap_int<32> in7_d = in[7] << 3;
    ap_int<32> in7_e = in[7] << 2;
    ap_int<32> in7_f = in[7] << 1;
    ap_int<32> in7_g = in[7];

    ap_int<32> in9_a = in[9] << 6;
    ap_int<32> in9_b = in[9] << 5;
    ap_int<32> in9_c = in[9] << 4;
    ap_int<32> in9_d = in[9] << 3;
    ap_int<32> in9_e = in[9] << 2;
    ap_int<32> in9_f = in[9] << 1;
    ap_int<32> in9_g = in[9];

    ap_int<32> in11_a = in[11] << 6;
    ap_int<32> in11_b = in[11] << 5;
    ap_int<32> in11_c = in[11] << 4;
    ap_int<32> in11_d = in[11] << 3;
    ap_int<32> in11_e = in[11] << 2;
    ap_int<32> in11_f = in[11] << 1;
    ap_int<32> in11_g = in[11];

    ap_int<32> in13_a = in[13] << 6;
    ap_int<32> in13_b = in[13] << 5;
    ap_int<32> in13_c = in[13] << 4;
    ap_int<32> in13_d = in[13] << 3;
    ap_int<32> in13_e = in[13] << 2;
    ap_int<32> in13_f = in[13] << 1;
    ap_int<32> in13_g = in[13];

    ap_int<32> in15_a = in[15] << 6;
    ap_int<32> in15_b = in[15] << 5;
    ap_int<32> in15_c = in[15] << 4;
    ap_int<32> in15_d = in[15] << 3;
    ap_int<32> in15_e = in[15] << 2;
    ap_int<32> in15_f = in[15] << 1;
    ap_int<32> in15_g = in[15];

    ap_int<32> in1s[8];
    #pragma HLS ARRAY_PARTITION variable=in1s complete dim=0

    in1s[0] = in1_a + in1_c + in1_d + in1_f;
    in1s[1] = in1_a + in1_c + in1_e + in1_f + in1_g;
    in1s[2] = in1_a + in1_c;
    in1s[3] = in1_a + in1_e + in1_f;
    in1s[4] = in1_b + in1_c + in1_d + in1_g;
    in1s[5] = in1_b + in1_d + in1_f + in1_g;
    in1s[6] = in1_c + in1_d + in1_g;
    in1s[7] = in1_d + in1_g;

    ap_int<32> in3s[8];
    #pragma HLS ARRAY_PARTITION variable=in3s complete dim=0

    in3s[0] = in3_a + in3_c + in3_e + in3_f + in3_g;
    in3s[1] = in3_b + in3_c + in3_d + in3_g;
    in3s[2] = in3_d + in3_g;
    in3s[3] = -(in3_b + in3_d + in3_f + in3_g);
    in3s[4] = -(in3_a + in3_c);
    in3s[5] = -(in3_a + in3_c + in3_d + in3_f);
    in3s[6] = -(in3_a + in3_e + in3_f);
    in3s[7] = -(in3_c + in3_d + in3_g);

    ap_int<32> in5s[8];
    #pragma HLS ARRAY_PARTITION variable=in5s complete dim=0

    in5s[0] = in5_a + in5_c;
    in5s[1] = in5_d + in5_g;
    in5s[2] = -(in5_a + in5_e + in5_f);
    in5s[3] = -(in5_a + in5_c + in5_e + in5_f + in5_g);
    in5s[4] = -(in5_c + in5_d + in5_g);
    in5s[5] = in5_b + in5_c + in5_d + in5_g;
    in5s[6] = in5_a + in5_c + in5_d + in5_f;
    in5s[7] = in5_b + in5_d + in5_f + in5_g;

    ap_int<32> in7s[8];
    #pragma HLS ARRAY_PARTITION variable=in7s complete dim=0

    in7s[0] = in7_a + in7_e + in7_f;
    in7s[1] = -(in7_b + in7_d + in7_f + in7_g);
    in7s[2] = -(in7_a + in7_c + in7_e + in7_f + in7_g);
    in7s[3] = in7_d + in7_g;
    in7s[4] = in7_a + in7_c + in7_d + in7_f;
    in7s[5] = in7_c + in7_d + in7_g;
    in7s[6] = -(in7_a + in7_c);
    in7s[7] = -(in7_b + in7_c + in7_d + in7_g);

    ap_int<32> in9s[8];
    #pragma HLS ARRAY_PARTITION variable=in9s complete dim=0

    in9s[0] = in9_b + in9_c + in9_d + in9_g;
    in9s[1] = -(in9_a + in9_c);
    in9s[2] = -(in9_c + in9_d + in9_g);
    in9s[3] = in9_a + in9_c + in9_d + in9_f;
    in9s[4] = -(in9_d + in9_g);
    in9s[5] = -(in9_a + in9_c + in9_e + in9_f + in9_g);
    in9s[6] = in9_b + in9_d + in9_f + in9_g;
    in9s[7] = in9_a + in9_e + in9_f;

    ap_int<32> in11s[8];
    #pragma HLS ARRAY_PARTITION variable=in11s complete dim=0

    in11s[0] = in11_b + in11_d + in11_f + in11_g;
    in11s[1] = -(in11_a + in11_c + in11_d + in11_f);
    in11s[2] = in11_b + in11_c + in11_d + in11_g;
    in11s[3] = in11_c + in11_d + in11_g;
    in11s[4] = -(in11_a + in11_c + in11_e + in11_f + in11_g);
    in11s[5] = in11_a + in11_e + in11_f;
    in11s[6] = in11_d + in11_g;
    in11s[7] = -(in11_a + in11_c);

    ap_int<32> in13s[8];
    #pragma HLS ARRAY_PARTITION variable=in13s complete dim=0

    in13s[0] = in13_c + in13_d + in13_g;
    in13s[1] = -(in13_a + in13_e + in13_f);
    in13s[2] = in13_a + in13_c + in13_d + in13_f;
    in13s[3] = -(in13_a + in13_c);
    in13s[4] = in13_b + in13_d + in13_f + in13_g;
    in13s[5] = in13_d + in13_g;
    in13s[6] = -(in13_b + in13_c + in13_d + in13_g);
    in13s[7] = in13_a + in13_c + in13_e + in13_f + in13_g;

    ap_int<32> in15s[8];
    #pragma HLS ARRAY_PARTITION variable=in15s complete dim=0

    in15s[0] = in15_d + in15_g;
    in15s[1] = -(in15_c + in15_d + in15_g);
    in15s[2] = in15_b + in15_d + in15_f + in15_g;
    in15s[3] = -(in15_b + in15_c + in15_d + in15_g);
    in15s[4] = in15_a + in15_e + in15_f;
    in15s[5] = -(in15_a + in15_c);
    in15s[6] = in15_a + in15_c + in15_e + in15_f + in15_g;
    in15s[7] = -(in15_a + in15_c + in15_d + in15_f);

    for(int i=0; i<8; i++){
        #pragma HLS UNROLL
        odds[i] = in1s[i] + in3s[i] + in5s[i] + in7s[i] + in9s[i] + in11s[i] + in13s[i] + in15s[i];
    }

    #else

    for(int i=0; i<8; i++){
        #pragma HLS UNROLL
        odds[i] = idct16[1][i]*in[1] + idct16[3][i]*in[3] + idct16[5][i]*in[5] + idct16[7][i]*in[7] + idct16[9][i]*in[9] + idct16[11][i]*in[11] + idct16[13][i]*in[13] + idct16[15][i]*in[15];
    }

    #endif

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[2] + odds[2];
    out[3] = evens[3] + odds[3];
    out[4] = evens[4] + odds[4];
    out[5] = evens[5] + odds[5];
    out[6] = evens[6] + odds[6];
    out[7] = evens[7] + odds[7];
    out[8] = evens[7] - odds[7];
    out[9] = evens[6] - odds[6];
    out[10] = evens[5] - odds[5];
    out[11] = evens[4] - odds[4];
    out[12] = evens[3] - odds[3];
    out[13] = evens[2] - odds[2];
    out[14] = evens[1] - odds[1];
    out[15] = evens[0] - odds[0];
}

void IDCT2B32(IN_TYPE in[32], OUT_TYPE out[32]){
    #pragma HLS inline off

    ap_int<32> evens[16];
    ap_int<32> odds[16];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    IN_TYPE inputs[16];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0

    inputs[0] = in[0];
    inputs[8] = in[16];
    inputs[4] = in[8];
    inputs[12] = in[24];
    inputs[2] = in[4];
    inputs[6] = in[12];
    inputs[10] = in[20];
    inputs[14] = in[28];
    inputs[1] = in[2];
    inputs[3] = in[6];
    inputs[5] = in[10];
    inputs[7] = in[14];
    inputs[9] = in[18];
    inputs[11] = in[22];
    inputs[13] = in[26];
    inputs[15] = in[30];

    IDCT2B16(inputs, evens);

    #ifdef USE_SHIFT_ADD_32

    ap_int<32> in1_a = in[1] << 6;
    ap_int<32> in1_b = in[1] << 5;
    ap_int<32> in1_c = in[1] << 4;
    ap_int<32> in1_d = in[1] << 3;
    ap_int<32> in1_e = in[1] << 2;
    ap_int<32> in1_f = in[1] << 1;
    ap_int<32> in1_g = in[1];

    ap_int<32> in3_a = in[3] << 6;
    ap_int<32> in3_b = in[3] << 5;
    ap_int<32> in3_c = in[3] << 4;
    ap_int<32> in3_d = in[3] << 3;
    ap_int<32> in3_e = in[3] << 2;
    ap_int<32> in3_f = in[3] << 1;
    ap_int<32> in3_g = in[3];

    ap_int<32> in5_a = in[5] << 6;
    ap_int<32> in5_b = in[5] << 5;
    ap_int<32> in5_c = in[5] << 4;
    ap_int<32> in5_d = in[5] << 3;
    ap_int<32> in5_e = in[5] << 2;
    ap_int<32> in5_f = in[5] << 1;
    ap_int<32> in5_g = in[5];

    ap_int<32> in7_a = in[7] << 6;
    ap_int<32> in7_b = in[7] << 5;
    ap_int<32> in7_c = in[7] << 4;
    ap_int<32> in7_d = in[7] << 3;
    ap_int<32> in7_e = in[7] << 2;
    ap_int<32> in7_f = in[7] << 1;
    ap_int<32> in7_g = in[7];

    ap_int<32> in9_a = in[9] << 6;
    ap_int<32> in9_b = in[9] << 5;
    ap_int<32> in9_c = in[9] << 4;
    ap_int<32> in9_d = in[9] << 3;
    ap_int<32> in9_e = in[9] << 2;
    ap_int<32> in9_f = in[9] << 1;
    ap_int<32> in9_g = in[9];

    ap_int<32> in11_a = in[11] << 6;
    ap_int<32> in11_b = in[11] << 5;
    ap_int<32> in11_c = in[11] << 4;
    ap_int<32> in11_d = in[11] << 3;
    ap_int<32> in11_e = in[11] << 2;
    ap_int<32> in11_f = in[11] << 1;
    ap_int<32> in11_g = in[11];

    ap_int<32> in13_a = in[13] << 6;
    ap_int<32> in13_b = in[13] << 5;
    ap_int<32> in13_c = in[13] << 4;
    ap_int<32> in13_d = in[13] << 3;
    ap_int<32> in13_e = in[13] << 2;
    ap_int<32> in13_f = in[13] << 1;
    ap_int<32> in13_g = in[13];

    ap_int<32> in15_a = in[15] << 6;
    ap_int<32> in15_b = in[15] << 5;
    ap_int<32> in15_c = in[15] << 4;
    ap_int<32> in15_d = in[15] << 3;
    ap_int<32> in15_e = in[15] << 2;
    ap_int<32> in15_f = in[15] << 1;
    ap_int<32> in15_g = in[15];

    ap_int<32> in17_a = in[17] << 6;
    ap_int<32> in17_b = in[17] << 5;
    ap_int<32> in17_c = in[17] << 4;
    ap_int<32> in17_d = in[17] << 3;
    ap_int<32> in17_e = in[17] << 2;
    ap_int<32> in17_f = in[17] << 1;
    ap_int<32> in17_g = in[17];

    ap_int<32> in19_a = in[19] << 6;
    ap_int<32> in19_b = in[19] << 5;
    ap_int<32> in19_c = in[19] << 4;
    ap_int<32> in19_d = in[19] << 3;
    ap_int<32> in19_e = in[19] << 2;
    ap_int<32> in19_f = in[19] << 1;
    ap_int<32> in19_g = in[19];

    ap_int<32> in21_a = in[21] << 6;
    ap_int<32> in21_b = in[21] << 5;
    ap_int<32> in21_c = in[21] << 4;
    ap_int<32> in21_d = in[21] << 3;
    ap_int<32> in21_e = in[21] << 2;
    ap_int<32> in21_f = in[21] << 1;
    ap_int<32> in21_g = in[21];

    ap_int<32> in23_a = in[23] << 6;
    ap_int<32> in23_b = in[23] << 5;
    ap_int<32> in23_c = in[23] << 4;
    ap_int<32> in23_d = in[23] << 3;
    ap_int<32> in23_e = in[23] << 2;
    ap_int<32> in23_f = in[23] << 1;
    ap_int<32> in23_g = in[23];

    ap_int<32> in25_a = in[25] << 6;
    ap_int<32> in25_b = in[25] << 5;
    ap_int<32> in25_c = in[25] << 4;
    ap_int<32> in25_d = in[25] << 3;
    ap_int<32> in25_e = in[25] << 2;
    ap_int<32> in25_f = in[25] << 1;
    ap_int<32> in25_g = in[25];

    ap_int<32> in27_a = in[27] << 6;
    ap_int<32> in27_b = in[27] << 5;
    ap_int<32> in27_c = in[27] << 4;
    ap_int<32> in27_d = in[27] << 3;
    ap_int<32> in27_e = in[27] << 2;
    ap_int<32> in27_f = in[27] << 1;
    ap_int<32> in27_g = in[27];

    ap_int<32> in29_a = in[29] << 6;
    ap_int<32> in29_b = in[29] << 5;
    ap_int<32> in29_c = in[29] << 4;
    ap_int<32> in29_d = in[29] << 3;
    ap_int<32> in29_e = in[29] << 2;
    ap_int<32> in29_f = in[29] << 1;
    ap_int<32> in29_g = in[29];

    ap_int<32> in31_a = in[31] << 6;
    ap_int<32> in31_b = in[31] << 5;
    ap_int<32> in31_c = in[31] << 4;
    ap_int<32> in31_d = in[31] << 3;
    ap_int<32> in31_e = in[31] << 2;
    ap_int<32> in31_f = in[31] << 1;
    ap_int<32> in31_g = in[31];

    ap_int<32> in1s[16];
    #pragma HLS ARRAY_PARTITION variable=in1s complete dim=0

    in1s[0] = in1_a + in1_c + in1_d + in1_f; // *90
    in1s[1] = in1_a + in1_c + in1_d + in1_f; // *90 
    in1s[2] = in1_a + in1_c + in1_d; // *88
    in1s[3] = in1_a + in1_c + in1_e + in1_f; // *85
    in1s[4] = in1_a + in1_c + in1_f; // *82
    in1s[5] = in1_a + in1_d + in1_e + in1_f; // *78
    in1s[6] = in1_a + in1_d + in1_g; // *73
    in1s[7] = in1_a + in1_f + in1_g; // *67
    in1s[8] = in1_b + in1_c + in1_d + in1_e + in1_g; // *61
    in1s[9] = in1_b + in1_c + in1_e + in1_f; // *54
    in1s[10] = in1_b + in1_d + in1_e + in1_f; // *46
    in1s[11] = in1_b + in1_d + in1_e; // *38
    in1s[12] = in1_c + in1_d + in1_e + in1_f + in1_g; // *31
    in1s[13] = in1_c + in1_e + in1_f; // *24
    in1s[14] = in1_d + in1_e + in1_g; // *13
    in1s[15] = in1_e; // *4

    ap_int<32> in3s[16];
    #pragma HLS ARRAY_PARTITION variable=in3s complete dim=0

    in3s[0] = in3_a + in3_c + in3_d + in3_f;
    in3s[1] = in3_a + in3_c + in3_f;
    in3s[2] = in3_a + in3_f + in3_g;
    in3s[3] = in3_b + in3_d + in3_e + in3_f;
    in3s[4] = in3_c + in3_e + in3_f;
    in3s[5] = -(in3_e);
    in3s[6] = -(in3_c + in3_d + in3_e + in3_f + in3_g);
    in3s[7] = -(in3_b + in3_c + in3_e + in3_f);
    in3s[8] = -(in3_a + in3_d + in3_g);
    in3s[9] = -(in3_a + in3_c + in3_e + in3_g);
    in3s[10] = -(in3_a + in3_c + in3_d + in3_f);
    in3s[11] = -(in3_a + in3_c + in3_d);
    in3s[12] = -(in3_a + in3_d + in3_e + in3_f);
    in3s[13] = -(in3_b + in3_c + in3_d + in3_e + in3_g);
    in3s[14] = -(in3_b + in3_e + in3_f);
    in3s[15] = -(in3_d + in3_e + in3_g);

    ap_int<32> in5s[16];
    #pragma HLS ARRAY_PARTITION variable=in5s complete dim=0

    in5s[0] = in5_a + in5_c + in5_d;
    in5s[1] = in5_a + in5_f + in5_g;
    in5s[2] = in5_c + in5_d + in5_e + in5_f + in5_g;
    in5s[3] = -(in5_d + in5_e + in5_g);
    in5s[4] = -(in5_b + in5_c + in5_e + in5_f);
    in5s[5] = -(in5_a + in5_c + in5_f);
    in5s[6] = -(in5_a + in5_c + in5_d + in5_f);
    in5s[7] = -(in5_a + in5_d + in5_e + in5_f);
    in5s[8] = -(in5_b + in5_d + in5_e + in5_f);
    in5s[9] = -(in5_e);
    in5s[10] = in5_b + in5_e + in5_f;
    in5s[11] = in5_a + in5_d + in5_g;
    in5s[12] = in5_a + in5_c + in5_d + in5_f;
    in5s[13] = in5_a + in5_c + in5_e + in5_g;
    in5s[14] = in5_b + in5_c + in5_d + in5_e + in5_g;
    in5s[15] = in5_c + in5_e + in5_f;

    ap_int<32> in7s[16];
    #pragma HLS ARRAY_PARTITION variable=in7s complete dim=0

    in7s[0] = in7_a + in7_c + in7_e + in7_g;
    in7s[1] = in7_b + in7_d + in7_e + in7_f;
    in7s[2] = -(in7_d + in7_e + in7_g);
    in7s[3] = -(in7_a + in7_f + in7_g);
    in7s[4] = -(in7_a + in7_c + in7_d + in7_f);
    in7s[5] = -(in7_a + in7_d + in7_g);
    in7s[6] = -(in7_c + in7_e + in7_f);
    in7s[7] = in7_b + in7_e + in7_f;
    in7s[8] = in7_a + in7_c + in7_f;
    in7s[9] = in7_a + in7_c + in7_d;
    in7s[10] = in7_b + in7_c + in7_e + in7_f;
    in7s[11] = -(in7_e);
    in7s[12] = -(in7_b + in7_c + in7_d + in7_e + in7_g);
    in7s[13] = -(in7_a + in7_c + in7_d + in7_f);
    in7s[14] = -(in7_a + in7_d + in7_e + in7_f);
    in7s[15] = -(in7_c + in7_d + in7_e + in7_f + in7_g);

    ap_int<32> in9s[16];
    #pragma HLS ARRAY_PARTITION variable=in9s complete dim=0

    in9s[0] = in9_a + in9_c + in9_f;
    in9s[1] = in9_c + in9_e + in9_f;
    in9s[2] = -(in9_b + in9_c + in9_e + in9_f);
    in9s[3] = -(in9_a + in9_c + in9_d + in9_f);
    in9s[4] = -(in9_b + in9_c + in9_d + in9_e + in9_g);
    in9s[5] = in9_d + in9_e + in9_g;
    in9s[6] = in9_a + in9_d + in9_e + in9_f;
    in9s[7] = in9_a + in9_c + in9_e + in9_g;
    in9s[8] = in9_c + in9_d + in9_e + in9_f + in9_g;
    in9s[9] = -(in9_b + in9_d + in9_e + in9_f);
    in9s[10] = -(in9_a + in9_c + in9_d + in9_f);
    in9s[11] = -(in9_a + in9_f + in9_g);
    in9s[12] = in9_e;
    in9s[13] = in9_a + in9_d + in9_g;
    in9s[14] = in9_a + in9_c + in9_d;
    in9s[15] = in9_b + in9_e + in9_f;

    ap_int<32> in11s[16];
    #pragma HLS ARRAY_PARTITION variable=in11s complete dim=0

    in11s[0] = in11_a + in11_d + in11_e + in11_f;
    in11s[1] = -(in11_e);
    in11s[2] = -(in11_a + in11_c + in11_f);
    in11s[3] = -(in11_a + in11_d + in11_g);
    in11s[4] = in11_d + in11_e + in11_g;
    in11s[5] = in11_a + in11_c + in11_e + in11_g;
    in11s[6] = in11_a + in11_f + in11_g;
    in11s[7] = -(in11_c + in11_e + in11_f);
    in11s[8] = -(in11_a + in11_c + in11_d);
    in11s[9] = -(in11_b + in11_c + in11_d + in11_e + in11_g);
    in11s[10] = in11_c + in11_d + in11_e + in11_f + in11_g;
    in11s[11] = in11_a + in11_c + in11_d + in11_f;
    in11s[12] = in11_b + in11_c + in11_e + in11_f;
    in11s[13] = -(in11_b + in11_e + in11_f);
    in11s[14] = -(in11_a + in11_c + in11_d + in11_f);
    in11s[15] = -(in11_b + in11_d + in11_e + in11_f);

    ap_int<32> in13s[16];
    #pragma HLS ARRAY_PARTITION variable=in13s complete dim=0

    in13s[0] = in13_a + in13_d + in13_g;
    in13s[1] = -(in13_c + in13_d + in13_e + in13_f + in13_g);
    in13s[2] = -(in13_a + in13_c + in13_d + in13_f);
    in13s[3] = -(in13_c + in13_e + in13_f);
    in13s[4] = in13_a + in13_d + in13_e + in13_f;
    in13s[5] = in13_a + in13_f + in13_g;
    in13s[6] = -(in13_b + in13_e + in13_f);
    in13s[7] = -(in13_a + in13_c + in13_d + in13_f);
    in13s[8] = -(in13_d + in13_e + in13_g);
    in13s[9] = in13_a + in13_c + in13_f;
    in13s[10] = in13_b + in13_c + in13_d + in13_e + in13_g;
    in13s[11] = -(in13_b + in13_d + in13_e + in13_f);
    in13s[12] = -(in13_a + in13_c + in13_d);
    in13s[13] = -(in13_e);
    in13s[14] = in13_a + in13_c + in13_e + in13_g;
    in13s[15] = in13_b + in13_c + in13_e + in13_f;

    ap_int<32> in15s[16];
    #pragma HLS ARRAY_PARTITION variable=in15s complete dim=0

    in15s[0] = in15_a + in15_f + in15_g;
    in15s[1] = -(in15_b + in15_c + in15_e + in15_f);
    in15s[2] = -(in15_a + in15_d + in15_e + in15_f);
    in15s[3] = in15_b + in15_e + in15_f;
    in15s[4] = in15_a + in15_c + in15_e + in15_g;
    in15s[5] = -(in15_c + in15_e + in15_f);
    in15s[6] = -(in15_a + in15_c + in15_d + in15_f);
    in15s[7] = in15_e;
    in15s[8] = in15_a + in15_c + in15_d + in15_f;
    in15s[9] = in15_d + in15_e + in15_g;
    in15s[10] = -(in15_a + in15_c + in15_d);
    in15s[11] = -(in15_c + in15_d + in15_e + in15_f + in15_g);
    in15s[12] = in15_a + in15_c + in15_f;
    in15s[13] = in15_b + in15_d + in15_e + in15_f;
    in15s[14] = -(in15_a + in15_d + in15_g);
    in15s[15] = -(in15_b + in15_c + in15_d + in15_e + in15_g);

    ap_int<32> in17s[16];
    #pragma HLS ARRAY_PARTITION variable=in17s complete dim=0

    in17s[0] = in17_b + in17_c + in17_d + in17_e + in17_g;
    in17s[1] = -(in17_a + in17_d + in17_g);
    in17s[2] = -(in17_b + in17_d + in17_e + in17_f);
    in17s[3] = in17_a + in17_c + in17_f;
    in17s[4] = in17_c + in17_d + in17_e + in17_f + in17_g;
    in17s[5] = -(in17_a + in17_c + in17_d);
    in17s[6] = -(in17_d + in17_e + in17_g);
    in17s[7] = in17_a + in17_c + in17_d + in17_f;
    in17s[8] = -(in17_e);
    in17s[9] = -(in17_a + in17_c + in17_d + in17_f);
    in17s[10] = in17_c + in17_e + in17_f;
    in17s[11] = in17_a + in17_c + in17_e + in17_g;
    in17s[12] = -(in17_b + in17_e + in17_f);
    in17s[13] = -(in17_a + in17_d + in17_e + in17_f);
    in17s[14] = in17_b + in17_c + in17_e + in17_f;
    in17s[15] = in17_a + in17_f + in17_g;

    ap_int<32> in19s[16];
    #pragma HLS ARRAY_PARTITION variable=in19s complete dim=0

    in19s[0] = in19_b + in19_c + in19_e + in19_f;
    in19s[1] = -(in19_a + in19_c + in19_e + in19_g);
    in19s[2] = -(in19_e);
    in19s[3] = in19_a + in19_c + in19_d;
    in19s[4] = -(in19_b + in19_d + in19_e + in19_f);
    in19s[5] = -(in19_b + in19_c + in19_d + in19_e + in19_g);
    in19s[6] = in19_a + in19_c + in19_f;
    in19s[7] = in19_d + in19_e + in19_g;
    in19s[8] = -(in19_a + in19_c + in19_d + in19_f);
    in19s[9] = in19_b + in19_e + in19_f;
    in19s[10] = in19_a + in19_f + in19_g;
    in19s[11] = -(in19_a + in19_d + in19_e + in19_f);
    in19s[12] = -(in19_c + in19_e + in19_f);
    in19s[13] = in19_a + in19_c + in19_d + in19_f;
    in19s[14] = -(in19_c + in19_d + in19_e + in19_f + in19_g);
    in19s[15] = -(in19_a + in19_d + in19_g);

    ap_int<32> in21s[16];
    #pragma HLS ARRAY_PARTITION variable=in21s complete dim=0

    in21s[0] = in21_b + in21_d + in21_e + in21_f;
    in21s[1] = -(in21_a + in21_c + in21_d + in21_f);
    in21s[2] = in21_b + in21_e + in21_f;
    in21s[3] = in21_b + in21_c + in21_e + in21_f;
    in21s[4] = -(in21_a + in21_c + in21_d + in21_f);
    in21s[5] = in21_c + in21_d + in21_e + in21_f + in21_g;
    in21s[6] = in21_b + in21_c + in21_d + in21_e + in21_g;
    in21s[7] = -(in21_a + in21_c + in21_d);
    in21s[8] = in21_c + in21_e + in21_f;
    in21s[9] = in21_a + in21_f + in21_g;
    in21s[10] = -(in21_a + in21_c + in21_e + in21_g);
    in21s[11] = in21_d + in21_e + in21_g;
    in21s[12] = in21_a + in21_d + in21_g;
    in21s[13] = -(in21_a + in21_c + in21_f);
    in21s[14] = in21_e;
    in21s[15] = in21_a + in21_d + in21_e + in21_f;

    ap_int<32> in23s[16];
    #pragma HLS ARRAY_PARTITION variable=in23s complete dim=0

    in23s[0] = in23_b + in23_e + in23_f;
    in23s[1] = -(in23_a + in23_c + in23_d);
    in23s[2] = in23_a + in23_d + in23_g;
    in23s[3] = -(in23_e);
    in23s[4] = -(in23_a + in23_f + in23_g);
    in23s[5] = in23_a + in23_c + in23_d + in23_f;
    in23s[6] = -(in23_b + in23_d + in23_e + in23_f);
    in23s[7] = -(in23_c + in23_d + in23_e + in23_f + in23_g);
    in23s[8] = in23_a + in23_c + in23_e + in23_g;
    in23s[9] = -(in23_a + in23_d + in23_e + in23_f);
    in23s[10] = in23_d + in23_e + in23_g;
    in23s[11] = in23_b + in23_c + in23_d + in23_e + in23_g;
    in23s[12] = -(in23_a + in23_c + in23_d + in23_f);
    in23s[13] = in23_b + in23_c + in23_e + in23_f;
    in23s[14] = in23_c + in23_e + in23_f;
    in23s[15] = -(in23_a + in23_c + in23_f);

    ap_int<32> in25s[16];
    #pragma HLS ARRAY_PARTITION variable=in25s complete dim=0

    in25s[0] = in25_c + in25_d + in25_e + in25_f + in25_g;
    in25s[1] = -(in25_a + in25_d + in25_e + in25_f);
    in25s[2] = in25_a + in25_c + in25_d + in25_f;
    in25s[3] = -(in25_b + in25_c + in25_d + in25_e + in25_g);
    in25s[4] = in25_e;
    in25s[5] = in25_b + in25_c + in25_e + in25_f;
    in25s[6] = -(in25_a + in25_c + in25_d);
    in25s[7] = in25_a + in25_c + in25_f;
    in25s[8] = -(in25_b + in25_e + in25_f);
    in25s[9] = -(in25_c + in25_e + in25_f);
    in25s[10] = in25_a + in25_d + in25_g;
    in25s[11] = -(in25_a + in25_c + in25_d + in25_f);
    in25s[12] = in25_a + in25_f + in25_g;
    in25s[13] = -(in25_d + in25_e + in25_g);
    in25s[14] = -(in25_b + in25_d + in25_e + in25_f);
    in25s[15] = in25_a + in25_c + in25_e + in25_g;

    ap_int<32> in27s[16];
    #pragma HLS ARRAY_PARTITION variable=in27s complete dim=0

    in27s[0] = in27_c + in27_e + in27_f;
    in27s[1] = -(in27_b + in27_c + in27_d + in27_e + in27_g);
    in27s[2] = in27_a + in27_c + in27_e + in27_g;
    in27s[3] = -(in27_a + in27_c + in27_d + in27_f);
    in27s[4] = in27_a + in27_d + in27_g;
    in27s[5] = -(in27_b + in27_e + in27_f);
    in27s[6] = -(in27_e);
    in27s[7] = in27_b + in27_d + in27_e + in27_f;
    in27s[8] = -(in27_a + in27_d + in27_e + in27_f);
    in27s[9] = in27_a + in27_c + in27_d + in27_f;
    in27s[10] = -(in27_a + in27_c + in27_f);
    in27s[11] = in27_b + in27_c + in27_e + in27_f;
    in27s[12] = -(in27_d + in27_e + in27_g);
    in27s[13] = -(in27_c + in27_d + in27_e + in27_f + in27_g);
    in27s[14] = in27_a + in27_f + in27_g;
    in27s[15] = -(in27_a + in27_c + in27_d);

    ap_int<32> in29s[16];
    #pragma HLS ARRAY_PARTITION variable=in29s complete dim=0

    in29s[0] = in29_d + in29_e + in29_g;
    in29s[1] = -(in29_b + in29_e + in29_f);
    in29s[2] = in29_b + in29_c + in29_d + in29_e + in29_g;
    in29s[3] = -(in29_a + in29_d + in29_e + in29_f);
    in29s[4] = in29_a + in29_c + in29_d;
    in29s[5] = -(in29_a + in29_c + in29_d + in29_f);
    in29s[6] = in29_a + in29_c + in29_e + in29_g;
    in29s[7] = -(in29_a + in29_d + in29_g);
    in29s[8] = in29_b + in29_c + in29_e + in29_f;
    in29s[9] = -(in29_c + in29_d + in29_e + in29_f + in29_g);
    in29s[10] = in29_e;
    in29s[11] = in29_c + in29_e + in29_f;
    in29s[12] = -(in29_b + in29_d + in29_e + in29_f);
    in29s[13] = in29_a + in29_f + in29_g;
    in29s[14] = -(in29_a + in29_c + in29_f);
    in29s[15] = in29_a + in29_c + in29_d + in29_f;

    ap_int<32> in31s[16];
    #pragma HLS ARRAY_PARTITION variable=in31s complete dim=0

    in31s[0] = in31_e;
    in31s[1] = -(in31_d + in31_e + in31_g);
    in31s[2] = in31_c + in31_e + in31_f;
    in31s[3] = -(in31_c + in31_d + in31_e + in31_f + in31_g);
    in31s[4] = in31_b + in31_e + in31_f;
    in31s[5] = -(in31_b + in31_d + in31_e + in31_f);
    in31s[6] = in31_b + in31_c + in31_e + in31_f;
    in31s[7] = -(in31_b + in31_c + in31_d + in31_e + in31_g);
    in31s[8] = in31_a + in31_f + in31_g;
    in31s[9] = -(in31_a + in31_d + in31_g);
    in31s[10] = in31_a + in31_d + in31_e + in31_f;
    in31s[11] = -(in31_a + in31_c + in31_f);
    in31s[12] = in31_a + in31_c + in31_e + in31_g;
    in31s[13] = -(in31_a + in31_c + in31_d);
    in31s[14] = in31_a + in31_c + in31_d + in31_f;
    in31s[15] = -(in31_a + in31_c + in31_d + in31_f);

    for(int i=0; i<16; i++){
        #pragma HLS UNROLL
        odds[i] = in1s[i] + in3s[i] + in5s[i] + in7s[i] + in9s[i] + in11s[i] + in13s[i] + in15s[i] +
            in17s[i] + in19s[i] + in21s[i] + in23s[i] + in25s[i] + in27s[i] + in29s[i] + in31s[i];
    }

    #else

    for(int i=0; i<16; i++){
        #pragma HLS UNROLL
        odds[i] = idct32[1][i]*in[1] + idct32[3][i]*in[3] + idct32[5][i]*in[5] + idct32[7][i]*in[7] + idct32[9][i]*in[9] + idct32[11][i]*in[11] + idct32[13][i]*in[13] + idct32[15][i]*in[15] +
            idct32[17][i]*in[17] + idct32[19][i]*in[19] + idct32[21][i]*in[21] + idct32[23][i]*in[23] + idct32[25][i]*in[25] + idct32[27][i]*in[27] + idct32[29][i]*in[29] + idct32[31][i]*in[31];
    }

    #endif

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[2] + odds[2];
    out[3] = evens[3] + odds[3];
    out[4] = evens[4] + odds[4];
    out[5] = evens[5] + odds[5];
    out[6] = evens[6] + odds[6];
    out[7] = evens[7] + odds[7];
    out[8] = evens[8] + odds[8];
    out[9] = evens[9] + odds[9];
    out[10] = evens[10] + odds[10];
    out[11] = evens[11] + odds[11];
    out[12] = evens[12] + odds[12];
    out[13] = evens[13] + odds[13];
    out[14] = evens[14] + odds[14];
    out[15] = evens[15] + odds[15];
    out[16] = evens[15] - odds[15];
    out[17] = evens[14] - odds[14];
    out[18] = evens[13] - odds[13];
    out[19] = evens[12] - odds[12];
    out[20] = evens[11] - odds[11];
    out[21] = evens[10] - odds[10];
    out[22] = evens[9] - odds[9];
    out[23] = evens[8] - odds[8];
    out[24] = evens[7] - odds[7];
    out[25] = evens[6] - odds[6];
    out[26] = evens[5] - odds[5];
    out[27] = evens[4] - odds[4];
    out[28] = evens[3] - odds[3];
    out[29] = evens[2] - odds[2];
    out[30] = evens[1] - odds[1];
    out[31] = evens[0] - odds[0];
}

void IDCT2B64(IN_TYPE in[64], OUT_TYPE out[64]){
    #pragma HLS inline off

    ap_int<32> evens[32];
    ap_int<32> odds[32];
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0

    IN_TYPE inputs[32];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0

    inputs[0] = in[0];
    inputs[16] = in[32];
    inputs[8] = in[16];
    inputs[24] = in[48];
    inputs[4] = in[8];
    inputs[12] = in[24];
    inputs[20] = in[40];
    inputs[28] = in[56];
    inputs[2] = in[4];
    inputs[6] = in[12];
    inputs[10] = in[20];
    inputs[14] = in[28];
    inputs[18] = in[36];
    inputs[22] = in[44];
    inputs[26] = in[52];
    inputs[30] = in[60];

    inputs[1] = in[2];
    inputs[3] = in[6];
    inputs[5] = in[10];
    inputs[7] = in[14];
    inputs[9] = in[18];
    inputs[11] = in[22];
    inputs[13] = in[26];
    inputs[15] = in[30];
    inputs[17] = in[34];
    inputs[19] = in[38];
    inputs[21] = in[42];
    inputs[23] = in[46];
    inputs[25] = in[50];
    inputs[27] = in[54];
    inputs[29] = in[58];
    inputs[31] = in[62];

    IDCT2B32(inputs, evens);

    #ifdef USE_SHIFT_ADD_64

    ap_int<32> in1_a = in[1] << 6;
    ap_int<32> in1_b = in[1] << 5;
    ap_int<32> in1_c = in[1] << 4;
    ap_int<32> in1_d = in[1] << 3;
    ap_int<32> in1_e = in[1] << 2;
    ap_int<32> in1_f = in[1] << 1;
    ap_int<32> in1_g = in[1];

    ap_int<32> in3_a = in[3] << 6;
    ap_int<32> in3_b = in[3] << 5;
    ap_int<32> in3_c = in[3] << 4;
    ap_int<32> in3_d = in[3] << 3;
    ap_int<32> in3_e = in[3] << 2;
    ap_int<32> in3_f = in[3] << 1;
    ap_int<32> in3_g = in[3];

    ap_int<32> in5_a = in[5] << 6;
    ap_int<32> in5_b = in[5] << 5;
    ap_int<32> in5_c = in[5] << 4;
    ap_int<32> in5_d = in[5] << 3;
    ap_int<32> in5_e = in[5] << 2;
    ap_int<32> in5_f = in[5] << 1;
    ap_int<32> in5_g = in[5];

    ap_int<32> in7_a = in[7] << 6;
    ap_int<32> in7_b = in[7] << 5;
    ap_int<32> in7_c = in[7] << 4;
    ap_int<32> in7_d = in[7] << 3;
    ap_int<32> in7_e = in[7] << 2;
    ap_int<32> in7_f = in[7] << 1;
    ap_int<32> in7_g = in[7];

    ap_int<32> in9_a = in[9] << 6;
    ap_int<32> in9_b = in[9] << 5;
    ap_int<32> in9_c = in[9] << 4;
    ap_int<32> in9_d = in[9] << 3;
    ap_int<32> in9_e = in[9] << 2;
    ap_int<32> in9_f = in[9] << 1;
    ap_int<32> in9_g = in[9];

    ap_int<32> in11_a = in[11] << 6;
    ap_int<32> in11_b = in[11] << 5;
    ap_int<32> in11_c = in[11] << 4;
    ap_int<32> in11_d = in[11] << 3;
    ap_int<32> in11_e = in[11] << 2;
    ap_int<32> in11_f = in[11] << 1;
    ap_int<32> in11_g = in[11];

    ap_int<32> in13_a = in[13] << 6;
    ap_int<32> in13_b = in[13] << 5;
    ap_int<32> in13_c = in[13] << 4;
    ap_int<32> in13_d = in[13] << 3;
    ap_int<32> in13_e = in[13] << 2;
    ap_int<32> in13_f = in[13] << 1;
    ap_int<32> in13_g = in[13];

    ap_int<32> in15_a = in[15] << 6;
    ap_int<32> in15_b = in[15] << 5;
    ap_int<32> in15_c = in[15] << 4;
    ap_int<32> in15_d = in[15] << 3;
    ap_int<32> in15_e = in[15] << 2;
    ap_int<32> in15_f = in[15] << 1;
    ap_int<32> in15_g = in[15];

    ap_int<32> in17_a = in[17] << 6;
    ap_int<32> in17_b = in[17] << 5;
    ap_int<32> in17_c = in[17] << 4;
    ap_int<32> in17_d = in[17] << 3;
    ap_int<32> in17_e = in[17] << 2;
    ap_int<32> in17_f = in[17] << 1;
    ap_int<32> in17_g = in[17];

    ap_int<32> in19_a = in[19] << 6;
    ap_int<32> in19_b = in[19] << 5;
    ap_int<32> in19_c = in[19] << 4;
    ap_int<32> in19_d = in[19] << 3;
    ap_int<32> in19_e = in[19] << 2;
    ap_int<32> in19_f = in[19] << 1;
    ap_int<32> in19_g = in[19];

    ap_int<32> in21_a = in[21] << 6;
    ap_int<32> in21_b = in[21] << 5;
    ap_int<32> in21_c = in[21] << 4;
    ap_int<32> in21_d = in[21] << 3;
    ap_int<32> in21_e = in[21] << 2;
    ap_int<32> in21_f = in[21] << 1;
    ap_int<32> in21_g = in[21];

    ap_int<32> in23_a = in[23] << 6;
    ap_int<32> in23_b = in[23] << 5;
    ap_int<32> in23_c = in[23] << 4;
    ap_int<32> in23_d = in[23] << 3;
    ap_int<32> in23_e = in[23] << 2;
    ap_int<32> in23_f = in[23] << 1;
    ap_int<32> in23_g = in[23];

    ap_int<32> in25_a = in[25] << 6;
    ap_int<32> in25_b = in[25] << 5;
    ap_int<32> in25_c = in[25] << 4;
    ap_int<32> in25_d = in[25] << 3;
    ap_int<32> in25_e = in[25] << 2;
    ap_int<32> in25_f = in[25] << 1;
    ap_int<32> in25_g = in[25];

    ap_int<32> in27_a = in[27] << 6;
    ap_int<32> in27_b = in[27] << 5;
    ap_int<32> in27_c = in[27] << 4;
    ap_int<32> in27_d = in[27] << 3;
    ap_int<32> in27_e = in[27] << 2;
    ap_int<32> in27_f = in[27] << 1;
    ap_int<32> in27_g = in[27];

    ap_int<32> in29_a = in[29] << 6;
    ap_int<32> in29_b = in[29] << 5;
    ap_int<32> in29_c = in[29] << 4;
    ap_int<32> in29_d = in[29] << 3;
    ap_int<32> in29_e = in[29] << 2;
    ap_int<32> in29_f = in[29] << 1;
    ap_int<32> in29_g = in[29];

    ap_int<32> in31_a = in[31] << 6;
    ap_int<32> in31_b = in[31] << 5;
    ap_int<32> in31_c = in[31] << 4;
    ap_int<32> in31_d = in[31] << 3;
    ap_int<32> in31_e = in[31] << 2;
    ap_int<32> in31_f = in[31] << 1;
    ap_int<32> in31_g = in[31];

    ap_int<32> in1_a_2 = in[33] << 6;
    ap_int<32> in1_b_2 = in[33] << 5;
    ap_int<32> in1_c_2 = in[33] << 4;
    ap_int<32> in1_d_2 = in[33] << 3;
    ap_int<32> in1_e_2 = in[33] << 2;
    ap_int<32> in1_f_2 = in[33] << 1;
    ap_int<32> in1_g_2 = in[33];

    ap_int<32> in3_a_2 = in[35] << 6;
    ap_int<32> in3_b_2 = in[35] << 5;
    ap_int<32> in3_c_2 = in[35] << 4;
    ap_int<32> in3_d_2 = in[35] << 3;
    ap_int<32> in3_e_2 = in[35] << 2;
    ap_int<32> in3_f_2 = in[35] << 1;
    ap_int<32> in3_g_2 = in[35];

    ap_int<32> in5_a_2 = in[37] << 6;
    ap_int<32> in5_b_2 = in[37] << 5;
    ap_int<32> in5_c_2 = in[37] << 4;
    ap_int<32> in5_d_2 = in[37] << 3;
    ap_int<32> in5_e_2 = in[37] << 2;
    ap_int<32> in5_f_2 = in[37] << 1;
    ap_int<32> in5_g_2 = in[37];

    ap_int<32> in7_a_2 = in[39] << 6;
    ap_int<32> in7_b_2 = in[39] << 5;
    ap_int<32> in7_c_2 = in[39] << 4;
    ap_int<32> in7_d_2 = in[39] << 3;
    ap_int<32> in7_e_2 = in[39] << 2;
    ap_int<32> in7_f_2 = in[39] << 1;
    ap_int<32> in7_g_2 = in[39];

    ap_int<32> in9_a_2 = in[41] << 6;
    ap_int<32> in9_b_2 = in[41] << 5;
    ap_int<32> in9_c_2 = in[41] << 4;
    ap_int<32> in9_d_2 = in[41] << 3;
    ap_int<32> in9_e_2 = in[41] << 2;
    ap_int<32> in9_f_2 = in[41] << 1;
    ap_int<32> in9_g_2 = in[41];

    ap_int<32> in11_a_2 = in[43] << 6;
    ap_int<32> in11_b_2 = in[43] << 5;
    ap_int<32> in11_c_2 = in[43] << 4;
    ap_int<32> in11_d_2 = in[43] << 3;
    ap_int<32> in11_e_2 = in[43] << 2;
    ap_int<32> in11_f_2 = in[43] << 1;
    ap_int<32> in11_g_2 = in[43];

    ap_int<32> in13_a_2 = in[45] << 6;
    ap_int<32> in13_b_2 = in[45] << 5;
    ap_int<32> in13_c_2 = in[45] << 4;
    ap_int<32> in13_d_2 = in[45] << 3;
    ap_int<32> in13_e_2 = in[45] << 2;
    ap_int<32> in13_f_2 = in[45] << 1;
    ap_int<32> in13_g_2 = in[45];

    ap_int<32> in15_a_2 = in[47] << 6;
    ap_int<32> in15_b_2 = in[47] << 5;
    ap_int<32> in15_c_2 = in[47] << 4;
    ap_int<32> in15_d_2 = in[47] << 3;
    ap_int<32> in15_e_2 = in[47] << 2;
    ap_int<32> in15_f_2 = in[47] << 1;
    ap_int<32> in15_g_2 = in[47];

    ap_int<32> in17_a_2 = in[49] << 6;
    ap_int<32> in17_b_2 = in[49] << 5;
    ap_int<32> in17_c_2 = in[49] << 4;
    ap_int<32> in17_d_2 = in[49] << 3;
    ap_int<32> in17_e_2 = in[49] << 2;
    ap_int<32> in17_f_2 = in[49] << 1;
    ap_int<32> in17_g_2 = in[49];

    ap_int<32> in19_a_2 = in[51] << 6;
    ap_int<32> in19_b_2 = in[51] << 5;
    ap_int<32> in19_c_2 = in[51] << 4;
    ap_int<32> in19_d_2 = in[51] << 3;
    ap_int<32> in19_e_2 = in[51] << 2;
    ap_int<32> in19_f_2 = in[51] << 1;
    ap_int<32> in19_g_2 = in[51];

    ap_int<32> in21_a_2 = in[53] << 6;
    ap_int<32> in21_b_2 = in[53] << 5;
    ap_int<32> in21_c_2 = in[53] << 4;
    ap_int<32> in21_d_2 = in[53] << 3;
    ap_int<32> in21_e_2 = in[53] << 2;
    ap_int<32> in21_f_2 = in[53] << 1;
    ap_int<32> in21_g_2 = in[53];

    ap_int<32> in23_a_2 = in[55] << 6;
    ap_int<32> in23_b_2 = in[55] << 5;
    ap_int<32> in23_c_2 = in[55] << 4;
    ap_int<32> in23_d_2 = in[55] << 3;
    ap_int<32> in23_e_2 = in[55] << 2;
    ap_int<32> in23_f_2 = in[55] << 1;
    ap_int<32> in23_g_2 = in[55];

    ap_int<32> in25_a_2 = in[57] << 6;
    ap_int<32> in25_b_2 = in[57] << 5;
    ap_int<32> in25_c_2 = in[57] << 4;
    ap_int<32> in25_d_2 = in[57] << 3;
    ap_int<32> in25_e_2 = in[57] << 2;
    ap_int<32> in25_f_2 = in[57] << 1;
    ap_int<32> in25_g_2 = in[57];

    ap_int<32> in27_a_2 = in[59] << 6;
    ap_int<32> in27_b_2 = in[59] << 5;
    ap_int<32> in27_c_2 = in[59] << 4;
    ap_int<32> in27_d_2 = in[59] << 3;
    ap_int<32> in27_e_2 = in[59] << 2;
    ap_int<32> in27_f_2 = in[59] << 1;
    ap_int<32> in27_g_2 = in[59];

    ap_int<32> in29_a_2 = in[61] << 6;
    ap_int<32> in29_b_2 = in[61] << 5;
    ap_int<32> in29_c_2 = in[61] << 4;
    ap_int<32> in29_d_2 = in[61] << 3;
    ap_int<32> in29_e_2 = in[61] << 2;
    ap_int<32> in29_f_2 = in[61] << 1;
    ap_int<32> in29_g_2 = in[61];

    ap_int<32> in31_a_2 = in[63] << 6;
    ap_int<32> in31_b_2 = in[63] << 5;
    ap_int<32> in31_c_2 = in[63] << 4;
    ap_int<32> in31_d_2 = in[63] << 3;
    ap_int<32> in31_e_2 = in[63] << 2;
    ap_int<32> in31_f_2 = in[63] << 1;
    ap_int<32> in31_g_2 = in[63];

    ap_int<32> in1s[32];
    #pragma HLS ARRAY_PARTITION variable=in1s complete dim=0

    in1s[0] = in1_a + in1_c + in1_d + in1_f + in1_g; // *91
    in1s[1] = in1_a + in1_c + in1_d + in1_f; // *90 
    in1s[2] = in1s[1];
    in1s[3] = in1s[1];
    in1s[4] = in1_a + in1_c + in1_d; // *88
    in1s[5] = in1_a + in1_c + in1_e + in1_f + in1_g; // *87
    in1s[6] = in1_a + in1_c + in1_e + in1_f; // *86
    in1s[7] = in1_a + in1_c + in1_e; // *84
    in1s[8] = in1_a + in1_c + in1_f + in1_g; // *83
    in1s[9] = in1_a + in1_c + in1_g; // *81
    in1s[10] = in1_a + in1_d + in1_e + in1_f + in1_g; // *79
    in1s[11] = in1_a + in1_d + in1_e + in1_g; // *77
    in1s[12] = in1_a + in1_d + in1_g; // *73
    in1s[13] = in1_a + in1_e + in1_f + in1_g; // *71
    in1s[14] = in1_a + in1_e + in1_g; // *69
    in1s[15] = in1_a + in1_g; // *65
    in1s[16] = in1_b + in1_c + in1_d + in1_e + in1_f; // *62
    in1s[17] = in1_b + in1_c + in1_d + in1_f + in1_g; // *59
    in1s[18] = in1_b + in1_c + in1_d; // *56
    in1s[19] = in1_b + in1_c + in1_e; // *52
    in1s[20] = in1_b + in1_c; // *48
    in1s[21] = in1_b + in1_d + in1_e; // *44
    in1s[22] = in1_b + in1_d + in1_g; // *41
    in1s[23] = in1_b + in1_e + in1_g; // *37
    in1s[24] = in1_b + in1_g; // *33
    in1s[25] = in1_c + in1_d + in1_e; // *28
    in1s[26] = in1_c + in1_d; // *24
    in1s[27] = in1_c + in1_e; // *20
    in1s[28] = in1_d + in1_e + in1_f + in1_g; // *15
    in1s[29] = in1_d + in1_f + in1_g; // *11
    in1s[30] = in1_e + in1_f + in1_g; // *7
    in1s[31] = in1_f; // *2

    ap_int<32> in3s[32];
    #pragma HLS ARRAY_PARTITION variable=in3s complete dim=0

    in3s[0 ] =  in3_a + in3_c + in3_d + in3_f;
    in3s[1 ] =  in3_a + in3_c + in3_d;
    in3s[2 ] =  in3_a + in3_c + in3_e;
    in3s[3 ] =  in3_a + in3_d + in3_e + in3_f + in3_g;
    in3s[4 ] =  in3_a + in3_e + in3_f + in3_g;
    in3s[5 ] =  in3_b + in3_c + in3_d + in3_e + in3_f;
    in3s[6 ] =  in3_b + in3_c + in3_e;
    in3s[7 ] =  in3_b + in3_d + in3_g;
    in3s[8 ] =  in3_c + in3_d + in3_e;
    in3s[9 ] =  in3_d + in3_e + in3_f + in3_g;
    in3s[10] =  in3_f;
    in3s[11] =  -(in3_d + in3_f + in3_g);
    in3s[12] =  -(in3_c + in3_d);
    in3s[13] =  -(in3_b + in3_e + in3_g);
    in3s[14] =  -(in3_b + in3_c);
    in3s[15] =  -(in3_b + in3_c + in3_d + in3_f + in3_g);
    in3s[16] =  -(in3_a + in3_e + in3_g);
    in3s[17] =  -(in3_a + in3_d + in3_e + in3_g);
    in3s[18] =  -(in3_a + in3_c + in3_f + in3_g);
    in3s[19] =  -(in3_a + in3_c + in3_e + in3_f + in3_g);
    in3s[20] =  -(in3_a + in3_c + in3_d + in3_f);
    in3s[21] =  -(in3_a + in3_c + in3_d + in3_f + in3_g);
    in3s[22] =  -(in3_a + in3_c + in3_d + in3_f);
    in3s[23] =  -(in3_a + in3_c + in3_e + in3_f);
    in3s[24] =  -(in3_a + in3_c + in3_g);
    in3s[25] =  -(in3_a + in3_d + in3_g);
    in3s[26] =  -(in3_a + in3_g);
    in3s[27] =  -(in3_b + in3_c + in3_d);
    in3s[28] =  -(in3_b + in3_d + in3_e);
    in3s[29] =  -(in3_b + in3_g);
    in3s[30] =  -(in3_c + in3_e);
    in3s[31] =  -(in3_e + in3_f + in3_g);

    ap_int<32> in5s[32];
    #pragma HLS ARRAY_PARTITION variable=in5s complete dim=0

    in5s[0 ] =  in5_a + in5_c + in5_d + in5_f;
    in5s[1 ] =  in5_a + in5_c + in5_e;
    in5s[2 ] =  in5_a + in5_d + in5_g;
    in5s[3 ] =  in5_b + in5_c + in5_d + in5_f + in5_g;
    in5s[4 ] =  in5_b + in5_d + in5_g;
    in5s[5 ] =  in5_c + in5_e;
    in5s[6 ] =  -(in5_f);
    in5s[7 ] =  -(in5_c + in5_d);
    in5s[8 ] =  -(in5_b + in5_d + in5_e);
    in5s[9 ] =  -(in5_b + in5_c + in5_d + in5_e + in5_f);
    in5s[10] =  -(in5_a + in5_d + in5_e + in5_g);
    in5s[11] =  -(in5_a + in5_c + in5_e + in5_f);
    in5s[12] =  -(in5_a + in5_c + in5_d + in5_f);
    in5s[13] =  -(in5_a + in5_c + in5_d + in5_f);
    in5s[14] =  -(in5_a + in5_c + in5_f + in5_g);
    in5s[15] =  -(in5_a + in5_e + in5_f + in5_g);
    in5s[16] =  -(in5_b + in5_c + in5_d);
    in5s[17] =  -(in5_b + in5_e + in5_g);
    in5s[18] =  -(in5_d + in5_e + in5_f + in5_g);
    in5s[19] =  in5_e + in5_f + in5_g;
    in5s[20] =  in5_c + in5_d + in5_e;
    in5s[21] =  in5_b + in5_c;
    in5s[22] =  in5_a + in5_g;
    in5s[23] =  in5_a + in5_d + in5_e + in5_f + in5_g;
    in5s[24] =  in5_a + in5_c + in5_e + in5_f + in5_g;
    in5s[25] =  in5_a + in5_c + in5_d + in5_f + in5_g;
    in5s[26] =  in5_a + in5_c + in5_d;
    in5s[27] =  in5_a + in5_c + in5_g;
    in5s[28] =  in5_a + in5_e + in5_g;
    in5s[29] =  in5_b + in5_c + in5_e;
    in5s[30] =  in5_b + in5_g;
    in5s[31] =  in5_d + in5_f + in5_g;

    ap_int<32> in7s[32];
    #pragma HLS ARRAY_PARTITION variable=in7s complete dim=0

    in7s[0 ] =  in7_a + in7_c + in7_d + in7_f;
    in7s[1 ] =  in7_a + in7_d + in7_e + in7_f + in7_g;
    in7s[2 ] =  in7_b + in7_c + in7_d + in7_f + in7_g;
    in7s[3 ] =  in7_b + in7_g;
    in7s[4 ] =  in7_f;
    in7s[5 ] =  -(in7_c + in7_d + in7_e);
    in7s[6 ] =  -(in7_b + in7_c + in7_d);
    in7s[7 ] =  -(in7_a + in7_d + in7_e + in7_g);
    in7s[8 ] =  -(in7_a + in7_c + in7_d);
    in7s[9 ] =  -(in7_a + in7_c + in7_d + in7_f);
    in7s[10] =  -(in7_a + in7_c + in7_g);
    in7s[11] =  -(in7_b + in7_c + in7_d + in7_e + in7_f);
    in7s[12] =  -(in7_b + in7_e + in7_g);
    in7s[13] =  -(in7_e + in7_f + in7_g);
    in7s[14] =  in7_c + in7_d;
    in7s[15] =  in7_b + in7_c + in7_e;
    in7s[16] =  in7_a + in7_d + in7_g;
    in7s[17] =  in7_a + in7_c + in7_e + in7_f + in7_g;
    in7s[18] =  in7_a + in7_c + in7_d + in7_f;
    in7s[19] =  in7_a + in7_c + in7_f + in7_g;
    in7s[20] =  in7_a + in7_g;
    in7s[21] =  in7_b + in7_d + in7_g;
    in7s[22] =  in7_d + in7_f + in7_g;
    in7s[23] =  -(in7_c + in7_e);
    in7s[24] =  -(in7_b + in7_c);
    in7s[25] =  -(in7_a + in7_e + in7_f + in7_g);
    in7s[26] =  -(in7_a + in7_c + in7_e + in7_f);
    in7s[27] =  -(in7_a + in7_c + in7_d + in7_f + in7_g);
    in7s[28] =  -(in7_a + in7_c + in7_e);
    in7s[29] =  -(in7_a + in7_e + in7_g);
    in7s[30] =  -(in7_b + in7_d + in7_e);
    in7s[31] =  -(in7_d + in7_e + in7_f + in7_g);

    ap_int<32> in9s[32];
    #pragma HLS ARRAY_PARTITION variable=in9s complete dim=0

    in9s[0 ] =  in9_a + in9_c + in9_d;
    in9s[1 ] =  in9_a + in9_e + in9_f + in9_g;
    in9s[2 ] =  in9_b + in9_d + in9_g;
    in9s[3 ] =  in9_f;
    in9s[4 ] =  -(in9_b + in9_e + in9_g);
    in9s[5 ] =  -(in9_a + in9_e + in9_g);
    in9s[6 ] =  -(in9_a + in9_c + in9_e + in9_f + in9_g);
    in9s[7 ] =  -(in9_a + in9_c + in9_d + in9_f);
    in9s[8 ] =  -(in9_a + in9_d + in9_g);
    in9s[9 ] =  -(in9_b + in9_d + in9_e);
    in9s[10] =  -(in9_e + in9_f + in9_g);
    in9s[11] =  in9_b + in9_g;
    in9s[12] =  in9_a + in9_g;
    in9s[13] =  in9_a + in9_c + in9_e + in9_f;
    in9s[14] =  in9_a + in9_c + in9_d + in9_f;
    in9s[15] =  in9_a + in9_d + in9_e + in9_g;
    in9s[16] =  in9_b + in9_c;
    in9s[17] =  in9_d + in9_f + in9_g;
    in9s[18] =  -(in9_c + in9_d + in9_e);
    in9s[19] =  -(in9_b + in9_c + in9_d + in9_e + in9_f);
    in9s[20] =  -(in9_a + in9_c + in9_e);
    in9s[21] =  -(in9_a + in9_c + in9_d + in9_f);
    in9s[22] =  -(in9_a + in9_d + in9_e + in9_f + in9_g);
    in9s[23] =  -(in9_b + in9_c + in9_e);
    in9s[24] =  -(in9_d + in9_e + in9_f + in9_g);
    in9s[25] =  in9_c + in9_d;
    in9s[26] =  in9_b + in9_c + in9_d + in9_f + in9_g;
    in9s[27] =  in9_a + in9_c + in9_f + in9_g;
    in9s[28] =  in9_a + in9_c + in9_d + in9_f + in9_g;
    in9s[29] =  in9_a + in9_c + in9_g;
    in9s[30] =  in9_b + in9_c + in9_d;
    in9s[31] =  in9_c + in9_e;

    ap_int<32> in11s[32];
    #pragma HLS ARRAY_PARTITION variable=in11s complete dim=0

    in11s[0 ] =  in11_a + in11_c + in11_e + in11_f + in11_g;
    in11s[1 ] =  in11_b + in11_c + in11_d + in11_e + in11_f;
    in11s[2 ] =  in11_c + in11_e;
    in11s[3 ] =  -(in11_c + in11_d + in11_e);
    in11s[4 ] =  -(in11_a + in11_e + in11_g);
    in11s[5 ] =  -(in11_a + in11_c + in11_d + in11_f);
    in11s[6 ] =  -(in11_a + in11_c + in11_e);
    in11s[7 ] =  -(in11_b + in11_c + in11_d);
    in11s[8 ] =  -(in11_d + in11_f + in11_g);
    in11s[9 ] =  in11_b + in11_e + in11_g;
    in11s[10] =  in11_a + in11_d + in11_g;
    in11s[11] =  in11_a + in11_c + in11_d + in11_f;
    in11s[12] =  in11_a + in11_c + in11_g;
    in11s[13] =  in11_b + in11_c;
    in11s[14] =  in11_f;
    in11s[15] =  -(in11_b + in11_d + in11_e);
    in11s[16] =  -(in11_a + in11_d + in11_e + in11_f + in11_g);
    in11s[17] =  -(in11_a + in11_c + in11_d + in11_f + in11_g);
    in11s[18] =  -(in11_a + in11_d + in11_e + in11_g);
    in11s[19] =  -(in11_b + in11_d + in11_g);
    in11s[20] =  in11_e + in11_f + in11_g;
    in11s[21] =  in11_b + in11_c + in11_e;
    in11s[22] =  in11_a + in11_c + in11_f + in11_g;
    in11s[23] =  in11_a + in11_c + in11_d + in11_f;
    in11s[24] =  in11_a + in11_e + in11_f + in11_g;
    in11s[25] =  in11_b + in11_g;
    in11s[26] =  -(in11_d + in11_e + in11_f + in11_g);
    in11s[27] =  -(in11_b + in11_c + in11_d + in11_f + in11_g);
    in11s[28] =  -(in11_a + in11_c + in11_e + in11_f);
    in11s[29] =  -(in11_a + in11_c + in11_d);
    in11s[30] =  -(in11_a + in11_g);
    in11s[31] =  -(in11_c + in11_d);

    ap_int<32> in13s[32];
    #pragma HLS ARRAY_PARTITION variable=in13s complete dim=0

    in13s[0 ] =  in13_a + in13_c + in13_e + in13_f;
    in13s[1 ] =  in13_b + in13_c + in13_e;
    in13s[2 ] =  -(in13_f);
    in13s[3 ] =  -(in13_b + in13_c + in13_d);
    in13s[4 ] =  -(in13_a + in13_c + in13_e + in13_f + in13_g);
    in13s[5 ] =  -(in13_a + in13_c + in13_e);
    in13s[6 ] =  -(in13_b + in13_c);
    in13s[7 ] =  in13_e + in13_f + in13_g;
    in13s[8 ] =  in13_b + in13_c + in13_d + in13_f + in13_g;
    in13s[9 ] =  in13_a + in13_c + in13_d;
    in13s[10] =  in13_a + in13_c + in13_f + in13_g;
    in13s[11] =  in13_b + in13_d + in13_e;
    in13s[12] =  -(in13_d + in13_f + in13_g);
    in13s[13] =  -(in13_b + in13_c + in13_d + in13_e + in13_f);
    in13s[14] =  -(in13_a + in13_c + in13_d + in13_f);
    in13s[15] =  -(in13_a + in13_c + in13_g);
    in13s[16] =  -(in13_b + in13_d + in13_g);
    in13s[17] =  in13_d + in13_e + in13_f + in13_g;
    in13s[18] =  in13_a + in13_g;
    in13s[19] =  in13_a + in13_c + in13_d + in13_f;
    in13s[20] =  in13_a + in13_d + in13_e + in13_f + in13_g;
    in13s[21] =  in13_b + in13_e + in13_g;
    in13s[22] =  -(in13_c + in13_e);
    in13s[23] =  -(in13_a + in13_e + in13_g);
    in13s[24] =  -(in13_a + in13_c + in13_d + in13_f);
    in13s[25] =  -(in13_a + in13_d + in13_e + in13_g);
    in13s[26] =  -(in13_b + in13_g);
    in13s[27] =  in13_c + in13_d;
    in13s[28] =  in13_a + in13_e + in13_f + in13_g;
    in13s[29] =  in13_a + in13_c + in13_d + in13_f + in13_g;
    in13s[30] =  in13_a + in13_d + in13_g;
    in13s[31] =  in13_c + in13_d + in13_e;

    ap_int<32> in15s[32];
    #pragma HLS ARRAY_PARTITION variable=in15s complete dim=0

    in15s[0 ] =  in15_a + in15_c + in15_e;
    in15s[1 ] =  in15_b + in15_d + in15_g;
    in15s[2 ] =  -(in15_c + in15_d);
    in15s[3 ] =  -(in15_a + in15_d + in15_e + in15_g);
    in15s[4 ] =  -(in15_a + in15_c + in15_d + in15_f);
    in15s[5 ] =  -(in15_b + in15_c + in15_d);
    in15s[6 ] =  in15_e + in15_f + in15_g;
    in15s[7 ] =  in15_a + in15_g;
    in15s[8 ] =  in15_a + in15_c + in15_d + in15_f + in15_g;
    in15s[9 ] =  in15_a + in15_e + in15_g;
    in15s[10] =  in15_d + in15_f + in15_g;
    in15s[11] =  -(in15_b + in15_c + in15_e);
    in15s[12] =  -(in15_a + in15_c + in15_d);
    in15s[13] =  -(in15_a + in15_d + in15_e + in15_f + in15_g);
    in15s[14] =  -(in15_c + in15_d + in15_e);
    in15s[15] =  in15_b + in15_e + in15_g;
    in15s[16] =  in15_a + in15_c + in15_f + in15_g;
    in15s[17] =  in15_a + in15_c + in15_e + in15_f;
    in15s[18] =  in15_b + in15_d + in15_e;
    in15s[19] =  -(in15_c + in15_e);
    in15s[20] =  -(in15_a + in15_d + in15_g);
    in15s[21] =  -(in15_a + in15_c + in15_d + in15_f);
    in15s[22] =  -(in15_b + in15_c + in15_d + in15_f + in15_g);
    in15s[23] =  in15_f;
    in15s[24] =  in15_b + in15_c + in15_d + in15_e + in15_f;
    in15s[25] =  in15_a + in15_c + in15_d + in15_f;
    in15s[26] =  in15_a + in15_e + in15_f + in15_g;
    in15s[27] =  in15_d + in15_e + in15_f + in15_g;
    in15s[28] =  -(in15_b + in15_c);
    in15s[29] =  -(in15_a + in15_c + in15_e + in15_f + in15_g);
    in15s[30] =  -(in15_a + in15_c + in15_g);
    in15s[31] =  -(in15_b + in15_g);

    ap_int<32> in17s[32];
    #pragma HLS ARRAY_PARTITION variable=in17s complete dim=0

    in17s[0 ] =  in17_a + in17_c + in17_f + in17_g;
    in17s[1 ] =  in17_c + in17_d + in17_e;
    in17s[2 ] =  -(in17_b + in17_d + in17_e);
    in17s[3 ] =  -(in17_a + in17_c + in17_d);
    in17s[4 ] =  -(in17_a + in17_d + in17_g);
    in17s[5 ] =  -(in17_d + in17_f + in17_g);
    in17s[6 ] =  in17_b + in17_c + in17_d + in17_f + in17_g;
    in17s[7 ] =  in17_a + in17_c + in17_d + in17_f + in17_g;
    in17s[8 ] =  in17_b + in17_c + in17_d + in17_e + in17_f;
    in17s[9 ] =  -(in17_e + in17_f + in17_g);
    in17s[10] =  -(in17_a + in17_e + in17_f + in17_g);
    in17s[11] =  -(in17_a + in17_c + in17_d + in17_f);
    in17s[12] =  -(in17_b + in17_c);
    in17s[13] =  in17_c + in17_d;
    in17s[14] =  in17_a + in17_c + in17_g;
    in17s[15] =  in17_a + in17_c + in17_e;
    in17s[16] =  in17_b + in17_g;
    in17s[17] =  -(in17_b + in17_d + in17_g);
    in17s[18] =  -(in17_a + in17_c + in17_e + in17_f + in17_g);
    in17s[19] =  -(in17_a + in17_d + in17_e + in17_g);
    in17s[20] =  -(in17_d + in17_e + in17_f + in17_g);
    in17s[21] =  in17_b + in17_c + in17_d;
    in17s[22] =  in17_a + in17_c + in17_d + in17_f;
    in17s[23] =  in17_a + in17_g;
    in17s[24] =  -(in17_f);
    in17s[25] =  -(in17_a + in17_e + in17_g);
    in17s[26] =  -(in17_a + in17_c + in17_d + in17_f);
    in17s[27] =  -(in17_b + in17_c + in17_e);
    in17s[28] =  in17_c + in17_e;
    in17s[29] =  in17_a + in17_d + in17_e + in17_f + in17_g;
    in17s[30] =  in17_a + in17_c + in17_e + in17_f;
    in17s[31] =  in17_b + in17_e + in17_g;

    ap_int<32> in19s[32];
    #pragma HLS ARRAY_PARTITION variable=in19s complete dim=0

    in19s[0 ] =  in19_a + in19_c + in19_g;
    in19s[1 ] =  in19_d + in19_e + in19_f + in19_g;
    in19s[2 ] =  -(in19_b + in19_c + in19_d + in19_e + in19_f);
    in19s[3 ] =  -(in19_a + in19_c + in19_d + in19_f);
    in19s[4 ] =  -(in19_b + in19_d + in19_e);
    in19s[5 ] =  in19_b + in19_e + in19_g;
    in19s[6 ] =  in19_a + in19_c + in19_d;
    in19s[7 ] =  in19_a + in19_e + in19_g;
    in19s[8 ] =  -(in19_e + in19_f + in19_g);
    in19s[9 ] =  -(in19_a + in19_d + in19_e + in19_g);
    in19s[10] =  -(in19_a + in19_c + in19_e);
    in19s[11] =  -(in19_c + in19_d);
    in19s[12] =  in19_b + in19_c + in19_d;
    in19s[13] =  in19_a + in19_c + in19_d + in19_f + in19_g;
    in19s[14] =  in19_b + in19_c + in19_e;
    in19s[15] =  -(in19_c + in19_d + in19_e);
    in19s[16] =  -(in19_a + in19_c + in19_e + in19_f);
    in19s[17] =  -(in19_a + in19_d + in19_g);
    in19s[18] =  -(in19_f);
    in19s[19] =  in19_a + in19_e + in19_f + in19_g;
    in19s[20] =  in19_a + in19_c + in19_e + in19_f + in19_g;
    in19s[21] =  in19_b + in19_g;
    in19s[22] =  -(in19_b + in19_c);
    in19s[23] =  -(in19_a + in19_c + in19_d + in19_f);
    in19s[24] =  -(in19_b + in19_c + in19_d + in19_f + in19_g);
    in19s[25] =  in19_c + in19_e;
    in19s[26] =  in19_a + in19_c + in19_f + in19_g;
    in19s[27] =  in19_a + in19_d + in19_e + in19_f + in19_g;
    in19s[28] =  in19_d + in19_f + in19_g;
    in19s[29] =  -(in19_a + in19_g);
    in19s[30] =  -(in19_a + in19_c + in19_d + in19_f);
    in19s[31] =  -(in19_b + in19_d + in19_g);

    ap_int<32> in21s[32];
    #pragma HLS ARRAY_PARTITION variable=in21s complete dim=0

    in21s[0 ] =  in21_a + in21_d + in21_e + in21_f + in21_g;
    in21s[1 ] =  in21_f;
    in21s[2 ] =  -(in21_a + in21_d + in21_e + in21_g);
    in21s[3 ] =  -(in21_a + in21_c + in21_g);
    in21s[4 ] =  -(in21_e + in21_f + in21_g);
    in21s[5 ] =  in21_a + in21_d + in21_g;
    in21s[6 ] =  in21_a + in21_c + in21_f + in21_g;
    in21s[7 ] =  in21_d + in21_f + in21_g;
    in21s[8 ] =  -(in21_a + in21_e + in21_f + in21_g);
    in21s[9 ] =  -(in21_a + in21_c + in21_e);
    in21s[10] =  -(in21_d + in21_e + in21_f + in21_g);
    in21s[11] =  in21_a + in21_e + in21_g;
    in21s[12] =  in21_a + in21_c + in21_e + in21_f;
    in21s[13] =  in21_c + in21_e;
    in21s[14] =  -(in21_a + in21_g);
    in21s[15] =  -(in21_a + in21_c + in21_e + in21_f + in21_g);
    in21s[16] =  -(in21_c + in21_d);
    in21s[17] =  in21_b + in21_c + in21_d + in21_e + in21_f;
    in21s[18] =  in21_a + in21_c + in21_d;
    in21s[19] =  in21_c + in21_d + in21_e;
    in21s[20] =  -(in21_b + in21_c + in21_d + in21_f + in21_g);
    in21s[21] =  -(in21_a + in21_c + in21_d + in21_f);
    in21s[22] =  -(in21_b + in21_g);
    in21s[23] =  in21_b + in21_c + in21_d;
    in21s[24] =  in21_a + in21_c + in21_d + in21_f;
    in21s[25] =  in21_b + in21_e + in21_g;
    in21s[26] =  -(in21_b + in21_c + in21_e);
    in21s[27] =  -(in21_a + in21_c + in21_d + in21_f);
    in21s[28] =  -(in21_b + in21_d + in21_g);
    in21s[29] =  in21_b + in21_c;
    in21s[30] =  in21_a + in21_c + in21_d + in21_f + in21_g;
    in21s[31] =  in21_b + in21_d + in21_e;

    ap_int<32> in23s[32];
    #pragma HLS ARRAY_PARTITION variable=in23s complete dim=0

    in23s[0 ] =  in23_a + in23_d + in23_e + in23_g;
    in23s[1 ] =  -(in23_d + in23_f + in23_g);
    in23s[2 ] =  -(in23_a + in23_c + in23_e + in23_f);
    in23s[3 ] =  -(in23_b + in23_c + in23_d + in23_e + in23_f);
    in23s[4 ] =  in23_b + in23_g;
    in23s[5 ] =  in23_a + in23_c + in23_d + in23_f;
    in23s[6 ] =  in23_b + in23_d + in23_e;
    in23s[7 ] =  -(in23_b + in23_c + in23_e);
    in23s[8 ] =  -(in23_a + in23_c + in23_d + in23_f);
    in23s[9 ] =  -(in23_c + in23_d);
    in23s[10] =  in23_a + in23_e + in23_g;
    in23s[11] =  in23_a + in23_c + in23_f + in23_g;
    in23s[12] =  in23_f;
    in23s[13] =  -(in23_a + in23_c + in23_g);
    in23s[14] =  -(in23_a + in23_e + in23_f + in23_g);
    in23s[15] =  in23_c + in23_e;
    in23s[16] =  in23_a + in23_c + in23_d;
    in23s[17] =  in23_b + in23_c + in23_d;
    in23s[18] =  -(in23_b + in23_d + in23_g);
    in23s[19] =  -(in23_a + in23_c + in23_d + in23_f + in23_g);
    in23s[20] =  -(in23_b + in23_e + in23_g);
    in23s[21] =  in23_b + in23_c + in23_d + in23_f + in23_g;
    in23s[22] =  in23_a + in23_c + in23_e + in23_f + in23_g;
    in23s[23] =  in23_d + in23_e + in23_f + in23_g;
    in23s[24] =  -(in23_a + in23_d + in23_g);
    in23s[25] =  -(in23_a + in23_d + in23_e + in23_f + in23_g);
    in23s[26] =  in23_e + in23_f + in23_g;
    in23s[27] =  in23_a + in23_c + in23_e;
    in23s[28] =  in23_a + in23_g;
    in23s[29] =  -(in23_c + in23_d + in23_e);
    in23s[30] =  -(in23_a + in23_c + in23_d + in23_f);
    in23s[31] =  -(in23_b + in23_c);

    ap_int<32> in25s[32];
    #pragma HLS ARRAY_PARTITION variable=in25s complete dim=0

    in25s[0 ] =  in25_a + in25_d + in25_g;
    in25s[1 ] =  -(in25_c + in25_d);
    in25s[2 ] =  -(in25_a + in25_c + in25_d + in25_f);
    in25s[3 ] =  -(in25_b + in25_e + in25_g);
    in25s[4 ] =  in25_a + in25_g;
    in25s[5 ] =  in25_a + in25_c + in25_g;
    in25s[6 ] =  -(in25_d + in25_f + in25_g);
    in25s[7 ] =  -(in25_a + in25_c + in25_d);
    in25s[8 ] =  -(in25_b + in25_c);
    in25s[9 ] =  in25_b + in25_c + in25_d;
    in25s[10] =  in25_a + in25_c + in25_e + in25_f;
    in25s[11] =  in25_f;
    in25s[12] =  -(in25_a + in25_c + in25_e);
    in25s[13] =  -(in25_b + in25_c + in25_d + in25_f + in25_g);
    in25s[14] =  in25_b + in25_d + in25_e;
    in25s[15] =  in25_a + in25_c + in25_d + in25_f;
    in25s[16] =  in25_d + in25_e + in25_f + in25_g;
    in25s[17] =  -(in25_a + in25_d + in25_e + in25_f + in25_g);
    in25s[18] =  -(in25_a + in25_e + in25_g);
    in25s[19] =  in25_b + in25_g;
    in25s[20] =  in25_a + in25_c + in25_d + in25_f + in25_g;
    in25s[21] =  in25_c + in25_d + in25_e;
    in25s[22] =  -(in25_a + in25_e + in25_f + in25_g);
    in25s[23] =  -(in25_a + in25_d + in25_e + in25_g);
    in25s[24] =  in25_c + in25_e;
    in25s[25] =  in25_a + in25_c + in25_d + in25_f;
    in25s[26] =  in25_b + in25_d + in25_g;
    in25s[27] =  -(in25_b + in25_c + in25_d + in25_e + in25_f);
    in25s[28] =  -(in25_a + in25_c + in25_f + in25_g);
    in25s[29] =  in25_e + in25_f + in25_g;
    in25s[30] =  in25_a + in25_c + in25_e + in25_f + in25_g;
    in25s[31] =  in25_b + in25_c + in25_e;

    ap_int<32> in27s[32];
    #pragma HLS ARRAY_PARTITION variable=in27s complete dim=0

    in27s[0 ] =  in27_a + in27_e + in27_f + in27_g;
    in27s[1 ] =  -(in27_b + in27_e + in27_g);
    in27s[2 ] =  -(in27_a + in27_c + in27_d + in27_f);
    in27s[3 ] =  -(in27_e + in27_f + in27_g);
    in27s[4 ] =  in27_a + in27_c + in27_e + in27_f;
    in27s[5 ] =  in27_b + in27_c;
    in27s[6 ] =  -(in27_b + in27_c + in27_d + in27_e + in27_f);
    in27s[7 ] =  -(in27_a + in27_d + in27_e + in27_f + in27_g);
    in27s[8 ] =  in27_c + in27_d;
    in27s[9 ] =  in27_a + in27_c + in27_d + in27_f + in27_g;
    in27s[10] =  in27_c + in27_e;
    in27s[11] =  -(in27_a + in27_c + in27_g);
    in27s[12] =  -(in27_b + in27_c + in27_d + in27_f + in27_g);
    in27s[13] =  in27_b + in27_c + in27_e;
    in27s[14] =  in27_a + in27_c + in27_e;
    in27s[15] =  -(in27_d + in27_f + in27_g);
    in27s[16] =  -(in27_a + in27_c + in27_d + in27_f);
    in27s[17] =  -(in27_b + in27_g);
    in27s[18] =  in27_a + in27_d + in27_g;
    in27s[19] =  in27_a + in27_e + in27_g;
    in27s[20] =  -(in27_b + in27_d + in27_g);
    in27s[21] =  -(in27_a + in27_c + in27_d);
    in27s[22] =  -(in27_f);
    in27s[23] =  in27_a + in27_c + in27_e + in27_f + in27_g;
    in27s[24] =  in27_b + in27_d + in27_e;
    in27s[25] =  -(in27_a + in27_g);
    in27s[26] =  -(in27_a + in27_d + in27_e + in27_g);
    in27s[27] =  in27_c + in27_d + in27_e;
    in27s[28] =  in27_a + in27_c + in27_d + in27_f;
    in27s[29] =  in27_d + in27_e + in27_f + in27_g;
    in27s[30] =  -(in27_a + in27_c + in27_f + in27_g);
    in27s[31] =  -(in27_b + in27_c + in27_d);

    ap_int<32> in29s[32];
    #pragma HLS ARRAY_PARTITION variable=in29s complete dim=0

    in29s[0 ] =  in29_a + in29_e + in29_g;
    in29s[1 ] =  -(in29_b + in29_c);
    in29s[2 ] =  -(in29_a + in29_c + in29_f + in29_g);
    in29s[3 ] =  in29_c + in29_d;
    in29s[4 ] =  in29_a + in29_c + in29_d + in29_f;
    in29s[5 ] =  in29_f;
    in29s[6 ] =  -(in29_a + in29_c + in29_d + in29_f);
    in29s[7 ] =  -(in29_c + in29_d + in29_e);
    in29s[8 ] =  in29_a + in29_c + in29_g;
    in29s[9 ] =  in29_b + in29_c + in29_e;
    in29s[10] =  -(in29_a + in29_g);
    in29s[11] =  -(in29_a + in29_e + in29_f + in29_g);
    in29s[12] =  in29_b + in29_d + in29_e;
    in29s[13] =  in29_a + in29_c + in29_e;
    in29s[14] =  -(in29_c + in29_e);
    in29s[15] =  -(in29_a + in29_c + in29_d + in29_f);
    in29s[16] =  -(in29_e + in29_f + in29_g);
    in29s[17] =  in29_a + in29_c + in29_d;
    in29s[18] =  in29_b + in29_g;
    in29s[19] =  -(in29_a + in29_d + in29_e + in29_f + in29_g);
    in29s[20] =  -(in29_b + in29_c + in29_d);
    in29s[21] =  in29_b + in29_c + in29_d + in29_e + in29_f;
    in29s[22] =  in29_a + in29_d + in29_g;
    in29s[23] =  -(in29_b + in29_d + in29_g);
    in29s[24] =  -(in29_a + in29_c + in29_e + in29_f);
    in29s[25] =  in29_d + in29_e + in29_f + in29_g;
    in29s[26] =  in29_a + in29_c + in29_d + in29_f + in29_g;
    in29s[27] =  in29_d + in29_f + in29_g;
    in29s[28] =  -(in29_a + in29_c + in29_e + in29_f + in29_g);
    in29s[29] =  -(in29_b + in29_e + in29_g);
    in29s[30] =  in29_a + in29_d + in29_e + in29_g;
    in29s[31] =  in29_b + in29_c + in29_d + in29_f + in29_g;

    ap_int<32> in31s[32];
    #pragma HLS ARRAY_PARTITION variable=in31s complete dim=0

    in31s[0 ] =  in31_a + in31_g;
    in31s[1 ] =  -(in31_b + in31_c + in31_d + in31_f + in31_g);
    in31s[2 ] =  -(in31_a + in31_e + in31_f + in31_g);
    in31s[3 ] =  in31_b + in31_c + in31_e;
    in31s[4 ] =  in31_a + in31_d + in31_e + in31_g;
    in31s[5 ] =  -(in31_b + in31_d + in31_e);
    in31s[6 ] =  -(in31_a + in31_c + in31_g);
    in31s[7 ] =  in31_b + in31_e + in31_g;
    in31s[8 ] =  in31_a + in31_c + in31_e;
    in31s[9 ] =  -(in31_c + in31_d + in31_e);
    in31s[10] =  -(in31_a + in31_c + in31_e + in31_f + in31_g);
    in31s[11] =  in31_c + in31_e;
    in31s[12] =  in31_a + in31_c + in31_d + in31_f;
    in31s[13] =  -(in31_d + in31_f + in31_g);
    in31s[14] =  -(in31_a + in31_c + in31_d + in31_f);
    in31s[15] =  in31_f;
    in31s[16] =  in31_a + in31_c + in31_d + in31_f + in31_g;
    in31s[17] =  in31_e + in31_f + in31_g;
    in31s[18] =  -(in31_a + in31_c + in31_d + in31_f);
    in31s[19] =  -(in31_d + in31_e + in31_f + in31_g);
    in31s[20] =  in31_a + in31_c + in31_d;
    in31s[21] =  in31_c + in31_d;
    in31s[22] =  -(in31_a + in31_c + in31_e + in31_f);
    in31s[23] =  -(in31_b + in31_g);
    in31s[24] =  in31_a + in31_c + in31_f + in31_g;
    in31s[25] =  in31_b + in31_d + in31_g;
    in31s[26] =  -(in31_a + in31_d + in31_e + in31_f + in31_g);
    in31s[27] =  -(in31_b + in31_c);
    in31s[28] =  in31_a + in31_d + in31_g;
    in31s[29] =  in31_b + in31_c + in31_d;
    in31s[30] =  -(in31_a + in31_e + in31_g);
    in31s[31] =  -(in31_b + in31_c + in31_d + in31_e + in31_f);

    ap_int<32> in1s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in1s_2 complete dim=0
    in1s_2[0 ] =  in1_b_2 + in1_c_2 + in1_d_2 + in1_e_2 + in1_f_2;
    in1s_2[1 ] =  -(in1_a_2 + in1_e_2 + in1_g_2);
    in1s_2[2 ] =  -(in1_b_2 + in1_c_2 + in1_d_2);
    in1s_2[3 ] =  in1_a_2 + in1_d_2 + in1_g_2;
    in1s_2[4 ] =  in1_b_2 + in1_c_2;
    in1s_2[5 ] =  -(in1_a_2 + in1_d_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[6 ] =  -(in1_b_2 + in1_d_2 + in1_g_2);
    in1s_2[7 ] =  in1_a_2 + in1_c_2 + in1_f_2 + in1_g_2;
    in1s_2[8 ] =  in1_b_2 + in1_g_2;
    in1s_2[9 ] =  -(in1_a_2 + in1_c_2 + in1_e_2 + in1_f_2);
    in1s_2[10] =  -(in1_c_2 + in1_d_2);
    in1s_2[11] =  in1_a_2 + in1_c_2 + in1_d_2;
    in1s_2[12] =  in1_d_2 + in1_e_2 + in1_f_2 + in1_g_2;
    in1s_2[13] =  -(in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2);
    in1s_2[14] =  -(in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[15] =  in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[16] =  -(in1_f_2);
    in1s_2[17] =  -(in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2);
    in1s_2[18] =  in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[19] =  in1_a_2 + in1_c_2 + in1_d_2 + in1_f_2;
    in1s_2[20] =  -(in1_c_2 + in1_e_2);
    in1s_2[21] =  -(in1_a_2 + in1_c_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[22] =  in1_c_2 + in1_d_2 + in1_e_2;
    in1s_2[23] =  in1_a_2 + in1_c_2 + in1_e_2;
    in1s_2[24] =  -(in1_b_2 + in1_e_2 + in1_g_2);
    in1s_2[25] =  -(in1_a_2 + in1_c_2 + in1_g_2);
    in1s_2[26] =  in1_b_2 + in1_d_2 + in1_e_2;
    in1s_2[27] =  in1_a_2 + in1_d_2 + in1_e_2 + in1_g_2;
    in1s_2[28] =  -(in1_b_2 + in1_c_2 + in1_e_2);
    in1s_2[29] =  -(in1_a_2 + in1_e_2 + in1_f_2 + in1_g_2);
    in1s_2[30] =  in1_b_2 + in1_c_2 + in1_d_2 + in1_f_2 + in1_g_2;
    in1s_2[31] =  in1_a_2 + in1_g_2;

    ap_int<32> in3s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in3s_2 complete dim=0
    in3s_2[0 ] =  in3_b_2 + in3_c_2 + in3_d_2 + in3_f_2 + in3_g_2;
    in3s_2[1 ] =  -(in3_a_2 + in3_d_2 + in3_e_2 + in3_g_2);
    in3s_2[2 ] =  -(in3_b_2 + in3_e_2 + in3_g_2);
    in3s_2[3 ] =  in3_a_2 + in3_c_2 + in3_e_2 + in3_f_2 + in3_g_2;
    in3s_2[4 ] =  in3_d_2 + in3_f_2 + in3_g_2;
    in3s_2[5 ] =  -(in3_a_2 + in3_c_2 + in3_d_2 + in3_f_2 + in3_g_2);
    in3s_2[6 ] =  in3_d_2 + in3_e_2 + in3_f_2 + in3_g_2;
    in3s_2[7 ] =  in3_a_2 + in3_c_2 + in3_e_2 + in3_f_2;
    in3s_2[8 ] =  -(in3_b_2 + in3_d_2 + in3_g_2);
    in3s_2[9 ] =  -(in3_a_2 + in3_d_2 + in3_g_2);
    in3s_2[10] =  in3_b_2 + in3_c_2 + in3_d_2 + in3_e_2 + in3_f_2;
    in3s_2[11] =  in3_b_2 + in3_c_2 + in3_d_2;
    in3s_2[12] =  -(in3_a_2 + in3_d_2 + in3_e_2 + in3_f_2 + in3_g_2);
    in3s_2[13] =  -(in3_b_2 + in3_g_2);
    in3s_2[14] =  in3_a_2 + in3_c_2 + in3_d_2;
    in3s_2[15] =  in3_e_2 + in3_f_2 + in3_g_2;
    in3s_2[16] =  -(in3_a_2 + in3_c_2 + in3_d_2 + in3_f_2);
    in3s_2[17] =  in3_c_2 + in3_e_2;
    in3s_2[18] =  in3_a_2 + in3_c_2 + in3_e_2;
    in3s_2[19] =  -(in3_b_2 + in3_d_2 + in3_e_2);
    in3s_2[20] =  -(in3_a_2 + in3_e_2 + in3_f_2 + in3_g_2);
    in3s_2[21] =  in3_a_2 + in3_g_2;
    in3s_2[22] =  in3_b_2 + in3_c_2 + in3_e_2;
    in3s_2[23] =  -(in3_a_2 + in3_c_2 + in3_g_2);
    in3s_2[24] =  -(in3_c_2 + in3_d_2 + in3_e_2);
    in3s_2[25] =  in3_a_2 + in3_c_2 + in3_d_2 + in3_f_2;
    in3s_2[26] =  in3_f_2;
    in3s_2[27] =  -(in3_a_2 + in3_c_2 + in3_d_2 + in3_f_2);
    in3s_2[28] =  in3_c_2 + in3_d_2;
    in3s_2[29] =  in3_a_2 + in3_c_2 + in3_f_2 + in3_g_2;
    in3s_2[30] =  -(in3_b_2 + in3_c_2);
    in3s_2[31] =  -(in3_a_2 + in3_e_2 + in3_g_2);

    ap_int<32> in5s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in5s_2 complete dim=0
    in5s_2[0 ] =  in5_b_2 + in5_c_2 + in5_d_2;
    in5s_2[1 ] =  -(in5_a_2 + in5_c_2 + in5_f_2 + in5_g_2);
    in5s_2[2 ] =  -(in5_d_2 + in5_e_2 + in5_f_2 + in5_g_2);
    in5s_2[3 ] =  in5_a_2 + in5_c_2 + in5_d_2 + in5_f_2;
    in5s_2[4 ] =  -(in5_c_2 + in5_d_2 + in5_e_2);
    in5s_2[5 ] =  -(in5_a_2 + in5_d_2 + in5_e_2 + in5_g_2);
    in5s_2[6 ] =  in5_a_2 + in5_g_2;
    in5s_2[7 ] =  in5_b_2 + in5_d_2 + in5_e_2;
    in5s_2[8 ] =  -(in5_a_2 + in5_c_2 + in5_e_2 + in5_f_2 + in5_g_2);
    in5s_2[9 ] =  -(in5_f_2);
    in5s_2[10] =  in5_a_2 + in5_c_2 + in5_d_2;
    in5s_2[11] =  -(in5_b_2 + in5_d_2 + in5_g_2);
    in5s_2[12] =  -(in5_a_2 + in5_e_2 + in5_g_2);
    in5s_2[13] =  in5_a_2 + in5_d_2 + in5_g_2;
    in5s_2[14] =  in5_b_2 + in5_g_2;
    in5s_2[15] =  -(in5_a_2 + in5_c_2 + in5_d_2 + in5_f_2);
    in5s_2[16] =  in5_d_2 + in5_f_2 + in5_g_2;
    in5s_2[17] =  in5_a_2 + in5_c_2 + in5_e_2;
    in5s_2[18] =  -(in5_b_2 + in5_c_2 + in5_e_2);
    in5s_2[19] =  -(in5_b_2 + in5_c_2 + in5_d_2 + in5_f_2 + in5_g_2);
    in5s_2[20] =  in5_a_2 + in5_c_2 + in5_g_2;
    in5s_2[21] =  in5_c_2 + in5_e_2;
    in5s_2[22] =  -(in5_a_2 + in5_c_2 + in5_d_2 + in5_f_2 + in5_g_2);
    in5s_2[23] =  in5_c_2 + in5_d_2;
    in5s_2[24] =  in5_a_2 + in5_d_2 + in5_e_2 + in5_f_2 + in5_g_2;
    in5s_2[25] =  -(in5_b_2 + in5_c_2 + in5_d_2 + in5_e_2 + in5_f_2);
    in5s_2[26] =  -(in5_b_2 + in5_c_2);
    in5s_2[27] =  in5_a_2 + in5_c_2 + in5_e_2 + in5_f_2;
    in5s_2[28] =  in5_e_2 + in5_f_2 + in5_g_2;
    in5s_2[29] =  -(in5_a_2 + in5_c_2 + in5_d_2 + in5_f_2);
    in5s_2[30] =  in5_b_2 + in5_e_2 + in5_g_2;
    in5s_2[31] =  in5_a_2 + in5_e_2 + in5_f_2 + in5_g_2;

    ap_int<32> in7s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in7s_2 complete dim=0
    in7s_2[0 ] =  in7_b_2 + in7_c_2 + in7_e_2;
    in7s_2[1 ] =  -(in7_a_2 + in7_c_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[2 ] =  in7_e_2 + in7_f_2 + in7_g_2;
    in7s_2[3 ] =  in7_a_2 + in7_c_2 + in7_f_2 + in7_g_2;
    in7s_2[4 ] =  -(in7_b_2 + in7_c_2 + in7_d_2 + in7_e_2 + in7_f_2);
    in7s_2[5 ] =  -(in7_b_2 + in7_d_2 + in7_g_2);
    in7s_2[6 ] =  in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2;
    in7s_2[7 ] =  -(in7_c_2 + in7_e_2);
    in7s_2[8 ] =  -(in7_a_2 + in7_d_2 + in7_e_2 + in7_g_2);
    in7s_2[9 ] =  in7_a_2 + in7_e_2 + in7_f_2 + in7_g_2;
    in7s_2[10] =  in7_c_2 + in7_d_2 + in7_e_2;
    in7s_2[11] =  -(in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2 + in7_g_2);
    in7s_2[12] =  in7_b_2 + in7_g_2;
    in7s_2[13] =  in7_a_2 + in7_e_2 + in7_g_2;
    in7s_2[14] =  -(in7_a_2 + in7_d_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[15] =  -(in7_d_2 + in7_e_2 + in7_f_2 + in7_g_2);
    in7s_2[16] =  in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2;
    in7s_2[17] =  -(in7_b_2 + in7_d_2 + in7_e_2);
    in7s_2[18] =  -(in7_b_2 + in7_c_2 + in7_d_2 + in7_f_2 + in7_g_2);
    in7s_2[19] =  in7_a_2 + in7_c_2 + in7_e_2;
    in7s_2[20] =  in7_f_2;
    in7s_2[21] =  -(in7_a_2 + in7_c_2 + in7_e_2 + in7_f_2);
    in7s_2[22] =  in7_b_2 + in7_c_2 + in7_d_2;
    in7s_2[23] =  in7_b_2 + in7_c_2;
    in7s_2[24] =  -(in7_a_2 + in7_c_2 + in7_d_2);
    in7s_2[25] =  in7_d_2 + in7_f_2 + in7_g_2;
    in7s_2[26] =  in7_a_2 + in7_c_2 + in7_g_2;
    in7s_2[27] =  -(in7_a_2 + in7_g_2);
    in7s_2[28] =  -(in7_b_2 + in7_e_2 + in7_g_2);
    in7s_2[29] =  in7_a_2 + in7_c_2 + in7_d_2 + in7_f_2;
    in7s_2[30] =  -(in7_c_2 + in7_d_2);
    in7s_2[31] =  -(in7_a_2 + in7_d_2 + in7_g_2);

    ap_int<32> in9s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in9s_2 complete dim=0
    in9s_2[0 ] =  in9_b_2 + in9_c_2;
    in9s_2[1 ] =  -(in9_a_2 + in9_c_2 + in9_d_2 + in9_f_2);
    in9s_2[2 ] =  in9_c_2 + in9_d_2 + in9_e_2;
    in9s_2[3 ] =  in9_a_2 + in9_g_2;
    in9s_2[4 ] =  -(in9_a_2 + in9_c_2 + in9_e_2);
    in9s_2[5 ] =  in9_e_2 + in9_f_2 + in9_g_2;
    in9s_2[6 ] =  in9_a_2 + in9_d_2 + in9_e_2 + in9_f_2 + in9_g_2;
    in9s_2[7 ] =  -(in9_a_2 + in9_d_2 + in9_g_2);
    in9s_2[8 ] =  -(in9_d_2 + in9_e_2 + in9_f_2 + in9_g_2);
    in9s_2[9 ] =  in9_a_2 + in9_c_2 + in9_e_2 + in9_f_2 + in9_g_2;
    in9s_2[10] =  -(in9_b_2 + in9_c_2 + in9_d_2 + in9_f_2 + in9_g_2);
    in9s_2[11] =  -(in9_b_2 + in9_e_2 + in9_g_2);
    in9s_2[12] =  in9_a_2 + in9_c_2 + in9_d_2 + in9_f_2 + in9_g_2;
    in9s_2[13] =  -(in9_b_2 + in9_d_2 + in9_g_2);
    in9s_2[14] =  -(in9_b_2 + in9_c_2 + in9_d_2);
    in9s_2[15] =  in9_a_2 + in9_c_2 + in9_d_2;
    in9s_2[16] =  -(in9_c_2 + in9_e_2);
    in9s_2[17] =  -(in9_a_2 + in9_e_2 + in9_f_2 + in9_g_2);
    in9s_2[18] =  in9_a_2 + in9_c_2 + in9_g_2;
    in9s_2[19] =  in9_f_2;
    in9s_2[20] =  -(in9_a_2 + in9_c_2 + in9_f_2 + in9_g_2);
    in9s_2[21] =  in9_a_2 + in9_e_2 + in9_g_2;
    in9s_2[22] =  in9_c_2 + in9_d_2;
    in9s_2[23] =  -(in9_a_2 + in9_c_2 + in9_d_2 + in9_f_2);
    in9s_2[24] =  in9_b_2 + in9_c_2 + in9_e_2;
    in9s_2[25] =  in9_b_2 + in9_d_2 + in9_e_2;
    in9s_2[26] =  -(in9_a_2 + in9_c_2 + in9_d_2 + in9_f_2);
    in9s_2[27] =  in9_b_2 + in9_g_2;
    in9s_2[28] =  in9_b_2 + in9_c_2 + in9_d_2 + in9_e_2 + in9_f_2;
    in9s_2[29] =  -(in9_a_2 + in9_c_2 + in9_e_2 + in9_f_2);
    in9s_2[30] =  in9_d_2 + in9_f_2 + in9_g_2;
    in9s_2[31] =  in9_a_2 + in9_d_2 + in9_e_2 + in9_g_2;

    ap_int<32> in11s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in11s_2 complete dim=0
    in11s_2[0 ] =  in11_b_2 + in11_d_2 + in11_e_2;
    in11s_2[1 ] =  -(in11_a_2 + in11_c_2 + in11_d_2 + in11_f_2 + in11_g_2);
    in11s_2[2 ] =  in11_b_2 + in11_c_2;
    in11s_2[3 ] =  in11_b_2 + in11_d_2 + in11_g_2;
    in11s_2[4 ] =  -(in11_a_2 + in11_c_2 + in11_d_2 + in11_f_2);
    in11s_2[5 ] =  in11_b_2 + in11_c_2 + in11_e_2;
    in11s_2[6 ] =  in11_b_2 + in11_e_2 + in11_g_2;
    in11s_2[7 ] =  -(in11_a_2 + in11_c_2 + in11_d_2 + in11_f_2);
    in11s_2[8 ] =  in11_b_2 + in11_c_2 + in11_d_2;
    in11s_2[9 ] =  in11_b_2 + in11_g_2;
    in11s_2[10] =  -(in11_a_2 + in11_c_2 + in11_d_2 + in11_f_2);
    in11s_2[11] =  in11_b_2 + in11_c_2 + in11_d_2 + in11_f_2 + in11_g_2;
    in11s_2[12] =  in11_c_2 + in11_d_2 + in11_e_2;
    in11s_2[13] =  -(in11_a_2 + in11_c_2 + in11_d_2);
    in11s_2[14] =  in11_b_2 + in11_c_2 + in11_d_2 + in11_e_2 + in11_f_2;
    in11s_2[15] =  in11_c_2 + in11_d_2;
    in11s_2[16] =  -(in11_a_2 + in11_c_2 + in11_e_2 + in11_f_2 + in11_g_2);
    in11s_2[17] =  in11_a_2 + in11_g_2;
    in11s_2[18] =  in11_c_2 + in11_e_2;
    in11s_2[19] =  -(in11_a_2 + in11_c_2 + in11_e_2 + in11_f_2);
    in11s_2[20] =  in11_a_2 + in11_e_2 + in11_g_2;
    in11s_2[21] =  in11_d_2 + in11_e_2 + in11_f_2 + in11_g_2;
    in11s_2[22] =  -(in11_a_2 + in11_c_2 + in11_e_2);
    in11s_2[23] =  in11_a_2 + in11_e_2 + in11_f_2 + in11_g_2;
    in11s_2[24] =  in11_d_2 + in11_f_2 + in11_g_2;
    in11s_2[25] =  -(in11_a_2 + in11_c_2 + in11_f_2 + in11_g_2);
    in11s_2[26] =  in11_a_2 + in11_d_2 + in11_g_2;
    in11s_2[27] =  in11_e_2 + in11_f_2 + in11_g_2;
    in11s_2[28] =  -(in11_a_2 + in11_c_2 + in11_g_2);
    in11s_2[29] =  in11_a_2 + in11_d_2 + in11_e_2 + in11_g_2;
    in11s_2[30] =  in11_f_2;
    in11s_2[31] =  -(in11_a_2 + in11_d_2 + in11_e_2 + in11_f_2 + in11_g_2);

    ap_int<32> in13s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in13s_2 complete dim=0
    in13s_2[0 ] =  in13_b_2 + in13_d_2 + in13_g_2;
    in13s_2[1 ] =  -(in13_a_2 + in13_c_2 + in13_d_2 + in13_f_2);
    in13s_2[2 ] =  in13_a_2 + in13_g_2;
    in13s_2[3 ] =  in13_d_2 + in13_f_2 + in13_g_2;
    in13s_2[4 ] =  -(in13_a_2 + in13_d_2 + in13_e_2 + in13_f_2 + in13_g_2);
    in13s_2[5 ] =  in13_a_2 + in13_c_2 + in13_f_2 + in13_g_2;
    in13s_2[6 ] =  -(in13_c_2 + in13_e_2);
    in13s_2[7 ] =  -(in13_b_2 + in13_c_2 + in13_d_2 + in13_f_2 + in13_g_2);
    in13s_2[8 ] =  in13_a_2 + in13_c_2 + in13_d_2 + in13_f_2;
    in13s_2[9 ] =  -(in13_b_2 + in13_c_2);
    in13s_2[10] =  -(in13_b_2 + in13_g_2);
    in13s_2[11] =  in13_a_2 + in13_c_2 + in13_e_2 + in13_f_2 + in13_g_2;
    in13s_2[12] =  -(in13_a_2 + in13_e_2 + in13_f_2 + in13_g_2);
    in13s_2[13] =  -(in13_f_2);
    in13s_2[14] =  in13_a_2 + in13_d_2 + in13_g_2;
    in13s_2[15] =  -(in13_a_2 + in13_c_2 + in13_e_2 + in13_f_2);
    in13s_2[16] =  in13_c_2 + in13_d_2 + in13_e_2;
    in13s_2[17] =  in13_b_2 + in13_c_2 + in13_e_2;
    in13s_2[18] =  -(in13_a_2 + in13_c_2 + in13_d_2 + in13_f_2 + in13_g_2);
    in13s_2[19] =  in13_b_2 + in13_c_2 + in13_d_2;
    in13s_2[20] =  in13_c_2 + in13_d_2;
    in13s_2[21] =  -(in13_a_2 + in13_c_2 + in13_e_2);
    in13s_2[22] =  in13_a_2 + in13_d_2 + in13_e_2 + in13_g_2;
    in13s_2[23] =  -(in13_e_2 + in13_f_2 + in13_g_2);
    in13s_2[24] =  -(in13_a_2 + in13_e_2 + in13_g_2);
    in13s_2[25] =  in13_a_2 + in13_c_2 + in13_d_2;
    in13s_2[26] =  -(in13_b_2 + in13_e_2 + in13_g_2);
    in13s_2[27] =  -(in13_b_2 + in13_d_2 + in13_e_2);
    in13s_2[28] =  in13_a_2 + in13_c_2 + in13_d_2 + in13_f_2;
    in13s_2[29] =  -(in13_b_2 + in13_c_2 + in13_d_2 + in13_e_2 + in13_f_2);
    in13s_2[30] =  -(in13_d_2 + in13_e_2 + in13_f_2 + in13_g_2);
    in13s_2[31] =  in13_a_2 + in13_c_2 + in13_g_2;

    ap_int<32> in15s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in15s_2 complete dim=0
    in15s_2[0 ] =  in15_b_2 + in15_e_2 + in15_g_2;
    in15s_2[1 ] =  -(in15_a_2 + in15_c_2 + in15_e_2 + in15_f_2);
    in15s_2[2 ] =  in15_a_2 + in15_d_2 + in15_e_2 + in15_f_2 + in15_g_2;
    in15s_2[3 ] =  -(in15_c_2 + in15_e_2);
    in15s_2[4 ] =  -(in15_b_2 + in15_c_2 + in15_e_2);
    in15s_2[5 ] =  in15_a_2 + in15_c_2 + in15_d_2 + in15_f_2;
    in15s_2[6 ] =  -(in15_a_2 + in15_e_2 + in15_g_2);
    in15s_2[7 ] =  in15_f_2;
    in15s_2[8 ] =  in15_a_2 + in15_g_2;
    in15s_2[9 ] =  -(in15_a_2 + in15_c_2 + in15_d_2 + in15_f_2);
    in15s_2[10] =  in15_b_2 + in15_c_2 + in15_d_2;
    in15s_2[11] =  in15_d_2 + in15_e_2 + in15_f_2 + in15_g_2;
    in15s_2[12] =  -(in15_a_2 + in15_d_2 + in15_e_2 + in15_g_2);
    in15s_2[13] =  in15_a_2 + in15_c_2 + in15_e_2 + in15_f_2 + in15_g_2;
    in15s_2[14] =  -(in15_b_2 + in15_d_2 + in15_g_2);
    in15s_2[15] =  -(in15_b_2 + in15_g_2);
    in15s_2[16] =  in15_a_2 + in15_c_2 + in15_e_2;
    in15s_2[17] =  -(in15_a_2 + in15_c_2 + in15_g_2);
    in15s_2[18] =  in15_c_2 + in15_d_2;
    in15s_2[19] =  in15_b_2 + in15_c_2;
    in15s_2[20] =  -(in15_a_2 + in15_c_2 + in15_d_2 + in15_f_2);
    in15s_2[21] =  in15_a_2 + in15_e_2 + in15_f_2 + in15_g_2;
    in15s_2[22] =  -(in15_e_2 + in15_f_2 + in15_g_2);
    in15s_2[23] =  -(in15_b_2 + in15_c_2 + in15_d_2 + in15_e_2 + in15_f_2);
    in15s_2[24] =  in15_a_2 + in15_c_2 + in15_d_2 + in15_f_2 + in15_g_2;
    in15s_2[25] =  -(in15_b_2 + in15_c_2 + in15_d_2 + in15_f_2 + in15_g_2);
    in15s_2[26] =  -(in15_d_2 + in15_f_2 + in15_g_2);
    in15s_2[27] =  in15_a_2 + in15_d_2 + in15_g_2;
    in15s_2[28] =  -(in15_a_2 + in15_c_2 + in15_d_2);
    in15s_2[29] =  in15_b_2 + in15_d_2 + in15_e_2;
    in15s_2[30] =  in15_c_2 + in15_d_2 + in15_e_2;
    in15s_2[31] =  -(in15_a_2 + in15_c_2 + in15_f_2 + in15_g_2);

    ap_int<32> in17s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in17s_2 complete dim=0
    in17s_2[0 ] =  in17_b_2 + in17_g_2;
    in17s_2[1 ] =  -(in17_a_2 + in17_c_2 + in17_g_2);
    in17s_2[2 ] =  in17_a_2 + in17_c_2 + in17_e_2 + in17_f_2 + in17_g_2;
    in17s_2[3 ] =  -(in17_b_2 + in17_c_2);
    in17s_2[4 ] =  -(in17_d_2 + in17_e_2 + in17_f_2 + in17_g_2);
    in17s_2[5 ] =  in17_a_2 + in17_e_2 + in17_f_2 + in17_g_2;
    in17s_2[6 ] =  -(in17_a_2 + in17_c_2 + in17_d_2 + in17_f_2);
    in17s_2[7 ] =  in17_b_2 + in17_c_2 + in17_d_2 + in17_e_2 + in17_f_2;
    in17s_2[8 ] =  -(in17_f_2);
    in17s_2[9 ] =  -(in17_b_2 + in17_c_2 + in17_d_2 + in17_f_2 + in17_g_2);
    in17s_2[10] =  in17_a_2 + in17_c_2 + in17_d_2 + in17_f_2;
    in17s_2[11] =  -(in17_a_2 + in17_d_2 + in17_g_2);
    in17s_2[12] =  in17_c_2 + in17_e_2;
    in17s_2[13] =  in17_b_2 + in17_d_2 + in17_e_2;
    in17s_2[14] =  -(in17_a_2 + in17_c_2 + in17_e_2 + in17_f_2);
    in17s_2[15] =  in17_a_2 + in17_c_2 + in17_f_2 + in17_g_2;
    in17s_2[16] =  -(in17_b_2 + in17_e_2 + in17_g_2);
    in17s_2[17] =  -(in17_c_2 + in17_d_2 + in17_e_2);
    in17s_2[18] =  in17_a_2 + in17_d_2 + in17_e_2 + in17_f_2 + in17_g_2;
    in17s_2[19] =  -(in17_a_2 + in17_c_2 + in17_d_2);
    in17s_2[20] =  in17_b_2 + in17_c_2 + in17_e_2;
    in17s_2[21] =  in17_d_2 + in17_f_2 + in17_g_2;
    in17s_2[22] =  -(in17_a_2 + in17_e_2 + in17_g_2);
    in17s_2[23] =  in17_a_2 + in17_c_2 + in17_d_2 + in17_f_2 + in17_g_2;
    in17s_2[24] =  -(in17_a_2 + in17_g_2);
    in17s_2[25] =  in17_e_2 + in17_f_2 + in17_g_2;
    in17s_2[26] =  in17_b_2 + in17_c_2 + in17_d_2;
    in17s_2[27] =  -(in17_a_2 + in17_c_2 + in17_d_2 + in17_f_2);
    in17s_2[28] =  in17_a_2 + in17_d_2 + in17_e_2 + in17_g_2;
    in17s_2[29] =  -(in17_c_2 + in17_d_2);
    in17s_2[30] =  -(in17_b_2 + in17_d_2 + in17_g_2);
    in17s_2[31] =  in17_a_2 + in17_c_2 + in17_e_2;

    ap_int<32> in19s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in19s_2 complete dim=0
    in19s_2[0 ] =  in19_c_2 + in19_d_2 + in19_e_2;
    in19s_2[1 ] =  -(in19_a_2 + in19_d_2 + in19_g_2);
    in19s_2[2 ] =  in19_a_2 + in19_c_2 + in19_d_2 + in19_f_2 + in19_g_2;
    in19s_2[3 ] =  -(in19_a_2 + in19_e_2 + in19_f_2 + in19_g_2);
    in19s_2[4 ] =  in19_c_2 + in19_d_2;
    in19s_2[5 ] =  in19_b_2 + in19_g_2;
    in19s_2[6 ] =  -(in19_a_2 + in19_d_2 + in19_e_2 + in19_g_2);
    in19s_2[7 ] =  in19_a_2 + in19_c_2 + in19_d_2 + in19_f_2;
    in19s_2[8 ] =  -(in19_a_2 + in19_e_2 + in19_g_2);
    in19s_2[9 ] =  in19_c_2 + in19_e_2;
    in19s_2[10] =  in19_b_2 + in19_e_2 + in19_g_2;
    in19s_2[11] =  -(in19_a_2 + in19_d_2 + in19_e_2 + in19_f_2 + in19_g_2);
    in19s_2[12] =  in19_a_2 + in19_c_2 + in19_d_2 + in19_f_2;
    in19s_2[13] =  -(in19_a_2 + in19_g_2);
    in19s_2[14] =  in19_d_2 + in19_e_2 + in19_f_2 + in19_g_2;
    in19s_2[15] =  in19_b_2 + in19_d_2 + in19_g_2;
    in19s_2[16] =  -(in19_a_2 + in19_c_2 + in19_g_2);
    in19s_2[17] =  in19_a_2 + in19_c_2 + in19_d_2 + in19_f_2;
    in19s_2[18] =  -(in19_b_2 + in19_c_2 + in19_d_2 + in19_e_2 + in19_f_2);
    in19s_2[19] =  in19_d_2 + in19_f_2 + in19_g_2;
    in19s_2[20] =  in19_b_2 + in19_d_2 + in19_e_2;
    in19s_2[21] =  -(in19_a_2 + in19_c_2 + in19_f_2 + in19_g_2);
    in19s_2[22] =  in19_a_2 + in19_c_2 + in19_d_2;
    in19s_2[23] =  -(in19_b_2 + in19_c_2 + in19_d_2 + in19_f_2 + in19_g_2);
    in19s_2[24] =  in19_e_2 + in19_f_2 + in19_g_2;
    in19s_2[25] =  in19_b_2 + in19_c_2;
    in19s_2[26] =  -(in19_a_2 + in19_c_2 + in19_e_2);
    in19s_2[27] =  in19_a_2 + in19_c_2 + in19_e_2 + in19_f_2 + in19_g_2;
    in19s_2[28] =  -(in19_b_2 + in19_c_2 + in19_d_2);
    in19s_2[29] =  in19_f_2;
    in19s_2[30] =  in19_b_2 + in19_c_2 + in19_e_2;
    in19s_2[31] =  -(in19_a_2 + in19_c_2 + in19_e_2 + in19_f_2);

    ap_int<32> in21s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in21s_2 complete dim=0
    in21s_2[0 ] =  in21_c_2 + in21_d_2;
    in21s_2[1 ] =  -(in21_a_2 + in21_g_2);
    in21s_2[2 ] =  in21_a_2 + in21_c_2 + in21_d_2;
    in21s_2[3 ] =  -(in21_a_2 + in21_c_2 + in21_e_2 + in21_f_2);
    in21s_2[4 ] =  in21_b_2 + in21_c_2 + in21_d_2 + in21_f_2 + in21_g_2;
    in21s_2[5 ] =  -(in21_d_2 + in21_e_2 + in21_f_2 + in21_g_2);
    in21s_2[6 ] =  -(in21_b_2 + in21_g_2);
    in21s_2[7 ] =  in21_a_2 + in21_e_2 + in21_f_2 + in21_g_2;
    in21s_2[8 ] =  -(in21_a_2 + in21_c_2 + in21_d_2 + in21_f_2);
    in21s_2[9 ] =  in21_a_2 + in21_c_2 + in21_f_2 + in21_g_2;
    in21s_2[10] =  -(in21_b_2 + in21_c_2 + in21_e_2);
    in21s_2[11] =  in21_e_2 + in21_f_2 + in21_g_2;
    in21s_2[12] =  in21_b_2 + in21_d_2 + in21_g_2;
    in21s_2[13] =  -(in21_a_2 + in21_d_2 + in21_e_2 + in21_g_2);
    in21s_2[14] =  in21_a_2 + in21_c_2 + in21_d_2 + in21_f_2 + in21_g_2;
    in21s_2[15] =  -(in21_a_2 + in21_d_2 + in21_e_2 + in21_f_2 + in21_g_2);
    in21s_2[16] =  in21_b_2 + in21_d_2 + in21_e_2;
    in21s_2[17] =  in21_f_2;
    in21s_2[18] =  -(in21_b_2 + in21_c_2);
    in21s_2[19] =  in21_a_2 + in21_c_2 + in21_g_2;
    in21s_2[20] =  -(in21_a_2 + in21_c_2 + in21_d_2 + in21_f_2);
    in21s_2[21] =  in21_a_2 + in21_d_2 + in21_g_2;
    in21s_2[22] =  -(in21_b_2 + in21_e_2 + in21_g_2);
    in21s_2[23] =  -(in21_d_2 + in21_f_2 + in21_g_2);
    in21s_2[24] =  in21_b_2 + in21_c_2 + in21_d_2;
    in21s_2[25] =  -(in21_a_2 + in21_c_2 + in21_e_2);
    in21s_2[26] =  in21_a_2 + in21_c_2 + in21_d_2 + in21_f_2;
    in21s_2[27] =  -(in21_a_2 + in21_e_2 + in21_g_2);
    in21s_2[28] =  in21_c_2 + in21_d_2 + in21_e_2;
    in21s_2[29] =  in21_c_2 + in21_e_2;
    in21s_2[30] =  -(in21_b_2 + in21_c_2 + in21_d_2 + in21_e_2 + in21_f_2);
    in21s_2[31] =  in21_a_2 + in21_c_2 + in21_e_2 + in21_f_2 + in21_g_2;

    ap_int<32> in23s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in23s_2 complete dim=0
    in23s_2[0 ] =  in23_c_2 + in23_e_2;
    in23s_2[1 ] =  -(in23_b_2 + in23_c_2 + in23_d_2);
    in23s_2[2 ] =  in23_a_2 + in23_c_2 + in23_g_2;
    in23s_2[3 ] =  -(in23_a_2 + in23_c_2 + in23_d_2 + in23_f_2 + in23_g_2);
    in23s_2[4 ] =  in23_a_2 + in23_c_2 + in23_f_2 + in23_g_2;
    in23s_2[5 ] =  -(in23_b_2 + in23_c_2 + in23_d_2 + in23_f_2 + in23_g_2);
    in23s_2[6 ] =  in23_c_2 + in23_d_2;
    in23s_2[7 ] =  in23_d_2 + in23_e_2 + in23_f_2 + in23_g_2;
    in23s_2[8 ] =  -(in23_b_2 + in23_c_2 + in23_e_2);
    in23s_2[9 ] =  in23_a_2 + in23_d_2 + in23_e_2 + in23_f_2 + in23_g_2;
    in23s_2[10] =  -(in23_a_2 + in23_c_2 + in23_d_2 + in23_f_2);
    in23s_2[11] =  in23_a_2 + in23_c_2 + in23_e_2;
    in23s_2[12] =  -(in23_b_2 + in23_c_2 + in23_d_2 + in23_e_2 + in23_f_2);
    in23s_2[13] =  in23_c_2 + in23_d_2 + in23_e_2;
    in23s_2[14] =  in23_d_2 + in23_f_2 + in23_g_2;
    in23s_2[15] =  -(in23_b_2 + in23_c_2);
    in23s_2[16] =  in23_a_2 + in23_d_2 + in23_e_2 + in23_g_2;
    in23s_2[17] =  -(in23_a_2 + in23_c_2 + in23_d_2 + in23_f_2);
    in23s_2[18] =  in23_a_2 + in23_c_2 + in23_e_2 + in23_f_2;
    in23s_2[19] =  -(in23_a_2 + in23_g_2);
    in23s_2[20] =  in23_b_2 + in23_g_2;
    in23s_2[21] =  in23_e_2 + in23_f_2 + in23_g_2;
    in23s_2[22] =  -(in23_b_2 + in23_d_2 + in23_e_2);
    in23s_2[23] =  in23_a_2 + in23_d_2 + in23_g_2;
    in23s_2[24] =  -(in23_a_2 + in23_c_2 + in23_d_2 + in23_f_2);
    in23s_2[25] =  in23_a_2 + in23_c_2 + in23_e_2 + in23_f_2 + in23_g_2;
    in23s_2[26] =  -(in23_a_2 + in23_e_2 + in23_g_2);
    in23s_2[27] =  in23_b_2 + in23_e_2 + in23_g_2;
    in23s_2[28] =  in23_f_2;
    in23s_2[29] =  -(in23_b_2 + in23_d_2 + in23_g_2);
    in23s_2[30] =  in23_a_2 + in23_e_2 + in23_f_2 + in23_g_2;
    in23s_2[31] =  -(in23_a_2 + in23_c_2 + in23_d_2);

    ap_int<32> in25s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in25s_2 complete dim=0
    in25s_2[0 ] =  in25_d_2 + in25_e_2 + in25_f_2 + in25_g_2;
    in25s_2[1 ] =  -(in25_b_2 + in25_d_2 + in25_e_2);
    in25s_2[2 ] =  in25_a_2 + in25_e_2 + in25_g_2;
    in25s_2[3 ] =  -(in25_a_2 + in25_c_2 + in25_e_2);
    in25s_2[4 ] =  in25_a_2 + in25_c_2 + in25_d_2 + in25_f_2 + in25_g_2;
    in25s_2[5 ] =  -(in25_a_2 + in25_c_2 + in25_e_2 + in25_f_2);
    in25s_2[6 ] =  in25_a_2 + in25_e_2 + in25_f_2 + in25_g_2;
    in25s_2[7 ] =  -(in25_b_2 + in25_c_2);
    in25s_2[8 ] =  in25_c_2 + in25_e_2;
    in25s_2[9 ] =  in25_d_2 + in25_f_2 + in25_g_2;
    in25s_2[10] =  -(in25_b_2 + in25_d_2 + in25_g_2);
    in25s_2[11] =  in25_a_2 + in25_g_2;
    in25s_2[12] =  -(in25_a_2 + in25_c_2 + in25_f_2 + in25_g_2);
    in25s_2[13] =  in25_a_2 + in25_c_2 + in25_d_2 + in25_f_2;
    in25s_2[14] =  -(in25_a_2 + in25_c_2 + in25_e_2 + in25_f_2 + in25_g_2);
    in25s_2[15] =  in25_a_2 + in25_d_2 + in25_g_2;
    in25s_2[16] =  -(in25_b_2 + in25_c_2 + in25_e_2);
    in25s_2[17] =  in25_c_2 + in25_d_2;
    in25s_2[18] =  in25_e_2 + in25_f_2 + in25_g_2;
    in25s_2[19] =  -(in25_b_2 + in25_e_2 + in25_g_2);
    in25s_2[20] =  in25_b_2 + in25_c_2 + in25_d_2 + in25_e_2 + in25_f_2;
    in25s_2[21] =  -(in25_a_2 + in25_c_2 + in25_g_2);
    in25s_2[22] =  in25_a_2 + in25_c_2 + in25_d_2 + in25_f_2;
    in25s_2[23] =  -(in25_a_2 + in25_c_2 + in25_d_2);
    in25s_2[24] =  in25_a_2 + in25_d_2 + in25_e_2 + in25_g_2;
    in25s_2[25] =  -(in25_b_2 + in25_c_2 + in25_d_2);
    in25s_2[26] =  in25_c_2 + in25_d_2 + in25_e_2;
    in25s_2[27] =  in25_f_2;
    in25s_2[28] =  -(in25_b_2 + in25_g_2);
    in25s_2[29] =  in25_b_2 + in25_c_2 + in25_d_2 + in25_f_2 + in25_g_2;
    in25s_2[30] =  -(in25_a_2 + in25_d_2 + in25_e_2 + in25_f_2 + in25_g_2);
    in25s_2[31] =  in25_a_2 + in25_c_2 + in25_d_2 + in25_f_2;

    ap_int<32> in27s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in27s_2 complete dim=0
    in27s_2[0 ] =  in27_d_2 + in27_f_2 + in27_g_2;
    in27s_2[1 ] =  -(in27_b_2 + in27_g_2);
    in27s_2[2 ] =  in27_b_2 + in27_c_2 + in27_e_2;
    in27s_2[3 ] =  -(in27_a_2 + in27_e_2 + in27_g_2);
    in27s_2[4 ] =  in27_a_2 + in27_c_2 + in27_g_2;
    in27s_2[5 ] =  -(in27_a_2 + in27_c_2 + in27_d_2);
    in27s_2[6 ] =  in27_a_2 + in27_c_2 + in27_d_2 + in27_f_2 + in27_g_2;
    in27s_2[7 ] =  -(in27_a_2 + in27_c_2 + in27_e_2 + in27_f_2 + in27_g_2);
    in27s_2[8 ] =  in27_a_2 + in27_d_2 + in27_e_2 + in27_f_2 + in27_g_2;
    in27s_2[9 ] =  -(in27_a_2 + in27_g_2);
    in27s_2[10] =  in27_b_2 + in27_c_2;
    in27s_2[11] =  -(in27_c_2 + in27_d_2 + in27_e_2);
    in27s_2[12] =  in27_e_2 + in27_f_2 + in27_g_2;
    in27s_2[13] =  in27_d_2 + in27_e_2 + in27_f_2 + in27_g_2;
    in27s_2[14] =  -(in27_b_2 + in27_e_2 + in27_g_2);
    in27s_2[15] =  in27_b_2 + in27_c_2 + in27_d_2;
    in27s_2[16] =  -(in27_a_2 + in27_e_2 + in27_f_2 + in27_g_2);
    in27s_2[17] =  in27_a_2 + in27_c_2 + in27_f_2 + in27_g_2;
    in27s_2[18] =  -(in27_a_2 + in27_c_2 + in27_d_2 + in27_f_2);
    in27s_2[19] =  in27_a_2 + in27_c_2 + in27_d_2 + in27_f_2;
    in27s_2[20] =  -(in27_a_2 + in27_c_2 + in27_e_2 + in27_f_2);
    in27s_2[21] =  in27_a_2 + in27_d_2 + in27_e_2 + in27_g_2;
    in27s_2[22] =  -(in27_b_2 + in27_c_2 + in27_d_2 + in27_e_2 + in27_f_2);
    in27s_2[23] =  in27_b_2 + in27_d_2 + in27_e_2;
    in27s_2[24] =  -(in27_c_2 + in27_d_2);
    in27s_2[25] =  in27_f_2;
    in27s_2[26] =  in27_c_2 + in27_e_2;
    in27s_2[27] =  -(in27_b_2 + in27_d_2 + in27_g_2);
    in27s_2[28] =  in27_b_2 + in27_c_2 + in27_d_2 + in27_f_2 + in27_g_2;
    in27s_2[29] =  -(in27_a_2 + in27_d_2 + in27_g_2);
    in27s_2[30] =  in27_a_2 + in27_c_2 + in27_e_2;
    in27s_2[31] =  -(in27_a_2 + in27_c_2 + in27_d_2 + in27_f_2);

    ap_int<32> in29s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in29s_2 complete dim=0
    in29s_2[0 ] =  in29_e_2 + in29_f_2 + in29_g_2;
    in29s_2[1 ] =  -(in29_c_2 + in29_e_2);
    in29s_2[2 ] =  in29_b_2 + in29_g_2;
    in29s_2[3 ] =  -(in29_b_2 + in29_d_2 + in29_e_2);
    in29s_2[4 ] =  in29_b_2 + in29_c_2 + in29_d_2;
    in29s_2[5 ] =  -(in29_a_2 + in29_g_2);
    in29s_2[6 ] =  in29_a_2 + in29_d_2 + in29_g_2;
    in29s_2[7 ] =  -(in29_a_2 + in29_c_2 + in29_g_2);
    in29s_2[8 ] =  in29_a_2 + in29_c_2 + in29_e_2 + in29_f_2;
    in29s_2[9 ] =  -(in29_a_2 + in29_c_2 + in29_d_2 + in29_f_2);
    in29s_2[10] =  in29_a_2 + in29_c_2 + in29_d_2 + in29_f_2 + in29_g_2;
    in29s_2[11] =  -(in29_a_2 + in29_c_2 + in29_d_2 + in29_f_2);
    in29s_2[12] =  in29_a_2 + in29_c_2 + in29_e_2 + in29_f_2 + in29_g_2;
    in29s_2[13] =  -(in29_a_2 + in29_c_2 + in29_f_2 + in29_g_2);
    in29s_2[14] =  in29_a_2 + in29_d_2 + in29_e_2 + in29_g_2;
    in29s_2[15] =  -(in29_a_2 + in29_e_2 + in29_g_2);
    in29s_2[16] =  in29_b_2 + in29_c_2 + in29_d_2 + in29_f_2 + in29_g_2;
    in29s_2[17] =  -(in29_b_2 + in29_c_2);
    in29s_2[18] =  in29_b_2 + in29_e_2 + in29_g_2;
    in29s_2[19] =  -(in29_c_2 + in29_d_2);
    in29s_2[20] =  in29_d_2 + in29_f_2 + in29_g_2;
    in29s_2[21] =  in29_f_2;
    in29s_2[22] =  -(in29_d_2 + in29_e_2 + in29_f_2 + in29_g_2);
    in29s_2[23] =  in29_c_2 + in29_d_2 + in29_e_2;
    in29s_2[24] =  -(in29_b_2 + in29_d_2 + in29_g_2);
    in29s_2[25] =  in29_b_2 + in29_c_2 + in29_e_2;
    in29s_2[26] =  -(in29_b_2 + in29_c_2 + in29_d_2 + in29_e_2 + in29_f_2);
    in29s_2[27] =  in29_a_2 + in29_e_2 + in29_f_2 + in29_g_2;
    in29s_2[28] =  -(in29_a_2 + in29_d_2 + in29_e_2 + in29_f_2 + in29_g_2);
    in29s_2[29] =  in29_a_2 + in29_c_2 + in29_e_2;
    in29s_2[30] =  -(in29_a_2 + in29_c_2 + in29_d_2);
    in29s_2[31] =  in29_a_2 + in29_c_2 + in29_d_2 + in29_f_2;

    ap_int<32> in31s_2[32];
    #pragma HLS ARRAY_PARTITION variable=in31s_2 complete dim=0
    in31s_2[0 ] =  in31_f_2;
    in31s_2[1 ] =  -(in31_e_2 + in31_f_2 + in31_g_2);
    in31s_2[2 ] =  in31_d_2 + in31_f_2 + in31_g_2;
    in31s_2[3 ] =  -(in31_d_2 + in31_e_2 + in31_f_2 + in31_g_2);
    in31s_2[4 ] =  in31_c_2 + in31_e_2;
    in31s_2[5 ] =  -(in31_c_2 + in31_d_2);
    in31s_2[6 ] =  in31_c_2 + in31_d_2 + in31_e_2;
    in31s_2[7 ] =  -(in31_b_2 + in31_g_2);
    in31s_2[8 ] =  in31_b_2 + in31_e_2 + in31_g_2;
    in31s_2[9 ] =  -(in31_b_2 + in31_d_2 + in31_g_2);
    in31s_2[10] =  in31_b_2 + in31_d_2 + in31_e_2;
    in31s_2[11] =  -(in31_b_2 + in31_c_2);
    in31s_2[12] =  in31_b_2 + in31_c_2 + in31_e_2;
    in31s_2[13] =  -(in31_b_2 + in31_c_2 + in31_d_2);
    in31s_2[14] =  in31_b_2 + in31_c_2 + in31_d_2 + in31_f_2 + in31_g_2;
    in31s_2[15] =  -(in31_b_2 + in31_c_2 + in31_d_2 + in31_e_2 + in31_f_2);
    in31s_2[16] =  in31_a_2 + in31_g_2;
    in31s_2[17] =  -(in31_a_2 + in31_e_2 + in31_g_2);
    in31s_2[18] =  in31_a_2 + in31_e_2 + in31_f_2 + in31_g_2;
    in31s_2[19] =  -(in31_a_2 + in31_d_2 + in31_g_2);
    in31s_2[20] =  in31_a_2 + in31_d_2 + in31_e_2 + in31_g_2;
    in31s_2[21] =  -(in31_a_2 + in31_d_2 + in31_e_2 + in31_f_2 + in31_g_2);
    in31s_2[22] =  in31_a_2 + in31_c_2 + in31_g_2;
    in31s_2[23] =  -(in31_a_2 + in31_c_2 + in31_f_2 + in31_g_2);
    in31s_2[24] =  in31_a_2 + in31_c_2 + in31_e_2;
    in31s_2[25] =  -(in31_a_2 + in31_c_2 + in31_e_2 + in31_f_2);
    in31s_2[26] =  in31_a_2 + in31_c_2 + in31_e_2 + in31_f_2 + in31_g_2;
    in31s_2[27] =  -(in31_a_2 + in31_c_2 + in31_d_2);
    in31s_2[28] =  in31_a_2 + in31_c_2 + in31_d_2 + in31_f_2;
    in31s_2[29] =  -(in31_a_2 + in31_c_2 + in31_d_2 + in31_f_2);
    in31s_2[30] =  in31_a_2 + in31_c_2 + in31_d_2 + in31_f_2;
    in31s_2[31] =  -(in31_a_2 + in31_c_2 + in31_d_2 + in31_f_2 + in31_g_2);

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = in1s[i] + in3s[i] + in5s[i] + in7s[i] + in9s[i] + in11s[i] + in13s[i] + in15s[i] +
            in17s[i] + in19s[i] + in21s[i] + in23s[i] + in25s[i] + in27s[i] + in29s[i] + in31s[i] +
            in1s_2[i] + in3s_2[i] + in5s_2[i] + in7s_2[i] + in9s_2[i] + in11s_2[i] + in13s_2[i] + in15s_2[i] +
            in17s_2[i] + in19s_2[i] + in21s_2[i] + in23s_2[i] + in25s_2[i] + in27s_2[i] + in29s_2[i] + in31s_2[i];
    }

    #else

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = idct64[1][i]*in[1] + idct64[3][i]*in[3] + idct64[5][i]*in[5] + idct64[7][i]*in[7] + idct64[9][i]*in[9] + idct64[11][i]*in[11] + idct64[13][i]*in[13] + idct64[15][i]*in[15] +
            idct64[17][i]*in[17] + idct64[19][i]*in[19] + idct64[21][i]*in[21] + idct64[23][i]*in[23] + idct64[25][i]*in[25] + idct64[27][i]*in[27] + idct64[29][i]*in[29] + idct64[31][i]*in[31] +
            idct64[33][i]*in[33] + idct64[35][i]*in[35] + idct64[37][i]*in[37] + idct64[39][i]*in[39] + idct64[41][i]*in[41] + idct64[43][i]*in[43] + idct64[45][i]*in[45] + idct64[47][i]*in[47] +
            idct64[49][i]*in[49] + idct64[51][i]*in[51] + idct64[53][i]*in[53] + idct64[55][i]*in[55] + idct64[57][i]*in[57] + idct64[59][i]*in[59] + idct64[61][i]*in[61] + idct64[63][i]*in[63];
    }

    #endif

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[2] + odds[2];
    out[3] = evens[3] + odds[3];
    out[4] = evens[4] + odds[4];
    out[5] = evens[5] + odds[5];
    out[6] = evens[6] + odds[6];
    out[7] = evens[7] + odds[7];
    out[8] = evens[8] + odds[8];
    out[9] = evens[9] + odds[9];
    out[10] = evens[10] + odds[10];
    out[11] = evens[11] + odds[11];
    out[12] = evens[12] + odds[12];
    out[13] = evens[13] + odds[13];
    out[14] = evens[14] + odds[14];
    out[15] = evens[15] + odds[15];
    out[16] = evens[16] + odds[16];
    out[17] = evens[17] + odds[17];
    out[18] = evens[18] + odds[18];
    out[19] = evens[19] + odds[19];
    out[20] = evens[20] + odds[20];
    out[21] = evens[21] + odds[21];
    out[22] = evens[22] + odds[22];
    out[23] = evens[23] + odds[23];
    out[24] = evens[24] + odds[24];
    out[25] = evens[25] + odds[25];
    out[26] = evens[26] + odds[26];
    out[27] = evens[27] + odds[27];
    out[28] = evens[28] + odds[28];
    out[29] = evens[29] + odds[29];
    out[30] = evens[30] + odds[30];
    out[31] = evens[31] + odds[31];

    out[32] = evens[31] - odds[31];
    out[33] = evens[30] - odds[30];
    out[34] = evens[29] - odds[29];
    out[35] = evens[28] - odds[28];
    out[36] = evens[27] - odds[27];
    out[37] = evens[26] - odds[26];
    out[38] = evens[25] - odds[25];
    out[39] = evens[24] - odds[24];
    out[40] = evens[23] - odds[23];
    out[41] = evens[22] - odds[22];
    out[42] = evens[21] - odds[21];
    out[43] = evens[20] - odds[20];
    out[44] = evens[19] - odds[19];
    out[45] = evens[18] - odds[18];
    out[46] = evens[17] - odds[17];
    out[47] = evens[16] - odds[16];
    out[48] = evens[15] - odds[15];
    out[49] = evens[14] - odds[14];
    out[50] = evens[13] - odds[13];
    out[51] = evens[12] - odds[12];
    out[52] = evens[11] - odds[11];
    out[53] = evens[10] - odds[10];
    out[54] = evens[9] - odds[9];
    out[55] = evens[8] - odds[8];
    out[56] = evens[7] - odds[7];
    out[57] = evens[6] - odds[6];
    out[58] = evens[5] - odds[5];
    out[59] = evens[4] - odds[4];
    out[60] = evens[3] - odds[3];
    out[61] = evens[2] - odds[2];
    out[62] = evens[1] - odds[1];
    out[63] = evens[0] - odds[0];
}

extern "C" void IDCT2(ap_uint<1024>* in, ap_uint<1024>* out, int block_size, int size, int shift, int outputMinimum, int outputMaximum){
    #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0
    #pragma HLS INTERFACE s_axilite port=block_size
    #pragma HLS INTERFACE s_axilite port=size
    #pragma HLS INTERFACE s_axilite port=shift
    #pragma HLS INTERFACE s_axilite port=outputMinimum
    #pragma HLS INTERFACE s_axilite port=outputMaximum
    #pragma HLS INTERFACE s_axilite port=return

    int add = 1 << (shift - 1);

    

if(block_size == 64){
    for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[64];
        OUT_TYPE out_data[64];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<64; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B64(in_data, out_data);

        for(int j=0; j<64; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }

        out[i] = out_block;
}
            //out[i] = out_block;
}else if(block_size == 32){
    for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[32];
        OUT_TYPE out_data[32];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<32; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B32(in_data, out_data);

        for(int j=0; j<32; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }
        out[i] = out_block;
    }
    //out[i] = out_block;
}else if(block_size == 16){
for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[16];
        OUT_TYPE out_data[16];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<16; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B16(in_data, out_data);

        for(int j=0; j<16; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }
        out[i] = out_block;
    }
}else if(block_size == 8){
for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[8];
        OUT_TYPE out_data[8];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<8; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B8(in_data, out_data);

        for(int j=0; j<8; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }
        out[i] = out_block;
    }
}else if(block_size == 4){
for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[4];
        OUT_TYPE out_data[4];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<4; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B4(in_data, out_data);

        for(int j=0; j<4; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }
        out[i] = out_block;
    }
}else{
for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1
        ap_uint<1024> in_block = in[i];
        ap_uint<1024> out_block = 0;

        IN_TYPE in_data[2];
        OUT_TYPE out_data[2];
        #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

        for(int j=0; j<2; j++){
            #pragma HLS UNROLL
            in_data[j] = (ap_int<16>)in_block.range((j+1)*16-1, j*16);
        }

        IDCT2B2(in_data, out_data);

        for(int j=0; j<2; j++){
            #pragma HLS UNROLL
            ap_int<16> tmp1 = CLIP3(((out_data[j]+add) >> shift), ap_int<16>(outputMinimum), ap_int<16>(outputMaximum));
            out_block.range((j+1)*16-1, j*16) = tmp1.range(15, 0);
        }
        out[i] = out_block;
    }
}

}