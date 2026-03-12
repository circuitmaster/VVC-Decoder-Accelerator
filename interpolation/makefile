# ============================================================
# Makefile for VVC Fractional Interpolation Testbench
# ============================================================
# 
# Targets:
#   make csim_basic     - Run basic testbench (all 256 frac positions)
#   make csim_video     - Run video testbench with real YUV file
#   make gen_test_yuv   - Generate synthetic test YUV (no ffmpeg needed)
#   make test_all       - Run everything: generate YUV + both testbenches
#   make hls            - Run Vitis HLS synthesis
#   make clean          - Remove generated files

CXX      = g++
CXXFLAGS = -O2 -Wall -I.
LDFLAGS  = -lm

# Default test video settings
YUV_FILE   ?= test_synthetic_352x288.yuv
YUV_WIDTH  ?= 352
YUV_HEIGHT ?= 288
NUM_FRAMES ?= 3
TEST_MODE  ?= random

# ============================================================
# Compile targets
# ============================================================

# Basic testbench (exhaustive frac position test, no video needed)
tb_basic: vvc_fractional_interp.cpp vvc_fractional_interp_tb.cpp vvc_fractional_interp.h
	$(CXX) $(CXXFLAGS) -o $@ vvc_fractional_interp.cpp vvc_fractional_interp_tb.cpp $(LDFLAGS)

# Video testbench
tb_video: vvc_fractional_interp.cpp video_testbench.cpp vvc_fractional_interp.h
	$(CXX) $(CXXFLAGS) -o $@ vvc_fractional_interp.cpp video_testbench.cpp $(LDFLAGS)

# Synthetic YUV generator
gen_yuv: generate_test_yuv.cpp
	$(CXX) $(CXXFLAGS) -o $@ generate_test_yuv.cpp $(LDFLAGS)

# ============================================================
# Run targets
# ============================================================

# Run basic testbench
csim_basic: tb_basic
	@echo "============================================"
	@echo "Running basic testbench (all 256 frac combos)"
	@echo "============================================"
	./tb_basic

# Generate synthetic test YUV file
gen_test_yuv: gen_yuv
	@echo "============================================"
	@echo "Generating synthetic test YUV: $(YUV_FILE)"
	@echo "============================================"
	./gen_yuv $(YUV_FILE) $(YUV_WIDTH) $(YUV_HEIGHT) $(NUM_FRAMES)

# Run video testbench with synthetic YUV
csim_video: tb_video gen_test_yuv
	@echo "============================================"
	@echo "Running video testbench: $(YUV_FILE)"
	@echo "============================================"
	./tb_video $(YUV_FILE) $(YUV_WIDTH) $(YUV_HEIGHT) $(NUM_FRAMES) $(TEST_MODE)

# Run video testbench with sweep mode (all frac positions)
csim_video_sweep: tb_video gen_test_yuv
	./tb_video $(YUV_FILE) $(YUV_WIDTH) $(YUV_HEIGHT) $(NUM_FRAMES) sweep

# Run video testbench with half-pel only
csim_video_halfpel: tb_video gen_test_yuv
	./tb_video $(YUV_FILE) $(YUV_WIDTH) $(YUV_HEIGHT) $(NUM_FRAMES) halfpel

# Run all tests
test_all: csim_basic csim_video csim_video_sweep
	@echo ""
	@echo "============================================"
	@echo "ALL TESTS COMPLETE"
	@echo "============================================"

# ============================================================
# Run with real test sequences (examples)
# Download sequences first, then use these targets
# ============================================================

# Tennis 1080p (paper's test sequence)
test_tennis: tb_video
	./tb_video Tennis_1920x1080_24.yuv 1920 1080 3 random

# Kimono 1080p (paper's test sequence)  
test_kimono: tb_video
	./tb_video Kimono_1920x1080_24.yuv 1920 1080 3 random

# Use ffmpeg to create test YUV from any video file
# Usage: make convert_video INPUT=myvideo.mp4 OUTPUT=test.yuv W=1920 H=1080 F=3
convert_video:
	ffmpeg -i $(INPUT) -vf "scale=$(W):$(H)" -pix_fmt yuv420p -frames:v $(F) $(OUTPUT)

# ============================================================
# Vitis HLS synthesis
# ============================================================
hls:
	vitis_hls -f run_hls.tcl

# ============================================================
# Cleanup
# ============================================================
clean:
	rm -f tb_basic tb_video gen_yuv
	rm -f *.yuv
	rm -rf vvc_interp_proj
	rm -f *.o *.log

.PHONY: csim_basic csim_video csim_video_sweep csim_video_halfpel \
        gen_test_yuv test_all test_tennis test_kimono hls clean convert_video