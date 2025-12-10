// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xidst7.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XIdst7_CfgInitialize(XIdst7 *InstancePtr, XIdst7_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XIdst7_Start(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XIdst7_IsDone(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XIdst7_IsIdle(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XIdst7_IsReady(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XIdst7_Continue(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XIdst7_EnableAutoRestart(XIdst7 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XIdst7_DisableAutoRestart(XIdst7 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_AP_CTRL, 0);
}

void XIdst7_Set_in_r(XIdst7 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdst7_Get_in_r(XIdst7 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XIdst7_Set_out_r(XIdst7 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdst7_Get_out_r(XIdst7 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XIdst7_Set_block_size(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_BLOCK_SIZE_DATA, Data);
}

u32 XIdst7_Get_block_size(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_BLOCK_SIZE_DATA);
    return Data;
}

void XIdst7_Set_sIn(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SIN_DATA, Data);
}

u32 XIdst7_Get_sIn(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SIN_DATA);
    return Data;
}

void XIdst7_Set_size(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XIdst7_Get_size(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XIdst7_Set_shift(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SHIFT_DATA, Data);
}

u32 XIdst7_Get_shift(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_SHIFT_DATA);
    return Data;
}

void XIdst7_Set_oMin(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OMIN_DATA, Data);
}

u32 XIdst7_Get_oMin(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OMIN_DATA);
    return Data;
}

void XIdst7_Set_oMax(XIdst7 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OMAX_DATA, Data);
}

u32 XIdst7_Get_oMax(XIdst7 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_OMAX_DATA);
    return Data;
}

void XIdst7_InterruptGlobalEnable(XIdst7 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_GIE, 1);
}

void XIdst7_InterruptGlobalDisable(XIdst7 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_GIE, 0);
}

void XIdst7_InterruptEnable(XIdst7 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IER);
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IER, Register | Mask);
}

void XIdst7_InterruptDisable(XIdst7 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IER);
    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IER, Register & (~Mask));
}

void XIdst7_InterruptClear(XIdst7 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdst7_WriteReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_ISR, Mask);
}

u32 XIdst7_InterruptGetEnabled(XIdst7 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_IER);
}

u32 XIdst7_InterruptGetStatus(XIdst7 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdst7_ReadReg(InstancePtr->Control_BaseAddress, XIDST7_CONTROL_ADDR_ISR);
}

