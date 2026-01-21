#include "libspir_types.h"
#include "hls_stream_thread_safe.h"
#include "xcl_top_defines.h"
#include "ap_axi_sdata.h"
#include "xcl_top_datamovers.h"
#define EXPORT_PIPE_SYMBOLS 1
#include "cpu_pipes.h"
#undef EXPORT_PIPE_SYMBOLS
#include "xcl_half.h"
#include <cstddef>
#include <vector>
#include <complex>
#include <pthread.h>
using namespace std;

extern "C" {

void IDST7(size_t in_r, size_t out_r, unsigned int block_size, unsigned int sIn, unsigned int size, unsigned int shift, unsigned int oMin, unsigned int oMax);

static pthread_mutex_t __xlnx_cl_IDST7_mutex = PTHREAD_MUTEX_INITIALIZER;
void __stub____xlnx_cl_IDST7(char **argv) {
  void **args = (void **)argv;
  size_t in_r = *((size_t*)args[0+1]);
  size_t out_r = *((size_t*)args[1+1]);
  unsigned int block_size = *((unsigned int*)args[2+1]);
  unsigned int sIn = *((unsigned int*)args[3+1]);
  unsigned int size = *((unsigned int*)args[4+1]);
  unsigned int shift = *((unsigned int*)args[5+1]);
  unsigned int oMin = *((unsigned int*)args[6+1]);
  unsigned int oMax = *((unsigned int*)args[7+1]);
 pthread_mutex_lock(&__xlnx_cl_IDST7_mutex);
  IDST7(in_r, out_r, block_size, sIn, size, shift, oMin, oMax);
  pthread_mutex_unlock(&__xlnx_cl_IDST7_mutex);
}
void IDCT8(size_t in_r, size_t out_r, unsigned int block_size, unsigned int sIn, unsigned int size, unsigned int shift, unsigned int oMin, unsigned int oMax);

static pthread_mutex_t __xlnx_cl_IDCT8_mutex = PTHREAD_MUTEX_INITIALIZER;
void __stub____xlnx_cl_IDCT8(char **argv) {
  void **args = (void **)argv;
  size_t in_r = *((size_t*)args[0+1]);
  size_t out_r = *((size_t*)args[1+1]);
  unsigned int block_size = *((unsigned int*)args[2+1]);
  unsigned int sIn = *((unsigned int*)args[3+1]);
  unsigned int size = *((unsigned int*)args[4+1]);
  unsigned int shift = *((unsigned int*)args[5+1]);
  unsigned int oMin = *((unsigned int*)args[6+1]);
  unsigned int oMax = *((unsigned int*)args[7+1]);
 pthread_mutex_lock(&__xlnx_cl_IDCT8_mutex);
  IDCT8(in_r, out_r, block_size, sIn, size, shift, oMin, oMax);
  pthread_mutex_unlock(&__xlnx_cl_IDCT8_mutex);
}
void IDCT2(size_t in_r, size_t in2, size_t out_r, size_t out2, unsigned int block_size, unsigned int size, unsigned int shift, unsigned int outputMinimum, unsigned int outputMaximum);

static pthread_mutex_t __xlnx_cl_IDCT2_mutex = PTHREAD_MUTEX_INITIALIZER;
void __stub____xlnx_cl_IDCT2(char **argv) {
  void **args = (void **)argv;
  size_t in_r = *((size_t*)args[0+1]);
  size_t in2 = *((size_t*)args[1+1]);
  size_t out_r = *((size_t*)args[2+1]);
  size_t out2 = *((size_t*)args[3+1]);
  unsigned int block_size = *((unsigned int*)args[4+1]);
  unsigned int size = *((unsigned int*)args[5+1]);
  unsigned int shift = *((unsigned int*)args[6+1]);
  unsigned int outputMinimum = *((unsigned int*)args[7+1]);
  unsigned int outputMaximum = *((unsigned int*)args[8+1]);
 pthread_mutex_lock(&__xlnx_cl_IDCT2_mutex);
  IDCT2(in_r, in2, out_r, out2, block_size, size, shift, outputMinimum, outputMaximum);
  pthread_mutex_unlock(&__xlnx_cl_IDCT2_mutex);
}
}
