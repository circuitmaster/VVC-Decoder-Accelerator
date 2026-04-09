# 2D IDCT-II on AIE-ML (64x64 Block Transform)

Pipelined two-pass 64x64 inverse discrete cosine transform (Type II) targeting
the AMD Versal AIE-ML tile array on the VEK280 platform.

## Architecture Overview

Each **engine** occupies one AIE-ML column and contains:

- **NUM_CU** horizontal--vertical kernel pairs (compute units)
- Two L2 shared buffers (memory tiles): one for input staging, one for output
  collection, both double-buffered (ping/pong)
- **NUM_GMIO_PORTS** = 2^GMIO_LEVEL GMIO channels per engine for DDR access

The design is replicated across **NUM_ENGINE** columns. All parameters are
set in `src/reshape.h` and `src/graph.h`, and `GMIO_LEVEL` is passed at
build time.

## Source Files

| File | Description |
|------|-------------|
| `src/idct_ii.h` | Kernel class declarations (H and V transform) |
| `src/idct_ii.cpp` | Kernel implementations (tiled MMA with tensor descriptors) |
| `src/graph.h` | AIE graph: engine instantiation, placement, connectivity |
| `src/reshape.h` | DMA tiling/reshape buffer descriptors, design constants |
| `src/coeff.h` | Pre-computed 64x64 IDCT-II coefficient matrices (int8) |
| `src/aiesim_graph_2d.cpp` | AIE simulation testbench with reference comparison |
| `sw/host_aie_2d.cpp` | XRT host application for hardware execution |
| `Makefile` | Build, simulate, and package targets |

## Prerequisites

- Vitis 2025.2 (or compatible) with AIE-ML support
- VEK280 base platform (`xilinx_vek280_base_202520_1`)
- For hardware flow: Petalinux SDK cross-compiler (sets `CXX`, `SDKTARGETSYSROOT`)

Source the Vitis and SDK environment before building:

```bash
source /tools/Xilinx/2025.2/Vitis/settings64.sh
# For hw flow only:
source <petalinux-sdk>/environment-setup-aarch64-xilinx-linux
```

## Build Parameters

| Variable | Default | Description |
|----------|---------|-------------|
| `TARGET` | `hw` | Build target: `hw` or `hw_emu` |
| `GMIO_LEVEL` | `0` | GMIO parallelism: 0 = 1 port, 1 = 2 ports, 2 = 4 ports per engine |

Pass at build time as a make variable:

```bash
make <target> GMIO_LEVEL=1
```

## Simulation Flow

### 1. Compile the AIE graph

```bash
make libadf_2d.a GMIO_LEVEL=0
```

This runs `v++ -c` with the AIE compiler, producing the compiled graph
archive.  The preprocessor receives `-DGMIO_LEVEL=<value>` so that
`reshape.h` configures the correct number of GMIO ports and DMA patterns.

### 2. Run the AIE simulator

```bash
make sim_2d
```

This launches `aiesimulator` against the compiled graph. The testbench
(`src/aiesim_graph_2d.cpp`):

1. Generates synthetic 64x64 input blocks
2. Computes a software reference 2D IDCT (horizontal pass then vertical pass)
3. Scatters input data across `NUM_GMIO_PORTS` port buffers
4. Runs the graph for `N_ITERS_2D` iterations
5. Gathers per-port output and compares against reference
6. Reports **SIM PASS** or **SIM FAIL** with mismatch details

By default the testbench uses a 256x256 quick-sim frame (16 blocks).
Uncomment `// #define QUICK_SIM` in `aiesim_graph_2d.cpp` to test a full
1920x1080 frame.

### 3. View simulation results

```bash
make aieviz
```

Opens Vitis Analyzer on the simulation run summary (profile + VCD trace).

## Hardware Flow

### 1. Compile and link

```bash
make libadf_2d.a GMIO_LEVEL=1        # AIE compile
make idct_ii_2d_aie.xsa GMIO_LEVEL=1 # AIE link -> XSA
```

### 2. Build the host application

Requires the Petalinux cross-compiler:

```bash
make host_2d GMIO_LEVEL=1
```

The host code (`sw/host_aie_2d.cpp`) receives the same `-DGMIO_LEVEL`
define so that buffer allocation and GMIO name strings match the compiled
graph.

### 3. Package for SD card boot

```bash
make package_2d GMIO_LEVEL=1
```

Produces `idct_ii_2d_aie.xclbin` with the host binary packaged into a
bootable SD card image.

### 4. Run on VEK280

Boot the board from the SD card, then:

```bash
cd /run/media/mmcblk0p1
./host_aie_2d.exe idct_ii_2d_aie.xclbin
```

The host application:

1. Loads the xclbin and obtains a graph handle
2. Packs a 1920x1080 test frame into 64x64 blocks
3. Allocates XRT buffer objects: one input BO and one output BO per GMIO port
   per engine (`NUM_ENGINE * NUM_GMIO_PORTS` each)
4. Scatters input data into per-port BOs (linear split per iteration)
5. Runs 2 warm-up iterations, then a timed iteration
6. Reports latency, bandwidth, and frames per second

## GMIO Scaling

The `GMIO_LEVEL` parameter controls how many parallel GMIO DMA channels feed
each engine's L2 shared buffer:

| GMIO_LEVEL | Ports per engine | Total GMIO (4 engines) |
|------------|-----------------|------------------------|
| 0 | 1 | 4 in + 4 out |
| 1 | 2 | 8 in + 8 out |
| 2 | 4 | 16 in + 16 out |

Each port carries an equal share of the data. Increasing `GMIO_LEVEL`
scales DDR bandwidth proportionally but consumes additional GMIO routing
resources.

**Constraint:** `NUM_CU * N_WINDOWS_2D` must be divisible by
`2^GMIO_LEVEL` (enforced by `static_assert` in `reshape.h`).

## Cleaning Build Artifacts

```bash
make clean
```

Removes all generated files under the project directory except `src/`,
`sw/`, and the `Makefile`.
