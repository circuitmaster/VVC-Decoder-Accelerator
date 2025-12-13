#include <iostream>
#include "ap_int.h"
#include "ap_fixed.h"
#include "transform_coeffs.h"

int CLIP3(ap_int<32> outputMinimum, ap_int<32> outputMaximum, ap_int<32> x){
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
    inputs[3] = in[4];
    inputs[7] = in[12];
    inputs[1] = in[2];
    inputs[2] = in[6];
    inputs[5] = in[10];
    inputs[6] = in[14];

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

void IDCT2B64(ap_int<32> in[64], ap_int<32> out[64]){
    #pragma HLS inline off

    ap_int<32> evens[32];
    ap_int<32> odds[32];
    #pragma HLS ARRAY_PARTITION variable=evens complete dim=0
    #pragma HLS ARRAY_PARTITION variable=odds complete dim=0

    ap_int<32> inputs[32];
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

    for(int i=0; i<32; i++){
        #pragma HLS UNROLL
        odds[i] = idct64[1][i]*in[1] + idct64[3][i]*in[3] + idct64[5][i]*in[5] + idct64[7][i]*in[7] + idct64[9][i]*in[9] + idct64[11][i]*in[11] + idct64[13][i]*in[13] + idct64[15][i]*in[15] +
            idct64[17][i]*in[17] + idct64[19][i]*in[19] + idct64[21][i]*in[21] + idct64[23][i]*in[23] + idct64[25][i]*in[25] + idct64[27][i]*in[27] + idct64[29][i]*in[29] + idct64[31][i]*in[31] +
            idct64[33][i]*in[33] + idct64[35][i]*in[35] + idct64[37][i]*in[37] + idct64[39][i]*in[39] + idct64[41][i]*in[41] + idct64[43][i]*in[43] + idct64[45][i]*in[45] + idct64[47][i]*in[47] +
            idct64[49][i]*in[49] + idct64[51][i]*in[51] + idct64[53][i]*in[53] + idct64[55][i]*in[55] + idct64[57][i]*in[57] + idct64[59][i]*in[59] + idct64[61][i]*in[61] + idct64[63][i]*in[63];
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

        if(block_size == 64){
            ap_int<32> in_data[64];
            ap_int<32> out_data[64];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                in_data[j+32] = in_block2.range((j+1)*32-1, j*32);
            }

            IDCT2B64(in_data, out_data);

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) =  CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_block2.range((j+1)*32-1, j*32) =  CLIP3(((out_data[j+32]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
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

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
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
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }

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
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }

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
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }

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
                out_block.range((j+1)*32-1, j*32) = CLIP3(((out_data[j]+add) >> shift), ap_int<32>(outputMinimum), ap_int<32>(outputMaximum));
            }

            //out[i] = out_block;
        }
        out[i] = out_block;
        out2[i] = out_block2;
    }
}
