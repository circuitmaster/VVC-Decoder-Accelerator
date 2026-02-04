set moduleName IDST7B8
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
set C_modelName {IDST7B8}
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
	{ dst_0 int 32 regular {pointer 1}  }
	{ dst_1 int 32 regular {pointer 1}  }
	{ dst_2 int 32 regular {pointer 1}  }
	{ dst_3 int 32 regular {pointer 1}  }
	{ dst_4 int 32 regular {pointer 1}  }
	{ dst_5 int 32 regular {pointer 1}  }
	{ dst_6 int 32 regular {pointer 1}  }
	{ dst_7 int 32 regular {pointer 1}  }
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
 	{ "Name" : "dst_0", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_1", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_2", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_3", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_4", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_5", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_6", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_7", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "shift", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "skipLine2", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "oMin", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "oMax", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 34
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
	{ dst_0 sc_out sc_lv 32 signal 8 } 
	{ dst_0_ap_vld sc_out sc_logic 1 outvld 8 } 
	{ dst_1 sc_out sc_lv 32 signal 9 } 
	{ dst_1_ap_vld sc_out sc_logic 1 outvld 9 } 
	{ dst_2 sc_out sc_lv 32 signal 10 } 
	{ dst_2_ap_vld sc_out sc_logic 1 outvld 10 } 
	{ dst_3 sc_out sc_lv 32 signal 11 } 
	{ dst_3_ap_vld sc_out sc_logic 1 outvld 11 } 
	{ dst_4 sc_out sc_lv 32 signal 12 } 
	{ dst_4_ap_vld sc_out sc_logic 1 outvld 12 } 
	{ dst_5 sc_out sc_lv 32 signal 13 } 
	{ dst_5_ap_vld sc_out sc_logic 1 outvld 13 } 
	{ dst_6 sc_out sc_lv 32 signal 14 } 
	{ dst_6_ap_vld sc_out sc_logic 1 outvld 14 } 
	{ dst_7 sc_out sc_lv 32 signal 15 } 
	{ dst_7_ap_vld sc_out sc_logic 1 outvld 15 } 
	{ shift sc_in sc_lv 32 signal 16 } 
	{ skipLine2 sc_in sc_lv 32 signal 17 } 
	{ oMin sc_in sc_lv 32 signal 18 } 
	{ oMax sc_in sc_lv 32 signal 19 } 
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
 	{ "name": "shift", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "shift", "role": "default" }} , 
 	{ "name": "skipLine2", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "skipLine2", "role": "default" }} , 
 	{ "name": "oMin", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMin", "role": "default" }} , 
 	{ "name": "oMax", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMax", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "IDST7B8",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "20", "EstimateLatencyMax" : "20",
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
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "skipLine2", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idst7_8_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idst7_8_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Parent" : "0", "Child" : ["2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"],
		"CDFG" : "IDST7B8_Pipeline_VITIS_LOOP_21_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "18", "EstimateLatencyMax" : "18",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O"},
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
			{"Name" : "conv3_i12_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i9_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_33", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_34", "Type" : "None", "Direction" : "I"},
			{"Name" : "cutoff", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_35", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idst7_8_7", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_21_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter9", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter9", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_0_U", "Parent" : "1"},
	{"ID" : "3", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_1_U", "Parent" : "1"},
	{"ID" : "4", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_2_U", "Parent" : "1"},
	{"ID" : "5", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_3_U", "Parent" : "1"},
	{"ID" : "6", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_4_U", "Parent" : "1"},
	{"ID" : "7", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_5_U", "Parent" : "1"},
	{"ID" : "8", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_6_U", "Parent" : "1"},
	{"ID" : "9", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idst7_8_7_U", "Parent" : "1"},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_7ns_32s_32_2_1_U1", "Parent" : "1"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U2", "Parent" : "1"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U3", "Parent" : "1"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U4", "Parent" : "1"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U5", "Parent" : "1"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U6", "Parent" : "1"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U7", "Parent" : "1"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U8", "Parent" : "1"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDST7B8_Pipeline_VITIS_LOOP_21_1_fu_158.flow_control_loop_pipe_sequential_init_U", "Parent" : "1"}]}


set ArgLastReadFirstWriteLatency {
	IDST7B8 {
		src_0_val {Type I LastRead 1 FirstWrite -1}
		src_1_val {Type I LastRead 1 FirstWrite -1}
		src_2_val {Type I LastRead 1 FirstWrite -1}
		src_3_val {Type I LastRead 1 FirstWrite -1}
		src_4_val {Type I LastRead 1 FirstWrite -1}
		src_5_val {Type I LastRead 1 FirstWrite -1}
		src_6_val {Type I LastRead 1 FirstWrite -1}
		src_7_val {Type I LastRead 1 FirstWrite -1}
		dst_0 {Type O LastRead -1 FirstWrite 9}
		dst_1 {Type O LastRead -1 FirstWrite 9}
		dst_2 {Type O LastRead -1 FirstWrite 9}
		dst_3 {Type O LastRead -1 FirstWrite 9}
		dst_4 {Type O LastRead -1 FirstWrite 9}
		dst_5 {Type O LastRead -1 FirstWrite 9}
		dst_6 {Type O LastRead -1 FirstWrite 9}
		dst_7 {Type O LastRead -1 FirstWrite 9}
		shift {Type I LastRead 0 FirstWrite -1}
		skipLine2 {Type I LastRead 1 FirstWrite -1}
		oMin {Type I LastRead 1 FirstWrite -1}
		oMax {Type I LastRead 1 FirstWrite -1}
		p_ZL7idst7_8_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_7 {Type I LastRead -1 FirstWrite -1}}
	IDST7B8_Pipeline_VITIS_LOOP_21_1 {
		dst_0 {Type O LastRead -1 FirstWrite 9}
		dst_7 {Type O LastRead -1 FirstWrite 9}
		dst_6 {Type O LastRead -1 FirstWrite 9}
		dst_5 {Type O LastRead -1 FirstWrite 9}
		dst_4 {Type O LastRead -1 FirstWrite 9}
		dst_3 {Type O LastRead -1 FirstWrite 9}
		dst_2 {Type O LastRead -1 FirstWrite 9}
		dst_1 {Type O LastRead -1 FirstWrite 9}
		src_0_val {Type I LastRead 0 FirstWrite -1}
		src_1_val {Type I LastRead 0 FirstWrite -1}
		src_2_val {Type I LastRead 0 FirstWrite -1}
		src_3_val {Type I LastRead 0 FirstWrite -1}
		src_4_val {Type I LastRead 0 FirstWrite -1}
		src_5_val {Type I LastRead 0 FirstWrite -1}
		src_6_val {Type I LastRead 0 FirstWrite -1}
		src_7_val {Type I LastRead 0 FirstWrite -1}
		conv3_i12_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i9_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i_i_i {Type I LastRead 0 FirstWrite -1}
		empty_33 {Type I LastRead 0 FirstWrite -1}
		oMin {Type I LastRead 0 FirstWrite -1}
		oMax {Type I LastRead 0 FirstWrite -1}
		empty_34 {Type I LastRead 0 FirstWrite -1}
		cutoff {Type I LastRead 0 FirstWrite -1}
		empty_35 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		p_ZL7idst7_8_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idst7_8_7 {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "20", "Max" : "20"}
	, {"Name" : "Interval", "Min" : "20", "Max" : "20"}
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
	dst_0 { ap_vld {  { dst_0 out_data 1 32 }  { dst_0_ap_vld out_vld 1 1 } } }
	dst_1 { ap_vld {  { dst_1 out_data 1 32 }  { dst_1_ap_vld out_vld 1 1 } } }
	dst_2 { ap_vld {  { dst_2 out_data 1 32 }  { dst_2_ap_vld out_vld 1 1 } } }
	dst_3 { ap_vld {  { dst_3 out_data 1 32 }  { dst_3_ap_vld out_vld 1 1 } } }
	dst_4 { ap_vld {  { dst_4 out_data 1 32 }  { dst_4_ap_vld out_vld 1 1 } } }
	dst_5 { ap_vld {  { dst_5 out_data 1 32 }  { dst_5_ap_vld out_vld 1 1 } } }
	dst_6 { ap_vld {  { dst_6 out_data 1 32 }  { dst_6_ap_vld out_vld 1 1 } } }
	dst_7 { ap_vld {  { dst_7 out_data 1 32 }  { dst_7_ap_vld out_vld 1 1 } } }
	shift { ap_none {  { shift in_data 0 32 } } }
	skipLine2 { ap_none {  { skipLine2 in_data 0 32 } } }
	oMin { ap_none {  { oMin in_data 0 32 } } }
	oMax { ap_none {  { oMax in_data 0 32 } } }
}
