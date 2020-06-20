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

static float AmpMono_faustpower2_f(float value) {
	return (value * value);

}
static float AmpMono_faustpower3_f(float value) {
	return ((value * value) * value);

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
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
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
	float fVec0[2];
	float fRec8[2];
	FAUSTFLOAT fEntry22;
	FAUSTFLOAT fEntry23;
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	float fRec10[2];
	float fRec9[2];
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fRec11[2];
	FAUSTFLOAT fEntry32;
	float fRec7[2];
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	float fVec1[2];
	float fRec13[2];
	float fRec15[2];
	float fRec14[2];
	float fRec16[2];
	float fRec17[2];
	float fVec2[2];
	float fRec12[2];
	float fRec19[2];
	float fRec18[2];
	float fRec20[2];
	float fRec21[2];
	float fVec3[2];
	float fRec24[2];
	float fRec26[2];
	float fRec25[2];
	float fRec27[2];
	float fRec23[2];
	float fVec4[2];
	float fRec22[2];
	float fRec29[2];
	float fRec28[2];
	float fRec30[2];
	float fRec31[2];
	float fVec5[2];
	float fRec35[2];
	float fRec37[2];
	float fRec36[2];
	float fRec38[2];
	float fRec34[2];
	float fVec6[2];
	float fRec33[2];
	float fRec40[2];
	float fRec39[2];
	float fRec41[2];
	float fRec32[2];
	float fVec7[2];
	float fRec6[2];
	float fRec42[2];
	float fVec8[2];
	float fConst11;
	float fConst12;
	float fRec5[2];
	float fConst13;
	FAUSTFLOAT fEntry36;
	float fConst14;
	float fRec4[3];
	float fVec9[2];
	FAUSTFLOAT fEntry37;
	float fRec3[2];
	float fRec43[2];
	float fConst15;
	FAUSTFLOAT fEntry38;
	float fConst16;
	float fRec2[3];
	FAUSTFLOAT fEntry39;
	float fVec10[2];
	float fRec1[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	float fRec44[2];
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	float fRec45[2];
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	float fRec46[2];
	float fRec0[2];
	FAUSTFLOAT fEntry48;
	FAUSTFLOAT fEntry49;
	float fRec48[2];
	float fRec47[2];
	FAUSTFLOAT fEntry50;
	FAUSTFLOAT fEntry51;
	FAUSTFLOAT fEntry52;
	float fRec49[2];
	FAUSTFLOAT fEntry53;
	FAUSTFLOAT fEntry54;
	float fRec50[2];
	FAUSTFLOAT fEntry55;
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
	float fRec73[3];
	float fConst117;
	float fConst118;
	float fRec72[3];
	float fVec11[2];
	float fRec71[2];
	float fConst119;
	float fConst120;
	float fRec70[3];
	float fVec12[2];
	float fConst121;
	float fConst122;
	float fRec69[2];
	float fConst123;
	float fConst124;
	float fRec68[3];
	float fConst125;
	float fRec67[3];
	float fConst126;
	float fRec66[3];
	float fConst127;
	float fRec77[2];
	float fRec76[3];
	float fRec75[3];
	float fRec74[3];
	float fConst128;
	float fConst129;
	float fRec65[3];
	float fConst130;
	float fConst131;
	float fRec64[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec63[3];
	float fConst137;
	float fConst138;
	float fRec62[3];
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fRec61[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec60[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec59[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fRec58[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec57[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec56[3];
	float fConst164;
	float fVec13[2];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec55[2];
	float fConst168;
	float fConst169;
	float fRec54[3];
	float fConst170;
	FAUSTFLOAT fEntry56;
	float fConst171;
	float fRec79[2];
	float fRec78[3];
	float fConst172;
	float fConst173;
	float fRec53[3];
	float fConst174;
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec52[3];
	float fConst178;
	float fConst179;
	float fRec51[3];

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
		fConst1 = (1.0f / fConst0);
		fConst2 = (3.14159274f / fConst0);
		fConst3 = std::tan((12566.3711f / fConst0));
		fConst4 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst3))));
		fConst5 = std::tan((1570.79639f / fConst0));
		fConst6 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst5))));
		fConst7 = std::tan((31.415926f / fConst0));
		fConst8 = (1.0f / fConst7);
		fConst9 = (fConst8 + 1.0f);
		fConst10 = (0.0f - (1.0f / (fConst7 * fConst9)));
		fConst11 = (1.0f / fConst9);
		fConst12 = (1.0f - fConst8);
		fConst13 = (1.0f / fConst5);
		fConst14 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst15 = (1.0f / fConst3);
		fConst16 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
		fConst17 = std::tan((3769.91113f / fConst0));
		fConst18 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst17))));
		fConst19 = std::tan((18849.5566f / fConst0));
		fConst20 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst19))));
		fConst21 = std::tan((3455.75195f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (1.0f / (((fConst22 + 1.0f) / fConst21) + 1.0f));
		fConst24 = AmpMono_faustpower2_f(fConst21);
		fConst25 = (1.0f / fConst24);
		fConst26 = std::tan((2984.51294f / fConst0));
		fConst27 = (1.0f / fConst26);
		fConst28 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst29 = (27816.8476f / fConst28);
		fConst30 = (1.0f / (((fConst27 + fConst29) / fConst26) + 1.0f));
		fConst31 = (fConst22 + 1.0f);
		fConst32 = (1.0f / (fConst21 * fConst31));
		fConst33 = (8796.45898f / fConst28);
		fConst34 = (((fConst27 + fConst33) / fConst26) + 1.0f);
		fConst35 = (37699.1133f / fConst0);
		fConst36 = std::tan(fConst35);
		fConst37 = (1.0f / fConst36);
		fConst38 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst39 = (24836.4707f / fConst38);
		fConst40 = (1.0f / (((fConst37 + fConst39) / fConst36) + 1.0f));
		fConst41 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst36))));
		fConst42 = std::tan((21362.8301f / fConst0));
		fConst43 = (1.0f / fConst42);
		fConst44 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst45 = (19869.1758f / fConst44);
		fConst46 = (1.0f / (((fConst43 + fConst45) / fConst42) + 1.0f));
		fConst47 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst42))));
		fConst48 = std::tan((11938.0518f / fConst0));
		fConst49 = (1.0f / fConst48);
		fConst50 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst51 = (4701.22607f / fConst50);
		fConst52 = (1.0f / (((fConst49 + fConst51) / fConst48) + 1.0f));
		fConst53 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst48))));
		fConst54 = std::tan((9581.85742f / fConst0));
		fConst55 = (1.0f / fConst54);
		fConst56 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst57 = (2921.88965f / fConst56);
		fConst58 = (1.0f / (((fConst55 + fConst57) / fConst54) + 1.0f));
		fConst59 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst54))));
		fConst60 = std::tan((5215.04394f / fConst0));
		fConst61 = (1.0f / fConst60);
		fConst62 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst63 = (3713.44482f / fConst62);
		fConst64 = (1.0f / (((fConst61 + fConst63) / fConst60) + 1.0f));
		fConst65 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst60))));
		fConst66 = (3707.07935f / fConst0);
		fConst67 = std::tan(fConst66);
		fConst68 = (1.0f / fConst67);
		fConst69 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst70 = (502.654816f / fConst69);
		fConst71 = (1.0f / (((fConst68 + fConst70) / fConst67) + 1.0f));
		fConst72 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst67))));
		fConst73 = std::tan((3518.58374f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst76 = (875.483398f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (219.911484f / fConst75);
		fConst79 = (((fConst74 + fConst78) / fConst73) + 1.0f);
		fConst80 = std::tan((2010.61926f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst83 = (439.822968f / fConst82);
		fConst84 = (1.0f / (((fConst81 + fConst83) / fConst80) + 1.0f));
		fConst85 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst80))));
		fConst86 = std::tan((1853.53967f / fConst0));
		fConst87 = (1.0f / fConst86);
		fConst88 = (fConst0 * std::sin(fConst66));
		fConst89 = (1059.9884f / fConst88);
		fConst90 = (1.0f / (((fConst87 + fConst89) / fConst86) + 1.0f));
		fConst91 = (188.49556f / fConst88);
		fConst92 = (((fConst87 + fConst91) / fConst86) + 1.0f);
		fConst93 = std::tan((17592.918f / fConst0));
		fConst94 = (1.0f / fConst93);
		fConst95 = (1.0f / (((fConst94 + 0.445041865f) / fConst93) + 1.0f));
		fConst96 = AmpMono_faustpower2_f(fConst93);
		fConst97 = (1.0f / fConst96);
		fConst98 = (1.0f / (((fConst94 + 1.24697959f) / fConst93) + 1.0f));
		fConst99 = (0.0f - (2.0f / fConst96));
		fConst100 = (1.0f / (((fConst94 + 1.8019377f) / fConst93) + 1.0f));
		fConst101 = std::tan((34557.5195f / fConst0));
		fConst102 = (1.0f / fConst101);
		fConst103 = (1.0f / (((fConst102 + 1.0f) / fConst101) + 1.0f));
		fConst104 = (fConst94 + 1.0f);
		fConst105 = (1.0f / (fConst93 * fConst104));
		fConst106 = (0.0f - fConst105);
		fConst107 = (1.0f / (fConst102 + 1.0f));
		fConst108 = (1.0f - fConst102);
		fConst109 = std::tan((345.575195f / fConst0));
		fConst110 = (1.0f / fConst109);
		fConst111 = (1.0f / (((fConst110 + 0.765366852f) / fConst109) + 1.0f));
		fConst112 = AmpMono_faustpower2_f(fConst109);
		fConst113 = (1.0f / fConst112);
		fConst114 = (1.0f / (((fConst110 + 1.84775901f) / fConst109) + 1.0f));
		fConst115 = (((fConst110 + -1.84775901f) / fConst109) + 1.0f);
		fConst116 = (2.0f * (1.0f - fConst113));
		fConst117 = (0.0f - (2.0f / fConst112));
		fConst118 = (((fConst110 + -0.765366852f) / fConst109) + 1.0f);
		fConst119 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst101))));
		fConst120 = (((fConst102 + -1.0f) / fConst101) + 1.0f);
		fConst121 = (1.0f - fConst94);
		fConst122 = (fConst121 / fConst104);
		fConst123 = (((fConst94 + -1.8019377f) / fConst93) + 1.0f);
		fConst124 = (2.0f * (1.0f - fConst97));
		fConst125 = (((fConst94 + -1.24697959f) / fConst93) + 1.0f);
		fConst126 = (((fConst94 + -0.445041865f) / fConst93) + 1.0f);
		fConst127 = (1.0f / fConst104);
		fConst128 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst86))));
		fConst129 = (((fConst87 - fConst89) / fConst86) + 1.0f);
		fConst130 = (((fConst87 - fConst91) / fConst86) + 1.0f);
		fConst131 = (((fConst81 - fConst83) / fConst80) + 1.0f);
		fConst132 = (1390.84241f / fConst82);
		fConst133 = (((fConst81 + fConst132) / fConst80) + 1.0f);
		fConst134 = (((fConst81 - fConst132) / fConst80) + 1.0f);
		fConst135 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst136 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst137 = (((fConst74 - fConst78) / fConst73) + 1.0f);
		fConst138 = (((fConst68 - fConst70) / fConst67) + 1.0f);
		fConst139 = (1416.67383f / fConst69);
		fConst140 = (((fConst68 + fConst139) / fConst67) + 1.0f);
		fConst141 = (((fConst68 - fConst139) / fConst67) + 1.0f);
		fConst142 = (((fConst61 - fConst63) / fConst60) + 1.0f);
		fConst143 = (2481.85815f / fConst62);
		fConst144 = (((fConst61 + fConst143) / fConst60) + 1.0f);
		fConst145 = (((fConst61 - fConst143) / fConst60) + 1.0f);
		fConst146 = (((fConst55 - fConst57) / fConst54) + 1.0f);
		fConst147 = (1036.72558f / fConst56);
		fConst148 = (((fConst55 + fConst147) / fConst54) + 1.0f);
		fConst149 = (((fConst55 - fConst147) / fConst54) + 1.0f);
		fConst150 = (((fConst49 - fConst51) / fConst48) + 1.0f);
		fConst151 = (2356.19458f / fConst50);
		fConst152 = (((fConst49 + fConst151) / fConst48) + 1.0f);
		fConst153 = (((fConst49 - fConst151) / fConst48) + 1.0f);
		fConst154 = (((fConst43 - fConst45) / fConst42) + 1.0f);
		fConst155 = (628.318542f / fConst44);
		fConst156 = (((fConst43 + fConst155) / fConst42) + 1.0f);
		fConst157 = (((fConst43 - fConst155) / fConst42) + 1.0f);
		fConst158 = (((fConst37 - fConst39) / fConst36) + 1.0f);
		fConst159 = (785.398193f / fConst38);
		fConst160 = (((fConst37 + fConst159) / fConst36) + 1.0f);
		fConst161 = (((fConst37 - fConst159) / fConst36) + 1.0f);
		fConst162 = (((fConst27 - fConst29) / fConst26) + 1.0f);
		fConst163 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst26))));
		fConst164 = (((fConst27 - fConst33) / fConst26) + 1.0f);
		fConst165 = (0.0f - fConst32);
		fConst166 = (1.0f - fConst22);
		fConst167 = (fConst166 / fConst31);
		fConst168 = (((fConst22 + -1.0f) / fConst21) + 1.0f);
		fConst169 = (2.0f * (1.0f - fConst25));
		fConst170 = (0.0f - (2.0f / fConst24));
		fConst171 = (1.0f / fConst31);
		fConst172 = (1.0f / fConst19);
		fConst173 = (3141.59277f / (fConst0 * std::sin(fConst35)));
		fConst174 = std::tan((219.911484f / fConst0));
		fConst175 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst174))));
		fConst176 = (1.0f / fConst174);
		fConst177 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst178 = (1.0f / fConst17);
		fConst179 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));

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
			fRec8[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec10[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec9[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec11[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec7[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec13[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec15[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec14[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec16[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec17[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec19[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec18[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec20[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec21[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec24[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec26[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec25[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec27[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec23[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec22[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec29[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec28[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec30[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec31[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec35[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec37[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec36[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec38[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec34[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec6[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec33[l37] = 0.0f;

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
			fRec32[l41] = 0.0f;

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
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec9[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec3[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec43[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec2[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec10[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec1[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec44[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec45[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec46[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec0[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec48[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec47[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec49[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec50[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec73[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec72[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fVec11[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec71[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec70[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fVec12[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec69[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec68[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec67[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec66[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec77[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec76[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec75[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec74[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec65[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec64[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec63[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec62[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec61[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec60[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec59[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec58[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec57[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec56[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fVec13[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec55[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec54[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 2); l89 = (l89 + 1)) {
			fRec79[l89] = 0.0f;

		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec78[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec53[l91] = 0.0f;

		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec52[l92] = 0.0f;

		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec51[l93] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry20 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry21 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry44 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry39 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry41 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry43 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry42 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry40 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry9 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry5 = value + 3.866967e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry48 = value + 1.049631e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry6 = value + -6.951565e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry7 = value + -1.091596e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry49 = value + 5.941641e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry53 = value + -2.019639e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry54 = value + 5.374066e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry45 = value + 1.512931e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry47 = value + 8.753486e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry46 = value + -2.094365e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry4 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry52 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry51 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry50 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry3 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry8 = value + 3.147941e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry26 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry27 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry24 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry25 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry22 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry23 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry19 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry16 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry28 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry17 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry33 = value + -1.719012e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry13 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry15 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry32 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry14 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry18 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry29 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry31 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry30 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry37 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry36 = value + 0.000000e+00f; }
	void set_ts_presence(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00f; }
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
		float fSlow6 = ((20.0f * (float(fEntry5) + 1.0f)) + 10.0f);
		float fSlow7 = std::exp(((2.30258512f * (float(fEntry6) + 1.0f)) + -2.30258512f));
		float fSlow8 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry7) + 1.0f)) + -6.90775537f)))));
		float fSlow9 = (1.0f - fSlow8);
		float fSlow10 = (1.0f / fSlow6);
		float fSlow11 = std::exp(((4.60517025f * (float(fEntry8) + 1.0f)) + -4.60517025f));
		float fSlow12 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry9) + 1.0f)) + -2.30258512f))));
		float fSlow13 = (1.0f / fSlow12);
		float fSlow14 = (fSlow13 + 1.0f);
		float fSlow15 = (0.0f - (1.0f / (fSlow12 * fSlow14)));
		float fSlow16 = (float(fEntry10) + 1.0f);
		float fSlow17 = (fSlow2 * std::exp((3.45387769f * fSlow16)));
		float fSlow18 = float(fEntry11);
		float fSlow19 = (fSlow18 + 1.0f);
		float fSlow20 = (1.0f - (0.5f * fSlow19));
		float fSlow21 = std::tan((fConst2 * ((25.0f * fSlow19) + (400.0f * fSlow20))));
		float fSlow22 = (1.0f / fSlow21);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (0.0f - (1.0f / (fSlow21 * fSlow23)));
		float fSlow25 = float(fEntry12);
		float fSlow26 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow25) + -5.0f));
		float fSlow27 = (1.0f - (0.5f * fSlow26));
		float fSlow28 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow25) + -3.0f));
		float fSlow29 = (1.0f - (0.5f * fSlow28));
		float fSlow30 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow25) + -1.0f));
		float fSlow31 = (1.0f - (0.5f * fSlow30));
		float fSlow32 = std::exp(((2.30258512f * (float(fEntry13) + 1.0f)) + -2.30258512f));
		float fSlow33 = std::exp(((3.45387769f * (float(fEntry14) + 1.0f)) + -6.90775537f));
		float fSlow34 = (1.0f / ((fConst0 * fSlow33) + 1.0f));
		float fSlow35 = (100.0f * (1.0f - (float(fEntry15) + 1.0f)));
		float fSlow36 = (0.0f - fSlow35);
		float fSlow37 = (1.0f - (float(fEntry16) + 1.0f));
		float fSlow38 = (1.0f - (float(fEntry17) + 1.0f));
		float fSlow39 = std::exp(((4.60517025f * (float(fEntry18) + 1.0f)) + -4.60517025f));
		float fSlow40 = ((100.0f * (fSlow37 - fSlow38)) + fSlow39);
		float fSlow41 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry19) + 1.0f)) + -2.30258512f))));
		float fSlow42 = (1.0f / fSlow41);
		float fSlow43 = (fSlow42 + 1.0f);
		float fSlow44 = (0.0f - (1.0f / (fSlow41 * fSlow43)));
		float fSlow45 = (float(fEntry21) + 1.0f);
		float fSlow46 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry20) + 1.0f)))))) * std::exp((3.80045128f * fSlow45)));
		float fSlow47 = (1.0f / fSlow43);
		float fSlow48 = (1.0f - fSlow42);
		float fSlow49 = (fSlow46 / fSlow41);
		float fSlow50 = std::exp(((3.45387769f * (float(fEntry23) + 1.0f)) + -13.8155107f));
		float fSlow51 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry22) + 1.0f)) + -11.5129251f)) * fSlow50)) + 1.0f));
		float fSlow52 = (1.0f - fSlow51);
		float fSlow53 = (1.0f / ((fConst0 * fSlow50) + 1.0f));
		float fSlow54 = (5.0f * (1.0f - (float(fEntry24) + 1.0f)));
		float fSlow55 = (1.0f / ((fConst0 * (fSlow50 * std::exp(((5.75646257f * (float(fEntry25) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow56 = (1.0f - fSlow55);
		float fSlow57 = (float(fEntry27) + 1.0f);
		float fSlow58 = ((float(fEntry26) + 1.0f) - fSlow57);
		float fSlow59 = (2.5f * fSlow58);
		float fSlow60 = (0.117647059f / fSlow57);
		float fSlow61 = std::exp(((4.60517025f * (float(fEntry28) + 1.0f)) + -2.30258512f));
		float fSlow62 = (fSlow61 + (100.0f * fSlow37));
		float fSlow63 = (0.294117659f / fSlow61);
		float fSlow64 = (0.294117659f / fSlow39);
		float fSlow65 = std::exp(((2.30258512f * (float(fEntry29) + 1.0f)) + -2.30258512f));
		float fSlow66 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry30) + 1.0f)) + -6.90775537f)))));
		float fSlow67 = (1.0f - fSlow66);
		float fSlow68 = (100.0f * (1.0f - (float(fEntry31) + 1.0f)));
		float fSlow69 = (0.0f - fSlow68);
		float fSlow70 = (100.0f * fSlow38);
		float fSlow71 = (1.0f / ((fConst0 * (fSlow33 * std::exp((1.15129256f * (float(fEntry32) + 1.0f))))) + 1.0f));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = std::exp(((3.45387769f * (float(fEntry33) + 1.0f)) + -2.30258512f));
		float fSlow74 = (1.0f - (float(fEntry34) + 1.0f));
		float fSlow75 = (100.0f * (fSlow38 - fSlow74));
		float fSlow76 = (0.294117659f / fSlow73);
		float fSlow77 = (100.0f * fSlow74);
		float fSlow78 = ((float(fEntry35) + 1.0f) + 1.0f);
		float fSlow79 = (fSlow30 / fSlow78);
		float fSlow80 = (fSlow41 * fSlow2);
		float fSlow81 = (0.5f * (fSlow78 / fSlow80));
		float fSlow82 = (0.5f * (fSlow78 / fSlow2));
		float fSlow83 = (1.0f / fSlow80);
		float fSlow84 = (0.5f * fSlow78);
		float fSlow85 = AmpMono_faustpower2_f(fSlow84);
		float fSlow86 = (0.5f * (fSlow28 / fSlow85));
		float fSlow87 = (fSlow85 / fSlow2);
		float fSlow88 = (fSlow85 / fSlow80);
		float fSlow89 = (fSlow55 + -1.0f);
		float fSlow90 = (fSlow71 + -1.0f);
		float fSlow91 = AmpMono_faustpower3_f(fSlow84);
		float fSlow92 = (0.5f * (fSlow26 / fSlow91));
		float fSlow93 = (fSlow91 / fSlow2);
		float fSlow94 = (fSlow91 / fSlow80);
		float fSlow95 = (5.0f * fSlow45);
		int iSlow96 = (fSlow95 < 9.0f);
		int iSlow97 = (fSlow95 < 8.0f);
		int iSlow98 = (fSlow95 < 7.0f);
		int iSlow99 = (fSlow95 < 6.0f);
		int iSlow100 = (fSlow95 < 5.0f);
		int iSlow101 = (fSlow95 < 4.0f);
		int iSlow102 = (fSlow95 < 3.0f);
		int iSlow103 = (fSlow95 < 2.0f);
		int iSlow104 = (fSlow95 < 1.0f);
		float fSlow105 = std::pow(10.0f, (0.0500000007f * (iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?(iSlow103?(iSlow104?((fSlow95 < 0.0f)?0.0324000008f:(iSlow104?(0.0324000008f - (32.9620018f * fSlow45)):-6.55999994f)):(iSlow103?(-6.55999994f - (6.53999996f * (fSlow95 + -1.0f))):-13.1000004f)):(iSlow102?(-13.1000004f - (6.5f * (fSlow95 + -2.0f))):-19.6000004f)):(iSlow101?(-19.6000004f - (6.19999981f * (fSlow95 + -3.0f))):-25.7999992f)):(iSlow100?(-25.7999992f - (4.80000019f * (fSlow95 + -4.0f))):-30.6000004f)):(iSlow99?(-30.6000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow45))))):-32.7999992f)):(iSlow98?(-32.7999992f - (0.100000001f * (fSlow95 + -6.0f))):-32.9000015f)):(iSlow97?((0.400000006f * (fSlow95 + -7.0f)) + -32.9000015f):-32.5f)):(iSlow96?((0.300000012f * (fSlow95 + -8.0f)) + -32.5f):-32.2000008f)):((fSlow95 < 10.0f)?((0.100000001f * (fSlow95 + -9.0f)) + -32.2000008f):-32.0999985f))));
		float fSlow106 = (1.0f / fSlow23);
		float fSlow107 = (1.0f - fSlow22);
		float fSlow108 = (1.0f / (fSlow21 * fSlow2));
		float fSlow109 = std::pow(10.0f, (0.0500000007f * (fSlow18 * ((18.0f * fSlow20) + (4.5f * fSlow19)))));
		float fSlow110 = float(fEntry36);
		float fSlow111 = ((10.0f * fSlow110) + -14.0f);
		int iSlow112 = (fSlow111 > 0.0f);
		float fSlow113 = ((fSlow110 * ((fSlow18 < 0.0f)?800.0f:0.0f)) + 1000.0f);
		float fSlow114 = ((fConst14 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow111)))) * fSlow113);
		float fSlow115 = (fConst14 * fSlow113);
		float fSlow116 = (iSlow112?fSlow115:fSlow114);
		float fSlow117 = ((fConst13 * (fConst13 - fSlow116)) + 1.0f);
		float fSlow118 = ((fConst13 * (fConst13 + fSlow116)) + 1.0f);
		float fSlow119 = (iSlow112?fSlow114:fSlow115);
		float fSlow120 = ((fConst13 * (fConst13 + fSlow119)) + 1.0f);
		float fSlow121 = ((fConst13 * (fConst13 - fSlow119)) + 1.0f);
		float fSlow122 = float(fEntry37);
		int iSlow123 = (fSlow122 < 0.0f);
		float fSlow124 = std::tan((fConst2 * ((iSlow123?(1500.0f * fSlow122):0.0f) + 2000.0f)));
		float fSlow125 = (1.0f / fSlow124);
		float fSlow126 = (1.0f - fSlow125);
		float fSlow127 = (fSlow125 + 1.0f);
		float fSlow128 = (0.0f - (1.0f / (fSlow127 * fSlow124)));
		float fSlow129 = (fSlow124 * fSlow118);
		float fSlow130 = std::pow(10.0f, ((0.0500000007f * fSlow122) * (iSlow123?18.0f:9.0f)));
		float fSlow131 = (10.0f * float(fEntry38));
		int iSlow132 = (fSlow131 > 0.0f);
		float fSlow133 = (fConst16 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow131))));
		float fSlow134 = (iSlow132?fConst16:fSlow133);
		float fSlow135 = ((fConst15 * (fConst15 - fSlow134)) + 1.0f);
		float fSlow136 = ((fConst15 * (fConst15 + fSlow134)) + 1.0f);
		float fSlow137 = (iSlow132?fSlow133:fConst16);
		float fSlow138 = ((fConst15 * (fConst15 + fSlow137)) + 1.0f);
		float fSlow139 = ((fConst15 * (fConst15 - fSlow137)) + 1.0f);
		float fSlow140 = (250.0f * (float(fEntry39) + 1.0f));
		float fSlow141 = (1.0f / fSlow14);
		float fSlow142 = (1.0f - fSlow13);
		float fSlow143 = std::exp((0.0f - (fConst1 / std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -9.2103405f)))));
		float fSlow144 = (1.0f - fSlow143);
		float fSlow145 = (250.0f * (float(fEntry41) + 1.0f));
		float fSlow146 = std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -9.2103405f));
		float fSlow147 = (1.0f - (1.0f / ((fConst0 * (fSlow146 * std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow148 = (1.0f / ((fConst0 * fSlow146) + 1.0f));
		float fSlow149 = (100.0f * (1.0f - (float(fEntry44) + 1.0f)));
		float fSlow150 = std::exp(((2.30258512f * (float(fEntry45) + 1.0f)) + -2.30258512f));
		float fSlow151 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry46) + 1.0f)) + -6.90775537f)))));
		float fSlow152 = (1.0f - fSlow151);
		float fSlow153 = (100.0f * (1.0f - (float(fEntry47) + 1.0f)));
		float fSlow154 = (0.0f - fSlow153);
		float fSlow155 = std::exp(((3.45387769f * (float(fEntry48) + 1.0f)) + -2.30258512f));
		float fSlow156 = (0.294117659f / fSlow155);
		float fSlow157 = std::exp(((3.45387769f * (float(fEntry49) + 1.0f)) + -2.30258512f));
		float fSlow158 = (0.294117659f / fSlow157);
		float fSlow159 = std::exp(((2.30258512f * (float(fEntry50) + 1.0f)) + -4.60517025f));
		float fSlow160 = (1.0f - (1.0f / ((fConst0 * (fSlow159 * std::exp((1.15129256f * (float(fEntry51) + 1.0f))))) + 1.0f)));
		float fSlow161 = (1.0f / ((fConst0 * fSlow159) + 1.0f));
		float fSlow162 = std::exp(((2.30258512f * (float(fEntry52) + 1.0f)) + -2.30258512f));
		float fSlow163 = (fSlow11 / fSlow6);
		float fSlow164 = std::exp(((2.30258512f * (float(fEntry53) + 1.0f)) + -2.30258512f));
		float fSlow165 = (50.0f * (1.0f - (float(fEntry54) + 1.0f)));
		float fSlow166 = (0.0f - fSlow165);
		float fSlow167 = (5.0f * fSlow16);
		int iSlow168 = (fSlow167 < 9.0f);
		int iSlow169 = (fSlow167 < 7.0f);
		int iSlow170 = (fSlow167 < 6.0f);
		int iSlow171 = (fSlow167 < 5.0f);
		int iSlow172 = (fSlow167 < 4.0f);
		int iSlow173 = (fSlow167 < 3.0f);
		int iSlow174 = (fSlow167 < 2.0f);
		int iSlow175 = (fSlow167 < 1.0f);
		float fSlow176 = std::pow(10.0f, (0.0500000007f * (iSlow168?((fSlow167 < 8.0f)?(iSlow169?(iSlow170?(iSlow171?(iSlow172?(iSlow173?(iSlow174?(iSlow175?((fSlow167 < 0.0f)?8.36999989f:(iSlow175?(8.36999989f - (29.1499996f * fSlow16)):2.53999996f)):(iSlow174?(2.53999996f - (5.67000008f * (fSlow167 + -1.0f))):-3.13000011f)):(iSlow173?(-3.13000011f - (5.48000002f * (fSlow167 + -2.0f))):-8.60999966f)):(iSlow172?(-8.60999966f - (5.38999987f * (fSlow167 + -3.0f))):-14.0f)):(iSlow171?(-14.0f - (4.4000001f * (fSlow167 + -4.0f))):-18.3999996f)):(iSlow170?(-18.3999996f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow16))))):-20.6000004f)):(iSlow169?(-20.6000004f - (0.600000024f * (fSlow167 + -6.0f))):-21.2000008f)):-21.2000008f):(iSlow168?((0.100000001f * (fSlow167 + -8.0f)) + -21.2000008f):-21.1000004f)):((fSlow167 < 10.0f)?((0.100000001f * (fSlow167 + -9.0f)) + -21.1000004f):-21.0f))));
		float fSlow177 = float(fEntry55);
		float fSlow178 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow177)));
		float fSlow179 = float(fEntry56);
		float fSlow180 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow179))));
		float fSlow181 = (15.0f * fSlow179);
		int iSlow182 = (fSlow181 > 0.0f);
		float fSlow183 = (fConst173 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow181))));
		float fSlow184 = (iSlow182?fConst173:fSlow183);
		float fSlow185 = ((fConst172 * (fConst172 - fSlow184)) + 1.0f);
		float fSlow186 = ((fConst172 * (fConst172 + fSlow184)) + 1.0f);
		float fSlow187 = (iSlow182?fSlow183:fConst173);
		float fSlow188 = ((fConst172 * (fConst172 + fSlow187)) + 1.0f);
		float fSlow189 = ((fConst172 * (fConst172 - fSlow187)) + 1.0f);
		float fSlow190 = (0.0f - (10.0f * fSlow177));
		int iSlow191 = (fSlow190 > 0.0f);
		float fSlow192 = (fConst177 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow190))));
		float fSlow193 = (iSlow191?fConst177:fSlow192);
		float fSlow194 = ((fConst176 * (fConst176 - fSlow193)) + 1.0f);
		float fSlow195 = ((fConst176 * (fConst176 + fSlow193)) + 1.0f);
		float fSlow196 = (iSlow191?fSlow192:fConst177);
		float fSlow197 = ((fConst176 * (fConst176 + fSlow196)) + 1.0f);
		float fSlow198 = ((fConst176 * (fConst176 - fSlow196)) + 1.0f);
		float fSlow199 = (0.0f - (17.0f * fSlow177));
		int iSlow200 = (fSlow199 > 0.0f);
		float fSlow201 = (fConst179 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow199))));
		float fSlow202 = (iSlow200?fConst179:fSlow201);
		float fSlow203 = ((fConst178 * (fConst178 - fSlow202)) + 1.0f);
		float fSlow204 = ((fConst178 * (fConst178 + fSlow202)) + 1.0f);
		float fSlow205 = (iSlow200?fSlow201:fConst179);
		float fSlow206 = ((fConst178 * (fConst178 + fSlow205)) + 1.0f);
		float fSlow207 = ((fConst178 * (fConst178 - fSlow205)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow46 * fTemp0);
			fRec8[0] = ((fSlow44 * fVec0[1]) - (fSlow47 * ((fSlow48 * fRec8[1]) - (fSlow49 * fTemp0))));
			fRec10[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec8[0])) - fRec10[1]))) + (fSlow56 * fRec10[1]));
			fRec9[0] = ((fSlow52 * fRec9[1]) + (fSlow51 * fRec10[0]));
			float fTemp1 = ((fRec8[0] - fRec9[0]) - fSlow59);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * (fSlow58 + (fSlow57 * (((std::fabs((fTemp2 * fTemp3)) + -2.0f) * fTemp2) * fTemp3)))))) - fSlow62);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow40 + (std::max<float>(0.0f, fTemp4) + (fSlow61 * ((((std::fabs((fTemp6 * fTemp5)) + -2.0f) * fTemp6) * fTemp5) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (std::fabs(fTemp8) + -2.0f);
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow39 * ((((std::fabs((fTemp9 * fTemp8)) + -2.0f) * fTemp9) * fTemp8) + 1.0f)));
			fRec11[0] = ((fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp10 - fSlow70)))) + (fSlow66 * fRec11[1]));
			float fTemp11 = (fSlow65 * fRec11[0]);
			fRec7[0] = ((fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp10 - fTemp11) - fSlow70)) - fRec7[1])))) + (fSlow72 * fRec7[1]));
			float fTemp12 = (fSlow32 * fRec7[0]);
			float fTemp13 = (fSlow73 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow75));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((fTemp12 + std::min<float>(0.0f, fTemp13)) - (fSlow73 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow77);
			fVec1[0] = (fSlow82 * fTemp16);
			fRec13[0] = ((fSlow47 * ((fSlow81 * fTemp16) - (fSlow48 * fRec13[1]))) + (fSlow44 * fVec1[1]));
			fRec15[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec13[0])) - fRec15[1]))) + (fSlow56 * fRec15[1]));
			fRec14[0] = ((fSlow52 * fRec14[1]) + (fSlow51 * fRec15[0]));
			float fTemp17 = ((fRec13[0] - fRec14[0]) - fSlow59);
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * ((2.5f * (fSlow58 + (fSlow57 * (((std::fabs((fTemp18 * fTemp19)) + -2.0f) * fTemp18) * fTemp19)))) + std::min<float>(0.0f, fTemp17))) - fSlow62);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = ((std::fabs(fTemp21) + -2.0f) * fTemp21);
			float fTemp23 = (0.0f - (fSlow40 + (std::max<float>(0.0f, fTemp20) + (fSlow61 * ((fTemp22 * (std::fabs(fTemp22) + -2.0f)) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (std::fabs(fTemp24) + -2.0f);
			float fTemp26 = ((fSlow39 * ((((std::fabs((fTemp25 * fTemp24)) + -2.0f) * fTemp25) * fTemp24) + 1.0f)) + std::max<float>(0.0f, fTemp23));
			fRec16[0] = ((fSlow66 * fRec16[1]) + (fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp26 - fSlow70)))));
			float fTemp27 = (fSlow65 * fRec16[0]);
			fRec17[0] = ((fSlow72 * fRec17[1]) + (fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp26 - fTemp27) - fSlow70)) - fRec17[1])))));
			float fTemp28 = (fSlow32 * fRec17[0]);
			float fTemp29 = (fSlow73 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow75));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (std::fabs(fTemp30) + -2.0f);
			float fTemp32 = (((std::min<float>(0.0f, fTemp29) + fTemp28) - (fSlow73 * (1.0f - ((fTemp30 * (std::fabs((fTemp30 * fTemp31)) + -2.0f)) * fTemp31)))) - fSlow77);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec12[0] = ((fSlow44 * fVec2[1]) - (fSlow47 * ((fSlow48 * fRec12[1]) - (fSlow83 * fTemp32))));
			fRec19[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec12[0])) - fRec19[1]))) + (fSlow56 * fRec19[1]));
			fRec18[0] = ((fSlow51 * fRec19[0]) + (fSlow52 * fRec18[1]));
			float fTemp33 = ((fRec12[0] - fRec18[0]) - fSlow59);
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * ((2.5f * (fSlow58 + (fSlow57 * (((std::fabs((fTemp35 * fTemp34)) + -2.0f) * fTemp35) * fTemp34)))) + std::min<float>(0.0f, fTemp33))) - fSlow62);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (fTemp37 * (std::fabs(fTemp37) + -2.0f));
			float fTemp39 = (0.0f - (fSlow40 + ((fSlow61 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp36))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = ((std::fabs(fTemp40) + -2.0f) * fTemp40);
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow39 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)));
			fRec20[0] = ((fSlow66 * fRec20[1]) + (fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp42 - fSlow70)))));
			float fTemp43 = (fSlow65 * fRec20[0]);
			fRec21[0] = ((fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp42 - fTemp43) - fSlow70)) - fRec21[1])))) + (fSlow72 * fRec21[1]));
			float fTemp44 = (fSlow32 * fRec21[0]);
			float fTemp45 = (fSlow73 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow75));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (fTemp46 * (std::fabs(fTemp46) + -2.0f));
			float fTemp48 = ((fSlow31 * fTemp16) + (fSlow79 * (((std::min<float>(0.0f, fTemp45) + fTemp44) - (fSlow73 * (1.0f - (fTemp47 * (std::fabs(fTemp47) + -2.0f))))) - fSlow77)));
			fVec3[0] = (fSlow87 * fTemp48);
			fRec24[0] = ((fSlow44 * fVec3[1]) - (fSlow47 * ((fSlow48 * fRec24[1]) - (fSlow88 * fTemp48))));
			fRec26[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec24[0])) - fRec26[1]))) - (fSlow89 * fRec26[1]));
			fRec25[0] = ((fSlow51 * fRec26[0]) + (fSlow52 * fRec25[1]));
			float fTemp49 = ((fRec24[0] - fRec25[0]) - fSlow59);
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (fTemp50 * (std::fabs(fTemp50) + -2.0f));
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) + (2.5f * (fSlow58 + (fSlow57 * (fTemp51 * (std::fabs(fTemp51) + -2.0f))))))) - fSlow62);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = ((std::fabs(fTemp53) + -2.0f) * fTemp53);
			float fTemp55 = (0.0f - (fSlow40 + (std::max<float>(0.0f, fTemp52) + (fSlow61 * ((fTemp54 * (std::fabs(fTemp54) + -2.0f)) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (fTemp56 * (std::fabs(fTemp56) + -2.0f));
			float fTemp58 = ((fSlow39 * ((fTemp57 * (std::fabs(fTemp57) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp55));
			fRec27[0] = ((fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp58 - fSlow70)))) + (fSlow66 * fRec27[1]));
			float fTemp59 = (fSlow65 * fRec27[0]);
			fRec23[0] = ((fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp58 - fTemp59) - fSlow70)) - fRec23[1])))) - (fSlow90 * fRec23[1]));
			float fTemp60 = (fSlow32 * fRec23[0]);
			float fTemp61 = (fSlow73 + ((fTemp58 - (fTemp59 + fTemp60)) - fSlow75));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (std::fabs(fTemp62) + -2.0f);
			float fTemp64 = (((fTemp60 + std::min<float>(0.0f, fTemp61)) - (fSlow73 * (1.0f - (((std::fabs((fTemp62 * fTemp63)) + -2.0f) * fTemp62) * fTemp63)))) - fSlow77);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec22[0] = ((fSlow44 * fVec4[1]) - (fSlow47 * ((fSlow48 * fRec22[1]) - (fSlow83 * fTemp64))));
			fRec29[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec22[0])) - fRec29[1]))) - (fSlow89 * fRec29[1]));
			fRec28[0] = ((fSlow52 * fRec28[1]) + (fSlow51 * fRec29[0]));
			float fTemp65 = ((fRec22[0] - fRec28[0]) - fSlow59);
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = ((std::fabs(fTemp66) + -2.0f) * fTemp66);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) + (2.5f * (fSlow58 + (fSlow57 * (fTemp67 * (std::fabs(fTemp67) + -2.0f))))))) - fSlow62);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow40 + (std::max<float>(0.0f, fTemp68) + (fSlow61 * (((fTemp69 * (std::fabs((fTemp69 * fTemp70)) + -2.0f)) * fTemp70) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = ((std::fabs(fTemp72) + -2.0f) * fTemp72);
			float fTemp74 = ((fSlow39 * ((fTemp73 * (std::fabs(fTemp73) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp71));
			fRec30[0] = ((fSlow66 * fRec30[1]) + (fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp74 - fSlow70)))));
			float fTemp75 = (fSlow65 * fRec30[0]);
			fRec31[0] = ((fSlow72 * fRec31[1]) + (fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp74 - fTemp75) - fSlow70)) - fRec31[1])))));
			float fTemp76 = (fSlow32 * fRec31[0]);
			float fTemp77 = (fSlow73 + ((fTemp74 - (fTemp75 + fTemp76)) - fSlow75));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = ((fSlow29 * fTemp48) + (fSlow86 * (((std::min<float>(0.0f, fTemp77) + fTemp76) - (fSlow73 * (1.0f - ((fTemp78 * (std::fabs((fTemp78 * fTemp79)) + -2.0f)) * fTemp79)))) - fSlow77)));
			fVec5[0] = (fSlow93 * fTemp80);
			fRec35[0] = ((fSlow44 * fVec5[1]) - (fSlow47 * ((fSlow48 * fRec35[1]) - (fSlow94 * fTemp80))));
			fRec37[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec35[0])) - fRec37[1]))) + (fSlow56 * fRec37[1]));
			fRec36[0] = ((fSlow51 * fRec37[0]) + (fSlow52 * fRec36[1]));
			float fTemp81 = ((fRec35[0] - fRec36[0]) - fSlow59);
			float fTemp82 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp81))));
			float fTemp83 = (std::fabs(fTemp82) + -2.0f);
			float fTemp84 = ((fSlow2 * (std::min<float>(0.0f, fTemp81) + (2.5f * (fSlow58 + (fSlow57 * (((std::fabs((fTemp82 * fTemp83)) + -2.0f) * fTemp82) * fTemp83)))))) - fSlow62);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp84))));
			float fTemp86 = (fTemp85 * (std::fabs(fTemp85) + -2.0f));
			float fTemp87 = (0.0f - (fSlow40 + (std::max<float>(0.0f, fTemp84) + (fSlow61 * ((fTemp86 * (std::fabs(fTemp86) + -2.0f)) + 1.0f)))));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = (std::fabs(fTemp88) + -2.0f);
			float fTemp90 = (std::max<float>(0.0f, fTemp87) + (fSlow39 * (((fTemp89 * (std::fabs((fTemp89 * fTemp88)) + -2.0f)) * fTemp88) + 1.0f)));
			fRec38[0] = ((fSlow66 * fRec38[1]) + (fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp90 - fSlow70)))));
			float fTemp91 = (fSlow65 * fRec38[0]);
			fRec34[0] = ((fSlow72 * fRec34[1]) + (fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp90 - fTemp91) - fSlow70)) - fRec34[1])))));
			float fTemp92 = (fSlow32 * fRec34[0]);
			float fTemp93 = (fSlow73 + ((fTemp90 - (fTemp92 + fTemp91)) - fSlow75));
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = ((std::fabs(fTemp94) + -2.0f) * fTemp94);
			float fTemp96 = (((fTemp92 + std::min<float>(0.0f, fTemp93)) - (fSlow73 * (1.0f - (fTemp95 * (std::fabs(fTemp95) + -2.0f))))) - fSlow77);
			fVec6[0] = (fSlow3 * fTemp96);
			fRec33[0] = ((fSlow44 * fVec6[1]) - (fSlow47 * ((fSlow48 * fRec33[1]) - (fSlow83 * fTemp96))));
			fRec40[0] = ((fSlow53 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow54 + fRec33[0])) - fRec40[1]))) + (fSlow56 * fRec40[1]));
			fRec39[0] = ((fSlow52 * fRec39[1]) + (fSlow51 * fRec40[0]));
			float fTemp97 = ((fRec33[0] - fRec39[0]) - fSlow59);
			float fTemp98 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp97))));
			float fTemp99 = (std::fabs(fTemp98) + -2.0f);
			float fTemp100 = ((fSlow2 * (std::min<float>(0.0f, fTemp97) + (2.5f * (fSlow58 + (fSlow57 * ((fTemp98 * (std::fabs((fTemp98 * fTemp99)) + -2.0f)) * fTemp99)))))) - fSlow62);
			float fTemp101 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp100))));
			float fTemp102 = (fTemp101 * (std::fabs(fTemp101) + -2.0f));
			float fTemp103 = (0.0f - (fSlow40 + ((fSlow61 * ((fTemp102 * (std::fabs(fTemp102) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp100))));
			float fTemp104 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::min<float>(0.0f, fTemp103))));
			float fTemp105 = ((std::fabs(fTemp104) + -2.0f) * fTemp104);
			float fTemp106 = (std::max<float>(0.0f, fTemp103) + (fSlow39 * ((fTemp105 * (std::fabs(fTemp105) + -2.0f)) + 1.0f)));
			fRec41[0] = ((fSlow67 * (fSlow68 + std::max<float>(fSlow69, (fTemp106 - fSlow70)))) + (fSlow66 * fRec41[1]));
			float fTemp107 = (fSlow65 * fRec41[0]);
			fRec32[0] = ((fSlow34 * std::max<float>(0.0f, (fSlow35 + (std::max<float>(fSlow36, ((fTemp106 - fTemp107) - fSlow70)) - fRec32[1])))) - (fSlow90 * fRec32[1]));
			float fTemp108 = (fSlow32 * fRec32[0]);
			float fTemp109 = (fSlow73 + ((fTemp106 - (fTemp108 + fTemp107)) - fSlow75));
			float fTemp110 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp109))));
			float fTemp111 = (std::fabs(fTemp110) + -2.0f);
			float fTemp112 = (((fSlow27 * fTemp80) + (fSlow92 * (((fTemp108 + std::min<float>(0.0f, fTemp109)) - (fSlow73 * (1.0f - ((fTemp111 * (std::fabs((fTemp111 * fTemp110)) + -2.0f)) * fTemp110)))) - fSlow77))) * fSlow105);
			float fTemp113 = (fSlow3 * fTemp112);
			fVec7[0] = fTemp113;
			fRec6[0] = ((fSlow24 * fVec7[1]) - (fSlow106 * ((fSlow107 * fRec6[1]) - (fSlow108 * fTemp112))));
			fRec42[0] = (0.0f - (fSlow106 * ((fSlow107 * fRec42[1]) - (fTemp113 + fVec7[1]))));
			float fTemp114 = (fRec6[0] + (fSlow109 * fRec42[0]));
			fVec8[0] = fTemp114;
			fRec5[0] = ((fConst10 * fVec8[1]) - (fConst11 * ((fConst12 * fRec5[1]) - (fConst8 * fTemp114))));
			float fTemp115 = (fConst6 * fRec4[1]);
			fRec4[0] = (fRec5[0] - (((fRec4[2] * fSlow117) + fTemp115) / fSlow118));
			float fTemp116 = ((fTemp115 + (fRec4[0] * fSlow120)) + (fRec4[2] * fSlow121));
			float fTemp117 = (fTemp116 / fSlow118);
			fVec9[0] = fTemp117;
			fRec3[0] = (((fTemp117 + fVec9[1]) - (fSlow126 * fRec3[1])) / fSlow127);
			fRec43[0] = ((fVec9[1] * fSlow128) - (((fRec43[1] * fSlow126) - (fTemp116 / fSlow129)) / fSlow127));
			float fTemp118 = (fConst4 * fRec2[1]);
			fRec2[0] = ((fRec3[0] + (fRec43[0] * fSlow130)) - ((fTemp118 + (fRec2[2] * fSlow135)) / fSlow136));
			float fTemp119 = ((fSlow17 * (((fTemp118 + (fRec2[0] * fSlow138)) + (fRec2[2] * fSlow139)) / fSlow136)) - fSlow140);
			fVec10[0] = fTemp119;
			fRec1[0] = ((fSlow15 * fVec10[1]) - (fSlow141 * ((fSlow142 * fRec1[1]) - (fSlow13 * fTemp119))));
			fRec44[0] = ((fSlow143 * fRec44[1]) + (fSlow144 * (fRec1[0] - fSlow145)));
			fRec45[0] = ((fSlow147 * fRec45[1]) + (fSlow148 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow149 + ((fRec1[0] - fRec44[0]) - fSlow145))) - fRec45[1]))));
			float fTemp120 = ((fRec1[0] - (fRec44[0] + fRec45[0])) - fSlow145);
			float fTemp121 = (fSlow11 * fTemp120);
			fRec46[0] = ((fSlow151 * fRec46[1]) + (fSlow152 * (fSlow153 + std::max<float>(fSlow154, fTemp121))));
			float fTemp122 = (fSlow150 * fRec46[0]);
			fRec0[0] = ((fSlow9 * std::min<float>(1.0f, std::fabs((fSlow10 * (fTemp121 - fTemp122))))) + (fSlow8 * fRec0[1]));
			float fTemp123 = (fSlow6 / ((fSlow7 * fRec0[0]) + 1.0f));
			float fTemp124 = (fSlow155 + (fTemp121 - (fTemp123 + fTemp122)));
			float fTemp125 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow156 * std::max<float>(0.0f, fTemp124))));
			float fTemp126 = (fTemp125 * (std::fabs(fTemp125) + -2.0f));
			float fTemp127 = (((fTemp123 + std::min<float>(0.0f, fTemp124)) - (fSlow155 * (1.0f - (fTemp126 * (std::fabs(fTemp126) + -2.0f))))) - fSlow157);
			fRec48[0] = ((fSlow151 * fRec48[1]) + (fSlow152 * (fSlow153 + std::max<float>(fSlow154, (0.0f - fTemp121)))));
			float fTemp128 = (fSlow150 * fRec48[0]);
			fRec47[0] = ((fSlow9 * std::min<float>(1.0f, std::fabs((fSlow10 * (0.0f - (fTemp121 + fTemp128)))))) + (fSlow8 * fRec47[1]));
			float fTemp129 = (fSlow6 / ((fSlow7 * fRec47[0]) + 1.0f));
			float fTemp130 = (fSlow155 - ((fTemp121 + fTemp129) + fTemp128));
			float fTemp131 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow156 * std::max<float>(0.0f, fTemp130))));
			float fTemp132 = (std::fabs(fTemp131) + -2.0f);
			float fTemp133 = (((fTemp129 + std::min<float>(0.0f, fTemp130)) - (fSlow155 * (1.0f - ((fTemp131 * (std::fabs((fTemp131 * fTemp132)) + -2.0f)) * fTemp132)))) - fSlow157);
			float fTemp134 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow158 * std::min<float>(0.0f, fTemp133))));
			float fTemp135 = ((std::fabs(fTemp134) + -2.0f) * fTemp134);
			float fTemp136 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow158 * std::min<float>(0.0f, fTemp127))));
			float fTemp137 = (std::fabs(fTemp136) + -2.0f);
			float fTemp138 = std::fabs((fSlow163 * fTemp120));
			fRec49[0] = ((fSlow160 * fRec49[1]) + (fSlow161 * std::max<float>(0.0f, (((fSlow162 * std::min<float>(1.0f, fTemp138)) + std::max<float>(1.0f, fTemp138)) + (-1.0f - fRec49[1])))));
			float fTemp139 = (fSlow5 * ((std::max<float>(0.0f, fTemp127) - (std::max<float>(0.0f, fTemp133) + (fSlow157 * (((fTemp135 * (std::fabs(fTemp135) + -2.0f)) + 1.0f) - ((((std::fabs((fTemp136 * fTemp137)) + -2.0f) * fTemp136) * fTemp137) + 1.0f))))) / ((fSlow4 * fRec49[0]) + 1.0f)));
			fRec50[0] = ((fSlow151 * fRec50[1]) + (fSlow152 * (fSlow165 + std::max<float>(fSlow166, std::fabs(fTemp139)))));
			float fTemp140 = (fSlow3 * ((fTemp139 + (fSlow164 * fRec50[0])) * fSlow176));
			fRec73[0] = (fTemp140 - (fConst114 * ((fConst115 * fRec73[2]) + (fConst116 * fRec73[1]))));
			fRec72[0] = ((fConst114 * ((fConst113 * fRec73[2]) + ((fConst113 * fRec73[0]) + (fConst117 * fRec73[1])))) - (fConst111 * ((fConst118 * fRec72[2]) + (fConst116 * fRec72[1]))));
			float fTemp141 = ((fConst113 * fRec72[2]) + ((fConst117 * fRec72[1]) + (fConst113 * fRec72[0])));
			fVec11[0] = fTemp141;
			fRec71[0] = (0.0f - (fConst107 * ((fConst108 * fRec71[1]) - (fConst111 * (fTemp141 + fVec11[1])))));
			fRec70[0] = (fRec71[0] - (fConst103 * ((fConst119 * fRec70[1]) + (fConst120 * fRec70[2]))));
			float fTemp142 = (fRec70[2] + (fRec70[0] + (2.0f * fRec70[1])));
			fVec12[0] = fTemp142;
			fRec69[0] = ((fConst103 * ((fConst106 * fVec12[1]) + (fConst105 * fTemp142))) - (fConst122 * fRec69[1]));
			fRec68[0] = (fRec69[0] - (fConst100 * ((fConst123 * fRec68[2]) + (fConst124 * fRec68[1]))));
			fRec67[0] = ((fConst100 * (((fConst97 * fRec68[0]) + (fConst99 * fRec68[1])) + (fConst97 * fRec68[2]))) - (fConst98 * ((fConst125 * fRec67[2]) + (fConst124 * fRec67[1]))));
			fRec66[0] = ((fConst98 * (((fConst99 * fRec67[1]) + (fConst97 * fRec67[0])) + (fConst97 * fRec67[2]))) - (fConst95 * ((fConst126 * fRec66[2]) + (fConst124 * fRec66[1]))));
			fRec77[0] = (fConst127 * ((fConst103 * (fVec12[1] + fTemp142)) - (fConst121 * fRec77[1])));
			fRec76[0] = (fRec77[0] - (fConst100 * ((fConst123 * fRec76[2]) + (fConst124 * fRec76[1]))));
			fRec75[0] = ((fConst100 * (fRec76[2] + (fRec76[0] + (2.0f * fRec76[1])))) - (fConst98 * ((fConst125 * fRec75[2]) + (fConst124 * fRec75[1]))));
			fRec74[0] = ((fConst98 * (fRec75[2] + (fRec75[0] + (2.0f * fRec75[1])))) - (fConst95 * ((fConst126 * fRec74[2]) + (fConst124 * fRec74[1]))));
			float fTemp143 = (fConst128 * fRec65[1]);
			fRec65[0] = ((fConst95 * ((0.0316227749f * ((fConst97 * fRec66[2]) + ((fConst97 * fRec66[0]) + (fConst99 * fRec66[1])))) + (fRec74[2] + (fRec74[0] + (2.0f * fRec74[1]))))) - (fConst90 * (fTemp143 + (fConst129 * fRec65[2]))));
			float fTemp144 = (fConst85 * fRec64[1]);
			fRec64[0] = ((fConst90 * (((fConst92 * fRec65[0]) + fTemp143) + (fConst130 * fRec65[2]))) - (fConst84 * ((fConst131 * fRec64[2]) + fTemp144)));
			float fTemp145 = (fConst136 * fRec63[1]);
			fRec63[0] = ((fConst84 * ((fTemp144 + (fConst133 * fRec64[0])) + (fConst134 * fRec64[2]))) - (fConst77 * ((fConst135 * fRec63[2]) + fTemp145)));
			float fTemp146 = (fConst72 * fRec62[1]);
			fRec62[0] = ((fConst77 * (((fConst79 * fRec63[0]) + fTemp145) + (fConst137 * fRec63[2]))) - (fConst71 * (fTemp146 + (fConst138 * fRec62[2]))));
			float fTemp147 = (fConst65 * fRec61[1]);
			fRec61[0] = ((fConst71 * ((fTemp146 + (fConst140 * fRec62[0])) + (fConst141 * fRec62[2]))) - (fConst64 * ((fConst142 * fRec61[2]) + fTemp147)));
			float fTemp148 = (fConst59 * fRec60[1]);
			fRec60[0] = ((fConst64 * ((fTemp147 + (fConst144 * fRec61[0])) + (fConst145 * fRec61[2]))) - (fConst58 * ((fConst146 * fRec60[2]) + fTemp148)));
			float fTemp149 = (fConst53 * fRec59[1]);
			fRec59[0] = ((fConst58 * ((fTemp148 + (fConst148 * fRec60[0])) + (fConst149 * fRec60[2]))) - (fConst52 * (fTemp149 + (fConst150 * fRec59[2]))));
			float fTemp150 = (fConst47 * fRec58[1]);
			fRec58[0] = ((fConst52 * ((fTemp149 + (fConst152 * fRec59[0])) + (fConst153 * fRec59[2]))) - (fConst46 * ((fConst154 * fRec58[2]) + fTemp150)));
			float fTemp151 = (fConst41 * fRec57[1]);
			fRec57[0] = ((fConst46 * ((fTemp150 + (fConst156 * fRec58[0])) + (fConst157 * fRec58[2]))) - (fConst40 * (fTemp151 + (fConst158 * fRec57[2]))));
			float fTemp152 = (fConst163 * fRec56[1]);
			fRec56[0] = ((fConst40 * ((fTemp151 + (fConst160 * fRec57[0])) + (fConst161 * fRec57[2]))) - (fConst30 * ((fConst162 * fRec56[2]) + fTemp152)));
			float fTemp153 = (((fConst34 * fRec56[0]) + fTemp152) + (fConst164 * fRec56[2]));
			fVec13[0] = fTemp153;
			fRec55[0] = ((fConst30 * ((fConst32 * fTemp153) + (fConst165 * fVec13[1]))) - (fConst167 * fRec55[1]));
			fRec54[0] = (fRec55[0] - (fConst23 * ((fConst168 * fRec54[2]) + (fConst169 * fRec54[1]))));
			fRec79[0] = (fConst171 * ((fConst30 * (fVec13[1] + fTemp153)) - (fConst166 * fRec79[1])));
			fRec78[0] = (fRec79[0] - (fConst23 * ((fConst168 * fRec78[2]) + (fConst169 * fRec78[1]))));
			float fTemp154 = (fConst20 * fRec53[1]);
			fRec53[0] = ((fConst23 * (((fConst25 * fRec54[2]) + ((fConst25 * fRec54[0]) + (fConst170 * fRec54[1]))) + (fSlow180 * (fRec78[2] + (fRec78[0] + (2.0f * fRec78[1])))))) - (((fSlow185 * fRec53[2]) + fTemp154) / fSlow186));
			float fTemp155 = (fConst175 * fRec52[1]);
			fRec52[0] = ((((fTemp154 + (fRec53[0] * fSlow188)) + (fRec53[2] * fSlow189)) / fSlow186) - ((fTemp155 + (fRec52[2] * fSlow194)) / fSlow195));
			float fTemp156 = (fConst18 * fRec51[1]);
			fRec51[0] = (((((fRec52[0] * fSlow197) + fTemp155) + (fSlow198 * fRec52[2])) / fSlow195) - (((fRec51[2] * fSlow203) + fTemp156) / fSlow204));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow178 * (((fTemp156 + (fRec51[0] * fSlow206)) + (fRec51[2] * fSlow207)) / fSlow204)):fTemp140)));
			fVec0[1] = fVec0[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fVec1[1] = fVec1[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec17[1] = fRec17[0];
			fVec2[1] = fVec2[0];
			fRec12[1] = fRec12[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec21[1] = fRec21[0];
			fVec3[1] = fVec3[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec27[1] = fRec27[0];
			fRec23[1] = fRec23[0];
			fVec4[1] = fVec4[0];
			fRec22[1] = fRec22[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fVec5[1] = fVec5[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec38[1] = fRec38[0];
			fRec34[1] = fRec34[0];
			fVec6[1] = fVec6[0];
			fRec33[1] = fRec33[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec32[1] = fRec32[0];
			fVec7[1] = fVec7[0];
			fRec6[1] = fRec6[0];
			fRec42[1] = fRec42[0];
			fVec8[1] = fVec8[0];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fVec9[1] = fVec9[0];
			fRec3[1] = fRec3[0];
			fRec43[1] = fRec43[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec10[1] = fVec10[0];
			fRec1[1] = fRec1[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec0[1] = fRec0[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fVec11[1] = fVec11[0];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fVec12[1] = fVec12[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
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
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fVec13[1] = fVec13[0];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];

		}

	}


};

#endif
