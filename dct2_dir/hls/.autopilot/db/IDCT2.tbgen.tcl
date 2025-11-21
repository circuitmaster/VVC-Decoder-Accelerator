set moduleName IDCT2
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type loop_auto_rewind
set FunctionProtocol ap_ctrl_chain
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 8
set C_modelName {IDCT2}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ gmem0 int 512 regular {axi_master 0}  }
	{ gmem1 int 512 regular {axi_master 1}  }
	{ in_r int 64 regular {axi_slave 0}  }
	{ out_r int 64 regular {axi_slave 0}  }
	{ block_size int 32 regular {axi_slave 0}  }
	{ size int 32 regular {axi_slave 0}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "gmem0", "interface" : "axi_master", "bitwidth" : 512, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "in_r","offset": { "type": "dynamic","port_name": "in_r","bundle": "control"},"direction": "READONLY"}]}]} , 
 	{ "Name" : "gmem1", "interface" : "axi_master", "bitwidth" : 512, "direction" : "WRITEONLY", "bitSlice":[ {"cElement": [{"cName": "out_r","offset": { "type": "dynamic","port_name": "out_r","bundle": "control"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "in_r", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "out_r", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "block_size", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":47}} , 
 	{ "Name" : "size", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":48}, "offset_end" : {"in":55}} ]}
# RTL Port declarations: 
set portNum 110
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ m_axi_gmem0_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem0_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_AWLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem0_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WDATA sc_out sc_lv 512 signal 0 } 
	{ m_axi_gmem0_WSTRB sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem0_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_gmem0_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_ARLEN sc_out sc_lv 8 signal 0 } 
	{ m_axi_gmem0_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_gmem0_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_gmem0_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_gmem0_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RDATA sc_in sc_lv 512 signal 0 } 
	{ m_axi_gmem0_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem0_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_gmem0_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_gmem0_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_gmem0_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem0_BUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_gmem1_AWVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_AWREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_AWADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem1_AWID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_AWLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem1_AWSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_AWBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_AWLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_AWCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_AWQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_AWUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_WVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WDATA sc_out sc_lv 512 signal 1 } 
	{ m_axi_gmem1_WSTRB sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem1_WLAST sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_WID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_WUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_ARVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_ARREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_ARADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_gmem1_ARID sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_ARLEN sc_out sc_lv 8 signal 1 } 
	{ m_axi_gmem1_ARSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_ARBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_ARLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_gmem1_ARCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_gmem1_ARQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_gmem1_ARUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RDATA sc_in sc_lv 512 signal 1 } 
	{ m_axi_gmem1_RLAST sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_RID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_RRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem1_BVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_gmem1_BREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_gmem1_BRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_gmem1_BID sc_in sc_lv 1 signal 1 } 
	{ m_axi_gmem1_BUSER sc_in sc_lv 1 signal 1 } 
	{ s_axi_control_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_control_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_control_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_control_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_BRESP sc_out sc_lv 2 signal -1 } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"IDCT2","role":"start","value":"0","valid_bit":"0"},{"name":"IDCT2","role":"continue","value":"0","valid_bit":"4"},{"name":"IDCT2","role":"auto_start","value":"0","valid_bit":"7"},{"name":"in_r","role":"data","value":"16"},{"name":"out_r","role":"data","value":"28"},{"name":"block_size","role":"data","value":"40"},{"name":"size","role":"data","value":"48"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[{"name":"IDCT2","role":"start","value":"0","valid_bit":"0"},{"name":"IDCT2","role":"done","value":"0","valid_bit":"1"},{"name":"IDCT2","role":"idle","value":"0","valid_bit":"2"},{"name":"IDCT2","role":"ready","value":"0","valid_bit":"3"},{"name":"IDCT2","role":"auto_start","value":"0","valid_bit":"7"}] },
	{ "name": "s_axi_control_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARVALID" } },
	{ "name": "s_axi_control_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "ARREADY" } },
	{ "name": "s_axi_control_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RVALID" } },
	{ "name": "s_axi_control_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "RREADY" } },
	{ "name": "s_axi_control_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "RDATA" } },
	{ "name": "s_axi_control_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "RRESP" } },
	{ "name": "s_axi_control_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BVALID" } },
	{ "name": "s_axi_control_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "BREADY" } },
	{ "name": "s_axi_control_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "control", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "interrupt" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }} , 
 	{ "name": "m_axi_gmem0_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem0_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem0_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem0_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem0_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem0_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem0_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem0_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem0_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem0_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem0_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem0_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem0_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem0_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem0_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem0_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem0", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem0_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem0_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem0_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WID" }} , 
 	{ "name": "m_axi_gmem0_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem0_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem0_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem0_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem0", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem0_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem0_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem0_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem0_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem0_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem0_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem0_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem0", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem0_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem0_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem0", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem0_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem0_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem0_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem0_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem0", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem0_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem0_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RID" }} , 
 	{ "name": "m_axi_gmem0_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem0_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem0_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem0_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem0_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem0", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem0_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BID" }} , 
 	{ "name": "m_axi_gmem0_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem0", "role": "BUSER" }} , 
 	{ "name": "m_axi_gmem1_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWVALID" }} , 
 	{ "name": "m_axi_gmem1_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREADY" }} , 
 	{ "name": "m_axi_gmem1_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "AWADDR" }} , 
 	{ "name": "m_axi_gmem1_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWID" }} , 
 	{ "name": "m_axi_gmem1_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLEN" }} , 
 	{ "name": "m_axi_gmem1_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_gmem1_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWBURST" }} , 
 	{ "name": "m_axi_gmem1_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_gmem1_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_gmem1_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "AWPROT" }} , 
 	{ "name": "m_axi_gmem1_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWQOS" }} , 
 	{ "name": "m_axi_gmem1_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "AWREGION" }} , 
 	{ "name": "m_axi_gmem1_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "AWUSER" }} , 
 	{ "name": "m_axi_gmem1_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WVALID" }} , 
 	{ "name": "m_axi_gmem1_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WREADY" }} , 
 	{ "name": "m_axi_gmem1_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem1", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem1_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "WSTRB" }} , 
 	{ "name": "m_axi_gmem1_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WLAST" }} , 
 	{ "name": "m_axi_gmem1_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WID" }} , 
 	{ "name": "m_axi_gmem1_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "WUSER" }} , 
 	{ "name": "m_axi_gmem1_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARVALID" }} , 
 	{ "name": "m_axi_gmem1_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREADY" }} , 
 	{ "name": "m_axi_gmem1_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "gmem1", "role": "ARADDR" }} , 
 	{ "name": "m_axi_gmem1_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARID" }} , 
 	{ "name": "m_axi_gmem1_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLEN" }} , 
 	{ "name": "m_axi_gmem1_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_gmem1_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARBURST" }} , 
 	{ "name": "m_axi_gmem1_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_gmem1_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_gmem1_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "gmem1", "role": "ARPROT" }} , 
 	{ "name": "m_axi_gmem1_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARQOS" }} , 
 	{ "name": "m_axi_gmem1_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "gmem1", "role": "ARREGION" }} , 
 	{ "name": "m_axi_gmem1_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "ARUSER" }} , 
 	{ "name": "m_axi_gmem1_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RVALID" }} , 
 	{ "name": "m_axi_gmem1_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RREADY" }} , 
 	{ "name": "m_axi_gmem1_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":512, "type": "signal", "bundle":{"name": "gmem1", "role": "RDATA" }} , 
 	{ "name": "m_axi_gmem1_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RLAST" }} , 
 	{ "name": "m_axi_gmem1_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RID" }} , 
 	{ "name": "m_axi_gmem1_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "RUSER" }} , 
 	{ "name": "m_axi_gmem1_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "RRESP" }} , 
 	{ "name": "m_axi_gmem1_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BVALID" }} , 
 	{ "name": "m_axi_gmem1_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BREADY" }} , 
 	{ "name": "m_axi_gmem1_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "gmem1", "role": "BRESP" }} , 
 	{ "name": "m_axi_gmem1_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BID" }} , 
 	{ "name": "m_axi_gmem1_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "gmem1", "role": "BUSER" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "30", "153", "392", "395", "404", "405", "406", "407", "408"],
		"CDFG" : "IDCT2",
		"Protocol" : "ap_ctrl_chain",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "145", "EstimateLatencyMax" : "1168",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "gmem0", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "gmem0_blk_n_AR", "Type" : "RtlSignal"},
					{"Name" : "gmem0_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "gmem1", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "gmem1_blk_n_AW", "Type" : "RtlSignal"},
					{"Name" : "gmem1_blk_n_W", "Type" : "RtlSignal"},
					{"Name" : "gmem1_blk_n_B", "Type" : "RtlSignal"}]},
			{"Name" : "in_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "out_r", "Type" : "None", "Direction" : "I"},
			{"Name" : "block_size", "Type" : "None", "Direction" : "I"},
			{"Name" : "size", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_324_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter143", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter143", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "1"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260", "Parent" : "0", "Child" : ["2", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29"],
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
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164", "Parent" : "1", "Child" : ["3", "6", "7", "8", "9", "10"],
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
	{"ID" : "3", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92", "Parent" : "2", "Child" : ["4", "5"],
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
	{"ID" : "4", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "3",
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
	{"ID" : "5", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.mul_32s_8s_32_1_1_U3", "Parent" : "3"},
	{"ID" : "6", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U9", "Parent" : "2"},
	{"ID" : "7", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U10", "Parent" : "2"},
	{"ID" : "8", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U11", "Parent" : "2"},
	{"ID" : "9", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U12", "Parent" : "2"},
	{"ID" : "10", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U13", "Parent" : "2"},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_7s_32_1_1_U23", "Parent" : "1"},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U24", "Parent" : "1"},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U25", "Parent" : "1"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_6s_32_1_1_U26", "Parent" : "1"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U27", "Parent" : "1"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U28", "Parent" : "1"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_6s_32_1_1_U29", "Parent" : "1"},
	{"ID" : "18", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_7s_32_1_1_U30", "Parent" : "1"},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U31", "Parent" : "1"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_7s_32_1_1_U32", "Parent" : "1"},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_6s_32_1_1_U33", "Parent" : "1"},
	{"ID" : "22", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U34", "Parent" : "1"},
	{"ID" : "23", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U35", "Parent" : "1"},
	{"ID" : "24", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U36", "Parent" : "1"},
	{"ID" : "25", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U37", "Parent" : "1"},
	{"ID" : "26", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_7s_32_1_1_U38", "Parent" : "1"},
	{"ID" : "27", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_6s_32_1_1_U39", "Parent" : "1"},
	{"ID" : "28", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_7s_32_1_1_U40", "Parent" : "1"},
	{"ID" : "29", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret4_IDCT2B16_fu_260.mul_32s_8s_32_1_1_U41", "Parent" : "1"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280", "Parent" : "0", "Child" : ["31", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124", "125", "126", "127", "128", "129", "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148", "149", "150", "151", "152"],
		"CDFG" : "IDCT2B32",
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
	{"ID" : "31", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306", "Parent" : "30", "Child" : ["32", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54", "55", "56", "57", "58", "59"],
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
	{"ID" : "32", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164", "Parent" : "31", "Child" : ["33", "36", "37", "38", "39", "40"],
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
	{"ID" : "33", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92", "Parent" : "32", "Child" : ["34", "35"],
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
	{"ID" : "34", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "33",
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
	{"ID" : "35", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.mul_32s_8s_32_1_1_U3", "Parent" : "33"},
	{"ID" : "36", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U9", "Parent" : "32"},
	{"ID" : "37", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U10", "Parent" : "32"},
	{"ID" : "38", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U11", "Parent" : "32"},
	{"ID" : "39", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U12", "Parent" : "32"},
	{"ID" : "40", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U13", "Parent" : "32"},
	{"ID" : "41", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U23", "Parent" : "31"},
	{"ID" : "42", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U24", "Parent" : "31"},
	{"ID" : "43", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U25", "Parent" : "31"},
	{"ID" : "44", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U26", "Parent" : "31"},
	{"ID" : "45", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U27", "Parent" : "31"},
	{"ID" : "46", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U28", "Parent" : "31"},
	{"ID" : "47", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U29", "Parent" : "31"},
	{"ID" : "48", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U30", "Parent" : "31"},
	{"ID" : "49", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U31", "Parent" : "31"},
	{"ID" : "50", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U32", "Parent" : "31"},
	{"ID" : "51", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U33", "Parent" : "31"},
	{"ID" : "52", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U34", "Parent" : "31"},
	{"ID" : "53", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U35", "Parent" : "31"},
	{"ID" : "54", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U36", "Parent" : "31"},
	{"ID" : "55", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U37", "Parent" : "31"},
	{"ID" : "56", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U38", "Parent" : "31"},
	{"ID" : "57", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U39", "Parent" : "31"},
	{"ID" : "58", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U40", "Parent" : "31"},
	{"ID" : "59", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U41", "Parent" : "31"},
	{"ID" : "60", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U59", "Parent" : "30"},
	{"ID" : "61", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U60", "Parent" : "30"},
	{"ID" : "62", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U61", "Parent" : "30"},
	{"ID" : "63", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U62", "Parent" : "30"},
	{"ID" : "64", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U63", "Parent" : "30"},
	{"ID" : "65", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U64", "Parent" : "30"},
	{"ID" : "66", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U65", "Parent" : "30"},
	{"ID" : "67", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U66", "Parent" : "30"},
	{"ID" : "68", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U67", "Parent" : "30"},
	{"ID" : "69", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U68", "Parent" : "30"},
	{"ID" : "70", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U69", "Parent" : "30"},
	{"ID" : "71", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U70", "Parent" : "30"},
	{"ID" : "72", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U71", "Parent" : "30"},
	{"ID" : "73", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U72", "Parent" : "30"},
	{"ID" : "74", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U73", "Parent" : "30"},
	{"ID" : "75", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U74", "Parent" : "30"},
	{"ID" : "76", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U75", "Parent" : "30"},
	{"ID" : "77", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U76", "Parent" : "30"},
	{"ID" : "78", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U77", "Parent" : "30"},
	{"ID" : "79", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U78", "Parent" : "30"},
	{"ID" : "80", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U79", "Parent" : "30"},
	{"ID" : "81", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U80", "Parent" : "30"},
	{"ID" : "82", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U81", "Parent" : "30"},
	{"ID" : "83", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U82", "Parent" : "30"},
	{"ID" : "84", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U83", "Parent" : "30"},
	{"ID" : "85", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U84", "Parent" : "30"},
	{"ID" : "86", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U85", "Parent" : "30"},
	{"ID" : "87", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U86", "Parent" : "30"},
	{"ID" : "88", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U87", "Parent" : "30"},
	{"ID" : "89", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U88", "Parent" : "30"},
	{"ID" : "90", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U89", "Parent" : "30"},
	{"ID" : "91", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U90", "Parent" : "30"},
	{"ID" : "92", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U91", "Parent" : "30"},
	{"ID" : "93", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U92", "Parent" : "30"},
	{"ID" : "94", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U93", "Parent" : "30"},
	{"ID" : "95", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U94", "Parent" : "30"},
	{"ID" : "96", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U95", "Parent" : "30"},
	{"ID" : "97", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U96", "Parent" : "30"},
	{"ID" : "98", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U97", "Parent" : "30"},
	{"ID" : "99", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U98", "Parent" : "30"},
	{"ID" : "100", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U99", "Parent" : "30"},
	{"ID" : "101", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U100", "Parent" : "30"},
	{"ID" : "102", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U101", "Parent" : "30"},
	{"ID" : "103", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U102", "Parent" : "30"},
	{"ID" : "104", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U103", "Parent" : "30"},
	{"ID" : "105", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U104", "Parent" : "30"},
	{"ID" : "106", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U105", "Parent" : "30"},
	{"ID" : "107", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U106", "Parent" : "30"},
	{"ID" : "108", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U107", "Parent" : "30"},
	{"ID" : "109", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U108", "Parent" : "30"},
	{"ID" : "110", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U109", "Parent" : "30"},
	{"ID" : "111", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U110", "Parent" : "30"},
	{"ID" : "112", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U111", "Parent" : "30"},
	{"ID" : "113", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U112", "Parent" : "30"},
	{"ID" : "114", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U113", "Parent" : "30"},
	{"ID" : "115", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U114", "Parent" : "30"},
	{"ID" : "116", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U115", "Parent" : "30"},
	{"ID" : "117", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U116", "Parent" : "30"},
	{"ID" : "118", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U117", "Parent" : "30"},
	{"ID" : "119", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U118", "Parent" : "30"},
	{"ID" : "120", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U119", "Parent" : "30"},
	{"ID" : "121", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U120", "Parent" : "30"},
	{"ID" : "122", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U121", "Parent" : "30"},
	{"ID" : "123", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U122", "Parent" : "30"},
	{"ID" : "124", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U123", "Parent" : "30"},
	{"ID" : "125", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U124", "Parent" : "30"},
	{"ID" : "126", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U125", "Parent" : "30"},
	{"ID" : "127", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U126", "Parent" : "30"},
	{"ID" : "128", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_6s_32_1_1_U127", "Parent" : "30"},
	{"ID" : "129", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U128", "Parent" : "30"},
	{"ID" : "130", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U129", "Parent" : "30"},
	{"ID" : "131", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U130", "Parent" : "30"},
	{"ID" : "132", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U131", "Parent" : "30"},
	{"ID" : "133", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U132", "Parent" : "30"},
	{"ID" : "134", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U133", "Parent" : "30"},
	{"ID" : "135", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U134", "Parent" : "30"},
	{"ID" : "136", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U135", "Parent" : "30"},
	{"ID" : "137", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U136", "Parent" : "30"},
	{"ID" : "138", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U137", "Parent" : "30"},
	{"ID" : "139", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U138", "Parent" : "30"},
	{"ID" : "140", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U139", "Parent" : "30"},
	{"ID" : "141", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_7s_32_1_1_U140", "Parent" : "30"},
	{"ID" : "142", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U141", "Parent" : "30"},
	{"ID" : "143", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U142", "Parent" : "30"},
	{"ID" : "144", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_8s_32_1_1_U143", "Parent" : "30"},
	{"ID" : "145", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U144", "Parent" : "30"},
	{"ID" : "146", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U145", "Parent" : "30"},
	{"ID" : "147", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U146", "Parent" : "30"},
	{"ID" : "148", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U147", "Parent" : "30"},
	{"ID" : "149", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U148", "Parent" : "30"},
	{"ID" : "150", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U149", "Parent" : "30"},
	{"ID" : "151", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U150", "Parent" : "30"},
	{"ID" : "152", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B32_fu_280.mul_32s_5s_32_1_1_U151", "Parent" : "30"},
	{"ID" : "153", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316", "Parent" : "0", "Child" : ["154", "277", "278", "279", "280", "281", "282", "283", "284", "285", "286", "287", "288", "289", "290", "291", "292", "293", "294", "295", "296", "297", "298", "299", "300", "301", "302", "303", "304", "305", "306", "307", "308", "309", "310", "311", "312", "313", "314", "315", "316", "317", "318", "319", "320", "321", "322", "323", "324", "325", "326", "327", "328", "329", "330", "331", "332", "333", "334", "335", "336", "337", "338", "339", "340", "341", "342", "343", "344", "345", "346", "347", "348", "349", "350", "351", "352", "353", "354", "355", "356", "357", "358", "359", "360", "361", "362", "363", "364", "365", "366", "367", "368", "369", "370", "371", "372", "373", "374", "375", "376", "377", "378", "379", "380", "381", "382", "383", "384", "385", "386", "387", "388", "389", "390", "391"],
		"CDFG" : "IDCT2B64",
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
			{"Name" : "in_16_val", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "154", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260", "Parent" : "153", "Child" : ["155", "184", "185", "186", "187", "188", "189", "190", "191", "192", "193", "194", "195", "196", "197", "198", "199", "200", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210", "211", "212", "213", "214", "215", "216", "217", "218", "219", "220", "221", "222", "223", "224", "225", "226", "227", "228", "229", "230", "231", "232", "233", "234", "235", "236", "237", "238", "239", "240", "241", "242", "243", "244", "245", "246", "247", "248", "249", "250", "251", "252", "253", "254", "255", "256", "257", "258", "259", "260", "261", "262", "263", "264", "265", "266", "267", "268", "269", "270", "271", "272", "273", "274", "275", "276"],
		"CDFG" : "IDCT2B32",
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
	{"ID" : "155", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306", "Parent" : "154", "Child" : ["156", "165", "166", "167", "168", "169", "170", "171", "172", "173", "174", "175", "176", "177", "178", "179", "180", "181", "182", "183"],
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
	{"ID" : "156", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164", "Parent" : "155", "Child" : ["157", "160", "161", "162", "163", "164"],
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
	{"ID" : "157", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92", "Parent" : "156", "Child" : ["158", "159"],
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
	{"ID" : "158", "Level" : "6", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "157",
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
	{"ID" : "159", "Level" : "6", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.call_ret_IDCT2B4_fu_92.mul_32s_8s_32_1_1_U3", "Parent" : "157"},
	{"ID" : "160", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U9", "Parent" : "156"},
	{"ID" : "161", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U10", "Parent" : "156"},
	{"ID" : "162", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U11", "Parent" : "156"},
	{"ID" : "163", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_7s_32_1_1_U12", "Parent" : "156"},
	{"ID" : "164", "Level" : "5", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.call_ret_IDCT2B8_fu_164.mul_32s_8s_32_1_1_U13", "Parent" : "156"},
	{"ID" : "165", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U23", "Parent" : "155"},
	{"ID" : "166", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U24", "Parent" : "155"},
	{"ID" : "167", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U25", "Parent" : "155"},
	{"ID" : "168", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U26", "Parent" : "155"},
	{"ID" : "169", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U27", "Parent" : "155"},
	{"ID" : "170", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U28", "Parent" : "155"},
	{"ID" : "171", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U29", "Parent" : "155"},
	{"ID" : "172", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U30", "Parent" : "155"},
	{"ID" : "173", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U31", "Parent" : "155"},
	{"ID" : "174", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U32", "Parent" : "155"},
	{"ID" : "175", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U33", "Parent" : "155"},
	{"ID" : "176", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U34", "Parent" : "155"},
	{"ID" : "177", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U35", "Parent" : "155"},
	{"ID" : "178", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U36", "Parent" : "155"},
	{"ID" : "179", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U37", "Parent" : "155"},
	{"ID" : "180", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U38", "Parent" : "155"},
	{"ID" : "181", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_6s_32_1_1_U39", "Parent" : "155"},
	{"ID" : "182", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_7s_32_1_1_U40", "Parent" : "155"},
	{"ID" : "183", "Level" : "4", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.call_ret_IDCT2B16_fu_306.mul_32s_8s_32_1_1_U41", "Parent" : "155"},
	{"ID" : "184", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U59", "Parent" : "154"},
	{"ID" : "185", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U60", "Parent" : "154"},
	{"ID" : "186", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U61", "Parent" : "154"},
	{"ID" : "187", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U62", "Parent" : "154"},
	{"ID" : "188", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U63", "Parent" : "154"},
	{"ID" : "189", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U64", "Parent" : "154"},
	{"ID" : "190", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U65", "Parent" : "154"},
	{"ID" : "191", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U66", "Parent" : "154"},
	{"ID" : "192", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U67", "Parent" : "154"},
	{"ID" : "193", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U68", "Parent" : "154"},
	{"ID" : "194", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U69", "Parent" : "154"},
	{"ID" : "195", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U70", "Parent" : "154"},
	{"ID" : "196", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U71", "Parent" : "154"},
	{"ID" : "197", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U72", "Parent" : "154"},
	{"ID" : "198", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U73", "Parent" : "154"},
	{"ID" : "199", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U74", "Parent" : "154"},
	{"ID" : "200", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U75", "Parent" : "154"},
	{"ID" : "201", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U76", "Parent" : "154"},
	{"ID" : "202", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U77", "Parent" : "154"},
	{"ID" : "203", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U78", "Parent" : "154"},
	{"ID" : "204", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U79", "Parent" : "154"},
	{"ID" : "205", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U80", "Parent" : "154"},
	{"ID" : "206", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U81", "Parent" : "154"},
	{"ID" : "207", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U82", "Parent" : "154"},
	{"ID" : "208", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U83", "Parent" : "154"},
	{"ID" : "209", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U84", "Parent" : "154"},
	{"ID" : "210", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U85", "Parent" : "154"},
	{"ID" : "211", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U86", "Parent" : "154"},
	{"ID" : "212", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U87", "Parent" : "154"},
	{"ID" : "213", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U88", "Parent" : "154"},
	{"ID" : "214", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U89", "Parent" : "154"},
	{"ID" : "215", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U90", "Parent" : "154"},
	{"ID" : "216", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U91", "Parent" : "154"},
	{"ID" : "217", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U92", "Parent" : "154"},
	{"ID" : "218", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U93", "Parent" : "154"},
	{"ID" : "219", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U94", "Parent" : "154"},
	{"ID" : "220", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U95", "Parent" : "154"},
	{"ID" : "221", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U96", "Parent" : "154"},
	{"ID" : "222", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U97", "Parent" : "154"},
	{"ID" : "223", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U98", "Parent" : "154"},
	{"ID" : "224", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U99", "Parent" : "154"},
	{"ID" : "225", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U100", "Parent" : "154"},
	{"ID" : "226", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U101", "Parent" : "154"},
	{"ID" : "227", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U102", "Parent" : "154"},
	{"ID" : "228", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U103", "Parent" : "154"},
	{"ID" : "229", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U104", "Parent" : "154"},
	{"ID" : "230", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U105", "Parent" : "154"},
	{"ID" : "231", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U106", "Parent" : "154"},
	{"ID" : "232", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U107", "Parent" : "154"},
	{"ID" : "233", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U108", "Parent" : "154"},
	{"ID" : "234", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U109", "Parent" : "154"},
	{"ID" : "235", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U110", "Parent" : "154"},
	{"ID" : "236", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U111", "Parent" : "154"},
	{"ID" : "237", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U112", "Parent" : "154"},
	{"ID" : "238", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U113", "Parent" : "154"},
	{"ID" : "239", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U114", "Parent" : "154"},
	{"ID" : "240", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U115", "Parent" : "154"},
	{"ID" : "241", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U116", "Parent" : "154"},
	{"ID" : "242", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U117", "Parent" : "154"},
	{"ID" : "243", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U118", "Parent" : "154"},
	{"ID" : "244", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U119", "Parent" : "154"},
	{"ID" : "245", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U120", "Parent" : "154"},
	{"ID" : "246", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U121", "Parent" : "154"},
	{"ID" : "247", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U122", "Parent" : "154"},
	{"ID" : "248", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U123", "Parent" : "154"},
	{"ID" : "249", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U124", "Parent" : "154"},
	{"ID" : "250", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U125", "Parent" : "154"},
	{"ID" : "251", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U126", "Parent" : "154"},
	{"ID" : "252", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_6s_32_1_1_U127", "Parent" : "154"},
	{"ID" : "253", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U128", "Parent" : "154"},
	{"ID" : "254", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U129", "Parent" : "154"},
	{"ID" : "255", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U130", "Parent" : "154"},
	{"ID" : "256", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U131", "Parent" : "154"},
	{"ID" : "257", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U132", "Parent" : "154"},
	{"ID" : "258", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U133", "Parent" : "154"},
	{"ID" : "259", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U134", "Parent" : "154"},
	{"ID" : "260", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U135", "Parent" : "154"},
	{"ID" : "261", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U136", "Parent" : "154"},
	{"ID" : "262", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U137", "Parent" : "154"},
	{"ID" : "263", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U138", "Parent" : "154"},
	{"ID" : "264", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U139", "Parent" : "154"},
	{"ID" : "265", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_7s_32_1_1_U140", "Parent" : "154"},
	{"ID" : "266", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U141", "Parent" : "154"},
	{"ID" : "267", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U142", "Parent" : "154"},
	{"ID" : "268", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_8s_32_1_1_U143", "Parent" : "154"},
	{"ID" : "269", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U144", "Parent" : "154"},
	{"ID" : "270", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U145", "Parent" : "154"},
	{"ID" : "271", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U146", "Parent" : "154"},
	{"ID" : "272", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U147", "Parent" : "154"},
	{"ID" : "273", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U148", "Parent" : "154"},
	{"ID" : "274", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U149", "Parent" : "154"},
	{"ID" : "275", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U150", "Parent" : "154"},
	{"ID" : "276", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.grp_IDCT2B32_fu_260.mul_32s_5s_32_1_1_U151", "Parent" : "154"},
	{"ID" : "277", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U185", "Parent" : "153"},
	{"ID" : "278", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U186", "Parent" : "153"},
	{"ID" : "279", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U187", "Parent" : "153"},
	{"ID" : "280", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U188", "Parent" : "153"},
	{"ID" : "281", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U189", "Parent" : "153"},
	{"ID" : "282", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U190", "Parent" : "153"},
	{"ID" : "283", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U191", "Parent" : "153"},
	{"ID" : "284", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U192", "Parent" : "153"},
	{"ID" : "285", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U193", "Parent" : "153"},
	{"ID" : "286", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U194", "Parent" : "153"},
	{"ID" : "287", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_12s_32_1_1_U195", "Parent" : "153"},
	{"ID" : "288", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U196", "Parent" : "153"},
	{"ID" : "289", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U197", "Parent" : "153"},
	{"ID" : "290", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U198", "Parent" : "153"},
	{"ID" : "291", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U199", "Parent" : "153"},
	{"ID" : "292", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U200", "Parent" : "153"},
	{"ID" : "293", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U201", "Parent" : "153"},
	{"ID" : "294", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U202", "Parent" : "153"},
	{"ID" : "295", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U203", "Parent" : "153"},
	{"ID" : "296", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U204", "Parent" : "153"},
	{"ID" : "297", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U205", "Parent" : "153"},
	{"ID" : "298", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U206", "Parent" : "153"},
	{"ID" : "299", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U207", "Parent" : "153"},
	{"ID" : "300", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U208", "Parent" : "153"},
	{"ID" : "301", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U209", "Parent" : "153"},
	{"ID" : "302", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U210", "Parent" : "153"},
	{"ID" : "303", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U211", "Parent" : "153"},
	{"ID" : "304", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U212", "Parent" : "153"},
	{"ID" : "305", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U213", "Parent" : "153"},
	{"ID" : "306", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U214", "Parent" : "153"},
	{"ID" : "307", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U215", "Parent" : "153"},
	{"ID" : "308", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U216", "Parent" : "153"},
	{"ID" : "309", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U217", "Parent" : "153"},
	{"ID" : "310", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_6s_32_1_1_U218", "Parent" : "153"},
	{"ID" : "311", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U219", "Parent" : "153"},
	{"ID" : "312", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U220", "Parent" : "153"},
	{"ID" : "313", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U221", "Parent" : "153"},
	{"ID" : "314", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U222", "Parent" : "153"},
	{"ID" : "315", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U223", "Parent" : "153"},
	{"ID" : "316", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U224", "Parent" : "153"},
	{"ID" : "317", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U225", "Parent" : "153"},
	{"ID" : "318", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_6s_32_1_1_U226", "Parent" : "153"},
	{"ID" : "319", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U227", "Parent" : "153"},
	{"ID" : "320", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U228", "Parent" : "153"},
	{"ID" : "321", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U229", "Parent" : "153"},
	{"ID" : "322", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U230", "Parent" : "153"},
	{"ID" : "323", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U231", "Parent" : "153"},
	{"ID" : "324", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U232", "Parent" : "153"},
	{"ID" : "325", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U233", "Parent" : "153"},
	{"ID" : "326", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U234", "Parent" : "153"},
	{"ID" : "327", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U235", "Parent" : "153"},
	{"ID" : "328", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U236", "Parent" : "153"},
	{"ID" : "329", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U237", "Parent" : "153"},
	{"ID" : "330", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U238", "Parent" : "153"},
	{"ID" : "331", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U239", "Parent" : "153"},
	{"ID" : "332", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U240", "Parent" : "153"},
	{"ID" : "333", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U241", "Parent" : "153"},
	{"ID" : "334", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U242", "Parent" : "153"},
	{"ID" : "335", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U243", "Parent" : "153"},
	{"ID" : "336", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U244", "Parent" : "153"},
	{"ID" : "337", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U245", "Parent" : "153"},
	{"ID" : "338", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U246", "Parent" : "153"},
	{"ID" : "339", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U247", "Parent" : "153"},
	{"ID" : "340", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U248", "Parent" : "153"},
	{"ID" : "341", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U249", "Parent" : "153"},
	{"ID" : "342", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U250", "Parent" : "153"},
	{"ID" : "343", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U251", "Parent" : "153"},
	{"ID" : "344", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U252", "Parent" : "153"},
	{"ID" : "345", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U253", "Parent" : "153"},
	{"ID" : "346", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U254", "Parent" : "153"},
	{"ID" : "347", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U255", "Parent" : "153"},
	{"ID" : "348", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U256", "Parent" : "153"},
	{"ID" : "349", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U257", "Parent" : "153"},
	{"ID" : "350", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U258", "Parent" : "153"},
	{"ID" : "351", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U259", "Parent" : "153"},
	{"ID" : "352", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U260", "Parent" : "153"},
	{"ID" : "353", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U261", "Parent" : "153"},
	{"ID" : "354", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U262", "Parent" : "153"},
	{"ID" : "355", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U263", "Parent" : "153"},
	{"ID" : "356", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U264", "Parent" : "153"},
	{"ID" : "357", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U265", "Parent" : "153"},
	{"ID" : "358", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U266", "Parent" : "153"},
	{"ID" : "359", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U267", "Parent" : "153"},
	{"ID" : "360", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U268", "Parent" : "153"},
	{"ID" : "361", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U269", "Parent" : "153"},
	{"ID" : "362", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U270", "Parent" : "153"},
	{"ID" : "363", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U271", "Parent" : "153"},
	{"ID" : "364", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U272", "Parent" : "153"},
	{"ID" : "365", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U273", "Parent" : "153"},
	{"ID" : "366", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U274", "Parent" : "153"},
	{"ID" : "367", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_6s_32_1_1_U275", "Parent" : "153"},
	{"ID" : "368", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U276", "Parent" : "153"},
	{"ID" : "369", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U277", "Parent" : "153"},
	{"ID" : "370", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_9s_32_1_1_U278", "Parent" : "153"},
	{"ID" : "371", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U279", "Parent" : "153"},
	{"ID" : "372", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U280", "Parent" : "153"},
	{"ID" : "373", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U281", "Parent" : "153"},
	{"ID" : "374", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U282", "Parent" : "153"},
	{"ID" : "375", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U283", "Parent" : "153"},
	{"ID" : "376", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U284", "Parent" : "153"},
	{"ID" : "377", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U285", "Parent" : "153"},
	{"ID" : "378", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U286", "Parent" : "153"},
	{"ID" : "379", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U287", "Parent" : "153"},
	{"ID" : "380", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U288", "Parent" : "153"},
	{"ID" : "381", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U289", "Parent" : "153"},
	{"ID" : "382", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U290", "Parent" : "153"},
	{"ID" : "383", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U291", "Parent" : "153"},
	{"ID" : "384", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U292", "Parent" : "153"},
	{"ID" : "385", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_7s_32_1_1_U293", "Parent" : "153"},
	{"ID" : "386", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_8s_32_1_1_U294", "Parent" : "153"},
	{"ID" : "387", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_5s_32_1_1_U295", "Parent" : "153"},
	{"ID" : "388", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_5s_32_1_1_U296", "Parent" : "153"},
	{"ID" : "389", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_5s_32_1_1_U297", "Parent" : "153"},
	{"ID" : "390", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_5s_32_1_1_U298", "Parent" : "153"},
	{"ID" : "391", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT2B64_fu_316.mul_32s_5s_32_1_1_U299", "Parent" : "153"},
	{"ID" : "392", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.call_ret5_IDCT2B4_fu_337", "Parent" : "0", "Child" : ["393", "394"],
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
	{"ID" : "393", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret5_IDCT2B4_fu_337.call_ret_IDCT2B2_fu_50", "Parent" : "392",
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
	{"ID" : "394", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret5_IDCT2B4_fu_337.mul_32s_8s_32_1_1_U3", "Parent" : "392"},
	{"ID" : "395", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345", "Parent" : "0", "Child" : ["396", "399", "400", "401", "402", "403"],
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
	{"ID" : "396", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.call_ret_IDCT2B4_fu_92", "Parent" : "395", "Child" : ["397", "398"],
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
	{"ID" : "397", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.call_ret_IDCT2B4_fu_92.call_ret_IDCT2B2_fu_50", "Parent" : "396",
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
	{"ID" : "398", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.call_ret_IDCT2B4_fu_92.mul_32s_8s_32_1_1_U3", "Parent" : "396"},
	{"ID" : "399", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.mul_32s_8s_32_1_1_U9", "Parent" : "395"},
	{"ID" : "400", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.mul_32s_7s_32_1_1_U10", "Parent" : "395"},
	{"ID" : "401", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.mul_32s_8s_32_1_1_U11", "Parent" : "395"},
	{"ID" : "402", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.mul_32s_7s_32_1_1_U12", "Parent" : "395"},
	{"ID" : "403", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.call_ret_IDCT2B8_fu_345.mul_32s_8s_32_1_1_U13", "Parent" : "395"},
	{"ID" : "404", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.call_ret1_IDCT2B2_fu_357", "Parent" : "0",
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
	{"ID" : "405", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "406", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem0_m_axi_U", "Parent" : "0"},
	{"ID" : "407", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem1_m_axi_U", "Parent" : "0"},
	{"ID" : "408", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	IDCT2 {
		gmem0 {Type I LastRead 72 FirstWrite -1}
		gmem1 {Type O LastRead 76 FirstWrite 75}
		in_r {Type I LastRead 0 FirstWrite -1}
		out_r {Type I LastRead 0 FirstWrite -1}
		block_size {Type I LastRead 0 FirstWrite -1}
		size {Type I LastRead 0 FirstWrite -1}}
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
		in_1_val {Type I LastRead 0 FirstWrite -1}}
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
		in_1_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B64 {
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
		in_16_val {Type I LastRead 0 FirstWrite -1}}
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
		in_1_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B4 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}
		in_2_val {Type I LastRead 0 FirstWrite -1}
		in_3_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B2 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}}
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
		in_1_val {Type I LastRead 0 FirstWrite -1}}
	IDCT2B2 {
		in_0_val {Type I LastRead 0 FirstWrite -1}
		in_1_val {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "145", "Max" : "1168"}
	, {"Name" : "Interval", "Min" : "146", "Max" : "1169"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	gmem0 { m_axi {  { m_axi_gmem0_AWVALID VALID 1 1 }  { m_axi_gmem0_AWREADY READY 0 1 }  { m_axi_gmem0_AWADDR ADDR 1 64 }  { m_axi_gmem0_AWID ID 1 1 }  { m_axi_gmem0_AWLEN SIZE 1 8 }  { m_axi_gmem0_AWSIZE BURST 1 3 }  { m_axi_gmem0_AWBURST LOCK 1 2 }  { m_axi_gmem0_AWLOCK CACHE 1 2 }  { m_axi_gmem0_AWCACHE PROT 1 4 }  { m_axi_gmem0_AWPROT QOS 1 3 }  { m_axi_gmem0_AWQOS REGION 1 4 }  { m_axi_gmem0_AWREGION USER 1 4 }  { m_axi_gmem0_AWUSER DATA 1 1 }  { m_axi_gmem0_WVALID VALID 1 1 }  { m_axi_gmem0_WREADY READY 0 1 }  { m_axi_gmem0_WDATA FIFONUM 1 512 }  { m_axi_gmem0_WSTRB STRB 1 64 }  { m_axi_gmem0_WLAST LAST 1 1 }  { m_axi_gmem0_WID ID 1 1 }  { m_axi_gmem0_WUSER DATA 1 1 }  { m_axi_gmem0_ARVALID VALID 1 1 }  { m_axi_gmem0_ARREADY READY 0 1 }  { m_axi_gmem0_ARADDR ADDR 1 64 }  { m_axi_gmem0_ARID ID 1 1 }  { m_axi_gmem0_ARLEN SIZE 1 8 }  { m_axi_gmem0_ARSIZE BURST 1 3 }  { m_axi_gmem0_ARBURST LOCK 1 2 }  { m_axi_gmem0_ARLOCK CACHE 1 2 }  { m_axi_gmem0_ARCACHE PROT 1 4 }  { m_axi_gmem0_ARPROT QOS 1 3 }  { m_axi_gmem0_ARQOS REGION 1 4 }  { m_axi_gmem0_ARREGION USER 1 4 }  { m_axi_gmem0_ARUSER DATA 1 1 }  { m_axi_gmem0_RVALID VALID 0 1 }  { m_axi_gmem0_RREADY READY 1 1 }  { m_axi_gmem0_RDATA FIFONUM 0 512 }  { m_axi_gmem0_RLAST LAST 0 1 }  { m_axi_gmem0_RID ID 0 1 }  { m_axi_gmem0_RUSER DATA 0 1 }  { m_axi_gmem0_RRESP RESP 0 2 }  { m_axi_gmem0_BVALID VALID 0 1 }  { m_axi_gmem0_BREADY READY 1 1 }  { m_axi_gmem0_BRESP RESP 0 2 }  { m_axi_gmem0_BID ID 0 1 }  { m_axi_gmem0_BUSER DATA 0 1 } } }
	gmem1 { m_axi {  { m_axi_gmem1_AWVALID VALID 1 1 }  { m_axi_gmem1_AWREADY READY 0 1 }  { m_axi_gmem1_AWADDR ADDR 1 64 }  { m_axi_gmem1_AWID ID 1 1 }  { m_axi_gmem1_AWLEN SIZE 1 8 }  { m_axi_gmem1_AWSIZE BURST 1 3 }  { m_axi_gmem1_AWBURST LOCK 1 2 }  { m_axi_gmem1_AWLOCK CACHE 1 2 }  { m_axi_gmem1_AWCACHE PROT 1 4 }  { m_axi_gmem1_AWPROT QOS 1 3 }  { m_axi_gmem1_AWQOS REGION 1 4 }  { m_axi_gmem1_AWREGION USER 1 4 }  { m_axi_gmem1_AWUSER DATA 1 1 }  { m_axi_gmem1_WVALID VALID 1 1 }  { m_axi_gmem1_WREADY READY 0 1 }  { m_axi_gmem1_WDATA FIFONUM 1 512 }  { m_axi_gmem1_WSTRB STRB 1 64 }  { m_axi_gmem1_WLAST LAST 1 1 }  { m_axi_gmem1_WID ID 1 1 }  { m_axi_gmem1_WUSER DATA 1 1 }  { m_axi_gmem1_ARVALID VALID 1 1 }  { m_axi_gmem1_ARREADY READY 0 1 }  { m_axi_gmem1_ARADDR ADDR 1 64 }  { m_axi_gmem1_ARID ID 1 1 }  { m_axi_gmem1_ARLEN SIZE 1 8 }  { m_axi_gmem1_ARSIZE BURST 1 3 }  { m_axi_gmem1_ARBURST LOCK 1 2 }  { m_axi_gmem1_ARLOCK CACHE 1 2 }  { m_axi_gmem1_ARCACHE PROT 1 4 }  { m_axi_gmem1_ARPROT QOS 1 3 }  { m_axi_gmem1_ARQOS REGION 1 4 }  { m_axi_gmem1_ARREGION USER 1 4 }  { m_axi_gmem1_ARUSER DATA 1 1 }  { m_axi_gmem1_RVALID VALID 0 1 }  { m_axi_gmem1_RREADY READY 1 1 }  { m_axi_gmem1_RDATA FIFONUM 0 512 }  { m_axi_gmem1_RLAST LAST 0 1 }  { m_axi_gmem1_RID ID 0 1 }  { m_axi_gmem1_RUSER DATA 0 1 }  { m_axi_gmem1_RRESP RESP 0 2 }  { m_axi_gmem1_BVALID VALID 0 1 }  { m_axi_gmem1_BREADY READY 1 1 }  { m_axi_gmem1_BRESP RESP 0 2 }  { m_axi_gmem1_BID ID 0 1 }  { m_axi_gmem1_BUSER DATA 0 1 } } }
}

set maxi_interface_dict [dict create]
dict set maxi_interface_dict gmem0 { CHANNEL_NUM 0 BUNDLE gmem0 NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE READ_ONLY}
dict set maxi_interface_dict gmem1 { CHANNEL_NUM 0 BUNDLE gmem1 NUM_READ_OUTSTANDING 16 NUM_WRITE_OUTSTANDING 16 MAX_READ_BURST_LENGTH 16 MAX_WRITE_BURST_LENGTH 16 READ_WRITE_MODE WRITE_ONLY}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
	{ gmem0 64 }
	{ gmem1 64 }
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
	{ gmem0 64 }
	{ gmem1 64 }
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
