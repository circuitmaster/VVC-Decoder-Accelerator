#
# this file was created by a computer. trust it.
#

# compiler tools
XILINX_VITIS ?= /tools/Xilinx/Vitis/2022.2
XILINX_XRT ?= /opt/xilinx/xrt

HOST_CXX ?= g++
RM = rm -f
RMDIR = rm -rf

VITIS_PLATFORM = xilinx_u2_gen3x4_xdma_gc_2_202110_1
VITIS_PLATFORM_PATH = $(VITIS_PLATFORM)

# host compiler global settings
CXXFLAGS += -std=c++1y -DVITIS_PLATFORM=$(VITIS_PLATFORM) -D__USE_XOPEN2K8 -I$(XILINX_XRT)/include/ -I/tools/Xilinx/Vitis_HLS/2022.2/include/ -O2 -g -Wall -c -fmessage-length=0
LDFLAGS += -lxilinxopencl -lxrt_coreutil -lpthread -lrt -lstdc++ -L$(XILINX_XRT)/lib/ -Wl,-rpath-link,$(XILINX_XRT)/lib

#
# host files
#


HOST_OBJECTS += src/host.o
HOST2_OBJECTS += src/host2.o
HOST3_OBJECTS += src/host3.o
HOST4_OBJECTS += src/host4.o

HOST_EXE = main
HOST2_EXE = main2
HOST3_EXE = main3
HOST4_EXE = main4

BUILD_SUBDIRS += src/
#
# primary build targets
#

.PHONY: all clean
all:  $(HOST_EXE) $(HOST2_EXE) $(HOST3_EXE) $(HOST4_EXE) $(EMCONFIG_FILE)

clean:
	-$(RM) $(HOST_EXE) $(HOST2_EXE) $(HOST3_EXE) $(HOST4_EXE) $(HOST_OBJECTS) $(HOST2_OBJECTS) $(HOST3_OBJECTS) $(HOST4_OBJECTS)

.PHONY: incremental
incremental: all

nothing:

#
# host rules
#


src/host.o: src/host.cpp
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

src/host2.o: src/host2.cpp
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

src/host3.o: src/host3.cpp
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

src/host4.o: src/host4.cpp
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

$(HOST_EXE): $(HOST_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)

$(HOST2_EXE): $(HOST2_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)

$(HOST3_EXE): $(HOST3_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)

$(HOST4_EXE): $(HOST4_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)
