set moduleName IDST7B32_Pipeline_VITIS_LOOP_73_1
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type loop_auto_rewind
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
set C_modelName {IDST7B32_Pipeline_VITIS_LOOP_73_1}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ dst_0 int 32 regular {pointer 1}  }
	{ dst_31 int 32 regular {pointer 1}  }
	{ dst_30 int 32 regular {pointer 1}  }
	{ dst_29 int 32 regular {pointer 1}  }
	{ dst_28 int 32 regular {pointer 1}  }
	{ dst_27 int 32 regular {pointer 1}  }
	{ dst_26 int 32 regular {pointer 1}  }
	{ dst_25 int 32 regular {pointer 1}  }
	{ dst_24 int 32 regular {pointer 1}  }
	{ dst_23 int 32 regular {pointer 1}  }
	{ dst_22 int 32 regular {pointer 1}  }
	{ dst_21 int 32 regular {pointer 1}  }
	{ dst_20 int 32 regular {pointer 1}  }
	{ dst_19 int 32 regular {pointer 1}  }
	{ dst_18 int 32 regular {pointer 1}  }
	{ dst_17 int 32 regular {pointer 1}  }
	{ dst_16 int 32 regular {pointer 1}  }
	{ dst_15 int 32 regular {pointer 1}  }
	{ dst_14 int 32 regular {pointer 1}  }
	{ dst_13 int 32 regular {pointer 1}  }
	{ dst_12 int 32 regular {pointer 1}  }
	{ dst_11 int 32 regular {pointer 1}  }
	{ dst_10 int 32 regular {pointer 1}  }
	{ dst_9 int 32 regular {pointer 1}  }
	{ dst_8 int 32 regular {pointer 1}  }
	{ dst_7 int 32 regular {pointer 1}  }
	{ dst_6 int 32 regular {pointer 1}  }
	{ dst_5 int 32 regular {pointer 1}  }
	{ dst_4 int 32 regular {pointer 1}  }
	{ dst_3 int 32 regular {pointer 1}  }
	{ dst_2 int 32 regular {pointer 1}  }
	{ dst_1 int 32 regular {pointer 1}  }
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
	{ src_16_val int 32 regular  }
	{ src_17_val int 32 regular  }
	{ src_18_val int 32 regular  }
	{ src_19_val int 32 regular  }
	{ src_20_val int 32 regular  }
	{ src_21_val int 32 regular  }
	{ src_22_val int 32 regular  }
	{ src_23_val int 32 regular  }
	{ src_24_val int 32 regular  }
	{ src_25_val int 32 regular  }
	{ src_26_val int 32 regular  }
	{ src_27_val int 32 regular  }
	{ src_28_val int 32 regular  }
	{ src_29_val int 32 regular  }
	{ src_30_val int 32 regular  }
	{ src_31_val int 32 regular  }
	{ conv3_i12_i_i int 32 regular  }
	{ sh_prom_i9_i_i int 32 regular  }
	{ sh_prom_i_i_i int 32 regular  }
	{ empty_36 int 1 regular  }
	{ oMin int 32 regular  }
	{ oMax int 32 regular  }
	{ empty_37 int 27 regular  }
	{ cutoff int 32 regular  }
	{ empty_38 int 28 regular  }
	{ empty_39 int 29 regular  }
	{ empty_40 int 30 regular  }
	{ empty int 31 regular  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "dst_0", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_31", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_30", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_29", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_28", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_27", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_26", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_25", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_24", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_23", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_22", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_21", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_20", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_19", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_18", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_17", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_16", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_15", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_14", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_13", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_12", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_11", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_10", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_9", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_8", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_7", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_6", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_5", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_4", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_3", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_2", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "dst_1", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
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
 	{ "Name" : "src_16_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_17_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_18_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_19_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_20_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_21_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_22_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_23_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_24_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_25_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_26_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_27_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_28_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_29_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_30_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "src_31_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "conv3_i12_i_i", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sh_prom_i9_i_i", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sh_prom_i_i_i", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_36", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "oMin", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "oMax", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_37", "interface" : "wire", "bitwidth" : 27, "direction" : "READONLY"} , 
 	{ "Name" : "cutoff", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "empty_38", "interface" : "wire", "bitwidth" : 28, "direction" : "READONLY"} , 
 	{ "Name" : "empty_39", "interface" : "wire", "bitwidth" : 29, "direction" : "READONLY"} , 
 	{ "Name" : "empty_40", "interface" : "wire", "bitwidth" : 30, "direction" : "READONLY"} , 
 	{ "Name" : "empty", "interface" : "wire", "bitwidth" : 31, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 114
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ dst_0 sc_out sc_lv 32 signal 0 } 
	{ dst_0_ap_vld sc_out sc_logic 1 outvld 0 } 
	{ dst_31 sc_out sc_lv 32 signal 1 } 
	{ dst_31_ap_vld sc_out sc_logic 1 outvld 1 } 
	{ dst_30 sc_out sc_lv 32 signal 2 } 
	{ dst_30_ap_vld sc_out sc_logic 1 outvld 2 } 
	{ dst_29 sc_out sc_lv 32 signal 3 } 
	{ dst_29_ap_vld sc_out sc_logic 1 outvld 3 } 
	{ dst_28 sc_out sc_lv 32 signal 4 } 
	{ dst_28_ap_vld sc_out sc_logic 1 outvld 4 } 
	{ dst_27 sc_out sc_lv 32 signal 5 } 
	{ dst_27_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ dst_26 sc_out sc_lv 32 signal 6 } 
	{ dst_26_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ dst_25 sc_out sc_lv 32 signal 7 } 
	{ dst_25_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ dst_24 sc_out sc_lv 32 signal 8 } 
	{ dst_24_ap_vld sc_out sc_logic 1 outvld 8 } 
	{ dst_23 sc_out sc_lv 32 signal 9 } 
	{ dst_23_ap_vld sc_out sc_logic 1 outvld 9 } 
	{ dst_22 sc_out sc_lv 32 signal 10 } 
	{ dst_22_ap_vld sc_out sc_logic 1 outvld 10 } 
	{ dst_21 sc_out sc_lv 32 signal 11 } 
	{ dst_21_ap_vld sc_out sc_logic 1 outvld 11 } 
	{ dst_20 sc_out sc_lv 32 signal 12 } 
	{ dst_20_ap_vld sc_out sc_logic 1 outvld 12 } 
	{ dst_19 sc_out sc_lv 32 signal 13 } 
	{ dst_19_ap_vld sc_out sc_logic 1 outvld 13 } 
	{ dst_18 sc_out sc_lv 32 signal 14 } 
	{ dst_18_ap_vld sc_out sc_logic 1 outvld 14 } 
	{ dst_17 sc_out sc_lv 32 signal 15 } 
	{ dst_17_ap_vld sc_out sc_logic 1 outvld 15 } 
	{ dst_16 sc_out sc_lv 32 signal 16 } 
	{ dst_16_ap_vld sc_out sc_logic 1 outvld 16 } 
	{ dst_15 sc_out sc_lv 32 signal 17 } 
	{ dst_15_ap_vld sc_out sc_logic 1 outvld 17 } 
	{ dst_14 sc_out sc_lv 32 signal 18 } 
	{ dst_14_ap_vld sc_out sc_logic 1 outvld 18 } 
	{ dst_13 sc_out sc_lv 32 signal 19 } 
	{ dst_13_ap_vld sc_out sc_logic 1 outvld 19 } 
	{ dst_12 sc_out sc_lv 32 signal 20 } 
	{ dst_12_ap_vld sc_out sc_logic 1 outvld 20 } 
	{ dst_11 sc_out sc_lv 32 signal 21 } 
	{ dst_11_ap_vld sc_out sc_logic 1 outvld 21 } 
	{ dst_10 sc_out sc_lv 32 signal 22 } 
	{ dst_10_ap_vld sc_out sc_logic 1 outvld 22 } 
	{ dst_9 sc_out sc_lv 32 signal 23 } 
	{ dst_9_ap_vld sc_out sc_logic 1 outvld 23 } 
	{ dst_8 sc_out sc_lv 32 signal 24 } 
	{ dst_8_ap_vld sc_out sc_logic 1 outvld 24 } 
	{ dst_7 sc_out sc_lv 32 signal 25 } 
	{ dst_7_ap_vld sc_out sc_logic 1 outvld 25 } 
	{ dst_6 sc_out sc_lv 32 signal 26 } 
	{ dst_6_ap_vld sc_out sc_logic 1 outvld 26 } 
	{ dst_5 sc_out sc_lv 32 signal 27 } 
	{ dst_5_ap_vld sc_out sc_logic 1 outvld 27 } 
	{ dst_4 sc_out sc_lv 32 signal 28 } 
	{ dst_4_ap_vld sc_out sc_logic 1 outvld 28 } 
	{ dst_3 sc_out sc_lv 32 signal 29 } 
	{ dst_3_ap_vld sc_out sc_logic 1 outvld 29 } 
	{ dst_2 sc_out sc_lv 32 signal 30 } 
	{ dst_2_ap_vld sc_out sc_logic 1 outvld 30 } 
	{ dst_1 sc_out sc_lv 32 signal 31 } 
	{ dst_1_ap_vld sc_out sc_logic 1 outvld 31 } 
	{ src_0_val sc_in sc_lv 32 signal 32 } 
	{ src_1_val sc_in sc_lv 32 signal 33 } 
	{ src_2_val sc_in sc_lv 32 signal 34 } 
	{ src_3_val sc_in sc_lv 32 signal 35 } 
	{ src_4_val sc_in sc_lv 32 signal 36 } 
	{ src_5_val sc_in sc_lv 32 signal 37 } 
	{ src_6_val sc_in sc_lv 32 signal 38 } 
	{ src_7_val sc_in sc_lv 32 signal 39 } 
	{ src_8_val sc_in sc_lv 32 signal 40 } 
	{ src_9_val sc_in sc_lv 32 signal 41 } 
	{ src_10_val sc_in sc_lv 32 signal 42 } 
	{ src_11_val sc_in sc_lv 32 signal 43 } 
	{ src_12_val sc_in sc_lv 32 signal 44 } 
	{ src_13_val sc_in sc_lv 32 signal 45 } 
	{ src_14_val sc_in sc_lv 32 signal 46 } 
	{ src_15_val sc_in sc_lv 32 signal 47 } 
	{ src_16_val sc_in sc_lv 32 signal 48 } 
	{ src_17_val sc_in sc_lv 32 signal 49 } 
	{ src_18_val sc_in sc_lv 32 signal 50 } 
	{ src_19_val sc_in sc_lv 32 signal 51 } 
	{ src_20_val sc_in sc_lv 32 signal 52 } 
	{ src_21_val sc_in sc_lv 32 signal 53 } 
	{ src_22_val sc_in sc_lv 32 signal 54 } 
	{ src_23_val sc_in sc_lv 32 signal 55 } 
	{ src_24_val sc_in sc_lv 32 signal 56 } 
	{ src_25_val sc_in sc_lv 32 signal 57 } 
	{ src_26_val sc_in sc_lv 32 signal 58 } 
	{ src_27_val sc_in sc_lv 32 signal 59 } 
	{ src_28_val sc_in sc_lv 32 signal 60 } 
	{ src_29_val sc_in sc_lv 32 signal 61 } 
	{ src_30_val sc_in sc_lv 32 signal 62 } 
	{ src_31_val sc_in sc_lv 32 signal 63 } 
	{ conv3_i12_i_i sc_in sc_lv 32 signal 64 } 
	{ sh_prom_i9_i_i sc_in sc_lv 32 signal 65 } 
	{ sh_prom_i_i_i sc_in sc_lv 32 signal 66 } 
	{ empty_36 sc_in sc_lv 1 signal 67 } 
	{ oMin sc_in sc_lv 32 signal 68 } 
	{ oMax sc_in sc_lv 32 signal 69 } 
	{ empty_37 sc_in sc_lv 27 signal 70 } 
	{ cutoff sc_in sc_lv 32 signal 71 } 
	{ empty_38 sc_in sc_lv 28 signal 72 } 
	{ empty_39 sc_in sc_lv 29 signal 73 } 
	{ empty_40 sc_in sc_lv 30 signal 74 } 
	{ empty sc_in sc_lv 31 signal 75 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "dst_0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_0", "role": "default" }} , 
 	{ "name": "dst_0_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_0", "role": "ap_vld" }} , 
 	{ "name": "dst_31", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_31", "role": "default" }} , 
 	{ "name": "dst_31_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_31", "role": "ap_vld" }} , 
 	{ "name": "dst_30", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_30", "role": "default" }} , 
 	{ "name": "dst_30_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_30", "role": "ap_vld" }} , 
 	{ "name": "dst_29", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_29", "role": "default" }} , 
 	{ "name": "dst_29_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_29", "role": "ap_vld" }} , 
 	{ "name": "dst_28", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_28", "role": "default" }} , 
 	{ "name": "dst_28_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_28", "role": "ap_vld" }} , 
 	{ "name": "dst_27", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_27", "role": "default" }} , 
 	{ "name": "dst_27_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_27", "role": "ap_vld" }} , 
 	{ "name": "dst_26", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_26", "role": "default" }} , 
 	{ "name": "dst_26_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_26", "role": "ap_vld" }} , 
 	{ "name": "dst_25", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_25", "role": "default" }} , 
 	{ "name": "dst_25_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_25", "role": "ap_vld" }} , 
 	{ "name": "dst_24", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_24", "role": "default" }} , 
 	{ "name": "dst_24_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_24", "role": "ap_vld" }} , 
 	{ "name": "dst_23", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_23", "role": "default" }} , 
 	{ "name": "dst_23_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_23", "role": "ap_vld" }} , 
 	{ "name": "dst_22", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_22", "role": "default" }} , 
 	{ "name": "dst_22_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_22", "role": "ap_vld" }} , 
 	{ "name": "dst_21", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_21", "role": "default" }} , 
 	{ "name": "dst_21_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_21", "role": "ap_vld" }} , 
 	{ "name": "dst_20", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_20", "role": "default" }} , 
 	{ "name": "dst_20_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_20", "role": "ap_vld" }} , 
 	{ "name": "dst_19", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_19", "role": "default" }} , 
 	{ "name": "dst_19_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_19", "role": "ap_vld" }} , 
 	{ "name": "dst_18", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_18", "role": "default" }} , 
 	{ "name": "dst_18_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_18", "role": "ap_vld" }} , 
 	{ "name": "dst_17", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_17", "role": "default" }} , 
 	{ "name": "dst_17_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_17", "role": "ap_vld" }} , 
 	{ "name": "dst_16", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_16", "role": "default" }} , 
 	{ "name": "dst_16_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_16", "role": "ap_vld" }} , 
 	{ "name": "dst_15", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_15", "role": "default" }} , 
 	{ "name": "dst_15_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_15", "role": "ap_vld" }} , 
 	{ "name": "dst_14", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_14", "role": "default" }} , 
 	{ "name": "dst_14_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_14", "role": "ap_vld" }} , 
 	{ "name": "dst_13", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_13", "role": "default" }} , 
 	{ "name": "dst_13_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_13", "role": "ap_vld" }} , 
 	{ "name": "dst_12", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_12", "role": "default" }} , 
 	{ "name": "dst_12_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_12", "role": "ap_vld" }} , 
 	{ "name": "dst_11", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_11", "role": "default" }} , 
 	{ "name": "dst_11_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_11", "role": "ap_vld" }} , 
 	{ "name": "dst_10", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_10", "role": "default" }} , 
 	{ "name": "dst_10_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_10", "role": "ap_vld" }} , 
 	{ "name": "dst_9", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_9", "role": "default" }} , 
 	{ "name": "dst_9_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_9", "role": "ap_vld" }} , 
 	{ "name": "dst_8", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_8", "role": "default" }} , 
 	{ "name": "dst_8_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_8", "role": "ap_vld" }} , 
 	{ "name": "dst_7", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_7", "role": "default" }} , 
 	{ "name": "dst_7_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_7", "role": "ap_vld" }} , 
 	{ "name": "dst_6", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_6", "role": "default" }} , 
 	{ "name": "dst_6_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_6", "role": "ap_vld" }} , 
 	{ "name": "dst_5", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_5", "role": "default" }} , 
 	{ "name": "dst_5_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_5", "role": "ap_vld" }} , 
 	{ "name": "dst_4", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_4", "role": "default" }} , 
 	{ "name": "dst_4_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_4", "role": "ap_vld" }} , 
 	{ "name": "dst_3", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_3", "role": "default" }} , 
 	{ "name": "dst_3_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_3", "role": "ap_vld" }} , 
 	{ "name": "dst_2", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_2", "role": "default" }} , 
 	{ "name": "dst_2_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_2", "role": "ap_vld" }} , 
 	{ "name": "dst_1", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "dst_1", "role": "default" }} , 
 	{ "name": "dst_1_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "dst_1", "role": "ap_vld" }} , 
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
 	{ "name": "src_16_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_16_val", "role": "default" }} , 
 	{ "name": "src_17_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_17_val", "role": "default" }} , 
 	{ "name": "src_18_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_18_val", "role": "default" }} , 
 	{ "name": "src_19_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_19_val", "role": "default" }} , 
 	{ "name": "src_20_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_20_val", "role": "default" }} , 
 	{ "name": "src_21_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_21_val", "role": "default" }} , 
 	{ "name": "src_22_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_22_val", "role": "default" }} , 
 	{ "name": "src_23_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_23_val", "role": "default" }} , 
 	{ "name": "src_24_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_24_val", "role": "default" }} , 
 	{ "name": "src_25_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_25_val", "role": "default" }} , 
 	{ "name": "src_26_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_26_val", "role": "default" }} , 
 	{ "name": "src_27_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_27_val", "role": "default" }} , 
 	{ "name": "src_28_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_28_val", "role": "default" }} , 
 	{ "name": "src_29_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_29_val", "role": "default" }} , 
 	{ "name": "src_30_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_30_val", "role": "default" }} , 
 	{ "name": "src_31_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "src_31_val", "role": "default" }} , 
 	{ "name": "conv3_i12_i_i", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "conv3_i12_i_i", "role": "default" }} , 
 	{ "name": "sh_prom_i9_i_i", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sh_prom_i9_i_i", "role": "default" }} , 
 	{ "name": "sh_prom_i_i_i", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sh_prom_i_i_i", "role": "default" }} , 
 	{ "name": "empty_36", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "empty_36", "role": "default" }} , 
 	{ "name": "oMin", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMin", "role": "default" }} , 
 	{ "name": "oMax", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "oMax", "role": "default" }} , 
 	{ "name": "empty_37", "direction": "in", "datatype": "sc_lv", "bitwidth":27, "type": "signal", "bundle":{"name": "empty_37", "role": "default" }} , 
 	{ "name": "cutoff", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "cutoff", "role": "default" }} , 
 	{ "name": "empty_38", "direction": "in", "datatype": "sc_lv", "bitwidth":28, "type": "signal", "bundle":{"name": "empty_38", "role": "default" }} , 
 	{ "name": "empty_39", "direction": "in", "datatype": "sc_lv", "bitwidth":29, "type": "signal", "bundle":{"name": "empty_39", "role": "default" }} , 
 	{ "name": "empty_40", "direction": "in", "datatype": "sc_lv", "bitwidth":30, "type": "signal", "bundle":{"name": "empty_40", "role": "default" }} , 
 	{ "name": "empty", "direction": "in", "datatype": "sc_lv", "bitwidth":31, "type": "signal", "bundle":{"name": "empty", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65"],
		"CDFG" : "IDST7B32_Pipeline_VITIS_LOOP_73_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "58", "EstimateLatencyMax" : "58",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_31", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_30", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_29", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_28", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_27", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_26", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_25", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_24", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_23", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_22", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_21", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_20", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_19", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_18", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_17", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "dst_16", "Type" : "Vld", "Direction" : "O"},
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
			{"Name" : "src_16_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_17_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_18_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_19_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_20_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_21_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_22_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_23_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_24_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_25_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_26_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_27_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_28_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_29_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_30_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "src_31_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "conv3_i12_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i9_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "sh_prom_i_i_i", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_36", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_37", "Type" : "None", "Direction" : "I"},
			{"Name" : "cutoff", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_38", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_39", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_40", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_8", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_9", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_10", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_11", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_12", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_13", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_14", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_15", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_16", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_17", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_18", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_19", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_20", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_21", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_22", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_23", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_24", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_25", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_26", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_27", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_28", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_29", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_30", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idst7_32_31", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_73_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter25", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter25", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_0_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_1_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_2_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_3_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_4_U", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_5_U", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_6_U", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_7_U", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_8_U", "Parent" : "0"},
	{"ID" : "10", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_9_U", "Parent" : "0"},
	{"ID" : "11", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_10_U", "Parent" : "0"},
	{"ID" : "12", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_11_U", "Parent" : "0"},
	{"ID" : "13", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_12_U", "Parent" : "0"},
	{"ID" : "14", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_13_U", "Parent" : "0"},
	{"ID" : "15", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_14_U", "Parent" : "0"},
	{"ID" : "16", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_15_U", "Parent" : "0"},
	{"ID" : "17", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_16_U", "Parent" : "0"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_17_U", "Parent" : "0"},
	{"ID" : "19", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_18_U", "Parent" : "0"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_19_U", "Parent" : "0"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_20_U", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_21_U", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_22_U", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_23_U", "Parent" : "0"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_24_U", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_25_U", "Parent" : "0"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_26_U", "Parent" : "0"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_27_U", "Parent" : "0"},
	{"ID" : "29", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_28_U", "Parent" : "0"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_29_U", "Parent" : "0"},
	{"ID" : "31", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_30_U", "Parent" : "0"},
	{"ID" : "32", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.p_ZL8idst7_32_31_U", "Parent" : "0"},
	{"ID" : "33", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_7ns_32s_32_2_1_U176", "Parent" : "0"},
	{"ID" : "34", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U177", "Parent" : "0"},
	{"ID" : "35", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U178", "Parent" : "0"},
	{"ID" : "36", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U179", "Parent" : "0"},
	{"ID" : "37", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U180", "Parent" : "0"},
	{"ID" : "38", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U181", "Parent" : "0"},
	{"ID" : "39", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U182", "Parent" : "0"},
	{"ID" : "40", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U183", "Parent" : "0"},
	{"ID" : "41", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U184", "Parent" : "0"},
	{"ID" : "42", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U185", "Parent" : "0"},
	{"ID" : "43", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U186", "Parent" : "0"},
	{"ID" : "44", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U187", "Parent" : "0"},
	{"ID" : "45", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U188", "Parent" : "0"},
	{"ID" : "46", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U189", "Parent" : "0"},
	{"ID" : "47", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U190", "Parent" : "0"},
	{"ID" : "48", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U191", "Parent" : "0"},
	{"ID" : "49", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U192", "Parent" : "0"},
	{"ID" : "50", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U193", "Parent" : "0"},
	{"ID" : "51", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U194", "Parent" : "0"},
	{"ID" : "52", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U195", "Parent" : "0"},
	{"ID" : "53", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U196", "Parent" : "0"},
	{"ID" : "54", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U197", "Parent" : "0"},
	{"ID" : "55", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U198", "Parent" : "0"},
	{"ID" : "56", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U199", "Parent" : "0"},
	{"ID" : "57", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U200", "Parent" : "0"},
	{"ID" : "58", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U201", "Parent" : "0"},
	{"ID" : "59", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U202", "Parent" : "0"},
	{"ID" : "60", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U203", "Parent" : "0"},
	{"ID" : "61", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U204", "Parent" : "0"},
	{"ID" : "62", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U205", "Parent" : "0"},
	{"ID" : "63", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U206", "Parent" : "0"},
	{"ID" : "64", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_8s_32s_32_2_1_U207", "Parent" : "0"},
	{"ID" : "65", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	IDST7B32_Pipeline_VITIS_LOOP_73_1 {
		dst_0 {Type O LastRead -1 FirstWrite 25}
		dst_31 {Type O LastRead -1 FirstWrite 25}
		dst_30 {Type O LastRead -1 FirstWrite 25}
		dst_29 {Type O LastRead -1 FirstWrite 25}
		dst_28 {Type O LastRead -1 FirstWrite 25}
		dst_27 {Type O LastRead -1 FirstWrite 25}
		dst_26 {Type O LastRead -1 FirstWrite 25}
		dst_25 {Type O LastRead -1 FirstWrite 25}
		dst_24 {Type O LastRead -1 FirstWrite 25}
		dst_23 {Type O LastRead -1 FirstWrite 25}
		dst_22 {Type O LastRead -1 FirstWrite 25}
		dst_21 {Type O LastRead -1 FirstWrite 25}
		dst_20 {Type O LastRead -1 FirstWrite 25}
		dst_19 {Type O LastRead -1 FirstWrite 25}
		dst_18 {Type O LastRead -1 FirstWrite 25}
		dst_17 {Type O LastRead -1 FirstWrite 25}
		dst_16 {Type O LastRead -1 FirstWrite 25}
		dst_15 {Type O LastRead -1 FirstWrite 25}
		dst_14 {Type O LastRead -1 FirstWrite 25}
		dst_13 {Type O LastRead -1 FirstWrite 25}
		dst_12 {Type O LastRead -1 FirstWrite 25}
		dst_11 {Type O LastRead -1 FirstWrite 25}
		dst_10 {Type O LastRead -1 FirstWrite 25}
		dst_9 {Type O LastRead -1 FirstWrite 25}
		dst_8 {Type O LastRead -1 FirstWrite 25}
		dst_7 {Type O LastRead -1 FirstWrite 25}
		dst_6 {Type O LastRead -1 FirstWrite 25}
		dst_5 {Type O LastRead -1 FirstWrite 25}
		dst_4 {Type O LastRead -1 FirstWrite 25}
		dst_3 {Type O LastRead -1 FirstWrite 25}
		dst_2 {Type O LastRead -1 FirstWrite 25}
		dst_1 {Type O LastRead -1 FirstWrite 25}
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
		src_16_val {Type I LastRead 0 FirstWrite -1}
		src_17_val {Type I LastRead 0 FirstWrite -1}
		src_18_val {Type I LastRead 0 FirstWrite -1}
		src_19_val {Type I LastRead 0 FirstWrite -1}
		src_20_val {Type I LastRead 0 FirstWrite -1}
		src_21_val {Type I LastRead 0 FirstWrite -1}
		src_22_val {Type I LastRead 0 FirstWrite -1}
		src_23_val {Type I LastRead 0 FirstWrite -1}
		src_24_val {Type I LastRead 0 FirstWrite -1}
		src_25_val {Type I LastRead 0 FirstWrite -1}
		src_26_val {Type I LastRead 0 FirstWrite -1}
		src_27_val {Type I LastRead 0 FirstWrite -1}
		src_28_val {Type I LastRead 0 FirstWrite -1}
		src_29_val {Type I LastRead 0 FirstWrite -1}
		src_30_val {Type I LastRead 0 FirstWrite -1}
		src_31_val {Type I LastRead 0 FirstWrite -1}
		conv3_i12_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i9_i_i {Type I LastRead 0 FirstWrite -1}
		sh_prom_i_i_i {Type I LastRead 0 FirstWrite -1}
		empty_36 {Type I LastRead 0 FirstWrite -1}
		oMin {Type I LastRead 0 FirstWrite -1}
		oMax {Type I LastRead 0 FirstWrite -1}
		empty_37 {Type I LastRead 0 FirstWrite -1}
		cutoff {Type I LastRead 0 FirstWrite -1}
		empty_38 {Type I LastRead 0 FirstWrite -1}
		empty_39 {Type I LastRead 0 FirstWrite -1}
		empty_40 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		p_ZL8idst7_32_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_15 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_16 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_17 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_18 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_19 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_20 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_21 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_22 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_23 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_24 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_25 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_26 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_27 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_28 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_29 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_30 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idst7_32_31 {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "58", "Max" : "58"}
	, {"Name" : "Interval", "Min" : "58", "Max" : "58"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	dst_0 { ap_vld {  { dst_0 out_data 1 32 }  { dst_0_ap_vld out_vld 1 1 } } }
	dst_31 { ap_vld {  { dst_31 out_data 1 32 }  { dst_31_ap_vld out_vld 1 1 } } }
	dst_30 { ap_vld {  { dst_30 out_data 1 32 }  { dst_30_ap_vld out_vld 1 1 } } }
	dst_29 { ap_vld {  { dst_29 out_data 1 32 }  { dst_29_ap_vld out_vld 1 1 } } }
	dst_28 { ap_vld {  { dst_28 out_data 1 32 }  { dst_28_ap_vld out_vld 1 1 } } }
	dst_27 { ap_vld {  { dst_27 out_data 1 32 }  { dst_27_ap_vld out_vld 1 1 } } }
	dst_26 { ap_vld {  { dst_26 out_data 1 32 }  { dst_26_ap_vld out_vld 1 1 } } }
	dst_25 { ap_vld {  { dst_25 out_data 1 32 }  { dst_25_ap_vld out_vld 1 1 } } }
	dst_24 { ap_vld {  { dst_24 out_data 1 32 }  { dst_24_ap_vld out_vld 1 1 } } }
	dst_23 { ap_vld {  { dst_23 out_data 1 32 }  { dst_23_ap_vld out_vld 1 1 } } }
	dst_22 { ap_vld {  { dst_22 out_data 1 32 }  { dst_22_ap_vld out_vld 1 1 } } }
	dst_21 { ap_vld {  { dst_21 out_data 1 32 }  { dst_21_ap_vld out_vld 1 1 } } }
	dst_20 { ap_vld {  { dst_20 out_data 1 32 }  { dst_20_ap_vld out_vld 1 1 } } }
	dst_19 { ap_vld {  { dst_19 out_data 1 32 }  { dst_19_ap_vld out_vld 1 1 } } }
	dst_18 { ap_vld {  { dst_18 out_data 1 32 }  { dst_18_ap_vld out_vld 1 1 } } }
	dst_17 { ap_vld {  { dst_17 out_data 1 32 }  { dst_17_ap_vld out_vld 1 1 } } }
	dst_16 { ap_vld {  { dst_16 out_data 1 32 }  { dst_16_ap_vld out_vld 1 1 } } }
	dst_15 { ap_vld {  { dst_15 out_data 1 32 }  { dst_15_ap_vld out_vld 1 1 } } }
	dst_14 { ap_vld {  { dst_14 out_data 1 32 }  { dst_14_ap_vld out_vld 1 1 } } }
	dst_13 { ap_vld {  { dst_13 out_data 1 32 }  { dst_13_ap_vld out_vld 1 1 } } }
	dst_12 { ap_vld {  { dst_12 out_data 1 32 }  { dst_12_ap_vld out_vld 1 1 } } }
	dst_11 { ap_vld {  { dst_11 out_data 1 32 }  { dst_11_ap_vld out_vld 1 1 } } }
	dst_10 { ap_vld {  { dst_10 out_data 1 32 }  { dst_10_ap_vld out_vld 1 1 } } }
	dst_9 { ap_vld {  { dst_9 out_data 1 32 }  { dst_9_ap_vld out_vld 1 1 } } }
	dst_8 { ap_vld {  { dst_8 out_data 1 32 }  { dst_8_ap_vld out_vld 1 1 } } }
	dst_7 { ap_vld {  { dst_7 out_data 1 32 }  { dst_7_ap_vld out_vld 1 1 } } }
	dst_6 { ap_vld {  { dst_6 out_data 1 32 }  { dst_6_ap_vld out_vld 1 1 } } }
	dst_5 { ap_vld {  { dst_5 out_data 1 32 }  { dst_5_ap_vld out_vld 1 1 } } }
	dst_4 { ap_vld {  { dst_4 out_data 1 32 }  { dst_4_ap_vld out_vld 1 1 } } }
	dst_3 { ap_vld {  { dst_3 out_data 1 32 }  { dst_3_ap_vld out_vld 1 1 } } }
	dst_2 { ap_vld {  { dst_2 out_data 1 32 }  { dst_2_ap_vld out_vld 1 1 } } }
	dst_1 { ap_vld {  { dst_1 out_data 1 32 }  { dst_1_ap_vld out_vld 1 1 } } }
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
	src_16_val { ap_none {  { src_16_val in_data 0 32 } } }
	src_17_val { ap_none {  { src_17_val in_data 0 32 } } }
	src_18_val { ap_none {  { src_18_val in_data 0 32 } } }
	src_19_val { ap_none {  { src_19_val in_data 0 32 } } }
	src_20_val { ap_none {  { src_20_val in_data 0 32 } } }
	src_21_val { ap_none {  { src_21_val in_data 0 32 } } }
	src_22_val { ap_none {  { src_22_val in_data 0 32 } } }
	src_23_val { ap_none {  { src_23_val in_data 0 32 } } }
	src_24_val { ap_none {  { src_24_val in_data 0 32 } } }
	src_25_val { ap_none {  { src_25_val in_data 0 32 } } }
	src_26_val { ap_none {  { src_26_val in_data 0 32 } } }
	src_27_val { ap_none {  { src_27_val in_data 0 32 } } }
	src_28_val { ap_none {  { src_28_val in_data 0 32 } } }
	src_29_val { ap_none {  { src_29_val in_data 0 32 } } }
	src_30_val { ap_none {  { src_30_val in_data 0 32 } } }
	src_31_val { ap_none {  { src_31_val in_data 0 32 } } }
	conv3_i12_i_i { ap_none {  { conv3_i12_i_i in_data 0 32 } } }
	sh_prom_i9_i_i { ap_none {  { sh_prom_i9_i_i in_data 0 32 } } }
	sh_prom_i_i_i { ap_none {  { sh_prom_i_i_i in_data 0 32 } } }
	empty_36 { ap_none {  { empty_36 in_data 0 1 } } }
	oMin { ap_none {  { oMin in_data 0 32 } } }
	oMax { ap_none {  { oMax in_data 0 32 } } }
	empty_37 { ap_none {  { empty_37 in_data 0 27 } } }
	cutoff { ap_none {  { cutoff in_data 0 32 } } }
	empty_38 { ap_none {  { empty_38 in_data 0 28 } } }
	empty_39 { ap_none {  { empty_39 in_data 0 29 } } }
	empty_40 { ap_none {  { empty_40 in_data 0 30 } } }
	empty { ap_none {  { empty in_data 0 31 } } }
}
