# VVC-Decoder-Accelerator

## Project Description

This project focuses on the design and performance comparison of the inverse transform core of VVC (Versatile Video Coding) implemented on programmable logic (PL) and AI Engines (AIE). The accelerator targets Xilinx Versal platforms and explores hardware acceleration of compute-intensive VVC decoding operations, including IDCT2, IDCT8, IDST7, and fractional interpolation filters.

---

## AI Engine Implementation

For the AIE-ML native implementation of the 2D IDCT-II (64x64 block transform)
on the VEK280 platform, including simulation and hardware flow instructions,
see [`AI_Engine_Impl/idct_ii/README.md`](AI_Engine_Impl/idct_ii/README.md).

---

## Requirements

| Platform | Vitis Version |
|----------|--------------|
| VCK5000  | 2022.2       |
| VEK280   | 2025.2       |

---

## Building Hardware Kernels

```bash
cd Hardware
```

| Kernel | Command |
|--------|---------|
| IDCT2 | `make -j20 build/idct2.xo` |
| IDCT Combined (IDCT8 + IDST7) | `make -j20 build/idctcomb.xo` |
| Interpolation (frame-wise) | `make -j20 build/interpolation_frame.xo` |

> **Note:** `idct8.xo` and `idst7.xo` are deprecated. `idctcomb.xo` handles both IDCT8 and IDST7 due to the computational similarity between the two functions.

> **Note:** `interpolation.xo` applies block-wise interpolation instead of frame-wise, which resulted in lower throughput and has been deprecated in favor of `interpolation_frame.xo`.

---

## Linking Hardware Kernels

```bash
cd hw_link
```

Different link targets are available depending on the desired configuration:

| Target | Command | Description |
|--------|---------|-------------|
| IDCT2 only | `make idct2.xsa` | Links only the IDCT2 function |
| Full transform core | `make vvc_decoder.xsa` | Links IDCT2, IDCT8, and IDST7 |
| Interpolation filter | `make vvc_interp_frame.xsa` | Links the frame-wise interpolation filter |

---

## Testing Results

```bash
cd host
```

### Preparing the xclbin

Navigate to the build output directory and copy the compiled xclbin to the target server:

```bash
cd hw_link/<hardware>.build/link/int/
scp <xclbin_name>.xclbin <server_ip>:<path>
```

### Test Targets

**IDCT2 — bandwidth, scalability, and golden comparison:**

```bash
make idct2_test
# Copy binary to host processor, then:
./idct2_test <arguments>
```

**IDCT8 and IDST7 — bandwidth, scalability, and golden comparison:**

```bash
make idct8_idst7_test
# Copy binary to host processor, then:
./idct8_idst7_test <arguments>
```

**IDCT2 block size 64 — video streaming pipeline:**

```bash
make idct64_pipeline
# Copy binary to host processor, then:
./idct64_pipeline <arguments>
```

**Interpolation filter — video streaming pipeline:**

```bash
make interpolation_pipeline
# Copy binary to host processor, then:
./interpolation_pipeline <arguments>
```
