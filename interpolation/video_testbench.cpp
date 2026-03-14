/**
 * ============================================================
 * VVC Fractional Interpolation — Real Video Testbench
 * With Latency Instrumentation (µs) + YUV Output + Total Timer
 * ============================================================
 *
 * New in this version:
 *   1. Writes interpolated frames to <input>_interp.yuv
 *      Play: ffplay -f rawvideo -pix_fmt yuv420p -s WxH output.yuv
 *         or: ffmpeg -f rawvideo -pix_fmt yuv420p -s WxH -r 25 -i out.yuv out.mp4
 *
 *   2. Total operation timer wraps everything (I/O + HLS + SW ref + write)
 *      Reported in µs, ms, and seconds with per-frame and per-block averages.
 *
 * Latency levels:
 *   - Per-block  : min / max / avg (HLS call only)
 *   - Per-case   : integer / H-only / V-only / quarter-pel
 *   - Per-frame  : totals and averages
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vvc_fractional_interp.h"

#define MARGIN       3
#define MAX_WIDTH  3840
#define MAX_HEIGHT 2160

// ============================================================
// Timer (µs)
// ============================================================
static inline double now_us(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec * 1e6 + (double)ts.tv_nsec / 1e3;
}

// ============================================================
// Latency accumulator
// ============================================================
typedef struct {
    double min_us, max_us, sum_us;
    long   count;
} LatencyStats;

static void lat_init(LatencyStats *s) {
    s->min_us = 1e18; s->max_us = 0.0; s->sum_us = 0.0; s->count = 0;
}
static void lat_record(LatencyStats *s, double us) {
    if (us < s->min_us) s->min_us = us;
    if (us > s->max_us) s->max_us = us;
    s->sum_us += us; s->count++;
}
static double lat_avg(const LatencyStats *s) {
    return s->count > 0 ? s->sum_us / s->count : 0.0;
}
static void lat_print(const char *label, const LatencyStats *s) {
    if (s->count == 0) { printf("  %-22s  (no blocks)\n", label); return; }
    printf("  %-22s  count=%7ld   min=%7.3f µs   avg=%7.3f µs   max=%7.3f µs\n",
           label, s->count, s->min_us, lat_avg(s), s->max_us);
}

// ============================================================
// Software Reference
// ============================================================
static const int SW_FILTER[NUM_FRAC_POS][NTAPS] = {
    {  0,  0,   0, 64,  0,   0,  0,  0 },
    {  0,  1,  -3, 63,  4,  -2,  1,  0 },
    { -1,  2,  -5, 62,  8,  -3,  1,  0 },
    { -1,  3,  -8, 60, 13,  -4,  1,  0 },
    { -1,  4, -10, 58, 17,  -5,  1,  0 },
    { -1,  4, -11, 52, 26,  -8,  3, -1 },
    { -1,  3,  -9, 47, 31, -10,  4, -1 },
    { -1,  4, -11, 45, 34, -10,  4, -1 },
    { -1,  4, -11, 40, 40, -11,  4, -1 },
    { -1,  4, -10, 34, 45, -11,  4, -1 },
    { -1,  4, -10, 31, 47,  -9,  3, -1 },
    { -1,  3,  -8, 26, 52, -11,  4, -1 },
    {  0,  1,  -5, 17, 58, -10,  4, -1 },
    {  0,  1,  -4, 13, 60,  -8,  3, -1 },
    {  0,  1,  -3,  8, 62,  -5,  2, -1 },
    {  0,  1,  -2,  4, 63,  -3,  1,  0 },
};

static inline int clip_sw(int v, int lo, int hi) {
    return v < lo ? lo : v > hi ? hi : v;
}

static void sw_interp_block(
    unsigned char *frame, int stride,
    int block_row, int block_col,
    int sw_out[BLOCK_SIZE][BLOCK_SIZE],
    int frac_x, int frac_y
) {
    if (frac_x == 0 && frac_y == 0) {
        for (int r = 0; r < BLOCK_SIZE; r++)
            for (int c = 0; c < BLOCK_SIZE; c++)
                sw_out[r][c] = frame[(block_row+r)*stride + (block_col+c)];
    } else if (frac_y == 0) {
        for (int r = 0; r < BLOCK_SIZE; r++)
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += frame[(block_row+r)*stride+(block_col+c+t-MARGIN)]
                           * SW_FILTER[frac_x][t];
                sw_out[r][c] = clip_sw((sum+(1<<(FILTER_PREC-1)))>>FILTER_PREC,0,255);
            }
    } else if (frac_x == 0) {
        for (int r = 0; r < BLOCK_SIZE; r++)
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += frame[(block_row+r+t-MARGIN)*stride+(block_col+c)]
                           * SW_FILTER[frac_y][t];
                sw_out[r][c] = clip_sw((sum+(1<<(FILTER_PREC-1)))>>FILTER_PREC,0,255);
            }
    } else {
        const int headroom = INTERNAL_PREC - BIT_DEPTH;
        const int shift1   = FILTER_PREC - headroom;
        const int offset1  = shift1 > 0 ? (1<<(shift1-1)) : 0;
        const int shift2   = FILTER_PREC + headroom;
        const int offset2  = 1 << (shift2-1);
        int mid[REF_BLOCK_H][BLOCK_SIZE];
        for (int r = 0; r < REF_BLOCK_H; r++)
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += frame[(block_row+r-MARGIN)*stride+(block_col+c+t-MARGIN)]
                           * SW_FILTER[frac_x][t];
                mid[r][c] = shift1>=0 ? (sum+offset1)>>shift1 : sum<<(-shift1);
            }
        for (int r = 0; r < BLOCK_SIZE; r++)
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += mid[r+t][c] * SW_FILTER[frac_y][t];
                sw_out[r][c] = clip_sw((sum+offset2)>>shift2, 0, 255);
            }
    }
}

static void extract_ref_window(
    unsigned char *frame, int stride,
    int block_row, int block_col,
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W]
) {
    for (int r = 0; r < REF_BLOCK_H; r++)
        for (int c = 0; c < REF_BLOCK_W; c++)
            ref_block[r][c] = frame[(block_row+r-MARGIN)*stride+(block_col+c-MARGIN)];
}

// ============================================================
// Motion vector generation
// ============================================================

typedef struct { int int_x, int_y, frac_x, frac_y; } motion_vector_t;

static motion_vector_t generate_mv(int bx, int by, int fi, int w, int h) {
    motion_vector_t mv;
    unsigned int seed = bx*31 + by*97 + fi*173;
    mv.int_x  = (int)(seed%33)-16;
    mv.int_y  = (int)((seed>>5)%33)-16;
    mv.frac_x = (seed>>10)%16;
    mv.frac_y = (seed>>14)%16;
    int rc = bx*BLOCK_SIZE+mv.int_x, rr = by*BLOCK_SIZE+mv.int_y;
    if (rc-MARGIN<0||rc+BLOCK_SIZE+MARGIN>w||rr-MARGIN<0||rr+BLOCK_SIZE+MARGIN>h)
        mv.int_x = mv.int_y = 0;
    return mv;
}

static int read_yuv_frame(FILE *fp, unsigned char *y, int w, int h, int fi) {
    long fsz = (long)w*h*3/2, ysz = (long)w*h;
    if (fseek(fp, fi*fsz, SEEK_SET)) { printf("ERROR: seek frame %d\n",fi); return -1; }
    if ((long)fread(y,1,ysz,fp)!=ysz) { printf("ERROR: read frame %d\n",fi); return -1; }
    return 0;
}

// ============================================================
// Write one interpolated frame to output YUV.
// Y plane = hw_out pixels; chroma copied from source unchanged.
// ============================================================
static void write_yuv_frame(
    FILE *out_fp, unsigned char *y_out,
    FILE *in_fp,  int width, int height, int fi
) {
    fwrite(y_out, 1, (size_t)width*height, out_fp);

    long chroma_sz    = (long)(width/2)*(height/2);
    long chroma_start = (long)fi*(long)width*height*3/2 + (long)width*height;
    unsigned char *buf = (unsigned char *)malloc(chroma_sz*2);
    if (!buf) {
        unsigned char grey = 128;
        for (long i = 0; i < chroma_sz*2; i++) fwrite(&grey,1,1,out_fp);
        return;
    }
    fseek(in_fp, chroma_start, SEEK_SET);
    size_t got = fread(buf, 1, chroma_sz*2, in_fp);
    if ((long)got != chroma_sz*2) memset(buf, 128, chroma_sz*2);
    fwrite(buf, 1, chroma_sz*2, out_fp);
    free(buf);
}

// ============================================================
// Main
// ============================================================
int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: %s <yuv> <width> <height> [frames] [mode]\n", argv[0]);
        printf("  mode: random|sweep|halfpel\n"); return 1;
    }

    const char *yuv_file = argv[1];
    int width   = atoi(argv[2]);
    int height  = atoi(argv[3]);
    int nframes = argc>=5 ? atoi(argv[4]) : 1;
    const char *mode = argc>=6 ? argv[5] : "random";

    // Build output filename
    char out_file[512];
    const char *dot = strrchr(yuv_file, '.');
    if (dot) snprintf(out_file,sizeof(out_file),"%.*s_interp%s",(int)(dot-yuv_file),yuv_file,dot);
    else     snprintf(out_file,sizeof(out_file),"%s_interp.yuv",yuv_file);

    printf("============================================================\n");
    printf("VVC Fractional Interpolation Testbench\n");
    printf("Latency (µs)  |  YUV Output  |  Total Operation Timer\n");
    printf("============================================================\n");
    printf("Input:      %s\n", yuv_file);
    printf("Output:     %s\n", out_file);
    printf("Resolution: %dx%d  |  Frames: %d  |  Mode: %s\n",
           width, height, nframes, mode);
    printf("============================================================\n\n");

    FILE *fp = fopen(yuv_file,"rb");
    if (!fp) { printf("ERROR: cannot open %s\n",yuv_file); return 1; }

    FILE *out_fp = fopen(out_file,"wb");
    if (!out_fp) { printf("ERROR: cannot create %s\n",out_file); fclose(fp); return 1; }

    fseek(fp,0,SEEK_END);
    long file_size = ftell(fp); fseek(fp,0,SEEK_SET);
    long fsz = (long)width*height*3/2;
    int avail = (int)(file_size/fsz);
    printf("Available frames: %d\n", avail);
    if (avail < nframes) { printf("Adjusting to %d frames.\n",avail); nframes=avail; }
    if (nframes<=0) { printf("ERROR: no frames.\n"); fclose(fp); fclose(out_fp); return 1; }

    long ysz = (long)width*height;
    unsigned char *y_plane = (unsigned char *)malloc(ysz);
    unsigned char *y_out   = (unsigned char *)malloc(ysz);
    if (!y_plane||!y_out) { printf("ERROR: alloc\n"); return 1; }

    int nbx = (width  - 2*MARGIN - BLOCK_SIZE + 1) / BLOCK_SIZE;
    int nby = (height - 2*MARGIN - BLOCK_SIZE + 1) / BLOCK_SIZE;
    if (nbx<=0) nbx=1; if (nby<=0) nby=1;
    printf("Block grid: %d x %d = %d blocks/frame\n\n", nbx, nby, nbx*nby);

    // Counters
    int total_blocks=0, total_errors=0, total_pixels=0;
    double max_err=0, sum_sq=0;
    int ci=0,ch=0,cv=0,cq=0, ei=0,eh=0,ev=0,eq=0;

    LatencyStats lat_all, lat_i, lat_h, lat_v, lat_q;
    lat_init(&lat_all); lat_init(&lat_i); lat_init(&lat_h);
    lat_init(&lat_v);   lat_init(&lat_q);

    LatencyStats *lf = (LatencyStats*)malloc(nframes*sizeof(LatencyStats));
    for (int f=0;f<nframes;f++) lat_init(&lf[f]);

    // ===========================================================
    //  TOTAL OPERATION TIMER START
    //  Covers: all frame reads, HLS calls, SW checks, file writes
    // ===========================================================
    double total_start = now_us();

    for (int f = 0; f < nframes; f++) {
        printf("--- Frame %d/%d ---\n", f+1, nframes);
        if (read_yuv_frame(fp, y_plane, width, height, f)) break;

        // Seed output with source so uncovered border pixels are valid
        memcpy(y_out, y_plane, ysz);

        int ferr=0, fblk=0;
        double fstart = now_us();

        for (int by=0; by<nby; by++) {
            for (int bx=0; bx<nbx; bx++) {

                int br = MARGIN + by*BLOCK_SIZE;
                int bc = MARGIN + bx*BLOCK_SIZE;
                int fx, fy;

                if (!strcmp(mode,"sweep")) {
                    int idx = by*nbx+bx; fx=idx%16; fy=(idx/16)%16;
                } else if (!strcmp(mode,"halfpel")) {
                    fx=8; fy=8;
                } else {
                    motion_vector_t mv = generate_mv(bx,by,f,width,height);
                    fx=mv.frac_x; fy=mv.frac_y;
                    int rr=br+mv.int_y, rc=bc+mv.int_x;
                    if (rr-MARGIN<0||rr+BLOCK_SIZE+MARGIN>height||
                        rc-MARGIN<0||rc+BLOCK_SIZE+MARGIN>width) continue;
                    br=rr; bc=rc;
                }
                if (br-MARGIN<0||br+BLOCK_SIZE+MARGIN>height||
                    bc-MARGIN<0||bc+BLOCK_SIZE+MARGIN>width) continue;

                int ii=(fx==0&&fy==0), ih=(fy==0&&fx!=0),
                    iv=(fx==0&&fy!=0), iq=(fx!=0&&fy!=0);
                if (ii) ci++; else if (ih) ch++; else if (iv) cv++; else cq++;

                pixel_t ref[REF_BLOCK_H][REF_BLOCK_W];
                extract_ref_window(y_plane, width, br, bc, ref);

                // ---- TIME HLS call only ----
                pel_t hw[BLOCK_SIZE][BLOCK_SIZE];
                double t0 = now_us();
                vvc_fractional_interp(ref, hw, (frac_t)fx, (frac_t)fy);
                double elapsed = now_us() - t0;
                // ----------------------------

                lat_record(&lat_all,elapsed); lat_record(&lf[f],elapsed);
                if (ii) lat_record(&lat_i,elapsed);
                else if (ih) lat_record(&lat_h,elapsed);
                else if (iv) lat_record(&lat_v,elapsed);
                else         lat_record(&lat_q,elapsed);

                // Write HLS pixels into output Y plane
                for (int r=0;r<BLOCK_SIZE;r++)
                    for (int c=0;c<BLOCK_SIZE;c++)
                        y_out[(br+r)*width+(bc+c)] = (unsigned char)hw[r][c];

                // SW reference check
                int sw[BLOCK_SIZE][BLOCK_SIZE];
                sw_interp_block(y_plane,width,br,bc,sw,fx,fy);
                int berr=0;
                for (int r=0;r<BLOCK_SIZE;r++)
                    for (int c=0;c<BLOCK_SIZE;c++) {
                        int d=(int)hw[r][c]-sw[r][c];
                        if (d) { berr++; double ad=fabs((double)d);
                            if(ad>max_err) max_err=ad; sum_sq+=d*d; }
                        total_pixels++;
                    }
                if (berr) {
                    ferr+=berr;
                    if (ferr<=5)
                        printf("  MISMATCH block(%d,%d) frac(%d,%d): %d err\n",
                               bx,by,fx,fy,berr);
                    if (ii) ei+=berr; else if (ih) eh+=berr;
                    else if (iv) ev+=berr; else eq+=berr;
                }
                total_blocks++; fblk++;
            }
        }

        // Write frame to output file
        write_yuv_frame(out_fp, y_out, fp, width, height, f);

        double fms = (now_us()-fstart)/1000.0;
        total_errors += ferr;
        printf("  Frame %d: %d blocks | %d errors | "
               "HLS avg=%.3f µs | HLS total=%.2f ms | wall=%.2f ms\n",
               f, fblk, ferr, lat_avg(&lf[f]), lf[f].sum_us/1000.0, fms);
    }

    // ===========================================================
    //  TOTAL OPERATION TIMER END
    // ===========================================================
    double total_end = now_us();
    double total_us  = total_end - total_start;
    double total_ms  = total_us  / 1000.0;
    double total_sec = total_us  / 1e6;

    fclose(out_fp);

    // ---- Correctness ----
    printf("\n============================================================\n");
    printf("                    CORRECTNESS SUMMARY\n");
    printf("============================================================\n");
    printf("Frames: %d  |  Blocks: %d  |  Pixels: %d\n",
           nframes, total_blocks, total_pixels);
    printf("Total errors: %d  |  Max error: %.0f\n", total_errors, max_err);
    if (total_pixels>0 && total_errors>0)
        printf("PSNR: %.2f dB\n",
               10.0*log10(255.0*255.0/(sum_sq/total_pixels)));
    printf("  Integer  (0,0):  %6d blocks, %d errors\n",ci,ei);
    printf("  Horiz only:      %6d blocks, %d errors\n",ch,eh);
    printf("  Vert  only:      %6d blocks, %d errors\n",cv,ev);
    printf("  Quarter-pixel:   %6d blocks, %d errors\n",cq,eq);

    // ---- Latency ----
    printf("\n============================================================\n");
    printf("                 LATENCY SUMMARY (µs) — HLS call only\n");
    printf("============================================================\n");
    printf("  %-22s  count        min          avg          max\n","Category");
    printf("  %s\n","----------------------------------------------------------------------");
    lat_print("ALL blocks",     &lat_all);
    printf("\n");
    lat_print("Integer (0,0)",  &lat_i);
    lat_print("Horizontal only",&lat_h);
    lat_print("Vertical only",  &lat_v);
    lat_print("Quarter-pixel",  &lat_q);

    printf("\n  %-8s  %-8s  %-12s  %-12s  %-12s  %-12s\n",
           "Frame","Blocks","min(µs)","avg(µs)","max(µs)","total(ms)");
    printf("  %s\n","--------------------------------------------------------------------");
    for (int f=0;f<nframes;f++)
        printf("  %-8d  %-8ld  %-12.3f  %-12.3f  %-12.3f  %-12.3f\n",
               f, lf[f].count,
               lf[f].min_us, lat_avg(&lf[f]), lf[f].max_us,
               lf[f].sum_us/1000.0);

    // ---- Total operation time ----
    printf("\n============================================================\n");
    printf("              TOTAL OPERATION TIME\n");
    printf("  (file I/O + HLS calls + SW reference check + YUV write)\n");
    printf("============================================================\n");
    printf("  Total:              %.3f µs\n",  total_us);
    printf("  Total:              %.3f ms\n",  total_ms);
    printf("  Total:              %.6f sec\n", total_sec);
    if (nframes>0)
        printf("  Per-frame avg:      %.3f ms\n",  total_ms/nframes);
    if (total_sec>0) {
        printf("  Frame throughput:   %.1f fps\n",   nframes/total_sec);
        printf("  Block throughput:   %.0f blk/sec\n", total_blocks/total_sec);
    }

    printf("\n============================================================\n");
    printf("RESULT: %s\n", total_errors==0 ? "ALL PASSED ✓" : "FAILED ✗");
    printf("============================================================\n");

    printf("\nOutput written to: %s\n\n", out_file);
    printf("View (real-time):\n");
    printf("  ffplay -f rawvideo -pix_fmt yuv420p -s %dx%d %s\n\n",
           width, height, out_file);
    printf("Convert to MP4:\n");
    printf("  ffmpeg -f rawvideo -pix_fmt yuv420p -s %dx%d -r 25 \\\n",
           width, height);
    printf("         -i %s -c:v libx264 -crf 18 output.mp4\n", out_file);

    free(y_plane); free(y_out); free(lf);
    fclose(fp);
    return total_errors==0 ? 0 : 1;
}