# This script segment is generated automatically by AutoPilot

# clear list
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_begin
    cg_default_interface_gen_bundle_begin
    AESL_LIB_XILADAPTER::native_axis_begin
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 45 \
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
    id 46 \
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
    id 47 \
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
    id 48 \
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
    id 49 \
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
    id 50 \
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
    id 51 \
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
    id 52 \
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
    id 53 \
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
    id 54 \
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
    id 55 \
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
    id 56 \
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
    id 57 \
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
    id 58 \
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
    id 59 \
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
    id 60 \
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
    id 61 \
    name shift \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_shift \
    op interface \
    ports { shift { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 62 \
    name skipLine2 \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_skipLine2 \
    op interface \
    ports { skipLine2 { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 63 \
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
    id 64 \
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


