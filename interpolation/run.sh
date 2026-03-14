#!/bin/bash
# ============================================================
# VVC Fractional Interpolation Testbench — Build & Run Script
# (with latency instrumentation)
# ============================================================
set -e

YUV_FILE="${1:-video_1920x1080.yuv}"
WIDTH=1920
HEIGHT=1080
NUM_FRAMES=72
MODE="${2:-random}"
BINARY="vvc_tb"

echo "============================================================"
echo " VVC Fractional Interpolation Testbench (with Latency)"
echo "============================================================"

echo "[1/4] Checking source files..."
MISSING=0
for f in video_testbench.cpp vvc_fractional_interp.cpp vvc_fractional_interp.h; do
    if [ ! -f "$f" ]; then echo "  ERROR: Missing '$f'"; MISSING=1
    else echo "  OK: $f"; fi
done
if [ $MISSING -ne 0 ]; then echo "Put all three files in the same directory."; exit 1; fi

echo ""
echo "[2/4] Checking YUV input file..."
if [ ! -f "$YUV_FILE" ]; then
    echo "  ERROR: YUV file not found: '$YUV_FILE'"
    echo "  Convert any video: ffmpeg -i input.mp4 -pix_fmt yuv420p -frames:v 3 $YUV_FILE"
    exit 1
fi
EXPECTED_SIZE=$(( WIDTH * HEIGHT * 3 / 2 ))
ACTUAL_SIZE=$(wc -c < "$YUV_FILE")
if [ "$ACTUAL_SIZE" -lt "$EXPECTED_SIZE" ]; then
    echo "  WARNING: File smaller than one frame — check resolution settings."
else
    FRAMES_AVAILABLE=$(( ACTUAL_SIZE / EXPECTED_SIZE ))
    echo "  OK: $YUV_FILE  ($FRAMES_AVAILABLE frame(s) at ${WIDTH}x${HEIGHT})"
    if [ "$NUM_FRAMES" -gt "$FRAMES_AVAILABLE" ]; then
        echo "  Adjusting NUM_FRAMES → $FRAMES_AVAILABLE"
        NUM_FRAMES=$FRAMES_AVAILABLE
    fi
fi

echo ""
echo "[3/4] Compiling..."
# -lrt needed on Linux for clock_gettime; harmless on macOS
g++ -std=c++11 -O2 -Wall \
    -o "$BINARY" \
    video_testbench.cpp \
    vvc_fractional_interp.cpp \
    -lm -lrt 2>/dev/null || \
g++ -std=c++11 -O2 -Wall \
    -o "$BINARY" \
    video_testbench.cpp \
    vvc_fractional_interp.cpp \
    -lm
echo "  OK: Built '$BINARY'"

echo ""
echo "[4/4] Running testbench..."
echo "  File:    $YUV_FILE"
echo "  Size:    ${WIDTH}x${HEIGHT}"
echo "  Frames:  $NUM_FRAMES"
echo "  Mode:    $MODE"
echo ""

./"$BINARY" "$YUV_FILE" "$WIDTH" "$HEIGHT" "$NUM_FRAMES" "$MODE"
EXIT_CODE=$?

echo ""
if [ $EXIT_CODE -eq 0 ]; then echo "✓  Testbench PASSED"
else echo "✗  Testbench FAILED (exit code $EXIT_CODE)"; fi
exit $EXIT_CODE