// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XIDST7_H
#define XIDST7_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xidst7_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XIdst7_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XIdst7;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XIdst7_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XIdst7_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XIdst7_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XIdst7_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XIdst7_Initialize(XIdst7 *InstancePtr, UINTPTR BaseAddress);
XIdst7_Config* XIdst7_LookupConfig(UINTPTR BaseAddress);
#else
int XIdst7_Initialize(XIdst7 *InstancePtr, u16 DeviceId);
XIdst7_Config* XIdst7_LookupConfig(u16 DeviceId);
#endif
int XIdst7_CfgInitialize(XIdst7 *InstancePtr, XIdst7_Config *ConfigPtr);
#else
int XIdst7_Initialize(XIdst7 *InstancePtr, const char* InstanceName);
int XIdst7_Release(XIdst7 *InstancePtr);
#endif

void XIdst7_Start(XIdst7 *InstancePtr);
u32 XIdst7_IsDone(XIdst7 *InstancePtr);
u32 XIdst7_IsIdle(XIdst7 *InstancePtr);
u32 XIdst7_IsReady(XIdst7 *InstancePtr);
void XIdst7_Continue(XIdst7 *InstancePtr);
void XIdst7_EnableAutoRestart(XIdst7 *InstancePtr);
void XIdst7_DisableAutoRestart(XIdst7 *InstancePtr);

void XIdst7_Set_in_r(XIdst7 *InstancePtr, u64 Data);
u64 XIdst7_Get_in_r(XIdst7 *InstancePtr);
void XIdst7_Set_out_r(XIdst7 *InstancePtr, u64 Data);
u64 XIdst7_Get_out_r(XIdst7 *InstancePtr);
void XIdst7_Set_block_size(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_block_size(XIdst7 *InstancePtr);
void XIdst7_Set_sIn(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_sIn(XIdst7 *InstancePtr);
void XIdst7_Set_size(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_size(XIdst7 *InstancePtr);
void XIdst7_Set_shift(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_shift(XIdst7 *InstancePtr);
void XIdst7_Set_oMin(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_oMin(XIdst7 *InstancePtr);
void XIdst7_Set_oMax(XIdst7 *InstancePtr, u32 Data);
u32 XIdst7_Get_oMax(XIdst7 *InstancePtr);

void XIdst7_InterruptGlobalEnable(XIdst7 *InstancePtr);
void XIdst7_InterruptGlobalDisable(XIdst7 *InstancePtr);
void XIdst7_InterruptEnable(XIdst7 *InstancePtr, u32 Mask);
void XIdst7_InterruptDisable(XIdst7 *InstancePtr, u32 Mask);
void XIdst7_InterruptClear(XIdst7 *InstancePtr, u32 Mask);
u32 XIdst7_InterruptGetEnabled(XIdst7 *InstancePtr);
u32 XIdst7_InterruptGetStatus(XIdst7 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
