/* ------------------------------------------------------------
name: "AmpMono"
Code generated with Faust 2.14.4 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __AmpMono_H__
#define  __AmpMono_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <math.h>

static float AmpMono_faustpower3_f(float value) {
	return ((value * value) * value);

}
static float AmpMono_faustpower2_f(float value) {
	return (value * value);

}

#ifndef FAUSTCLASS
#define FAUSTCLASS AmpMono
#endif
#ifdef __APPLE__
#define exp10f __exp10f
#define exp10 __exp10
#endif

class AmpMono {

 private:

	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fEntry1;
	FAUSTFLOAT fEntry2;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	FAUSTFLOAT fEntry15;
	FAUSTFLOAT fEntry16;
	FAUSTFLOAT fEntry17;
	FAUSTFLOAT fEntry18;
	FAUSTFLOAT fEntry19;
	FAUSTFLOAT fEntry20;
	FAUSTFLOAT fEntry21;
	FAUSTFLOAT fEntry22;
	FAUSTFLOAT fEntry23;
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	float fVec0[2];
	float fRec13[2];
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	float fRec15[2];
	float fRec14[2];
	FAUSTFLOAT fEntry30;
	float fConst6;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	float fRec16[2];
	float fRec17[2];
	FAUSTFLOAT fEntry33;
	float fVec1[2];
	float fRec12[2];
	float fRec19[2];
	float fRec18[2];
	float fRec20[2];
	float fRec11[2];
	float fVec2[2];
	float fRec10[2];
	float fRec22[2];
	float fRec21[2];
	float fRec23[2];
	float fRec24[2];
	float fVec3[2];
	float fRec28[2];
	float fRec30[2];
	float fRec29[2];
	float fRec31[2];
	float fRec27[2];
	float fVec4[2];
	float fRec26[2];
	float fRec33[2];
	float fRec32[2];
	float fRec34[2];
	float fRec25[2];
	float fVec5[2];
	float fRec9[2];
	float fRec36[2];
	float fRec35[2];
	float fRec37[2];
	float fRec38[2];
	float fVec6[2];
	float fRec8[2];
	float fRec40[2];
	float fRec39[2];
	float fRec41[2];
	float fRec7[2];
	float fVec7[2];
	float fRec6[2];
	float fRec42[2];
	float fVec8[2];
	float fConst7;
	float fConst8;
	float fRec5[2];
	float fConst9;
	float fConst10;
	FAUSTFLOAT fEntry34;
	float fConst11;
	float fConst12;
	float fConst13;
	float fRec4[3];
	float fConst14;
	float fRec3[3];
	float fVec9[2];
	FAUSTFLOAT fEntry35;
	float fRec2[2];
	float fRec43[2];
	float fConst15;
	float fConst16;
	float fConst17;
	FAUSTFLOAT fEntry36;
	float fConst18;
	float fRec1[3];
	FAUSTFLOAT fEntry37;
	float fVec10[2];
	float fRec0[2];
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	float fRec44[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fRec45[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec47[2];
	float fRec46[2];
	FAUSTFLOAT fEntry49;
	float fRec48[2];
	float fRec49[2];
	FAUSTFLOAT fEntry50;
	FAUSTFLOAT fEntry51;
	FAUSTFLOAT fEntry52;
	float fRec50[2];
	FAUSTFLOAT fEntry53;
	FAUSTFLOAT fEntry54;
	float fRec51[2];
	FAUSTFLOAT fEntry55;
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
	float fConst37;
	float fConst38;
	float fConst39;
	float fConst40;
	float fConst41;
	float fConst42;
	float fConst43;
	float fConst44;
	float fConst45;
	float fConst46;
	float fConst47;
	float fConst48;
	float fConst49;
	float fConst50;
	float fConst51;
	float fConst52;
	float fConst53;
	float fConst54;
	float fConst55;
	float fConst56;
	float fConst57;
	float fConst58;
	float fConst59;
	float fConst60;
	float fConst61;
	float fConst62;
	float fConst63;
	float fConst64;
	float fConst65;
	float fConst66;
	float fConst67;
	float fConst68;
	float fConst69;
	float fConst70;
	float fConst71;
	float fConst72;
	float fConst73;
	float fConst74;
	float fConst75;
	float fConst76;
	float fConst77;
	float fConst78;
	float fConst79;
	float fConst80;
	float fConst81;
	float fConst82;
	float fConst83;
	float fConst84;
	float fConst85;
	float fConst86;
	float fConst87;
	float fConst88;
	float fConst89;
	float fConst90;
	float fConst91;
	float fConst92;
	float fConst93;
	float fConst94;
	float fConst95;
	float fConst96;
	float fConst97;
	float fConst98;
	float fConst99;
	float fConst100;
	float fConst101;
	float fConst102;
	float fConst103;
	float fConst104;
	float fConst105;
	float fConst106;
	float fConst107;
	float fConst108;
	float fConst109;
	float fConst110;
	float fConst111;
	float fConst112;
	float fConst113;
	float fConst114;
	float fConst115;
	float fConst116;
	float fConst117;
	float fRec74[3];
	float fConst118;
	float fConst119;
	float fRec73[3];
	float fVec11[2];
	float fRec72[2];
	float fConst120;
	float fConst121;
	float fRec71[3];
	float fVec12[2];
	float fConst122;
	float fConst123;
	float fRec70[2];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec69[3];
	float fConst127;
	float fRec68[3];
	float fConst128;
	float fRec67[3];
	float fConst129;
	float fRec78[2];
	float fRec77[3];
	float fRec76[3];
	float fRec75[3];
	float fConst130;
	float fRec66[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec65[3];
	float fConst136;
	float fConst137;
	float fRec64[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec63[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec62[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec61[3];
	float fConst150;
	float fConst151;
	float fRec60[3];
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec59[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec58[3];
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec57[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fVec13[2];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec56[2];
	float fConst170;
	float fConst171;
	float fRec55[3];
	float fConst172;
	FAUSTFLOAT fEntry56;
	float fConst173;
	float fRec80[2];
	float fRec79[3];
	float fConst174;
	float fConst175;
	float fRec54[3];
	float fConst176;
	float fConst177;
	float fRec53[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec52[3];

 public:


	virtual int getNumInputs() {
		return 1;

	}
	virtual int getNumOutputs() {
		return 1;

	}
	virtual int getInputRate(int channel) {
		int rate;
		switch (channel) {
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
		switch (channel) {
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

	static void classInit(int samplingFreq) {

	}

	virtual void instanceConstants(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
		fConst1 = (3.14159274f / fConst0);
		fConst2 = std::tan((31.415926f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (fConst3 + 1.0f);
		fConst5 = (0.0f - (1.0f / (fConst2 * fConst4)));
		fConst6 = (1.0f / fConst0);
		fConst7 = (1.0f / fConst4);
		fConst8 = (1.0f - fConst3);
		fConst9 = std::tan((1570.79639f / fConst0));
		fConst10 = (1.0f / fConst9);
		fConst11 = (fConst0 * std::sin((3141.59277f / fConst0)));
		fConst12 = (3.14159274f / fConst11);
		fConst13 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst14 = (3141.59277f / fConst11);
		fConst15 = std::tan((12566.3711f / fConst0));
		fConst16 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst15))));
		fConst17 = (1.0f / fConst15);
		fConst18 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
		fConst19 = std::tan((219.911484f / fConst0));
		fConst20 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst19))));
		fConst21 = std::tan((18849.5566f / fConst0));
		fConst22 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst21))));
		fConst23 = std::tan((3455.75195f / fConst0));
		fConst24 = (1.0f / fConst23);
		fConst25 = (1.0f / (((fConst24 + 1.0f) / fConst23) + 1.0f));
		fConst26 = AmpMono_faustpower2_f(fConst23);
		fConst27 = (1.0f / fConst26);
		fConst28 = std::tan((2984.51294f / fConst0));
		fConst29 = (1.0f / fConst28);
		fConst30 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst31 = (27816.8476f / fConst30);
		fConst32 = (1.0f / (((fConst29 + fConst31) / fConst28) + 1.0f));
		fConst33 = (fConst24 + 1.0f);
		fConst34 = (1.0f / (fConst23 * fConst33));
		fConst35 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
		fConst36 = (37699.1133f / fConst0);
		fConst37 = std::tan(fConst36);
		fConst38 = (1.0f / fConst37);
		fConst39 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst40 = (24836.4707f / fConst39);
		fConst41 = (1.0f / (((fConst38 + fConst40) / fConst37) + 1.0f));
		fConst42 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst37))));
		fConst43 = std::tan((21362.8301f / fConst0));
		fConst44 = (1.0f / fConst43);
		fConst45 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst46 = (19869.1758f / fConst45);
		fConst47 = (1.0f / (((fConst44 + fConst46) / fConst43) + 1.0f));
		fConst48 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst43))));
		fConst49 = std::tan((11938.0518f / fConst0));
		fConst50 = (1.0f / fConst49);
		fConst51 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst52 = (4701.22607f / fConst51);
		fConst53 = (1.0f / (((fConst50 + fConst52) / fConst49) + 1.0f));
		fConst54 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst49))));
		fConst55 = std::tan((9581.85742f / fConst0));
		fConst56 = (1.0f / fConst55);
		fConst57 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst58 = (2921.88965f / fConst57);
		fConst59 = (1.0f / (((fConst56 + fConst58) / fConst55) + 1.0f));
		fConst60 = (1036.72558f / fConst57);
		fConst61 = (((fConst56 + fConst60) / fConst55) + 1.0f);
		fConst62 = std::tan((5215.04394f / fConst0));
		fConst63 = (1.0f / fConst62);
		fConst64 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst65 = (3713.44482f / fConst64);
		fConst66 = (1.0f / (((fConst63 + fConst65) / fConst62) + 1.0f));
		fConst67 = (2481.85815f / fConst64);
		fConst68 = (((fConst63 - fConst67) / fConst62) + 1.0f);
		fConst69 = (3707.07935f / fConst0);
		fConst70 = std::tan(fConst69);
		fConst71 = (1.0f / fConst70);
		fConst72 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst73 = (502.654816f / fConst72);
		fConst74 = (1.0f / (((fConst71 + fConst73) / fConst70) + 1.0f));
		fConst75 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst70))));
		fConst76 = std::tan((3518.58374f / fConst0));
		fConst77 = (1.0f / fConst76);
		fConst78 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst79 = (875.483398f / fConst78);
		fConst80 = (1.0f / (((fConst77 + fConst79) / fConst76) + 1.0f));
		fConst81 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst76))));
		fConst82 = std::tan((2010.61926f / fConst0));
		fConst83 = (1.0f / fConst82);
		fConst84 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst85 = (439.822968f / fConst84);
		fConst86 = (1.0f / (((fConst83 + fConst85) / fConst82) + 1.0f));
		fConst87 = (1390.84241f / fConst84);
		fConst88 = (((fConst83 + fConst87) / fConst82) + 1.0f);
		fConst89 = std::tan((1853.53967f / fConst0));
		fConst90 = (1.0f / fConst89);
		fConst91 = (fConst0 * std::sin(fConst69));
		fConst92 = (1059.9884f / fConst91);
		fConst93 = (1.0f / (((fConst90 + fConst92) / fConst89) + 1.0f));
		fConst94 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst89))));
		fConst95 = std::tan((17592.918f / fConst0));
		fConst96 = (1.0f / fConst95);
		fConst97 = (1.0f / (((fConst96 + 0.445041865f) / fConst95) + 1.0f));
		fConst98 = AmpMono_faustpower2_f(fConst95);
		fConst99 = (0.0f - (2.0f / fConst98));
		fConst100 = (1.0f / (((fConst96 + 1.24697959f) / fConst95) + 1.0f));
		fConst101 = (1.0f / (((fConst96 + 1.8019377f) / fConst95) + 1.0f));
		fConst102 = std::tan((34557.5195f / fConst0));
		fConst103 = (1.0f / fConst102);
		fConst104 = (1.0f / (((fConst103 + 1.0f) / fConst102) + 1.0f));
		fConst105 = (fConst96 + 1.0f);
		fConst106 = (1.0f / (fConst95 * fConst105));
		fConst107 = (0.0f - fConst106);
		fConst108 = (1.0f / (fConst103 + 1.0f));
		fConst109 = (1.0f - fConst103);
		fConst110 = std::tan((345.575195f / fConst0));
		fConst111 = (1.0f / fConst110);
		fConst112 = (1.0f / (((fConst111 + 0.765366852f) / fConst110) + 1.0f));
		fConst113 = AmpMono_faustpower2_f(fConst110);
		fConst114 = (1.0f / fConst113);
		fConst115 = (1.0f / (((fConst111 + 1.84775901f) / fConst110) + 1.0f));
		fConst116 = (2.0f * (1.0f - fConst114));
		fConst117 = (((fConst111 + -1.84775901f) / fConst110) + 1.0f);
		fConst118 = (0.0f - (2.0f / fConst113));
		fConst119 = (((fConst111 + -0.765366852f) / fConst110) + 1.0f);
		fConst120 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst102))));
		fConst121 = (((fConst103 + -1.0f) / fConst102) + 1.0f);
		fConst122 = (1.0f - fConst96);
		fConst123 = (fConst122 / fConst105);
		fConst124 = (((fConst96 + -1.8019377f) / fConst95) + 1.0f);
		fConst125 = (1.0f / fConst98);
		fConst126 = (2.0f * (1.0f - fConst125));
		fConst127 = (((fConst96 + -1.24697959f) / fConst95) + 1.0f);
		fConst128 = (((fConst96 + -0.445041865f) / fConst95) + 1.0f);
		fConst129 = (1.0f / fConst105);
		fConst130 = (((fConst90 - fConst92) / fConst89) + 1.0f);
		fConst131 = (188.49556f / fConst91);
		fConst132 = (((fConst90 + fConst131) / fConst89) + 1.0f);
		fConst133 = (((fConst90 - fConst131) / fConst89) + 1.0f);
		fConst134 = (((fConst83 - fConst85) / fConst82) + 1.0f);
		fConst135 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst82))));
		fConst136 = (((fConst83 - fConst87) / fConst82) + 1.0f);
		fConst137 = (((fConst77 - fConst79) / fConst76) + 1.0f);
		fConst138 = (219.911484f / fConst78);
		fConst139 = (((fConst77 + fConst138) / fConst76) + 1.0f);
		fConst140 = (((fConst77 - fConst138) / fConst76) + 1.0f);
		fConst141 = (((fConst71 - fConst73) / fConst70) + 1.0f);
		fConst142 = (1416.67383f / fConst72);
		fConst143 = (((fConst71 + fConst142) / fConst70) + 1.0f);
		fConst144 = (((fConst71 - fConst142) / fConst70) + 1.0f);
		fConst145 = (((fConst63 - fConst65) / fConst62) + 1.0f);
		fConst146 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst62))));
		fConst147 = (((fConst63 + fConst67) / fConst62) + 1.0f);
		fConst148 = (((fConst56 - fConst58) / fConst55) + 1.0f);
		fConst149 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst55))));
		fConst150 = (((fConst56 - fConst60) / fConst55) + 1.0f);
		fConst151 = (((fConst50 - fConst52) / fConst49) + 1.0f);
		fConst152 = (2356.19458f / fConst51);
		fConst153 = (((fConst50 + fConst152) / fConst49) + 1.0f);
		fConst154 = (((fConst50 - fConst152) / fConst49) + 1.0f);
		fConst155 = (((fConst44 - fConst46) / fConst43) + 1.0f);
		fConst156 = (628.318542f / fConst45);
		fConst157 = (((fConst44 + fConst156) / fConst43) + 1.0f);
		fConst158 = (((fConst44 - fConst156) / fConst43) + 1.0f);
		fConst159 = (((fConst38 - fConst40) / fConst37) + 1.0f);
		fConst160 = (785.398193f / fConst39);
		fConst161 = (((fConst38 + fConst160) / fConst37) + 1.0f);
		fConst162 = (((fConst38 - fConst160) / fConst37) + 1.0f);
		fConst163 = (((fConst29 - fConst31) / fConst28) + 1.0f);
		fConst164 = (8796.45898f / fConst30);
		fConst165 = (((fConst29 + fConst164) / fConst28) + 1.0f);
		fConst166 = (((fConst29 - fConst164) / fConst28) + 1.0f);
		fConst167 = (0.0f - fConst34);
		fConst168 = (1.0f - fConst24);
		fConst169 = (fConst168 / fConst33);
		fConst170 = (2.0f * (1.0f - fConst27));
		fConst171 = (((fConst24 + -1.0f) / fConst23) + 1.0f);
		fConst172 = (0.0f - (2.0f / fConst26));
		fConst173 = (1.0f / fConst33);
		fConst174 = (1.0f / fConst21);
		fConst175 = (3141.59277f / (fConst0 * std::sin(fConst36)));
		fConst176 = (1.0f / fConst19);
		fConst177 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst178 = std::tan((3769.91113f / fConst0));
		fConst179 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst178))));
		fConst180 = (1.0f / fConst178);
		fConst181 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));

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
		fEntry41 = FAUSTFLOAT(0.0f);
		fEntry42 = FAUSTFLOAT(0.0f);
		fEntry43 = FAUSTFLOAT(0.0f);
		fEntry44 = FAUSTFLOAT(0.0f);
		fEntry45 = FAUSTFLOAT(0.0f);
		fEntry46 = FAUSTFLOAT(0.0f);
		fEntry47 = FAUSTFLOAT(0.0f);
		fEntry48 = FAUSTFLOAT(0.0f);
		fEntry49 = FAUSTFLOAT(0.0f);
		fEntry50 = FAUSTFLOAT(0.0f);
		fEntry51 = FAUSTFLOAT(0.0f);
		fEntry52 = FAUSTFLOAT(0.0f);
		fEntry53 = FAUSTFLOAT(0.0f);
		fEntry54 = FAUSTFLOAT(0.0f);
		fEntry55 = FAUSTFLOAT(0.0f);
		fEntry56 = FAUSTFLOAT(0.0f);

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec13[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec15[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec14[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec16[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec17[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec12[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec19[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec18[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec20[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec11[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec10[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec22[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec21[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec23[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec24[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec28[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec30[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec29[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec31[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec27[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec26[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec33[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec32[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec34[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec25[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec9[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec36[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec35[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec37[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec38[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec6[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec8[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec40[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec39[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec41[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec7[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec7[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec6[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec42[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec8[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec5[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec4[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec3[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec9[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec2[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec43[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec1[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fVec10[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec0[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec44[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec45[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec47[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec46[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec48[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec49[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec50[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec51[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec74[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec73[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fVec11[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec72[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec71[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fVec12[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec70[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec69[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec68[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec67[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec78[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec77[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec76[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec75[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec66[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec65[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec64[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec63[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec62[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec61[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec60[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec59[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec58[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec57[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fVec13[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec56[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec55[l89] = 0.0f;

		}
		for (int l90 = 0; (l90 < 2); l90 = (l90 + 1)) {
			fRec80[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec79[l91] = 0.0f;

		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec54[l92] = 0.0f;

		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec53[l93] = 0.0f;

		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec52[l94] = 0.0f;

		}

	}

	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	virtual void instanceInit(int samplingFreq) {
		instanceConstants(samplingFreq);
		instanceResetUserInterface();
		instanceClear();
	}

	virtual AmpMono* clone() {
		return new AmpMono();
	}
	virtual int getSampleRate() {
		return fSamplingFreq;

	}

	void set_cab_brightness(FAUSTFLOAT value) { fEntry56 = value + 0.000000e+00f; }
	void set_cab_distance(FAUSTFLOAT value) { fEntry55 = value + 0.000000e+00f; }
	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry25 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry24 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry41 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry37 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry39 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry42 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry40 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry38 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry7 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry43 = value + 3.866967e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry5 = value + 1.049631e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry44 = value + -6.951565e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry45 = value + -1.091596e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry49 = value + 5.941641e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry53 = value + -2.019639e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry54 = value + 5.374066e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry46 = value + 1.512931e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry48 = value + 8.753486e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry47 = value + -2.094365e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry4 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry51 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry52 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry50 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry3 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry6 = value + 3.147941e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry22 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry23 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry28 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry29 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry27 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry26 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry19 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry15 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry18 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry16 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry20 = value + -1.719012e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry12 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry14 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry33 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry21 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry13 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry17 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry30 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry32 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry31 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00f; }
	void set_ts_presence(FAUSTFLOAT value) { fEntry36 = value + 0.000000e+00f; }
	void zero_all() {
		set_cab_brightness(0.0f);
		set_cab_distance(0.0f);
		set_cab_on_off(0.0f);
		set_gain_slope(0.0f);
		set_gain_stages(0.0f);
		set_input_level(0.0f);
		set_output_level(0.0f);
		set_power_drive(0.0f);
		set_pre_drive(0.0f);
		set_tetrode_grid_level(0.0f);
		set_tetrode_grid_offset1(0.0f);
		set_tetrode_grid_offset2(0.0f);
		set_tetrode_grid_ratio(0.0f);
		set_tetrode_grid_tau(0.0f);
		set_tetrode_grid_taus(0.0f);
		set_tetrode_hp_freq(0.0f);
		set_tetrode_plate_clip(0.0f);
		set_tetrode_plate_clip_corner(0.0f);
		set_tetrode_plate_comp_depth(0.0f);
		set_tetrode_plate_comp_tau(0.0f);
		set_tetrode_plate_cross_corner(0.0f);
		set_tetrode_plate_drift2_depth(0.0f);
		set_tetrode_plate_drift2_level(0.0f);
		set_tetrode_plate_drift_depth(0.0f);
		set_tetrode_plate_drift_level(0.0f);
		set_tetrode_plate_drift_tau(0.0f);
		set_tetrode_plate_sag_depth(0.0f);
		set_tetrode_plate_sag_onset(0.0f);
		set_tetrode_plate_sag_ratio(0.0f);
		set_tetrode_plate_sag_tau(0.0f);
		set_tetrode_plate_sag_toggle(0.0f);
		set_tetrode_plate_scale(0.0f);
		set_triode_grid_clip(0.0f);
		set_triode_grid_corner(0.0f);
		set_triode_grid_level(0.0f);
		set_triode_grid_ratio(0.0f);
		set_triode_grid_smooth(0.0f);
		set_triode_grid_tau(0.0f);
		set_triode_hp_freq(0.0f);
		set_triode_plate_bias(0.0f);
		set_triode_plate_bias_corner(0.0f);
		set_triode_plate_clip(0.0f);
		set_triode_plate_comp_corner(0.0f);
		set_triode_plate_comp_depth(0.0f);
		set_triode_plate_comp_level(0.0f);
		set_triode_plate_comp_offset(0.0f);
		set_triode_plate_comp_ratio(0.0f);
		set_triode_plate_comp_tau(0.0f);
		set_triode_plate_corner(0.0f);
		set_triode_plate_drift_depth(0.0f);
		set_triode_plate_drift_level(0.0f);
		set_triode_plate_drift_tau(0.0f);
		set_triode_plate_scale(0.0f);
		set_ts_high(0.0f);
		set_ts_low(0.0f);
		set_ts_mid(0.0f);
		set_ts_presence(0.0f);
	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f))))));
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = std::exp(((2.30258512f * (float(fEntry2) + 1.0f)) + -2.30258512f));
		float fSlow3 = (1.0f / fSlow2);
		float fSlow4 = (0.5f * ((float(fEntry3) + 1.0f) * std::exp(((2.30258512f * (float(fEntry4) + 1.0f)) + -2.30258512f))));
		float fSlow5 = (fSlow4 + 1.0f);
		float fSlow6 = std::exp(((3.45387769f * (float(fEntry5) + 1.0f)) + -2.30258512f));
		float fSlow7 = std::exp(((4.60517025f * (float(fEntry6) + 1.0f)) + -4.60517025f));
		float fSlow8 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry7) + 1.0f)) + -2.30258512f))));
		float fSlow9 = (1.0f / fSlow8);
		float fSlow10 = (fSlow9 + 1.0f);
		float fSlow11 = (0.0f - (1.0f / (fSlow8 * fSlow10)));
		float fSlow12 = (float(fEntry8) + 1.0f);
		float fSlow13 = (fSlow2 * std::exp((3.45387769f * fSlow12)));
		float fSlow14 = float(fEntry9);
		float fSlow15 = (fSlow14 + 1.0f);
		float fSlow16 = (1.0f - (0.5f * fSlow15));
		float fSlow17 = std::tan((fConst1 * ((25.0f * fSlow15) + (400.0f * fSlow16))));
		float fSlow18 = (1.0f / fSlow17);
		float fSlow19 = (fSlow18 + 1.0f);
		float fSlow20 = (0.0f - (1.0f / (fSlow17 * fSlow19)));
		float fSlow21 = float(fEntry10);
		float fSlow22 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow21) + -5.0f));
		float fSlow23 = ((float(fEntry11) + 1.0f) + 1.0f);
		float fSlow24 = (0.5f * fSlow23);
		float fSlow25 = AmpMono_faustpower3_f(fSlow24);
		float fSlow26 = (0.5f * (fSlow22 / fSlow25));
		float fSlow27 = std::exp(((2.30258512f * (float(fEntry12) + 1.0f)) + -2.30258512f));
		float fSlow28 = std::exp(((3.45387769f * (float(fEntry13) + 1.0f)) + -6.90775537f));
		float fSlow29 = (1.0f / ((fConst0 * fSlow28) + 1.0f));
		float fSlow30 = (100.0f * (1.0f - (float(fEntry14) + 1.0f)));
		float fSlow31 = (0.0f - fSlow30);
		float fSlow32 = (1.0f - (float(fEntry15) + 1.0f));
		float fSlow33 = (1.0f - (float(fEntry16) + 1.0f));
		float fSlow34 = std::exp(((4.60517025f * (float(fEntry17) + 1.0f)) + -4.60517025f));
		float fSlow35 = ((100.0f * (fSlow32 - fSlow33)) + fSlow34);
		float fSlow36 = std::exp(((4.60517025f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow37 = (0.294117659f / fSlow36);
		float fSlow38 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry19) + 1.0f)) + -2.30258512f))));
		float fSlow39 = (1.0f / fSlow38);
		float fSlow40 = (fSlow39 + 1.0f);
		float fSlow41 = (0.0f - (1.0f / (fSlow38 * fSlow40)));
		float fSlow42 = std::exp(((3.45387769f * (float(fEntry20) + 1.0f)) + -2.30258512f));
		float fSlow43 = (fSlow25 / fSlow2);
		float fSlow44 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow21) + -3.0f));
		float fSlow45 = (1.0f - (0.5f * fSlow44));
		float fSlow46 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow21) + -1.0f));
		float fSlow47 = (fSlow46 / fSlow23);
		float fSlow48 = (0.294117659f / fSlow34);
		float fSlow49 = (1.0f / ((fConst0 * (std::exp((1.15129256f * (float(fEntry21) + 1.0f))) * fSlow28)) + 1.0f));
		float fSlow50 = (1.0f - fSlow49);
		float fSlow51 = (float(fEntry23) + 1.0f);
		float fSlow52 = ((float(fEntry22) + 1.0f) - fSlow51);
		float fSlow53 = (0.117647059f / fSlow51);
		float fSlow54 = (0.5f * (fSlow23 / fSlow2));
		float fSlow55 = (float(fEntry24) + 1.0f);
		float fSlow56 = (std::exp((3.80045128f * fSlow55)) * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry25) + 1.0f)))))));
		float fSlow57 = (1.0f / fSlow40);
		float fSlow58 = (1.0f - fSlow39);
		float fSlow59 = (fSlow56 / fSlow38);
		float fSlow60 = std::exp(((3.45387769f * (float(fEntry26) + 1.0f)) + -13.8155107f));
		float fSlow61 = (1.0f / ((fConst0 * (fSlow60 * std::exp(((6.90775537f * (float(fEntry27) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow62 = (1.0f / ((fConst0 * fSlow60) + 1.0f));
		float fSlow63 = (5.0f * (1.0f - (float(fEntry28) + 1.0f)));
		float fSlow64 = (1.0f / ((fConst0 * (std::exp(((5.75646257f * (float(fEntry29) + 1.0f)) + -2.30258512f)) * fSlow60)) + 1.0f));
		float fSlow65 = (fSlow64 + -1.0f);
		float fSlow66 = (1.0f - fSlow61);
		float fSlow67 = (2.5f * fSlow52);
		float fSlow68 = ((100.0f * fSlow32) + fSlow36);
		float fSlow69 = std::exp(((2.30258512f * (float(fEntry30) + 1.0f)) + -2.30258512f));
		float fSlow70 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry31) + 1.0f)) + -6.90775537f)))));
		float fSlow71 = (1.0f - fSlow70);
		float fSlow72 = (100.0f * (1.0f - (float(fEntry32) + 1.0f)));
		float fSlow73 = (0.0f - fSlow72);
		float fSlow74 = (100.0f * fSlow33);
		float fSlow75 = (1.0f - (float(fEntry33) + 1.0f));
		float fSlow76 = (100.0f * (fSlow33 - fSlow75));
		float fSlow77 = (0.294117659f / fSlow42);
		float fSlow78 = (100.0f * fSlow75);
		float fSlow79 = (fSlow38 * fSlow2);
		float fSlow80 = (0.5f * (fSlow23 / fSlow79));
		float fSlow81 = (1.0f - fSlow64);
		float fSlow82 = (1.0f / fSlow79);
		float fSlow83 = (1.0f - (0.5f * fSlow46));
		float fSlow84 = AmpMono_faustpower2_f(fSlow24);
		float fSlow85 = (0.5f * (fSlow44 / fSlow84));
		float fSlow86 = (fSlow84 / fSlow2);
		float fSlow87 = (fSlow84 / fSlow79);
		float fSlow88 = (fSlow49 + -1.0f);
		float fSlow89 = (fSlow25 / fSlow79);
		float fSlow90 = (1.0f - (0.5f * fSlow22));
		float fSlow91 = (5.0f * fSlow55);
		int iSlow92 = (fSlow91 < 9.0f);
		int iSlow93 = (fSlow91 < 8.0f);
		int iSlow94 = (fSlow91 < 7.0f);
		int iSlow95 = (fSlow91 < 6.0f);
		int iSlow96 = (fSlow91 < 5.0f);
		int iSlow97 = (fSlow91 < 4.0f);
		int iSlow98 = (fSlow91 < 3.0f);
		int iSlow99 = (fSlow91 < 2.0f);
		int iSlow100 = (fSlow91 < 1.0f);
		float fSlow101 = std::pow(10.0f, (0.0500000007f * (iSlow92?(iSlow93?(iSlow94?(iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?((fSlow91 < 0.0f)?10.8000002f:(iSlow100?(10.8000002f - (33.0f * fSlow55)):4.19999981f)):(iSlow99?(4.19999981f - (6.53000021f * (fSlow91 + -1.0f))):-2.32999992f)):(iSlow98?(-2.32999992f - (6.5999999f * (fSlow91 + -2.0f))):-8.93000031f)):(iSlow97?(-8.93000031f - (6.57000017f * (fSlow91 + -3.0f))):-15.5f)):(iSlow96?(-15.5f - (4.80000019f * (fSlow91 + -4.0f))):-20.2999992f)):(iSlow95?(-20.2999992f - (2.5f * (0.0f - (5.0f * (1.0f - fSlow55))))):-22.7999992f)):(iSlow94?(-16.7999992f - fSlow91):-23.7999992f)):(iSlow93?(-23.7999992f - (0.600000024f * (fSlow91 + -7.0f))):-24.3999996f)):(iSlow92?(-24.3999996f - (0.699999988f * (fSlow91 + -8.0f))):-25.1000004f)):((fSlow91 < 10.0f)?(-25.1000004f - (0.600000024f * (fSlow91 + -9.0f))):-25.7000008f))));
		float fSlow102 = (1.0f / fSlow19);
		float fSlow103 = (1.0f - fSlow18);
		float fSlow104 = (1.0f / (fSlow17 * fSlow2));
		float fSlow105 = std::pow(10.0f, (0.0500000007f * (fSlow14 * ((4.5f * fSlow15) + (18.0f * fSlow16)))));
		float fSlow106 = float(fEntry34);
		float fSlow107 = (fSlow106 + 1.0f);
		float fSlow108 = ((fSlow106 * ((10.0f * (1.0f - (0.5f * fSlow107))) + (2.5f * fSlow107))) + -14.0f);
		int iSlow109 = (fSlow108 > 0.0f);
		float fSlow110 = ((800.0f * fSlow106) + 1200.0f);
		float fSlow111 = (fConst12 * (fSlow110 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow108)))));
		float fSlow112 = (fConst12 * fSlow110);
		float fSlow113 = (iSlow109?fSlow112:fSlow111);
		float fSlow114 = ((fConst10 * (fConst10 - fSlow113)) + 1.0f);
		float fSlow115 = ((fConst10 * (fConst10 + fSlow113)) + 1.0f);
		float fSlow116 = (iSlow109?fSlow111:fSlow112);
		float fSlow117 = ((fConst10 * (fConst10 - fSlow116)) + 1.0f);
		float fSlow118 = ((fConst10 * (fConst10 + fSlow116)) + 1.0f);
		float fSlow119 = (fSlow106 * ((fSlow106 > 0.0f)?5.0f:0.0f));
		int iSlow120 = (fSlow119 > 0.0f);
		float fSlow121 = (fConst14 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow119))));
		float fSlow122 = (iSlow120?fConst14:fSlow121);
		float fSlow123 = ((fConst10 * (fConst10 - fSlow122)) + 1.0f);
		float fSlow124 = ((fConst10 * (fConst10 + fSlow122)) + 1.0f);
		float fSlow125 = (iSlow120?fSlow121:fConst14);
		float fSlow126 = ((fConst10 * (fConst10 + fSlow125)) + 1.0f);
		float fSlow127 = ((fConst10 * (fConst10 - fSlow125)) + 1.0f);
		float fSlow128 = float(fEntry35);
		int iSlow129 = (fSlow128 < 0.0f);
		float fSlow130 = std::tan((fConst1 * ((iSlow129?(1500.0f * fSlow128):0.0f) + 2000.0f)));
		float fSlow131 = (1.0f / fSlow130);
		float fSlow132 = (1.0f - fSlow131);
		float fSlow133 = (fSlow131 + 1.0f);
		float fSlow134 = (0.0f - (1.0f / (fSlow133 * fSlow130)));
		float fSlow135 = (fSlow130 * fSlow124);
		float fSlow136 = std::pow(10.0f, ((0.0500000007f * fSlow128) * (iSlow129?18.0f:9.0f)));
		float fSlow137 = (10.0f * float(fEntry36));
		int iSlow138 = (fSlow137 > 0.0f);
		float fSlow139 = (fConst18 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow137))));
		float fSlow140 = (iSlow138?fConst18:fSlow139);
		float fSlow141 = ((fConst17 * (fConst17 - fSlow140)) + 1.0f);
		float fSlow142 = ((fConst17 * (fConst17 + fSlow140)) + 1.0f);
		float fSlow143 = (iSlow138?fSlow139:fConst18);
		float fSlow144 = ((fConst17 * (fConst17 + fSlow143)) + 1.0f);
		float fSlow145 = ((fConst17 * (fConst17 - fSlow143)) + 1.0f);
		float fSlow146 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow147 = (1.0f / fSlow10);
		float fSlow148 = (1.0f - fSlow9);
		float fSlow149 = std::exp((0.0f - (fConst6 / std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -9.2103405f)))));
		float fSlow150 = (1.0f - fSlow149);
		float fSlow151 = (250.0f * (float(fEntry39) + 1.0f));
		float fSlow152 = std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -9.2103405f));
		float fSlow153 = (1.0f / ((fConst0 * fSlow152) + 1.0f));
		float fSlow154 = (100.0f * (1.0f - (float(fEntry41) + 1.0f)));
		float fSlow155 = (1.0f - (1.0f / ((fConst0 * (fSlow152 * std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow156 = ((20.0f * (float(fEntry43) + 1.0f)) + 10.0f);
		float fSlow157 = std::exp(((2.30258512f * (float(fEntry44) + 1.0f)) + -2.30258512f));
		float fSlow158 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry45) + 1.0f)) + -6.90775537f)))));
		float fSlow159 = (1.0f - fSlow158);
		float fSlow160 = (1.0f / fSlow156);
		float fSlow161 = std::exp(((2.30258512f * (float(fEntry46) + 1.0f)) + -2.30258512f));
		float fSlow162 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry47) + 1.0f)) + -6.90775537f)))));
		float fSlow163 = (1.0f - fSlow162);
		float fSlow164 = (100.0f * (1.0f - (float(fEntry48) + 1.0f)));
		float fSlow165 = (0.0f - fSlow164);
		float fSlow166 = (0.294117659f / fSlow6);
		float fSlow167 = std::exp(((3.45387769f * (float(fEntry49) + 1.0f)) + -2.30258512f));
		float fSlow168 = (0.294117659f / fSlow167);
		float fSlow169 = std::exp(((1.95601153f * (float(fEntry50) + 1.0f)) + -4.60517025f));
		float fSlow170 = (1.0f / ((fConst0 * fSlow169) + 1.0f));
		float fSlow171 = (fSlow7 / fSlow156);
		float fSlow172 = std::exp(((2.30258512f * (float(fEntry51) + 1.0f)) + -2.30258512f));
		float fSlow173 = (1.0f - (1.0f / ((fConst0 * (fSlow169 * std::exp((1.15129256f * (float(fEntry52) + 1.0f))))) + 1.0f)));
		float fSlow174 = std::exp(((2.30258512f * (float(fEntry53) + 1.0f)) + -2.30258512f));
		float fSlow175 = (50.0f * (1.0f - (float(fEntry54) + 1.0f)));
		float fSlow176 = (0.0f - fSlow175);
		float fSlow177 = (5.0f * fSlow12);
		int iSlow178 = (fSlow177 < 8.0f);
		int iSlow179 = (fSlow177 < 7.0f);
		int iSlow180 = (fSlow177 < 6.0f);
		int iSlow181 = (fSlow177 < 5.0f);
		int iSlow182 = (fSlow177 < 4.0f);
		int iSlow183 = (fSlow177 < 3.0f);
		int iSlow184 = (fSlow177 < 2.0f);
		int iSlow185 = (fSlow177 < 1.0f);
		float fSlow186 = std::pow(10.0f, (0.0500000007f * ((fSlow177 < 9.0f)?(iSlow178?(iSlow179?(iSlow180?(iSlow181?(iSlow182?(iSlow183?(iSlow184?(iSlow185?((fSlow177 < 0.0f)?-0.518999994f:(iSlow185?(-0.518999994f - (27.5550003f * fSlow12)):-6.03000021f)):(iSlow184?(-6.03000021f - (5.46999979f * (fSlow177 + -1.0f))):-11.5f)):(iSlow183?(-11.5f - (5.0999999f * (fSlow177 + -2.0f))):-16.6000004f)):(iSlow182?(-16.6000004f - (3.0999999f * (fSlow177 + -3.0f))):-19.7000008f)):(iSlow181?(-19.7000008f - (1.10000002f * (fSlow177 + -4.0f))):-20.7999992f)):(iSlow180?(-20.7999992f - (0.200000003f * (0.0f - (5.0f * (1.0f - fSlow12))))):-21.0f)):(iSlow179?(-21.0f - (0.100000001f * (fSlow177 + -6.0f))):-21.1000004f)):(iSlow178?((0.100000001f * (fSlow177 + -7.0f)) + -21.1000004f):-21.0f)):-21.0f):-21.0f)));
		float fSlow187 = float(fEntry55);
		float fSlow188 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow187)));
		float fSlow189 = float(fEntry56);
		float fSlow190 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow189))));
		float fSlow191 = (15.0f * fSlow189);
		int iSlow192 = (fSlow191 > 0.0f);
		float fSlow193 = (fConst175 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow191))));
		float fSlow194 = (iSlow192?fConst175:fSlow193);
		float fSlow195 = ((fConst174 * (fConst174 - fSlow194)) + 1.0f);
		float fSlow196 = ((fConst174 * (fConst174 + fSlow194)) + 1.0f);
		float fSlow197 = (iSlow192?fSlow193:fConst175);
		float fSlow198 = ((fConst174 * (fConst174 + fSlow197)) + 1.0f);
		float fSlow199 = ((fConst174 * (fConst174 - fSlow197)) + 1.0f);
		float fSlow200 = (0.0f - (10.0f * fSlow187));
		int iSlow201 = (fSlow200 > 0.0f);
		float fSlow202 = (fConst177 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow200))));
		float fSlow203 = (iSlow201?fConst177:fSlow202);
		float fSlow204 = ((fConst176 * (fConst176 - fSlow203)) + 1.0f);
		float fSlow205 = ((fConst176 * (fConst176 + fSlow203)) + 1.0f);
		float fSlow206 = (iSlow201?fSlow202:fConst177);
		float fSlow207 = ((fConst176 * (fConst176 + fSlow206)) + 1.0f);
		float fSlow208 = ((fConst176 * (fConst176 - fSlow206)) + 1.0f);
		float fSlow209 = (0.0f - (17.0f * fSlow187));
		int iSlow210 = (fSlow209 > 0.0f);
		float fSlow211 = (fConst181 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow209))));
		float fSlow212 = (iSlow210?fConst181:fSlow211);
		float fSlow213 = ((fConst180 * (fConst180 - fSlow212)) + 1.0f);
		float fSlow214 = ((fConst180 * (fConst180 + fSlow212)) + 1.0f);
		float fSlow215 = (iSlow210?fSlow211:fConst181);
		float fSlow216 = ((fConst180 * (fConst180 + fSlow215)) + 1.0f);
		float fSlow217 = ((fConst180 * (fConst180 - fSlow215)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow56 * fTemp0);
			fRec13[0] = ((fSlow41 * fVec0[1]) - (fSlow57 * ((fSlow58 * fRec13[1]) - (fSlow59 * fTemp0))));
			fRec15[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec13[0])) - fRec15[1]))) - (fSlow65 * fRec15[1]));
			fRec14[0] = ((fSlow61 * fRec15[0]) + (fSlow66 * fRec14[1]));
			float fTemp1 = ((fRec13[0] - fRec14[0]) - fSlow67);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * (fSlow52 + (fSlow51 * (fTemp3 * (std::fabs(fTemp3) + -2.0f))))))) - fSlow68);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (fTemp5 * (std::fabs(fTemp5) + -2.0f));
			float fTemp7 = (0.0f - (fSlow35 + (std::max<float>(0.0f, fTemp4) + (fSlow36 * ((fTemp6 * (std::fabs(fTemp6) + -2.0f)) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = ((std::fabs(fTemp8) + -2.0f) * fTemp8);
			float fTemp10 = ((fSlow34 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp7));
			fRec16[0] = ((fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp10 - fSlow74)))) + (fSlow70 * fRec16[1]));
			float fTemp11 = (fSlow69 * fRec16[0]);
			fRec17[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp10 - fTemp11) - fSlow74)) - fRec17[1])))) + (fSlow50 * fRec17[1]));
			float fTemp12 = (fSlow27 * fRec17[0]);
			float fTemp13 = (fSlow42 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow76));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((std::min<float>(0.0f, fTemp13) + fTemp12) - (fSlow42 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow78);
			fVec1[0] = (fSlow54 * fTemp16);
			fRec12[0] = ((fSlow41 * fVec1[1]) + (fSlow57 * ((fSlow80 * fTemp16) - (fSlow58 * fRec12[1]))));
			fRec19[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec12[0])) - fRec19[1]))) + (fSlow81 * fRec19[1]));
			fRec18[0] = ((fSlow66 * fRec18[1]) + (fSlow61 * fRec19[0]));
			float fTemp17 = ((fRec12[0] - fRec18[0]) - fSlow67);
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (fTemp18 * (std::fabs(fTemp18) + -2.0f));
			float fTemp20 = ((fSlow2 * ((2.5f * (fSlow52 + (fSlow51 * (fTemp19 * (std::fabs(fTemp19) + -2.0f))))) + std::min<float>(0.0f, fTemp17))) - fSlow68);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow35 + (std::max<float>(0.0f, fTemp20) + (fSlow36 * (((fTemp22 * (std::fabs((fTemp22 * fTemp21)) + -2.0f)) * fTemp21) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = ((std::fabs(fTemp24) + -2.0f) * fTemp24);
			float fTemp26 = ((fSlow34 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp23));
			fRec20[0] = ((fSlow70 * fRec20[1]) + (fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp26 - fSlow74)))));
			float fTemp27 = (fSlow69 * fRec20[0]);
			fRec11[0] = ((fSlow50 * fRec11[1]) + (fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp26 - fTemp27) - fSlow74)) - fRec11[1])))));
			float fTemp28 = (fSlow27 * fRec11[0]);
			float fTemp29 = (fSlow42 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow76));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (fTemp30 * (std::fabs(fTemp30) + -2.0f));
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow42 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow78);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec10[0] = ((fSlow41 * fVec2[1]) - (fSlow57 * ((fSlow58 * fRec10[1]) - (fSlow82 * fTemp32))));
			fRec22[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec10[0])) - fRec22[1]))) + (fSlow81 * fRec22[1]));
			fRec21[0] = ((fSlow66 * fRec21[1]) + (fSlow61 * fRec22[0]));
			float fTemp33 = ((fRec10[0] - fRec21[0]) - fSlow67);
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) + (2.5f * (fSlow52 + (fSlow51 * (((std::fabs((fTemp34 * fTemp35)) + -2.0f) * fTemp34) * fTemp35)))))) - fSlow68);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (std::fabs(fTemp37) + -2.0f);
			float fTemp39 = (0.0f - (fSlow35 + (std::max<float>(0.0f, fTemp36) + (fSlow36 * (((fTemp38 * (std::fabs((fTemp38 * fTemp37)) + -2.0f)) * fTemp37) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (fTemp40 * (std::fabs(fTemp40) + -2.0f));
			float fTemp42 = ((fSlow34 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp39));
			fRec23[0] = ((fSlow70 * fRec23[1]) + (fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp42 - fSlow74)))));
			float fTemp43 = (fSlow69 * fRec23[0]);
			fRec24[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp42 - fTemp43) - fSlow74)) - fRec24[1])))) + (fSlow50 * fRec24[1]));
			float fTemp44 = (fSlow27 * fRec24[0]);
			float fTemp45 = (fSlow42 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow76));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = ((fSlow47 * (((std::min<float>(0.0f, fTemp45) + fTemp44) - (fSlow42 * (1.0f - ((fTemp47 * (std::fabs((fTemp47 * fTemp46)) + -2.0f)) * fTemp46)))) - fSlow78)) + (fSlow83 * fTemp16));
			fVec3[0] = (fSlow86 * fTemp48);
			fRec28[0] = ((fSlow41 * fVec3[1]) - (fSlow57 * ((fSlow58 * fRec28[1]) - (fSlow87 * fTemp48))));
			fRec30[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec28[0])) - fRec30[1]))) - (fSlow65 * fRec30[1]));
			fRec29[0] = ((fSlow61 * fRec30[0]) + (fSlow66 * fRec29[1]));
			float fTemp49 = ((fRec28[0] - fRec29[0]) - fSlow67);
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (fTemp50 * (std::fabs(fTemp50) + -2.0f));
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) + (2.5f * (fSlow52 + (fSlow51 * (fTemp51 * (std::fabs(fTemp51) + -2.0f))))))) - fSlow68);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (std::fabs(fTemp53) + -2.0f);
			float fTemp55 = (0.0f - (fSlow35 + ((fSlow36 * ((((std::fabs((fTemp54 * fTemp53)) + -2.0f) * fTemp54) * fTemp53) + 1.0f)) + std::max<float>(0.0f, fTemp52))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (fTemp56 * (std::fabs(fTemp56) + -2.0f));
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow34 * ((fTemp57 * (std::fabs(fTemp57) + -2.0f)) + 1.0f)));
			fRec31[0] = ((fSlow70 * fRec31[1]) + (fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp58 - fSlow74)))));
			float fTemp59 = (fSlow69 * fRec31[0]);
			fRec27[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp58 - fTemp59) - fSlow74)) - fRec27[1])))) - (fSlow88 * fRec27[1]));
			float fTemp60 = (fSlow27 * fRec27[0]);
			float fTemp61 = (fSlow42 + ((fTemp58 - (fTemp60 + fTemp59)) - fSlow76));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (fTemp62 * (std::fabs(fTemp62) + -2.0f));
			float fTemp64 = (((fTemp60 + std::min<float>(0.0f, fTemp61)) - (fSlow42 * (1.0f - (fTemp63 * (std::fabs(fTemp63) + -2.0f))))) - fSlow78);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec26[0] = ((fSlow41 * fVec4[1]) - (fSlow57 * ((fSlow58 * fRec26[1]) - (fSlow82 * fTemp64))));
			fRec33[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec26[0])) - fRec33[1]))) - (fSlow65 * fRec33[1]));
			fRec32[0] = ((fSlow61 * fRec33[0]) + (fSlow66 * fRec32[1]));
			float fTemp65 = ((fRec26[0] - fRec32[0]) - fSlow67);
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) + (2.5f * (fSlow52 + (fSlow51 * ((fTemp66 * (std::fabs((fTemp66 * fTemp67)) + -2.0f)) * fTemp67)))))) - fSlow68);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow35 + (std::max<float>(0.0f, fTemp68) + (fSlow36 * (((fTemp70 * (std::fabs((fTemp70 * fTemp69)) + -2.0f)) * fTemp69) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (std::fabs(fTemp72) + -2.0f);
			float fTemp74 = (std::max<float>(0.0f, fTemp71) + (fSlow34 * (((fTemp72 * (std::fabs((fTemp72 * fTemp73)) + -2.0f)) * fTemp73) + 1.0f)));
			fRec34[0] = ((fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp74 - fSlow74)))) + (fSlow70 * fRec34[1]));
			float fTemp75 = (fSlow69 * fRec34[0]);
			fRec25[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp74 - fTemp75) - fSlow74)) - fRec25[1])))) - (fSlow88 * fRec25[1]));
			float fTemp76 = (fSlow27 * fRec25[0]);
			float fTemp77 = (fSlow42 + ((fTemp74 - (fTemp75 + fTemp76)) - fSlow76));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (fTemp78 * (std::fabs(fTemp78) + -2.0f));
			float fTemp80 = ((fSlow45 * fTemp48) + (fSlow85 * (((fTemp76 + std::min<float>(0.0f, fTemp77)) - (fSlow42 * (1.0f - (fTemp79 * (std::fabs(fTemp79) + -2.0f))))) - fSlow78)));
			fVec5[0] = (fSlow43 * fTemp80);
			fRec9[0] = ((fSlow41 * fVec5[1]) - (fSlow57 * ((fSlow58 * fRec9[1]) - (fSlow89 * fTemp80))));
			fRec36[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec9[0])) - fRec36[1]))) + (fSlow81 * fRec36[1]));
			fRec35[0] = ((fSlow61 * fRec36[0]) + (fSlow66 * fRec35[1]));
			float fTemp81 = ((fRec9[0] - fRec35[0]) - fSlow67);
			float fTemp82 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp81))));
			float fTemp83 = (std::fabs(fTemp82) + -2.0f);
			float fTemp84 = ((fSlow2 * (std::min<float>(0.0f, fTemp81) + (2.5f * (fSlow52 + (fSlow51 * ((fTemp83 * (std::fabs((fTemp83 * fTemp82)) + -2.0f)) * fTemp82)))))) - fSlow68);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp84))));
			float fTemp86 = (std::fabs(fTemp85) + -2.0f);
			float fTemp87 = (0.0f - (fSlow35 + ((fSlow36 * ((((std::fabs((fTemp86 * fTemp85)) + -2.0f) * fTemp86) * fTemp85) + 1.0f)) + std::max<float>(0.0f, fTemp84))));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = (std::fabs(fTemp88) + -2.0f);
			float fTemp90 = (std::max<float>(0.0f, fTemp87) + (fSlow34 * ((((std::fabs((fTemp89 * fTemp88)) + -2.0f) * fTemp89) * fTemp88) + 1.0f)));
			fRec37[0] = ((fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp90 - fSlow74)))) + (fSlow70 * fRec37[1]));
			float fTemp91 = (fSlow69 * fRec37[0]);
			fRec38[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp90 - fTemp91) - fSlow74)) - fRec38[1])))) - (fSlow88 * fRec38[1]));
			float fTemp92 = (fSlow27 * fRec38[0]);
			float fTemp93 = (fSlow42 + ((fTemp90 - (fTemp91 + fTemp92)) - fSlow76));
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = (fTemp94 * (std::fabs(fTemp94) + -2.0f));
			float fTemp96 = (((std::min<float>(0.0f, fTemp93) + fTemp92) - (fSlow42 * (1.0f - (fTemp95 * (std::fabs(fTemp95) + -2.0f))))) - fSlow78);
			fVec6[0] = (fSlow3 * fTemp96);
			fRec8[0] = ((fSlow41 * fVec6[1]) - (fSlow57 * ((fSlow58 * fRec8[1]) - (fSlow82 * fTemp96))));
			fRec40[0] = ((fSlow81 * fRec40[1]) + (fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow63 + fRec8[0])) - fRec40[1]))));
			fRec39[0] = ((fSlow66 * fRec39[1]) + (fSlow61 * fRec40[0]));
			float fTemp97 = ((fRec8[0] - fRec39[0]) - fSlow67);
			float fTemp98 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow53 * std::max<float>(0.0f, fTemp97))));
			float fTemp99 = (std::fabs(fTemp98) + -2.0f);
			float fTemp100 = ((fSlow2 * (std::min<float>(0.0f, fTemp97) + (2.5f * (fSlow52 + (fSlow51 * (((std::fabs((fTemp99 * fTemp98)) + -2.0f) * fTemp99) * fTemp98)))))) - fSlow68);
			float fTemp101 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow37 * std::min<float>(0.0f, fTemp100))));
			float fTemp102 = (std::fabs(fTemp101) + -2.0f);
			float fTemp103 = (0.0f - (fSlow35 + ((fSlow36 * ((((std::fabs((fTemp101 * fTemp102)) + -2.0f) * fTemp101) * fTemp102) + 1.0f)) + std::max<float>(0.0f, fTemp100))));
			float fTemp104 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp103))));
			float fTemp105 = (std::fabs(fTemp104) + -2.0f);
			float fTemp106 = (std::max<float>(0.0f, fTemp103) + (fSlow34 * (((fTemp104 * (std::fabs((fTemp104 * fTemp105)) + -2.0f)) * fTemp105) + 1.0f)));
			fRec41[0] = ((fSlow71 * (fSlow72 + std::max<float>(fSlow73, (fTemp106 - fSlow74)))) + (fSlow70 * fRec41[1]));
			float fTemp107 = (fSlow69 * fRec41[0]);
			fRec7[0] = ((fSlow29 * std::max<float>(0.0f, (fSlow30 + (std::max<float>(fSlow31, ((fTemp106 - fTemp107) - fSlow74)) - fRec7[1])))) - (fSlow88 * fRec7[1]));
			float fTemp108 = (fSlow27 * fRec7[0]);
			float fTemp109 = (fSlow42 + ((fTemp106 - (fTemp108 + fTemp107)) - fSlow76));
			float fTemp110 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp109))));
			float fTemp111 = ((std::fabs(fTemp110) + -2.0f) * fTemp110);
			float fTemp112 = (((fSlow26 * (((fTemp108 + std::min<float>(0.0f, fTemp109)) - (fSlow42 * (1.0f - (fTemp111 * (std::fabs(fTemp111) + -2.0f))))) - fSlow78)) + (fSlow90 * fTemp80)) * fSlow101);
			float fTemp113 = (fSlow3 * fTemp112);
			fVec7[0] = fTemp113;
			fRec6[0] = ((fSlow20 * fVec7[1]) - (fSlow102 * ((fSlow103 * fRec6[1]) - (fSlow104 * fTemp112))));
			fRec42[0] = (0.0f - (fSlow102 * ((fSlow103 * fRec42[1]) - (fTemp113 + fVec7[1]))));
			float fTemp114 = (fRec6[0] + (fSlow105 * fRec42[0]));
			fVec8[0] = fTemp114;
			fRec5[0] = ((fConst5 * fVec8[1]) - (fConst7 * ((fConst8 * fRec5[1]) - (fConst3 * fTemp114))));
			float fTemp115 = (fConst13 * fRec4[1]);
			fRec4[0] = (fRec5[0] - (((fRec4[2] * fSlow114) + fTemp115) / fSlow115));
			float fTemp116 = (fConst13 * fRec3[1]);
			fRec3[0] = ((((fRec4[2] * fSlow117) + (fTemp115 + (fRec4[0] * fSlow118))) / fSlow115) - (((fRec3[2] * fSlow123) + fTemp116) / fSlow124));
			float fTemp117 = (((fRec3[0] * fSlow126) + fTemp116) + (fSlow127 * fRec3[2]));
			float fTemp118 = (fTemp117 / fSlow124);
			fVec9[0] = fTemp118;
			fRec2[0] = (((fVec9[1] + fTemp118) - (fSlow132 * fRec2[1])) / fSlow133);
			fRec43[0] = ((fVec9[1] * fSlow134) - (((fRec43[1] * fSlow132) - (fTemp117 / fSlow135)) / fSlow133));
			float fTemp119 = (fConst16 * fRec1[1]);
			fRec1[0] = ((fRec2[0] + (fRec43[0] * fSlow136)) - ((fTemp119 + (fSlow141 * fRec1[2])) / fSlow142));
			float fTemp120 = ((fSlow13 * ((((fRec1[0] * fSlow144) + fTemp119) + (fRec1[2] * fSlow145)) / fSlow142)) - fSlow146);
			fVec10[0] = fTemp120;
			fRec0[0] = ((fSlow11 * fVec10[1]) - (fSlow147 * ((fSlow148 * fRec0[1]) - (fSlow9 * fTemp120))));
			fRec44[0] = ((fSlow150 * (fRec0[0] - fSlow151)) + (fSlow149 * fRec44[1]));
			fRec45[0] = ((fSlow153 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow154 + ((fRec0[0] - fRec44[0]) - fSlow151))) - fRec45[1]))) + (fSlow155 * fRec45[1]));
			float fTemp121 = ((fRec0[0] - (fRec44[0] + fRec45[0])) - fSlow151);
			float fTemp122 = (fSlow7 * fTemp121);
			fRec47[0] = ((fSlow163 * (fSlow164 + std::max<float>(fSlow165, fTemp122))) + (fSlow162 * fRec47[1]));
			float fTemp123 = (fSlow161 * fRec47[0]);
			fRec46[0] = ((fSlow158 * fRec46[1]) + (fSlow159 * std::min<float>(1.0f, std::fabs((fSlow160 * (fTemp122 - fTemp123))))));
			float fTemp124 = (fSlow156 / ((fSlow157 * fRec46[0]) + 1.0f));
			float fTemp125 = (fSlow6 + (fTemp122 - (fTemp124 + fTemp123)));
			float fTemp126 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow166 * std::max<float>(0.0f, fTemp125))));
			float fTemp127 = (std::fabs(fTemp126) + -2.0f);
			float fTemp128 = (((std::min<float>(0.0f, fTemp125) + fTemp124) - (fSlow6 * (1.0f - ((fTemp127 * (std::fabs((fTemp127 * fTemp126)) + -2.0f)) * fTemp126)))) - fSlow167);
			fRec48[0] = ((fSlow163 * (fSlow164 + std::max<float>(fSlow165, (0.0f - fTemp122)))) + (fSlow162 * fRec48[1]));
			float fTemp129 = (fTemp122 + (fSlow161 * fRec48[0]));
			fRec49[0] = ((fSlow158 * fRec49[1]) + (fSlow159 * std::min<float>(1.0f, std::fabs((fSlow160 * (0.0f - fTemp129))))));
			float fTemp130 = (fSlow156 / ((fSlow157 * fRec49[0]) + 1.0f));
			float fTemp131 = (fSlow6 - (fTemp129 + fTemp130));
			float fTemp132 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow166 * std::max<float>(0.0f, fTemp131))));
			float fTemp133 = ((std::fabs(fTemp132) + -2.0f) * fTemp132);
			float fTemp134 = ((((fSlow6 * ((fTemp133 * (std::fabs(fTemp133) + -2.0f)) + -1.0f)) + fTemp130) + std::min<float>(0.0f, fTemp131)) - fSlow167);
			float fTemp135 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow168 * std::min<float>(0.0f, fTemp134))));
			float fTemp136 = (std::fabs(fTemp135) + -2.0f);
			float fTemp137 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow168 * std::min<float>(0.0f, fTemp128))));
			float fTemp138 = (std::fabs(fTemp137) + -2.0f);
			float fTemp139 = std::fabs((fSlow171 * fTemp121));
			fRec50[0] = ((fSlow170 * std::max<float>(0.0f, ((std::max<float>(1.0f, fTemp139) + (fSlow172 * std::min<float>(1.0f, fTemp139))) + (-1.0f - fRec50[1])))) + (fSlow173 * fRec50[1]));
			float fTemp140 = (fSlow5 * ((std::max<float>(0.0f, fTemp128) - (std::max<float>(0.0f, fTemp134) + (fSlow167 * (((((std::fabs((fTemp136 * fTemp135)) + -2.0f) * fTemp136) * fTemp135) + 1.0f) - ((((std::fabs((fTemp137 * fTemp138)) + -2.0f) * fTemp137) * fTemp138) + 1.0f))))) / ((fSlow4 * fRec50[0]) + 1.0f)));
			fRec51[0] = ((fSlow162 * fRec51[1]) + (fSlow163 * (fSlow175 + std::max<float>(fSlow176, std::fabs(fTemp140)))));
			float fTemp141 = (fSlow3 * ((fTemp140 + (fSlow174 * fRec51[0])) * fSlow186));
			fRec74[0] = (fTemp141 - (fConst115 * ((fConst116 * fRec74[1]) + (fConst117 * fRec74[2]))));
			fRec73[0] = ((fConst115 * ((fConst114 * fRec74[2]) + ((fConst118 * fRec74[1]) + (fConst114 * fRec74[0])))) - (fConst112 * ((fConst116 * fRec73[1]) + (fConst119 * fRec73[2]))));
			float fTemp142 = ((fConst114 * fRec73[2]) + ((fConst118 * fRec73[1]) + (fConst114 * fRec73[0])));
			fVec11[0] = fTemp142;
			fRec72[0] = (0.0f - (fConst108 * ((fConst109 * fRec72[1]) - (fConst112 * (fVec11[1] + fTemp142)))));
			fRec71[0] = (fRec72[0] - (fConst104 * ((fConst120 * fRec71[1]) + (fConst121 * fRec71[2]))));
			float fTemp143 = ((fRec71[0] + (2.0f * fRec71[1])) + fRec71[2]);
			fVec12[0] = fTemp143;
			fRec70[0] = ((fConst104 * ((fConst107 * fVec12[1]) + (fConst106 * fTemp143))) - (fConst123 * fRec70[1]));
			fRec69[0] = (fRec70[0] - (fConst101 * ((fConst124 * fRec69[2]) + (fConst126 * fRec69[1]))));
			fRec68[0] = ((fConst101 * (((fConst99 * fRec69[1]) + (fConst125 * fRec69[0])) + (fConst125 * fRec69[2]))) - (fConst100 * ((fConst126 * fRec68[1]) + (fConst127 * fRec68[2]))));
			fRec67[0] = ((fConst100 * (((fConst99 * fRec68[1]) + (fConst125 * fRec68[0])) + (fConst125 * fRec68[2]))) - (fConst97 * ((fConst126 * fRec67[1]) + (fConst128 * fRec67[2]))));
			fRec78[0] = (0.0f - (fConst129 * ((fConst122 * fRec78[1]) - (fConst104 * (fTemp143 + fVec12[1])))));
			fRec77[0] = (fRec78[0] - (fConst101 * ((fConst126 * fRec77[1]) + (fConst124 * fRec77[2]))));
			fRec76[0] = ((fConst101 * (fRec77[2] + (fRec77[0] + (2.0f * fRec77[1])))) - (fConst100 * ((fConst126 * fRec76[1]) + (fConst127 * fRec76[2]))));
			fRec75[0] = ((fConst100 * (fRec76[2] + (fRec76[0] + (2.0f * fRec76[1])))) - (fConst97 * ((fConst126 * fRec75[1]) + (fConst128 * fRec75[2]))));
			float fTemp144 = (fConst94 * fRec66[1]);
			fRec66[0] = ((fConst97 * ((0.0316227749f * (((fConst99 * fRec67[1]) + (fConst125 * fRec67[0])) + (fConst125 * fRec67[2]))) + ((fRec75[0] + (2.0f * fRec75[1])) + fRec75[2]))) - (fConst93 * (fTemp144 + (fConst130 * fRec66[2]))));
			float fTemp145 = (fConst135 * fRec65[1]);
			fRec65[0] = ((fConst93 * ((fTemp144 + (fConst132 * fRec66[0])) + (fConst133 * fRec66[2]))) - (fConst86 * ((fConst134 * fRec65[2]) + fTemp145)));
			float fTemp146 = (fConst81 * fRec64[1]);
			fRec64[0] = ((fConst86 * (((fConst88 * fRec65[0]) + fTemp145) + (fConst136 * fRec65[2]))) - (fConst80 * (fTemp146 + (fConst137 * fRec64[2]))));
			float fTemp147 = (fConst75 * fRec63[1]);
			fRec63[0] = ((fConst80 * ((fTemp146 + (fConst139 * fRec64[0])) + (fConst140 * fRec64[2]))) - (fConst74 * (fTemp147 + (fConst141 * fRec63[2]))));
			float fTemp148 = (fConst146 * fRec62[1]);
			fRec62[0] = ((fConst74 * ((fTemp147 + (fConst143 * fRec63[0])) + (fConst144 * fRec63[2]))) - (fConst66 * ((fConst145 * fRec62[2]) + fTemp148)));
			float fTemp149 = (fConst149 * fRec61[1]);
			fRec61[0] = ((fConst66 * ((fConst68 * fRec62[2]) + ((fConst147 * fRec62[0]) + fTemp148))) - (fConst59 * ((fConst148 * fRec61[2]) + fTemp149)));
			float fTemp150 = (fConst54 * fRec60[1]);
			fRec60[0] = ((fConst59 * (((fConst61 * fRec61[0]) + fTemp149) + (fConst150 * fRec61[2]))) - (fConst53 * ((fConst151 * fRec60[2]) + fTemp150)));
			float fTemp151 = (fConst48 * fRec59[1]);
			fRec59[0] = ((fConst53 * ((fTemp150 + (fConst153 * fRec60[0])) + (fConst154 * fRec60[2]))) - (fConst47 * ((fConst155 * fRec59[2]) + fTemp151)));
			float fTemp152 = (fConst42 * fRec58[1]);
			fRec58[0] = ((fConst47 * ((fTemp151 + (fConst157 * fRec59[0])) + (fConst158 * fRec59[2]))) - (fConst41 * (fTemp152 + (fConst159 * fRec58[2]))));
			float fTemp153 = (fConst35 * fRec57[1]);
			fRec57[0] = ((fConst41 * ((fTemp152 + (fConst161 * fRec58[0])) + (fConst162 * fRec58[2]))) - (fConst32 * ((fConst163 * fRec57[2]) + fTemp153)));
			float fTemp154 = ((fTemp153 + (fConst165 * fRec57[0])) + (fConst166 * fRec57[2]));
			fVec13[0] = fTemp154;
			fRec56[0] = ((fConst32 * ((fConst34 * fTemp154) + (fConst167 * fVec13[1]))) - (fConst169 * fRec56[1]));
			fRec55[0] = (fRec56[0] - (fConst25 * ((fConst170 * fRec55[1]) + (fConst171 * fRec55[2]))));
			fRec80[0] = (0.0f - (fConst173 * ((fConst168 * fRec80[1]) - (fConst32 * (fVec13[1] + fTemp154)))));
			fRec79[0] = (fRec80[0] - (fConst25 * ((fConst170 * fRec79[1]) + (fConst171 * fRec79[2]))));
			float fTemp155 = (fConst22 * fRec54[1]);
			fRec54[0] = ((fConst25 * (((fConst27 * fRec55[2]) + ((fConst172 * fRec55[1]) + (fConst27 * fRec55[0]))) + (fSlow190 * (fRec79[2] + (fRec79[0] + (2.0f * fRec79[1])))))) - ((fTemp155 + (fSlow195 * fRec54[2])) / fSlow196));
			float fTemp156 = (fConst20 * fRec53[1]);
			fRec53[0] = ((((fTemp155 + (fRec54[0] * fSlow198)) + (fRec54[2] * fSlow199)) / fSlow196) - ((fTemp156 + (fSlow204 * fRec53[2])) / fSlow205));
			float fTemp157 = (fConst179 * fRec52[1]);
			fRec52[0] = ((((fTemp156 + (fRec53[0] * fSlow207)) + (fRec53[2] * fSlow208)) / fSlow205) - ((fTemp157 + (fRec52[2] * fSlow213)) / fSlow214));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow188 * ((((fRec52[0] * fSlow216) + fTemp157) + (fRec52[2] * fSlow217)) / fSlow214)):fTemp141)));
			fVec0[1] = fVec0[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fVec1[1] = fVec1[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec11[1] = fRec11[0];
			fVec2[1] = fVec2[0];
			fRec10[1] = fRec10[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec24[1] = fRec24[0];
			fVec3[1] = fVec3[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec29[1] = fRec29[0];
			fRec31[1] = fRec31[0];
			fRec27[1] = fRec27[0];
			fVec4[1] = fVec4[0];
			fRec26[1] = fRec26[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fRec25[1] = fRec25[0];
			fVec5[1] = fVec5[0];
			fRec9[1] = fRec9[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fVec6[1] = fVec6[0];
			fRec8[1] = fRec8[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec7[1] = fRec7[0];
			fVec7[1] = fVec7[0];
			fRec6[1] = fRec6[0];
			fRec42[1] = fRec42[0];
			fVec8[1] = fVec8[0];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec9[1] = fVec9[0];
			fRec2[1] = fRec2[0];
			fRec43[1] = fRec43[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec48[1] = fRec48[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec51[1] = fRec51[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fVec11[1] = fVec11[0];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fVec12[1] = fVec12[0];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fVec13[1] = fVec13[0];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];

		}

	}


};

#endif
