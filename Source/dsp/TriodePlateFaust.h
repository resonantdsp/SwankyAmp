/* ------------------------------------------------------------
name: "TriodePlate"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef __TriodePlateFaust_H__
#define __TriodePlateFaust_H__

#ifndef __faust2hpp_FaustImpl_H__
#define __faust2hpp_FaustImpl_H__

#include <stdexcept>
#include <unordered_map>

#include "Meta.h"
#include "UI.h"

class FaustImpl : public UI, public Meta
{
public:
  FaustImpl() = default;
  ~FaustImpl() = default;

  FAUSTFLOAT* getParameter(const char* name)
  {
    const auto entry = parameterMap.find(name);
    if (entry == parameterMap.end())
      throw std::invalid_argument(
          std::string("FaustImpl::getParameter: invalid parameter name: ")
          + name);
    return entry->second;
  }

  void setParameter(const char* name, FAUSTFLOAT* value)
  {
    const auto entry = parameterMap.find(name);
    if (entry != parameterMap.end()) entry->second = value;
  }

  // blank implementations for UI
  virtual void openTabBox(const char*){};
  virtual void openHorizontalBox(const char*){};
  virtual void openVerticalBox(const char*){};
  virtual void closeBox(){};
  virtual void addButton(const char*, FAUSTFLOAT*){};
  virtual void addCheckButton(const char*, FAUSTFLOAT*){};
  virtual void addVerticalSlider(
      const char*,
      FAUSTFLOAT*,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT){};
  virtual void addHorizontalSlider(
      const char*,
      FAUSTFLOAT*,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT){};
  virtual void
  // use UI entry to expose user parameters
  addNumEntry(
      const char* label,
      FAUSTFLOAT* zone,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT,
      FAUSTFLOAT)
  {
    if (zone == nullptr) return;
    parameterMap.insert_or_assign(label, zone);
  }
  virtual void
  addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT){};
  virtual void
  addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT){};
  virtual void addSoundfile(const char*, const char*, Soundfile**){};

  // blank implememtation for Meta
  virtual void declare(const char*, const char*){};

private:
  std::unordered_map<const char*, FAUSTFLOAT*> parameterMap;
};

#endif
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <math.h>

#ifndef FAUSTCLASS
#define FAUSTCLASS TriodePlateFaust
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

class TriodePlateFaust : public FaustImpl
{
private:
  FAUSTFLOAT fEntry0;
  FAUSTFLOAT fEntry1;
  FAUSTFLOAT fEntry2;
  int fSampleRate;
  float fConst0;
  FAUSTFLOAT fEntry3;
  FAUSTFLOAT fEntry4;
  FAUSTFLOAT fEntry5;
  FAUSTFLOAT fEntry6;
  FAUSTFLOAT fEntry7;
  FAUSTFLOAT fEntry8;
  FAUSTFLOAT fEntry9;
  FAUSTFLOAT fEntry10;
  FAUSTFLOAT fEntry11;
  float fConst1;
  FAUSTFLOAT fEntry12;
  float fRec2[2];
  FAUSTFLOAT fEntry13;
  float fRec1[2];
  FAUSTFLOAT fEntry14;
  float fVec0[2];
  float fRec0[2];

public:
  void metadata(Meta* m)
  {
    m->declare("basics.lib/name", "Faust Basic Element Library");
    m->declare("basics.lib/version", "0.1");
    m->declare("filename", "TriodePlate.dsp");
    m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
    m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
    m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/lowpass:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/name", "Faust Filters Library");
    m->declare("filters.lib/tf1:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/tf1:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/tf1s:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
    m->declare("maths.lib/author", "GRAME");
    m->declare("maths.lib/copyright", "GRAME");
    m->declare("maths.lib/license", "LGPL with exception");
    m->declare("maths.lib/name", "Faust Math Library");
    m->declare("maths.lib/version", "2.3");
    m->declare("name", "TriodePlate");
    m->declare("platform.lib/name", "Generic Platform Library");
    m->declare("platform.lib/version", "0.1");
    m->declare("signals.lib/name", "Faust Signal Routing Library");
    m->declare("signals.lib/version", "0.0");
  }

  virtual int getNumInputs() { return 1; }
  virtual int getNumOutputs() { return 1; }
  virtual int getInputRate(int channel)
  {
    int rate;
    switch ((channel))
    {
    case 0:
    {
      rate = 1;
      break;
    }
    default:
    {
      rate = -1;
      break;
    }
    }
    return rate;
  }
  virtual int getOutputRate(int channel)
  {
    int rate;
    switch ((channel))
    {
    case 0:
    {
      rate = 1;
      break;
    }
    default:
    {
      rate = -1;
      break;
    }
    }
    return rate;
  }

  static void classInit(int) {}

  virtual void instanceConstants(int sample_rate)
  {
    fSampleRate = sample_rate;
    fConst0 =
        std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
    fConst1 = (1.0f / fConst0);
  }

  virtual void instanceResetUserInterface()
  {
    fEntry0 = FAUSTFLOAT(0.0f);
    fEntry1 = FAUSTFLOAT(0.0f);
    fEntry2 = FAUSTFLOAT(0.0f);
    fEntry3 = FAUSTFLOAT(0.0f);
    fEntry4 = FAUSTFLOAT(0.0f);
    fEntry5 = FAUSTFLOAT(0.0f);
    fEntry6 = FAUSTFLOAT(0.0f);
    fEntry7 = FAUSTFLOAT(0.0f);
    fEntry8 = FAUSTFLOAT(0.0f);
    fEntry9 = FAUSTFLOAT(0.0f);
    fEntry10 = FAUSTFLOAT(0.0f);
    fEntry11 = FAUSTFLOAT(0.0f);
    fEntry12 = FAUSTFLOAT(0.0f);
    fEntry13 = FAUSTFLOAT(0.0f);
    fEntry14 = FAUSTFLOAT(0.0f);
  }

  virtual void instanceClear()
  {
    for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) { fRec2[l0] = 0.0f; }
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) { fRec1[l1] = 0.0f; }
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) { fVec0[l2] = 0.0f; }
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) { fRec0[l3] = 0.0f; }
  }

  virtual void init(int sample_rate)
  {
    classInit(sample_rate);
    instanceInit(sample_rate);
  }
  virtual void instanceInit(int sample_rate)
  {
    instanceConstants(sample_rate);
    instanceResetUserInterface();
    instanceClear();
  }

  virtual TriodePlateFaust* clone() { return new TriodePlateFaust(); }

  virtual int getSampleRate() { return fSampleRate; }

  virtual void buildUserInterface(UI* ui_interface)
  {
    ui_interface->openVerticalBox("TriodePlate");
    ui_interface->addNumEntry("bias", &fEntry6, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("bias_corner", &fEntry9, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("clip", &fEntry5, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_cap", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_corner", &fEntry14, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_depth", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_level", &fEntry4, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_offset", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_ratio", &fEntry13, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("comp_tau", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("corner", &fEntry7, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("drift_depth", &fEntry10, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("drift_level", &fEntry12, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("drift_tau", &fEntry11, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("scale", &fEntry8, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->closeBox();
  }

  virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
  {
    FAUSTFLOAT* input0 = inputs[0];
    FAUSTFLOAT* output0 = outputs[0];
    float fSlow0 = float(fEntry0);
    float fSlow1 = float(fEntry1);
    float fSlow2 = float(fEntry2);
    float fSlow3 = float(fEntry3);
    float fSlow4 = (1.0f / (fSlow2 * ((fConst0 * fSlow3) + 1.0f)));
    float fSlow5 = float(fEntry4);
    float fSlow6 = float(fEntry5);
    float fSlow7 = float(fEntry6);
    float fSlow8 = float(fEntry7);
    float fSlow9 = (fSlow8 + fSlow6);
    float fSlow10 = float(fEntry8);
    float fSlow11 = float(fEntry9);
    float fSlow12 = (0.294117659f / fSlow11);
    float fSlow13 = (0.294117659f / fSlow8);
    float fSlow14 = float(fEntry10);
    float fSlow15 = float(fEntry11);
    int iSlow16 = (std::fabs(fSlow15) < 1.1920929e-07f);
    float fSlow17 =
        (iSlow16 ? 0.0f
                 : std::exp((0.0f - (fConst1 / (iSlow16 ? 1.0f : fSlow15)))));
    float fSlow18 = float(fEntry12);
    float fSlow19 = (1.0f - fSlow17);
    float fSlow20 =
        ((1.0f / ((fConst0 * (fSlow3 * float(fEntry13))) + 1.0f)) + -1.0f);
    float fSlow21 = float(fEntry14);
    float fSlow22 = (fSlow21 + fSlow6);
    float fSlow23 = (0.294117659f / fSlow21);
    for (int i = 0; (i < count); i = (i + 1))
    {
      float fTemp0 = float(input0[i]);
      float fTemp1 = (fSlow7 + ((fSlow10 * fTemp0) - fSlow11));
      float fTemp2 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow12 * std::min<float>(0.0f, fTemp1))));
      float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
      float fTemp4 =
          (fSlow7
           - (fSlow9
              + (std::max<float>(0.0f, fTemp1)
                 + (fSlow11
                    * ((fTemp3 * (std::fabs(fTemp3) + -2.0f)) + 1.0f)))));
      float fTemp5 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow13 * std::min<float>(0.0f, fTemp4))));
      float fTemp6 = (fTemp5 * (std::fabs(fTemp5) + -2.0f));
      float fTemp7 =
          (std::max<float>(0.0f, fTemp4)
           + (fSlow8 * ((fTemp6 * (std::fabs(fTemp6) + -2.0f)) + 1.0f)));
      float fTempFTZ0 =
          ((fRec2[1] * fSlow17)
           + ((std::max<float>(fSlow18, (fSlow6 + fTemp7)) - fSlow18)
              * fSlow19));
      fRec2[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ0) & 2139095040) ? fTempFTZ0
                                                              : 0.0f);
      float fTemp8 = (fSlow14 * fRec2[0]);
      float fTempFTZ1 =
          ((fSlow4
            * (std::max<float>(0.0f, (fSlow2 - fRec1[1]))
               * std::max<float>(
                   0.0f,
                   ((std::max<float>(fSlow5, (fSlow6 + (fTemp7 - fTemp8)))
                     - fRec1[1])
                    - fSlow5))))
           - (fSlow20 * fRec1[1]));
      fRec1[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ1) & 2139095040) ? fTempFTZ1
                                                              : 0.0f);
      float fTemp9 = (fSlow1 * fRec1[0]);
      float fTemp10 = (fSlow22 + ((fTemp7 - (fTemp8 + fTemp9)) - fSlow0));
      float fTemp11 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow23 * std::max<float>(0.0f, fTemp10))));
      float fTemp12 = (fTemp11 * (std::fabs(fTemp11) + -2.0f));
      float fTemp13 =
          (fSlow0
           + ((fTemp9 + std::min<float>(0.0f, fTemp10))
              - (fSlow21 * (1.0f - (fTemp12 * (std::fabs(fTemp12) + -2.0f))))));
      fVec0[0] = fTemp13;
      float fTempFTZ2 =
          ((0.863271236f * (fTemp13 + fVec0[1])) - (0.726542532f * fRec0[1]));
      fRec0[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ2) & 2139095040) ? fTempFTZ2
                                                              : 0.0f);
      output0[i] = FAUSTFLOAT(fRec0[0]);
      fRec2[1] = fRec2[0];
      fRec1[1] = fRec1[0];
      fVec0[1] = fVec0[0];
      fRec0[1] = fRec0[0];
    }
  }
};

#endif
