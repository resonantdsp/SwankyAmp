/* ------------------------------------------------------------
name: "GreenOD"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef  __GreenODFaust_H__
#define  __GreenODFaust_H__

#include "FaustImpl.h"
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float GreenODFaust_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS GreenODFaust
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class GreenODFaust : public FaustImpl {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
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
	FAUSTFLOAT fEntry3;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec2[3];
	float fVec0[2];
	float fRec1[2];
	float fConst17;
	float fConst18;
	float fRec0[2];
	float fRec3[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "GreenOD.dsp");
		m->declare("filters.lib/bandpass0_bandstop1:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass0_bandstop1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass0_bandstop1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandpass:author", "Julius O. Smith III");
		m->declare("filters.lib/bandpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/bandstop:author", "Julius O. Smith III");
		m->declare("filters.lib/bandstop:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/bandstop:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
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
		m->declare("name", "GreenOD");
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
		fConst1 = (0.449999988f * fConst0);
		fConst2 = std::tan((3.14159274f * (std::min<float>(fConst1, 3200.0f) / fConst0)));
		fConst3 = (1.0f / fConst2);
		fConst4 = (fConst3 + 1.0f);
		fConst5 = (0.0f - (1.0f / (fConst2 * fConst4)));
		fConst6 = std::tan((3.14159274f * (std::min<float>(fConst1, 720.0f) / fConst0)));
		fConst7 = (1.0f / fConst6);
		fConst8 = (1.0f / (fConst7 + 1.0f));
		fConst9 = (1.0f - fConst7);
		fConst10 = (2.0f / fConst0);
		fConst11 = (2.0f * fConst0);
		fConst12 = (3.14159274f / fConst0);
		fConst13 = (0.5f / fConst0);
		fConst14 = (4.0f * (GreenODFaust_faustpower2_f(fConst0) * fConst6));
		fConst15 = GreenODFaust_faustpower2_f((1.0f / fConst0));
		fConst16 = (2.0f * fConst15);
		fConst17 = (1.0f / fConst4);
		fConst18 = (1.0f - fConst3);
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fEntry3 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 3); l0 = (l0 + 1)) {
			fRec2[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fVec0[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec1[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec0[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec3[l4] = 0.0f;
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
	
	virtual GreenODFaust* clone() {
		return new GreenODFaust();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("GreenOD");
		ui_interface->addNumEntry("drive", &fEntry3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("level", &fEntry0, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("mix", &fEntry1, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->addNumEntry("tone", &fEntry2, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(10.0f, (1.75f * float(fEntry0)));
		float fSlow1 = float(fEntry1);
		float fSlow2 = (1.0f - fSlow1);
		float fSlow3 = float(fEntry2);
		float fSlow4 = ((50.0f * float(fEntry3)) + 5.0f);
		float fSlow5 = ((2.0f * fSlow4) + 1.0f);
		float fSlow6 = std::tan((fConst12 * std::min<float>(fConst1, (312500.0f / fSlow4))));
		float fSlow7 = GreenODFaust_faustpower2_f(std::sqrt((fConst14 * fSlow6)));
		float fSlow8 = ((fConst11 * fSlow6) - (fConst13 * (fSlow7 / fSlow6)));
		float fSlow9 = (fConst15 * fSlow7);
		float fSlow10 = (fConst10 * fSlow8);
		float fSlow11 = ((fSlow9 + fSlow10) + 4.0f);
		float fSlow12 = (fConst10 * (fSlow8 / fSlow11));
		float fSlow13 = (1.0f / fSlow11);
		float fSlow14 = ((fConst16 * fSlow7) + -8.0f);
		float fSlow15 = (fSlow9 + (4.0f - fSlow10));
		float fSlow16 = (0.0f - fSlow12);
		float fSlow17 = (1.0f / fSlow5);
		float fSlow18 = (fSlow9 + 4.0f);
		float fSlow19 = (1.0f - fSlow3);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			float fTemp1 = (fSlow14 * fRec2[1]);
			float fTempFTZ0 = (fTemp0 - (fSlow13 * (fTemp1 + (fSlow15 * fRec2[2]))));
			fRec2[0] = ((*reinterpret_cast<int*>(&fTempFTZ0) & 2139095040) ? fTempFTZ0 : 0.0f);
			float fTemp2 = ((fSlow12 * fRec2[0]) + (fSlow16 * fRec2[2]));
			float fTemp3 = (fSlow5 * fTemp2);
			float fTemp4 = (fSlow5 * (0.0f - fTemp2));
			float fTemp5 = ((std::max<float>(0.0f, (std::min<float>(1.0f, fTemp3) + (fSlow17 * (std::max<float>(1.0f, fTemp3) + -1.0f)))) + (fSlow13 * ((fTemp1 + (fSlow18 * fRec2[0])) + (fSlow18 * fRec2[2])))) - std::max<float>(0.0f, (std::min<float>(1.0f, fTemp4) + (fSlow17 * (std::max<float>(1.0f, fTemp4) + -1.0f)))));
			fVec0[0] = fTemp5;
			float fTempFTZ1 = (0.0f - (fConst8 * ((fConst9 * fRec1[1]) - (fTemp5 + fVec0[1]))));
			fRec1[0] = ((*reinterpret_cast<int*>(&fTempFTZ1) & 2139095040) ? fTempFTZ1 : 0.0f);
			float fTempFTZ2 = ((fConst5 * fRec1[1]) - (fConst17 * ((fConst18 * fRec0[1]) - (fConst3 * fRec1[0]))));
			fRec0[0] = ((*reinterpret_cast<int*>(&fTempFTZ2) & 2139095040) ? fTempFTZ2 : 0.0f);
			float fTempFTZ3 = (0.0f - (fConst17 * ((fConst18 * fRec3[1]) - (fRec1[0] + fRec1[1]))));
			fRec3[0] = ((*reinterpret_cast<int*>(&fTempFTZ3) & 2139095040) ? fTempFTZ3 : 0.0f);
			output0[i] = FAUSTFLOAT((fSlow0 * ((fSlow2 * fTemp0) + (fSlow1 * ((fSlow3 * fRec0[0]) + (fSlow19 * fRec3[0]))))));
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec0[1] = fVec0[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif
