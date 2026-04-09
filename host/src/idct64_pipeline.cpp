// idct64_pipeline.cpp
//
// Pipeline for IDCT-2 64-point 1D (horizontal pass only) with FPGA acceleration.
//
// Encodes each video frame using a 1-D forward DCT-2 applied to every 64-pixel
// row segment (30 segments per 1920-wide row, 1080 rows = 32 400 blocks/frame).
// The encoded blocks are then decoded in hardware via three pipeline variants:
//
//   Scenario 1 – bulk upload: pre-sync one fixed encoded frame to FPGA DRAM,
//                then execute the IDCT kernel for every frame in a loop.
//   Scenario 2 – per-frame:   copy → sync → run → sync → stream each frame.
//   Scenario 3 – double-buf:  overlap next-frame transfer with current execution.
//
// Usage:
//   idct64_pipeline <xclbin> <total_frames>
//                   <input:random|gradient|video:/path/to/file.yuv>
//                   [output:display|mp4:/path/to/output.mp4]
//
// The inverse DCT shift is computed automatically as 2*SHIFT_FWD (=12) and
// the output pixel range is clamped to [0, 255] — no manual tuning required.

#include <algorithm>
#include <array>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <atomic>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

#include <ap_int.h>

#include "xrt/xrt_bo.h"
#include "xrt/xrt_device.h"
#include "xrt/xrt_kernel.h"

#include <gst/gst.h>
#include <gst/app/gstappsrc.h>

#include <memory>
#include "indicators.hpp"

// ============================================================================
// Types & constants
// ============================================================================
namespace {

using TCoeff       = int32_t;
using TMatrixCoeff = int16_t;
// One 64-element block of int16_t coefficients packed in a 1024-bit word.
using coeff_word_t = ap_uint<1024>;

constexpr int WIDTH            = 1920;
constexpr int HEIGHT           = 1080;
constexpr int IDCT_BLOCK       = 64;
constexpr int BLOCKS_PER_ROW   = WIDTH  / IDCT_BLOCK;         // 30
constexpr int BLOCKS_PER_FRAME = HEIGHT * BLOCKS_PER_ROW;     // 32 400
constexpr int SHIFT_FWD        = 6;   // forward DCT horizontal shift
constexpr int SHIFT_INV        = 2 * SHIFT_FWD; // = 12: recovers original pixel scale
constexpr int OUT_MIN          = 0;   // pixel clip min after inverse DCT
constexpr int OUT_MAX          = 255; // pixel clip max after inverse DCT

// ============================================================================
// VVC/HEVC DCT-2 64-point inverse-transform matrix
// (used by the forward butterfly via its transpose relationship)
// ============================================================================
static const TMatrixCoeff idct64[64][64] =
{
  { 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64 },
  { 91, 90, 90, 90, 88, 87, 86, 84, 83, 81, 79, 77, 73, 71, 69, 65, 62, 59, 56, 52, 48, 44, 41, 37, 33, 28, 24, 20, 15, 11,  7,  2, -2, -7,-11,-15,-20,-24,-28,-33,-37,-41,-44,-48,-52,-56,-59,-62,-65,-69,-71,-73,-77,-79,-81,-83,-84,-86,-87,-88,-90,-90,-90,-91 },
  { 90, 90, 88, 85, 82, 78, 73, 67, 61, 54, 46, 38, 31, 22, 13,  4, -4,-13,-22,-31,-38,-46,-54,-61,-67,-73,-78,-82,-85,-88,-90,-90,-90,-90,-88,-85,-82,-78,-73,-67,-61,-54,-46,-38,-31,-22,-13, -4,  4, 13, 22, 31, 38, 46, 54, 61, 67, 73, 78, 82, 85, 88, 90, 90 },
  { 90, 88, 84, 79, 71, 62, 52, 41, 28, 15,  2,-11,-24,-37,-48,-59,-69,-77,-83,-87,-90,-91,-90,-86,-81,-73,-65,-56,-44,-33,-20, -7,  7, 20, 33, 44, 56, 65, 73, 81, 86, 90, 91, 90, 87, 83, 77, 69, 59, 48, 37, 24, 11, -2,-15,-28,-41,-52,-62,-71,-79,-84,-88,-90 },
  { 90, 87, 80, 70, 57, 43, 25,  9, -9,-25,-43,-57,-70,-80,-87,-90,-90,-87,-80,-70,-57,-43,-25, -9,  9, 25, 43, 57, 70, 80, 87, 90, 90, 87, 80, 70, 57, 43, 25,  9, -9,-25,-43,-57,-70,-80,-87,-90,-90,-87,-80,-70,-57,-43,-25, -9,  9, 25, 43, 57, 70, 80, 87, 90 },
  { 90, 84, 73, 59, 41, 20, -2,-24,-44,-62,-77,-86,-90,-90,-83,-71,-56,-37,-15,  7, 28, 48, 65, 79, 87, 91, 88, 81, 69, 52, 33, 11,-11,-33,-52,-69,-81,-88,-91,-87,-79,-65,-48,-28, -7, 15, 37, 56, 71, 83, 90, 90, 86, 77, 62, 44, 24,  2,-20,-41,-59,-73,-84,-90 },
  { 90, 82, 67, 46, 22, -4,-31,-54,-73,-85,-90,-88,-78,-61,-38,-13, 13, 38, 61, 78, 88, 90, 85, 73, 54, 31,  4,-22,-46,-67,-82,-90,-90,-82,-67,-46,-22,  4, 31, 54, 73, 85, 90, 88, 78, 61, 38, 13,-13,-38,-61,-78,-88,-90,-85,-73,-54,-31, -4, 22, 46, 67, 82, 90 },
  { 90, 79, 59, 33,  2,-28,-56,-77,-88,-90,-81,-62,-37, -7, 24, 52, 73, 87, 90, 83, 65, 41, 11,-20,-48,-71,-86,-91,-84,-69,-44,-15, 15, 44, 69, 84, 91, 86, 71, 48, 20,-11,-41,-65,-83,-90,-87,-73,-52,-24,  7, 37, 62, 81, 90, 88, 77, 56, 28, -2,-33,-59,-79,-90 },
  { 89, 75, 50, 18,-18,-50,-75,-89,-89,-75,-50,-18, 18, 50, 75, 89, 89, 75, 50, 18,-18,-50,-75,-89,-89,-75,-50,-18, 18, 50, 75, 89, 89, 75, 50, 18,-18,-50,-75,-89,-89,-75,-50,-18, 18, 50, 75, 89, 89, 75, 50, 18,-18,-50,-75,-89,-89,-75,-50,-18, 18, 50, 75, 89 },
  { 88, 71, 41,  2,-37,-69,-87,-90,-73,-44, -7, 33, 65, 86, 90, 77, 48, 11,-28,-62,-84,-90,-79,-52,-15, 24, 59, 83, 91, 81, 56, 20,-20,-56,-81,-91,-83,-59,-24, 15, 52, 79, 90, 84, 62, 28,-11,-48,-77,-90,-86,-65,-33,  7, 44, 73, 90, 87, 69, 37, -2,-41,-71,-88 },
  { 88, 67, 31,-13,-54,-82,-90,-78,-46, -4, 38, 73, 90, 85, 61, 22,-22,-61,-85,-90,-73,-38,  4, 46, 78, 90, 82, 54, 13,-31,-67,-88,-88,-67,-31, 13, 54, 82, 90, 78, 46,  4,-38,-73,-90,-85,-61,-22, 22, 61, 85, 90, 73, 38, -4,-46,-78,-90,-82,-54,-13, 31, 67, 88 },
  { 87, 62, 20,-28,-69,-90,-84,-56,-11, 37, 73, 90, 81, 48,  2,-44,-79,-91,-77,-41,  7, 52, 83, 90, 71, 33,-15,-59,-86,-88,-65,-24, 24, 65, 88, 86, 59, 15,-33,-71,-90,-83,-52, -7, 41, 77, 91, 79, 44, -2,-48,-81,-90,-73,-37, 11, 56, 84, 90, 69, 28,-20,-62,-87 },
  { 87, 57,  9,-43,-80,-90,-70,-25, 25, 70, 90, 80, 43, -9,-57,-87,-87,-57, -9, 43, 80, 90, 70, 25,-25,-70,-90,-80,-43,  9, 57, 87, 87, 57,  9,-43,-80,-90,-70,-25, 25, 70, 90, 80, 43, -9,-57,-87,-87,-57, -9, 43, 80, 90, 70, 25,-25,-70,-90,-80,-43,  9, 57, 87 },
  { 86, 52, -2,-56,-87,-84,-48,  7, 59, 88, 83, 44,-11,-62,-90,-81,-41, 15, 65, 90, 79, 37,-20,-69,-90,-77,-33, 24, 71, 91, 73, 28,-28,-73,-91,-71,-24, 33, 77, 90, 69, 20,-37,-79,-90,-65,-15, 41, 81, 90, 62, 11,-44,-83,-88,-59, -7, 48, 84, 87, 56,  2,-52,-86 },
  { 85, 46,-13,-67,-90,-73,-22, 38, 82, 88, 54, -4,-61,-90,-78,-31, 31, 78, 90, 61,  4,-54,-88,-82,-38, 22, 73, 90, 67, 13,-46,-85,-85,-46, 13, 67, 90, 73, 22,-38,-82,-88,-54,  4, 61, 90, 78, 31,-31,-78,-90,-61, -4, 54, 88, 82, 38,-22,-73,-90,-67,-13, 46, 85 },
  { 84, 41,-24,-77,-90,-56,  7, 65, 91, 69, 11,-52,-88,-79,-28, 37, 83, 86, 44,-20,-73,-90,-59,  2, 62, 90, 71, 15,-48,-87,-81,-33, 33, 81, 87, 48,-15,-71,-90,-62, -2, 59, 90, 73, 20,-44,-86,-83,-37, 28, 79, 88, 52,-11,-69,-91,-65, -7, 56, 90, 77, 24,-41,-84 },
  { 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83, 83, 36,-36,-83,-83,-36, 36, 83 },
  { 83, 28,-44,-88,-73,-11, 59, 91, 62, -7,-71,-90,-48, 24, 81, 84, 33,-41,-87,-77,-15, 56, 90, 65, -2,-69,-90,-52, 20, 79, 86, 37,-37,-86,-79,-20, 52, 90, 69,  2,-65,-90,-56, 15, 77, 87, 41,-33,-84,-81,-24, 48, 90, 71,  7,-62,-91,-59, 11, 73, 88, 44,-28,-83 },
  { 82, 22,-54,-90,-61, 13, 78, 85, 31,-46,-90,-67,  4, 73, 88, 38,-38,-88,-73, -4, 67, 90, 46,-31,-85,-78,-13, 61, 90, 54,-22,-82,-82,-22, 54, 90, 61,-13,-78,-85,-31, 46, 90, 67, -4,-73,-88,-38, 38, 88, 73,  4,-67,-90,-46, 31, 85, 78, 13,-61,-90,-54, 22, 82 },
  { 81, 15,-62,-90,-44, 37, 88, 69, -7,-77,-84,-24, 56, 91, 52,-28,-86,-73, -2, 71, 87, 33,-48,-90,-59, 20, 83, 79, 11,-65,-90,-41, 41, 90, 65,-11,-79,-83,-20, 59, 90, 48,-33,-87,-71,  2, 73, 86, 28,-52,-91,-56, 24, 84, 77,  7,-69,-88,-37, 44, 90, 62,-15,-81 },
  { 80,  9,-70,-87,-25, 57, 90, 43,-43,-90,-57, 25, 87, 70, -9,-80,-80, -9, 70, 87, 25,-57,-90,-43, 43, 90, 57,-25,-87,-70,  9, 80, 80,  9,-70,-87,-25, 57, 90, 43,-43,-90,-57, 25, 87, 70, -9,-80,-80, -9, 70, 87, 25,-57,-90,-43, 43, 90, 57,-25,-87,-70,  9, 80 },
  { 79,  2,-77,-81, -7, 73, 83, 11,-71,-84,-15, 69, 86, 20,-65,-87,-24, 62, 88, 28,-59,-90,-33, 56, 90, 37,-52,-90,-41, 48, 91, 44,-44,-91,-48, 41, 90, 52,-37,-90,-56, 33, 90, 59,-28,-88,-62, 24, 87, 65,-20,-86,-69, 15, 84, 71,-11,-83,-73,  7, 81, 77, -2,-79 },
  { 78, -4,-82,-73, 13, 85, 67,-22,-88,-61, 31, 90, 54,-38,-90,-46, 46, 90, 38,-54,-90,-31, 61, 88, 22,-67,-85,-13, 73, 82,  4,-78,-78,  4, 82, 73,-13,-85,-67, 22, 88, 61,-31,-90,-54, 38, 90, 46,-46,-90,-38, 54, 90, 31,-61,-88,-22, 67, 85, 13,-73,-82, -4, 78 },
  { 77,-11,-86,-62, 33, 90, 44,-52,-90,-24, 69, 83,  2,-81,-71, 20, 88, 56,-41,-91,-37, 59, 87, 15,-73,-79,  7, 84, 65,-28,-90,-48, 48, 90, 28,-65,-84, -7, 79, 73,-15,-87,-59, 37, 91, 41,-56,-88,-20, 71, 81, -2,-83,-69, 24, 90, 52,-44,-90,-33, 62, 86, 11,-77 },
  { 75,-18,-89,-50, 50, 89, 18,-75,-75, 18, 89, 50,-50,-89,-18, 75, 75,-18,-89,-50, 50, 89, 18,-75,-75, 18, 89, 50,-50,-89,-18, 75, 75,-18,-89,-50, 50, 89, 18,-75,-75, 18, 89, 50,-50,-89,-18, 75, 75,-18,-89,-50, 50, 89, 18,-75,-75, 18, 89, 50,-50,-89,-18, 75 },
  { 73,-24,-90,-37, 65, 81,-11,-88,-48, 56, 86,  2,-84,-59, 44, 90, 15,-79,-69, 33, 91, 28,-71,-77, 20, 90, 41,-62,-83,  7, 87, 52,-52,-87, -7, 83, 62,-41,-90,-20, 77, 71,-28,-91,-33, 69, 79,-15,-90,-44, 59, 84, -2,-86,-56, 48, 88, 11,-81,-65, 37, 90, 24,-73 },
  { 73,-31,-90,-22, 78, 67,-38,-90,-13, 82, 61,-46,-88, -4, 85, 54,-54,-85,  4, 88, 46,-61,-82, 13, 90, 38,-67,-78, 22, 90, 31,-73,-73, 31, 90, 22,-78,-67, 38, 90, 13,-82,-61, 46, 88,  4,-85,-54, 54, 85, -4,-88,-46, 61, 82,-13,-90,-38, 67, 78,-22,-90,-31, 73 },
  { 71,-37,-90, -7, 86, 48,-62,-79, 24, 91, 20,-81,-59, 52, 84,-11,-90,-33, 73, 69,-41,-88, -2, 87, 44,-65,-77, 28, 90, 15,-83,-56, 56, 83,-15,-90,-28, 77, 65,-44,-87,  2, 88, 41,-69,-73, 33, 90, 11,-84,-52, 59, 81,-20,-91,-24, 79, 62,-48,-86,  7, 90, 37,-71 },
  { 70,-43,-87,  9, 90, 25,-80,-57, 57, 80,-25,-90, -9, 87, 43,-70,-70, 43, 87, -9,-90,-25, 80, 57,-57,-80, 25, 90,  9,-87,-43, 70, 70,-43,-87,  9, 90, 25,-80,-57, 57, 80,-25,-90, -9, 87, 43,-70,-70, 43, 87, -9,-90,-25, 80, 57,-57,-80, 25, 90,  9,-87,-43, 70 },
  { 69,-48,-83, 24, 90,  2,-90,-28, 81, 52,-65,-71, 44, 84,-20,-90, -7, 88, 33,-79,-56, 62, 73,-41,-86, 15, 91, 11,-87,-37, 77, 59,-59,-77, 37, 87,-11,-91,-15, 86, 41,-73,-62, 56, 79,-33,-88,  7, 90, 20,-84,-44, 71, 65,-52,-81, 28, 90, -2,-90,-24, 83, 48,-69 },
  { 67,-54,-78, 38, 85,-22,-90,  4, 90, 13,-88,-31, 82, 46,-73,-61, 61, 73,-46,-82, 31, 88,-13,-90, -4, 90, 22,-85,-38, 78, 54,-67,-67, 54, 78,-38,-85, 22, 90, -4,-90,-13, 88, 31,-82,-46, 73, 61,-61,-73, 46, 82,-31,-88, 13, 90,  4,-90,-22, 85, 38,-78,-54, 67 },
  { 65,-59,-71, 52, 77,-44,-81, 37, 84,-28,-87, 20, 90,-11,-90,  2, 91,  7,-90,-15, 88, 24,-86,-33, 83, 41,-79,-48, 73, 56,-69,-62, 62, 69,-56,-73, 48, 79,-41,-83, 33, 86,-24,-88, 15, 90, -7,-91, -2, 90, 11,-90,-20, 87, 28,-84,-37, 81, 44,-77,-52, 71, 59,-65 },
  { 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64, 64,-64,-64, 64 },
  { 62,-69,-56, 73, 48,-79,-41, 83, 33,-86,-24, 88, 15,-90, -7, 91, -2,-90, 11, 90,-20,-87, 28, 84,-37,-81, 44, 77,-52,-71, 59, 65,-65,-59, 71, 52,-77,-44, 81, 37,-84,-28, 87, 20,-90,-11, 90,  2,-91,  7, 90,-15,-88, 24, 86,-33,-83, 41, 79,-48,-73, 56, 69,-62 },
  { 61,-73,-46, 82, 31,-88,-13, 90, -4,-90, 22, 85,-38,-78, 54, 67,-67,-54, 78, 38,-85,-22, 90,  4,-90, 13, 88,-31,-82, 46, 73,-61,-61, 73, 46,-82,-31, 88, 13,-90,  4, 90,-22,-85, 38, 78,-54,-67, 67, 54,-78,-38, 85, 22,-90, -4, 90,-13,-88, 31, 82,-46,-73, 61 },
  { 59,-77,-37, 87, 11,-91, 15, 86,-41,-73, 62, 56,-79,-33, 88,  7,-90, 20, 84,-44,-71, 65, 52,-81,-28, 90,  2,-90, 24, 83,-48,-69, 69, 48,-83,-24, 90, -2,-90, 28, 81,-52,-65, 71, 44,-84,-20, 90, -7,-88, 33, 79,-56,-62, 73, 41,-86,-15, 91,-11,-87, 37, 77,-59 },
  { 57,-80,-25, 90, -9,-87, 43, 70,-70,-43, 87,  9,-90, 25, 80,-57,-57, 80, 25,-90,  9, 87,-43,-70, 70, 43,-87, -9, 90,-25,-80, 57, 57,-80,-25, 90, -9,-87, 43, 70,-70,-43, 87,  9,-90, 25, 80,-57,-57, 80, 25,-90,  9, 87,-43,-70, 70, 43,-87, -9, 90,-25,-80, 57 },
  { 56,-83,-15, 90,-28,-77, 65, 44,-87, -2, 88,-41,-69, 73, 33,-90, 11, 84,-52,-59, 81, 20,-91, 24, 79,-62,-48, 86,  7,-90, 37, 71,-71,-37, 90, -7,-86, 48, 62,-79,-24, 91,-20,-81, 59, 52,-84,-11, 90,-33,-73, 69, 41,-88,  2, 87,-44,-65, 77, 28,-90, 15, 83,-56 },
  { 54,-85, -4, 88,-46,-61, 82, 13,-90, 38, 67,-78,-22, 90,-31,-73, 73, 31,-90, 22, 78,-67,-38, 90,-13,-82, 61, 46,-88,  4, 85,-54,-54, 85,  4,-88, 46, 61,-82,-13, 90,-38,-67, 78, 22,-90, 31, 73,-73,-31, 90,-22,-78, 67, 38,-90, 13, 82,-61,-46, 88, -4,-85, 54 },
  { 52,-87,  7, 83,-62,-41, 90,-20,-77, 71, 28,-91, 33, 69,-79,-15, 90,-44,-59, 84,  2,-86, 56, 48,-88, 11, 81,-65,-37, 90,-24,-73, 73, 24,-90, 37, 65,-81,-11, 88,-48,-56, 86, -2,-84, 59, 44,-90, 15, 79,-69,-33, 91,-28,-71, 77, 20,-90, 41, 62,-83, -7, 87,-52 },
  { 50,-89, 18, 75,-75,-18, 89,-50,-50, 89,-18,-75, 75, 18,-89, 50, 50,-89, 18, 75,-75,-18, 89,-50,-50, 89,-18,-75, 75, 18,-89, 50, 50,-89, 18, 75,-75,-18, 89,-50,-50, 89,-18,-75, 75, 18,-89, 50, 50,-89, 18, 75,-75,-18, 89,-50,-50, 89,-18,-75, 75, 18,-89, 50 },
  { 48,-90, 28, 65,-84,  7, 79,-73,-15, 87,-59,-37, 91,-41,-56, 88,-20,-71, 81,  2,-83, 69, 24,-90, 52, 44,-90, 33, 62,-86, 11, 77,-77,-11, 86,-62,-33, 90,-44,-52, 90,-24,-69, 83, -2,-81, 71, 20,-88, 56, 41,-91, 37, 59,-87, 15, 73,-79, -7, 84,-65,-28, 90,-48 },
  { 46,-90, 38, 54,-90, 31, 61,-88, 22, 67,-85, 13, 73,-82,  4, 78,-78, -4, 82,-73,-13, 85,-67,-22, 88,-61,-31, 90,-54,-38, 90,-46,-46, 90,-38,-54, 90,-31,-61, 88,-22,-67, 85,-13,-73, 82, -4,-78, 78,  4,-82, 73, 13,-85, 67, 22,-88, 61, 31,-90, 54, 38,-90, 46 },
  { 44,-91, 48, 41,-90, 52, 37,-90, 56, 33,-90, 59, 28,-88, 62, 24,-87, 65, 20,-86, 69, 15,-84, 71, 11,-83, 73,  7,-81, 77,  2,-79, 79, -2,-77, 81, -7,-73, 83,-11,-71, 84,-15,-69, 86,-20,-65, 87,-24,-62, 88,-28,-59, 90,-33,-56, 90,-37,-52, 90,-41,-48, 91,-44 },
  { 43,-90, 57, 25,-87, 70,  9,-80, 80, -9,-70, 87,-25,-57, 90,-43,-43, 90,-57,-25, 87,-70, -9, 80,-80,  9, 70,-87, 25, 57,-90, 43, 43,-90, 57, 25,-87, 70,  9,-80, 80, -9,-70, 87,-25,-57, 90,-43,-43, 90,-57,-25, 87,-70, -9, 80,-80,  9, 70,-87, 25, 57,-90, 43 },
  { 41,-90, 65, 11,-79, 83,-20,-59, 90,-48,-33, 87,-71, -2, 73,-86, 28, 52,-91, 56, 24,-84, 77, -7,-69, 88,-37,-44, 90,-62,-15, 81,-81, 15, 62,-90, 44, 37,-88, 69,  7,-77, 84,-24,-56, 91,-52,-28, 86,-73,  2, 71,-87, 33, 48,-90, 59, 20,-83, 79,-11,-65, 90,-41 },
  { 38,-88, 73, -4,-67, 90,-46,-31, 85,-78, 13, 61,-90, 54, 22,-82, 82,-22,-54, 90,-61,-13, 78,-85, 31, 46,-90, 67,  4,-73, 88,-38,-38, 88,-73,  4, 67,-90, 46, 31,-85, 78,-13,-61, 90,-54,-22, 82,-82, 22, 54,-90, 61, 13,-78, 85,-31,-46, 90,-67, -4, 73,-88, 38 },
  { 37,-86, 79,-20,-52, 90,-69,  2, 65,-90, 56, 15,-77, 87,-41,-33, 84,-81, 24, 48,-90, 71, -7,-62, 91,-59,-11, 73,-88, 44, 28,-83, 83,-28,-44, 88,-73, 11, 59,-91, 62,  7,-71, 90,-48,-24, 81,-84, 33, 41,-87, 77,-15,-56, 90,-65, -2, 69,-90, 52, 20,-79, 86,-37 },
  { 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36, 36,-83, 83,-36,-36, 83,-83, 36 },
  { 33,-81, 87,-48,-15, 71,-90, 62, -2,-59, 90,-73, 20, 44,-86, 83,-37,-28, 79,-88, 52, 11,-69, 91,-65,  7, 56,-90, 77,-24,-41, 84,-84, 41, 24,-77, 90,-56, -7, 65,-91, 69,-11,-52, 88,-79, 28, 37,-83, 86,-44,-20, 73,-90, 59,  2,-62, 90,-71, 15, 48,-87, 81,-33 },
  { 31,-78, 90,-61,  4, 54,-88, 82,-38,-22, 73,-90, 67,-13,-46, 85,-85, 46, 13,-67, 90,-73, 22, 38,-82, 88,-54, -4, 61,-90, 78,-31,-31, 78,-90, 61, -4,-54, 88,-82, 38, 22,-73, 90,-67, 13, 46,-85, 85,-46,-13, 67,-90, 73,-22,-38, 82,-88, 54,  4,-61, 90,-78, 31 },
  { 28,-73, 91,-71, 24, 33,-77, 90,-69, 20, 37,-79, 90,-65, 15, 41,-81, 90,-62, 11, 44,-83, 88,-59,  7, 48,-84, 87,-56,  2, 52,-86, 86,-52, -2, 56,-87, 84,-48, -7, 59,-88, 83,-44,-11, 62,-90, 81,-41,-15, 65,-90, 79,-37,-20, 69,-90, 77,-33,-24, 71,-91, 73,-28 },
  { 25,-70, 90,-80, 43,  9,-57, 87,-87, 57, -9,-43, 80,-90, 70,-25,-25, 70,-90, 80,-43, -9, 57,-87, 87,-57,  9, 43,-80, 90,-70, 25, 25,-70, 90,-80, 43,  9,-57, 87,-87, 57, -9,-43, 80,-90, 70,-25,-25, 70,-90, 80,-43, -9, 57,-87, 87,-57,  9, 43,-80, 90,-70, 25 },
  { 24,-65, 88,-86, 59,-15,-33, 71,-90, 83,-52,  7, 41,-77, 91,-79, 44,  2,-48, 81,-90, 73,-37,-11, 56,-84, 90,-69, 28, 20,-62, 87,-87, 62,-20,-28, 69,-90, 84,-56, 11, 37,-73, 90,-81, 48, -2,-44, 79,-91, 77,-41, -7, 52,-83, 90,-71, 33, 15,-59, 86,-88, 65,-24 },
  { 22,-61, 85,-90, 73,-38, -4, 46,-78, 90,-82, 54,-13,-31, 67,-88, 88,-67, 31, 13,-54, 82,-90, 78,-46,  4, 38,-73, 90,-85, 61,-22,-22, 61,-85, 90,-73, 38,  4,-46, 78,-90, 82,-54, 13, 31,-67, 88,-88, 67,-31,-13, 54,-82, 90,-78, 46, -4,-38, 73,-90, 85,-61, 22 },
  { 20,-56, 81,-91, 83,-59, 24, 15,-52, 79,-90, 84,-62, 28, 11,-48, 77,-90, 86,-65, 33,  7,-44, 73,-90, 87,-69, 37,  2,-41, 71,-88, 88,-71, 41, -2,-37, 69,-87, 90,-73, 44, -7,-33, 65,-86, 90,-77, 48,-11,-28, 62,-84, 90,-79, 52,-15,-24, 59,-83, 91,-81, 56,-20 },
  { 18,-50, 75,-89, 89,-75, 50,-18,-18, 50,-75, 89,-89, 75,-50, 18, 18,-50, 75,-89, 89,-75, 50,-18,-18, 50,-75, 89,-89, 75,-50, 18, 18,-50, 75,-89, 89,-75, 50,-18,-18, 50,-75, 89,-89, 75,-50, 18, 18,-50, 75,-89, 89,-75, 50,-18,-18, 50,-75, 89,-89, 75,-50, 18 },
  { 15,-44, 69,-84, 91,-86, 71,-48, 20, 11,-41, 65,-83, 90,-87, 73,-52, 24,  7,-37, 62,-81, 90,-88, 77,-56, 28,  2,-33, 59,-79, 90,-90, 79,-59, 33, -2,-28, 56,-77, 88,-90, 81,-62, 37, -7,-24, 52,-73, 87,-90, 83,-65, 41,-11,-20, 48,-71, 86,-91, 84,-69, 44,-15 },
  { 13,-38, 61,-78, 88,-90, 85,-73, 54,-31,  4, 22,-46, 67,-82, 90,-90, 82,-67, 46,-22, -4, 31,-54, 73,-85, 90,-88, 78,-61, 38,-13,-13, 38,-61, 78,-88, 90,-85, 73,-54, 31, -4,-22, 46,-67, 82,-90, 90,-82, 67,-46, 22,  4,-31, 54,-73, 85,-90, 88,-78, 61,-38, 13 },
  { 11,-33, 52,-69, 81,-88, 91,-87, 79,-65, 48,-28,  7, 15,-37, 56,-71, 83,-90, 90,-86, 77,-62, 44,-24,  2, 20,-41, 59,-73, 84,-90, 90,-84, 73,-59, 41,-20, -2, 24,-44, 62,-77, 86,-90, 90,-83, 71,-56, 37,-15, -7, 28,-48, 65,-79, 87,-91, 88,-81, 69,-52, 33,-11 },
  {  9,-25, 43,-57, 70,-80, 87,-90, 90,-87, 80,-70, 57,-43, 25, -9, -9, 25,-43, 57,-70, 80,-87, 90,-90, 87,-80, 70,-57, 43,-25,  9,  9,-25, 43,-57, 70,-80, 87,-90, 90,-87, 80,-70, 57,-43, 25, -9, -9, 25,-43, 57,-70, 80,-87, 90,-90, 87,-80, 70,-57, 43,-25,  9 },
  {  7,-20, 33,-44, 56,-65, 73,-81, 86,-90, 91,-90, 87,-83, 77,-69, 59,-48, 37,-24, 11,  2,-15, 28,-41, 52,-62, 71,-79, 84,-88, 90,-90, 88,-84, 79,-71, 62,-52, 41,-28, 15, -2,-11, 24,-37, 48,-59, 69,-77, 83,-87, 90,-91, 90,-86, 81,-73, 65,-56, 44,-33, 20, -7 },
  {  4,-13, 22,-31, 38,-46, 54,-61, 67,-73, 78,-82, 85,-88, 90,-90, 90,-90, 88,-85, 82,-78, 73,-67, 61,-54, 46,-38, 31,-22, 13, -4, -4, 13,-22, 31,-38, 46,-54, 61,-67, 73,-78, 82,-85, 88,-90, 90,-90, 90,-88, 85,-82, 78,-73, 67,-61, 54,-46, 38,-31, 22,-13,  4 },
  {  2, -7, 11,-15, 20,-24, 28,-33, 37,-41, 44,-48, 52,-56, 59,-62, 65,-69, 71,-73, 77,-79, 81,-83, 84,-86, 87,-88, 90,-90, 90,-91, 91,-90, 90,-90, 88,-87, 86,-84, 83,-81, 79,-77, 73,-71, 69,-65, 62,-59, 56,-52, 48,-44, 41,-37, 33,-28, 24,-20, 15,-11,  7, -2 }
};

// ============================================================================
// Forward 1-D DCT-2 64-point  (butterfly decomposition)
// ============================================================================
static void forward_dct2_64(const TCoeff* src, TCoeff* dst, int shift)
{
    const int rnd = 1 << (shift - 1);

    TCoeff E[32], O[32];
    TCoeff EE[16], EO[16];
    TCoeff EEE[8], EEO[8];
    TCoeff EEEE[4], EEEO[4];
    TCoeff EEEEE[2], EEEEO[2];

    for (int k = 0; k < 32; ++k) { E[k] = src[k] + src[63-k]; O[k] = src[k] - src[63-k]; }
    for (int k = 0; k < 16; ++k) { EE[k] = E[k] + E[31-k]; EO[k] = E[k] - E[31-k]; }
    for (int k = 0; k <  8; ++k) { EEE[k] = EE[k] + EE[15-k]; EEO[k] = EE[k] - EE[15-k]; }
    for (int k = 0; k <  4; ++k) { EEEE[k] = EEE[k] + EEE[7-k]; EEEO[k] = EEE[k] - EEE[7-k]; }
    EEEEE[0] = EEEE[0] + EEEE[3]; EEEEO[0] = EEEE[0] - EEEE[3];
    EEEEE[1] = EEEE[1] + EEEE[2]; EEEEO[1] = EEEE[1] - EEEE[2];

    dst[ 0] = (idct64[ 0][0]*EEEEE[0] + idct64[ 0][1]*EEEEE[1] + rnd) >> shift;
    dst[16] = (idct64[16][0]*EEEEO[0] + idct64[16][1]*EEEEO[1] + rnd) >> shift;
    dst[32] = (idct64[32][0]*EEEEE[0] + idct64[32][1]*EEEEE[1] + rnd) >> shift;
    dst[48] = (idct64[48][0]*EEEEO[0] + idct64[48][1]*EEEEO[1] + rnd) >> shift;

    for (int k = 8; k < 64; k += 16)
        dst[k] = (idct64[k][0]*EEEO[0] + idct64[k][1]*EEEO[1] +
                  idct64[k][2]*EEEO[2] + idct64[k][3]*EEEO[3] + rnd) >> shift;

    for (int k = 4; k < 64; k += 8)
        dst[k] = (idct64[k][0]*EEO[0] + idct64[k][1]*EEO[1] +
                  idct64[k][2]*EEO[2] + idct64[k][3]*EEO[3] +
                  idct64[k][4]*EEO[4] + idct64[k][5]*EEO[5] +
                  idct64[k][6]*EEO[6] + idct64[k][7]*EEO[7] + rnd) >> shift;

    for (int k = 2; k < 64; k += 4)
        dst[k] = (idct64[k][ 0]*EO[ 0] + idct64[k][ 1]*EO[ 1] +
                  idct64[k][ 2]*EO[ 2] + idct64[k][ 3]*EO[ 3] +
                  idct64[k][ 4]*EO[ 4] + idct64[k][ 5]*EO[ 5] +
                  idct64[k][ 6]*EO[ 6] + idct64[k][ 7]*EO[ 7] +
                  idct64[k][ 8]*EO[ 8] + idct64[k][ 9]*EO[ 9] +
                  idct64[k][10]*EO[10] + idct64[k][11]*EO[11] +
                  idct64[k][12]*EO[12] + idct64[k][13]*EO[13] +
                  idct64[k][14]*EO[14] + idct64[k][15]*EO[15] + rnd) >> shift;

    for (int k = 1; k < 64; k += 2)
        dst[k] = (idct64[k][ 0]*O[ 0] + idct64[k][ 1]*O[ 1] +
                  idct64[k][ 2]*O[ 2] + idct64[k][ 3]*O[ 3] +
                  idct64[k][ 4]*O[ 4] + idct64[k][ 5]*O[ 5] +
                  idct64[k][ 6]*O[ 6] + idct64[k][ 7]*O[ 7] +
                  idct64[k][ 8]*O[ 8] + idct64[k][ 9]*O[ 9] +
                  idct64[k][10]*O[10] + idct64[k][11]*O[11] +
                  idct64[k][12]*O[12] + idct64[k][13]*O[13] +
                  idct64[k][14]*O[14] + idct64[k][15]*O[15] +
                  idct64[k][16]*O[16] + idct64[k][17]*O[17] +
                  idct64[k][18]*O[18] + idct64[k][19]*O[19] +
                  idct64[k][20]*O[20] + idct64[k][21]*O[21] +
                  idct64[k][22]*O[22] + idct64[k][23]*O[23] +
                  idct64[k][24]*O[24] + idct64[k][25]*O[25] +
                  idct64[k][26]*O[26] + idct64[k][27]*O[27] +
                  idct64[k][28]*O[28] + idct64[k][29]*O[29] +
                  idct64[k][30]*O[30] + idct64[k][31]*O[31] + rnd) >> shift;
}

// ============================================================================
// Encode one luma plane – HORIZONTAL PASS ONLY
// Each row is split into BLOCKS_PER_ROW windows of IDCT_BLOCK pixels.
// A forward DCT-2 is applied to each window; coefficients are packed as int16_t
// inside a 1024-bit word (one ap_uint<1024> per 64-pixel block).
// out[] must have BLOCKS_PER_FRAME entries.
// ============================================================================
static void encode_frame_1d(const uint8_t* luma, coeff_word_t* out)
{
    TCoeff row_in[IDCT_BLOCK], row_out[IDCT_BLOCK];

    for (int row = 0; row < HEIGHT; ++row) {
        for (int bx = 0; bx < BLOCKS_PER_ROW; ++bx) {
            const int b = row * BLOCKS_PER_ROW + bx;
            for (int c = 0; c < IDCT_BLOCK; ++c)
                row_in[c] = static_cast<TCoeff>(luma[row * WIDTH + bx * IDCT_BLOCK + c]);

            forward_dct2_64(row_in, row_out, SHIFT_FWD);

            coeff_word_t word = 0;
            for (int c = 0; c < IDCT_BLOCK; ++c) {
                ap_int<16> v = static_cast<int16_t>(row_out[c]);
                word.range((c + 1) * 16 - 1, c * 16) = v.range(15, 0);
            }
            out[b] = word;
        }
    }
}

// ============================================================================
// YUV planar 4:2:0 loading (luma only — chroma discarded)
// ============================================================================
struct YuvFrameStore {
    int width = 0, height = 0, frame_count = 0;
    std::vector<std::vector<uint8_t>> frames; // one luma plane per frame
};

static YuvFrameStore load_yuv_file(const std::string& path, int w, int h)
{
    const size_t luma_sz   = static_cast<size_t>(w) * h;
    const size_t chroma_sz = luma_sz / 2;
    const size_t frame_bytes = luma_sz + chroma_sz;

    std::ifstream f(path, std::ios::binary | std::ios::ate);
    if (!f) throw std::runtime_error("Cannot open YUV file: " + path);

    const size_t file_size = static_cast<size_t>(f.tellg());
    if (file_size < frame_bytes)
        throw std::runtime_error("YUV file too small for one frame");

    f.seekg(0, std::ios::beg);
    const int n_frames = static_cast<int>(file_size / frame_bytes);

    YuvFrameStore store;
    store.width       = w;
    store.height      = h;
    store.frame_count = n_frames;
    store.frames.resize(static_cast<size_t>(n_frames));

    for (int fi = 0; fi < n_frames; ++fi) {
        auto& luma = store.frames[static_cast<size_t>(fi)];
        luma.resize(luma_sz);
        f.read(reinterpret_cast<char*>(luma.data()),
               static_cast<std::streamsize>(luma_sz));
        f.seekg(static_cast<std::streamoff>(chroma_sz), std::ios::cur);
    }

    std::cout << "Loaded " << n_frames << " YUV frame(s) from " << path
              << " (" << w << "x" << h << ")" << std::endl;
    return store;
}

// ============================================================================
// Input mode
// ============================================================================
enum class InputMode { Random, Gradient, Video };
struct InputConfig { InputMode mode; std::string video_path; };

static InputConfig parse_input_config(const std::string& arg)
{
    if (arg == "random")   return { InputMode::Random,   {} };
    if (arg == "gradient") return { InputMode::Gradient, {} };
    const std::string prefix = "video:";
    if (arg.size() > prefix.size() && arg.substr(0, prefix.size()) == prefix)
        return { InputMode::Video, arg.substr(prefix.size()) };
    throw std::runtime_error("input must be: random | gradient | video:/path/to/file.yuv");
}

// Fill a WIDTH*HEIGHT luma buffer with the chosen input content.
static void fill_luma(std::vector<uint8_t>& luma, const InputConfig& cfg,
                      int iteration, const YuvFrameStore* store)
{
    luma.resize(static_cast<size_t>(WIDTH) * HEIGHT);
    switch (cfg.mode) {
    case InputMode::Random:
        for (auto& px : luma) px = static_cast<uint8_t>(std::rand() % 256);
        break;
    case InputMode::Gradient:
        for (int r = 0; r < HEIGHT; ++r)
            for (int c = 0; c < WIDTH; ++c)
                luma[static_cast<size_t>(r) * WIDTH + c] =
                    static_cast<uint8_t>((iteration + r + c) % 256);
        break;
    case InputMode::Video: {
        const int fi = iteration % store->frame_count;
        luma = store->frames[static_cast<size_t>(fi)];
        break;
    }
    }
}

// ============================================================================
// GStreamer FrameStreamer
// Accepts raw IDCT-output snapshots (one coeff_word_t per 64-pixel row-block)
// on the hot path and reassembles / pushes them on a background thread.
// ============================================================================
enum class StreamMode { Display, File };

class FrameStreamer {
public:
    FrameStreamer(int fps, StreamMode mode, const std::string& output_path)
        : fps_(fps), mode_(mode), output_path_(output_path) {}

    ~FrameStreamer() { stop(); }

    bool start()
    {
        if (!gst_is_initialized()) gst_init(nullptr, nullptr);

        const std::string caps_str =
            "video/x-raw,format=GRAY8,width=" + std::to_string(WIDTH) +
            ",height=" + std::to_string(HEIGHT) +
            ",framerate=" + std::to_string(fps_) + "/1";

        std::string pipeline_desc;
        if (mode_ == StreamMode::File) {
            pipeline_desc =
                "appsrc name=src format=time caps=" + caps_str +
                " ! videoconvert"
                " ! x264enc tune=zerolatency bitrate=4000"
                " ! mp4mux"
                " ! filesink location=" + output_path_;
        } else {
            pipeline_desc =
                "appsrc name=src format=time caps=" + caps_str +
                " ! videoconvert"
                " ! ximagesink sync=true";
        }

        GError* err = nullptr;
        pipeline_ = gst_parse_launch(pipeline_desc.c_str(), &err);
        if (err) {
            std::cerr << "[Streamer] Pipeline error: " << err->message << std::endl;
            g_error_free(err);
            return false;
        }

        appsrc_ = gst_bin_get_by_name(GST_BIN(pipeline_), "src");
        if (!appsrc_) {
            std::cerr << "[Streamer] Failed to get appsrc" << std::endl;
            gst_object_unref(pipeline_);
            pipeline_ = nullptr;
            return false;
        }

        gst_element_set_state(pipeline_, GST_STATE_PLAYING);
        running_ = true;
        worker_ = std::thread(&FrameStreamer::loop, this);

        if (mode_ == StreamMode::File)
            std::cout << "[Streamer] Recording to " << output_path_
                      << " (" << WIDTH << "x" << HEIGHT << " @ " << fps_ << " fps)\n";
        else
            std::cout << "[Streamer] Display started (" << WIDTH << "x" << HEIGHT
                      << " @ " << fps_ << " fps, X11)\n";
        return true;
    }

    // Fast path: snapshot the raw output buffer (BLOCKS_PER_FRAME words).
    void push_raw_output(const coeff_word_t* output_ptr)
    {
        if (!running_) return;
        std::vector<coeff_word_t> snap(output_ptr, output_ptr + BLOCKS_PER_FRAME);
        {
            std::lock_guard<std::mutex> lk(mu_);
            queue_.push(std::move(snap));
        }
        cv_.notify_one();
    }

    void drain()
    {
        std::unique_lock<std::mutex> lk(mu_);
        drain_cv_.wait(lk, [&]{ return queue_.empty(); });
    }

    void stop()
    {
        if (!running_) return;
        drain();
        {
            std::lock_guard<std::mutex> lk(mu_);
            running_ = false;
        }
        cv_.notify_all();
        if (worker_.joinable()) worker_.join();

        if (appsrc_) {
            gst_app_src_end_of_stream(GST_APP_SRC(appsrc_));
            GstBus* bus = gst_element_get_bus(pipeline_);
            if (bus) {
                gst_bus_timed_pop_filtered(bus, 30 * GST_SECOND, GST_MESSAGE_EOS);
                gst_object_unref(bus);
            }
            gst_object_unref(appsrc_);
            appsrc_ = nullptr;
        }
        if (pipeline_) {
            gst_element_set_state(pipeline_, GST_STATE_NULL);
            gst_object_unref(pipeline_);
            pipeline_ = nullptr;
        }
        std::cout << "[Streamer] Stopped\n";
    }

private:
    // Reassemble BLOCKS_PER_FRAME 1-D row-blocks into a GRAY8 frame.
    // Block b covers row (b / BLOCKS_PER_ROW) and pixel columns
    // [bx*64 .. bx*64+63] where bx = b % BLOCKS_PER_ROW.
    void reassemble(const std::vector<coeff_word_t>& raw, uint8_t* frame)
    {
        const auto* src = reinterpret_cast<const int16_t*>(raw.data());
        for (int b = 0; b < BLOCKS_PER_FRAME; ++b) {
            const int row = b / BLOCKS_PER_ROW;
            const int bx  = b % BLOCKS_PER_ROW;
            const int16_t* block = src + b * IDCT_BLOCK;
            for (int c = 0; c < IDCT_BLOCK; ++c) {
                int16_t val = block[c];
                frame[static_cast<size_t>(row) * WIDTH + bx * IDCT_BLOCK + c] =
                    val < 0 ? uint8_t{0} : val > 255 ? uint8_t{255}
                                                      : static_cast<uint8_t>(val);
            }
        }
    }

    void loop()
    {
        const guint64 frame_dur = GST_SECOND / static_cast<guint64>(fps_);
        guint64 pts = 0;
        std::vector<uint8_t> frame_buf(static_cast<size_t>(WIDTH) * HEIGHT);

        while (true) {
            std::vector<coeff_word_t> raw;
            {
                std::unique_lock<std::mutex> lk(mu_);
                cv_.wait(lk, [&]{ return !queue_.empty() || !running_; });
                if (!running_ && queue_.empty()) break;
                raw = std::move(queue_.front());
                queue_.pop();
                if (queue_.empty()) drain_cv_.notify_all();
            }

            reassemble(raw, frame_buf.data());

            const gsize sz = static_cast<gsize>(WIDTH) * HEIGHT;
            GstBuffer* buf = gst_buffer_new_allocate(nullptr, sz, nullptr);
            gst_buffer_fill(buf, 0, frame_buf.data(), sz);
            GST_BUFFER_PTS(buf)      = pts;
            GST_BUFFER_DURATION(buf) = frame_dur;
            pts += frame_dur;

            GstFlowReturn ret = gst_app_src_push_buffer(GST_APP_SRC(appsrc_), buf);
            if (ret != GST_FLOW_OK) break;
        }
    }

    int         fps_;
    StreamMode  mode_;
    std::string output_path_;

    GstElement* pipeline_ = nullptr;
    GstElement* appsrc_   = nullptr;

    std::thread             worker_;
    std::mutex              mu_;
    std::condition_variable cv_, drain_cv_;
    std::queue<std::vector<coeff_word_t>> queue_;
    bool running_ = false;
};

// ============================================================================
// Utility helpers
// ============================================================================
static std::unique_ptr<indicators::BlockProgressBar>
make_progress_bar(const std::string& label, int total)
{
    using namespace indicators;
    return std::make_unique<BlockProgressBar>(
        option::BarWidth{40},
        option::PrefixText{label},
        option::MaxProgress{static_cast<size_t>(total)},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::ForegroundColor{Color::cyan}
    );
}

static std::vector<char> load_xclbin(const std::string& path)
{
    std::ifstream stream(path, std::ios::binary | std::ios::ate);
    if (!stream) throw std::runtime_error("Failed to open xclbin: " + path);
    std::streamsize size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> buf(size);
    if (!stream.read(buf.data(), size))
        throw std::runtime_error("Failed to read xclbin: " + path);
    return buf;
}

static size_t align_to_4096(size_t bytes)
{
    constexpr size_t a = 4096;
    return (bytes % a == 0) ? bytes : a * ((bytes + a - 1) / a);
}

static void print_stats(const std::string& label, int frames, double elapsed)
{
    std::cout << label << "\n"
              << "  Frames processed : " << frames << "\n"
              << "  Total time       : " << elapsed << " s\n"
              << "  Avg per frame    : " << elapsed / std::max(1, frames) << " s\n"
              << "  FPS (1920x1080)  : "
              << static_cast<double>(frames) / elapsed << "\n";
}

// ============================================================================
// Kernel warmup: a few random-data executions to settle clock/caches
// ============================================================================
static void run_kernel_warmup(xrt::kernel& kernel,
                              xrt::bo& in_bo, xrt::bo& out_bo,
                              coeff_word_t* in_ptr)
{
    std::vector<coeff_word_t> tmp(BLOCKS_PER_FRAME);
    for (auto& w : tmp) {
        w = 0;
        for (int c = 0; c < IDCT_BLOCK; ++c) {
            ap_int<16> v = static_cast<int16_t>((std::rand() % 256) - 128);
            w.range((c + 1) * 16 - 1, c * 16) = v.range(15, 0);
        }
    }
    std::copy(tmp.begin(), tmp.end(), in_ptr);
    in_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);
    for (int i = 0; i < 5; ++i) {
        auto run = kernel(in_bo, out_bo, IDCT_BLOCK, BLOCKS_PER_FRAME,
                          SHIFT_INV, OUT_MIN, OUT_MAX);
        run.wait();
    }
    std::cout << "Warmup complete.\n";
}

// ============================================================================
// Scenario 1
// Pre-sync a fixed encoded frame to FPGA DRAM once, then execute the IDCT
// kernel for every requested frame in a loop.  Input never changes — this
// isolates kernel + output-transfer cost.
// ============================================================================
static void run_scenario_1(xrt::kernel& kernel,
                            xrt::bo& in_bo, xrt::bo& out_bo,
                            coeff_word_t* in_ptr, coeff_word_t* out_ptr,
                            const std::vector<coeff_word_t>& fixed_encoded,
                            int total_frames,
                            FrameStreamer* streamer)
{
    std::cout << "\n[Scenario 1] Pre-sync fixed frame, execute " << total_frames
              << " times in loop\n";

    std::copy(fixed_encoded.begin(), fixed_encoded.end(), in_ptr);
    in_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);   // single bulk upload

    auto bar = make_progress_bar("[Scenario 1] ", total_frames);
    indicators::show_console_cursor(false);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < total_frames; ++it) {
        auto run = kernel(in_bo, out_bo, IDCT_BLOCK, BLOCKS_PER_FRAME,
                          SHIFT_INV, OUT_MIN, OUT_MAX);
        run.wait();
        out_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        //if (streamer) streamer->push_raw_output(out_ptr);
        bar->tick();
    }

    auto end = std::chrono::high_resolution_clock::now();
    bar->mark_as_completed();
    indicators::show_console_cursor(true);

    print_stats("[Scenario 1]",
                total_frames,
                std::chrono::duration<double>(end - start).count());
}

// ============================================================================
// Scenario 2
// Per-frame: copy encoded data → sync to FPGA → run kernel → sync from FPGA
// → stream.  Maximally simple but data movement is serialised with compute.
// ============================================================================
static void run_scenario_2(xrt::kernel& kernel,
                            xrt::bo& in_bo, xrt::bo& out_bo,
                            coeff_word_t* in_ptr, coeff_word_t* out_ptr,
                            const std::vector<std::vector<coeff_word_t>>& frame_bank,
                            int total_frames,
                            FrameStreamer* streamer)
{
    std::cout << "\n[Scenario 2] Per-frame copy+sync+execute+sync+stream\n";

    auto bar = make_progress_bar("[Scenario 2] ", total_frames);
    indicators::show_console_cursor(false);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < total_frames; ++it) {
        const auto& enc = frame_bank[static_cast<size_t>(it) % frame_bank.size()];
        std::copy(enc.begin(), enc.end(), in_ptr);
        in_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(in_bo, out_bo, IDCT_BLOCK, BLOCKS_PER_FRAME,
                          SHIFT_INV, OUT_MIN, OUT_MAX);
        run.wait();

        out_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        if (streamer) streamer->push_raw_output(out_ptr);
        bar->tick();
    }

    auto end = std::chrono::high_resolution_clock::now();
    bar->mark_as_completed();
    indicators::show_console_cursor(true);

    print_stats("[Scenario 2]",
                total_frames,
                std::chrono::duration<double>(end - start).count());
}

// ============================================================================
// Scenario 3
// Double-buffered ping-pong: while the kernel processes frame N, the host
// copies + syncs frame N+1, hiding most of the data-transfer latency.
// ============================================================================
static void run_scenario_3(xrt::kernel& kernel, xrt::device& device,
                            int g_in, int g_out,
                            const std::vector<std::vector<coeff_word_t>>& frame_bank,
                            int total_frames,
                            FrameStreamer* streamer)
{
    std::cout << "\n[Scenario 3] Double-buffer ping-pong\n";

    const size_t input_bytes  = align_to_4096(BLOCKS_PER_FRAME * sizeof(coeff_word_t));
    const size_t output_bytes = input_bytes;  // same word type and count

    std::array<xrt::bo, 2> in_bo = {
        xrt::bo(device, input_bytes,  xrt::bo::flags::normal, g_in),
        xrt::bo(device, input_bytes,  xrt::bo::flags::normal, g_in)
    };
    std::array<xrt::bo, 2> out_bo = {
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out),
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out)
    };

    std::array<coeff_word_t*, 2> in_ptr  = {
        in_bo[0].map<coeff_word_t*>(),
        in_bo[1].map<coeff_word_t*>()
    };
    std::array<coeff_word_t*, 2> out_ptr = {
        out_bo[0].map<coeff_word_t*>(),
        out_bo[1].map<coeff_word_t*>()
    };

    auto bar = make_progress_bar("[Scenario 3] ", total_frames);
    indicators::show_console_cursor(false);

    int cur = 0, nxt = 1;

    // Prime the first buffer
    {
        const auto& enc0 = frame_bank[0];
        std::copy(enc0.begin(), enc0.end(), in_ptr[cur]);
        in_bo[cur].sync(XCL_BO_SYNC_BO_TO_DEVICE);
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto run = kernel(in_bo[cur], out_bo[cur], IDCT_BLOCK, BLOCKS_PER_FRAME,
                      SHIFT_INV, OUT_MIN, OUT_MAX);

    for (int it = 1; it < total_frames; ++it) {
        // CPU-side copy to host shadow buffer while kernel runs — no PCIe, no DDR contention.
        const auto& enc_nxt = frame_bank[static_cast<size_t>(it) % frame_bank.size()];
        std::copy(enc_nxt.begin(), enc_nxt.end(), in_ptr[nxt]);

        // Wait for current kernel, then do DMA operations with no DDR bank contention.
        run.wait();
        out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        in_bo[nxt].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        // Launch next kernel immediately, then do bookkeeping.
        run = kernel(in_bo[nxt], out_bo[nxt], IDCT_BLOCK, BLOCKS_PER_FRAME,
                     SHIFT_INV, OUT_MIN, OUT_MAX);
        std::swap(cur, nxt);

        if (streamer) streamer->push_raw_output(out_ptr[nxt]); // nxt is now the just-completed buffer
        bar->tick();
    }

    // Flush the last in-flight frame
    run.wait();
    out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    if (streamer) streamer->push_raw_output(out_ptr[cur]);
    bar->tick();

    auto end = std::chrono::high_resolution_clock::now();
    bar->mark_as_completed();
    indicators::show_console_cursor(true);

    print_stats("[Scenario 3]",
                total_frames,
                std::chrono::duration<double>(end - start).count());
}

} // namespace

// ============================================================================
// main
// ============================================================================
int main(int argc, char** argv)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (argc < 4 || argc > 5) {
        std::cout << "Usage: " << argv[0]
                  << " <xclbin> <total_frames>"
                     " <input:random|gradient|video:/path/to/file.yuv>"
                     " [output:display|mp4:/path/to/output.mp4]\n";
        return EXIT_FAILURE;
    }

    const std::string xclbin_path = argv[1];
    const int total_frames        = std::stoi(argv[2]);
    const std::string input_arg   = argv[3];
    const std::string output_arg  = (argc == 5) ? argv[4] : "display";

    if (total_frames <= 0) {
        std::cerr << "total_frames must be > 0\n";
        return EXIT_FAILURE;
    }

    try {
        const InputConfig input_cfg = parse_input_config(input_arg);

        std::unique_ptr<YuvFrameStore> yuv_store;
        if (input_cfg.mode == InputMode::Video)
            yuv_store = std::make_unique<YuvFrameStore>(
                load_yuv_file(input_cfg.video_path, WIDTH, HEIGHT));

        std::cout << "Resolution    : " << WIDTH << "x" << HEIGHT << "\n"
                  << "Blocks/row    : " << BLOCKS_PER_ROW << "\n"
                  << "Blocks/frame  : " << BLOCKS_PER_FRAME << "\n"
                  << "Total frames  : " << total_frames << "\n"
                  << "Forward shift : " << SHIFT_FWD << "\n"
                  << "Inverse shift : " << SHIFT_INV << "\n"
                  << "Output clip   : [" << OUT_MIN << ", " << OUT_MAX << "]\n\n";

        // ------------------------------------------------------------------
        // Step 1: Encode all frames (1D horizontal DCT only)
        // ------------------------------------------------------------------
        std::cout << "Encoding " << total_frames << " frame(s) with 1D horizontal DCT-64...\n";

        const int encode_count = (input_cfg.mode == InputMode::Video && yuv_store)
                                 ? yuv_store->frame_count
                                 : total_frames;

        std::vector<std::vector<coeff_word_t>> frame_bank(
            static_cast<size_t>(encode_count),
            std::vector<coeff_word_t>(BLOCKS_PER_FRAME));

        {
            const unsigned int nthreads = 16; /* std::min(
                static_cast<unsigned int>(encode_count),
                std::thread::hardware_concurrency()); */
            std::cout << "Using " << nthreads << " thread(s).\n";

            auto bar = make_progress_bar("Encoding ", encode_count);
            indicators::show_console_cursor(false);

            std::atomic<int> next_fi{0};
            std::mutex        bar_mu;

            std::vector<std::thread> threads;
            threads.reserve(nthreads);

            for (unsigned int t = 0; t < nthreads; ++t) {
                threads.emplace_back([&]() {
                    std::vector<uint8_t> luma; // thread-local input buffer
                    while (true) {
                        const int fi = next_fi.fetch_add(1, std::memory_order_relaxed);
                        if (fi >= encode_count) break;
                        fill_luma(luma, input_cfg, fi, yuv_store.get());
                        encode_frame_1d(luma.data(),
                                        frame_bank[static_cast<size_t>(fi)].data());
                        std::lock_guard<std::mutex> lk(bar_mu);
                        bar->tick();
                    }
                });
            }
            for (auto& th : threads) th.join();

            bar->mark_as_completed();
            indicators::show_console_cursor(true);
        }
        std::cout << "Encoding done. " << encode_count << " frame(s) stored.\n\n";

        // ------------------------------------------------------------------
        // Step 2: FPGA setup
        // ------------------------------------------------------------------
        auto device      = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin      = xrt::xclbin(xclbin_data);
        auto uuid        = device.load_xclbin(xclbin);
        auto kernel      = xrt::kernel(device, uuid, "IDCT2");
        std::cout << "xclbin loaded successfully.\n";

        const size_t frame_bytes  = align_to_4096(BLOCKS_PER_FRAME * sizeof(coeff_word_t));

        auto g_in  = kernel.group_id(0);
        auto g_out = kernel.group_id(1);

        xrt::bo in_bo (device, frame_bytes, xrt::bo::flags::normal, g_in);
        xrt::bo out_bo(device, frame_bytes, xrt::bo::flags::normal, g_out);

        coeff_word_t* in_ptr  = in_bo.map<coeff_word_t*>();
        coeff_word_t* out_ptr = out_bo.map<coeff_word_t*>();

        run_kernel_warmup(kernel, in_bo, out_bo, in_ptr);

        // ------------------------------------------------------------------
        // Helper: create and start a fresh FrameStreamer.
        // For mp4 output the caller supplies a suffix ("_s2", "_s3") that is
        // inserted before the file extension so each scenario writes its own
        // file.  Returns nullptr if GStreamer fails to start.
        // ------------------------------------------------------------------
        auto make_streamer = [&](const std::string& file_suffix)
            -> std::unique_ptr<FrameStreamer>
        {
            StreamMode  smode = StreamMode::Display;
            std::string mp4_path;
            const std::string mp4_prefix = "mp4:";
            if (output_arg.size() > mp4_prefix.size() &&
                output_arg.substr(0, mp4_prefix.size()) == mp4_prefix) {
                smode = StreamMode::File;
                std::string base = output_arg.substr(mp4_prefix.size());
                const size_t dot = base.rfind('.');
                mp4_path = (dot != std::string::npos)
                           ? base.substr(0, dot) + file_suffix + base.substr(dot)
                           : base + file_suffix;
            }
            auto s = std::make_unique<FrameStreamer>(24, smode, mp4_path);
            if (!s->start()) {
                std::cerr << "Warning: could not start GStreamer streamer.\n";
                return nullptr;
            }
            return s;
        };

        // ------------------------------------------------------------------
        // Step 3 & 4: Run the three pipeline scenarios
        //
        // Scenario 1 is a pure throughput benchmark (fixed input, no streaming).
        // Scenarios 2 and 3 each get their own fresh streamer so that frames
        // from one scenario never mix with or delay the other.
        // ------------------------------------------------------------------

        // Scenario 1 – no streaming: same frame repeated, only measures kernel+DMA
        run_scenario_1(kernel, in_bo, out_bo, in_ptr, out_ptr,
                       frame_bank[0],
                       total_frames,
                       nullptr);

        // Scenario 2 – per-frame, fresh streamer
        {
            auto s2 = make_streamer("_s2");
            run_scenario_2(kernel, in_bo, out_bo, in_ptr, out_ptr,
                           frame_bank,
                           total_frames,
                           s2.get());
            if (s2) s2->stop();
        }

        // Scenario 3 – double-buffer, fresh streamer
        {
            auto s3 = make_streamer("_s3");
            run_scenario_3(kernel, device, g_in, g_out,
                           frame_bank,
                           total_frames,
                           s3.get());
            if (s3) s3->stop();
        }

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
