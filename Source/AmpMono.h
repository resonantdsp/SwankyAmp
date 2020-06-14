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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry6;
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
	float fVec0[2];
	float fRec9[2];
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	float fRec11[2];
	float fRec10[2];
	FAUSTFLOAT fEntry29;
	float fConst6;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fRec12[2];
	FAUSTFLOAT fEntry32;
	float fRec13[2];
	FAUSTFLOAT fEntry33;
	float fVec1[2];
	float fRec8[2];
	float fRec15[2];
	float fRec14[2];
	float fRec16[2];
	float fRec7[2];
	float fVec2[2];
	float fRec6[2];
	float fRec18[2];
	float fRec17[2];
	float fRec19[2];
	float fRec5[2];
	float fVec3[2];
	float fRec22[2];
	float fRec24[2];
	float fRec23[2];
	float fRec25[2];
	float fRec21[2];
	float fVec4[2];
	float fRec20[2];
	float fRec27[2];
	float fRec26[2];
	float fRec29[2];
	float fRec28[2];
	float fVec5[2];
	float fRec4[2];
	float fRec30[2];
	float fVec6[2];
	float fConst7;
	float fConst8;
	float fRec3[2];
	float fConst9;
	float fConst10;
	FAUSTFLOAT fEntry34;
	float fConst11;
	float fConst12;
	float fRec2[3];
	float fVec7[2];
	float fRec1[2];
	float fRec31[2];
	FAUSTFLOAT fEntry35;
	float fVec8[2];
	float fRec0[2];
	FAUSTFLOAT fEntry36;
	FAUSTFLOAT fEntry37;
	float fRec32[2];
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	float fRec33[2];
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	float fRec34[2];
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	float fRec35[2];
	FAUSTFLOAT fEntry48;
	float fRec36[2];
	float fRec37[2];
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
	float fRec60[3];
	float fConst113;
	float fConst114;
	float fRec59[3];
	float fVec9[2];
	float fRec58[2];
	float fConst115;
	float fConst116;
	float fRec57[3];
	float fVec10[2];
	float fConst117;
	float fRec56[2];
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fRec55[3];
	float fConst122;
	float fRec54[3];
	float fConst123;
	float fRec53[3];
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fRec64[2];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fConst128;
	float fConst129;
	float fRec52[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec51[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fRec50[3];
	float fConst136;
	float fConst137;
	float fRec49[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec48[3];
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec47[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec46[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec45[3];
	float fConst153;
	float fConst154;
	float fRec44[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec43[3];
	float fConst160;
	float fVec11[2];
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec42[2];
	float fConst164;
	float fConst165;
	float fRec41[3];
	float fConst166;
	FAUSTFLOAT fEntry50;
	float fConst167;
	float fRec66[2];
	float fRec65[3];
	float fConst168;
	float fConst169;
	float fRec40[3];
	float fConst170;
	float fConst171;
	float fRec39[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec38[3];

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
		fConst11 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst12 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
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
		fConst29 = (8796.45898f / fConst24);
		fConst30 = (((fConst23 - fConst29) / fConst22) + 1.0f);
		fConst31 = (37699.1133f / fConst0);
		fConst32 = std::tan(fConst31);
		fConst33 = (1.0f / fConst32);
		fConst34 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst35 = (24836.4707f / fConst34);
		fConst36 = (1.0f / (((fConst33 + fConst35) / fConst32) + 1.0f));
		fConst37 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst32))));
		fConst38 = std::tan((21362.8301f / fConst0));
		fConst39 = (1.0f / fConst38);
		fConst40 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst41 = (19869.1758f / fConst40);
		fConst42 = (1.0f / (((fConst39 + fConst41) / fConst38) + 1.0f));
		fConst43 = (628.318542f / fConst40);
		fConst44 = (((fConst39 + fConst43) / fConst38) + 1.0f);
		fConst45 = std::tan((11938.0518f / fConst0));
		fConst46 = (1.0f / fConst45);
		fConst47 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst48 = (4701.22607f / fConst47);
		fConst49 = (1.0f / (((fConst46 + fConst48) / fConst45) + 1.0f));
		fConst50 = (2356.19458f / fConst47);
		fConst51 = (((fConst46 - fConst50) / fConst45) + 1.0f);
		fConst52 = std::tan((9581.85742f / fConst0));
		fConst53 = (1.0f / fConst52);
		fConst54 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst55 = (2921.88965f / fConst54);
		fConst56 = (1.0f / (((fConst53 + fConst55) / fConst52) + 1.0f));
		fConst57 = (1036.72558f / fConst54);
		fConst58 = (((fConst53 - fConst57) / fConst52) + 1.0f);
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
		fConst78 = (((fConst73 - fConst77) / fConst72) + 1.0f);
		fConst79 = std::tan((2010.61926f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst82 = (439.822968f / fConst81);
		fConst83 = (1.0f / (((fConst80 + fConst82) / fConst79) + 1.0f));
		fConst84 = (1390.84241f / fConst81);
		fConst85 = (((fConst80 - fConst84) / fConst79) + 1.0f);
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
		fConst111 = (((fConst106 + -1.84775901f) / fConst105) + 1.0f);
		fConst112 = (2.0f * (1.0f - fConst109));
		fConst113 = (0.0f - (2.0f / fConst108));
		fConst114 = (((fConst106 + -0.765366852f) / fConst105) + 1.0f);
		fConst115 = (((fConst101 + -1.0f) / fConst100) + 1.0f);
		fConst116 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst100))));
		fConst117 = (1.0f - fConst94);
		fConst118 = (((fConst94 + -1.8019377f) / fConst93) + 1.0f);
		fConst119 = AmpMono_faustpower2_f(fConst93);
		fConst120 = (1.0f / fConst119);
		fConst121 = (2.0f * (1.0f - fConst120));
		fConst122 = (((fConst94 + -1.24697959f) / fConst93) + 1.0f);
		fConst123 = (((fConst94 + -0.445041865f) / fConst93) + 1.0f);
		fConst124 = (0.0f - (2.0f / fConst119));
		fConst125 = (1.0f / (fConst93 * fConst98));
		fConst126 = (0.0f - fConst125);
		fConst127 = (fConst117 / fConst98);
		fConst128 = (((fConst87 - fConst89) / fConst86) + 1.0f);
		fConst129 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst86))));
		fConst130 = (((fConst87 + fConst91) / fConst86) + 1.0f);
		fConst131 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst79))));
		fConst132 = (((fConst80 - fConst82) / fConst79) + 1.0f);
		fConst133 = (((fConst80 + fConst84) / fConst79) + 1.0f);
		fConst134 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst72))));
		fConst135 = (((fConst73 - fConst75) / fConst72) + 1.0f);
		fConst136 = (((fConst73 + fConst77) / fConst72) + 1.0f);
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
		fConst147 = (((fConst53 + fConst57) / fConst52) + 1.0f);
		fConst148 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst45))));
		fConst149 = (((fConst46 - fConst48) / fConst45) + 1.0f);
		fConst150 = (((fConst46 + fConst50) / fConst45) + 1.0f);
		fConst151 = (((fConst39 - fConst41) / fConst38) + 1.0f);
		fConst152 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst38))));
		fConst153 = (((fConst39 - fConst43) / fConst38) + 1.0f);
		fConst154 = (((fConst33 - fConst35) / fConst32) + 1.0f);
		fConst155 = (785.398193f / fConst34);
		fConst156 = (((fConst33 + fConst155) / fConst32) + 1.0f);
		fConst157 = (((fConst33 - fConst155) / fConst32) + 1.0f);
		fConst158 = (((fConst23 - fConst25) / fConst22) + 1.0f);
		fConst159 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst22))));
		fConst160 = (((fConst23 + fConst29) / fConst22) + 1.0f);
		fConst161 = (0.0f - fConst28);
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
			fRec13[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec8[l7] = 0.0f;

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
			fRec7[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec6[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec18[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec17[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec19[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec5[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec22[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec24[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec23[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec25[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec21[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec20[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec27[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec26[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec28[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec4[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec30[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec6[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec3[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec2[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec7[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec1[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec31[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec8[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec0[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec32[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec33[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec34[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec35[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec36[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec37[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec60[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec59[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fVec9[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec58[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec57[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec10[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec56[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec55[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec54[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec53[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec64[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec63[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec62[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec61[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec52[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec51[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec50[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec49[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec48[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec47[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec46[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec45[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec44[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec43[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
			fVec11[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fRec42[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec41[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
			fRec66[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec65[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec40[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec39[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec38[l78] = 0.0f;

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

	void set_cab_brightness(FAUSTFLOAT value) { fEntry50 = value; }
	void set_cab_distance(FAUSTFLOAT value) { fEntry49 = value; }
	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry23 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry24 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry39 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry35 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry37 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry40 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry38 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry36 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry6 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry3 = value + 2.438393e-02f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry4 = value + 1.314022e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry44 = value + 1.143102e-01f; }
	void set_tetrode_plate_comp_level(FAUSTFLOAT value) { fEntry46 = value + -1.456958e-01f; }
	void set_tetrode_plate_comp_ratio(FAUSTFLOAT value) { fEntry47 = value + -4.890451e+00f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry45 = value + 1.001772e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry48 = value + 8.671871e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry41 = value + 1.772658e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry43 = value + 5.447352e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry42 = value + -2.144346e-01f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry5 = value + 5.277323e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry19 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry18 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry27 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry28 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry25 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry26 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry20 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry16 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry21 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry17 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry22 = value + -1.772999e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry12 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry14 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry33 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry32 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry13 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry15 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry29 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry31 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry30 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00f; }
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
		set_tetrode_plate_comp_level(0.0f);
		set_tetrode_plate_comp_ratio(0.0f);
		set_tetrode_plate_comp_tau(0.0f);
		set_tetrode_plate_cross_corner(0.0f);
		set_tetrode_plate_drift_depth(0.0f);
		set_tetrode_plate_drift_level(0.0f);
		set_tetrode_plate_drift_tau(0.0f);
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
		float fSlow4 = (20.0f * (float(fEntry3) + 1.0f));
		float fSlow5 = std::exp(((3.45387769f * (float(fEntry4) + 1.0f)) + -2.30258512f));
		float fSlow6 = std::exp(((4.60517025f * (float(fEntry5) + 1.0f)) + -4.60517025f));
		float fSlow7 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry6) + 1.0f)) + -2.30258512f))));
		float fSlow8 = (1.0f / fSlow7);
		float fSlow9 = (fSlow8 + 1.0f);
		float fSlow10 = (0.0f - (1.0f / (fSlow7 * fSlow9)));
		float fSlow11 = (float(fEntry7) + 1.0f);
		float fSlow12 = (fSlow2 * std::exp((3.45387769f * fSlow11)));
		float fSlow13 = float(fEntry8);
		int iSlow14 = (fSlow13 < 0.0f);
		float fSlow15 = std::tan((fConst1 * ((iSlow14?(1500.0f * fSlow13):0.0f) + 2000.0f)));
		float fSlow16 = (1.0f / fSlow15);
		float fSlow17 = (1.0f - fSlow16);
		float fSlow18 = float(fEntry9);
		float fSlow19 = (fSlow18 + 1.0f);
		float fSlow20 = (1.0f - (0.5f * fSlow19));
		float fSlow21 = std::tan((fConst1 * ((25.0f * fSlow19) + (400.0f * fSlow20))));
		float fSlow22 = (1.0f / fSlow21);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (0.0f - (1.0f / (fSlow21 * fSlow23)));
		float fSlow25 = float(fEntry10);
		float fSlow26 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow25) + -3.0f));
		float fSlow27 = (1.0f - (0.5f * fSlow26));
		float fSlow28 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow25) + -1.0f));
		float fSlow29 = ((float(fEntry11) + 1.0f) + 1.0f);
		float fSlow30 = (fSlow28 / fSlow29);
		float fSlow31 = std::exp(((2.30258512f * (float(fEntry12) + 1.0f)) + -2.30258512f));
		float fSlow32 = std::exp(((3.45387769f * (float(fEntry13) + 1.0f)) + -6.90775537f));
		float fSlow33 = (1.0f / ((fConst0 * fSlow32) + 1.0f));
		float fSlow34 = (100.0f * (1.0f - (float(fEntry14) + 1.0f)));
		float fSlow35 = (0.0f - fSlow34);
		float fSlow36 = std::exp(((4.60517025f * (float(fEntry15) + 1.0f)) + -4.60517025f));
		float fSlow37 = (1.0f - (float(fEntry16) + 1.0f));
		float fSlow38 = (1.0f - (float(fEntry17) + 1.0f));
		float fSlow39 = (fSlow36 + (100.0f * (fSlow37 - fSlow38)));
		float fSlow40 = (float(fEntry18) + 1.0f);
		float fSlow41 = (fSlow40 - (float(fEntry19) + 1.0f));
		float fSlow42 = (2.5f * fSlow41);
		float fSlow43 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry20) + 1.0f)) + -2.30258512f))));
		float fSlow44 = (1.0f / fSlow43);
		float fSlow45 = (fSlow44 + 1.0f);
		float fSlow46 = (0.0f - (1.0f / (fSlow45 * fSlow43)));
		float fSlow47 = (0.294117659f / fSlow36);
		float fSlow48 = std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -2.30258512f));
		float fSlow49 = (0.294117659f / fSlow48);
		float fSlow50 = (0.5f * (fSlow29 / fSlow2));
		float fSlow51 = std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f));
		float fSlow52 = (float(fEntry24) + 1.0f);
		float fSlow53 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry23) + 1.0f)))))) * std::exp((3.45387769f * fSlow52)));
		float fSlow54 = (1.0f / fSlow45);
		float fSlow55 = (1.0f - fSlow44);
		float fSlow56 = (fSlow53 / fSlow43);
		float fSlow57 = std::exp(((3.45387769f * (float(fEntry26) + 1.0f)) + -13.8155107f));
		float fSlow58 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry25) + 1.0f)) + -11.5129251f)) * fSlow57)) + 1.0f));
		float fSlow59 = (1.0f - fSlow58);
		float fSlow60 = (1.0f / ((fConst0 * fSlow57) + 1.0f));
		float fSlow61 = (5.0f * (1.0f - (float(fEntry27) + 1.0f)));
		float fSlow62 = (1.0f / ((fConst0 * (fSlow57 * std::exp(((5.75646257f * (float(fEntry28) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow63 = (1.0f - fSlow62);
		float fSlow64 = (0.117647059f / fSlow40);
		float fSlow65 = ((100.0f * fSlow37) + fSlow48);
		float fSlow66 = std::exp(((2.30258512f * (float(fEntry29) + 1.0f)) + -2.30258512f));
		float fSlow67 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry30) + 1.0f)) + -6.90775537f)))));
		float fSlow68 = (1.0f - fSlow67);
		float fSlow69 = (100.0f * (1.0f - (float(fEntry31) + 1.0f)));
		float fSlow70 = (0.0f - fSlow69);
		float fSlow71 = (100.0f * fSlow38);
		float fSlow72 = (1.0f / ((fConst0 * (std::exp((1.15129256f * (float(fEntry32) + 1.0f))) * fSlow32)) + 1.0f));
		float fSlow73 = (1.0f - fSlow72);
		float fSlow74 = (1.0f - (float(fEntry33) + 1.0f));
		float fSlow75 = (100.0f * (fSlow38 - fSlow74));
		float fSlow76 = (0.294117659f / fSlow51);
		float fSlow77 = (100.0f * fSlow74);
		float fSlow78 = (fSlow43 * fSlow2);
		float fSlow79 = (0.5f * (fSlow29 / fSlow78));
		float fSlow80 = (fSlow62 + -1.0f);
		float fSlow81 = (1.0f / fSlow78);
		float fSlow82 = (fSlow72 + -1.0f);
		float fSlow83 = (1.0f - (0.5f * fSlow28));
		float fSlow84 = AmpMono_faustpower2_f((0.5f * fSlow29));
		float fSlow85 = (0.5f * (fSlow26 / fSlow84));
		float fSlow86 = (fSlow84 / fSlow2);
		float fSlow87 = (fSlow84 / fSlow78);
		float fSlow88 = (5.0f * fSlow52);
		int iSlow89 = (fSlow88 < 9.0f);
		int iSlow90 = (fSlow88 < 8.0f);
		int iSlow91 = (fSlow88 < 7.0f);
		int iSlow92 = (fSlow88 < 6.0f);
		int iSlow93 = (fSlow88 < 5.0f);
		int iSlow94 = (fSlow88 < 4.0f);
		int iSlow95 = (fSlow88 < 3.0f);
		int iSlow96 = (fSlow88 < 2.0f);
		int iSlow97 = (fSlow88 < 1.0f);
		float fSlow98 = std::pow(10.0f, (0.0500000007f * (iSlow89?(iSlow90?(iSlow91?(iSlow92?(iSlow93?(iSlow94?(iSlow95?(iSlow96?(iSlow97?((fSlow88 < 0.0f)?0.0324000008f:(iSlow97?(0.0324000008f - (29.9619999f * fSlow52)):-5.96000004f)):(iSlow96?(-5.96000004f - (5.94000006f * (fSlow88 + -1.0f))):-11.8999996f)):(iSlow95?(-11.8999996f - (5.9000001f * (fSlow88 + -2.0f))):-17.7999992f)):(iSlow94?(-17.7999992f - (5.80000019f * (fSlow88 + -3.0f))):-23.6000004f)):(iSlow93?(-23.6000004f - (5.19999981f * (fSlow88 + -4.0f))):-28.7999992f)):(iSlow92?(-28.7999992f - (3.0999999f * (0.0f - (5.0f * (1.0f - fSlow52))))):-31.8999996f)):(iSlow91?(-31.8999996f - (1.10000002f * (fSlow88 + -6.0f))):-33.0f)):(iSlow90?((0.200000003f * (fSlow88 + -7.0f)) + -33.0f):-32.7999992f)):(iSlow89?((0.400000006f * (fSlow88 + -8.0f)) + -32.7999992f):-32.4000015f)):((fSlow88 < 10.0f)?((0.200000003f * (fSlow88 + -9.0f)) + -32.4000015f):-32.2000008f))));
		float fSlow99 = (1.0f / fSlow23);
		float fSlow100 = (1.0f - fSlow22);
		float fSlow101 = (1.0f / (fSlow21 * fSlow2));
		float fSlow102 = std::pow(10.0f, (0.0500000007f * (fSlow18 * ((18.0f * fSlow20) + (4.5f * fSlow19)))));
		float fSlow103 = float(fEntry34);
		float fSlow104 = ((10.0f * fSlow103) + -14.0f);
		int iSlow105 = (fSlow104 > 0.0f);
		float fSlow106 = ((fSlow103 * ((fSlow18 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow107 = ((fConst11 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow104)))) * fSlow106);
		float fSlow108 = (fConst11 * fSlow106);
		float fSlow109 = (iSlow105?fSlow108:fSlow107);
		float fSlow110 = ((fConst10 * (fConst10 - fSlow109)) + 1.0f);
		float fSlow111 = ((fConst10 * (fConst10 + fSlow109)) + 1.0f);
		float fSlow112 = (iSlow105?fSlow107:fSlow108);
		float fSlow113 = ((fConst10 * (fConst10 + fSlow112)) + 1.0f);
		float fSlow114 = ((fConst10 * (fConst10 - fSlow112)) + 1.0f);
		float fSlow115 = (fSlow16 + 1.0f);
		float fSlow116 = (0.0f - (1.0f / (fSlow115 * fSlow15)));
		float fSlow117 = (fSlow15 * fSlow111);
		float fSlow118 = std::pow(10.0f, ((0.0500000007f * fSlow13) * (iSlow14?18.0f:9.0f)));
		float fSlow119 = (250.0f * (float(fEntry35) + 1.0f));
		float fSlow120 = (1.0f / fSlow9);
		float fSlow121 = (1.0f - fSlow8);
		float fSlow122 = std::exp((0.0f - (fConst6 / std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -9.2103405f)))));
		float fSlow123 = (1.0f - fSlow122);
		float fSlow124 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow125 = std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -9.2103405f));
		float fSlow126 = (1.0f / ((fConst0 * fSlow125) + 1.0f));
		float fSlow127 = (100.0f * (1.0f - (float(fEntry39) + 1.0f)));
		float fSlow128 = ((1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -4.60517025f)) * fSlow125)) + 1.0f)) + -1.0f);
		float fSlow129 = std::exp(((2.30258512f * (float(fEntry41) + 1.0f)) + -2.30258512f));
		float fSlow130 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry42) + 1.0f)) + -6.90775537f)))));
		float fSlow131 = (1.0f - fSlow130);
		float fSlow132 = std::exp((0.0f - (10.0f * (1.0f - (float(fEntry43) + 1.0f)))));
		float fSlow133 = std::exp(((2.30258512f * (float(fEntry44) + 1.0f)) + -2.30258512f));
		float fSlow134 = std::exp(((3.45387769f * (float(fEntry45) + 1.0f)) + -6.90775537f));
		float fSlow135 = (1.0f / ((fConst0 * fSlow134) + 1.0f));
		float fSlow136 = (100.0f * (1.0f - (float(fEntry46) + 1.0f)));
		float fSlow137 = (0.0f - fSlow136);
		float fSlow138 = (1.0f - (1.0f / ((fConst0 * (fSlow134 * std::exp((1.15129256f * (float(fEntry47) + 1.0f))))) + 1.0f)));
		float fSlow139 = (0.294117659f / fSlow5);
		float fSlow140 = std::exp(((3.45387769f * (float(fEntry48) + 1.0f)) + -2.30258512f));
		float fSlow141 = (0.294117659f / fSlow140);
		float fSlow142 = (5.0f * fSlow11);
		int iSlow143 = (fSlow142 < 9.0f);
		int iSlow144 = (fSlow142 < 8.0f);
		int iSlow145 = (fSlow142 < 7.0f);
		int iSlow146 = (fSlow142 < 6.0f);
		int iSlow147 = (fSlow142 < 5.0f);
		int iSlow148 = (fSlow142 < 4.0f);
		int iSlow149 = (fSlow142 < 3.0f);
		int iSlow150 = (fSlow142 < 2.0f);
		int iSlow151 = (fSlow142 < 1.0f);
		float fSlow152 = std::pow(10.0f, (0.0500000007f * (iSlow143?(iSlow144?(iSlow145?(iSlow146?(iSlow147?(iSlow148?(iSlow149?(iSlow150?(iSlow151?((fSlow142 < 0.0f)?-0.398000002f:(iSlow151?(-0.398000002f - (29.9099998f * fSlow11)):-6.38000011f)):(iSlow150?(-6.38000011f - (5.92000008f * (fSlow142 + -1.0f))):-12.3000002f)):(iSlow149?(-12.3000002f - (5.9000001f * (fSlow142 + -2.0f))):-18.2000008f)):(iSlow148?(-18.2000008f - (5.5999999f * (fSlow142 + -3.0f))):-23.7999992f)):(iSlow147?(-23.7999992f - (4.4000001f * (fSlow142 + -4.0f))):-28.2000008f)):(iSlow146?(-28.2000008f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow11))))):-30.3999996f)):(iSlow145?(-30.3999996f - (0.400000006f * (fSlow142 + -6.0f))):-30.7999992f)):(iSlow144?((0.300000012f * (fSlow142 + -7.0f)) + -30.7999992f):-30.5f)):(iSlow143?((0.600000024f * (fSlow142 + -8.0f)) + -30.5f):-29.8999996f)):((fSlow142 < 10.0f)?((1.20000005f * (fSlow142 + -9.0f)) + -29.8999996f):-28.7000008f))));
		float fSlow153 = float(fEntry49);
		float fSlow154 = (5.62341309f * std::pow(10.0f, (0.100000001f * fSlow153)));
		float fSlow155 = float(fEntry50);
		float fSlow156 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow155))));
		float fSlow157 = (15.0f * fSlow155);
		int iSlow158 = (fSlow157 > 0.0f);
		float fSlow159 = (fConst169 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow157))));
		float fSlow160 = (iSlow158?fConst169:fSlow159);
		float fSlow161 = ((fConst168 * (fConst168 - fSlow160)) + 1.0f);
		float fSlow162 = ((fConst168 * (fConst168 + fSlow160)) + 1.0f);
		float fSlow163 = (iSlow158?fSlow159:fConst169);
		float fSlow164 = ((fConst168 * (fConst168 + fSlow163)) + 1.0f);
		float fSlow165 = ((fConst168 * (fConst168 - fSlow163)) + 1.0f);
		float fSlow166 = (0.0f - (10.0f * fSlow153));
		int iSlow167 = (fSlow166 > 0.0f);
		float fSlow168 = (fConst171 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow166))));
		float fSlow169 = (iSlow167?fConst171:fSlow168);
		float fSlow170 = ((fConst170 * (fConst170 - fSlow169)) + 1.0f);
		float fSlow171 = ((fConst170 * (fConst170 + fSlow169)) + 1.0f);
		float fSlow172 = (iSlow167?fSlow168:fConst171);
		float fSlow173 = ((fConst170 * (fConst170 + fSlow172)) + 1.0f);
		float fSlow174 = ((fConst170 * (fConst170 - fSlow172)) + 1.0f);
		float fSlow175 = (0.0f - (17.0f * fSlow153));
		int iSlow176 = (fSlow175 > 0.0f);
		float fSlow177 = (fConst174 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow175))));
		float fSlow178 = (iSlow176?fConst174:fSlow177);
		float fSlow179 = ((fConst173 * (fConst173 - fSlow178)) + 1.0f);
		float fSlow180 = ((fConst173 * (fConst173 + fSlow178)) + 1.0f);
		float fSlow181 = (iSlow176?fSlow177:fConst174);
		float fSlow182 = ((fConst173 * (fConst173 - fSlow181)) + 1.0f);
		float fSlow183 = ((fConst173 * (fConst173 + fSlow181)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow53 * fTemp0);
			fRec9[0] = ((fSlow46 * fVec0[1]) - (fSlow54 * ((fSlow55 * fRec9[1]) - (fSlow56 * fTemp0))));
			fRec11[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec9[0])) - fRec11[1]))) + (fSlow63 * fRec11[1]));
			fRec10[0] = ((fSlow59 * fRec10[1]) + (fSlow58 * fRec11[0]));
			float fTemp1 = (fSlow42 + (fRec9[0] - fRec10[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * ((fSlow40 * (fTemp3 * (std::fabs(fTemp3) + -2.0f))) - fSlow41)))) - fSlow65);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp4) + (fSlow48 * (((fTemp5 * (std::fabs((fTemp5 * fTemp6)) + -2.0f)) * fTemp6) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow47 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (std::fabs(fTemp8) + -2.0f);
			float fTemp10 = ((fSlow36 * ((((std::fabs((fTemp8 * fTemp9)) + -2.0f) * fTemp8) * fTemp9) + 1.0f)) + std::max<float>(0.0f, fTemp7));
			fRec12[0] = ((fSlow67 * fRec12[1]) + (fSlow68 * (fSlow69 + std::max<float>(fSlow70, (fTemp10 - fSlow71)))));
			float fTemp11 = (fSlow66 * fRec12[0]);
			fRec13[0] = ((fSlow33 * std::max<float>(0.0f, (fSlow34 + (std::max<float>(fSlow35, ((fTemp10 - fTemp11) - fSlow71)) - fRec13[1])))) + (fSlow73 * fRec13[1]));
			float fTemp12 = (fSlow31 * fRec13[0]);
			float fTemp13 = (fSlow51 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow75));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (std::fabs(fTemp14) + -2.0f);
			float fTemp16 = (((std::min<float>(0.0f, fTemp13) + fTemp12) - (fSlow51 * (1.0f - ((fTemp14 * (std::fabs((fTemp14 * fTemp15)) + -2.0f)) * fTemp15)))) - fSlow77);
			fVec1[0] = (fSlow50 * fTemp16);
			fRec8[0] = ((fSlow46 * fVec1[1]) + (fSlow54 * ((fSlow79 * fTemp16) - (fSlow55 * fRec8[1]))));
			fRec15[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec8[0])) - fRec15[1]))) - (fSlow80 * fRec15[1]));
			fRec14[0] = ((fSlow59 * fRec14[1]) + (fSlow58 * fRec15[0]));
			float fTemp17 = (fSlow42 + (fRec8[0] - fRec14[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow41 - (fSlow40 * (((std::fabs((fTemp18 * fTemp19)) + -2.0f) * fTemp18) * fTemp19)))))) - fSlow65);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow39 + ((fSlow48 * (((fTemp21 * (std::fabs((fTemp21 * fTemp22)) + -2.0f)) * fTemp22) + 1.0f)) + std::max<float>(0.0f, fTemp20))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow47 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (std::fabs(fTemp24) + -2.0f);
			float fTemp26 = ((fSlow36 * ((((std::fabs((fTemp25 * fTemp24)) + -2.0f) * fTemp25) * fTemp24) + 1.0f)) + std::max<float>(0.0f, fTemp23));
			fRec16[0] = ((fSlow67 * fRec16[1]) + (fSlow68 * (fSlow69 + std::max<float>(fSlow70, (fTemp26 - fSlow71)))));
			float fTemp27 = (fSlow66 * fRec16[0]);
			fRec7[0] = ((fSlow33 * std::max<float>(0.0f, (fSlow34 + (std::max<float>(fSlow35, ((fTemp26 - fTemp27) - fSlow71)) - fRec7[1])))) + (fSlow73 * fRec7[1]));
			float fTemp28 = (fSlow31 * fRec7[0]);
			float fTemp29 = (fSlow51 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow75));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = ((std::fabs(fTemp30) + -2.0f) * fTemp30);
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow51 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow77);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec6[0] = ((fSlow46 * fVec2[1]) - (fSlow54 * ((fSlow55 * fRec6[1]) - (fSlow81 * fTemp32))));
			fRec18[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec6[0])) - fRec18[1]))) + (fSlow63 * fRec18[1]));
			fRec17[0] = ((fSlow58 * fRec18[0]) + (fSlow59 * fRec17[1]));
			float fTemp33 = (fSlow42 + (fRec6[0] - fRec17[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow41 - (fSlow40 * ((fTemp34 * (std::fabs((fTemp34 * fTemp35)) + -2.0f)) * fTemp35)))))) - fSlow65);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (fTemp37 * (std::fabs(fTemp37) + -2.0f));
			float fTemp39 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp36) + (fSlow48 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow47 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (fTemp40 * (std::fabs(fTemp40) + -2.0f));
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow36 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)));
			fRec19[0] = ((fSlow67 * fRec19[1]) + (fSlow68 * (fSlow69 + std::max<float>(fSlow70, (fTemp42 - fSlow71)))));
			float fTemp43 = (fSlow66 * fRec19[0]);
			fRec5[0] = ((fSlow33 * std::max<float>(0.0f, (fSlow34 + (std::max<float>(fSlow35, ((fTemp42 - fTemp43) - fSlow71)) - fRec5[1])))) - (fSlow82 * fRec5[1]));
			float fTemp44 = (fSlow31 * fRec5[0]);
			float fTemp45 = (fSlow51 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow75));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = ((fSlow30 * (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow51 * (1.0f - ((fTemp46 * (std::fabs((fTemp46 * fTemp47)) + -2.0f)) * fTemp47)))) - fSlow77)) + (fSlow83 * fTemp16));
			fVec3[0] = (fSlow86 * fTemp48);
			fRec22[0] = ((fSlow46 * fVec3[1]) - (fSlow54 * ((fSlow55 * fRec22[1]) - (fSlow87 * fTemp48))));
			fRec24[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec22[0])) - fRec24[1]))) - (fSlow80 * fRec24[1]));
			fRec23[0] = ((fSlow59 * fRec23[1]) + (fSlow58 * fRec24[0]));
			float fTemp49 = (fSlow42 + (fRec22[0] - fRec23[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (fTemp50 * (std::fabs(fTemp50) + -2.0f));
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow41 - (fSlow40 * (fTemp51 * (std::fabs(fTemp51) + -2.0f))))))) - fSlow65);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (fTemp53 * (std::fabs(fTemp53) + -2.0f));
			float fTemp55 = (0.0f - (fSlow39 + ((fSlow48 * ((fTemp54 * (std::fabs(fTemp54) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp52))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow47 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow36 * (((fTemp56 * (std::fabs((fTemp56 * fTemp57)) + -2.0f)) * fTemp57) + 1.0f)));
			fRec25[0] = ((fSlow68 * (fSlow69 + std::max<float>(fSlow70, (fTemp58 - fSlow71)))) + (fSlow67 * fRec25[1]));
			float fTemp59 = (fSlow66 * fRec25[0]);
			fRec21[0] = ((fSlow33 * std::max<float>(0.0f, (fSlow34 + (std::max<float>(fSlow35, ((fTemp58 - fTemp59) - fSlow71)) - fRec21[1])))) - (fSlow82 * fRec21[1]));
			float fTemp60 = (fSlow31 * fRec21[0]);
			float fTemp61 = (fSlow51 + ((fTemp58 - (fTemp60 + fTemp59)) - fSlow75));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (std::fabs(fTemp62) + -2.0f);
			float fTemp64 = (((fTemp60 + (fSlow51 * ((((std::fabs((fTemp62 * fTemp63)) + -2.0f) * fTemp62) * fTemp63) + -1.0f))) + std::min<float>(0.0f, fTemp61)) - fSlow77);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec20[0] = ((fSlow46 * fVec4[1]) + (fSlow54 * ((fSlow81 * fTemp64) - (fSlow55 * fRec20[1]))));
			fRec27[0] = ((fSlow63 * fRec27[1]) + (fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec20[0])) - fRec27[1]))));
			fRec26[0] = ((fSlow59 * fRec26[1]) + (fSlow58 * fRec27[0]));
			float fTemp65 = (fSlow42 + (fRec20[0] - fRec26[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow64 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow41 - (fSlow40 * (((std::fabs((fTemp66 * fTemp67)) + -2.0f) * fTemp66) * fTemp67)))))) - fSlow65);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow49 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (fTemp69 * (std::fabs(fTemp69) + -2.0f));
			float fTemp71 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp68) + (fSlow48 * ((fTemp70 * (std::fabs(fTemp70) + -2.0f)) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow47 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (fTemp72 * (std::fabs(fTemp72) + -2.0f));
			float fTemp74 = (std::max<float>(0.0f, fTemp71) + (fSlow36 * ((fTemp73 * (std::fabs(fTemp73) + -2.0f)) + 1.0f)));
			fRec29[0] = ((fSlow67 * fRec29[1]) + (fSlow68 * (fSlow69 + std::max<float>(fSlow70, (fTemp74 - fSlow71)))));
			float fTemp75 = (fSlow66 * fRec29[0]);
			fRec28[0] = ((fSlow33 * std::max<float>(0.0f, (fSlow34 + (std::max<float>(fSlow35, ((fTemp74 - fTemp75) - fSlow71)) - fRec28[1])))) + (fSlow73 * fRec28[1]));
			float fTemp76 = (fSlow31 * fRec28[0]);
			float fTemp77 = (fSlow51 + ((fTemp74 - (fTemp76 + fTemp75)) - fSlow75));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow76 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (fTemp78 * (std::fabs(fTemp78) + -2.0f));
			float fTemp80 = (((fSlow27 * fTemp48) + (fSlow85 * (((std::min<float>(0.0f, fTemp77) + fTemp76) - (fSlow51 * (1.0f - (fTemp79 * (std::fabs(fTemp79) + -2.0f))))) - fSlow77))) * fSlow98);
			float fTemp81 = (fSlow3 * fTemp80);
			fVec5[0] = fTemp81;
			fRec4[0] = ((fSlow24 * fVec5[1]) - (fSlow99 * ((fSlow100 * fRec4[1]) - (fSlow101 * fTemp80))));
			fRec30[0] = (0.0f - (fSlow99 * ((fSlow100 * fRec30[1]) - (fTemp81 + fVec5[1]))));
			float fTemp82 = (fRec4[0] + (fSlow102 * fRec30[0]));
			fVec6[0] = fTemp82;
			fRec3[0] = ((fConst5 * fVec6[1]) - (fConst7 * ((fConst8 * fRec3[1]) - (fConst3 * fTemp82))));
			float fTemp83 = (fConst12 * fRec2[1]);
			fRec2[0] = (fRec3[0] - (((fSlow110 * fRec2[2]) + fTemp83) / fSlow111));
			float fTemp84 = (((fRec2[0] * fSlow113) + fTemp83) + (fRec2[2] * fSlow114));
			float fTemp85 = (fTemp84 / fSlow111);
			fVec7[0] = fTemp85;
			fRec1[0] = (0.0f - (((fSlow17 * fRec1[1]) - (fTemp85 + fVec7[1])) / fSlow115));
			fRec31[0] = ((fSlow116 * fVec7[1]) - (((fRec31[1] * fSlow17) - (fTemp84 / fSlow117)) / fSlow115));
			float fTemp86 = ((fSlow12 * (fRec1[0] + (fRec31[0] * fSlow118))) - fSlow119);
			fVec8[0] = fTemp86;
			fRec0[0] = ((fSlow10 * fVec8[1]) - (fSlow120 * ((fSlow121 * fRec0[1]) - (fSlow8 * fTemp86))));
			fRec32[0] = ((fSlow122 * fRec32[1]) + (fSlow123 * (fRec0[0] - fSlow124)));
			fRec33[0] = ((fSlow126 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow127 + ((fRec0[0] - fRec32[0]) - fSlow124))) - fRec33[1]))) - (fSlow128 * fRec33[1]));
			float fTemp87 = (fSlow6 * ((fRec0[0] - (fRec32[0] + fRec33[0])) - fSlow124));
			fRec34[0] = ((fSlow130 * fRec34[1]) + (fSlow131 * (std::max<float>(fSlow132, fTemp87) - fSlow132)));
			float fTemp88 = (fSlow129 * fRec34[0]);
			fRec35[0] = ((fSlow135 * std::max<float>(0.0f, (fSlow136 + (std::max<float>(fSlow137, (fTemp87 - fTemp88)) - fRec35[1])))) + (fSlow138 * fRec35[1]));
			float fTemp89 = (fSlow133 * (0.0f - fRec35[0]));
			float fTemp90 = (fSlow5 + ((fTemp87 + (-10.0f - (fTemp88 + fTemp89))) - fSlow4));
			float fTemp91 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp90))));
			float fTemp92 = (std::fabs(fTemp91) + -2.0f);
			float fTemp93 = (fSlow4 + (((std::min<float>(0.0f, fTemp90) + fTemp89) + (10.0f - (fSlow5 * (1.0f - (((std::fabs((fTemp91 * fTemp92)) + -2.0f) * fTemp91) * fTemp92))))) - fSlow140));
			fRec36[0] = ((fSlow131 * (std::max<float>(fSlow132, (0.0f - fTemp87)) - fSlow132)) + (fSlow130 * fRec36[1]));
			float fTemp94 = (fTemp87 + (fSlow129 * fRec36[0]));
			fRec37[0] = ((fSlow135 * std::max<float>(0.0f, (fSlow136 + (std::max<float>(fSlow137, (0.0f - fTemp94)) - fRec37[1])))) + (fSlow138 * fRec37[1]));
			float fTemp95 = (fSlow133 * (0.0f - fRec37[0]));
			float fTemp96 = (fSlow5 + ((-10.0f - (fTemp94 + fTemp95)) - fSlow4));
			float fTemp97 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp96))));
			float fTemp98 = (fTemp97 * (std::fabs(fTemp97) + -2.0f));
			float fTemp99 = (fSlow4 + (((std::min<float>(0.0f, fTemp96) + fTemp95) + (10.0f - (fSlow5 * (1.0f - (fTemp98 * (std::fabs(fTemp98) + -2.0f)))))) - fSlow140));
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp99))));
			float fTemp101 = (std::fabs(fTemp100) + -2.0f);
			float fTemp102 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp93))));
			float fTemp103 = (std::fabs(fTemp102) + -2.0f);
			float fTemp104 = (fSlow3 * ((std::max<float>(0.0f, fTemp93) - (std::max<float>(0.0f, fTemp99) + (fSlow140 * ((((fTemp100 * (std::fabs((fTemp100 * fTemp101)) + -2.0f)) * fTemp101) + 1.0f) - ((((std::fabs((fTemp103 * fTemp102)) + -2.0f) * fTemp103) * fTemp102) + 1.0f))))) * fSlow152));
			fRec60[0] = (fTemp104 - (fConst110 * ((fConst111 * fRec60[2]) + (fConst112 * fRec60[1]))));
			fRec59[0] = ((fConst110 * (((fConst109 * fRec60[0]) + (fConst113 * fRec60[1])) + (fConst109 * fRec60[2]))) - (fConst107 * ((fConst112 * fRec59[1]) + (fConst114 * fRec59[2]))));
			float fTemp105 = (((fConst109 * fRec59[0]) + (fConst113 * fRec59[1])) + (fConst109 * fRec59[2]));
			fVec9[0] = fTemp105;
			fRec58[0] = (0.0f - (fConst103 * ((fConst104 * fRec58[1]) - (fConst107 * (fTemp105 + fVec9[1])))));
			fRec57[0] = (fRec58[0] - (fConst102 * ((fConst115 * fRec57[2]) + (fConst116 * fRec57[1]))));
			float fTemp106 = ((fRec57[0] + (2.0f * fRec57[1])) + fRec57[2]);
			fVec10[0] = fTemp106;
			fRec56[0] = (fConst99 * ((fConst102 * (fTemp106 + fVec10[1])) - (fConst117 * fRec56[1])));
			fRec55[0] = (fRec56[0] - (fConst97 * ((fConst118 * fRec55[2]) + (fConst121 * fRec55[1]))));
			fRec54[0] = ((fConst97 * (fRec55[2] + (fRec55[0] + (2.0f * fRec55[1])))) - (fConst96 * ((fConst121 * fRec54[1]) + (fConst122 * fRec54[2]))));
			fRec53[0] = ((fConst96 * ((fRec54[0] + (2.0f * fRec54[1])) + fRec54[2])) - (fConst95 * ((fConst123 * fRec53[2]) + (fConst121 * fRec53[1]))));
			fRec64[0] = ((fConst102 * ((fConst126 * fVec10[1]) + (fConst125 * fTemp106))) - (fConst127 * fRec64[1]));
			fRec63[0] = (fRec64[0] - (fConst97 * ((fConst118 * fRec63[2]) + (fConst121 * fRec63[1]))));
			fRec62[0] = ((fConst97 * (((fConst124 * fRec63[1]) + (fConst120 * fRec63[0])) + (fConst120 * fRec63[2]))) - (fConst96 * ((fConst122 * fRec62[2]) + (fConst121 * fRec62[1]))));
			fRec61[0] = ((fConst96 * ((fConst120 * fRec62[2]) + ((fConst120 * fRec62[0]) + (fConst124 * fRec62[1])))) - (fConst95 * ((fConst121 * fRec61[1]) + (fConst123 * fRec61[2]))));
			float fTemp107 = (fConst129 * fRec52[1]);
			fRec52[0] = ((fConst95 * ((fRec53[2] + (fRec53[0] + (2.0f * fRec53[1]))) + (0.0316227749f * (((fConst120 * fRec61[0]) + (fConst124 * fRec61[1])) + (fConst120 * fRec61[2]))))) - (fConst90 * ((fConst128 * fRec52[2]) + fTemp107)));
			float fTemp108 = (fConst131 * fRec51[1]);
			fRec51[0] = ((fConst90 * ((fConst92 * fRec52[2]) + ((fConst130 * fRec52[0]) + fTemp107))) - (fConst83 * (fTemp108 + (fConst132 * fRec51[2]))));
			float fTemp109 = (fConst134 * fRec50[1]);
			fRec50[0] = ((fConst83 * ((fConst85 * fRec51[2]) + ((fConst133 * fRec51[0]) + fTemp108))) - (fConst76 * (fTemp109 + (fConst135 * fRec50[2]))));
			float fTemp110 = (fConst71 * fRec49[1]);
			fRec49[0] = ((fConst76 * ((fConst78 * fRec50[2]) + (fTemp109 + (fConst136 * fRec50[0])))) - (fConst70 * (fTemp110 + (fConst137 * fRec49[2]))));
			float fTemp111 = (fConst64 * fRec48[1]);
			fRec48[0] = ((fConst70 * ((fTemp110 + (fConst139 * fRec49[0])) + (fConst140 * fRec49[2]))) - (fConst63 * (fTemp111 + (fConst141 * fRec48[2]))));
			float fTemp112 = (fConst146 * fRec47[1]);
			fRec47[0] = ((fConst63 * ((fTemp111 + (fConst143 * fRec48[0])) + (fConst144 * fRec48[2]))) - (fConst56 * ((fConst145 * fRec47[2]) + fTemp112)));
			float fTemp113 = (fConst148 * fRec46[1]);
			fRec46[0] = ((fConst56 * ((fConst58 * fRec47[2]) + (fTemp112 + (fConst147 * fRec47[0])))) - (fConst49 * (fTemp113 + (fConst149 * fRec46[2]))));
			float fTemp114 = (fConst152 * fRec45[1]);
			fRec45[0] = ((fConst49 * ((fConst51 * fRec46[2]) + (fTemp113 + (fConst150 * fRec46[0])))) - (fConst42 * ((fConst151 * fRec45[2]) + fTemp114)));
			float fTemp115 = (fConst37 * fRec44[1]);
			fRec44[0] = ((fConst42 * (((fConst44 * fRec45[0]) + fTemp114) + (fConst153 * fRec45[2]))) - (fConst36 * ((fConst154 * fRec44[2]) + fTemp115)));
			float fTemp116 = (fConst159 * fRec43[1]);
			fRec43[0] = ((fConst36 * ((fTemp115 + (fConst156 * fRec44[0])) + (fConst157 * fRec44[2]))) - (fConst26 * ((fConst158 * fRec43[2]) + fTemp116)));
			float fTemp117 = ((fConst30 * fRec43[2]) + (fTemp116 + (fConst160 * fRec43[0])));
			fVec11[0] = fTemp117;
			fRec42[0] = ((fConst26 * ((fConst28 * fTemp117) + (fConst161 * fVec11[1]))) - (fConst163 * fRec42[1]));
			fRec41[0] = (fRec42[0] - (fConst19 * ((fConst164 * fRec41[1]) + (fConst165 * fRec41[2]))));
			fRec66[0] = (0.0f - (fConst167 * ((fConst162 * fRec66[1]) - (fConst26 * (fTemp117 + fVec11[1])))));
			fRec65[0] = (fRec66[0] - (fConst19 * ((fConst164 * fRec65[1]) + (fConst165 * fRec65[2]))));
			float fTemp118 = (fConst16 * fRec40[1]);
			fRec40[0] = ((fConst19 * ((((fConst21 * fRec41[0]) + (fConst166 * fRec41[1])) + (fConst21 * fRec41[2])) + (fSlow156 * (fRec65[2] + (fRec65[0] + (2.0f * fRec65[1])))))) - ((fTemp118 + (fSlow161 * fRec40[2])) / fSlow162));
			float fTemp119 = (fConst14 * fRec39[1]);
			fRec39[0] = ((((fTemp118 + (fRec40[0] * fSlow164)) + (fRec40[2] * fSlow165)) / fSlow162) - ((fTemp119 + (fSlow170 * fRec39[2])) / fSlow171));
			float fTemp120 = (fConst175 * fRec38[1]);
			fRec38[0] = ((((fTemp119 + (fRec39[0] * fSlow173)) + (fRec39[2] * fSlow174)) / fSlow171) - (((fRec38[2] * fSlow179) + fTemp120) / fSlow180));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow154 * (((fRec38[2] * fSlow182) + (fTemp120 + (fRec38[0] * fSlow183))) / fSlow180)):fTemp104)));
			fVec0[1] = fVec0[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec13[1] = fRec13[0];
			fVec1[1] = fVec1[0];
			fRec8[1] = fRec8[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec16[1] = fRec16[0];
			fRec7[1] = fRec7[0];
			fVec2[1] = fVec2[0];
			fRec6[1] = fRec6[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec5[1] = fRec5[0];
			fVec3[1] = fVec3[0];
			fRec22[1] = fRec22[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec21[1] = fRec21[0];
			fVec4[1] = fVec4[0];
			fRec20[1] = fRec20[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fVec5[1] = fVec5[0];
			fRec4[1] = fRec4[0];
			fRec30[1] = fRec30[0];
			fVec6[1] = fVec6[0];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fVec7[1] = fVec7[0];
			fRec1[1] = fRec1[0];
			fRec31[1] = fRec31[0];
			fVec8[1] = fVec8[0];
			fRec0[1] = fRec0[0];
			fRec32[1] = fRec32[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fVec9[1] = fVec9[0];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fVec10[1] = fVec10[0];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fVec11[1] = fVec11[0];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec66[1] = fRec66[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec38[2] = fRec38[1];
			fRec38[1] = fRec38[0];

		}

	}


};

#endif
