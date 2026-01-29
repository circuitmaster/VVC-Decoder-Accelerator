set moduleName IDCT2B32
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
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
set cdfgNum 9
set C_modelName {IDCT2B32}
set C_modelType { int 1024 }
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
	{ in_8_val int 32 regular  }
	{ in_9_val int 32 regular  }
	{ in_10_val int 32 regular  }
	{ in_11_val int 32 regular  }
	{ in_12_val int 32 regular  }
	{ in_13_val int 32 regular  }
	{ in_14_val int 32 regular  }
	{ in_15_val int 32 regular  }
	{ in_16_val int 26 regular  }
	{ in_17_val int 32 regular  }
	{ in_18_val int 32 regular  }
	{ in_19_val int 32 regular  }
	{ in_20_val int 32 regular  }
	{ in_21_val int 32 regular  }
	{ in_22_val int 32 regular  }
	{ in_23_val int 32 regular  }
	{ in_24_val int 32 regular  }
	{ in_25_val int 32 regular  }
	{ in_26_val int 32 regular  }
	{ in_27_val int 32 regular  }
	{ in_28_val int 32 regular  }
	{ in_29_val int 32 regular  }
	{ in_30_val int 32 regular  }
	{ in_31_val int 32 regular  }
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
 	{ "Name" : "in_8_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_9_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_10_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_11_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_12_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_13_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_14_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_15_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_16_val", "interface" : "wire", "bitwidth" : 26, "direction" : "READONLY"} , 
 	{ "Name" : "in_17_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_18_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_19_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_20_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_21_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_22_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_23_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_24_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_25_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_26_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_27_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_28_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_29_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_30_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "in_31_val", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "ap_return", "interface" : "wire", "bitwidth" : 1024} ]}
# RTL Port declarations: 
set portNum 71
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ ap_ce sc_in sc_logic 1 ce -1 } 
	{ in_0_val sc_in sc_lv 26 signal 0 } 
	{ in_1_val sc_in sc_lv 32 signal 1 } 
	{ in_2_val sc_in sc_lv 32 signal 2 } 
	{ in_3_val sc_in sc_lv 32 signal 3 } 
	{ in_4_val sc_in sc_lv 32 signal 4 } 
	{ in_5_val sc_in sc_lv 32 signal 5 } 
	{ in_6_val sc_in sc_lv 32 signal 6 } 
	{ in_7_val sc_in sc_lv 32 signal 7 } 
	{ in_8_val sc_in sc_lv 32 signal 8 } 
	{ in_9_val sc_in sc_lv 32 signal 9 } 
	{ in_10_val sc_in sc_lv 32 signal 10 } 
	{ in_11_val sc_in sc_lv 32 signal 11 } 
	{ in_12_val sc_in sc_lv 32 signal 12 } 
	{ in_13_val sc_in sc_lv 32 signal 13 } 
	{ in_14_val sc_in sc_lv 32 signal 14 } 
	{ in_15_val sc_in sc_lv 32 signal 15 } 
	{ in_16_val sc_in sc_lv 26 signal 16 } 
	{ in_17_val sc_in sc_lv 32 signal 17 } 
	{ in_18_val sc_in sc_lv 32 signal 18 } 
	{ in_19_val sc_in sc_lv 32 signal 19 } 
	{ in_20_val sc_in sc_lv 32 signal 20 } 
	{ in_21_val sc_in sc_lv 32 signal 21 } 
	{ in_22_val sc_in sc_lv 32 signal 22 } 
	{ in_23_val sc_in sc_lv 32 signal 23 } 
	{ in_24_val sc_in sc_lv 32 signal 24 } 
	{ in_25_val sc_in sc_lv 32 signal 25 } 
	{ in_26_val sc_in sc_lv 32 signal 26 } 
	{ in_27_val sc_in sc_lv 32 signal 27 } 
	{ in_28_val sc_in sc_lv 32 signal 28 } 
	{ in_29_val sc_in sc_lv 32 signal 29 } 
	{ in_30_val sc_in sc_lv 32 signal 30 } 
	{ in_31_val sc_in sc_lv 32 signal 31 } 
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
	{ ap_return_16 sc_out sc_lv 32 signal -1 } 
	{ ap_return_17 sc_out sc_lv 32 signal -1 } 
	{ ap_return_18 sc_out sc_lv 32 signal -1 } 
	{ ap_return_19 sc_out sc_lv 32 signal -1 } 
	{ ap_return_20 sc_out sc_lv 32 signal -1 } 
	{ ap_return_21 sc_out sc_lv 32 signal -1 } 
	{ ap_return_22 sc_out sc_lv 32 signal -1 } 
	{ ap_return_23 sc_out sc_lv 32 signal -1 } 
	{ ap_return_24 sc_out sc_lv 32 signal -1 } 
	{ ap_return_25 sc_out sc_lv 32 signal -1 } 
	{ ap_return_26 sc_out sc_lv 32 signal -1 } 
	{ ap_return_27 sc_out sc_lv 32 signal -1 } 
	{ ap_return_28 sc_out sc_lv 32 signal -1 } 
	{ ap_return_29 sc_out sc_lv 32 signal -1 } 
	{ ap_return_30 sc_out sc_lv 32 signal -1 } 
	{ ap_return_31 sc_out sc_lv 32 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "ap_ce", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "ce", "bundle":{"name": "ap_ce", "role": "default" }} , 
 	{ "name": "in_0_val", "direction": "in", "datatype": "sc_lv", "bitwidth":26, "type": "signal", "bundle":{"name": "in_0_val", "role": "default" }} , 
 	{ "name": "in_1_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_1_val", "role": "default" }} , 
 	{ "name": "in_2_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_2_val", "role": "default" }} , 
 	{ "name": "in_3_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_3_val", "role": "default" }} , 
 	{ "name": "in_4_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_4_val", "role": "default" }} , 
 	{ "name": "in_5_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_5_val", "role": "default" }} , 
 	{ "name": "in_6_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_6_val", "role": "default" }} , 
 	{ "name": "in_7_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_7_val", "role": "default" }} , 
 	{ "name": "in_8_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_8_val", "role": "default" }} , 
 	{ "name": "in_9_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_9_val", "role": "default" }} , 
 	{ "name": "in_10_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_10_val", "role": "default" }} , 
 	{ "name": "in_11_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_11_val", "role": "default" }} , 
 	{ "name": "in_12_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_12_val", "role": "default" }} , 
 	{ "name": "in_13_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_13_val", "role": "default" }} , 
 	{ "name": "in_14_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_14_val", "role": "default" }} , 
 	{ "name": "in_15_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_15_val", "role": "default" }} , 
 	{ "name": "in_16_val", "direction": "in", "datatype": "sc_lv", "bitwidth":26, "type": "signal", "bundle":{"name": "in_16_val", "role": "default" }} , 
 	{ "name": "in_17_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_17_val", "role": "default" }} , 
 	{ "name": "in_18_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_18_val", "role": "default" }} , 
 	{ "name": "in_19_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_19_val", "role": "default" }} , 
 	{ "name": "in_20_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_20_val", "role": "default" }} , 
 	{ "name": "in_21_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_21_val", "role": "default" }} , 
 	{ "name": "in_22_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_22_val", "role": "default" }} , 
 	{ "name": "in_23_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_23_val", "role": "default" }} , 
 	{ "name": "in_24_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_24_val", "role": "default" }} , 
 	{ "name": "in_25_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_25_val", "role": "default" }} , 
 	{ "name": "in_26_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_26_val", "role": "default" }} , 
 	{ "name": "in_27_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_27_val", "role": "default" }} , 
 	{ "name": "in_28_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_28_val", "role": "default" }} , 
 	{ "name": "in_29_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_29_val", "role": "default" }} , 
 	{ "name": "in_30_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_30_val", "role": "default" }} , 
 	{ "name": "in_31_val", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_31_val", "role": "default" }} , 
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
 	{ "name": "ap_return_16", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_16", "role": "default" }} , 
 	{ "name": "ap_return_17", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_17", "role": "default" }} , 
 	{ "name": "ap_return_18", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_18", "role": "default" }} , 
 	{ "name": "ap_return_19", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_19", "role": "default" }} , 
 	{ "name": "ap_return_20", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_20", "role": "default" }} , 
 	{ "name": "ap_return_21", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_21", "role": "default" }} , 
 	{ "name": "ap_return_22", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_22", "role": "default" }} , 
 	{ "name": "ap_return_23", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_23", "role": "default" }} , 
 	{ "name": "ap_return_24", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_24", "role": "default" }} , 
 	{ "name": "ap_return_25", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_25", "role": "default" }} , 
 	{ "name": "ap_return_26", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_26", "role": "default" }} , 
 	{ "name": "ap_return_27", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_27", "role": "default" }} , 
 	{ "name": "ap_return_28", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_28", "role": "default" }} , 
 	{ "name": "ap_return_29", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_29", "role": "default" }} , 
 	{ "name": "ap_return_30", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_30", "role": "default" }} , 
 	{ "name": "ap_return_31", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "ap_return_31", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122"],
		"CDFG" : "IDCT2B32",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
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
			{"Name" : "in_15_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_16_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_17_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_18_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_19_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_20_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_21_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_22_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_23_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_24_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_25_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_26_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_27_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_28_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_29_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_30_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_31_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306", "Parent" : "0", "Child" : ["2", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29"],
		"CDFG" : "IDCT2B16",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "4", "EstimateLatencyMin" : "4", "EstimateLatencyMax" : "4",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
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
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164", "Parent" : "1", "Child" : ["3", "6", "7", "8", "9", "10"],
		"CDFG" : "IDCT2B8",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "3", "EstimateLatencyMin" : "3", "EstimateLatencyMax" : "3",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
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
	{"ID" : "3", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.grp_IDCT2B4_fu_92", "Parent" : "2", "Child" : ["4", "5"],
		"CDFG" : "IDCT2B4",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "Aligned", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "1", "EstimateLatencyMin" : "1", "EstimateLatencyMax" : "1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "in_0_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_1_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_2_val", "Type" : "None", "Direction" : "I"},
			{"Name" : "in_3_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "4", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.grp_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "3",
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
	{"ID" : "5", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.grp_IDCT2B4_fu_92.mul_32s_8s_32_2_1_U3", "Parent" : "3"},
	{"ID" : "6", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.mul_32s_7s_32_2_1_U9", "Parent" : "2"},
	{"ID" : "7", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.mul_32s_8s_32_2_1_U10", "Parent" : "2"},
	{"ID" : "8", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.mul_32s_7s_32_2_1_U11", "Parent" : "2"},
	{"ID" : "9", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.mul_32s_8s_32_2_1_U12", "Parent" : "2"},
	{"ID" : "10", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.grp_IDCT2B8_fu_164.mul_32s_8s_32_2_1_U13", "Parent" : "2"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_7s_32_2_1_U23", "Parent" : "1"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_6s_32_2_1_U24", "Parent" : "1"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U25", "Parent" : "1"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_7s_32_2_1_U26", "Parent" : "1"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_6s_32_2_1_U27", "Parent" : "1"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U28", "Parent" : "1"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U29", "Parent" : "1"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_7s_32_2_1_U30", "Parent" : "1"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_7s_32_2_1_U31", "Parent" : "1"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U32", "Parent" : "1"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U33", "Parent" : "1"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U34", "Parent" : "1"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U35", "Parent" : "1"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_6s_32_2_1_U36", "Parent" : "1"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_7s_32_2_1_U37", "Parent" : "1"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U38", "Parent" : "1"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U39", "Parent" : "1"},
	{"ID" : "28", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_8s_32_2_1_U40", "Parent" : "1"},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B16_fu_306.mul_32s_6s_32_2_1_U41", "Parent" : "1"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U59", "Parent" : "0"},
	{"ID" : "31", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U60", "Parent" : "0"},
	{"ID" : "32", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U61", "Parent" : "0"},
	{"ID" : "33", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U62", "Parent" : "0"},
	{"ID" : "34", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U63", "Parent" : "0"},
	{"ID" : "35", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U64", "Parent" : "0"},
	{"ID" : "36", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U65", "Parent" : "0"},
	{"ID" : "37", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U66", "Parent" : "0"},
	{"ID" : "38", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U67", "Parent" : "0"},
	{"ID" : "39", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U68", "Parent" : "0"},
	{"ID" : "40", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U69", "Parent" : "0"},
	{"ID" : "41", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U70", "Parent" : "0"},
	{"ID" : "42", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U71", "Parent" : "0"},
	{"ID" : "43", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U72", "Parent" : "0"},
	{"ID" : "44", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U73", "Parent" : "0"},
	{"ID" : "45", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U74", "Parent" : "0"},
	{"ID" : "46", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U75", "Parent" : "0"},
	{"ID" : "47", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U76", "Parent" : "0"},
	{"ID" : "48", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U77", "Parent" : "0"},
	{"ID" : "49", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U78", "Parent" : "0"},
	{"ID" : "50", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U79", "Parent" : "0"},
	{"ID" : "51", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U80", "Parent" : "0"},
	{"ID" : "52", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U81", "Parent" : "0"},
	{"ID" : "53", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U82", "Parent" : "0"},
	{"ID" : "54", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U83", "Parent" : "0"},
	{"ID" : "55", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U84", "Parent" : "0"},
	{"ID" : "56", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U85", "Parent" : "0"},
	{"ID" : "57", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U86", "Parent" : "0"},
	{"ID" : "58", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U87", "Parent" : "0"},
	{"ID" : "59", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U88", "Parent" : "0"},
	{"ID" : "60", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U89", "Parent" : "0"},
	{"ID" : "61", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U90", "Parent" : "0"},
	{"ID" : "62", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U91", "Parent" : "0"},
	{"ID" : "63", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U92", "Parent" : "0"},
	{"ID" : "64", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U93", "Parent" : "0"},
	{"ID" : "65", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U94", "Parent" : "0"},
	{"ID" : "66", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U95", "Parent" : "0"},
	{"ID" : "67", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U96", "Parent" : "0"},
	{"ID" : "68", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U97", "Parent" : "0"},
	{"ID" : "69", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U98", "Parent" : "0"},
	{"ID" : "70", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U99", "Parent" : "0"},
	{"ID" : "71", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U100", "Parent" : "0"},
	{"ID" : "72", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U101", "Parent" : "0"},
	{"ID" : "73", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U102", "Parent" : "0"},
	{"ID" : "74", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U103", "Parent" : "0"},
	{"ID" : "75", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U104", "Parent" : "0"},
	{"ID" : "76", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U105", "Parent" : "0"},
	{"ID" : "77", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U106", "Parent" : "0"},
	{"ID" : "78", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U107", "Parent" : "0"},
	{"ID" : "79", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U108", "Parent" : "0"},
	{"ID" : "80", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U109", "Parent" : "0"},
	{"ID" : "81", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_6s_32_2_1_U110", "Parent" : "0"},
	{"ID" : "82", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U111", "Parent" : "0"},
	{"ID" : "83", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U112", "Parent" : "0"},
	{"ID" : "84", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U113", "Parent" : "0"},
	{"ID" : "85", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U114", "Parent" : "0"},
	{"ID" : "86", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U115", "Parent" : "0"},
	{"ID" : "87", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U116", "Parent" : "0"},
	{"ID" : "88", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U117", "Parent" : "0"},
	{"ID" : "89", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U118", "Parent" : "0"},
	{"ID" : "90", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U119", "Parent" : "0"},
	{"ID" : "91", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U120", "Parent" : "0"},
	{"ID" : "92", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U121", "Parent" : "0"},
	{"ID" : "93", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U122", "Parent" : "0"},
	{"ID" : "94", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U123", "Parent" : "0"},
	{"ID" : "95", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U124", "Parent" : "0"},
	{"ID" : "96", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U125", "Parent" : "0"},
	{"ID" : "97", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U126", "Parent" : "0"},
	{"ID" : "98", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U127", "Parent" : "0"},
	{"ID" : "99", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U128", "Parent" : "0"},
	{"ID" : "100", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U129", "Parent" : "0"},
	{"ID" : "101", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U130", "Parent" : "0"},
	{"ID" : "102", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U131", "Parent" : "0"},
	{"ID" : "103", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U132", "Parent" : "0"},
	{"ID" : "104", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U133", "Parent" : "0"},
	{"ID" : "105", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U134", "Parent" : "0"},
	{"ID" : "106", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U135", "Parent" : "0"},
	{"ID" : "107", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U136", "Parent" : "0"},
	{"ID" : "108", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U137", "Parent" : "0"},
	{"ID" : "109", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U138", "Parent" : "0"},
	{"ID" : "110", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U139", "Parent" : "0"},
	{"ID" : "111", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U140", "Parent" : "0"},
	{"ID" : "112", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U141", "Parent" : "0"},
	{"ID" : "113", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_8s_32_2_1_U142", "Parent" : "0"},
	{"ID" : "114", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_32_2_1_U143", "Parent" : "0"},
	{"ID" : "115", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U144", "Parent" : "0"},
	{"ID" : "116", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U145", "Parent" : "0"},
	{"ID" : "117", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U146", "Parent" : "0"},
	{"ID" : "118", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U147", "Parent" : "0"},
	{"ID" : "119", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U148", "Parent" : "0"},
	{"ID" : "120", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U149", "Parent" : "0"},
	{"ID" : "121", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U150", "Parent" : "0"},
	{"ID" : "122", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_5s_32_2_1_U151", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	IDCT2B32 {
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
		in_15_val {Type I LastRead 0 FirstWrite -1}
		in_16_val {Type I LastRead 0 FirstWrite -1}
		in_17_val {Type I LastRead 0 FirstWrite -1}
		in_18_val {Type I LastRead 0 FirstWrite -1}
		in_19_val {Type I LastRead 0 FirstWrite -1}
		in_20_val {Type I LastRead 0 FirstWrite -1}
		in_21_val {Type I LastRead 0 FirstWrite -1}
		in_22_val {Type I LastRead 0 FirstWrite -1}
		in_23_val {Type I LastRead 0 FirstWrite -1}
		in_24_val {Type I LastRead 0 FirstWrite -1}
		in_25_val {Type I LastRead 0 FirstWrite -1}
		in_26_val {Type I LastRead 0 FirstWrite -1}
		in_27_val {Type I LastRead 0 FirstWrite -1}
		in_28_val {Type I LastRead 0 FirstWrite -1}
		in_29_val {Type I LastRead 0 FirstWrite -1}
		in_30_val {Type I LastRead 0 FirstWrite -1}
		in_31_val {Type I LastRead 0 FirstWrite -1}}
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
	{"Name" : "Latency", "Min" : "4", "Max" : "4"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
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
	in_8_val { ap_none {  { in_8_val in_data 0 32 } } }
	in_9_val { ap_none {  { in_9_val in_data 0 32 } } }
	in_10_val { ap_none {  { in_10_val in_data 0 32 } } }
	in_11_val { ap_none {  { in_11_val in_data 0 32 } } }
	in_12_val { ap_none {  { in_12_val in_data 0 32 } } }
	in_13_val { ap_none {  { in_13_val in_data 0 32 } } }
	in_14_val { ap_none {  { in_14_val in_data 0 32 } } }
	in_15_val { ap_none {  { in_15_val in_data 0 32 } } }
	in_16_val { ap_none {  { in_16_val in_data 0 26 } } }
	in_17_val { ap_none {  { in_17_val in_data 0 32 } } }
	in_18_val { ap_none {  { in_18_val in_data 0 32 } } }
	in_19_val { ap_none {  { in_19_val in_data 0 32 } } }
	in_20_val { ap_none {  { in_20_val in_data 0 32 } } }
	in_21_val { ap_none {  { in_21_val in_data 0 32 } } }
	in_22_val { ap_none {  { in_22_val in_data 0 32 } } }
	in_23_val { ap_none {  { in_23_val in_data 0 32 } } }
	in_24_val { ap_none {  { in_24_val in_data 0 32 } } }
	in_25_val { ap_none {  { in_25_val in_data 0 32 } } }
	in_26_val { ap_none {  { in_26_val in_data 0 32 } } }
	in_27_val { ap_none {  { in_27_val in_data 0 32 } } }
	in_28_val { ap_none {  { in_28_val in_data 0 32 } } }
	in_29_val { ap_none {  { in_29_val in_data 0 32 } } }
	in_30_val { ap_none {  { in_30_val in_data 0 32 } } }
	in_31_val { ap_none {  { in_31_val in_data 0 32 } } }
}
