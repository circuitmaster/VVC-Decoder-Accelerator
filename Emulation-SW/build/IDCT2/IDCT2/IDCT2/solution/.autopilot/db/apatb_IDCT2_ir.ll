; ModuleID = '/home/emre24/Desktop/vvc_proj_kernels/Emulation-SW/build/IDCT2/IDCT2/IDCT2/solution/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_int<1024>" = type { %"struct.ap_int_base<1024, true>" }
%"struct.ap_int_base<1024, true>" = type { %"struct.ssdm_int<1024, true>" }
%"struct.ssdm_int<1024, true>" = type { i1024 }

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_IDCT2_ir(%"struct.ap_int<1024>"* noalias nocapture nonnull readonly %in, %"struct.ap_int<1024>"* noalias nocapture nonnull readonly %in2, %"struct.ap_int<1024>"* noalias nocapture nonnull %out, %"struct.ap_int<1024>"* noalias nocapture nonnull %out2, i32 %block_size, i32 %size, i32 %shift, i32 %outputMinimum, i32 %outputMaximum) local_unnamed_addr #0 {
entry:
  %in_copy = alloca %"struct.ap_int<1024>", align 512
  %in2_copy = alloca %"struct.ap_int<1024>", align 512
  %out_copy = alloca %"struct.ap_int<1024>", align 512
  %out2_copy = alloca %"struct.ap_int<1024>", align 512
  call fastcc void @copy_in(%"struct.ap_int<1024>"* nonnull %in, %"struct.ap_int<1024>"* nonnull align 512 %in_copy, %"struct.ap_int<1024>"* nonnull %in2, %"struct.ap_int<1024>"* nonnull align 512 %in2_copy, %"struct.ap_int<1024>"* nonnull %out, %"struct.ap_int<1024>"* nonnull align 512 %out_copy, %"struct.ap_int<1024>"* nonnull %out2, %"struct.ap_int<1024>"* nonnull align 512 %out2_copy)
  call void @apatb_IDCT2_hw(%"struct.ap_int<1024>"* %in_copy, %"struct.ap_int<1024>"* %in2_copy, %"struct.ap_int<1024>"* %out_copy, %"struct.ap_int<1024>"* %out2_copy, i32 %block_size, i32 %size, i32 %shift, i32 %outputMinimum, i32 %outputMaximum)
  call void @copy_back(%"struct.ap_int<1024>"* %in, %"struct.ap_int<1024>"* %in_copy, %"struct.ap_int<1024>"* %in2, %"struct.ap_int<1024>"* %in2_copy, %"struct.ap_int<1024>"* %out, %"struct.ap_int<1024>"* %out_copy, %"struct.ap_int<1024>"* %out2, %"struct.ap_int<1024>"* %out2_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in(%"struct.ap_int<1024>"* noalias readonly, %"struct.ap_int<1024>"* noalias align 512, %"struct.ap_int<1024>"* noalias readonly, %"struct.ap_int<1024>"* noalias align 512, %"struct.ap_int<1024>"* noalias readonly, %"struct.ap_int<1024>"* noalias align 512, %"struct.ap_int<1024>"* noalias readonly, %"struct.ap_int<1024>"* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* align 512 %1, %"struct.ap_int<1024>"* %0)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* align 512 %3, %"struct.ap_int<1024>"* %2)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* align 512 %5, %"struct.ap_int<1024>"* %4)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* align 512 %7, %"struct.ap_int<1024>"* %6)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* noalias align 512, %"struct.ap_int<1024>"* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq %"struct.ap_int<1024>"* %0, null
  %3 = icmp eq %"struct.ap_int<1024>"* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  %.0.0.04 = getelementptr %"struct.ap_int<1024>", %"struct.ap_int<1024>"* %1, i32 0, i32 0, i32 0, i32 0
  %.01.0.05 = getelementptr %"struct.ap_int<1024>", %"struct.ap_int<1024>"* %0, i32 0, i32 0, i32 0, i32 0
  %5 = load i1024, i1024* %.0.0.04, align 128
  store i1024 %5, i1024* %.01.0.05, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out(%"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %0, %"struct.ap_int<1024>"* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %2, %"struct.ap_int<1024>"* align 512 %3)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %4, %"struct.ap_int<1024>"* align 512 %5)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %6, %"struct.ap_int<1024>"* align 512 %7)
  ret void
}

declare void @apatb_IDCT2_hw(%"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, i32, i32, i32, i32, i32)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back(%"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512, %"struct.ap_int<1024>"* noalias, %"struct.ap_int<1024>"* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %4, %"struct.ap_int<1024>"* align 512 %5)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %6, %"struct.ap_int<1024>"* align 512 %7)
  ret void
}

define void @IDCT2_hw_stub_wrapper(%"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, i32, i32, i32, i32, i32) #4 {
entry:
  call void @copy_out(%"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %0, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %1, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %2, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %3)
  call void @IDCT2_hw_stub(%"struct.ap_int<1024>"* %0, %"struct.ap_int<1024>"* %1, %"struct.ap_int<1024>"* %2, %"struct.ap_int<1024>"* %3, i32 %4, i32 %5, i32 %6, i32 %7, i32 %8)
  call void @copy_in(%"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %0, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %1, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %2, %"struct.ap_int<1024>"* null, %"struct.ap_int<1024>"* %3)
  ret void
}

declare void @IDCT2_hw_stub(%"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, %"struct.ap_int<1024>"*, i32, i32, i32, i32, i32)

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
