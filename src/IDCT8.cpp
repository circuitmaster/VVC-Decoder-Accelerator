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

void INV_MATMUL_8(const ap_int<32> src[8], ap_int<32> dst[8], int shift, int numOutLines, int skipOutLines,
                int skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const int m[8]) {
    #pragma HLS inline

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);

    const ap_int<32> reducedLine = numOutLines - skipOutLines;
    const ap_int<32> cutoff      = 8 - skipInLines;

    for (ap_int<32> i = 0; i < reducedLine; i++) {
        for (ap_int<32> j = 0; j < 8; j++) {
            #pragma HLS UNROLL
            ap_int<32> sum = 0;
            for (ap_int<32> k = 0; k < cutoff; k++) {
                #pragma HLS UNROLL
                sum += ap_int<32>(src[k * numOutLines + i]) * ap_int<32>(m[k * 8 + j]);
            }
            ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
            dst[i * 8 + j] = CLIP3(outputMinimum, outputMaximum, scaled);
        }
    }

    if (skipOutLines > 0) {
        const ap_int<32> start = reducedLine * 8;
        const ap_int<32> count = skipOutLines * 8;
        for (ap_int<32> idx = 0; idx < count; idx++) {
            dst[start + idx] = 0;
        }
    }
}

void INV_MATMUL_16(const ap_int<32> src[16], ap_int<32> dst[16], int shift, int numOutLines, int skipOutLines,
                int skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const int m[16]) {
    #pragma HLS inline

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);

    const ap_int<32> reducedLine = numOutLines - skipOutLines;
    const ap_int<32> cutoff      = 16 - skipInLines;

    for (ap_int<32> i = 0; i < reducedLine; i++) {
        for (ap_int<32> j = 0; j < 16; j++) {
            #pragma HLS UNROLL
            ap_int<32> sum = 0;
            for (ap_int<32> k = 0; k < cutoff; k++) {
                #pragma HLS UNROLL
                sum += ap_int<32>(src[k * numOutLines + i]) * ap_int<32>(m[k * 16 + j]);
            }
            ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
            dst[i * 16 + j] = CLIP3(outputMinimum, outputMaximum, scaled);
        }
    }

    if (skipOutLines > 0) {
        const ap_int<32> start = reducedLine * 16;
        const ap_int<32> count = skipOutLines * 16;
        for (ap_int<32> idx = 0; idx < count; idx++) {
            dst[start + idx] = 0;
        }
    }
}

void INV_MATMUL_32(const ap_int<32> src[32], ap_int<32> dst[32], int shift, int numOutLines, int skipOutLines,
                int skipInLines, ap_int<32> outputMinimum, ap_int<32> outputMaximum, const int m[32]) {
    #pragma HLS inline

    const ap_int<32> rndFactor = ap_int<32>(1) << (shift - 1);

    const ap_int<32> reducedLine = numOutLines - skipOutLines;
    const ap_int<32> cutoff      = 32 - skipInLines;

    for (ap_int<32> i = 0; i < reducedLine; i++) {
        for (ap_int<32> j = 0; j < 32; j++) {
            #pragma HLS UNROLL
            ap_int<32> sum = 0;
            for (ap_int<32> k = 0; k < cutoff; k++) {
                #pragma HLS UNROLL
                sum += ap_int<32>(src[k * numOutLines + i]) * ap_int<32>(m[k * 32 + j]);
            }
            ap_int<32> scaled = (ap_int<32>)((sum + rndFactor) >> shift);
            dst[i * 32 + j] = CLIP3(outputMinimum, outputMaximum, scaled);
        }
    }

    if (skipOutLines > 0) {
        const ap_int<32> start = reducedLine * 32;
        const ap_int<32> count = skipOutLines * 32;
        for (ap_int<32> idx = 0; idx < count; idx++) {
            dst[start + idx] = 0;
        }
    }
}


void IDCT8B4(ap_int<32> src[4], ap_int<32> dst[4], ap_int<32> shift, ap_int<32> line, ap_int<32> skipLine, ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax) {
    ap_int<32> i;
    ap_int<32> rnd_factor = ap_int<32>(1) << (shift - 1);

    ap_int<32> c[4];
    const ap_int<32>* reducedLine = line - skipLine;

    for (i = 0; i < reducedLine; i++) {
        #pragma HLS UNROLL
        c[0] = src[0*line] + src[3*line];
        c[1] = src[2*line] + src[0*line];
        c[2] = src[3*line] - src[2*line];
        c[3] = 74 * src[1*line];

        dst[0] = CLIP3(oMin, oMax, (29*c[0] + 55*c[1] + c[3] + rnd_factor) >> shift);
        dst[1] = CLIP3(oMin, oMax, (74*c[3] + (src[0*line] - src[2*line] - src[3*line]) + rnd_factor) >> shift);
        dst[2] = CLIP3(oMin, oMax, (29*c[0] - 55*c[1] - c[3] + rnd_factor) >> shift);
        dst[3] = CLIP3(oMin, oMax, (29*c[3] - 55*c[2] - c[3] + rnd_factor) >> shift);
    }
}

void IDCT8B8(ap_int<32> src[8], ap_int<32> dst[8], ap_int<32> shift, ap_int<32> line, ap_int<32> skipLine, ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax) {
    INV_MATMUL_8(src, dst, shift, line, skipLine, skipLine2, oMin, oMax, icdt_8_8_coeffs);
}

void IDCT8B16(ap_int<32> src[16], ap_int<32> dst[16], ap_int<32> shift, ap_int<32> line, ap_int<32> skipLine, ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax){
    ap_int<32> j;
    ap_int<32> k;
    ap_int<32> t;
    ap_int<32> a[5];
    ap_int<32> b[5];
    ap_int<32> c[5];
    ap_int<32> d[5];

    ap_int<32> add = (shift>0) ? ap_int<32>(1) << (shift-1) : 0;
    const ap_int<32> reducedLine = line - skipLine;

    for (j = 0; j< reducedLine ; j ++) {
        for (k = 0; k < 5; k++) {
            #pragma HLS UNROLL
            a[k] = src[(15-k)*line] + src[(4-k)*line] ;
            b[k] = src[(6-k)*line] + src[(4-k)*line] ;
            c[k] = src[(15-k)*line] - src[(6-k)*line] ;
            d[k] = src[(15-k)*line] + src[(6-k)*line] - src[(4-k)*line] ;
        }
        t =  ap_int<32>( 48 * src[ 5*line ] ) ;

        dst[ 1 ] = CLIP3( oMin, oMax, ( -87*d[0] -77*d[1] -62*d[2] -40*d[3] -17*d[4] +add ) >> shift ) ;
        dst[ 4 ] = CLIP3( oMin, oMax, ( 62*d[0] +17*d[1] + 77*d[2] -87*d[3] -40*d[4] +add  ) >> shift ) ;
        dst[ 7 ] = CLIP3( oMin, oMax, ( -17*d[0] -87*d[1] +40*d[2] + 77*d[3] -62*d[4] +add  ) >> shift ) ;
        dst[ 10 ] = CLIP3( oMin, oMax, ( 40*d[0] -62*d[1] -87*d[2] +17*d[3] -77*d[4] +add  ) >> shift ) ;
        dst[ 13 ] = CLIP3( oMin, oMax, ( -77*d[0] +40*d[1] -17*d[2] +62*d[3] -87*d[4] +add  ) >> shift ) ;
        dst[ 5 ] = CLIP3( oMin, oMax, ( -48*(src[15] + src[14] - src[12] - src[11] + src[9] + src[8] - src[6] - src[5] + src[3] + src[2] - src[0]) + add ) >> shift ) ;

        dst[ 0 ] = CLIP3( oMin, oMax, ( 88*a[0] + 55*b[0] + 88*a[1] + 62*b[1] + 87*a[2] + 68*b[2] + 85*a[3] + 73*b[3] + 81*a[4] + 77*b[4] + t + add) >> shift ) ;
        dst[ 2 ] = CLIP3( oMin, oMax, ( 81*c[0] - 77*b[0] + 55*c[1] - 88*b[1] + 73*c[2] + 85*a[2] + 88*c[3] + 62*a[3] + 68*a[4] + 87*b[4] - t + add) >> shift ) ;
        dst[ 3 ] = CLIP3( oMin, oMax, ( - 73*a[0] - 85*b[0] - 87*c[1] - 68*a[1] - 55*c[2] - 88*a[2] - 81*c[3] + 77*b[3] + 88*a[4] + 62*b[4] - t + add) >> shift ) ;
        dst[ 6 ] = CLIP3( oMin, oMax, ( 62*a[0] + 88*c[0] + 73*c[1] - 85*b[1] - 77*a[2] - 81*b[2] - 68*c[3] - 87*a[3] - 88*c[4] + 55*b[4] + t + add) >> shift ) ;
        dst[ 8 ] = CLIP3( oMin, oMax, ( 81*c[0] + 77*a[0] - 88*c[1] + 55*b[1] - 85*c[2] - 73*a[2] + 88*c[3] - 62*b[3] + 87*c[4] + 68*a[4] - t + add) >> shift ) ;
        dst[ 9 ] = CLIP3( oMin, oMax, ( - 68*c[0] - 87*a[0] + 81*a[1] + 77*b[1] + 62*c[2] - 88*b[2] - 55*a[3] - 88*b[3] - 85*c[4] + 73*b[4] - t + add) >> shift ) ;
        dst[ 11 ] = CLIP3( oMin, oMax, ( - 55*a[0] - 88*b[0] + 62*c[1] + 88*a[1] - 87*c[2] + 68*b[2] - 73*a[3] - 85*b[3] + 77*c[4] + 81*a[4] + t + add) >> shift ) ;
        dst[ 12 ] = CLIP3( oMin, oMax, ( 68*c[0] - 87*b[0] - 77*c[1] - 81*a[1] + 62*a[2] + 88*b[2] - 88*a[3] - 55*b[3] - 73*c[4] + 85*b[4] + t + add ) >> shift ) ;
        dst[ 14 ] = CLIP3( oMin, oMax, ( 85*a[0] + 73*b[0] - 68*a[1] - 87*b[1] + 88*c[2] + 55*a[2] - 81*c[3] - 77*a[3] + 62*c[4] + 88*a[4] - t + add ) >> shift ) ;
        dst[ 15 ] = CLIP3( oMin, oMax, ( - 88*c[0] + 62*b[0] + 85*c[1] - 73*b[1] - 77*c[2] + 81*b[2] + 68*c[3] - 87*b[3] - 55*c[4] + 88*b[4] - t + add) >> shift ) ;
    }
}

void IDCT8B32(ap_int<32> src[32], ap_int<32> dst[32], ap_int<32> shift, ap_int<32> line, ap_int<32> skipLine, ap_int<32> skipLine2, const ap_int<32> oMin, const ap_int<32> oMax){
    ap_int<32> j;
    ap_int<32> k;

    ap_int<32> a[10][6];
    ap_int<32> t[2];
    ap_int<32> b[6];
    ap_int<32> c[2];

    ap_int<32> add = (shift>0) ? ap_int<32>(1) << (shift-1) : 0;
    const ap_int<32> reducedLine = line - skipLine;

    for (j = 0; j< reducedLine ; j ++) {
        for (k = 0; k < 6; k++) {
            #pragma HLS UNROLL
            a[0][k] = src[(31 - k)*line] - src[(20 + k)*line];
            a[1][k] = src[(31 - k)*line] + src[(18 - k)*line];
            a[2][k] = src[(31 - k)*line] + src[(7 + k)*line];
            a[3][k] = src[(31 - k)*line] - src[(5 - k)*line];
            a[4][k] = src[(25 - k)*line] + src[(13 + k)*line];
            a[5][k] = src[(25 - k)*line] + src[(12 - k)*line];
            a[6][k] = src[(25 - k)*line] - src[k*line];
            a[7][k] = src[(18 - k)*line] - src[(7 + k)*line];
            a[8][k] = src[(18 - k)*line] + src[(5 - k)*line];
            a[9][k] = src[(12 - k)*line] + src[k*line];

            b[k] = src[(31 - k)*line] + src[(20 + k)*line] - src[(18 - k)*line] - src[(7 + k)*line] + src[(5 - k)*line];
            
        }
        for (k = 0; k < 2; k++) {
            #pragma HLS UNROLL
            c[k] = src[(31 - k)*line] + src[(28 + k)*line] - src[(26 - k)*line] - src[(23 + k)*line] + src[(21 - k)*line] + src[(18 + k)*line] - src[(16 - k)*line] - src[(13 + k)*line] + src[(11 - k)*line] + src[(8 + k)*line] - src[(6 - k)*line] - src[(3 + k)*line] + src[(1 - k)*line];
        }

        t[0] = 74 * src[19 * line] + 30 * src[ 6 * line];
        t[1] = 74 * src[ 6 * line] - 30 * src[19 * line];

    //Todo: Place coeffs
    dst[ 0] = CLIP3(oMin, oMax, (   iT[0] * a[3][0] + iT[11] * a[6][5] + iT[13] * a[8][0] + iT[24] * a[9][5] + iT[1] * a[3][1] + iT[10] * a[6][4] + iT[14] * a[8][1] + iT[23] * a[9][4] + iT[2] * a[3][2] + iT[9] * a[6][3] + iT[15] * a[8][2] + iT[22] * a[9][3] + iT[3] * a[3][3] + iT[8] * a[6][2] + iT[16] * a[8][3] + iT[21] * a[9][2] + iT[4] * a[3][4] + iT[7] * a[6][1] + iT[17] * a[8][4] + iT[20] * a[9][1] + iT[5] * a[3][5] + iT[6] * a[6][0] + iT[18] * a[8][5] + iT[19] * a[9][0] + t[0] + add) >> shift);
    dst[ 1] = CLIP3(oMin, oMax, (   iT[0] * a[5][2] - iT[11] * a[0][3] - iT[13] * a[4][2] - iT[24] * a[6][2] - iT[1] * a[9][1] - iT[10] * a[8][4] - iT[14] * a[3][4] - iT[23] * a[6][1] - iT[2] * a[0][0] + iT[9] * a[5][5] - iT[15] * a[6][5] - iT[22] * a[4][5] + iT[3] * a[5][3] - iT[8] * a[0][2] - iT[16] * a[4][3] - iT[21] * a[6][3] - iT[4] * a[9][0] - iT[7] * a[8][5] - iT[17] * a[3][5] - iT[20] * a[6][0] - iT[5] * a[0][1] + iT[6] * a[5][4] - iT[18] * a[6][4] - iT[19] * a[4][4] + t[1] + add) >> shift);
    dst[ 3] = CLIP3(oMin, oMax, (   iT[0] * a[9][4] + iT[11] * a[5][4] - iT[13] * a[2][1] + iT[24] * a[7][1] + iT[1] * a[0][3] + iT[10] * a[1][3] - iT[14] * a[3][3] - iT[23] * a[2][3] - iT[2] * a[8][5] - iT[9] * a[9][0] - iT[15] * a[6][0] - iT[22] * a[3][5] + iT[3] * a[1][4] + iT[8] * a[0][4] - iT[16] * a[2][4] - iT[21] * a[3][4] + iT[4] * a[5][3] + iT[7] * a[9][3] + iT[17] * a[7][2] - iT[20] * a[2][2] - iT[5] * a[8][0] - iT[6] * a[1][0] + iT[18] * a[4][5] + iT[19] * a[7][0] - t[1] + add) >> shift);
    dst[ 4] = CLIP3(oMin, oMax, ( - iT[0] * a[3][2] - iT[11] * a[2][2] + iT[13] * a[1][2] + iT[24] * a[0][2] + iT[1] * a[6][0] + iT[10] * a[3][5] + iT[14] * a[9][0] + iT[23] * a[8][5] - iT[2] * a[2][3] - iT[9] * a[3][3] + iT[15] * a[0][3] + iT[22] * a[1][3] - iT[3] * a[7][0] + iT[8] * a[2][0] - iT[16] * a[9][5] - iT[21] * a[5][5] + iT[4] * a[4][4] + iT[7] * a[6][4] + iT[17] * a[0][1] - iT[20] * a[5][4] - iT[5] * a[7][4] - iT[6] * a[4][1] + iT[18] * a[8][4] + iT[19] * a[1][4] - t[0] + add) >> shift);
    dst[ 5] = CLIP3(oMin, oMax, (   iT[0] * a[3][5] + iT[11] * a[6][0] + iT[13] * a[8][5] + iT[24] * a[9][0] - iT[1] * a[6][5] - iT[10] * a[3][0] - iT[14] * a[9][5] - iT[23] * a[8][0] + iT[2] * a[7][4] - iT[9] * a[2][4] + iT[15] * a[9][1] + iT[22] * a[5][1] + iT[3] * a[7][1] + iT[8] * a[4][4] - iT[16] * a[8][1] - iT[21] * a[1][1] - iT[4] * a[6][2] - iT[7] * a[4][2] + iT[17] * a[5][2] - iT[20] * a[0][3] + iT[5] * a[3][2] + iT[6] * a[2][2] - iT[18] * a[1][2] - iT[19] * a[0][2] - t[0] + add) >> shift);
    dst[ 8] = CLIP3(oMin, oMax, (   iT[0] * a[9][3] + iT[11] * a[8][2] + iT[13] * a[3][2] + iT[24] * a[6][3] + iT[1] * a[1][5] + iT[10] * a[0][5] - iT[14] * a[2][5] - iT[23] * a[3][5] - iT[2] * a[1][3] - iT[9] * a[8][3] + iT[15] * a[7][3] + iT[22] * a[4][2] - iT[3] * a[9][5] - iT[8] * a[5][5] + iT[16] * a[2][0] - iT[21] * a[7][0] - iT[4] * a[1][1] - iT[7] * a[0][1] + iT[17] * a[2][1] + iT[20] * a[3][1] + iT[5] * a[5][1] + iT[6] * a[9][1] + iT[18] * a[7][4] - iT[19] * a[2][4] + t[1] + add) >> shift);
    dst[ 9] = CLIP3(oMin, oMax, (   iT[0] * a[2][1] + iT[11] * a[3][1] - iT[13] * a[0][1] - iT[24] * a[1][1] - iT[1] * a[7][3] + iT[10] * a[2][3] - iT[14] * a[9][2] - iT[23] * a[5][2] - iT[2] * a[4][0] - iT[9] * a[7][5] + iT[15] * a[1][5] + iT[22] * a[8][5] - iT[3] * a[3][4] - iT[8] * a[2][4] + iT[16] * a[1][4] + iT[21] * a[0][4] - iT[4] * a[6][3] - iT[7] * a[3][2] - iT[17] * a[9][3] - iT[20] * a[8][2] - iT[5] * a[4][5] - iT[6] * a[6][5] - iT[18] * a[0][0] + iT[19] * a[5][5] + t[0] + add) >> shift);
    dst[10] = CLIP3(oMin, oMax, ( - iT[0] * a[6][1] - iT[11] * a[4][1] + iT[13] * a[5][1] - iT[24] * a[0][4] + iT[1] * a[2][2] - iT[10] * a[7][2] - iT[14] * a[5][3] - iT[23] * a[9][3] + iT[2] * a[6][4] + iT[9] * a[4][4] - iT[15] * a[5][4] + iT[22] * a[0][1] - iT[3] * a[2][5] + iT[8] * a[7][5] + iT[16] * a[5][0] + iT[21] * a[9][0] - iT[4] * a[7][0] - iT[7] * a[4][5] + iT[17] * a[8][0] + iT[20] * a[1][0] + iT[5] * a[4][2] + iT[6] * a[7][3] - iT[18] * a[1][3] - iT[19] * a[8][3] + t[0] + add) >> shift);
    dst[11] = CLIP3(oMin, oMax, ( - iT[0] * a[1][3] - iT[11] * a[0][3] + iT[13] * a[2][3] + iT[24] * a[3][3] - iT[1] * a[9][1] - iT[10] * a[5][1] + iT[14] * a[2][4] - iT[23] * a[7][4] - iT[2] * a[8][0] - iT[9] * a[9][5] - iT[15] * a[6][5] - iT[22] * a[3][0] + iT[3] * a[0][2] - iT[8] * a[5][3] + iT[16] * a[6][3] + iT[21] * a[4][3] + iT[4] * a[5][0] - iT[7] * a[0][5] - iT[17] * a[4][0] - iT[20] * a[6][0] + iT[5] * a[9][4] + iT[6] * a[5][4] - iT[18] * a[2][1] + iT[19] * a[7][1] + t[1] + add) >> shift);
    dst[13] = CLIP3(oMin, oMax, (   iT[0] * a[0][0] + iT[11] * a[1][0] - iT[13] * a[3][0] - iT[24] * a[2][0] + iT[1] * a[5][4] - iT[10] * a[0][1] - iT[14] * a[4][4] - iT[23] * a[6][4] - iT[2] * a[9][3] - iT[9] * a[5][3] + iT[15] * a[2][2] - iT[22] * a[7][2] + iT[3] * a[8][3] + iT[8] * a[9][2] + iT[16] * a[6][2] + iT[21] * a[3][3] - iT[4] * a[1][4] - iT[7] * a[8][4] + iT[17] * a[7][4] + iT[20] * a[4][1] + iT[5] * a[0][5] + iT[6] * a[1][5] - iT[18] * a[3][5] - iT[19] * a[2][5] - t[1] + add) >> shift);
    dst[14] = CLIP3(oMin, oMax, (   iT[0] * a[4][2] + iT[11] * a[7][3] - iT[13] * a[1][3] - iT[24] * a[8][3] + iT[1] * a[4][1] + iT[10] * a[6][1] + iT[14] * a[0][4] - iT[23] * a[5][1] - iT[2] * a[3][0] - iT[9] * a[2][0] + iT[15] * a[1][0] + iT[22] * a[0][0] - iT[3] * a[6][3] - iT[8] * a[4][3] + iT[16] * a[5][3] - iT[21] * a[0][2] - iT[4] * a[7][5] - iT[7] * a[4][0] + iT[17] * a[8][5] + iT[20] * a[1][5] + iT[5] * a[6][4] + iT[6] * a[3][1] + iT[18] * a[9][4] + iT[19] * a[8][1] - t[0] + add) >> shift);
    dst[15] = CLIP3(oMin, oMax, (   iT[0] * a[7][4] + iT[11] * a[4][1] - iT[13] * a[8][4] - iT[24] * a[1][4] - iT[1] * a[2][2] - iT[10] * a[3][2] + iT[14] * a[0][2] + iT[23] * a[1][2] - iT[2] * a[2][1] + iT[9] * a[7][1] + iT[15] * a[5][4] + iT[22] * a[9][4] + iT[3] * a[7][5] - iT[8] * a[2][5] + iT[16] * a[9][0] + iT[21] * a[5][0] + iT[4] * a[2][0] + iT[7] * a[3][0] - iT[17] * a[0][0] - iT[20] * a[1][0] + iT[5] * a[2][3] - iT[6] * a[7][3] - iT[18] * a[5][2] - iT[19] * a[9][2] - t[0] + add) >> shift);
    dst[16] = CLIP3(oMin, oMax, ( - iT[0] * a[0][1] + iT[11] * a[5][4] - iT[13] * a[6][4] - iT[24] * a[4][4] + iT[1] * a[0][3] - iT[10] * a[5][2] + iT[14] * a[6][2] + iT[23] * a[4][2] - iT[2] * a[0][5] + iT[9] * a[5][0] - iT[15] * a[6][0] - iT[22] * a[4][0] - iT[3] * a[0][4] - iT[8] * a[1][4] + iT[16] * a[3][4] + iT[21] * a[2][4] + iT[4] * a[0][2] + iT[7] * a[1][2] - iT[17] * a[3][2] - iT[20] * a[2][2] - iT[5] * a[0][0] - iT[6] * a[1][0] + iT[18] * a[3][0] + iT[19] * a[2][0] - t[1] + add) >> shift);
    dst[18] = CLIP3(oMin, oMax, (   iT[0] * a[0][5] + iT[11] * a[1][5] - iT[13] * a[3][5] - iT[24] * a[2][5] - iT[1] * a[1][0] - iT[10] * a[0][0] + iT[14] * a[2][0] + iT[23] * a[3][0] - iT[2] * a[5][1] + iT[9] * a[0][4] + iT[15] * a[4][1] + iT[22] * a[6][1] - iT[3] * a[8][1] - iT[8] * a[1][1] + iT[16] * a[4][4] + iT[21] * a[7][1] - iT[4] * a[9][2] - iT[7] * a[5][2] + iT[17] * a[2][3] - iT[20] * a[7][3] - iT[5] * a[9][3] - iT[6] * a[8][2] - iT[18] * a[3][2] - iT[19] * a[6][3] + t[1] + add) >> shift);
    dst[20] = CLIP3(oMin, oMax, ( - iT[0] * a[4][0] - iT[11] * a[6][0] - iT[13] * a[0][5] + iT[24] * a[5][0] + iT[1] * a[6][5] + iT[10] * a[4][5] - iT[14] * a[5][5] + iT[23] * a[0][0] - iT[2] * a[6][1] - iT[9] * a[3][4] - iT[15] * a[9][1] - iT[22] * a[8][4] + iT[3] * a[4][4] + iT[8] * a[7][1] - iT[16] * a[1][1] - iT[21] * a[8][1] - iT[4] * a[3][3] - iT[7] * a[2][3] + iT[17] * a[1][3] + iT[20] * a[0][3] + iT[5] * a[7][2] - iT[6] * a[2][2] + iT[18] * a[9][3] + iT[19] * a[5][3] + t[0] + add) >> shift);
    dst[21] = CLIP3(oMin, oMax, (   iT[0] * a[1][2] + iT[11] * a[8][2] - iT[13] * a[7][2] - iT[24] * a[4][3] + iT[1] * a[1][5] + iT[10] * a[8][5] - iT[14] * a[7][5] - iT[23] * a[4][0] + iT[2] * a[5][2] + iT[9] * a[9][2] + iT[15] * a[7][3] - iT[22] * a[2][3] + iT[3] * a[5][5] + iT[8] * a[9][5] + iT[16] * a[7][0] - iT[21] * a[2][0] + iT[4] * a[8][1] + iT[7] * a[9][4] + iT[17] * a[6][4] + iT[20] * a[3][1] + iT[5] * a[8][4] + iT[6] * a[9][1] + iT[18] * a[6][1] + iT[19] * a[3][4] + t[1] + add) >> shift);
    dst[23] = CLIP3(oMin, oMax, (   iT[0] * a[8][4] + iT[11] * a[9][1] + iT[13] * a[6][1] + iT[24] * a[3][4] - iT[1] * a[8][2] - iT[10] * a[1][2] + iT[14] * a[4][3] + iT[23] * a[7][2] - iT[2] * a[0][1] - iT[9] * a[1][1] + iT[15] * a[3][1] + iT[22] * a[2][1] + iT[3] * a[5][0] + iT[8] * a[9][0] + iT[16] * a[7][5] - iT[21] * a[2][5] - iT[4] * a[9][5] - iT[7] * a[8][0] - iT[17] * a[3][0] - iT[20] * a[6][5] + iT[5] * a[5][2] - iT[6] * a[0][3] - iT[18] * a[4][2] - iT[19] * a[6][2] - t[1] + add) >> shift);
    dst[24] = CLIP3(oMin, oMax, ( - iT[0] * a[2][3] + iT[11] * a[7][3] + iT[13] * a[5][2] + iT[24] * a[9][2] + iT[1] * a[4][1] + iT[10] * a[7][4] - iT[14] * a[1][4] - iT[23] * a[8][4] - iT[2] * a[4][5] - iT[9] * a[7][0] + iT[15] * a[1][0] + iT[22] * a[8][0] + iT[3] * a[4][3] + iT[8] * a[6][3] + iT[16] * a[0][2] - iT[21] * a[5][3] - iT[4] * a[2][5] - iT[7] * a[3][5] + iT[17] * a[0][5] + iT[20] * a[1][5] + iT[5] * a[2][1] + iT[6] * a[3][1] - iT[18] * a[0][1] - iT[19] * a[1][1] - t[0] + add) >> shift);
    dst[25] = CLIP3(oMin, oMax, ( - iT[0] * a[4][5] - iT[11] * a[6][5] - iT[13] * a[0][0] + iT[24] * a[5][5] - iT[1] * a[3][1] - iT[10] * a[2][1] + iT[14] * a[1][1] + iT[23] * a[0][1] + iT[2] * a[7][2] + iT[9] * a[4][3] - iT[15] * a[8][2] - iT[22] * a[1][2] + iT[3] * a[6][2] + iT[8] * a[3][3] + iT[16] * a[9][2] + iT[21] * a[8][3] + iT[4] * a[2][4] - iT[7] * a[7][4] - iT[17] * a[5][1] - iT[20] * a[9][1] - iT[5] * a[4][0] - iT[6] * a[6][0] - iT[18] * a[0][5] + iT[19] * a[5][0] - t[0] + add) >> shift);
    dst[26] = CLIP3(oMin, oMax, (   iT[0] * a[8][0] + iT[11] * a[1][0] - iT[13] * a[4][5] - iT[24] * a[7][0] + iT[1] * a[5][4] + iT[10] * a[9][4] + iT[14] * a[7][1] - iT[23] * a[2][1] - iT[2] * a[1][2] - iT[9] * a[0][2] + iT[15] * a[2][2] + iT[22] * a[3][2] - iT[3] * a[9][2] - iT[8] * a[8][3] - iT[16] * a[3][3] - iT[21] * a[6][2] + iT[4] * a[0][4] - iT[7] * a[5][1] + iT[17] * a[6][1] + iT[20] * a[4][1] + iT[5] * a[8][5] + iT[6] * a[1][5] - iT[18] * a[4][0] - iT[19] * a[7][5] - t[1] + add) >> shift);
    dst[28] = CLIP3(oMin, oMax, ( - iT[0] * a[5][1] - iT[11] * a[9][1] - iT[13] * a[7][4] + iT[24] * a[2][4] + iT[1] * a[8][2] + iT[10] * a[9][3] + iT[14] * a[6][3] + iT[23] * a[3][2] - iT[2] * a[9][4] - iT[9] * a[8][1] - iT[15] * a[3][1] - iT[22] * a[6][4] + iT[3] * a[9][0] + iT[8] * a[5][0] - iT[16] * a[2][5] + iT[21] * a[7][5] - iT[4] * a[5][5] + iT[7] * a[0][0] + iT[17] * a[4][5] + iT[20] * a[6][5] + iT[5] * a[1][3] + iT[6] * a[0][3] - iT[18] * a[2][3] - iT[19] * a[3][3] + t[1] + add) >> shift);
    dst[29] = CLIP3(oMin, oMax, (   iT[0] * a[6][4] + iT[11] * a[3][1] + iT[13] * a[9][4] + iT[24] * a[8][1] - iT[1] * a[7][3] - iT[10] * a[4][2] + iT[14] * a[8][3] + iT[23] * a[1][3] - iT[2] * a[3][5] - iT[9] * a[2][5] + iT[15] * a[1][5] + iT[22] * a[0][5] + iT[3] * a[2][4] + iT[8] * a[3][4] - iT[16] * a[0][4] - iT[21] * a[1][4] + iT[4] * a[4][3] + iT[7] * a[7][2] - iT[17] * a[1][2] - iT[20] * a[8][2] - iT[5] * a[3][0] - iT[6] * a[6][5] - iT[18] * a[8][0] - iT[19] * a[9][5] + t[0] + add) >> shift);
    dst[30] = CLIP3(oMin, oMax, ( - iT[0] * a[7][2] + iT[11] * a[2][2] - iT[13] * a[9][3] - iT[24] * a[5][3] - iT[1] * a[6][0] - iT[10] * a[4][0] + iT[14] * a[5][0] - iT[23] * a[0][5] - iT[2] * a[4][2] - iT[9] * a[6][2] - iT[15] * a[0][3] + iT[22] * a[5][2] + iT[3] * a[2][0] - iT[8] * a[7][0] - iT[16] * a[5][5] - iT[21] * a[9][5] + iT[4] * a[7][1] - iT[7] * a[2][1] + iT[17] * a[9][4] + iT[20] * a[5][4] + iT[5] * a[6][1] + iT[6] * a[4][1] - iT[18] * a[5][1] + iT[19] * a[0][4] + t[0] + add) >> shift);
    dst[31] = CLIP3(oMin, oMax, (   iT[0] * a[8][5] + iT[11] * a[1][5] - iT[13] * a[4][0] - iT[24] * a[7][5] - iT[1] * a[1][0] - iT[10] * a[8][0] + iT[14] * a[7][0] + iT[23] * a[4][5] - iT[2] * a[8][4] - iT[9] * a[1][4] + iT[15] * a[4][1] + iT[22] * a[7][4] + iT[3] * a[1][1] + iT[8] * a[8][1] - iT[16] * a[7][1] - iT[21] * a[4][4] + iT[4] * a[8][3] + iT[7] * a[1][3] - iT[17] * a[4][2] - iT[20] * a[7][3] - iT[5] * a[1][2] - iT[6] * a[8][2] + iT[18] * a[7][2] + iT[19] * a[4][3] + t[1] + add) >> shift);

    dst[ 2] = CLIP3(oMin, oMax, (   iT[ 4] * b[0] + iT[ 9] * b[1] + iT[14] * b[2] + iT[19] * b[3] + iT[24] * b[4] + iT[29] * b[5] + add) >> shift);
    dst[ 7] = CLIP3(oMin, oMax, ( - iT[14] * b[0] - iT[29] * b[1] - iT[19] * b[2] - iT[ 4] * b[3] + iT[ 9] * b[4] + iT[24] * b[5] + add) >> shift);
    dst[12] = CLIP3(oMin, oMax, (   iT[24] * b[0] + iT[14] * b[1] - iT[ 9] * b[2] - iT[29] * b[3] - iT[ 4] * b[4] + iT[19] * b[5] + add) >> shift);
    dst[17] = CLIP3(oMin, oMax, ( - iT[29] * b[0] + iT[ 4] * b[1] + iT[24] * b[2] - iT[ 9] * b[3] - iT[19] * b[4] + iT[14] * b[5] + add) >> shift);
    dst[22] = CLIP3(oMin, oMax, (   iT[19] * b[0] - iT[24] * b[1] + iT[ 4] * b[2] + iT[14] * b[3] - iT[29] * b[4] + iT[ 9] * b[5] + add) >> shift);
    dst[27] = CLIP3(oMin, oMax, ( - iT[ 9] * b[0] + iT[19] * b[1] - iT[29] * b[2] + iT[24] * b[3] - iT[14] * b[4] + iT[ 4] * b[5] + add) >> shift);

    dst[ 6] = CLIP3(oMin, oMax, (   iT[12] * c[0] + iT[25] * c[1] + add) >> shift);
    dst[19] = CLIP3(oMin, oMax, ( - iT[25] * c[0] + iT[12] * c[1] + add) >> shift);





}


extern "C" void IDCT2(ap_int<512>* in, ap_int<512>* out, int block_size, int size){
    #pragma HLS INTERFACE m_axi port=in offset=slave bundle=gmem0
    #pragma HLS INTERFACE m_axi port=out offset=slave bundle=gmem1
    #pragma HLS INTERFACE s_axilite port=in bundle=control
    #pragma HLS INTERFACE s_axilite port=out bundle=control
    #pragma HLS INTERFACE s_axilite port=block_size bundle=control
    #pragma HLS INTERFACE s_axilite port=size bundle=control
    #pragma HLS INTERFACE s_axilite port=return bundle=control

    for(int i=0; i<size; i++){
        #pragma HLS LOOP_TRIPCOUNT min=1 max=1024
        #pragma HLS PIPELINE II=1

        ap_int<512> in_block = in[i];
        ap_int<512> out_block = 0;

        if(block_size == 32){
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
                out_block.range((j+1)*32-1, j*32) = out_data[j];
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
                out_block.range((j+1)*32-1, j*32) = out_data[j];
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
                out_block.range((j+1)*32-1, j*32) = out_data[j];
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
                out_block.range((j+1)*32-1, j*32) = out_data[j];
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
                out_block.range((j+1)*32-1, j*32) = out_data[j];
            }

            //out[i] = out_block;
        }
        out[i] = out_block;
    }
}
