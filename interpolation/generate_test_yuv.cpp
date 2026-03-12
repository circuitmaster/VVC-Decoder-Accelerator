/**
 * ============================================================
 * Synthetic YUV 4:2:0 Test Video Generator
 * ============================================================
 *
 * Generates a raw YUV 4:2:0 file with realistic-looking content
 * for testing the fractional interpolation filter.
 *
 * The generated frames contain:
 *   - Smooth gradients (test smooth areas)
 *   - Sharp edges (test filter ringing behavior)
 *   - Checkerboard/texture patterns (test high-frequency content)
 *   - Motion between frames (shifting patterns)
 *
 * This allows testing WITHOUT downloading the official JCTVC
 * test sequences (Tennis, Kimono, etc.)
 *
 * Usage: ./gen_yuv <output.yuv> <width> <height> <num_frames>
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static unsigned char clip8(int val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return (unsigned char)val;
}

/**
 * Generate one Y plane with a mix of patterns.
 * Each frame is divided into regions with different content:
 *
 *   +------------------+------------------+
 *   |  Smooth gradient |   Diagonal edge  |
 *   |  (horizontal)    |   pattern        |
 *   +------------------+------------------+
 *   |  Checkerboard    |   Sinusoidal     |
 *   |  texture         |   waves          |
 *   +------------------+------------------+
 *
 * Patterns shift between frames to simulate motion.
 */
static void generate_y_plane(
    unsigned char *y,
    int width, int height,
    int frame_idx
) {
    int half_w = width / 2;
    int half_h = height / 2;

    // Motion offset: shifts by a few pixels per frame
    // This creates content at all fractional positions when sampled
    double motion_x = 2.3 * frame_idx;  // Non-integer to create fractional positions
    double motion_y = 1.7 * frame_idx;

    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            int val = 128;  // default mid-gray
            double mr = r + motion_y;
            double mc = c + motion_x;

            if (r < half_h && c < half_w) {
                // Region 1: Smooth horizontal gradient with slight vertical variation
                val = (int)(20 + 200.0 * mc / width + 15.0 * sin(mr * 0.05));
            }
            else if (r < half_h && c >= half_w) {
                // Region 2: Diagonal sharp edges (tests filter ringing)
                double d = fmod(mr + mc, 32.0);
                if (d < 16.0)
                    val = 40;
                else
                    val = 220;
            }
            else if (r >= half_h && c < half_w) {
                // Region 3: Checkerboard texture (high frequency content)
                int check_size = 4;  // 4x4 checkerboard
                int cr = ((int)mr / check_size) % 2;
                int cc = ((int)mc / check_size) % 2;
                val = (cr ^ cc) ? 200 : 60;
                // Add some noise
                val += (int)(10.0 * sin(mr * 0.3) * cos(mc * 0.4));
            }
            else {
                // Region 4: Sinusoidal waves (medium frequency)
                double freq1 = 0.08, freq2 = 0.12;
                val = (int)(128 + 80 * sin(mr * freq1 + mc * freq2) +
                            30 * cos(mr * freq2 * 1.5 - mc * freq1));
            }

            // Add a subtle border/grid pattern every 64 pixels
            // (helps visually verify block boundaries)
            if (r % 64 == 0 || c % 64 == 0) {
                val = (val + 128) / 2;  // Blend toward mid-gray
            }

            y[r * width + c] = clip8(val);
        }
    }
}

/**
 * Generate U and V chroma planes (simple patterns).
 * For our luma-focused test, chroma content doesn't matter much
 * but we need valid data for YUV file format.
 */
static void generate_uv_planes(
    unsigned char *u, unsigned char *v,
    int cwidth, int cheight,
    int frame_idx
) {
    for (int r = 0; r < cheight; r++) {
        for (int c = 0; c < cwidth; c++) {
            // Simple color pattern
            u[r * cwidth + c] = clip8(128 + (int)(30 * sin(r * 0.05 + frame_idx * 0.3)));
            v[r * cwidth + c] = clip8(128 + (int)(30 * cos(c * 0.05 + frame_idx * 0.2)));
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <output.yuv> <width> <height> <num_frames>\n", argv[0]);
        printf("Example: %s test_352x288.yuv 352 288 5\n", argv[0]);
        return 1;
    }

    const char *output = argv[1];
    int width = atoi(argv[2]);
    int height = atoi(argv[3]);
    int num_frames = atoi(argv[4]);

    if (width <= 0 || height <= 0 || num_frames <= 0) {
        printf("ERROR: Invalid parameters\n");
        return 1;
    }

    // Ensure even dimensions for YUV 4:2:0
    width  = (width  / 2) * 2;
    height = (height / 2) * 2;

    int cwidth = width / 2;
    int cheight = height / 2;

    printf("Generating: %s (%dx%d, %d frames, YUV 4:2:0)\n",
           output, width, height, num_frames);

    // Allocate buffers
    long y_size = (long)width * height;
    long uv_size = (long)cwidth * cheight;

    unsigned char *y_plane = (unsigned char *)malloc(y_size);
    unsigned char *u_plane = (unsigned char *)malloc(uv_size);
    unsigned char *v_plane = (unsigned char *)malloc(uv_size);

    if (!y_plane || !u_plane || !v_plane) {
        printf("ERROR: Cannot allocate memory\n");
        return 1;
    }

    FILE *fp = fopen(output, "wb");
    if (!fp) {
        printf("ERROR: Cannot create '%s'\n", output);
        return 1;
    }

    for (int f = 0; f < num_frames; f++) {
        generate_y_plane(y_plane, width, height, f);
        generate_uv_planes(u_plane, v_plane, cwidth, cheight, f);

        // Write Y, then U, then V (planar YUV 4:2:0)
        fwrite(y_plane, 1, y_size, fp);
        fwrite(u_plane, 1, uv_size, fp);
        fwrite(v_plane, 1, uv_size, fp);

        printf("  Frame %d/%d written\n", f + 1, num_frames);
    }

    long total_size = num_frames * (y_size + 2 * uv_size);
    printf("Done. File size: %.2f MB\n", total_size / (1024.0 * 1024.0));

    fclose(fp);
    free(y_plane);
    free(u_plane);
    free(v_plane);

    return 0;
}