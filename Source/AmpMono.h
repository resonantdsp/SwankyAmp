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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	FAUSTFLOAT fEntry3;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fEntry4;
	float fConst7;
	float fConst8;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
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
	float fConst15;
	FAUSTFLOAT fEntry18;
	FAUSTFLOAT fEntry19;
	float fConst16;
	FAUSTFLOAT fEntry20;
	FAUSTFLOAT fEntry21;
	FAUSTFLOAT fEntry22;
	FAUSTFLOAT fEntry23;
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	float fConst17;
	FAUSTFLOAT fEntry27;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	float fVec0[2];
	float fRec17[2];
	float fConst23;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fConst24;
	FAUSTFLOAT fEntry32;
	float fConst25;
	FAUSTFLOAT fEntry33;
	float fRec19[2];
	float fRec18[2];
	FAUSTFLOAT fEntry34;
	float fConst26;
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec20[2];
	float fRec16[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	float fVec1[2];
	float fRec15[2];
	float fVec2[2];
	float fRec14[2];
	float fConst27;
	float fConst28;
	float fConst29;
	float fRec22[2];
	float fRec21[2];
	float fConst30;
	float fRec23[2];
	float fConst31;
	float fRec13[2];
	float fVec3[2];
	float fRec12[2];
	float fVec4[2];
	float fRec11[2];
	float fConst32;
	float fConst33;
	float fRec25[2];
	float fRec24[2];
	float fRec26[2];
	float fRec10[2];
	float fVec5[2];
	float fRec9[2];
	float fVec6[2];
	float fRec32[2];
	float fRec34[2];
	float fRec33[2];
	float fRec35[2];
	float fRec31[2];
	float fVec7[2];
	float fRec30[2];
	float fVec8[2];
	float fRec29[2];
	float fRec37[2];
	float fRec36[2];
	float fRec38[2];
	float fRec28[2];
	float fVec9[2];
	float fRec27[2];
	float fVec10[2];
	float fRec44[2];
	float fRec46[2];
	float fRec45[2];
	float fRec47[2];
	float fRec43[2];
	float fVec11[2];
	float fRec42[2];
	float fVec12[2];
	float fRec41[2];
	float fRec49[2];
	float fRec48[2];
	float fRec50[2];
	float fRec40[2];
	float fVec13[2];
	float fRec39[2];
	float fVec14[2];
	float fRec8[2];
	float fRec51[2];
	float fVec15[2];
	float fConst34;
	float fConst35;
	float fRec7[2];
	float fConst36;
	FAUSTFLOAT fEntry39;
	float fConst37;
	float fConst38;
	float fRec6[3];
	float fConst39;
	float fRec5[3];
	float fVec16[2];
	float fRec4[2];
	float fRec52[2];
	float fConst40;
	float fConst41;
	float fConst42;
	FAUSTFLOAT fEntry40;
	float fConst43;
	float fRec3[3];
	FAUSTFLOAT fEntry41;
	float fVec17[2];
	float fRec2[2];
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	float fRec54[2];
	float fRec53[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	FAUSTFLOAT fEntry49;
	float fRec55[2];
	float fRec1[2];
	FAUSTFLOAT fEntry50;
	FAUSTFLOAT fEntry51;
	float fRec56[2];
	float fRec57[2];
	FAUSTFLOAT fEntry52;
	FAUSTFLOAT fEntry53;
	FAUSTFLOAT fEntry54;
	float fRec58[2];
	float fConst44;
	float fRec0[3];
	FAUSTFLOAT fEntry55;
	FAUSTFLOAT fEntry56;
	float fRec59[2];
	FAUSTFLOAT fEntry57;
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
	float fConst127;
	float fConst128;
	float fConst129;
	float fConst130;
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fRec82[3];
	float fConst152;
	float fRec81[3];
	float fVec18[2];
	float fRec80[2];
	float fConst153;
	float fConst154;
	float fRec79[3];
	float fVec19[2];
	float fConst155;
	float fConst156;
	float fConst157;
	float fRec78[2];
	float fConst158;
	float fConst159;
	float fRec77[3];
	float fConst160;
	float fRec76[3];
	float fConst161;
	float fRec75[3];
	float fConst162;
	float fRec86[2];
	float fRec85[3];
	float fRec84[3];
	float fRec83[3];
	float fConst163;
	float fConst164;
	float fRec74[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec73[3];
	float fConst168;
	float fConst169;
	float fRec72[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec71[3];
	float fConst175;
	float fConst176;
	float fRec70[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec69[3];
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec68[3];
	float fConst185;
	float fConst186;
	float fConst187;
	float fRec67[3];
	float fConst188;
	float fConst189;
	float fConst190;
	float fRec66[3];
	float fConst191;
	float fConst192;
	float fConst193;
	float fRec65[3];
	float fConst194;
	float fVec20[2];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec64[2];
	float fConst198;
	float fConst199;
	float fRec63[3];
	float fConst200;
	FAUSTFLOAT fEntry58;
	float fConst201;
	float fRec88[2];
	float fRec87[3];
	float fConst202;
	float fConst203;
	float fRec62[3];
	float fConst204;
	float fConst205;
	float fRec61[3];
	float fConst206;
	float fConst207;
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
		fConst1 = (2.0f / fConst0);
		fConst2 = (2.0f * fConst0);
		fConst3 = (3.14159274f / fConst0);
		fConst4 = (0.5f * fConst0);
		fConst5 = (0.5f / fConst0);
		fConst6 = (4.0f * AmpMono_faustpower2_f(fConst0));
		fConst7 = (1.0f / fConst0);
		fConst8 = AmpMono_faustpower2_f(fConst7);
		fConst9 = std::tan((1570.79639f / fConst0));
		fConst10 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst11 = std::tan((31.415926f / fConst0));
		fConst12 = (1.0f / fConst11);
		fConst13 = (fConst12 + 1.0f);
		fConst14 = (0.0f - (1.0f / (fConst11 * fConst13)));
		fConst15 = (1.32210004f * fConst0);
		fConst16 = (1.13f * fConst0);
		fConst17 = (3.48716784f / fConst0);
		fConst18 = (0.980000019f * fConst0);
		fConst19 = (2.70176959f / fConst0);
		fConst20 = (0.854399979f * fConst0);
		fConst21 = (0.889999986f * fConst0);
		fConst22 = (3.39292002f / fConst0);
		fConst23 = (0.874800026f * fConst0);
		fConst24 = (0.801900029f * fConst0);
		fConst25 = (0.810000002f * fConst0);
		fConst26 = (1.16279066f / fConst0);
		fConst27 = (0.864799976f * fConst0);
		fConst28 = (0.91079998f * fConst0);
		fConst29 = (0.920000017f * fConst0);
		fConst30 = (1.12359548f / fConst0);
		fConst31 = (0.921199977f * fConst0);
		fConst32 = (0.959999979f * fConst0);
		fConst33 = (0.931200027f * fConst0);
		fConst34 = (1.0f / fConst13);
		fConst35 = (1.0f - fConst12);
		fConst36 = (1.0f / fConst9);
		fConst37 = (fConst0 * std::sin((3141.59277f / fConst0)));
		fConst38 = (3.14159274f / fConst37);
		fConst39 = (3141.59277f / fConst37);
		fConst40 = std::tan((12566.3711f / fConst0));
		fConst41 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst40))));
		fConst42 = (1.0f / fConst40);
		fConst43 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
		fConst44 = (2.0f * fConst8);
		fConst45 = std::tan((3769.91113f / fConst0));
		fConst46 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst45))));
		fConst47 = std::tan((219.911484f / fConst0));
		fConst48 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst47))));
		fConst49 = std::tan((18849.5566f / fConst0));
		fConst50 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst49))));
		fConst51 = std::tan((3455.75195f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (1.0f / (((fConst52 + 1.0f) / fConst51) + 1.0f));
		fConst54 = AmpMono_faustpower2_f(fConst51);
		fConst55 = (1.0f / fConst54);
		fConst56 = std::tan((2984.51294f / fConst0));
		fConst57 = (1.0f / fConst56);
		fConst58 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst59 = (27816.8476f / fConst58);
		fConst60 = (1.0f / (((fConst57 + fConst59) / fConst56) + 1.0f));
		fConst61 = (fConst52 + 1.0f);
		fConst62 = (1.0f / (fConst51 * fConst61));
		fConst63 = (8796.45898f / fConst58);
		fConst64 = (((fConst57 + fConst63) / fConst56) + 1.0f);
		fConst65 = (37699.1133f / fConst0);
		fConst66 = std::tan(fConst65);
		fConst67 = (1.0f / fConst66);
		fConst68 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst69 = (24836.4707f / fConst68);
		fConst70 = (1.0f / (((fConst67 + fConst69) / fConst66) + 1.0f));
		fConst71 = (785.398193f / fConst68);
		fConst72 = (((fConst67 - fConst71) / fConst66) + 1.0f);
		fConst73 = std::tan((21362.8301f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst76 = (19869.1758f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (628.318542f / fConst75);
		fConst79 = (((fConst74 + fConst78) / fConst73) + 1.0f);
		fConst80 = std::tan((11938.0518f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst83 = (4701.22607f / fConst82);
		fConst84 = (1.0f / (((fConst81 + fConst83) / fConst80) + 1.0f));
		fConst85 = (2356.19458f / fConst82);
		fConst86 = (((fConst81 + fConst85) / fConst80) + 1.0f);
		fConst87 = std::tan((9581.85742f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst90 = (2921.88965f / fConst89);
		fConst91 = (1.0f / (((fConst88 + fConst90) / fConst87) + 1.0f));
		fConst92 = (1036.72558f / fConst89);
		fConst93 = (((fConst88 - fConst92) / fConst87) + 1.0f);
		fConst94 = std::tan((5215.04394f / fConst0));
		fConst95 = (1.0f / fConst94);
		fConst96 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst97 = (3713.44482f / fConst96);
		fConst98 = (1.0f / (((fConst95 + fConst97) / fConst94) + 1.0f));
		fConst99 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst94))));
		fConst100 = (3707.07935f / fConst0);
		fConst101 = std::tan(fConst100);
		fConst102 = (1.0f / fConst101);
		fConst103 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst104 = (502.654816f / fConst103);
		fConst105 = (1.0f / (((fConst102 + fConst104) / fConst101) + 1.0f));
		fConst106 = (1416.67383f / fConst103);
		fConst107 = (((fConst102 - fConst106) / fConst101) + 1.0f);
		fConst108 = std::tan((3518.58374f / fConst0));
		fConst109 = (1.0f / fConst108);
		fConst110 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst111 = (875.483398f / fConst110);
		fConst112 = (1.0f / (((fConst109 + fConst111) / fConst108) + 1.0f));
		fConst113 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst108))));
		fConst114 = std::tan((2010.61926f / fConst0));
		fConst115 = (1.0f / fConst114);
		fConst116 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst117 = (439.822968f / fConst116);
		fConst118 = (1.0f / (((fConst115 + fConst117) / fConst114) + 1.0f));
		fConst119 = (1390.84241f / fConst116);
		fConst120 = (((fConst115 - fConst119) / fConst114) + 1.0f);
		fConst121 = std::tan((1853.53967f / fConst0));
		fConst122 = (1.0f / fConst121);
		fConst123 = (fConst0 * std::sin(fConst100));
		fConst124 = (1059.9884f / fConst123);
		fConst125 = (1.0f / (((fConst122 + fConst124) / fConst121) + 1.0f));
		fConst126 = (188.49556f / fConst123);
		fConst127 = (((fConst122 + fConst126) / fConst121) + 1.0f);
		fConst128 = std::tan((17592.918f / fConst0));
		fConst129 = (1.0f / fConst128);
		fConst130 = (1.0f / (((fConst129 + 0.445041865f) / fConst128) + 1.0f));
		fConst131 = AmpMono_faustpower2_f(fConst128);
		fConst132 = (1.0f / fConst131);
		fConst133 = (1.0f / (((fConst129 + 1.24697959f) / fConst128) + 1.0f));
		fConst134 = (0.0f - (2.0f / fConst131));
		fConst135 = (1.0f / (((fConst129 + 1.8019377f) / fConst128) + 1.0f));
		fConst136 = std::tan((34557.5195f / fConst0));
		fConst137 = (1.0f / fConst136);
		fConst138 = (1.0f / (((fConst137 + 1.0f) / fConst136) + 1.0f));
		fConst139 = (fConst129 + 1.0f);
		fConst140 = (1.0f / (fConst128 * fConst139));
		fConst141 = (1.0f / (fConst137 + 1.0f));
		fConst142 = (1.0f - fConst137);
		fConst143 = std::tan((345.575195f / fConst0));
		fConst144 = (1.0f / fConst143);
		fConst145 = (1.0f / (((fConst144 + 0.765366852f) / fConst143) + 1.0f));
		fConst146 = AmpMono_faustpower2_f(fConst143);
		fConst147 = (1.0f / fConst146);
		fConst148 = (1.0f / (((fConst144 + 1.84775901f) / fConst143) + 1.0f));
		fConst149 = (0.0f - (2.0f / fConst146));
		fConst150 = (((fConst144 + -1.84775901f) / fConst143) + 1.0f);
		fConst151 = (2.0f * (1.0f - fConst147));
		fConst152 = (((fConst144 + -0.765366852f) / fConst143) + 1.0f);
		fConst153 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst136))));
		fConst154 = (((fConst137 + -1.0f) / fConst136) + 1.0f);
		fConst155 = (0.0f - fConst140);
		fConst156 = (1.0f - fConst129);
		fConst157 = (fConst156 / fConst139);
		fConst158 = (2.0f * (1.0f - fConst132));
		fConst159 = (((fConst129 + -1.8019377f) / fConst128) + 1.0f);
		fConst160 = (((fConst129 + -1.24697959f) / fConst128) + 1.0f);
		fConst161 = (((fConst129 + -0.445041865f) / fConst128) + 1.0f);
		fConst162 = (1.0f / fConst139);
		fConst163 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst121))));
		fConst164 = (((fConst122 - fConst124) / fConst121) + 1.0f);
		fConst165 = (((fConst122 - fConst126) / fConst121) + 1.0f);
		fConst166 = (((fConst115 - fConst117) / fConst114) + 1.0f);
		fConst167 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst114))));
		fConst168 = (((fConst115 + fConst119) / fConst114) + 1.0f);
		fConst169 = (((fConst109 - fConst111) / fConst108) + 1.0f);
		fConst170 = (219.911484f / fConst110);
		fConst171 = (((fConst109 + fConst170) / fConst108) + 1.0f);
		fConst172 = (((fConst109 - fConst170) / fConst108) + 1.0f);
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst101))));
		fConst174 = (((fConst102 - fConst104) / fConst101) + 1.0f);
		fConst175 = (((fConst102 + fConst106) / fConst101) + 1.0f);
		fConst176 = (((fConst95 - fConst97) / fConst94) + 1.0f);
		fConst177 = (2481.85815f / fConst96);
		fConst178 = (((fConst95 + fConst177) / fConst94) + 1.0f);
		fConst179 = (((fConst95 - fConst177) / fConst94) + 1.0f);
		fConst180 = (((fConst88 - fConst90) / fConst87) + 1.0f);
		fConst181 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst87))));
		fConst182 = (((fConst88 + fConst92) / fConst87) + 1.0f);
		fConst183 = (((fConst81 - fConst83) / fConst80) + 1.0f);
		fConst184 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst80))));
		fConst185 = (((fConst81 - fConst85) / fConst80) + 1.0f);
		fConst186 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst187 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst188 = (((fConst74 - fConst78) / fConst73) + 1.0f);
		fConst189 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst190 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst191 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst192 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst56))));
		fConst193 = (((fConst57 - fConst59) / fConst56) + 1.0f);
		fConst194 = (((fConst57 - fConst63) / fConst56) + 1.0f);
		fConst195 = (0.0f - fConst62);
		fConst196 = (1.0f - fConst52);
		fConst197 = (fConst196 / fConst61);
		fConst198 = (2.0f * (1.0f - fConst55));
		fConst199 = (((fConst52 + -1.0f) / fConst51) + 1.0f);
		fConst200 = (0.0f - (2.0f / fConst54));
		fConst201 = (1.0f / fConst61);
		fConst202 = (1.0f / fConst49);
		fConst203 = (3141.59277f / (fConst0 * std::sin(fConst65)));
		fConst204 = (1.0f / fConst47);
		fConst205 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst206 = (1.0f / fConst45);
		fConst207 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));

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
			fRec17[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec19[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec18[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec20[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec16[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec15[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec2[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec14[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec22[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec21[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec23[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec13[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fVec3[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec12[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec4[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec11[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec25[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec24[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec26[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec10[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fVec5[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec9[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec6[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec32[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec34[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec33[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec35[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec31[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec7[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec30[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec8[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec29[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec37[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec36[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec38[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec28[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fVec9[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec27[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec10[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec44[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec46[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec45[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec47[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec43[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fVec11[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec42[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fVec12[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec41[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec49[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec48[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fRec50[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec40[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fVec13[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec39[l55] = 0.0f;

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
			fRec54[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
			fRec53[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fRec55[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec1[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec56[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec57[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec58[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec0[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
			fRec59[l77] = 0.0f;

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
	void set_input_level(FAUSTFLOAT value) { fEntry28 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry29 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry44 = value + 4.244119e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry41 = value + 4.772432e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry46 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry42 = value + 6.149084e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry43 = value + -6.103051e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry45 = value + 2.089429e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry4 = value + -2.881866e+00f; }
	void set_tetrode_lp_freq(FAUSTFLOAT value) { fEntry3 = value + 4.886859e-01f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry7 = value + 5.109376e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry50 = value + 1.071150e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry8 = value + -5.416368e-01f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry9 = value + -1.307331e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry51 = value + 5.973931e-01f; }
	void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) { fEntry55 = value + -1.137037e-02f; }
	void set_tetrode_plate_drift2_level(FAUSTFLOAT value) { fEntry56 = value + 5.639039e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry47 = value + 1.736788e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry49 = value + 1.148646e+00f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry48 = value + -2.438411e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry6 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_onset(FAUSTFLOAT value) { fEntry53 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) { fEntry54 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_tau(FAUSTFLOAT value) { fEntry52 = value + 0.000000e+00f; }
	void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) { fEntry5 = value + -1.000000e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry10 = value + 3.358906e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry25 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry26 = value + 2.098359e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry33 = value + 3.350094e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry32 = value + 1.208385e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry30 = value + 1.499258e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry31 = value + -1.358083e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry27 = value + 4.527706e-01f; }
	void set_triode_lp_freq(FAUSTFLOAT value) { fEntry16 = value + 2.891656e+00f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry22 = value + 2.395946e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry24 = value + 4.949643e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry21 = value + -1.032404e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry38 = value + -1.750309e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry17 = value + -2.337059e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry20 = value + -1.437850e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry37 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry19 = value + 1.985518e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry18 = value + -9.502671e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry23 = value + -7.156034e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry34 = value + -8.226774e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry36 = value + 1.022375e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry35 = value + -1.098961e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524394e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry39 = value + 0.000000e+00f; }
	void set_ts_presence(FAUSTFLOAT value) { fEntry40 = value + 0.000000e+00f; }
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
		float fSlow4 = std::tan((fConst3 * std::min<float>(fConst4, std::exp(((0.549306154f * (float(fEntry3) + 1.0f)) + 8.51719284f)))));
		float fSlow5 = (float(fEntry4) + 1.0f);
		float fSlow6 = AmpMono_faustpower2_f(std::sqrt((fConst6 * (fSlow4 * std::tan((fConst3 * std::min<float>(fConst4, std::exp(((1.15129256f * fSlow5) + 2.30258512f)))))))));
		float fSlow7 = ((fConst2 * fSlow4) - (fConst5 * (fSlow6 / fSlow4)));
		float fSlow8 = (fConst8 * fSlow6);
		float fSlow9 = (fConst1 * fSlow7);
		float fSlow10 = ((fSlow8 + fSlow9) + 4.0f);
		float fSlow11 = (fConst1 * (fSlow7 / fSlow10));
		float fSlow12 = (0.5f * ((float(fEntry5) + 1.0f) * std::exp(((2.30258512f * (float(fEntry6) + 1.0f)) + -2.30258512f))));
		float fSlow13 = (fSlow12 + 1.0f);
		float fSlow14 = ((20.0f * (float(fEntry7) + 1.0f)) + 10.0f);
		float fSlow15 = std::exp(((2.30258512f * (float(fEntry8) + 1.0f)) + -2.30258512f));
		float fSlow16 = std::exp((0.0f - (fConst7 / std::exp(((3.45387769f * (float(fEntry9) + 1.0f)) + -6.90775537f)))));
		float fSlow17 = (1.0f - fSlow16);
		float fSlow18 = (1.0f / fSlow14);
		float fSlow19 = std::exp(((4.60517025f * (float(fEntry10) + 1.0f)) + -4.60517025f));
		float fSlow20 = std::tan((fConst3 * std::exp(((3.45387769f * fSlow5) + -2.30258512f))));
		float fSlow21 = (1.0f / fSlow20);
		float fSlow22 = (fSlow21 + 1.0f);
		float fSlow23 = (0.0f - (1.0f / (fSlow20 * fSlow22)));
		float fSlow24 = (float(fEntry11) + 1.0f);
		float fSlow25 = (fSlow2 * std::exp(((3.45387769f * fSlow24) + -0.693147182f)));
		float fSlow26 = float(fEntry12);
		int iSlow27 = (fSlow26 < 0.0f);
		float fSlow28 = std::tan((fConst3 * ((iSlow27?(1500.0f * fSlow26):0.0f) + 2000.0f)));
		float fSlow29 = (1.0f / fSlow28);
		float fSlow30 = (1.0f - fSlow29);
		float fSlow31 = float(fEntry13);
		float fSlow32 = (fSlow31 + 1.0f);
		float fSlow33 = (1.0f - (0.5f * fSlow32));
		float fSlow34 = std::tan((fConst3 * ((400.0f * fSlow33) + (25.0f * fSlow32))));
		float fSlow35 = (1.0f / fSlow34);
		float fSlow36 = (fSlow35 + 1.0f);
		float fSlow37 = (0.0f - (1.0f / (fSlow34 * fSlow36)));
		float fSlow38 = float(fEntry14);
		float fSlow39 = std::max<float>(0.0f, (std::min<float>(7.0f, fSlow38) + -5.0f));
		float fSlow40 = (1.0f - (0.5f * fSlow39));
		float fSlow41 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow38) + -3.0f));
		float fSlow42 = (1.0f - (0.5f * fSlow41));
		float fSlow43 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow38) + -1.0f));
		float fSlow44 = ((float(fEntry15) + 1.0f) + 1.0f);
		float fSlow45 = (fSlow43 / fSlow44);
		float fSlow46 = (1.0f / std::tan((fConst3 * std::min<float>(fConst4, std::exp(((0.549306154f * (float(fEntry16) + 1.0f)) + 8.51719284f))))));
		float fSlow47 = (1.0f / (fSlow46 + 1.0f));
		float fSlow48 = (1.0f - fSlow46);
		float fSlow49 = std::exp(((2.30258512f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow50 = std::exp(((3.45387769f * (float(fEntry18) + 1.0f)) + -6.90775537f));
		float fSlow51 = (fSlow50 * std::exp((1.15129256f * (float(fEntry19) + 1.0f))));
		float fSlow52 = (1.0f - (1.0f / ((fConst15 * fSlow51) + 1.0f)));
		float fSlow53 = (1.0f / ((fConst16 * fSlow50) + 1.0f));
		float fSlow54 = (0.0f - (100.0f * (1.0f - (float(fEntry20) + 1.0f))));
		float fSlow55 = (0.949999988f * fSlow54);
		float fSlow56 = (0.0f - (100.0f * (1.0f - (float(fEntry21) + 1.0f))));
		float fSlow57 = (0.970000029f * fSlow56);
		float fSlow58 = (0.0f - (100.0f * (1.0f - (float(fEntry22) + 1.0f))));
		float fSlow59 = (1.11000001f * fSlow58);
		float fSlow60 = std::exp(((4.60517025f * (float(fEntry23) + 1.0f)) + -4.60517025f));
		float fSlow61 = (fSlow57 + fSlow60);
		float fSlow62 = std::exp(((4.60517025f * (float(fEntry24) + 1.0f)) + -2.30258512f));
		float fSlow63 = (0.294117659f / fSlow62);
		float fSlow64 = (0.959999979f * fSlow2);
		float fSlow65 = (float(fEntry25) + 1.0f);
		float fSlow66 = (2.375f * fSlow65);
		float fSlow67 = (float(fEntry26) + 1.0f);
		float fSlow68 = (2.5f * fSlow67);
		float fSlow69 = std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -2.30258512f));
		float fSlow70 = std::tan((fConst17 * fSlow69));
		float fSlow71 = (1.0f / fSlow70);
		float fSlow72 = (fSlow71 + 1.0f);
		float fSlow73 = (0.0f - (1.0f / (fSlow72 * fSlow70)));
		float fSlow74 = (1.0f / ((fConst18 * fSlow50) + 1.0f));
		float fSlow75 = (0.959999979f * fSlow54);
		float fSlow76 = (0.99000001f * fSlow56);
		float fSlow77 = (0.860000014f * fSlow58);
		float fSlow78 = (fSlow60 + fSlow76);
		float fSlow79 = (0.920000017f * fSlow2);
		float fSlow80 = (2.4000001f * fSlow65);
		float fSlow81 = std::tan((fConst19 * fSlow69));
		float fSlow82 = (1.0f / fSlow81);
		float fSlow83 = (fSlow82 + 1.0f);
		float fSlow84 = (1.0f / fSlow83);
		float fSlow85 = (fSlow81 * fSlow2);
		float fSlow86 = (0.5f * (fSlow44 / fSlow85));
		float fSlow87 = (1.0f / ((fConst20 * fSlow51) + 1.0f));
		float fSlow88 = (1.0f - fSlow87);
		float fSlow89 = (1.0f / ((fConst21 * fSlow50) + 1.0f));
		float fSlow90 = (0.889999986f * fSlow54);
		float fSlow91 = (0.294117659f / fSlow60);
		float fSlow92 = (1.08000004f * fSlow58);
		float fSlow93 = (0.810000002f * fSlow2);
		float fSlow94 = (2.2249999f * fSlow65);
		float fSlow95 = std::tan((fConst22 * fSlow69));
		float fSlow96 = (1.0f / fSlow95);
		float fSlow97 = (fSlow96 + 1.0f);
		float fSlow98 = (0.0f - (1.0f / (fSlow95 * fSlow97)));
		float fSlow99 = (float(fEntry29) + 1.0f);
		float fSlow100 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry28) + 1.0f)))))) * std::exp((3.80045128f * fSlow99)));
		float fSlow101 = (1.0f / fSlow97);
		float fSlow102 = (1.0f - fSlow96);
		float fSlow103 = (fSlow100 / fSlow95);
		float fSlow104 = std::exp(((3.45387769f * (float(fEntry31) + 1.0f)) + -13.8155107f));
		float fSlow105 = (std::exp(((6.90775537f * (float(fEntry30) + 1.0f)) + -11.5129251f)) * fSlow104);
		float fSlow106 = (1.0f / ((fConst23 * fSlow105) + 1.0f));
		float fSlow107 = (1.0f - fSlow106);
		float fSlow108 = (fSlow104 * std::exp(((5.75646257f * (float(fEntry32) + 1.0f)) + -2.30258512f)));
		float fSlow109 = (1.0f - (1.0f / ((fConst24 * fSlow108) + 1.0f)));
		float fSlow110 = (1.0f / ((fConst25 * fSlow104) + 1.0f));
		float fSlow111 = (0.0f - (5.0f * (1.0f - (float(fEntry33) + 1.0f))));
		float fSlow112 = (0.860000014f * fSlow111);
		float fSlow113 = (0.117647059f / fSlow67);
		float fSlow114 = std::exp(((2.30258512f * (float(fEntry34) + 1.0f)) + -2.30258512f));
		float fSlow115 = std::exp(((3.45387769f * (float(fEntry35) + 1.0f)) + -6.90775537f));
		float fSlow116 = std::exp((0.0f - (fConst26 / fSlow115)));
		float fSlow117 = (1.0f - fSlow116);
		float fSlow118 = (100.0f * (1.0f - (float(fEntry36) + 1.0f)));
		float fSlow119 = (0.0f - fSlow118);
		float fSlow120 = (1.08000004f * fSlow119);
		float fSlow121 = (100.0f * (1.0f - (float(fEntry37) + 1.0f)));
		float fSlow122 = std::exp(((3.45387769f * (float(fEntry38) + 1.0f)) + -2.30258512f));
		float fSlow123 = ((fSlow76 + fSlow121) + fSlow122);
		float fSlow124 = (0.294117659f / fSlow122);
		float fSlow125 = (1.0f - fSlow82);
		float fSlow126 = (0.0f - (1.0f / (fSlow83 * fSlow81)));
		float fSlow127 = (0.5f * (fSlow44 / fSlow2));
		float fSlow128 = (1.0f / ((fConst27 * fSlow105) + 1.0f));
		float fSlow129 = (1.0f - fSlow128);
		float fSlow130 = (1.0f - (1.0f / ((fConst28 * fSlow108) + 1.0f)));
		float fSlow131 = (1.0f / ((fConst29 * fSlow104) + 1.0f));
		float fSlow132 = (0.889999986f * fSlow111);
		float fSlow133 = std::exp((0.0f - (fConst30 / fSlow115)));
		float fSlow134 = (1.0f - fSlow133);
		float fSlow135 = (0.939999998f * fSlow119);
		float fSlow136 = (1.0f - (1.0f / ((fConst31 * fSlow51) + 1.0f)));
		float fSlow137 = (1.0f / fSlow72);
		float fSlow138 = (1.0f - fSlow71);
		float fSlow139 = (fSlow70 * fSlow2);
		float fSlow140 = (1.0f / fSlow139);
		float fSlow141 = (1.0f / ((fConst32 * fSlow105) + 1.0f));
		float fSlow142 = (1.0f - fSlow141);
		float fSlow143 = (1.0f / ((fConst32 * fSlow104) + 1.0f));
		float fSlow144 = (1.0f - (1.0f / ((fConst33 * fSlow108) + 1.0f)));
		float fSlow145 = (fSlow122 + (fSlow57 + fSlow121));
		float fSlow146 = (1.0f - (0.5f * fSlow43));
		float fSlow147 = (0.5f * fSlow44);
		float fSlow148 = AmpMono_faustpower2_f(fSlow147);
		float fSlow149 = (0.5f * (fSlow41 / fSlow148));
		float fSlow150 = (fSlow148 / fSlow2);
		float fSlow151 = (fSlow95 * fSlow2);
		float fSlow152 = (fSlow148 / fSlow151);
		float fSlow153 = (1.0f / fSlow85);
		float fSlow154 = AmpMono_faustpower3_f(fSlow147);
		float fSlow155 = (0.5f * (fSlow39 / fSlow154));
		float fSlow156 = (fSlow154 / fSlow2);
		float fSlow157 = (fSlow154 / fSlow139);
		float fSlow158 = (1.0f / fSlow151);
		float fSlow159 = (fSlow87 + -1.0f);
		float fSlow160 = (1.0f / fSlow36);
		float fSlow161 = (1.0f - fSlow35);
		float fSlow162 = (1.0f / (fSlow34 * fSlow2));
		float fSlow163 = std::pow(10.0f, (0.0500000007f * (fSlow31 * ((18.0f * fSlow33) + (4.5f * fSlow32)))));
		float fSlow164 = float(fEntry39);
		float fSlow165 = (fSlow164 + 1.0f);
		float fSlow166 = ((fSlow164 * ((2.5f * fSlow165) + (10.0f * (1.0f - (0.5f * fSlow165))))) + -14.0f);
		int iSlow167 = (fSlow166 > 0.0f);
		float fSlow168 = ((800.0f * fSlow164) + 1200.0f);
		float fSlow169 = (fConst38 * (fSlow168 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow166)))));
		float fSlow170 = (fConst38 * fSlow168);
		float fSlow171 = (iSlow167?fSlow170:fSlow169);
		float fSlow172 = ((fConst36 * (fConst36 - fSlow171)) + 1.0f);
		float fSlow173 = ((fConst36 * (fConst36 + fSlow171)) + 1.0f);
		float fSlow174 = (iSlow167?fSlow169:fSlow170);
		float fSlow175 = ((fConst36 * (fConst36 - fSlow174)) + 1.0f);
		float fSlow176 = ((fConst36 * (fConst36 + fSlow174)) + 1.0f);
		float fSlow177 = (fSlow164 * ((fSlow164 > 0.0f)?5.0f:0.0f));
		int iSlow178 = (fSlow177 > 0.0f);
		float fSlow179 = (fConst39 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow177))));
		float fSlow180 = (iSlow178?fConst39:fSlow179);
		float fSlow181 = ((fConst36 * (fConst36 - fSlow180)) + 1.0f);
		float fSlow182 = ((fConst36 * (fConst36 + fSlow180)) + 1.0f);
		float fSlow183 = (iSlow178?fSlow179:fConst39);
		float fSlow184 = ((fConst36 * (fConst36 + fSlow183)) + 1.0f);
		float fSlow185 = ((fConst36 * (fConst36 - fSlow183)) + 1.0f);
		float fSlow186 = (fSlow29 + 1.0f);
		float fSlow187 = (0.0f - (1.0f / (fSlow28 * fSlow186)));
		float fSlow188 = (fSlow28 * fSlow182);
		float fSlow189 = std::pow(10.0f, ((0.0500000007f * fSlow26) * (iSlow27?18.0f:9.0f)));
		float fSlow190 = (10.0f * float(fEntry40));
		int iSlow191 = (fSlow190 > 0.0f);
		float fSlow192 = (fConst43 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow190))));
		float fSlow193 = (iSlow191?fConst43:fSlow192);
		float fSlow194 = ((fConst42 * (fConst42 - fSlow193)) + 1.0f);
		float fSlow195 = ((fConst42 * (fConst42 + fSlow193)) + 1.0f);
		float fSlow196 = (iSlow191?fSlow192:fConst43);
		float fSlow197 = ((fConst42 * (fConst42 + fSlow196)) + 1.0f);
		float fSlow198 = ((fConst42 * (fConst42 - fSlow196)) + 1.0f);
		float fSlow199 = (5.0f * fSlow99);
		int iSlow200 = (fSlow199 < 9.0f);
		int iSlow201 = (fSlow199 < 8.0f);
		int iSlow202 = (fSlow199 < 7.0f);
		int iSlow203 = (fSlow199 < 6.0f);
		int iSlow204 = (fSlow199 < 5.0f);
		int iSlow205 = (fSlow199 < 4.0f);
		int iSlow206 = (fSlow199 < 3.0f);
		int iSlow207 = (fSlow199 < 2.0f);
		int iSlow208 = (fSlow199 < 1.0f);
		float fSlow209 = std::pow(10.0f, (0.0500000007f * (iSlow200?(iSlow201?(iSlow202?(iSlow203?(iSlow204?(iSlow205?(iSlow206?(iSlow207?(iSlow208?((fSlow199 < 0.0f)?13.6999998f:(iSlow208?(13.6999998f - (32.9500008f * fSlow99)):7.11000013f)):(iSlow207?(7.11000013f - (6.57399988f * (fSlow199 + -1.0f))):0.536000013f)):(iSlow206?(0.536000013f - (6.546f * (fSlow199 + -2.0f))):-6.01000023f)):(iSlow205?(-6.01000023f - (6.59000015f * (fSlow199 + -3.0f))):-12.6000004f)):(iSlow204?(-12.6000004f - (5.0f * (fSlow199 + -4.0f))):-17.6000004f)):(iSlow203?(-17.6000004f - (2.79999995f * (0.0f - (5.0f * (1.0f - fSlow99))))):-20.3999996f)):(iSlow202?(-20.3999996f - (1.29999995f * (fSlow199 + -6.0f))):-21.7000008f)):(iSlow201?(-21.7000008f - (0.400000006f * (fSlow199 + -7.0f))):-22.1000004f)):(iSlow200?(-22.1000004f - (0.300000012f * (fSlow199 + -8.0f))):-22.3999996f)):((fSlow199 < 10.0f)?(-22.3999996f - (0.400000006f * (fSlow199 + -9.0f))):-22.7999992f))));
		float fSlow210 = (250.0f * (float(fEntry41) + 1.0f));
		float fSlow211 = (1.0f / fSlow22);
		float fSlow212 = (1.0f - fSlow21);
		float fSlow213 = std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f));
		float fSlow214 = (1.0f - (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -4.60517025f)) * fSlow213)) + 1.0f)));
		float fSlow215 = (1.0f / ((fConst0 * fSlow213) + 1.0f));
		float fSlow216 = (100.0f * (1.0f - (float(fEntry44) + 1.0f)));
		float fSlow217 = std::exp((0.0f - (fConst7 / std::exp(((4.60517025f * (float(fEntry45) + 1.0f)) + -9.2103405f)))));
		float fSlow218 = (1.0f - fSlow217);
		float fSlow219 = (250.0f * (float(fEntry46) + 1.0f));
		float fSlow220 = std::exp(((2.30258512f * (float(fEntry47) + 1.0f)) + -2.30258512f));
		float fSlow221 = std::exp((0.0f - (fConst7 / std::exp(((3.45387769f * (float(fEntry48) + 1.0f)) + -6.90775537f)))));
		float fSlow222 = (1.0f - fSlow221);
		float fSlow223 = (100.0f * (1.0f - (float(fEntry49) + 1.0f)));
		float fSlow224 = (0.0f - fSlow223);
		float fSlow225 = std::exp(((3.45387769f * (float(fEntry50) + 1.0f)) + -2.30258512f));
		float fSlow226 = (0.294117659f / fSlow225);
		float fSlow227 = std::exp(((3.45387769f * (float(fEntry51) + 1.0f)) + -2.30258512f));
		float fSlow228 = (0.294117659f / fSlow227);
		float fSlow229 = std::exp(((1.95601153f * (float(fEntry52) + 1.0f)) + -4.60517025f));
		float fSlow230 = (1.0f / ((fConst0 * fSlow229) + 1.0f));
		float fSlow231 = (fSlow19 / fSlow14);
		float fSlow232 = std::exp(((2.30258512f * (float(fEntry53) + 1.0f)) + -2.30258512f));
		float fSlow233 = (1.0f - (1.0f / ((fConst0 * (fSlow229 * std::exp((1.15129256f * (float(fEntry54) + 1.0f))))) + 1.0f)));
		float fSlow234 = (1.0f / fSlow10);
		float fSlow235 = (fSlow8 + (4.0f - fSlow9));
		float fSlow236 = ((fConst44 * fSlow6) + -8.0f);
		float fSlow237 = (0.0f - fSlow11);
		float fSlow238 = std::exp(((2.30258512f * (float(fEntry55) + 1.0f)) + -2.30258512f));
		float fSlow239 = (50.0f * (1.0f - (float(fEntry56) + 1.0f)));
		float fSlow240 = (0.0f - fSlow239);
		float fSlow241 = float(fEntry57);
		float fSlow242 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow241)));
		float fSlow243 = float(fEntry58);
		float fSlow244 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow243))));
		float fSlow245 = (15.0f * fSlow243);
		int iSlow246 = (fSlow245 > 0.0f);
		float fSlow247 = (fConst203 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow245))));
		float fSlow248 = (iSlow246?fConst203:fSlow247);
		float fSlow249 = ((fConst202 * (fConst202 - fSlow248)) + 1.0f);
		float fSlow250 = ((fConst202 * (fConst202 + fSlow248)) + 1.0f);
		float fSlow251 = (iSlow246?fSlow247:fConst203);
		float fSlow252 = ((fConst202 * (fConst202 + fSlow251)) + 1.0f);
		float fSlow253 = ((fConst202 * (fConst202 - fSlow251)) + 1.0f);
		float fSlow254 = (0.0f - (10.0f * fSlow241));
		int iSlow255 = (fSlow254 > 0.0f);
		float fSlow256 = (fConst205 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow254))));
		float fSlow257 = (iSlow255?fConst205:fSlow256);
		float fSlow258 = ((fConst204 * (fConst204 - fSlow257)) + 1.0f);
		float fSlow259 = ((fConst204 * (fConst204 + fSlow257)) + 1.0f);
		float fSlow260 = (iSlow255?fSlow256:fConst205);
		float fSlow261 = ((fConst204 * (fConst204 + fSlow260)) + 1.0f);
		float fSlow262 = ((fConst204 * (fConst204 - fSlow260)) + 1.0f);
		float fSlow263 = (0.0f - (17.0f * fSlow241));
		int iSlow264 = (fSlow263 > 0.0f);
		float fSlow265 = (fConst207 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow263))));
		float fSlow266 = (iSlow264?fConst207:fSlow265);
		float fSlow267 = ((fConst206 * (fConst206 - fSlow266)) + 1.0f);
		float fSlow268 = ((fConst206 * (fConst206 + fSlow266)) + 1.0f);
		float fSlow269 = (iSlow264?fSlow265:fConst207);
		float fSlow270 = ((fConst206 * (fConst206 + fSlow269)) + 1.0f);
		float fSlow271 = ((fConst206 * (fConst206 - fSlow269)) + 1.0f);
		float fSlow272 = (5.0f * fSlow24);
		int iSlow273 = (fSlow272 < 8.0f);
		int iSlow274 = (fSlow272 < 7.0f);
		int iSlow275 = (fSlow272 < 6.0f);
		int iSlow276 = (fSlow272 < 5.0f);
		int iSlow277 = (fSlow272 < 4.0f);
		int iSlow278 = (fSlow272 < 3.0f);
		int iSlow279 = (fSlow272 < 2.0f);
		int iSlow280 = (fSlow272 < 1.0f);
		float fSlow281 = std::pow(10.0f, (0.0500000007f * ((fSlow272 < 9.0f)?(iSlow273?(iSlow274?(iSlow275?(iSlow276?(iSlow277?(iSlow278?(iSlow279?(iSlow280?((fSlow272 < 0.0f)?5.26999998f:(iSlow280?(5.26999998f - (27.9449997f * fSlow24)):-0.319000006f)):(iSlow279?(-0.319000006f - (5.28100014f * (fSlow272 + -1.0f))):-5.5999999f)):(iSlow278?(-5.5999999f - (5.4000001f * (fSlow272 + -2.0f))):-11.0f)):(iSlow277?(-11.0f - (5.4000001f * (fSlow272 + -3.0f))):-16.3999996f)):(iSlow276?(-16.3999996f - (3.20000005f * (fSlow272 + -4.0f))):-19.6000004f)):(iSlow275?(-19.6000004f - (1.10000002f * (0.0f - (5.0f * (1.0f - fSlow24))))):-20.7000008f)):(iSlow274?(-20.7000008f - (0.200000003f * (fSlow272 + -6.0f))):-20.8999996f)):(iSlow273?((0.100000001f * (fSlow272 + -7.0f)) + -20.8999996f):-20.7999992f)):-20.7999992f):((fSlow272 < 10.0f)?((0.100000001f * (fSlow272 + -9.0f)) + -20.7999992f):-20.7000008f))));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow100 * fTemp0);
			fRec17[0] = ((fSlow98 * fVec0[1]) - (fSlow101 * ((fSlow102 * fRec17[1]) - (fSlow103 * fTemp0))));
			fRec19[0] = ((fSlow109 * fRec19[1]) + (fSlow110 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec17[0] - fSlow112)) - fRec19[1]))));
			fRec18[0] = ((fSlow107 * fRec18[1]) + (fSlow106 * fRec19[0]));
			float fTemp1 = (fSlow68 + ((fRec17[0] - fRec18[0]) - fSlow94));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
			float fTemp4 = (fSlow92 + ((fSlow93 * (fSlow94 + (std::min<float>(0.0f, fTemp1) - (fSlow68 * (1.0f - (fTemp3 * (std::fabs(fTemp3) + -2.0f))))))) - fSlow62));
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (fSlow92 - (fSlow78 + (std::max<float>(0.0f, fTemp4) + (fSlow62 * ((((std::fabs((fTemp6 * fTemp5)) + -2.0f) * fTemp6) * fTemp5) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = ((std::fabs(fTemp8) + -2.0f) * fTemp8);
			float fTemp10 = ((fSlow60 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp7));
			fRec20[0] = ((fSlow116 * fRec20[1]) + (fSlow117 * (std::max<float>(fSlow120, (fSlow76 + fTemp10)) - fSlow120)));
			float fTemp11 = (fSlow114 * fRec20[0]);
			fRec16[0] = ((fSlow88 * fRec16[1]) + (fSlow89 * std::max<float>(0.0f, ((std::max<float>(fSlow90, (fSlow76 + (fTemp10 - fTemp11))) - fRec16[1]) - fSlow90))));
			float fTemp12 = (fSlow49 * fRec16[0]);
			float fTemp13 = (fSlow123 + (fTemp10 - (fTemp11 + fTemp12)));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((fTemp12 + std::min<float>(0.0f, fTemp13)) - (fSlow122 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow121);
			fVec1[0] = fTemp16;
			fRec15[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec15[1]) - (fVec1[1] + fTemp16))));
			fVec2[0] = (fSlow127 * fRec15[0]);
			fRec14[0] = ((fSlow84 * ((fSlow86 * fRec15[0]) - (fSlow125 * fRec14[1]))) + (fSlow126 * fVec2[1]));
			fRec22[0] = ((fSlow130 * fRec22[1]) + (fSlow131 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec14[0] - fSlow132)) - fRec22[1]))));
			fRec21[0] = ((fSlow129 * fRec21[1]) + (fSlow128 * fRec22[0]));
			float fTemp17 = (fSlow68 + ((fRec14[0] - fRec21[0]) - fSlow80));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = (fSlow77 + ((fSlow79 * (fSlow80 + (std::min<float>(0.0f, fTemp17) - (fSlow68 * (1.0f - (((std::fabs((fTemp18 * fTemp19)) + -2.0f) * fTemp18) * fTemp19)))))) - fSlow62));
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (fTemp21 * (std::fabs(fTemp21) + -2.0f));
			float fTemp23 = (fSlow77 - (fSlow78 + (std::max<float>(0.0f, fTemp20) + (fSlow62 * ((fTemp22 * (std::fabs(fTemp22) + -2.0f)) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (std::fabs(fTemp24) + -2.0f);
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow60 * (((fTemp25 * (std::fabs((fTemp25 * fTemp24)) + -2.0f)) * fTemp24) + 1.0f)));
			fRec23[0] = ((fSlow133 * fRec23[1]) + (fSlow134 * (std::max<float>(fSlow135, (fSlow76 + fTemp26)) - fSlow135)));
			float fTemp27 = (fSlow114 * fRec23[0]);
			fRec13[0] = ((fSlow74 * std::max<float>(0.0f, ((std::max<float>(fSlow75, (fSlow76 + (fTemp26 - fTemp27))) - fRec13[1]) - fSlow75))) + (fSlow136 * fRec13[1]));
			float fTemp28 = (fSlow49 * fRec13[0]);
			float fTemp29 = (fSlow123 + (fTemp26 - (fTemp27 + fTemp28)));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (std::fabs(fTemp30) + -2.0f);
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow122 * (1.0f - ((fTemp30 * (std::fabs((fTemp30 * fTemp31)) + -2.0f)) * fTemp31)))) - fSlow121);
			fVec3[0] = fTemp32;
			fRec12[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec12[1]) - (fTemp32 + fVec3[1]))));
			fVec4[0] = (fSlow3 * fRec12[0]);
			fRec11[0] = ((fSlow73 * fVec4[1]) - (fSlow137 * ((fSlow138 * fRec11[1]) - (fSlow140 * fRec12[0]))));
			fRec25[0] = ((fSlow143 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec11[0] - fSlow132)) - fRec25[1]))) + (fSlow144 * fRec25[1]));
			fRec24[0] = ((fSlow142 * fRec24[1]) + (fSlow141 * fRec25[0]));
			float fTemp33 = (fSlow68 + ((fRec11[0] - fRec24[0]) - fSlow66));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = (fSlow59 + ((fSlow64 * (fSlow66 + (std::min<float>(0.0f, fTemp33) - (fSlow68 * (1.0f - ((fTemp34 * (std::fabs((fTemp34 * fTemp35)) + -2.0f)) * fTemp35)))))) - fSlow62));
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (std::fabs(fTemp37) + -2.0f);
			float fTemp39 = (fSlow59 - (fSlow61 + ((fSlow62 * ((((std::fabs((fTemp37 * fTemp38)) + -2.0f) * fTemp37) * fTemp38) + 1.0f)) + std::max<float>(0.0f, fTemp36))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (fTemp40 * (std::fabs(fTemp40) + -2.0f));
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow60 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)));
			fRec26[0] = ((fSlow133 * fRec26[1]) + (fSlow134 * (fSlow118 + std::max<float>(fSlow119, (fSlow57 + fTemp42)))));
			float fTemp43 = (fSlow114 * fRec26[0]);
			fRec10[0] = ((fSlow52 * fRec10[1]) + (fSlow53 * std::max<float>(0.0f, ((std::max<float>(fSlow55, (fSlow57 + (fTemp42 - fTemp43))) - fRec10[1]) - fSlow55))));
			float fTemp44 = (fSlow49 * fRec10[0]);
			float fTemp45 = (fSlow145 + (fTemp42 - (fTemp44 + fTemp43)));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow122 * (1.0f - ((fTemp46 * (std::fabs((fTemp46 * fTemp47)) + -2.0f)) * fTemp47)))) - fSlow121);
			fVec5[0] = fTemp48;
			fRec9[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec9[1]) - (fVec5[1] + fTemp48))));
			float fTemp49 = ((fSlow45 * fRec9[0]) + (fSlow146 * fRec15[0]));
			fVec6[0] = (fSlow150 * fTemp49);
			fRec32[0] = ((fSlow98 * fVec6[1]) - (fSlow101 * ((fSlow102 * fRec32[1]) - (fSlow152 * fTemp49))));
			fRec34[0] = ((fSlow110 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec32[0] - fSlow112)) - fRec34[1]))) + (fSlow109 * fRec34[1]));
			fRec33[0] = ((fSlow107 * fRec33[1]) + (fSlow106 * fRec34[0]));
			float fTemp50 = (fSlow68 + ((fRec32[0] - fRec33[0]) - fSlow94));
			float fTemp51 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp50))));
			float fTemp52 = (std::fabs(fTemp51) + -2.0f);
			float fTemp53 = (fSlow92 + ((fSlow93 * (fSlow94 + (std::min<float>(0.0f, fTemp50) - (fSlow68 * (1.0f - ((fTemp51 * (std::fabs((fTemp51 * fTemp52)) + -2.0f)) * fTemp52)))))) - fSlow62));
			float fTemp54 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp53))));
			float fTemp55 = (std::fabs(fTemp54) + -2.0f);
			float fTemp56 = (fSlow92 - (fSlow78 + (std::max<float>(0.0f, fTemp53) + (fSlow62 * ((((std::fabs((fTemp55 * fTemp54)) + -2.0f) * fTemp55) * fTemp54) + 1.0f)))));
			float fTemp57 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp56))));
			float fTemp58 = (std::fabs(fTemp57) + -2.0f);
			float fTemp59 = (std::max<float>(0.0f, fTemp56) + (fSlow60 * ((((std::fabs((fTemp57 * fTemp58)) + -2.0f) * fTemp57) * fTemp58) + 1.0f)));
			fRec35[0] = ((fSlow116 * fRec35[1]) + (fSlow117 * (std::max<float>(fSlow120, (fSlow76 + fTemp59)) - fSlow120)));
			float fTemp60 = (fSlow114 * fRec35[0]);
			fRec31[0] = ((fSlow88 * fRec31[1]) + (fSlow89 * std::max<float>(0.0f, ((std::max<float>(fSlow90, (fSlow76 + (fTemp59 - fTemp60))) - fRec31[1]) - fSlow90))));
			float fTemp61 = (fSlow49 * fRec31[0]);
			float fTemp62 = (fSlow123 + (fTemp59 - (fTemp60 + fTemp61)));
			float fTemp63 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp62))));
			float fTemp64 = (std::fabs(fTemp63) + -2.0f);
			float fTemp65 = (((fTemp61 + std::min<float>(0.0f, fTemp62)) - (fSlow122 * (1.0f - (((std::fabs((fTemp63 * fTemp64)) + -2.0f) * fTemp63) * fTemp64)))) - fSlow121);
			fVec7[0] = fTemp65;
			fRec30[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec30[1]) - (fTemp65 + fVec7[1]))));
			fVec8[0] = (fSlow3 * fRec30[0]);
			fRec29[0] = ((fSlow126 * fVec8[1]) - (fSlow84 * ((fSlow125 * fRec29[1]) - (fSlow153 * fRec30[0]))));
			fRec37[0] = ((fSlow130 * fRec37[1]) + (fSlow131 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec29[0] - fSlow132)) - fRec37[1]))));
			fRec36[0] = ((fSlow129 * fRec36[1]) + (fSlow128 * fRec37[0]));
			float fTemp66 = (fSlow68 + ((fRec29[0] - fRec36[0]) - fSlow80));
			float fTemp67 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp66))));
			float fTemp68 = (std::fabs(fTemp67) + -2.0f);
			float fTemp69 = (fSlow77 + ((fSlow79 * (fSlow80 + (std::min<float>(0.0f, fTemp66) - (fSlow68 * (1.0f - (((std::fabs((fTemp68 * fTemp67)) + -2.0f) * fTemp68) * fTemp67)))))) - fSlow62));
			float fTemp70 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp69))));
			float fTemp71 = (std::fabs(fTemp70) + -2.0f);
			float fTemp72 = (fSlow77 - (fSlow78 + (std::max<float>(0.0f, fTemp69) + (fSlow62 * ((((std::fabs((fTemp70 * fTemp71)) + -2.0f) * fTemp70) * fTemp71) + 1.0f)))));
			float fTemp73 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp72))));
			float fTemp74 = (std::fabs(fTemp73) + -2.0f);
			float fTemp75 = (std::max<float>(0.0f, fTemp72) + (fSlow60 * (((fTemp73 * (std::fabs((fTemp73 * fTemp74)) + -2.0f)) * fTemp74) + 1.0f)));
			fRec38[0] = ((fSlow133 * fRec38[1]) + (fSlow134 * (std::max<float>(fSlow135, (fSlow76 + fTemp75)) - fSlow135)));
			float fTemp76 = (fSlow114 * fRec38[0]);
			fRec28[0] = ((fSlow136 * fRec28[1]) + (fSlow74 * std::max<float>(0.0f, ((std::max<float>(fSlow75, (fSlow76 + (fTemp75 - fTemp76))) - fRec28[1]) - fSlow75))));
			float fTemp77 = (fSlow49 * fRec28[0]);
			float fTemp78 = (fSlow123 + (fTemp75 - (fTemp77 + fTemp76)));
			float fTemp79 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp78))));
			float fTemp80 = (std::fabs(fTemp79) + -2.0f);
			float fTemp81 = (((fTemp77 + std::min<float>(0.0f, fTemp78)) - (fSlow122 * (1.0f - (((std::fabs((fTemp79 * fTemp80)) + -2.0f) * fTemp79) * fTemp80)))) - fSlow121);
			fVec9[0] = fTemp81;
			fRec27[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec27[1]) - (fTemp81 + fVec9[1]))));
			float fTemp82 = ((fSlow42 * fTemp49) + (fSlow149 * fRec27[0]));
			fVec10[0] = (fSlow156 * fTemp82);
			fRec44[0] = ((fSlow73 * fVec10[1]) - (fSlow137 * ((fSlow138 * fRec44[1]) - (fSlow157 * fTemp82))));
			fRec46[0] = ((fSlow143 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec44[0] - fSlow132)) - fRec46[1]))) + (fSlow144 * fRec46[1]));
			fRec45[0] = ((fSlow142 * fRec45[1]) + (fSlow141 * fRec46[0]));
			float fTemp83 = (fSlow68 + ((fRec44[0] - fRec45[0]) - fSlow66));
			float fTemp84 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp83))));
			float fTemp85 = (fTemp84 * (std::fabs(fTemp84) + -2.0f));
			float fTemp86 = (fSlow59 + ((fSlow64 * (fSlow66 + (std::min<float>(0.0f, fTemp83) - (fSlow68 * (1.0f - (fTemp85 * (std::fabs(fTemp85) + -2.0f))))))) - fSlow62));
			float fTemp87 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp86))));
			float fTemp88 = (fTemp87 * (std::fabs(fTemp87) + -2.0f));
			float fTemp89 = (fSlow59 - (fSlow61 + (std::max<float>(0.0f, fTemp86) + (fSlow62 * ((fTemp88 * (std::fabs(fTemp88) + -2.0f)) + 1.0f)))));
			float fTemp90 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp89))));
			float fTemp91 = ((std::fabs(fTemp90) + -2.0f) * fTemp90);
			float fTemp92 = (std::max<float>(0.0f, fTemp89) + (fSlow60 * ((fTemp91 * (std::fabs(fTemp91) + -2.0f)) + 1.0f)));
			fRec47[0] = ((fSlow133 * fRec47[1]) + (fSlow134 * (fSlow118 + std::max<float>(fSlow119, (fSlow57 + fTemp92)))));
			float fTemp93 = (fSlow114 * fRec47[0]);
			fRec43[0] = ((fSlow52 * fRec43[1]) + (fSlow53 * std::max<float>(0.0f, ((std::max<float>(fSlow55, (fSlow57 + (fTemp92 - fTemp93))) - fRec43[1]) - fSlow55))));
			float fTemp94 = (fSlow49 * fRec43[0]);
			float fTemp95 = (fSlow145 + (fTemp92 - (fTemp93 + fTemp94)));
			float fTemp96 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp95))));
			float fTemp97 = ((std::fabs(fTemp96) + -2.0f) * fTemp96);
			float fTemp98 = (((fTemp94 + std::min<float>(0.0f, fTemp95)) - (fSlow122 * (1.0f - (fTemp97 * (std::fabs(fTemp97) + -2.0f))))) - fSlow121);
			fVec11[0] = fTemp98;
			fRec42[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec42[1]) - (fVec11[1] + fTemp98))));
			fVec12[0] = (fSlow3 * fRec42[0]);
			fRec41[0] = ((fSlow98 * fVec12[1]) - (fSlow101 * ((fSlow102 * fRec41[1]) - (fSlow158 * fRec42[0]))));
			fRec49[0] = ((fSlow110 * std::max<float>(0.0f, (std::max<float>(0.0f, (fRec41[0] - fSlow112)) - fRec49[1]))) + (fSlow109 * fRec49[1]));
			fRec48[0] = ((fSlow107 * fRec48[1]) + (fSlow106 * fRec49[0]));
			float fTemp99 = (fSlow68 + ((fRec41[0] - fRec48[0]) - fSlow94));
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow113 * std::max<float>(0.0f, fTemp99))));
			float fTemp101 = (std::fabs(fTemp100) + -2.0f);
			float fTemp102 = (fSlow92 + ((fSlow93 * (fSlow94 + (std::min<float>(0.0f, fTemp99) - (fSlow68 * (1.0f - ((fTemp101 * (std::fabs((fTemp101 * fTemp100)) + -2.0f)) * fTemp100)))))) - fSlow62));
			float fTemp103 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow63 * std::min<float>(0.0f, fTemp102))));
			float fTemp104 = (std::fabs(fTemp103) + -2.0f);
			float fTemp105 = (fSlow92 - (fSlow78 + ((fSlow62 * ((((std::fabs((fTemp103 * fTemp104)) + -2.0f) * fTemp103) * fTemp104) + 1.0f)) + std::max<float>(0.0f, fTemp102))));
			float fTemp106 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow91 * std::min<float>(0.0f, fTemp105))));
			float fTemp107 = ((std::fabs(fTemp106) + -2.0f) * fTemp106);
			float fTemp108 = ((fSlow60 * ((fTemp107 * (std::fabs(fTemp107) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp105));
			fRec50[0] = ((fSlow117 * (std::max<float>(fSlow120, (fSlow76 + fTemp108)) - fSlow120)) + (fSlow116 * fRec50[1]));
			float fTemp109 = (fSlow114 * fRec50[0]);
			fRec40[0] = ((fSlow89 * std::max<float>(0.0f, ((std::max<float>(fSlow90, (fSlow76 + (fTemp108 - fTemp109))) - fRec40[1]) - fSlow90))) - (fSlow159 * fRec40[1]));
			float fTemp110 = (fSlow49 * fRec40[0]);
			float fTemp111 = (fSlow123 + (fTemp108 - (fTemp109 + fTemp110)));
			float fTemp112 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow124 * std::max<float>(0.0f, fTemp111))));
			float fTemp113 = (fTemp112 * (std::fabs(fTemp112) + -2.0f));
			float fTemp114 = (((fTemp110 + std::min<float>(0.0f, fTemp111)) - (fSlow122 * (1.0f - (fTemp113 * (std::fabs(fTemp113) + -2.0f))))) - fSlow121);
			fVec13[0] = fTemp114;
			fRec39[0] = (0.0f - (fSlow47 * ((fSlow48 * fRec39[1]) - (fTemp114 + fVec13[1]))));
			float fTemp115 = ((fSlow40 * fTemp82) + (fSlow155 * fRec39[0]));
			float fTemp116 = (fSlow3 * fTemp115);
			fVec14[0] = fTemp116;
			fRec8[0] = ((fSlow37 * fVec14[1]) - (fSlow160 * ((fSlow161 * fRec8[1]) - (fSlow162 * fTemp115))));
			fRec51[0] = (fSlow160 * ((fTemp116 + fVec14[1]) - (fSlow161 * fRec51[1])));
			float fTemp117 = (fRec8[0] + (fSlow163 * fRec51[0]));
			fVec15[0] = fTemp117;
			fRec7[0] = ((fConst14 * fVec15[1]) - (fConst34 * ((fConst35 * fRec7[1]) - (fConst12 * fTemp117))));
			float fTemp118 = (fConst10 * fRec6[1]);
			fRec6[0] = (fRec7[0] - ((fTemp118 + (fSlow172 * fRec6[2])) / fSlow173));
			float fTemp119 = (fConst10 * fRec5[1]);
			fRec5[0] = ((((fRec6[2] * fSlow175) + (fTemp118 + (fRec6[0] * fSlow176))) / fSlow173) - ((fTemp119 + (fRec5[2] * fSlow181)) / fSlow182));
			float fTemp120 = ((fTemp119 + (fRec5[0] * fSlow184)) + (fRec5[2] * fSlow185));
			float fTemp121 = (fTemp120 / fSlow182);
			fVec16[0] = fTemp121;
			fRec4[0] = (0.0f - (((fSlow30 * fRec4[1]) - (fVec16[1] + fTemp121)) / fSlow186));
			fRec52[0] = ((fVec16[1] * fSlow187) - (((fRec52[1] * fSlow30) - (fTemp120 / fSlow188)) / fSlow186));
			float fTemp122 = (fConst41 * fRec3[1]);
			fRec3[0] = ((fRec4[0] + (fRec52[0] * fSlow189)) - ((fTemp122 + (fSlow194 * fRec3[2])) / fSlow195));
			float fTemp123 = ((fSlow25 * (((((fRec3[0] * fSlow197) + fTemp122) + (fSlow198 * fRec3[2])) * fSlow209) / fSlow195)) - fSlow210);
			fVec17[0] = fTemp123;
			fRec2[0] = ((fSlow23 * fVec17[1]) - (fSlow211 * ((fSlow212 * fRec2[1]) - (fSlow21 * fTemp123))));
			fRec54[0] = ((fSlow217 * fRec54[1]) + (fSlow218 * (fRec2[0] - fSlow219)));
			fRec53[0] = ((fSlow214 * fRec53[1]) + (fSlow215 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow216 + ((fRec2[0] - fRec54[0]) - fSlow219))) - fRec53[1]))));
			float fTemp124 = ((fRec2[0] - (fRec53[0] + fRec54[0])) - fSlow219);
			float fTemp125 = (fSlow19 * fTemp124);
			fRec55[0] = ((fSlow222 * (fSlow223 + std::max<float>(fSlow224, fTemp125))) + (fSlow221 * fRec55[1]));
			float fTemp126 = (fSlow220 * fRec55[0]);
			fRec1[0] = ((fSlow17 * std::min<float>(1.0f, std::fabs((fSlow18 * (fTemp125 - fTemp126))))) + (fSlow16 * fRec1[1]));
			float fTemp127 = (fSlow14 / ((fSlow15 * fRec1[0]) + 1.0f));
			float fTemp128 = (fSlow225 + (fTemp125 - (fTemp126 + fTemp127)));
			float fTemp129 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow226 * std::max<float>(0.0f, fTemp128))));
			float fTemp130 = (std::fabs(fTemp129) + -2.0f);
			float fTemp131 = (((fTemp127 + std::min<float>(0.0f, fTemp128)) - (fSlow225 * (1.0f - (((std::fabs((fTemp130 * fTemp129)) + -2.0f) * fTemp130) * fTemp129)))) - fSlow227);
			fRec56[0] = ((fSlow221 * fRec56[1]) + (fSlow222 * (fSlow223 + std::max<float>(fSlow224, (0.0f - fTemp125)))));
			float fTemp132 = ((fSlow220 * fRec56[0]) + fTemp125);
			fRec57[0] = ((fSlow16 * fRec57[1]) + (fSlow17 * std::min<float>(1.0f, std::fabs((fSlow18 * (0.0f - fTemp132))))));
			float fTemp133 = (fSlow14 / ((fSlow15 * fRec57[0]) + 1.0f));
			float fTemp134 = (fSlow225 - (fTemp132 + fTemp133));
			float fTemp135 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow226 * std::max<float>(0.0f, fTemp134))));
			float fTemp136 = (std::fabs(fTemp135) + -2.0f);
			float fTemp137 = ((((fSlow225 * (((fTemp135 * (std::fabs((fTemp135 * fTemp136)) + -2.0f)) * fTemp136) + -1.0f)) + fTemp133) + std::min<float>(0.0f, fTemp134)) - fSlow227);
			float fTemp138 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow228 * std::min<float>(0.0f, fTemp137))));
			float fTemp139 = (fTemp138 * (std::fabs(fTemp138) + -2.0f));
			float fTemp140 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow228 * std::min<float>(0.0f, fTemp131))));
			float fTemp141 = (std::fabs(fTemp140) + -2.0f);
			float fTemp142 = std::fabs((fSlow231 * fTemp124));
			fRec58[0] = ((fSlow230 * std::max<float>(0.0f, ((std::max<float>(1.0f, fTemp142) + (fSlow232 * std::min<float>(1.0f, fTemp142))) + (-1.0f - fRec58[1])))) + (fSlow233 * fRec58[1]));
			fRec0[0] = ((fSlow13 * ((std::max<float>(0.0f, fTemp131) - (std::max<float>(0.0f, fTemp137) + (fSlow227 * (((fTemp139 * (std::fabs(fTemp139) + -2.0f)) + 1.0f) - ((((std::fabs((fTemp140 * fTemp141)) + -2.0f) * fTemp140) * fTemp141) + 1.0f))))) / ((fSlow12 * fRec58[0]) + 1.0f))) - (fSlow234 * ((fSlow235 * fRec0[2]) + (fSlow236 * fRec0[1]))));
			float fTemp143 = ((fSlow11 * fRec0[0]) + (fSlow237 * fRec0[2]));
			fRec59[0] = ((fSlow222 * (fSlow239 + std::max<float>(fSlow240, std::fabs(fTemp143)))) + (fSlow221 * fRec59[1]));
			float fTemp144 = (fSlow3 * (fTemp143 + (fSlow238 * fRec59[0])));
			fRec82[0] = (fTemp144 - (fConst148 * ((fConst150 * fRec82[2]) + (fConst151 * fRec82[1]))));
			fRec81[0] = ((fConst148 * (((fConst149 * fRec82[1]) + (fConst147 * fRec82[0])) + (fConst147 * fRec82[2]))) - (fConst145 * ((fConst152 * fRec81[2]) + (fConst151 * fRec81[1]))));
			float fTemp145 = (((fConst147 * fRec81[0]) + (fConst149 * fRec81[1])) + (fConst147 * fRec81[2]));
			fVec18[0] = fTemp145;
			fRec80[0] = (0.0f - (fConst141 * ((fConst142 * fRec80[1]) - (fConst145 * (fTemp145 + fVec18[1])))));
			fRec79[0] = (fRec80[0] - (fConst138 * ((fConst153 * fRec79[1]) + (fConst154 * fRec79[2]))));
			float fTemp146 = (fRec79[2] + (fRec79[0] + (2.0f * fRec79[1])));
			fVec19[0] = fTemp146;
			fRec78[0] = ((fConst138 * ((fConst140 * fTemp146) + (fConst155 * fVec19[1]))) - (fConst157 * fRec78[1]));
			fRec77[0] = (fRec78[0] - (fConst135 * ((fConst158 * fRec77[1]) + (fConst159 * fRec77[2]))));
			fRec76[0] = ((fConst135 * (((fConst134 * fRec77[1]) + (fConst132 * fRec77[0])) + (fConst132 * fRec77[2]))) - (fConst133 * ((fConst160 * fRec76[2]) + (fConst158 * fRec76[1]))));
			fRec75[0] = ((fConst133 * (((fConst134 * fRec76[1]) + (fConst132 * fRec76[0])) + (fConst132 * fRec76[2]))) - (fConst130 * ((fConst161 * fRec75[2]) + (fConst158 * fRec75[1]))));
			fRec86[0] = (0.0f - (fConst162 * ((fConst156 * fRec86[1]) - (fConst138 * (fVec19[1] + fTemp146)))));
			fRec85[0] = (fRec86[0] - (fConst135 * ((fConst158 * fRec85[1]) + (fConst159 * fRec85[2]))));
			fRec84[0] = ((fConst135 * ((fRec85[0] + (2.0f * fRec85[1])) + fRec85[2])) - (fConst133 * ((fConst160 * fRec84[2]) + (fConst158 * fRec84[1]))));
			fRec83[0] = ((fConst133 * (fRec84[2] + (fRec84[0] + (2.0f * fRec84[1])))) - (fConst130 * ((fConst158 * fRec83[1]) + (fConst161 * fRec83[2]))));
			float fTemp147 = (fConst163 * fRec74[1]);
			fRec74[0] = ((fConst130 * ((0.0316227749f * ((fConst132 * fRec75[2]) + ((fConst134 * fRec75[1]) + (fConst132 * fRec75[0])))) + (fRec83[2] + (fRec83[0] + (2.0f * fRec83[1]))))) - (fConst125 * (fTemp147 + (fConst164 * fRec74[2]))));
			float fTemp148 = (fConst167 * fRec73[1]);
			fRec73[0] = ((fConst125 * (((fConst127 * fRec74[0]) + fTemp147) + (fConst165 * fRec74[2]))) - (fConst118 * ((fConst166 * fRec73[2]) + fTemp148)));
			float fTemp149 = (fConst113 * fRec72[1]);
			fRec72[0] = ((fConst118 * ((fConst120 * fRec73[2]) + (fTemp148 + (fConst168 * fRec73[0])))) - (fConst112 * (fTemp149 + (fConst169 * fRec72[2]))));
			float fTemp150 = (fConst173 * fRec71[1]);
			fRec71[0] = ((fConst112 * ((fTemp149 + (fConst171 * fRec72[0])) + (fConst172 * fRec72[2]))) - (fConst105 * (fTemp150 + (fConst174 * fRec71[2]))));
			float fTemp151 = (fConst99 * fRec70[1]);
			fRec70[0] = ((fConst105 * ((fConst107 * fRec71[2]) + (fTemp150 + (fConst175 * fRec71[0])))) - (fConst98 * ((fConst176 * fRec70[2]) + fTemp151)));
			float fTemp152 = (fConst181 * fRec69[1]);
			fRec69[0] = ((fConst98 * ((fTemp151 + (fConst178 * fRec70[0])) + (fConst179 * fRec70[2]))) - (fConst91 * ((fConst180 * fRec69[2]) + fTemp152)));
			float fTemp153 = (fConst184 * fRec68[1]);
			fRec68[0] = ((fConst91 * ((fConst93 * fRec69[2]) + ((fConst182 * fRec69[0]) + fTemp152))) - (fConst84 * ((fConst183 * fRec68[2]) + fTemp153)));
			float fTemp154 = (fConst186 * fRec67[1]);
			fRec67[0] = ((fConst84 * (((fConst86 * fRec68[0]) + fTemp153) + (fConst185 * fRec68[2]))) - (fConst77 * (fTemp154 + (fConst187 * fRec67[2]))));
			float fTemp155 = (fConst189 * fRec66[1]);
			fRec66[0] = ((fConst77 * (((fConst79 * fRec67[0]) + fTemp154) + (fConst188 * fRec67[2]))) - (fConst70 * (fTemp155 + (fConst190 * fRec66[2]))));
			float fTemp156 = (fConst192 * fRec65[1]);
			fRec65[0] = ((fConst70 * ((fConst72 * fRec66[2]) + (fTemp155 + (fConst191 * fRec66[0])))) - (fConst60 * (fTemp156 + (fConst193 * fRec65[2]))));
			float fTemp157 = (((fConst64 * fRec65[0]) + fTemp156) + (fConst194 * fRec65[2]));
			fVec20[0] = fTemp157;
			fRec64[0] = ((fConst60 * ((fConst62 * fTemp157) + (fConst195 * fVec20[1]))) - (fConst197 * fRec64[1]));
			fRec63[0] = (fRec64[0] - (fConst53 * ((fConst198 * fRec63[1]) + (fConst199 * fRec63[2]))));
			fRec88[0] = (fConst201 * ((fConst60 * (fVec20[1] + fTemp157)) - (fConst196 * fRec88[1])));
			fRec87[0] = (fRec88[0] - (fConst53 * ((fConst199 * fRec87[2]) + (fConst198 * fRec87[1]))));
			float fTemp158 = (fConst50 * fRec62[1]);
			fRec62[0] = ((fConst53 * ((((fConst55 * fRec63[0]) + (fConst200 * fRec63[1])) + (fConst55 * fRec63[2])) + (fSlow244 * ((fRec87[0] + (2.0f * fRec87[1])) + fRec87[2])))) - (((fSlow249 * fRec62[2]) + fTemp158) / fSlow250));
			float fTemp159 = (fConst48 * fRec61[1]);
			fRec61[0] = ((((fTemp158 + (fRec62[0] * fSlow252)) + (fRec62[2] * fSlow253)) / fSlow250) - ((fTemp159 + (fRec61[2] * fSlow258)) / fSlow259));
			float fTemp160 = (fConst46 * fRec60[1]);
			fRec60[0] = ((((fTemp159 + (fRec61[0] * fSlow261)) + (fRec61[2] * fSlow262)) / fSlow259) - ((fTemp160 + (fRec60[2] * fSlow267)) / fSlow268));
			output0[i] = FAUSTFLOAT((fSlow0 * ((iSlow1?(fSlow242 * (((fTemp160 + (fRec60[0] * fSlow270)) + (fRec60[2] * fSlow271)) / fSlow268)):fTemp144) * fSlow281)));
			fVec0[1] = fVec0[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec16[1] = fRec16[0];
			fVec1[1] = fVec1[0];
			fRec15[1] = fRec15[0];
			fVec2[1] = fVec2[0];
			fRec14[1] = fRec14[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec13[1] = fRec13[0];
			fVec3[1] = fVec3[0];
			fRec12[1] = fRec12[0];
			fVec4[1] = fVec4[0];
			fRec11[1] = fRec11[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec10[1] = fRec10[0];
			fVec5[1] = fVec5[0];
			fRec9[1] = fRec9[0];
			fVec6[1] = fVec6[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fRec31[1] = fRec31[0];
			fVec7[1] = fVec7[0];
			fRec30[1] = fRec30[0];
			fVec8[1] = fVec8[0];
			fRec29[1] = fRec29[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec38[1] = fRec38[0];
			fRec28[1] = fRec28[0];
			fVec9[1] = fVec9[0];
			fRec27[1] = fRec27[0];
			fVec10[1] = fVec10[0];
			fRec44[1] = fRec44[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			fRec47[1] = fRec47[0];
			fRec43[1] = fRec43[0];
			fVec11[1] = fVec11[0];
			fRec42[1] = fRec42[0];
			fVec12[1] = fVec12[0];
			fRec41[1] = fRec41[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec50[1] = fRec50[0];
			fRec40[1] = fRec40[0];
			fVec13[1] = fVec13[0];
			fRec39[1] = fRec39[0];
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
			fRec54[1] = fRec54[0];
			fRec53[1] = fRec53[0];
			fRec55[1] = fRec55[0];
			fRec1[1] = fRec1[0];
			fRec56[1] = fRec56[0];
			fRec57[1] = fRec57[0];
			fRec58[1] = fRec58[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			fRec59[1] = fRec59[0];
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
