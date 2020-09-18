#ifndef __faust2hpp_TriodePlate_H__
#define __faust2hpp_TriodePlate_H__

#include <cmath>

#define uscale(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l;
#define ulscale(x, l, u)                                                       \
  std::exp((x + 1.0f) / 2.0f * (std::log(u) - std::log(l)) + std::log(l));

#include "TriodePlateFaust.h"

class TriodePlate {
public:
  TriodePlate() {
    faustDsp.buildUserInterface(&faustDsp);
    par_bias = faustDsp.getParameter("bias");
    par_bias_corner = faustDsp.getParameter("bias_corner");
    par_clip = faustDsp.getParameter("clip");
    par_comp_cap = faustDsp.getParameter("comp_cap");
    par_comp_corner = faustDsp.getParameter("comp_corner");
    par_comp_depth = faustDsp.getParameter("comp_depth");
    par_comp_level = faustDsp.getParameter("comp_level");
    par_comp_offset = faustDsp.getParameter("comp_offset");
    par_comp_ratio = faustDsp.getParameter("comp_ratio");
    par_comp_tau = faustDsp.getParameter("comp_tau");
    par_corner = faustDsp.getParameter("corner");
    par_drift_depth = faustDsp.getParameter("drift_depth");
    par_drift_level = faustDsp.getParameter("drift_level");
    par_drift_tau = faustDsp.getParameter("drift_tau");
    par_scale = faustDsp.getParameter("scale");
  }

  ~TriodePlate() = default;

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

  inline void set_bias(FAUSTFLOAT x) {
    x += 2.367939e+00f;
    *par_bias = uscale(x, -100.0f, +100.0f);
  }
  inline void set_bias_corner(FAUSTFLOAT x) {
    x += 4.893280e-01f;
    *par_bias_corner = ulscale(x, 1e-1f, 1e+3f);
  }
  inline void set_clip(FAUSTFLOAT x) {
    x += -1.075737e+00f;
    *par_clip = uscale(x, -100.0f, +100.0f);
  }
  inline void set_comp_cap(FAUSTFLOAT x) {
    x += 2.536857e+00f;
    *par_comp_cap = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_comp_corner(FAUSTFLOAT x) {
    x += 1.574300e-02f;
    *par_comp_corner = ulscale(x, 1e-1f, 1e+2f);
  }
  inline void set_comp_depth(FAUSTFLOAT x) {
    x += -1.602213e-01f;
    *par_comp_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_comp_level(FAUSTFLOAT x) {
    x += -1.020013e+00f;
    *par_comp_level = uscale(x, -100.0f, +100.0f);
  }
  inline void set_comp_offset(FAUSTFLOAT x) {
    x += 0.000000e+00f;
    *par_comp_offset = uscale(x, -100.0f, +100.0f);
  }
  inline void set_comp_ratio(FAUSTFLOAT x) {
    x += 3.137935e+00f;
    *par_comp_ratio = ulscale(x, 1e0f, 1e+1f);
  }
  inline void set_comp_tau(FAUSTFLOAT x) {
    x += -1.100187e+00f;
    *par_comp_tau = ulscale(x, 1e-3f, 1e0f);
  }
  inline void set_corner(FAUSTFLOAT x) {
    x += 1.179033e-02f;
    *par_corner = ulscale(x, 1e-2f, 1e+2f);
  }
  inline void set_drift_depth(FAUSTFLOAT x) {
    x += -8.250187e-01f;
    *par_drift_depth = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_drift_level(FAUSTFLOAT x) {
    x += 1.016883e-01f;
    *par_drift_level = uscale(x, -100.0f, +100.0f);
  }
  inline void set_drift_tau(FAUSTFLOAT x) {
    x += -1.087854e+00f;
    *par_drift_tau = ulscale(x, 1e-3f, 1e0f);
  }
  inline void set_scale(FAUSTFLOAT x) {
    x += 1.524173e+00f;
    *par_scale = ulscale(x, 1e-1f, 1e+1f);
  }

private:
  TriodePlateFaust faustDsp;

  FAUSTFLOAT *par_bias = nullptr;
  FAUSTFLOAT *par_bias_corner = nullptr;
  FAUSTFLOAT *par_clip = nullptr;
  FAUSTFLOAT *par_comp_cap = nullptr;
  FAUSTFLOAT *par_comp_corner = nullptr;
  FAUSTFLOAT *par_comp_depth = nullptr;
  FAUSTFLOAT *par_comp_level = nullptr;
  FAUSTFLOAT *par_comp_offset = nullptr;
  FAUSTFLOAT *par_comp_ratio = nullptr;
  FAUSTFLOAT *par_comp_tau = nullptr;
  FAUSTFLOAT *par_corner = nullptr;
  FAUSTFLOAT *par_drift_depth = nullptr;
  FAUSTFLOAT *par_drift_level = nullptr;
  FAUSTFLOAT *par_drift_tau = nullptr;
  FAUSTFLOAT *par_scale = nullptr;

  void zeroParameters() {
    set_bias(0.0f);
    set_bias_corner(0.0f);
    set_clip(0.0f);
    set_comp_cap(0.0f);
    set_comp_corner(0.0f);
    set_comp_depth(0.0f);
    set_comp_level(0.0f);
    set_comp_offset(0.0f);
    set_comp_ratio(0.0f);
    set_comp_tau(0.0f);
    set_corner(0.0f);
    set_drift_depth(0.0f);
    set_drift_level(0.0f);
    set_drift_tau(0.0f);
    set_scale(0.0f);
  }
};

#undef uscale
#undef ulscale

#endif