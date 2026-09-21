#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <random>
#include <regex>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

// The reference headers are kept byte-for-byte at the released tag. Exposing
// their members here lets this verification-only executable observe seams
// without changing the code whose final output it compares.
#define private public
#include "released/Source/dsp/PushPullAmp.h"
#undef private

namespace {

constexpr int kBurnInSamples = 1024;
constexpr int kBlockSize = 512;

struct Wav {
  int sample_rate = 0;
  std::vector<float> samples;
};

uint16_t read_u16(std::istream& stream) {
  std::array<unsigned char, 2> bytes{};
  stream.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
  if (!stream) throw std::runtime_error("truncated WAV");
  return static_cast<uint16_t>(bytes[0] | (bytes[1] << 8));
}

uint32_t read_u32(std::istream& stream) {
  std::array<unsigned char, 4> bytes{};
  stream.read(reinterpret_cast<char*>(bytes.data()), bytes.size());
  if (!stream) throw std::runtime_error("truncated WAV");
  return static_cast<uint32_t>(bytes[0] | (bytes[1] << 8) |
                               (bytes[2] << 16) | (bytes[3] << 24));
}

void write_u16(std::ostream& stream, uint16_t value) {
  const std::array<unsigned char, 2> bytes{
      static_cast<unsigned char>(value),
      static_cast<unsigned char>(value >> 8)};
  stream.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

void write_u32(std::ostream& stream, uint32_t value) {
  const std::array<unsigned char, 4> bytes{
      static_cast<unsigned char>(value),
      static_cast<unsigned char>(value >> 8),
      static_cast<unsigned char>(value >> 16),
      static_cast<unsigned char>(value >> 24)};
  stream.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}

Wav read_wav(const std::string& path) {
  std::ifstream stream(path, std::ios::binary);
  if (!stream) throw std::runtime_error("cannot open input WAV: " + path);

  char riff[4];
  stream.read(riff, 4);
  (void)read_u32(stream);
  char wave[4];
  stream.read(wave, 4);
  if (std::memcmp(riff, "RIFF", 4) != 0 ||
      std::memcmp(wave, "WAVE", 4) != 0) {
    throw std::runtime_error("input is not a RIFF/WAVE file");
  }

  uint16_t format = 0;
  uint16_t channels = 0;
  uint16_t bits = 0;
  uint32_t sample_rate = 0;
  std::vector<unsigned char> data;
  while (stream && (format == 0 || data.empty())) {
    char id[4];
    stream.read(id, 4);
    if (!stream) break;
    const uint32_t size = read_u32(stream);
    if (std::memcmp(id, "fmt ", 4) == 0) {
      format = read_u16(stream);
      channels = read_u16(stream);
      sample_rate = read_u32(stream);
      (void)read_u32(stream);
      (void)read_u16(stream);
      bits = read_u16(stream);
      if (size < 16) throw std::runtime_error("invalid WAV fmt chunk");
      stream.seekg(size - 16, std::ios::cur);
    } else if (std::memcmp(id, "data", 4) == 0) {
      data.resize(size);
      stream.read(reinterpret_cast<char*>(data.data()), size);
    } else {
      stream.seekg(size, std::ios::cur);
    }
    if ((size & 1U) != 0) stream.seekg(1, std::ios::cur);
  }

  if (format != 1 || channels != 1 || bits != 24 || data.empty()) {
    throw std::runtime_error("reference input must be mono 24-bit PCM WAV");
  }

  Wav wav;
  wav.sample_rate = static_cast<int>(sample_rate);
  wav.samples.reserve(data.size() / 3);
  for (size_t i = 0; i + 2 < data.size(); i += 3) {
    int32_t value = static_cast<int32_t>(data[i]) |
                    (static_cast<int32_t>(data[i + 1]) << 8) |
                    (static_cast<int32_t>(data[i + 2]) << 16);
    if ((value & 0x800000) != 0) value |= ~0xffffff;
    wav.samples.push_back(static_cast<float>(value) / 8388608.0f);
  }
  return wav;
}

void write_float_wav(const std::string& path, int sample_rate,
                     const std::vector<float>& samples) {
  std::ofstream stream(path, std::ios::binary);
  if (!stream) throw std::runtime_error("cannot open output WAV: " + path);
  const uint32_t data_size = static_cast<uint32_t>(samples.size() * 4);
  stream.write("RIFF", 4);
  write_u32(stream, 36 + data_size);
  stream.write("WAVEfmt ", 8);
  write_u32(stream, 16);
  write_u16(stream, 3);  // IEEE float
  write_u16(stream, 1);
  write_u32(stream, static_cast<uint32_t>(sample_rate));
  write_u32(stream, static_cast<uint32_t>(sample_rate * 4));
  write_u16(stream, 4);
  write_u16(stream, 32);
  stream.write("data", 4);
  write_u32(stream, data_size);
  stream.write(reinterpret_cast<const char*>(samples.data()), data_size);
}

std::vector<float> resample_linear(const Wav& input, int sample_rate) {
  if (sample_rate == input.sample_rate) return input.samples;
  const size_t output_size = static_cast<size_t>(std::llround(
      static_cast<double>(input.samples.size()) * sample_rate /
      input.sample_rate));
  std::vector<float> output(output_size);
  for (size_t i = 0; i < output.size(); ++i) {
    const double position =
        static_cast<double>(i) * input.sample_rate / sample_rate;
    const size_t lower = static_cast<size_t>(position);
    const size_t upper = std::min(lower + 1, input.samples.size() - 1);
    const float fraction = static_cast<float>(position - lower);
    output[i] = input.samples[lower] +
                fraction * (input.samples[upper] - input.samples[lower]);
  }
  return output;
}

struct Parameters {
  float input_level = 0.0f;
  float output_level = 0.0f;
  float ts_low = 0.0f;
  float ts_mid = 0.0f;
  float ts_high = 0.0f;
  float ts_presence = 0.0f;
  float ts_selection = 0.0f;
  float gain_stages = 3.0f;
  float gain_overhead = 0.0f;
  float low_cut = 0.0f;
  float cab_on = 1.0f;
  float cab_brightness = 0.0f;
  float cab_distance = 0.5f;
  float cab_dynamic = -0.3f;
  float preamp_drive = -0.4f;
  float preamp_tight = 0.0f;
  float preamp_grit = 0.0f;
  float power_drive = -0.2f;
  float power_tight = 0.0f;
  float power_grit = 0.0f;
  float power_sag = -0.6f;
  float power_sag_ratio = 0.0f;
};

struct Preset {
  std::string name;
  Parameters parameters;
};

std::string read_text(const std::string& path) {
  std::ifstream stream(path);
  if (!stream) throw std::runtime_error("cannot open file: " + path);
  return {std::istreambuf_iterator<char>(stream),
          std::istreambuf_iterator<char>()};
}

void assign_parameter(Parameters& p, const std::string& id, float value) {
  if (id == "idInputLevel") p.input_level = value;
  else if (id == "idOutputLevel") p.output_level = value;
  else if (id == "idTsLow") p.ts_low = value;
  else if (id == "idTsMid") p.ts_mid = value;
  else if (id == "idTsHigh") p.ts_high = value;
  else if (id == "idTsPresence") p.ts_presence = value;
  else if (id == "idTsSelection") p.ts_selection = value;
  else if (id == "idGainStages") p.gain_stages = value;
  else if (id == "idGainOverhead") p.gain_overhead = value;
  else if (id == "idLowCut") p.low_cut = value;
  else if (id == "idCabOnOff") p.cab_on = value;
  else if (id == "idCabBrightness") p.cab_brightness = value;
  else if (id == "idCabDistance") p.cab_distance = value;
  else if (id == "idCabDynamic") p.cab_dynamic = value;
  else if (id == "idPreAmpDrive") p.preamp_drive = value;
  else if (id == "idPreAmpTight") p.preamp_tight = value;
  else if (id == "idPreAmpGrit") p.preamp_grit = value;
  else if (id == "idPowerAmpDrive") p.power_drive = value;
  else if (id == "idPowerAmpTight") p.power_tight = value;
  else if (id == "idPowerAmpGrit") p.power_grit = value;
  else if (id == "idPowerAmpSag") p.power_sag = value;
  else if (id == "idPowerAmpSagRatio") p.power_sag_ratio = value;
}

std::vector<Preset> read_presets(const std::string& path) {
  const std::string xml = read_text(path);
  const std::regex preset_re(
      R"re(<APVTSSwankyAmp\s+presetName="([^"]+)"[^>]*>([\s\S]*?)</APVTSSwankyAmp>)re");
  const std::regex parameter_re(
      R"re(<PARAM\s+id="([^"]+)"\s+value="([^"]+)"\s*/>)re");
  std::vector<Preset> presets;
  for (std::sregex_iterator it(xml.begin(), xml.end(), preset_re), end;
       it != end; ++it) {
    Preset preset;
    preset.name = (*it)[1].str();
    const std::string body = (*it)[2].str();
    for (std::sregex_iterator parameter(body.begin(), body.end(), parameter_re);
         parameter != end; ++parameter) {
      assign_parameter(preset.parameters, (*parameter)[1].str(),
                       std::stof((*parameter)[2].str()));
    }
    presets.push_back(preset);
  }
  if (presets.empty()) {
    const std::regex single_re(
        R"re(<APVTSSwankyAmp(?:\s+[^>]*)?>([\s\S]*?)</APVTSSwankyAmp>)re");
    std::smatch match;
    if (std::regex_search(xml, match, single_re)) {
      Preset preset;
      preset.name = "custom";
      const std::string body = match[1].str();
      const std::sregex_iterator end;
      for (std::sregex_iterator parameter(body.begin(), body.end(), parameter_re);
           parameter != end; ++parameter) {
        assign_parameter(preset.parameters, (*parameter)[1].str(),
                         std::stof((*parameter)[2].str()));
      }
      presets.push_back(preset);
    }
  }
  if (presets.empty()) {
    throw std::runtime_error("no current-format Swanky Amp presets found");
  }
  return presets;
}

float remap_sided(float unit, float to_low, float to_high) {
  if (unit >= 0.0f) return unit * to_high;
  return -unit * to_low;
}

float remap_range(float unit, float to_low, float to_high) {
  return (unit + 1.0f) / 2.0f * (to_high - to_low) + to_low;
}

float remap_xy(float x, float x1, float x2, float y1, float y2) {
  x = std::max(x1, std::min(x2, x));
  x = (x - x1) / (x2 - x1);
  return x * (y2 - y1) + y1;
}

float remap_sinh(float x, float x0, float scale) {
  const float mapped = sinh((x - x0) * scale);
  const float lower = sinh((-1.0f - x0) * scale);
  const float upper = sinh((1.0f - x0) * scale);
  return (mapped - lower) / (upper - lower) * 2.0f - 1.0f;
}

float db_to_linear(float db) { return std::pow(10.0f, db / 20.0f); }

void set_amp_parameters(PushPullAmp& amp, const Parameters& p) {
  const float preamp_drive_map = remap_sinh(p.preamp_drive, 0.5f, 1.0f);
  const float power_drive_map = remap_sinh(p.power_drive, -0.2f, 1.0f);
  const float power_sag_map = remap_sinh(p.power_sag, 0.0f, 1.0f);
  const float low_cut_map =
      remap_sinh(remap_xy(p.low_cut, -1.0f, 1.0f, 0.0f, 1.23f),
                 0.5f, 1.0f);

  amp.set_input_level(p.input_level);
  amp.set_output_level(
      p.output_level +
      (10.0f + remap_xy(preamp_drive_map, 0.0f, 1.0f, 0.0f, -3.0f)) /
          35.0f);
  amp.set_triode_drive(preamp_drive_map);
  amp.set_tetrode_drive(power_drive_map);
  amp.set_tonestack_bass(p.ts_low);
  amp.set_tonestack_mids(p.ts_mid);
  amp.set_tonestack_treble(p.ts_high);
  amp.set_tonestack_presence(p.ts_presence);
  amp.set_tonestack_selection(p.ts_selection);
  amp.set_triode_num_stages(p.gain_stages);
  amp.set_triode_overhead(p.gain_overhead);
  amp.set_cabinet_on(p.cab_on > 0.5f);
  amp.set_cabinet_brightness(remap_sided(p.cab_brightness, -0.6f, 0.6f));
  amp.set_cabinet_distance(p.cab_distance);
  amp.set_cabinet_dynamic(remap_xy(p.cab_dynamic, -1.0f, 0.0f, -1.0f, 1.0f));
  amp.set_cabinet_dynamic_level(-p.cab_dynamic);
  amp.set_triode_hp_freq(remap_sided(low_cut_map, -1.0f, 0.75f));

  const float min_preamp_tight =
      remap_xy(preamp_drive_map, -0.5f, 1.0f, -1.0f, 0.0f);
  const float adjusted_preamp_tight =
      remap_range(p.preamp_tight, min_preamp_tight, 1.0f);
  amp.set_triode_grid_tau(
      remap_sided(-adjusted_preamp_tight, -0.5f, 0.1f));
  amp.set_triode_grid_ratio(
      remap_sided(-adjusted_preamp_tight, -1.0f, 0.1f));
  amp.set_triode_plate_bias(
      remap_sided(adjusted_preamp_tight, -1.0f, 0.5f));
  amp.set_triode_plate_comp_ratio(
      remap_sided(adjusted_preamp_tight, -1.0f, 0.0f));
  amp.set_triode_grid_level(remap_sided(-p.preamp_grit, -0.2f, 3.0f));
  amp.set_triode_grid_clip(remap_sided(-p.preamp_grit, -1.0f, 4.0f));
  amp.set_triode_plate_comp_level(
      remap_sided(p.preamp_grit, -0.0f, 1.0f));
  amp.set_triode_plate_comp_offset(
      remap_sided(-p.preamp_grit, -0.0f, 5.0f));

  amp.set_tetrode_grid_tau(remap_sided(-p.power_tight, -1.0f, 1.0f));
  amp.set_tetrode_grid_ratio(remap_sided(-p.power_tight, -1.0f, 0.1f));
  amp.set_tetrode_plate_comp_depth(
      remap_sided(-p.power_tight, -0.5f, 0.0f));
  amp.set_tetrode_plate_sag_tau(
      remap_sided(-p.power_tight, -1.0f, 1.0f));
  amp.set_tetrode_plate_sag_depth(
      power_sag_map +
      remap_xy(power_drive_map, -1.0f, 1.0f, 1.0f, -1.0f));
  amp.set_tetrode_plate_sag_ratio(p.power_sag_ratio);
  amp.set_tetrode_plate_sag_onset(power_sag_map);
  amp.set_tetrode_plate_sag_factor(amp.get_tetrode_drive());
  amp.set_tetrode_plate_sag_toggle(power_sag_map < -0.99f ? -1.0f : 1.0f);
}

struct WindowStats {
  uint64_t count = 0;
  double square_sum = 0.0;
  float peak = 0.0f;

  void add(float value) {
    if (!std::isfinite(value)) {
      throw std::runtime_error("DSP produced non-finite audio");
    }
    ++count;
    square_sum += static_cast<double>(value) * value;
    peak = std::max(peak, std::abs(value));
  }
};

struct SeamStats {
  WindowStats startup;
  WindowStats post_mute;
  WindowStats after_preroll;

  void add(const float* samples, int count, size_t absolute_offset,
           bool has_preroll) {
    for (int i = 0; i < count; ++i) {
      if (has_preroll) {
        after_preroll.add(samples[i]);
        continue;
      }
      auto& window = absolute_offset + static_cast<size_t>(i) <
                             static_cast<size_t>(kBurnInSamples)
                         ? startup
                         : post_mute;
      window.add(samples[i]);
    }
  }
};

using SeamMap = std::map<std::string, SeamStats>;
using SeamAudioMap = std::map<std::string, std::vector<float>>;

void capture_seam(const std::string& name, const float* samples, int count,
                  size_t offset, bool has_preroll, SeamMap* seams,
                  SeamAudioMap* audio) {
  if (seams != nullptr) {
    (*seams)[name].add(samples, count, offset, has_preroll);
  }
  if (audio != nullptr) {
    auto& destination = (*audio)[name];
    destination.insert(destination.end(), samples, samples + count);
  }
}

void process_instrumented(PushPullAmp& amp, int count, float** buffer,
                          size_t offset, bool has_preroll, SeamMap* seams,
                          SeamAudioMap* audio) {
  scaleBuffer(count, buffer, db_to_linear(amp.inputLevel));

  PreAmp& preamp = amp.preAmp;
  scaleBuffer(count, buffer, preamp.drive < 0.5f ? 0.5f : preamp.drive);
  const int stages_low = static_cast<int>(std::floor(preamp.numStagesActive()));
  const int stages_high = static_cast<int>(std::ceil(preamp.numStagesActive()));
  const float stage_mix = preamp.numStagesActive() - stages_low;
  for (int i = 0; i < stages_high; ++i) {
    preamp.triode[i].set_overhead(i > 0 ? preamp.overhead : 1.0f);
    preamp.triode[i].set_mix(i < stages_low ? 1.0f : stage_mix);
    preamp.triode[i].process(count, buffer);
    capture_seam("triode_" + std::to_string(i + 1), buffer[0], count, offset,
                 has_preroll, seams, audio);
  }
  scaleBuffer(count, buffer, preamp.triodeScale);

  const float preamp_scale = interp1d(
      preamp.get_drive(), -1.0f, 1.0f, amp.preAmpSweepScales,
      static_cast<size_t>(NUM_SWEEP_BINS));
  constexpr float preamp_target = 3.228806e+01f;
  constexpr float tone_stack_scale = 1.0f / 5.302220e-01f;
  amp.toneStack.process(count, buffer);
  capture_seam("tone_stack", buffer[0], count, offset, has_preroll, seams,
               audio);
  scaleBuffer(count, buffer, tone_stack_scale * preamp_scale * preamp_target);

  amp.powerAmp.process(count, buffer);
  capture_seam("power_amp", buffer[0], count, offset, has_preroll, seams,
               audio);
  scaleBuffer(count, buffer, 1.0f / preamp_target);

  const float cabinet_scale = amp.cabinetOn ? 1.0f / 2.821151e+00f : 1.0f;
  if (amp.cabinetOn) amp.cabinet.process(count, buffer);
  capture_seam("cabinet", buffer[0], count, offset, has_preroll, seams,
               audio);

  const float power_amp_scale = interp1d(
      amp.powerAmp.get_drive(), -1.0f, 1.0f, amp.powerAmpSweepScales,
      static_cast<size_t>(NUM_SWEEP_BINS));
  const float output_scale = db_to_linear(amp.outputLevel);
  scaleBuffer(count, buffer, power_amp_scale * cabinet_scale * output_scale);
  capture_seam("raw_output", buffer[0], count, offset, has_preroll, seams,
               audio);
}

std::string db_json(double linear) {
  if (linear == 0.0) return "null";
  std::ostringstream stream;
  stream << std::fixed << std::setprecision(9) << 20.0 * std::log10(linear);
  return stream.str();
}

void write_window_json(std::ostream& stream, const WindowStats& stats,
                       int indent) {
  const std::string pad(static_cast<size_t>(indent), ' ');
  const double rms = stats.count == 0
                         ? 0.0
                         : std::sqrt(stats.square_sum / stats.count);
  stream << "{\n" << pad << "  \"samples\": " << stats.count
         << ",\n" << pad << "  \"rms_dbfs\": " << db_json(rms)
         << ",\n" << pad << "  \"peak_dbfs\": "
         << db_json(stats.peak) << "\n" << pad << "}";
}

std::string json_escape(const std::string& value) {
  std::string escaped;
  for (const char c : value) {
    if (c == '\\' || c == '"') escaped += '\\';
    escaped += c;
  }
  return escaped;
}

void write_report(const std::string& path, const Preset& preset,
                  int sample_rate, size_t samples, const SeamMap& seams,
                  const SeamStats& rendered, uint64_t mismatch_count,
                  float max_difference, size_t silence_preroll,
                  const std::map<std::string, std::string>& seam_paths) {
  std::ofstream stream(path);
  if (!stream) throw std::runtime_error("cannot open report: " + path);
  stream << "{\n"
         << "  \"preset\": \"" << json_escape(preset.name) << "\",\n"
         << "  \"sample_rate\": " << sample_rate << ",\n"
         << "  \"samples\": " << samples << ",\n"
         << "  \"block_size\": " << kBlockSize << ",\n";
  if (silence_preroll == 0) {
    stream << "  \"legacy_output_mute_samples\": " << kBurnInSamples
           << ",\n";
  } else {
    const size_t remaining_mute = silence_preroll >= kBurnInSamples
                                      ? 0
                                      : kBurnInSamples - silence_preroll;
    stream << "  \"silence_preroll_samples\": " << silence_preroll
           << ",\n"
           << "  \"measurement_begins_after_silence_samples\": "
           << silence_preroll << ",\n"
           << "  \"released_startup_mute_total_samples\": "
           << kBurnInSamples << ",\n"
           << "  \"legacy_output_mute_samples\": " << remaining_mute
           << ",\n";
  }
  stream
         << "  \"instrumented_comparison\": {\n"
         << "    \"bit_mismatches\": " << mismatch_count << ",\n"
         << "    \"max_abs_difference\": " << std::scientific
         << max_difference << std::defaultfloat << "\n"
         << "  },\n"
         << "  \"seams\": {\n";
  size_t index = 0;
  for (const auto& [name, stats] : seams) {
    stream << "    \"" << name << "\": {\n";
    if (silence_preroll == 0) {
      stream << "      \"startup\": ";
      write_window_json(stream, stats.startup, 6);
      stream << ",\n      \"post_mute\": ";
      write_window_json(stream, stats.post_mute, 6);
    } else {
      stream << "      \"after_preroll\": ";
      write_window_json(stream, stats.after_preroll, 6);
    }
    stream << "\n    }" << (++index == seams.size() ? "\n" : ",\n");
  }
  stream << "  },\n"
         << "  \"rendered_output\": {\n";
  if (silence_preroll == 0) {
    stream << "    \"startup\": ";
    write_window_json(stream, rendered.startup, 4);
    stream << ",\n    \"post_mute\": ";
    write_window_json(stream, rendered.post_mute, 4);
  } else {
    stream << "    \"after_preroll\": ";
    write_window_json(stream, rendered.after_preroll, 4);
  }
  stream << "\n  }";
  if (!seam_paths.empty()) {
    stream << ",\n  \"seam_wavs\": {\n";
    size_t path_index = 0;
    for (const auto& [name, seam_path] : seam_paths) {
      stream << "    \"" << name << "\": \""
             << json_escape(seam_path) << "\""
             << (++path_index == seam_paths.size() ? "\n" : ",\n");
    }
    stream << "  }";
  }
  stream << "\n}\n";
}

Preset find_preset(const std::vector<Preset>& presets, const std::string& name) {
  const auto it = std::find_if(presets.begin(), presets.end(),
                               [&](const Preset& p) { return p.name == name; });
  if (it == presets.end() && presets.size() == 1) return presets.front();
  if (it == presets.end()) throw std::runtime_error("unknown preset: " + name);
  return *it;
}

std::string option(int argc, char** argv, const std::string& name) {
  for (int i = 1; i + 1 < argc; ++i) {
    if (argv[i] == name) return argv[i + 1];
  }
  throw std::runtime_error("missing option: " + name);
}

std::optional<std::string> optional_option(int argc, char** argv,
                                           const std::string& name) {
  for (int i = 1; i + 1 < argc; ++i) {
    if (argv[i] == name) return argv[i + 1];
  }
  return std::nullopt;
}

int print_detuning() {
  const std::array<std::pair<const char*, unsigned int>, 8> families{{
      {"hp_freq", 124},
      {"grid_tau", 125},
      {"grid_clip", 127},
      {"plate_bias", 128},
      {"plate_clip", 130},
      {"plate_drift_level", 131},
      {"plate_drift_tau", 132},
      {"plate_comp_level", 133},
  }};
  std::uniform_real_distribution<float> distribution(-0.2f, 0.2f);
  std::cout << "{\n";
  for (size_t family_index = 0; family_index < families.size();
       ++family_index) {
    const auto& [name, seed] = families[family_index];
    std::minstd_rand rng(seed);
    std::cout << "  \"" << name << "\": [";
    for (int stage = 0; stage < 5; ++stage) {
      if (stage != 0) std::cout << ", ";
      std::cout << std::setprecision(9) << distribution(rng);
    }
    std::cout << "]" <<
        (family_index + 1 == families.size() ? "\n" : ",\n");
  }
  std::cout << "}\n";
  return 0;
}

}  // namespace

int main(int argc, char** argv) {
  try {
    if (argc == 2 && std::string(argv[1]) == "--detuning") {
      return print_detuning();
    }
    const std::string input_path = option(argc, argv, "--input");
    const std::string presets_path = option(argc, argv, "--presets");
    const std::string preset_name = option(argc, argv, "--preset");
    const int sample_rate = std::stoi(option(argc, argv, "--sample-rate"));
    const std::string output_path = option(argc, argv, "--output");
    const std::string report_path = option(argc, argv, "--report");
    const auto seam_directory = optional_option(argc, argv, "--seams-dir");
    const auto preroll_option =
        optional_option(argc, argv, "--silence-preroll");
    const size_t silence_preroll = preroll_option.has_value()
                                         ? std::stoull(*preroll_option)
                                         : 0;
    if (sample_rate < 8000 || sample_rate > 384000) {
      throw std::runtime_error("sample rate must be between 8000 and 384000 Hz");
    }

    const Wav input = read_wav(input_path);
    const std::vector<float> source = resample_linear(input, sample_rate);
    const Preset preset = find_preset(read_presets(presets_path), preset_name);

    PushPullAmp released;
    PushPullAmp instrumented;
    released.prepare(sample_rate);
    instrumented.prepare(sample_rate);
    std::vector<float> output(source.size());
    SeamMap seams;
    for (int stage = 1; stage <= 5; ++stage) {
      seams["triode_" + std::to_string(stage)];
    }
    seams["tone_stack"];
    seams["power_amp"];
    seams["cabinet"];
    seams["raw_output"];
    SeamStats rendered;
    SeamAudioMap seam_audio;
    uint64_t mismatch_count = 0;
    float max_difference = 0.0f;

    const auto compare_blocks = [&](const std::vector<float>& released_block,
                                    const std::vector<float>&
                                        instrumented_block) {
      for (size_t i = 0; i < released_block.size(); ++i) {
        if (!std::isfinite(released_block[i]) ||
            !std::isfinite(instrumented_block[i])) {
          throw std::runtime_error("DSP produced non-finite final output");
        }
        const float difference =
            std::abs(released_block[i] - instrumented_block[i]);
        max_difference = std::max(max_difference, difference);
        if (std::bit_cast<uint32_t>(released_block[i]) !=
            std::bit_cast<uint32_t>(instrumented_block[i])) {
          ++mismatch_count;
        }
      }
    };

    for (size_t consumed = 0; consumed < silence_preroll;) {
      const int count = static_cast<int>(std::min(
          silence_preroll - consumed, static_cast<size_t>(kBlockSize)));
      std::vector<float> released_block(static_cast<size_t>(count), 0.0f);
      std::vector<float> instrumented_block = released_block;
      float* released_ptr = released_block.data();
      float* instrumented_ptr = instrumented_block.data();
      set_amp_parameters(released, preset.parameters);
      set_amp_parameters(instrumented, preset.parameters);
      released.process(count, &released_ptr);
      process_instrumented(instrumented, count, &instrumented_ptr, 0, true,
                           nullptr, nullptr);
      compare_blocks(released_block, instrumented_block);
      consumed += static_cast<size_t>(count);
    }

    for (size_t offset = 0; offset < source.size(); offset += kBlockSize) {
      const int count = static_cast<int>(
          std::min(source.size() - offset, static_cast<size_t>(kBlockSize)));
      std::vector<float> released_block(source.begin() + offset,
                                        source.begin() + offset + count);
      std::vector<float> instrumented_block = released_block;
      float* released_ptr = released_block.data();
      float* instrumented_ptr = instrumented_block.data();
      set_amp_parameters(released, preset.parameters);
      set_amp_parameters(instrumented, preset.parameters);
      released.process(count, &released_ptr);
      process_instrumented(
          instrumented, count, &instrumented_ptr, offset,
          silence_preroll != 0, &seams,
          seam_directory.has_value() ? &seam_audio : nullptr);

      compare_blocks(released_block, instrumented_block);

      for (int i = 0; i < count; ++i) {
        const size_t absolute = offset + static_cast<size_t>(i);
        output[absolute] = absolute + silence_preroll <
                                   static_cast<size_t>(kBurnInSamples)
                               ? 0.0f
                               : released_block[i];
        if (silence_preroll != 0) {
          rendered.after_preroll.add(output[absolute]);
        } else if (absolute < static_cast<size_t>(kBurnInSamples)) {
          rendered.startup.add(output[absolute]);
        } else {
          rendered.post_mute.add(output[absolute]);
        }
      }
    }

    if (mismatch_count != 0) {
      throw std::runtime_error(
          "instrumented seam renderer changed released output: " +
          std::to_string(mismatch_count) + " mismatched samples");
    }
    write_float_wav(output_path, sample_rate, output);
    std::map<std::string, std::string> seam_paths;
    if (seam_directory.has_value()) {
      const std::filesystem::path directory(*seam_directory);
      std::filesystem::create_directories(directory);
      const std::filesystem::path report_parent =
          std::filesystem::absolute(report_path).parent_path();
      for (const auto& [name, samples] : seam_audio) {
        const std::filesystem::path seam_path = directory / (name + ".wav");
        write_float_wav(seam_path.string(), sample_rate, samples);
        auto relative =
            std::filesystem::absolute(seam_path).lexically_relative(report_parent);
        seam_paths[name] = relative.empty() ? seam_path.generic_string()
                                            : relative.generic_string();
      }
    }
    write_report(report_path, preset, sample_rate, output.size(), seams,
                 rendered, mismatch_count, max_difference, silence_preroll,
                 seam_paths);
  } catch (const std::exception& error) {
    std::cerr << "reference renderer: " << error.what() << '\n';
    return 1;
  }
  return 0;
}
