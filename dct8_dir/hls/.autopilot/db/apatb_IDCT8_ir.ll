; ModuleID = '/home/mahir/Desktop/vvc/VVC-Decoder-Accelerator/dct8_dir/hls/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"struct.ap_int<1024>" = type { %"struct.ap_int_base<1024, true>" }
%"struct.ap_int_base<1024, true>" = type { %"struct.ssdm_int<1024, true>" }
%"struct.ssdm_int<1024, true>" = type { i1024 }
%"struct.ap_int<32>" = type { %"struct.ap_int_base<32, true>" }
%"struct.ap_int_base<32, true>" = type { %"struct.ssdm_int<32, true>" }
%"struct.ssdm_int<32, true>" = type { i32 }

; Function Attrs: inaccessiblemem_or_argmemonly noinline willreturn
define void @apatb_IDCT8_ir(%"struct.ap_int<1024>"* noalias nocapture nonnull readonly "maxi" %in, %"struct.ap_int<1024>"* noalias nocapture nonnull "maxi" %out, %"struct.ap_int<32>"* nocapture readonly %block_size, %"struct.ap_int<32>"* nocapture readonly %sIn, %"struct.ap_int<32>"* nocapture readonly %size, %"struct.ap_int<32>"* nocapture readonly %shift, %"struct.ap_int<32>"* nocapture readonly %oMin, %"struct.ap_int<32>"* nocapture readonly %oMax) local_unnamed_addr #0 {
entry:
  %in_copy = alloca i1024, align 512
  %out_copy = alloca i1024, align 512
  call fastcc void @copy_in(%"struct.ap_int<1024>"* nonnull %in, i1024* nonnull align 512 %in_copy, %"struct.ap_int<1024>"* nonnull %out, i1024* nonnull align 512 %out_copy)
  call void @apatb_IDCT8_hw(i1024* %in_copy, i1024* %out_copy, %"struct.ap_int<32>"* %block_size, %"struct.ap_int<32>"* %sIn, %"struct.ap_int<32>"* %size, %"struct.ap_int<32>"* %shift, %"struct.ap_int<32>"* %oMin, %"struct.ap_int<32>"* %oMax)
  call void @copy_back(%"struct.ap_int<1024>"* %in, i1024* %in_copy, %"struct.ap_int<1024>"* %out, i1024* %out_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in(%"struct.ap_int<1024>"* noalias readonly "unpacked"="0", i1024* noalias nocapture align 512 "unpacked"="1.0", %"struct.ap_int<1024>"* noalias readonly "unpacked"="2", i1024* noalias nocapture align 512 "unpacked"="3.0") unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>.54"(i1024* align 512 %1, %"struct.ap_int<1024>"* %0)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>.54"(i1024* align 512 %3, %"struct.ap_int<1024>"* %2)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out(%"struct.ap_int<1024>"* noalias "unpacked"="0", i1024* noalias nocapture readonly align 512 "unpacked"="1.0", %"struct.ap_int<1024>"* noalias "unpacked"="2", i1024* noalias nocapture readonly align 512 "unpacked"="3.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %0, i1024* align 512 %1)
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %2, i1024* align 512 %3)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* noalias "unpacked"="0" %dst, i1024* noalias nocapture readonly align 512 "unpacked"="1.0" %src) unnamed_addr #3 {
entry:
  %0 = icmp eq %"struct.ap_int<1024>"* %dst, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  %dst.0.0.04 = getelementptr %"struct.ap_int<1024>", %"struct.ap_int<1024>"* %dst, i64 0, i32 0, i32 0, i32 0
  %1 = load i1024, i1024* %src, align 512
  store i1024 %1, i1024* %dst.0.0.04, align 128
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>.54"(i1024* noalias nocapture align 512 "unpacked"="0.0" %dst, %"struct.ap_int<1024>"* noalias readonly "unpacked"="1" %src) unnamed_addr #3 {
entry:
  %0 = icmp eq %"struct.ap_int<1024>"* %src, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  %src.0.0.03 = getelementptr %"struct.ap_int<1024>", %"struct.ap_int<1024>"* %src, i64 0, i32 0, i32 0, i32 0
  %1 = load i1024, i1024* %src.0.0.03, align 128
  store i1024 %1, i1024* %dst, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

declare i8* @malloc(i64)

declare void @free(i8*)

declare void @apatb_IDCT8_hw(i1024*, i1024*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back(%"struct.ap_int<1024>"* noalias "unpacked"="0", i1024* noalias nocapture readonly align 512 "unpacked"="1.0", %"struct.ap_int<1024>"* noalias "unpacked"="2", i1024* noalias nocapture readonly align 512 "unpacked"="3.0") unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0struct.ap_int<1024>"(%"struct.ap_int<1024>"* %2, i1024* align 512 %3)
  ret void
}

declare void @IDCT8_hw_stub(%"struct.ap_int<1024>"* noalias nocapture nonnull readonly, %"struct.ap_int<1024>"* noalias nocapture nonnull, %"struct.ap_int<32>"* nocapture readonly, %"struct.ap_int<32>"* nocapture readonly, %"struct.ap_int<32>"* nocapture readonly, %"struct.ap_int<32>"* nocapture readonly, %"struct.ap_int<32>"* nocapture readonly, %"struct.ap_int<32>"* nocapture readonly)

define void @IDCT8_hw_stub_wrapper(i1024*, i1024*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*, %"struct.ap_int<32>"*) #4 {
entry:
  %8 = call i8* @malloc(i64 128)
  %9 = bitcast i8* %8 to %"struct.ap_int<1024>"*
  %10 = call i8* @malloc(i64 128)
  %11 = bitcast i8* %10 to %"struct.ap_int<1024>"*
  call void @copy_out(%"struct.ap_int<1024>"* %9, i1024* %0, %"struct.ap_int<1024>"* %11, i1024* %1)
  call void @IDCT8_hw_stub(%"struct.ap_int<1024>"* %9, %"struct.ap_int<1024>"* %11, %"struct.ap_int<32>"* %2, %"struct.ap_int<32>"* %3, %"struct.ap_int<32>"* %4, %"struct.ap_int<32>"* %5, %"struct.ap_int<32>"* %6, %"struct.ap_int<32>"* %7)
  call void @copy_in(%"struct.ap_int<1024>"* %9, i1024* %0, %"struct.ap_int<1024>"* %11, i1024* %1)
  call void @free(i8* %8)
  call void @free(i8* %10)
  ret void
}

attributes #0 = { inaccessiblemem_or_argmemonly noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
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
