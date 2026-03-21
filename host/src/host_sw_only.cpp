#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "indicators.hpp"


static indicators::BlockProgressBar make_progress_bar(const std::string& label, int total) {
    using namespace indicators;
    return BlockProgressBar{
        option::BarWidth{40},
        option::PrefixText{label},
        option::MaxProgress{static_cast<size_t>(total)},
        option::ShowElapsedTime{true},
        option::ShowRemainingTime{true},
        option::ForegroundColor{Color::cyan},
    };
}

namespace {

constexpr int REF_BLOCK_H      = 15;
constexpr int REF_BLOCK_W      = 15;
constexpr int BLOCK_SIZE       = 8;
constexpr int NTAPS            = 8;
constexpr int NUM_FRAC_POS     = 16;
constexpr int FILTER_PREC      = 6;
constexpr int BIT_DEPTH        = 8;
constexpr int INTERNAL_PREC    = 14;
constexpr int OUT_ROWS_PER_BLOCK = BLOCK_SIZE;

// ---------------------------------------------------------------------------
// Word types — plain structs replacing ap_uint<256> / ap_uint<128>
// 256-bit input word  = 16 x uint16_t pixels (we only use 15, last slot unused)
// 128-bit output word =  8 x uint16_t pixels
// ---------------------------------------------------------------------------

struct input_word_t {
    uint16_t pixels[16]{};  // slots [0..14] used; [15] padding
};

struct output_word_t {
    uint16_t pixels[8]{};
};

// ---------------------------------------------------------------------------
// VVC luma interpolation filter
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// Configs
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// Input mode
// ---------------------------------------------------------------------------

enum class InputMode { Random, Gradient, Video };

struct InputConfig {
    InputMode   mode;
    std::string video_path; // only used when mode == Video
};

static InputConfig parse_input_config(const std::string& arg) {
    if (arg == "random")   return { InputMode::Random,   {} };
    if (arg == "gradient") return { InputMode::Gradient, {} };
    const std::string prefix = "video:";
    if (arg.size() > prefix.size() && arg.substr(0, prefix.size()) == prefix)
        return { InputMode::Video, arg.substr(prefix.size()) };
    throw std::runtime_error(
        "input must be: random | gradient | video:/path/to/file.yuv");
}

// ---------------------------------------------------------------------------
// YUV frame store  (planar YUV 4:2:0, 8-bit, luma only)
// ---------------------------------------------------------------------------

struct YuvFrameStore {
    int frame_width  = 0;
    int frame_height = 0;
    int frame_count  = 0;
    std::vector<std::vector<uint16_t>> frames; // [frame][row*width+col]
};

static YuvFrameStore load_yuv_file(
    const std::string& path,
    int width,
    int height
) {
    const size_t luma_pixels   = static_cast<size_t>(width) * height;
    const size_t chroma_pixels = luma_pixels / 2; // Cb+Cr for 4:2:0
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
        // skip chroma
        f.seekg(static_cast<std::streamoff>(chroma_pixels), std::ios::cur);
    }

    std::cout << "Loaded " << n_frames << " YUV frame(s) from " << path
              << " (" << width << "x" << height << ")" << std::endl;
    return store;
}

// ---------------------------------------------------------------------------
// Frame fill strategies
// ---------------------------------------------------------------------------

static void fill_random_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count
) {
    frame_input.resize(static_cast<size_t>(block_count) * REF_BLOCK_H);
    for (int b = 0; b < block_count; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t word{};
            for (int c = 0; c < REF_BLOCK_W; ++c)
                word.pixels[c] = static_cast<uint16_t>(std::rand() % 256);
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = word;
        }
    }
}

static void fill_gradient_frame_input(
    std::vector<input_word_t>& frame_input,
    int block_count,
    int exec_iteration
) {
    frame_input.resize(static_cast<size_t>(block_count) * REF_BLOCK_H);
    for (int b = 0; b < block_count; ++b) {
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t word{};
            for (int c = 0; c < REF_BLOCK_W; ++c)
                word.pixels[c] = static_cast<uint16_t>((exec_iteration + r + c) % 256);
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = word;
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
    frame_input.resize(static_cast<size_t>(block_count) * REF_BLOCK_H);
    const int fi = exec_iteration % store.frame_count;
    const std::vector<uint16_t>& luma = store.frames[static_cast<size_t>(fi)];
    const int W = store.frame_width;

    for (int b = 0; b < block_count; ++b) {
        const int origin_x = (b % blocks_w) * REF_BLOCK_W;
        const int origin_y = (b / blocks_w) * REF_BLOCK_H;
        for (int r = 0; r < REF_BLOCK_H; ++r) {
            input_word_t word{};
            for (int c = 0; c < REF_BLOCK_W; ++c) {
                const int px = (origin_y + r) * W + (origin_x + c);
                word.pixels[c] = (px < static_cast<int>(luma.size()))
                                 ? luma[static_cast<size_t>(px)]
                                 : uint16_t{0};
            }
            frame_input[static_cast<size_t>(b) * REF_BLOCK_H + r] = word;
        }
    }
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

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static FrameConfig make_frame_config(const std::string& resolution) {
    int width = 0, height = 0;
    if (resolution == "fhd" || resolution == "1080p") { width = 1920; height = 1080; }
    else if (resolution == "4k" || resolution == "2160p") { width = 3840; height = 2160; }
    else throw std::runtime_error("Resolution must be: fhd | 1080p | 4k | 2160p");
    const int bw = (width  + REF_BLOCK_W - 1) / REF_BLOCK_W;
    const int bh = (height + REF_BLOCK_H - 1) / REF_BLOCK_H;
    return { width, height, bw, bh, bw * bh };
}

static uint8_t random_binary_frac() {
    return static_cast<uint8_t>(std::rand() & 1);
}

static void fill_binary_frac_bank(
    std::vector<uint8_t>& frac_x_bank,
    std::vector<uint8_t>& frac_y_bank,
    int count
) {
    for (int i = 0; i < count; ++i) {
        frac_x_bank[static_cast<size_t>(i)] = random_binary_frac();
        frac_y_bank[static_cast<size_t>(i)] = random_binary_frac();
    }
}

static void print_fps(const FrameConfig& cfg, int frames, double seconds) {
    if (seconds <= 0.0 || frames <= 0) {
        std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): N/A\n";
        return;
    }
    std::cout << "FPS (" << cfg.width << "x" << cfg.height << "): "
              << static_cast<double>(frames) / seconds << "\n";
}

static void print_run_stats(
    const FrameConfig& cfg,
    const RunConfig&   run_cfg,
    double             elapsed
) {
    std::cout << "Frames processed:    " << run_cfg.total_frames                              << "\n";
    std::cout << "Frames per exec:     " << run_cfg.frames_per_exec                           << "\n";
    std::cout << "Kernel executions:   " << run_cfg.exec_count                                << "\n";
    std::cout << "Blocks per frame:    " << cfg.block_count                                   << "\n";
    std::cout << "Blocks per exec:     " << run_cfg.blocks_per_exec                           << "\n";
    std::cout << "Total time:          " << elapsed                                           << " s\n";
    std::cout << "Average per frame:   " << elapsed / std::max(1, run_cfg.total_frames)       << " s\n";
    print_fps(cfg, run_cfg.total_frames, elapsed);
}

// ---------------------------------------------------------------------------
// Software interpolation model
// ---------------------------------------------------------------------------

static uint8_t clip_pixel(int32_t v) {
    return static_cast<uint8_t>(v < 0 ? 0 : v > 255 ? 255 : v);
}

static int32_t fir_8tap(const int16_t s[NTAPS], const int16_t h[NTAPS]) {
    int32_t sum = 0;
    for (int t = 0; t < NTAPS; ++t)
        sum += static_cast<int32_t>(s[t]) * static_cast<int32_t>(h[t]);
    return sum;
}

static void unpack_ref_block(
    const std::vector<input_word_t>& frame_input,
    int block_idx,
    int16_t ref[REF_BLOCK_H][REF_BLOCK_W]
) {
    const size_t base = static_cast<size_t>(block_idx) * REF_BLOCK_H;
    for (int r = 0; r < REF_BLOCK_H; ++r)
        for (int c = 0; c < REF_BLOCK_W; ++c)
            ref[r][c] = static_cast<int16_t>(frame_input[base + r].pixels[c]);
}

static void interp_block(
    const int16_t ref[REF_BLOCK_H][REF_BLOCK_W],
    uint8_t       out[BLOCK_SIZE][BLOCK_SIZE],
    uint8_t frac_x,
    uint8_t frac_y
) {
    if (frac_x == 0 && frac_y == 0) {
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c)
                out[r][c] = clip_pixel(ref[r + 3][c + 3]);
        return;
    }
    if (frac_y == 0) {
        const int16_t* h = LUMA_FILTER[frac_x];
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c) {
                int16_t s[NTAPS];
                for (int t = 0; t < NTAPS; ++t) s[t] = ref[r + 3][c + t];
                out[r][c] = clip_pixel((fir_8tap(s, h) + (1 << (FILTER_PREC - 1))) >> FILTER_PREC);
            }
        return;
    }
    if (frac_x == 0) {
        const int16_t* h = LUMA_FILTER[frac_y];
        for (int c = 0; c < BLOCK_SIZE; ++c)
            for (int r = 0; r < BLOCK_SIZE; ++r) {
                int16_t s[NTAPS];
                for (int t = 0; t < NTAPS; ++t) s[t] = ref[r + t][c + 3];
                out[r][c] = clip_pixel((fir_8tap(s, h) + (1 << (FILTER_PREC - 1))) >> FILTER_PREC);
            }
        return;
    }
    // Both fractional: horizontal pass -> transpose -> vertical pass
    const int headroom = INTERNAL_PREC - BIT_DEPTH;
    const int shift1   = FILTER_PREC - headroom;
    const int offset1  = (shift1 > 0) ? (1 << (shift1 - 1)) : 0;
    const int shift2   = FILTER_PREC + headroom;
    const int offset2  = 1 << (shift2 - 1);

    int32_t tmp[REF_BLOCK_H][BLOCK_SIZE]{};
    for (int r = 0; r < REF_BLOCK_H; ++r)
        for (int c = 0; c < BLOCK_SIZE; ++c) {
            int16_t s[NTAPS];
            for (int t = 0; t < NTAPS; ++t) s[t] = ref[r][c + t];
            const int32_t sum = fir_8tap(s, LUMA_FILTER[frac_x]);
            tmp[r][c] = (shift1 >= 0) ? ((sum + offset1) >> shift1) : (sum << -shift1);
        }
    for (int r = 0; r < BLOCK_SIZE; ++r)
        for (int c = 0; c < BLOCK_SIZE; ++c) {
            int32_t sum = 0;
            for (int t = 0; t < NTAPS; ++t)
                sum += tmp[r + t][c] * static_cast<int32_t>(LUMA_FILTER[frac_y][t]);
            out[r][c] = clip_pixel((sum + offset2) >> shift2);
        }
}

static void software_model_frame(
    const std::vector<input_word_t>& frame_input,
    std::vector<output_word_t>&      frame_output,
    int     block_count,
    uint8_t frac_x,
    uint8_t frac_y
) {
    frame_output.assign(static_cast<size_t>(block_count) * OUT_ROWS_PER_BLOCK, output_word_t{});
    for (int b = 0; b < block_count; ++b) {
        int16_t ref[REF_BLOCK_H][REF_BLOCK_W]{};
        uint8_t blk[BLOCK_SIZE][BLOCK_SIZE]{};
        unpack_ref_block(frame_input, b, ref);
        interp_block(ref, blk, frac_x, frac_y);
        const size_t base = static_cast<size_t>(b) * OUT_ROWS_PER_BLOCK;
        for (int r = 0; r < BLOCK_SIZE; ++r)
            for (int c = 0; c < BLOCK_SIZE; ++c)
                frame_output[base + r].pixels[c] = static_cast<uint16_t>(blk[r][c]);
    }
}

// ---------------------------------------------------------------------------
// Scenarios  (no hardware — just measure fill + model time as a CPU baseline)
// ---------------------------------------------------------------------------

static void run_scenario_1(
    const FrameConfig& cfg,
    const RunConfig&   run_cfg,
    const InputConfig& input_cfg,
    const YuvFrameStore* yuv_store
) {
    std::cout << "\n[Scenario 1] Fixed input for all executions, random frac per execution\n";

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    // Fill once and reuse — mirrors Scenario 1's intent
    std::vector<input_word_t> fixed_input;
    fill_frame_input(fixed_input, run_cfg.blocks_per_exec,
                     input_cfg, 0, yuv_store, cfg.blocks_w);

    auto start = std::chrono::high_resolution_clock::now();
    auto bar = make_progress_bar("[Scenario 1] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);
    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<output_word_t> out;
        software_model_frame(fixed_input, out, run_cfg.blocks_per_exec,
                             frac_x_bank[static_cast<size_t>(it)],
                             frac_y_bank[static_cast<size_t>(it)]);

        bar.tick();
    }
    std::chrono::duration<double> elapsed =
        std::chrono::high_resolution_clock::now() - start;

    print_run_stats(cfg, run_cfg, elapsed.count());
    bar.mark_as_completed();
    indicators::show_console_cursor(true);
}

static void run_scenario_2(
    const FrameConfig& cfg,
    const RunConfig&   run_cfg,
    const InputConfig& input_cfg,
    const YuvFrameStore* yuv_store
) {
    std::cout << "\n[Scenario 2] New input fill every execution\n";

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);
    auto bar = make_progress_bar("[Scenario 2] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);

    auto start = std::chrono::high_resolution_clock::now();
    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t>  exec_input;
        std::vector<output_word_t> out;
        fill_frame_input(exec_input, run_cfg.blocks_per_exec,
                         input_cfg, it, yuv_store, cfg.blocks_w);
        software_model_frame(exec_input, out, run_cfg.blocks_per_exec,
                             frac_x_bank[static_cast<size_t>(it)],
                             frac_y_bank[static_cast<size_t>(it)]);
        bar.tick();
    }
    std::chrono::duration<double> elapsed =
        std::chrono::high_resolution_clock::now() - start;

    print_run_stats(cfg, run_cfg, elapsed.count());
    bar.mark_as_completed();
    indicators::show_console_cursor(true);
}

static void run_scenario_3(
    const FrameConfig& cfg,
    const RunConfig&   run_cfg,
    const InputConfig& input_cfg,
    const YuvFrameStore* yuv_store
) {
    // Without hardware DMA the ping-pong concept does not apply, so Scenario 3
    // pre-fills all inputs and then runs the model passes back-to-back to give
    // a clean compute-only number with no allocation inside the hot loop.
    std::cout << "\n[Scenario 3] Pre-filled input bank, compute-only hot loop\n";

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    const size_t words_per_exec = static_cast<size_t>(run_cfg.blocks_per_exec) * REF_BLOCK_H;
    std::vector<input_word_t> input_bank(static_cast<size_t>(run_cfg.exec_count) * words_per_exec);
    auto bar = make_progress_bar("[Scenario 3] ", run_cfg.exec_count);
    indicators::show_console_cursor(false);

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> tmp;
        fill_frame_input(tmp, run_cfg.blocks_per_exec,
                         input_cfg, it, yuv_store, cfg.blocks_w);
        std::copy(tmp.begin(), tmp.end(),
                  input_bank.begin() + static_cast<size_t>(it) * words_per_exec);
        bar.tick();
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int it = 0; it < run_cfg.exec_count; ++it) {
        // Construct a view into the pre-filled bank without copying
        const std::vector<input_word_t> exec_input(
            input_bank.begin() + static_cast<size_t>(it) * words_per_exec,
            input_bank.begin() + static_cast<size_t>(it) * words_per_exec + words_per_exec);
        std::vector<output_word_t> out;
        software_model_frame(exec_input, out, run_cfg.blocks_per_exec,
                             frac_x_bank[static_cast<size_t>(it)],
                             frac_y_bank[static_cast<size_t>(it)]);
        bar.tick();
    }
    std::chrono::duration<double> elapsed =
        std::chrono::high_resolution_clock::now() - start;

    print_run_stats(cfg, run_cfg, elapsed.count());
    bar.mark_as_completed();
    indicators::show_console_cursor(true);
}

static void run_golden_check(
    const FrameConfig& cfg,
    const RunConfig&   run_cfg,
    const InputConfig& input_cfg,
    const YuvFrameStore* yuv_store
) {
    std::cout << "\n[Golden Check] Verifying software model self-consistency\n";

    std::vector<uint8_t> frac_x_bank(static_cast<size_t>(run_cfg.exec_count));
    std::vector<uint8_t> frac_y_bank(static_cast<size_t>(run_cfg.exec_count));
    fill_binary_frac_bank(frac_x_bank, frac_y_bank, run_cfg.exec_count);

    size_t mismatch_count = 0;
    const size_t out_words = static_cast<size_t>(run_cfg.blocks_per_exec) * OUT_ROWS_PER_BLOCK;

    for (int it = 0; it < run_cfg.exec_count; ++it) {
        std::vector<input_word_t> frame_input;
        fill_frame_input(frame_input, run_cfg.blocks_per_exec,
                         input_cfg, it, yuv_store, cfg.blocks_w);

        // Run twice with the same input — results must be identical
        std::vector<output_word_t> out_a, out_b;
        software_model_frame(frame_input, out_a, run_cfg.blocks_per_exec,
                             frac_x_bank[static_cast<size_t>(it)],
                             frac_y_bank[static_cast<size_t>(it)]);
        software_model_frame(frame_input, out_b, run_cfg.blocks_per_exec,
                             frac_x_bank[static_cast<size_t>(it)],
                             frac_y_bank[static_cast<size_t>(it)]);

        for (size_t i = 0; i < out_words; ++i)
            for (int c = 0; c < BLOCK_SIZE; ++c)
                if (out_a[i].pixels[c] != out_b[i].pixels[c]) {
                    if (mismatch_count < 20)
                        std::cout << "Mismatch iter=" << it
                                  << " word=" << i << " lane=" << c
                                  << " a=" << out_a[i].pixels[c]
                                  << " b=" << out_b[i].pixels[c] << "\n";
                    ++mismatch_count;
                }
    }

    if (mismatch_count == 0)
        std::cout << "Golden check passed: model is deterministic.\n";
    else
        std::cout << "Golden check FAILED: " << mismatch_count << " mismatches.\n";
}

} // namespace

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------

int main(int argc, char** argv) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    if (argc != 5) {
        std::cout << "Usage: " << argv[0]
                  << " <total_frames>"
                     " <resolution:fhd|4k>"
                     " <frames_per_exec>"
                     " <input:random|gradient|video:/path/to/file.yuv>\n";
        return EXIT_FAILURE;
    }

    const int         total_frames    = std::stoi(argv[1]);
    const std::string resolution      = argv[2];
    const int         frames_per_exec = std::stoi(argv[3]);
    const std::string input_arg       = argv[4];

    if (total_frames <= 0)    { std::cerr << "total_frames must be > 0\n";    return EXIT_FAILURE; }
    if (frames_per_exec <= 0) { std::cerr << "frames_per_exec must be > 0\n"; return EXIT_FAILURE; }
    if (total_frames % frames_per_exec != 0) {
        std::cerr << "total_frames must be divisible by frames_per_exec\n";
        return EXIT_FAILURE;
    }

    try {
        const InputConfig input_cfg = parse_input_config(input_arg);
        const FrameConfig cfg       = make_frame_config(resolution);
        const RunConfig   run_cfg   = {
            total_frames,
            frames_per_exec,
            total_frames / frames_per_exec,
            cfg.block_count * frames_per_exec
        };

        std::unique_ptr<YuvFrameStore> yuv_store;
        if (input_cfg.mode == InputMode::Video)
            yuv_store = std::make_unique<YuvFrameStore>(
                load_yuv_file(input_cfg.video_path, cfg.width, cfg.height));
        const YuvFrameStore* yuv_ptr = yuv_store.get();

        std::cout << "Frame: " << cfg.width << "x" << cfg.height
                  << "  blocks_w=" << cfg.blocks_w
                  << "  blocks_h=" << cfg.blocks_h
                  << "  block_count=" << cfg.block_count << "\n";
        std::cout << "Run: total_frames=" << run_cfg.total_frames
                  << "  frames_per_exec=" << run_cfg.frames_per_exec
                  << "  exec_count=" << run_cfg.exec_count
                  << "  blocks_per_exec=" << run_cfg.blocks_per_exec << "\n";

        run_scenario_1(cfg, run_cfg, input_cfg, yuv_ptr);
        run_scenario_2(cfg, run_cfg, input_cfg, yuv_ptr);
        run_scenario_3(cfg, run_cfg, input_cfg, yuv_ptr);
        run_golden_check(cfg, run_cfg, input_cfg, yuv_ptr);

    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}