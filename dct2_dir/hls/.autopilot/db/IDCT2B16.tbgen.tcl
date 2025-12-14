set moduleName IDCT2B16
set isTopModule 0
set isCombinational 1
set isDatapathOnly 0
set isPipelined 0
set pipeline_type function
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 8
set C_modelName {IDCT2B16}
set C_modelType { int 512 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ in_0_val int 26 regular  }
	{ in_1_val int 32 regular  }
	{ in_2_val int 32 regular  }
	{ in_3_val int 32 regular  }
	{ in_4_val int 32 regular  }
	{ in_5_val int 32 regular  }
	{ in_6_val int 32 regular  }
	{ in_7_val int 32 regular  }
	{ in_8_val int 26 regular  }
	{ in_9_val int 32 regular  }
	{ in_10_val int 32 regular  }
	{ in_11_val int 32 regular  }
	{ in_12_val int 32 regular  }
	{ in_13_val int 32 regular  }
	{ in_14_val int 32 regular  }
	{ in_15_val int 32 regular  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "in_0_val", "interface" : "wire", "bitwidth" : 26, "direction" : "READONLY"} , 
 	{ "Name" : "in_1_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_2_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_3_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_4_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_5_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_6_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_7_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_8_val", "interface" : "wire", "bitwidth" : 26, "direction" : "READONLY"} , 
 	{ "Name" : "in_9_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_10_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_11_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_12_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_13_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_14_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_15_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 512} ]}
# RTL Port declarations: 
set portNum 34
set portList { 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ in_0_val sc_in sc_lv 26 signal 0 } 
	{ in_1_val sc_in sc_lv 32 signal 1 } 
	{ in_2_val sc_in sc_lv 32 signal 2 } 
	{ in_3_val sc_in sc_lv 32 signal 3 } 
	{ in_4_val sc_in sc_lv 32 signal 4 } 
	{ in_5_val sc_in sc_lv 32 signal 5 } 
	{ in_6_val sc_in sc_lv 32 signal 6 } 
	{ in_7_val sc_in sc_lv 32 signal 7 } 
	{ in_8_val sc_in sc_lv 26 signal 8 } 
	{ in_9_val sc_in sc_lv 32 signal 9 } 
	{ in_10_val sc_in sc_lv 32 signal 10 } 
	{ in_11_val sc_in sc_lv 32 signal 11 } 
	{ in_12_val sc_in sc_lv 32 signal 12 } 
	{ in_13_val sc_in sc_lv 32 signal 13 } 
	{ in_14_val sc_in sc_lv 32 signal 14 } 
	{ in_15_val sc_in sc_lv 32 signal 15 } 
	{ ap_return_0 sc_out sc_lv 32 signal -1 } 
	{ ap_return_1 sc_out sc_lv 32 signal -1 } 
	{ ap_return_2 sc_out sc_lv 32 signal -1 } 
	{ ap_return_3 sc_out sc_lv 32 signal -1 } 
	{ ap_return_4 sc_out sc_lv 32 signal -1 } 
	{ ap_return_5 sc_out sc_lv 32 signal -1 } 
	{ ap_return_6 sc_out sc_lv 32 signal -1 } 
	{ ap_return_7 sc_out sc_lv 32 signal -1 } 
	{ ap_return_8 sc_out sc_lv 32 signal -1 } 
	{ ap_return_9 sc_out sc_lv 32 signal -1 } 
	{ ap_return_10 sc_out sc_lv 32 signal -1 } 
	{ ap_return_11 sc_out sc_lv 32 signal -1 } 
	{ ap_return_12 sc_out sc_lv 32 signal -1 } 
	{ ap_return_13 sc_out sc_lv 32 signal -1 } 
	{ ap_return_14 sc_out sc_lv 32 signal -1 } 
	{ ap_return_15 sc_out sc_lv 32 signal -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
}
set NewPortList {[ 
	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "in_0_val", "direction": "in", "datatype": "sc_lv", "bitwidth":26, "type": "signal", "bundle":{"name": "in_0_val", "role": "default" }} , 
 	{ "name": "in_1_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_1_val", "role": "default" }} , 
 	{ "name": "in_2_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_2_val", "role": "default" }} , 
 	{ "name": "in_3_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_3_val", "role": "default" }} , 
 	{ "name": "in_4_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_4_val", "role": "default" }} , 
 	{ "name": "in_5_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_5_val", "role": "default" }} , 
 	{ "name": "in_6_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_6_val", "role": "default" }} , 
 	{ "name": "in_7_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_7_val", "role": "default" }} , 
 	{ "name": "in_8_val", "direction": "in", "datatype": "sc_lv", "bitwidth":26, "type": "signal", "bundle":{"name": "in_8_val", "role": "default" }} , 
 	{ "name": "in_9_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_9_val", "role": "default" }} , 
 	{ "name": "in_10_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_10_val", "role": "default" }} , 
 	{ "name": "in_11_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_11_val", "role": "default" }} , 
 	{ "name": "in_12_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_12_val", "role": "default" }} , 
 	{ "name": "in_13_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_13_val", "role": "default" }} , 
 	{ "name": "in_14_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_14_val", "role": "default" }} , 
 	{ "name": "in_15_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_15_val", "role": "default" }} , 
 	{ "name": "ap_return_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_0", "role": "default" }} , 
 	{ "name": "ap_return_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_1", "role": "default" }} , 
 	{ "name": "ap_return_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_2", "role": "default" }} , 
 	{ "name": "ap_return_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_3", "role": "default" }} , 
 	{ "name": "ap_return_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_4", "role": "default" }} , 
 	{ "name": "ap_return_5", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_5", "role": "default" }} , 
 	{ "name": "ap_return_6", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_6", "role": "default" }} , 
 	{ "name": "ap_return_7", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_7", "role": "default" }} , 
 	{ "name": "ap_return_8", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_8", "role": "default" }} , 
 	{ "name": "ap_return_9", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_9", "role": "default" }} , 
 	{ "name": "ap_return_10", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_10", "role": "default" }} , 
 	{ "name": "ap_return_11", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_11", "role": "default" }} , 
 	{ "name": "ap_return_12", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_12", "role": "default" }} , 
 	{ "name": "ap_return_13", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_13", "role": "default" }} , 
 	{ "name": "ap_return_14", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_14", "role": "default" }} , 
 	{ "name": "ap_return_15", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_15", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28"],
		"CDFG" : "IDCT2B16",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "1", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "in_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_3_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_4_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_5_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_6_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_7_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_8_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_9_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_10_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_11_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_12_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_13_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_14_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_15_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164", "Parent" : "0", "Child" : ["2", "5", "6", "7", "8", "9"],
		"CDFG" : "IDCT2B8",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "1", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "in_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_3_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_4_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_5_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_6_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_7_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92", "Parent" : "1", "Child" : ["3", "4"],
		"CDFG" : "IDCT2B4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "1", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "in_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_3_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "3", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "2",
		"CDFG" : "IDCT2B2",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "0", "ap_start" : "0", "ap_ready" : "1", "ap_done" : "0", "ap_continue" : "0", "ap_idle" : "0", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "in_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_1_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "4", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.mul_32s_8s_32_1_1_U3", "Parent" : "2"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U9", "Parent" : "1"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U10", "Parent" : "1"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U11", "Parent" : "1"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U12", "Parent" : "1"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U13", "Parent" : "1"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_1_1_U23", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U24", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U25", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_1_1_U26", "Parent" : "0"},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U27", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U28", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_1_1_U29", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_1_1_U30", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U31", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_1_1_U32", "Parent" : "0"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_1_1_U33", "Parent" : "0"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U34", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U35", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U36", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U37", "Parent" : "0"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_1_1_U38", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_1_1_U39", "Parent" : "0"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_1_1_U40", "Parent" : "0"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_1_1_U41", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	IDCT2B16 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}
		in_2_val {Type I LastRead 0 FirstWrite -1}
		in_3_val {Type I LastRead 0 FirstWrite -1}
		in_4_val {Type I LastRead 0 FirstWrite -1}
		in_5_val {Type I LastRead 0 FirstWrite -1}
		in_6_val {Type I LastRead 0 FirstWrite -1}
		in_7_val {Type I LastRead 0 FirstWrite -1}
		in_8_val {Type I LastRead 0 FirstWrite -1}
		in_9_val {Type I LastRead 0 FirstWrite -1}
		in_10_val {Type I LastRead 0 FirstWrite -1}
		in_11_val {Type I LastRead 0 FirstWrite -1}
		in_12_val {Type I LastRead 0 FirstWrite -1}
		in_13_val {Type I LastRead 0 FirstWrite -1}
		in_14_val {Type I LastRead 0 FirstWrite -1}
		in_15_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B8 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}
		in_2_val {Type I LastRead 0 FirstWrite -1}
		in_3_val {Type I LastRead 0 FirstWrite -1}
		in_4_val {Type I LastRead 0 FirstWrite -1}
		in_5_val {Type I LastRead 0 FirstWrite -1}
		in_6_val {Type I LastRead 0 FirstWrite -1}
		in_7_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B4 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}
		in_2_val {Type I LastRead 0 FirstWrite -1}
		in_3_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B2 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "0", "Max" : "0"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	in_0_val { ap_none {  { in_0_val in_data 0 26 } } }
	in_1_val { ap_none {  { in_1_val in_data 0 32 } } }
	in_2_val { ap_none {  { in_2_val in_data 0 32 } } }
	in_3_val { ap_none {  { in_3_val in_data 0 32 } } }
	in_4_val { ap_none {  { in_4_val in_data 0 32 } } }
	in_5_val { ap_none {  { in_5_val in_data 0 32 } } }
	in_6_val { ap_none {  { in_6_val in_data 0 32 } } }
	in_7_val { ap_none {  { in_7_val in_data 0 32 } } }
	in_8_val { ap_none {  { in_8_val in_data 0 26 } } }
	in_9_val { ap_none {  { in_9_val in_data 0 32 } } }
	in_10_val { ap_none {  { in_10_val in_data 0 32 } } }
	in_11_val { ap_none {  { in_11_val in_data 0 32 } } }
	in_12_val { ap_none {  { in_12_val in_data 0 32 } } }
	in_13_val { ap_none {  { in_13_val in_data 0 32 } } }
	in_14_val { ap_none {  { in_14_val in_data 0 32 } } }
	in_15_val { ap_none {  { in_15_val in_data 0 32 } } }
}
