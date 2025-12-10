// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2024.2 (64-bit)
// Tool Version Limit: 2024.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2024 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xidst7.h"

extern XIdst7_Config XIdst7_ConfigTable[];

#ifdef SDT
XIdst7_Config *XIdst7_LookupConfig(UINTPTR BaseAddress) {
	XIdst7_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XIdst7_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XIdst7_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XIdst7_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdst7_Initialize(XIdst7 *InstancePtr, UINTPTR BaseAddress) {
	XIdst7_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdst7_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdst7_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XIdst7_Config *XIdst7_LookupConfig(u16 DeviceId) {
	XIdst7_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIDST7_NUM_INSTANCES; Index++) {
		if (XIdst7_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XIdst7_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdst7_Initialize(XIdst7 *InstancePtr, u16 DeviceId) {
	XIdst7_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdst7_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdst7_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

