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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	float fConst2;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
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
	float fVec0[2];
	float fRec7[2];
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	float fRec9[2];
	float fRec8[2];
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	float fRec10[2];
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	float fRec11[2];
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fVec1[2];
	float fRec15[2];
	float fRec17[2];
	float fRec16[2];
	float fRec18[2];
	float fRec14[2];
	float fVec2[2];
	float fRec13[2];
	float fRec20[2];
	float fRec19[2];
	float fRec21[2];
	float fRec12[2];
	float fVec3[2];
	float fRec23[2];
	float fRec25[2];
	float fRec24[2];
	float fRec26[2];
	float fRec27[2];
	float fVec4[2];
	float fRec22[2];
	float fRec29[2];
	float fRec28[2];
	float fRec30[2];
	float fRec31[2];
	float fVec5[2];
	float fRec34[2];
	float fRec36[2];
	float fRec35[2];
	float fRec37[2];
	float fRec33[2];
	float fVec6[2];
	float fRec32[2];
	float fRec39[2];
	float fRec38[2];
	float fRec40[2];
	float fRec41[2];
	float fVec7[2];
	float fRec6[2];
	float fRec42[2];
	float fVec8[2];
	float fConst7;
	float fConst8;
	float fRec5[2];
	float fConst9;
	float fConst10;
	FAUSTFLOAT fEntry37;
	float fConst11;
	float fConst12;
	float fRec4[3];
	float fVec9[2];
	FAUSTFLOAT fEntry38;
	float fRec3[2];
	float fRec43[2];
	float fConst13;
	float fConst14;
	FAUSTFLOAT fEntry39;
	float fConst15;
	float fConst16;
	float fRec2[3];
	FAUSTFLOAT fEntry40;
	float fVec10[2];
	float fRec1[2];
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	float fRec45[2];
	FAUSTFLOAT fEntry45;
	float fRec44[2];
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	float fRec46[2];
	FAUSTFLOAT fEntry48;
	FAUSTFLOAT fEntry49;
	FAUSTFLOAT fEntry50;
	float fRec47[2];
	FAUSTFLOAT fEntry51;
	float fRec49[2];
	float fRec48[2];
	FAUSTFLOAT fEntry52;
	FAUSTFLOAT fEntry53;
	FAUSTFLOAT fEntry54;
	float fRec50[2];
	float fRec0[2];
	FAUSTFLOAT fEntry55;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	FAUSTFLOAT fEntry56;
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
	float fRec73[3];
	float fConst118;
	float fConst119;
	float fRec72[3];
	float fVec11[2];
	float fRec71[2];
	float fConst120;
	float fConst121;
	float fRec70[3];
	float fVec12[2];
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec69[2];
	float fConst125;
	float fConst126;
	float fRec68[3];
	float fConst127;
	float fRec67[3];
	float fConst128;
	float fRec66[3];
	float fConst129;
	float fRec77[2];
	float fRec76[3];
	float fRec75[3];
	float fRec74[3];
	float fConst130;
	float fRec65[3];
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec64[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fRec63[3];
	float fConst140;
	float fConst141;
	float fRec62[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec61[3];
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec60[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec59[3];
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec58[3];
	float fConst159;
	float fConst160;
	float fRec57[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec56[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fVec13[2];
	float fConst168;
	float fConst169;
	float fRec55[2];
	float fConst170;
	float fConst171;
	float fRec54[3];
	float fConst172;
	float fConst173;
	float fRec79[2];
	float fRec78[3];
	float fConst174;
	float fRec53[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fConst178;
	float fRec52[3];
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
		fConst3 = std::tan((31.415926f / fConst0));
		fConst4 = (1.0f / fConst3);
		fConst5 = (fConst4 + 1.0f);
		fConst6 = (0.0f - (1.0f / (fConst3 * fConst5)));
		fConst7 = (1.0f / fConst5);
		fConst8 = (1.0f - fConst4);
		fConst9 = std::tan((1570.79639f / fConst0));
		fConst10 = (1.0f / fConst9);
		fConst11 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst12 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst13 = std::tan((12566.3711f / fConst0));
		fConst14 = (1.0f / fConst13);
		fConst15 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
		fConst16 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst17 = std::tan((3769.91113f / fConst0));
		fConst18 = (1.0f / fConst17);
		fConst19 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));
		fConst20 = std::tan((18849.5566f / fConst0));
		fConst21 = (1.0f / fConst20);
		fConst22 = (37699.1133f / fConst0);
		fConst23 = (3141.59277f / (fConst0 * std::sin(fConst22)));
		fConst24 = std::tan((3455.75195f / fConst0));
		fConst25 = (1.0f / fConst24);
		fConst26 = (1.0f / (((fConst25 + 1.0f) / fConst24) + 1.0f));
		fConst27 = AmpMono_faustpower2_f(fConst24);
		fConst28 = (1.0f / fConst27);
		fConst29 = std::tan((2984.51294f / fConst0));
		fConst30 = (1.0f / fConst29);
		fConst31 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst32 = (27816.8476f / fConst31);
		fConst33 = (1.0f / (((fConst30 + fConst32) / fConst29) + 1.0f));
		fConst34 = (fConst25 + 1.0f);
		fConst35 = (1.0f / (fConst24 * fConst34));
		fConst36 = (0.0f - fConst35);
		fConst37 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst29))));
		fConst38 = std::tan(fConst22);
		fConst39 = (1.0f / fConst38);
		fConst40 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst41 = (24836.4707f / fConst40);
		fConst42 = (1.0f / (((fConst39 + fConst41) / fConst38) + 1.0f));
		fConst43 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst38))));
		fConst44 = std::tan((21362.8301f / fConst0));
		fConst45 = (1.0f / fConst44);
		fConst46 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst47 = (19869.1758f / fConst46);
		fConst48 = (1.0f / (((fConst45 + fConst47) / fConst44) + 1.0f));
		fConst49 = (628.318542f / fConst46);
		fConst50 = (((fConst45 + fConst49) / fConst44) + 1.0f);
		fConst51 = std::tan((11938.0518f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst54 = (4701.22607f / fConst53);
		fConst55 = (1.0f / (((fConst52 + fConst54) / fConst51) + 1.0f));
		fConst56 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst51))));
		fConst57 = std::tan((9581.85742f / fConst0));
		fConst58 = (1.0f / fConst57);
		fConst59 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst60 = (2921.88965f / fConst59);
		fConst61 = (1.0f / (((fConst58 + fConst60) / fConst57) + 1.0f));
		fConst62 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst57))));
		fConst63 = std::tan((5215.04394f / fConst0));
		fConst64 = (1.0f / fConst63);
		fConst65 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst66 = (3713.44482f / fConst65);
		fConst67 = (1.0f / (((fConst64 + fConst66) / fConst63) + 1.0f));
		fConst68 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst63))));
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
		fConst81 = (219.911484f / fConst78);
		fConst82 = (((fConst77 + fConst81) / fConst76) + 1.0f);
		fConst83 = std::tan((2010.61926f / fConst0));
		fConst84 = (1.0f / fConst83);
		fConst85 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst86 = (439.822968f / fConst85);
		fConst87 = (1.0f / (((fConst84 + fConst86) / fConst83) + 1.0f));
		fConst88 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst83))));
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
		fConst99 = (1.0f / fConst98);
		fConst100 = (1.0f / (((fConst96 + 1.24697959f) / fConst95) + 1.0f));
		fConst101 = (0.0f - (2.0f / fConst98));
		fConst102 = (1.0f / (((fConst96 + 1.8019377f) / fConst95) + 1.0f));
		fConst103 = std::tan((34557.5195f / fConst0));
		fConst104 = (1.0f / fConst103);
		fConst105 = (1.0f / (((fConst104 + 1.0f) / fConst103) + 1.0f));
		fConst106 = (fConst96 + 1.0f);
		fConst107 = (1.0f / (fConst95 * fConst106));
		fConst108 = (1.0f / (fConst104 + 1.0f));
		fConst109 = (1.0f - fConst104);
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
		fConst120 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst103))));
		fConst121 = (((fConst104 + -1.0f) / fConst103) + 1.0f);
		fConst122 = (0.0f - fConst107);
		fConst123 = (1.0f - fConst96);
		fConst124 = (fConst123 / fConst106);
		fConst125 = (((fConst96 + -1.8019377f) / fConst95) + 1.0f);
		fConst126 = (2.0f * (1.0f - fConst99));
		fConst127 = (((fConst96 + -1.24697959f) / fConst95) + 1.0f);
		fConst128 = (((fConst96 + -0.445041865f) / fConst95) + 1.0f);
		fConst129 = (1.0f / fConst106);
		fConst130 = (((fConst90 - fConst92) / fConst89) + 1.0f);
		fConst131 = (188.49556f / fConst91);
		fConst132 = (((fConst90 + fConst131) / fConst89) + 1.0f);
		fConst133 = (((fConst90 - fConst131) / fConst89) + 1.0f);
		fConst134 = (((fConst84 - fConst86) / fConst83) + 1.0f);
		fConst135 = (1390.84241f / fConst85);
		fConst136 = (((fConst84 + fConst135) / fConst83) + 1.0f);
		fConst137 = (((fConst84 - fConst135) / fConst83) + 1.0f);
		fConst138 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst76))));
		fConst139 = (((fConst77 - fConst79) / fConst76) + 1.0f);
		fConst140 = (((fConst77 - fConst81) / fConst76) + 1.0f);
		fConst141 = (((fConst71 - fConst73) / fConst70) + 1.0f);
		fConst142 = (1416.67383f / fConst72);
		fConst143 = (((fConst71 + fConst142) / fConst70) + 1.0f);
		fConst144 = (((fConst71 - fConst142) / fConst70) + 1.0f);
		fConst145 = (((fConst64 - fConst66) / fConst63) + 1.0f);
		fConst146 = (2481.85815f / fConst65);
		fConst147 = (((fConst64 + fConst146) / fConst63) + 1.0f);
		fConst148 = (((fConst64 - fConst146) / fConst63) + 1.0f);
		fConst149 = (((fConst58 - fConst60) / fConst57) + 1.0f);
		fConst150 = (1036.72558f / fConst59);
		fConst151 = (((fConst58 + fConst150) / fConst57) + 1.0f);
		fConst152 = (((fConst58 - fConst150) / fConst57) + 1.0f);
		fConst153 = (((fConst52 - fConst54) / fConst51) + 1.0f);
		fConst154 = (2356.19458f / fConst53);
		fConst155 = (((fConst52 + fConst154) / fConst51) + 1.0f);
		fConst156 = (((fConst52 - fConst154) / fConst51) + 1.0f);
		fConst157 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst44))));
		fConst158 = (((fConst45 - fConst47) / fConst44) + 1.0f);
		fConst159 = (((fConst45 - fConst49) / fConst44) + 1.0f);
		fConst160 = (((fConst39 - fConst41) / fConst38) + 1.0f);
		fConst161 = (785.398193f / fConst40);
		fConst162 = (((fConst39 + fConst161) / fConst38) + 1.0f);
		fConst163 = (((fConst39 - fConst161) / fConst38) + 1.0f);
		fConst164 = (((fConst30 - fConst32) / fConst29) + 1.0f);
		fConst165 = (8796.45898f / fConst31);
		fConst166 = (((fConst30 + fConst165) / fConst29) + 1.0f);
		fConst167 = (((fConst30 - fConst165) / fConst29) + 1.0f);
		fConst168 = (1.0f - fConst25);
		fConst169 = (fConst168 / fConst34);
		fConst170 = (((fConst25 + -1.0f) / fConst24) + 1.0f);
		fConst171 = (2.0f * (1.0f - fConst28));
		fConst172 = (0.0f - (2.0f / fConst27));
		fConst173 = (1.0f / fConst34);
		fConst174 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst20))));
		fConst175 = std::tan((219.911484f / fConst0));
		fConst176 = (1.0f / fConst175);
		fConst177 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst178 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst175))));
		fConst179 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst17))));

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
			fRec7[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec9[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec8[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec11[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec15[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec17[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec16[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec18[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec14[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec20[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec19[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec21[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec12[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec23[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec25[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec24[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec26[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec27[l23] = 0.0f;

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
			fRec34[l31] = 0.0f;

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
			fRec33[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec6[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec32[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec39[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec38[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec40[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec41[l41] = 0.0f;

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
			fRec45[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec44[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec46[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec47[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec49[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec48[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec50[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec0[l61] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry36 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry22 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry23 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry42 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry40 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry44 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry45 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry41 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry43 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry10 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry48 = value + 3.866967e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry8 = value + 1.049631e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry49 = value + -6.951565e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry50 = value + -1.091596e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry51 = value + 5.941641e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry3 = value + -2.019639e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry5 = value + 5.374066e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry46 = value + 1.512931e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry47 = value + 8.753486e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry4 = value + -2.094365e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry53 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry54 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry52 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry6 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry9 = value + 3.147941e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry20 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry19 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry26 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry27 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry25 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry24 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry21 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry15 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry18 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry16 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry14 = value + -1.719012e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry31 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry34 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry33 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry32 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry17 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry28 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry30 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry29 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry37 = value + 0.000000e+00f; }
	void set_ts_presence(FAUSTFLOAT value) { fEntry39 = value + 0.000000e+00f; }
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
		float fSlow4 = std::exp(((2.30258512f * (float(fEntry3) + 1.0f)) + -2.30258512f));
		float fSlow5 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry4) + 1.0f)) + -6.90775537f)))));
		float fSlow6 = (1.0f - fSlow5);
		float fSlow7 = (50.0f * (1.0f - (float(fEntry5) + 1.0f)));
		float fSlow8 = (0.0f - fSlow7);
		float fSlow9 = (0.5f * ((float(fEntry6) + 1.0f) * std::exp(((2.30258512f * (float(fEntry7) + 1.0f)) + -2.30258512f))));
		float fSlow10 = (fSlow9 + 1.0f);
		float fSlow11 = std::exp(((3.45387769f * (float(fEntry8) + 1.0f)) + -2.30258512f));
		float fSlow12 = std::exp(((4.60517025f * (float(fEntry9) + 1.0f)) + -4.60517025f));
		float fSlow13 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry10) + 1.0f)) + -2.30258512f))));
		float fSlow14 = (1.0f / fSlow13);
		float fSlow15 = (fSlow14 + 1.0f);
		float fSlow16 = (0.0f - (1.0f / (fSlow15 * fSlow13)));
		float fSlow17 = (float(fEntry11) + 1.0f);
		float fSlow18 = (fSlow2 * std::exp((3.45387769f * fSlow17)));
		float fSlow19 = float(fEntry12);
		float fSlow20 = (fSlow19 + 1.0f);
		float fSlow21 = (1.0f - (0.5f * fSlow20));
		float fSlow22 = std::tan((fConst2 * ((400.0f * fSlow21) + (25.0f * fSlow20))));
		float fSlow23 = (1.0f / fSlow22);
		float fSlow24 = (fSlow23 + 1.0f);
		float fSlow25 = (0.0f - (1.0f / (fSlow22 * fSlow24)));
		float fSlow26 = float(fEntry13);
		float fSlow27 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow26) + -5.0f));
		float fSlow28 = (1.0f - (0.5f * fSlow27));
		float fSlow29 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow26) + -3.0f));
		float fSlow30 = (1.0f - (0.5f * fSlow29));
		float fSlow31 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow26) + -1.0f));
		float fSlow32 = (1.0f - (0.5f * fSlow31));
		float fSlow33 = std::exp(((3.45387769f * (float(fEntry14) + 1.0f)) + -2.30258512f));
		float fSlow34 = (1.0f - (float(fEntry15) + 1.0f));
		float fSlow35 = (1.0f - (float(fEntry16) + 1.0f));
		float fSlow36 = std::exp(((4.60517025f * (float(fEntry17) + 1.0f)) + -4.60517025f));
		float fSlow37 = ((100.0f * (fSlow34 - fSlow35)) + fSlow36);
		float fSlow38 = std::exp(((4.60517025f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow39 = (0.294117659f / fSlow38);
		float fSlow40 = (float(fEntry19) + 1.0f);
		float fSlow41 = (fSlow40 - (float(fEntry20) + 1.0f));
		float fSlow42 = (2.5f * fSlow41);
		float fSlow43 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry21) + 1.0f)) + -2.30258512f))));
		float fSlow44 = (1.0f / fSlow43);
		float fSlow45 = (fSlow44 + 1.0f);
		float fSlow46 = (0.0f - (1.0f / (fSlow45 * fSlow43)));
		float fSlow47 = (float(fEntry23) + 1.0f);
		float fSlow48 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry22) + 1.0f)))))) * std::exp((3.80045128f * fSlow47)));
		float fSlow49 = (1.0f / fSlow45);
		float fSlow50 = (1.0f - fSlow44);
		float fSlow51 = (fSlow48 / fSlow43);
		float fSlow52 = std::exp(((3.45387769f * (float(fEntry24) + 1.0f)) + -13.8155107f));
		float fSlow53 = (1.0f / ((fConst0 * (fSlow52 * std::exp(((6.90775537f * (float(fEntry25) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow54 = (1.0f - fSlow53);
		float fSlow55 = (1.0f / ((fConst0 * fSlow52) + 1.0f));
		float fSlow56 = (5.0f * (1.0f - (float(fEntry26) + 1.0f)));
		float fSlow57 = (1.0f / ((fConst0 * (fSlow52 * std::exp(((5.75646257f * (float(fEntry27) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow58 = (1.0f - fSlow57);
		float fSlow59 = (0.117647059f / fSlow40);
		float fSlow60 = (fSlow38 + (100.0f * fSlow34));
		float fSlow61 = (0.294117659f / fSlow36);
		float fSlow62 = std::exp(((2.30258512f * (float(fEntry28) + 1.0f)) + -2.30258512f));
		float fSlow63 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry29) + 1.0f)) + -6.90775537f)))));
		float fSlow64 = (1.0f - fSlow63);
		float fSlow65 = (100.0f * (1.0f - (float(fEntry30) + 1.0f)));
		float fSlow66 = (0.0f - fSlow65);
		float fSlow67 = (100.0f * fSlow35);
		float fSlow68 = std::exp(((2.30258512f * (float(fEntry31) + 1.0f)) + -2.30258512f));
		float fSlow69 = std::exp(((3.45387769f * (float(fEntry32) + 1.0f)) + -6.90775537f));
		float fSlow70 = (1.0f / ((fConst0 * (fSlow69 * std::exp((1.15129256f * (float(fEntry33) + 1.0f))))) + 1.0f));
		float fSlow71 = (1.0f - fSlow70);
		float fSlow72 = (1.0f / ((fConst0 * fSlow69) + 1.0f));
		float fSlow73 = (100.0f * (1.0f - (float(fEntry34) + 1.0f)));
		float fSlow74 = (0.0f - fSlow73);
		float fSlow75 = (1.0f - (float(fEntry35) + 1.0f));
		float fSlow76 = (100.0f * (fSlow35 - fSlow75));
		float fSlow77 = (0.294117659f / fSlow33);
		float fSlow78 = (100.0f * fSlow75);
		float fSlow79 = ((float(fEntry36) + 1.0f) + 1.0f);
		float fSlow80 = (fSlow31 / fSlow79);
		float fSlow81 = (fSlow43 * fSlow2);
		float fSlow82 = (0.5f * (fSlow79 / fSlow81));
		float fSlow83 = (0.5f * (fSlow79 / fSlow2));
		float fSlow84 = (1.0f / fSlow81);
		float fSlow85 = (fSlow70 + -1.0f);
		float fSlow86 = (0.5f * fSlow79);
		float fSlow87 = AmpMono_faustpower2_f(fSlow86);
		float fSlow88 = (0.5f * (fSlow29 / fSlow87));
		float fSlow89 = (fSlow87 / fSlow2);
		float fSlow90 = (fSlow87 / fSlow81);
		float fSlow91 = (fSlow57 + -1.0f);
		float fSlow92 = AmpMono_faustpower3_f(fSlow86);
		float fSlow93 = (0.5f * (fSlow27 / fSlow92));
		float fSlow94 = (fSlow92 / fSlow2);
		float fSlow95 = (fSlow92 / fSlow81);
		float fSlow96 = (5.0f * fSlow47);
		int iSlow97 = (fSlow96 < 9.0f);
		int iSlow98 = (fSlow96 < 8.0f);
		int iSlow99 = (fSlow96 < 7.0f);
		int iSlow100 = (fSlow96 < 6.0f);
		int iSlow101 = (fSlow96 < 5.0f);
		int iSlow102 = (fSlow96 < 4.0f);
		int iSlow103 = (fSlow96 < 3.0f);
		int iSlow104 = (fSlow96 < 2.0f);
		int iSlow105 = (fSlow96 < 1.0f);
		float fSlow106 = std::pow(10.0f, (0.0500000007f * (iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?(iSlow103?(iSlow104?(iSlow105?((fSlow96 < 0.0f)?0.0324000008f:(iSlow105?(0.0324000008f - (32.9620018f * fSlow47)):-6.55999994f)):(iSlow104?(-6.55999994f - (6.53999996f * (fSlow96 + -1.0f))):-13.1000004f)):(iSlow103?(-13.1000004f - (6.5f * (fSlow96 + -2.0f))):-19.6000004f)):(iSlow102?(-19.6000004f - (6.19999981f * (fSlow96 + -3.0f))):-25.7999992f)):(iSlow101?(-25.7999992f - (4.80000019f * (fSlow96 + -4.0f))):-30.6000004f)):(iSlow100?(-30.6000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow47))))):-32.7999992f)):(iSlow99?(-32.7999992f - (0.100000001f * (fSlow96 + -6.0f))):-32.9000015f)):(iSlow98?((0.400000006f * (fSlow96 + -7.0f)) + -32.9000015f):-32.5f)):(iSlow97?((0.300000012f * (fSlow96 + -8.0f)) + -32.5f):-32.2000008f)):((fSlow96 < 10.0f)?((0.100000001f * (fSlow96 + -9.0f)) + -32.2000008f):-32.0999985f))));
		float fSlow107 = (1.0f / fSlow24);
		float fSlow108 = (1.0f - fSlow23);
		float fSlow109 = (1.0f / (fSlow22 * fSlow2));
		float fSlow110 = std::pow(10.0f, (0.0500000007f * (fSlow19 * ((18.0f * fSlow21) + (4.5f * fSlow20)))));
		float fSlow111 = float(fEntry37);
		float fSlow112 = ((10.0f * fSlow111) + -14.0f);
		int iSlow113 = (fSlow112 > 0.0f);
		float fSlow114 = ((fSlow111 * ((fSlow19 < 0.0f)?800.0f:0.0f)) + 1000.0f);
		float fSlow115 = ((fConst11 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow112)))) * fSlow114);
		float fSlow116 = (fConst11 * fSlow114);
		float fSlow117 = (iSlow113?fSlow116:fSlow115);
		float fSlow118 = ((fConst10 * (fConst10 - fSlow117)) + 1.0f);
		float fSlow119 = ((fConst10 * (fConst10 + fSlow117)) + 1.0f);
		float fSlow120 = (iSlow113?fSlow115:fSlow116);
		float fSlow121 = ((fConst10 * (fConst10 + fSlow120)) + 1.0f);
		float fSlow122 = ((fConst10 * (fConst10 - fSlow120)) + 1.0f);
		float fSlow123 = float(fEntry38);
		int iSlow124 = (fSlow123 < 0.0f);
		float fSlow125 = std::tan((fConst2 * ((iSlow124?(1500.0f * fSlow123):0.0f) + 2000.0f)));
		float fSlow126 = (1.0f / fSlow125);
		float fSlow127 = (1.0f - fSlow126);
		float fSlow128 = (fSlow126 + 1.0f);
		float fSlow129 = (0.0f - (1.0f / (fSlow125 * fSlow128)));
		float fSlow130 = (fSlow125 * fSlow119);
		float fSlow131 = std::pow(10.0f, ((0.0500000007f * fSlow123) * (iSlow124?18.0f:9.0f)));
		float fSlow132 = (10.0f * float(fEntry39));
		int iSlow133 = (fSlow132 > 0.0f);
		float fSlow134 = (fConst15 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow132))));
		float fSlow135 = (iSlow133?fConst15:fSlow134);
		float fSlow136 = ((fConst14 * (fConst14 - fSlow135)) + 1.0f);
		float fSlow137 = ((fConst14 * (fConst14 + fSlow135)) + 1.0f);
		float fSlow138 = (iSlow133?fSlow134:fConst15);
		float fSlow139 = ((fConst14 * (fConst14 + fSlow138)) + 1.0f);
		float fSlow140 = ((fConst14 * (fConst14 - fSlow138)) + 1.0f);
		float fSlow141 = (250.0f * (float(fEntry40) + 1.0f));
		float fSlow142 = (1.0f / fSlow15);
		float fSlow143 = (1.0f - fSlow14);
		float fSlow144 = std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -9.2103405f));
		float fSlow145 = (1.0f / ((fConst0 * fSlow144) + 1.0f));
		float fSlow146 = (100.0f * (1.0f - (float(fEntry42) + 1.0f)));
		float fSlow147 = std::exp((0.0f - (fConst1 / std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f)))));
		float fSlow148 = (1.0f - fSlow147);
		float fSlow149 = (250.0f * (float(fEntry44) + 1.0f));
		float fSlow150 = ((1.0f / ((fConst0 * (fSlow144 * std::exp(((4.60517025f * (float(fEntry45) + 1.0f)) + -4.60517025f)))) + 1.0f)) + -1.0f);
		float fSlow151 = std::exp(((2.30258512f * (float(fEntry46) + 1.0f)) + -2.30258512f));
		float fSlow152 = (100.0f * (1.0f - (float(fEntry47) + 1.0f)));
		float fSlow153 = (0.0f - fSlow152);
		float fSlow154 = ((20.0f * (float(fEntry48) + 1.0f)) + 10.0f);
		float fSlow155 = std::exp(((2.30258512f * (float(fEntry49) + 1.0f)) + -2.30258512f));
		float fSlow156 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry50) + 1.0f)) + -6.90775537f)))));
		float fSlow157 = (1.0f - fSlow156);
		float fSlow158 = (1.0f / fSlow154);
		float fSlow159 = (0.294117659f / fSlow11);
		float fSlow160 = std::exp(((3.45387769f * (float(fEntry51) + 1.0f)) + -2.30258512f));
		float fSlow161 = (0.294117659f / fSlow160);
		float fSlow162 = std::exp(((1.95601153f * (float(fEntry52) + 1.0f)) + -4.60517025f));
		float fSlow163 = (1.0f / ((fConst0 * fSlow162) + 1.0f));
		float fSlow164 = std::exp(((2.30258512f * (float(fEntry53) + 1.0f)) + -2.30258512f));
		float fSlow165 = (fSlow12 / fSlow154);
		float fSlow166 = (1.0f - (1.0f / ((fConst0 * (fSlow162 * std::exp((1.15129256f * (float(fEntry54) + 1.0f))))) + 1.0f)));
		float fSlow167 = (5.0f * fSlow17);
		int iSlow168 = (fSlow167 < 9.0f);
		int iSlow169 = (fSlow167 < 7.0f);
		int iSlow170 = (fSlow167 < 6.0f);
		int iSlow171 = (fSlow167 < 5.0f);
		int iSlow172 = (fSlow167 < 4.0f);
		int iSlow173 = (fSlow167 < 3.0f);
		int iSlow174 = (fSlow167 < 2.0f);
		int iSlow175 = (fSlow167 < 1.0f);
		float fSlow176 = std::pow(10.0f, (0.0500000007f * (iSlow168?((fSlow167 < 8.0f)?(iSlow169?(iSlow170?(iSlow171?(iSlow172?(iSlow173?(iSlow174?(iSlow175?((fSlow167 < 0.0f)?8.36999989f:(iSlow175?(8.36999989f - (29.1499996f * fSlow17)):2.53999996f)):(iSlow174?(2.53999996f - (5.67000008f * (fSlow167 + -1.0f))):-3.13000011f)):(iSlow173?(-3.13000011f - (5.48000002f * (fSlow167 + -2.0f))):-8.60999966f)):(iSlow172?(-8.60999966f - (5.38999987f * (fSlow167 + -3.0f))):-14.0f)):(iSlow171?(-14.0f - (4.4000001f * (fSlow167 + -4.0f))):-18.3999996f)):(iSlow170?(-18.3999996f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow17))))):-20.6000004f)):(iSlow169?(-20.6000004f - (0.600000024f * (fSlow167 + -6.0f))):-21.2000008f)):-21.2000008f):(iSlow168?((0.100000001f * (fSlow167 + -8.0f)) + -21.2000008f):-21.1000004f)):((fSlow167 < 10.0f)?((0.100000001f * (fSlow167 + -9.0f)) + -21.1000004f):-21.0f))));
		float fSlow177 = float(fEntry55);
		float fSlow178 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow177)));
		float fSlow179 = (0.0f - (17.0f * fSlow177));
		int iSlow180 = (fSlow179 > 0.0f);
		float fSlow181 = (fConst19 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow179))));
		float fSlow182 = (iSlow180?fSlow181:fConst19);
		float fSlow183 = ((fConst18 * (fConst18 - fSlow182)) + 1.0f);
		float fSlow184 = float(fEntry56);
		float fSlow185 = (15.0f * fSlow184);
		int iSlow186 = (fSlow185 > 0.0f);
		float fSlow187 = (fConst23 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow185))));
		float fSlow188 = (iSlow186?fSlow187:fConst23);
		float fSlow189 = ((fConst21 * (fConst21 - fSlow188)) + 1.0f);
		float fSlow190 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow184))));
		float fSlow191 = (iSlow186?fConst23:fSlow187);
		float fSlow192 = ((fConst21 * (fConst21 - fSlow191)) + 1.0f);
		float fSlow193 = ((fConst21 * (fConst21 + fSlow191)) + 1.0f);
		float fSlow194 = ((fConst21 * (fConst21 + fSlow188)) + 1.0f);
		float fSlow195 = (0.0f - (10.0f * fSlow177));
		int iSlow196 = (fSlow195 > 0.0f);
		float fSlow197 = (fConst177 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow195))));
		float fSlow198 = (iSlow196?fConst177:fSlow197);
		float fSlow199 = ((fConst176 * (fConst176 - fSlow198)) + 1.0f);
		float fSlow200 = ((fConst176 * (fConst176 + fSlow198)) + 1.0f);
		float fSlow201 = (iSlow196?fSlow197:fConst177);
		float fSlow202 = ((fConst176 * (fConst176 - fSlow201)) + 1.0f);
		float fSlow203 = ((fConst176 * (fConst176 + fSlow201)) + 1.0f);
		float fSlow204 = (iSlow180?fConst19:fSlow181);
		float fSlow205 = ((fConst18 * (fConst18 - fSlow204)) + 1.0f);
		float fSlow206 = ((fConst18 * (fConst18 + fSlow204)) + 1.0f);
		float fSlow207 = ((fConst18 * (fConst18 + fSlow182)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow48 * fTemp0);
			fRec7[0] = ((fSlow46 * fVec0[1]) - (fSlow49 * ((fSlow50 * fRec7[1]) - (fSlow51 * fTemp0))));
			fRec9[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec7[0])) - fRec9[1]))) + (fSlow58 * fRec9[1]));
			fRec8[0] = ((fSlow54 * fRec8[1]) + (fSlow53 * fRec9[0]));
			float fTemp1 = (fSlow42 + (fRec7[0] - fRec8[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) - (2.5f * (fSlow41 - (fSlow40 * (fTemp3 * (std::fabs(fTemp3) + -2.0f))))))) - fSlow60);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (fTemp5 * (std::fabs(fTemp5) + -2.0f));
			float fTemp7 = (0.0f - (fSlow37 + ((fSlow38 * ((fTemp6 * (std::fabs(fTemp6) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp4))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = ((std::fabs(fTemp8) + -2.0f) * fTemp8);
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow36 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)));
			fRec10[0] = ((fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp10 - fSlow67)))) + (fSlow63 * fRec10[1]));
			float fTemp11 = (fSlow62 * fRec10[0]);
			fRec11[0] = ((fSlow71 * fRec11[1]) + (fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp10 - fTemp11) - fSlow67)) - fRec11[1])))));
			float fTemp12 = (fSlow68 * fRec11[0]);
			float fTemp13 = (fSlow33 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow76));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (std::fabs(fTemp14) + -2.0f);
			float fTemp16 = (((std::min<float>(0.0f, fTemp13) + fTemp12) - (fSlow33 * (1.0f - ((fTemp15 * (std::fabs((fTemp15 * fTemp14)) + -2.0f)) * fTemp14)))) - fSlow78);
			fVec1[0] = (fSlow83 * fTemp16);
			fRec15[0] = ((fSlow49 * ((fSlow82 * fTemp16) - (fSlow50 * fRec15[1]))) + (fSlow46 * fVec1[1]));
			fRec17[0] = ((fSlow58 * fRec17[1]) + (fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec15[0])) - fRec17[1]))));
			fRec16[0] = ((fSlow53 * fRec17[0]) + (fSlow54 * fRec16[1]));
			float fTemp17 = (fSlow42 + (fRec15[0] - fRec16[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow41 - (fSlow40 * ((fTemp19 * (std::fabs((fTemp19 * fTemp18)) + -2.0f)) * fTemp18)))))) - fSlow60);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow37 + ((fSlow38 * (((fTemp21 * (std::fabs((fTemp21 * fTemp22)) + -2.0f)) * fTemp22) + 1.0f)) + std::max<float>(0.0f, fTemp20))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = ((std::fabs(fTemp24) + -2.0f) * fTemp24);
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow36 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)));
			fRec18[0] = ((fSlow63 * fRec18[1]) + (fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp26 - fSlow67)))));
			float fTemp27 = (fSlow62 * fRec18[0]);
			fRec14[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp26 - fTemp27) - fSlow67)) - fRec14[1])))) + (fSlow71 * fRec14[1]));
			float fTemp28 = (fSlow68 * fRec14[0]);
			float fTemp29 = (fSlow33 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow76));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (std::fabs(fTemp30) + -2.0f);
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow33 * (1.0f - (((std::fabs((fTemp31 * fTemp30)) + -2.0f) * fTemp31) * fTemp30)))) - fSlow78);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec13[0] = ((fSlow46 * fVec2[1]) - (fSlow49 * ((fSlow50 * fRec13[1]) - (fSlow84 * fTemp32))));
			fRec20[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec13[0])) - fRec20[1]))) + (fSlow58 * fRec20[1]));
			fRec19[0] = ((fSlow53 * fRec20[0]) + (fSlow54 * fRec19[1]));
			float fTemp33 = (fSlow42 + (fRec13[0] - fRec19[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow41 - (fSlow40 * ((fTemp35 * (std::fabs((fTemp35 * fTemp34)) + -2.0f)) * fTemp34)))))) - fSlow60);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = ((std::fabs(fTemp37) + -2.0f) * fTemp37);
			float fTemp39 = (0.0f - (fSlow37 + ((fSlow38 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp36))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (fTemp40 * (std::fabs(fTemp40) + -2.0f));
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow36 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)));
			fRec21[0] = ((fSlow63 * fRec21[1]) + (fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp42 - fSlow67)))));
			float fTemp43 = (fSlow62 * fRec21[0]);
			fRec12[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp42 - fTemp43) - fSlow67)) - fRec12[1])))) - (fSlow85 * fRec12[1]));
			float fTemp44 = (fSlow68 * fRec12[0]);
			float fTemp45 = (fSlow33 + ((fTemp42 - (fTemp44 + fTemp43)) - fSlow76));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (fTemp46 * (std::fabs(fTemp46) + -2.0f));
			float fTemp48 = ((fSlow32 * fTemp16) + (fSlow80 * (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow33 * (1.0f - (fTemp47 * (std::fabs(fTemp47) + -2.0f))))) - fSlow78)));
			fVec3[0] = (fSlow89 * fTemp48);
			fRec23[0] = ((fSlow46 * fVec3[1]) - (fSlow49 * ((fSlow50 * fRec23[1]) - (fSlow90 * fTemp48))));
			fRec25[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec23[0])) - fRec25[1]))) + (fSlow58 * fRec25[1]));
			fRec24[0] = ((fSlow54 * fRec24[1]) + (fSlow53 * fRec25[0]));
			float fTemp49 = (fSlow42 + (fRec23[0] - fRec24[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (std::fabs(fTemp50) + -2.0f);
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow41 - (fSlow40 * (((std::fabs((fTemp50 * fTemp51)) + -2.0f) * fTemp50) * fTemp51)))))) - fSlow60);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (fTemp53 * (std::fabs(fTemp53) + -2.0f));
			float fTemp55 = (0.0f - (fSlow37 + (std::max<float>(0.0f, fTemp52) + (fSlow38 * ((fTemp54 * (std::fabs(fTemp54) + -2.0f)) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow36 * (((fTemp57 * (std::fabs((fTemp57 * fTemp56)) + -2.0f)) * fTemp56) + 1.0f)));
			fRec26[0] = ((fSlow63 * fRec26[1]) + (fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp58 - fSlow67)))));
			float fTemp59 = (fSlow62 * fRec26[0]);
			fRec27[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp58 - fTemp59) - fSlow67)) - fRec27[1])))) + (fSlow71 * fRec27[1]));
			float fTemp60 = (fSlow68 * fRec27[0]);
			float fTemp61 = (fSlow33 + ((fTemp58 - (fTemp59 + fTemp60)) - fSlow76));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (std::fabs(fTemp62) + -2.0f);
			float fTemp64 = (((std::min<float>(0.0f, fTemp61) + fTemp60) - (fSlow33 * (1.0f - (((std::fabs((fTemp63 * fTemp62)) + -2.0f) * fTemp63) * fTemp62)))) - fSlow78);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec22[0] = ((fSlow46 * fVec4[1]) - (fSlow49 * ((fSlow50 * fRec22[1]) - (fSlow84 * fTemp64))));
			fRec29[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec22[0])) - fRec29[1]))) - (fSlow91 * fRec29[1]));
			fRec28[0] = ((fSlow53 * fRec29[0]) + (fSlow54 * fRec28[1]));
			float fTemp65 = (fSlow42 + (fRec22[0] - fRec28[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow41 - (fSlow40 * ((fTemp67 * (std::fabs((fTemp67 * fTemp66)) + -2.0f)) * fTemp66)))))) - fSlow60);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow37 + (std::max<float>(0.0f, fTemp68) + (fSlow38 * (((fTemp70 * (std::fabs((fTemp70 * fTemp69)) + -2.0f)) * fTemp69) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (std::fabs(fTemp72) + -2.0f);
			float fTemp74 = (std::max<float>(0.0f, fTemp71) + (fSlow36 * ((((std::fabs((fTemp73 * fTemp72)) + -2.0f) * fTemp73) * fTemp72) + 1.0f)));
			fRec30[0] = ((fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp74 - fSlow67)))) + (fSlow63 * fRec30[1]));
			float fTemp75 = (fSlow62 * fRec30[0]);
			fRec31[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp74 - fTemp75) - fSlow67)) - fRec31[1])))) + (fSlow71 * fRec31[1]));
			float fTemp76 = (fSlow68 * fRec31[0]);
			float fTemp77 = (fSlow33 + ((fTemp74 - (fTemp75 + fTemp76)) - fSlow76));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = ((fSlow30 * fTemp48) + (fSlow88 * (((std::min<float>(0.0f, fTemp77) + fTemp76) - (fSlow33 * (1.0f - ((fTemp78 * (std::fabs((fTemp78 * fTemp79)) + -2.0f)) * fTemp79)))) - fSlow78)));
			fVec5[0] = (fSlow94 * fTemp80);
			fRec34[0] = ((fSlow46 * fVec5[1]) - (fSlow49 * ((fSlow50 * fRec34[1]) - (fSlow95 * fTemp80))));
			fRec36[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec34[0])) - fRec36[1]))) + (fSlow58 * fRec36[1]));
			fRec35[0] = ((fSlow54 * fRec35[1]) + (fSlow53 * fRec36[0]));
			float fTemp81 = (fSlow42 + (fRec34[0] - fRec35[0]));
			float fTemp82 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp81))));
			float fTemp83 = (fTemp82 * (std::fabs(fTemp82) + -2.0f));
			float fTemp84 = ((fSlow2 * (std::min<float>(0.0f, fTemp81) - (2.5f * (fSlow41 - (fSlow40 * (fTemp83 * (std::fabs(fTemp83) + -2.0f))))))) - fSlow60);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp84))));
			float fTemp86 = (std::fabs(fTemp85) + -2.0f);
			float fTemp87 = (0.0f - (fSlow37 + (std::max<float>(0.0f, fTemp84) + (fSlow38 * ((((std::fabs((fTemp85 * fTemp86)) + -2.0f) * fTemp85) * fTemp86) + 1.0f)))));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = (std::fabs(fTemp88) + -2.0f);
			float fTemp90 = (std::max<float>(0.0f, fTemp87) + (fSlow36 * ((((std::fabs((fTemp89 * fTemp88)) + -2.0f) * fTemp89) * fTemp88) + 1.0f)));
			fRec37[0] = ((fSlow63 * fRec37[1]) + (fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp90 - fSlow67)))));
			float fTemp91 = (fSlow62 * fRec37[0]);
			fRec33[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp90 - fTemp91) - fSlow67)) - fRec33[1])))) + (fSlow71 * fRec33[1]));
			float fTemp92 = (fSlow68 * fRec33[0]);
			float fTemp93 = (fSlow33 + ((fTemp90 - (fTemp91 + fTemp92)) - fSlow76));
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = (std::fabs(fTemp94) + -2.0f);
			float fTemp96 = (((fTemp92 + std::min<float>(0.0f, fTemp93)) - (fSlow33 * (1.0f - (((std::fabs((fTemp94 * fTemp95)) + -2.0f) * fTemp94) * fTemp95)))) - fSlow78);
			fVec6[0] = (fSlow3 * fTemp96);
			fRec32[0] = ((fSlow46 * fVec6[1]) - (fSlow49 * ((fSlow50 * fRec32[1]) - (fSlow84 * fTemp96))));
			fRec39[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + fRec32[0])) - fRec39[1]))) + (fSlow58 * fRec39[1]));
			fRec38[0] = ((fSlow54 * fRec38[1]) + (fSlow53 * fRec39[0]));
			float fTemp97 = (fSlow42 + (fRec32[0] - fRec38[0]));
			float fTemp98 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::max<float>(0.0f, fTemp97))));
			float fTemp99 = (std::fabs(fTemp98) + -2.0f);
			float fTemp100 = ((fSlow2 * (std::min<float>(0.0f, fTemp97) - (2.5f * (fSlow41 - (fSlow40 * (((std::fabs((fTemp98 * fTemp99)) + -2.0f) * fTemp98) * fTemp99)))))) - fSlow60);
			float fTemp101 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow39 * std::min<float>(0.0f, fTemp100))));
			float fTemp102 = (std::fabs(fTemp101) + -2.0f);
			float fTemp103 = (0.0f - (fSlow37 + ((fSlow38 * (((fTemp102 * (std::fabs((fTemp102 * fTemp101)) + -2.0f)) * fTemp101) + 1.0f)) + std::max<float>(0.0f, fTemp100))));
			float fTemp104 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow61 * std::min<float>(0.0f, fTemp103))));
			float fTemp105 = (std::fabs(fTemp104) + -2.0f);
			float fTemp106 = (std::max<float>(0.0f, fTemp103) + (fSlow36 * (((fTemp104 * (std::fabs((fTemp104 * fTemp105)) + -2.0f)) * fTemp105) + 1.0f)));
			fRec40[0] = ((fSlow63 * fRec40[1]) + (fSlow64 * (fSlow65 + std::max<float>(fSlow66, (fTemp106 - fSlow67)))));
			float fTemp107 = (fSlow62 * fRec40[0]);
			fRec41[0] = ((fSlow72 * std::max<float>(0.0f, (fSlow73 + (std::max<float>(fSlow74, ((fTemp106 - fTemp107) - fSlow67)) - fRec41[1])))) + (fSlow71 * fRec41[1]));
			float fTemp108 = (fSlow68 * fRec41[0]);
			float fTemp109 = (fSlow33 + ((fTemp106 - (fTemp107 + fTemp108)) - fSlow76));
			float fTemp110 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow77 * std::max<float>(0.0f, fTemp109))));
			float fTemp111 = (fTemp110 * (std::fabs(fTemp110) + -2.0f));
			float fTemp112 = (((fSlow28 * fTemp80) + (fSlow93 * (((std::min<float>(0.0f, fTemp109) + fTemp108) - (fSlow33 * (1.0f - (fTemp111 * (std::fabs(fTemp111) + -2.0f))))) - fSlow78))) * fSlow106);
			float fTemp113 = (fSlow3 * fTemp112);
			fVec7[0] = fTemp113;
			fRec6[0] = ((fSlow25 * fVec7[1]) - (fSlow107 * ((fSlow108 * fRec6[1]) - (fSlow109 * fTemp112))));
			fRec42[0] = (0.0f - (fSlow107 * ((fSlow108 * fRec42[1]) - (fVec7[1] + fTemp113))));
			float fTemp114 = (fRec6[0] + (fSlow110 * fRec42[0]));
			fVec8[0] = fTemp114;
			fRec5[0] = ((fConst6 * fVec8[1]) - (fConst7 * ((fConst8 * fRec5[1]) - (fConst4 * fTemp114))));
			float fTemp115 = (fConst12 * fRec4[1]);
			fRec4[0] = (fRec5[0] - (((fSlow118 * fRec4[2]) + fTemp115) / fSlow119));
			float fTemp116 = (((fRec4[0] * fSlow121) + fTemp115) + (fSlow122 * fRec4[2]));
			float fTemp117 = (fTemp116 / fSlow119);
			fVec9[0] = fTemp117;
			fRec3[0] = (((fTemp117 + fVec9[1]) - (fSlow127 * fRec3[1])) / fSlow128);
			fRec43[0] = ((fVec9[1] * fSlow129) - (((fSlow127 * fRec43[1]) - (fTemp116 / fSlow130)) / fSlow128));
			float fTemp118 = (fConst16 * fRec2[1]);
			fRec2[0] = ((fRec3[0] + (fRec43[0] * fSlow131)) - (((fRec2[2] * fSlow136) + fTemp118) / fSlow137));
			float fTemp119 = ((fSlow18 * ((((fRec2[0] * fSlow139) + fTemp118) + (fRec2[2] * fSlow140)) / fSlow137)) - fSlow141);
			fVec10[0] = fTemp119;
			fRec1[0] = ((fSlow16 * fVec10[1]) - (fSlow142 * ((fSlow143 * fRec1[1]) - (fSlow14 * fTemp119))));
			fRec45[0] = ((fSlow147 * fRec45[1]) + (fSlow148 * (fRec1[0] - fSlow149)));
			fRec44[0] = ((fSlow145 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow146 + ((fRec1[0] - fRec45[0]) - fSlow149))) - fRec44[1]))) - (fSlow150 * fRec44[1]));
			float fTemp120 = ((fRec1[0] - (fRec44[0] + fRec45[0])) - fSlow149);
			float fTemp121 = (fSlow12 * fTemp120);
			fRec46[0] = ((fSlow5 * fRec46[1]) + (fSlow6 * (fSlow152 + std::max<float>(fSlow153, fTemp121))));
			float fTemp122 = (fSlow151 * fRec46[0]);
			fRec47[0] = ((fSlow156 * fRec47[1]) + (fSlow157 * std::min<float>(1.0f, std::fabs((fSlow158 * (fTemp121 - fTemp122))))));
			float fTemp123 = (fSlow154 / ((fSlow155 * fRec47[0]) + 1.0f));
			float fTemp124 = (fSlow11 + (fTemp121 - (fTemp122 + fTemp123)));
			float fTemp125 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow159 * std::max<float>(0.0f, fTemp124))));
			float fTemp126 = (fTemp125 * (std::fabs(fTemp125) + -2.0f));
			float fTemp127 = (((std::min<float>(0.0f, fTemp124) + fTemp123) - (fSlow11 * (1.0f - (fTemp126 * (std::fabs(fTemp126) + -2.0f))))) - fSlow160);
			fRec49[0] = ((fSlow6 * (fSlow152 + std::max<float>(fSlow153, (0.0f - fTemp121)))) + (fSlow5 * fRec49[1]));
			float fTemp128 = (fTemp121 + (fSlow151 * fRec49[0]));
			fRec48[0] = ((fSlow156 * fRec48[1]) + (fSlow157 * std::min<float>(1.0f, std::fabs((fSlow158 * (0.0f - fTemp128))))));
			float fTemp129 = (fSlow154 / ((fSlow155 * fRec48[0]) + 1.0f));
			float fTemp130 = (fSlow11 - (fTemp128 + fTemp129));
			float fTemp131 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow159 * std::max<float>(0.0f, fTemp130))));
			float fTemp132 = (std::fabs(fTemp131) + -2.0f);
			float fTemp133 = (((fTemp129 + std::min<float>(0.0f, fTemp130)) - (fSlow11 * (1.0f - (((std::fabs((fTemp131 * fTemp132)) + -2.0f) * fTemp131) * fTemp132)))) - fSlow160);
			float fTemp134 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow161 * std::min<float>(0.0f, fTemp133))));
			float fTemp135 = ((std::fabs(fTemp134) + -2.0f) * fTemp134);
			float fTemp136 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow161 * std::min<float>(0.0f, fTemp127))));
			float fTemp137 = (std::fabs(fTemp136) + -2.0f);
			float fTemp138 = std::fabs((fSlow165 * fTemp120));
			fRec50[0] = ((fSlow163 * std::max<float>(0.0f, (((fSlow164 * std::min<float>(1.0f, fTemp138)) + std::max<float>(1.0f, fTemp138)) + (-1.0f - fRec50[1])))) + (fSlow166 * fRec50[1]));
			float fTemp139 = (fSlow10 * ((std::max<float>(0.0f, fTemp127) - (std::max<float>(0.0f, fTemp133) + (fSlow160 * (((fTemp135 * (std::fabs(fTemp135) + -2.0f)) + 1.0f) - ((((std::fabs((fTemp137 * fTemp136)) + -2.0f) * fTemp137) * fTemp136) + 1.0f))))) / ((fSlow9 * fRec50[0]) + 1.0f)));
			fRec0[0] = ((fSlow6 * (fSlow7 + std::max<float>(fSlow8, std::fabs(fTemp139)))) + (fSlow5 * fRec0[1]));
			float fTemp140 = (fSlow3 * (((fSlow4 * fRec0[0]) + fTemp139) * fSlow176));
			fRec73[0] = (fTemp140 - (fConst115 * ((fConst116 * fRec73[1]) + (fConst117 * fRec73[2]))));
			fRec72[0] = ((fConst115 * (((fConst114 * fRec73[0]) + (fConst118 * fRec73[1])) + (fConst114 * fRec73[2]))) - (fConst112 * ((fConst116 * fRec72[1]) + (fConst119 * fRec72[2]))));
			float fTemp141 = (((fConst114 * fRec72[0]) + (fConst118 * fRec72[1])) + (fConst114 * fRec72[2]));
			fVec11[0] = fTemp141;
			fRec71[0] = (0.0f - (fConst108 * ((fConst109 * fRec71[1]) - (fConst112 * (fTemp141 + fVec11[1])))));
			fRec70[0] = (fRec71[0] - (fConst105 * ((fConst120 * fRec70[1]) + (fConst121 * fRec70[2]))));
			float fTemp142 = ((fRec70[0] + (2.0f * fRec70[1])) + fRec70[2]);
			fVec12[0] = fTemp142;
			fRec69[0] = ((fConst105 * ((fConst107 * fTemp142) + (fConst122 * fVec12[1]))) - (fConst124 * fRec69[1]));
			fRec68[0] = (fRec69[0] - (fConst102 * ((fConst125 * fRec68[2]) + (fConst126 * fRec68[1]))));
			fRec67[0] = ((fConst102 * (((fConst99 * fRec68[0]) + (fConst101 * fRec68[1])) + (fConst99 * fRec68[2]))) - (fConst100 * ((fConst126 * fRec67[1]) + (fConst127 * fRec67[2]))));
			fRec66[0] = ((fConst100 * (((fConst101 * fRec67[1]) + (fConst99 * fRec67[0])) + (fConst99 * fRec67[2]))) - (fConst97 * ((fConst126 * fRec66[1]) + (fConst128 * fRec66[2]))));
			fRec77[0] = (0.0f - (fConst129 * ((fConst123 * fRec77[1]) - (fConst105 * (fVec12[1] + fTemp142)))));
			fRec76[0] = (fRec77[0] - (fConst102 * ((fConst126 * fRec76[1]) + (fConst125 * fRec76[2]))));
			fRec75[0] = ((fConst102 * (fRec76[2] + (fRec76[0] + (2.0f * fRec76[1])))) - (fConst100 * ((fConst127 * fRec75[2]) + (fConst126 * fRec75[1]))));
			fRec74[0] = ((fConst100 * (fRec75[2] + (fRec75[0] + (2.0f * fRec75[1])))) - (fConst97 * ((fConst128 * fRec74[2]) + (fConst126 * fRec74[1]))));
			float fTemp143 = (fConst94 * fRec65[1]);
			fRec65[0] = ((fConst97 * ((0.0316227749f * (((fConst99 * fRec66[0]) + (fConst101 * fRec66[1])) + (fConst99 * fRec66[2]))) + (fRec74[2] + (fRec74[0] + (2.0f * fRec74[1]))))) - (fConst93 * ((fConst130 * fRec65[2]) + fTemp143)));
			float fTemp144 = (fConst88 * fRec64[1]);
			fRec64[0] = ((fConst93 * ((fTemp143 + (fConst132 * fRec65[0])) + (fConst133 * fRec65[2]))) - (fConst87 * (fTemp144 + (fConst134 * fRec64[2]))));
			float fTemp145 = (fConst138 * fRec63[1]);
			fRec63[0] = ((fConst87 * ((fTemp144 + (fConst136 * fRec64[0])) + (fConst137 * fRec64[2]))) - (fConst80 * (fTemp145 + (fConst139 * fRec63[2]))));
			float fTemp146 = (fConst75 * fRec62[1]);
			fRec62[0] = ((fConst80 * (((fConst82 * fRec63[0]) + fTemp145) + (fConst140 * fRec63[2]))) - (fConst74 * ((fConst141 * fRec62[2]) + fTemp146)));
			float fTemp147 = (fConst68 * fRec61[1]);
			fRec61[0] = ((fConst74 * ((fTemp146 + (fConst143 * fRec62[0])) + (fConst144 * fRec62[2]))) - (fConst67 * (fTemp147 + (fConst145 * fRec61[2]))));
			float fTemp148 = (fConst62 * fRec60[1]);
			fRec60[0] = ((fConst67 * ((fTemp147 + (fConst147 * fRec61[0])) + (fConst148 * fRec61[2]))) - (fConst61 * (fTemp148 + (fConst149 * fRec60[2]))));
			float fTemp149 = (fConst56 * fRec59[1]);
			fRec59[0] = ((fConst61 * ((fTemp148 + (fConst151 * fRec60[0])) + (fConst152 * fRec60[2]))) - (fConst55 * ((fConst153 * fRec59[2]) + fTemp149)));
			float fTemp150 = (fConst157 * fRec58[1]);
			fRec58[0] = ((fConst55 * ((fTemp149 + (fConst155 * fRec59[0])) + (fConst156 * fRec59[2]))) - (fConst48 * (fTemp150 + (fConst158 * fRec58[2]))));
			float fTemp151 = (fConst43 * fRec57[1]);
			fRec57[0] = ((fConst48 * (((fConst50 * fRec58[0]) + fTemp150) + (fConst159 * fRec58[2]))) - (fConst42 * ((fConst160 * fRec57[2]) + fTemp151)));
			float fTemp152 = (fConst37 * fRec56[1]);
			fRec56[0] = ((fConst42 * ((fTemp151 + (fConst162 * fRec57[0])) + (fConst163 * fRec57[2]))) - (fConst33 * ((fConst164 * fRec56[2]) + fTemp152)));
			float fTemp153 = ((fTemp152 + (fConst166 * fRec56[0])) + (fConst167 * fRec56[2]));
			fVec13[0] = fTemp153;
			fRec55[0] = ((fConst33 * ((fConst36 * fVec13[1]) + (fConst35 * fTemp153))) - (fConst169 * fRec55[1]));
			fRec54[0] = (fRec55[0] - (fConst26 * ((fConst170 * fRec54[2]) + (fConst171 * fRec54[1]))));
			fRec79[0] = (fConst173 * ((fConst33 * (fTemp153 + fVec13[1])) - (fConst168 * fRec79[1])));
			fRec78[0] = (fRec79[0] - (fConst26 * ((fConst170 * fRec78[2]) + (fConst171 * fRec78[1]))));
			float fTemp154 = (fConst174 * fRec53[1]);
			fRec53[0] = ((fConst26 * (((fConst28 * fRec54[2]) + ((fConst28 * fRec54[0]) + (fConst172 * fRec54[1]))) + (fSlow190 * (fRec78[2] + (fRec78[0] + (2.0f * fRec78[1])))))) - ((fTemp154 + (fSlow192 * fRec53[2])) / fSlow193));
			float fTemp155 = (fConst178 * fRec52[1]);
			fRec52[0] = ((((fSlow189 * fRec53[2]) + (fTemp154 + (fRec53[0] * fSlow194))) / fSlow193) - (((fRec52[2] * fSlow199) + fTemp155) / fSlow200));
			float fTemp156 = (fConst179 * fRec51[1]);
			fRec51[0] = ((((fRec52[2] * fSlow202) + (fTemp155 + (fRec52[0] * fSlow203))) / fSlow200) - ((fTemp156 + (fRec51[2] * fSlow205)) / fSlow206));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow178 * (((fSlow183 * fRec51[2]) + ((fRec51[0] * fSlow207) + fTemp156)) / fSlow206)):fTemp140)));
			fVec0[1] = fVec0[0];
			fRec7[1] = fRec7[0];
			fRec9[1] = fRec9[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec11[1] = fRec11[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fRec14[1] = fRec14[0];
			fVec2[1] = fVec2[0];
			fRec13[1] = fRec13[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec12[1] = fRec12[0];
			fVec3[1] = fVec3[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fVec4[1] = fVec4[0];
			fRec22[1] = fRec22[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fVec5[1] = fVec5[0];
			fRec34[1] = fRec34[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec33[1] = fRec33[0];
			fVec6[1] = fVec6[0];
			fRec32[1] = fRec32[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec40[1] = fRec40[0];
			fRec41[1] = fRec41[0];
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
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec50[1] = fRec50[0];
			fRec0[1] = fRec0[0];
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
