#ifndef __faust2hpp_DigiBoost_H__
#define __faust2hpp_DigiBoost_H__

#include <cmath>

#define uscale(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l;
#define ulscale(x, l, u) std::exp((x + 1.0f) / 2.0f * (std::log(u) - std::log(l)) + std::log(l));

#include "DigiBoostFaust.h"

class DigiBoost
{
public:
  DigiBoost()
  {
    faustDsp.buildUserInterface(&faustDsp);
    par_drift = faustDsp.getParameter("drift");
    par_high_pass = faustDsp.getParameter("high_pass");
    par_input_level = faustDsp.getParameter("input_level");
    par_low_pass = faustDsp.getParameter("low_pass");
    par_mix = faustDsp.getParameter("mix");
    par_saturation = faustDsp.getParameter("saturation");
  }

  ~DigiBoost() = default;

  void reset()
  {
    faustDsp.instanceClear();
    zeroParameters();
  }

  void prepare(int sampleRate)
  {
    faustDsp.init(sampleRate);
    zeroParameters();
  }

  void process(int count, FAUSTFLOAT** buffer)
  {
    faustDsp.compute(count, buffer, buffer);
  }

  inline void set_drift(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_drift = ulscale(x, 1e0f, 5e2f);
  }
  inline void set_high_pass(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_high_pass = ulscale(x, 1e1f, 4e2f);
  }
  inline void set_input_level(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_input_level = x;
  }
  inline void set_low_pass(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_low_pass = ulscale(x, 6e2f, 20e3f);
  }
  inline void set_mix(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_mix = x;
  }
  inline void set_saturation(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_saturation = ulscale(x, 1e-1f, 1e2f);
  }

private:
  DigiBoostFaust faustDsp;

  FAUSTFLOAT* par_drift = nullptr;
  FAUSTFLOAT* par_high_pass = nullptr;
  FAUSTFLOAT* par_input_level = nullptr;
  FAUSTFLOAT* par_low_pass = nullptr;
  FAUSTFLOAT* par_mix = nullptr;
  FAUSTFLOAT* par_saturation = nullptr;

  void zeroParameters()
  {
    set_drift(0.0f);
    set_high_pass(0.0f);
    set_input_level(0.0f);
    set_low_pass(0.0f);
    set_mix(0.0f);
    set_saturation(0.0f);
  }
};

#undef uscale
#undef ulscale

#endif