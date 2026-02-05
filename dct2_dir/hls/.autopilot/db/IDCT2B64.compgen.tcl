# This script segment is generated automatically by AutoPilot

set name IDCT2_mul_32s_7s_32_2_1_x
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {auto} LATENCY 1 ALLOW_PRAGMA 1
}


set name IDCT2_mul_32s_8s_32_2_1_x
if {${::AESL::PGuard_rtl_comp_handler}} {
	::AP::rtl_comp_handler $name BINDTYPE {op} TYPE {mul} IMPL {auto} LATENCY 1 ALLOW_PRAGMA 1
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
    id 487 \
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
    id 488 \
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
    id 489 \
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
    id 490 \
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
    id 491 \
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
    id 492 \
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
    id 493 \
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
    id 494 \
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
    id 495 \
    name in_8_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_8_val \
    op interface \
    ports { in_8_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 496 \
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
    id 497 \
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
    id 498 \
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
    id 499 \
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
    id 500 \
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
    id 501 \
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
    id 502 \
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
    id 503 \
    name in_16_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_16_val \
    op interface \
    ports { in_16_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 504 \
    name in_17_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_17_val \
    op interface \
    ports { in_17_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 505 \
    name in_18_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_18_val \
    op interface \
    ports { in_18_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 506 \
    name in_19_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_19_val \
    op interface \
    ports { in_19_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 507 \
    name in_20_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_20_val \
    op interface \
    ports { in_20_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 508 \
    name in_21_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_21_val \
    op interface \
    ports { in_21_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 509 \
    name in_22_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_22_val \
    op interface \
    ports { in_22_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 510 \
    name in_23_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_23_val \
    op interface \
    ports { in_23_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 511 \
    name in_24_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_24_val \
    op interface \
    ports { in_24_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 512 \
    name in_25_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_25_val \
    op interface \
    ports { in_25_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 513 \
    name in_26_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_26_val \
    op interface \
    ports { in_26_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 514 \
    name in_27_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_27_val \
    op interface \
    ports { in_27_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 515 \
    name in_28_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_28_val \
    op interface \
    ports { in_28_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 516 \
    name in_29_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_29_val \
    op interface \
    ports { in_29_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 517 \
    name in_30_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_30_val \
    op interface \
    ports { in_30_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 518 \
    name in_31_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_31_val \
    op interface \
    ports { in_31_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 519 \
    name in_32_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_32_val \
    op interface \
    ports { in_32_val { I 26 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 520 \
    name in_33_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_33_val \
    op interface \
    ports { in_33_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 521 \
    name in_34_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_34_val \
    op interface \
    ports { in_34_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 522 \
    name in_35_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_35_val \
    op interface \
    ports { in_35_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 523 \
    name in_36_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_36_val \
    op interface \
    ports { in_36_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 524 \
    name in_37_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_37_val \
    op interface \
    ports { in_37_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 525 \
    name in_38_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_38_val \
    op interface \
    ports { in_38_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 526 \
    name in_39_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_39_val \
    op interface \
    ports { in_39_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 527 \
    name in_40_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_40_val \
    op interface \
    ports { in_40_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 528 \
    name in_41_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_41_val \
    op interface \
    ports { in_41_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 529 \
    name in_42_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_42_val \
    op interface \
    ports { in_42_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 530 \
    name in_43_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_43_val \
    op interface \
    ports { in_43_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 531 \
    name in_44_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_44_val \
    op interface \
    ports { in_44_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 532 \
    name in_45_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_45_val \
    op interface \
    ports { in_45_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 533 \
    name in_46_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_46_val \
    op interface \
    ports { in_46_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 534 \
    name in_47_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_47_val \
    op interface \
    ports { in_47_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 535 \
    name in_48_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_48_val \
    op interface \
    ports { in_48_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 536 \
    name in_49_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_49_val \
    op interface \
    ports { in_49_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 537 \
    name in_50_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_50_val \
    op interface \
    ports { in_50_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 538 \
    name in_51_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_51_val \
    op interface \
    ports { in_51_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 539 \
    name in_52_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_52_val \
    op interface \
    ports { in_52_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 540 \
    name in_53_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_53_val \
    op interface \
    ports { in_53_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 541 \
    name in_54_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_54_val \
    op interface \
    ports { in_54_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 542 \
    name in_55_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_55_val \
    op interface \
    ports { in_55_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 543 \
    name in_56_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_56_val \
    op interface \
    ports { in_56_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 544 \
    name in_57_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_57_val \
    op interface \
    ports { in_57_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 545 \
    name in_58_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_58_val \
    op interface \
    ports { in_58_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 546 \
    name in_59_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_59_val \
    op interface \
    ports { in_59_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 547 \
    name in_60_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_60_val \
    op interface \
    ports { in_60_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 548 \
    name in_61_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_61_val \
    op interface \
    ports { in_61_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 549 \
    name in_62_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_62_val \
    op interface \
    ports { in_62_val { I 32 vector } } \
} "
}

# Direct connection:
if {${::AESL::PGuard_autoexp_gen}} {
eval "cg_default_interface_gen_dc { \
    id 550 \
    name in_63_val \
    type other \
    dir I \
    reset_level 1 \
    sync_rst true \
    corename dc_in_63_val \
    op interface \
    ports { in_63_val { I 32 vector } } \
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
set PortName ap_clk
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_clock] == "cg_default_interface_gen_clock"} {
eval "cg_default_interface_gen_clock { \
    id -3 \
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
    id -4 \
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


# Adapter definition:
set PortName ap_ce
set DataWd 1 
if {${::AESL::PGuard_autoexp_gen}} {
if {[info proc cg_default_interface_gen_ce] == "cg_default_interface_gen_ce"} {
eval "cg_default_interface_gen_ce { \
    id -5 \
    name ${PortName} \
    reset_level 1 \
    sync_rst true \
    corename apif_ap_ce \
    data_wd ${DataWd} \
    op interface \
}"
} else {
puts "@W \[IMPL-113\] Cannot find bus interface model in the library. Ignored generation of bus interface for '${PortName}'"
}
}



# merge
if {${::AESL::PGuard_autoexp_gen}} {
    cg_default_interface_gen_dc_end
    cg_default_interface_gen_bundle_end
    AESL_LIB_XILADAPTER::native_axis_end
}


