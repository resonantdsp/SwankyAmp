/* ------------------------------------------------------------
name: "TriodeGrid"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef __TriodeGridFaust_H__
#define __TriodeGridFaust_H__

#ifndef __faust2hpp_FaustImpl_H__
#define __faust2hpp_FaustImpl_H__

#include <stdexcept>
#include <unordered_map>

#include "Meta.h"
#include "UI.h"

class FaustImpl : public UI, public Meta {
public:
  FaustImpl() = default;
  ~FaustImpl() = default;

  FAUSTFLOAT *getParameter(const char *name) {
    const auto entry = parameterMap.find(name);
    if (entry == parameterMap.end())
      throw std::invalid_argument(
          std::string("FaustImpl::getParameter: invalid parameter name: ") +
          name);
    return entry->second;
  }

  void setParameter(const char *name, FAUSTFLOAT *value) {
    const auto entry = parameterMap.find(name);
    if (entry != parameterMap.end())
      entry->second = value;
  }

  // blank implementations for UI
  virtual void openTabBox(const char *){};
  virtual void openHorizontalBox(const char *){};
  virtual void openVerticalBox(const char *){};
  virtual void closeBox(){};
  virtual void addButton(const char *, FAUSTFLOAT *){};
  virtual void addCheckButton(const char *, FAUSTFLOAT *){};
  virtual void addVerticalSlider(const char *, FAUSTFLOAT *, FAUSTFLOAT,
                                 FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT){};
  virtual void addHorizontalSlider(const char *, FAUSTFLOAT *, FAUSTFLOAT,
                                   FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT){};
  virtual void
  // use UI entry to expose user parameters
  addNumEntry(const char *label, FAUSTFLOAT *zone, FAUSTFLOAT, FAUSTFLOAT,
              FAUSTFLOAT, FAUSTFLOAT) {
    if (zone == nullptr)
      return;
    parameterMap.insert_or_assign(label, zone);
  }
  virtual void addHorizontalBargraph(const char *, FAUSTFLOAT *, FAUSTFLOAT,
                                     FAUSTFLOAT){};
  virtual void addVerticalBargraph(const char *, FAUSTFLOAT *, FAUSTFLOAT,
                                   FAUSTFLOAT){};
  virtual void addSoundfile(const char *, const char *, Soundfile **){};

  // blank implememtation for Meta
  virtual void declare(const char *, const char *){};

private:
  std::unordered_map<const char *, FAUSTFLOAT *> parameterMap;
};

#endif
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <math.h>

#ifndef FAUSTCLASS
#define FAUSTCLASS TriodeGridFaust
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

class TriodeGridFaust : public FaustImpl {

private:
  float fVec0[2];
  FAUSTFLOAT fEntry0;
  FAUSTFLOAT fEntry1;
  int fSampleRate;
  float fConst0;
  float fConst1;
  FAUSTFLOAT fEntry2;
  float fRec0[2];
  FAUSTFLOAT fEntry3;
  FAUSTFLOAT fEntry4;
  FAUSTFLOAT fEntry5;
  FAUSTFLOAT fEntry6;
  FAUSTFLOAT fEntry7;
  float fRec2[2];
  float fRec1[2];

public:
  void metadata(Meta *m) {
    m->declare("basics.lib/name", "Faust Basic Element Library");
    m->declare("basics.lib/version", "0.1");
    m->declare("filename", "TriodeGrid.dsp");
    m->declare("filters.lib/highpass:author", "Julius O. Smith III");
    m->declare("filters.lib/highpass:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
    m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
    m->declare("filters.lib/name", "Faust Filters Library");
    m->declare("filters.lib/tf1:author", "Julius O. Smith III");
    m->declare("filters.lib/tf1:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
    m->declare("filters.lib/tf1s:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
    m->declare("maths.lib/author", "GRAME");
    m->declare("maths.lib/copyright", "GRAME");
    m->declare("maths.lib/license", "LGPL with exception");
    m->declare("maths.lib/name", "Faust Math Library");
    m->declare("maths.lib/version", "2.3");
    m->declare("name", "TriodeGrid");
    m->declare("platform.lib/name", "Generic Platform Library");
    m->declare("platform.lib/version", "0.1");
    m->declare("signals.lib/name", "Faust Signal Routing Library");
    m->declare("signals.lib/version", "0.0");
  }

  virtual int getNumInputs() { return 1; }
  virtual int getNumOutputs() { return 1; }
  virtual int getInputRate(int channel) {
    int rate;
    switch ((channel)) {
    case 0: {
      rate = 1;
      break;
    }
    default: {
      rate = -1;
      break;
    }
    }
    return rate;
  }
  virtual int getOutputRate(int channel) {
    int rate;
    switch ((channel)) {
    case 0: {
      rate = 1;
      break;
    }
    default: {
      rate = -1;
      break;
    }
    }
    return rate;
  }

  static void classInit(int) {}

  virtual void instanceConstants(int sample_rate) {
    fSampleRate = sample_rate;
    fConst0 =
        std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
    fConst1 = (3.14159274f / fConst0);
  }

  virtual void instanceResetUserInterface() {
    fEntry0 = FAUSTFLOAT(0.0f);
    fEntry1 = FAUSTFLOAT(0.0f);
    fEntry2 = FAUSTFLOAT(0.0f);
    fEntry3 = FAUSTFLOAT(0.0f);
    fEntry4 = FAUSTFLOAT(0.0f);
    fEntry5 = FAUSTFLOAT(0.0f);
    fEntry6 = FAUSTFLOAT(0.0f);
    fEntry7 = FAUSTFLOAT(0.0f);
  }

  virtual void instanceClear() {
    for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
      fVec0[l0] = 0.0f;
    }
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
      fRec0[l1] = 0.0f;
    }
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
      fRec2[l2] = 0.0f;
    }
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
      fRec1[l3] = 0.0f;
    }
  }

  virtual void init(int sample_rate) {
    classInit(sample_rate);
    instanceInit(sample_rate);
  }
  virtual void instanceInit(int sample_rate) {
    instanceConstants(sample_rate);
    instanceResetUserInterface();
    instanceClear();
  }

  virtual TriodeGridFaust *clone() { return new TriodeGridFaust(); }

  virtual int getSampleRate() { return fSampleRate; }

  virtual void buildUserInterface(UI *ui_interface) {
    ui_interface->openVerticalBox("TriodeGrid");
    ui_interface->addNumEntry("cap", &fEntry5, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("clip", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("corner", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("hp_freq", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("level", &fEntry6, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("ratio", &fEntry7, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("smooth", &fEntry4, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("tau", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->closeBox();
  }

  virtual void compute(int count, FAUSTFLOAT **inputs, FAUSTFLOAT **outputs) {
    FAUSTFLOAT *input0 = inputs[0];
    FAUSTFLOAT *output0 = outputs[0];
    float fSlow0 = float(fEntry0);
    float fSlow1 = float(fEntry1);
    float fSlow2 = std::tan((fConst1 * float(fEntry2)));
    float fSlow3 = (1.0f / fSlow2);
    float fSlow4 = (fSlow3 + 1.0f);
    float fSlow5 = (0.0f - (1.0f / (fSlow2 * fSlow4)));
    float fSlow6 = (1.0f / fSlow4);
    float fSlow7 = (1.0f - fSlow3);
    float fSlow8 = float(fEntry3);
    float fSlow9 = (1.0f / ((fConst0 * (fSlow8 * float(fEntry4))) + 1.0f));
    float fSlow10 = (1.0f - fSlow9);
    float fSlow11 = float(fEntry5);
    float fSlow12 = (1.0f / (fSlow11 * ((fConst0 * fSlow8) + 1.0f)));
    float fSlow13 = float(fEntry6);
    float fSlow14 =
        (1.0f - (1.0f / ((fConst0 * (fSlow8 * float(fEntry7))) + 1.0f)));
    float fSlow15 = (0.294117659f / fSlow1);
    for (int i = 0; (i < count); i = (i + 1)) {
      float fTemp0 = float(input0[i]);
      fVec0[0] = fTemp0;
      float fTempFTZ0 = ((fSlow5 * fVec0[1]) -
                         (fSlow6 * ((fSlow7 * fRec0[1]) - (fSlow3 * fTemp0))));
      fRec0[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ0) & 2139095040) ? fTempFTZ0
                                                               : 0.0f);
      float fTempFTZ1 =
          ((fSlow12 * (std::max<float>(0.0f, (fSlow11 - fRec2[1])) *
                       std::max<float>(
                           0.0f, (std::max<float>(0.0f, (fRec0[0] - fSlow13)) -
                                  fRec2[1])))) +
           (fSlow14 * fRec2[1]));
      fRec2[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ1) & 2139095040) ? fTempFTZ1
                                                               : 0.0f);
      float fTempFTZ2 = ((fSlow10 * fRec1[1]) + (fSlow9 * fRec2[0]));
      fRec1[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ2) & 2139095040) ? fTempFTZ2
                                                               : 0.0f);
      float fTemp1 = (fSlow1 + ((fRec0[0] - fRec1[0]) - fSlow0));
      float fTemp2 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow15 * std::max<float>(0.0f, fTemp1))));
      float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
      output0[i] = FAUSTFLOAT(
          (fSlow0 +
           (std::min<float>(0.0f, fTemp1) -
            (fSlow1 * (1.0f - (fTemp3 * (std::fabs(fTemp3) + -2.0f)))))));
      fVec0[1] = fVec0[0];
      fRec0[1] = fRec0[0];
      fRec2[1] = fRec2[0];
      fRec1[1] = fRec1[0];
    }
  }
};

#endif
