// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xidct8.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XIdct8_CfgInitialize(XIdct8 *InstancePtr, XIdct8_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XIdct8_Start(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XIdct8_IsDone(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XIdct8_IsIdle(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XIdct8_IsReady(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XIdct8_Continue(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL) & 0x80;
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL, Data | 0x10);
}

void XIdct8_EnableAutoRestart(XIdct8 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XIdct8_DisableAutoRestart(XIdct8 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_AP_CTRL, 0);
}

void XIdct8_Set_in_r(XIdct8 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IN_R_DATA, (u32)(Data));
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IN_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdct8_Get_in_r(XIdct8 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IN_R_DATA);
    Data += (u64)XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IN_R_DATA + 4) << 32;
    return Data;
}

void XIdct8_Set_out_r(XIdct8 *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XIdct8_Get_out_r(XIdct8 *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XIdct8_Set_block_size(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_BLOCK_SIZE_DATA, Data);
}

u32 XIdct8_Get_block_size(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_BLOCK_SIZE_DATA);
    return Data;
}

void XIdct8_Set_sIn(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SIN_DATA, Data);
}

u32 XIdct8_Get_sIn(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SIN_DATA);
    return Data;
}

void XIdct8_Set_size(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SIZE_DATA, Data);
}

u32 XIdct8_Get_size(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SIZE_DATA);
    return Data;
}

void XIdct8_Set_shift(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SHIFT_DATA, Data);
}

u32 XIdct8_Get_shift(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_SHIFT_DATA);
    return Data;
}

void XIdct8_Set_oMin(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OMIN_DATA, Data);
}

u32 XIdct8_Get_oMin(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OMIN_DATA);
    return Data;
}

void XIdct8_Set_oMax(XIdct8 *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OMAX_DATA, Data);
}

u32 XIdct8_Get_oMax(XIdct8 *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_OMAX_DATA);
    return Data;
}

void XIdct8_InterruptGlobalEnable(XIdct8 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_GIE, 1);
}

void XIdct8_InterruptGlobalDisable(XIdct8 *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_GIE, 0);
}

void XIdct8_InterruptEnable(XIdct8 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IER);
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IER, Register | Mask);
}

void XIdct8_InterruptDisable(XIdct8 *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IER);
    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IER, Register & (~Mask));
}

void XIdct8_InterruptClear(XIdct8 *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XIdct8_WriteReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_ISR, Mask);
}

u32 XIdct8_InterruptGetEnabled(XIdct8 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_IER);
}

u32 XIdct8_InterruptGetStatus(XIdct8 *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XIdct8_ReadReg(InstancePtr->Control_BaseAddress, XIDCT8_CONTROL_ADDR_ISR);
}

