set moduleName IDCT8
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_chain
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 9
set C_modelName {IDCT8}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ gmem0 int 1024 regular {axi_master 0}  }
	{ gmem1 int 1024 regular {axi_master 1}  }
	{ in_r int 64 regular {axi_slave 0}  }
	{ out_r int 64 regular {axi_slave 0}  }
	{ block_size int 32 regular {axi_slave 0}  }
	{ sIn int 32 regular {axi_slave 0}  }
	{ size int 32 regular {axi_slave 0}  }
	{ shift int 32 regular {axi_slave 0}  }
	{ oMin int 32 regular {axi_slave 0}  }
	{ oMax int 32 regular {axi_slave 0}  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "gmem0", "interface" : "axi_master", "bitwidth" : 1024, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "in_r","offset": { "type": "dynamic","port_name": "in_r","bundle": "control"},"direction": "READONLY"}]}]} , 
 	{ "Name" : "gmem1", "interface" : "axi_master", "bitwidth" : 1024, "direction" : "WRITEONLY", "bitSlice":[ {"cElement": [{"cName": "out_r","offset": { "type": "dynamic","port_name": "out_r","bundle": "control"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "in_r", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":16}, "offset_end" : {"in":27}} , 
 	{ "Name" : "out_r", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 64, "direction" : "READONLY", "offset" : {"in":28}, "offset_end" : {"in":39}} , 
 	{ "Name" : "block_size", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":40}, "offset_end" : {"in":47}} , 
 	{ "Name" : "sIn", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":48}, "offset_end" : {"in":55}} , 
 	{ "Name" : "size", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":56}, "offset_end" : {"in":63}} , 
 	{ "Name" : "shift", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":64}, "offset_end" : {"in":71}} , 
 	{ "Name" : "oMin", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":72}, "offset_end" : {"in":79}} , 
 	{ "Name" : "oMax", "interface" : "axi_slave", "bundle":"control","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":80}, "offset_end" : {"in":87}} ]}
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
	{ m_axi_gmem0_WDATA sc_out sc_lv 1024 signal 0 } 
	{ m_axi_gmem0_WSTRB sc_out sc_lv 128 signal 0 } 
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
	{ m_axi_gmem0_RDATA sc_in sc_lv 1024 signal 0 } 
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
	{ m_axi_gmem1_WDATA sc_out sc_lv 1024 signal 1 } 
	{ m_axi_gmem1_WSTRB sc_out sc_lv 128 signal 1 } 
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
	{ m_axi_gmem1_RDATA sc_in sc_lv 1024 signal 1 } 
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
	{ s_axi_control_AWADDR sc_in sc_lv 7 signal -1 } 
	{ s_axi_control_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_control_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_control_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_control_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_control_ARADDR sc_in sc_lv 7 signal -1 } 
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
	{ "name": "s_axi_control_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "control", "role": "AWADDR" },"address":[{"name":"IDCT8","role":"start","value":"0","valid_bit":"0"},{"name":"IDCT8","role":"continue","value":"0","valid_bit":"4"},{"name":"IDCT8","role":"auto_start","value":"0","valid_bit":"7"},{"name":"in_r","role":"data","value":"16"},{"name":"out_r","role":"data","value":"28"},{"name":"block_size","role":"data","value":"40"},{"name":"sIn","role":"data","value":"48"},{"name":"size","role":"data","value":"56"},{"name":"shift","role":"data","value":"64"},{"name":"oMin","role":"data","value":"72"},{"name":"oMax","role":"data","value":"80"}] },
	{ "name": "s_axi_control_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWVALID" } },
	{ "name": "s_axi_control_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "AWREADY" } },
	{ "name": "s_axi_control_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WVALID" } },
	{ "name": "s_axi_control_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "control", "role": "WREADY" } },
	{ "name": "s_axi_control_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "control", "role": "WDATA" } },
	{ "name": "s_axi_control_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "control", "role": "WSTRB" } },
	{ "name": "s_axi_control_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":7, "type": "signal", "bundle":{"name": "control", "role": "ARADDR" },"address":[{"name":"IDCT8","role":"start","value":"0","valid_bit":"0"},{"name":"IDCT8","role":"done","value":"0","valid_bit":"1"},{"name":"IDCT8","role":"idle","value":"0","valid_bit":"2"},{"name":"IDCT8","role":"ready","value":"0","valid_bit":"3"},{"name":"IDCT8","role":"auto_start","value":"0","valid_bit":"7"}] },
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
 	{ "name": "m_axi_gmem0_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":1024, "type": "signal", "bundle":{"name": "gmem0", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem0_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":128, "type": "signal", "bundle":{"name": "gmem0", "role": "WSTRB" }} , 
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
 	{ "name": "m_axi_gmem0_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":1024, "type": "signal", "bundle":{"name": "gmem0", "role": "RDATA" }} , 
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
 	{ "name": "m_axi_gmem1_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":1024, "type": "signal", "bundle":{"name": "gmem1", "role": "WDATA" }} , 
 	{ "name": "m_axi_gmem1_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":128, "type": "signal", "bundle":{"name": "gmem1", "role": "WSTRB" }} , 
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
 	{ "name": "m_axi_gmem1_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":1024, "type": "signal", "bundle":{"name": "gmem1", "role": "RDATA" }} , 
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
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "20", "55", "122", "123", "124", "125"],
		"CDFG" : "IDCT8",
		"Protocol" : "ap_ctrl_chain",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "151", "EstimateLatencyMax" : "67732",
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
			{"Name" : "sIn", "Type" : "None", "Direction" : "I"},
			{"Name" : "size", "Type" : "None", "Direction" : "I"},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_0", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_1", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_2", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_3", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_4", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_5", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_6", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_7", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_8", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_8", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_9", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_9", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_10", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_10", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_11", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_11", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_12", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_13", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_13", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_14", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_14", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_15", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_15", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_16", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_16", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_17", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_17", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_18", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_18", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_19", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_19", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_20", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_20", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_21", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_21", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_22", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_22", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_23", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_23", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_24", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_24", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_25", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_25", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_26", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_26", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_27", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_27", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_28", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_28", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_29", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_29", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_30", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_30", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_32_31", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "55", "SubInstance" : "grp_IDCT8B32_fu_792", "Port" : "p_ZL8idct8_32_31", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_0", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_1", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_2", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_3", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_4", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_5", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_6", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_7", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_8", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_8", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_9", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_9", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_10", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_10", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_11", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_11", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_12", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_13", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_13", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_14", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_14", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL8idct8_16_15", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "20", "SubInstance" : "grp_IDCT8B16_fu_720", "Port" : "p_ZL8idct8_16_15", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_0", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_1", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_2", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_3", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_4", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_5", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_6", "Inst_start_state" : "81", "Inst_end_state" : "82"}]},
			{"Name" : "p_ZL7idct8_8_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "grp_IDCT8B8_fu_680", "Port" : "p_ZL7idct8_8_7", "Inst_start_state" : "81", "Inst_end_state" : "82"}]}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_260_1", "PipelineType" : "no",
				"LoopDec" : {"FSMBitwidth" : "157", "FirstState" : "ap_ST_fsm_state76", "LastState" : ["ap_ST_fsm_state84"], "QuitState" : ["ap_ST_fsm_state76"], "PreState" : ["ap_ST_fsm_state75"], "PostState" : ["ap_ST_fsm_state85"], "OneDepthLoop" : "0", "OneStateBlock": ""}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680", "Parent" : "0", "Child" : ["2"],
		"CDFG" : "IDCT8B8",
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
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "dst_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "skipLine2", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL7idct8_8_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "2", "SubInstance" : "grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Port" : "p_ZL7idct8_8_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]}]},
	{"ID" : "2", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158", "Parent" : "1", "Child" : ["3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19"],
		"CDFG" : "IDCT8B8_Pipeline_VITIS_LOOP_21_1",
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
			{"Name" : "p_ZL7idct8_8_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL7idct8_8_7", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_21_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter9", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter9", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "3", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_0_U", "Parent" : "2"},
	{"ID" : "4", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_1_U", "Parent" : "2"},
	{"ID" : "5", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_2_U", "Parent" : "2"},
	{"ID" : "6", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_3_U", "Parent" : "2"},
	{"ID" : "7", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_4_U", "Parent" : "2"},
	{"ID" : "8", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_5_U", "Parent" : "2"},
	{"ID" : "9", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_6_U", "Parent" : "2"},
	{"ID" : "10", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.p_ZL7idct8_8_7_U", "Parent" : "2"},
	{"ID" : "11", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_7ns_32s_32_2_1_U1", "Parent" : "2"},
	{"ID" : "12", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U2", "Parent" : "2"},
	{"ID" : "13", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U3", "Parent" : "2"},
	{"ID" : "14", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U4", "Parent" : "2"},
	{"ID" : "15", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U5", "Parent" : "2"},
	{"ID" : "16", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U6", "Parent" : "2"},
	{"ID" : "17", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U7", "Parent" : "2"},
	{"ID" : "18", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.mul_8s_32s_32_2_1_U8", "Parent" : "2"},
	{"ID" : "19", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B8_fu_680.grp_IDCT8B8_Pipeline_VITIS_LOOP_21_1_fu_158.flow_control_loop_pipe_sequential_init_U", "Parent" : "2"},
	{"ID" : "20", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720", "Parent" : "0", "Child" : ["21"],
		"CDFG" : "IDCT8B16",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "33", "EstimateLatencyMax" : "33",
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
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_8", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_8", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_9", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_9", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_10", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_10", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_11", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_11", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_12", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_12", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_13", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_13", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_14", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_14", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_15", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "dst_15", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "skipLine2", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_8", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_8", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_9", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_9", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_10", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_10", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_11", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_11", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_12", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_13", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_13", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_14", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_14", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_16_15", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "21", "SubInstance" : "grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Port" : "p_ZL8idct8_16_15", "Inst_start_state" : "2", "Inst_end_state" : "3"}]}]},
	{"ID" : "21", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258", "Parent" : "20", "Child" : ["22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43", "44", "45", "46", "47", "48", "49", "50", "51", "52", "53", "54"],
		"CDFG" : "IDCT8B16_Pipeline_VITIS_LOOP_47_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "31", "EstimateLatencyMax" : "31",
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
			{"Name" : "empty_41", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_42", "Type" : "None", "Direction" : "I"},
			{"Name" : "cutoff", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_43", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty_44", "Type" : "None", "Direction" : "I"},
			{"Name" : "empty", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_8", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_9", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_10", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_11", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_12", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_13", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_14", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_16_15", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_47_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter14", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter14", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "22", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_0_U", "Parent" : "21"},
	{"ID" : "23", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_1_U", "Parent" : "21"},
	{"ID" : "24", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_2_U", "Parent" : "21"},
	{"ID" : "25", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_3_U", "Parent" : "21"},
	{"ID" : "26", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_4_U", "Parent" : "21"},
	{"ID" : "27", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_5_U", "Parent" : "21"},
	{"ID" : "28", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_6_U", "Parent" : "21"},
	{"ID" : "29", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_7_U", "Parent" : "21"},
	{"ID" : "30", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_8_U", "Parent" : "21"},
	{"ID" : "31", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_9_U", "Parent" : "21"},
	{"ID" : "32", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_10_U", "Parent" : "21"},
	{"ID" : "33", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_11_U", "Parent" : "21"},
	{"ID" : "34", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_12_U", "Parent" : "21"},
	{"ID" : "35", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_13_U", "Parent" : "21"},
	{"ID" : "36", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_14_U", "Parent" : "21"},
	{"ID" : "37", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.p_ZL8idct8_16_15_U", "Parent" : "21"},
	{"ID" : "38", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_7ns_32s_32_2_1_U65", "Parent" : "21"},
	{"ID" : "39", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U66", "Parent" : "21"},
	{"ID" : "40", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U67", "Parent" : "21"},
	{"ID" : "41", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U68", "Parent" : "21"},
	{"ID" : "42", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U69", "Parent" : "21"},
	{"ID" : "43", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U70", "Parent" : "21"},
	{"ID" : "44", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U71", "Parent" : "21"},
	{"ID" : "45", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U72", "Parent" : "21"},
	{"ID" : "46", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U73", "Parent" : "21"},
	{"ID" : "47", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U74", "Parent" : "21"},
	{"ID" : "48", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U75", "Parent" : "21"},
	{"ID" : "49", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U76", "Parent" : "21"},
	{"ID" : "50", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U77", "Parent" : "21"},
	{"ID" : "51", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U78", "Parent" : "21"},
	{"ID" : "52", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U79", "Parent" : "21"},
	{"ID" : "53", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.mul_8s_32s_32_2_1_U80", "Parent" : "21"},
	{"ID" : "54", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B16_fu_720.grp_IDCT8B16_Pipeline_VITIS_LOOP_47_1_fu_258.flow_control_loop_pipe_sequential_init_U", "Parent" : "21"},
	{"ID" : "55", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792", "Parent" : "0", "Child" : ["56"],
		"CDFG" : "IDCT8B32",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "60", "EstimateLatencyMax" : "60",
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
			{"Name" : "dst_0", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_1", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_2", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_3", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_4", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_5", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_6", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_7", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_8", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_8", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_9", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_9", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_10", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_10", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_11", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_11", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_12", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_12", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_13", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_13", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_14", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_14", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_15", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_15", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_16", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_16", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_17", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_17", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_18", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_18", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_19", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_19", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_20", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_20", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_21", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_21", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_22", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_22", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_23", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_23", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_24", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_24", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_25", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_25", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_26", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_26", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_27", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_27", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_28", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_28", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_29", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_29", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_30", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_30", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "dst_31", "Type" : "Vld", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "dst_31", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "shift", "Type" : "None", "Direction" : "I"},
			{"Name" : "skipLine2", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMin", "Type" : "None", "Direction" : "I"},
			{"Name" : "oMax", "Type" : "None", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_0", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_0", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_1", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_1", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_2", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_2", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_3", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_3", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_4", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_4", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_5", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_5", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_6", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_6", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_7", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_7", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_8", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_8", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_9", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_9", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_10", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_10", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_11", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_11", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_12", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_12", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_13", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_13", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_14", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_14", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_15", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_15", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_16", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_16", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_17", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_17", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_18", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_18", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_19", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_19", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_20", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_20", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_21", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_21", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_22", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_22", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_23", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_23", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_24", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_24", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_25", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_25", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_26", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_26", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_27", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_27", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_28", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_28", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_29", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_29", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_30", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_30", "Inst_start_state" : "2", "Inst_end_state" : "3"}]},
			{"Name" : "p_ZL8idct8_32_31", "Type" : "Memory", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "56", "SubInstance" : "grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Port" : "p_ZL8idct8_32_31", "Inst_start_state" : "2", "Inst_end_state" : "3"}]}]},
	{"ID" : "56", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452", "Parent" : "55", "Child" : ["57", "58", "59", "60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "70", "71", "72", "73", "74", "75", "76", "77", "78", "79", "80", "81", "82", "83", "84", "85", "86", "87", "88", "89", "90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "100", "101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "111", "112", "113", "114", "115", "116", "117", "118", "119", "120", "121"],
		"CDFG" : "IDCT8B32_Pipeline_VITIS_LOOP_73_1",
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
			{"Name" : "p_ZL8idct8_32_0", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_1", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_2", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_3", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_8", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_9", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_10", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_11", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_12", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_13", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_14", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_15", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_16", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_17", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_18", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_19", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_20", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_21", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_22", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_23", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_24", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_25", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_26", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_27", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_28", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_29", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_30", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "p_ZL8idct8_32_31", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_73_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter25", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter25", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "57", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_0_U", "Parent" : "56"},
	{"ID" : "58", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_1_U", "Parent" : "56"},
	{"ID" : "59", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_2_U", "Parent" : "56"},
	{"ID" : "60", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_3_U", "Parent" : "56"},
	{"ID" : "61", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_4_U", "Parent" : "56"},
	{"ID" : "62", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_5_U", "Parent" : "56"},
	{"ID" : "63", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_6_U", "Parent" : "56"},
	{"ID" : "64", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_7_U", "Parent" : "56"},
	{"ID" : "65", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_8_U", "Parent" : "56"},
	{"ID" : "66", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_9_U", "Parent" : "56"},
	{"ID" : "67", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_10_U", "Parent" : "56"},
	{"ID" : "68", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_11_U", "Parent" : "56"},
	{"ID" : "69", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_12_U", "Parent" : "56"},
	{"ID" : "70", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_13_U", "Parent" : "56"},
	{"ID" : "71", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_14_U", "Parent" : "56"},
	{"ID" : "72", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_15_U", "Parent" : "56"},
	{"ID" : "73", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_16_U", "Parent" : "56"},
	{"ID" : "74", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_17_U", "Parent" : "56"},
	{"ID" : "75", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_18_U", "Parent" : "56"},
	{"ID" : "76", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_19_U", "Parent" : "56"},
	{"ID" : "77", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_20_U", "Parent" : "56"},
	{"ID" : "78", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_21_U", "Parent" : "56"},
	{"ID" : "79", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_22_U", "Parent" : "56"},
	{"ID" : "80", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_23_U", "Parent" : "56"},
	{"ID" : "81", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_24_U", "Parent" : "56"},
	{"ID" : "82", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_25_U", "Parent" : "56"},
	{"ID" : "83", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_26_U", "Parent" : "56"},
	{"ID" : "84", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_27_U", "Parent" : "56"},
	{"ID" : "85", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_28_U", "Parent" : "56"},
	{"ID" : "86", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_29_U", "Parent" : "56"},
	{"ID" : "87", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_30_U", "Parent" : "56"},
	{"ID" : "88", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.p_ZL8idct8_32_31_U", "Parent" : "56"},
	{"ID" : "89", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_7ns_32s_32_2_1_U176", "Parent" : "56"},
	{"ID" : "90", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U177", "Parent" : "56"},
	{"ID" : "91", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U178", "Parent" : "56"},
	{"ID" : "92", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U179", "Parent" : "56"},
	{"ID" : "93", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U180", "Parent" : "56"},
	{"ID" : "94", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U181", "Parent" : "56"},
	{"ID" : "95", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U182", "Parent" : "56"},
	{"ID" : "96", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U183", "Parent" : "56"},
	{"ID" : "97", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U184", "Parent" : "56"},
	{"ID" : "98", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U185", "Parent" : "56"},
	{"ID" : "99", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U186", "Parent" : "56"},
	{"ID" : "100", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U187", "Parent" : "56"},
	{"ID" : "101", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U188", "Parent" : "56"},
	{"ID" : "102", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U189", "Parent" : "56"},
	{"ID" : "103", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U190", "Parent" : "56"},
	{"ID" : "104", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U191", "Parent" : "56"},
	{"ID" : "105", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U192", "Parent" : "56"},
	{"ID" : "106", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U193", "Parent" : "56"},
	{"ID" : "107", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U194", "Parent" : "56"},
	{"ID" : "108", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U195", "Parent" : "56"},
	{"ID" : "109", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U196", "Parent" : "56"},
	{"ID" : "110", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U197", "Parent" : "56"},
	{"ID" : "111", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U198", "Parent" : "56"},
	{"ID" : "112", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U199", "Parent" : "56"},
	{"ID" : "113", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U200", "Parent" : "56"},
	{"ID" : "114", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U201", "Parent" : "56"},
	{"ID" : "115", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U202", "Parent" : "56"},
	{"ID" : "116", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U203", "Parent" : "56"},
	{"ID" : "117", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U204", "Parent" : "56"},
	{"ID" : "118", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U205", "Parent" : "56"},
	{"ID" : "119", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U206", "Parent" : "56"},
	{"ID" : "120", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.mul_8s_32s_32_2_1_U207", "Parent" : "56"},
	{"ID" : "121", "Level" : "3", "Path" : "`AUTOTB_DUT_INST.grp_IDCT8B32_fu_792.grp_IDCT8B32_Pipeline_VITIS_LOOP_73_1_fu_452.flow_control_loop_pipe_sequential_init_U", "Parent" : "56"},
	{"ID" : "122", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.control_s_axi_U", "Parent" : "0"},
	{"ID" : "123", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem0_m_axi_U", "Parent" : "0"},
	{"ID" : "124", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.gmem1_m_axi_U", "Parent" : "0"},
	{"ID" : "125", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mul_32s_7s_39_2_1_U384", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	IDCT8 {
		gmem0 {Type I LastRead 75 FirstWrite -1}
		gmem1 {Type O LastRead 75 FirstWrite 80}
		in_r {Type I LastRead 1 FirstWrite -1}
		out_r {Type I LastRead 1 FirstWrite -1}
		block_size {Type I LastRead 74 FirstWrite -1}
		sIn {Type I LastRead 74 FirstWrite -1}
		size {Type I LastRead 0 FirstWrite -1}
		shift {Type I LastRead 73 FirstWrite -1}
		oMin {Type I LastRead 74 FirstWrite -1}
		oMax {Type I LastRead 74 FirstWrite -1}
		p_ZL8idct8_32_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_15 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_16 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_17 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_18 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_19 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_20 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_21 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_22 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_23 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_24 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_25 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_26 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_27 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_28 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_29 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_30 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_31 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_15 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_7 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B8 {
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
		p_ZL7idct8_8_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_7 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B8_Pipeline_VITIS_LOOP_21_1 {
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
		p_ZL7idct8_8_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL7idct8_8_7 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B16 {
		src_0_val {Type I LastRead 1 FirstWrite -1}
		src_1_val {Type I LastRead 1 FirstWrite -1}
		src_2_val {Type I LastRead 1 FirstWrite -1}
		src_3_val {Type I LastRead 1 FirstWrite -1}
		src_4_val {Type I LastRead 1 FirstWrite -1}
		src_5_val {Type I LastRead 1 FirstWrite -1}
		src_6_val {Type I LastRead 1 FirstWrite -1}
		src_7_val {Type I LastRead 1 FirstWrite -1}
		src_8_val {Type I LastRead 1 FirstWrite -1}
		src_9_val {Type I LastRead 1 FirstWrite -1}
		src_10_val {Type I LastRead 1 FirstWrite -1}
		src_11_val {Type I LastRead 1 FirstWrite -1}
		src_12_val {Type I LastRead 1 FirstWrite -1}
		src_13_val {Type I LastRead 1 FirstWrite -1}
		src_14_val {Type I LastRead 1 FirstWrite -1}
		src_15_val {Type I LastRead 1 FirstWrite -1}
		dst_0 {Type O LastRead -1 FirstWrite 14}
		dst_1 {Type O LastRead -1 FirstWrite 14}
		dst_2 {Type O LastRead -1 FirstWrite 14}
		dst_3 {Type O LastRead -1 FirstWrite 14}
		dst_4 {Type O LastRead -1 FirstWrite 14}
		dst_5 {Type O LastRead -1 FirstWrite 14}
		dst_6 {Type O LastRead -1 FirstWrite 14}
		dst_7 {Type O LastRead -1 FirstWrite 14}
		dst_8 {Type O LastRead -1 FirstWrite 14}
		dst_9 {Type O LastRead -1 FirstWrite 14}
		dst_10 {Type O LastRead -1 FirstWrite 14}
		dst_11 {Type O LastRead -1 FirstWrite 14}
		dst_12 {Type O LastRead -1 FirstWrite 14}
		dst_13 {Type O LastRead -1 FirstWrite 14}
		dst_14 {Type O LastRead -1 FirstWrite 14}
		dst_15 {Type O LastRead -1 FirstWrite 14}
		shift {Type I LastRead 0 FirstWrite -1}
		skipLine2 {Type I LastRead 1 FirstWrite -1}
		oMin {Type I LastRead 1 FirstWrite -1}
		oMax {Type I LastRead 1 FirstWrite -1}
		p_ZL8idct8_16_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_15 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B16_Pipeline_VITIS_LOOP_47_1 {
		dst_0 {Type O LastRead -1 FirstWrite 14}
		dst_15 {Type O LastRead -1 FirstWrite 14}
		dst_14 {Type O LastRead -1 FirstWrite 14}
		dst_13 {Type O LastRead -1 FirstWrite 14}
		dst_12 {Type O LastRead -1 FirstWrite 14}
		dst_11 {Type O LastRead -1 FirstWrite 14}
		dst_10 {Type O LastRead -1 FirstWrite 14}
		dst_9 {Type O LastRead -1 FirstWrite 14}
		dst_8 {Type O LastRead -1 FirstWrite 14}
		dst_7 {Type O LastRead -1 FirstWrite 14}
		dst_6 {Type O LastRead -1 FirstWrite 14}
		dst_5 {Type O LastRead -1 FirstWrite 14}
		dst_4 {Type O LastRead -1 FirstWrite 14}
		dst_3 {Type O LastRead -1 FirstWrite 14}
		dst_2 {Type O LastRead -1 FirstWrite 14}
		dst_1 {Type O LastRead -1 FirstWrite 14}
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
		empty_41 {Type I LastRead 0 FirstWrite -1}
		oMin {Type I LastRead 0 FirstWrite -1}
		oMax {Type I LastRead 0 FirstWrite -1}
		empty_42 {Type I LastRead 0 FirstWrite -1}
		cutoff {Type I LastRead 0 FirstWrite -1}
		empty_43 {Type I LastRead 0 FirstWrite -1}
		empty_44 {Type I LastRead 0 FirstWrite -1}
		empty {Type I LastRead 0 FirstWrite -1}
		p_ZL8idct8_16_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_16_15 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B32 {
		src_0_val {Type I LastRead 1 FirstWrite -1}
		src_1_val {Type I LastRead 1 FirstWrite -1}
		src_2_val {Type I LastRead 1 FirstWrite -1}
		src_3_val {Type I LastRead 1 FirstWrite -1}
		src_4_val {Type I LastRead 1 FirstWrite -1}
		src_5_val {Type I LastRead 1 FirstWrite -1}
		src_6_val {Type I LastRead 1 FirstWrite -1}
		src_7_val {Type I LastRead 1 FirstWrite -1}
		src_8_val {Type I LastRead 1 FirstWrite -1}
		src_9_val {Type I LastRead 1 FirstWrite -1}
		src_10_val {Type I LastRead 1 FirstWrite -1}
		src_11_val {Type I LastRead 1 FirstWrite -1}
		src_12_val {Type I LastRead 1 FirstWrite -1}
		src_13_val {Type I LastRead 1 FirstWrite -1}
		src_14_val {Type I LastRead 1 FirstWrite -1}
		src_15_val {Type I LastRead 1 FirstWrite -1}
		src_16_val {Type I LastRead 1 FirstWrite -1}
		src_17_val {Type I LastRead 1 FirstWrite -1}
		src_18_val {Type I LastRead 1 FirstWrite -1}
		src_19_val {Type I LastRead 1 FirstWrite -1}
		src_20_val {Type I LastRead 1 FirstWrite -1}
		src_21_val {Type I LastRead 1 FirstWrite -1}
		src_22_val {Type I LastRead 1 FirstWrite -1}
		src_23_val {Type I LastRead 1 FirstWrite -1}
		src_24_val {Type I LastRead 1 FirstWrite -1}
		src_25_val {Type I LastRead 1 FirstWrite -1}
		src_26_val {Type I LastRead 1 FirstWrite -1}
		src_27_val {Type I LastRead 1 FirstWrite -1}
		src_28_val {Type I LastRead 1 FirstWrite -1}
		src_29_val {Type I LastRead 1 FirstWrite -1}
		src_30_val {Type I LastRead 1 FirstWrite -1}
		src_31_val {Type I LastRead 1 FirstWrite -1}
		dst_0 {Type O LastRead -1 FirstWrite 25}
		dst_1 {Type O LastRead -1 FirstWrite 25}
		dst_2 {Type O LastRead -1 FirstWrite 25}
		dst_3 {Type O LastRead -1 FirstWrite 25}
		dst_4 {Type O LastRead -1 FirstWrite 25}
		dst_5 {Type O LastRead -1 FirstWrite 25}
		dst_6 {Type O LastRead -1 FirstWrite 25}
		dst_7 {Type O LastRead -1 FirstWrite 25}
		dst_8 {Type O LastRead -1 FirstWrite 25}
		dst_9 {Type O LastRead -1 FirstWrite 25}
		dst_10 {Type O LastRead -1 FirstWrite 25}
		dst_11 {Type O LastRead -1 FirstWrite 25}
		dst_12 {Type O LastRead -1 FirstWrite 25}
		dst_13 {Type O LastRead -1 FirstWrite 25}
		dst_14 {Type O LastRead -1 FirstWrite 25}
		dst_15 {Type O LastRead -1 FirstWrite 25}
		dst_16 {Type O LastRead -1 FirstWrite 25}
		dst_17 {Type O LastRead -1 FirstWrite 25}
		dst_18 {Type O LastRead -1 FirstWrite 25}
		dst_19 {Type O LastRead -1 FirstWrite 25}
		dst_20 {Type O LastRead -1 FirstWrite 25}
		dst_21 {Type O LastRead -1 FirstWrite 25}
		dst_22 {Type O LastRead -1 FirstWrite 25}
		dst_23 {Type O LastRead -1 FirstWrite 25}
		dst_24 {Type O LastRead -1 FirstWrite 25}
		dst_25 {Type O LastRead -1 FirstWrite 25}
		dst_26 {Type O LastRead -1 FirstWrite 25}
		dst_27 {Type O LastRead -1 FirstWrite 25}
		dst_28 {Type O LastRead -1 FirstWrite 25}
		dst_29 {Type O LastRead -1 FirstWrite 25}
		dst_30 {Type O LastRead -1 FirstWrite 25}
		dst_31 {Type O LastRead -1 FirstWrite 25}
		shift {Type I LastRead 0 FirstWrite -1}
		skipLine2 {Type I LastRead 1 FirstWrite -1}
		oMin {Type I LastRead 1 FirstWrite -1}
		oMax {Type I LastRead 1 FirstWrite -1}
		p_ZL8idct8_32_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_15 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_16 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_17 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_18 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_19 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_20 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_21 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_22 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_23 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_24 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_25 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_26 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_27 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_28 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_29 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_30 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_31 {Type I LastRead -1 FirstWrite -1}}
	IDCT8B32_Pipeline_VITIS_LOOP_73_1 {
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
		p_ZL8idct8_32_0 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_1 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_2 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_3 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_4 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_5 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_6 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_7 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_8 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_9 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_10 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_11 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_12 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_13 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_14 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_15 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_16 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_17 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_18 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_19 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_20 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_21 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_22 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_23 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_24 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_25 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_26 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_27 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_28 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_29 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_30 {Type I LastRead -1 FirstWrite -1}
		p_ZL8idct8_32_31 {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "151", "Max" : "67732"}
	, {"Name" : "Interval", "Min" : "152", "Max" : "67733"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	gmem0 { m_axi {  { m_axi_gmem0_AWVALID VALID 1 1 }  { m_axi_gmem0_AWREADY READY 0 1 }  { m_axi_gmem0_AWADDR ADDR 1 64 }  { m_axi_gmem0_AWID ID 1 1 }  { m_axi_gmem0_AWLEN SIZE 1 8 }  { m_axi_gmem0_AWSIZE BURST 1 3 }  { m_axi_gmem0_AWBURST LOCK 1 2 }  { m_axi_gmem0_AWLOCK CACHE 1 2 }  { m_axi_gmem0_AWCACHE PROT 1 4 }  { m_axi_gmem0_AWPROT QOS 1 3 }  { m_axi_gmem0_AWQOS REGION 1 4 }  { m_axi_gmem0_AWREGION USER 1 4 }  { m_axi_gmem0_AWUSER DATA 1 1 }  { m_axi_gmem0_WVALID VALID 1 1 }  { m_axi_gmem0_WREADY READY 0 1 }  { m_axi_gmem0_WDATA FIFONUM 1 1024 }  { m_axi_gmem0_WSTRB STRB 1 128 }  { m_axi_gmem0_WLAST LAST 1 1 }  { m_axi_gmem0_WID ID 1 1 }  { m_axi_gmem0_WUSER DATA 1 1 }  { m_axi_gmem0_ARVALID VALID 1 1 }  { m_axi_gmem0_ARREADY READY 0 1 }  { m_axi_gmem0_ARADDR ADDR 1 64 }  { m_axi_gmem0_ARID ID 1 1 }  { m_axi_gmem0_ARLEN SIZE 1 8 }  { m_axi_gmem0_ARSIZE BURST 1 3 }  { m_axi_gmem0_ARBURST LOCK 1 2 }  { m_axi_gmem0_ARLOCK CACHE 1 2 }  { m_axi_gmem0_ARCACHE PROT 1 4 }  { m_axi_gmem0_ARPROT QOS 1 3 }  { m_axi_gmem0_ARQOS REGION 1 4 }  { m_axi_gmem0_ARREGION USER 1 4 }  { m_axi_gmem0_ARUSER DATA 1 1 }  { m_axi_gmem0_RVALID VALID 0 1 }  { m_axi_gmem0_RREADY READY 1 1 }  { m_axi_gmem0_RDATA FIFONUM 0 1024 }  { m_axi_gmem0_RLAST LAST 0 1 }  { m_axi_gmem0_RID ID 0 1 }  { m_axi_gmem0_RUSER DATA 0 1 }  { m_axi_gmem0_RRESP RESP 0 2 }  { m_axi_gmem0_BVALID VALID 0 1 }  { m_axi_gmem0_BREADY READY 1 1 }  { m_axi_gmem0_BRESP RESP 0 2 }  { m_axi_gmem0_BID ID 0 1 }  { m_axi_gmem0_BUSER DATA 0 1 } } }
	gmem1 { m_axi {  { m_axi_gmem1_AWVALID VALID 1 1 }  { m_axi_gmem1_AWREADY READY 0 1 }  { m_axi_gmem1_AWADDR ADDR 1 64 }  { m_axi_gmem1_AWID ID 1 1 }  { m_axi_gmem1_AWLEN SIZE 1 8 }  { m_axi_gmem1_AWSIZE BURST 1 3 }  { m_axi_gmem1_AWBURST LOCK 1 2 }  { m_axi_gmem1_AWLOCK CACHE 1 2 }  { m_axi_gmem1_AWCACHE PROT 1 4 }  { m_axi_gmem1_AWPROT QOS 1 3 }  { m_axi_gmem1_AWQOS REGION 1 4 }  { m_axi_gmem1_AWREGION USER 1 4 }  { m_axi_gmem1_AWUSER DATA 1 1 }  { m_axi_gmem1_WVALID VALID 1 1 }  { m_axi_gmem1_WREADY READY 0 1 }  { m_axi_gmem1_WDATA FIFONUM 1 1024 }  { m_axi_gmem1_WSTRB STRB 1 128 }  { m_axi_gmem1_WLAST LAST 1 1 }  { m_axi_gmem1_WID ID 1 1 }  { m_axi_gmem1_WUSER DATA 1 1 }  { m_axi_gmem1_ARVALID VALID 1 1 }  { m_axi_gmem1_ARREADY READY 0 1 }  { m_axi_gmem1_ARADDR ADDR 1 64 }  { m_axi_gmem1_ARID ID 1 1 }  { m_axi_gmem1_ARLEN SIZE 1 8 }  { m_axi_gmem1_ARSIZE BURST 1 3 }  { m_axi_gmem1_ARBURST LOCK 1 2 }  { m_axi_gmem1_ARLOCK CACHE 1 2 }  { m_axi_gmem1_ARCACHE PROT 1 4 }  { m_axi_gmem1_ARPROT QOS 1 3 }  { m_axi_gmem1_ARQOS REGION 1 4 }  { m_axi_gmem1_ARREGION USER 1 4 }  { m_axi_gmem1_ARUSER DATA 1 1 }  { m_axi_gmem1_RVALID VALID 0 1 }  { m_axi_gmem1_RREADY READY 1 1 }  { m_axi_gmem1_RDATA FIFONUM 0 1024 }  { m_axi_gmem1_RLAST LAST 0 1 }  { m_axi_gmem1_RID ID 0 1 }  { m_axi_gmem1_RUSER DATA 0 1 }  { m_axi_gmem1_RRESP RESP 0 2 }  { m_axi_gmem1_BVALID VALID 0 1 }  { m_axi_gmem1_BREADY READY 1 1 }  { m_axi_gmem1_BRESP RESP 0 2 }  { m_axi_gmem1_BID ID 0 1 }  { m_axi_gmem1_BUSER DATA 0 1 } } }
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
