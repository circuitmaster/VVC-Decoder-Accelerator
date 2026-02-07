#
# this file was created by a computer. trust it.
#

# compiler tools
XILINX_VITIS ?= /tools/Xilinx/Vitis/2022.2

HOST_CXX ?= g++
EMCONFIGUTIL = ${XILINX_VITIS}/bin/emconfigutil --od .
RM = rm -f
RMDIR = rm -rf

# host compiler global settings
CXXFLAGS += -std=c++1y -D__USE_XOPEN2K8  -I/tools/Xilinx/Vitis_HLS/2022.2/include/ -O0 -g -Wall -c -fmessage-length=0
LDFLAGS +=  -lpthread -lstdc++ -Wl,-rpath-link

#
# host files
#


HOST_OBJECTS += src/host.o

HOST_EXE = main

BUILD_SUBDIRS += src/

EMCONFIG_FILE = emconfig.json

#
# primary build targets
#

.PHONY: all clean
all:  $(HOST_EXE) $(EMCONFIG_FILE)

clean:
	-$(RM) $(HOST_EXE) $(HOST_OBJECTS)

.PHONY: incremental
incremental: all

nothing:

#
# host rules
#


src/host.o: src/host.cpp
	-@mkdir -p $(@D)
	$(HOST_CXX) $(CXXFLAGS) -o "$@" "$<"

$(HOST_EXE): $(HOST_OBJECTS)
	$(HOST_CXX) -o "$@" $(+) $(LDFLAGS)
