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

void INV_MATMUL_8(const ap_int<32> src[8], ap_int<32> dst[8], ap_int<32> shift,
                ap_int<32> skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const ap_int<8> m[8][8]) {
    #pragma HLS inline off

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);
    const ap_int<32> cutoff      = 8 - skipInLines;

    //for (ap_int<32> i = 0; i < reducedLine; i++) {
    for (ap_int<32> j = 0; j < 8; j++) {
        //#pragma HLS UNROLL
        #pragma HLS PIPELINE 
        ap_int<32> sum = 0;
        for (ap_int<32> k = 0; k < 8; k++) {
            //#pragma HLS UNROLL
            //#pragma HLS PIPELINE 

            if(k< cutoff){
                sum += src[k] * m[k][j];
            }
            //sum += ap_int<32>(src[k * numOutLines]) * ap_int<32>(m[k * 8 + j]);
        }
        ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
        dst[j] = CLIP3(outputMinimum, outputMaximum, scaled);
    }
}

void INV_MATMUL_16(const ap_int<32> src[16], ap_int<32> dst[16], ap_int<32> shift,
                ap_int<32> skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const ap_int<8> m[16][16]) {
    #pragma HLS inline off

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);
    const ap_int<32> cutoff      = 16 - skipInLines;

    //for (ap_int<32> i = 0; i < reducedLine; i++) {
    for (ap_int<32> j = 0; j < 16; j++) {
        //#pragma HLS UNROLL
        #pragma HLS PIPELINE 

        ap_int<32> sum = 0;
        for (ap_int<32> k = 0; k < 16; k++) {
            //#pragma HLS UNROLL
            //#pragma HLS PIPELINE 

            if(k< cutoff){
                sum += src[k] * m[k][j];
            }
            //sum += ap_int<32>(src[k * numOutLines]) * ap_int<32>(m[k * 8 + j]);
        }
        ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
        dst[j] = CLIP3(outputMinimum, outputMaximum, scaled);
    }
}

void INV_MATMUL_32(const ap_int<32> src[32], ap_int<32> dst[32], ap_int<32> shift,
                ap_int<32> skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const ap_int<8> m[32][32]) {
    #pragma HLS inline off

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);
    const ap_int<32> cutoff      = 32 - skipInLines;
    //for (ap_int<32> i = 0; i < reducedLine; i++) {
    for (ap_int<32> j = 0; j < 32; j++) {
        //#pragma HLS UNROLL
        #pragma HLS PIPELINE 

        ap_int<32> sum = 0;
        for (ap_int<32> k = 0; k < 32; k++) {
            //#pragma HLS UNROLL
            //#pragma HLS PIPELINE 

            if(k< cutoff){
                sum += src[k] * m[k][j];
            }
            //sum += ap_int<32>(src[k * numOutLines]) * ap_int<32>(m[k * 8 + j]);
        }
        ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
        dst[j] = CLIP3(outputMinimum, outputMaximum, scaled);
    }
}

/* void INV_MATMUL(const ap_int<32> src[32], ap_int<32> dst[32], ap_int<32> shift,
                ap_int<32> skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const ap_int<32> m[32][32], int block_size) {
    #pragma HLS inline off

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);
    const ap_int<32> cutoff      = block_size - skipInLines;
    //for (ap_int<32> i = 0; i < reducedLine; i++) {
    for (ap_int<32> j = 0; j < block_size; j++) {
        #pragma HLS loop_tripcount min=8 max=32
        //#pragma HLS UNROLL
        #pragma HLS PIPELINE 

        ap_int<32> sum = 0;
        for (ap_int<32> k = 0; k < 32; k++) {
            //#pragma HLS UNROLL
            //#pragma HLS PIPELINE 

            if(k < cutoff){
                sum += src[k] * m[k][j];
            }
            //sum += ap_int<32>(src[k * numOutLines]) * ap_int<32>(m[k * 8 + j]);
        }
        ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
        dst[j] = CLIP3(outputMinimum, outputMaximum, scaled);
    }
} */


/* void IDCT8B4(ap_int<32> src[4], ap_int<32> dst[4], ap_int<32> shift, const ap_int<32> oMin, const ap_int<32> oMax) {
    ap_int<32> i;
    ap_int<32> rnd_factor = ap_int<32>(1) << (shift - 1);

    ap_int<32> c[4];
    //const ap_int<32>* reducedLine = line - skipLine;

    //for (i = 0; i < reducedLine; i++) {
    //#pragma HLS UNROLL
    c[0] = src[0] + src[3];
    c[1] = src[2] + src[0];
    c[2] = src[3] - src[2];
    c[3] = 74 * src[1];

    dst[0] = CLIP3(oMin, oMax, (29*c[0] + 55*c[1] + c[3] + rnd_factor) >> shift);
    dst[1] = CLIP3(oMin, oMax, (74*c[3] + (src[0] - src[2] - src[3]) + rnd_factor) >> shift);
    dst[2] = CLIP3(oMin, oMax, (29*c[0] - 55*c[1] - c[3] + rnd_factor) >> shift);
    dst[3] = CLIP3(oMin, oMax, (29*c[3] - 55*c[2] - c[3] + rnd_factor) >> shift);
    //}
}

void IDST7B4(ap_int<32> src[4], ap_int<32> dst[4], ap_int<32> shift, const ap_int<32> oMin, const ap_int<32> oMax) {
    ap_int<32> i;
    ap_int<32> rnd_factor = ap_int<32>(1) << (shift - 1);

    ap_int<32> c[4];
    //const ap_int<32>* reducedLine = line - skipLine;

    //for (i = 0; i < reducedLine; i++) {
    //#pragma HLS UNROLL    
    c[0] = src[0] + src[3];
    c[1] = src[2] + src[0];
    c[2] = src[3] - src[2];
    c[3] = 74 * src[1];

    dst[0] = CLIP3(oMin, oMax, (29*c[0] + 55*c[1] + c[3] + rnd_factor) >> shift);
    dst[1] = CLIP3(oMin, oMax, (55*c[3] - 55*c[1] + c[3] + rnd_factor) >> shift);
    dst[2] = CLIP3(oMin, oMax, (29* (src[0] - src[2] + src[3]) + rnd_factor) >> shift);
    dst[3] = CLIP3(oMin, oMax, (55*c[3] - 29*c[2] - c[3] + rnd_factor) >> shift);
    //}
}
 */

void ICOMB4(ap_int<32> src[4], ap_int<32> dst[4], ap_int<32> shift, const ap_int<32> oMin, const ap_int<32> oMax, const ap_uint<1> selector) {
    ap_int<32> i;
    ap_int<32> rnd_factor = ap_int<32>(1) << (shift - 1);

    ap_int<32> c[4];
    //const ap_int<32>* reducedLine = line - skipLine;

    //for (i = 0; i < reducedLine; i++) {
    //#pragma HLS UNROLL

    ap_int<32> x, y, z, t;

    if (selector == 0) {
        c[0] = src[0] + src[3];
        c[1] = src[2] + src[0];
        c[2] = src[3] - src[2];
        c[3] = 74 * src[1];

        x = (29*c[0] + 55*c[1] + c[3] + rnd_factor) >> shift;
        y = (74*c[3] + (src[0] - src[2] - src[3]) + rnd_factor) >> shift;
        z = (29*c[0] - 55*c[1] - c[3] + rnd_factor) >> shift;
        t = (29*c[3] - 55*c[2] - c[3] + rnd_factor) >> shift;
    } 
    
    else {
        c[0] = src[0] + src[3];
        c[1] = src[2] + src[0];
        c[2] = src[3] - src[2];
        c[3] = 74 * src[1];

        x = (29*c[0] + 55*c[1] + c[3] + rnd_factor) >> shift;
        y = (55*c[3] - 55*c[1] + c[3] + rnd_factor) >> shift;
        z = (29* (src[0] - src[2] + src[3]) + rnd_factor) >> shift;
        t = (55*c[3] - 29*c[2] - c[3] + rnd_factor) >> shift;
    }

    dst[0] = CLIP3(oMin, oMax, x);
    dst[1] = CLIP3(oMin, oMax, y);
    dst[2] = CLIP3(oMin, oMax, z);
    dst[3] = CLIP3(oMin, oMax, t);
}



void ICOMB8(ap_int<32> src[8], ap_int<32> dst[8], ap_int<32> shift,  ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax, const ap_uint<1> selector) {
    if (selector == 0) {
        INV_MATMUL_8(src, dst, shift, skipLine2, oMin, oMax, idct8_8);
    } else {
        INV_MATMUL_8(src, dst, shift, skipLine2, oMin, oMax, idst7_8);
    }
}

void ICOMB16(ap_int<32> src[16], ap_int<32> dst[16], ap_int<32> shift,  ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax, const ap_uint<1> selector) {
    if (selector == 0) {
        INV_MATMUL_16(src, dst, shift, skipLine2, oMin, oMax, idct8_16);
    } else {
        INV_MATMUL_16(src, dst, shift, skipLine2, oMin, oMax, idst7_16);
    }
}

void ICOMB32(ap_int<32> src[32], ap_int<32> dst[32], ap_int<32> shift,  ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax, const ap_uint<1> selector) {
    if (selector == 0) {
        INV_MATMUL_32(src, dst, shift, skipLine2, oMin, oMax, idct8_32);
    } else {
        INV_MATMUL_32(src, dst, shift, skipLine2, oMin, oMax, idst7_32);
    }
}

/* void ICOMB16(ap_int<32> src[16], ap_int<32> dst[16], ap_int<32> shift , ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax){
    INV_MATMUL_16(src, dst, shift, skipLine2, oMin, oMax, idct8_16);
}

void IDCT8B32(ap_int<32> src[32], ap_int<32> dst[32], ap_int<32> shift, ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax){
    INV_MATMUL_32(src, dst, shift, skipLine2, oMin, oMax, idct8_32);
} */


extern "C" void IDCTComb(ap_int<1024>* in, ap_int<1024>* out, ap_int<32> block_size, ap_int<32> sIn, ap_int<32>  size, ap_int<32>  shift, ap_int<32>  oMin, ap_int<32>  oMax, ap_uint<1> selector) {
    #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem1
    #pragma HLS INTERFACE s_axilite port=in bundle=control
    #pragma HLS INTERFACE s_axilite port=out bundle=control
    #pragma HLS INTERFACE s_axilite port=block_size bundle=control
    #pragma HLS INTERFACE s_axilite port=sIn bundle=control
    #pragma HLS INTERFACE s_axilite port=selector bundle=control
    #pragma HLS INTERFACE s_axilite port=size bundle=control
    #pragma HLS INTERFACE s_axilite port=shift bundle=control
    #pragma HLS INTERFACE s_axilite port=oMin bundle=control
    #pragma HLS INTERFACE s_axilite port=oMax bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control


    for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE OFF

        ap_int<1024> in_block = in[i];
        ap_int<1024> out_block = 0;

        ap_int<32> in_data_[32];
        ap_int<32> out_data_[32];
        #pragma HLS ARRAY_PARTITION variable=in_data_ complete dim=0
        #pragma HLS ARRAY_PARTITION variable=out_data_ complete dim=0

       if(block_size == 32){
            ap_int<32> in_data[32];
            ap_int<32> out_data[32];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                in_data_[j] = in_block.range((j+1)*32-1, j*32);
            }

            ICOMB32(in_data_, out_data_, shift, sIn, oMin, oMax, selector);

            for(int j=0; j<32; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = out_data_[j];
            } 

            //out[i] = out_block;
        }
        else if(block_size == 16){
            ap_int<32> in_data[16];
            ap_int<32> out_data[16];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<16; j++){
                #pragma HLS UNROLL
                in_data_[j] = in_block.range((j+1)*32-1, j*32);
            }

            ICOMB16(in_data_, out_data_, shift, sIn, oMin, oMax, selector);

            for(int j=0; j<16; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = out_data_[j];
            }

            //out[i] = out_block;
        }else if(block_size == 8){
            ap_int<32> in_data[8];
            ap_int<32> out_data[8];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<8; j++){
                #pragma HLS UNROLL
                in_data_[j] = in_block.range((j+1)*32-1, j*32);
            }

            ICOMB8(in_data_, out_data_, shift, sIn, oMin, oMax, selector);

            for(int j=0; j<8; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = out_data_[j];
            } 

            //out[i] = out_block;
        }
        else if(block_size == 4){
            ap_int<32> in_data[4];
            ap_int<32> out_data[4];
            #pragma HLS ARRAY_PARTITION variable=in_data complete dim=0
            #pragma HLS ARRAY_PARTITION variable=out_data complete dim=0

            for(int j=0; j<4; j++){
                #pragma HLS UNROLL
                in_data[j] = in_block.range((j+1)*32-1, j*32);
            }

            ICOMB4(in_data, out_data, shift, oMin, oMax, selector);

            for(int j=0; j<4; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = out_data[j];
            }

            //out[i] = out_block;
        }
        out[i] = out_block;
    }
}
