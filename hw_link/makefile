#
# this file was created by a computer. trust it.
#

# compiler tools
XILINX_VITIS ?= /tools/Xilinx/Vitis/2022.2
XILINX_XRT ?= /opt/xilinx/xrt
XILINX_VIVADO ?= /tools/Xilinx/Vivado/2022.2
XILINX_HLS ?= $(XILINX_VITIS)/Vivado_HLS

VPP_LINKER ?= ${XILINX_VITIS}/bin/v++
RM = rm -f
RMDIR = rm -rf

VITIS_PLATFORM = /tools/Xilinx/Vitis/2022.2/base_platforms/xilinx_zcu102_base_202220_1/xilinx_zcu102_base_202220_1.xpfm
VITIS_PLATFORM_PATH = $(VITIS_PLATFORM)

VPP_OPTS = --target hw

#
# Hw kernel files
#

BINARY_CONTAINERS += vvc_decoder.xclbin

BUILD_SUBDIRS += vvc_decoder.build
vvc_decoder_OBJS += ../../xilinx_idct2_kernels/Hardware/build/IDCT2.xo
vvc_decoder_OBJS += ../../xilinx_idct8_kernels/Hardware/build/IDCT8.xo
vvc_decoder_OBJS += ../../xilinx_idst7_kernels/Hardware/build/IDST7.xo

ALL_MESSAGE_FILES = $(subst .xclbin,.mdb,$(BINARY_CONTAINERS))

#
# primary build targets
#

.PHONY: all clean
all: $(BINARY_CONTAINERS)


clean:
	-$(RM) $(BINARY_CONTAINERS) $(ALL_MESSAGE_FILES) 
	-$(RM) *.xclbin.sh *.xclbin.info *.xclbin.link_summary*
	-$(RMDIR) $(BUILD_SUBDIRS)
	-$(RMDIR) .Xil


nothing:

#
# binary container: vvc_decoder.xclbin
#

vvc_decoder.xclbin: $(vvc_decoder_OBJS) vvc_decoder-link.cfg
	-@echo $(VPP_LINKER) $(VPP_OPTS) --link --config vvc_decoder-link.cfg -o"$@" $(vvc_decoder_OBJS) > vvc_decoder.xclbin.sh
	$(VPP_LINKER) $(VPP_OPTS) --link --config vvc_decoder-link.cfg -o"$@" $(vvc_decoder_OBJS)