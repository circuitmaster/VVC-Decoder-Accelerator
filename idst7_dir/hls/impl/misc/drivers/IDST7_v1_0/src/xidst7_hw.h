// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 4  - ap_continue (Read/Write/SC)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of in_r
//        bit 31~0 - in_r[31:0] (Read/Write)
// 0x14 : Data signal of in_r
//        bit 31~0 - in_r[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of out_r
//        bit 31~0 - out_r[31:0] (Read/Write)
// 0x20 : Data signal of out_r
//        bit 31~0 - out_r[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of block_size
//        bit 31~0 - block_size[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of sIn
//        bit 31~0 - sIn[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of size
//        bit 31~0 - size[31:0] (Read/Write)
// 0x3c : reserved
// 0x40 : Data signal of shift
//        bit 31~0 - shift[31:0] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of oMin
//        bit 31~0 - oMin[31:0] (Read/Write)
// 0x4c : reserved
// 0x50 : Data signal of oMax
//        bit 31~0 - oMax[31:0] (Read/Write)
// 0x54 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XIDST7_CONTROL_ADDR_AP_CTRL         0x00
#define XIDST7_CONTROL_ADDR_GIE             0x04
#define XIDST7_CONTROL_ADDR_IER             0x08
#define XIDST7_CONTROL_ADDR_ISR             0x0c
#define XIDST7_CONTROL_ADDR_IN_R_DATA       0x10
#define XIDST7_CONTROL_BITS_IN_R_DATA       64
#define XIDST7_CONTROL_ADDR_OUT_R_DATA      0x1c
#define XIDST7_CONTROL_BITS_OUT_R_DATA      64
#define XIDST7_CONTROL_ADDR_BLOCK_SIZE_DATA 0x28
#define XIDST7_CONTROL_BITS_BLOCK_SIZE_DATA 32
#define XIDST7_CONTROL_ADDR_SIN_DATA        0x30
#define XIDST7_CONTROL_BITS_SIN_DATA        32
#define XIDST7_CONTROL_ADDR_SIZE_DATA       0x38
#define XIDST7_CONTROL_BITS_SIZE_DATA       32
#define XIDST7_CONTROL_ADDR_SHIFT_DATA      0x40
#define XIDST7_CONTROL_BITS_SHIFT_DATA      32
#define XIDST7_CONTROL_ADDR_OMIN_DATA       0x48
#define XIDST7_CONTROL_BITS_OMIN_DATA       32
#define XIDST7_CONTROL_ADDR_OMAX_DATA       0x50
#define XIDST7_CONTROL_BITS_OMAX_DATA       32

