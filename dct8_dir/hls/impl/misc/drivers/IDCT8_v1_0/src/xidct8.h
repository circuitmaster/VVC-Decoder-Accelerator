// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XIDCT8_H
#define XIDCT8_H

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
#include "xidct8_hw.h"

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
} XIdct8_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XIdct8;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XIdct8_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XIdct8_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XIdct8_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XIdct8_ReadReg(BaseAddress, RegOffset) \
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
int XIdct8_Initialize(XIdct8 *InstancePtr, UINTPTR BaseAddress);
XIdct8_Config* XIdct8_LookupConfig(UINTPTR BaseAddress);
#else
int XIdct8_Initialize(XIdct8 *InstancePtr, u16 DeviceId);
XIdct8_Config* XIdct8_LookupConfig(u16 DeviceId);
#endif
int XIdct8_CfgInitialize(XIdct8 *InstancePtr, XIdct8_Config *ConfigPtr);
#else
int XIdct8_Initialize(XIdct8 *InstancePtr, const char* InstanceName);
int XIdct8_Release(XIdct8 *InstancePtr);
#endif

void XIdct8_Start(XIdct8 *InstancePtr);
u32 XIdct8_IsDone(XIdct8 *InstancePtr);
u32 XIdct8_IsIdle(XIdct8 *InstancePtr);
u32 XIdct8_IsReady(XIdct8 *InstancePtr);
void XIdct8_Continue(XIdct8 *InstancePtr);
void XIdct8_EnableAutoRestart(XIdct8 *InstancePtr);
void XIdct8_DisableAutoRestart(XIdct8 *InstancePtr);

void XIdct8_Set_in_r(XIdct8 *InstancePtr, u64 Data);
u64 XIdct8_Get_in_r(XIdct8 *InstancePtr);
void XIdct8_Set_out_r(XIdct8 *InstancePtr, u64 Data);
u64 XIdct8_Get_out_r(XIdct8 *InstancePtr);
void XIdct8_Set_block_size(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_block_size(XIdct8 *InstancePtr);
void XIdct8_Set_sIn(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_sIn(XIdct8 *InstancePtr);
void XIdct8_Set_size(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_size(XIdct8 *InstancePtr);
void XIdct8_Set_shift(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_shift(XIdct8 *InstancePtr);
void XIdct8_Set_oMin(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_oMin(XIdct8 *InstancePtr);
void XIdct8_Set_oMax(XIdct8 *InstancePtr, u32 Data);
u32 XIdct8_Get_oMax(XIdct8 *InstancePtr);

void XIdct8_InterruptGlobalEnable(XIdct8 *InstancePtr);
void XIdct8_InterruptGlobalDisable(XIdct8 *InstancePtr);
void XIdct8_InterruptEnable(XIdct8 *InstancePtr, u32 Mask);
void XIdct8_InterruptDisable(XIdct8 *InstancePtr, u32 Mask);
void XIdct8_InterruptClear(XIdct8 *InstancePtr, u32 Mask);
u32 XIdct8_InterruptGetEnabled(XIdct8 *InstancePtr);
u32 XIdct8_InterruptGetStatus(XIdct8 *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
