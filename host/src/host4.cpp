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
#include <mutex>
#include <numeric>
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

static std::unique_ptr<indicators::BlockProgressBar> make_progress_bar(const std::string& label, int total) {
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
namespace {

constexpr int REF_BLOCK_H = 15;
constexpr int REF_BLOCK_W = 15;
constexpr int BLOCK_SIZE = 8;
constexpr int NTAPS = 8;
constexpr int NUM_FRAC_POS = 16;
constexpr int FILTER_PREC = 6;
constexpr int BIT_DEPTH = 8;
constexpr int INTERNAL_PREC = 14;
constexpr int OUT_ROWS_PER_BLOCK = BLOCK_SIZE;

using input_word_t = ap_uint<256>;
using output_word_t = ap_uint<128>;

static const int16_t LUMA_FILTER[NUM_FRAC_POS][NTAPS] = {
    {  0,  0,   0, 64,  0,   0,  0,  0 },
    {  0,  1,  -3, 63,  4,  -2,  1,  0 },
    { -1,  2,  -5, 62,  8,  -3,  1,  0 },
    { -1,  3,  -8, 60, 13,  -4,  1,  0 },
    { -1,  4, -10, 58, 17,  -5,  1,  0 },
    { -1,  4, -11, 52, 26,  -8,  3, -1 },
    { -1,  3,  -9, 47, 31, -10,  4, -1 },
    { -1,  4, -11, 45, 34, -10,  4, -1 },
    { -1,  4, -11, 40, 40, -11,  4, -1 },
    { -1,  4, -10, 34, 45, -11,  4, -1 },
    { -1,  4, -10, 31, 47,  -9,  3, -1 },
    { -1,  3,  -8, 26, 52, -11,  4, -1 },
    {  0,  1,  -5, 17, 58, -10,  4, -1 },
    {  0,  1,  -4, 13, 60,  -8,  3, -1 },
    {  0,  1,  -3,  8, 62,  -5,  2, -1 },
    {  0,  1,  -2,  4, 63,  -3,  1,  0 },
};

struct FrameConfig {
    int width;
    int height;
    int blocks_w;
    int blocks_h;
    int block_count;
};

struct RunConfig {
    int total_frames;
    int frames_per_exec;
    int exec_count;
    int blocks_per_exec;
};

struct YuvFrameStore {
    int frame_width  = 0;
    int frame_height = 0;
    int frame_count  = 0;
    std::vector<std::vector<uint16_t>> frames;
};

// ---------------------------------------------------------------------------
// GStreamer frame streamer — runs pipeline on a background thread.
// Supports two modes:
//   display  — opens an X11 window (via ssh -X)
//   file     — encodes to mp4 file
//
// The caller pushes raw output_word_t snapshots via push_raw_output().
// The worker thread handles reassembly + GStreamer push so the HW loop
// only pays for a ~1 MB memcpy instead of full-frame reassembly.
// ---------------------------------------------------------------------------
enum class StreamMode { Display, File };

class FrameStreamer {
public:
    FrameStreamer(int width, int height,
                  int block_count, int blocks_w,
                  int fps = 24,
                  StreamMode mode = StreamMode::Display,
                  const std::string& output_path = "")
        : width_(width), height_(height),
          block_count_(block_count), blocks_w_(blocks_w),
          fps_(fps), mode_(mode), output_path_(output_path),
          raw_words_per_frame_(static_cast<size_t>(block_count) * OUT_ROWS_PER_BLOCK) {}

    ~FrameStreamer() { stop(); }

    bool start() {
        if (!gst_is_initialized()) {
            gst_init(nullptr, nullptr);
        }

        std::string caps_str =
            "video/x-raw,format=GRAY8,width=" + std::to_string(width_) +
            ",height=" + std::to_string(height_) +
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
            std::cerr << "[Streamer] Failed to get appsrc element" << std::endl;
            gst_object_unref(pipeline_);
            pipeline_ = nullptr;
            return false;
        }

        gst_element_set_state(pipeline_, GST_STATE_PLAYING);
        running_ = true;
        worker_ = std::thread(&FrameStreamer::loop, this);

        if (mode_ == StreamMode::File)
            std::cout << "[Streamer] Recording to " << output_path_
                      << " (" << width_ << "x" << height_
                      << " @ " << fps_ << " fps)" << std::endl;
        else
            std::cout << "[Streamer] Display started (" << width_ << "x" << height_
                      << " @ " << fps_ << " fps, X11)" << std::endl;
        return true;
    }

    // Fast path for the HW loop: snapshot raw output words (~1 MB memcpy).
    // Reassembly happens on the worker thread.
    void push_raw_output(const output_word_t* output_ptr) {
        if (!running_) return;
        // Copy raw output into a vector (fast contiguous memcpy)
        std::vector<output_word_t> snapshot(output_ptr, output_ptr + raw_words_per_frame_);
        {
            std::lock_guard<std::mutex> lk(mu_);
            raw_queue_.push(std::move(snapshot));
        }
        cv_.notify_one();
    }

    // Wait until all queued frames have been pushed to the pipeline.
    void drain() {
        std::unique_lock<std::mutex> lk(mu_);
        drain_cv_.wait(lk, [&]{ return raw_queue_.empty(); });
    }

    void stop() {
        if (!running_) return;

        // Drain remaining frames before shutting down
        drain();

        {
            std::lock_guard<std::mutex> lk(mu_);
            running_ = false;
        }
        cv_.notify_all();
        if (worker_.joinable()) worker_.join();

        if (appsrc_) {
            gst_app_src_end_of_stream(GST_APP_SRC(appsrc_));
            // Wait for EOS — essential for mp4 to finalize the file
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
        std::cout << "[Streamer] Stopped" << std::endl;
    }

private:
    // Reassemble output blocks into a grayscale frame (runs on worker thread).
    void reassemble(const std::vector<output_word_t>& raw, uint8_t* frame) {
        std::memset(frame, 0, static_cast<size_t>(width_) * height_);
        for (int b = 0; b < block_count_; ++b) {
            const int origin_x = (b % blocks_w_) * BLOCK_SIZE;
            const int origin_y = (b / blocks_w_) * BLOCK_SIZE;
            const size_t out_base = static_cast<size_t>(b) * OUT_ROWS_PER_BLOCK;
            for (int r = 0; r < BLOCK_SIZE; ++r) {
                const int fy = origin_y + r;
                if (fy >= height_) break;
                const output_word_t word = raw[out_base + r];
                for (int c = 0; c < BLOCK_SIZE; ++c) {
                    const int fx = origin_x + c;
                    if (fx >= width_) break;
                    uint16_t val = static_cast<uint16_t>(
                        word.range((c + 1) * 16 - 1, c * 16));
                    frame[fy * width_ + fx] =
                        static_cast<uint8_t>(std::min<uint16_t>(val, 255));
                }
            }
        }
    }

    void loop() {
        const guint64 frame_dur = GST_SECOND / static_cast<guint64>(fps_);
        guint64 pts = 0;
        // Pre-allocate frame buffer — reused every iteration
        std::vector<uint8_t> frame_buf(static_cast<size_t>(width_) * height_);

        while (true) {
            std::vector<output_word_t> raw;
            {
                std::unique_lock<std::mutex> lk(mu_);
                cv_.wait(lk, [&]{ return !raw_queue_.empty() || !running_; });
                if (!running_ && raw_queue_.empty()) break;
                raw = std::move(raw_queue_.front());
                raw_queue_.pop();
                if (raw_queue_.empty()) drain_cv_.notify_all();
            }

            // Reassemble on this thread (off the HW hot path)
            reassemble(raw, frame_buf.data());

            const gsize sz = static_cast<gsize>(width_) * height_;
            GstBuffer* buf = gst_buffer_new_allocate(nullptr, sz, nullptr);
            gst_buffer_fill(buf, 0, frame_buf.data(), sz);
            GST_BUFFER_PTS(buf) = pts;
            GST_BUFFER_DURATION(buf) = frame_dur;
            pts += frame_dur;

            GstFlowReturn ret = gst_app_src_push_buffer(GST_APP_SRC(appsrc_), buf);
            if (ret != GST_FLOW_OK) break;
        }
    }

    int width_, height_;
    int block_count_, blocks_w_;
    int fps_;
    StreamMode  mode_;
    std::string output_path_;
    size_t      raw_words_per_frame_;

    GstElement* pipeline_ = nullptr;
    GstElement* appsrc_   = nullptr;

    std::thread             worker_;
    std::mutex              mu_;
    std::condition_variable cv_;
    std::condition_variable drain_cv_;
    std::queue<std::vector<output_word_t>> raw_queue_;
    bool                    running_ = false;
};

static std::vector<char> load_xclbin(const std::string& xclbin_path) {
    std::ifstream stream(xclbin_path, std::ios::binary | std::ios::ate);
    if (!stream) {
        throw std::runtime_error("Failed to open xclbin: " + xclbin_path);
    }
    std::streamsize size = stream.tellg();
    stream.seekg(0, std::ios::beg);
    std::vector<char> buffer(size);
    if (!stream.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read xclbin: " + xclbin_path);
    }
    return buffer;
}

static size_t align_to_4096(size_t bytes) {
    constexpr size_t align = 4096;
    return (bytes % align == 0) ? bytes : align * ((bytes + align - 1) / align);
}

static uint8_t random_binary_frac() {
    return static_cast<uint8_t>(std::rand() & 1);
}

static uint16_t random_pixel() {
    return static_cast<uint16_t>(std::rand() % 256);
}

static FrameConfig make_frame_config(const std::string& resolution) {
    if (resolution == "fhd" || resolution == "1080p") {
        const int width = 1920;
        const int height = 1080;
        const int blocks_w = (width + REF_BLOCK_W - 1) / REF_BLOCK_W;
        const int blocks_h = (height + REF_BLOCK_H - 1) / REF_BLOCK_H;
        return {width, height, blocks_w, blocks_h, blocks_w * blocks_h};
    }
    if (resolution == "4k" || resolution == "2160p") {
        const int width = 3840;
        const int height = 2160;
        const int blocks_w = (width + REF_BLOCK_W - 1) / REF_BLOCK_W;
        const int blocks_h = (height + REF_BLOCK_H - 1) / REF_BLOCK_H;
        return {width, height, blocks_w, blocks_h, blocks_w * blocks_h};
    }
    throw std::runtime_error("Resolution must be one of: fhd, 1080p, 4k, 2160p");
}

static void fill_binary_frac_bank(
    std::vector<uint8_t>& frac_x_bank,
    std::vector<uint8_t>& frac_y_bank,
    int iterations
) {
    for (int it = 0; it < iterations; ++it) {
        const auto idx = static_cast<size_t>(it);
        frac_x_bank[idx] = random_binary_frac();
        frac_y_bank[idx] = random_binary_frac();
    }
}

static void fill_random_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count
) {
    const size_t words_per_frame = static_cast<size_t>(block_count) * REF_BLOCK_H;
    frame_input.resize(words_per_frame);

    for (int b = 0; b < block_count; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t row = 0;
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                row.range((c + 1) * 16 - 1, c * 16) = random_pixel();
            }
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = row;
        }
    }
}

static void fill_gradient_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count,
    int exec_iteration
) {
    const size_t words_per_frame = static_cast<size_t>(block_count) * REF_BLOCK_H;
    frame_input.resize(words_per_frame);
    for (int b = 0; b < block_count; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t row = 0;
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                row.range((c + 1) * 16 - 1, c * 16) =
                    static_cast<uint16_t>((exec_iteration + r + c) % 256);
            }
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = row;
        }
    }
}

static void fill_video_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count,
    int exec_iteration,
    const YuvFrameStore& store,
    int blocks_w
) {
    const size_t words_per_frame = static_cast<size_t>(block_count) * REF_BLOCK_H;
    frame_input.resize(words_per_frame);
    const int fi = exec_iteration % store.frame_count;
    const std::vector<uint16_t>& luma = store.frames[static_cast<size_t>(fi)];
    const int W = store.frame_width;
    for (int b = 0; b < block_count; ++b) {
        const int origin_x = (b % blocks_w) * REF_BLOCK_W;
        const int origin_y = (b / blocks_w) * REF_BLOCK_H;
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t row = 0;
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                const int px = (origin_y + r) * W + (origin_x + c);
                row.range((c + 1) * 16 - 1, c * 16) =
                    (px < static_cast<int>(luma.size()))
                    ? luma[static_cast<size_t>(px)]
                    : uint16_t{0};
            }
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = row;
        }
    }
}

enum class InputMode { Random, Gradient, Video };

struct InputConfig {
    InputMode   mode;
    std::string video_path;
};

static InputConfig parse_input_config(const std::string& arg) {
    if (arg == "random")   return { InputMode::Random,   {} };
    if (arg == "gradient") return { InputMode::Gradient, {} };
    const std::string prefix = "video:";
    if (arg.size() > prefix.size() && arg.substr(0, prefix.size()) == prefix)
        return { InputMode::Video, arg.substr(prefix.size()) };
    throw std::runtime_error("input must be: random | gradient | video:/path/to/file.yuv");
}


static YuvFrameStore load_yuv_file(const std::string& path, int width, int height) {
    const size_t luma_pixels   = static_cast<size_t>(width) * height;
    const size_t chroma_pixels = luma_pixels / 2;
    const size_t frame_bytes   = luma_pixels + chroma_pixels;
    std::ifstream f(path, std::ios::binary | std::ios::ate);
    if (!f) throw std::runtime_error("Cannot open YUV file: " + path);
    const auto file_size = static_cast<size_t>(f.tellg());
    if (file_size < frame_bytes)
        throw std::runtime_error("YUV file too small for one frame at this resolution");
    f.seekg(0, std::ios::beg);
    const int n_frames = static_cast<int>(file_size / frame_bytes);
    std::vector<uint8_t> buf(luma_pixels);
    YuvFrameStore store;
    store.frame_width  = width;
    store.frame_height = height;
    store.frame_count  = n_frames;
    store.frames.resize(static_cast<size_t>(n_frames));
    for (int fi = 0; fi < n_frames; ++fi) {
        f.read(reinterpret_cast<char*>(buf.data()),
               static_cast<std::streamsize>(luma_pixels));
        auto& frame = store.frames[static_cast<size_t>(fi)];
        frame.resize(luma_pixels);
        for (size_t px = 0; px < luma_pixels; ++px)
            frame[px] = static_cast<uint16_t>(buf[px]);
        f.seekg(static_cast<std::streamoff>(chroma_pixels), std::ios::cur);
    }
    std::cout << "Loaded " << n_frames << " YUV frame(s) from " << path
              << " (" << width << "x" << height << ")" << std::endl;
    return store;
}

static void fill_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count,
    const InputConfig& input_cfg,
    int exec_iteration,
    const YuvFrameStore* yuv_store = nullptr,
    int blocks_w = 0
) {
    switch (input_cfg.mode) {
        case InputMode::Random:
            fill_random_frame_input(frame_input, block_count);
            break;
        case InputMode::Gradient:
            fill_gradient_frame_input(frame_input, block_count, exec_iteration);
            break;
        case InputMode::Video:
            fill_video_frame_input(frame_input, block_count, exec_iteration,
                                   *yuv_store, blocks_w);
            break;
    }
}

static void print_fps_for_resolution(const FrameConfig& cfg, int iterations, double elapsed_seconds) {
    if (elapsed_seconds <= 0.0 || iterations <= 0) {
        std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): N/A" << std::endl;
        return;
    }
    const double fps = static_cast<double>(iterations) / elapsed_seconds;
    std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): " << fps << std::endl;
}

static uint8_t clip_pixel_sw(int32_t val) {
    if (val < 0) return 0;
    if (val > 255) return 255;
    return static_cast<uint8_t>(val);
}

static int32_t fir_8tap_sw(const int16_t samples[NTAPS], const int16_t coeffs[NTAPS]) {
    int32_t sum = 0;
    for (int t = 0; t < NTAPS; ++t) {
        sum += static_cast<int32_t>(samples[t]) * static_cast<int32_t>(coeffs[t]);
    }
    return sum;
}

static void unpack_ref_block_from_frame(
    const std::vector<input_word_t>& frame_input,
    int block_idx,
    int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W]
) {
    const size_t base = static_cast<size_t>(block_idx) * REF_BLOCK_H;
    for (int r = 0; r < REF_BLOCK_H; ++r) {
        const input_word_t row = frame_input[base + r];
        for (int c = 0; c < REF_BLOCK_W; ++c) {
            ref_block[r][c] = static_cast<int16_t>(row.range((c + 1) * 16 - 1, c * 16));
        }
    }
}

static void interp_block_sw(
    const int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W],
    uint8_t out_block[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t frac_x,
    uint8_t frac_y
) {
    if (frac_x == 0 && frac_y == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                out_block[r][c] = clip_pixel_sw(ref_block[r + 3][c + 3]);
            }
        }
    } else if (frac_y == 0) {
        int16_t coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) coeffs[t] = LUMA_FILTER[frac_x][t];

        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r + 3][c + t];
                }
                const int32_t sum = fir_8tap_sw(samples, coeffs);
                const int32_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    } else if (frac_x == 0) {
        int16_t coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) coeffs[t] = LUMA_FILTER[frac_y][t];

        for (int c = 0; c < BLOCK_SIZE; ++c) {
            for (int r = 0; r < BLOCK_SIZE; ++r) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r + t][c + 3];
                }
                const int32_t sum = fir_8tap_sw(samples, coeffs);
                const int32_t val = (sum + (1 << (FILTER_PREC - 1))) >> FILTER_PREC;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    } else {
        int32_t transpose_mem[REF_BLOCK_H][BLOCK_SIZE] = {};
        const int headroom = INTERNAL_PREC - BIT_DEPTH;
        const int shift1 = FILTER_PREC - headroom;
        const int offset1 = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
        const int shift2 = FILTER_PREC + headroom;
        const int offset2 = (1 << (shift2 - 1));

        int16_t h_coeffs[NTAPS] = {};
        int16_t v_coeffs[NTAPS] = {};
        for (int t = 0; t < NTAPS; ++t) {
            h_coeffs[t] = LUMA_FILTER[frac_x][t];
            v_coeffs[t] = LUMA_FILTER[frac_y][t];
        }

        for (int r = 0; r < REF_BLOCK_H; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int16_t samples[NTAPS] = {};
                for (int t = 0; t < NTAPS; ++t) {
                    samples[t] = ref_block[r][c + t];
                }
                const int32_t sum = fir_8tap_sw(samples, h_coeffs);
                if (shift1 >= 0) {
                    transpose_mem[r][c] = (sum + offset1) >> shift1;
                } else {
                    transpose_mem[r][c] = sum << (-shift1);
                }
            }
        }

        for (int r = 0; r < BLOCK_SIZE; ++r) {
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int32_t sum = 0;
                for (int t = 0; t < NTAPS; ++t) {
                    sum += transpose_mem[r + t][c] * static_cast<int32_t>(v_coeffs[t]);
                }
                const int32_t val = (sum + offset2) >> shift2;
                out_block[r][c] = clip_pixel_sw(val);
            }
        }
    }
}

static void software_model_frame(
    const std::vector<input_word_t>& frame_input,
    std::vector<output_word_t>& frame_output,
    int block_count,
    uint8_t frac_x,
    uint8_t frac_y
) {
    frame_output.assign(static_cast<size_t>(block_count) * OUT_ROWS_PER_BLOCK, output_word_t(0));

    for (int b = 0; b < block_count; ++b) {
        int16_t ref_block[REF_BLOCK_H][REF_BLOCK_W] = {};
        uint8_t out_block[BLOCK_SIZE][BLOCK_SIZE] = {};
        unpack_ref_block_from_frame(frame_input, b, ref_block);
        interp_block_sw(ref_block, out_block, frac_x, frac_y);

        const size_t out_base = static_cast<size_t>(b) * OUT_ROWS_PER_BLOCK;
        for (int r = 0; r < BLOCK_SIZE; ++r) {
            output_word_t packed = 0;
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                packed.range((c + 1) * 16 - 1, c * 16) = static_cast<uint16_t>(out_block[r][c]);
            }
            frame_output[out_base + r] = packed;
        }
    }
}

static void run_kernel_warmup(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    int blocks_per_exec
) {
    std::vector<input_word_t> warmup_exec_input;
    fill_random_frame_input(warmup_exec_input, blocks_per_exec);
    std::copy(warmup_exec_input.begin(), warmup_exec_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    for (int i = 0; i < 10; ++i) {
        const uint8_t fx = random_binary_frac();
        const uint8_t fy = random_binary_frac();
        auto run = kernel(input_bo, output_bo, fx, fy, blocks_per_exec);
        run.wait();
    }
}

static void run_scenario_1(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_word_t* output_ptr,
    const FrameConfig& cfg,
    const RunConfig& run_cfg,
    const InputConfig& input_cfg,      // new
    const YuvFrameStore* yuv_ptr       // new
) {
    std::cout << "\n[Scenario 1] Fixed batched input, random binary frac_x/frac_y per execution" << std::endl;

    std::vector<input_word_t> fixed_exec_input;
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));

    //fill_random_frame_input(fixed_exec_input, run_cfg.blocks_per_exec);
    fill_frame_input(fixed_exec_input, run_cfg.blocks_per_exec, input_cfg, 0, yuv_ptr, cfg.blocks_w);
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);
    auto bar = make_progress_bar("[Scenario 1] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);

    std::copy(fixed_exec_input.begin(), fixed_exec_input.end(), input_ptr);
    input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        // checksum disabled to avoid affecting timing
        (void)output_ptr;
        bar->tick();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    bar->mark_as_completed();
    indicators::show_console_cursor(true);

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static void run_scenario_2(
    xrt::kernel& kernel,
    xrt::bo& input_bo,
    xrt::bo& output_bo,
    input_word_t* input_ptr,
    output_word_t* output_ptr,
    const FrameConfig& cfg,
    const RunConfig& run_cfg,
    const InputConfig& input_cfg,      // new
    const YuvFrameStore* yuv_ptr,      // new
    FrameStreamer* streamer = nullptr
) {
    std::cout << "\n[Scenario 2] Prefilled random frame bank, per-frame copy+sync+run+sync" << std::endl;

    const size_t words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    const size_t out_words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    std::vector<input_word_t> frame_bank(static_cast<size_t>(run_cfg.exec_count) * words_per_exec);
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<output_word_t> output_bank(static_cast<size_t>(run_cfg.exec_count) * out_words_per_exec);
    auto bar = make_progress_bar("[Scenario 2] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);
    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> tmp;
        //fill_random_frame_input(tmp, run_cfg.blocks_per_exec);
        fill_frame_input(tmp, run_cfg.blocks_per_exec, input_cfg, it, yuv_ptr, cfg.blocks_w);
        std::copy(tmp.begin(), tmp.end(), frame_bank.begin() + static_cast<size_t>(it) * words_per_exec);
        bar->tick();
    }
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);
    bar->mark_as_completed();
    indicators::show_console_cursor(true);
    auto start = std::chrono::high_resolution_clock::now();

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        const auto in_off = idx * words_per_exec;
        const auto out_off = idx * out_words_per_exec;

        std::copy(frame_bank.begin() + in_off, frame_bank.begin() + in_off + words_per_exec, input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo, frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        run.wait();

        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);
        std::copy(output_ptr, output_ptr + out_words_per_exec, output_bank.begin() + out_off);

        if (streamer) {
            streamer->push_raw_output(output_ptr);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static void run_scenario_3(
    xrt::kernel& kernel,
    xrt::device& device,
    int g_in,
    int g_out,
    const FrameConfig& cfg,
    const RunConfig& run_cfg,
    const InputConfig& input_cfg,      // new
    const YuvFrameStore* yuv_ptr,      // new
    FrameStreamer* streamer = nullptr
) {
    std::cout << "\n[Scenario 3] Double-buffer frame ping-pong" << std::endl;

    const size_t words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    const size_t out_words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    std::vector<input_word_t> frame_bank(static_cast<size_t>(run_cfg.exec_count) * words_per_exec);
    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<output_word_t> output_bank(static_cast<size_t>(run_cfg.exec_count) * out_words_per_exec);
    auto bar = make_progress_bar("[Scenario 3] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);
    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> tmp;
        //fill_random_frame_input(tmp, run_cfg.blocks_per_exec);
        fill_frame_input(tmp, run_cfg.blocks_per_exec, input_cfg, it, yuv_ptr, cfg.blocks_w);
        std::copy(tmp.begin(), tmp.end(), frame_bank.begin() + static_cast<size_t>(it) * words_per_exec);
        bar->tick();
    }
    bar->mark_as_completed();
    indicators::show_console_cursor(true);
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    const size_t input_bytes = align_to_4096(words_per_exec * sizeof(input_word_t));
    const size_t output_bytes = align_to_4096(out_words_per_exec * sizeof(output_word_t));

    std::array<xrt::bo, 2> in_bo = {
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in),
        xrt::bo(device, input_bytes, xrt::bo::flags::normal, g_in)
    };
    std::array<xrt::bo, 2> out_bo = {
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out),
        xrt::bo(device, output_bytes, xrt::bo::flags::normal, g_out)
    };

    std::array<input_word_t*, 2> in_ptr = {
        in_bo[0].map<input_word_t*>(),
        in_bo[1].map<input_word_t*>()
    };
    std::array<output_word_t*, 2> out_ptr = {
        out_bo[0].map<output_word_t*>(),
        out_bo[1].map<output_word_t*>()
    };

    int cur = 0;
    int nxt = 1;

    std::copy(frame_bank.begin(), frame_bank.begin() + words_per_exec, in_ptr[cur]);
    in_bo[cur].sync(XCL_BO_SYNC_BO_TO_DEVICE);

    auto start = std::chrono::high_resolution_clock::now();

    auto run = kernel(in_bo[cur], out_bo[cur], frac_x_bank[0], frac_y_bank[0], run_cfg.blocks_per_exec);

    for (int it = 1; it < run_cfg.exec_count; ++it) {
        const auto idx = static_cast<size_t>(it);
        const auto in_off = idx * words_per_exec;

        std::copy(frame_bank.begin() + in_off, frame_bank.begin() + in_off + words_per_exec, in_ptr[nxt]);
        in_bo[nxt].sync(XCL_BO_SYNC_BO_TO_DEVICE);

        run.wait();
        out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        const auto out_off = static_cast<size_t>(it - 1) * out_words_per_exec;
        std::copy(out_ptr[cur], out_ptr[cur] + out_words_per_exec, output_bank.begin() + out_off);

        if (streamer) {
            streamer->push_raw_output(out_ptr[cur]);
        }

        run = kernel(in_bo[nxt], out_bo[nxt], frac_x_bank[idx], frac_y_bank[idx], run_cfg.blocks_per_exec);
        std::swap(cur, nxt);
    }

    run.wait();
    out_bo[cur].sync(XCL_BO_SYNC_BO_FROM_DEVICE);
    std::copy(out_ptr[cur], out_ptr[cur] + out_words_per_exec,
              output_bank.begin() + static_cast<size_t>(run_cfg.exec_count - 1) * out_words_per_exec);

    if (streamer) {
        streamer->push_raw_output(out_ptr[cur]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Frames processed: " << run_cfg.total_frames << std::endl;
    std::cout << "Frames per execution: " << run_cfg.frames_per_exec << std::endl;
    std::cout << "Kernel executions: " << run_cfg.exec_count << std::endl;
    std::cout << "Blocks per frame: " << cfg.block_count << std::endl;
    std::cout << "Blocks per execution: " << run_cfg.blocks_per_exec << std::endl;
    std::cout << "Total time: " << elapsed.count() << " s" << std::endl;
    std::cout << "Average per frame: " << (elapsed.count() / std::max(1, run_cfg.total_frames)) << " s" << std::endl;
    print_fps_for_resolution(cfg, run_cfg.total_frames, elapsed.count());
}

static bool run_golden_verification(
    xrt::kernel& kernel,
    xrt::device& device,
    int g_in,
    int g_out,
    const FrameConfig& cfg,
    const RunConfig& run_cfg
) {
    std::cout << "\n[Golden Check] Hardware vs software model (frame mode)" << std::endl;

    // Allocate fresh buffers to avoid any state from previous scenarios
    const size_t input_words  = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    const size_t output_words = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;
    const size_t input_bytes  = align_to_4096(input_words  * sizeof(input_word_t));
    const size_t output_bytes = align_to_4096(output_words * sizeof(output_word_t));

    xrt::bo input_bo (device, input_bytes,  xrt::bo::flags::normal, g_in);
    xrt::bo output_bo(device, output_bytes, xrt::bo::flags::normal, g_out);
    input_word_t*  input_ptr  = input_bo.map<input_word_t*>();
    output_word_t* output_ptr = output_bo.map<output_word_t*>();

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    bool mismatch = false;
    size_t mismatch_count = 0;
    const size_t out_words_per_exec = output_words;

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> frame_input;
        fill_random_frame_input(frame_input, run_cfg.blocks_per_exec);

        std::vector<output_word_t> sw_out;
        software_model_frame(frame_input, sw_out, run_cfg.blocks_per_exec, frac_x_bank[static_cast<size_t>(it)], frac_y_bank[static_cast<size_t>(it)]);

        std::copy(frame_input.begin(), frame_input.end(), input_ptr);
        input_bo.sync(XCL_BO_SYNC_BO_TO_DEVICE);

        auto run = kernel(input_bo, output_bo,
                          frac_x_bank[static_cast<size_t>(it)],
                          frac_y_bank[static_cast<size_t>(it)],
                          run_cfg.blocks_per_exec);
        run.wait();
        output_bo.sync(XCL_BO_SYNC_BO_FROM_DEVICE);

        for (size_t i = 0; i < out_words_per_exec; ++i) {
            const output_word_t hw_word = output_ptr[i];
            const output_word_t sw_word = sw_out[i];
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                const uint16_t hw = static_cast<uint16_t>(hw_word.range((c + 1) * 16 - 1, c * 16));
                const uint16_t sw = static_cast<uint16_t>(sw_word.range((c + 1) * 16 - 1, c * 16));
                if (hw != sw) {
                    if (mismatch_count < 20) {
                        std::cout << "Mismatch iter=" << it
                                  << " out_word=" << i
                                  << " lane=" << c
                                  << " frac_x=" << static_cast<int>(frac_x_bank[static_cast<size_t>(it)])
                                  << " frac_y=" << static_cast<int>(frac_y_bank[static_cast<size_t>(it)])
                                  << " sw=" << sw
                                  << " hw=" << hw
                                  << std::endl;
                    }
                    mismatch = true;
                    ++mismatch_count;
                }
            }
        }
    }

    if (!mismatch) {
        std::cout << "Golden model match: all outputs identical." << std::endl;
    } else {
        std::cout << "Golden model mismatch count: " << mismatch_count << std::endl;
    }

    return !mismatch;
}

} // namespace

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (argc < 6 || argc > 7) {
        std::cout << "Usage: " << argv[0]
                  << " <xclbin> <total_frames> <resolution:fhd|4k> <frames_per_exec>"
                     " <input:random|gradient|video:/path/to/file.yuv>"
                     " [output:display|mp4:/path/to/output.mp4]" << std::endl;
        return EXIT_FAILURE;
    }

    const std::string xclbin_path    = argv[1];
    const int         iterations     = std::stoi(argv[2]);
    const std::string resolution     = argv[3];
    const int         frames_per_exec = std::stoi(argv[4]);
    const std::string input_arg      = argv[5];
    const std::string output_arg     = (argc >= 7) ? argv[6] : "display";

    if (iterations <= 0) {
        std::cerr << "Iterations must be > 0." << std::endl;
        return EXIT_FAILURE;
    }
    if (frames_per_exec <= 0) {
        std::cerr << "frames_per_exec must be > 0." << std::endl;
        return EXIT_FAILURE;
    }
    if (iterations % frames_per_exec != 0) {
        std::cerr << "iterations(total_frames) must be divisible by frames_per_exec." << std::endl;
        return EXIT_FAILURE;
    }

    try {
        const InputConfig input_cfg = parse_input_config(input_arg);
        const FrameConfig cfg       = make_frame_config(resolution);

        // yuv_store and cfg are now both alive at the same point
        std::unique_ptr<YuvFrameStore> yuv_store;
        if (input_cfg.mode == InputMode::Video)
            yuv_store = std::make_unique<YuvFrameStore>(
                load_yuv_file(input_cfg.video_path, cfg.width, cfg.height));
        const YuvFrameStore* yuv_ptr = yuv_store.get();

        const RunConfig run_cfg = {
            iterations,
            frames_per_exec,
            iterations / frames_per_exec,
            cfg.block_count * frames_per_exec
        };

        std::cout << "Frame: " << cfg.width << "x" << cfg.height
                  << ", blocks_w=" << cfg.blocks_w
                  << ", blocks_h=" << cfg.blocks_h
                  << ", block_count=" << cfg.block_count << std::endl;
        std::cout << "Run config: total_frames=" << run_cfg.total_frames
                  << ", frames_per_exec=" << run_cfg.frames_per_exec
                  << ", exec_count=" << run_cfg.exec_count
                  << ", blocks_per_exec=" << run_cfg.blocks_per_exec << std::endl;

        auto device      = xrt::device(0);
        auto xclbin_data = load_xclbin(xclbin_path);
        auto xclbin      = xrt::xclbin(xclbin_data);
        auto uuid        = device.load_xclbin(xclbin);
        auto kernel      = xrt::kernel(device, uuid, "vvc_fractional_interp");
        std::cout << "xclbin load successful" << std::endl;

        const size_t input_words  = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
        const size_t output_words = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;
        const size_t input_bytes  = align_to_4096(input_words  * sizeof(input_word_t));
        const size_t output_bytes = align_to_4096(output_words * sizeof(output_word_t));

        auto g_in  = kernel.group_id(0);
        auto g_out = kernel.group_id(1);

        xrt::bo input_bo (device, input_bytes,  xrt::bo::flags::normal, g_in);
        xrt::bo output_bo(device, output_bytes, xrt::bo::flags::normal, g_out);

        input_word_t*  input_ptr  = input_bo.map<input_word_t*>();
        output_word_t* output_ptr = output_bo.map<output_word_t*>();

        run_kernel_warmup(kernel, input_bo, output_bo, input_ptr, run_cfg.blocks_per_exec);

        // Create GStreamer streamer when using video input
        std::unique_ptr<FrameStreamer> streamer;
        if (input_cfg.mode == InputMode::Video) {
            StreamMode smode = StreamMode::Display;
            std::string mp4_path;
            const std::string mp4_prefix = "mp4:";
            if (output_arg.size() > mp4_prefix.size() &&
                output_arg.substr(0, mp4_prefix.size()) == mp4_prefix) {
                smode = StreamMode::File;
                mp4_path = output_arg.substr(mp4_prefix.size());
            }

            streamer = std::make_unique<FrameStreamer>(
                cfg.width, cfg.height, cfg.block_count, cfg.blocks_w,
                24, smode, mp4_path);
            if (!streamer->start()) {
                std::cerr << "Warning: Could not start video streamer. "
                             "Continuing without streaming." << std::endl;
                streamer.reset();
            }
        }

        run_scenario_1(kernel, input_bo, output_bo, input_ptr, output_ptr, cfg, run_cfg, input_cfg, yuv_ptr);
        run_scenario_2(kernel, input_bo, output_bo, input_ptr, output_ptr, cfg, run_cfg, input_cfg, yuv_ptr, streamer.get());
        run_scenario_3(kernel, device, g_in, g_out,                        cfg, run_cfg, input_cfg, yuv_ptr, streamer.get());
        run_golden_verification(kernel, device, g_in, g_out, cfg, run_cfg);

        if (streamer) streamer->stop();

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
