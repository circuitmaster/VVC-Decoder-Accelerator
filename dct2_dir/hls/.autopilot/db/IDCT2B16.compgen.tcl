# This script segment is generated automatically by AutoPilot

set name IDCT2_mul_32s_6s_32_1_1
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {auto} LATENCY 0 ALLOW_PRAGMA 1
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
    id 43 \
    name in_0_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_0_val \
    op interface \
    ports { in_0_val { I 26 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 44 \
    name in_1_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_1_val \
    op interface \
    ports { in_1_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 45 \
    name in_2_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_2_val \
    op interface \
    ports { in_2_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 46 \
    name in_3_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_3_val \
    op interface \
    ports { in_3_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 47 \
    name in_4_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_4_val \
    op interface \
    ports { in_4_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 48 \
    name in_5_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_5_val \
    op interface \
    ports { in_5_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 49 \
    name in_6_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_6_val \
    op interface \
    ports { in_6_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 50 \
    name in_7_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_7_val \
    op interface \
    ports { in_7_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 51 \
    name in_8_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_8_val \
    op interface \
    ports { in_8_val { I 26 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 52 \
    name in_9_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_9_val \
    op interface \
    ports { in_9_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 53 \
    name in_10_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_10_val \
    op interface \
    ports { in_10_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 54 \
    name in_11_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_11_val \
    op interface \
    ports { in_11_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 55 \
    name in_12_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_12_val \
    op interface \
    ports { in_12_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 56 \
    name in_13_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_13_val \
    op interface \
    ports { in_13_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 57 \
    name in_14_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_14_val \
    op interface \
    ports { in_14_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 58 \
    name in_15_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_15_val \
    op interface \
    ports { in_15_val { I 32 vector } } \
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
    ports { ap_ready { O 1 bit } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id -2 \
    name ap_return \
    type ap_return \
    reset_level 1 \
    sync_rst true \
    corename ap_return \
    op interface \
    ports { ap_return { O 1 vector } } \
} "
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


