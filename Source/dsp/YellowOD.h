#ifndef __faust2hpp_YellowOD_H__
#define __faust2hpp_YellowOD_H__

#include <cmath>

#define uscale(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l;
#define ulscale(x, l, u) std::exp((x + 1.0f) / 2.0f * (std::log(u) - std::log(l)) + std::log(l));

#include "YellowODFaust.h"

class YellowOD
{
public:
  YellowOD()
  {
    faustDsp.buildUserInterface(&faustDsp);
    par_drive = faustDsp.getParameter("drive");
    par_level = faustDsp.getParameter("level");
    par_mix = faustDsp.getParameter("mix");
    par_tone = faustDsp.getParameter("tone");
  }

  ~YellowOD() = default;

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

  inline void set_drive(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_drive = x;
  }
  inline void set_level(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_level = x;
  }
  inline void set_mix(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_mix = x;
  }
  inline void set_tone(FAUSTFLOAT x)
  {
    x += 0.000000e+00f;
    *par_tone = x;
  }

private:
  YellowODFaust faustDsp;

  FAUSTFLOAT* par_drive = nullptr;
  FAUSTFLOAT* par_level = nullptr;
  FAUSTFLOAT* par_mix = nullptr;
  FAUSTFLOAT* par_tone = nullptr;

  void zeroParameters()
  {
    set_drive(0.0f);
    set_level(0.0f);
    set_mix(0.0f);
    set_tone(0.0f);
  }
};

#undef uscale
#undef ulscale

#endif