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
	float fConst2;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
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
	float fRec11[2];
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	float fRec13[2];
	float fRec12[2];
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	float fRec14[2];
	float fRec10[2];
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	float fVec1[2];
	float fRec9[2];
	float fRec16[2];
	float fRec15[2];
	float fRec17[2];
	float fRec8[2];
	float fVec2[2];
	float fRec7[2];
	float fRec19[2];
	float fRec18[2];
	float fRec20[2];
	float fRec6[2];
	float fVec3[2];
	float fRec23[2];
	float fRec25[2];
	float fRec24[2];
	float fRec27[2];
	float fRec26[2];
	float fVec4[2];
	float fRec22[2];
	float fRec29[2];
	float fRec28[2];
	float fRec30[2];
	float fRec21[2];
	float fVec5[2];
	float fRec5[2];
	float fRec31[2];
	float fVec6[2];
	float fConst7;
	float fConst8;
	float fRec4[2];
	float fConst9;
	float fConst10;
	FAUSTFLOAT fEntry35;
	float fConst11;
	float fConst12;
	float fRec3[3];
	float fVec7[2];
	float fRec2[2];
	float fRec32[2];
	FAUSTFLOAT fEntry36;
	float fVec8[2];
	float fRec1[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	float fRec33[2];
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	float fRec34[2];
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	float fRec35[2];
	float fRec0[2];
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	float fRec36[2];
	float fRec37[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec38[2];
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
	float fRec61[3];
	float fConst112;
	float fRec60[3];
	float fVec9[2];
	float fRec59[2];
	float fConst113;
	float fConst114;
	float fRec58[3];
	float fVec10[2];
	float fRec57[2];
	float fConst115;
	float fConst116;
	float fConst117;
	float fConst118;
	float fRec56[3];
	float fConst119;
	float fRec55[3];
	float fConst120;
	float fRec54[3];
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fRec65[2];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fConst125;
	float fRec53[3];
	float fConst126;
	float fConst127;
	float fConst128;
	float fConst129;
	float fRec52[3];
	float fConst130;
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec51[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec50[3];
	float fConst138;
	float fConst139;
	float fRec49[3];
	float fConst140;
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec48[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fConst147;
	float fRec47[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec46[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec45[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec44[3];
	float fConst159;
	float fVec11[2];
	float fConst160;
	float fConst161;
	float fRec43[2];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec42[3];
	FAUSTFLOAT fEntry50;
	float fConst165;
	float fRec67[2];
	float fRec66[3];
	float fConst166;
	float fConst167;
	float fRec41[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec40[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec39[3];

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
		fConst13 = std::tan((18849.5566f / fConst0));
		fConst14 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst15 = std::tan((3455.75195f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (1.0f / (((fConst16 + 1.0f) / fConst15) + 1.0f));
		fConst18 = AmpMono_faustpower2_f(fConst15);
		fConst19 = (0.0f - (2.0f / fConst18));
		fConst20 = std::tan((2984.51294f / fConst0));
		fConst21 = (1.0f / fConst20);
		fConst22 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst23 = (27816.8476f / fConst22);
		fConst24 = (1.0f / (((fConst21 + fConst23) / fConst20) + 1.0f));
		fConst25 = (fConst16 + 1.0f);
		fConst26 = (1.0f / (fConst15 * fConst25));
		fConst27 = (0.0f - fConst26);
		fConst28 = (8796.45898f / fConst22);
		fConst29 = (((fConst21 - fConst28) / fConst20) + 1.0f);
		fConst30 = (37699.1133f / fConst0);
		fConst31 = std::tan(fConst30);
		fConst32 = (1.0f / fConst31);
		fConst33 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst34 = (24836.4707f / fConst33);
		fConst35 = (1.0f / (((fConst32 + fConst34) / fConst31) + 1.0f));
		fConst36 = (785.398193f / fConst33);
		fConst37 = (((fConst32 - fConst36) / fConst31) + 1.0f);
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
		fConst50 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst45))));
		fConst51 = std::tan((9581.85742f / fConst0));
		fConst52 = (1.0f / fConst51);
		fConst53 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst54 = (2921.88965f / fConst53);
		fConst55 = (1.0f / (((fConst52 + fConst54) / fConst51) + 1.0f));
		fConst56 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst51))));
		fConst57 = std::tan((5215.04394f / fConst0));
		fConst58 = (1.0f / fConst57);
		fConst59 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst60 = (3713.44482f / fConst59);
		fConst61 = (1.0f / (((fConst58 + fConst60) / fConst57) + 1.0f));
		fConst62 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst57))));
		fConst63 = (3707.07935f / fConst0);
		fConst64 = std::tan(fConst63);
		fConst65 = (1.0f / fConst64);
		fConst66 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst67 = (502.654816f / fConst66);
		fConst68 = (1.0f / (((fConst65 + fConst67) / fConst64) + 1.0f));
		fConst69 = (1416.67383f / fConst66);
		fConst70 = (((fConst65 + fConst69) / fConst64) + 1.0f);
		fConst71 = std::tan((3518.58374f / fConst0));
		fConst72 = (1.0f / fConst71);
		fConst73 = (fConst0 * std::sin((7037.16748f / fConst0)));
		fConst74 = (875.483398f / fConst73);
		fConst75 = (1.0f / (((fConst72 + fConst74) / fConst71) + 1.0f));
		fConst76 = (219.911484f / fConst73);
		fConst77 = (((fConst72 - fConst76) / fConst71) + 1.0f);
		fConst78 = std::tan((2010.61926f / fConst0));
		fConst79 = (1.0f / fConst78);
		fConst80 = (fConst0 * std::sin((4021.23853f / fConst0)));
		fConst81 = (439.822968f / fConst80);
		fConst82 = (1.0f / (((fConst79 + fConst81) / fConst78) + 1.0f));
		fConst83 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst78))));
		fConst84 = std::tan((1853.53967f / fConst0));
		fConst85 = (1.0f / fConst84);
		fConst86 = (fConst0 * std::sin(fConst63));
		fConst87 = (1059.9884f / fConst86);
		fConst88 = (1.0f / (((fConst85 + fConst87) / fConst84) + 1.0f));
		fConst89 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst84))));
		fConst90 = std::tan((17592.918f / fConst0));
		fConst91 = (1.0f / fConst90);
		fConst92 = (1.0f / (((fConst91 + 0.445041865f) / fConst90) + 1.0f));
		fConst93 = (1.0f / (((fConst91 + 1.24697959f) / fConst90) + 1.0f));
		fConst94 = (1.0f / (((fConst91 + 1.8019377f) / fConst90) + 1.0f));
		fConst95 = (fConst91 + 1.0f);
		fConst96 = (1.0f / fConst95);
		fConst97 = (1.0f - fConst91);
		fConst98 = std::tan((34557.5195f / fConst0));
		fConst99 = (1.0f / fConst98);
		fConst100 = (1.0f / (((fConst99 + 1.0f) / fConst98) + 1.0f));
		fConst101 = (1.0f / (fConst99 + 1.0f));
		fConst102 = (1.0f - fConst99);
		fConst103 = std::tan((345.575195f / fConst0));
		fConst104 = (1.0f / fConst103);
		fConst105 = (1.0f / (((fConst104 + 0.765366852f) / fConst103) + 1.0f));
		fConst106 = AmpMono_faustpower2_f(fConst103);
		fConst107 = (1.0f / fConst106);
		fConst108 = (1.0f / (((fConst104 + 1.84775901f) / fConst103) + 1.0f));
		fConst109 = (0.0f - (2.0f / fConst106));
		fConst110 = (((fConst104 + -1.84775901f) / fConst103) + 1.0f);
		fConst111 = (2.0f * (1.0f - fConst107));
		fConst112 = (((fConst104 + -0.765366852f) / fConst103) + 1.0f);
		fConst113 = (((fConst99 + -1.0f) / fConst98) + 1.0f);
		fConst114 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst98))));
		fConst115 = (((fConst91 + -1.8019377f) / fConst90) + 1.0f);
		fConst116 = AmpMono_faustpower2_f(fConst90);
		fConst117 = (1.0f / fConst116);
		fConst118 = (2.0f * (1.0f - fConst117));
		fConst119 = (((fConst91 + -1.24697959f) / fConst90) + 1.0f);
		fConst120 = (((fConst91 + -0.445041865f) / fConst90) + 1.0f);
		fConst121 = (0.0f - (2.0f / fConst116));
		fConst122 = (1.0f / (fConst90 * fConst95));
		fConst123 = (0.0f - fConst122);
		fConst124 = (fConst97 / fConst95);
		fConst125 = (((fConst85 - fConst87) / fConst84) + 1.0f);
		fConst126 = (188.49556f / fConst86);
		fConst127 = (((fConst85 + fConst126) / fConst84) + 1.0f);
		fConst128 = (((fConst85 - fConst126) / fConst84) + 1.0f);
		fConst129 = (((fConst79 - fConst81) / fConst78) + 1.0f);
		fConst130 = (1390.84241f / fConst80);
		fConst131 = (((fConst79 + fConst130) / fConst78) + 1.0f);
		fConst132 = (((fConst79 - fConst130) / fConst78) + 1.0f);
		fConst133 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst71))));
		fConst134 = (((fConst72 - fConst74) / fConst71) + 1.0f);
		fConst135 = (((fConst72 + fConst76) / fConst71) + 1.0f);
		fConst136 = (((fConst65 - fConst67) / fConst64) + 1.0f);
		fConst137 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst64))));
		fConst138 = (((fConst65 - fConst69) / fConst64) + 1.0f);
		fConst139 = (((fConst58 - fConst60) / fConst57) + 1.0f);
		fConst140 = (2481.85815f / fConst59);
		fConst141 = (((fConst58 + fConst140) / fConst57) + 1.0f);
		fConst142 = (((fConst58 - fConst140) / fConst57) + 1.0f);
		fConst143 = (((fConst52 - fConst54) / fConst51) + 1.0f);
		fConst144 = (1036.72558f / fConst53);
		fConst145 = (((fConst52 + fConst144) / fConst51) + 1.0f);
		fConst146 = (((fConst52 - fConst144) / fConst51) + 1.0f);
		fConst147 = (((fConst46 - fConst48) / fConst45) + 1.0f);
		fConst148 = (2356.19458f / fConst47);
		fConst149 = (((fConst46 + fConst148) / fConst45) + 1.0f);
		fConst150 = (((fConst46 - fConst148) / fConst45) + 1.0f);
		fConst151 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst38))));
		fConst152 = (((fConst39 - fConst41) / fConst38) + 1.0f);
		fConst153 = (((fConst39 - fConst43) / fConst38) + 1.0f);
		fConst154 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst31))));
		fConst155 = (((fConst32 - fConst34) / fConst31) + 1.0f);
		fConst156 = (((fConst32 + fConst36) / fConst31) + 1.0f);
		fConst157 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst20))));
		fConst158 = (((fConst21 - fConst23) / fConst20) + 1.0f);
		fConst159 = (((fConst21 + fConst28) / fConst20) + 1.0f);
		fConst160 = (1.0f - fConst16);
		fConst161 = (fConst160 / fConst25);
		fConst162 = (((fConst16 + -1.0f) / fConst15) + 1.0f);
		fConst163 = (1.0f / fConst18);
		fConst164 = (2.0f * (1.0f - fConst163));
		fConst165 = (1.0f / fConst25);
		fConst166 = (1.0f / fConst13);
		fConst167 = (3141.59277f / (fConst0 * std::sin(fConst30)));
		fConst168 = std::tan((219.911484f / fConst0));
		fConst169 = (1.0f / fConst168);
		fConst170 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst171 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst168))));
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
			fRec11[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec13[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec12[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec14[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec10[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec9[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec16[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec15[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec17[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec8[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec7[l13] = 0.0f;

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
			fRec6[l17] = 0.0f;

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
			fRec27[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec26[l23] = 0.0f;

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
			fRec21[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fVec5[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec5[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec31[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fVec6[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec4[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec3[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec7[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec2[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec32[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec8[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec1[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec33[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec34[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec35[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec0[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec36[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec37[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec38[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec61[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec60[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec9[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec59[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec58[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fVec10[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec57[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec56[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec55[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec54[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec65[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec64[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec63[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec62[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec53[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec52[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec51[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec50[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec49[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec48[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec47[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec46[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec45[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec44[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
			fVec11[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
			fRec43[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec42[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
			fRec67[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec66[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec41[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec40[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec39[l79] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry25 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry24 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry40 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry36 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry38 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry41 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry39 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry37 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry7 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry3 = value + 1.864208e-01f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry45 = value + 1.132531e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry4 = value + -1.127463e+00f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry5 = value + -3.133557e-01f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry46 = value + 6.868355e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry42 = value + 1.825885e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry44 = value + 4.877098e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry43 = value + -2.237074e-01f; }
	void set_tetrode_plate_sag_depth(FAUSTFLOAT value) { fEntry47 = value + 4.216220e-01f; }
	void set_tetrode_plate_sag_level(FAUSTFLOAT value) { fEntry48 = value + 1.536646e+00f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry6 = value + 3.997976e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry20 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry19 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry29 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry28 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry26 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry27 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry21 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry17 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry23 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry18 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry33 = value + -1.772999e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry13 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry15 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry22 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry14 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry16 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry30 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry32 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry31 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
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
		float fSlow4 = ((20.0f * (float(fEntry3) + 1.0f)) + 10.0f);
		float fSlow5 = std::exp(((2.30258512f * (float(fEntry4) + 1.0f)) + -2.30258512f));
		float fSlow6 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry5) + 1.0f)) + -6.90775537f)))));
		float fSlow7 = (1.0f - fSlow6);
		float fSlow8 = (1.0f / fSlow4);
		float fSlow9 = std::exp(((4.60517025f * (float(fEntry6) + 1.0f)) + -4.60517025f));
		float fSlow10 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry7) + 1.0f)) + -2.30258512f))));
		float fSlow11 = (1.0f / fSlow10);
		float fSlow12 = (fSlow11 + 1.0f);
		float fSlow13 = (0.0f - (1.0f / (fSlow10 * fSlow12)));
		float fSlow14 = (float(fEntry8) + 1.0f);
		float fSlow15 = (fSlow2 * std::exp((3.45387769f * fSlow14)));
		float fSlow16 = float(fEntry9);
		int iSlow17 = (fSlow16 < 0.0f);
		float fSlow18 = std::tan((fConst2 * ((iSlow17?(1500.0f * fSlow16):0.0f) + 2000.0f)));
		float fSlow19 = (1.0f / fSlow18);
		float fSlow20 = (1.0f - fSlow19);
		float fSlow21 = float(fEntry10);
		float fSlow22 = (fSlow21 + 1.0f);
		float fSlow23 = (1.0f - (0.5f * fSlow22));
		float fSlow24 = std::tan((fConst2 * ((400.0f * fSlow23) + (25.0f * fSlow22))));
		float fSlow25 = (1.0f / fSlow24);
		float fSlow26 = (fSlow25 + 1.0f);
		float fSlow27 = (0.0f - (1.0f / (fSlow24 * fSlow26)));
		float fSlow28 = float(fEntry11);
		float fSlow29 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow28) + -3.0f));
		float fSlow30 = (1.0f - (0.5f * fSlow29));
		float fSlow31 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow28) + -1.0f));
		float fSlow32 = ((float(fEntry12) + 1.0f) + 1.0f);
		float fSlow33 = (fSlow31 / fSlow32);
		float fSlow34 = std::exp(((2.30258512f * (float(fEntry13) + 1.0f)) + -2.30258512f));
		float fSlow35 = std::exp(((3.45387769f * (float(fEntry14) + 1.0f)) + -6.90775537f));
		float fSlow36 = (1.0f / ((fConst0 * fSlow35) + 1.0f));
		float fSlow37 = (100.0f * (1.0f - (float(fEntry15) + 1.0f)));
		float fSlow38 = (0.0f - fSlow37);
		float fSlow39 = std::exp(((4.60517025f * (float(fEntry16) + 1.0f)) + -4.60517025f));
		float fSlow40 = (1.0f - (float(fEntry17) + 1.0f));
		float fSlow41 = (1.0f - (float(fEntry18) + 1.0f));
		float fSlow42 = (fSlow39 + (100.0f * (fSlow40 - fSlow41)));
		float fSlow43 = (float(fEntry19) + 1.0f);
		float fSlow44 = (fSlow43 - (float(fEntry20) + 1.0f));
		float fSlow45 = (2.5f * fSlow44);
		float fSlow46 = std::tan((fConst2 * std::exp(((3.45387769f * (float(fEntry21) + 1.0f)) + -2.30258512f))));
		float fSlow47 = (1.0f / fSlow46);
		float fSlow48 = (fSlow47 + 1.0f);
		float fSlow49 = (0.0f - (1.0f / (fSlow48 * fSlow46)));
		float fSlow50 = (0.5f * (fSlow32 / fSlow2));
		float fSlow51 = (1.0f / ((fConst0 * (fSlow35 * std::exp((1.15129256f * (float(fEntry22) + 1.0f))))) + 1.0f));
		float fSlow52 = (1.0f - fSlow51);
		float fSlow53 = std::exp(((4.60517025f * (float(fEntry23) + 1.0f)) + -2.30258512f));
		float fSlow54 = (0.294117659f / fSlow53);
		float fSlow55 = (float(fEntry24) + 1.0f);
		float fSlow56 = (std::exp((3.45387769f * fSlow55)) * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry25) + 1.0f)))))));
		float fSlow57 = (1.0f / fSlow48);
		float fSlow58 = (1.0f - fSlow47);
		float fSlow59 = (fSlow56 / fSlow46);
		float fSlow60 = std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -13.8155107f));
		float fSlow61 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry26) + 1.0f)) + -11.5129251f)) * fSlow60)) + 1.0f));
		float fSlow62 = (1.0f / ((fConst0 * (fSlow60 * std::exp(((5.75646257f * (float(fEntry28) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow63 = (1.0f - fSlow62);
		float fSlow64 = (1.0f / ((fConst0 * fSlow60) + 1.0f));
		float fSlow65 = (5.0f * (1.0f - (float(fEntry29) + 1.0f)));
		float fSlow66 = (1.0f - fSlow61);
		float fSlow67 = (0.117647059f / fSlow43);
		float fSlow68 = ((100.0f * fSlow40) + fSlow53);
		float fSlow69 = (0.294117659f / fSlow39);
		float fSlow70 = std::exp(((2.30258512f * (float(fEntry30) + 1.0f)) + -2.30258512f));
		float fSlow71 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry31) + 1.0f)) + -6.90775537f)))));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = (100.0f * (1.0f - (float(fEntry32) + 1.0f)));
		float fSlow74 = (0.0f - fSlow73);
		float fSlow75 = (100.0f * fSlow41);
		float fSlow76 = std::exp(((3.45387769f * (float(fEntry33) + 1.0f)) + -2.30258512f));
		float fSlow77 = (1.0f - (float(fEntry34) + 1.0f));
		float fSlow78 = (100.0f * (fSlow41 - fSlow77));
		float fSlow79 = (0.294117659f / fSlow76);
		float fSlow80 = (100.0f * fSlow77);
		float fSlow81 = (fSlow46 * fSlow2);
		float fSlow82 = (0.5f * (fSlow32 / fSlow81));
		float fSlow83 = (fSlow51 + -1.0f);
		float fSlow84 = (1.0f / fSlow81);
		float fSlow85 = (1.0f - (0.5f * fSlow31));
		float fSlow86 = AmpMono_faustpower2_f((0.5f * fSlow32));
		float fSlow87 = (0.5f * (fSlow29 / fSlow86));
		float fSlow88 = (fSlow86 / fSlow2);
		float fSlow89 = (fSlow86 / fSlow81);
		float fSlow90 = (fSlow62 + -1.0f);
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
		float fSlow101 = std::pow(10.0f, (0.0500000007f * (iSlow92?(iSlow93?(iSlow94?(iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?((fSlow91 < 0.0f)?0.0324000008f:(iSlow100?(0.0324000008f - (29.9619999f * fSlow55)):-5.96000004f)):(iSlow99?(-5.96000004f - (5.94000006f * (fSlow91 + -1.0f))):-11.8999996f)):(iSlow98?(-11.8999996f - (5.9000001f * (fSlow91 + -2.0f))):-17.7999992f)):(iSlow97?(-17.7999992f - (5.80000019f * (fSlow91 + -3.0f))):-23.6000004f)):(iSlow96?(-23.6000004f - (5.19999981f * (fSlow91 + -4.0f))):-28.7999992f)):(iSlow95?(-28.7999992f - (3.0999999f * (0.0f - (5.0f * (1.0f - fSlow55))))):-31.8999996f)):(iSlow94?(-31.8999996f - (1.10000002f * (fSlow91 + -6.0f))):-33.0f)):(iSlow93?((0.200000003f * (fSlow91 + -7.0f)) + -33.0f):-32.7999992f)):(iSlow92?((0.400000006f * (fSlow91 + -8.0f)) + -32.7999992f):-32.4000015f)):((fSlow91 < 10.0f)?((0.200000003f * (fSlow91 + -9.0f)) + -32.4000015f):-32.2000008f))));
		float fSlow102 = (1.0f / fSlow26);
		float fSlow103 = (1.0f - fSlow25);
		float fSlow104 = (1.0f / (fSlow24 * fSlow2));
		float fSlow105 = std::pow(10.0f, (0.0500000007f * (fSlow21 * ((4.5f * fSlow22) + (18.0f * fSlow23)))));
		float fSlow106 = float(fEntry35);
		float fSlow107 = ((10.0f * fSlow106) + -14.0f);
		int iSlow108 = (fSlow107 > 0.0f);
		float fSlow109 = ((fSlow106 * ((fSlow21 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow110 = ((fConst11 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow107)))) * fSlow109);
		float fSlow111 = (fConst11 * fSlow109);
		float fSlow112 = (iSlow108?fSlow111:fSlow110);
		float fSlow113 = ((fConst10 * (fConst10 - fSlow112)) + 1.0f);
		float fSlow114 = ((fConst10 * (fConst10 + fSlow112)) + 1.0f);
		float fSlow115 = (iSlow108?fSlow110:fSlow111);
		float fSlow116 = ((fConst10 * (fConst10 + fSlow115)) + 1.0f);
		float fSlow117 = ((fConst10 * (fConst10 - fSlow115)) + 1.0f);
		float fSlow118 = (fSlow19 + 1.0f);
		float fSlow119 = (0.0f - (1.0f / (fSlow18 * fSlow118)));
		float fSlow120 = (fSlow18 * fSlow114);
		float fSlow121 = std::pow(10.0f, ((0.0500000007f * fSlow16) * (iSlow17?18.0f:9.0f)));
		float fSlow122 = (250.0f * (float(fEntry36) + 1.0f));
		float fSlow123 = (1.0f / fSlow12);
		float fSlow124 = (1.0f - fSlow11);
		float fSlow125 = std::exp((0.0f - (fConst1 / std::exp(((4.60517025f * (float(fEntry37) + 1.0f)) + -9.2103405f)))));
		float fSlow126 = (1.0f - fSlow125);
		float fSlow127 = (250.0f * (float(fEntry38) + 1.0f));
		float fSlow128 = std::exp(((4.60517025f * (float(fEntry39) + 1.0f)) + -9.2103405f));
		float fSlow129 = (1.0f / ((fConst0 * fSlow128) + 1.0f));
		float fSlow130 = (100.0f * (1.0f - (float(fEntry40) + 1.0f)));
		float fSlow131 = (1.0f - (1.0f / ((fConst0 * (fSlow128 * std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow132 = std::exp(((2.30258512f * (float(fEntry42) + 1.0f)) + -2.30258512f));
		float fSlow133 = std::exp((0.0f - (fConst1 / std::exp(((3.45387769f * (float(fEntry43) + 1.0f)) + -6.90775537f)))));
		float fSlow134 = (1.0f - fSlow133);
		float fSlow135 = std::exp((0.0f - (10.0f * (1.0f - (float(fEntry44) + 1.0f)))));
		float fSlow136 = std::exp(((3.45387769f * (float(fEntry45) + 1.0f)) + -2.30258512f));
		float fSlow137 = (0.294117659f / fSlow136);
		float fSlow138 = std::exp(((3.45387769f * (float(fEntry46) + 1.0f)) + -2.30258512f));
		float fSlow139 = (0.294117659f / fSlow138);
		float fSlow140 = (5.0f * fSlow14);
		int iSlow141 = (fSlow140 < 9.0f);
		int iSlow142 = (fSlow140 < 8.0f);
		int iSlow143 = (fSlow140 < 7.0f);
		int iSlow144 = (fSlow140 < 6.0f);
		int iSlow145 = (fSlow140 < 5.0f);
		int iSlow146 = (fSlow140 < 4.0f);
		int iSlow147 = (fSlow140 < 3.0f);
		int iSlow148 = (fSlow140 < 2.0f);
		int iSlow149 = (fSlow140 < 1.0f);
		float fSlow150 = std::pow(10.0f, (0.0500000007f * (iSlow141?(iSlow142?(iSlow143?(iSlow144?(iSlow145?(iSlow146?(iSlow147?(iSlow148?(iSlow149?((fSlow140 < 0.0f)?9.47000027f:(iSlow149?(9.47000027f - (29.6499996f * fSlow14)):3.53999996f)):(iSlow148?(3.53999996f - (5.8499999f * (fSlow140 + -1.0f))):-2.30999994f)):(iSlow147?(-2.30999994f - (5.75f * (fSlow140 + -2.0f))):-8.06000042f)):(iSlow146?(-8.06000042f - (5.63999987f * (fSlow140 + -3.0f))):-13.6999998f)):(iSlow145?(-13.6999998f - (4.4000001f * (fSlow140 + -4.0f))):-18.1000004f)):(iSlow144?(-18.1000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow14))))):-20.2999992f)):(iSlow143?(-20.2999992f - (0.600000024f * (fSlow140 + -6.0f))):-20.8999996f)):(iSlow142?((0.100000001f * (fSlow140 + -7.0f)) + -20.8999996f):-20.7999992f)):(iSlow141?((0.100000001f * (fSlow140 + -8.0f)) + -20.7999992f):-20.7000008f)):((fSlow140 < 10.0f)?((0.100000001f * (fSlow140 + -9.0f)) + -20.7000008f):-20.6000004f))));
		float fSlow151 = std::exp(((2.30258512f * (float(fEntry47) + 1.0f)) + -2.30258512f));
		float fSlow152 = (0.5f * (float(tanhf(float(float(fEntry48)))) + 1.0f));
		float fSlow153 = (fSlow7 / (1.00100005f - fSlow152));
		float fSlow154 = float(fEntry49);
		float fSlow155 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow154)));
		float fSlow156 = float(fEntry50);
		float fSlow157 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow156))));
		float fSlow158 = (15.0f * fSlow156);
		int iSlow159 = (fSlow158 > 0.0f);
		float fSlow160 = (fConst167 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow158))));
		float fSlow161 = (iSlow159?fConst167:fSlow160);
		float fSlow162 = ((fConst166 * (fConst166 - fSlow161)) + 1.0f);
		float fSlow163 = ((fConst166 * (fConst166 + fSlow161)) + 1.0f);
		float fSlow164 = (iSlow159?fSlow160:fConst167);
		float fSlow165 = ((fConst166 * (fConst166 + fSlow164)) + 1.0f);
		float fSlow166 = ((fConst166 * (fConst166 - fSlow164)) + 1.0f);
		float fSlow167 = (0.0f - (10.0f * fSlow154));
		int iSlow168 = (fSlow167 > 0.0f);
		float fSlow169 = (fConst170 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow167))));
		float fSlow170 = (iSlow168?fConst170:fSlow169);
		float fSlow171 = ((fConst169 * (fConst169 - fSlow170)) + 1.0f);
		float fSlow172 = ((fConst169 * (fConst169 + fSlow170)) + 1.0f);
		float fSlow173 = (iSlow168?fSlow169:fConst170);
		float fSlow174 = ((fConst169 * (fConst169 - fSlow173)) + 1.0f);
		float fSlow175 = ((fConst169 * (fConst169 + fSlow173)) + 1.0f);
		float fSlow176 = (0.0f - (17.0f * fSlow154));
		int iSlow177 = (fSlow176 > 0.0f);
		float fSlow178 = (fConst174 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow176))));
		float fSlow179 = (iSlow177?fConst174:fSlow178);
		float fSlow180 = ((fConst173 * (fConst173 - fSlow179)) + 1.0f);
		float fSlow181 = ((fConst173 * (fConst173 + fSlow179)) + 1.0f);
		float fSlow182 = (iSlow177?fSlow178:fConst174);
		float fSlow183 = ((fConst173 * (fConst173 + fSlow182)) + 1.0f);
		float fSlow184 = ((fConst173 * (fConst173 - fSlow182)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow56 * fTemp0);
			fRec11[0] = ((fSlow49 * fVec0[1]) - (fSlow57 * ((fSlow58 * fRec11[1]) - (fSlow59 * fTemp0))));
			fRec13[0] = ((fSlow63 * fRec13[1]) + (fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec11[0])) - fRec13[1]))));
			fRec12[0] = ((fSlow61 * fRec13[0]) + (fSlow66 * fRec12[1]));
			float fTemp1 = (fSlow45 + (fRec11[0] - fRec12[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) - (2.5f * (fSlow44 - (fSlow43 * (((std::fabs((fTemp3 * fTemp2)) + -2.0f) * fTemp3) * fTemp2)))))) - fSlow68);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow42 + ((fSlow53 * ((((std::fabs((fTemp6 * fTemp5)) + -2.0f) * fTemp6) * fTemp5) + 1.0f)) + std::max<float>(0.0f, fTemp4))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow69 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (fTemp8 * (std::fabs(fTemp8) + -2.0f));
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow39 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)));
			fRec14[0] = ((fSlow71 * fRec14[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp10 - fSlow75)))));
			float fTemp11 = (fSlow70 * fRec14[0]);
			fRec10[0] = ((fSlow52 * fRec10[1]) + (fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp10 - fTemp11) - fSlow75)) - fRec10[1])))));
			float fTemp12 = (fSlow34 * fRec10[0]);
			float fTemp13 = (fSlow76 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow78));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((fTemp12 + std::min<float>(0.0f, fTemp13)) - (fSlow76 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow80);
			fVec1[0] = (fSlow50 * fTemp16);
			fRec9[0] = ((fSlow49 * fVec1[1]) + (fSlow57 * ((fSlow82 * fTemp16) - (fSlow58 * fRec9[1]))));
			fRec16[0] = ((fSlow63 * fRec16[1]) + (fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec9[0])) - fRec16[1]))));
			fRec15[0] = ((fSlow66 * fRec15[1]) + (fSlow61 * fRec16[0]));
			float fTemp17 = (fSlow45 + (fRec9[0] - fRec15[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow44 - (fSlow43 * ((fTemp18 * (std::fabs((fTemp18 * fTemp19)) + -2.0f)) * fTemp19)))))) - fSlow68);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp20) + (fSlow53 * ((((std::fabs((fTemp21 * fTemp22)) + -2.0f) * fTemp21) * fTemp22) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow69 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (std::fabs(fTemp24) + -2.0f);
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow39 * ((((std::fabs((fTemp24 * fTemp25)) + -2.0f) * fTemp24) * fTemp25) + 1.0f)));
			fRec17[0] = ((fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp26 - fSlow75)))) + (fSlow71 * fRec17[1]));
			float fTemp27 = (fSlow70 * fRec17[0]);
			fRec8[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp26 - fTemp27) - fSlow75)) - fRec8[1])))) - (fSlow83 * fRec8[1]));
			float fTemp28 = (fSlow34 * fRec8[0]);
			float fTemp29 = (fSlow76 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow78));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (fTemp30 * (std::fabs(fTemp30) + -2.0f));
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow76 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow80);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec7[0] = ((fSlow49 * fVec2[1]) - (fSlow57 * ((fSlow58 * fRec7[1]) - (fSlow84 * fTemp32))));
			fRec19[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec7[0])) - fRec19[1]))) + (fSlow63 * fRec19[1]));
			fRec18[0] = ((fSlow66 * fRec18[1]) + (fSlow61 * fRec19[0]));
			float fTemp33 = (fSlow45 + (fRec7[0] - fRec18[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = ((std::fabs(fTemp34) + -2.0f) * fTemp34);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow44 - (fSlow43 * (fTemp35 * (std::fabs(fTemp35) + -2.0f))))))) - fSlow68);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (std::fabs(fTemp37) + -2.0f);
			float fTemp39 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp36) + (fSlow53 * ((((std::fabs((fTemp37 * fTemp38)) + -2.0f) * fTemp37) * fTemp38) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow69 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = (std::fabs(fTemp40) + -2.0f);
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow39 * ((((std::fabs((fTemp41 * fTemp40)) + -2.0f) * fTemp41) * fTemp40) + 1.0f)));
			fRec20[0] = ((fSlow71 * fRec20[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp42 - fSlow75)))));
			float fTemp43 = (fSlow70 * fRec20[0]);
			fRec6[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp42 - fTemp43) - fSlow75)) - fRec6[1])))) + (fSlow52 * fRec6[1]));
			float fTemp44 = (fSlow34 * fRec6[0]);
			float fTemp45 = (fSlow76 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow78));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (fTemp46 * (std::fabs(fTemp46) + -2.0f));
			float fTemp48 = ((fSlow33 * (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow76 * (1.0f - (fTemp47 * (std::fabs(fTemp47) + -2.0f))))) - fSlow80)) + (fSlow85 * fTemp16));
			fVec3[0] = (fSlow88 * fTemp48);
			fRec23[0] = ((fSlow49 * fVec3[1]) - (fSlow57 * ((fSlow58 * fRec23[1]) - (fSlow89 * fTemp48))));
			fRec25[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec23[0])) - fRec25[1]))) - (fSlow90 * fRec25[1]));
			fRec24[0] = ((fSlow61 * fRec25[0]) + (fSlow66 * fRec24[1]));
			float fTemp49 = (fSlow45 + (fRec23[0] - fRec24[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (std::fabs(fTemp50) + -2.0f);
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow44 - (fSlow43 * ((fTemp50 * (std::fabs((fTemp50 * fTemp51)) + -2.0f)) * fTemp51)))))) - fSlow68);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (fTemp53 * (std::fabs(fTemp53) + -2.0f));
			float fTemp55 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp52) + (fSlow53 * ((fTemp54 * (std::fabs(fTemp54) + -2.0f)) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow69 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = ((std::fabs(fTemp56) + -2.0f) * fTemp56);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow39 * ((fTemp57 * (std::fabs(fTemp57) + -2.0f)) + 1.0f)));
			fRec27[0] = ((fSlow71 * fRec27[1]) + (fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp58 - fSlow75)))));
			float fTemp59 = (fSlow70 * fRec27[0]);
			fRec26[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp58 - fTemp59) - fSlow75)) - fRec26[1])))) - (fSlow83 * fRec26[1]));
			float fTemp60 = (fSlow34 * fRec26[0]);
			float fTemp61 = (fSlow76 + ((fTemp58 - (fTemp60 + fTemp59)) - fSlow78));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (std::fabs(fTemp62) + -2.0f);
			float fTemp64 = ((((fSlow76 * (((fTemp63 * (std::fabs((fTemp63 * fTemp62)) + -2.0f)) * fTemp62) + -1.0f)) + fTemp60) + std::min<float>(0.0f, fTemp61)) - fSlow80);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec22[0] = ((fSlow49 * fVec4[1]) + (fSlow57 * ((fSlow84 * fTemp64) - (fSlow58 * fRec22[1]))));
			fRec29[0] = ((fSlow64 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow65 + fRec22[0])) - fRec29[1]))) - (fSlow90 * fRec29[1]));
			fRec28[0] = ((fSlow66 * fRec28[1]) + (fSlow61 * fRec29[0]));
			float fTemp65 = (fSlow45 + (fRec22[0] - fRec28[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow44 - (fSlow43 * (((std::fabs((fTemp66 * fTemp67)) + -2.0f) * fTemp66) * fTemp67)))))) - fSlow68);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (fTemp69 * (std::fabs(fTemp69) + -2.0f));
			float fTemp71 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp68) + (fSlow53 * ((fTemp70 * (std::fabs(fTemp70) + -2.0f)) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow69 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (std::fabs(fTemp72) + -2.0f);
			float fTemp74 = ((fSlow39 * (((fTemp73 * (std::fabs((fTemp73 * fTemp72)) + -2.0f)) * fTemp72) + 1.0f)) + std::max<float>(0.0f, fTemp71));
			fRec30[0] = ((fSlow72 * (fSlow73 + std::max<float>(fSlow74, (fTemp74 - fSlow75)))) + (fSlow71 * fRec30[1]));
			float fTemp75 = (fSlow70 * fRec30[0]);
			fRec21[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp74 - fTemp75) - fSlow75)) - fRec21[1])))) + (fSlow52 * fRec21[1]));
			float fTemp76 = (fSlow34 * fRec21[0]);
			float fTemp77 = (fSlow76 + ((fTemp74 - (fTemp76 + fTemp75)) - fSlow78));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = (((fSlow30 * fTemp48) + (fSlow87 * (((fTemp76 + std::min<float>(0.0f, fTemp77)) - (fSlow76 * (1.0f - ((fTemp79 * (std::fabs((fTemp79 * fTemp78)) + -2.0f)) * fTemp78)))) - fSlow80))) * fSlow101);
			float fTemp81 = (fSlow3 * fTemp80);
			fVec5[0] = fTemp81;
			fRec5[0] = ((fSlow27 * fVec5[1]) - (fSlow102 * ((fSlow103 * fRec5[1]) - (fSlow104 * fTemp80))));
			fRec31[0] = (0.0f - (fSlow102 * ((fSlow103 * fRec31[1]) - (fTemp81 + fVec5[1]))));
			float fTemp82 = (fRec5[0] + (fSlow105 * fRec31[0]));
			fVec6[0] = fTemp82;
			fRec4[0] = ((fConst6 * fVec6[1]) - (fConst7 * ((fConst8 * fRec4[1]) - (fConst4 * fTemp82))));
			float fTemp83 = (fConst12 * fRec3[1]);
			fRec3[0] = (fRec4[0] - (((fSlow113 * fRec3[2]) + fTemp83) / fSlow114));
			float fTemp84 = (((fRec3[0] * fSlow116) + fTemp83) + (fRec3[2] * fSlow117));
			float fTemp85 = (fTemp84 / fSlow114);
			fVec7[0] = fTemp85;
			fRec2[0] = (0.0f - (((fSlow20 * fRec2[1]) - (fVec7[1] + fTemp85)) / fSlow118));
			fRec32[0] = ((fVec7[1] * fSlow119) - (((fRec32[1] * fSlow20) - (fTemp84 / fSlow120)) / fSlow118));
			float fTemp86 = ((fSlow15 * (fRec2[0] + (fRec32[0] * fSlow121))) - fSlow122);
			fVec8[0] = fTemp86;
			fRec1[0] = ((fSlow13 * fVec8[1]) - (fSlow123 * ((fSlow124 * fRec1[1]) - (fSlow11 * fTemp86))));
			fRec33[0] = ((fSlow125 * fRec33[1]) + (fSlow126 * (fRec1[0] - fSlow127)));
			fRec34[0] = ((fSlow129 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow130 + ((fRec1[0] - fRec33[0]) - fSlow127))) - fRec34[1]))) + (fSlow131 * fRec34[1]));
			float fTemp87 = (fSlow9 * ((fRec1[0] - (fRec33[0] + fRec34[0])) - fSlow127));
			fRec35[0] = ((fSlow133 * fRec35[1]) + (fSlow134 * (std::max<float>(fSlow135, fTemp87) - fSlow135)));
			float fTemp88 = (fSlow132 * fRec35[0]);
			fRec0[0] = ((fSlow6 * fRec0[1]) + (fSlow7 * std::min<float>(1.0f, std::fabs((fSlow8 * (fTemp87 - fTemp88))))));
			float fTemp89 = (fSlow4 / ((fSlow5 * fRec0[0]) + 1.0f));
			float fTemp90 = (fSlow136 + (fTemp87 - (fTemp88 + fTemp89)));
			float fTemp91 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow137 * std::max<float>(0.0f, fTemp90))));
			float fTemp92 = (fTemp91 * (std::fabs(fTemp91) + -2.0f));
			float fTemp93 = (((fTemp89 + std::min<float>(0.0f, fTemp90)) - (fSlow136 * (1.0f - (fTemp92 * (std::fabs(fTemp92) + -2.0f))))) - fSlow138);
			fRec36[0] = ((fSlow134 * (std::max<float>(fSlow135, (0.0f - fTemp87)) - fSlow135)) + (fSlow133 * fRec36[1]));
			float fTemp94 = (fSlow132 * fRec36[0]);
			fRec37[0] = ((fSlow7 * std::min<float>(1.0f, std::fabs((fSlow8 * (0.0f - (fTemp87 + fTemp94)))))) + (fSlow6 * fRec37[1]));
			float fTemp95 = (fSlow4 / ((fSlow5 * fRec37[0]) + 1.0f));
			float fTemp96 = (fSlow136 - (fTemp94 + (fTemp87 + fTemp95)));
			float fTemp97 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow137 * std::max<float>(0.0f, fTemp96))));
			float fTemp98 = (fTemp97 * (std::fabs(fTemp97) + -2.0f));
			float fTemp99 = (((std::min<float>(0.0f, fTemp96) + fTemp95) - (fSlow136 * (1.0f - (fTemp98 * (std::fabs(fTemp98) + -2.0f))))) - fSlow138);
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::min<float>(0.0f, fTemp99))));
			float fTemp101 = (fTemp100 * (std::fabs(fTemp100) + -2.0f));
			float fTemp102 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::min<float>(0.0f, fTemp93))));
			float fTemp103 = (fTemp102 * (std::fabs(fTemp102) + -2.0f));
			float fTemp104 = (std::max<float>(0.0f, fTemp93) - (std::max<float>(0.0f, fTemp99) + (fSlow138 * (((fTemp101 * (std::fabs(fTemp101) + -2.0f)) + 1.0f) - ((fTemp103 * (std::fabs(fTemp103) + -2.0f)) + 1.0f)))));
			fRec38[0] = ((fSlow6 * fRec38[1]) + (fSlow153 * (std::max<float>(fSlow152, (fSlow8 * fTemp104)) - fSlow152)));
			float fTemp105 = (fSlow3 * ((fTemp104 * fSlow150) / ((fSlow151 * fRec38[0]) + 1.0f)));
			fRec61[0] = (fTemp105 - (fConst108 * ((fConst110 * fRec61[2]) + (fConst111 * fRec61[1]))));
			fRec60[0] = ((fConst108 * (((fConst109 * fRec61[1]) + (fConst107 * fRec61[0])) + (fConst107 * fRec61[2]))) - (fConst105 * ((fConst111 * fRec60[1]) + (fConst112 * fRec60[2]))));
			float fTemp106 = (((fConst107 * fRec60[0]) + (fConst109 * fRec60[1])) + (fConst107 * fRec60[2]));
			fVec9[0] = fTemp106;
			fRec59[0] = (0.0f - (fConst101 * ((fConst102 * fRec59[1]) - (fConst105 * (fVec9[1] + fTemp106)))));
			fRec58[0] = (fRec59[0] - (fConst100 * ((fConst113 * fRec58[2]) + (fConst114 * fRec58[1]))));
			float fTemp107 = (fRec58[2] + (fRec58[0] + (2.0f * fRec58[1])));
			fVec10[0] = fTemp107;
			fRec57[0] = (0.0f - (fConst96 * ((fConst97 * fRec57[1]) - (fConst100 * (fTemp107 + fVec10[1])))));
			fRec56[0] = (fRec57[0] - (fConst94 * ((fConst115 * fRec56[2]) + (fConst118 * fRec56[1]))));
			fRec55[0] = ((fConst94 * (fRec56[2] + (fRec56[0] + (2.0f * fRec56[1])))) - (fConst93 * ((fConst119 * fRec55[2]) + (fConst118 * fRec55[1]))));
			fRec54[0] = ((fConst93 * (fRec55[2] + (fRec55[0] + (2.0f * fRec55[1])))) - (fConst92 * ((fConst118 * fRec54[1]) + (fConst120 * fRec54[2]))));
			fRec65[0] = ((fConst100 * ((fConst122 * fTemp107) + (fConst123 * fVec10[1]))) - (fConst124 * fRec65[1]));
			fRec64[0] = (fRec65[0] - (fConst94 * ((fConst115 * fRec64[2]) + (fConst118 * fRec64[1]))));
			fRec63[0] = ((fConst94 * (((fConst121 * fRec64[1]) + (fConst117 * fRec64[0])) + (fConst117 * fRec64[2]))) - (fConst93 * ((fConst119 * fRec63[2]) + (fConst118 * fRec63[1]))));
			fRec62[0] = ((fConst93 * (((fConst117 * fRec63[0]) + (fConst121 * fRec63[1])) + (fConst117 * fRec63[2]))) - (fConst92 * ((fConst120 * fRec62[2]) + (fConst118 * fRec62[1]))));
			float fTemp108 = (fConst89 * fRec53[1]);
			fRec53[0] = ((fConst92 * ((fRec54[2] + (fRec54[0] + (2.0f * fRec54[1]))) + (0.0316227749f * (((fConst121 * fRec62[1]) + (fConst117 * fRec62[0])) + (fConst117 * fRec62[2]))))) - (fConst88 * (fTemp108 + (fConst125 * fRec53[2]))));
			float fTemp109 = (fConst83 * fRec52[1]);
			fRec52[0] = ((fConst88 * ((fTemp108 + (fConst127 * fRec53[0])) + (fConst128 * fRec53[2]))) - (fConst82 * (fTemp109 + (fConst129 * fRec52[2]))));
			float fTemp110 = (fConst133 * fRec51[1]);
			fRec51[0] = ((fConst82 * ((fTemp109 + (fConst131 * fRec52[0])) + (fConst132 * fRec52[2]))) - (fConst75 * (fTemp110 + (fConst134 * fRec51[2]))));
			float fTemp111 = (fConst137 * fRec50[1]);
			fRec50[0] = ((fConst75 * ((fConst77 * fRec51[2]) + (fTemp110 + (fConst135 * fRec51[0])))) - (fConst68 * ((fConst136 * fRec50[2]) + fTemp111)));
			float fTemp112 = (fConst62 * fRec49[1]);
			fRec49[0] = ((fConst68 * (((fConst70 * fRec50[0]) + fTemp111) + (fConst138 * fRec50[2]))) - (fConst61 * (fTemp112 + (fConst139 * fRec49[2]))));
			float fTemp113 = (fConst56 * fRec48[1]);
			fRec48[0] = ((fConst61 * ((fTemp112 + (fConst141 * fRec49[0])) + (fConst142 * fRec49[2]))) - (fConst55 * ((fConst143 * fRec48[2]) + fTemp113)));
			float fTemp114 = (fConst50 * fRec47[1]);
			fRec47[0] = ((fConst55 * ((fTemp113 + (fConst145 * fRec48[0])) + (fConst146 * fRec48[2]))) - (fConst49 * ((fConst147 * fRec47[2]) + fTemp114)));
			float fTemp115 = (fConst151 * fRec46[1]);
			fRec46[0] = ((fConst49 * ((fTemp114 + (fConst149 * fRec47[0])) + (fConst150 * fRec47[2]))) - (fConst42 * (fTemp115 + (fConst152 * fRec46[2]))));
			float fTemp116 = (fConst154 * fRec45[1]);
			fRec45[0] = ((fConst42 * (((fConst44 * fRec46[0]) + fTemp115) + (fConst153 * fRec46[2]))) - (fConst35 * (fTemp116 + (fConst155 * fRec45[2]))));
			float fTemp117 = (fConst157 * fRec44[1]);
			fRec44[0] = ((fConst35 * ((fConst37 * fRec45[2]) + (fTemp116 + (fConst156 * fRec45[0])))) - (fConst24 * (fTemp117 + (fConst158 * fRec44[2]))));
			float fTemp118 = ((fConst29 * fRec44[2]) + ((fConst159 * fRec44[0]) + fTemp117));
			fVec11[0] = fTemp118;
			fRec43[0] = ((fConst24 * ((fConst27 * fVec11[1]) + (fConst26 * fTemp118))) - (fConst161 * fRec43[1]));
			fRec42[0] = (fRec43[0] - (fConst17 * ((fConst162 * fRec42[2]) + (fConst164 * fRec42[1]))));
			fRec67[0] = (0.0f - (fConst165 * ((fConst160 * fRec67[1]) - (fConst24 * (fTemp118 + fVec11[1])))));
			fRec66[0] = (fRec67[0] - (fConst17 * ((fConst164 * fRec66[1]) + (fConst162 * fRec66[2]))));
			float fTemp119 = (fConst14 * fRec41[1]);
			fRec41[0] = ((fConst17 * ((((fConst19 * fRec42[1]) + (fConst163 * fRec42[0])) + (fConst163 * fRec42[2])) + (fSlow157 * (fRec66[2] + (fRec66[0] + (2.0f * fRec66[1])))))) - (((fSlow162 * fRec41[2]) + fTemp119) / fSlow163));
			float fTemp120 = (fConst171 * fRec40[1]);
			fRec40[0] = ((((fTemp119 + (fRec41[0] * fSlow165)) + (fRec41[2] * fSlow166)) / fSlow163) - (((fRec40[2] * fSlow171) + fTemp120) / fSlow172));
			float fTemp121 = (fConst175 * fRec39[1]);
			fRec39[0] = ((((fRec40[2] * fSlow174) + (fTemp120 + (fRec40[0] * fSlow175))) / fSlow172) - (((fRec39[2] * fSlow180) + fTemp121) / fSlow181));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow155 * ((((fRec39[0] * fSlow183) + fTemp121) + (fRec39[2] * fSlow184)) / fSlow181)):fTemp105)));
			fVec0[1] = fVec0[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec14[1] = fRec14[0];
			fRec10[1] = fRec10[0];
			fVec1[1] = fVec1[0];
			fRec9[1] = fRec9[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fRec8[1] = fRec8[0];
			fVec2[1] = fVec2[0];
			fRec7[1] = fRec7[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec6[1] = fRec6[0];
			fVec3[1] = fVec3[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fVec4[1] = fVec4[0];
			fRec22[1] = fRec22[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec21[1] = fRec21[0];
			fVec5[1] = fVec5[0];
			fRec5[1] = fRec5[0];
			fRec31[1] = fRec31[0];
			fVec6[1] = fVec6[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec7[1] = fVec7[0];
			fRec2[1] = fRec2[0];
			fRec32[1] = fRec32[0];
			fVec8[1] = fVec8[0];
			fRec1[1] = fRec1[0];
			fRec33[1] = fRec33[0];
			fRec34[1] = fRec34[0];
			fRec35[1] = fRec35[0];
			fRec0[1] = fRec0[0];
			fRec36[1] = fRec36[0];
			fRec37[1] = fRec37[0];
			fRec38[1] = fRec38[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fVec9[1] = fVec9[0];
			fRec59[1] = fRec59[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fVec10[1] = fVec10[0];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec65[1] = fRec65[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
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
			fVec11[1] = fVec11[0];
			fRec43[1] = fRec43[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec67[1] = fRec67[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];

		}

	}


};

#endif
