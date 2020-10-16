#ifndef __faust2hpp_TriodeGrid_H__
#define __faust2hpp_TriodeGrid_H__

#include <cmath>

#define uscale(x, l, u) (x + 1.0f) / 2.0f * (u - l) + l;
#define ulscale(x, l, u) \
  std::exp((x + 1.0f) / 2.0f * (std::log(u) - std::log(l)) + std::log(l));

#include "TriodeGridFaust.h"

class TriodeGrid
{
public:
  TriodeGrid()
  {
    faustDsp.buildUserInterface(&faustDsp);
    par_cap = faustDsp.getParameter("cap");
    par_clip = faustDsp.getParameter("clip");
    par_corner = faustDsp.getParameter("corner");
    par_hp_freq = faustDsp.getParameter("hp_freq");
    par_level = faustDsp.getParameter("level");
    par_ratio = faustDsp.getParameter("ratio");
    par_smooth = faustDsp.getParameter("smooth");
    par_tau = faustDsp.getParameter("tau");
  }

  ~TriodeGrid() = default;

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

  inline void set_cap(FAUSTFLOAT x)
  {
    x += 1.739606e+00f;
    *par_cap = ulscale(x, 1e-1f, 1e+1f);
  }
  inline void set_clip(FAUSTFLOAT x)
  {
    x += 4.146244e-01f;
    *par_clip = uscale(x, 0.0f, 5.0f);
  }
  inline void set_corner(FAUSTFLOAT x)
  {
    x += 1.847635e-02f;
    *par_corner = uscale(x, 0.0f, 5.0f);
  }
  inline void set_hp_freq(FAUSTFLOAT x)
  {
    x += 4.522112e-01f;
    *par_hp_freq = ulscale(x, 1e-1f, 1e+2f);
  }
  inline void set_level(FAUSTFLOAT x)
  {
    x += 3.357345e-01f;
    *par_level = uscale(x, -5.0f, +5.0f);
  }
  inline void set_ratio(FAUSTFLOAT x)
  {
    x += 1.209004e+00f;
    *par_ratio = ulscale(x, 1e-1f, 1e+4f);
  }
  inline void set_smooth(FAUSTFLOAT x)
  {
    x += 1.528339e+00f;
    *par_smooth = ulscale(x, 1e-5f, 1e+1f);
  }
  inline void set_tau(FAUSTFLOAT x)
  {
    x += -1.357749e+00f;
    *par_tau = ulscale(x, 1e-6f, 1e-3f);
  }

private:
  TriodeGridFaust faustDsp;

  FAUSTFLOAT* par_cap = nullptr;
  FAUSTFLOAT* par_clip = nullptr;
  FAUSTFLOAT* par_corner = nullptr;
  FAUSTFLOAT* par_hp_freq = nullptr;
  FAUSTFLOAT* par_level = nullptr;
  FAUSTFLOAT* par_ratio = nullptr;
  FAUSTFLOAT* par_smooth = nullptr;
  FAUSTFLOAT* par_tau = nullptr;

  void zeroParameters()
  {
    set_cap(0.0f);
    set_clip(0.0f);
    set_corner(0.0f);
    set_hp_freq(0.0f);
    set_level(0.0f);
    set_ratio(0.0f);
    set_smooth(0.0f);
    set_tau(0.0f);
  }
};

#undef uscale
#undef ulscale

#endif