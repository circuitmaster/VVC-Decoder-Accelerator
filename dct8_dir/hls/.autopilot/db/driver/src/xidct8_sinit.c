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
#include "xidct8.h"

extern XIdct8_Config XIdct8_ConfigTable[];

#ifdef SDT
XIdct8_Config *XIdct8_LookupConfig(UINTPTR BaseAddress) {
	XIdct8_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XIdct8_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XIdct8_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XIdct8_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdct8_Initialize(XIdct8 *InstancePtr, UINTPTR BaseAddress) {
	XIdct8_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdct8_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdct8_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XIdct8_Config *XIdct8_LookupConfig(u16 DeviceId) {
	XIdct8_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIDCT8_NUM_INSTANCES; Index++) {
		if (XIdct8_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XIdct8_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XIdct8_Initialize(XIdct8 *InstancePtr, u16 DeviceId) {
	XIdct8_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XIdct8_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XIdct8_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

