PFM_NAME := xilinx_vek280_base_202520_1
PFM_NAME := $(strip $(PFM_NAME))
PLATFORM := ${PLATFORM_REPO_PATHS}/${PFM_NAME}/${PFM_NAME}.xpfm

TARGET ?= hw

LIBADF    := libadf.a
XSA_AIE   := fir_interp_aie.xsa
WORKDIR   := ./Work
AIEOUTDIR := aiesimulator_output
GRAPH     := src/aiesim_graph.cpp

# AIE compile
AIE_FLAGS := -t $(TARGET) --mode aie --platform $(PLATFORM) \
             --include "./src" --aie.workdir $(WORKDIR) \
             --aie.stacksize 1024

# AIE link
AIE_LINK_FLAGS := -t $(TARGET) --platform $(PLATFORM) --save-temps -o $(XSA_AIE)

# AIE Simulation
AIE_SIM_CMD := aiesimulator --pkg-dir=$(WORKDIR) --profile --dump-vcd trace

# Host
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

.PHONY: all aie sim host package aieviz clean

all: aie host package

$(LIBADF): src/*
	v++ -c $(AIE_FLAGS) $(GRAPH)

$(XSA_AIE): $(LIBADF)
	v++ -l $(AIE_LINK_FLAGS) $(LIBADF)

aie: $(XSA_AIE)

sim: $(LIBADF)
	$(AIE_SIM_CMD)

host: sw/host_aie.exe
sw/host_aie.exe: sw/host_aie.cpp
	$(CXX) $(HOST_CFLAGS) -o sw/host_aie.o sw/host_aie.cpp
	$(CXX) sw/host_aie.o $(HOST_LDFLAGS) -o sw/host_aie.exe

package: $(XSA_AIE) sw/host_aie.exe
	PATH=$(XILINX_VITIS)/bin:$$PATH v++ --package $(PKG_FLAGS) \
		--package.sd_file sw/host_aie.exe \
		-o fir_interp_aie.xclbin \
		$(XSA_AIE) $(LIBADF)

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
