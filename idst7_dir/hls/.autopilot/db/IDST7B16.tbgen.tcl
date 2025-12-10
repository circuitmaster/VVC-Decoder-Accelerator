set moduleName IDST7B16
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 9
set C_modelName {IDST7B16}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ src_0_val int 32 regular  }
	{ src_1_val int 32 regular  }
	{ src_2_val int 32 regular  }
	{ src_3_val int 32 regular  }
	{ src_4_val int 32 regular  }
	{ src_5_val int 32 regular  }
	{ src_6_val int 32 regular  }
	{ src_7_val int 32 regular  }
	{ src_8_val int 32 regular  }
	{ src_9_val int 32 regular  }
	{ src_10_val int 32 regular  }
	{ src_11_val int 32 regular  }
	{ src_12_val int 32 regular  }
	{ src_13_val int 32 regular  }
	{ src_14_val int 32 regular  }
	{ src_15_val int 32 regular  }
	{ dst_0 int 32 regular {pointer 1}  }
	{ dst_1 int 32 regular {pointer 1}  }
	{ dst_2 int 32 regular {pointer 1}  }
	{ dst_3 int 32 regular {pointer 1}  }
	{ dst_4 int 32 regular {pointer 1}  }
	{ dst_5 int 32 regular {pointer 1}  }
	{ dst_6 int 32 regular {pointer 1}  }
	{ dst_7 int 32 regular {pointer 1}  }
	{ dst_8 int 32 regular {pointer 1}  }
	{ dst_9 int 32 regular {pointer 1}  }
	{ dst_10 int 32 regular {pointer 1}  }
	{ dst_11 int 32 regular {pointer 1}  }
	{ dst_12 int 32 regular {pointer 1}  }
	{ dst_13 int 32 regular {pointer 1}  }
	{ dst_14 int 32 regular {pointer 1}  }
	{ dst_15 int 32 regular {pointer 1}  }
	{ shift int 32 regular  }
	{ skipLine2 int 32 regular  }
	{ oMin int 32 regular  }
	{ oMax int 32 regular  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "src_0_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_1_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_2_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_3_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_4_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_5_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_6_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_7_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_8_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_9_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_10_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_11_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_12_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_13_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_14_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_15_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "dst_0", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_1", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_2", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_3", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_4", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_5", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_6", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_7", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_8", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_9", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_10", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_11", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_12", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_13", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_14", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_15", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "shift", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "skipLine2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "oMin", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "oMax", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 58
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ src_0_val sc_in sc_lv 32 signal 0 } 
	{ src_1_val sc_in sc_lv 32 signal 1 } 
	{ src_2_val sc_in sc_lv 32 signal 2 } 
	{ src_3_val sc_in sc_lv 32 signal 3 } 
	{ src_4_val sc_in sc_lv 32 signal 4 } 
	{ src_5_val sc_in sc_lv 32 signal 5 } 
	{ src_6_val sc_in sc_lv 32 signal 6 } 
	{ src_7_val sc_in sc_lv 32 signal 7 } 
	{ src_8_val sc_in sc_lv 32 signal 8 } 
	{ src_9_val sc_in sc_lv 32 signal 9 } 
	{ src_10_val sc_in sc_lv 32 signal 10 } 
	{ src_11_val sc_in sc_lv 32 signal 11 } 
	{ src_12_val sc_in sc_lv 32 signal 12 } 
	{ src_13_val sc_in sc_lv 32 signal 13 } 
	{ src_14_val sc_in sc_lv 32 signal 14 } 
	{ src_15_val sc_in sc_lv 32 signal 15 } 
	{ dst_0 sc_out sc_lv 32 signal 16 } 
	{ dst_0_ap_vld sc_out sc_logic 1 outvld 16 } 
	{ dst_1 sc_out sc_lv 32 signal 17 } 
	{ dst_1_ap_vld sc_out sc_logic 1 outvld 17 } 
	{ dst_2 sc_out sc_lv 32 signal 18 } 
	{ dst_2_ap_vld sc_out sc_logic 1 outvld 18 } 
	{ dst_3 sc_out sc_lv 32 signal 19 } 
	{ dst_3_ap_vld sc_out sc_logic 1 outvld 19 } 
	{ dst_4 sc_out sc_lv 32 signal 20 } 
	{ dst_4_ap_vld sc_out sc_logic 1 outvld 20 } 
	{ dst_5 sc_out sc_lv 32 signal 21 } 
	{ dst_5_ap_vld sc_out sc_logic 1 outvld 21 } 
	{ dst_6 sc_out sc_lv 32 signal 22 } 
	{ dst_6_ap_vld sc_out sc_logic 1 outvld 22 } 
	{ dst_7 sc_out sc_lv 32 signal 23 } 
	{ dst_7_ap_vld sc_out sc_logic 1 outvld 23 } 
	{ dst_8 sc_out sc_lv 32 signal 24 } 
	{ dst_8_ap_vld sc_out sc_logic 1 outvld 24 } 
	{ dst_9 sc_out sc_lv 32 signal 25 } 
	{ dst_9_ap_vld sc_out sc_logic 1 outvld 25 } 
	{ dst_10 sc_out sc_lv 32 signal 26 } 
	{ dst_10_ap_vld sc_out sc_logic 1 outvld 26 } 
	{ dst_11 sc_out sc_lv 32 signal 27 } 
	{ dst_11_ap_vld sc_out sc_logic 1 outvld 27 } 
	{ dst_12 sc_out sc_lv 32 signal 28 } 
	{ dst_12_ap_vld sc_out sc_logic 1 outvld 28 } 
	{ dst_13 sc_out sc_lv 32 signal 29 } 
	{ dst_13_ap_vld sc_out sc_logic 1 outvld 29 } 
	{ dst_14 sc_out sc_lv 32 signal 30 } 
	{ dst_14_ap_vld sc_out sc_logic 1 outvld 30 } 
	{ dst_15 sc_out sc_lv 32 signal 31 } 
	{ dst_15_ap_vld sc_out sc_logic 1 outvld 31 } 
	{ shift sc_in sc_lv 32 signal 32 } 
	{ skipLine2 sc_in sc_lv 32 signal 33 } 
	{ oMin sc_in sc_lv 32 signal 34 } 
	{ oMax sc_in sc_lv 32 signal 35 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "src_0_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_0_val", "role": "default" }} , 
 	{ "name": "src_1_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_1_val", "role": "default" }} , 
 	{ "name": "src_2_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_2_val", "role": "default" }} , 
 	{ "name": "src_3_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_3_val", "role": "default" }} , 
 	{ "name": "src_4_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_4_val", "role": "default" }} , 
 	{ "name": "src_5_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_5_val", "role": "default" }} , 
 	{ "name": "src_6_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_6_val", "role": "default" }} , 
 	{ "name": "src_7_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_7_val", "role": "default" }} , 
 	{ "name": "src_8_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_8_val", "role": "default" }} , 
 	{ "name": "src_9_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_9_val", "role": "default" }} , 
 	{ "name": "src_10_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_10_val", "role": "default" }} , 
 	{ "name": "src_11_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_11_val", "role": "default" }} , 
 	{ "name": "src_12_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_12_val", "role": "default" }} , 
 	{ "name": "src_13_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_13_val", "role": "default" }} , 
 	{ "name": "src_14_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_14_val", "role": "default" }} , 
 	{ "name": "src_15_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_15_val", "role": "default" }} , 
 	{ "name": "dst_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_0", "role": "default" }} , 
 	{ "name": "dst_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_0", "role": "ap_vld" }} , 
 	{ "name": "dst_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_1", "role": "default" }} , 
 	{ "name": "dst_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_1", "role": "ap_vld" }} , 
 	{ "name": "dst_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_2", "role": "default" }} , 
 	{ "name": "dst_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_2", "role": "ap_vld" }} , 
 	{ "name": "dst_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_3", "role": "default" }} , 
 	{ "name": "dst_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_3", "role": "ap_vld" }} , 
 	{ "name": "dst_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_4", "role": "default" }} , 
 	{ "name": "dst_4_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_4", "role": "ap_vld" }} , 
 	{ "name": "dst_5", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_5", "role": "default" }} , 
 	{ "name": "dst_5_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_5", "role": "ap_vld" }} , 
 	{ "name": "dst_6", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_6", "role": "default" }} , 
 	{ "name": "dst_6_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_6", "role": "ap_vld" }} , 
 	{ "name": "dst_7", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_7", "role": "default" }} , 
 	{ "name": "dst_7_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_7", "role": "ap_vld" }} , 
 	{ "name": "dst_8", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_8", "role": "default" }} , 
 	{ "name": "dst_8_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_8", "role": "ap_vld" }} , 
 	{ "name": "dst_9", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_9", "role": "default" }} , 
 	{ "name": "dst_9_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_9", "role": "ap_vld" }} , 
 	{ "name": "dst_10", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_10", "role": "default" }} , 
 	{ "name": "dst_10_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_10", "role": "ap_vld" }} , 
 	{ "name": "dst_11", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_11", "role": "default" }} , 
 	{ "name": "dst_11_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_11", "role": "ap_vld" }} , 
 	{ "name": "dst_12", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_12", "role": "default" }} , 
 	{ "name": "dst_12_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_12", "role": "ap_vld" }} , 
 	{ "name": "dst_13", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_13", "role": "default" }} , 
 	{ "name": "dst_13_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_13", "role": "ap_vld" }} , 
 	{ "name": "dst_14", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_14", "role": "default" }} , 
 	{ "name": "dst_14_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_14", "role": "ap_vld" }} , 
 	{ "name": "dst_15", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_15", "role": "default" }} , 
 	{ "name": "dst_15_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_15", "role": "ap_vld" }} , 
 	{ "name": "shift", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "shift", "role": "default" }} , 
 	{ "name": "skipLine2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "skipLine2", "role": "default" }} , 
 	{ "name": "oMin", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMin", "role": "default" }} , 
 	{ "name": "oMax", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMax", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "IDST7B16",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "23", "EstimateLatencyMax" : "23",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "src_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_3_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_4_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_5_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_6_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_7_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_8_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_9_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_10_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_11_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_12_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_13_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_14_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_15_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_0", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_1", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_2", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_3", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_4", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_5", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_6", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_7", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_8", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_8", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_9", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_9", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_10", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_10", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_11", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_11", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_12", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_12", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_13", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_13", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_14", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_14", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "dst_15", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_15", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "skipLine2", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_0", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_1", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_2", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_3", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_4", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_5", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_6", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_7", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_8", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_8", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_9", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_9", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_10", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_10", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_11", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_11", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_12", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_13", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_13", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_14", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_14", "Inst_start_state" : "1", "Inst_end_state" : "2"}]},
			{"Name" : "p_ZL8idst7_16_15", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idst7_16_15", "Inst_start_state" : "1", "Inst_end_state" : "2"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Parent" : "0", "Child" : ["2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34"],
		"CDFG" : "IDST7B16_Pipeline_VITIS_LOOP_47_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "22", "EstimateLatencyMax" : "22",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_15", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_14", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_13", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_12", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_11", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_10", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_9", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_8", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "src_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_3_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_4_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_5_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_6_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_7_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_8_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_9_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_10_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_11_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_12_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_13_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_14_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_15_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "conv3_i12_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i9_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_44", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_45", "Type" : "None", "Direction" : "I"},
			{"Name" : "cutoff", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_46", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_47", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_8", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_9", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_10", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_11", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_12", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_13", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_14", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_16_15", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_47_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter5", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter5", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_0_U", "Parent" : "1"},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_1_U", "Parent" : "1"},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_2_U", "Parent" : "1"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_3_U", "Parent" : "1"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_4_U", "Parent" : "1"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_5_U", "Parent" : "1"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_6_U", "Parent" : "1"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_7_U", "Parent" : "1"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_8_U", "Parent" : "1"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_9_U", "Parent" : "1"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_10_U", "Parent" : "1"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_11_U", "Parent" : "1"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_12_U", "Parent" : "1"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_13_U", "Parent" : "1"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_14_U", "Parent" : "1"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idst7_16_15_U", "Parent" : "1"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_7ns_32s_32_1_1_U65", "Parent" : "1"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U66", "Parent" : "1"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U67", "Parent" : "1"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U68", "Parent" : "1"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U69", "Parent" : "1"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U70", "Parent" : "1"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U71", "Parent" : "1"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U72", "Parent" : "1"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U73", "Parent" : "1"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U74", "Parent" : "1"},
	{"ID" : "28", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U75", "Parent" : "1"},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U76", "Parent" : "1"},
	{"ID" : "30", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U77", "Parent" : "1"},
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U78", "Parent" : "1"},
	{"ID" : "32", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U79", "Parent" : "1"},
	{"ID" : "33", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_1_1_U80", "Parent" : "1"},
	{"ID" : "34", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B16_Pipeline_VITIS_LOOP_47_1_fu_258.flow_control_loop_pipe_sequential_init_U", "Parent" : "1"}]}


set ArgLastReadFirstWriteLatency {
	IDST7B16 {
		src_0_val {Type I LastRead 0 FirstWrite -1}
		src_1_val {Type I LastRead 0 FirstWrite -1}
		src_2_val {Type I LastRead 0 FirstWrite -1}
		src_3_val {Type I LastRead 0 FirstWrite -1}
		src_4_val {Type I LastRead 0 FirstWrite -1}
		src_5_val {Type I LastRead 0 FirstWrite -1}
		src_6_val {Type I LastRead 0 FirstWrite -1}
		src_7_val {Type I LastRead 0 FirstWrite -1}
		src_8_val {Type I LastRead 0 FirstWrite -1}
		src_9_val {Type I LastRead 0 FirstWrite -1}
		src_10_val {Type I LastRead 0 FirstWrite -1}
		src_11_val {Type I LastRead 0 FirstWrite -1}
		src_12_val {Type I LastRead 0 FirstWrite -1}
		src_13_val {Type I LastRead 0 FirstWrite -1}
		src_14_val {Type I LastRead 0 FirstWrite -1}
		src_15_val {Type I LastRead 0 FirstWrite -1}
		dst_0 {Type O LastRead -1 FirstWrite 5}
		dst_1 {Type O LastRead -1 FirstWrite 5}
		dst_2 {Type O LastRead -1 FirstWrite 5}
		dst_3 {Type O LastRead -1 FirstWrite 5}
		dst_4 {Type O LastRead -1 FirstWrite 5}
		dst_5 {Type O LastRead -1 FirstWrite 5}
		dst_6 {Type O LastRead -1 FirstWrite 5}
		dst_7 {Type O LastRead -1 FirstWrite 5}
		dst_8 {Type O LastRead -1 FirstWrite 5}
		dst_9 {Type O LastRead -1 FirstWrite 5}
		dst_10 {Type O LastRead -1 FirstWrite 5}
		dst_11 {Type O LastRead -1 FirstWrite 5}
		dst_12 {Type O LastRead -1 FirstWrite 5}
		dst_13 {Type O LastRead -1 FirstWrite 5}
		dst_14 {Type O LastRead -1 FirstWrite 5}
		dst_15 {Type O LastRead -1 FirstWrite 5}
		shift {Type I LastRead 0 FirstWrite -1}
		skipLine2 {Type I LastRead 0 FirstWrite -1}
		oMin {Type I LastRead 0 FirstWrite -1}
		oMax {Type I LastRead 0 FirstWrite -1}
		p_ZL8idst7_16_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_15 {Type I LastRead -1 FirstWrite -1}}
	IDST7B16_Pipeline_VITIS_LOOP_47_1 {
		dst_0 {Type O LastRead -1 FirstWrite 5}
		dst_15 {Type O LastRead -1 FirstWrite 5}
		dst_14 {Type O LastRead -1 FirstWrite 5}
		dst_13 {Type O LastRead -1 FirstWrite 5}
		dst_12 {Type O LastRead -1 FirstWrite 5}
		dst_11 {Type O LastRead -1 FirstWrite 5}
		dst_10 {Type O LastRead -1 FirstWrite 5}
		dst_9 {Type O LastRead -1 FirstWrite 5}
		dst_8 {Type O LastRead -1 FirstWrite 5}
		dst_7 {Type O LastRead -1 FirstWrite 5}
		dst_6 {Type O LastRead -1 FirstWrite 5}
		dst_5 {Type O LastRead -1 FirstWrite 5}
		dst_4 {Type O LastRead -1 FirstWrite 5}
		dst_3 {Type O LastRead -1 FirstWrite 5}
		dst_2 {Type O LastRead -1 FirstWrite 5}
		dst_1 {Type O LastRead -1 FirstWrite 5}
		src_0_val {Type I LastRead 0 FirstWrite -1}
		src_1_val {Type I LastRead 0 FirstWrite -1}
		src_2_val {Type I LastRead 0 FirstWrite -1}
		src_3_val {Type I LastRead 0 FirstWrite -1}
		src_4_val {Type I LastRead 0 FirstWrite -1}
		src_5_val {Type I LastRead 0 FirstWrite -1}
		src_6_val {Type I LastRead 0 FirstWrite -1}
		src_7_val {Type I LastRead 0 FirstWrite -1}
		src_8_val {Type I LastRead 0 FirstWrite -1}
		src_9_val {Type I LastRead 0 FirstWrite -1}
		src_10_val {Type I LastRead 0 FirstWrite -1}
		src_11_val {Type I LastRead 0 FirstWrite -1}
		src_12_val {Type I LastRead 0 FirstWrite -1}
		src_13_val {Type I LastRead 0 FirstWrite -1}
		src_14_val {Type I LastRead 0 FirstWrite -1}
		src_15_val {Type I LastRead 0 FirstWrite -1}
		conv3_i12_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i9_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i_i_i {Type I LastRead 0 FirstWrite -1}
		empty_44 {Type I LastRead 0 FirstWrite -1}
		oMin {Type I LastRead 0 FirstWrite -1}
		oMax {Type I LastRead 0 FirstWrite -1}
		empty_45 {Type I LastRead 0 FirstWrite -1}
		cutoff {Type I LastRead 0 FirstWrite -1}
		empty_46 {Type I LastRead 0 FirstWrite -1}
		empty_47 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		p_ZL8idst7_16_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_16_15 {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "23", "Max" : "23"}
	, {"Name" : "Interval", "Min" : "23", "Max" : "23"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	src_0_val { ap_none {  { src_0_val in_data 0 32 } } }
	src_1_val { ap_none {  { src_1_val in_data 0 32 } } }
	src_2_val { ap_none {  { src_2_val in_data 0 32 } } }
	src_3_val { ap_none {  { src_3_val in_data 0 32 } } }
	src_4_val { ap_none {  { src_4_val in_data 0 32 } } }
	src_5_val { ap_none {  { src_5_val in_data 0 32 } } }
	src_6_val { ap_none {  { src_6_val in_data 0 32 } } }
	src_7_val { ap_none {  { src_7_val in_data 0 32 } } }
	src_8_val { ap_none {  { src_8_val in_data 0 32 } } }
	src_9_val { ap_none {  { src_9_val in_data 0 32 } } }
	src_10_val { ap_none {  { src_10_val in_data 0 32 } } }
	src_11_val { ap_none {  { src_11_val in_data 0 32 } } }
	src_12_val { ap_none {  { src_12_val in_data 0 32 } } }
	src_13_val { ap_none {  { src_13_val in_data 0 32 } } }
	src_14_val { ap_none {  { src_14_val in_data 0 32 } } }
	src_15_val { ap_none {  { src_15_val in_data 0 32 } } }
	dst_0 { ap_vld {  { dst_0 out_data 1 32 }  { dst_0_ap_vld out_vld 1 1 } } }
	dst_1 { ap_vld {  { dst_1 out_data 1 32 }  { dst_1_ap_vld out_vld 1 1 } } }
	dst_2 { ap_vld {  { dst_2 out_data 1 32 }  { dst_2_ap_vld out_vld 1 1 } } }
	dst_3 { ap_vld {  { dst_3 out_data 1 32 }  { dst_3_ap_vld out_vld 1 1 } } }
	dst_4 { ap_vld {  { dst_4 out_data 1 32 }  { dst_4_ap_vld out_vld 1 1 } } }
	dst_5 { ap_vld {  { dst_5 out_data 1 32 }  { dst_5_ap_vld out_vld 1 1 } } }
	dst_6 { ap_vld {  { dst_6 out_data 1 32 }  { dst_6_ap_vld out_vld 1 1 } } }
	dst_7 { ap_vld {  { dst_7 out_data 1 32 }  { dst_7_ap_vld out_vld 1 1 } } }
	dst_8 { ap_vld {  { dst_8 out_data 1 32 }  { dst_8_ap_vld out_vld 1 1 } } }
	dst_9 { ap_vld {  { dst_9 out_data 1 32 }  { dst_9_ap_vld out_vld 1 1 } } }
	dst_10 { ap_vld {  { dst_10 out_data 1 32 }  { dst_10_ap_vld out_vld 1 1 } } }
	dst_11 { ap_vld {  { dst_11 out_data 1 32 }  { dst_11_ap_vld out_vld 1 1 } } }
	dst_12 { ap_vld {  { dst_12 out_data 1 32 }  { dst_12_ap_vld out_vld 1 1 } } }
	dst_13 { ap_vld {  { dst_13 out_data 1 32 }  { dst_13_ap_vld out_vld 1 1 } } }
	dst_14 { ap_vld {  { dst_14 out_data 1 32 }  { dst_14_ap_vld out_vld 1 1 } } }
	dst_15 { ap_vld {  { dst_15 out_data 1 32 }  { dst_15_ap_vld out_vld 1 1 } } }
	shift { ap_none {  { shift in_data 0 32 } } }
	skipLine2 { ap_none {  { skipLine2 in_data 0 32 } } }
	oMin { ap_none {  { oMin in_data 0 32 } } }
	oMax { ap_none {  { oMax in_data 0 32 } } }
}
