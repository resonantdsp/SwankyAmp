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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	float fConst2;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
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
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fVec0[2];
	float fRec14[2];
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	float fRec16[2];
	float fRec15[2];
	FAUSTFLOAT fEntry36;
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	float fRec17[2];
	float fRec18[2];
	float fVec1[2];
	float fRec13[2];
	float fRec20[2];
	float fRec19[2];
	float fRec22[2];
	float fRec21[2];
	float fVec2[2];
	float fRec12[2];
	float fRec24[2];
	float fRec23[2];
	float fRec25[2];
	float fRec11[2];
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
	float fRec35[2];
	float fVec5[2];
	float fRec10[2];
	float fRec37[2];
	float fRec36[2];
	float fRec38[2];
	float fRec9[2];
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
	float fConst11;
	FAUSTFLOAT fEntry40;
	float fConst12;
	float fRec4[3];
	float fVec9[2];
	float fRec3[2];
	float fRec43[2];
	FAUSTFLOAT fEntry41;
	float fVec10[2];
	float fRec2[2];
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	float fRec44[2];
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	float fRec45[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec46[2];
	float fRec1[2];
	FAUSTFLOAT fEntry49;
	FAUSTFLOAT fEntry50;
	float fRec48[2];
	float fRec47[2];
	FAUSTFLOAT fEntry51;
	FAUSTFLOAT fEntry52;
	FAUSTFLOAT fEntry53;
	float fRec49[2];
	float fRec0[2];
	FAUSTFLOAT fEntry54;
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
	float fRec72[3];
	float fConst116;
	float fRec71[3];
	float fVec11[2];
	float fRec70[2];
	float fConst117;
	float fConst118;
	float fRec69[3];
	float fVec12[2];
	float fConst119;
	float fRec68[2];
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fRec67[3];
	float fConst124;
	float fRec66[3];
	float fConst125;
	float fRec65[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec76[2];
	float fRec75[3];
	float fRec74[3];
	float fRec73[3];
	float fConst130;
	float fConst131;
	float fRec64[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec63[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec62[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec61[3];
	float fConst141;
	float fConst142;
	float fRec60[3];
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec59[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec58[3];
	float fConst151;
	float fConst152;
	float fRec57[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fConst157;
	float fRec56[3];
	float fConst158;
	float fConst159;
	float fConst160;
	float fRec55[3];
	float fConst161;
	float fVec13[2];
	float fConst162;
	float fConst163;
	float fRec54[2];
	float fConst164;
	float fConst165;
	float fRec53[3];
	float fConst166;
	FAUSTFLOAT fEntry55;
	float fConst167;
	float fRec78[2];
	float fRec77[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec52[3];
	float fConst172;
	float fConst173;
	float fRec51[3];
	float fConst174;
	float fConst175;
	float fRec50[3];

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
		fConst10 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst11 = (1.0f / fConst9);
		fConst12 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst13 = std::tan((3769.91113f / fConst0));
		fConst14 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst15 = std::tan((219.911484f / fConst0));
		fConst16 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst15))));
		fConst17 = std::tan((3455.75195f / fConst0));
		fConst18 = (1.0f / fConst17);
		fConst19 = (1.0f / (((fConst18 + 1.0f) / fConst17) + 1.0f));
		fConst20 = AmpMono_faustpower2_f(fConst17);
		fConst21 = (1.0f / fConst20);
		fConst22 = std::tan((2984.51294f / fConst0));
		fConst23 = (1.0f / fConst22);
		fConst24 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst25 = (27816.8476f / fConst24);
		fConst26 = (1.0f / (((fConst23 + fConst25) / fConst22) + 1.0f));
		fConst27 = (fConst18 + 1.0f);
		fConst28 = (1.0f / (fConst17 * fConst27));
		fConst29 = (0.0f - fConst28);
		fConst30 = (8796.45898f / fConst24);
		fConst31 = (((fConst23 + fConst30) / fConst22) + 1.0f);
		fConst32 = (37699.1133f / fConst0);
		fConst33 = std::tan(fConst32);
		fConst34 = (1.0f / fConst33);
		fConst35 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst36 = (24836.4707f / fConst35);
		fConst37 = (1.0f / (((fConst34 + fConst36) / fConst33) + 1.0f));
		fConst38 = (785.398193f / fConst35);
		fConst39 = (((fConst34 - fConst38) / fConst33) + 1.0f);
		fConst40 = std::tan((21362.8301f / fConst0));
		fConst41 = (1.0f / fConst40);
		fConst42 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst43 = (19869.1758f / fConst42);
		fConst44 = (1.0f / (((fConst41 + fConst43) / fConst40) + 1.0f));
		fConst45 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst40))));
		fConst46 = std::tan((11938.0518f / fConst0));
		fConst47 = (1.0f / fConst46);
		fConst48 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst49 = (4701.22607f / fConst48);
		fConst50 = (1.0f / (((fConst47 + fConst49) / fConst46) + 1.0f));
		fConst51 = (2356.19458f / fConst48);
		fConst52 = (((fConst47 + fConst51) / fConst46) + 1.0f);
		fConst53 = std::tan((9581.85742f / fConst0));
		fConst54 = (1.0f / fConst53);
		fConst55 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst56 = (2921.88965f / fConst55);
		fConst57 = (1.0f / (((fConst54 + fConst56) / fConst53) + 1.0f));
		fConst58 = (1036.72558f / fConst55);
		fConst59 = (((fConst54 - fConst58) / fConst53) + 1.0f);
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
		fConst72 = (1416.67383f / fConst69);
		fConst73 = (((fConst68 - fConst72) / fConst67) + 1.0f);
		fConst74 = std::tan((3518.58374f / fConst0));
		fConst75 = (1.0f / fConst74);
		fConst76 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst77 = (875.483398f / fConst76);
		fConst78 = (1.0f / (((fConst75 + fConst77) / fConst74) + 1.0f));
		fConst79 = (219.911484f / fConst76);
		fConst80 = (((fConst75 - fConst79) / fConst74) + 1.0f);
		fConst81 = std::tan((2010.61926f / fConst0));
		fConst82 = (1.0f / fConst81);
		fConst83 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst84 = (439.822968f / fConst83);
		fConst85 = (1.0f / (((fConst82 + fConst84) / fConst81) + 1.0f));
		fConst86 = (1390.84241f / fConst83);
		fConst87 = (((fConst82 + fConst86) / fConst81) + 1.0f);
		fConst88 = std::tan((1853.53967f / fConst0));
		fConst89 = (1.0f / fConst88);
		fConst90 = (fConst0 * std::sin(fConst66));
		fConst91 = (1059.9884f / fConst90);
		fConst92 = (1.0f / (((fConst89 + fConst91) / fConst88) + 1.0f));
		fConst93 = (188.49556f / fConst90);
		fConst94 = (((fConst89 - fConst93) / fConst88) + 1.0f);
		fConst95 = std::tan((17592.918f / fConst0));
		fConst96 = (1.0f / fConst95);
		fConst97 = (1.0f / (((fConst96 + 0.445041865f) / fConst95) + 1.0f));
		fConst98 = (1.0f / (((fConst96 + 1.24697959f) / fConst95) + 1.0f));
		fConst99 = (1.0f / (((fConst96 + 1.8019377f) / fConst95) + 1.0f));
		fConst100 = (fConst96 + 1.0f);
		fConst101 = (1.0f / fConst100);
		fConst102 = std::tan((34557.5195f / fConst0));
		fConst103 = (1.0f / fConst102);
		fConst104 = (1.0f / (((fConst103 + 1.0f) / fConst102) + 1.0f));
		fConst105 = (1.0f / (fConst103 + 1.0f));
		fConst106 = (1.0f - fConst103);
		fConst107 = std::tan((345.575195f / fConst0));
		fConst108 = (1.0f / fConst107);
		fConst109 = (1.0f / (((fConst108 + 0.765366852f) / fConst107) + 1.0f));
		fConst110 = AmpMono_faustpower2_f(fConst107);
		fConst111 = (0.0f - (2.0f / fConst110));
		fConst112 = (1.0f / (((fConst108 + 1.84775901f) / fConst107) + 1.0f));
		fConst113 = (1.0f / fConst110);
		fConst114 = (2.0f * (1.0f - fConst113));
		fConst115 = (((fConst108 + -1.84775901f) / fConst107) + 1.0f);
		fConst116 = (((fConst108 + -0.765366852f) / fConst107) + 1.0f);
		fConst117 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst102))));
		fConst118 = (((fConst103 + -1.0f) / fConst102) + 1.0f);
		fConst119 = (1.0f - fConst96);
		fConst120 = AmpMono_faustpower2_f(fConst95);
		fConst121 = (1.0f / fConst120);
		fConst122 = (2.0f * (1.0f - fConst121));
		fConst123 = (((fConst96 + -1.8019377f) / fConst95) + 1.0f);
		fConst124 = (((fConst96 + -1.24697959f) / fConst95) + 1.0f);
		fConst125 = (((fConst96 + -0.445041865f) / fConst95) + 1.0f);
		fConst126 = (0.0f - (2.0f / fConst120));
		fConst127 = (1.0f / (fConst95 * fConst100));
		fConst128 = (0.0f - fConst127);
		fConst129 = (fConst119 / fConst100);
		fConst130 = (((fConst89 - fConst91) / fConst88) + 1.0f);
		fConst131 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst88))));
		fConst132 = (((fConst89 + fConst93) / fConst88) + 1.0f);
		fConst133 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst81))));
		fConst134 = (((fConst82 - fConst84) / fConst81) + 1.0f);
		fConst135 = (((fConst82 - fConst86) / fConst81) + 1.0f);
		fConst136 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst74))));
		fConst137 = (((fConst75 - fConst77) / fConst74) + 1.0f);
		fConst138 = (((fConst75 + fConst79) / fConst74) + 1.0f);
		fConst139 = (((fConst68 - fConst70) / fConst67) + 1.0f);
		fConst140 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst67))));
		fConst141 = (((fConst68 + fConst72) / fConst67) + 1.0f);
		fConst142 = (((fConst61 - fConst63) / fConst60) + 1.0f);
		fConst143 = (2481.85815f / fConst62);
		fConst144 = (((fConst61 + fConst143) / fConst60) + 1.0f);
		fConst145 = (((fConst61 - fConst143) / fConst60) + 1.0f);
		fConst146 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst53))));
		fConst147 = (((fConst54 - fConst56) / fConst53) + 1.0f);
		fConst148 = (((fConst54 + fConst58) / fConst53) + 1.0f);
		fConst149 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst46))));
		fConst150 = (((fConst47 - fConst49) / fConst46) + 1.0f);
		fConst151 = (((fConst47 - fConst51) / fConst46) + 1.0f);
		fConst152 = (((fConst41 - fConst43) / fConst40) + 1.0f);
		fConst153 = (628.318542f / fConst42);
		fConst154 = (((fConst41 + fConst153) / fConst40) + 1.0f);
		fConst155 = (((fConst41 - fConst153) / fConst40) + 1.0f);
		fConst156 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst33))));
		fConst157 = (((fConst34 - fConst36) / fConst33) + 1.0f);
		fConst158 = (((fConst34 + fConst38) / fConst33) + 1.0f);
		fConst159 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst22))));
		fConst160 = (((fConst23 - fConst25) / fConst22) + 1.0f);
		fConst161 = (((fConst23 - fConst30) / fConst22) + 1.0f);
		fConst162 = (1.0f - fConst18);
		fConst163 = (fConst162 / fConst27);
		fConst164 = (((fConst18 + -1.0f) / fConst17) + 1.0f);
		fConst165 = (2.0f * (1.0f - fConst21));
		fConst166 = (0.0f - (2.0f / fConst20));
		fConst167 = (1.0f / fConst27);
		fConst168 = std::tan((18849.5566f / fConst0));
		fConst169 = (1.0f / fConst168);
		fConst170 = (3141.59277f / (fConst0 * std::sin(fConst32)));
		fConst171 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst168))));
		fConst172 = (1.0f / fConst15);
		fConst173 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst174 = (1.0f / fConst13);
		fConst175 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));

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

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec14[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec16[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec15[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec17[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec18[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec13[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec20[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec19[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec22[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec21[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec12[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec24[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec23[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec25[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;

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
			fRec35[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec10[l31] = 0.0f;

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
			fRec9[l35] = 0.0f;

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
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec9[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec3[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec43[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec10[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec2[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec44[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec45[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec46[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec1[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec48[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec47[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec49[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec0[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec72[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec71[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fVec11[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec70[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec69[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fVec12[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fRec68[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec67[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec66[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec65[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec76[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec75[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec74[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec73[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec64[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec63[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec62[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec61[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec60[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec59[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec58[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec57[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec56[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec55[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fVec13[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 2); l86 = (l86 + 1)) {
			fRec54[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec53[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec78[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec77[l89] = 0.0f;

		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec52[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec51[l91] = 0.0f;

		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec50[l92] = 0.0f;

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

	void set_cab_brightness(FAUSTFLOAT value) { fEntry55 = value + 0.000000e+00f; }
	void set_cab_distance(FAUSTFLOAT value) { fEntry54 = value + 0.000000e+00f; }
	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry17 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry16 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry30 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry31 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry45 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry41 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry43 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry46 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry44 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry42 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry12 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry8 = value + 3.866967e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry49 = value + 1.049631e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry9 = value + -6.951565e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry10 = value + -1.091596e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry50 = value + 5.941641e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry3 = value + -2.019639e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry5 = value + 5.374066e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry47 = value + 1.512931e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry48 = value + 8.753486e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry4 = value + -2.094365e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry52 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry53 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry51 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry6 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry11 = value + 3.147941e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry26 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry25 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry35 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry34 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry32 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry33 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry27 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry23 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry36 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry24 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry29 = value + -1.719012e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry18 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry21 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry28 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry19 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry20 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry22 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry37 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry39 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry38 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry15 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry40 = value + 0.000000e+00f; }
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
		float fSlow11 = ((20.0f * (float(fEntry8) + 1.0f)) + 10.0f);
		float fSlow12 = std::exp(((2.30258512f * (float(fEntry9) + 1.0f)) + -2.30258512f));
		float fSlow13 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry10) + 1.0f)) + -6.90775537f)))));
		float fSlow14 = (1.0f - fSlow13);
		float fSlow15 = (1.0f / fSlow11);
		float fSlow16 = std::exp(((4.60517025f * (float(fEntry11) + 1.0f)) + -4.60517025f));
		float fSlow17 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry12) + 1.0f)) + -2.30258512f))));
		float fSlow18 = (1.0f / fSlow17);
		float fSlow19 = (fSlow18 + 1.0f);
		float fSlow20 = (0.0f - (1.0f / (fSlow17 * fSlow19)));
		float fSlow21 = (float(fEntry13) + 1.0f);
		float fSlow22 = (fSlow2 * std::exp((3.45387769f * fSlow21)));
		float fSlow23 = float(fEntry14);
		int iSlow24 = (fSlow23 < 0.0f);
		float fSlow25 = std::tan((fConst2 * ((iSlow24?(1500.0f * fSlow23):0.0f) + 2000.0f)));
		float fSlow26 = (1.0f / fSlow25);
		float fSlow27 = (1.0f - fSlow26);
		float fSlow28 = float(fEntry15);
		float fSlow29 = (fSlow28 + 1.0f);
		float fSlow30 = (1.0f - (0.5f * fSlow29));
		float fSlow31 = std::tan((fConst2 * ((400.0f * fSlow30) + (25.0f * fSlow29))));
		float fSlow32 = (1.0f / fSlow31);
		float fSlow33 = (fSlow32 + 1.0f);
		float fSlow34 = (0.0f - (1.0f / (fSlow31 * fSlow33)));
		float fSlow35 = float(fEntry16);
		float fSlow36 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow35) + -5.0f));
		float fSlow37 = ((float(fEntry17) + 1.0f) + 1.0f);
		float fSlow38 = (0.5f * fSlow37);
		float fSlow39 = AmpMono_faustpower3_f(fSlow38);
		float fSlow40 = (0.5f * (fSlow36 / fSlow39));
		float fSlow41 = std::exp(((2.30258512f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow42 = std::exp(((3.45387769f * (float(fEntry20) + 1.0f)) + -6.90775537f));
		float fSlow43 = (1.0f / ((fConst0 * (std::exp((1.15129256f * (float(fEntry19) + 1.0f))) * fSlow42)) + 1.0f));
		float fSlow44 = (1.0f - fSlow43);
		float fSlow45 = (1.0f / ((fConst0 * fSlow42) + 1.0f));
		float fSlow46 = (100.0f * (1.0f - (float(fEntry21) + 1.0f)));
		float fSlow47 = (0.0f - fSlow46);
		float fSlow48 = std::exp(((4.60517025f * (float(fEntry22) + 1.0f)) + -4.60517025f));
		float fSlow49 = (0.294117659f / fSlow48);
		float fSlow50 = (1.0f - (float(fEntry23) + 1.0f));
		float fSlow51 = (1.0f - (float(fEntry24) + 1.0f));
		float fSlow52 = ((100.0f * (fSlow50 - fSlow51)) + fSlow48);
		float fSlow53 = (float(fEntry25) + 1.0f);
		float fSlow54 = (fSlow53 - (float(fEntry26) + 1.0f));
		float fSlow55 = (2.5f * fSlow54);
		float fSlow56 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -2.30258512f))));
		float fSlow57 = (1.0f / fSlow56);
		float fSlow58 = (fSlow57 + 1.0f);
		float fSlow59 = (0.0f - (1.0f / (fSlow56 * fSlow58)));
		float fSlow60 = (fSlow39 / fSlow2);
		float fSlow61 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow35) + -3.0f));
		float fSlow62 = (1.0f - (0.5f * fSlow61));
		float fSlow63 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow35) + -1.0f));
		float fSlow64 = (fSlow63 / fSlow37);
		float fSlow65 = (1.0f - (float(fEntry28) + 1.0f));
		float fSlow66 = std::exp(((3.45387769f * (float(fEntry29) + 1.0f)) + -2.30258512f));
		float fSlow67 = ((100.0f * (fSlow65 - fSlow51)) + fSlow66);
		float fSlow68 = (0.5f * (fSlow37 / fSlow2));
		float fSlow69 = (float(fEntry31) + 1.0f);
		float fSlow70 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry30) + 1.0f)))))) * std::exp((3.80045128f * fSlow69)));
		float fSlow71 = (1.0f / fSlow58);
		float fSlow72 = (1.0f - fSlow57);
		float fSlow73 = (fSlow70 / fSlow56);
		float fSlow74 = std::exp(((3.45387769f * (float(fEntry33) + 1.0f)) + -13.8155107f));
		float fSlow75 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry32) + 1.0f)) + -11.5129251f)) * fSlow74)) + 1.0f));
		float fSlow76 = (1.0f - fSlow75);
		float fSlow77 = (1.0f / ((fConst0 * (std::exp(((5.75646257f * (float(fEntry34) + 1.0f)) + -2.30258512f)) * fSlow74)) + 1.0f));
		float fSlow78 = (1.0f - fSlow77);
		float fSlow79 = (1.0f / ((fConst0 * fSlow74) + 1.0f));
		float fSlow80 = (5.0f * (1.0f - (float(fEntry35) + 1.0f)));
		float fSlow81 = (0.117647059f / fSlow53);
		float fSlow82 = std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -2.30258512f));
		float fSlow83 = ((100.0f * fSlow50) + fSlow82);
		float fSlow84 = (0.294117659f / fSlow82);
		float fSlow85 = std::exp(((2.30258512f * (float(fEntry37) + 1.0f)) + -2.30258512f));
		float fSlow86 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry38) + 1.0f)) + -6.90775537f)))));
		float fSlow87 = (1.0f - fSlow86);
		float fSlow88 = (100.0f * (1.0f - (float(fEntry39) + 1.0f)));
		float fSlow89 = (0.0f - fSlow88);
		float fSlow90 = (100.0f * fSlow51);
		float fSlow91 = (0.294117659f / fSlow66);
		float fSlow92 = (100.0f * fSlow65);
		float fSlow93 = (fSlow56 * fSlow2);
		float fSlow94 = (0.5f * (fSlow37 / fSlow93));
		float fSlow95 = (fSlow77 + -1.0f);
		float fSlow96 = (1.0f / fSlow93);
		float fSlow97 = (fSlow43 + -1.0f);
		float fSlow98 = (1.0f - (0.5f * fSlow63));
		float fSlow99 = AmpMono_faustpower2_f(fSlow38);
		float fSlow100 = (0.5f * (fSlow61 / fSlow99));
		float fSlow101 = (fSlow99 / fSlow2);
		float fSlow102 = (fSlow99 / fSlow93);
		float fSlow103 = (fSlow39 / fSlow93);
		float fSlow104 = (1.0f - (0.5f * fSlow36));
		float fSlow105 = (5.0f * fSlow69);
		int iSlow106 = (fSlow105 < 9.0f);
		int iSlow107 = (fSlow105 < 8.0f);
		int iSlow108 = (fSlow105 < 7.0f);
		int iSlow109 = (fSlow105 < 6.0f);
		int iSlow110 = (fSlow105 < 5.0f);
		int iSlow111 = (fSlow105 < 4.0f);
		int iSlow112 = (fSlow105 < 3.0f);
		int iSlow113 = (fSlow105 < 2.0f);
		int iSlow114 = (fSlow105 < 1.0f);
		float fSlow115 = std::pow(10.0f, (0.0500000007f * (iSlow106?(iSlow107?(iSlow108?(iSlow109?(iSlow110?(iSlow111?(iSlow112?(iSlow113?(iSlow114?((fSlow105 < 0.0f)?0.0324000008f:(iSlow114?(0.0324000008f - (32.9620018f * fSlow69)):-6.55999994f)):(iSlow113?(-6.55999994f - (6.53999996f * (fSlow105 + -1.0f))):-13.1000004f)):(iSlow112?(-13.1000004f - (6.5f * (fSlow105 + -2.0f))):-19.6000004f)):(iSlow111?(-19.6000004f - (6.19999981f * (fSlow105 + -3.0f))):-25.7999992f)):(iSlow110?(-25.7999992f - (4.80000019f * (fSlow105 + -4.0f))):-30.6000004f)):(iSlow109?(-30.6000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow69))))):-32.7999992f)):(iSlow108?(-32.7999992f - (0.100000001f * (fSlow105 + -6.0f))):-32.9000015f)):(iSlow107?((0.400000006f * (fSlow105 + -7.0f)) + -32.9000015f):-32.5f)):(iSlow106?((0.300000012f * (fSlow105 + -8.0f)) + -32.5f):-32.2000008f)):((fSlow105 < 10.0f)?((0.100000001f * (fSlow105 + -9.0f)) + -32.2000008f):-32.0999985f))));
		float fSlow116 = (1.0f / fSlow33);
		float fSlow117 = (1.0f - fSlow32);
		float fSlow118 = (1.0f / (fSlow31 * fSlow2));
		float fSlow119 = std::pow(10.0f, (0.0500000007f * (fSlow28 * ((4.5f * fSlow29) + (18.0f * fSlow30)))));
		float fSlow120 = float(fEntry40);
		float fSlow121 = ((10.0f * fSlow120) + -14.0f);
		int iSlow122 = (fSlow121 > 0.0f);
		float fSlow123 = ((fSlow120 * ((fSlow28 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow124 = ((fConst12 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow121)))) * fSlow123);
		float fSlow125 = (fConst12 * fSlow123);
		float fSlow126 = (iSlow122?fSlow125:fSlow124);
		float fSlow127 = ((fConst11 * (fConst11 - fSlow126)) + 1.0f);
		float fSlow128 = ((fConst11 * (fConst11 + fSlow126)) + 1.0f);
		float fSlow129 = (iSlow122?fSlow124:fSlow125);
		float fSlow130 = ((fConst11 * (fConst11 - fSlow129)) + 1.0f);
		float fSlow131 = ((fConst11 * (fConst11 + fSlow129)) + 1.0f);
		float fSlow132 = (fSlow26 + 1.0f);
		float fSlow133 = (0.0f - (1.0f / (fSlow132 * fSlow25)));
		float fSlow134 = (fSlow25 * fSlow128);
		float fSlow135 = std::pow(10.0f, ((0.0500000007f * fSlow23) * (iSlow24?18.0f:9.0f)));
		float fSlow136 = (250.0f * (float(fEntry41) + 1.0f));
		float fSlow137 = (1.0f / fSlow19);
		float fSlow138 = (1.0f - fSlow18);
		float fSlow139 = std::exp((0.0f - (fConst1 / std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -9.2103405f)))));
		float fSlow140 = (1.0f - fSlow139);
		float fSlow141 = (250.0f * (float(fEntry43) + 1.0f));
		float fSlow142 = std::exp(((4.60517025f * (float(fEntry44) + 1.0f)) + -9.2103405f));
		float fSlow143 = (1.0f / ((fConst0 * fSlow142) + 1.0f));
		float fSlow144 = (100.0f * (1.0f - (float(fEntry45) + 1.0f)));
		float fSlow145 = ((1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry46) + 1.0f)) + -4.60517025f)) * fSlow142)) + 1.0f)) + -1.0f);
		float fSlow146 = std::exp(((2.30258512f * (float(fEntry47) + 1.0f)) + -2.30258512f));
		float fSlow147 = (100.0f * (1.0f - (float(fEntry48) + 1.0f)));
		float fSlow148 = (0.0f - fSlow147);
		float fSlow149 = std::exp(((3.45387769f * (float(fEntry49) + 1.0f)) + -2.30258512f));
		float fSlow150 = (0.294117659f / fSlow149);
		float fSlow151 = std::exp(((3.45387769f * (float(fEntry50) + 1.0f)) + -2.30258512f));
		float fSlow152 = (0.294117659f / fSlow151);
		float fSlow153 = std::exp(((2.30258512f * (float(fEntry51) + 1.0f)) + -4.60517025f));
		float fSlow154 = (1.0f / ((fConst0 * fSlow153) + 1.0f));
		float fSlow155 = (fSlow16 / fSlow11);
		float fSlow156 = std::exp(((2.30258512f * (float(fEntry52) + 1.0f)) + -2.30258512f));
		float fSlow157 = (1.0f - (1.0f / ((fConst0 * (fSlow153 * std::exp((1.15129256f * (float(fEntry53) + 1.0f))))) + 1.0f)));
		float fSlow158 = (5.0f * fSlow21);
		int iSlow159 = (fSlow158 < 9.0f);
		int iSlow160 = (fSlow158 < 8.0f);
		int iSlow161 = (fSlow158 < 7.0f);
		int iSlow162 = (fSlow158 < 6.0f);
		int iSlow163 = (fSlow158 < 5.0f);
		int iSlow164 = (fSlow158 < 4.0f);
		int iSlow165 = (fSlow158 < 3.0f);
		int iSlow166 = (fSlow158 < 2.0f);
		int iSlow167 = (fSlow158 < 1.0f);
		float fSlow168 = std::pow(10.0f, (0.0500000007f * (iSlow159?(iSlow160?(iSlow161?(iSlow162?(iSlow163?(iSlow164?(iSlow165?(iSlow166?(iSlow167?((fSlow158 < 0.0f)?9.22000027f:(iSlow167?(9.22000027f - (29.25f * fSlow21)):3.36999989f)):(iSlow166?(3.36999989f - (5.69000006f * (fSlow158 + -1.0f))):-2.31999993f)):(iSlow165?(-2.31999993f - (5.48999977f * (fSlow158 + -2.0f))):-7.80999994f)):(iSlow164?(-7.80999994f - (5.48999977f * (fSlow158 + -3.0f))):-13.3000002f)):(iSlow163?(-13.3000002f - (4.5f * (fSlow158 + -4.0f))):-17.7999992f)):(iSlow162?(-17.7999992f - (2.5f * (0.0f - (5.0f * (1.0f - fSlow21))))):-20.2999992f)):(iSlow161?(-20.2999992f - (0.699999988f * (fSlow158 + -6.0f))):-21.0f)):(iSlow160?(-21.0f - (0.100000001f * (fSlow158 + -7.0f))):-21.1000004f)):(iSlow159?((0.100000001f * (fSlow158 + -8.0f)) + -21.1000004f):-21.0f)):-21.0f)));
		float fSlow169 = float(fEntry54);
		float fSlow170 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow169)));
		float fSlow171 = float(fEntry55);
		float fSlow172 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow171))));
		float fSlow173 = (15.0f * fSlow171);
		int iSlow174 = (fSlow173 > 0.0f);
		float fSlow175 = (fConst170 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow173))));
		float fSlow176 = (iSlow174?fConst170:fSlow175);
		float fSlow177 = ((fConst169 * (fConst169 - fSlow176)) + 1.0f);
		float fSlow178 = ((fConst169 * (fConst169 + fSlow176)) + 1.0f);
		float fSlow179 = (iSlow174?fSlow175:fConst170);
		float fSlow180 = ((fConst169 * (fConst169 - fSlow179)) + 1.0f);
		float fSlow181 = ((fConst169 * (fConst169 + fSlow179)) + 1.0f);
		float fSlow182 = (0.0f - (10.0f * fSlow169));
		int iSlow183 = (fSlow182 > 0.0f);
		float fSlow184 = (fConst173 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow182))));
		float fSlow185 = (iSlow183?fConst173:fSlow184);
		float fSlow186 = ((fConst172 * (fConst172 - fSlow185)) + 1.0f);
		float fSlow187 = ((fConst172 * (fConst172 + fSlow185)) + 1.0f);
		float fSlow188 = (iSlow183?fSlow184:fConst173);
		float fSlow189 = ((fConst172 * (fConst172 + fSlow188)) + 1.0f);
		float fSlow190 = ((fConst172 * (fConst172 - fSlow188)) + 1.0f);
		float fSlow191 = (0.0f - (17.0f * fSlow169));
		int iSlow192 = (fSlow191 > 0.0f);
		float fSlow193 = (fConst175 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow191))));
		float fSlow194 = (iSlow192?fConst175:fSlow193);
		float fSlow195 = ((fConst174 * (fConst174 - fSlow194)) + 1.0f);
		float fSlow196 = ((fConst174 * (fConst174 + fSlow194)) + 1.0f);
		float fSlow197 = (iSlow192?fSlow193:fConst175);
		float fSlow198 = ((fConst174 * (fConst174 + fSlow197)) + 1.0f);
		float fSlow199 = ((fConst174 * (fConst174 - fSlow197)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow70 * fTemp0);
			fRec14[0] = ((fSlow59 * fVec0[1]) - (fSlow71 * ((fSlow72 * fRec14[1]) - (fSlow73 * fTemp0))));
			fRec16[0] = ((fSlow78 * fRec16[1]) + (fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec14[0])) - fRec16[1]))));
			fRec15[0] = ((fSlow76 * fRec15[1]) + (fSlow75 * fRec16[0]));
			float fTemp1 = (fSlow55 + (fRec14[0] - fRec15[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * ((fSlow53 * ((fTemp3 * (std::fabs((fTemp3 * fTemp2)) + -2.0f)) * fTemp2)) - fSlow54)))) - fSlow83);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp4) + (fSlow82 * (((fTemp6 * (std::fabs((fTemp6 * fTemp5)) + -2.0f)) * fTemp5) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (fTemp8 * (std::fabs(fTemp8) + -2.0f));
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow48 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)));
			fRec17[0] = ((fSlow86 * fRec17[1]) + (fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp10 - fSlow90)))));
			float fTemp11 = (fSlow85 * fRec17[0]);
			fRec18[0] = ((fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp10 - fTemp11) - fSlow90)) - fRec18[1])))) + (fSlow44 * fRec18[1]));
			float fTemp12 = (fSlow41 * fRec18[0]);
			float fTemp13 = (fSlow67 + (fTemp10 - (fTemp11 + fTemp12)));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (std::fabs(fTemp14) + -2.0f);
			float fTemp16 = (((std::min<float>(0.0f, fTemp13) + fTemp12) - (fSlow66 * (1.0f - (((std::fabs((fTemp15 * fTemp14)) + -2.0f) * fTemp15) * fTemp14)))) - fSlow92);
			fVec1[0] = (fSlow68 * fTemp16);
			fRec13[0] = ((fSlow59 * fVec1[1]) + (fSlow71 * ((fSlow94 * fTemp16) - (fSlow72 * fRec13[1]))));
			fRec20[0] = ((fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec13[0])) - fRec20[1]))) - (fSlow95 * fRec20[1]));
			fRec19[0] = ((fSlow76 * fRec19[1]) + (fSlow75 * fRec20[0]));
			float fTemp17 = (fSlow55 + (fRec13[0] - fRec19[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (fTemp18 * (std::fabs(fTemp18) + -2.0f));
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow54 - (fSlow53 * (fTemp19 * (std::fabs(fTemp19) + -2.0f))))))) - fSlow83);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp20) + (fSlow82 * (((fTemp21 * (std::fabs((fTemp21 * fTemp22)) + -2.0f)) * fTemp22) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (fTemp24 * (std::fabs(fTemp24) + -2.0f));
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow48 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)));
			fRec22[0] = ((fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp26 - fSlow90)))) + (fSlow86 * fRec22[1]));
			float fTemp27 = (fSlow85 * fRec22[0]);
			fRec21[0] = ((fSlow44 * fRec21[1]) + (fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp26 - fTemp27) - fSlow90)) - fRec21[1])))));
			float fTemp28 = (fSlow41 * fRec21[0]);
			float fTemp29 = (fSlow67 + (fTemp26 - (fTemp28 + fTemp27)));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = ((std::fabs(fTemp30) + -2.0f) * fTemp30);
			float fTemp32 = (((std::min<float>(0.0f, fTemp29) + fTemp28) - (fSlow66 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow92);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec12[0] = ((fSlow59 * fVec2[1]) - (fSlow71 * ((fSlow72 * fRec12[1]) - (fSlow96 * fTemp32))));
			fRec24[0] = ((fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec12[0])) - fRec24[1]))) - (fSlow95 * fRec24[1]));
			fRec23[0] = ((fSlow75 * fRec24[0]) + (fSlow76 * fRec23[1]));
			float fTemp33 = (fSlow55 + (fRec12[0] - fRec23[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow54 - (fSlow53 * ((fTemp34 * (std::fabs((fTemp34 * fTemp35)) + -2.0f)) * fTemp35)))))) - fSlow83);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (fTemp37 * (std::fabs(fTemp37) + -2.0f));
			float fTemp39 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp36) + (fSlow82 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (std::fabs(fTemp40) + -2.0f);
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow48 * (((fTemp40 * (std::fabs((fTemp40 * fTemp41)) + -2.0f)) * fTemp41) + 1.0f)));
			fRec25[0] = ((fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp42 - fSlow90)))) + (fSlow86 * fRec25[1]));
			float fTemp43 = (fSlow85 * fRec25[0]);
			fRec11[0] = ((fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp42 - fTemp43) - fSlow90)) - fRec11[1])))) - (fSlow97 * fRec11[1]));
			float fTemp44 = (fSlow41 * fRec11[0]);
			float fTemp45 = (fSlow67 + (fTemp42 - (fTemp43 + fTemp44)));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (fTemp46 * (std::fabs(fTemp46) + -2.0f));
			float fTemp48 = ((fSlow64 * (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow66 * (1.0f - (fTemp47 * (std::fabs(fTemp47) + -2.0f))))) - fSlow92)) + (fSlow98 * fTemp16));
			fVec3[0] = (fSlow101 * fTemp48);
			fRec28[0] = ((fSlow59 * fVec3[1]) - (fSlow71 * ((fSlow72 * fRec28[1]) - (fSlow102 * fTemp48))));
			fRec30[0] = ((fSlow78 * fRec30[1]) + (fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec28[0])) - fRec30[1]))));
			fRec29[0] = ((fSlow76 * fRec29[1]) + (fSlow75 * fRec30[0]));
			float fTemp49 = (fSlow55 + (fRec28[0] - fRec29[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (fTemp50 * (std::fabs(fTemp50) + -2.0f));
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow54 - (fSlow53 * (fTemp51 * (std::fabs(fTemp51) + -2.0f))))))) - fSlow83);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (fTemp53 * (std::fabs(fTemp53) + -2.0f));
			float fTemp55 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp52) + (fSlow82 * ((fTemp54 * (std::fabs(fTemp54) + -2.0f)) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow48 * (((fTemp56 * (std::fabs((fTemp56 * fTemp57)) + -2.0f)) * fTemp57) + 1.0f)));
			fRec31[0] = ((fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp58 - fSlow90)))) + (fSlow86 * fRec31[1]));
			float fTemp59 = (fSlow85 * fRec31[0]);
			fRec27[0] = ((fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp58 - fTemp59) - fSlow90)) - fRec27[1])))) + (fSlow44 * fRec27[1]));
			float fTemp60 = (fSlow41 * fRec27[0]);
			float fTemp61 = (fSlow67 + (fTemp58 - (fTemp60 + fTemp59)));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (fTemp62 * (std::fabs(fTemp62) + -2.0f));
			float fTemp64 = (((fTemp60 + std::min<float>(0.0f, fTemp61)) - (fSlow66 * (1.0f - (fTemp63 * (std::fabs(fTemp63) + -2.0f))))) - fSlow92);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec26[0] = ((fSlow59 * fVec4[1]) - (fSlow71 * ((fSlow72 * fRec26[1]) - (fSlow96 * fTemp64))));
			fRec33[0] = ((fSlow78 * fRec33[1]) + (fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec26[0])) - fRec33[1]))));
			fRec32[0] = ((fSlow76 * fRec32[1]) + (fSlow75 * fRec33[0]));
			float fTemp65 = (fSlow55 + (fRec26[0] - fRec32[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow54 - (fSlow53 * ((fTemp66 * (std::fabs((fTemp66 * fTemp67)) + -2.0f)) * fTemp67)))))) - fSlow83);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow52 + ((fSlow82 * (((fTemp69 * (std::fabs((fTemp69 * fTemp70)) + -2.0f)) * fTemp70) + 1.0f)) + std::max<float>(0.0f, fTemp68))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (fTemp72 * (std::fabs(fTemp72) + -2.0f));
			float fTemp74 = ((fSlow48 * ((fTemp73 * (std::fabs(fTemp73) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp71));
			fRec34[0] = ((fSlow86 * fRec34[1]) + (fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp74 - fSlow90)))));
			float fTemp75 = (fSlow85 * fRec34[0]);
			fRec35[0] = ((fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp74 - fTemp75) - fSlow90)) - fRec35[1])))) + (fSlow44 * fRec35[1]));
			float fTemp76 = (fSlow41 * fRec35[0]);
			float fTemp77 = (fSlow67 + (fTemp74 - (fTemp75 + fTemp76)));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = ((fSlow62 * fTemp48) + (fSlow100 * (((std::min<float>(0.0f, fTemp77) + fTemp76) - (fSlow66 * (1.0f - (((std::fabs((fTemp78 * fTemp79)) + -2.0f) * fTemp78) * fTemp79)))) - fSlow92)));
			fVec5[0] = (fSlow60 * fTemp80);
			fRec10[0] = ((fSlow59 * fVec5[1]) - (fSlow71 * ((fSlow72 * fRec10[1]) - (fSlow103 * fTemp80))));
			fRec37[0] = ((fSlow78 * fRec37[1]) + (fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec10[0])) - fRec37[1]))));
			fRec36[0] = ((fSlow76 * fRec36[1]) + (fSlow75 * fRec37[0]));
			float fTemp81 = (fSlow55 + (fRec10[0] - fRec36[0]));
			float fTemp82 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp81))));
			float fTemp83 = (std::fabs(fTemp82) + -2.0f);
			float fTemp84 = ((fSlow2 * (std::min<float>(0.0f, fTemp81) - (2.5f * (fSlow54 - (fSlow53 * (((std::fabs((fTemp83 * fTemp82)) + -2.0f) * fTemp83) * fTemp82)))))) - fSlow83);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp84))));
			float fTemp86 = ((std::fabs(fTemp85) + -2.0f) * fTemp85);
			float fTemp87 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp84) + (fSlow82 * ((fTemp86 * (std::fabs(fTemp86) + -2.0f)) + 1.0f)))));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = ((std::fabs(fTemp88) + -2.0f) * fTemp88);
			float fTemp90 = ((fSlow48 * ((fTemp89 * (std::fabs(fTemp89) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp87));
			fRec38[0] = ((fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp90 - fSlow90)))) + (fSlow86 * fRec38[1]));
			float fTemp91 = (fSlow85 * fRec38[0]);
			fRec9[0] = ((fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp90 - fTemp91) - fSlow90)) - fRec9[1])))) + (fSlow44 * fRec9[1]));
			float fTemp92 = (fSlow41 * fRec9[0]);
			float fTemp93 = (fSlow67 + (fTemp90 - (fTemp92 + fTemp91)));
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = (fTemp94 * (std::fabs(fTemp94) + -2.0f));
			float fTemp96 = (((fTemp92 + std::min<float>(0.0f, fTemp93)) - (fSlow66 * (1.0f - (fTemp95 * (std::fabs(fTemp95) + -2.0f))))) - fSlow92);
			fVec6[0] = (fSlow3 * fTemp96);
			fRec8[0] = ((fSlow59 * fVec6[1]) - (fSlow71 * ((fSlow72 * fRec8[1]) - (fSlow96 * fTemp96))));
			fRec40[0] = ((fSlow78 * fRec40[1]) + (fSlow79 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow80 + fRec8[0])) - fRec40[1]))));
			fRec39[0] = ((fSlow75 * fRec40[0]) + (fSlow76 * fRec39[1]));
			float fTemp97 = (fSlow55 + (fRec8[0] - fRec39[0]));
			float fTemp98 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp97))));
			float fTemp99 = (fTemp98 * (std::fabs(fTemp98) + -2.0f));
			float fTemp100 = ((fSlow2 * (std::min<float>(0.0f, fTemp97) - (2.5f * (fSlow54 - (fSlow53 * (fTemp99 * (std::fabs(fTemp99) + -2.0f))))))) - fSlow83);
			float fTemp101 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp100))));
			float fTemp102 = (std::fabs(fTemp101) + -2.0f);
			float fTemp103 = (0.0f - (fSlow52 + (std::max<float>(0.0f, fTemp100) + (fSlow82 * (((fTemp101 * (std::fabs((fTemp101 * fTemp102)) + -2.0f)) * fTemp102) + 1.0f)))));
			float fTemp104 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp103))));
			float fTemp105 = (std::fabs(fTemp104) + -2.0f);
			float fTemp106 = ((fSlow48 * ((((std::fabs((fTemp104 * fTemp105)) + -2.0f) * fTemp104) * fTemp105) + 1.0f)) + std::max<float>(0.0f, fTemp103));
			fRec41[0] = ((fSlow87 * (fSlow88 + std::max<float>(fSlow89, (fTemp106 - fSlow90)))) + (fSlow86 * fRec41[1]));
			float fTemp107 = (fSlow85 * fRec41[0]);
			fRec7[0] = ((fSlow44 * fRec7[1]) + (fSlow45 * std::max<float>(0.0f, (fSlow46 + (std::max<float>(fSlow47, ((fTemp106 - fTemp107) - fSlow90)) - fRec7[1])))));
			float fTemp108 = (fSlow41 * fRec7[0]);
			float fTemp109 = (fSlow67 + (fTemp106 - (fTemp108 + fTemp107)));
			float fTemp110 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::max<float>(0.0f, fTemp109))));
			float fTemp111 = (fTemp110 * (std::fabs(fTemp110) + -2.0f));
			float fTemp112 = (((fSlow40 * (((fTemp108 + std::min<float>(0.0f, fTemp109)) - (fSlow66 * (1.0f - (fTemp111 * (std::fabs(fTemp111) + -2.0f))))) - fSlow92)) + (fSlow104 * fTemp80)) * fSlow115);
			float fTemp113 = (fSlow3 * fTemp112);
			fVec7[0] = fTemp113;
			fRec6[0] = ((fSlow34 * fVec7[1]) - (fSlow116 * ((fSlow117 * fRec6[1]) - (fSlow118 * fTemp112))));
			fRec42[0] = (0.0f - (fSlow116 * ((fSlow117 * fRec42[1]) - (fTemp113 + fVec7[1]))));
			float fTemp114 = (fRec6[0] + (fSlow119 * fRec42[0]));
			fVec8[0] = fTemp114;
			fRec5[0] = ((fConst6 * fVec8[1]) - (fConst7 * ((fConst8 * fRec5[1]) - (fConst4 * fTemp114))));
			float fTemp115 = (fConst10 * fRec4[1]);
			fRec4[0] = (fRec5[0] - ((fTemp115 + (fSlow127 * fRec4[2])) / fSlow128));
			float fTemp116 = ((fRec4[2] * fSlow130) + (fTemp115 + (fRec4[0] * fSlow131)));
			float fTemp117 = (fTemp116 / fSlow128);
			fVec9[0] = fTemp117;
			fRec3[0] = (0.0f - (((fSlow27 * fRec3[1]) - (fTemp117 + fVec9[1])) / fSlow132));
			fRec43[0] = ((fVec9[1] * fSlow133) - (((fRec43[1] * fSlow27) - (fTemp116 / fSlow134)) / fSlow132));
			float fTemp118 = ((fSlow22 * (fRec3[0] + (fRec43[0] * fSlow135))) - fSlow136);
			fVec10[0] = fTemp118;
			fRec2[0] = ((fSlow20 * fVec10[1]) - (fSlow137 * ((fSlow138 * fRec2[1]) - (fSlow18 * fTemp118))));
			fRec44[0] = ((fSlow139 * fRec44[1]) + (fSlow140 * (fRec2[0] - fSlow141)));
			fRec45[0] = ((fSlow143 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow144 + ((fRec2[0] - fRec44[0]) - fSlow141))) - fRec45[1]))) - (fSlow145 * fRec45[1]));
			float fTemp119 = ((fRec2[0] - (fRec44[0] + fRec45[0])) - fSlow141);
			float fTemp120 = (fSlow16 * fTemp119);
			fRec46[0] = ((fSlow5 * fRec46[1]) + (fSlow6 * (fSlow147 + std::max<float>(fSlow148, fTemp120))));
			float fTemp121 = (fSlow146 * fRec46[0]);
			fRec1[0] = ((fSlow13 * fRec1[1]) + (fSlow14 * std::min<float>(1.0f, std::fabs((fSlow15 * (fTemp120 - fTemp121))))));
			float fTemp122 = (fSlow11 / ((fSlow12 * fRec1[0]) + 1.0f));
			float fTemp123 = (fSlow149 + (fTemp120 - (fTemp121 + fTemp122)));
			float fTemp124 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow150 * std::max<float>(0.0f, fTemp123))));
			float fTemp125 = (std::fabs(fTemp124) + -2.0f);
			float fTemp126 = (((fTemp122 + std::min<float>(0.0f, fTemp123)) - (fSlow149 * (1.0f - ((fTemp124 * (std::fabs((fTemp124 * fTemp125)) + -2.0f)) * fTemp125)))) - fSlow151);
			fRec48[0] = ((fSlow5 * fRec48[1]) + (fSlow6 * (fSlow147 + std::max<float>(fSlow148, (0.0f - fTemp120)))));
			float fTemp127 = (fTemp120 + (fSlow146 * fRec48[0]));
			fRec47[0] = ((fSlow14 * std::min<float>(1.0f, std::fabs((fSlow15 * (0.0f - fTemp127))))) + (fSlow13 * fRec47[1]));
			float fTemp128 = (fSlow11 / ((fSlow12 * fRec47[0]) + 1.0f));
			float fTemp129 = (fSlow149 - (fTemp127 + fTemp128));
			float fTemp130 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow150 * std::max<float>(0.0f, fTemp129))));
			float fTemp131 = (std::fabs(fTemp130) + -2.0f);
			float fTemp132 = (((fTemp128 + std::min<float>(0.0f, fTemp129)) + (fSlow149 * (((fTemp130 * (std::fabs((fTemp130 * fTemp131)) + -2.0f)) * fTemp131) + -1.0f))) - fSlow151);
			float fTemp133 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow152 * std::min<float>(0.0f, fTemp132))));
			float fTemp134 = (std::fabs(fTemp133) + -2.0f);
			float fTemp135 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow152 * std::min<float>(0.0f, fTemp126))));
			float fTemp136 = (std::fabs(fTemp135) + -2.0f);
			float fTemp137 = std::fabs((fSlow155 * fTemp119));
			fRec49[0] = ((fSlow154 * std::max<float>(0.0f, ((std::max<float>(1.0f, fTemp137) + (fSlow156 * std::min<float>(1.0f, fTemp137))) + (-1.0f - fRec49[1])))) + (fSlow157 * fRec49[1]));
			float fTemp138 = (fSlow10 * ((std::max<float>(0.0f, fTemp126) - (std::max<float>(0.0f, fTemp132) + (fSlow151 * (((((std::fabs((fTemp134 * fTemp133)) + -2.0f) * fTemp134) * fTemp133) + 1.0f) - ((((std::fabs((fTemp135 * fTemp136)) + -2.0f) * fTemp135) * fTemp136) + 1.0f))))) / ((fSlow9 * fRec49[0]) + 1.0f)));
			fRec0[0] = ((fSlow6 * (fSlow7 + std::max<float>(fSlow8, std::fabs(fTemp138)))) + (fSlow5 * fRec0[1]));
			float fTemp139 = (fSlow3 * (((fSlow4 * fRec0[0]) + fTemp138) * fSlow168));
			fRec72[0] = (fTemp139 - (fConst112 * ((fConst114 * fRec72[1]) + (fConst115 * fRec72[2]))));
			fRec71[0] = ((fConst112 * (((fConst113 * fRec72[0]) + (fConst111 * fRec72[1])) + (fConst113 * fRec72[2]))) - (fConst109 * ((fConst114 * fRec71[1]) + (fConst116 * fRec71[2]))));
			float fTemp140 = (((fConst111 * fRec71[1]) + (fConst113 * fRec71[0])) + (fConst113 * fRec71[2]));
			fVec11[0] = fTemp140;
			fRec70[0] = (0.0f - (fConst105 * ((fConst106 * fRec70[1]) - (fConst109 * (fTemp140 + fVec11[1])))));
			fRec69[0] = (fRec70[0] - (fConst104 * ((fConst117 * fRec69[1]) + (fConst118 * fRec69[2]))));
			float fTemp141 = ((fRec69[0] + (2.0f * fRec69[1])) + fRec69[2]);
			fVec12[0] = fTemp141;
			fRec68[0] = (fConst101 * ((fConst104 * (fTemp141 + fVec12[1])) - (fConst119 * fRec68[1])));
			fRec67[0] = (fRec68[0] - (fConst99 * ((fConst122 * fRec67[1]) + (fConst123 * fRec67[2]))));
			fRec66[0] = ((fConst99 * ((fRec67[0] + (2.0f * fRec67[1])) + fRec67[2])) - (fConst98 * ((fConst122 * fRec66[1]) + (fConst124 * fRec66[2]))));
			fRec65[0] = ((fConst98 * ((fRec66[0] + (2.0f * fRec66[1])) + fRec66[2])) - (fConst97 * ((fConst122 * fRec65[1]) + (fConst125 * fRec65[2]))));
			fRec76[0] = ((fConst104 * ((fConst128 * fVec12[1]) + (fConst127 * fTemp141))) - (fConst129 * fRec76[1]));
			fRec75[0] = (fRec76[0] - (fConst99 * ((fConst123 * fRec75[2]) + (fConst122 * fRec75[1]))));
			fRec74[0] = ((fConst99 * (((fConst126 * fRec75[1]) + (fConst121 * fRec75[0])) + (fConst121 * fRec75[2]))) - (fConst98 * ((fConst122 * fRec74[1]) + (fConst124 * fRec74[2]))));
			fRec73[0] = ((fConst98 * (((fConst121 * fRec74[0]) + (fConst126 * fRec74[1])) + (fConst121 * fRec74[2]))) - (fConst97 * ((fConst125 * fRec73[2]) + (fConst122 * fRec73[1]))));
			float fTemp142 = (fConst131 * fRec64[1]);
			fRec64[0] = ((fConst97 * (((fRec65[0] + (2.0f * fRec65[1])) + fRec65[2]) + (0.0316227749f * (((fConst121 * fRec73[0]) + (fConst126 * fRec73[1])) + (fConst121 * fRec73[2]))))) - (fConst92 * ((fConst130 * fRec64[2]) + fTemp142)));
			float fTemp143 = (fConst133 * fRec63[1]);
			fRec63[0] = ((fConst92 * ((fConst94 * fRec64[2]) + (fTemp142 + (fConst132 * fRec64[0])))) - (fConst85 * (fTemp143 + (fConst134 * fRec63[2]))));
			float fTemp144 = (fConst136 * fRec62[1]);
			fRec62[0] = ((fConst85 * (((fConst87 * fRec63[0]) + fTemp143) + (fConst135 * fRec63[2]))) - (fConst78 * (fTemp144 + (fConst137 * fRec62[2]))));
			float fTemp145 = (fConst140 * fRec61[1]);
			fRec61[0] = ((fConst78 * ((fConst80 * fRec62[2]) + (fTemp144 + (fConst138 * fRec62[0])))) - (fConst71 * ((fConst139 * fRec61[2]) + fTemp145)));
			float fTemp146 = (fConst65 * fRec60[1]);
			fRec60[0] = ((fConst71 * ((fConst73 * fRec61[2]) + (fTemp145 + (fConst141 * fRec61[0])))) - (fConst64 * (fTemp146 + (fConst142 * fRec60[2]))));
			float fTemp147 = (fConst146 * fRec59[1]);
			fRec59[0] = ((fConst64 * ((fTemp146 + (fConst144 * fRec60[0])) + (fConst145 * fRec60[2]))) - (fConst57 * (fTemp147 + (fConst147 * fRec59[2]))));
			float fTemp148 = (fConst149 * fRec58[1]);
			fRec58[0] = ((fConst57 * ((fConst59 * fRec59[2]) + (fTemp147 + (fConst148 * fRec59[0])))) - (fConst50 * (fTemp148 + (fConst150 * fRec58[2]))));
			float fTemp149 = (fConst45 * fRec57[1]);
			fRec57[0] = ((fConst50 * (((fConst52 * fRec58[0]) + fTemp148) + (fConst151 * fRec58[2]))) - (fConst44 * (fTemp149 + (fConst152 * fRec57[2]))));
			float fTemp150 = (fConst156 * fRec56[1]);
			fRec56[0] = ((fConst44 * ((fTemp149 + (fConst154 * fRec57[0])) + (fConst155 * fRec57[2]))) - (fConst37 * (fTemp150 + (fConst157 * fRec56[2]))));
			float fTemp151 = (fConst159 * fRec55[1]);
			fRec55[0] = ((fConst37 * ((fConst39 * fRec56[2]) + (fTemp150 + (fConst158 * fRec56[0])))) - (fConst26 * (fTemp151 + (fConst160 * fRec55[2]))));
			float fTemp152 = (((fConst31 * fRec55[0]) + fTemp151) + (fConst161 * fRec55[2]));
			fVec13[0] = fTemp152;
			fRec54[0] = ((fConst26 * ((fConst29 * fVec13[1]) + (fConst28 * fTemp152))) - (fConst163 * fRec54[1]));
			fRec53[0] = (fRec54[0] - (fConst19 * ((fConst164 * fRec53[2]) + (fConst165 * fRec53[1]))));
			fRec78[0] = (0.0f - (fConst167 * ((fConst162 * fRec78[1]) - (fConst26 * (fTemp152 + fVec13[1])))));
			fRec77[0] = (fRec78[0] - (fConst19 * ((fConst164 * fRec77[2]) + (fConst165 * fRec77[1]))));
			float fTemp153 = (fConst171 * fRec52[1]);
			fRec52[0] = ((fConst19 * (((fConst21 * fRec53[2]) + ((fConst21 * fRec53[0]) + (fConst166 * fRec53[1]))) + (fSlow172 * ((fRec77[0] + (2.0f * fRec77[1])) + fRec77[2])))) - (((fRec52[2] * fSlow177) + fTemp153) / fSlow178));
			float fTemp154 = (fConst16 * fRec51[1]);
			fRec51[0] = ((((fRec52[2] * fSlow180) + (fTemp153 + (fRec52[0] * fSlow181))) / fSlow178) - ((fTemp154 + (fRec51[2] * fSlow186)) / fSlow187));
			float fTemp155 = (fConst14 * fRec50[1]);
			fRec50[0] = ((((fTemp154 + (fRec51[0] * fSlow189)) + (fRec51[2] * fSlow190)) / fSlow187) - ((fTemp155 + (fSlow195 * fRec50[2])) / fSlow196));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow170 * (((fTemp155 + (fRec50[0] * fSlow198)) + (fSlow199 * fRec50[2])) / fSlow196)):fTemp139)));
			fVec0[1] = fVec0[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec18[1] = fRec18[0];
			fVec1[1] = fVec1[0];
			fRec13[1] = fRec13[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fVec2[1] = fVec2[0];
			fRec12[1] = fRec12[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec11[1] = fRec11[0];
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
			fRec35[1] = fRec35[0];
			fVec5[1] = fVec5[0];
			fRec10[1] = fRec10[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec38[1] = fRec38[0];
			fRec9[1] = fRec9[0];
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
			fVec9[1] = fVec9[0];
			fRec3[1] = fRec3[0];
			fRec43[1] = fRec43[0];
			fVec10[1] = fVec10[0];
			fRec2[1] = fRec2[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec1[1] = fRec1[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec0[1] = fRec0[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fVec11[1] = fVec11[0];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fVec12[1] = fVec12[0];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
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
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fVec13[1] = fVec13[0];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];

		}

	}


};

#endif
