/* ------------------------------------------------------------
name: "YellowOD"
Code generated with Faust 2.28.3 (https://faust.grame.fr)
Compilation options: -lang cpp -inpl -scal -ftz 2
------------------------------------------------------------ */

#ifndef  __YellowODFaust_H__
#define  __YellowODFaust_H__

#include "FaustImpl.h"
#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float YellowODFaust_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS YellowODFaust
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class YellowODFaust : public FaustImpl {
	
 private:
	
	float fVec0[2];
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
	float fConst10;
	FAUSTFLOAT fEntry3;
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
	float fConst27;
	float fConst28;
	float fConst29;
	float fConst30;
	float fConst31;
	float fConst32;
	float fConst33;
	float fConst34;
	float fConst35;
	float fConst36;
	float fRec9[2];
	float fConst37;
	float fConst38;
	float fRec8[2];
	float fConst39;
	float fConst40;
	float fRec7[2];
	float fConst41;
	float fRec6[2];
	float fConst42;
	float fRec5[2];
	float fVec1[2];
	float fConst43;
	float fConst44;
	float fRec4[2];
	float fConst45;
	float fRec3[3];
	float fVec2[2];
	float fRec2[2];
	float fConst46;
	float fConst47;
	float fRec1[2];
	float fRec0[2];
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fRec10[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("filename", "YellowOD.dsp");
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
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
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
		m->declare("name", "YellowOD");
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
		fConst1 = (1.0f / std::tan((735.13269f / fConst0)));
		fConst2 = (1.0f / (fConst1 + 1.0f));
		fConst3 = (1.0f - fConst1);
		fConst4 = std::tan((10.6814146f / fConst0));
		fConst5 = (1.0f / fConst4);
		fConst6 = (fConst5 + 1.0f);
		fConst7 = (0.0f - (1.0f / (fConst4 * fConst6)));
		fConst8 = (1.0f / std::tan((22619.4668f / fConst0)));
		fConst9 = (1.0f / (fConst8 + 1.0f));
		fConst10 = (1.0f - fConst8);
		fConst11 = (2.0f / fConst0);
		fConst12 = std::tan((50265.4844f / fConst0));
		fConst13 = (fConst0 * fConst12);
		fConst14 = (2.0f * fConst13);
		fConst15 = (0.5f / fConst13);
		fConst16 = (4.0f * (YellowODFaust_faustpower2_f(fConst0) * fConst12));
		fConst17 = (1068.14148f / fConst0);
		fConst18 = YellowODFaust_faustpower2_f((1.0f / fConst0));
		fConst19 = std::tan((72.2566299f / fConst0));
		fConst20 = (1.0f / fConst19);
		fConst21 = (fConst20 + 1.0f);
		fConst22 = (0.0f - (1.0f / (fConst19 * fConst21)));
		fConst23 = std::tan((103.672554f / fConst0));
		fConst24 = (1.0f / fConst23);
		fConst25 = (fConst24 + 1.0f);
		fConst26 = (0.0f - (1.0f / (fConst23 * fConst25)));
		fConst27 = std::tan((9.42477798f / fConst0));
		fConst28 = (1.0f / fConst27);
		fConst29 = (fConst28 + 1.0f);
		fConst30 = (0.0f - (1.0f / (fConst27 * fConst29)));
		fConst31 = std::tan((22.6194668f / fConst0));
		fConst32 = (1.0f / fConst31);
		fConst33 = (fConst32 + 1.0f);
		fConst34 = (0.0f - (1.0f / (fConst31 * fConst33)));
		fConst35 = (1.0f / fConst33);
		fConst36 = (1.0f - fConst32);
		fConst37 = (1.0f / fConst29);
		fConst38 = (1.0f - fConst28);
		fConst39 = (1.0f / fConst25);
		fConst40 = (1.0f - fConst24);
		fConst41 = (1.0f - std::exp((0.0f - (100000.0f / fConst0))));
		fConst42 = (1.0f - std::exp((0.0f - (250000.0f / fConst0))));
		fConst43 = (1.0f / fConst21);
		fConst44 = (1.0f - fConst20);
		fConst45 = (2.0f * fConst18);
		fConst46 = (1.0f / fConst6);
		fConst47 = (1.0f - fConst5);
		fConst48 = std::tan((3339.51294f / fConst0));
		fConst49 = (1.0f / fConst48);
		fConst50 = (fConst49 + 1.0f);
		fConst51 = (0.0f - (1.0f / (fConst48 * fConst50)));
		fConst52 = (1.0f / fConst50);
		fConst53 = (1.0f - fConst49);
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = FAUSTFLOAT(0.0f);
		fEntry1 = FAUSTFLOAT(0.0f);
		fEntry2 = FAUSTFLOAT(0.0f);
		fEntry3 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec9[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec8[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec7[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec6[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec5[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;
		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec4[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 3); l8 = (l8 + 1)) {
			fRec3[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fVec2[l9] = 0.0f;
		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec2[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec1[l11] = 0.0f;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec0[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec10[l13] = 0.0f;
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
	
	virtual YellowODFaust* clone() {
		return new YellowODFaust();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("YellowOD");
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
		float fSlow3 = ((2.0f * float(fEntry2)) + -1.0f);
		float fSlow4 = std::max<float>((0.0f - fSlow3), 0.0f);
		float fSlow5 = std::max<float>(fSlow3, 0.0f);
		float fSlow6 = ((0.129999995f * fSlow4) + (0.200000003f - (0.100000001f * fSlow5)));
		float fSlow7 = float(fEntry3);
		float fSlow8 = ((21.0f * fSlow7) + 1.0f);
		float fSlow9 = YellowODFaust_faustpower2_f(std::sqrt((fConst16 * std::tan((fConst17 / ((95.3000031f * (1.0f - fSlow7)) + 4.69999981f))))));
		float fSlow10 = (fConst14 - (fConst15 * fSlow9));
		float fSlow11 = (fConst18 * fSlow9);
		float fSlow12 = (fConst11 * fSlow10);
		float fSlow13 = ((fSlow11 + fSlow12) + 4.0f);
		float fSlow14 = (fConst11 * (fSlow10 / fSlow13));
		float fSlow15 = ((50.0f * fSlow7) + 5.0f);
		float fSlow16 = (1.0f / fSlow13);
		float fSlow17 = ((fConst45 * fSlow9) + -8.0f);
		float fSlow18 = (fSlow11 + (4.0f - fSlow12));
		float fSlow19 = (0.0f - fSlow14);
		float fSlow20 = (fSlow11 + 4.0f);
		float fSlow21 = ((0.129999995f * fSlow5) + (0.200000003f * (1.0f - fSlow4)));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = fTemp0;
			float fTempFTZ0 = ((fConst34 * fVec0[1]) - (fConst35 * ((fConst36 * fRec9[1]) - (fConst32 * fTemp0))));
			fRec9[0] = ((*reinterpret_cast<int*>(&fTempFTZ0) & 2139095040) ? fTempFTZ0 : 0.0f);
			float fTempFTZ1 = ((fConst30 * fRec9[1]) - (fConst37 * ((fConst38 * fRec8[1]) - (fConst28 * fRec9[0]))));
			fRec8[0] = ((*reinterpret_cast<int*>(&fTempFTZ1) & 2139095040) ? fTempFTZ1 : 0.0f);
			float fTempFTZ2 = ((fConst26 * fRec8[1]) - (fConst39 * ((fConst40 * fRec7[1]) - (fConst24 * fRec8[0]))));
			fRec7[0] = ((*reinterpret_cast<int*>(&fTempFTZ2) & 2139095040) ? fTempFTZ2 : 0.0f);
			float fTemp1 = (fSlow15 * fRec7[0]);
			float fTempFTZ3 = (std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp1 + -5.0f)) - fRec6[1])) + (fConst41 * fRec6[1]));
			fRec6[0] = ((*reinterpret_cast<int*>(&fTempFTZ3) & 2139095040) ? fTempFTZ3 : 0.0f);
			float fTempFTZ4 = (std::max<float>(0.0f, (std::max<float>(0.0f, (fRec6[0] + (-4.0f - fTemp1))) - fRec5[1])) + (fConst42 * fRec5[1]));
			fRec5[0] = ((*reinterpret_cast<int*>(&fTempFTZ4) & 2139095040) ? fTempFTZ4 : 0.0f);
			float fTemp2 = ((fRec5[0] + fTemp1) + (-4.0f - fRec6[0]));
			float fTemp3 = std::max<float>(-1.0f, std::min<float>(1.0f, (0.294117659f * std::max<float>(0.0f, fTemp2))));
			float fTemp4 = (fTemp3 * (std::fabs(fTemp3) + -2.0f));
			float fTemp5 = ((std::min<float>(0.0f, fTemp2) + (fTemp4 * (std::fabs(fTemp4) + -2.0f))) + 7.0f);
			float fTemp6 = std::max<float>(-1.0f, std::min<float>(1.0f, (0.294117659f * std::min<float>(0.0f, fTemp5))));
			float fTemp7 = (fTemp6 * (std::fabs(fTemp6) + -2.0f));
			float fTemp8 = (((fTemp7 * (std::fabs(fTemp7) + -2.0f)) + std::max<float>(0.0f, fTemp5)) + -3.0f);
			fVec1[0] = fTemp8;
			float fTempFTZ5 = ((fConst22 * fVec1[1]) - (fConst43 * ((fConst44 * fRec4[1]) - (fConst20 * fTemp8))));
			fRec4[0] = ((*reinterpret_cast<int*>(&fTempFTZ5) & 2139095040) ? fTempFTZ5 : 0.0f);
			float fTemp9 = (fSlow17 * fRec3[1]);
			float fTempFTZ6 = (fRec4[0] - (fSlow16 * (fTemp9 + (fSlow18 * fRec3[2]))));
			fRec3[0] = ((*reinterpret_cast<int*>(&fTempFTZ6) & 2139095040) ? fTempFTZ6 : 0.0f);
			float fTemp10 = ((fSlow8 * ((fSlow14 * fRec3[0]) + (fSlow19 * fRec3[2]))) + (fSlow16 * ((fTemp9 + (fSlow20 * fRec3[0])) + (fSlow20 * fRec3[2]))));
			float fTemp11 = std::max<float>(-1.0f, std::min<float>(1.0f, (0.980392158f * std::max<float>(0.0f, fTemp10))));
			float fTemp12 = (fTemp11 * (std::fabs(fTemp11) + -2.0f));
			float fTemp13 = ((std::min<float>(0.0f, fTemp10) + (0.300000012f * (fTemp12 * (std::fabs(fTemp12) + -2.0f)))) + 0.800000012f);
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (0.980392158f * std::min<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((0.300000012f * (fTemp15 * (std::fabs(fTemp15) + -2.0f))) + std::max<float>(0.0f, fTemp13)) + -0.400000006f);
			fVec2[0] = fTemp16;
			float fTempFTZ7 = (0.0f - (fConst9 * ((fConst10 * fRec2[1]) - (fTemp16 + fVec2[1]))));
			fRec2[0] = ((*reinterpret_cast<int*>(&fTempFTZ7) & 2139095040) ? fTempFTZ7 : 0.0f);
			float fTempFTZ8 = ((fConst7 * fRec2[1]) - (fConst46 * ((fConst47 * fRec1[1]) - (fConst5 * fRec2[0]))));
			fRec1[0] = ((*reinterpret_cast<int*>(&fTempFTZ8) & 2139095040) ? fTempFTZ8 : 0.0f);
			float fTempFTZ9 = (0.0f - (fConst2 * ((fConst3 * fRec0[1]) - (fRec1[0] + fRec1[1]))));
			fRec0[0] = ((*reinterpret_cast<int*>(&fTempFTZ9) & 2139095040) ? fTempFTZ9 : 0.0f);
			float fTempFTZ10 = ((fConst51 * fRec1[1]) - (fConst52 * ((fConst53 * fRec10[1]) - (fConst49 * fRec1[0]))));
			fRec10[0] = ((*reinterpret_cast<int*>(&fTempFTZ10) & 2139095040) ? fTempFTZ10 : 0.0f);
			output0[i] = FAUSTFLOAT((fSlow0 * ((fSlow2 * fTemp0) + (fSlow1 * ((fSlow6 * fRec0[0]) + (fSlow21 * fRec10[0]))))));
			fVec0[1] = fVec0[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fRec5[1] = fRec5[0];
			fVec1[1] = fVec1[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec2[1] = fVec2[0];
			fRec2[1] = fRec2[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec10[1] = fRec10[0];
		}
	}

};

#endif
