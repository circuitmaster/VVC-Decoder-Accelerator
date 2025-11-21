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
#include "xidct2.h"

extern XIdct2_Config XIdct2_ConfigTable[];

#ifdef SDT
XIdct2_Config *XIdct2_LookupConfig(UINTPTR BaseAddress) {
	XIdct2_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XIdct2_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XIdct2_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XIdct2_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdct2_Initialize(XIdct2 *InstancePtr, UINTPTR BaseAddress) {
	XIdct2_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdct2_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdct2_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XIdct2_Config *XIdct2_LookupConfig(u16 DeviceId) {
	XIdct2_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIDCT2_NUM_INSTANCES; Index++) {
		if (XIdct2_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XIdct2_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdct2_Initialize(XIdct2 *InstancePtr, u16 DeviceId) {
	XIdct2_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdct2_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdct2_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

