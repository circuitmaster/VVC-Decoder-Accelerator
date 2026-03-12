/**
 * ============================================================
 * VVC Fractional Interpolation — Real Video Testbench
 * ============================================================
 *
 * This testbench replicates the paper's testing methodology:
 *   - Reads real YUV 4:2:0 video frames (Tennis, Kimono, etc.)
 *   - Extracts 15x15 reference windows for each 8x8 block
 *   - Applies fractional interpolation with various MV fractions
 *   - Compares HLS output against software reference
 *   - Reports per-frame and overall pass/fail
 *
 * The paper used:
 *   - Tennis (1920x1080) — JCT-VC Class B test sequence
 *   - Kimono (1920x1080) — JCT-VC Class B test sequence
 *   Reference: F. Bossen, "Common test conditions and software
 *              reference configurations", JCTVC-I1100, May 2012.
 *
 * These are raw YUV 4:2:0 planar files. Only the Y (luma)
 * plane is used since the paper's hardware targets luma
 * interpolation with 8-tap filters.
 *
 * HOW TO GET TEST SEQUENCES:
 *   The standard JCTVC/JVET test sequences can be obtained from:
 *   - https://media.xiph.org/video/derf/  (some sequences)
 *   - Contact JVET/MPEG for official test sequences
 *   - Or use any raw YUV 4:2:0 file (e.g., from ffmpeg conversion)
 *
 *   To convert any video to raw YUV for testing:
 *     ffmpeg -i input.mp4 -pix_fmt yuv420p -frames:v 3 test.yuv
 *
 * USAGE:
 *   Compile: g++ -o tb vvc_fractional_interp.cpp video_testbench.cpp -I.
 *   Run:     ./tb <yuv_file> <width> <height> [num_frames]
 *
 *   Examples:
 *     ./tb Tennis_1920x1080.yuv    1920 1080 3
 *     ./tb Kimono_1920x1080.yuv   1920 1080 3
 *     ./tb BQTerrace_1920x1080.yuv 1920 1080 1
 *     ./tb foreman_352x288.yuv     352  288  5
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "vvc_fractional_interp.h"

// ============================================================
// Configuration
// ============================================================
#define MARGIN           3     // Filter margin (NTAPS/2 - 1)
#define MAX_WIDTH     3840     // Support up to 4K
#define MAX_HEIGHT    2160

// ============================================================
// Software Reference (golden model)
// Replicates InterpolationFilter::filter<8,...>() exactly
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

static inline int clip_sw(int val, int lo, int hi) {
    return (val < lo) ? lo : (val > hi) ? hi : val;
}

/**
 * Software single-pass filter (horizontal or vertical)
 */
static void sw_filter_1d(
    unsigned char *frame, int stride,
    int start_row, int start_col,
    int out[BLOCK_SIZE],
    int frac, int is_vertical
) {
    int samples[NTAPS];
    for (int t = 0; t < NTAPS; t++) {
        int r, c;
        if (is_vertical) {
            r = start_row + t - MARGIN;
            c = start_col;
        } else {
            r = start_row;
            c = start_col + t - MARGIN;
        }
        samples[t] = (int)frame[r * stride + c];
    }

    int sum = 0;
    for (int t = 0; t < NTAPS; t++)
        sum += samples[t] * SW_FILTER[frac][t];

    int val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
    out[0] = clip_sw(val, 0, 255);
}

/**
 * Software reference: complete block interpolation
 * Matches the behavior of the HLS top function
 */
static void sw_interp_block(
    unsigned char *frame, int stride,
    int block_row, int block_col,
    int sw_out[BLOCK_SIZE][BLOCK_SIZE],
    int frac_x, int frac_y
) {
    if (frac_x == 0 && frac_y == 0) {
        // Integer: direct copy
        for (int r = 0; r < BLOCK_SIZE; r++)
            for (int c = 0; c < BLOCK_SIZE; c++)
                sw_out[r][c] = (int)frame[(block_row + r) * stride + (block_col + c)];
    }
    else if (frac_y == 0) {
        // Horizontal only
        for (int r = 0; r < BLOCK_SIZE; r++) {
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int samples[NTAPS];
                for (int t = 0; t < NTAPS; t++)
                    samples[t] = (int)frame[(block_row + r) * stride + (block_col + c + t - MARGIN)];
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += samples[t] * SW_FILTER[frac_x][t];
                int val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                sw_out[r][c] = clip_sw(val, 0, 255);
            }
        }
    }
    else if (frac_x == 0) {
        // Vertical only
        for (int r = 0; r < BLOCK_SIZE; r++) {
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int samples[NTAPS];
                for (int t = 0; t < NTAPS; t++)
                    samples[t] = (int)frame[(block_row + r + t - MARGIN) * stride + (block_col + c)];
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += samples[t] * SW_FILTER[frac_y][t];
                int val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                sw_out[r][c] = clip_sw(val, 0, 255);
            }
        }
    }
    else {
        // Quarter-pixel: two-pass
        const int headroom = INTERNAL_PREC - BIT_DEPTH;
        const int shift1 = FILTER_PREC - headroom;
        const int offset1 = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
        const int shift2 = FILTER_PREC + headroom;
        const int offset2 = (1 << (shift2 - 1));

        // Pass 1: horizontal → intermediate (15 rows x 8 cols)
        int intermediate[REF_BLOCK_H][BLOCK_SIZE];
        for (int r = 0; r < REF_BLOCK_H; r++) {
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int samples[NTAPS];
                for (int t = 0; t < NTAPS; t++)
                    samples[t] = (int)frame[(block_row + r - MARGIN) * stride
                                            + (block_col + c + t - MARGIN)];
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += samples[t] * SW_FILTER[frac_x][t];
                if (shift1 >= 0)
                    intermediate[r][c] = (sum + offset1) >> shift1;
                else
                    intermediate[r][c] = sum << (-shift1);
            }
        }

        // Pass 2: vertical → output (8 rows x 8 cols)
        for (int r = 0; r < BLOCK_SIZE; r++) {
            for (int c = 0; c < BLOCK_SIZE; c++) {
                int sum = 0;
                for (int t = 0; t < NTAPS; t++)
                    sum += intermediate[r + t][c] * SW_FILTER[frac_y][t];
                int val = (sum + offset2) >> shift2;
                sw_out[r][c] = clip_sw(val, 0, 255);
            }
        }
    }
}

/**
 * Extract the 15x15 reference window from the frame for HLS input.
 * The window is centered at (block_row, block_col) with MARGIN=3
 * pixels of border on each side for the 8-tap filter.
 */
static void extract_ref_window(
    unsigned char *frame, int stride,
    int block_row, int block_col,
    pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W]
) {
    for (int r = 0; r < REF_BLOCK_H; r++) {
        for (int c = 0; c < REF_BLOCK_W; c++) {
            int fr = block_row + r - MARGIN;
            int fc = block_col + c - MARGIN;
            ref_block[r][c] = (pixel_t)frame[fr * stride + fc];
        }
    }
}

// ============================================================
// Motion vector generation
// Simulates realistic motion vectors for testing.
// In real VVC, MVs come from the encoder's ME stage.
// ============================================================
typedef struct {
    int int_x;    // Integer part of MV (horizontal)
    int int_y;    // Integer part of MV (vertical)
    int frac_x;   // Fractional part 0-15
    int frac_y;   // Fractional part 0-15
} motion_vector_t;

/**
 * Generate a pseudo-random but deterministic motion vector
 * for block at position (bx, by) in frame f
 */
static motion_vector_t generate_mv(int bx, int by, int frame_idx, int width, int height) {
    motion_vector_t mv;
    // Use a simple hash for deterministic but varied MVs
    unsigned int seed = (bx * 31 + by * 97 + frame_idx * 173);

    // Integer MV: small range [-16, +16] pixels (typical for 1080p)
    mv.int_x = ((int)(seed % 33)) - 16;
    mv.int_y = ((int)((seed >> 5) % 33)) - 16;

    // Fractional MV: 0-15 (1/16 pel accuracy)
    mv.frac_x = (seed >> 10) % 16;
    mv.frac_y = (seed >> 14) % 16;

    // Clamp so the reference window stays within frame bounds
    int ref_col = bx * BLOCK_SIZE + mv.int_x;
    int ref_row = by * BLOCK_SIZE + mv.int_y;

    // Ensure 15x15 window fits: need MARGIN pixels on each side
    if (ref_col - MARGIN < 0 || ref_col + BLOCK_SIZE + MARGIN > width ||
        ref_row - MARGIN < 0 || ref_row + BLOCK_SIZE + MARGIN > height) {
        // Fall back to zero MV if out of bounds
        mv.int_x = 0;
        mv.int_y = 0;
    }

    return mv;
}

// ============================================================
// Read one YUV 4:2:0 frame (luma plane only)
// YUV 4:2:0 layout: Y plane (w*h), U plane (w/2 * h/2), V plane (w/2 * h/2)
// ============================================================
static int read_yuv_frame(
    FILE *fp,
    unsigned char *y_plane,
    int width, int height,
    int frame_idx
) {
    // Frame size in bytes for YUV 4:2:0
    long frame_size = (long)width * height * 3 / 2;
    long y_size = (long)width * height;

    // Seek to the target frame
    if (fseek(fp, frame_idx * frame_size, SEEK_SET) != 0) {
        printf("ERROR: Cannot seek to frame %d\n", frame_idx);
        return -1;
    }

    // Read only Y plane
    size_t read = fread(y_plane, 1, y_size, fp);
    if ((long)read != y_size) {
        printf("ERROR: Could not read frame %d (got %zu of %ld bytes)\n",
               frame_idx, read, y_size);
        return -1;
    }

    return 0;
}

// ============================================================
// Print usage
// ============================================================
static void print_usage(const char *prog) {
    printf("Usage: %s <yuv_file> <width> <height> [num_frames] [mode]\n\n", prog);
    printf("Arguments:\n");
    printf("  yuv_file    : Raw YUV 4:2:0 video file\n");
    printf("  width       : Frame width in pixels\n");
    printf("  height      : Frame height in pixels\n");
    printf("  num_frames  : Number of frames to process (default: 1)\n");
    printf("  mode        : Test mode (default: random)\n");
    printf("                'random'   - Random MVs per block\n");
    printf("                'sweep'    - Sweep all 16 frac positions\n");
    printf("                'halfpel'  - Only half-pel positions (8,8)\n");
    printf("\nExamples:\n");
    printf("  %s Tennis_1920x1080.yuv 1920 1080 3\n", prog);
    printf("  %s Kimono_1920x1080.yuv 1920 1080 1 sweep\n", prog);
    printf("  %s foreman_352x288.yuv 352 288 5 random\n", prog);
    printf("\nTo create a test YUV file from any video:\n");
    printf("  ffmpeg -i input.mp4 -pix_fmt yuv420p -frames:v 3 test.yuv\n");
}

// ============================================================
// Main testbench
// ============================================================
int main(int argc, char *argv[]) {

    // --------------------------------------------------------
    // Parse arguments
    // --------------------------------------------------------
    if (argc < 4) {
        print_usage(argv[0]);
        return 1;
    }

    const char *yuv_file = argv[1];
    int width  = atoi(argv[2]);
    int height = atoi(argv[3]);
    int num_frames = (argc >= 5) ? atoi(argv[4]) : 1;
    const char *mode = (argc >= 6) ? argv[5] : "random";

    if (width <= 0 || height <= 0 || width > MAX_WIDTH || height > MAX_HEIGHT) {
        printf("ERROR: Invalid resolution %dx%d\n", width, height);
        return 1;
    }

    printf("============================================================\n");
    printf("VVC Fractional Interpolation — Real Video Testbench\n");
    printf("============================================================\n");
    printf("File:       %s\n", yuv_file);
    printf("Resolution: %dx%d\n", width, height);
    printf("Frames:     %d\n", num_frames);
    printf("Mode:       %s\n", mode);
    printf("============================================================\n\n");

    // --------------------------------------------------------
    // Open YUV file
    // --------------------------------------------------------
    FILE *fp = fopen(yuv_file, "rb");
    if (!fp) {
        printf("ERROR: Cannot open '%s'\n", yuv_file);
        printf("\nTo create a test file:\n");
        printf("  ffmpeg -i any_video.mp4 -pix_fmt yuv420p -frames:v %d %s\n",
               num_frames, yuv_file);
        return 1;
    }

    // Check file size to determine available frames
    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    long frame_size = (long)width * height * 3 / 2;
    int available_frames = (int)(file_size / frame_size);
    printf("File size: %ld bytes, available frames: %d\n", file_size, available_frames);

    if (available_frames < num_frames) {
        printf("WARNING: Only %d frames available, adjusting.\n", available_frames);
        num_frames = available_frames;
    }

    if (num_frames <= 0) {
        printf("ERROR: No frames available. Check file and resolution.\n");
        fclose(fp);
        return 1;
    }

    // --------------------------------------------------------
    // Allocate frame buffer
    // --------------------------------------------------------
    long y_size = (long)width * height;
    unsigned char *y_plane = (unsigned char *)malloc(y_size);
    if (!y_plane) {
        printf("ERROR: Cannot allocate %ld bytes for frame\n", y_size);
        fclose(fp);
        return 1;
    }

    // --------------------------------------------------------
    // Block grid dimensions
    // Only process blocks where a full 15x15 window fits
    // --------------------------------------------------------
    int num_blocks_x = (width  - 2 * MARGIN - BLOCK_SIZE + 1) / BLOCK_SIZE;
    int num_blocks_y = (height - 2 * MARGIN - BLOCK_SIZE + 1) / BLOCK_SIZE;
    // Limit to valid range
    if (num_blocks_x <= 0) num_blocks_x = 1;
    if (num_blocks_y <= 0) num_blocks_y = 1;

    int blocks_per_frame = num_blocks_x * num_blocks_y;
    printf("Block grid:  %d x %d = %d blocks per frame\n\n",
           num_blocks_x, num_blocks_y, blocks_per_frame);

    // --------------------------------------------------------
    // Statistics
    // --------------------------------------------------------
    int total_blocks = 0;
    int total_errors = 0;
    int total_pixels_tested = 0;
    double max_abs_error = 0;
    double sum_sq_error = 0;

    // Per-case counters
    int count_integer = 0, count_honly = 0, count_vonly = 0, count_quarter = 0;
    int errors_integer = 0, errors_honly = 0, errors_vonly = 0, errors_quarter = 0;

    clock_t start_time = clock();

    // --------------------------------------------------------
    // Process each frame
    // --------------------------------------------------------
    for (int f = 0; f < num_frames; f++) {
        printf("--- Frame %d/%d ---\n", f + 1, num_frames);

        if (read_yuv_frame(fp, y_plane, width, height, f) != 0) {
            printf("ERROR: Failed to read frame %d\n", f);
            break;
        }

        int frame_errors = 0;
        int frame_blocks = 0;

        // --------------------------------------------------------
        // Process each 8x8 block in the frame
        // --------------------------------------------------------
        for (int by = 0; by < num_blocks_y; by++) {
            for (int bx = 0; bx < num_blocks_x; bx++) {
                // Block top-left corner in frame (with margin offset)
                int block_row = MARGIN + by * BLOCK_SIZE;
                int block_col = MARGIN + bx * BLOCK_SIZE;

                // Determine fractional positions based on test mode
                int frac_x, frac_y;

                if (strcmp(mode, "sweep") == 0) {
                    // Systematically sweep through all fractional positions
                    int block_idx = by * num_blocks_x + bx;
                    frac_x = block_idx % 16;
                    frac_y = (block_idx / 16) % 16;
                }
                else if (strcmp(mode, "halfpel") == 0) {
                    // Test only half-pel (position 8), worst case for filter
                    frac_x = 8;
                    frac_y = 8;
                }
                else {
                    // Random mode: generate pseudo-random MV
                    motion_vector_t mv = generate_mv(bx, by, f, width, height);
                    frac_x = mv.frac_x;
                    frac_y = mv.frac_y;

                    // For random mode, apply integer MV offset to block position
                    int ref_row = block_row + mv.int_y;
                    int ref_col = block_col + mv.int_x;

                    // Bounds check for the 15x15 window
                    if (ref_row - MARGIN < 0 || ref_row + BLOCK_SIZE + MARGIN > height ||
                        ref_col - MARGIN < 0 || ref_col + BLOCK_SIZE + MARGIN > width) {
                        continue;  // Skip out-of-bounds blocks
                    }

                    block_row = ref_row;
                    block_col = ref_col;
                }

                // Bounds check
                if (block_row - MARGIN < 0 || block_row + BLOCK_SIZE + MARGIN > height ||
                    block_col - MARGIN < 0 || block_col + BLOCK_SIZE + MARGIN > width) {
                    continue;
                }

                // Track case type
                if (frac_x == 0 && frac_y == 0)      count_integer++;
                else if (frac_y == 0)                  count_honly++;
                else if (frac_x == 0)                  count_vonly++;
                else                                   count_quarter++;

                // ----- Extract 15x15 reference window for HLS -----
                pixel_t ref_block[REF_BLOCK_H][REF_BLOCK_W];
                extract_ref_window(y_plane, width, block_row, block_col, ref_block);

                // ----- Run HLS function -----
                pel_t hw_out[BLOCK_SIZE][BLOCK_SIZE];
                vvc_fractional_interp(ref_block, hw_out, (frac_t)frac_x, (frac_t)frac_y);

                // ----- Run software reference -----
                int sw_out[BLOCK_SIZE][BLOCK_SIZE];
                sw_interp_block(y_plane, width, block_row, block_col, sw_out, frac_x, frac_y);

                // ----- Compare -----
                int block_err = 0;
                for (int r = 0; r < BLOCK_SIZE; r++) {
                    for (int c = 0; c < BLOCK_SIZE; c++) {
                        int diff = (int)hw_out[r][c] - sw_out[r][c];
                        if (diff != 0) {
                            block_err++;
                            double abs_diff = fabs((double)diff);
                            if (abs_diff > max_abs_error) max_abs_error = abs_diff;
                            sum_sq_error += (double)diff * diff;
                        }
                        total_pixels_tested++;
                    }
                }

                if (block_err > 0) {
                    frame_errors += block_err;
                    if (frame_errors <= 5) {  // Print first few errors per frame
                        printf("  MISMATCH at block (%3d,%3d) frac=(%2d,%2d): %d pixel errors\n",
                               bx, by, frac_x, frac_y, block_err);
                    }

                    if (frac_x == 0 && frac_y == 0)      errors_integer += block_err;
                    else if (frac_y == 0)                  errors_honly += block_err;
                    else if (frac_x == 0)                  errors_vonly += block_err;
                    else                                   errors_quarter += block_err;
                }

                total_blocks++;
                frame_blocks++;
            }
        }

        total_errors += frame_errors;
        printf("  Frame %d: %d blocks tested, %d pixel errors\n",
               f, frame_blocks, frame_errors);
    }

    clock_t end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    // --------------------------------------------------------
    // Print summary report
    // --------------------------------------------------------
    printf("\n============================================================\n");
    printf("                    TEST SUMMARY\n");
    printf("============================================================\n");
    printf("Frames processed:     %d\n", num_frames);
    printf("Blocks tested:        %d\n", total_blocks);
    printf("Pixels tested:        %d\n", total_pixels_tested);
    printf("Total pixel errors:   %d\n", total_errors);
    printf("Max absolute error:   %.0f\n", max_abs_error);
    if (total_pixels_tested > 0 && total_errors > 0) {
        printf("PSNR (error):         %.2f dB\n",
               10.0 * log10(255.0 * 255.0 / (sum_sq_error / total_pixels_tested)));
    }
    printf("Execution time:       %.3f sec\n", elapsed);
    if (elapsed > 0) {
        printf("Throughput:           %.0f blocks/sec\n", total_blocks / elapsed);
    }

    printf("\n--- Breakdown by interpolation case ---\n");
    printf("  Integer (0,0):      %6d blocks, %d errors\n", count_integer, errors_integer);
    printf("  Horizontal only:    %6d blocks, %d errors\n", count_honly, errors_honly);
    printf("  Vertical only:      %6d blocks, %d errors\n", count_vonly, errors_vonly);
    printf("  Quarter-pixel:      %6d blocks, %d errors\n", count_quarter, errors_quarter);

    printf("\n============================================================\n");
    printf("RESULT: %s\n", (total_errors == 0) ? "ALL PASSED ✓" : "FAILED ✗");
    printf("============================================================\n");

    // --------------------------------------------------------
    // Cleanup
    // --------------------------------------------------------
    free(y_plane);
    fclose(fp);

    return (total_errors == 0) ? 0 : 1;
}