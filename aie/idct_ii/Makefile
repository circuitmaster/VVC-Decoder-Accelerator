PFM_NAME := xilinx_vek280_base_202520_1
PFM_NAME := $(strip $(PFM_NAME))
PLATFORM := ${PLATFORM_REPO_PATHS}/${PFM_NAME}/${PFM_NAME}.xpfm

TARGET ?= hw

# Common
WORKDIR   := ./Work
AIEOUTDIR := aiesimulator_output

# AIE compile flags
AIE_FLAGS := -t $(TARGET) --mode aie --platform $(PLATFORM) \
             --include "./src" --aie.workdir $(WORKDIR) \
             --aie.stacksize 1024

# AIE Simulation
AIE_SIM_CMD := aiesimulator --pkg-dir=$(WORKDIR) --profile --dump-vcd trace

# Host (CXX set by sourcing environment-setup-aarch64-xilinx-linux)
HOST_CFLAGS  := -Wall -c -std=c++17 -Wno-int-to-pointer-cast \
                --sysroot=$(SDKTARGETSYSROOT) \
                -I$(SDKTARGETSYSROOT)/usr/include/xrt \
                -I$(SDKTARGETSYSROOT)/usr/include \
                -I./src

HOST_LDFLAGS := -lxrt_coreutil \
                -L$(SDKTARGETSYSROOT)/usr/lib \
                --sysroot=$(SDKTARGETSYSROOT) \
                -std=c++17 -lpthread

# Package
PKG_FLAGS := -t $(TARGET) \
             -f $(PLATFORM) \
             --package.rootfs=$(ROOTFS) \
             --package.image_format=ext4 \
             --package.boot_mode=sd \
             --package.kernel_image=$(IMAGE)

# ============================================================
# 1D IDCT targets
# ============================================================
LIBADF_1D  := libadf_1d.a
XSA_1D     := idct_ii_1d_aie.xsa
GRAPH_1D   := src/aiesim_graph.cpp

AIE_LINK_1D := -t $(TARGET) --platform $(PLATFORM) --save-temps -o $(XSA_1D)

# ============================================================
# 2D IDCT targets
# ============================================================
LIBADF_2D  := libadf_2d.a
XSA_2D     := idct_ii_2d_aie.xsa
GRAPH_2D   := src/aiesim_graph_2d.cpp

AIE_LINK_2D := -t $(TARGET) --platform $(PLATFORM) --save-temps -o $(XSA_2D)

# ============================================================

.PHONY: all 1d 2d sim_1d sim_2d host_1d host_2d package_1d package_2d aieviz clean

all: 1d 2d

# --- 1D IDCT ---
1d: package_1d

$(LIBADF_1D): src/*
	v++ -c $(AIE_FLAGS) --aie.output-archive $(LIBADF_1D) $(GRAPH_1D)

$(XSA_1D): $(LIBADF_1D)
	v++ -l $(AIE_LINK_1D) $(LIBADF_1D)

sim_1d: $(LIBADF_1D)
	$(AIE_SIM_CMD)

host_1d: sw/host_aie.exe
sw/host_aie.exe: sw/host_aie.cpp
	$(CXX) $(HOST_CFLAGS) -o sw/host_aie.o sw/host_aie.cpp
	$(CXX) sw/host_aie.o $(HOST_LDFLAGS) -o sw/host_aie.exe

package_1d: $(XSA_1D) sw/host_aie.exe
	PATH=$(XILINX_VITIS)/bin:$$PATH v++ --package $(PKG_FLAGS) \
		--package.sd_file sw/host_aie.exe \
		-o idct_ii_1d_aie.xclbin \
		$(XSA_1D) $(LIBADF_1D)

# --- 2D IDCT ---
2d: package_2d

$(LIBADF_2D): src/*
	v++ -c $(AIE_FLAGS) --aie.output-archive $(LIBADF_2D) $(GRAPH_2D)

$(XSA_2D): $(LIBADF_2D)
	v++ -l $(AIE_LINK_2D) $(LIBADF_2D)

sim_2d: $(LIBADF_2D)
	$(AIE_SIM_CMD)

host_2d: sw/host_aie_2d.exe
sw/host_aie_2d.exe: sw/host_aie_2d.cpp
	$(CXX) $(HOST_CFLAGS) -o sw/host_aie_2d.o sw/host_aie_2d.cpp
	$(CXX) sw/host_aie_2d.o $(HOST_LDFLAGS) -o sw/host_aie_2d.exe

package_2d: $(XSA_2D) sw/host_aie_2d.exe
	PATH=$(XILINX_VITIS)/bin:$$PATH v++ --package $(PKG_FLAGS) \
		--package.sd_file sw/host_aie_2d.exe \
		-o idct_ii_2d_aie.xclbin \
		$(XSA_2D) $(LIBADF_2D)

# --- Common ---
aieviz:
	vitis_analyzer $(AIEOUTDIR)/default.aierun_summary

clean:
	@echo "Cleaning all build artifacts..."
	@find . -mindepth 1 \
		! -path "./src*" \
		! -path "./sw*" \
		! -name "Makefile" \
		! -name "." \
		-exec rm -rf {} +
