/* ------------------------------------------------------------
name: "Cabinet"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef __CabinetFaust_H__
#define __CabinetFaust_H__

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

static float CabinetFaust_faustpower2_f(float value) { return (value * value); }

#ifndef FAUSTCLASS
#define FAUSTCLASS CabinetFaust
#endif

#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

class CabinetFaust : public FaustImpl {

private:
  FAUSTFLOAT fEntry0;
  FAUSTFLOAT fEntry1;
  int fSampleRate;
  float fConst0;
  float fConst1;
  float fConst2;
  float fConst3;
  float fConst4;
  float fConst5;
  float fConst6;
  float fConst7;
  float fConst8;
  float fConst9;
  float fConst10;
  float fConst11;
  float fConst12;
  float fConst13;
  float fConst14;
  float fConst15;
  float fConst16;
  float fConst17;
  float fConst18;
  float fConst19;
  float fConst20;
  float fConst21;
  float fConst22;
  float fConst23;
  float fConst24;
  float fConst25;
  float fConst26;
  FAUSTFLOAT fEntry2;
  FAUSTFLOAT fEntry3;
  FAUSTFLOAT fEntry4;
  FAUSTFLOAT fEntry5;
  FAUSTFLOAT fEntry6;
  FAUSTFLOAT fEntry7;
  FAUSTFLOAT fEntry8;
  FAUSTFLOAT fEntry9;
  FAUSTFLOAT fEntry10;
  FAUSTFLOAT fEntry11;
  FAUSTFLOAT fEntry12;
  FAUSTFLOAT fEntry13;
  FAUSTFLOAT fEntry14;
  FAUSTFLOAT fEntry15;
  FAUSTFLOAT fEntry16;
  float fRec26[3];
  float fRec25[3];
  float fVec0[2];
  float fRec24[2];
  float fRec23[3];
  float fVec1[2];
  float fRec22[2];
  float fRec21[3];
  float fRec20[3];
  float fRec19[3];
  FAUSTFLOAT fEntry17;
  float fRec30[2];
  float fRec29[3];
  float fRec28[3];
  float fRec27[3];
  FAUSTFLOAT fEntry18;
  FAUSTFLOAT fEntry19;
  float fConst27;
  float fRec18[3];
  FAUSTFLOAT fEntry20;
  FAUSTFLOAT fEntry21;
  float fRec17[3];
  FAUSTFLOAT fEntry22;
  FAUSTFLOAT fEntry23;
  float fRec16[3];
  FAUSTFLOAT fEntry24;
  FAUSTFLOAT fEntry25;
  float fRec15[3];
  FAUSTFLOAT fEntry26;
  FAUSTFLOAT fEntry27;
  float fRec14[3];
  FAUSTFLOAT fEntry28;
  FAUSTFLOAT fEntry29;
  float fRec13[3];
  FAUSTFLOAT fEntry30;
  FAUSTFLOAT fEntry31;
  float fRec12[3];
  FAUSTFLOAT fEntry32;
  FAUSTFLOAT fEntry33;
  float fRec11[3];
  FAUSTFLOAT fEntry34;
  FAUSTFLOAT fEntry35;
  float fRec10[3];
  FAUSTFLOAT fEntry36;
  FAUSTFLOAT fEntry37;
  float fRec9[3];
  FAUSTFLOAT fEntry38;
  FAUSTFLOAT fEntry39;
  float fRec8[3];
  float fConst28;
  float fRec7[3];
  float fConst29;
  float fConst30;
  float fConst31;
  float fVec2[2];
  float fConst32;
  float fConst33;
  float fConst34;
  float fRec6[2];
  float fConst35;
  float fConst36;
  float fRec5[3];
  float fConst37;
  FAUSTFLOAT fEntry40;
  float fConst38;
  float fRec32[2];
  float fRec31[3];
  float fConst39;
  float fConst40;
  float fRec4[3];
  float fVec3[2];
  float fRec3[2];
  float fConst41;
  float fConst42;
  float fConst43;
  float fConst44;
  float fRec2[3];
  float fConst45;
  float fRec34[2];
  float fRec33[3];
  float fConst46;
  float fConst47;
  float fConst48;
  float fRec1[3];
  float fConst49;
  float fConst50;
  float fRec0[3];

public:
  void metadata(Meta *m) {
    m->declare("analyzers.lib/name", "Faust Analyzer Library");
    m->declare("analyzers.lib/version", "0.1");
    m->declare("basics.lib/name", "Faust Basic Element Library");
    m->declare("basics.lib/version", "0.1");
    m->declare("filename", "Cabinet.dsp");
    m->declare("filters.lib/filterbank:author", "Julius O. Smith III");
    m->declare("filters.lib/filterbank:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/filterbank:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/fir:author", "Julius O. Smith III");
    m->declare("filters.lib/fir:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/highpass:author", "Julius O. Smith III");
    m->declare("filters.lib/highpass:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/highshelf:author", "Julius O. Smith III");
    m->declare("filters.lib/highshelf:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/highshelf:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/iir:author", "Julius O. Smith III");
    m->declare("filters.lib/iir:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/low_shelf:author", "Julius O. Smith III");
    m->declare("filters.lib/low_shelf:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/low_shelf:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/lowpass0_highpass1",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
    m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
    m->declare("filters.lib/lowpass:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/lowshelf:author", "Julius O. Smith III");
    m->declare("filters.lib/lowshelf:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/lowshelf:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/name", "Faust Filters Library");
    m->declare("filters.lib/peak_eq:author", "Julius O. Smith III");
    m->declare("filters.lib/peak_eq:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/peak_eq:license", "MIT-style STK-4.3 license");
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
    m->declare("filters.lib/tf2:author", "Julius O. Smith III");
    m->declare("filters.lib/tf2:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
    m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
    m->declare("filters.lib/tf2s:copyright",
               "Copyright (C) 2003-2019 by Julius O. Smith III "
               "<jos@ccrma.stanford.edu>");
    m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
    m->declare("maths.lib/author", "GRAME");
    m->declare("maths.lib/copyright", "GRAME");
    m->declare("maths.lib/license", "LGPL with exception");
    m->declare("maths.lib/name", "Faust Math Library");
    m->declare("maths.lib/version", "2.3");
    m->declare("name", "Cabinet");
    m->declare("platform.lib/name", "Generic Platform Library");
    m->declare("platform.lib/version", "0.1");
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
    fConst1 = std::tan((3769.91113f / fConst0));
    fConst2 = (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fConst1))));
    fConst3 = std::tan((219.911484f / fConst0));
    fConst4 = (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fConst3))));
    fConst5 = std::tan((20420.3516f / fConst0));
    fConst6 = (1.0f / fConst5);
    fConst7 = (1.0f / (((fConst6 + 1.0f) / fConst5) + 1.0f));
    fConst8 = (fConst6 + 1.0f);
    fConst9 = (1.0f / fConst8);
    fConst10 = (1.0f - fConst6);
    fConst11 = std::tan((18849.5566f / fConst0));
    fConst12 = (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fConst11))));
    fConst13 = std::tan((3455.75195f / fConst0));
    fConst14 = (1.0f / fConst13);
    fConst15 = (1.0f / (((fConst14 + 1.0f) / fConst13) + 1.0f));
    fConst16 = CabinetFaust_faustpower2_f(fConst13);
    fConst17 = (1.0f / fConst16);
    fConst18 = std::tan((314.159271f / fConst0));
    fConst19 = (1.0f / fConst18);
    fConst20 = (fConst0 * std::sin((628.318542f / fConst0)));
    fConst21 = (1117.32593f / fConst20);
    fConst22 = (1.0f / (((fConst19 + fConst21) / fConst18) + 1.0f));
    fConst23 = (fConst14 + 1.0f);
    fConst24 = (1.0f / (fConst13 * fConst23));
    fConst25 = (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fConst18))));
    fConst26 = (3.14159274f / fConst0);
    fConst27 = (6.28318548f / fConst0);
    fConst28 = (((fConst19 - fConst21) / fConst18) + 1.0f);
    fConst29 = (628.318542f / fConst20);
    fConst30 = (((fConst19 + fConst29) / fConst18) + 1.0f);
    fConst31 = (((fConst19 - fConst29) / fConst18) + 1.0f);
    fConst32 = (0.0f - fConst24);
    fConst33 = (1.0f - fConst14);
    fConst34 = (fConst33 / fConst23);
    fConst35 = (((fConst14 + -1.0f) / fConst13) + 1.0f);
    fConst36 = (2.0f * (1.0f - fConst17));
    fConst37 = (0.0f - (2.0f / fConst16));
    fConst38 = (1.0f / fConst23);
    fConst39 = (1.0f / fConst11);
    fConst40 = (3141.59277f / (fConst0 * std::sin((37699.1133f / fConst0))));
    fConst41 = (((fConst6 + -1.0f) / fConst5) + 1.0f);
    fConst42 = CabinetFaust_faustpower2_f(fConst5);
    fConst43 = (1.0f / fConst42);
    fConst44 = (2.0f * (1.0f - fConst43));
    fConst45 = (0.0f - (1.0f / (fConst5 * fConst8)));
    fConst46 = (0.0f - (2.0f / fConst42));
    fConst47 = (1.0f / fConst3);
    fConst48 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
    fConst49 = (1.0f / fConst1);
    fConst50 = (942.477783f / (fConst0 * std::sin((7539.82227f / fConst0))));
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
    fEntry8 = FAUSTFLOAT(0.0f);
    fEntry9 = FAUSTFLOAT(0.0f);
    fEntry10 = FAUSTFLOAT(0.0f);
    fEntry11 = FAUSTFLOAT(0.0f);
    fEntry12 = FAUSTFLOAT(0.0f);
    fEntry13 = FAUSTFLOAT(0.0f);
    fEntry14 = FAUSTFLOAT(0.0f);
    fEntry15 = FAUSTFLOAT(0.0f);
    fEntry16 = FAUSTFLOAT(0.0f);
    fEntry17 = FAUSTFLOAT(0.0f);
    fEntry18 = FAUSTFLOAT(0.0f);
    fEntry19 = FAUSTFLOAT(0.0f);
    fEntry20 = FAUSTFLOAT(0.0f);
    fEntry21 = FAUSTFLOAT(0.0f);
    fEntry22 = FAUSTFLOAT(0.0f);
    fEntry23 = FAUSTFLOAT(0.0f);
    fEntry24 = FAUSTFLOAT(0.0f);
    fEntry25 = FAUSTFLOAT(0.0f);
    fEntry26 = FAUSTFLOAT(0.0f);
    fEntry27 = FAUSTFLOAT(0.0f);
    fEntry28 = FAUSTFLOAT(0.0f);
    fEntry29 = FAUSTFLOAT(0.0f);
    fEntry30 = FAUSTFLOAT(0.0f);
    fEntry31 = FAUSTFLOAT(0.0f);
    fEntry32 = FAUSTFLOAT(0.0f);
    fEntry33 = FAUSTFLOAT(0.0f);
    fEntry34 = FAUSTFLOAT(0.0f);
    fEntry35 = FAUSTFLOAT(0.0f);
    fEntry36 = FAUSTFLOAT(0.0f);
    fEntry37 = FAUSTFLOAT(0.0f);
    fEntry38 = FAUSTFLOAT(0.0f);
    fEntry39 = FAUSTFLOAT(0.0f);
    fEntry40 = FAUSTFLOAT(0.0f);
  }

  virtual void instanceClear() {
    for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
      fRec26[l0] = 0.0f;
    }
    for (int l1 = 0; (l1 < 3); l1 = (l1 + 1)) {
      fRec25[l1] = 0.0f;
    }
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
      fVec0[l2] = 0.0f;
    }
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
      fRec24[l3] = 0.0f;
    }
    for (int l4 = 0; (l4 < 3); l4 = (l4 + 1)) {
      fRec23[l4] = 0.0f;
    }
    for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
      fVec1[l5] = 0.0f;
    }
    for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
      fRec22[l6] = 0.0f;
    }
    for (int l7 = 0; (l7 < 3); l7 = (l7 + 1)) {
      fRec21[l7] = 0.0f;
    }
    for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
      fRec20[l8] = 0.0f;
    }
    for (int l9 = 0; (l9 < 3); l9 = (l9 + 1)) {
      fRec19[l9] = 0.0f;
    }
    for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
      fRec30[l10] = 0.0f;
    }
    for (int l11 = 0; (l11 < 3); l11 = (l11 + 1)) {
      fRec29[l11] = 0.0f;
    }
    for (int l12 = 0; (l12 < 3); l12 = (l12 + 1)) {
      fRec28[l12] = 0.0f;
    }
    for (int l13 = 0; (l13 < 3); l13 = (l13 + 1)) {
      fRec27[l13] = 0.0f;
    }
    for (int l14 = 0; (l14 < 3); l14 = (l14 + 1)) {
      fRec18[l14] = 0.0f;
    }
    for (int l15 = 0; (l15 < 3); l15 = (l15 + 1)) {
      fRec17[l15] = 0.0f;
    }
    for (int l16 = 0; (l16 < 3); l16 = (l16 + 1)) {
      fRec16[l16] = 0.0f;
    }
    for (int l17 = 0; (l17 < 3); l17 = (l17 + 1)) {
      fRec15[l17] = 0.0f;
    }
    for (int l18 = 0; (l18 < 3); l18 = (l18 + 1)) {
      fRec14[l18] = 0.0f;
    }
    for (int l19 = 0; (l19 < 3); l19 = (l19 + 1)) {
      fRec13[l19] = 0.0f;
    }
    for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
      fRec12[l20] = 0.0f;
    }
    for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
      fRec11[l21] = 0.0f;
    }
    for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
      fRec10[l22] = 0.0f;
    }
    for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
      fRec9[l23] = 0.0f;
    }
    for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
      fRec8[l24] = 0.0f;
    }
    for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
      fRec7[l25] = 0.0f;
    }
    for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
      fVec2[l26] = 0.0f;
    }
    for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
      fRec6[l27] = 0.0f;
    }
    for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
      fRec5[l28] = 0.0f;
    }
    for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
      fRec32[l29] = 0.0f;
    }
    for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
      fRec31[l30] = 0.0f;
    }
    for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
      fRec4[l31] = 0.0f;
    }
    for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
      fVec3[l32] = 0.0f;
    }
    for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
      fRec3[l33] = 0.0f;
    }
    for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
      fRec2[l34] = 0.0f;
    }
    for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
      fRec34[l35] = 0.0f;
    }
    for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
      fRec33[l36] = 0.0f;
    }
    for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
      fRec1[l37] = 0.0f;
    }
    for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
      fRec0[l38] = 0.0f;
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

  virtual CabinetFaust *clone() { return new CabinetFaust(); }

  virtual int getSampleRate() { return fSampleRate; }

  virtual void buildUserInterface(UI *ui_interface) {
    ui_interface->openVerticalBox("Cabinet");
    ui_interface->addNumEntry("brightness", &fEntry40, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("distance", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("gain", &fEntry6, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("hp_f", &fEntry16, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("lp_f", &fEntry15, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("offset", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_10_b", &fEntry37, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_10_f", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_10_l", &fEntry36, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_1_b", &fEntry19, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_1_f", &fEntry13, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_1_l", &fEntry18, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_2_b", &fEntry21, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_2_f", &fEntry12, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_2_l", &fEntry20, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_3_b", &fEntry23, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_3_f", &fEntry11, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_3_l", &fEntry22, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_4_b", &fEntry25, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_4_f", &fEntry10, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_4_l", &fEntry24, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_5_b", &fEntry27, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_5_f", &fEntry9, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_5_l", &fEntry26, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_6_b", &fEntry29, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_6_f", &fEntry8, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_6_l", &fEntry28, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_7_b", &fEntry31, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_7_f", &fEntry7, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_7_l", &fEntry30, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_8_b", &fEntry33, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_8_f", &fEntry5, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_8_l", &fEntry32, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_9_b", &fEntry35, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_9_f", &fEntry4, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("peak_9_l", &fEntry34, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("scoop_b", &fEntry39, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("scoop_f", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("scoop_l", &fEntry38, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("shelf_f", &fEntry14, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->addNumEntry("shelf_l", &fEntry17, 0.0f, 0.0f, 1.0f, 1.0f);
    ui_interface->closeBox();
  }

  virtual void compute(int count, FAUSTFLOAT **inputs, FAUSTFLOAT **outputs) {
    FAUSTFLOAT *input0 = inputs[0];
    FAUSTFLOAT *output0 = outputs[0];
    float fSlow0 = float(fEntry0);
    float fSlow1 = (std::pow(10.0f, (0.100000001f * fSlow0)) *
                    std::pow(10.0f, (0.0500000007f * float(fEntry1))));
    float fSlow2 = float(fEntry2);
    float fSlow3 = std::tan((fConst26 * fSlow2));
    float fSlow4 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow3))));
    float fSlow5 = float(fEntry3);
    float fSlow6 = std::tan((fConst26 * fSlow5));
    float fSlow7 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow6))));
    float fSlow8 = float(fEntry4);
    float fSlow9 = std::tan((fConst26 * fSlow8));
    float fSlow10 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow9))));
    float fSlow11 = float(fEntry6);
    float fSlow12 = (float(fEntry5) - (500.0f * fSlow11));
    float fSlow13 = std::tan((fConst26 * fSlow12));
    float fSlow14 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow13))));
    float fSlow15 = float(fEntry7);
    float fSlow16 = std::tan((fConst26 * fSlow15));
    float fSlow17 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow16))));
    float fSlow18 = float(fEntry8);
    float fSlow19 = std::tan((fConst26 * fSlow18));
    float fSlow20 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow19))));
    float fSlow21 = float(fEntry9);
    float fSlow22 = std::tan((fConst26 * fSlow21));
    float fSlow23 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow22))));
    float fSlow24 = float(fEntry10);
    float fSlow25 = std::tan((fConst26 * fSlow24));
    float fSlow26 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow25))));
    float fSlow27 = float(fEntry11);
    float fSlow28 = std::tan((fConst26 * fSlow27));
    float fSlow29 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow28))));
    float fSlow30 = float(fEntry12);
    float fSlow31 = std::tan((fConst26 * fSlow30));
    float fSlow32 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow31))));
    float fSlow33 = float(fEntry13);
    float fSlow34 = std::tan((fConst26 * fSlow33));
    float fSlow35 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow34))));
    float fSlow36 = std::tan((fConst26 * float(fEntry14)));
    float fSlow37 = (1.0f / fSlow36);
    float fSlow38 = (1.0f / (((fSlow37 + 0.445041865f) / fSlow36) + 1.0f));
    float fSlow39 = (1.0f / (((fSlow37 + 1.24697959f) / fSlow36) + 1.0f));
    float fSlow40 = (1.0f / (((fSlow37 + 1.8019377f) / fSlow36) + 1.0f));
    float fSlow41 = (fSlow37 + 1.0f);
    float fSlow42 = (1.0f / fSlow41);
    float fSlow43 = (1.0f - fSlow37);
    float fSlow44 = std::tan((fConst26 * float(fEntry15)));
    float fSlow45 = (1.0f / fSlow44);
    float fSlow46 = (((fSlow45 + 1.0f) / fSlow44) + 1.0f);
    float fSlow47 = (1.0f / fSlow46);
    float fSlow48 = (1.0f / (fSlow45 + 1.0f));
    float fSlow49 = (1.0f - fSlow45);
    float fSlow50 = std::tan((fConst26 * float(fEntry16)));
    float fSlow51 = (1.0f / fSlow50);
    float fSlow52 = (1.0f / (((fSlow51 + 0.765366852f) / fSlow50) + 1.0f));
    float fSlow53 = CabinetFaust_faustpower2_f(fSlow50);
    float fSlow54 = (1.0f / fSlow53);
    float fSlow55 = (1.0f / (((fSlow51 + 1.84775901f) / fSlow50) + 1.0f));
    float fSlow56 = (((fSlow51 + -1.84775901f) / fSlow50) + 1.0f);
    float fSlow57 = (2.0f * (1.0f - fSlow54));
    float fSlow58 = (0.0f - (2.0f / fSlow53));
    float fSlow59 = (((fSlow51 + -0.765366852f) / fSlow50) + 1.0f);
    float fSlow60 = (((fSlow45 + -1.0f) / fSlow44) + 1.0f);
    float fSlow61 =
        (2.0f * (1.0f - (1.0f / CabinetFaust_faustpower2_f(fSlow44))));
    float fSlow62 = (((fSlow37 + -1.8019377f) / fSlow36) + 1.0f);
    float fSlow63 = CabinetFaust_faustpower2_f(fSlow36);
    float fSlow64 = (1.0f / fSlow63);
    float fSlow65 = (2.0f * (1.0f - fSlow64));
    float fSlow66 = (((fSlow37 + -1.24697959f) / fSlow36) + 1.0f);
    float fSlow67 = (((fSlow37 + -0.445041865f) / fSlow36) + 1.0f);
    float fSlow68 = std::pow(10.0f, (0.0500000007f * float(fEntry17)));
    float fSlow69 = (0.0f - (1.0f / (fSlow36 * fSlow41)));
    float fSlow70 = (1.0f / (fSlow36 * fSlow46));
    float fSlow71 = (0.0f - (2.0f / fSlow63));
    float fSlow72 = (1.0f / fSlow34);
    float fSlow73 = float(fEntry18);
    int iSlow74 = (fSlow73 > 0.0f);
    float fSlow75 = float(fEntry19);
    float fSlow76 = std::sin((fConst27 * fSlow33));
    float fSlow77 =
        (fConst26 *
         ((fSlow75 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow73)))) /
          fSlow76));
    float fSlow78 = (fConst26 * (fSlow75 / fSlow76));
    float fSlow79 = (iSlow74 ? fSlow78 : fSlow77);
    float fSlow80 = ((fSlow72 * (fSlow72 - fSlow79)) + 1.0f);
    float fSlow81 = ((fSlow72 * (fSlow72 + fSlow79)) + 1.0f);
    float fSlow82 = (iSlow74 ? fSlow77 : fSlow78);
    float fSlow83 = ((fSlow72 * (fSlow72 + fSlow82)) + 1.0f);
    float fSlow84 = ((fSlow72 * (fSlow72 - fSlow82)) + 1.0f);
    float fSlow85 = (1.0f / fSlow31);
    float fSlow86 = float(fEntry20);
    int iSlow87 = (fSlow86 > 0.0f);
    float fSlow88 = float(fEntry21);
    float fSlow89 = std::sin((fConst27 * fSlow30));
    float fSlow90 =
        (fConst26 *
         ((fSlow88 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow86)))) /
          fSlow89));
    float fSlow91 = (fConst26 * (fSlow88 / fSlow89));
    float fSlow92 = (iSlow87 ? fSlow91 : fSlow90);
    float fSlow93 = ((fSlow85 * (fSlow85 - fSlow92)) + 1.0f);
    float fSlow94 = ((fSlow85 * (fSlow85 + fSlow92)) + 1.0f);
    float fSlow95 = (iSlow87 ? fSlow90 : fSlow91);
    float fSlow96 = ((fSlow85 * (fSlow85 + fSlow95)) + 1.0f);
    float fSlow97 = ((fSlow85 * (fSlow85 - fSlow95)) + 1.0f);
    float fSlow98 = (1.0f / fSlow28);
    float fSlow99 = float(fEntry22);
    int iSlow100 = (fSlow99 > 0.0f);
    float fSlow101 = float(fEntry23);
    float fSlow102 = std::sin((fConst27 * fSlow27));
    float fSlow103 =
        (fConst26 *
         ((fSlow101 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow99)))) /
          fSlow102));
    float fSlow104 = (fConst26 * (fSlow101 / fSlow102));
    float fSlow105 = (iSlow100 ? fSlow104 : fSlow103);
    float fSlow106 = ((fSlow98 * (fSlow98 - fSlow105)) + 1.0f);
    float fSlow107 = ((fSlow98 * (fSlow98 + fSlow105)) + 1.0f);
    float fSlow108 = (iSlow100 ? fSlow103 : fSlow104);
    float fSlow109 = ((fSlow98 * (fSlow98 + fSlow108)) + 1.0f);
    float fSlow110 = ((fSlow98 * (fSlow98 - fSlow108)) + 1.0f);
    float fSlow111 = (1.0f / fSlow25);
    float fSlow112 = float(fEntry24);
    int iSlow113 = (fSlow112 > 0.0f);
    float fSlow114 = float(fEntry25);
    float fSlow115 = std::sin((fConst27 * fSlow24));
    float fSlow116 =
        (fConst26 *
         ((fSlow114 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow112)))) /
          fSlow115));
    float fSlow117 = (fConst26 * (fSlow114 / fSlow115));
    float fSlow118 = (iSlow113 ? fSlow117 : fSlow116);
    float fSlow119 = ((fSlow111 * (fSlow111 - fSlow118)) + 1.0f);
    float fSlow120 = ((fSlow111 * (fSlow111 + fSlow118)) + 1.0f);
    float fSlow121 = (iSlow113 ? fSlow116 : fSlow117);
    float fSlow122 = ((fSlow111 * (fSlow111 + fSlow121)) + 1.0f);
    float fSlow123 = ((fSlow111 * (fSlow111 - fSlow121)) + 1.0f);
    float fSlow124 = (1.0f / fSlow22);
    float fSlow125 = float(fEntry26);
    int iSlow126 = (fSlow125 > 0.0f);
    float fSlow127 = float(fEntry27);
    float fSlow128 = std::sin((fConst27 * fSlow21));
    float fSlow129 =
        (fConst26 *
         ((fSlow127 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow125)))) /
          fSlow128));
    float fSlow130 = (fConst26 * (fSlow127 / fSlow128));
    float fSlow131 = (iSlow126 ? fSlow130 : fSlow129);
    float fSlow132 = ((fSlow124 * (fSlow124 - fSlow131)) + 1.0f);
    float fSlow133 = ((fSlow124 * (fSlow124 + fSlow131)) + 1.0f);
    float fSlow134 = (iSlow126 ? fSlow129 : fSlow130);
    float fSlow135 = ((fSlow124 * (fSlow124 + fSlow134)) + 1.0f);
    float fSlow136 = ((fSlow124 * (fSlow124 - fSlow134)) + 1.0f);
    float fSlow137 = (1.0f / fSlow19);
    float fSlow138 = float(fEntry28);
    int iSlow139 = (fSlow138 > 0.0f);
    float fSlow140 = float(fEntry29);
    float fSlow141 = std::sin((fConst27 * fSlow18));
    float fSlow142 =
        (fConst26 *
         ((fSlow140 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow138)))) /
          fSlow141));
    float fSlow143 = (fConst26 * (fSlow140 / fSlow141));
    float fSlow144 = (iSlow139 ? fSlow143 : fSlow142);
    float fSlow145 = ((fSlow137 * (fSlow137 - fSlow144)) + 1.0f);
    float fSlow146 = ((fSlow137 * (fSlow137 + fSlow144)) + 1.0f);
    float fSlow147 = (iSlow139 ? fSlow142 : fSlow143);
    float fSlow148 = ((fSlow137 * (fSlow137 + fSlow147)) + 1.0f);
    float fSlow149 = ((fSlow137 * (fSlow137 - fSlow147)) + 1.0f);
    float fSlow150 = (1.0f / fSlow16);
    float fSlow151 = float(fEntry30);
    int iSlow152 = (fSlow151 > 0.0f);
    float fSlow153 = float(fEntry31);
    float fSlow154 = std::sin((fConst27 * fSlow15));
    float fSlow155 =
        (fConst26 *
         ((fSlow153 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow151)))) /
          fSlow154));
    float fSlow156 = (fConst26 * (fSlow153 / fSlow154));
    float fSlow157 = (iSlow152 ? fSlow156 : fSlow155);
    float fSlow158 = ((fSlow150 * (fSlow150 - fSlow157)) + 1.0f);
    float fSlow159 = ((fSlow150 * (fSlow150 + fSlow157)) + 1.0f);
    float fSlow160 = (iSlow152 ? fSlow155 : fSlow156);
    float fSlow161 = ((fSlow150 * (fSlow150 + fSlow160)) + 1.0f);
    float fSlow162 = ((fSlow150 * (fSlow150 - fSlow160)) + 1.0f);
    float fSlow163 = (1.0f / fSlow13);
    float fSlow164 = (5.0f * fSlow11);
    float fSlow165 = (float(fEntry32) + fSlow164);
    int iSlow166 = (fSlow165 > 0.0f);
    float fSlow167 = (float(fEntry33) + (200.0f * fSlow11));
    float fSlow168 = std::sin((fConst27 * fSlow12));
    float fSlow169 =
        (fConst26 *
         ((fSlow167 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow165)))) /
          fSlow168));
    float fSlow170 = (fConst26 * (fSlow167 / fSlow168));
    float fSlow171 = (iSlow166 ? fSlow170 : fSlow169);
    float fSlow172 = ((fSlow163 * (fSlow163 - fSlow171)) + 1.0f);
    float fSlow173 = ((fSlow163 * (fSlow163 + fSlow171)) + 1.0f);
    float fSlow174 = (iSlow166 ? fSlow169 : fSlow170);
    float fSlow175 = ((fSlow163 * (fSlow163 + fSlow174)) + 1.0f);
    float fSlow176 = ((fSlow163 * (fSlow163 - fSlow174)) + 1.0f);
    float fSlow177 = (1.0f / fSlow9);
    float fSlow178 = float(fEntry34);
    int iSlow179 = (fSlow178 > 0.0f);
    float fSlow180 = float(fEntry35);
    float fSlow181 = std::sin((fConst27 * fSlow8));
    float fSlow182 =
        (fConst26 *
         ((fSlow180 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow178)))) /
          fSlow181));
    float fSlow183 = (fConst26 * (fSlow180 / fSlow181));
    float fSlow184 = (iSlow179 ? fSlow183 : fSlow182);
    float fSlow185 = ((fSlow177 * (fSlow177 - fSlow184)) + 1.0f);
    float fSlow186 = ((fSlow177 * (fSlow177 + fSlow184)) + 1.0f);
    float fSlow187 = (iSlow179 ? fSlow182 : fSlow183);
    float fSlow188 = ((fSlow177 * (fSlow177 + fSlow187)) + 1.0f);
    float fSlow189 = ((fSlow177 * (fSlow177 - fSlow187)) + 1.0f);
    float fSlow190 = (1.0f / fSlow6);
    float fSlow191 = float(fEntry36);
    int iSlow192 = (fSlow191 > 0.0f);
    float fSlow193 = float(fEntry37);
    float fSlow194 = std::sin((fConst27 * fSlow5));
    float fSlow195 =
        (fConst26 *
         ((fSlow193 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow191)))) /
          fSlow194));
    float fSlow196 = (fConst26 * (fSlow193 / fSlow194));
    float fSlow197 = (iSlow192 ? fSlow196 : fSlow195);
    float fSlow198 = ((fSlow190 * (fSlow190 - fSlow197)) + 1.0f);
    float fSlow199 = ((fSlow190 * (fSlow190 + fSlow197)) + 1.0f);
    float fSlow200 = (iSlow192 ? fSlow195 : fSlow196);
    float fSlow201 = ((fSlow190 * (fSlow190 + fSlow200)) + 1.0f);
    float fSlow202 = ((fSlow190 * (fSlow190 - fSlow200)) + 1.0f);
    float fSlow203 = (1.0f / fSlow3);
    float fSlow204 = float(fEntry38);
    int iSlow205 = (fSlow204 > 0.0f);
    float fSlow206 = float(fEntry39);
    float fSlow207 = std::sin((fConst27 * fSlow2));
    float fSlow208 =
        (fConst26 *
         ((fSlow206 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow204)))) /
          fSlow207));
    float fSlow209 = (fConst26 * (fSlow206 / fSlow207));
    float fSlow210 = (iSlow205 ? fSlow209 : fSlow208);
    float fSlow211 = ((fSlow203 * (fSlow203 - fSlow210)) + 1.0f);
    float fSlow212 = ((fSlow203 * (fSlow203 + fSlow210)) + 1.0f);
    float fSlow213 = (iSlow205 ? fSlow208 : fSlow209);
    float fSlow214 = ((fSlow203 * (fSlow203 + fSlow213)) + 1.0f);
    float fSlow215 = ((fSlow203 * (fSlow203 - fSlow213)) + 1.0f);
    float fSlow216 = float(fEntry40);
    float fSlow217 = std::pow(10.0f, (0.150000006f * (fSlow11 - fSlow216)));
    float fSlow218 = (15.0f * fSlow216);
    int iSlow219 = (fSlow218 > 0.0f);
    float fSlow220 =
        (fConst40 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow218))));
    float fSlow221 = (iSlow219 ? fConst40 : fSlow220);
    float fSlow222 = ((fConst39 * (fConst39 - fSlow221)) + 1.0f);
    float fSlow223 = ((fConst39 * (fConst39 + fSlow221)) + 1.0f);
    float fSlow224 = (iSlow219 ? fSlow220 : fConst40);
    float fSlow225 = ((fConst39 * (fConst39 + fSlow224)) + 1.0f);
    float fSlow226 = ((fConst39 * (fConst39 - fSlow224)) + 1.0f);
    float fSlow227 = std::pow(10.0f, (0.0500000007f * (0.0f - fSlow164)));
    float fSlow228 = (0.0f - (10.0f * fSlow0));
    int iSlow229 = (fSlow228 > 0.0f);
    float fSlow230 =
        (fConst48 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow228))));
    float fSlow231 = (iSlow229 ? fConst48 : fSlow230);
    float fSlow232 = ((fConst47 * (fConst47 - fSlow231)) + 1.0f);
    float fSlow233 = ((fConst47 * (fConst47 + fSlow231)) + 1.0f);
    float fSlow234 = (iSlow229 ? fSlow230 : fConst48);
    float fSlow235 = ((fConst47 * (fConst47 + fSlow234)) + 1.0f);
    float fSlow236 = ((fConst47 * (fConst47 - fSlow234)) + 1.0f);
    float fSlow237 = (0.0f - (17.0f * fSlow0));
    int iSlow238 = (fSlow237 > 0.0f);
    float fSlow239 =
        (fConst50 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow237))));
    float fSlow240 = (iSlow238 ? fConst50 : fSlow239);
    float fSlow241 = ((fConst49 * (fConst49 - fSlow240)) + 1.0f);
    float fSlow242 = ((fConst49 * (fConst49 + fSlow240)) + 1.0f);
    float fSlow243 = (iSlow238 ? fSlow239 : fConst50);
    float fSlow244 = ((fConst49 * (fConst49 + fSlow243)) + 1.0f);
    float fSlow245 = ((fConst49 * (fConst49 - fSlow243)) + 1.0f);
    for (int i = 0; (i < count); i = (i + 1)) {
      float fTemp0 = float(input0[i]);
      float fTempFTZ0 =
          (fTemp0 -
           (fSlow55 * ((fSlow56 * fRec26[2]) + (fSlow57 * fRec26[1]))));
      fRec26[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ0) & 2139095040) ? fTempFTZ0
                                                               : 0.0f);
      float fTempFTZ1 =
          ((fSlow55 * (((fSlow54 * fRec26[0]) + (fSlow58 * fRec26[1])) +
                       (fSlow54 * fRec26[2]))) -
           (fSlow52 * ((fSlow59 * fRec25[2]) + (fSlow57 * fRec25[1]))));
      fRec25[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ1) & 2139095040) ? fTempFTZ1
                                                               : 0.0f);
      float fTemp1 =
          (fSlow52 * (((fSlow54 * fRec25[0]) + (fSlow58 * fRec25[1])) +
                      (fSlow54 * fRec25[2])));
      fVec0[0] = fTemp1;
      float fTempFTZ2 =
          (0.0f - (fSlow48 * ((fSlow49 * fRec24[1]) - (fTemp1 + fVec0[1]))));
      fRec24[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ2) & 2139095040) ? fTempFTZ2
                                                               : 0.0f);
      float fTempFTZ3 =
          (fRec24[0] -
           (fSlow47 * ((fSlow60 * fRec23[2]) + (fSlow61 * fRec23[1]))));
      fRec23[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ3) & 2139095040) ? fTempFTZ3
                                                               : 0.0f);
      float fTemp2 = (fRec23[2] + (fRec23[0] + (2.0f * fRec23[1])));
      float fTemp3 = (fSlow47 * fTemp2);
      fVec1[0] = fTemp3;
      float fTempFTZ4 =
          (0.0f - (fSlow42 * ((fSlow43 * fRec22[1]) - (fTemp3 + fVec1[1]))));
      fRec22[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ4) & 2139095040) ? fTempFTZ4
                                                               : 0.0f);
      float fTempFTZ5 =
          (fRec22[0] -
           (fSlow40 * ((fSlow62 * fRec21[2]) + (fSlow65 * fRec21[1]))));
      fRec21[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ5) & 2139095040) ? fTempFTZ5
                                                               : 0.0f);
      float fTempFTZ6 =
          ((fSlow40 * (fRec21[2] + (fRec21[0] + (2.0f * fRec21[1])))) -
           (fSlow39 * ((fSlow66 * fRec20[2]) + (fSlow65 * fRec20[1]))));
      fRec20[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ6) & 2139095040) ? fTempFTZ6
                                                               : 0.0f);
      float fTempFTZ7 =
          ((fSlow39 * (fRec20[2] + (fRec20[0] + (2.0f * fRec20[1])))) -
           (fSlow38 * ((fSlow67 * fRec19[2]) + (fSlow65 * fRec19[1]))));
      fRec19[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ7) & 2139095040) ? fTempFTZ7
                                                               : 0.0f);
      float fTempFTZ8 =
          ((fSlow69 * fVec1[1]) -
           (fSlow42 * ((fSlow43 * fRec30[1]) - (fSlow70 * fTemp2))));
      fRec30[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ8) & 2139095040) ? fTempFTZ8
                                                               : 0.0f);
      float fTempFTZ9 =
          (fRec30[0] -
           (fSlow40 * ((fSlow62 * fRec29[2]) + (fSlow65 * fRec29[1]))));
      fRec29[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ9) & 2139095040) ? fTempFTZ9
                                                               : 0.0f);
      float fTempFTZ10 =
          ((fSlow40 * (((fSlow64 * fRec29[0]) + (fSlow71 * fRec29[1])) +
                       (fSlow64 * fRec29[2]))) -
           (fSlow39 * ((fSlow66 * fRec28[2]) + (fSlow65 * fRec28[1]))));
      fRec28[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ10) & 2139095040) ? fTempFTZ10
                                                                : 0.0f);
      float fTempFTZ11 =
          ((fSlow39 * (((fSlow64 * fRec28[0]) + (fSlow71 * fRec28[1])) +
                       (fSlow64 * fRec28[2]))) -
           (fSlow38 * ((fSlow67 * fRec27[2]) + (fSlow65 * fRec27[1]))));
      fRec27[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ11) & 2139095040) ? fTempFTZ11
                                                                : 0.0f);
      float fTemp4 = (fSlow35 * fRec18[1]);
      float fTempFTZ12 =
          ((fSlow38 *
            ((fRec19[2] + (fRec19[0] + (2.0f * fRec19[1]))) +
             (fSlow68 * (((fSlow64 * fRec27[0]) + (fSlow71 * fRec27[1])) +
                         (fSlow64 * fRec27[2]))))) -
           (((fRec18[2] * fSlow80) + fTemp4) / fSlow81));
      fRec18[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ12) & 2139095040) ? fTempFTZ12
                                                                : 0.0f);
      float fTemp5 = (fSlow32 * fRec17[1]);
      float fTempFTZ13 =
          ((((fTemp4 + (fRec18[0] * fSlow83)) + (fRec18[2] * fSlow84)) /
            fSlow81) -
           (((fRec17[2] * fSlow93) + fTemp5) / fSlow94));
      fRec17[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ13) & 2139095040) ? fTempFTZ13
                                                                : 0.0f);
      float fTemp6 = (fSlow29 * fRec16[1]);
      float fTempFTZ14 =
          ((((fTemp5 + (fRec17[0] * fSlow96)) + (fRec17[2] * fSlow97)) /
            fSlow94) -
           (((fRec16[2] * fSlow106) + fTemp6) / fSlow107));
      fRec16[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ14) & 2139095040) ? fTempFTZ14
                                                                : 0.0f);
      float fTemp7 = (fSlow26 * fRec15[1]);
      float fTempFTZ15 =
          ((((fTemp6 + (fRec16[0] * fSlow109)) + (fRec16[2] * fSlow110)) /
            fSlow107) -
           (((fRec15[2] * fSlow119) + fTemp7) / fSlow120));
      fRec15[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ15) & 2139095040) ? fTempFTZ15
                                                                : 0.0f);
      float fTemp8 = (fSlow23 * fRec14[1]);
      float fTempFTZ16 =
          ((((fTemp7 + (fRec15[0] * fSlow122)) + (fRec15[2] * fSlow123)) /
            fSlow120) -
           (((fRec14[2] * fSlow132) + fTemp8) / fSlow133));
      fRec14[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ16) & 2139095040) ? fTempFTZ16
                                                                : 0.0f);
      float fTemp9 = (fSlow20 * fRec13[1]);
      float fTempFTZ17 =
          ((((fTemp8 + (fRec14[0] * fSlow135)) + (fRec14[2] * fSlow136)) /
            fSlow133) -
           (((fRec13[2] * fSlow145) + fTemp9) / fSlow146));
      fRec13[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ17) & 2139095040) ? fTempFTZ17
                                                                : 0.0f);
      float fTemp10 = (fSlow17 * fRec12[1]);
      float fTempFTZ18 =
          ((((fTemp9 + (fRec13[0] * fSlow148)) + (fRec13[2] * fSlow149)) /
            fSlow146) -
           (((fRec12[2] * fSlow158) + fTemp10) / fSlow159));
      fRec12[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ18) & 2139095040) ? fTempFTZ18
                                                                : 0.0f);
      float fTemp11 = (fSlow14 * fRec11[1]);
      float fTempFTZ19 =
          ((((fTemp10 + (fRec12[0] * fSlow161)) + (fRec12[2] * fSlow162)) /
            fSlow159) -
           (((fRec11[2] * fSlow172) + fTemp11) / fSlow173));
      fRec11[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ19) & 2139095040) ? fTempFTZ19
                                                                : 0.0f);
      float fTemp12 = (fSlow10 * fRec10[1]);
      float fTempFTZ20 =
          ((((fTemp11 + (fRec11[0] * fSlow175)) + (fRec11[2] * fSlow176)) /
            fSlow173) -
           (((fRec10[2] * fSlow185) + fTemp12) / fSlow186));
      fRec10[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ20) & 2139095040) ? fTempFTZ20
                                                                : 0.0f);
      float fTemp13 = (fSlow7 * fRec9[1]);
      float fTempFTZ21 =
          ((((fTemp12 + (fRec10[0] * fSlow188)) + (fRec10[2] * fSlow189)) /
            fSlow186) -
           (((fRec9[2] * fSlow198) + fTemp13) / fSlow199));
      fRec9[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ21) & 2139095040) ? fTempFTZ21
                                                                : 0.0f);
      float fTemp14 = (fSlow4 * fRec8[1]);
      float fTempFTZ22 =
          ((((fTemp13 + (fRec9[0] * fSlow201)) + (fRec9[2] * fSlow202)) /
            fSlow199) -
           (((fRec8[2] * fSlow211) + fTemp14) / fSlow212));
      fRec8[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ22) & 2139095040) ? fTempFTZ22
                                                                : 0.0f);
      float fTemp15 = (fConst25 * fRec7[1]);
      float fTempFTZ23 =
          ((((fTemp14 + (fRec8[0] * fSlow214)) + (fRec8[2] * fSlow215)) /
            fSlow212) -
           (fConst22 * ((fConst28 * fRec7[2]) + fTemp15)));
      fRec7[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ23) & 2139095040) ? fTempFTZ23
                                                                : 0.0f);
      float fTemp16 =
          ((fTemp15 + (fConst30 * fRec7[0])) + (fConst31 * fRec7[2]));
      fVec2[0] = fTemp16;
      float fTempFTZ24 =
          ((fConst22 * ((fConst24 * fTemp16) + (fConst32 * fVec2[1]))) -
           (fConst34 * fRec6[1]));
      fRec6[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ24) & 2139095040) ? fTempFTZ24
                                                                : 0.0f);
      float fTempFTZ25 =
          (fRec6[0] -
           (fConst15 * ((fConst35 * fRec5[2]) + (fConst36 * fRec5[1]))));
      fRec5[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ25) & 2139095040) ? fTempFTZ25
                                                                : 0.0f);
      float fTempFTZ26 =
          (0.0f - (fConst38 * ((fConst33 * fRec32[1]) -
                               (fConst22 * (fTemp16 + fVec2[1])))));
      fRec32[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ26) & 2139095040) ? fTempFTZ26
                                                                : 0.0f);
      float fTempFTZ27 =
          (fRec32[0] -
           (fConst15 * ((fConst35 * fRec31[2]) + (fConst36 * fRec31[1]))));
      fRec31[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ27) & 2139095040) ? fTempFTZ27
                                                                : 0.0f);
      float fTemp17 = (fConst12 * fRec4[1]);
      float fTempFTZ28 =
          ((fConst15 *
            ((((fConst17 * fRec5[0]) + (fConst37 * fRec5[1])) +
              (fConst17 * fRec5[2])) +
             (fSlow217 * (fRec31[2] + (fRec31[0] + (2.0f * fRec31[1])))))) -
           (((fRec4[2] * fSlow222) + fTemp17) / fSlow223));
      fRec4[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ28) & 2139095040) ? fTempFTZ28
                                                                : 0.0f);
      float fTemp18 =
          (((fTemp17 + (fRec4[0] * fSlow225)) + (fRec4[2] * fSlow226)) /
           fSlow223);
      fVec3[0] = fTemp18;
      float fTempFTZ29 =
          (0.0f - (fConst9 * ((fConst10 * fRec3[1]) - (fTemp18 + fVec3[1]))));
      fRec3[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ29) & 2139095040) ? fTempFTZ29
                                                                : 0.0f);
      float fTempFTZ30 =
          (fRec3[0] -
           (fConst7 * ((fConst41 * fRec2[2]) + (fConst44 * fRec2[1]))));
      fRec2[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ30) & 2139095040) ? fTempFTZ30
                                                                : 0.0f);
      float fTempFTZ31 =
          ((fConst45 * fVec3[1]) -
           (fConst9 * ((fConst10 * fRec34[1]) - (fConst6 * fTemp18))));
      fRec34[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ31) & 2139095040) ? fTempFTZ31
                                                                : 0.0f);
      float fTempFTZ32 =
          (fRec34[0] -
           (fConst7 * ((fConst41 * fRec33[2]) + (fConst44 * fRec33[1]))));
      fRec33[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ32) & 2139095040) ? fTempFTZ32
                                                                : 0.0f);
      float fTemp19 = (fConst4 * fRec1[1]);
      float fTempFTZ33 =
          ((fConst7 *
            ((fRec2[2] + (fRec2[0] + (2.0f * fRec2[1]))) +
             (fSlow227 * (((fConst43 * fRec33[0]) + (fConst46 * fRec33[1])) +
                          (fConst43 * fRec33[2]))))) -
           (((fRec1[2] * fSlow232) + fTemp19) / fSlow233));
      fRec1[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ33) & 2139095040) ? fTempFTZ33
                                                                : 0.0f);
      float fTemp20 = (fConst2 * fRec0[1]);
      float fTempFTZ34 =
          ((((fTemp19 + (fRec1[0] * fSlow235)) + (fRec1[2] * fSlow236)) /
            fSlow233) -
           (((fRec0[2] * fSlow241) + fTemp20) / fSlow242));
      fRec0[0] =
          ((*reinterpret_cast<int *>(&fTempFTZ34) & 2139095040) ? fTempFTZ34
                                                                : 0.0f);
      output0[i] = FAUSTFLOAT((fSlow1 * (((fTemp20 + (fRec0[0] * fSlow244)) +
                                          (fRec0[2] * fSlow245)) /
                                         fSlow242)));
      fRec26[2] = fRec26[1];
      fRec26[1] = fRec26[0];
      fRec25[2] = fRec25[1];
      fRec25[1] = fRec25[0];
      fVec0[1] = fVec0[0];
      fRec24[1] = fRec24[0];
      fRec23[2] = fRec23[1];
      fRec23[1] = fRec23[0];
      fVec1[1] = fVec1[0];
      fRec22[1] = fRec22[0];
      fRec21[2] = fRec21[1];
      fRec21[1] = fRec21[0];
      fRec20[2] = fRec20[1];
      fRec20[1] = fRec20[0];
      fRec19[2] = fRec19[1];
      fRec19[1] = fRec19[0];
      fRec30[1] = fRec30[0];
      fRec29[2] = fRec29[1];
      fRec29[1] = fRec29[0];
      fRec28[2] = fRec28[1];
      fRec28[1] = fRec28[0];
      fRec27[2] = fRec27[1];
      fRec27[1] = fRec27[0];
      fRec18[2] = fRec18[1];
      fRec18[1] = fRec18[0];
      fRec17[2] = fRec17[1];
      fRec17[1] = fRec17[0];
      fRec16[2] = fRec16[1];
      fRec16[1] = fRec16[0];
      fRec15[2] = fRec15[1];
      fRec15[1] = fRec15[0];
      fRec14[2] = fRec14[1];
      fRec14[1] = fRec14[0];
      fRec13[2] = fRec13[1];
      fRec13[1] = fRec13[0];
      fRec12[2] = fRec12[1];
      fRec12[1] = fRec12[0];
      fRec11[2] = fRec11[1];
      fRec11[1] = fRec11[0];
      fRec10[2] = fRec10[1];
      fRec10[1] = fRec10[0];
      fRec9[2] = fRec9[1];
      fRec9[1] = fRec9[0];
      fRec8[2] = fRec8[1];
      fRec8[1] = fRec8[0];
      fRec7[2] = fRec7[1];
      fRec7[1] = fRec7[0];
      fVec2[1] = fVec2[0];
      fRec6[1] = fRec6[0];
      fRec5[2] = fRec5[1];
      fRec5[1] = fRec5[0];
      fRec32[1] = fRec32[0];
      fRec31[2] = fRec31[1];
      fRec31[1] = fRec31[0];
      fRec4[2] = fRec4[1];
      fRec4[1] = fRec4[0];
      fVec3[1] = fVec3[0];
      fRec3[1] = fRec3[0];
      fRec2[2] = fRec2[1];
      fRec2[1] = fRec2[0];
      fRec34[1] = fRec34[0];
      fRec33[2] = fRec33[1];
      fRec33[1] = fRec33[0];
      fRec1[2] = fRec1[1];
      fRec1[1] = fRec1[0];
      fRec0[2] = fRec0[1];
      fRec0[1] = fRec0[0];
    }
  }
};

#endif
