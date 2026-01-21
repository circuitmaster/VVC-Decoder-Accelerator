; ModuleID = '/home/emre24/Desktop/vvc_proj_kernels/Emulation-SW/build/IDCT8/IDCT8/IDCT8/solution/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_int<512>" = type { %"struct.ap_int_base<512, true>" }
%"struct.ap_int_base<512, true>" = type { %"struct.ssdm_int<512, true>" }
%"struct.ssdm_int<512, true>" = type { i512 }
%"struct.ap_int<32>" = type { %"struct.ap_int_base<32, true>" }
%"struct.ap_int_base<32, true>" = type { %"struct.ssdm_int<32, true>" }
%"struct.ssdm_int<32, true>" = type { i32 }

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_IDCT8_ir(%"struct.ap_int<512>"* noalias nocapture nonnull readonly %in, %"struct.ap_int<512>"* noalias nocapture nonnull %out, %"struct.ap_int<32>"* nocapture readonly %block_size, %"struct.ap_int<32>"* nocapture readonly %sIn, %"struct.ap_int<32>"* nocapture readonly %size, %"struct.ap_int<32>"* nocapture readonly %shift, %"struct.ap_int<32>"* nocapture readonly %oMin, %"struct.ap_int<32>"* nocapture readonly %oMax) local_unnamed_addr #0 {
entry:
  %in_copy = alloca %"struct.ap_int<512>", align 512
  %out_copy = alloca %"struct.ap_int<512>", align 512
  call fastcc void @copy_in(%"struct.ap_int<512>"* nonnull %in, %"struct.ap_int<512>"* nonnull align 512 %in_copy, %"struct.ap_int<512>"* nonnull %out, %"struct.ap_int<512>"* nonnull align 512 %out_copy)
  call void @apatb_IDCT8_hw(%"struct.ap_int<512>"* %in_copy, %"struct.ap_int<512>"* %out_copy, %"struct.ap_int<32>"* %block_size, %"struct.ap_int<32>"* %sIn, %"struct.ap_int<32>"* %size, %"struct.ap_int<32>"* %shift, %"struct.ap_int<32>"* %oMin, %"struct.ap_int<32>"* %oMax)
  call void @copy_back(%"struct.ap_int<512>"* %in, %"struct.ap_int<512>"* %in_copy, %"struct.ap_int<512>"* %out, %"struct.ap_int<512>"* %out_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in(%"struct.ap_int<512>"* noalias readonly, %"struct.ap_int<512>"* noalias align 512, %"struct.ap_int<512>"* noalias readonly, %"struct.ap_int<512>"* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* align 512 %1, %"struct.ap_int<512>"* %0)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* align 512 %3, %"struct.ap_int<512>"* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* noalias align 512, %"struct.ap_int<512>"* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq %"struct.ap_int<512>"* %0, null
  %3 = icmp eq %"struct.ap_int<512>"* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.0.04 = getelementptr %"struct.ap_int<512>", %"struct.ap_int<512>"* %1, i32 0, i32 0, i32 0, i32 0
  %.01.0.05 = getelementptr %"struct.ap_int<512>", %"struct.ap_int<512>"* %0, i32 0, i32 0, i32 0, i32 0
  %5 = load i512, i512* %.0.0.04, align 64
  store i512 %5, i512* %.01.0.05, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out(%"struct.ap_int<512>"* noalias, %"struct.ap_int<512>"* noalias readonly align 512, %"struct.ap_int<512>"* noalias, %"struct.ap_int<512>"* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* %0, %"struct.ap_int<512>"* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* %2, %"struct.ap_int<512>"* align 512 %3)
  ret void
}

declare void @apatb_IDCT8_hw(%"struct.ap_int<512>"*, %"struct.ap_int<512>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back(%"struct.ap_int<512>"* noalias, %"struct.ap_int<512>"* noalias readonly align 512, %"struct.ap_int<512>"* noalias, %"struct.ap_int<512>"* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<512>"(%"struct.ap_int<512>"* %2, %"struct.ap_int<512>"* align 512 %3)
  ret void
}

define void @IDCT8_hw_stub_wrapper(%"struct.ap_int<512>"*, %"struct.ap_int<512>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*) #4 {
entry:
  call void @copy_out(%"struct.ap_int<512>"* null, %"struct.ap_int<512>"* %0, %"struct.ap_int<512>"* null, %"struct.ap_int<512>"* %1)
  call void @IDCT8_hw_stub(%"struct.ap_int<512>"* %0, %"struct.ap_int<512>"* %1, %"struct.ap_int<32>"* %2, %"struct.ap_int<32>"* %3, %"struct.ap_int<32>"* %4, %"struct.ap_int<32>"* %5, %"struct.ap_int<32>"* %6, %"struct.ap_int<32>"* %7)
  call void @copy_in(%"struct.ap_int<512>"* null, %"struct.ap_int<512>"* %0, %"struct.ap_int<512>"* null, %"struct.ap_int<512>"* %1)
  ret void
}

declare void @IDCT8_hw_stub(%"struct.ap_int<512>"*, %"struct.ap_int<512>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*)

attributes #0 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
