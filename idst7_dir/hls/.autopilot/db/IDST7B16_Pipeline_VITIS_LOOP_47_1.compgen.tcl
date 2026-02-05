# This script segment is generated automatically by AutoPilot

if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_0_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_1_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_2_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_3_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_4_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_5_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_6_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_7_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_8_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_9_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_10_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_11_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_12_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_13_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_14_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler IDST7_IDST7B16_Pipeline_VITIS_LOOP_47_1_p_ZL8idst7_16_15_ROM_AUTO_1R BINDTYPE {storage} TYPE {rom} IMPL {auto} LATENCY 2 ALLOW_PRAGMA 1
}


# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 97 \
    name dst_0 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_0 \
    op interface \
    ports { dst_0 { O 32 vector } dst_0_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 98 \
    name dst_15 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_15 \
    op interface \
    ports { dst_15 { O 32 vector } dst_15_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 99 \
    name dst_14 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_14 \
    op interface \
    ports { dst_14 { O 32 vector } dst_14_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 100 \
    name dst_13 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_13 \
    op interface \
    ports { dst_13 { O 32 vector } dst_13_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 101 \
    name dst_12 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_12 \
    op interface \
    ports { dst_12 { O 32 vector } dst_12_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 102 \
    name dst_11 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_11 \
    op interface \
    ports { dst_11 { O 32 vector } dst_11_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 103 \
    name dst_10 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_10 \
    op interface \
    ports { dst_10 { O 32 vector } dst_10_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 104 \
    name dst_9 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_9 \
    op interface \
    ports { dst_9 { O 32 vector } dst_9_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 105 \
    name dst_8 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_8 \
    op interface \
    ports { dst_8 { O 32 vector } dst_8_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 106 \
    name dst_7 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_7 \
    op interface \
    ports { dst_7 { O 32 vector } dst_7_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 107 \
    name dst_6 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_6 \
    op interface \
    ports { dst_6 { O 32 vector } dst_6_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 108 \
    name dst_5 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_5 \
    op interface \
    ports { dst_5 { O 32 vector } dst_5_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 109 \
    name dst_4 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_4 \
    op interface \
    ports { dst_4 { O 32 vector } dst_4_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 110 \
    name dst_3 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_3 \
    op interface \
    ports { dst_3 { O 32 vector } dst_3_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 111 \
    name dst_2 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_2 \
    op interface \
    ports { dst_2 { O 32 vector } dst_2_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 112 \
    name dst_1 \
    type other \
    dir O \
    reset_level 1 \
    sync_rst true \
    corename dc_dst_1 \
    op interface \
    ports { dst_1 { O 32 vector } dst_1_ap_vld { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 113 \
    name src_0_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_0_val \
    op interface \
    ports { src_0_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 114 \
    name src_1_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_1_val \
    op interface \
    ports { src_1_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 115 \
    name src_2_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_2_val \
    op interface \
    ports { src_2_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 116 \
    name src_3_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_3_val \
    op interface \
    ports { src_3_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 117 \
    name src_4_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_4_val \
    op interface \
    ports { src_4_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 118 \
    name src_5_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_5_val \
    op interface \
    ports { src_5_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 119 \
    name src_6_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_6_val \
    op interface \
    ports { src_6_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 120 \
    name src_7_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_7_val \
    op interface \
    ports { src_7_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 121 \
    name src_8_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_8_val \
    op interface \
    ports { src_8_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 122 \
    name src_9_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_9_val \
    op interface \
    ports { src_9_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 123 \
    name src_10_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_10_val \
    op interface \
    ports { src_10_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 124 \
    name src_11_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_11_val \
    op interface \
    ports { src_11_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 125 \
    name src_12_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_12_val \
    op interface \
    ports { src_12_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 126 \
    name src_13_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_13_val \
    op interface \
    ports { src_13_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 127 \
    name src_14_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_14_val \
    op interface \
    ports { src_14_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 128 \
    name src_15_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_src_15_val \
    op interface \
    ports { src_15_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 129 \
    name conv3_i12_i_i \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_conv3_i12_i_i \
    op interface \
    ports { conv3_i12_i_i { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 130 \
    name sh_prom_i9_i_i \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_sh_prom_i9_i_i \
    op interface \
    ports { sh_prom_i9_i_i { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 131 \
    name sh_prom_i_i_i \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_sh_prom_i_i_i \
    op interface \
    ports { sh_prom_i_i_i { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 132 \
    name empty_41 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_empty_41 \
    op interface \
    ports { empty_41 { I 1 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 133 \
    name oMin \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_oMin \
    op interface \
    ports { oMin { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 134 \
    name oMax \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_oMax \
    op interface \
    ports { oMax { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 135 \
    name empty_42 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_empty_42 \
    op interface \
    ports { empty_42 { I 28 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 136 \
    name cutoff \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_cutoff \
    op interface \
    ports { cutoff { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 137 \
    name empty_43 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_empty_43 \
    op interface \
    ports { empty_43 { I 29 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 138 \
    name empty_44 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_empty_44 \
    op interface \
    ports { empty_44 { I 30 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 139 \
    name empty \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_empty \
    op interface \
    ports { empty { I 31 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -1 \
    name ap_ctrl \
    type ap_ctrl \
    reset_level 1 \
    sync_rst true \
    corename ap_ctrl \
    op interface \
    ports { ap_start { I 1 bit } ap_ready { O 1 bit } ap_done { O 1 bit } ap_idle { O 1 bit } } \
} "
}


# Adapter definition:
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -2 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_clk \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}


# Adapter definition:
set PortName ap_rst
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_reset] == "cg_default_interface_gen_reset"} {
eval "cg_default_interface_gen_reset { \
    id -3 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_rst \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-114\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


# flow_control definition:
set InstName IDST7_flow_control_loop_pipe_sequential_init_U
set CompName IDST7_flow_control_loop_pipe_sequential_init
set name flow_control_loop_pipe_sequential_init
if {${::AESL::PGuard_autocg_gen} && ${::AESL::PGuard_autocg_ipmgen}} {
if {[info proc ::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control] == "::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control"} {
eval "::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control { \
    name ${name} \
    prefix IDST7_ \
}"
} else {
puts "@W \[IMPL-107\] Cannot find ::AESL_LIB_VIRTEX::xil_gen_UPC_flow_control, check your platform lib"
}
}


if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $CompName BINDTYPE interface TYPE internal_upc_flow_control INSTNAME $InstName
}


