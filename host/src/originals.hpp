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

