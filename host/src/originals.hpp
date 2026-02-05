#include "tranform_coeffs_int.h"


#include <algorithm> // for std::min and std::max

inline int Clip3(int minVal, int maxVal, int a) {
    if (a < minVal) return minVal;
    if (a > maxVal) return maxVal;
    return a;
}



void fastInverseDCT2_B4( const int *src, int *dst, int shift, int line, int iSkipLine, int iSkipLine2, const int outputMinimum, const int outputMaximum )
{
  int j;
  int E[2], O[2];
  int add = 1 << ( shift - 1 );
  const int *iT = &idct4_i[0][0];

  const int  reducedLine = line - iSkipLine;
  for( j = 0; j < reducedLine; j++ )
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    O[0] = iT[1 * 4 + 0] * src[line] + iT[3 * 4 + 0] * src[3 * line];
    O[1] = iT[1 * 4 + 1] * src[line] + iT[3 * 4 + 1] * src[3 * line];
    E[0] = iT[0 * 4 + 0] * src[   0] + iT[2 * 4 + 0] * src[2 * line];
    E[1] = iT[0 * 4 + 1] * src[   0] + iT[2 * 4 + 1] * src[2 * line];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    dst[0] = Clip3( outputMinimum, outputMaximum, ( E[0] + O[0] + add ) >> shift );
    dst[1] = Clip3( outputMinimum, outputMaximum, ( E[1] + O[1] + add ) >> shift );
    dst[2] = Clip3( outputMinimum, outputMaximum, ( E[1] - O[1] + add ) >> shift );
    dst[3] = Clip3( outputMinimum, outputMaximum, ( E[0] - O[0] + add ) >> shift );

    src++;
    dst += 4;
  }
  if( iSkipLine )
  {
    memset( dst, 0, ( iSkipLine << 2 ) * sizeof( int ) );
  }
}

template<size_t TR_SIZE>
inline void inverseMatrixMult(const int *src, int *dst, int shift, size_t numOutLines, int skipOutLines,
                              int skipInLines, const int outputMinimum, const int outputMaximum,
                              const int *m)
{
  const int rndFactor = int(1) << (shift - 1);
  const size_t reducedLine = numOutLines - skipOutLines;
  const size_t cutoff      = TR_SIZE - skipInLines;

  for (size_t i = 0; i < reducedLine; i++)
  {
    for (size_t j = 0; j < TR_SIZE; j++)
    {
      int sum = 0;
      for (size_t k = 0; k < cutoff; k++)
      {
        sum += src[k * numOutLines + i] * m[k * TR_SIZE + j];
      }
      dst[i * TR_SIZE + j] = Clip3(outputMinimum, outputMaximum, (sum + rndFactor) >> shift);
    }
  }

  if (skipOutLines > 0)
  {
    std::fill_n(dst + reducedLine * TR_SIZE, skipOutLines * TR_SIZE, 0);
  }
}

template<size_t TR_SIZE>
inline void forwardMatrixMult(const int *src, int *dst, int shift, size_t numInLines, int skipInLines,
                              int skipOutLines, const int *m)
{
  const int rndFactor = int(1) << (shift - 1);

  const size_t reducedLine = numInLines - skipInLines;
  const size_t cutoff      = TR_SIZE - skipOutLines;

  for (int j = 0; j < cutoff; j++)
  {
    for (int i = 0; i < reducedLine; i++)
    {
      int sum = 0;
      for (int k = 0; k < TR_SIZE; k++)
      {
        sum += src[i * TR_SIZE + k] * m[j * TR_SIZE + k];
      }
      dst[j * numInLines + i] = (sum + rndFactor) >> shift;
    }

    if (skipInLines > 0)
    {
      std::fill_n(dst + j * numInLines + reducedLine, skipInLines, 0);
    }
  }

  if (skipOutLines > 0)
  {
    std::fill_n(dst + cutoff * numInLines, skipOutLines * numInLines, 0);
  }
}


//For 8
void fastInverseDCT2_B8(const int *src, int *dst, int shift, int line, int iSkipLine, int iSkipLine2, const int outputMinimum, const int outputMaximum)
{
  int j, k;
  int E[4], O[4];
  int EE[2], EO[2];
  int add = int(1) << (shift - 1);

  const int *iT = &idct8_i[0][0];

  const int  reducedLine = line - iSkipLine;
  for( j = 0; j < reducedLine; j++ )
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    for( k = 0; k < 4; k++ )
    {
      O[k] = iT[1 * 8 + k] * src[line] + iT[3 * 8 + k] * src[3 * line] + iT[5 * 8 + k] * src[5 * line] + iT[7 * 8 + k] * src[7 * line];
    }

    EO[0] = iT[2 * 8 + 0] * src[2 * line] + iT[6 * 8 + 0] * src[6 * line];
    EO[1] = iT[2 * 8 + 1] * src[2 * line] + iT[6 * 8 + 1] * src[6 * line];
    EE[0] = iT[0 * 8 + 0] * src[0       ] + iT[4 * 8 + 0] * src[4 * line];
    EE[1] = iT[0 * 8 + 1] * src[0       ] + iT[4 * 8 + 1] * src[4 * line];

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    E[0] = EE[0] + EO[0];
    E[3] = EE[0] - EO[0];
    E[1] = EE[1] + EO[1];
    E[2] = EE[1] - EO[1];

    for( k = 0; k < 4; k++ )
    {
      dst[k    ] = Clip3( outputMinimum, outputMaximum, ( E[    k] + O[    k] + add ) >> shift );
      dst[k + 4] = Clip3( outputMinimum, outputMaximum, ( E[3 - k] - O[3 - k] + add ) >> shift );
    }
    src++;
    dst += 8;
  }
  if( iSkipLine )
  {
    memset( dst, 0, ( iSkipLine << 3 ) * sizeof( int ) );
  }
}


void fastInverseDCT2_B64(const int *src, int *dst, int shift, int line, int iSkipLine, int iSkipLine2, const int outputMinimum, const int outputMaximum)
{
  int rnd_factor = 1 << (shift - 1);
  const int uiTrSize = 64;
  const int *iT = &idct64_i[0][0];

  int    j, k;
  int E[32], O[32];
  int EE[16], EO[16];
  int EEE[8], EEO[8];
  int EEEE[4], EEEO[4];
  int EEEEE[2], EEEEO[2];
  bool zo = iSkipLine2 >= 32;
  for (j = 0; j<line - iSkipLine; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
    for (k = 0;k<32;k++)
    {
      O[k] = iT[1 * 64 + k] * src[line] + iT[3 * 64 + k] * src[3 * line] + iT[5 * 64 + k] * src[5 * line] + iT[7 * 64 + k] * src[7 * line] +
        iT[9 * 64 + k] * src[9 * line] + iT[11 * 64 + k] * src[11 * line] + iT[13 * 64 + k] * src[13 * line] + iT[15 * 64 + k] * src[15 * line] +
        iT[17 * 64 + k] * src[17 * line] + iT[19 * 64 + k] * src[19 * line] + iT[21 * 64 + k] * src[21 * line] + iT[23 * 64 + k] * src[23 * line] +
        iT[25 * 64 + k] * src[25 * line] + iT[27 * 64 + k] * src[27 * line] + iT[29 * 64 + k] * src[29 * line] + iT[31 * 64 + k] * src[31 * line] +
        (zo ? 0 : (
        iT[33 * 64 + k] * src[33 * line] + iT[35 * 64 + k] * src[35 * line] + iT[37 * 64 + k] * src[37 * line] + iT[39 * 64 + k] * src[39 * line] +
        iT[41 * 64 + k] * src[41 * line] + iT[43 * 64 + k] * src[43 * line] + iT[45 * 64 + k] * src[45 * line] + iT[47 * 64 + k] * src[47 * line] +
        iT[49 * 64 + k] * src[49 * line] + iT[51 * 64 + k] * src[51 * line] + iT[53 * 64 + k] * src[53 * line] + iT[55 * 64 + k] * src[55 * line] +
        iT[57 * 64 + k] * src[57 * line] + iT[59 * 64 + k] * src[59 * line] + iT[61 * 64 + k] * src[61 * line] + iT[63 * 64 + k] * src[63 * line]));
    }
    for (k = 0;k<16;k++)
    {
      EO[k] = iT[2 * 64 + k] * src[2 * line] + iT[6 * 64 + k] * src[6 * line] + iT[10 * 64 + k] * src[10 * line] + iT[14 * 64 + k] * src[14 * line] +
        iT[18 * 64 + k] * src[18 * line] + iT[22 * 64 + k] * src[22 * line] + iT[26 * 64 + k] * src[26 * line] + iT[30 * 64 + k] * src[30 * line] +
        (zo ? 0 : (
        iT[34 * 64 + k] * src[34 * line] + iT[38 * 64 + k] * src[38 * line] + iT[42 * 64 + k] * src[42 * line] + iT[46 * 64 + k] * src[46 * line] +
        iT[50 * 64 + k] * src[50 * line] + iT[54 * 64 + k] * src[54 * line] + iT[58 * 64 + k] * src[58 * line] + iT[62 * 64 + k] * src[62 * line]));
    }
    for (k = 0;k<8;k++)
    {
      EEO[k] = iT[4 * 64 + k] * src[4 * line] + iT[12 * 64 + k] * src[12 * line] + iT[20 * 64 + k] * src[20 * line] + iT[28 * 64 + k] * src[28 * line] +
        (zo ? 0 : (
        iT[36 * 64 + k] * src[36 * line] + iT[44 * 64 + k] * src[44 * line] + iT[52 * 64 + k] * src[52 * line] + iT[60 * 64 + k] * src[60 * line]));
    }
    for (k = 0;k<4;k++)
    {
      EEEO[k] = iT[8 * 64 + k] * src[8 * line] + iT[24 * 64 + k] * src[24 * line] + (zo ? 0 : (iT[40 * 64 + k] * src[40 * line] + iT[56 * 64 + k] * src[56 * line]));
    }
    EEEEO[0] = iT[16 * 64 + 0] * src[16 * line] + (zo ? 0 : iT[48 * 64 + 0] * src[48 * line]);
    EEEEO[1] = iT[16 * 64 + 1] * src[16 * line] + (zo ? 0 : iT[48 * 64 + 1] * src[48 * line]);
    EEEEE[0] = iT[0 * 64 + 0] * src[0] + (zo ? 0 : iT[32 * 64 + 0] * src[32 * line]);
    EEEEE[1] = iT[0 * 64 + 1] * src[0] + (zo ? 0 : iT[32 * 64 + 1] * src[32 * line]);

    /* Combining even and odd terms at each hierarchy levels to calculate the final spatial domain vector */
    for (k = 0;k<2;k++)
    {
      EEEE[k] = EEEEE[k] + EEEEO[k];
      EEEE[k + 2] = EEEEE[1 - k] - EEEEO[1 - k];
    }
    for (k = 0;k<4;k++)
    {
      EEE[k] = EEEE[k] + EEEO[k];
      EEE[k + 4] = EEEE[3 - k] - EEEO[3 - k];
    }
    for (k = 0;k<8;k++)
    {
      EE[k] = EEE[k] + EEO[k];
      EE[k + 8] = EEE[7 - k] - EEO[7 - k];
    }
    for (k = 0;k<16;k++)
    {
      E[k] = EE[k] + EO[k];
      E[k + 16] = EE[15 - k] - EO[15 - k];
    }
    for (k = 0;k<32;k++)
    {
      dst[k] = Clip3(outputMinimum, outputMaximum, (E[k] + O[k] + rnd_factor) >> shift);
      dst[k + 32] = Clip3(outputMinimum, outputMaximum, (E[31 - k] - O[31 - k] + rnd_factor) >> shift);
    }
    src++;
    dst += uiTrSize;
  }

  memset(dst, 0, uiTrSize*iSkipLine * sizeof(int));
}

