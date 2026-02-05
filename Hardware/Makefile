#
# this file was created by a computer. trust it.
#

# compiler tools
XILINX_VITIS ?= /tools/Xilinx/Vitis/2022.2
#XILINX_VITIS ?= /tools/Xilinx/Vitis/2024.2
XILINX_XRT ?= /opt/xilinx/xrt
XILINX_VIVADO ?= /tools/Xilinx/Vivado/2022.2
#XILINX_VIVADO ?= /tools/Xilinx/Vivado/2024.2
XILINX_HLS ?= $(XILINX_VITIS)/Vivado_HLS
#XILINX_HLS ?= /tools/Xilinx/Vitis/Vitis_HLS

VPP ?= ${XILINX_VITIS}/bin/v++
RM = rm -f
RMDIR = rm -rf

VITIS_PLATFORM = xilinx_u2_gen3x4_xdma_gc_2_202110_1
VITIS_PLATFORM_PATH = $(VITIS_PLATFORM)

TARGET = hw
VPP_OPTS = --target $(TARGET)

#
# Hw kernel files
#


BUILD_SUBDIRS += build

HW_KERNEL_OBJS += build/idct2.xo
SRC_KERNEL_OBJS += build/idct2.xo

ALL_MESSAGE_FILES = $(subst .xo,.o,.mdb,$(SRC_KERNEL_OBJS))

#
# primary build targets
#

.PHONY: all clean
all: $(HW_KERNEL_OBJS)


clean:
	-$(RM) $(SRC_KERNEL_OBJS) $(ALL_MESSAGE_FILES) 
	-$(RMDIR) $(BUILD_SUBDIRS)
	-$(RMDIR) .Xil

.PHONY: incremental
incremental: all


nothing:

#
# Hw Kernels compile;
#
build/idct2.xo: ../src/IDCT2.cpp dct-compile.cfg
	-@mkdir -p $(@D)
	-@$(RM) $@
	$(VPP) $(VPP_OPTS) --compile -I"$(<D)" --config dct-compile.cfg -o"$@" "$<"

build/idct8.xo: ../src/IDCT8.cpp dct8-compile.cfg
	-@mkdir -p $(@D)
	-@$(RM) $@
	$(VPP) $(VPP_OPTS) --compile -I"$(<D)" --config dct8-compile.cfg -o"$@" "$<"

build/idst7.xo: ../src/IDST7.cpp dst7-compile.cfg
	-@mkdir -p $(@D)
	-@$(RM) $@
	$(VPP) $(VPP_OPTS) --compile -I"$(<D)" --config dst7-compile.cfg -o"$@" "$<"

build/idctcomb.xo: ../src/IDCT_Com.cpp dctcomb-compile.cfg
	-@mkdir -p $(@D)
	-@$(RM) $@
	$(VPP) $(VPP_OPTS) --compile -I"$(<D)" --config dctcomb-compile.cfg -o"$@" "$<"

build/idctcomb_mahir.xo: ../src/IDCT_Com.cpp dctcomb-compile-mahir.cfg
	-@mkdir -p $(@D)
	-@$(RM) $@
	$(VPP) $(VPP_OPTS) -c --mode hls --config dctcomb-compile-mahir.cfg --work_dir ../dctcomb_dir/
	vitis-run --mode hls --package --config dctcomb-compile-mahir.cfg --work_dir ../dctcomb_dir/