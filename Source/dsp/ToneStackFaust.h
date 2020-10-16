/* ------------------------------------------------------------
name: "ToneStack"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef __ToneStackFaust_H__
#define __ToneStackFaust_H__

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

static float ToneStackFaust_faustpower2_f(float value)
{
  return (value * value);
}

#ifndef FAUSTCLASS
#define FAUSTCLASS ToneStackFaust
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

class ToneStackFaust : public FaustImpl
{
private:
  int fSampleRate;
  float fConst0;
  float fConst1;
  float fConst2;
  FAUSTFLOAT fEntry0;
  float fConst3;
  float fConst4;
  FAUSTFLOAT fEntry1;
  FAUSTFLOAT fEntry2;
  float fRec1[3];
  float fConst5;
  float fConst6;
  float fConst7;
  float fConst8;
  FAUSTFLOAT fEntry3;
  float fConst9;
  float fConst10;
  float fRec2[3];
  float fConst11;
  float fConst12;
  float fRec3[3];
  float fConst13;
  float fConst14;
  float fConst15;
  float fConst16;
  float fConst17;
  float fRec4[3];
  float fConst18;
  FAUSTFLOAT fEntry4;
  float fConst19;
  float fRec0[3];

public:
  void metadata(Meta* m)
  {
    m->declare("basics.lib/name", "Faust Basic Element Library");
    m->declare("basics.lib/version", "0.1");
    m->declare("filename", "ToneStack.dsp");
    m->declare("filters.lib/fir:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/fir:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/iir:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/iir:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
    m->declare("filters.lib/name", "Faust Filters Library");
    m->declare("filters.lib/peak_eq:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/peak_eq:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/tf2:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/tf2:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
    m->declare(
        "filters.lib/tf2s:copyright",
        "Copyright (C) 2003-2019 by Julius O. Smith III "
        "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
    m->declare("maths.lib/author", "GRAME");
    m->declare("maths.lib/copyright", "GRAME");
    m->declare("maths.lib/license", "LGPL with exception");
    m->declare("maths.lib/name", "Faust Math Library");
    m->declare("maths.lib/version", "2.3");
    m->declare("name", "ToneStack");
    m->declare("platform.lib/name", "Generic Platform Library");
    m->declare("platform.lib/version", "0.1");
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
    fConst1 = std::tan((12566.3711f / fConst0));
    fConst2 = (2.0f * (1.0f - (1.0f / ToneStackFaust_faustpower2_f(fConst1))));
    fConst3 = ToneStackFaust_faustpower2_f(fConst0);
    fConst4 = (2.35000007e-05f * fConst3);
    fConst5 = (1.17500003e-05f * fConst0);
    fConst6 = (9.57499981f * fConst0);
    fConst7 = (fConst6 + 138000.0f);
    fConst8 = (2.5f * (fConst0 / fConst7));
    fConst9 = (1.0f / fConst7);
    fConst10 = (138000.0f - fConst6);
    fConst11 = (9.68000052e-16f * fConst3);
    fConst12 = (4.84000026e-16f * fConst0);
    fConst13 = (3.41219997f * fConst0);
    fConst14 = (fConst13 + 33000.0f);
    fConst15 = (0.511829972f * (fConst0 / fConst14));
    fConst16 = (1.0f / fConst14);
    fConst17 = (33000.0f - fConst13);
    fConst18 = (1.0f / fConst1);
    fConst19 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
  }

  virtual void instanceResetUserInterface()
  {
    fEntry0 = FAUSTFLOAT(0.0f);
    fEntry1 = FAUSTFLOAT(0.0f);
    fEntry2 = FAUSTFLOAT(0.0f);
    fEntry3 = FAUSTFLOAT(0.0f);
    fEntry4 = FAUSTFLOAT(0.0f);
  }

  virtual void instanceClear()
  {
    for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) { fRec1[l0] = 0.0f; }
    for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) { fRec2[l1] = 0.0f; }
    for (int l2 = 0; (l2 < 3); l2 = (l2 + 1)) { fRec3[l2] = 0.0f; }
    for (int l3 = 0; (l3 < 3); l3 = (l3 + 1)) { fRec4[l3] = 0.0f; }
    for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) { fRec0[l4] = 0.0f; }
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

  virtual ToneStackFaust* clone() { return new ToneStackFaust(); }

  virtual int getSampleRate() { return fSampleRate; }

  virtual void buildUserInterface(UI* ui_interface)
  {
    ui_interface->openVerticalBox("ToneStack");
    ui_interface->addNumEntry("bass", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("mids", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("presence", &fEntry4, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("selection", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("treble", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->closeBox();
  }

  virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
  {
    FAUSTFLOAT* input0 = inputs[0];
    FAUSTFLOAT* output0 = outputs[0];
    float fSlow0 = float(fEntry0);
    float fSlow1 = (1.0f - fSlow0);
    float fSlow2 = ((0.495000005f * float(fEntry1)) + 0.504999995f);
    float fSlow3 = ToneStackFaust_faustpower2_f(fSlow2);
    float fSlow4 = float(fEntry2);
    float fSlow5 = (0.495000005f * fSlow4);
    float fSlow6 = (fSlow5 + 0.504999995f);
    float fSlow7 = (fSlow3 * fSlow6);
    float fSlow8 = ((0.00147000002f * fSlow6) + (0.0250000004f * fSlow3));
    float fSlow9 = (fSlow8 + 0.0202859994f);
    float fSlow10 = (fSlow3 * ((1.17500003e-05f * fSlow6) + 0.000162149998f));
    float fSlow11 = (fConst0 * fSlow10);
    float fSlow12 = ((fConst0 * (fSlow9 + fSlow11)) + 1.0f);
    float fSlow13 = (0.0f - (fConst4 * (fSlow7 / fSlow12)));
    float fSlow14 = (1.0f / fSlow12);
    float fSlow15 = (1.0f - (fConst0 * (fSlow9 - fSlow11)));
    float fSlow16 = (2.0f * (1.0f - (fConst3 * fSlow10)));
    float fSlow17 = (fConst0 / fSlow12);
    float fSlow18 = (fConst5 * fSlow7);
    float fSlow19 = (fSlow8 + fSlow18);
    float fSlow20 = (fSlow18 - fSlow8);
    float fSlow21 = ((0.495000005f * float(fEntry3)) + 0.504999995f);
    float fSlow22 = (fConst8 * fSlow21);
    float fSlow23 = (0.0f - fSlow22);
    float fSlow24 =
        (484000000.0f
         * (ToneStackFaust_faustpower2_f(fSlow6) + (-0.504999995f - fSlow5)));
    float fSlow25 =
        ((0.200000003f * (fSlow2 * float((fSlow2 <= 0.5f))))
         + (float((fSlow2 > 0.5f)) * ((1.60000002f * fSlow2) + -0.699999988f)));
    float fSlow26 = (fSlow6 * fSlow25);
    float fSlow27 = (fSlow24 - (2.2000001e+10f * fSlow26));
    float fSlow28 = (22000.0f * (0.0f - (2.2e-08f * (fSlow6 + 1.0f))));
    float fSlow29 = (0.0219999999f * fSlow25);
    float fSlow30 = (fSlow28 + (-0.001452f - fSlow29));
    float fSlow31 =
        ((fSlow24
          + (22000.0f
             * ((1000000.0f * (0.0f - fSlow26))
                + (16335.0f * (fSlow4 + -1.0f)))))
         + (1000000.0f * (0.0f - (33000.0f * fSlow25))));
    float fSlow32 = (fConst12 * fSlow31);
    float fSlow33 = ((fConst0 * (fSlow30 + fSlow32)) + -1.0f);
    float fSlow34 = (0.0f - (fConst11 * (fSlow27 / fSlow33)));
    float fSlow35 = (1.0f / fSlow33);
    float fSlow36 = (-2.0f - (fConst11 * fSlow31));
    float fSlow37 = ((fConst0 * (fSlow32 - fSlow30)) + -1.0f);
    float fSlow38 = (fConst0 / fSlow33);
    float fSlow39 = (fSlow28 - fSlow29);
    float fSlow40 = (fConst12 * fSlow27);
    float fSlow41 = (fSlow39 + fSlow40);
    float fSlow42 = (fSlow40 - fSlow39);
    float fSlow43 = (fConst15 * fSlow21);
    float fSlow44 = (0.0f - fSlow43);
    float fSlow45 = (10.0f * float(fEntry4));
    int iSlow46 = (fSlow45 > 0.0f);
    float fSlow47 =
        (fConst19 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow45))));
    float fSlow48 = (iSlow46 ? fConst19 : fSlow47);
    float fSlow49 = ((fConst18 * (fConst18 - fSlow48)) + 1.0f);
    float fSlow50 = ((fConst18 * (fConst18 + fSlow48)) + 1.0f);
    float fSlow51 = (iSlow46 ? fSlow47 : fConst19);
    float fSlow52 = ((fConst18 * (fConst18 + fSlow51)) + 1.0f);
    float fSlow53 = ((fConst18 * (fConst18 - fSlow51)) + 1.0f);
    for (int i = 0; (i < count); i = (i + 1))
    {
      float fTemp0 = float(input0[i]);
      float fTempFTZ0 =
          (fTemp0 - (fSlow14 * ((fSlow15 * fRec1[2]) + (fSlow16 * fRec1[1]))));
      fRec1[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ0) & 2139095040) ? fTempFTZ0
                                                              : 0.0f);
      float fTempFTZ1 =
          (fTemp0
           - (fConst9 * ((fConst10 * fRec2[2]) + (276000.0f * fRec2[1]))));
      fRec2[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ1) & 2139095040) ? fTempFTZ1
                                                              : 0.0f);
      float fTempFTZ2 =
          (fTemp0 - (fSlow35 * ((fSlow36 * fRec3[1]) + (fSlow37 * fRec3[2]))));
      fRec3[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ2) & 2139095040) ? fTempFTZ2
                                                              : 0.0f);
      float fTempFTZ3 =
          (fTemp0
           - (fConst16 * ((fConst17 * fRec4[2]) + (66000.0f * fRec4[1]))));
      fRec4[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ3) & 2139095040) ? fTempFTZ3
                                                              : 0.0f);
      float fTemp1 = (fConst2 * fRec0[1]);
      float fTempFTZ4 =
          (((fSlow1
             * ((4.0f
                 * ((fSlow13 * fRec1[1])
                    + (fSlow17
                       * ((fSlow19 * fRec1[0]) + (fSlow20 * fRec1[2])))))
                + (12.0f * ((fSlow22 * fRec2[0]) + (fSlow23 * fRec2[2])))))
            + (fSlow0
               * ((1.39999998f
                   * ((fSlow34 * fRec3[1])
                      + (fSlow38
                         * ((fSlow41 * fRec3[0]) + (fSlow42 * fRec3[2])))))
                  + (6.0f * ((fSlow43 * fRec4[0]) + (fSlow44 * fRec4[2]))))))
           - (((fRec0[2] * fSlow49) + fTemp1) / fSlow50));
      fRec0[0] =
          ((*reinterpret_cast<int*>(&fTempFTZ4) & 2139095040) ? fTempFTZ4
                                                              : 0.0f);
      output0[i] = FAUSTFLOAT(
          (((fTemp1 + (fRec0[0] * fSlow52)) + (fRec0[2] * fSlow53)) / fSlow50));
      fRec1[2] = fRec1[1];
      fRec1[1] = fRec1[0];
      fRec2[2] = fRec2[1];
      fRec2[1] = fRec2[0];
      fRec3[2] = fRec3[1];
      fRec3[1] = fRec3[0];
      fRec4[2] = fRec4[1];
      fRec4[1] = fRec4[0];
      fRec0[2] = fRec0[1];
      fRec0[1] = fRec0[0];
    }
  }
};

#endif
