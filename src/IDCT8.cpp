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

    dst[ 0] = CLIP3(oMin, oMax, (   90 * a[3][0] + 77 * a[6][5] + 72 * a[8][0] + 34 * a[9][5] + 90 * a[3][1] + 78 * a[6][4] + 68 * a[8][1] + 38 * a[9][4] + 89 * a[3][2] + 80 * a[6][3] + 66 * a[8][2] + 42 * a[9][3] + 88 * a[3][3] + 82 * a[6][2] + 63 * a[8][3] + 46 * a[9][2] + 87 * a[3][4] + 84 * a[6][1] + 60 * a[8][4] + 50 * a[9][1] + 86 * a[3][5] + 85 * a[6][0] + 56 * a[8][5] + 53 * a[9][0] + t[0] + add) >> shift);
    dst[ 1] = CLIP3(oMin, oMax, (   90 * a[5][2] - 77 * a[0][3] - 72 * a[4][2] - 34 * a[6][2] - 90 * a[9][1] - 78 * a[8][4] - 68 * a[3][4] - 38 * a[6][1] - 89 * a[0][0] + 80 * a[5][5] - 66 * a[6][5] - 42 * a[4][5] + 88 * a[5][3] - 82 * a[0][2] - 63 * a[4][3] - 46 * a[6][3] - 87 * a[9][0] - 84 * a[8][5] - 60 * a[3][5] - 50 * a[6][0] - 86 * a[0][1] + 85 * a[5][4] - 56 * a[6][4] - 53 * a[4][4] + t[1] + add) >> shift);
    dst[ 3] = CLIP3(oMin, oMax, (   90 * a[9][4] + 77 * a[5][4] - 72 * a[2][1] + 34 * a[7][1] + 90 * a[0][3] + 78 * a[1][3] - 68 * a[3][3] - 38 * a[2][3] - 89 * a[8][5] - 80 * a[9][0] - 66 * a[6][0] - 42 * a[3][5] + 88 * a[1][4] + 82 * a[0][4] - 63 * a[2][4] - 46 * a[3][4] + 87 * a[5][3] + 84 * a[9][3] + 60 * a[7][2] - 50 * a[2][2] - 86 * a[8][0] - 85 * a[1][0] + 56 * a[4][5] + 53 * a[7][0] - t[1] + add) >> shift);
    dst[ 4] = CLIP3(oMin, oMax, ( - 90 * a[3][2] - 77 * a[2][2] + 72 * a[1][2] + 34 * a[0][2] + 90 * a[6][0] + 78 * a[3][5] + 68 * a[9][0] + 38 * a[8][5] - 89 * a[2][3] - 80 * a[3][3] + 66 * a[0][3] + 42 * a[1][3] - 88 * a[7][0] + 82 * a[2][0] - 63 * a[9][5] - 46 * a[5][5] + 87 * a[4][4] + 84 * a[6][4] + 60 * a[0][1] - 50 * a[5][4] - 86 * a[7][4] - 85 * a[4][1] + 56 * a[8][4] + 53 * a[1][4] - t[0] + add) >> shift);
    dst[ 5] = CLIP3(oMin, oMax, (   90 * a[3][5] + 77 * a[6][0] + 72 * a[8][5] + 34 * a[9][0] - 90 * a[6][5] - 78 * a[3][0] - 68 * a[9][5] - 38 * a[8][0] + 89 * a[7][4] - 80 * a[2][4] + 66 * a[9][1] + 42 * a[5][1] + 88 * a[7][1] + 82 * a[4][4] - 63 * a[8][1] - 46 * a[1][1] - 87 * a[6][2] - 84 * a[4][2] + 60 * a[5][2] - 50 * a[0][3] + 86 * a[3][2] + 85 * a[2][2] - 56 * a[1][2] - 53 * a[0][2] - t[0] + add) >> shift);
    dst[ 8] = CLIP3(oMin, oMax, (   90 * a[9][3] + 77 * a[8][2] + 72 * a[3][2] + 34 * a[6][3] + 90 * a[1][5] + 78 * a[0][5] - 68 * a[2][5] - 38 * a[3][5] - 89 * a[1][3] - 80 * a[8][3] + 66 * a[7][3] + 42 * a[4][2] - 88 * a[9][5] - 82 * a[5][5] + 63 * a[2][0] - 46 * a[7][0] - 87 * a[1][1] - 84 * a[0][1] + 60 * a[2][1] + 50 * a[3][1] + 86 * a[5][1] + 85 * a[9][1] + 56 * a[7][4] - 53 * a[2][4] + t[1] + add) >> shift);
    dst[ 9] = CLIP3(oMin, oMax, (   90 * a[2][1] + 77 * a[3][1] - 72 * a[0][1] - 34 * a[1][1] - 90 * a[7][3] + 78 * a[2][3] - 68 * a[9][2] - 38 * a[5][2] - 89 * a[4][0] - 80 * a[7][5] + 66 * a[1][5] + 42 * a[8][5] - 88 * a[3][4] - 82 * a[2][4] + 63 * a[1][4] + 46 * a[0][4] - 87 * a[6][3] - 84 * a[3][2] - 60 * a[9][3] - 50 * a[8][2] - 86 * a[4][5] - 85 * a[6][5] - 56 * a[0][0] + 53 * a[5][5] + t[0] + add) >> shift);
    dst[10] = CLIP3(oMin, oMax, ( - 90 * a[6][1] - 77 * a[4][1] + 72 * a[5][1] - 34 * a[0][4] + 90 * a[2][2] - 78 * a[7][2] - 68 * a[5][3] - 38 * a[9][3] + 89 * a[6][4] + 80 * a[4][4] - 66 * a[5][4] + 42 * a[0][1] - 88 * a[2][5] + 82 * a[7][5] + 63 * a[5][0] + 46 * a[9][0] - 87 * a[7][0] - 84 * a[4][5] + 60 * a[8][0] + 50 * a[1][0] + 86 * a[4][2] + 85 * a[7][3] - 56 * a[1][3] - 53 * a[8][3] + t[0] + add) >> shift);
    dst[11] = CLIP3(oMin, oMax, ( - 90 * a[1][3] - 77 * a[0][3] + 72 * a[2][3] + 34 * a[3][3] - 90 * a[9][1] - 78 * a[5][1] + 68 * a[2][4] - 38 * a[7][4] - 89 * a[8][0] - 80 * a[9][5] - 66 * a[6][5] - 42 * a[3][0] + 88 * a[0][2] - 82 * a[5][3] + 63 * a[6][3] + 46 * a[4][3] + 87 * a[5][0] - 84 * a[0][5] - 60 * a[4][0] - 50 * a[6][0] + 86 * a[9][4] + 85 * a[5][4] - 56 * a[2][1] + 53 * a[7][1] + t[1] + add) >> shift);
    dst[13] = CLIP3(oMin, oMax, (   90 * a[0][0] + 77 * a[1][0] - 72 * a[3][0] - 34 * a[2][0] + 90 * a[5][4] - 78 * a[0][1] - 68 * a[4][4] - 38 * a[6][4] - 89 * a[9][3] - 80 * a[5][3] + 66 * a[2][2] - 42 * a[7][2] + 88 * a[8][3] + 82 * a[9][2] + 63 * a[6][2] + 46 * a[3][3] - 87 * a[1][4] - 84 * a[8][4] + 60 * a[7][4] + 50 * a[4][1] + 86 * a[0][5] + 85 * a[1][5] - 56 * a[3][5] - 53 * a[2][5] - t[1] + add) >> shift);
    dst[14] = CLIP3(oMin, oMax, (   90 * a[4][2] + 77 * a[7][3] - 72 * a[1][3] - 34 * a[8][3] + 90 * a[4][1] + 78 * a[6][1] + 68 * a[0][4] - 38 * a[5][1] - 89 * a[3][0] - 80 * a[2][0] + 66 * a[1][0] + 42 * a[0][0] - 88 * a[6][3] - 82 * a[4][3] + 63 * a[5][3] - 46 * a[0][2] - 87 * a[7][5] - 84 * a[4][0] + 60 * a[8][5] + 50 * a[1][5] + 86 * a[6][4] + 85 * a[3][1] + 56 * a[9][4] + 53 * a[8][1] - t[0] + add) >> shift);
    dst[15] = CLIP3(oMin, oMax, (   90 * a[7][4] + 77 * a[4][1] - 72 * a[8][4] - 34 * a[1][4] - 90 * a[2][2] - 78 * a[3][2] + 68 * a[0][2] + 38 * a[1][2] - 89 * a[2][1] + 80 * a[7][1] + 66 * a[5][4] + 42 * a[9][4] + 88 * a[7][5] - 82 * a[2][5] + 63 * a[9][0] + 46 * a[5][0] + 87 * a[2][0] + 84 * a[3][0] - 60 * a[0][0] - 50 * a[1][0] + 86 * a[2][3] - 85 * a[7][3] - 56 * a[5][2] - 53 * a[9][2] - t[0] + add) >> shift);
    dst[16] = CLIP3(oMin, oMax, ( - 90 * a[0][1] + 77 * a[5][4] - 72 * a[6][4] - 34 * a[4][4] + 90 * a[0][3] - 78 * a[5][2] + 68 * a[6][2] + 38 * a[4][2] - 89 * a[0][5] + 80 * a[5][0] - 66 * a[6][0] - 42 * a[4][0] - 88 * a[0][4] - 82 * a[1][4] + 63 * a[3][4] + 46 * a[2][4] + 87 * a[0][2] + 84 * a[1][2] - 60 * a[3][2] - 50 * a[2][2] - 86 * a[0][0] - 85 * a[1][0] + 56 * a[3][0] + 53 * a[2][0] - t[1] + add) >> shift);
    dst[18] = CLIP3(oMin, oMax, (   90 * a[0][5] + 77 * a[1][5] - 72 * a[3][5] - 34 * a[2][5] - 90 * a[1][0] - 78 * a[0][0] + 68 * a[2][0] + 38 * a[3][0] - 89 * a[5][1] + 80 * a[0][4] + 66 * a[4][1] + 42 * a[6][1] - 88 * a[8][1] - 82 * a[1][1] + 63 * a[4][4] + 46 * a[7][1] - 87 * a[9][2] - 84 * a[5][2] + 60 * a[2][3] - 50 * a[7][3] - 86 * a[9][3] - 85 * a[8][2] - 56 * a[3][2] - 53 * a[6][3] + t[1] + add) >> shift);
    dst[20] = CLIP3(oMin, oMax, ( - 90 * a[4][0] - 77 * a[6][0] - 72 * a[0][5] + 34 * a[5][0] + 90 * a[6][5] + 78 * a[4][5] - 68 * a[5][5] + 38 * a[0][0] - 89 * a[6][1] - 80 * a[3][4] - 66 * a[9][1] - 42 * a[8][4] + 88 * a[4][4] + 82 * a[7][1] - 63 * a[1][1] - 46 * a[8][1] - 87 * a[3][3] - 84 * a[2][3] + 60 * a[1][3] + 50 * a[0][3] + 86 * a[7][2] - 85 * a[2][2] + 56 * a[9][3] + 53 * a[5][3] + t[0] + add) >> shift);
    dst[21] = CLIP3(oMin, oMax, (   90 * a[1][2] + 77 * a[8][2] - 72 * a[7][2] - 34 * a[4][3] + 90 * a[1][5] + 78 * a[8][5] - 68 * a[7][5] - 38 * a[4][0] + 89 * a[5][2] + 80 * a[9][2] + 66 * a[7][3] - 42 * a[2][3] + 88 * a[5][5] + 82 * a[9][5] + 63 * a[7][0] - 46 * a[2][0] + 87 * a[8][1] + 84 * a[9][4] + 60 * a[6][4] + 50 * a[3][1] + 86 * a[8][4] + 85 * a[9][1] + 56 * a[6][1] + 53 * a[3][4] + t[1] + add) >> shift);
    dst[23] = CLIP3(oMin, oMax, (   90 * a[8][4] + 77 * a[9][1] + 72 * a[6][1] + 34 * a[3][4] - 90 * a[8][2] - 78 * a[1][2] + 68 * a[4][3] + 38 * a[7][2] - 89 * a[0][1] - 80 * a[1][1] + 66 * a[3][1] + 42 * a[2][1] + 88 * a[5][0] + 82 * a[9][0] + 63 * a[7][5] - 46 * a[2][5] - 87 * a[9][5] - 84 * a[8][0] - 60 * a[3][0] - 50 * a[6][5] + 86 * a[5][2] - 85 * a[0][3] - 56 * a[4][2] - 53 * a[6][2] - t[1] + add) >> shift);
    dst[24] = CLIP3(oMin, oMax, ( - 90 * a[2][3] + 77 * a[7][3] + 72 * a[5][2] + 34 * a[9][2] + 90 * a[4][1] + 78 * a[7][4] - 68 * a[1][4] - 38 * a[8][4] - 89 * a[4][5] - 80 * a[7][0] + 66 * a[1][0] + 42 * a[8][0] + 88 * a[4][3] + 82 * a[6][3] + 63 * a[0][2] - 46 * a[5][3] - 87 * a[2][5] - 84 * a[3][5] + 60 * a[0][5] + 50 * a[1][5] + 86 * a[2][1] + 85 * a[3][1] - 56 * a[0][1] - 53 * a[1][1] - t[0] + add) >> shift);
    dst[25] = CLIP3(oMin, oMax, ( - 90 * a[4][5] - 77 * a[6][5] - 72 * a[0][0] + 34 * a[5][5] - 90 * a[3][1] - 78 * a[2][1] + 68 * a[1][1] + 38 * a[0][1] + 89 * a[7][2] + 80 * a[4][3] - 66 * a[8][2] - 42 * a[1][2] + 88 * a[6][2] + 82 * a[3][3] + 63 * a[9][2] + 46 * a[8][3] + 87 * a[2][4] - 84 * a[7][4] - 60 * a[5][1] - 50 * a[9][1] - 86 * a[4][0] - 85 * a[6][0] - 56 * a[0][5] + 53 * a[5][0] - t[0] + add) >> shift);
    dst[26] = CLIP3(oMin, oMax, (   90 * a[8][0] + 77 * a[1][0] - 72 * a[4][5] - 34 * a[7][0] + 90 * a[5][4] + 78 * a[9][4] + 68 * a[7][1] - 38 * a[2][1] - 89 * a[1][2] - 80 * a[0][2] + 66 * a[2][2] + 42 * a[3][2] - 88 * a[9][2] - 82 * a[8][3] - 63 * a[3][3] - 46 * a[6][2] + 87 * a[0][4] - 84 * a[5][1] + 60 * a[6][1] + 50 * a[4][1] + 86 * a[8][5] + 85 * a[1][5] - 56 * a[4][0] - 53 * a[7][5] - t[1] + add) >> shift);
    dst[28] = CLIP3(oMin, oMax, ( - 90 * a[5][1] - 77 * a[9][1] - 72 * a[7][4] + 34 * a[2][4] + 90 * a[8][2] + 78 * a[9][3] + 68 * a[6][3] + 38 * a[3][2] - 89 * a[9][4] - 80 * a[8][1] - 66 * a[3][1] - 42 * a[6][4] + 88 * a[9][0] + 82 * a[5][0] - 63 * a[2][5] + 46 * a[7][5] - 87 * a[5][5] + 84 * a[0][0] + 60 * a[4][5] + 50 * a[6][5] + 86 * a[1][3] + 85 * a[0][3] - 56 * a[2][3] - 53 * a[3][3] + t[1] + add) >> shift);
    dst[29] = CLIP3(oMin, oMax, (   90 * a[6][4] + 77 * a[3][1] + 72 * a[9][4] + 34 * a[8][1] - 90 * a[7][3] - 78 * a[4][2] + 68 * a[8][3] + 38 * a[1][3] - 89 * a[3][5] - 80 * a[2][5] + 66 * a[1][5] + 42 * a[0][5] + 88 * a[2][4] + 82 * a[3][4] - 63 * a[0][4] - 46 * a[1][4] + 87 * a[4][3] + 84 * a[7][2] - 60 * a[1][2] - 50 * a[8][2] - 86 * a[3][0] - 85 * a[6][5] - 56 * a[8][0] - 53 * a[9][5] + t[0] + add) >> shift);
    dst[30] = CLIP3(oMin, oMax, ( - 90 * a[7][2] + 77 * a[2][2] - 72 * a[9][3] - 34 * a[5][3] - 90 * a[6][0] - 78 * a[4][0] + 68 * a[5][0] - 38 * a[0][5] - 89 * a[4][2] - 80 * a[6][2] - 66 * a[0][3] + 42 * a[5][2] + 88 * a[2][0] - 82 * a[7][0] - 63 * a[5][5] - 46 * a[9][5] + 87 * a[7][1] - 84 * a[2][1] + 60 * a[9][4] + 50 * a[5][4] + 86 * a[6][1] + 85 * a[4][1] - 56 * a[5][1] + 53 * a[0][4] + t[0] + add) >> shift);
    dst[31] = CLIP3(oMin, oMax, (   90 * a[8][5] + 77 * a[1][5] - 72 * a[4][0] - 34 * a[7][5] - 90 * a[1][0] - 78 * a[8][0] + 68 * a[7][0] + 38 * a[4][5] - 89 * a[8][4] - 80 * a[1][4] + 66 * a[4][1] + 42 * a[7][4] + 88 * a[1][1] + 82 * a[8][1] - 63 * a[7][1] - 46 * a[4][4] + 87 * a[8][3] + 84 * a[1][3] - 60 * a[4][2] - 50 * a[7][3] - 86 * a[1][2] - 85 * a[8][2] + 56 * a[7][2] + 53 * a[4][3] + t[1] + add) >> shift);

    dst[ 2] = CLIP3(oMin, oMax, (   87 * b[0] + 80 * b[1] + 68 * b[2] + 53 * b[3] + 34 * b[4] + 13 * b[5] + add) >> shift);
    dst[ 7] = CLIP3(oMin, oMax, ( - 68 * b[0] - 13 * b[1] - 53 * b[2] - 87 * b[3] + 80 * b[4] + 34 * b[5] + add) >> shift);
    dst[12] = CLIP3(oMin, oMax, (   34 * b[0] + 68 * b[1] - 80 * b[2] - 13 * b[3] - 87 * b[4] + 53 * b[5] + add) >> shift);
    dst[17] = CLIP3(oMin, oMax, ( - 13 * b[0] + 87 * b[1] + 34 * b[2] - 80 * b[3] - 53 * b[4] + 68 * b[5] + add) >> shift);
    dst[22] = CLIP3(oMin, oMax, (   53 * b[0] - 34 * b[1] + 87 * b[2] + 68 * b[3] - 13 * b[4] + 80 * b[5] + add) >> shift);
    dst[27] = CLIP3(oMin, oMax, ( - 80 * b[0] + 53 * b[1] - 13 * b[2] + 34 * b[3] - 68 * b[4] + 87 * b[5] + add) >> shift);

    dst[ 6] = CLIP3(oMin, oMax, (   74 * c[0] + 30 * c[1] + add) >> shift);
    dst[19] = CLIP3(oMin, oMax, ( - 30 * c[0] + 74 * c[1] + add) >> shift);

}


extern "C" void IDCT8(ap_int<512>* in, ap_int<512>* out, int block_size, int size, int shift, int oMin, int oMax) {
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

            IDCT8B32(in_data, out_data);

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

            IDCT8B16(in_data, out_data);

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

            IDCT8B8(in_data, out_data);

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

            IDCT8B4(in_data, out_data);

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

            IDCT8B2(in_data, out_data);

            for(int j=0; j<2; j++){
                #pragma HLS UNROLL
                out_block.range((j+1)*32-1, j*32) = out_data[j];
            }

            //out[i] = out_block;
        }
        out[i] = out_block;
    }
}
