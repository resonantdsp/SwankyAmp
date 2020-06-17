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

/* link with : "" */
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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fEntry8;
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
	float fVec0[2];
	float fRec9[2];
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	float fRec11[2];
	float fRec10[2];
	FAUSTFLOAT fEntry28;
	float fConst8;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	float fRec12[2];
	FAUSTFLOAT fEntry31;
	float fRec8[2];
	FAUSTFLOAT fEntry32;
	float fVec1[2];
	float fRec14[2];
	float fRec16[2];
	float fRec15[2];
	float fRec18[2];
	float fRec17[2];
	float fVec2[2];
	float fRec13[2];
	float fRec20[2];
	float fRec19[2];
	float fRec21[2];
	float fRec22[2];
	float fVec3[2];
	float fRec26[2];
	float fRec28[2];
	float fRec27[2];
	float fRec29[2];
	float fRec25[2];
	float fVec4[2];
	float fRec24[2];
	float fRec31[2];
	float fRec30[2];
	float fRec32[2];
	float fRec23[2];
	float fVec5[2];
	float fRec7[2];
	float fRec34[2];
	float fRec33[2];
	float fRec35[2];
	float fRec6[2];
	float fVec6[2];
	float fRec5[2];
	float fRec37[2];
	float fRec36[2];
	float fRec39[2];
	float fRec38[2];
	float fVec7[2];
	float fRec4[2];
	float fRec40[2];
	float fVec8[2];
	float fConst9;
	float fConst10;
	float fRec3[2];
	float fConst11;
	FAUSTFLOAT fEntry33;
	float fConst12;
	float fRec2[3];
	float fVec9[2];
	float fRec1[2];
	float fRec41[2];
	FAUSTFLOAT fEntry34;
	float fVec10[2];
	float fRec0[2];
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec42[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	float fRec43[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fRec44[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fRec45[2];
	FAUSTFLOAT fEntry46;
	float fRec46[2];
	float fRec47[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec48[2];
	FAUSTFLOAT fEntry49;
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
	float fRec71[3];
	float fConst113;
	float fConst114;
	float fRec70[3];
	float fVec11[2];
	float fRec69[2];
	float fConst115;
	float fConst116;
	float fRec68[3];
	float fVec12[2];
	float fConst117;
	float fRec67[2];
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec66[3];
	float fConst122;
	float fRec65[3];
	float fConst123;
	float fRec64[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec75[2];
	float fRec74[3];
	float fConst127;
	float fRec73[3];
	float fRec72[3];
	float fConst128;
	float fConst129;
	float fRec63[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec62[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec61[3];
	float fConst136;
	float fConst137;
	float fRec60[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec59[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec58[3];
	float fConst147;
	float fConst148;
	float fRec57[3];
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fRec56[3];
	float fConst154;
	float fConst155;
	float fConst156;
	float fRec55[3];
	float fConst157;
	float fConst158;
	float fRec54[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fVec13[2];
	float fConst162;
	float fConst163;
	float fRec53[2];
	float fConst164;
	float fConst165;
	float fRec52[3];
	float fConst166;
	FAUSTFLOAT fEntry50;
	float fConst167;
	float fRec77[2];
	float fRec76[3];
	float fConst168;
	float fConst169;
	float fRec51[3];
	float fConst170;
	float fConst171;
	float fRec50[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec49[3];

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
		fConst2 = std::tan((1570.79639f / fConst0));
		fConst3 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst2))));
		fConst4 = std::tan((31.415926f / fConst0));
		fConst5 = (1.0f / fConst4);
		fConst6 = (fConst5 + 1.0f);
		fConst7 = (0.0f - (1.0f / (fConst4 * fConst6)));
		fConst8 = (1.0f / fConst0);
		fConst9 = (1.0f / fConst6);
		fConst10 = (1.0f - fConst5);
		fConst11 = (1.0f / fConst2);
		fConst12 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst13 = std::tan((219.911484f / fConst0));
		fConst14 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst15 = std::tan((18849.5566f / fConst0));
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
		fConst30 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst22))));
		fConst31 = (37699.1133f / fConst0);
		fConst32 = std::tan(fConst31);
		fConst33 = (1.0f / fConst32);
		fConst34 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst35 = (24836.4707f / fConst34);
		fConst36 = (1.0f / (((fConst33 + fConst35) / fConst32) + 1.0f));
		fConst37 = (785.398193f / fConst34);
		fConst38 = (((fConst33 - fConst37) / fConst32) + 1.0f);
		fConst39 = std::tan((21362.8301f / fConst0));
		fConst40 = (1.0f / fConst39);
		fConst41 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst42 = (19869.1758f / fConst41);
		fConst43 = (1.0f / (((fConst40 + fConst42) / fConst39) + 1.0f));
		fConst44 = (628.318542f / fConst41);
		fConst45 = (((fConst40 + fConst44) / fConst39) + 1.0f);
		fConst46 = std::tan((11938.0518f / fConst0));
		fConst47 = (1.0f / fConst46);
		fConst48 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst49 = (4701.22607f / fConst48);
		fConst50 = (1.0f / (((fConst47 + fConst49) / fConst46) + 1.0f));
		fConst51 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst46))));
		fConst52 = std::tan((9581.85742f / fConst0));
		fConst53 = (1.0f / fConst52);
		fConst54 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst55 = (2921.88965f / fConst54);
		fConst56 = (1.0f / (((fConst53 + fConst55) / fConst52) + 1.0f));
		fConst57 = (1036.72558f / fConst54);
		fConst58 = (((fConst53 + fConst57) / fConst52) + 1.0f);
		fConst59 = std::tan((5215.04394f / fConst0));
		fConst60 = (1.0f / fConst59);
		fConst61 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst62 = (3713.44482f / fConst61);
		fConst63 = (1.0f / (((fConst60 + fConst62) / fConst59) + 1.0f));
		fConst64 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst59))));
		fConst65 = (3707.07935f / fConst0);
		fConst66 = std::tan(fConst65);
		fConst67 = (1.0f / fConst66);
		fConst68 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst69 = (502.654816f / fConst68);
		fConst70 = (1.0f / (((fConst67 + fConst69) / fConst66) + 1.0f));
		fConst71 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst72 = std::tan((3518.58374f / fConst0));
		fConst73 = (1.0f / fConst72);
		fConst74 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst75 = (875.483398f / fConst74);
		fConst76 = (1.0f / (((fConst73 + fConst75) / fConst72) + 1.0f));
		fConst77 = (219.911484f / fConst74);
		fConst78 = (((fConst73 + fConst77) / fConst72) + 1.0f);
		fConst79 = std::tan((2010.61926f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst82 = (439.822968f / fConst81);
		fConst83 = (1.0f / (((fConst80 + fConst82) / fConst79) + 1.0f));
		fConst84 = (1390.84241f / fConst81);
		fConst85 = (((fConst80 + fConst84) / fConst79) + 1.0f);
		fConst86 = std::tan((1853.53967f / fConst0));
		fConst87 = (1.0f / fConst86);
		fConst88 = (fConst0 * std::sin(fConst65));
		fConst89 = (1059.9884f / fConst88);
		fConst90 = (1.0f / (((fConst87 + fConst89) / fConst86) + 1.0f));
		fConst91 = (188.49556f / fConst88);
		fConst92 = (((fConst87 - fConst91) / fConst86) + 1.0f);
		fConst93 = std::tan((17592.918f / fConst0));
		fConst94 = (1.0f / fConst93);
		fConst95 = (1.0f / (((fConst94 + 0.445041865f) / fConst93) + 1.0f));
		fConst96 = (1.0f / (((fConst94 + 1.24697959f) / fConst93) + 1.0f));
		fConst97 = (1.0f / (((fConst94 + 1.8019377f) / fConst93) + 1.0f));
		fConst98 = (fConst94 + 1.0f);
		fConst99 = (1.0f / fConst98);
		fConst100 = std::tan((34557.5195f / fConst0));
		fConst101 = (1.0f / fConst100);
		fConst102 = (1.0f / (((fConst101 + 1.0f) / fConst100) + 1.0f));
		fConst103 = (1.0f / (fConst101 + 1.0f));
		fConst104 = (1.0f - fConst101);
		fConst105 = std::tan((345.575195f / fConst0));
		fConst106 = (1.0f / fConst105);
		fConst107 = (1.0f / (((fConst106 + 0.765366852f) / fConst105) + 1.0f));
		fConst108 = AmpMono_faustpower2_f(fConst105);
		fConst109 = (1.0f / fConst108);
		fConst110 = (1.0f / (((fConst106 + 1.84775901f) / fConst105) + 1.0f));
		fConst111 = (2.0f * (1.0f - fConst109));
		fConst112 = (((fConst106 + -1.84775901f) / fConst105) + 1.0f);
		fConst113 = (0.0f - (2.0f / fConst108));
		fConst114 = (((fConst106 + -0.765366852f) / fConst105) + 1.0f);
		fConst115 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst100))));
		fConst116 = (((fConst101 + -1.0f) / fConst100) + 1.0f);
		fConst117 = (1.0f - fConst94);
		fConst118 = AmpMono_faustpower2_f(fConst93);
		fConst119 = (1.0f / fConst118);
		fConst120 = (2.0f * (1.0f - fConst119));
		fConst121 = (((fConst94 + -1.8019377f) / fConst93) + 1.0f);
		fConst122 = (((fConst94 + -1.24697959f) / fConst93) + 1.0f);
		fConst123 = (((fConst94 + -0.445041865f) / fConst93) + 1.0f);
		fConst124 = (1.0f / (fConst93 * fConst98));
		fConst125 = (0.0f - fConst124);
		fConst126 = (fConst117 / fConst98);
		fConst127 = (0.0f - (2.0f / fConst118));
		fConst128 = (((fConst87 - fConst89) / fConst86) + 1.0f);
		fConst129 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst86))));
		fConst130 = (((fConst87 + fConst91) / fConst86) + 1.0f);
		fConst131 = (((fConst80 - fConst82) / fConst79) + 1.0f);
		fConst132 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst79))));
		fConst133 = (((fConst80 - fConst84) / fConst79) + 1.0f);
		fConst134 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst72))));
		fConst135 = (((fConst73 - fConst75) / fConst72) + 1.0f);
		fConst136 = (((fConst73 - fConst77) / fConst72) + 1.0f);
		fConst137 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst138 = (1416.67383f / fConst68);
		fConst139 = (((fConst67 + fConst138) / fConst66) + 1.0f);
		fConst140 = (((fConst67 - fConst138) / fConst66) + 1.0f);
		fConst141 = (((fConst60 - fConst62) / fConst59) + 1.0f);
		fConst142 = (2481.85815f / fConst61);
		fConst143 = (((fConst60 + fConst142) / fConst59) + 1.0f);
		fConst144 = (((fConst60 - fConst142) / fConst59) + 1.0f);
		fConst145 = (((fConst53 - fConst55) / fConst52) + 1.0f);
		fConst146 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst52))));
		fConst147 = (((fConst53 - fConst57) / fConst52) + 1.0f);
		fConst148 = (((fConst47 - fConst49) / fConst46) + 1.0f);
		fConst149 = (2356.19458f / fConst48);
		fConst150 = (((fConst47 + fConst149) / fConst46) + 1.0f);
		fConst151 = (((fConst47 - fConst149) / fConst46) + 1.0f);
		fConst152 = (((fConst40 - fConst42) / fConst39) + 1.0f);
		fConst153 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst39))));
		fConst154 = (((fConst40 - fConst44) / fConst39) + 1.0f);
		fConst155 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst32))));
		fConst156 = (((fConst33 - fConst35) / fConst32) + 1.0f);
		fConst157 = (((fConst33 + fConst37) / fConst32) + 1.0f);
		fConst158 = (((fConst23 - fConst25) / fConst22) + 1.0f);
		fConst159 = (8796.45898f / fConst24);
		fConst160 = (((fConst23 + fConst159) / fConst22) + 1.0f);
		fConst161 = (((fConst23 - fConst159) / fConst22) + 1.0f);
		fConst162 = (1.0f - fConst18);
		fConst163 = (fConst162 / fConst27);
		fConst164 = (2.0f * (1.0f - fConst21));
		fConst165 = (((fConst18 + -1.0f) / fConst17) + 1.0f);
		fConst166 = (0.0f - (2.0f / fConst20));
		fConst167 = (1.0f / fConst27);
		fConst168 = (1.0f / fConst15);
		fConst169 = (3141.59277f / (fConst0 * std::sin(fConst31)));
		fConst170 = (1.0f / fConst13);
		fConst171 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst172 = std::tan((3769.91113f / fConst0));
		fConst173 = (1.0f / fConst172);
		fConst174 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));
		fConst175 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst172))));

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

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec9[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec11[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec10[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec12[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec8[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec14[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec16[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec18[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec17[l11] = 0.0f;

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
			fRec22[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec26[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec28[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec27[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec29[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec25[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec24[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec31[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec30[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec32[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec23[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec7[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec34[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec33[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec35[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec6[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec6[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec5[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec37[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec36[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec39[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec38[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec7[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec4[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec40[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec8[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec3[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec2[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec9[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec1[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec41[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fVec10[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec0[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec42[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec43[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec44[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec45[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec46[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec47[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec48[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec71[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec70[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fVec11[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec69[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec68[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fVec12[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 2); l66 = (l66 + 1)) {
			fRec67[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec66[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec65[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec64[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec75[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec74[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec73[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec72[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec63[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec62[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec61[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec60[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec59[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec58[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec57[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec56[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec55[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec54[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fVec13[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 2); l85 = (l85 + 1)) {
			fRec53[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec52[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 2); l87 = (l87 + 1)) {
			fRec77[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec76[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec51[l89] = 0.0f;

		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec50[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec49[l91] = 0.0f;

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

	void set_cab_brightness(FAUSTFLOAT value) { fEntry50 = value + 0.000000e+00f; }
	void set_cab_distance(FAUSTFLOAT value) { fEntry49 = value + 0.000000e+00f; }
	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry22 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry6 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry23 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry38 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry34 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry36 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry39 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry37 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry35 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry5 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry43 = value + 1.864208e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry3 = value + 1.132531e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry44 = value + -1.127463e+00f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry45 = value + -3.133557e-01f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry46 = value + 6.868355e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry40 = value + 1.825885e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry42 = value + 4.877098e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry41 = value + -2.237074e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry47 = value + 4.216220e-01f; }
	void set_tetrode_plate_sag_level(FAUSTFLOAT value) { fEntry48 = value + 1.536646e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry4 = value + 3.997976e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry16 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry17 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry26 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry27 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry24 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry25 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry18 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry13 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry15 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry14 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry11 = value + -1.772999e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry19 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry21 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry32 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry31 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry20 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry12 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry28 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry30 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry29 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry33 = value + 0.000000e+00f; }
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
		set_tetrode_plate_drift_depth(0.0f);
		set_tetrode_plate_drift_level(0.0f);
		set_tetrode_plate_drift_tau(0.0f);
		set_tetrode_plate_sag_depth(0.0f);
		set_tetrode_plate_sag_level(0.0f);
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
		float fSlow4 = std::exp(((3.45387769f * (float(fEntry3) + 1.0f)) + -2.30258512f));
		float fSlow5 = std::exp(((4.60517025f * (float(fEntry4) + 1.0f)) + -4.60517025f));
		float fSlow6 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry5) + 1.0f)) + -2.30258512f))));
		float fSlow7 = (1.0f / fSlow6);
		float fSlow8 = (fSlow7 + 1.0f);
		float fSlow9 = (0.0f - (1.0f / (fSlow6 * fSlow8)));
		float fSlow10 = (float(fEntry6) + 1.0f);
		float fSlow11 = (fSlow2 * std::exp((3.45387769f * fSlow10)));
		float fSlow12 = float(fEntry7);
		int iSlow13 = (fSlow12 < 0.0f);
		float fSlow14 = std::tan((fConst1 * ((iSlow13?(1500.0f * fSlow12):0.0f) + 2000.0f)));
		float fSlow15 = (1.0f / fSlow14);
		float fSlow16 = (1.0f - fSlow15);
		float fSlow17 = float(fEntry8);
		float fSlow18 = (fSlow17 + 1.0f);
		float fSlow19 = (1.0f - (0.5f * fSlow18));
		float fSlow20 = std::tan((fConst1 * ((25.0f * fSlow18) + (400.0f * fSlow19))));
		float fSlow21 = (1.0f / fSlow20);
		float fSlow22 = (fSlow21 + 1.0f);
		float fSlow23 = (0.0f - (1.0f / (fSlow20 * fSlow22)));
		float fSlow24 = float(fEntry9);
		float fSlow25 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow24) + -5.0f));
		float fSlow26 = ((float(fEntry10) + 1.0f) + 1.0f);
		float fSlow27 = (0.5f * fSlow26);
		float fSlow28 = AmpMono_faustpower3_f(fSlow27);
		float fSlow29 = (0.5f * (fSlow25 / fSlow28));
		float fSlow30 = std::exp(((3.45387769f * (float(fEntry11) + 1.0f)) + -2.30258512f));
		float fSlow31 = (0.294117659f / fSlow30);
		float fSlow32 = std::exp(((4.60517025f * (float(fEntry12) + 1.0f)) + -4.60517025f));
		float fSlow33 = (0.294117659f / fSlow32);
		float fSlow34 = (1.0f - (float(fEntry13) + 1.0f));
		float fSlow35 = (1.0f - (float(fEntry14) + 1.0f));
		float fSlow36 = (fSlow32 + (100.0f * (fSlow34 - fSlow35)));
		float fSlow37 = std::exp(((4.60517025f * (float(fEntry15) + 1.0f)) + -2.30258512f));
		float fSlow38 = (0.294117659f / fSlow37);
		float fSlow39 = (float(fEntry17) + 1.0f);
		float fSlow40 = ((float(fEntry16) + 1.0f) - fSlow39);
		float fSlow41 = (0.117647059f / fSlow39);
		float fSlow42 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry18) + 1.0f)) + -2.30258512f))));
		float fSlow43 = (1.0f / fSlow42);
		float fSlow44 = (fSlow43 + 1.0f);
		float fSlow45 = (0.0f - (1.0f / (fSlow42 * fSlow44)));
		float fSlow46 = std::exp(((2.30258512f * (float(fEntry19) + 1.0f)) + -2.30258512f));
		float fSlow47 = std::exp(((3.45387769f * (float(fEntry20) + 1.0f)) + -6.90775537f));
		float fSlow48 = (1.0f / ((fConst0 * fSlow47) + 1.0f));
		float fSlow49 = (100.0f * (1.0f - (float(fEntry21) + 1.0f)));
		float fSlow50 = (0.0f - fSlow49);
		float fSlow51 = (fSlow28 / fSlow2);
		float fSlow52 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow24) + -3.0f));
		float fSlow53 = (1.0f - (0.5f * fSlow52));
		float fSlow54 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow24) + -1.0f));
		float fSlow55 = (1.0f - (0.5f * fSlow54));
		float fSlow56 = (float(fEntry23) + 1.0f);
		float fSlow57 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry22) + 1.0f)))))) * std::exp((3.80045128f * fSlow56)));
		float fSlow58 = (1.0f / fSlow44);
		float fSlow59 = (1.0f - fSlow43);
		float fSlow60 = (fSlow57 / fSlow42);
		float fSlow61 = std::exp(((3.45387769f * (float(fEntry25) + 1.0f)) + -13.8155107f));
		float fSlow62 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry24) + 1.0f)) + -11.5129251f)) * fSlow61)) + 1.0f));
		float fSlow63 = (1.0f - fSlow62);
		float fSlow64 = (1.0f / ((fConst0 * fSlow61) + 1.0f));
		float fSlow65 = (5.0f * (1.0f - (float(fEntry26) + 1.0f)));
		float fSlow66 = (1.0f / ((fConst0 * (std::exp(((5.75646257f * (float(fEntry27) + 1.0f)) + -2.30258512f)) * fSlow61)) + 1.0f));
		float fSlow67 = (1.0f - fSlow66);
		float fSlow68 = (2.5f * fSlow40);
		float fSlow69 = ((100.0f * fSlow34) + fSlow37);
		float fSlow70 = std::exp(((2.30258512f * (float(fEntry28) + 1.0f)) + -2.30258512f));
		float fSlow71 = std::exp((0.0f - (fConst8 / std::exp(((3.45387769f * (float(fEntry29) + 1.0f)) + -6.90775537f)))));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = (100.0f * (1.0f - (float(fEntry30) + 1.0f)));
		float fSlow74 = (0.0f - fSlow73);
		float fSlow75 = (100.0f * fSlow35);
		float fSlow76 = (1.0f / ((fConst0 * (fSlow47 * std::exp((1.15129256f * (float(fEntry31) + 1.0f))))) + 1.0f));
		float fSlow77 = (1.0f - fSlow76);
		float fSlow78 = (1.0f - (float(fEntry32) + 1.0f));
		float fSlow79 = (100.0f * (fSlow35 - fSlow78));
		float fSlow80 = (100.0f * fSlow78);
		float fSlow81 = (fSlow54 / fSlow26);
		float fSlow82 = (0.5f * (fSlow26 / fSlow2));
		float fSlow83 = (fSlow42 * fSlow2);
		float fSlow84 = (0.5f * (fSlow26 / fSlow83));
		float fSlow85 = (fSlow66 + -1.0f);
		float fSlow86 = (fSlow76 + -1.0f);
		float fSlow87 = (1.0f / fSlow83);
		float fSlow88 = AmpMono_faustpower2_f(fSlow27);
		float fSlow89 = (0.5f * (fSlow52 / fSlow88));
		float fSlow90 = (fSlow88 / fSlow2);
		float fSlow91 = (fSlow88 / fSlow83);
		float fSlow92 = (fSlow28 / fSlow83);
		float fSlow93 = (1.0f - (0.5f * fSlow25));
		float fSlow94 = (5.0f * fSlow56);
		int iSlow95 = (fSlow94 < 9.0f);
		int iSlow96 = (fSlow94 < 8.0f);
		int iSlow97 = (fSlow94 < 7.0f);
		int iSlow98 = (fSlow94 < 6.0f);
		int iSlow99 = (fSlow94 < 5.0f);
		int iSlow100 = (fSlow94 < 4.0f);
		int iSlow101 = (fSlow94 < 3.0f);
		int iSlow102 = (fSlow94 < 2.0f);
		int iSlow103 = (fSlow94 < 1.0f);
		float fSlow104 = std::pow(10.0f, (0.0500000007f * (iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?(iSlow103?((fSlow94 < 0.0f)?0.0324000008f:(iSlow103?(0.0324000008f - (32.9620018f * fSlow56)):-6.55999994f)):(iSlow102?(-6.55999994f - (6.53999996f * (fSlow94 + -1.0f))):-13.1000004f)):(iSlow101?(-13.1000004f - (6.5f * (fSlow94 + -2.0f))):-19.6000004f)):(iSlow100?(-19.6000004f - (6.19999981f * (fSlow94 + -3.0f))):-25.7999992f)):(iSlow99?(-25.7999992f - (4.80000019f * (fSlow94 + -4.0f))):-30.6000004f)):(iSlow98?(-30.6000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow56))))):-32.7999992f)):(iSlow97?(-32.7999992f - (0.100000001f * (fSlow94 + -6.0f))):-32.9000015f)):(iSlow96?((0.400000006f * (fSlow94 + -7.0f)) + -32.9000015f):-32.5f)):(iSlow95?((0.300000012f * (fSlow94 + -8.0f)) + -32.5f):-32.2000008f)):((fSlow94 < 10.0f)?((0.100000001f * (fSlow94 + -9.0f)) + -32.2000008f):-32.0999985f))));
		float fSlow105 = (1.0f / fSlow22);
		float fSlow106 = (1.0f - fSlow21);
		float fSlow107 = (1.0f / (fSlow20 * fSlow2));
		float fSlow108 = std::pow(10.0f, (0.0500000007f * (fSlow17 * ((18.0f * fSlow19) + (4.5f * fSlow18)))));
		float fSlow109 = float(fEntry33);
		float fSlow110 = ((10.0f * fSlow109) + -14.0f);
		int iSlow111 = (fSlow110 > 0.0f);
		float fSlow112 = ((fSlow109 * ((fSlow17 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow113 = ((fConst12 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow110)))) * fSlow112);
		float fSlow114 = (fConst12 * fSlow112);
		float fSlow115 = (iSlow111?fSlow114:fSlow113);
		float fSlow116 = ((fConst11 * (fConst11 - fSlow115)) + 1.0f);
		float fSlow117 = ((fConst11 * (fConst11 + fSlow115)) + 1.0f);
		float fSlow118 = (iSlow111?fSlow113:fSlow114);
		float fSlow119 = ((fConst11 * (fConst11 + fSlow118)) + 1.0f);
		float fSlow120 = ((fConst11 * (fConst11 - fSlow118)) + 1.0f);
		float fSlow121 = (fSlow15 + 1.0f);
		float fSlow122 = (0.0f - (1.0f / (fSlow14 * fSlow121)));
		float fSlow123 = (fSlow14 * fSlow117);
		float fSlow124 = std::pow(10.0f, ((0.0500000007f * fSlow12) * (iSlow13?18.0f:9.0f)));
		float fSlow125 = (250.0f * (float(fEntry34) + 1.0f));
		float fSlow126 = (1.0f / fSlow8);
		float fSlow127 = (1.0f - fSlow7);
		float fSlow128 = std::exp((0.0f - (fConst8 / std::exp(((4.60517025f * (float(fEntry35) + 1.0f)) + -9.2103405f)))));
		float fSlow129 = (1.0f - fSlow128);
		float fSlow130 = (250.0f * (float(fEntry36) + 1.0f));
		float fSlow131 = std::exp(((4.60517025f * (float(fEntry37) + 1.0f)) + -9.2103405f));
		float fSlow132 = (1.0f / ((fConst0 * fSlow131) + 1.0f));
		float fSlow133 = (100.0f * (1.0f - (float(fEntry38) + 1.0f)));
		float fSlow134 = ((1.0f / ((fConst0 * (fSlow131 * std::exp(((4.60517025f * (float(fEntry39) + 1.0f)) + -4.60517025f)))) + 1.0f)) + -1.0f);
		float fSlow135 = std::exp(((2.30258512f * (float(fEntry40) + 1.0f)) + -2.30258512f));
		float fSlow136 = std::exp((0.0f - (fConst8 / std::exp(((3.45387769f * (float(fEntry41) + 1.0f)) + -6.90775537f)))));
		float fSlow137 = (1.0f - fSlow136);
		float fSlow138 = std::exp((0.0f - (10.0f * (1.0f - (float(fEntry42) + 1.0f)))));
		float fSlow139 = ((20.0f * (float(fEntry43) + 1.0f)) + 10.0f);
		float fSlow140 = std::exp(((2.30258512f * (float(fEntry44) + 1.0f)) + -2.30258512f));
		float fSlow141 = std::exp((0.0f - (fConst8 / std::exp(((3.45387769f * (float(fEntry45) + 1.0f)) + -6.90775537f)))));
		float fSlow142 = (1.0f - fSlow141);
		float fSlow143 = (1.0f / fSlow139);
		float fSlow144 = (0.294117659f / fSlow4);
		float fSlow145 = std::exp(((3.45387769f * (float(fEntry46) + 1.0f)) + -2.30258512f));
		float fSlow146 = (0.294117659f / fSlow145);
		float fSlow147 = (5.0f * fSlow10);
		int iSlow148 = (fSlow147 < 9.0f);
		int iSlow149 = (fSlow147 < 8.0f);
		int iSlow150 = (fSlow147 < 7.0f);
		int iSlow151 = (fSlow147 < 6.0f);
		int iSlow152 = (fSlow147 < 5.0f);
		int iSlow153 = (fSlow147 < 4.0f);
		int iSlow154 = (fSlow147 < 3.0f);
		int iSlow155 = (fSlow147 < 2.0f);
		int iSlow156 = (fSlow147 < 1.0f);
		float fSlow157 = std::pow(10.0f, (0.0500000007f * (iSlow148?(iSlow149?(iSlow150?(iSlow151?(iSlow152?(iSlow153?(iSlow154?(iSlow155?(iSlow156?((fSlow147 < 0.0f)?9.48999977f:(iSlow156?(9.48999977f - (29.6499996f * fSlow10)):3.55999994f)):(iSlow155?(3.55999994f - (5.8499999f * (fSlow147 + -1.0f))):-2.28999996f)):(iSlow154?(-2.28999996f - (5.75f * (fSlow147 + -2.0f))):-8.03999996f)):(iSlow153?(-8.03999996f - (5.55999994f * (fSlow147 + -3.0f))):-13.6000004f)):(iSlow152?(-13.6000004f - (4.5f * (fSlow147 + -4.0f))):-18.1000004f)):(iSlow151?(-18.1000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow10))))):-20.2999992f)):(iSlow150?(-20.2999992f - (0.600000024f * (fSlow147 + -6.0f))):-20.8999996f)):(iSlow149?((0.100000001f * (fSlow147 + -7.0f)) + -20.8999996f):-20.7999992f)):(iSlow148?((0.100000001f * (fSlow147 + -8.0f)) + -20.7999992f):-20.7000008f)):((fSlow147 < 10.0f)?((0.100000001f * (fSlow147 + -9.0f)) + -20.7000008f):-20.6000004f))));
		float fSlow158 = std::exp(((2.30258512f * (float(fEntry47) + 1.0f)) + -2.30258512f));
		float fSlow159 = (0.5f * (float(tanhf(float(float(fEntry48)))) + 1.0f));
		float fSlow160 = (fSlow142 / (1.00100005f - fSlow159));
		float fSlow161 = float(fEntry49);
		float fSlow162 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow161)));
		float fSlow163 = float(fEntry50);
		float fSlow164 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow163))));
		float fSlow165 = (15.0f * fSlow163);
		int iSlow166 = (fSlow165 > 0.0f);
		float fSlow167 = (fConst169 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow165))));
		float fSlow168 = (iSlow166?fConst169:fSlow167);
		float fSlow169 = ((fConst168 * (fConst168 - fSlow168)) + 1.0f);
		float fSlow170 = ((fConst168 * (fConst168 + fSlow168)) + 1.0f);
		float fSlow171 = (iSlow166?fSlow167:fConst169);
		float fSlow172 = ((fConst168 * (fConst168 + fSlow171)) + 1.0f);
		float fSlow173 = ((fConst168 * (fConst168 - fSlow171)) + 1.0f);
		float fSlow174 = (0.0f - (10.0f * fSlow161));
		int iSlow175 = (fSlow174 > 0.0f);
		float fSlow176 = (fConst171 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow174))));
		float fSlow177 = (iSlow175?fConst171:fSlow176);
		float fSlow178 = ((fConst170 * (fConst170 - fSlow177)) + 1.0f);
		float fSlow179 = ((fConst170 * (fConst170 + fSlow177)) + 1.0f);
		float fSlow180 = (iSlow175?fSlow176:fConst171);
		float fSlow181 = ((fConst170 * (fConst170 + fSlow180)) + 1.0f);
		float fSlow182 = ((fConst170 * (fConst170 - fSlow180)) + 1.0f);
		float fSlow183 = (0.0f - (17.0f * fSlow161));
		int iSlow184 = (fSlow183 > 0.0f);
		float fSlow185 = (fConst174 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow183))));
		float fSlow186 = (iSlow184?fConst174:fSlow185);
		float fSlow187 = ((fConst173 * (fConst173 - fSlow186)) + 1.0f);
		float fSlow188 = ((fConst173 * (fConst173 + fSlow186)) + 1.0f);
		float fSlow189 = (iSlow184?fSlow185:fConst174);
		float fSlow190 = ((fConst173 * (fConst173 - fSlow189)) + 1.0f);
		float fSlow191 = ((fConst173 * (fConst173 + fSlow189)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow57 * fTemp0);
			fRec9[0] = ((fSlow45 * fVec0[1]) - (fSlow58 * ((fSlow59 * fRec9[1]) - (fSlow60 * fTemp0))));
			fRec11[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec9[0])) - fRec11[1]))) + (fSlow67 * fRec11[1]));
			fRec10[0] = ((fSlow63 * fRec10[1]) + (fSlow62 * fRec11[0]));
			float fTemp1 = ((fRec9[0] - fRec10[0]) - fSlow68);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * ((2.5f * (fSlow40 + (fSlow39 * (((std::fabs((fTemp3 * fTemp2)) + -2.0f) * fTemp3) * fTemp2)))) + std::min<float>(0.0f, fTemp1))) - fSlow69);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow36 + (std::max<float>(0.0f, fTemp4) + (fSlow37 * ((((std::fabs((fTemp5 * fTemp6)) + -2.0f) * fTemp5) * fTemp6) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (std::fabs(fTemp8) + -2.0f);
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow32 * (((fTemp8 * (std::fabs((fTemp8 * fTemp9)) + -2.0f)) * fTemp9) + 1.0f)));
			fRec12[0] = ((fSlow71 * fRec12[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp10 - fSlow75)))));
			float fTemp11 = (fSlow70 * fRec12[0]);
			fRec8[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp10 - fTemp11) - fSlow75)) - fRec8[1])))) + (fSlow77 * fRec8[1]));
			float fTemp12 = (fSlow46 * fRec8[0]);
			float fTemp13 = (fSlow30 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow79));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (std::fabs(fTemp14) + -2.0f);
			float fTemp16 = (((fTemp12 + std::min<float>(0.0f, fTemp13)) - (fSlow30 * (1.0f - ((fTemp15 * (std::fabs((fTemp15 * fTemp14)) + -2.0f)) * fTemp14)))) - fSlow80);
			fVec1[0] = (fSlow82 * fTemp16);
			fRec14[0] = ((fSlow45 * fVec1[1]) + (fSlow58 * ((fSlow84 * fTemp16) - (fSlow59 * fRec14[1]))));
			fRec16[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec14[0])) - fRec16[1]))) - (fSlow85 * fRec16[1]));
			fRec15[0] = ((fSlow63 * fRec15[1]) + (fSlow62 * fRec16[0]));
			float fTemp17 = ((fRec14[0] - fRec15[0]) - fSlow68);
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (fTemp18 * (std::fabs(fTemp18) + -2.0f));
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) + (2.5f * (fSlow40 + (fSlow39 * (fTemp19 * (std::fabs(fTemp19) + -2.0f))))))) - fSlow69);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow36 + ((fSlow37 * ((((std::fabs((fTemp22 * fTemp21)) + -2.0f) * fTemp22) * fTemp21) + 1.0f)) + std::max<float>(0.0f, fTemp20))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = ((std::fabs(fTemp24) + -2.0f) * fTemp24);
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow32 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)));
			fRec18[0] = ((fSlow71 * fRec18[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp26 - fSlow75)))));
			float fTemp27 = (fSlow70 * fRec18[0]);
			fRec17[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp26 - fTemp27) - fSlow75)) - fRec17[1])))) - (fSlow86 * fRec17[1]));
			float fTemp28 = (fSlow46 * fRec17[0]);
			float fTemp29 = (fSlow30 + ((fTemp26 - (fTemp28 + fTemp27)) - fSlow79));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = ((std::fabs(fTemp30) + -2.0f) * fTemp30);
			float fTemp32 = (((std::min<float>(0.0f, fTemp29) + fTemp28) - (fSlow30 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow80);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec13[0] = ((fSlow45 * fVec2[1]) - (fSlow58 * ((fSlow59 * fRec13[1]) - (fSlow87 * fTemp32))));
			fRec20[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec13[0])) - fRec20[1]))) - (fSlow85 * fRec20[1]));
			fRec19[0] = ((fSlow62 * fRec20[0]) + (fSlow63 * fRec19[1]));
			float fTemp33 = ((fRec13[0] - fRec19[0]) - fSlow68);
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (fTemp34 * (std::fabs(fTemp34) + -2.0f));
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) + (2.5f * (fSlow40 + (fSlow39 * (fTemp35 * (std::fabs(fTemp35) + -2.0f))))))) - fSlow69);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (fTemp37 * (std::fabs(fTemp37) + -2.0f));
			float fTemp39 = (0.0f - (fSlow36 + (std::max<float>(0.0f, fTemp36) + (fSlow37 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = ((std::fabs(fTemp40) + -2.0f) * fTemp40);
			float fTemp42 = ((fSlow32 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp39));
			fRec21[0] = ((fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp42 - fSlow75)))) + (fSlow71 * fRec21[1]));
			float fTemp43 = (fSlow70 * fRec21[0]);
			fRec22[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp42 - fTemp43) - fSlow75)) - fRec22[1])))) + (fSlow77 * fRec22[1]));
			float fTemp44 = (fSlow46 * fRec22[0]);
			float fTemp45 = (fSlow30 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow79));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = ((fSlow55 * fTemp16) + (fSlow81 * (((std::min<float>(0.0f, fTemp45) + fTemp44) - (fSlow30 * (1.0f - ((fTemp46 * (std::fabs((fTemp46 * fTemp47)) + -2.0f)) * fTemp47)))) - fSlow80)));
			fVec3[0] = (fSlow90 * fTemp48);
			fRec26[0] = ((fSlow45 * fVec3[1]) - (fSlow58 * ((fSlow59 * fRec26[1]) - (fSlow91 * fTemp48))));
			fRec28[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec26[0])) - fRec28[1]))) + (fSlow67 * fRec28[1]));
			fRec27[0] = ((fSlow63 * fRec27[1]) + (fSlow62 * fRec28[0]));
			float fTemp49 = ((fRec26[0] - fRec27[0]) - fSlow68);
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (std::fabs(fTemp50) + -2.0f);
			float fTemp52 = ((fSlow2 * ((2.5f * (fSlow40 + (fSlow39 * (((std::fabs((fTemp51 * fTemp50)) + -2.0f) * fTemp51) * fTemp50)))) + std::min<float>(0.0f, fTemp49))) - fSlow69);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (std::fabs(fTemp53) + -2.0f);
			float fTemp55 = (0.0f - (fSlow36 + ((fSlow37 * (((fTemp53 * (std::fabs((fTemp53 * fTemp54)) + -2.0f)) * fTemp54) + 1.0f)) + std::max<float>(0.0f, fTemp52))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow32 * (((fTemp56 * (std::fabs((fTemp56 * fTemp57)) + -2.0f)) * fTemp57) + 1.0f)));
			fRec29[0] = ((fSlow71 * fRec29[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp58 - fSlow75)))));
			float fTemp59 = (fSlow70 * fRec29[0]);
			fRec25[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp58 - fTemp59) - fSlow75)) - fRec25[1])))) - (fSlow86 * fRec25[1]));
			float fTemp60 = (fSlow46 * fRec25[0]);
			float fTemp61 = (fSlow30 + ((fTemp58 - (fTemp59 + fTemp60)) - fSlow79));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (fTemp62 * (std::fabs(fTemp62) + -2.0f));
			float fTemp64 = (((fTemp60 + std::min<float>(0.0f, fTemp61)) - (fSlow30 * (1.0f - (fTemp63 * (std::fabs(fTemp63) + -2.0f))))) - fSlow80);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec24[0] = ((fSlow45 * fVec4[1]) - (fSlow58 * ((fSlow59 * fRec24[1]) - (fSlow87 * fTemp64))));
			fRec31[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec24[0])) - fRec31[1]))) + (fSlow67 * fRec31[1]));
			fRec30[0] = ((fSlow62 * fRec31[0]) + (fSlow63 * fRec30[1]));
			float fTemp65 = ((fRec24[0] - fRec30[0]) - fSlow68);
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) + (2.5f * (fSlow40 + (fSlow39 * (((std::fabs((fTemp66 * fTemp67)) + -2.0f) * fTemp66) * fTemp67)))))) - fSlow69);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow36 + ((fSlow37 * (((fTemp70 * (std::fabs((fTemp70 * fTemp69)) + -2.0f)) * fTemp69) + 1.0f)) + std::max<float>(0.0f, fTemp68))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (std::fabs(fTemp72) + -2.0f);
			float fTemp74 = (std::max<float>(0.0f, fTemp71) + (fSlow32 * (((fTemp73 * (std::fabs((fTemp73 * fTemp72)) + -2.0f)) * fTemp72) + 1.0f)));
			fRec32[0] = ((fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp74 - fSlow75)))) + (fSlow71 * fRec32[1]));
			float fTemp75 = (fSlow70 * fRec32[0]);
			fRec23[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp74 - fTemp75) - fSlow75)) - fRec23[1])))) - (fSlow86 * fRec23[1]));
			float fTemp76 = (fSlow46 * fRec23[0]);
			float fTemp77 = (fSlow30 + ((fTemp74 - (fTemp76 + fTemp75)) - fSlow79));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = ((fSlow53 * fTemp48) + (fSlow89 * (((fTemp76 + std::min<float>(0.0f, fTemp77)) - (fSlow30 * (1.0f - (((std::fabs((fTemp78 * fTemp79)) + -2.0f) * fTemp78) * fTemp79)))) - fSlow80)));
			fVec5[0] = (fSlow51 * fTemp80);
			fRec7[0] = ((fSlow45 * fVec5[1]) - (fSlow58 * ((fSlow59 * fRec7[1]) - (fSlow92 * fTemp80))));
			fRec34[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec7[0])) - fRec34[1]))) + (fSlow67 * fRec34[1]));
			fRec33[0] = ((fSlow63 * fRec33[1]) + (fSlow62 * fRec34[0]));
			float fTemp81 = ((fRec7[0] - fRec33[0]) - fSlow68);
			float fTemp82 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp81))));
			float fTemp83 = (std::fabs(fTemp82) + -2.0f);
			float fTemp84 = ((fSlow2 * (std::min<float>(0.0f, fTemp81) + (2.5f * (fSlow40 + (fSlow39 * (((std::fabs((fTemp82 * fTemp83)) + -2.0f) * fTemp82) * fTemp83)))))) - fSlow69);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp84))));
			float fTemp86 = (fTemp85 * (std::fabs(fTemp85) + -2.0f));
			float fTemp87 = (0.0f - (fSlow36 + (std::max<float>(0.0f, fTemp84) + (fSlow37 * ((fTemp86 * (std::fabs(fTemp86) + -2.0f)) + 1.0f)))));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = (std::fabs(fTemp88) + -2.0f);
			float fTemp90 = ((fSlow32 * ((((std::fabs((fTemp88 * fTemp89)) + -2.0f) * fTemp88) * fTemp89) + 1.0f)) + std::max<float>(0.0f, fTemp87));
			fRec35[0] = ((fSlow71 * fRec35[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp90 - fSlow75)))));
			float fTemp91 = (fSlow70 * fRec35[0]);
			fRec6[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp90 - fTemp91) - fSlow75)) - fRec6[1])))) + (fSlow77 * fRec6[1]));
			float fTemp92 = (fSlow46 * fRec6[0]);
			float fTemp93 = (fSlow30 + ((fTemp90 - (fTemp91 + fTemp92)) - fSlow79));
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = (std::fabs(fTemp94) + -2.0f);
			float fTemp96 = (((fTemp92 + std::min<float>(0.0f, fTemp93)) - (fSlow30 * (1.0f - ((fTemp94 * (std::fabs((fTemp94 * fTemp95)) + -2.0f)) * fTemp95)))) - fSlow80);
			fVec6[0] = (fSlow3 * fTemp96);
			fRec5[0] = ((fSlow45 * fVec6[1]) - (fSlow58 * ((fSlow59 * fRec5[1]) - (fSlow87 * fTemp96))));
			fRec37[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec5[0])) - fRec37[1]))) - (fSlow85 * fRec37[1]));
			fRec36[0] = ((fSlow62 * fRec37[0]) + (fSlow63 * fRec36[1]));
			float fTemp97 = ((fRec5[0] - fRec36[0]) - fSlow68);
			float fTemp98 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::max<float>(0.0f, fTemp97))));
			float fTemp99 = (std::fabs(fTemp98) + -2.0f);
			float fTemp100 = ((fSlow2 * ((2.5f * (fSlow40 + (fSlow39 * ((fTemp98 * (std::fabs((fTemp98 * fTemp99)) + -2.0f)) * fTemp99)))) + std::min<float>(0.0f, fTemp97))) - fSlow69);
			float fTemp101 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow38 * std::min<float>(0.0f, fTemp100))));
			float fTemp102 = (std::fabs(fTemp101) + -2.0f);
			float fTemp103 = (0.0f - (fSlow36 + ((fSlow37 * (((fTemp102 * (std::fabs((fTemp102 * fTemp101)) + -2.0f)) * fTemp101) + 1.0f)) + std::max<float>(0.0f, fTemp100))));
			float fTemp104 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow33 * std::min<float>(0.0f, fTemp103))));
			float fTemp105 = ((std::fabs(fTemp104) + -2.0f) * fTemp104);
			float fTemp106 = ((fSlow32 * ((fTemp105 * (std::fabs(fTemp105) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp103));
			fRec39[0] = ((fSlow71 * fRec39[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp106 - fSlow75)))));
			float fTemp107 = (fSlow70 * fRec39[0]);
			fRec38[0] = ((fSlow48 * std::max<float>(0.0f, (fSlow49 + (std::max<float>(fSlow50, ((fTemp106 - fTemp107) - fSlow75)) - fRec38[1])))) - (fSlow86 * fRec38[1]));
			float fTemp108 = (fSlow46 * fRec38[0]);
			float fTemp109 = (fSlow30 + ((fTemp106 - (fTemp108 + fTemp107)) - fSlow79));
			float fTemp110 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow31 * std::max<float>(0.0f, fTemp109))));
			float fTemp111 = (std::fabs(fTemp110) + -2.0f);
			float fTemp112 = (((fSlow29 * (((fSlow30 * ((((std::fabs((fTemp110 * fTemp111)) + -2.0f) * fTemp110) * fTemp111) + -1.0f)) + (fTemp108 + std::min<float>(0.0f, fTemp109))) - fSlow80)) + (fSlow93 * fTemp80)) * fSlow104);
			float fTemp113 = (fSlow3 * fTemp112);
			fVec7[0] = fTemp113;
			fRec4[0] = ((fSlow23 * fVec7[1]) - (fSlow105 * ((fSlow106 * fRec4[1]) - (fSlow107 * fTemp112))));
			fRec40[0] = (0.0f - (fSlow105 * ((fSlow106 * fRec40[1]) - (fTemp113 + fVec7[1]))));
			float fTemp114 = (fRec4[0] + (fSlow108 * fRec40[0]));
			fVec8[0] = fTemp114;
			fRec3[0] = ((fConst7 * fVec8[1]) - (fConst9 * ((fConst10 * fRec3[1]) - (fConst5 * fTemp114))));
			float fTemp115 = (fConst3 * fRec2[1]);
			fRec2[0] = (fRec3[0] - ((fTemp115 + (fRec2[2] * fSlow116)) / fSlow117));
			float fTemp116 = ((fTemp115 + (fRec2[0] * fSlow119)) + (fRec2[2] * fSlow120));
			float fTemp117 = (fTemp116 / fSlow117);
			fVec9[0] = fTemp117;
			fRec1[0] = (0.0f - (((fSlow16 * fRec1[1]) - (fTemp117 + fVec9[1])) / fSlow121));
			fRec41[0] = ((fSlow122 * fVec9[1]) - (((fSlow16 * fRec41[1]) - (fTemp116 / fSlow123)) / fSlow121));
			float fTemp118 = ((fSlow11 * (fRec1[0] + (fRec41[0] * fSlow124))) - fSlow125);
			fVec10[0] = fTemp118;
			fRec0[0] = ((fSlow9 * fVec10[1]) - (fSlow126 * ((fSlow127 * fRec0[1]) - (fSlow7 * fTemp118))));
			fRec42[0] = ((fSlow128 * fRec42[1]) + (fSlow129 * (fRec0[0] - fSlow130)));
			fRec43[0] = ((fSlow132 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow133 + ((fRec0[0] - fRec42[0]) - fSlow130))) - fRec43[1]))) - (fSlow134 * fRec43[1]));
			float fTemp119 = (fSlow5 * ((fRec0[0] - (fRec42[0] + fRec43[0])) - fSlow130));
			fRec44[0] = ((fSlow136 * fRec44[1]) + (fSlow137 * (std::max<float>(fSlow138, fTemp119) - fSlow138)));
			float fTemp120 = (fSlow135 * fRec44[0]);
			fRec45[0] = ((fSlow141 * fRec45[1]) + (fSlow142 * std::min<float>(1.0f, std::fabs((fSlow143 * (fTemp119 - fTemp120))))));
			float fTemp121 = (fSlow139 / ((fSlow140 * fRec45[0]) + 1.0f));
			float fTemp122 = (fSlow4 + (fTemp119 - (fTemp120 + fTemp121)));
			float fTemp123 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow144 * std::max<float>(0.0f, fTemp122))));
			float fTemp124 = (std::fabs(fTemp123) + -2.0f);
			float fTemp125 = (((std::min<float>(0.0f, fTemp122) + fTemp121) - (fSlow4 * (1.0f - ((fTemp123 * (std::fabs((fTemp123 * fTemp124)) + -2.0f)) * fTemp124)))) - fSlow145);
			fRec46[0] = ((fSlow137 * (std::max<float>(fSlow138, (0.0f - fTemp119)) - fSlow138)) + (fSlow136 * fRec46[1]));
			float fTemp126 = (fTemp119 + (fSlow135 * fRec46[0]));
			fRec47[0] = ((fSlow141 * fRec47[1]) + (fSlow142 * std::min<float>(1.0f, std::fabs((fSlow143 * (0.0f - fTemp126))))));
			float fTemp127 = (fSlow139 / ((fSlow140 * fRec47[0]) + 1.0f));
			float fTemp128 = (fSlow4 - (fTemp126 + fTemp127));
			float fTemp129 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow144 * std::max<float>(0.0f, fTemp128))));
			float fTemp130 = (std::fabs(fTemp129) + -2.0f);
			float fTemp131 = ((((fSlow4 * (((fTemp130 * (std::fabs((fTemp130 * fTemp129)) + -2.0f)) * fTemp129) + -1.0f)) + std::min<float>(0.0f, fTemp128)) + fTemp127) - fSlow145);
			float fTemp132 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow146 * std::min<float>(0.0f, fTemp131))));
			float fTemp133 = ((std::fabs(fTemp132) + -2.0f) * fTemp132);
			float fTemp134 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow146 * std::min<float>(0.0f, fTemp125))));
			float fTemp135 = (std::fabs(fTemp134) + -2.0f);
			float fTemp136 = (std::max<float>(0.0f, fTemp125) - (std::max<float>(0.0f, fTemp131) + (fSlow145 * (((fTemp133 * (std::fabs(fTemp133) + -2.0f)) + 1.0f) - (((fTemp135 * (std::fabs((fTemp135 * fTemp134)) + -2.0f)) * fTemp134) + 1.0f)))));
			fRec48[0] = ((fSlow141 * fRec48[1]) + (fSlow160 * (std::max<float>(fSlow159, (fSlow143 * fTemp136)) - fSlow159)));
			float fTemp137 = (fSlow3 * ((fTemp136 * fSlow157) / ((fSlow158 * fRec48[0]) + 1.0f)));
			fRec71[0] = (fTemp137 - (fConst110 * ((fConst111 * fRec71[1]) + (fConst112 * fRec71[2]))));
			fRec70[0] = ((fConst110 * ((fConst109 * fRec71[2]) + ((fConst109 * fRec71[0]) + (fConst113 * fRec71[1])))) - (fConst107 * ((fConst114 * fRec70[2]) + (fConst111 * fRec70[1]))));
			float fTemp138 = ((fConst109 * fRec70[2]) + ((fConst109 * fRec70[0]) + (fConst113 * fRec70[1])));
			fVec11[0] = fTemp138;
			fRec69[0] = (0.0f - (fConst103 * ((fConst104 * fRec69[1]) - (fConst107 * (fVec11[1] + fTemp138)))));
			fRec68[0] = (fRec69[0] - (fConst102 * ((fConst115 * fRec68[1]) + (fConst116 * fRec68[2]))));
			float fTemp139 = (fRec68[2] + (fRec68[0] + (2.0f * fRec68[1])));
			fVec12[0] = fTemp139;
			fRec67[0] = (fConst99 * ((fConst102 * (fVec12[1] + fTemp139)) - (fConst117 * fRec67[1])));
			fRec66[0] = (fRec67[0] - (fConst97 * ((fConst120 * fRec66[1]) + (fConst121 * fRec66[2]))));
			fRec65[0] = ((fConst97 * ((fRec66[0] + (2.0f * fRec66[1])) + fRec66[2])) - (fConst96 * ((fConst120 * fRec65[1]) + (fConst122 * fRec65[2]))));
			fRec64[0] = ((fConst96 * ((fRec65[0] + (2.0f * fRec65[1])) + fRec65[2])) - (fConst95 * ((fConst120 * fRec64[1]) + (fConst123 * fRec64[2]))));
			fRec75[0] = ((fConst102 * ((fConst125 * fVec12[1]) + (fConst124 * fTemp139))) - (fConst126 * fRec75[1]));
			fRec74[0] = (fRec75[0] - (fConst97 * ((fConst121 * fRec74[2]) + (fConst120 * fRec74[1]))));
			fRec73[0] = ((fConst97 * (((fConst119 * fRec74[0]) + (fConst127 * fRec74[1])) + (fConst119 * fRec74[2]))) - (fConst96 * ((fConst120 * fRec73[1]) + (fConst122 * fRec73[2]))));
			fRec72[0] = ((fConst96 * (((fConst119 * fRec73[0]) + (fConst127 * fRec73[1])) + (fConst119 * fRec73[2]))) - (fConst95 * ((fConst123 * fRec72[2]) + (fConst120 * fRec72[1]))));
			float fTemp140 = (fConst129 * fRec63[1]);
			fRec63[0] = ((fConst95 * (((fRec64[0] + (2.0f * fRec64[1])) + fRec64[2]) + (0.0316227749f * (((fConst119 * fRec72[0]) + (fConst127 * fRec72[1])) + (fConst119 * fRec72[2]))))) - (fConst90 * ((fConst128 * fRec63[2]) + fTemp140)));
			float fTemp141 = (fConst132 * fRec62[1]);
			fRec62[0] = ((fConst90 * ((fConst92 * fRec63[2]) + (fTemp140 + (fConst130 * fRec63[0])))) - (fConst83 * ((fConst131 * fRec62[2]) + fTemp141)));
			float fTemp142 = (fConst134 * fRec61[1]);
			fRec61[0] = ((fConst83 * (((fConst85 * fRec62[0]) + fTemp141) + (fConst133 * fRec62[2]))) - (fConst76 * (fTemp142 + (fConst135 * fRec61[2]))));
			float fTemp143 = (fConst71 * fRec60[1]);
			fRec60[0] = ((fConst76 * (((fConst78 * fRec61[0]) + fTemp142) + (fConst136 * fRec61[2]))) - (fConst70 * ((fConst137 * fRec60[2]) + fTemp143)));
			float fTemp144 = (fConst64 * fRec59[1]);
			fRec59[0] = ((fConst70 * ((fTemp143 + (fConst139 * fRec60[0])) + (fConst140 * fRec60[2]))) - (fConst63 * (fTemp144 + (fConst141 * fRec59[2]))));
			float fTemp145 = (fConst146 * fRec58[1]);
			fRec58[0] = ((fConst63 * ((fTemp144 + (fConst143 * fRec59[0])) + (fConst144 * fRec59[2]))) - (fConst56 * ((fConst145 * fRec58[2]) + fTemp145)));
			float fTemp146 = (fConst51 * fRec57[1]);
			fRec57[0] = ((fConst56 * (((fConst58 * fRec58[0]) + fTemp145) + (fConst147 * fRec58[2]))) - (fConst50 * ((fConst148 * fRec57[2]) + fTemp146)));
			float fTemp147 = (fConst153 * fRec56[1]);
			fRec56[0] = ((fConst50 * ((fTemp146 + (fConst150 * fRec57[0])) + (fConst151 * fRec57[2]))) - (fConst43 * ((fConst152 * fRec56[2]) + fTemp147)));
			float fTemp148 = (fConst155 * fRec55[1]);
			fRec55[0] = ((fConst43 * (((fConst45 * fRec56[0]) + fTemp147) + (fConst154 * fRec56[2]))) - (fConst36 * (fTemp148 + (fConst156 * fRec55[2]))));
			float fTemp149 = (fConst30 * fRec54[1]);
			fRec54[0] = ((fConst36 * ((fConst38 * fRec55[2]) + (fTemp148 + (fConst157 * fRec55[0])))) - (fConst26 * ((fConst158 * fRec54[2]) + fTemp149)));
			float fTemp150 = ((fTemp149 + (fConst160 * fRec54[0])) + (fConst161 * fRec54[2]));
			fVec13[0] = fTemp150;
			fRec53[0] = ((fConst26 * ((fConst29 * fVec13[1]) + (fConst28 * fTemp150))) - (fConst163 * fRec53[1]));
			fRec52[0] = (fRec53[0] - (fConst19 * ((fConst164 * fRec52[1]) + (fConst165 * fRec52[2]))));
			fRec77[0] = (fConst167 * ((fConst26 * (fVec13[1] + fTemp150)) - (fConst162 * fRec77[1])));
			fRec76[0] = (fRec77[0] - (fConst19 * ((fConst165 * fRec76[2]) + (fConst164 * fRec76[1]))));
			float fTemp151 = (fConst16 * fRec51[1]);
			fRec51[0] = ((fConst19 * (((fConst21 * fRec52[2]) + ((fConst166 * fRec52[1]) + (fConst21 * fRec52[0]))) + (fSlow164 * (fRec76[2] + (fRec76[0] + (2.0f * fRec76[1])))))) - ((fTemp151 + (fRec51[2] * fSlow169)) / fSlow170));
			float fTemp152 = (fConst14 * fRec50[1]);
			fRec50[0] = ((((fTemp151 + (fRec51[0] * fSlow172)) + (fRec51[2] * fSlow173)) / fSlow170) - (((fSlow178 * fRec50[2]) + fTemp152) / fSlow179));
			float fTemp153 = (fConst175 * fRec49[1]);
			fRec49[0] = ((((fTemp152 + (fRec50[0] * fSlow181)) + (fRec50[2] * fSlow182)) / fSlow179) - (((fSlow187 * fRec49[2]) + fTemp153) / fSlow188));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow162 * (((fRec49[2] * fSlow190) + (fTemp153 + (fRec49[0] * fSlow191))) / fSlow188)):fTemp137)));
			fVec0[1] = fVec0[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec8[1] = fRec8[0];
			fVec1[1] = fVec1[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fVec2[1] = fVec2[0];
			fRec13[1] = fRec13[0];
			fRec20[1] = fRec20[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec22[1] = fRec22[0];
			fVec3[1] = fVec3[0];
			fRec26[1] = fRec26[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec25[1] = fRec25[0];
			fVec4[1] = fVec4[0];
			fRec24[1] = fRec24[0];
			fRec31[1] = fRec31[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec23[1] = fRec23[0];
			fVec5[1] = fVec5[0];
			fRec7[1] = fRec7[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fRec6[1] = fRec6[0];
			fVec6[1] = fVec6[0];
			fRec5[1] = fRec5[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fVec7[1] = fVec7[0];
			fRec4[1] = fRec4[0];
			fRec40[1] = fRec40[0];
			fVec8[1] = fVec8[0];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec9[1] = fVec9[0];
			fRec1[1] = fRec1[0];
			fRec41[1] = fRec41[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
			fRec42[1] = fRec42[0];
			fRec43[1] = fRec43[0];
			fRec44[1] = fRec44[0];
			fRec45[1] = fRec45[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fRec48[1] = fRec48[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fVec11[1] = fVec11[0];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fVec12[1] = fVec12[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec75[1] = fRec75[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
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
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fVec13[1] = fVec13[0];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];

		}

	}


};

#endif
