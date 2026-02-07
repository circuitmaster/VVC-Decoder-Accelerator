#include <iostream>
#include "ap_int.h"
#include "ap_fixed.h"
#include "transform_coeffs.h"

ap_int<32> CLIP3(ap_int<32> x, ap_int<32> outputMinimum, ap_int<32> outputMaximum){
    #pragma HLS inline
    if(x < outputMinimum) return outputMinimum;
    if(x > outputMaximum) return outputMaximum;
    return x;
}

void IDCT2B2(ap_int<32> in[2], ap_int<32> out[2]){
    #pragma HLS inline off

    ap_int<32> sum = in[0] + in[1];
    ap_int<32> diff = in[0] - in[1];

    ap_int<32> even = sum << 6;
    ap_int<32> odd = diff << 6;

    out[0] = even;
    out[1] = odd;
}

void IDCT2B4(ap_int<32> in[4], ap_int<32> out[4]){
    #pragma HLS inline off

    ap_int<32> evens[2];
    ap_int<32> odds[2];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[2];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
    inputs[0] = in[0];
    inputs[1] = in[2];

    IDCT2B2(inputs, evens);
    odds[0] = 83*in[1] + 36*in[3];
    odds[1] = 36*in[1] - 83*in[3];

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[1] - odds[1];
    out[3] = evens[0] - odds[0];
}

void IDCT2B8(ap_int<32> in[8], ap_int<32> out[8]){
    #pragma HLS inline off

    ap_int<32> evens[4];
    ap_int<32> odds[4];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[4];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
    inputs[0] = in[0];
    inputs[2] = in[4];
    inputs[1] = in[2];
    inputs[3] = in[6];

    IDCT2B4(inputs, evens);
    odds[0] = 89*in[1] + 75*in[3] + 50*in[5] + 18*in[7];
    odds[1] = 75*in[1] - 18*in[3] - 89*in[5] - 50*in[7];
    odds[2] = 50*in[1] - 89*in[3] + 18*in[5] + 75*in[7];
    odds[3] = 18*in[1] - 50*in[3] + 75*in[5] - 89*in[7];

    out[0] = evens[0] + odds[0];
    out[1] = evens[1] + odds[1];
    out[2] = evens[2] + odds[2];
    out[3] = evens[3] + odds[3];
    out[4] = evens[3] - odds[3];
    out[5] = evens[2] - odds[2];
    out[6] = evens[1] - odds[1];
    out[7] = evens[0] - odds[0];
}

void IDCT2B16(ap_int<32> in[16], ap_int<32> out[16]){
    #pragma HLS inline off

    ap_int<32> evens[8];
    ap_int<32> odds[8];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[8];
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

    for(int i=0; i<8; i++){
        #pragma HLS UNROLL
        odds[i] = idct16[1][i]*in[1] + idct16[3][i]*in[3] + idct16[5][i]*in[5] + idct16[7][i]*in[7] + idct16[9][i]*in[9] + idct16[11][i]*in[11] + idct16[13][i]*in[13] + idct16[15][i]*in[15];
    }

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

void IDCT2B32(ap_int<32> in[32], ap_int<32> out[32]){
    #pragma HLS inline off

    ap_int<32> evens[16];
    ap_int<32> odds[16];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[16];
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

    for(int i=0; i<16; i++){
        #pragma HLS UNROLL
        odds[i] = idct32[1][i]*in[1] + idct32[3][i]*in[3] + idct32[5][i]*in[5] + idct32[7][i]*in[7] + idct32[9][i]*in[9] + idct32[11][i]*in[11] + idct32[13][i]*in[13] + idct32[15][i]*in[15] +
            idct32[17][i]*in[17] + idct32[19][i]*in[19] + idct32[21][i]*in[21] + idct32[23][i]*in[23] + idct32[25][i]*in[25] + idct32[27][i]*in[27] + idct32[29][i]*in[29] + idct32[31][i]*in[31];
    }

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

void IDCT2B64(ap_int<32> in1[32], ap_int<32> in2[32], ap_int<32> out1[32], ap_int<32> out2[32]){
    #pragma HLS inline off

    ap_int<32> evens[32];
    ap_int<32> odds[32];
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0
    /* ap_int<16> odds_1[32];
    ap_int<16> odds_2[32];
    ap_int<16> odds_3[32];
    ap_int<16> odds_4[32]; */
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    /* #pragma HLS ARRAY_PARTITION variable=odds_1 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds_2 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds_3 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds_4 complete dim=0 */

    /* ap_int<8> in1_1[32];
    ap_int<8> in1_2[32];
    ap_int<8> in1_3[32];
    ap_int<8> in1_4[32];
    ap_int<8> in2_1[32];
    ap_int<8> in2_2[32];
    ap_int<8> in2_3[32];
    ap_int<8> in2_4[32];
    #pragma HLS ARRAY_PARTITION variable=in1_1 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in1_2 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in1_3 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in1_4 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in2_1 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in2_2 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in2_3 complete dim=0
    #pragma HLS ARRAY_PARTITION variable=in2_4 complete dim=0 */

    /* for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        in1_1[i].range(7,0) = in1[i].range(7,0);
        in1_2[i].range(7,0) = in1[i].range(15,8);
        in1_3[i].range(7,0) = in1[i].range(23,16);
        in1_4[i].range(7,0) = in1[i].range(31,24);
        in2_1[i].range(7,0) = in2[i].range(7,0);
        in2_2[i].range(7,0) = in2[i].range(15,8);
        in2_3[i].range(7,0) = in2[i].range(23,16);
        in2_4[i].range(7,0) = in2[i].range(31,24);
    } */

    ap_int<32> inputs[32];
    #pragma HLS ARRAY_PARTITION variable=inputs complete dim=0

    inputs[0] = in1[0];
    inputs[16] = in2[0];
    inputs[8] = in1[16];
    inputs[24] = in2[16];
    inputs[4] = in1[8];
    inputs[12] = in1[24];
    inputs[20] = in2[8];
    inputs[28] = in2[24];
    inputs[2] = in1[4];
    inputs[6] = in1[12];
    inputs[10] = in1[20];
    inputs[14] = in1[28];
    inputs[18] = in2[4];
    inputs[22] = in2[12];
    inputs[26] = in2[20];
    inputs[30] = in2[28];

    inputs[1] = in1[2];
    inputs[3] = in1[6];
    inputs[5] = in1[10];
    inputs[7] = in1[14];
    inputs[9] = in1[18];
    inputs[11] = in1[22];
    inputs[13] = in1[26];
    inputs[15] = in1[30];
    inputs[17] = in2[2];
    inputs[19] = in2[6];
    inputs[21] = in2[10];
    inputs[23] = in2[14];
    inputs[25] = in2[18];
    inputs[27] = in2[22];
    inputs[29] = in2[26];
    inputs[31] = in2[30];
    IDCT2B32(inputs, evens);

    ap_int<32> in1_a = in1[1] << 6;
    ap_int<32> in1_b = in1[1] << 5;
    ap_int<32> in1_c = in1[1] << 4;
    ap_int<32> in1_d = in1[1] << 3;
    ap_int<32> in1_e = in1[1] << 2;
    ap_int<32> in1_f = in1[1] << 1;
    ap_int<32> in1_g = in1[1];

    ap_int<32> in3_a = in1[3] << 6;
    ap_int<32> in3_b = in1[3] << 5;
    ap_int<32> in3_c = in1[3] << 4;
    ap_int<32> in3_d = in1[3] << 3;
    ap_int<32> in3_e = in1[3] << 2;
    ap_int<32> in3_f = in1[3] << 1;
    ap_int<32> in3_g = in1[3];

    ap_int<32> in5_a = in1[5] << 6;
    ap_int<32> in5_b = in1[5] << 5;
    ap_int<32> in5_c = in1[5] << 4;
    ap_int<32> in5_d = in1[5] << 3;
    ap_int<32> in5_e = in1[5] << 2;
    ap_int<32> in5_f = in1[5] << 1;
    ap_int<32> in5_g = in1[5];

    ap_int<32> in7_a = in1[7] << 6;
    ap_int<32> in7_b = in1[7] << 5;
    ap_int<32> in7_c = in1[7] << 4;
    ap_int<32> in7_d = in1[7] << 3;
    ap_int<32> in7_e = in1[7] << 2;
    ap_int<32> in7_f = in1[7] << 1;
    ap_int<32> in7_g = in1[7];

    ap_int<32> in9_a = in1[9] << 6;
    ap_int<32> in9_b = in1[9] << 5;
    ap_int<32> in9_c = in1[9] << 4;
    ap_int<32> in9_d = in1[9] << 3;
    ap_int<32> in9_e = in1[9] << 2;
    ap_int<32> in9_f = in1[9] << 1;
    ap_int<32> in9_g = in1[9];

    ap_int<32> in11_a = in1[11] << 6;
    ap_int<32> in11_b = in1[11] << 5;
    ap_int<32> in11_c = in1[11] << 4;
    ap_int<32> in11_d = in1[11] << 3;
    ap_int<32> in11_e = in1[11] << 2;
    ap_int<32> in11_f = in1[11] << 1;
    ap_int<32> in11_g = in1[11];

    ap_int<32> in13_a = in1[13] << 6;
    ap_int<32> in13_b = in1[13] << 5;
    ap_int<32> in13_c = in1[13] << 4;
    ap_int<32> in13_d = in1[13] << 3;
    ap_int<32> in13_e = in1[13] << 2;
    ap_int<32> in13_f = in1[13] << 1;
    ap_int<32> in13_g = in1[13];

    ap_int<32> in15_a = in1[15] << 6;
    ap_int<32> in15_b = in1[15] << 5;
    ap_int<32> in15_c = in1[15] << 4;
    ap_int<32> in15_d = in1[15] << 3;
    ap_int<32> in15_e = in1[15] << 2;
    ap_int<32> in15_f = in1[15] << 1;
    ap_int<32> in15_g = in1[15];

    ap_int<32> in17_a = in1[17] << 6;
    ap_int<32> in17_b = in1[17] << 5;
    ap_int<32> in17_c = in1[17] << 4;
    ap_int<32> in17_d = in1[17] << 3;
    ap_int<32> in17_e = in1[17] << 2;
    ap_int<32> in17_f = in1[17] << 1;
    ap_int<32> in17_g = in1[17];

    ap_int<32> in19_a = in1[19] << 6;
    ap_int<32> in19_b = in1[19] << 5;
    ap_int<32> in19_c = in1[19] << 4;
    ap_int<32> in19_d = in1[19] << 3;
    ap_int<32> in19_e = in1[19] << 2;
    ap_int<32> in19_f = in1[19] << 1;
    ap_int<32> in19_g = in1[19];

    ap_int<32> in21_a = in1[21] << 6;
    ap_int<32> in21_b = in1[21] << 5;
    ap_int<32> in21_c = in1[21] << 4;
    ap_int<32> in21_d = in1[21] << 3;
    ap_int<32> in21_e = in1[21] << 2;
    ap_int<32> in21_f = in1[21] << 1;
    ap_int<32> in21_g = in1[21];

    ap_int<32> in23_a = in1[23] << 6;
    ap_int<32> in23_b = in1[23] << 5;
    ap_int<32> in23_c = in1[23] << 4;
    ap_int<32> in23_d = in1[23] << 3;
    ap_int<32> in23_e = in1[23] << 2;
    ap_int<32> in23_f = in1[23] << 1;
    ap_int<32> in23_g = in1[23];

    ap_int<32> in25_a = in1[25] << 6;
    ap_int<32> in25_b = in1[25] << 5;
    ap_int<32> in25_c = in1[25] << 4;
    ap_int<32> in25_d = in1[25] << 3;
    ap_int<32> in25_e = in1[25] << 2;
    ap_int<32> in25_f = in1[25] << 1;
    ap_int<32> in25_g = in1[25];

    ap_int<32> in27_a = in1[27] << 6;
    ap_int<32> in27_b = in1[27] << 5;
    ap_int<32> in27_c = in1[27] << 4;
    ap_int<32> in27_d = in1[27] << 3;
    ap_int<32> in27_e = in1[27] << 2;
    ap_int<32> in27_f = in1[27] << 1;
    ap_int<32> in27_g = in1[27];

    ap_int<32> in29_a = in1[29] << 6;
    ap_int<32> in29_b = in1[29] << 5;
    ap_int<32> in29_c = in1[29] << 4;
    ap_int<32> in29_d = in1[29] << 3;
    ap_int<32> in29_e = in1[29] << 2;
    ap_int<32> in29_f = in1[29] << 1;
    ap_int<32> in29_g = in1[29];

    ap_int<32> in31_a = in1[31] << 6;
    ap_int<32> in31_b = in1[31] << 5;
    ap_int<32> in31_c = in1[31] << 4;
    ap_int<32> in31_d = in1[31] << 3;
    ap_int<32> in31_e = in1[31] << 2;
    ap_int<32> in31_f = in1[31] << 1;
    ap_int<32> in31_g = in1[31];

    ap_int<32> in1_a_2 = in2[1] << 6;
    ap_int<32> in1_b_2 = in2[1] << 5;
    ap_int<32> in1_c_2 = in2[1] << 4;
    ap_int<32> in1_d_2 = in2[1] << 3;
    ap_int<32> in1_e_2 = in2[1] << 2;
    ap_int<32> in1_f_2 = in2[1] << 1;
    ap_int<32> in1_g_2 = in2[1];

    ap_int<32> in3_a_2 = in2[3] << 6;
    ap_int<32> in3_b_2 = in2[3] << 5;
    ap_int<32> in3_c_2 = in2[3] << 4;
    ap_int<32> in3_d_2 = in2[3] << 3;
    ap_int<32> in3_e_2 = in2[3] << 2;
    ap_int<32> in3_f_2 = in2[3] << 1;
    ap_int<32> in3_g_2 = in2[3];

    ap_int<32> in5_a_2 = in2[5] << 6;
    ap_int<32> in5_b_2 = in2[5] << 5;
    ap_int<32> in5_c_2 = in2[5] << 4;
    ap_int<32> in5_d_2 = in2[5] << 3;
    ap_int<32> in5_e_2 = in2[5] << 2;
    ap_int<32> in5_f_2 = in2[5] << 1;
    ap_int<32> in5_g_2 = in2[5];

    ap_int<32> in7_a_2 = in2[7] << 6;
    ap_int<32> in7_b_2 = in2[7] << 5;
    ap_int<32> in7_c_2 = in2[7] << 4;
    ap_int<32> in7_d_2 = in2[7] << 3;
    ap_int<32> in7_e_2 = in2[7] << 2;
    ap_int<32> in7_f_2 = in2[7] << 1;
    ap_int<32> in7_g_2 = in2[7];

    ap_int<32> in9_a_2 = in2[9] << 6;
    ap_int<32> in9_b_2 = in2[9] << 5;
    ap_int<32> in9_c_2 = in2[9] << 4;
    ap_int<32> in9_d_2 = in2[9] << 3;
    ap_int<32> in9_e_2 = in2[9] << 2;
    ap_int<32> in9_f_2 = in2[9] << 1;
    ap_int<32> in9_g_2 = in2[9];

    ap_int<32> in11_a_2 = in2[11] << 6;
    ap_int<32> in11_b_2 = in2[11] << 5;
    ap_int<32> in11_c_2 = in2[11] << 4;
    ap_int<32> in11_d_2 = in2[11] << 3;
    ap_int<32> in11_e_2 = in2[11] << 2;
    ap_int<32> in11_f_2 = in2[11] << 1;
    ap_int<32> in11_g_2 = in2[11];

    ap_int<32> in13_a_2 = in2[13] << 6;
    ap_int<32> in13_b_2 = in2[13] << 5;
    ap_int<32> in13_c_2 = in2[13] << 4;
    ap_int<32> in13_d_2 = in2[13] << 3;
    ap_int<32> in13_e_2 = in2[13] << 2;
    ap_int<32> in13_f_2 = in2[13] << 1;
    ap_int<32> in13_g_2 = in2[13];

    ap_int<32> in15_a_2 = in2[15] << 6;
    ap_int<32> in15_b_2 = in2[15] << 5;
    ap_int<32> in15_c_2 = in2[15] << 4;
    ap_int<32> in15_d_2 = in2[15] << 3;
    ap_int<32> in15_e_2 = in2[15] << 2;
    ap_int<32> in15_f_2 = in2[15] << 1;
    ap_int<32> in15_g_2 = in2[15];
    
    ap_int<32> in17_a_2 = in2[17] << 6;
    ap_int<32> in17_b_2 = in2[17] << 5;
    ap_int<32> in17_c_2 = in2[17] << 4;
    ap_int<32> in17_d_2 = in2[17] << 3;
    ap_int<32> in17_e_2 = in2[17] << 2;
    ap_int<32> in17_f_2 = in2[17] << 1;
    ap_int<32> in17_g_2 = in2[17];

    ap_int<32> in19_a_2 = in2[19] << 6;
    ap_int<32> in19_b_2 = in2[19] << 5;
    ap_int<32> in19_c_2 = in2[19] << 4;
    ap_int<32> in19_d_2 = in2[19] << 3;
    ap_int<32> in19_e_2 = in2[19] << 2;
    ap_int<32> in19_f_2 = in2[19] << 1;
    ap_int<32> in19_g_2 = in2[19];

    ap_int<32> in21_a_2 = in2[21] << 6;
    ap_int<32> in21_b_2 = in2[21] << 5;
    ap_int<32> in21_c_2 = in2[21] << 4;
    ap_int<32> in21_d_2 = in2[21] << 3;
    ap_int<32> in21_e_2 = in2[21] << 2;
    ap_int<32> in21_f_2 = in2[21] << 1;
    ap_int<32> in21_g_2 = in2[21];
    
    ap_int<32> in23_a_2 = in2[23] << 6;
    ap_int<32> in23_b_2 = in2[23] << 5;
    ap_int<32> in23_c_2 = in2[23] << 4;
    ap_int<32> in23_d_2 = in2[23] << 3;
    ap_int<32> in23_e_2 = in2[23] << 2;
    ap_int<32> in23_f_2 = in2[23] << 1;
    ap_int<32> in23_g_2 = in2[23];

    ap_int<32> in25_a_2 = in2[25] << 6;
    ap_int<32> in25_b_2 = in2[25] << 5;
    ap_int<32> in25_c_2 = in2[25] << 4;
    ap_int<32> in25_d_2 = in2[25] << 3;
    ap_int<32> in25_e_2 = in2[25] << 2;
    ap_int<32> in25_f_2 = in2[25] << 1;
    ap_int<32> in25_g_2 = in2[25];

    ap_int<32> in27_a_2 = in2[27] << 6;
    ap_int<32> in27_b_2 = in2[27] << 5;
    ap_int<32> in27_c_2 = in2[27] << 4;
    ap_int<32> in27_d_2 = in2[27] << 3;
    ap_int<32> in27_e_2 = in2[27] << 2;
    ap_int<32> in27_f_2 = in2[27] << 1;
    ap_int<32> in27_g_2 = in2[27];

    ap_int<32> in29_a_2 = in2[29] << 6;
    ap_int<32> in29_b_2 = in2[29] << 5;
    ap_int<32> in29_c_2 = in2[29] << 4;
    ap_int<32> in29_d_2 = in2[29] << 3;
    ap_int<32> in29_e_2 = in2[29] << 2;
    ap_int<32> in29_f_2 = in2[29] << 1;
    ap_int<32> in29_g_2 = in2[29];

    ap_int<32> in31_a_2 = in2[31] << 6;
    ap_int<32> in31_b_2 = in2[31] << 5;
    ap_int<32> in31_c_2 = in2[31] << 4;
    ap_int<32> in31_d_2 = in2[31] << 3;
    ap_int<32> in31_e_2 = in2[31] << 2;
    ap_int<32> in31_f_2 = in2[31] << 1;
    ap_int<32> in31_g_2 = in2[31];

    /* IN1s */

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

    /* IN2s */

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

    /* for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = idct64[1][i]*in1[1] + idct64[3][i]*in1[3] + idct64[5][i]*in1[5] + idct64[7][i]*in1[7] + idct64[9][i]*in1[9] + idct64[11][i]*in1[11] + idct64[13][i]*in1[13] + idct64[15][i]*in1[15] +
            idct64[17][i]*in1[17] + idct64[19][i]*in1[19] + idct64[21][i]*in1[21] + idct64[23][i]*in1[23] + idct64[25][i]*in1[25] + idct64[27][i]*in1[27] + idct64[29][i]*in1[29] + idct64[31][i]*in1[31] +
            idct64[33][i]*in2[1] + idct64[35][i]*in2[3] + idct64[37][i]*in2[5] + idct64[39][i]*in2[7] + idct64[41][i]*in2[9] + idct64[43][i]*in2[11] + idct64[45][i]*in2[13] + idct64[47][i]*in2[15] +
            idct64[49][i]*in2[17] + idct64[51][i]*in2[19] + idct64[53][i]*in2[21] + idct64[55][i]*in2[23] + idct64[57][i]*in2[25] + idct64[59][i]*in2[27] + idct64[61][i]*in2[29] + idct64[63][i]*in2[31];
    } */

    /* for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds_1[i] = idct64[1][i]*in1_1[1] + idct64[3][i]*in1_1[3] + idct64[5][i]*in1_1[5] + idct64[7][i]*in1_1[7] + idct64[9][i]*in1_1[9] + idct64[11][i]*in1_1[11] + idct64[13][i]*in1_1[13] + idct64[15][i]*in1_1[15] +
            idct64[17][i]*in1_1[17] + idct64[19][i]*in1_1[19] + idct64[21][i]*in1_1[21] + idct64[23][i]*in1_1[23] + idct64[25][i]*in1_1[25] + idct64[27][i]*in1_1[27] + idct64[29][i]*in1_1[29] + idct64[31][i]*in1_1[31] +
            idct64[33][i]*in2_1[1] + idct64[35][i]*in2_1[3] + idct64[37][i]*in2_1[5] + idct64[39][i]*in2_1[7] + idct64[41][i]*in2_1[9] + idct64[43][i]*in2_1[11] + idct64[45][i]*in2_1[13] + idct64[47][i]*in2_1[15] +
            idct64[49][i]*in2_1[17] + idct64[51][i]*in2_1[19] + idct64[53][i]*in2_1[21] + idct64[55][i]*in2_1[23] + idct64[57][i]*in2_1[25] + idct64[59][i]*in2_1[27] + idct64[61][i]*in2_1[29] + idct64[63][i]*in2_1[31];
    }

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds_2[i] = idct64[1][i]*in1_2[1] + idct64[3][i]*in1_2[3] + idct64[5][i]*in1_2[5] + idct64[7][i]*in1_2[7] + idct64[9][i]*in1_2[9] + idct64[11][i]*in1_2[11] + idct64[13][i]*in1_2[13] + idct64[15][i]*in1_2[15] +
            idct64[17][i]*in1_2[17] + idct64[19][i]*in1_2[19] + idct64[21][i]*in1_2[21] + idct64[23][i]*in1_2[23] + idct64[25][i]*in1_2[25] + idct64[27][i]*in1_2[27] + idct64[29][i]*in1_2[29] + idct64[31][i]*in1_2[31] +
            idct64[33][i]*in2_2[1] + idct64[35][i]*in2_2[3] + idct64[37][i]*in2_2[5] + idct64[39][i]*in2_2[7] + idct64[41][i]*in2_2[9] + idct64[43][i]*in2_2[11] + idct64[45][i]*in2_2[13] + idct64[47][i]*in2_2[15] +
            idct64[49][i]*in2_2[17] + idct64[51][i]*in2_2[19] + idct64[53][i]*in2_2[21] + idct64[55][i]*in2_2[23] + idct64[57][i]*in2_2[25] + idct64[59][i]*in2_2[27] + idct64[61][i]*in2_2[29] + idct64[63][i]*in2_2[31];
    }

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds_3[i] = idct64[1][i]*in1_3[1] + idct64[3][i]*in1_3[3] + idct64[5][i]*in1_3[5] + idct64[7][i]*in1_3[7] + idct64[9][i]*in1_3[9] + idct64[11][i]*in1_3[11] + idct64[13][i]*in1_3[13] + idct64[15][i]*in1_3[15] +
            idct64[17][i]*in1_3[17] + idct64[19][i]*in1_3[19] + idct64[21][i]*in1_3[21] + idct64[23][i]*in1_3[23] + idct64[25][i]*in1_3[25] + idct64[27][i]*in1_3[27] + idct64[29][i]*in1_3[29] + idct64[31][i]*in1_3[31] +
            idct64[33][i]*in2_3[1] + idct64[35][i]*in2_3[3] + idct64[37][i]*in2_3[5] + idct64[39][i]*in2_3[7] + idct64[41][i]*in2_3[9] + idct64[43][i]*in2_3[11] + idct64[45][i]*in2_3[13] + idct64[47][i]*in2_3[15] +
            idct64[49][i]*in2_3[17] + idct64[51][i]*in2_3[19] + idct64[53][i]*in2_3[21] + idct64[55][i]*in2_3[23] + idct64[57][i]*in2_3[25] + idct64[59][i]*in2_3[27] + idct64[61][i]*in2_3[29] + idct64[63][i]*in2_3[31];
    }
    
    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds_4[i] = idct64[1][i]*in1_4[1] + idct64[3][i]*in1_4[3] + idct64[5][i]*in1_4[5] + idct64[7][i]*in1_4[7] + idct64[9][i]*in1_4[9] + idct64[11][i]*in1_4[11] + idct64[13][i]*in1_4[13] + idct64[15][i]*in1_4[15] +
            idct64[17][i]*in1_4[17] + idct64[19][i]*in1_4[19] + idct64[21][i]*in1_4[21] + idct64[23][i]*in1_4[23] + idct64[25][i]*in1_4[25] + idct64[27][i]*in1_4[27] + idct64[29][i]*in1_4[29] + idct64[31][i]*in1_4[31] +
            idct64[33][i]*in2_4[1] + idct64[35][i]*in2_4[3] + idct64[37][i]*in2_4[5] + idct64[39][i]*in2_4[7] + idct64[41][i]*in2_4[9] + idct64[43][i]*in2_4[11] + idct64[45][i]*in2_4[13] + idct64[47][i]*in2_4[15] +
            idct64[49][i]*in2_4[17] + idct64[51][i]*in2_4[19] + idct64[53][i]*in2_4[21] + idct64[55][i]*in2_4[23] + idct64[57][i]*in2_4[25] + idct64[59][i]*in2_4[27] + idct64[61][i]*in2_4[29] + idct64[63][i]*in2_4[31];
    }

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = odds_1[i] + odds_2[i] + odds_3[i] + odds_4[i];
    } */

    out1[0] = evens[0] + odds[0];
    out1[1] = evens[1] + odds[1];
    out1[2] = evens[2] + odds[2];
    out1[3] = evens[3] + odds[3];
    out1[4] = evens[4] + odds[4];
    out1[5] = evens[5] + odds[5];
    out1[6] = evens[6] + odds[6];
    out1[7] = evens[7] + odds[7];
    out1[8] = evens[8] + odds[8];
    out1[9] = evens[9] + odds[9];
    out1[10] = evens[10] + odds[10];
    out1[11] = evens[11] + odds[11];
    out1[12] = evens[12] + odds[12];
    out1[13] = evens[13] + odds[13];
    out1[14] = evens[14] + odds[14];
    out1[15] = evens[15] + odds[15];
    out1[16] = evens[16] + odds[16];
    out1[17] = evens[17] + odds[17];
    out1[18] = evens[18] + odds[18];
    out1[19] = evens[19] + odds[19];
    out1[20] = evens[20] + odds[20];
    out1[21] = evens[21] + odds[21];
    out1[22] = evens[22] + odds[22];
    out1[23] = evens[23] + odds[23];
    out1[24] = evens[24] + odds[24];
    out1[25] = evens[25] + odds[25];
    out1[26] = evens[26] + odds[26];
    out1[27] = evens[27] + odds[27];
    out1[28] = evens[28] + odds[28];
    out1[29] = evens[29] + odds[29];
    out1[30] = evens[30] + odds[30];
    out1[31] = evens[31] + odds[31];

    out2[0] = evens[31] - odds[31];
    out2[1] = evens[30] - odds[30];
    out2[2] = evens[29] - odds[29];
    out2[3] = evens[28] - odds[28];
    out2[4] = evens[27] - odds[27];
    out2[5] = evens[26] - odds[26];
    out2[6] = evens[25] - odds[25];
    out2[7] = evens[24] - odds[24];
    out2[8] = evens[23] - odds[23];
    out2[9] = evens[22] - odds[22];
    out2[10] = evens[21] - odds[21];
    out2[11] = evens[20] - odds[20];
    out2[12] = evens[19] - odds[19];
    out2[13] = evens[18] - odds[18];
    out2[14] = evens[17] - odds[17];
    out2[15] = evens[16] - odds[16];
    out2[16] = evens[15] - odds[15];
    out2[17] = evens[14] - odds[14];
    out2[18] = evens[13] - odds[13];
    out2[19] = evens[12] - odds[12];
    out2[20] = evens[11] - odds[11];
    out2[21] = evens[10] - odds[10];
    out2[22] = evens[9] - odds[9];
    out2[23] = evens[8] - odds[8];
    out2[24] = evens[7] - odds[7];
    out2[25] = evens[6] - odds[6];
    out2[26] = evens[5] - odds[5];
    out2[27] = evens[4] - odds[4];
    out2[28] = evens[3] - odds[3];
    out2[29] = evens[2] - odds[2];
    out2[30] = evens[1] - odds[1];
    out2[31] = evens[0] - odds[0];
}

extern "C" void IDCT2(ap_int<1024>* in, ap_int<1024>* in2, ap_int<1024>* out, ap_int<1024>* out2, int block_size, int size, int shift, int outputMinimum, int outputMaximum){
    #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=in2 offset=slave bundle=gmem1
    #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=out2 offset=slave bundle=gmem1
    #pragma HLS INTERFACE s_axilite port=block_size
    #pragma HLS INTERFACE s_axilite port=size
    #pragma HLS INTERFACE s_axilite port=shift
    #pragma HLS INTERFACE s_axilite port=outputMinimum
    #pragma HLS INTERFACE s_axilite port=outputMaximum
    #pragma HLS INTERFACE s_axilite port=return

    int add = 1 << (shift - 1);

    for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1

        ap_int<1024> in_block = in[i];
        ap_int<1024> in_block2 = in2[i];
        ap_int<1024> out_block = 0;
        ap_int<1024> out_block2 = 0;

        ap_int<32> out_data_a[32];
        #pragma HLS ARRAY_PARTITION variable=out_data_a complete dim=0
        ap_int<32> out_data_b[32];
        #pragma HLS ARRAY_PARTITION variable=out_data_b complete dim=0

        for(int j=0; j<32; j++){
            #pragma HLS UNROLL
            out_data_a[j] = 0;
            out_data_b[j] = 0;
        }

        if(block_size == 64){
            ap_int<32> in_data_1[32];
            ap_int<32> in_data_2[32];
            ap_int<32> out_data_1[32];
            ap_int<32> out_data_2[32];
            #pragma HLS ARRAY_PARTITION variable=in_data_1 complete dim=0
            #pragma HLS ARRAY_PARTITION variable=in_data_2 complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data_1 complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data_2 complete dim=0

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                in_data_1[j] = in_block.range((j+1)*32-1, j*32);
                in_data_2[j] = in_block2.range((j+1)*32-1, j*32);

            }

            IDCT2B64(in_data_1, in_data_2, out_data_1, out_data_2);

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data_1[j];
                out_data_b[j] = out_data_2[j];
            }
            //out[i] = out_block;
        }else if(block_size == 32){
            ap_int<32> in_data[32];
            ap_int<32> out_data[32];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B32(in_data, out_data);

            /* for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            //out[i] = out_block;
        }else if(block_size == 16){
            ap_int<32> in_data[16];
            ap_int<32> out_data[16];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<16; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B16(in_data, out_data);

            for(int j=0; j<16; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<16; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }else if(block_size == 8){
            ap_int<32> in_data[8];
            ap_int<32> out_data[8];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<8; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B8(in_data, out_data);

            for(int j=0; j<8; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<8; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }else if(block_size == 4){
            ap_int<32> in_data[4];
            ap_int<32> out_data[4];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<4; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B4(in_data, out_data);

            for(int j=0; j<4; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<4; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }*/

            //out[i] = out_block;
        }else{
            ap_int<32> in_data[2];
            ap_int<32> out_data[2];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<2; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B2(in_data, out_data);

            for(int j=0; j<2; j++){
                #pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<2; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }

        for(int j=0; j<32; j++){
            #pragma HLS UNROLL
            ap_int<32> tmp1 = CLIP3(((out_data_a[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            ap_int<32> tmp2 = CLIP3(((out_data_b[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            out_block.range((j+1)*32-1, j*32) = tmp1.range(31, 0);
            out_block2.range((j+1)*32-1, j*32) = tmp2.range(31, 0);
        }

       /*  out_block = out_block >> shift;
        out_block2 = out_block2 >> shift; */

        /* for(int j=0; j<32; j++){
            #pragma HLS UNROLL
            out_block2.range((j+1)*32-1, j*32) =  CLIP3(((out_data[j+32]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
        } */
        out[i] = out_block;
        out2[i] = out_block2;
    }
}
