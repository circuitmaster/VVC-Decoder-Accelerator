#include <iostream>
#include "ap_int.h"
#include "ap_fixed.h"
#include "transform_coeffs.h"

ap_int<32> CLIP3(ap_int<32> x, ap_int<32> outputMinimum, ap_int<32> outputMaximum){
    //#pragma HLS inline
    if(x < outputMinimum) return outputMinimum;
    if(x > outputMaximum) return outputMaximum;
    return x;
}

void IDCT2B2(ap_int<32> in[2], ap_int<32> out[2]){
    //#pragma HLS inline off

    ap_int<32> sum = in[0] + in[1];
    ap_int<32> diff = in[0] - in[1];

    ap_int<32> even = sum << 6;
    ap_int<32> odd = diff << 6;

    out[0] = even;
    out[1] = odd;
}

void IDCT2B4(ap_int<32> in[4], ap_int<32> out[4]){
    //#pragma HLS inline off

    ap_int<32> evens[2];
    ap_int<32> odds[2];
    //#pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    //#pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[2];
    //#pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
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
    //#pragma HLS inline off

    ap_int<32> evens[4];
    ap_int<32> odds[4];
    //#pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    //#pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[4];
    //#pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
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

    // print output
    /* for(int i=0; i<8; i++){
        //#pragma HLS UNROLL
        std::cout << "Output " << i << ": " << out[i] << std::endl;
    } */
}

void IDCT2B8_eff(ap_int<32> in[8], ap_int<32> out[8]){
    //#pragma HLS inline off

    ap_int<32> evens[4];
    ap_int<32> odds[4];
    //#pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    //#pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[4];
    //#pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
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

    // print output
    for(int i=0; i<8; i++){
        //#pragma HLS UNROLL
        std::cout << "Output " << i << ": " << out[i] << std::endl;
    }
}

void IDCT2B16(ap_int<32> in[16], ap_int<32> out[16]){
    //#pragma HLS inline off

    ap_int<32> evens[8];
    ap_int<32> odds[8];
    //#pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    //#pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[8];
    //#pragma HLS ARRAY_PARTITION variable=inputs complete dim=0
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
        //#pragma HLS UNROLL
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
    //#pragma HLS inline off

    ap_int<32> evens[16];
    ap_int<32> odds[16];
    //#pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    //#pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[16];
    //#pragma HLS ARRAY_PARTITION variable=inputs complete dim=0

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
        //#pragma HLS UNROLL
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

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = idct64[1][i]*in1[1] + idct64[3][i]*in1[3] + idct64[5][i]*in1[5] + idct64[7][i]*in1[7] + idct64[9][i]*in1[9] + idct64[11][i]*in1[11] + idct64[13][i]*in1[13] + idct64[15][i]*in1[15] +
            idct64[17][i]*in1[17] + idct64[19][i]*in1[19] + idct64[21][i]*in1[21] + idct64[23][i]*in1[23] + idct64[25][i]*in1[25] + idct64[27][i]*in1[27] + idct64[29][i]*in1[29] + idct64[31][i]*in1[31] +
            idct64[33][i]*in2[1] + idct64[35][i]*in2[3] + idct64[37][i]*in2[5] + idct64[39][i]*in2[7] + idct64[41][i]*in2[9] + idct64[43][i]*in2[11] + idct64[45][i]*in2[13] + idct64[47][i]*in2[15] +
            idct64[49][i]*in2[17] + idct64[51][i]*in2[19] + idct64[53][i]*in2[21] + idct64[55][i]*in2[23] + idct64[57][i]*in2[25] + idct64[59][i]*in2[27] + idct64[61][i]*in2[29] + idct64[63][i]*in2[31];
    }

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
    //#pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0
    //#pragma HLS INTERFACE m_axi port=in2 offset=slave bundle=gmem1
    //#pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem0
    //#pragma HLS INTERFACE m_axi port=out2 offset=slave bundle=gmem1
    //#pragma HLS INTERFACE s_axilite port=block_size
    //#pragma HLS INTERFACE s_axilite port=size
    //#pragma HLS INTERFACE s_axilite port=shift
    //#pragma HLS INTERFACE s_axilite port=outputMinimum
    //#pragma HLS INTERFACE s_axilite port=outputMaximum
    //#pragma HLS INTERFACE s_axilite port=return

    int add = 1 << (shift - 1);

    for(int i=0; i<size; i++){
        //#pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        //#pragma HLS PIPELINE II=1

        ap_int<1024> in_block = in[i];
        ap_int<1024> in_block2 = in2[i];
        ap_int<1024> out_block = 0;
        ap_int<1024> out_block2 = 0;

        ap_int<32> out_data_a[32];
        //#pragma HLS ARRAY_PARTITION variable=out_data_a complete dim=0
        ap_int<32> out_data_b[32];
        //#pragma HLS ARRAY_PARTITION variable=out_data_b complete dim=0

        for(int j=0; j<32; j++){
            //#pragma HLS UNROLL
            out_data_a[j] = 0;
            out_data_b[j] = 0;
        }

        if(block_size == 64){
            ap_int<32> in_data_1[32];
            ap_int<32> in_data_2[32];
            ap_int<32> out_data_1[32];
            ap_int<32> out_data_2[32];
            //#pragma HLS ARRAY_PARTITION variable=in_data_1 complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=in_data_2 complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data_1 complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data_2 complete dim=0

            for(int j=0; j<32; j++){
                //#pragma HLS UNROLL
                in_data_1[j] = in_block.range((j+1)*32-1, j*32);
                in_data_2[j] = in_block2.range((j+1)*32-1, j*32);

            }

            IDCT2B64(in_data_1, in_data_2, out_data_1, out_data_2);

            for(int j=0; j<32; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data_1[j];
                out_data_b[j] = out_data_2[j];
            }
            //out[i] = out_block;
        }else if(block_size == 32){
            ap_int<32> in_data[32];
            ap_int<32> out_data[32];
            //#pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<32; j++){
                //#pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B32(in_data, out_data);

            for(int j=0; j<32; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            //out[i] = out_block;
        }else if(block_size == 16){
            ap_int<32> in_data[16];
            ap_int<32> out_data[16];
            //#pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<16; j++){
                //#pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B16(in_data, out_data);

            for(int j=0; j<16; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<16; j++){
                //#pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }else if(block_size == 8){
            ap_int<32> in_data[8];
            ap_int<32> out_data[8];
            //#pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<8; j++){
                //#pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
                //std::cout << "in_data[" << j << "] = " << in_data[j] << std::endl;
            }

            IDCT2B8(in_data, out_data);

            for(int j=0; j<8; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<8; j++){
                //#pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }else if(block_size == 4){
            ap_int<32> in_data[4];
            ap_int<32> out_data[4];
            //#pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<4; j++){
                //#pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B4(in_data, out_data);

            for(int j=0; j<4; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<4; j++){
                //#pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }*/

            //out[i] = out_block;
        }else{
            ap_int<32> in_data[2];
            ap_int<32> out_data[2];
            //#pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            //#pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<2; j++){
                //#pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            IDCT2B2(in_data, out_data);

            for(int j=0; j<2; j++){
                //#pragma HLS UNROLL
                out_data_a[j] = out_data[j];
            }

            /* for(int j=0; j<2; j++){
                //#pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            } */

            //out[i] = out_block;
        }

        for(int j=0; j<32; j++){
            //#pragma HLS UNROLL
            ap_int<32> tmp1 = CLIP3(((out_data_a[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            ap_int<32> tmp2 = CLIP3(((out_data_b[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            //std::cout << "out_data_a[" << j << "] = " << out_data_a[j] << ", tmp1 = " << tmp1 << std::endl;
            out_block.range((j+1)*32-1, j*32) = tmp1.range(31, 0);
            out_block2.range((j+1)*32-1, j*32) = tmp2.range(31, 0);
        }

       /*  out_block = out_block >> shift;
        out_block2 = out_block2 >> shift; */

        /* for(int j=0; j<32; j++){
            //#pragma HLS UNROLL
            out_block2.range((j+1)*32-1, j*32) =  CLIP3(((out_data[j+32]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
        } */
        out[i] = out_block;
        out2[i] = out_block2;
    }
}
