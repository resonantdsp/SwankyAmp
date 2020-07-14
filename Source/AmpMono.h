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
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fEntry6;
	float fConst6;
	float fConst7;
	FAUSTFLOAT fEntry7;
	float fConst8;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
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
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	float fVec0[2];
	float fRec21[2];
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	float fRec23[2];
	float fRec22[2];
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	FAUSTFLOAT fEntry37;
	float fRec24[2];
	float fRec25[2];
	FAUSTFLOAT fEntry38;
	float fVec1[2];
	float fRec20[2];
	float fVec2[2];
	float fRec31[2];
	float fRec33[2];
	float fRec32[2];
	float fRec34[2];
	float fRec30[2];
	float fVec3[2];
	float fRec29[2];
	float fVec4[2];
	float fRec28[2];
	float fRec36[2];
	float fRec35[2];
	float fRec37[2];
	float fRec27[2];
	float fVec5[2];
	float fRec26[2];
	float fVec6[2];
	float fRec19[2];
	float fRec39[2];
	float fRec38[2];
	float fRec40[2];
	float fRec18[2];
	float fVec7[2];
	float fRec17[2];
	float fVec8[2];
	float fRec16[2];
	float fRec42[2];
	float fRec41[2];
	float fRec43[2];
	float fRec15[2];
	float fVec9[2];
	float fRec14[2];
	float fVec10[2];
	float fRec13[2];
	float fRec45[2];
	float fRec44[2];
	float fRec46[2];
	float fRec12[2];
	float fVec11[2];
	float fRec11[2];
	float fVec12[2];
	float fRec10[2];
	float fRec48[2];
	float fRec47[2];
	float fRec49[2];
	float fRec50[2];
	float fVec13[2];
	float fRec9[2];
	float fVec14[2];
	float fRec8[2];
	float fRec51[2];
	float fVec15[2];
	float fConst15;
	float fConst16;
	float fRec7[2];
	float fConst17;
	FAUSTFLOAT fEntry39;
	float fConst18;
	float fConst19;
	float fRec6[3];
	float fConst20;
	float fRec5[3];
	float fVec16[2];
	FAUSTFLOAT fEntry40;
	float fRec4[2];
	float fRec52[2];
	float fConst21;
	float fConst22;
	FAUSTFLOAT fEntry41;
	float fConst23;
	float fConst24;
	float fRec3[3];
	FAUSTFLOAT fEntry42;
	float fVec17[2];
	float fRec2[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	float fRec53[2];
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	float fRec54[2];
	FAUSTFLOAT fEntry48;
	FAUSTFLOAT fEntry49;
	float fRec55[2];
	FAUSTFLOAT fEntry50;
	FAUSTFLOAT fEntry51;
	FAUSTFLOAT fEntry52;
	float fRec56[2];
	FAUSTFLOAT fEntry53;
	float fRec57[2];
	float fRec58[2];
	FAUSTFLOAT fEntry54;
	FAUSTFLOAT fEntry55;
	FAUSTFLOAT fEntry56;
	float fRec59[2];
	float fConst25;
	float fRec1[3];
	float fRec0[2];
	FAUSTFLOAT fEntry57;
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
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec82[3];
	float fConst127;
	float fConst128;
	float fRec81[3];
	float fVec18[2];
	float fRec80[2];
	float fConst129;
	float fConst130;
	float fRec79[3];
	float fVec19[2];
	float fConst131;
	float fConst132;
	float fRec78[2];
	float fConst133;
	float fConst134;
	float fRec77[3];
	float fConst135;
	float fRec76[3];
	float fConst136;
	float fRec75[3];
	float fConst137;
	float fRec86[2];
	float fRec85[3];
	float fRec84[3];
	float fRec83[3];
	float fConst138;
	float fConst139;
	float fRec74[3];
	float fConst140;
	float fConst141;
	float fRec73[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec72[3];
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec71[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fRec70[3];
	float fConst155;
	float fConst156;
	float fRec69[3];
	float fConst157;
	float fConst158;
	float fConst159;
	float fConst160;
	float fRec68[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fConst165;
	float fRec67[3];
	float fConst166;
	float fConst167;
	float fRec66[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fConst172;
	float fRec65[3];
	float fConst173;
	float fVec20[2];
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec64[2];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec63[3];
	FAUSTFLOAT fEntry58;
	float fConst180;
	float fRec88[2];
	float fRec87[3];
	float fConst181;
	float fConst182;
	float fRec62[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec61[3];
	float fConst187;
	float fConst188;
	float fRec60[3];

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
		fConst2 = (2.0f / fConst0);
		fConst3 = (2.0f * fConst0);
		fConst4 = (3.14159274f / fConst0);
		fConst5 = (0.5f * fConst0);
		fConst6 = (0.5f / fConst0);
		fConst7 = (4.0f * AmpMono_faustpower2_f(fConst0));
		fConst8 = AmpMono_faustpower2_f(fConst1);
		fConst9 = std::tan((1570.79639f / fConst0));
		fConst10 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst11 = std::tan((31.415926f / fConst0));
		fConst12 = (1.0f / fConst11);
		fConst13 = (fConst12 + 1.0f);
		fConst14 = (0.0f - (1.0f / (fConst11 * fConst13)));
		fConst15 = (1.0f / fConst13);
		fConst16 = (1.0f - fConst12);
		fConst17 = (1.0f / fConst9);
		fConst18 = (fConst0 * std::sin((3141.59277f / fConst0)));
		fConst19 = (3.14159274f / fConst18);
		fConst20 = (3141.59277f / fConst18);
		fConst21 = std::tan((12566.3711f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
		fConst24 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst21))));
		fConst25 = (2.0f * fConst8);
		fConst26 = std::tan((3769.91113f / fConst0));
		fConst27 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst26))));
		fConst28 = std::tan((18849.5566f / fConst0));
		fConst29 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
		fConst30 = std::tan((3455.75195f / fConst0));
		fConst31 = (1.0f / fConst30);
		fConst32 = (1.0f / (((fConst31 + 1.0f) / fConst30) + 1.0f));
		fConst33 = AmpMono_faustpower2_f(fConst30);
		fConst34 = (0.0f - (2.0f / fConst33));
		fConst35 = std::tan((2984.51294f / fConst0));
		fConst36 = (1.0f / fConst35);
		fConst37 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst38 = (27816.8476f / fConst37);
		fConst39 = (1.0f / (((fConst36 + fConst38) / fConst35) + 1.0f));
		fConst40 = (fConst31 + 1.0f);
		fConst41 = (1.0f / (fConst30 * fConst40));
		fConst42 = (8796.45898f / fConst37);
		fConst43 = (((fConst36 - fConst42) / fConst35) + 1.0f);
		fConst44 = (37699.1133f / fConst0);
		fConst45 = std::tan(fConst44);
		fConst46 = (1.0f / fConst45);
		fConst47 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst48 = (24836.4707f / fConst47);
		fConst49 = (1.0f / (((fConst46 + fConst48) / fConst45) + 1.0f));
		fConst50 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst45))));
		fConst51 = std::tan((21362.8301f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst54 = (19869.1758f / fConst53);
		fConst55 = (1.0f / (((fConst52 + fConst54) / fConst51) + 1.0f));
		fConst56 = (628.318542f / fConst53);
		fConst57 = (((fConst52 + fConst56) / fConst51) + 1.0f);
		fConst58 = std::tan((11938.0518f / fConst0));
		fConst59 = (1.0f / fConst58);
		fConst60 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst61 = (4701.22607f / fConst60);
		fConst62 = (1.0f / (((fConst59 + fConst61) / fConst58) + 1.0f));
		fConst63 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst58))));
		fConst64 = std::tan((9581.85742f / fConst0));
		fConst65 = (1.0f / fConst64);
		fConst66 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst67 = (2921.88965f / fConst66);
		fConst68 = (1.0f / (((fConst65 + fConst67) / fConst64) + 1.0f));
		fConst69 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst64))));
		fConst70 = std::tan((5215.04394f / fConst0));
		fConst71 = (1.0f / fConst70);
		fConst72 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst73 = (3713.44482f / fConst72);
		fConst74 = (1.0f / (((fConst71 + fConst73) / fConst70) + 1.0f));
		fConst75 = (2481.85815f / fConst72);
		fConst76 = (((fConst71 + fConst75) / fConst70) + 1.0f);
		fConst77 = (3707.07935f / fConst0);
		fConst78 = std::tan(fConst77);
		fConst79 = (1.0f / fConst78);
		fConst80 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst81 = (502.654816f / fConst80);
		fConst82 = (1.0f / (((fConst79 + fConst81) / fConst78) + 1.0f));
		fConst83 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst78))));
		fConst84 = std::tan((3518.58374f / fConst0));
		fConst85 = (1.0f / fConst84);
		fConst86 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst87 = (875.483398f / fConst86);
		fConst88 = (1.0f / (((fConst85 + fConst87) / fConst84) + 1.0f));
		fConst89 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst84))));
		fConst90 = std::tan((2010.61926f / fConst0));
		fConst91 = (1.0f / fConst90);
		fConst92 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst93 = (439.822968f / fConst92);
		fConst94 = (1.0f / (((fConst91 + fConst93) / fConst90) + 1.0f));
		fConst95 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst90))));
		fConst96 = std::tan((1853.53967f / fConst0));
		fConst97 = (1.0f / fConst96);
		fConst98 = (fConst0 * std::sin(fConst77));
		fConst99 = (1059.9884f / fConst98);
		fConst100 = (1.0f / (((fConst97 + fConst99) / fConst96) + 1.0f));
		fConst101 = (188.49556f / fConst98);
		fConst102 = (((fConst97 - fConst101) / fConst96) + 1.0f);
		fConst103 = std::tan((17592.918f / fConst0));
		fConst104 = (1.0f / fConst103);
		fConst105 = (1.0f / (((fConst104 + 0.445041865f) / fConst103) + 1.0f));
		fConst106 = AmpMono_faustpower2_f(fConst103);
		fConst107 = (1.0f / fConst106);
		fConst108 = (1.0f / (((fConst104 + 1.24697959f) / fConst103) + 1.0f));
		fConst109 = (0.0f - (2.0f / fConst106));
		fConst110 = (1.0f / (((fConst104 + 1.8019377f) / fConst103) + 1.0f));
		fConst111 = std::tan((34557.5195f / fConst0));
		fConst112 = (1.0f / fConst111);
		fConst113 = (1.0f / (((fConst112 + 1.0f) / fConst111) + 1.0f));
		fConst114 = (fConst104 + 1.0f);
		fConst115 = (1.0f / (fConst103 * fConst114));
		fConst116 = (0.0f - fConst115);
		fConst117 = (1.0f / (fConst112 + 1.0f));
		fConst118 = (1.0f - fConst112);
		fConst119 = std::tan((345.575195f / fConst0));
		fConst120 = (1.0f / fConst119);
		fConst121 = (1.0f / (((fConst120 + 0.765366852f) / fConst119) + 1.0f));
		fConst122 = AmpMono_faustpower2_f(fConst119);
		fConst123 = (1.0f / fConst122);
		fConst124 = (1.0f / (((fConst120 + 1.84775901f) / fConst119) + 1.0f));
		fConst125 = (((fConst120 + -1.84775901f) / fConst119) + 1.0f);
		fConst126 = (2.0f * (1.0f - fConst123));
		fConst127 = (0.0f - (2.0f / fConst122));
		fConst128 = (((fConst120 + -0.765366852f) / fConst119) + 1.0f);
		fConst129 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst111))));
		fConst130 = (((fConst112 + -1.0f) / fConst111) + 1.0f);
		fConst131 = (1.0f - fConst104);
		fConst132 = (fConst131 / fConst114);
		fConst133 = (((fConst104 + -1.8019377f) / fConst103) + 1.0f);
		fConst134 = (2.0f * (1.0f - fConst107));
		fConst135 = (((fConst104 + -1.24697959f) / fConst103) + 1.0f);
		fConst136 = (((fConst104 + -0.445041865f) / fConst103) + 1.0f);
		fConst137 = (1.0f / fConst114);
		fConst138 = (((fConst97 - fConst99) / fConst96) + 1.0f);
		fConst139 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst96))));
		fConst140 = (((fConst97 + fConst101) / fConst96) + 1.0f);
		fConst141 = (((fConst91 - fConst93) / fConst90) + 1.0f);
		fConst142 = (1390.84241f / fConst92);
		fConst143 = (((fConst91 + fConst142) / fConst90) + 1.0f);
		fConst144 = (((fConst91 - fConst142) / fConst90) + 1.0f);
		fConst145 = (((fConst85 - fConst87) / fConst84) + 1.0f);
		fConst146 = (219.911484f / fConst86);
		fConst147 = (((fConst85 + fConst146) / fConst84) + 1.0f);
		fConst148 = (((fConst85 - fConst146) / fConst84) + 1.0f);
		fConst149 = (((fConst79 - fConst81) / fConst78) + 1.0f);
		fConst150 = (1416.67383f / fConst80);
		fConst151 = (((fConst79 + fConst150) / fConst78) + 1.0f);
		fConst152 = (((fConst79 - fConst150) / fConst78) + 1.0f);
		fConst153 = (((fConst71 - fConst73) / fConst70) + 1.0f);
		fConst154 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst70))));
		fConst155 = (((fConst71 - fConst75) / fConst70) + 1.0f);
		fConst156 = (((fConst65 - fConst67) / fConst64) + 1.0f);
		fConst157 = (1036.72558f / fConst66);
		fConst158 = (((fConst65 + fConst157) / fConst64) + 1.0f);
		fConst159 = (((fConst65 - fConst157) / fConst64) + 1.0f);
		fConst160 = (((fConst59 - fConst61) / fConst58) + 1.0f);
		fConst161 = (2356.19458f / fConst60);
		fConst162 = (((fConst59 + fConst161) / fConst58) + 1.0f);
		fConst163 = (((fConst59 - fConst161) / fConst58) + 1.0f);
		fConst164 = (((fConst52 - fConst54) / fConst51) + 1.0f);
		fConst165 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst51))));
		fConst166 = (((fConst52 - fConst56) / fConst51) + 1.0f);
		fConst167 = (((fConst46 - fConst48) / fConst45) + 1.0f);
		fConst168 = (785.398193f / fConst47);
		fConst169 = (((fConst46 + fConst168) / fConst45) + 1.0f);
		fConst170 = (((fConst46 - fConst168) / fConst45) + 1.0f);
		fConst171 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst35))));
		fConst172 = (((fConst36 - fConst38) / fConst35) + 1.0f);
		fConst173 = (((fConst36 + fConst42) / fConst35) + 1.0f);
		fConst174 = (0.0f - fConst41);
		fConst175 = (1.0f - fConst31);
		fConst176 = (fConst175 / fConst40);
		fConst177 = (((fConst31 + -1.0f) / fConst30) + 1.0f);
		fConst178 = (1.0f / fConst33);
		fConst179 = (2.0f * (1.0f - fConst178));
		fConst180 = (1.0f / fConst40);
		fConst181 = (1.0f / fConst28);
		fConst182 = (3141.59277f / (fConst0 * std::sin(fConst44)));
		fConst183 = std::tan((219.911484f / fConst0));
		fConst184 = (1.0f / fConst183);
		fConst185 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst186 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst183))));
		fConst187 = (1.0f / fConst26);
		fConst188 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));

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
		fEntry57 = FAUSTFLOAT(0.0f);
		fEntry58 = FAUSTFLOAT(0.0f);

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec21[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec23[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec22[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec24[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec25[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec20[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec2[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec31[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec33[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec32[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec34[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec30[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec3[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec29[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec4[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec28[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec36[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec35[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec37[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec27[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec5[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec26[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec6[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec19[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec39[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec38[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec40[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec18[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec7[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec17[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec8[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec16[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec42[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec41[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec43[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec15[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fVec9[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec14[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec10[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec13[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec45[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec44[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec46[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec12[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec11[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec11[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec12[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec10[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec48[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec47[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec49[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec50[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fVec13[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec9[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fVec14[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec8[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec51[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fVec15[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fRec7[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec6[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec5[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fVec16[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec4[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
			fRec52[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec3[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
			fVec17[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
			fRec2[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec53[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec54[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec55[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec56[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec57[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec58[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec59[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec1[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec0[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec82[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec81[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
			fVec18[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
			fRec80[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec79[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
			fVec19[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
			fRec78[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec77[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec76[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec75[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
			fRec86[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec85[l89] = 0.0f;

		}
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec84[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec83[l91] = 0.0f;

		}
		for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
			fRec74[l92] = 0.0f;

		}
		for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
			fRec73[l93] = 0.0f;

		}
		for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
			fRec72[l94] = 0.0f;

		}
		for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
			fRec71[l95] = 0.0f;

		}
		for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
			fRec70[l96] = 0.0f;

		}
		for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
			fRec69[l97] = 0.0f;

		}
		for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
			fRec68[l98] = 0.0f;

		}
		for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
			fRec67[l99] = 0.0f;

		}
		for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
			fRec66[l100] = 0.0f;

		}
		for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
			fRec65[l101] = 0.0f;

		}
		for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
			fVec20[l102] = 0.0f;

		}
		for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
			fRec64[l103] = 0.0f;

		}
		for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
			fRec63[l104] = 0.0f;

		}
		for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
			fRec88[l105] = 0.0f;

		}
		for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
			fRec87[l106] = 0.0f;

		}
		for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
			fRec62[l107] = 0.0f;

		}
		for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
			fRec61[l108] = 0.0f;

		}
		for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
			fRec60[l109] = 0.0f;

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

	void set_cab_brightness(FAUSTFLOAT value) { fEntry58 = value + 0.000000e+00f; }
	void set_cab_distance(FAUSTFLOAT value) { fEntry57 = value + 0.000000e+00f; }
	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry15 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry29 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry30 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry46 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry42 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry44 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry47 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry45 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry43 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry7 = value + -2.881445e+00f; }
	void set_tetrode_lp_freq(FAUSTFLOAT value) { fEntry6 = value + 4.860719e-01f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry50 = value + 5.105934e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry10 = value + 1.071032e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry51 = value + -5.419944e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry52 = value + -1.311108e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry53 = value + 5.972256e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry3 = value + -1.110910e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry5 = value + 5.639132e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry48 = value + 1.738520e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry49 = value + 1.148484e+00f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry4 = value + -2.438944e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry55 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry56 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry54 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry8 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry11 = value + 3.358306e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry27 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry28 = value + 2.098361e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry34 = value + 3.350094e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry33 = value + 1.208393e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry31 = value + 1.499258e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry32 = value + -1.358083e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry22 = value + 4.527706e-01f; }
	void set_triode_lp_freq(FAUSTFLOAT value) { fEntry16 = value + 2.889678e+00f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry18 = value + 2.396475e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry21 = value + 4.950481e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry19 = value + -1.032065e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry17 = value + -1.689672e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry23 = value + -2.338176e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry26 = value + -1.438144e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry25 = value + 1.985668e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry24 = value + -9.503685e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry20 = value + -6.756085e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry35 = value + -8.226255e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry37 = value + 1.024238e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry36 = value + -1.099234e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524402e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry40 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry39 = value + 0.000000e+00f; }
	void set_ts_presence(FAUSTFLOAT value) { fEntry41 = value + 0.000000e+00f; }
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
		set_tetrode_lp_freq(0.0f);
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
		set_triode_lp_freq(0.0f);
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
		float fSlow9 = std::tan((fConst4 * std::min<float>(fConst5, std::exp(((0.549306154f * (float(fEntry6) + 1.0f)) + 8.51719284f)))));
		float fSlow10 = (float(fEntry7) + 1.0f);
		float fSlow11 = AmpMono_faustpower2_f(std::sqrt((fConst7 * (std::tan((fConst4 * std::min<float>(fConst5, std::exp(((1.15129256f * fSlow10) + 2.30258512f))))) * fSlow9))));
		float fSlow12 = ((fConst3 * fSlow9) - (fConst6 * (fSlow11 / fSlow9)));
		float fSlow13 = (fConst2 * fSlow12);
		float fSlow14 = (fConst8 * fSlow11);
		float fSlow15 = ((fSlow13 + fSlow14) + 4.0f);
		float fSlow16 = (fConst2 * (fSlow12 / fSlow15));
		float fSlow17 = (0.5f * ((float(fEntry8) + 1.0f) * std::exp(((2.30258512f * (float(fEntry9) + 1.0f)) + -2.30258512f))));
		float fSlow18 = (fSlow17 + 1.0f);
		float fSlow19 = std::exp(((3.45387769f * (float(fEntry10) + 1.0f)) + -2.30258512f));
		float fSlow20 = std::exp(((4.60517025f * (float(fEntry11) + 1.0f)) + -4.60517025f));
		float fSlow21 = std::tan((fConst4 * std::exp(((3.45387769f * fSlow10) + -2.30258512f))));
		float fSlow22 = (1.0f / fSlow21);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (0.0f - (1.0f / (fSlow21 * fSlow23)));
		float fSlow25 = (float(fEntry12) + 1.0f);
		float fSlow26 = (fSlow2 * std::exp(((3.45387769f * fSlow25) + -0.693147182f)));
		float fSlow27 = float(fEntry13);
		float fSlow28 = (fSlow27 + 1.0f);
		float fSlow29 = (1.0f - (0.5f * fSlow28));
		float fSlow30 = std::tan((fConst4 * ((400.0f * fSlow29) + (25.0f * fSlow28))));
		float fSlow31 = (1.0f / fSlow30);
		float fSlow32 = (fSlow31 + 1.0f);
		float fSlow33 = (0.0f - (1.0f / (fSlow30 * fSlow32)));
		float fSlow34 = float(fEntry14);
		float fSlow35 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow34) + -5.0f));
		float fSlow36 = ((float(fEntry15) + 1.0f) + 1.0f);
		float fSlow37 = (0.5f * fSlow36);
		float fSlow38 = AmpMono_faustpower3_f(fSlow37);
		float fSlow39 = (0.5f * (fSlow35 / fSlow38));
		float fSlow40 = (1.0f / std::tan((fConst4 * std::min<float>(fConst5, std::exp(((0.549306154f * (float(fEntry16) + 1.0f)) + 8.51719284f))))));
		float fSlow41 = (1.0f / (fSlow40 + 1.0f));
		float fSlow42 = (1.0f - fSlow40);
		float fSlow43 = std::exp(((3.45387769f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow44 = (1.0f - (float(fEntry18) + 1.0f));
		float fSlow45 = (1.0f - (float(fEntry19) + 1.0f));
		float fSlow46 = std::exp(((4.60517025f * (float(fEntry20) + 1.0f)) + -4.60517025f));
		float fSlow47 = ((100.0f * (fSlow44 - fSlow45)) + fSlow46);
		float fSlow48 = std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -2.30258512f));
		float fSlow49 = (0.294117659f / fSlow48);
		float fSlow50 = std::tan((fConst4 * std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f))));
		float fSlow51 = (1.0f / fSlow50);
		float fSlow52 = (fSlow51 + 1.0f);
		float fSlow53 = (0.0f - (1.0f / (fSlow52 * fSlow50)));
		float fSlow54 = std::exp(((2.30258512f * (float(fEntry23) + 1.0f)) + -2.30258512f));
		float fSlow55 = std::exp(((3.45387769f * (float(fEntry24) + 1.0f)) + -6.90775537f));
		float fSlow56 = (1.0f / ((fConst0 * (fSlow55 * std::exp((1.15129256f * (float(fEntry25) + 1.0f))))) + 1.0f));
		float fSlow57 = (1.0f - fSlow56);
		float fSlow58 = (1.0f / ((fConst0 * fSlow55) + 1.0f));
		float fSlow59 = (100.0f * (1.0f - (float(fEntry26) + 1.0f)));
		float fSlow60 = (0.0f - fSlow59);
		float fSlow61 = (fSlow38 / fSlow2);
		float fSlow62 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow34) + -3.0f));
		float fSlow63 = AmpMono_faustpower2_f(fSlow37);
		float fSlow64 = (0.5f * (fSlow62 / fSlow63));
		float fSlow65 = (float(fEntry28) + 1.0f);
		float fSlow66 = ((float(fEntry27) + 1.0f) - fSlow65);
		float fSlow67 = (0.117647059f / fSlow65);
		float fSlow68 = (0.294117659f / fSlow46);
		float fSlow69 = (fSlow63 / fSlow2);
		float fSlow70 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow34) + -1.0f));
		float fSlow71 = (1.0f - (0.5f * fSlow70));
		float fSlow72 = (float(fEntry30) + 1.0f);
		float fSlow73 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry29) + 1.0f)))))) * std::exp((3.80045128f * fSlow72)));
		float fSlow74 = (1.0f / fSlow52);
		float fSlow75 = (1.0f - fSlow51);
		float fSlow76 = (fSlow73 / fSlow50);
		float fSlow77 = std::exp(((3.45387769f * (float(fEntry32) + 1.0f)) + -13.8155107f));
		float fSlow78 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry31) + 1.0f)) + -11.5129251f)) * fSlow77)) + 1.0f));
		float fSlow79 = (1.0f - fSlow78);
		float fSlow80 = (1.0f / ((fConst0 * (fSlow77 * std::exp(((5.75646257f * (float(fEntry33) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow81 = (1.0f - fSlow80);
		float fSlow82 = (1.0f / ((fConst0 * fSlow77) + 1.0f));
		float fSlow83 = (5.0f * (1.0f - (float(fEntry34) + 1.0f)));
		float fSlow84 = (2.5f * fSlow66);
		float fSlow85 = ((100.0f * fSlow44) + fSlow48);
		float fSlow86 = std::exp(((2.30258512f * (float(fEntry35) + 1.0f)) + -2.30258512f));
		float fSlow87 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry36) + 1.0f)) + -6.90775537f)))));
		float fSlow88 = (1.0f - fSlow87);
		float fSlow89 = (100.0f * (1.0f - (float(fEntry37) + 1.0f)));
		float fSlow90 = (0.0f - fSlow89);
		float fSlow91 = (100.0f * fSlow45);
		float fSlow92 = (1.0f - (float(fEntry38) + 1.0f));
		float fSlow93 = (100.0f * (fSlow45 - fSlow92));
		float fSlow94 = (0.294117659f / fSlow43);
		float fSlow95 = (100.0f * fSlow92);
		float fSlow96 = (fSlow70 / fSlow36);
		float fSlow97 = (0.5f * (fSlow36 / fSlow2));
		float fSlow98 = (fSlow50 * fSlow2);
		float fSlow99 = (0.5f * (fSlow36 / fSlow98));
		float fSlow100 = (fSlow80 + -1.0f);
		float fSlow101 = (1.0f / fSlow98);
		float fSlow102 = (fSlow56 + -1.0f);
		float fSlow103 = (fSlow63 / fSlow98);
		float fSlow104 = (1.0f - (0.5f * fSlow62));
		float fSlow105 = (fSlow38 / fSlow98);
		float fSlow106 = (1.0f - (0.5f * fSlow35));
		float fSlow107 = (1.0f / fSlow32);
		float fSlow108 = (1.0f - fSlow31);
		float fSlow109 = (1.0f / (fSlow30 * fSlow2));
		float fSlow110 = std::pow(10.0f, (0.0500000007f * (fSlow27 * ((18.0f * fSlow29) + (4.5f * fSlow28)))));
		float fSlow111 = float(fEntry39);
		float fSlow112 = (fSlow111 + 1.0f);
		float fSlow113 = ((fSlow111 * ((10.0f * (1.0f - (0.5f * fSlow112))) + (2.5f * fSlow112))) + -14.0f);
		int iSlow114 = (fSlow113 > 0.0f);
		float fSlow115 = ((800.0f * fSlow111) + 1200.0f);
		float fSlow116 = (fConst19 * (fSlow115 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow113)))));
		float fSlow117 = (fConst19 * fSlow115);
		float fSlow118 = (iSlow114?fSlow117:fSlow116);
		float fSlow119 = ((fConst17 * (fConst17 - fSlow118)) + 1.0f);
		float fSlow120 = ((fConst17 * (fConst17 + fSlow118)) + 1.0f);
		float fSlow121 = (iSlow114?fSlow116:fSlow117);
		float fSlow122 = ((fConst17 * (fConst17 + fSlow121)) + 1.0f);
		float fSlow123 = ((fConst17 * (fConst17 - fSlow121)) + 1.0f);
		float fSlow124 = (fSlow111 * ((fSlow111 > 0.0f)?5.0f:0.0f));
		int iSlow125 = (fSlow124 > 0.0f);
		float fSlow126 = (fConst20 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow124))));
		float fSlow127 = (iSlow125?fConst20:fSlow126);
		float fSlow128 = ((fConst17 * (fConst17 - fSlow127)) + 1.0f);
		float fSlow129 = ((fConst17 * (fConst17 + fSlow127)) + 1.0f);
		float fSlow130 = (iSlow125?fSlow126:fConst20);
		float fSlow131 = ((fConst17 * (fConst17 + fSlow130)) + 1.0f);
		float fSlow132 = ((fConst17 * (fConst17 - fSlow130)) + 1.0f);
		float fSlow133 = float(fEntry40);
		int iSlow134 = (fSlow133 < 0.0f);
		float fSlow135 = std::tan((fConst4 * ((iSlow134?(1500.0f * fSlow133):0.0f) + 2000.0f)));
		float fSlow136 = (1.0f / fSlow135);
		float fSlow137 = (1.0f - fSlow136);
		float fSlow138 = (fSlow136 + 1.0f);
		float fSlow139 = (0.0f - (1.0f / (fSlow135 * fSlow138)));
		float fSlow140 = (fSlow135 * fSlow129);
		float fSlow141 = std::pow(10.0f, ((0.0500000007f * fSlow133) * (iSlow134?18.0f:9.0f)));
		float fSlow142 = (10.0f * float(fEntry41));
		int iSlow143 = (fSlow142 > 0.0f);
		float fSlow144 = (fConst23 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow142))));
		float fSlow145 = (iSlow143?fConst23:fSlow144);
		float fSlow146 = ((fConst22 * (fConst22 - fSlow145)) + 1.0f);
		float fSlow147 = ((fConst22 * (fConst22 + fSlow145)) + 1.0f);
		float fSlow148 = (iSlow143?fSlow144:fConst23);
		float fSlow149 = ((fConst22 * (fConst22 - fSlow148)) + 1.0f);
		float fSlow150 = ((fConst22 * (fConst22 + fSlow148)) + 1.0f);
		float fSlow151 = (5.0f * fSlow72);
		int iSlow152 = (fSlow151 < 9.0f);
		int iSlow153 = (fSlow151 < 8.0f);
		int iSlow154 = (fSlow151 < 7.0f);
		int iSlow155 = (fSlow151 < 6.0f);
		int iSlow156 = (fSlow151 < 5.0f);
		float fSlow157 = (1.0f - fSlow72);
		int iSlow158 = (fSlow151 < 4.0f);
		int iSlow159 = (fSlow151 < 3.0f);
		int iSlow160 = (fSlow151 < 2.0f);
		int iSlow161 = (fSlow151 < 1.0f);
		float fSlow162 = std::pow(10.0f, (0.0500000007f * (iSlow152?(iSlow153?(iSlow154?(iSlow155?(iSlow156?(iSlow158?(iSlow159?(iSlow160?(iSlow161?((fSlow151 < 0.0f)?10.8000002f:(iSlow161?(10.8000002f - (33.0f * fSlow72)):4.19999981f)):(iSlow160?(4.19999981f - (6.53000021f * (fSlow151 + -1.0f))):-2.32999992f)):(iSlow159?(-2.32999992f - (6.57999992f * (fSlow151 + -2.0f))):-8.90999985f)):(iSlow158?(-8.90999985f - (6.59000015f * (fSlow151 + -3.0f))):-15.5f)):(iSlow156?(-15.5f - (4.80000019f * (fSlow151 + -4.0f))):-20.2999992f)):(iSlow155?(-20.2999992f - (2.4000001f * (0.0f - (5.0f * fSlow157)))):-22.7000008f)):(iSlow154?(-22.7000008f - (1.10000002f * (fSlow151 + -6.0f))):-23.7999992f)):(iSlow153?(-23.7999992f - (0.600000024f * (fSlow151 + -7.0f))):-24.3999996f)):(iSlow152?(-24.3999996f - (0.699999988f * (fSlow151 + -8.0f))):-25.1000004f)):((fSlow151 < 10.0f)?(-25.1000004f - (0.600000024f * (fSlow151 + -9.0f))):-25.7000008f))));
		float fSlow163 = (250.0f * (float(fEntry42) + 1.0f));
		float fSlow164 = (1.0f / fSlow23);
		float fSlow165 = (1.0f - fSlow22);
		float fSlow166 = std::exp((0.0f - (fConst1 / std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f)))));
		float fSlow167 = (1.0f - fSlow166);
		float fSlow168 = (250.0f * (float(fEntry44) + 1.0f));
		float fSlow169 = std::exp(((4.60517025f * (float(fEntry45) + 1.0f)) + -9.2103405f));
		float fSlow170 = (1.0f / ((fConst0 * fSlow169) + 1.0f));
		float fSlow171 = (100.0f * (1.0f - (float(fEntry46) + 1.0f)));
		float fSlow172 = ((1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry47) + 1.0f)) + -4.60517025f)) * fSlow169)) + 1.0f)) + -1.0f);
		float fSlow173 = std::exp(((2.30258512f * (float(fEntry48) + 1.0f)) + -2.30258512f));
		float fSlow174 = (100.0f * (1.0f - (float(fEntry49) + 1.0f)));
		float fSlow175 = (0.0f - fSlow174);
		float fSlow176 = ((20.0f * (float(fEntry50) + 1.0f)) + 10.0f);
		float fSlow177 = std::exp(((2.30258512f * (float(fEntry51) + 1.0f)) + -2.30258512f));
		float fSlow178 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry52) + 1.0f)) + -6.90775537f)))));
		float fSlow179 = (1.0f - fSlow178);
		float fSlow180 = (1.0f / fSlow176);
		float fSlow181 = (0.294117659f / fSlow19);
		float fSlow182 = std::exp(((3.45387769f * (float(fEntry53) + 1.0f)) + -2.30258512f));
		float fSlow183 = (0.294117659f / fSlow182);
		float fSlow184 = std::exp(((1.95601153f * (float(fEntry54) + 1.0f)) + -4.60517025f));
		float fSlow185 = (1.0f / ((fConst0 * fSlow184) + 1.0f));
		float fSlow186 = (fSlow20 / fSlow176);
		float fSlow187 = std::exp(((2.30258512f * (float(fEntry55) + 1.0f)) + -2.30258512f));
		float fSlow188 = (1.0f - (1.0f / ((fConst0 * (fSlow184 * std::exp((1.15129256f * (float(fEntry56) + 1.0f))))) + 1.0f)));
		float fSlow189 = (1.0f / fSlow15);
		float fSlow190 = (fSlow14 + (4.0f - fSlow13));
		float fSlow191 = ((fConst25 * fSlow11) + -8.0f);
		float fSlow192 = (0.0f - fSlow16);
		float fSlow193 = float(fEntry57);
		float fSlow194 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow193)));
		float fSlow195 = float(fEntry58);
		float fSlow196 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow195))));
		float fSlow197 = (15.0f * fSlow195);
		int iSlow198 = (fSlow197 > 0.0f);
		float fSlow199 = (fConst182 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow197))));
		float fSlow200 = (iSlow198?fConst182:fSlow199);
		float fSlow201 = ((fConst181 * (fConst181 - fSlow200)) + 1.0f);
		float fSlow202 = ((fConst181 * (fConst181 + fSlow200)) + 1.0f);
		float fSlow203 = (iSlow198?fSlow199:fConst182);
		float fSlow204 = ((fConst181 * (fConst181 + fSlow203)) + 1.0f);
		float fSlow205 = ((fConst181 * (fConst181 - fSlow203)) + 1.0f);
		float fSlow206 = (0.0f - (10.0f * fSlow193));
		int iSlow207 = (fSlow206 > 0.0f);
		float fSlow208 = (fConst185 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow206))));
		float fSlow209 = (iSlow207?fConst185:fSlow208);
		float fSlow210 = ((fConst184 * (fConst184 - fSlow209)) + 1.0f);
		float fSlow211 = ((fConst184 * (fConst184 + fSlow209)) + 1.0f);
		float fSlow212 = (iSlow207?fSlow208:fConst185);
		float fSlow213 = ((fConst184 * (fConst184 - fSlow212)) + 1.0f);
		float fSlow214 = ((fConst184 * (fConst184 + fSlow212)) + 1.0f);
		float fSlow215 = (0.0f - (17.0f * fSlow193));
		int iSlow216 = (fSlow215 > 0.0f);
		float fSlow217 = (fConst188 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow215))));
		float fSlow218 = (iSlow216?fConst188:fSlow217);
		float fSlow219 = ((fConst187 * (fConst187 - fSlow218)) + 1.0f);
		float fSlow220 = ((fConst187 * (fConst187 + fSlow218)) + 1.0f);
		float fSlow221 = (iSlow216?fSlow217:fConst188);
		float fSlow222 = ((fConst187 * (fConst187 + fSlow221)) + 1.0f);
		float fSlow223 = ((fConst187 * (fConst187 - fSlow221)) + 1.0f);
		float fSlow224 = (5.0f * fSlow25);
		int iSlow225 = (fSlow224 < 9.0f);
		int iSlow226 = (fSlow224 < 8.0f);
		int iSlow227 = (fSlow224 < 7.0f);
		int iSlow228 = (fSlow224 < 6.0f);
		int iSlow229 = (fSlow224 < 5.0f);
		int iSlow230 = (fSlow224 < 4.0f);
		int iSlow231 = (fSlow224 < 3.0f);
		int iSlow232 = (fSlow224 < 2.0f);
		int iSlow233 = (fSlow224 < 1.0f);
		float fSlow234 = std::pow(10.0f, (0.0500000007f * (iSlow225?(iSlow226?(iSlow227?(iSlow228?(iSlow229?(iSlow230?(iSlow231?(iSlow232?(iSlow233?((fSlow224 < 0.0f)?5.13999987f:(iSlow233?(5.13999987f - (27.9500008f * fSlow25)):-0.449999988f)):(iSlow232?(-0.449999988f - (5.28999996f * (fSlow224 + -1.0f))):-5.73999977f)):(iSlow231?(-5.73999977f - (5.36000013f * (fSlow224 + -2.0f))):-11.1000004f)):(iSlow230?(-11.1000004f - (5.4000001f * (fSlow224 + -3.0f))):-16.5f)):(iSlow229?(-16.5f - (3.29999995f * (fSlow224 + -4.0f))):-19.7999992f)):(iSlow228?((5.0f * (1.0f - fSlow25)) + -19.7999992f):-20.7999992f)):(iSlow227?(-20.7999992f - (0.200000003f * (fSlow224 + -6.0f))):-21.0f)):(iSlow226?((0.100000001f * (fSlow224 + -7.0f)) + -21.0f):-20.8999996f)):(iSlow225?((0.100000001f * (fSlow224 + -8.0f)) + -20.8999996f):-20.7999992f)):-20.7999992f)));
		float fSlow235 = (2.0f * fSlow72);
		float fSlow236 = std::pow(10.0f, (0.0500000007f * ((fSlow235 < 2.0f)?0.0f:((fSlow235 < 3.0f)?(0.0f - (5.0f * (0.0f - (2.0f * fSlow157)))):-5.0f))));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow73 * fTemp0);
			fRec21[0] = ((fSlow53 * fVec0[1]) - (fSlow74 * ((fSlow75 * fRec21[1]) - (fSlow76 * fTemp0))));
			fRec23[0] = ((fSlow81 * fRec23[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec21[0])) - fRec23[1]))));
			fRec22[0] = ((fSlow79 * fRec22[1]) + (fSlow78 * fRec23[0]));
			float fTemp1 = ((fRec21[0] - fRec22[0]) - fSlow84);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * (fSlow66 + (fSlow65 * ((fTemp2 * (std::fabs((fTemp2 * fTemp3)) + -2.0f)) * fTemp3)))))) - fSlow85);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow47 + (std::max<float>(0.0f, fTemp4) + (fSlow48 * (((fTemp6 * (std::fabs((fTemp6 * fTemp5)) + -2.0f)) * fTemp5) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (std::fabs(fTemp8) + -2.0f);
			float fTemp10 = ((fSlow46 * (((fTemp9 * (std::fabs((fTemp9 * fTemp8)) + -2.0f)) * fTemp8) + 1.0f)) + std::max<float>(0.0f, fTemp7));
			fRec24[0] = ((fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp10 - fSlow91)))) + (fSlow87 * fRec24[1]));
			float fTemp11 = (fSlow86 * fRec24[0]);
			fRec25[0] = ((fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp10 - fTemp11) - fSlow91)) - fRec25[1])))) + (fSlow57 * fRec25[1]));
			float fTemp12 = (fSlow54 * fRec25[0]);
			float fTemp13 = (fSlow43 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow93));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((std::min<float>(0.0f, fTemp13) + fTemp12) - (fSlow43 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow95);
			fVec1[0] = fTemp16;
			fRec20[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec20[1]) - (fTemp16 + fVec1[1]))));
			fVec2[0] = (fSlow97 * fRec20[0]);
			fRec31[0] = ((fSlow53 * fVec2[1]) + (fSlow74 * ((fSlow99 * fRec20[0]) - (fSlow75 * fRec31[1]))));
			fRec33[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec31[0])) - fRec33[1]))) - (fSlow100 * fRec33[1]));
			fRec32[0] = ((fSlow78 * fRec33[0]) + (fSlow79 * fRec32[1]));
			float fTemp17 = ((fRec31[0] - fRec32[0]) - fSlow84);
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * ((2.5f * (fSlow66 + (fSlow65 * ((fTemp18 * (std::fabs((fTemp18 * fTemp19)) + -2.0f)) * fTemp19)))) + std::min<float>(0.0f, fTemp17))) - fSlow85);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow47 + ((fSlow48 * ((((std::fabs((fTemp21 * fTemp22)) + -2.0f) * fTemp21) * fTemp22) + 1.0f)) + std::max<float>(0.0f, fTemp20))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (fTemp24 * (std::fabs(fTemp24) + -2.0f));
			float fTemp26 = ((fSlow46 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp23));
			fRec34[0] = ((fSlow87 * fRec34[1]) + (fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp26 - fSlow91)))));
			float fTemp27 = (fSlow86 * fRec34[0]);
			fRec30[0] = ((fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp26 - fTemp27) - fSlow91)) - fRec30[1])))) + (fSlow57 * fRec30[1]));
			float fTemp28 = (fSlow54 * fRec30[0]);
			float fTemp29 = (fSlow43 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow93));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (fTemp30 * (std::fabs(fTemp30) + -2.0f));
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow43 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow95);
			fVec3[0] = fTemp32;
			fRec29[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec29[1]) - (fTemp32 + fVec3[1]))));
			fVec4[0] = (fSlow3 * fRec29[0]);
			fRec28[0] = ((fSlow53 * fVec4[1]) - (fSlow74 * ((fSlow75 * fRec28[1]) - (fSlow101 * fRec29[0]))));
			fRec36[0] = ((fSlow81 * fRec36[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec28[0])) - fRec36[1]))));
			fRec35[0] = ((fSlow78 * fRec36[0]) + (fSlow79 * fRec35[1]));
			float fTemp33 = ((fRec28[0] - fRec35[0]) - fSlow84);
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) + (2.5f * (fSlow66 + (fSlow65 * (((std::fabs((fTemp34 * fTemp35)) + -2.0f) * fTemp34) * fTemp35)))))) - fSlow85);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (std::fabs(fTemp37) + -2.0f);
			float fTemp39 = (0.0f - (fSlow47 + ((fSlow48 * ((((std::fabs((fTemp38 * fTemp37)) + -2.0f) * fTemp38) * fTemp37) + 1.0f)) + std::max<float>(0.0f, fTemp36))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (std::fabs(fTemp40) + -2.0f);
			float fTemp42 = ((fSlow46 * (((fTemp41 * (std::fabs((fTemp41 * fTemp40)) + -2.0f)) * fTemp40) + 1.0f)) + std::max<float>(0.0f, fTemp39));
			fRec37[0] = ((fSlow87 * fRec37[1]) + (fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp42 - fSlow91)))));
			float fTemp43 = (fSlow86 * fRec37[0]);
			fRec27[0] = ((fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp42 - fTemp43) - fSlow91)) - fRec27[1])))) - (fSlow102 * fRec27[1]));
			float fTemp44 = (fSlow54 * fRec27[0]);
			float fTemp45 = (fSlow43 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow93));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow43 * (1.0f - (((std::fabs((fTemp46 * fTemp47)) + -2.0f) * fTemp46) * fTemp47)))) - fSlow95);
			fVec5[0] = fTemp48;
			fRec26[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec26[1]) - (fVec5[1] + fTemp48))));
			float fTemp49 = ((fSlow71 * fRec20[0]) + (fSlow96 * fRec26[0]));
			fVec6[0] = (fSlow69 * fTemp49);
			fRec19[0] = ((fSlow53 * fVec6[1]) - (fSlow74 * ((fSlow75 * fRec19[1]) - (fSlow103 * fTemp49))));
			fRec39[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec19[0])) - fRec39[1]))) + (fSlow81 * fRec39[1]));
			fRec38[0] = ((fSlow78 * fRec39[0]) + (fSlow79 * fRec38[1]));
			float fTemp50 = ((fRec19[0] - fRec38[0]) - fSlow84);
			float fTemp51 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp50))));
			float fTemp52 = (fTemp51 * (std::fabs(fTemp51) + -2.0f));
			float fTemp53 = ((fSlow2 * (std::min<float>(0.0f, fTemp50) + (2.5f * (fSlow66 + (fSlow65 * (fTemp52 * (std::fabs(fTemp52) + -2.0f))))))) - fSlow85);
			float fTemp54 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp53))));
			float fTemp55 = ((std::fabs(fTemp54) + -2.0f) * fTemp54);
			float fTemp56 = (0.0f - (fSlow47 + ((fSlow48 * ((fTemp55 * (std::fabs(fTemp55) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp53))));
			float fTemp57 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp56))));
			float fTemp58 = (fTemp57 * (std::fabs(fTemp57) + -2.0f));
			float fTemp59 = ((fSlow46 * ((fTemp58 * (std::fabs(fTemp58) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp56));
			fRec40[0] = ((fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp59 - fSlow91)))) + (fSlow87 * fRec40[1]));
			float fTemp60 = (fSlow86 * fRec40[0]);
			fRec18[0] = ((fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp59 - fTemp60) - fSlow91)) - fRec18[1])))) - (fSlow102 * fRec18[1]));
			float fTemp61 = (fSlow54 * fRec18[0]);
			float fTemp62 = (fSlow43 + ((fTemp59 - (fTemp61 + fTemp60)) - fSlow93));
			float fTemp63 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp62))));
			float fTemp64 = (std::fabs(fTemp63) + -2.0f);
			float fTemp65 = (((fTemp61 + std::min<float>(0.0f, fTemp62)) - (fSlow43 * (1.0f - (((std::fabs((fTemp63 * fTemp64)) + -2.0f) * fTemp63) * fTemp64)))) - fSlow95);
			fVec7[0] = fTemp65;
			fRec17[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec17[1]) - (fVec7[1] + fTemp65))));
			fVec8[0] = (fSlow3 * fRec17[0]);
			fRec16[0] = ((fSlow53 * fVec8[1]) - (fSlow74 * ((fSlow75 * fRec16[1]) - (fSlow101 * fRec17[0]))));
			fRec42[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec16[0])) - fRec42[1]))) - (fSlow100 * fRec42[1]));
			fRec41[0] = ((fSlow79 * fRec41[1]) + (fSlow78 * fRec42[0]));
			float fTemp66 = ((fRec16[0] - fRec41[0]) - fSlow84);
			float fTemp67 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp66))));
			float fTemp68 = (fTemp67 * (std::fabs(fTemp67) + -2.0f));
			float fTemp69 = ((fSlow2 * ((2.5f * (fSlow66 + (fSlow65 * (fTemp68 * (std::fabs(fTemp68) + -2.0f))))) + std::min<float>(0.0f, fTemp66))) - fSlow85);
			float fTemp70 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp69))));
			float fTemp71 = (fTemp70 * (std::fabs(fTemp70) + -2.0f));
			float fTemp72 = (0.0f - (fSlow47 + (std::max<float>(0.0f, fTemp69) + (fSlow48 * ((fTemp71 * (std::fabs(fTemp71) + -2.0f)) + 1.0f)))));
			float fTemp73 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp72))));
			float fTemp74 = (std::fabs(fTemp73) + -2.0f);
			float fTemp75 = (std::max<float>(0.0f, fTemp72) + (fSlow46 * ((((std::fabs((fTemp74 * fTemp73)) + -2.0f) * fTemp74) * fTemp73) + 1.0f)));
			fRec43[0] = ((fSlow87 * fRec43[1]) + (fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp75 - fSlow91)))));
			float fTemp76 = (fSlow86 * fRec43[0]);
			fRec15[0] = ((fSlow57 * fRec15[1]) + (fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp75 - fTemp76) - fSlow91)) - fRec15[1])))));
			float fTemp77 = (fSlow54 * fRec15[0]);
			float fTemp78 = (fSlow43 + ((fTemp75 - (fTemp76 + fTemp77)) - fSlow93));
			float fTemp79 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp78))));
			float fTemp80 = (std::fabs(fTemp79) + -2.0f);
			float fTemp81 = (((fTemp77 + std::min<float>(0.0f, fTemp78)) - (fSlow43 * (1.0f - ((fTemp80 * (std::fabs((fTemp80 * fTemp79)) + -2.0f)) * fTemp79)))) - fSlow95);
			fVec9[0] = fTemp81;
			fRec14[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec14[1]) - (fTemp81 + fVec9[1]))));
			float fTemp82 = ((fSlow64 * fRec14[0]) + (fSlow104 * fTemp49));
			fVec10[0] = (fSlow61 * fTemp82);
			fRec13[0] = ((fSlow53 * fVec10[1]) - (fSlow74 * ((fSlow75 * fRec13[1]) - (fSlow105 * fTemp82))));
			fRec45[0] = ((fSlow81 * fRec45[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec13[0])) - fRec45[1]))));
			fRec44[0] = ((fSlow79 * fRec44[1]) + (fSlow78 * fRec45[0]));
			float fTemp83 = ((fRec13[0] - fRec44[0]) - fSlow84);
			float fTemp84 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp83))));
			float fTemp85 = (fTemp84 * (std::fabs(fTemp84) + -2.0f));
			float fTemp86 = ((fSlow2 * (std::min<float>(0.0f, fTemp83) + (2.5f * (fSlow66 + (fSlow65 * (fTemp85 * (std::fabs(fTemp85) + -2.0f))))))) - fSlow85);
			float fTemp87 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp86))));
			float fTemp88 = (std::fabs(fTemp87) + -2.0f);
			float fTemp89 = (0.0f - (fSlow47 + (std::max<float>(0.0f, fTemp86) + (fSlow48 * (((fTemp87 * (std::fabs((fTemp87 * fTemp88)) + -2.0f)) * fTemp88) + 1.0f)))));
			float fTemp90 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp89))));
			float fTemp91 = (fTemp90 * (std::fabs(fTemp90) + -2.0f));
			float fTemp92 = (std::max<float>(0.0f, fTemp89) + (fSlow46 * ((fTemp91 * (std::fabs(fTemp91) + -2.0f)) + 1.0f)));
			fRec46[0] = ((fSlow87 * fRec46[1]) + (fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp92 - fSlow91)))));
			float fTemp93 = (fSlow86 * fRec46[0]);
			fRec12[0] = ((fSlow57 * fRec12[1]) + (fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp92 - fTemp93) - fSlow91)) - fRec12[1])))));
			float fTemp94 = (fSlow54 * fRec12[0]);
			float fTemp95 = (fSlow43 + ((fTemp92 - (fTemp93 + fTemp94)) - fSlow93));
			float fTemp96 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp95))));
			float fTemp97 = (std::fabs(fTemp96) + -2.0f);
			float fTemp98 = (((fTemp94 + std::min<float>(0.0f, fTemp95)) - (fSlow43 * (1.0f - ((fTemp97 * (std::fabs((fTemp97 * fTemp96)) + -2.0f)) * fTemp96)))) - fSlow95);
			fVec11[0] = fTemp98;
			fRec11[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec11[1]) - (fTemp98 + fVec11[1]))));
			fVec12[0] = (fSlow3 * fRec11[0]);
			fRec10[0] = ((fSlow53 * fVec12[1]) - (fSlow74 * ((fSlow75 * fRec10[1]) - (fSlow101 * fRec11[0]))));
			fRec48[0] = ((fSlow81 * fRec48[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow83 + fRec10[0])) - fRec48[1]))));
			fRec47[0] = ((fSlow79 * fRec47[1]) + (fSlow78 * fRec48[0]));
			float fTemp99 = ((fRec10[0] - fRec47[0]) - fSlow84);
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp99))));
			float fTemp101 = (fTemp100 * (std::fabs(fTemp100) + -2.0f));
			float fTemp102 = ((fSlow2 * (std::min<float>(0.0f, fTemp99) + (2.5f * (fSlow66 + (fSlow65 * (fTemp101 * (std::fabs(fTemp101) + -2.0f))))))) - fSlow85);
			float fTemp103 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp102))));
			float fTemp104 = (std::fabs(fTemp103) + -2.0f);
			float fTemp105 = (0.0f - (fSlow47 + ((fSlow48 * (((fTemp104 * (std::fabs((fTemp104 * fTemp103)) + -2.0f)) * fTemp103) + 1.0f)) + std::max<float>(0.0f, fTemp102))));
			float fTemp106 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow68 * std::min<float>(0.0f, fTemp105))));
			float fTemp107 = (std::fabs(fTemp106) + -2.0f);
			float fTemp108 = (std::max<float>(0.0f, fTemp105) + (fSlow46 * (((fTemp107 * (std::fabs((fTemp107 * fTemp106)) + -2.0f)) * fTemp106) + 1.0f)));
			fRec49[0] = ((fSlow88 * (fSlow89 + std::max<float>(fSlow90, (fTemp108 - fSlow91)))) + (fSlow87 * fRec49[1]));
			float fTemp109 = (fSlow86 * fRec49[0]);
			fRec50[0] = ((fSlow58 * std::max<float>(0.0f, (fSlow59 + (std::max<float>(fSlow60, ((fTemp108 - fTemp109) - fSlow91)) - fRec50[1])))) - (fSlow102 * fRec50[1]));
			float fTemp110 = (fSlow54 * fRec50[0]);
			float fTemp111 = (fSlow43 + ((fTemp108 - (fTemp109 + fTemp110)) - fSlow93));
			float fTemp112 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow94 * std::max<float>(0.0f, fTemp111))));
			float fTemp113 = (std::fabs(fTemp112) + -2.0f);
			float fTemp114 = (((std::min<float>(0.0f, fTemp111) + fTemp110) - (fSlow43 * (1.0f - (((std::fabs((fTemp112 * fTemp113)) + -2.0f) * fTemp112) * fTemp113)))) - fSlow95);
			fVec13[0] = fTemp114;
			fRec9[0] = (0.0f - (fSlow41 * ((fSlow42 * fRec9[1]) - (fTemp114 + fVec13[1]))));
			float fTemp115 = ((fSlow39 * fRec9[0]) + (fSlow106 * fTemp82));
			float fTemp116 = (fSlow3 * fTemp115);
			fVec14[0] = fTemp116;
			fRec8[0] = ((fSlow33 * fVec14[1]) - (fSlow107 * ((fSlow108 * fRec8[1]) - (fSlow109 * fTemp115))));
			fRec51[0] = (fSlow107 * ((fTemp116 + fVec14[1]) - (fSlow108 * fRec51[1])));
			float fTemp117 = (fRec8[0] + (fSlow110 * fRec51[0]));
			fVec15[0] = fTemp117;
			fRec7[0] = ((fConst14 * fVec15[1]) - (fConst15 * ((fConst16 * fRec7[1]) - (fConst12 * fTemp117))));
			float fTemp118 = (fConst10 * fRec6[1]);
			fRec6[0] = (fRec7[0] - (((fSlow119 * fRec6[2]) + fTemp118) / fSlow120));
			float fTemp119 = (fConst10 * fRec5[1]);
			fRec5[0] = ((((fTemp118 + (fRec6[0] * fSlow122)) + (fRec6[2] * fSlow123)) / fSlow120) - (((fRec5[2] * fSlow128) + fTemp119) / fSlow129));
			float fTemp120 = ((fTemp119 + (fRec5[0] * fSlow131)) + (fRec5[2] * fSlow132));
			float fTemp121 = (fTemp120 / fSlow129);
			fVec16[0] = fTemp121;
			fRec4[0] = (((fVec16[1] + fTemp121) - (fSlow137 * fRec4[1])) / fSlow138);
			fRec52[0] = ((fVec16[1] * fSlow139) - (((fSlow137 * fRec52[1]) - (fTemp120 / fSlow140)) / fSlow138));
			float fTemp122 = (fConst24 * fRec3[1]);
			fRec3[0] = ((fRec4[0] + (fRec52[0] * fSlow141)) - (((fRec3[2] * fSlow146) + fTemp122) / fSlow147));
			float fTemp123 = ((fSlow26 * ((((fRec3[2] * fSlow149) + ((fRec3[0] * fSlow150) + fTemp122)) * fSlow162) / fSlow147)) - fSlow163);
			fVec17[0] = fTemp123;
			fRec2[0] = ((fSlow24 * fVec17[1]) - (fSlow164 * ((fSlow165 * fRec2[1]) - (fSlow22 * fTemp123))));
			fRec53[0] = ((fSlow166 * fRec53[1]) + (fSlow167 * (fRec2[0] - fSlow168)));
			fRec54[0] = ((fSlow170 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow171 + ((fRec2[0] - fRec53[0]) - fSlow168))) - fRec54[1]))) - (fSlow172 * fRec54[1]));
			float fTemp124 = ((fRec2[0] - (fRec53[0] + fRec54[0])) - fSlow168);
			float fTemp125 = (fSlow20 * fTemp124);
			fRec55[0] = ((fSlow5 * fRec55[1]) + (fSlow6 * (fSlow174 + std::max<float>(fSlow175, fTemp125))));
			float fTemp126 = (fSlow173 * fRec55[0]);
			fRec56[0] = ((fSlow178 * fRec56[1]) + (fSlow179 * std::min<float>(1.0f, std::fabs((fSlow180 * (fTemp125 - fTemp126))))));
			float fTemp127 = (fSlow176 / ((fSlow177 * fRec56[0]) + 1.0f));
			float fTemp128 = (fSlow19 + (fTemp125 - (fTemp126 + fTemp127)));
			float fTemp129 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow181 * std::max<float>(0.0f, fTemp128))));
			float fTemp130 = (fTemp129 * (std::fabs(fTemp129) + -2.0f));
			float fTemp131 = (((std::min<float>(0.0f, fTemp128) + fTemp127) - (fSlow19 * (1.0f - (fTemp130 * (std::fabs(fTemp130) + -2.0f))))) - fSlow182);
			fRec57[0] = ((fSlow5 * fRec57[1]) + (fSlow6 * (fSlow174 + std::max<float>(fSlow175, (0.0f - fTemp125)))));
			float fTemp132 = (fTemp125 + (fSlow173 * fRec57[0]));
			fRec58[0] = ((fSlow178 * fRec58[1]) + (fSlow179 * std::min<float>(1.0f, std::fabs((fSlow180 * (0.0f - fTemp132))))));
			float fTemp133 = (fSlow176 / ((fSlow177 * fRec58[0]) + 1.0f));
			float fTemp134 = (fSlow19 - (fTemp132 + fTemp133));
			float fTemp135 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow181 * std::max<float>(0.0f, fTemp134))));
			float fTemp136 = (std::fabs(fTemp135) + -2.0f);
			float fTemp137 = (((std::min<float>(0.0f, fTemp134) + fTemp133) - (fSlow19 * (1.0f - (((std::fabs((fTemp135 * fTemp136)) + -2.0f) * fTemp135) * fTemp136)))) - fSlow182);
			float fTemp138 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow183 * std::min<float>(0.0f, fTemp137))));
			float fTemp139 = (fTemp138 * (std::fabs(fTemp138) + -2.0f));
			float fTemp140 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow183 * std::min<float>(0.0f, fTemp131))));
			float fTemp141 = ((std::fabs(fTemp140) + -2.0f) * fTemp140);
			float fTemp142 = std::fabs((fSlow186 * fTemp124));
			fRec59[0] = ((fSlow185 * std::max<float>(0.0f, ((std::max<float>(1.0f, fTemp142) + (fSlow187 * std::min<float>(1.0f, fTemp142))) + (-1.0f - fRec59[1])))) + (fSlow188 * fRec59[1]));
			fRec1[0] = ((fSlow18 * ((std::max<float>(0.0f, fTemp131) - (std::max<float>(0.0f, fTemp137) + (fSlow182 * (((fTemp139 * (std::fabs(fTemp139) + -2.0f)) + 1.0f) - ((fTemp141 * (std::fabs(fTemp141) + -2.0f)) + 1.0f))))) / ((fSlow17 * fRec59[0]) + 1.0f))) - (fSlow189 * ((fSlow190 * fRec1[2]) + (fSlow191 * fRec1[1]))));
			float fTemp143 = (fSlow16 * fRec1[0]);
			float fTemp144 = (fSlow192 * fRec1[2]);
			fRec0[0] = ((fSlow5 * fRec0[1]) + (fSlow6 * (fSlow7 + std::max<float>(fSlow8, std::fabs((fTemp143 + fTemp144))))));
			float fTemp145 = (fSlow3 * (((fSlow4 * fRec0[0]) + fTemp143) + fTemp144));
			fRec82[0] = (fTemp145 - (fConst124 * ((fConst125 * fRec82[2]) + (fConst126 * fRec82[1]))));
			fRec81[0] = ((fConst124 * ((fConst123 * fRec82[2]) + ((fConst127 * fRec82[1]) + (fConst123 * fRec82[0])))) - (fConst121 * ((fConst128 * fRec81[2]) + (fConst126 * fRec81[1]))));
			float fTemp146 = (((fConst123 * fRec81[0]) + (fConst127 * fRec81[1])) + (fConst123 * fRec81[2]));
			fVec18[0] = fTemp146;
			fRec80[0] = (0.0f - (fConst117 * ((fConst118 * fRec80[1]) - (fConst121 * (fTemp146 + fVec18[1])))));
			fRec79[0] = (fRec80[0] - (fConst113 * ((fConst129 * fRec79[1]) + (fConst130 * fRec79[2]))));
			float fTemp147 = (fRec79[2] + (fRec79[0] + (2.0f * fRec79[1])));
			fVec19[0] = fTemp147;
			fRec78[0] = ((fConst113 * ((fConst116 * fVec19[1]) + (fConst115 * fTemp147))) - (fConst132 * fRec78[1]));
			fRec77[0] = (fRec78[0] - (fConst110 * ((fConst133 * fRec77[2]) + (fConst134 * fRec77[1]))));
			fRec76[0] = ((fConst110 * ((fConst107 * fRec77[2]) + ((fConst107 * fRec77[0]) + (fConst109 * fRec77[1])))) - (fConst108 * ((fConst135 * fRec76[2]) + (fConst134 * fRec76[1]))));
			fRec75[0] = ((fConst108 * (((fConst109 * fRec76[1]) + (fConst107 * fRec76[0])) + (fConst107 * fRec76[2]))) - (fConst105 * ((fConst136 * fRec75[2]) + (fConst134 * fRec75[1]))));
			fRec86[0] = (0.0f - (fConst137 * ((fConst131 * fRec86[1]) - (fConst113 * (fTemp147 + fVec19[1])))));
			fRec85[0] = (fRec86[0] - (fConst110 * ((fConst133 * fRec85[2]) + (fConst134 * fRec85[1]))));
			fRec84[0] = ((fConst110 * ((fRec85[0] + (2.0f * fRec85[1])) + fRec85[2])) - (fConst108 * ((fConst134 * fRec84[1]) + (fConst135 * fRec84[2]))));
			fRec83[0] = ((fConst108 * ((fRec84[0] + (2.0f * fRec84[1])) + fRec84[2])) - (fConst105 * ((fConst136 * fRec83[2]) + (fConst134 * fRec83[1]))));
			float fTemp148 = (fConst139 * fRec74[1]);
			fRec74[0] = ((fConst105 * ((0.0316227749f * ((fConst107 * fRec75[2]) + ((fConst107 * fRec75[0]) + (fConst109 * fRec75[1])))) + ((fRec83[0] + (2.0f * fRec83[1])) + fRec83[2]))) - (fConst100 * ((fConst138 * fRec74[2]) + fTemp148)));
			float fTemp149 = (fConst95 * fRec73[1]);
			fRec73[0] = ((fConst100 * ((fConst102 * fRec74[2]) + ((fConst140 * fRec74[0]) + fTemp148))) - (fConst94 * ((fConst141 * fRec73[2]) + fTemp149)));
			float fTemp150 = (fConst89 * fRec72[1]);
			fRec72[0] = ((fConst94 * ((fTemp149 + (fConst143 * fRec73[0])) + (fConst144 * fRec73[2]))) - (fConst88 * ((fConst145 * fRec72[2]) + fTemp150)));
			float fTemp151 = (fConst83 * fRec71[1]);
			fRec71[0] = ((fConst88 * ((fTemp150 + (fConst147 * fRec72[0])) + (fConst148 * fRec72[2]))) - (fConst82 * ((fConst149 * fRec71[2]) + fTemp151)));
			float fTemp152 = (fConst154 * fRec70[1]);
			fRec70[0] = ((fConst82 * ((fTemp151 + (fConst151 * fRec71[0])) + (fConst152 * fRec71[2]))) - (fConst74 * ((fConst153 * fRec70[2]) + fTemp152)));
			float fTemp153 = (fConst69 * fRec69[1]);
			fRec69[0] = ((fConst74 * (((fConst76 * fRec70[0]) + fTemp152) + (fConst155 * fRec70[2]))) - (fConst68 * ((fConst156 * fRec69[2]) + fTemp153)));
			float fTemp154 = (fConst63 * fRec68[1]);
			fRec68[0] = ((fConst68 * ((fTemp153 + (fConst158 * fRec69[0])) + (fConst159 * fRec69[2]))) - (fConst62 * ((fConst160 * fRec68[2]) + fTemp154)));
			float fTemp155 = (fConst165 * fRec67[1]);
			fRec67[0] = ((fConst62 * ((fTemp154 + (fConst162 * fRec68[0])) + (fConst163 * fRec68[2]))) - (fConst55 * ((fConst164 * fRec67[2]) + fTemp155)));
			float fTemp156 = (fConst50 * fRec66[1]);
			fRec66[0] = ((fConst55 * (((fConst57 * fRec67[0]) + fTemp155) + (fConst166 * fRec67[2]))) - (fConst49 * (fTemp156 + (fConst167 * fRec66[2]))));
			float fTemp157 = (fConst171 * fRec65[1]);
			fRec65[0] = ((fConst49 * ((fTemp156 + (fConst169 * fRec66[0])) + (fConst170 * fRec66[2]))) - (fConst39 * (fTemp157 + (fConst172 * fRec65[2]))));
			float fTemp158 = ((fConst43 * fRec65[2]) + ((fConst173 * fRec65[0]) + fTemp157));
			fVec20[0] = fTemp158;
			fRec64[0] = ((fConst39 * ((fConst41 * fTemp158) + (fConst174 * fVec20[1]))) - (fConst176 * fRec64[1]));
			fRec63[0] = (fRec64[0] - (fConst32 * ((fConst177 * fRec63[2]) + (fConst179 * fRec63[1]))));
			fRec88[0] = (0.0f - (fConst180 * ((fConst175 * fRec88[1]) - (fConst39 * (fVec20[1] + fTemp158)))));
			fRec87[0] = (fRec88[0] - (fConst32 * ((fConst177 * fRec87[2]) + (fConst179 * fRec87[1]))));
			float fTemp159 = (fConst29 * fRec62[1]);
			fRec62[0] = ((fConst32 * ((((fConst34 * fRec63[1]) + (fConst178 * fRec63[0])) + (fConst178 * fRec63[2])) + (fSlow196 * ((fRec87[0] + (2.0f * fRec87[1])) + fRec87[2])))) - ((fTemp159 + (fRec62[2] * fSlow201)) / fSlow202));
			float fTemp160 = (fConst186 * fRec61[1]);
			fRec61[0] = ((((fTemp159 + (fRec62[0] * fSlow204)) + (fRec62[2] * fSlow205)) / fSlow202) - (((fRec61[2] * fSlow210) + fTemp160) / fSlow211));
			float fTemp161 = (fConst27 * fRec60[1]);
			fRec60[0] = ((((fRec61[2] * fSlow213) + (fTemp160 + (fRec61[0] * fSlow214))) / fSlow211) - ((fTemp161 + (fRec60[2] * fSlow219)) / fSlow220));
			output0[i] = FAUSTFLOAT((fSlow0 * (((iSlow1?(fSlow194 * (((fTemp161 + (fRec60[0] * fSlow222)) + (fRec60[2] * fSlow223)) / fSlow220)):fTemp145) * fSlow234) * fSlow236)));
			fVec0[1] = fVec0[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec24[1] = fRec24[0];
			fRec25[1] = fRec25[0];
			fVec1[1] = fVec1[0];
			fRec20[1] = fRec20[0];
			fVec2[1] = fVec2[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fRec30[1] = fRec30[0];
			fVec3[1] = fVec3[0];
			fRec29[1] = fRec29[0];
			fVec4[1] = fVec4[0];
			fRec28[1] = fRec28[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec37[1] = fRec37[0];
			fRec27[1] = fRec27[0];
			fVec5[1] = fVec5[0];
			fRec26[1] = fRec26[0];
			fVec6[1] = fVec6[0];
			fRec19[1] = fRec19[0];
			fRec39[1] = fRec39[0];
			fRec38[1] = fRec38[0];
			fRec40[1] = fRec40[0];
			fRec18[1] = fRec18[0];
			fVec7[1] = fVec7[0];
			fRec17[1] = fRec17[0];
			fVec8[1] = fVec8[0];
			fRec16[1] = fRec16[0];
			fRec42[1] = fRec42[0];
			fRec41[1] = fRec41[0];
			fRec43[1] = fRec43[0];
			fRec15[1] = fRec15[0];
			fVec9[1] = fVec9[0];
			fRec14[1] = fRec14[0];
			fVec10[1] = fVec10[0];
			fRec13[1] = fRec13[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec46[1] = fRec46[0];
			fRec12[1] = fRec12[0];
			fVec11[1] = fVec11[0];
			fRec11[1] = fRec11[0];
			fVec12[1] = fVec12[0];
			fRec10[1] = fRec10[0];
			fRec48[1] = fRec48[0];
			fRec47[1] = fRec47[0];
			fRec49[1] = fRec49[0];
			fRec50[1] = fRec50[0];
			fVec13[1] = fVec13[0];
			fRec9[1] = fRec9[0];
			fVec14[1] = fVec14[0];
			fRec8[1] = fRec8[0];
			fRec51[1] = fRec51[0];
			fVec15[1] = fVec15[0];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fVec16[1] = fVec16[0];
			fRec4[1] = fRec4[0];
			fRec52[1] = fRec52[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec17[1] = fVec17[0];
			fRec2[1] = fRec2[0];
			fRec53[1] = fRec53[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fRec56[1] = fRec56[0];
			fRec57[1] = fRec57[0];
			fRec58[1] = fRec58[0];
			fRec59[1] = fRec59[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fVec18[1] = fVec18[0];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fVec19[1] = fVec19[0];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec86[1] = fRec86[0];
			fRec85[2] = fRec85[1];
			fRec85[1] = fRec85[0];
			fRec84[2] = fRec84[1];
			fRec84[1] = fRec84[0];
			fRec83[2] = fRec83[1];
			fRec83[1] = fRec83[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fVec20[1] = fVec20[0];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec88[1] = fRec88[0];
			fRec87[2] = fRec87[1];
			fRec87[1] = fRec87[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];

		}

	}


};

#endif
