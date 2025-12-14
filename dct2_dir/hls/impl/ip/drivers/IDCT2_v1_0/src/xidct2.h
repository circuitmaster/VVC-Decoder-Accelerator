// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XIDCT2_H
#define XIDCT2_H

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
#include "xidct2_hw.h"

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
} XIdct2_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XIdct2;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XIdct2_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XIdct2_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XIdct2_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XIdct2_ReadReg(BaseAddress, RegOffset) \
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
int XIdct2_Initialize(XIdct2 *InstancePtr, UINTPTR BaseAddress);
XIdct2_Config* XIdct2_LookupConfig(UINTPTR BaseAddress);
#else
int XIdct2_Initialize(XIdct2 *InstancePtr, u16 DeviceId);
XIdct2_Config* XIdct2_LookupConfig(u16 DeviceId);
#endif
int XIdct2_CfgInitialize(XIdct2 *InstancePtr, XIdct2_Config *ConfigPtr);
#else
int XIdct2_Initialize(XIdct2 *InstancePtr, const char* InstanceName);
int XIdct2_Release(XIdct2 *InstancePtr);
#endif

void XIdct2_Start(XIdct2 *InstancePtr);
u32 XIdct2_IsDone(XIdct2 *InstancePtr);
u32 XIdct2_IsIdle(XIdct2 *InstancePtr);
u32 XIdct2_IsReady(XIdct2 *InstancePtr);
void XIdct2_Continue(XIdct2 *InstancePtr);
void XIdct2_EnableAutoRestart(XIdct2 *InstancePtr);
void XIdct2_DisableAutoRestart(XIdct2 *InstancePtr);

void XIdct2_Set_in_r(XIdct2 *InstancePtr, u64 Data);
u64 XIdct2_Get_in_r(XIdct2 *InstancePtr);
void XIdct2_Set_out_r(XIdct2 *InstancePtr, u64 Data);
u64 XIdct2_Get_out_r(XIdct2 *InstancePtr);
void XIdct2_Set_block_size(XIdct2 *InstancePtr, u32 Data);
u32 XIdct2_Get_block_size(XIdct2 *InstancePtr);
void XIdct2_Set_size(XIdct2 *InstancePtr, u32 Data);
u32 XIdct2_Get_size(XIdct2 *InstancePtr);

void XIdct2_InterruptGlobalEnable(XIdct2 *InstancePtr);
void XIdct2_InterruptGlobalDisable(XIdct2 *InstancePtr);
void XIdct2_InterruptEnable(XIdct2 *InstancePtr, u32 Mask);
void XIdct2_InterruptDisable(XIdct2 *InstancePtr, u32 Mask);
void XIdct2_InterruptClear(XIdct2 *InstancePtr, u32 Mask);
u32 XIdct2_InterruptGetEnabled(XIdct2 *InstancePtr);
u32 XIdct2_InterruptGetStatus(XIdct2 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
