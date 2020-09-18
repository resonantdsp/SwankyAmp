#ifndef __PushPullAmP_H__
#define __PushPullAmP_H__

#include <cmath>

#define USCALE(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l
#define ULSCALE(x, l, u) std::exp(USCALE(x, std::log(l), std::log(u)));
#define IUSCALE(x, l, u) (x - l) / (u - l) * 2.0f - 1.0f
#define IULSCALE(x, l, u) IUSCALE(std::log(x), std::log(l), std::log(u))

#define LINEAR2DB(x) 20.0f * std::log10(x)
#define DB2LINEAR(x) std::pow(10.0f, x / 20.0f)

#define NUM_SWEEP_BINS 10

#include "Cabinet.h"
#include "TetrodeGrid.h"
#include "TetrodePlate.h"
#include "ToneStackF.h"
#include "TriodeGrid.h"
#include "TriodePlate.h"

inline void scaleBuffer(int count, FAUSTFLOAT **buffer, FAUSTFLOAT scale) {
  for (int i = 0; i < count; i++)
    buffer[0][i] *= scale;
}

inline float interp1d(float x, float xl, float xh, const float *edges,
                      size_t n) {
  const float xu = (x - xl) / (xh - xl);
  const float xbin = xu * (float)n;
  size_t i = 0;
  if (xbin >= n)
    i = n - 1;
  else if (xbin >= 0)
    i = (int)(xbin);
  const float m = edges[i + 1] - edges[i];
  const float b = edges[i];
  return m * (xbin - i) + b;
}

class PreAmp {
public:
  PreAmp() = default;
  ~PreAmp() = default;

  void reset() {
    for (size_t i = 0; i < MAX_STAGES; i++) {
      triodeGrid[i].reset();
      triodePlate[i].reset();
    }
    resetParameters();
  }

  void prepare(int sampleRate) {
    for (size_t i = 0; i < MAX_STAGES; i++) {
      triodeGrid[i].prepare(sampleRate);
      triodePlate[i].prepare(sampleRate);
    }
    resetParameters();
  }

  void process(int count, FAUSTFLOAT **buffer) {
    const float triodeScale = 3.501334e+01f;
    scaleBuffer(count, buffer, drive);
    for (size_t i = 0; i < numStagesActive(); i++) {
      if (i > 0)
        scaleBuffer(count, buffer, 1.0f / overhead);
      triodeGrid[i].process(count, buffer);
      triodePlate[i].process(count, buffer);
      if (i == 0)
        // scale down to avoid growing rms
        scaleBuffer(count, buffer, 1.0f / triodeScale);
      else
        // also scale down the overhead factor
        scaleBuffer(count, buffer, 1.0f / triodeScale * overhead);
    }
    // scale up to nominal output rms
    scaleBuffer(count, buffer, triodeScale);
  }

  // TDOO: randomized stages

  inline void set_hp_freq(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodeGrid[i].set_hp_freq(x);
  }
  inline void set_grid_tau(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodeGrid[i].set_tau(x);
  }
  inline void set_grid_ratio(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodeGrid[i].set_ratio(x);
  }
  inline void set_grid_level(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodeGrid[i].set_level(x);
  }
  inline void set_grid_clip(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodeGrid[i].set_clip(x);
  }
  inline void set_plate_bias(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodePlate[i].set_bias(x);
  }
  inline void set_plate_comp_ratio(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodePlate[i].set_comp_ratio(x);
  }
  inline void set_plate_comp_level(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodePlate[i].set_comp_level(x);
  }
  inline void set_plate_comp_offset(FAUSTFLOAT x) {
    for (size_t i = 0; i < MAX_STAGES; i++)
      triodePlate[i].set_comp_offset(x);
  }

  inline void set_num_stages(int x) { numStages = x; }
  inline void set_drive(FAUSTFLOAT x) { drive = ULSCALE(x, 1e0f, 2e3f); }
  inline float get_drive() const { return IULSCALE(drive, 1e0f, 2e3f); }
  inline void set_overhead(FAUSTFLOAT x) { overhead = ULSCALE(x, 1e-1f, 1e1f); }
  inline float get_overhead() const { return IULSCALE(overhead, 1e-1f, 1e1f); }

private:
  static const size_t MAX_STAGES = 5;

  FAUSTFLOAT drive = 0.0f;
  FAUSTFLOAT overhead = 0.0f;
  int numStages = 0;

  TriodeGrid triodeGrid[MAX_STAGES];
  TriodePlate triodePlate[MAX_STAGES];

  inline size_t numStagesActive() const {
    size_t num = numStages > MAX_STAGES ? MAX_STAGES : numStages;
    num = num < 1 ? 1 : num;
    return num;
  }

  void resetParameters() {
    set_num_stages(3);
    set_drive(0.0f);
    set_overhead(0.0f);
  }
};

class PowerAmp {
public:
  PowerAmp() = default;
  ~PowerAmp() = default;

  void reset() {
    tetrodeGrid.reset();
    tetrodePlate.reset();
    resetParameters();
  }

  void prepare(int sampleRate) {
    tetrodeGrid.prepare(sampleRate);
    tetrodePlate.prepare(sampleRate);
    resetParameters();
  }

  void process(int count, FAUSTFLOAT **buffer) {
    scaleBuffer(count, buffer, drive);
    tetrodeGrid.process(count, buffer);
    tetrodePlate.process(count, buffer);
  }

  inline void set_hp_freq(FAUSTFLOAT x) { tetrodeGrid.set_hp_freq(x); }
  inline void set_grid_tau(FAUSTFLOAT x) { tetrodeGrid.set_tau(x); }
  inline void set_grid_ratio(FAUSTFLOAT x) { tetrodeGrid.set_ratio(x); }
  inline void set_plate_comp_depth(FAUSTFLOAT x) {
    tetrodePlate.set_comp_depth(x);
  }
  inline void set_plate_sag_tau(FAUSTFLOAT x) { tetrodePlate.set_sag_tau(x); }
  inline void set_plate_sag_toggle(FAUSTFLOAT x) {
    tetrodePlate.set_sag_toggle(x);
  }
  inline void set_plate_sag_depth(FAUSTFLOAT x) {
    tetrodePlate.set_sag_depth(x);
  }
  inline void set_plate_sag_ratio(FAUSTFLOAT x) {
    tetrodePlate.set_sag_ratio(x);
  }
  inline void set_plate_sag_onset(FAUSTFLOAT x) {
    tetrodePlate.set_sag_onset(x);
  }

  inline void set_drive(FAUSTFLOAT x) { drive = ULSCALE(x, 5e-1f, 5e2f); }
  inline float get_drive() const { return IULSCALE(drive, 5e-1f, 5e2f); }

private:
  TetrodeGrid tetrodeGrid;
  TetrodePlate tetrodePlate;

  FAUSTFLOAT drive;

  void resetParameters() { set_drive(0.0f); }
};

class PushPullAmp {
public:
  PushPullAmp() = default;
  ~PushPullAmp() = default;

  void reset() {
    preAmp.reset();
    toneStackF.reset();
    powerAmp.reset();
    cabinet.reset();
    resetParameters();
  }

  void prepare(int sampleRate) {
    preAmp.prepare(sampleRate);
    toneStackF.prepare(sampleRate);
    powerAmp.prepare(sampleRate);
    cabinet.prepare(sampleRate);
    resetParameters();
  }

  void process(int count, FAUSTFLOAT **buffer) {
    scaleBuffer(count, buffer, DB2LINEAR(inputLevel));

    preAmp.process(count, buffer);

    const float tonestackFactor = 5.302220e-01f;
    toneStackF.process(count, buffer);
    scaleBuffer(count, buffer, 1.0f / tonestackFactor);

    powerAmp.process(count, buffer);

    if (cabinetOn) {
      const float cabinetFactor = 2.723280e+00f;
      cabinet.process(count, buffer);
      scaleBuffer(count, buffer, 1.0f / cabinetFactor);
    }

    const float scale = interp1d(preAmp.get_drive(), -1.0f, 1.0f,
                                 preAmpDriveScale, (size_t)NUM_SWEEP_BINS) *
                        interp1d(powerAmp.get_drive(), -1.0f, 1.0f,
                                 powerAmpDriveScale, (size_t)NUM_SWEEP_BINS) *
                        DB2LINEAR(outputLevel);
    scaleBuffer(count, buffer, scale);
  }

  inline void set_triode_num_stages(int x) { preAmp.set_num_stages(x); }
  inline void set_triode_overhead(FAUSTFLOAT x) { preAmp.set_overhead(x); }
  inline void set_triode_hp_freq(FAUSTFLOAT x) { preAmp.set_hp_freq(x); }
  inline void set_triode_grid_tau(FAUSTFLOAT x) { preAmp.set_grid_tau(x); }
  inline void set_triode_grid_ratio(FAUSTFLOAT x) { preAmp.set_grid_ratio(x); }
  inline void set_triode_grid_level(FAUSTFLOAT x) { preAmp.set_grid_level(x); }
  inline void set_triode_grid_clip(FAUSTFLOAT x) { preAmp.set_grid_clip(x); }
  inline void set_triode_plate_bias(FAUSTFLOAT x) { preAmp.set_plate_bias(x); }
  inline void set_triode_plate_comp_ratio(FAUSTFLOAT x) {
    preAmp.set_plate_comp_ratio(x);
  }
  inline void set_triode_plate_comp_level(FAUSTFLOAT x) {
    preAmp.set_plate_comp_level(x);
  }
  inline void set_triode_plate_comp_offset(FAUSTFLOAT x) {
    preAmp.set_plate_comp_offset(x);
  }
  inline void set_triode_drive(FAUSTFLOAT x) { preAmp.set_drive(x); }

  inline void set_tetrode_hp_freq(FAUSTFLOAT x) { powerAmp.set_hp_freq(x); }
  inline void set_tetrode_grid_tau(FAUSTFLOAT x) { powerAmp.set_grid_tau(x); }
  inline void set_tetrode_grid_ratio(FAUSTFLOAT x) {
    powerAmp.set_grid_ratio(x);
  }

  inline void set_tetrode_plate_comp_depth(FAUSTFLOAT x) {
    powerAmp.set_plate_comp_depth(x);
  }
  inline void set_tetrode_plate_sag_tau(FAUSTFLOAT x) {
    powerAmp.set_plate_sag_tau(x);
  }
  inline void set_tetrode_plate_sag_toggle(FAUSTFLOAT x) {
    powerAmp.set_plate_sag_toggle(x);
  }
  inline void set_tetrode_plate_sag_depth(FAUSTFLOAT x) {
    powerAmp.set_plate_sag_depth(x);
  }
  inline void set_tetrode_plate_sag_ratio(FAUSTFLOAT x) {
    powerAmp.set_plate_sag_ratio(x);
  }
  inline void set_tetrode_plate_sag_onset(FAUSTFLOAT x) {
    powerAmp.set_plate_sag_onset(x);
  }
  inline void set_tetrode_drive(FAUSTFLOAT x) { powerAmp.set_drive(x); }

  inline void set_tonestack_bass(FAUSTFLOAT x) { toneStackF.set_bass(x); }
  inline void set_tonestack_mids(FAUSTFLOAT x) { toneStackF.set_mids(x); }
  inline void set_tonestack_treble(FAUSTFLOAT x) { toneStackF.set_treble(x); }
  inline void set_tonestack_presence(FAUSTFLOAT x) {
    toneStackF.set_presence(x);
  }

  inline void set_cabinet_brightness(FAUSTFLOAT x) {
    cabinet.set_brightness(x);
  }
  inline void set_cabinet_distance(FAUSTFLOAT x) { cabinet.set_distance(x); }

  inline void set_input_level(FAUSTFLOAT x) {
    inputLevel = USCALE(x, -35.0f, 35.0f);
  }
  inline void set_output_level(FAUSTFLOAT x) {
    outputLevel = USCALE(x, -35.0f, 35.0f);
  }
  inline void set_cabinet_on(bool x) { cabinetOn = x; }

private:
  PreAmp preAmp;
  ToneStackF toneStackF;
  PowerAmp powerAmp;
  Cabinet cabinet;

  FAUSTFLOAT inputLevel = 0.0f;
  FAUSTFLOAT outputLevel = 0.0f;
  bool cabinetOn = true;

  const float preAmpDriveScale[NUM_SWEEP_BINS + 1] = {
      2.132676e-03f, 1.393774e-03f, 1.249533e-03f, 1.266841e-03f,
      1.324153e-03f, 1.461887e-03f, 1.597716e-03f, 1.623120e-03f,
      1.625593e-03f, 1.678839e-03f, 1.798028e-03f};

  const float powerAmpDriveScale[NUM_SWEEP_BINS + 1] = {
      1.249540e+00f, 9.394168e-01f, 8.825729e-01f, 8.955081e-01f,
      9.266342e-01f, 9.999998e-01f, 1.175000e+00f, 1.551158e+00f,
      2.276709e+00f, 3.587572e+00f, 5.770323e+00f};

  void resetParameters() {
    set_input_level(0.0f);
    set_output_level(0.0f);
  }
};

#undef USCALE
#undef ULSCALE
#undef IUSCALE
#undef IULSCALE
#undef LINEAR2DB
#undef DB2LINEAR

#endif