// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xidct2.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XIdct2_CfgInitialize(XIdct2 *InstancePtr, XIdct2_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XIdct2_Start(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XIdct2_IsDone(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XIdct2_IsIdle(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XIdct2_IsReady(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XIdct2_Continue(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XIdct2_EnableAutoRestart(XIdct2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XIdct2_DisableAutoRestart(XIdct2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_AP_CTRL, 0);
}

void XIdct2_Set_in_r(XIdct2 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdct2_Get_in_r(XIdct2 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XIdct2_Set_out_r(XIdct2 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdct2_Get_out_r(XIdct2 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XIdct2_Set_block_size(XIdct2 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_BLOCK_SIZE_DATA, Data);
}

u32 XIdct2_Get_block_size(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_BLOCK_SIZE_DATA);
    return Data;
}

void XIdct2_Set_size(XIdct2 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XIdct2_Get_size(XIdct2 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XIdct2_InterruptGlobalEnable(XIdct2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_GIE, 1);
}

void XIdct2_InterruptGlobalDisable(XIdct2 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_GIE, 0);
}

void XIdct2_InterruptEnable(XIdct2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IER);
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IER, Register | Mask);
}

void XIdct2_InterruptDisable(XIdct2 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IER);
    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IER, Register & (~Mask));
}

void XIdct2_InterruptClear(XIdct2 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct2_WriteReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_ISR, Mask);
}

u32 XIdct2_InterruptGetEnabled(XIdct2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_IER);
}

u32 XIdct2_InterruptGetStatus(XIdct2 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdct2_ReadReg(InstancePtr->Control_BaseAddress, XIDCT2_CONTROL_ADDR_ISR);
}

