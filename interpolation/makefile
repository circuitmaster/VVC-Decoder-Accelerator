# =============================================================
# Makefile — VVC Fractional Interpolation, Vitis HLS 2024.2
# =============================================================
#
# Targets:
#   make hls        — run C synthesis, print resource + timing report
#   make gui        — open project in Vitis HLS GUI (after make hls)
#   make csim       — run C simulation only (needs a YUV file)
#   make all        — hls (default)
#   make clean      — remove all generated files
#   make help       — print this message
#
# Usage:
#   make hls
#   make gui
#   YUV=MyVideo_1920x1080.yuv make csim
# =============================================================

# -------------------------------------------------------------
# Tool paths — adjust if Vitis is installed elsewhere
# -------------------------------------------------------------
XILINX_HLS     := /tools/Xilinx/Vitis_HLS/2024.2
VITIS_HLS      := $(XILINX_HLS)/bin/vitis_hls
SETTINGS       := $(XILINX_HLS)/settings64.sh

# -------------------------------------------------------------
# Project config
# -------------------------------------------------------------
PROJ_NAME      := vvc_interp_hls
SOLUTION       := solution1
TOP_FUNC       := vvc_fractional_interp
TCL_SCRIPT     := run_hls.tcl

# Report we care about most
SYNTH_RPT      := $(PROJ_NAME)/$(SOLUTION)/syn/report/$(TOP_FUNC)_csynth.rpt

# YUV file for csim (override on command line: YUV=xxx.yuv make csim)
YUV            ?= ParkScene_1920x1080_24.yuv
YUV_W          := 1920
YUV_H          := 1080
YUV_FRAMES     := 1

# -------------------------------------------------------------
# Colours for terminal output
# -------------------------------------------------------------
BOLD  := \033[1m
GREEN := \033[0;32m
CYAN  := \033[0;36m
RED   := \033[0;31m
RESET := \033[0m

# =============================================================
# Default target
# =============================================================
.PHONY: all
all: hls

# =============================================================
# hls — C Synthesis
# =============================================================
.PHONY: hls
hls: check-tools $(SYNTH_RPT)

$(SYNTH_RPT): run_hls.tcl vvc_fractional_interp.cpp vvc_fractional_interp.h
	@echo ""
	@echo "$(BOLD)$(CYAN)=== Vitis HLS 2024.2 — C Synthesis ===$(RESET)"
	@echo "  Top function : $(TOP_FUNC)"
	@echo "  Project      : $(PROJ_NAME)"
	@echo "  Tcl script   : $(TCL_SCRIPT)"
	@echo ""
	@bash -c "source $(SETTINGS) && $(VITIS_HLS) -f $(TCL_SCRIPT)" 2>&1 | tee build_hls.log
	@echo ""
	@if [ -f "$(SYNTH_RPT)" ]; then \
	    echo "$(BOLD)$(GREEN)=== Synthesis Report Summary ===$(RESET)"; \
	    echo ""; \
	    echo "$(BOLD)--- Timing ---$(RESET)"; \
	    grep -A 5 "Timing Summary" $(SYNTH_RPT) || true; \
	    echo ""; \
	    echo "$(BOLD)--- Resource Utilization ---$(RESET)"; \
	    grep -A 20 "Utilization Estimates" $(SYNTH_RPT) | head -30 || true; \
	    echo ""; \
	    echo "$(BOLD)--- Latency ---$(RESET)"; \
	    grep -A 15 "Latency Summary" $(SYNTH_RPT) | head -20 || true; \
	    echo ""; \
	    echo "$(GREEN)Full report: $(SYNTH_RPT)$(RESET)"; \
	else \
	    echo "$(RED)ERROR: Synthesis report not found. Check build_hls.log$(RESET)"; \
	    exit 1; \
	fi

# =============================================================
# csim — C Simulation only (no synthesis)
# =============================================================
.PHONY: csim
csim: check-tools check-yuv
	@echo ""
	@echo "$(BOLD)$(CYAN)=== Vitis HLS — C Simulation ===$(RESET)"
	@echo "  YUV file : $(YUV)"
	@echo ""
	@bash -c "source $(SETTINGS) && $(VITIS_HLS) -f run_csim.tcl \
	    -tclargs $(YUV) $(YUV_W) $(YUV_H) $(YUV_FRAMES)" 2>&1 | tee build_csim.log

# =============================================================
# gui — Open project in Vitis HLS GUI
# =============================================================
.PHONY: gui
gui: check-tools
	@if [ ! -d "$(PROJ_NAME)" ]; then \
	    echo "$(RED)Project '$(PROJ_NAME)' not found.$(RESET)"; \
	    echo "Run 'make hls' first to create it."; \
	    exit 1; \
	fi
	@echo "$(CYAN)Opening Vitis HLS GUI...$(RESET)"
	@bash -c "source $(SETTINGS) && $(VITIS_HLS) -p $(PROJ_NAME)" &

# =============================================================
# report — Print synthesis report to terminal without rebuilding
# =============================================================
.PHONY: report
report:
	@if [ ! -f "$(SYNTH_RPT)" ]; then \
	    echo "$(RED)No report found. Run 'make hls' first.$(RESET)"; exit 1; \
	fi
	@echo "$(BOLD)=== Timing ===$(RESET)"
	@grep -A 5  "Timing Summary"       $(SYNTH_RPT) || true
	@echo ""
	@echo "$(BOLD)=== Utilization ===$(RESET)"
	@grep -A 25 "Utilization Estimates" $(SYNTH_RPT) | head -35 || true
	@echo ""
	@echo "$(BOLD)=== Latency ===$(RESET)"
	@grep -A 15 "Latency Summary"      $(SYNTH_RPT) | head -20 || true
	@echo ""
	@echo "Full report: $(SYNTH_RPT)"

# =============================================================
# Sanity checks
# =============================================================
.PHONY: check-tools
check-tools:
	@if [ ! -f "$(SETTINGS)" ]; then \
	    echo "$(RED)ERROR: Vitis HLS not found at $(XILINX_HLS)$(RESET)"; \
	    echo "Set XILINX_HLS=/your/path/to/Vitis_HLS/2024.2"; \
	    exit 1; \
	fi
	@if [ ! -f "$(VITIS_HLS)" ]; then \
	    echo "$(RED)ERROR: 'vitis_hls' binary not found at $(VITIS_HLS)$(RESET)"; \
	    exit 1; \
	fi
	@if [ ! -f "vvc_fractional_interp.cpp" ]; then \
	    echo "$(RED)ERROR: vvc_fractional_interp.cpp not found in current directory$(RESET)"; \
	    exit 1; \
	fi
	@if [ ! -f "vvc_fractional_interp.h" ]; then \
	    echo "$(RED)ERROR: vvc_fractional_interp.h not found in current directory$(RESET)"; \
	    exit 1; \
	fi
	@if [ ! -f "$(TCL_SCRIPT)" ]; then \
	    echo "$(RED)ERROR: $(TCL_SCRIPT) not found in current directory$(RESET)"; \
	    exit 1; \
	fi

.PHONY: check-yuv
check-yuv:
	@if [ ! -f "$(YUV)" ]; then \
	    echo "$(RED)ERROR: YUV file '$(YUV)' not found.$(RESET)"; \
	    echo "  Either copy it here or override: YUV=myfile.yuv make csim"; \
	    exit 1; \
	fi

# =============================================================
# Clean
# =============================================================
.PHONY: clean
clean:
	@echo "$(CYAN)Cleaning generated files...$(RESET)"
	rm -rf $(PROJ_NAME)
	rm -f  build_hls.log build_csim.log
	rm -rf .Xil vivado*.log vivado*.jou
	@echo "Done."

# =============================================================
# Help
# =============================================================
.PHONY: help
help:
	@echo ""
	@echo "$(BOLD)VVC Fractional Interpolation — Vitis HLS 2024.2 Makefile$(RESET)"
	@echo ""
	@echo "  $(BOLD)make hls$(RESET)              Run C synthesis → get LUT/FF/DSP/timing report"
	@echo "  $(BOLD)make gui$(RESET)              Open project in Vitis HLS GUI (run make hls first)"
	@echo "  $(BOLD)make report$(RESET)           Re-print synthesis report without rebuilding"
	@echo "  $(BOLD)make csim$(RESET)             Run C simulation only"
	@echo "  $(BOLD)make clean$(RESET)            Remove all generated files"
	@echo ""
	@echo "  Override HLS path:     $(BOLD)XILINX_HLS=/my/path make hls$(RESET)"
	@echo "  Override YUV for sim:  $(BOLD)YUV=my_video.yuv make csim$(RESET)"
	@echo ""
	@echo "  Part: xczu9eg-ffvb1156-2-e (ZCU102)"
	@echo "  Edit run_hls.tcl to change part or clock target."
	@echo ""