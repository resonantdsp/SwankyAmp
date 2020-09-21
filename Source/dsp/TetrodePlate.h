#ifndef __faust2hpp_TetrodePlate_H__
#define __faust2hpp_TetrodePlate_H__

#include <cmath>

#define uscale(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l;
#define ulscale(x, l, u)                                                       \
  std::exp((x + 1.0f) / 2.0f * (std::log(u) - std::log(l)) + std::log(l));

#include "TetrodePlateFaust.h"

class TetrodePlate {
public:
  TetrodePlate() {
    faustDsp.buildUserInterface(&faustDsp);
    par_clip = faustDsp.getParameter("clip");
    par_clip_corner = faustDsp.getParameter("clip_corner");
    par_comp_depth = faustDsp.getParameter("comp_depth");
    par_comp_tau = faustDsp.getParameter("comp_tau");
    par_cross_corner = faustDsp.getParameter("cross_corner");
    par_drift2_depth = faustDsp.getParameter("drift2_depth");
    par_drift2_level = faustDsp.getParameter("drift2_level");
    par_drift_depth = faustDsp.getParameter("drift_depth");
    par_drift_level = faustDsp.getParameter("drift_level");
    par_drift_tau = faustDsp.getParameter("drift_tau");
    par_hp_freq = faustDsp.getParameter("hp_freq");
    par_lp_freq = faustDsp.getParameter("lp_freq");
    par_sag_depth = faustDsp.getParameter("sag_depth");
    par_sag_onset = faustDsp.getParameter("sag_onset");
    par_sag_ratio = faustDsp.getParameter("sag_ratio");
    par_sag_tau = faustDsp.getParameter("sag_tau");
    par_sag_toggle = faustDsp.getParameter("sag_toggle");
    par_scale = faustDsp.getParameter("scale");
  }

  ~TetrodePlate() = default;

  void reset() {
    faustDsp.instanceClear();
    zeroParameters();
  }

  void prepare(int sampleRate) {
    faustDsp.init(sampleRate);
    zeroParameters();
  }

  void process(int count, FAUSTFLOAT **buffer) {
    faustDsp.compute(count, buffer, buffer);
  }

  inline void set_clip(FAUSTFLOAT x) {
    x += 5.141067e-01f;
    *par_clip = uscale(x, 10.0f, 50.0f);
  }
  inline void set_clip_corner(FAUSTFLOAT x) {
    x += 1.071221e+00f;
    *par_clip_corner = ulscale(x, 1e-1f, 1e+2f);
  }
  inline void set_comp_depth(FAUSTFLOAT x) {
    x += -5.449357e-01f;
    *par_comp_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_comp_tau(FAUSTFLOAT x) {
    x += -1.313830e+00f;
    *par_comp_tau = ulscale(x, 1e-3f, 1e0f);
  }
  inline void set_cross_corner(FAUSTFLOAT x) {
    x += 5.966702e-01f;
    *par_cross_corner = ulscale(x, 1e-1f, 1e+2f);
  }
  inline void set_drift2_depth(FAUSTFLOAT x) {
    x += -4.166159e-03f;
    *par_drift2_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_drift2_level(FAUSTFLOAT x) {
    x += 5.644939e-01f;
    *par_drift2_level = uscale(x, -50.0f, +50.0f);
  }
  inline void set_drift_depth(FAUSTFLOAT x) {
    x += 1.685149e-01f;
    *par_drift_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_drift_level(FAUSTFLOAT x) {
    x += 1.146432e+00f;
    *par_drift_level = uscale(x, -100.0f, +100.0f);
  }
  inline void set_drift_tau(FAUSTFLOAT x) {
    x += -2.489241e-01f;
    *par_drift_tau = ulscale(x, 1e-3f, 1e0f);
  }
  inline void set_hp_freq(FAUSTFLOAT x) {
    x += -2.866546e+00f;
    *par_hp_freq = ulscale(x, 1e1f, 1e2f);
  }
  inline void set_lp_freq(FAUSTFLOAT x) {
    x += 4.812430e-01f;
    *par_lp_freq = ulscale(x, 5e3f, 15e3f);
  }
  inline void set_sag_depth(FAUSTFLOAT x) {
    x += -2.201614e-03f;
    *par_sag_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_sag_onset(FAUSTFLOAT x) {
    x += -4.477669e-04f;
    *par_sag_onset = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_sag_ratio(FAUSTFLOAT x) {
    x += -2.917738e-03f;
    *par_sag_ratio = ulscale(x, 1e0f, 1e+1f);
  }
  inline void set_sag_tau(FAUSTFLOAT x) {
    x += 2.090635e-03f;
    *par_sag_tau = ulscale(x, 1e-2f, 5e-1f);
  }
  inline void set_sag_toggle(FAUSTFLOAT x) {
    x += -9.873799e-01f;
    *par_sag_toggle = uscale(x, 0.0f, 1.0f);
  }
  inline void set_scale(FAUSTFLOAT x) {
    x += 3.344047e-01f;
    *par_scale = ulscale(x, 1e-2f, 1e+2f);
  }

private:
  TetrodePlateFaust faustDsp;

  FAUSTFLOAT *par_clip = nullptr;
  FAUSTFLOAT *par_clip_corner = nullptr;
  FAUSTFLOAT *par_comp_depth = nullptr;
  FAUSTFLOAT *par_comp_tau = nullptr;
  FAUSTFLOAT *par_cross_corner = nullptr;
  FAUSTFLOAT *par_drift2_depth = nullptr;
  FAUSTFLOAT *par_drift2_level = nullptr;
  FAUSTFLOAT *par_drift_depth = nullptr;
  FAUSTFLOAT *par_drift_level = nullptr;
  FAUSTFLOAT *par_drift_tau = nullptr;
  FAUSTFLOAT *par_hp_freq = nullptr;
  FAUSTFLOAT *par_lp_freq = nullptr;
  FAUSTFLOAT *par_sag_depth = nullptr;
  FAUSTFLOAT *par_sag_onset = nullptr;
  FAUSTFLOAT *par_sag_ratio = nullptr;
  FAUSTFLOAT *par_sag_tau = nullptr;
  FAUSTFLOAT *par_sag_toggle = nullptr;
  FAUSTFLOAT *par_scale = nullptr;

  void zeroParameters() {
    set_clip(0.0f);
    set_clip_corner(0.0f);
    set_comp_depth(0.0f);
    set_comp_tau(0.0f);
    set_cross_corner(0.0f);
    set_drift2_depth(0.0f);
    set_drift2_level(0.0f);
    set_drift_depth(0.0f);
    set_drift_level(0.0f);
    set_drift_tau(0.0f);
    set_hp_freq(0.0f);
    set_lp_freq(0.0f);
    set_sag_depth(0.0f);
    set_sag_onset(0.0f);
    set_sag_ratio(0.0f);
    set_sag_tau(0.0f);
    set_sag_toggle(0.0f);
    set_scale(0.0f);
  }
};

#undef uscale
#undef ulscale

#endif