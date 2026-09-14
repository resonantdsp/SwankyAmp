/* ------------------------------------------------------------
name: "DigiBoost"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef  __DigiBoostFaust_H__
#define  __DigiBoostFaust_H__

#include "FaustImpl.h"
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float DigiBoostFaust_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS DigiBoostFaust
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class DigiBoostFaust : public FaustImpl {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	FAUSTFLOAT fEntry2;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fEntry3;
	float fConst7;
	FAUSTFLOAT fEntry4;
	float fConst8;
	float fRec0[3];
	FAUSTFLOAT fEntry5;
	float fConst9;
	float fConst10;
	float fRec1[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "DigiBoost.dsp");
		m->declare("filters.lib/bandpass0_bandstop1:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass0_bandstop1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass0_bandstop1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandpass:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1sb:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1sb:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1sb:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "DigiBoost");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
	}

	virtual int getNumInputs() {
		return 1;
	}
	virtual int getNumOutputs() {
		return 1;
	}
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
	
	static void classInit(int) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (2.0f / fConst0);
		fConst2 = (2.0f * fConst0);
		fConst3 = (3.14159274f / fConst0);
		fConst4 = (0.449999988f * fConst0);
		fConst5 = (0.5f / fConst0);
		fConst6 = (4.0f * DigiBoostFaust_faustpower2_f(fConst0));
		fConst7 = DigiBoostFaust_faustpower2_f((1.0f / fConst0));
		fConst8 = (2.0f * fConst7);
		fConst9 = (1.0f / ((0.150000006f * fConst0) + 1.0f));
		fConst10 = (1.0f - fConst9);
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fEntry3 = FAUSTFLOAT(0.0f);
		fEntry4 = FAUSTFLOAT(0.0f);
		fEntry5 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec1[l1] = 0.0f;
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
	
	virtual DigiBoostFaust* clone() {
		return new DigiBoostFaust();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("DigiBoost");
		ui_interface->addNumEntry("drift", &fEntry5, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("high_pass", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("input_level", &fEntry4, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("low_pass", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("mix", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("saturation", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fEntry0);
		float fSlow1 = (1.0f - fSlow0);
		float fSlow2 = float(fEntry1);
		float fSlow3 = (fSlow0 / fSlow2);
		float fSlow4 = (0.294117659f * fSlow2);
		float fSlow5 = std::tan((fConst3 * std::min<float>(fConst4, float(fEntry2))));
		float fSlow6 = DigiBoostFaust_faustpower2_f(std::sqrt((fConst6 * (fSlow5 * std::tan((fConst3 * std::min<float>(fConst4, float(fEntry3))))))));
		float fSlow7 = ((fConst2 * fSlow5) - (fConst5 * (fSlow6 / fSlow5)));
		float fSlow8 = (fConst7 * fSlow6);
		float fSlow9 = (fConst1 * fSlow7);
		float fSlow10 = ((fSlow8 + fSlow9) + 4.0f);
		float fSlow11 = (fConst1 * (fSlow7 / fSlow10));
		float fSlow12 = std::pow(10.0f, float(fEntry4));
		float fSlow13 = (1.0f / fSlow10);
		float fSlow14 = ((fConst8 * fSlow6) + -8.0f);
		float fSlow15 = (fSlow8 + (4.0f - fSlow9));
		float fSlow16 = (0.0f - fSlow11);
		float fSlow17 = float(fEntry5);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTempFTZ0 = ((fSlow12 * fTemp0) - (fSlow13 * ((fSlow14 * fRec0[1]) + (fSlow15 * fRec0[2]))));
			fRec0[0] = ((*reinterpret_cast<int*>(&fTempFTZ0) & 2139095040) ? fTempFTZ0 : 0.0f);
			float fTempFTZ1 = ((fConst9 * std::max<float>(0.0f, (std::max<float>(0.0f, fTemp0) - fRec1[1]))) + (fConst10 * fRec1[1]));
			fRec1[0] = ((*reinterpret_cast<int*>(&fTempFTZ1) & 2139095040) ? fTempFTZ1 : 0.0f);
			float fTemp1 = (std::fabs((fSlow17 * fRec1[0])) + 1.0f);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow4 * (((fSlow11 * fRec0[0]) + (fSlow16 * fRec0[2])) * fTemp1))));
			float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
			output0[i] = FAUSTFLOAT(((fSlow1 * fTemp0) + (fSlow3 * ((fTemp3 * (std::fabs(fTemp3) + -2.0f)) / fTemp1))));
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
		}
	}

};

#endif
