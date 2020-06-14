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
	int fSamplingFreq;
	float fConst0;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	float fConst1;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	FAUSTFLOAT fEntry10;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
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
	float fRec10[2];
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	float fRec12[2];
	float fRec11[2];
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fConst6;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	float fRec13[2];
	FAUSTFLOAT fEntry34;
	float fRec9[2];
	FAUSTFLOAT fEntry35;
	float fVec1[2];
	float fRec17[2];
	float fRec19[2];
	float fRec18[2];
	float fRec20[2];
	float fRec16[2];
	float fVec2[2];
	float fRec15[2];
	float fRec22[2];
	float fRec21[2];
	float fRec23[2];
	float fRec14[2];
	float fVec3[2];
	float fRec8[2];
	float fRec25[2];
	float fRec24[2];
	float fRec26[2];
	float fRec27[2];
	float fVec4[2];
	float fRec7[2];
	float fRec29[2];
	float fRec28[2];
	float fRec30[2];
	float fRec6[2];
	float fVec5[2];
	float fRec5[2];
	float fRec31[2];
	float fVec6[2];
	float fConst7;
	float fConst8;
	float fRec4[2];
	float fConst9;
	float fConst10;
	float fConst11;
	FAUSTFLOAT fEntry36;
	float fConst12;
	float fRec3[3];
	float fVec7[2];
	float fRec2[2];
	float fRec32[2];
	FAUSTFLOAT fEntry37;
	float fVec8[2];
	float fRec1[2];
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	float fRec34[2];
	FAUSTFLOAT fEntry42;
	float fRec33[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fRec35[2];
	FAUSTFLOAT fEntry46;
	float fRec0[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec37[2];
	float fRec36[2];
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
	float fRec60[3];
	float fConst112;
	float fConst113;
	float fRec59[3];
	float fVec9[2];
	float fRec58[2];
	float fConst114;
	float fConst115;
	float fRec57[3];
	float fVec10[2];
	float fConst116;
	float fRec56[2];
	float fConst117;
	float fConst118;
	float fConst119;
	float fConst120;
	float fRec55[3];
	float fConst121;
	float fRec54[3];
	float fConst122;
	float fRec53[3];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fRec64[2];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fConst127;
	float fConst128;
	float fRec52[3];
	float fConst129;
	float fConst130;
	float fConst131;
	float fRec51[3];
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec50[3];
	float fConst135;
	float fConst136;
	float fConst137;
	float fRec49[3];
	float fConst138;
	float fConst139;
	float fConst140;
	float fRec48[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fRec47[3];
	float fConst144;
	float fConst145;
	float fConst146;
	float fRec46[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec45[3];
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec44[3];
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec43[3];
	float fConst156;
	float fVec11[2];
	float fConst157;
	float fConst158;
	float fConst159;
	float fRec42[2];
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec41[3];
	FAUSTFLOAT fEntry50;
	float fConst163;
	float fRec66[2];
	float fRec65[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec40[3];
	float fConst168;
	float fConst169;
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
		fConst10 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst11 = (1.0f / fConst9);
		fConst12 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst13 = std::tan((3455.75195f / fConst0));
		fConst14 = (1.0f / fConst13);
		fConst15 = (1.0f / (((fConst14 + 1.0f) / fConst13) + 1.0f));
		fConst16 = AmpMono_faustpower2_f(fConst13);
		fConst17 = (0.0f - (2.0f / fConst16));
		fConst18 = std::tan((2984.51294f / fConst0));
		fConst19 = (1.0f / fConst18);
		fConst20 = (fConst0 * std::sin((5969.02588f / fConst0)));
		fConst21 = (27816.8476f / fConst20);
		fConst22 = (1.0f / (((fConst19 + fConst21) / fConst18) + 1.0f));
		fConst23 = (fConst14 + 1.0f);
		fConst24 = (1.0f / (fConst13 * fConst23));
		fConst25 = (8796.45898f / fConst20);
		fConst26 = (((fConst19 - fConst25) / fConst18) + 1.0f);
		fConst27 = (37699.1133f / fConst0);
		fConst28 = std::tan(fConst27);
		fConst29 = (1.0f / fConst28);
		fConst30 = (fConst0 * std::sin((75398.2266f / fConst0)));
		fConst31 = (24836.4707f / fConst30);
		fConst32 = (1.0f / (((fConst29 + fConst31) / fConst28) + 1.0f));
		fConst33 = (785.398193f / fConst30);
		fConst34 = (((fConst29 - fConst33) / fConst28) + 1.0f);
		fConst35 = std::tan((21362.8301f / fConst0));
		fConst36 = (1.0f / fConst35);
		fConst37 = (fConst0 * std::sin((42725.6602f / fConst0)));
		fConst38 = (19869.1758f / fConst37);
		fConst39 = (1.0f / (((fConst36 + fConst38) / fConst35) + 1.0f));
		fConst40 = (628.318542f / fConst37);
		fConst41 = (((fConst36 - fConst40) / fConst35) + 1.0f);
		fConst42 = std::tan((11938.0518f / fConst0));
		fConst43 = (1.0f / fConst42);
		fConst44 = (fConst0 * std::sin((23876.1035f / fConst0)));
		fConst45 = (4701.22607f / fConst44);
		fConst46 = (1.0f / (((fConst43 + fConst45) / fConst42) + 1.0f));
		fConst47 = (2356.19458f / fConst44);
		fConst48 = (((fConst43 + fConst47) / fConst42) + 1.0f);
		fConst49 = std::tan((9581.85742f / fConst0));
		fConst50 = (1.0f / fConst49);
		fConst51 = (fConst0 * std::sin((19163.7148f / fConst0)));
		fConst52 = (2921.88965f / fConst51);
		fConst53 = (1.0f / (((fConst50 + fConst52) / fConst49) + 1.0f));
		fConst54 = (1036.72558f / fConst51);
		fConst55 = (((fConst50 - fConst54) / fConst49) + 1.0f);
		fConst56 = std::tan((5215.04394f / fConst0));
		fConst57 = (1.0f / fConst56);
		fConst58 = (fConst0 * std::sin((10430.0879f / fConst0)));
		fConst59 = (3713.44482f / fConst58);
		fConst60 = (1.0f / (((fConst57 + fConst59) / fConst56) + 1.0f));
		fConst61 = (2481.85815f / fConst58);
		fConst62 = (((fConst57 + fConst61) / fConst56) + 1.0f);
		fConst63 = (3707.07935f / fConst0);
		fConst64 = std::tan(fConst63);
		fConst65 = (1.0f / fConst64);
		fConst66 = (fConst0 * std::sin((7414.15869f / fConst0)));
		fConst67 = (502.654816f / fConst66);
		fConst68 = (1.0f / (((fConst65 + fConst67) / fConst64) + 1.0f));
		fConst69 = (1416.67383f / fConst66);
		fConst70 = (((fConst65 - fConst69) / fConst64) + 1.0f);
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
		fConst83 = (1390.84241f / fConst80);
		fConst84 = (((fConst79 - fConst83) / fConst78) + 1.0f);
		fConst85 = std::tan((1853.53967f / fConst0));
		fConst86 = (1.0f / fConst85);
		fConst87 = (fConst0 * std::sin(fConst63));
		fConst88 = (1059.9884f / fConst87);
		fConst89 = (1.0f / (((fConst86 + fConst88) / fConst85) + 1.0f));
		fConst90 = (188.49556f / fConst87);
		fConst91 = (((fConst86 - fConst90) / fConst85) + 1.0f);
		fConst92 = std::tan((17592.918f / fConst0));
		fConst93 = (1.0f / fConst92);
		fConst94 = (1.0f / (((fConst93 + 0.445041865f) / fConst92) + 1.0f));
		fConst95 = (1.0f / (((fConst93 + 1.24697959f) / fConst92) + 1.0f));
		fConst96 = (1.0f / (((fConst93 + 1.8019377f) / fConst92) + 1.0f));
		fConst97 = (fConst93 + 1.0f);
		fConst98 = (1.0f / fConst97);
		fConst99 = std::tan((34557.5195f / fConst0));
		fConst100 = (1.0f / fConst99);
		fConst101 = (1.0f / (((fConst100 + 1.0f) / fConst99) + 1.0f));
		fConst102 = (1.0f / (fConst100 + 1.0f));
		fConst103 = (1.0f - fConst100);
		fConst104 = std::tan((345.575195f / fConst0));
		fConst105 = (1.0f / fConst104);
		fConst106 = (1.0f / (((fConst105 + 0.765366852f) / fConst104) + 1.0f));
		fConst107 = AmpMono_faustpower2_f(fConst104);
		fConst108 = (1.0f / fConst107);
		fConst109 = (1.0f / (((fConst105 + 1.84775901f) / fConst104) + 1.0f));
		fConst110 = (((fConst105 + -1.84775901f) / fConst104) + 1.0f);
		fConst111 = (2.0f * (1.0f - fConst108));
		fConst112 = (0.0f - (2.0f / fConst107));
		fConst113 = (((fConst105 + -0.765366852f) / fConst104) + 1.0f);
		fConst114 = (((fConst100 + -1.0f) / fConst99) + 1.0f);
		fConst115 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst99))));
		fConst116 = (1.0f - fConst93);
		fConst117 = (((fConst93 + -1.8019377f) / fConst92) + 1.0f);
		fConst118 = AmpMono_faustpower2_f(fConst92);
		fConst119 = (1.0f / fConst118);
		fConst120 = (2.0f * (1.0f - fConst119));
		fConst121 = (((fConst93 + -1.24697959f) / fConst92) + 1.0f);
		fConst122 = (((fConst93 + -0.445041865f) / fConst92) + 1.0f);
		fConst123 = (0.0f - (2.0f / fConst118));
		fConst124 = (1.0f / (fConst92 * fConst97));
		fConst125 = (0.0f - fConst124);
		fConst126 = (fConst116 / fConst97);
		fConst127 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst85))));
		fConst128 = (((fConst86 - fConst88) / fConst85) + 1.0f);
		fConst129 = (((fConst86 + fConst90) / fConst85) + 1.0f);
		fConst130 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst78))));
		fConst131 = (((fConst79 - fConst81) / fConst78) + 1.0f);
		fConst132 = (((fConst79 + fConst83) / fConst78) + 1.0f);
		fConst133 = (((fConst72 - fConst74) / fConst71) + 1.0f);
		fConst134 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst71))));
		fConst135 = (((fConst72 + fConst76) / fConst71) + 1.0f);
		fConst136 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst64))));
		fConst137 = (((fConst65 - fConst67) / fConst64) + 1.0f);
		fConst138 = (((fConst65 + fConst69) / fConst64) + 1.0f);
		fConst139 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst56))));
		fConst140 = (((fConst57 - fConst59) / fConst56) + 1.0f);
		fConst141 = (((fConst57 - fConst61) / fConst56) + 1.0f);
		fConst142 = (((fConst50 - fConst52) / fConst49) + 1.0f);
		fConst143 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst49))));
		fConst144 = (((fConst50 + fConst54) / fConst49) + 1.0f);
		fConst145 = (((fConst43 - fConst45) / fConst42) + 1.0f);
		fConst146 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst42))));
		fConst147 = (((fConst43 - fConst47) / fConst42) + 1.0f);
		fConst148 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst35))));
		fConst149 = (((fConst36 - fConst38) / fConst35) + 1.0f);
		fConst150 = (((fConst36 + fConst40) / fConst35) + 1.0f);
		fConst151 = (((fConst29 - fConst31) / fConst28) + 1.0f);
		fConst152 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
		fConst153 = (((fConst29 + fConst33) / fConst28) + 1.0f);
		fConst154 = (((fConst19 - fConst21) / fConst18) + 1.0f);
		fConst155 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst18))));
		fConst156 = (((fConst19 + fConst25) / fConst18) + 1.0f);
		fConst157 = (0.0f - fConst24);
		fConst158 = (1.0f - fConst14);
		fConst159 = (fConst158 / fConst23);
		fConst160 = (((fConst14 + -1.0f) / fConst13) + 1.0f);
		fConst161 = (1.0f / fConst16);
		fConst162 = (2.0f * (1.0f - fConst161));
		fConst163 = (1.0f / fConst23);
		fConst164 = std::tan((18849.5566f / fConst0));
		fConst165 = (1.0f / fConst164);
		fConst166 = (3141.59277f / (fConst0 * std::sin(fConst27)));
		fConst167 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst164))));
		fConst168 = std::tan((219.911484f / fConst0));
		fConst169 = (1.0f / fConst168);
		fConst170 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
		fConst171 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst168))));
		fConst172 = std::tan((3769.91113f / fConst0));
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst172))));
		fConst174 = (1.0f / fConst172);
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

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec10[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec12[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec11[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec13[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec9[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec17[l7] = 0.0f;

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
			fRec16[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;

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
			fRec14[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec8[l19] = 0.0f;

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
			fRec7[l25] = 0.0f;

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
			fRec6[l29] = 0.0f;

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
			fRec34[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec33[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec35[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec0[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec37[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec36[l46] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry24 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry25 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry39 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry37 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry41 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry42 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry38 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry40 = value + 1.755841e-04f; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry8 = value + -8.160828e+00f; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry3 = value + 2.438393e-02f; }
	void set_tetrode_plate_clip_corner(FAUSTFLOAT value) { fEntry47 = value + 1.314022e+00f; }
	void set_tetrode_plate_comp_depth(FAUSTFLOAT value) { fEntry4 = value + 1.143102e-01f; }
	void set_tetrode_plate_comp_level(FAUSTFLOAT value) { fEntry6 = value + -1.456958e-01f; }
	void set_tetrode_plate_comp_ratio(FAUSTFLOAT value) { fEntry46 = value + -4.890451e+00f; }
	void set_tetrode_plate_comp_tau(FAUSTFLOAT value) { fEntry5 = value + 1.001772e+00f; }
	void set_tetrode_plate_cross_corner(FAUSTFLOAT value) { fEntry48 = value + 8.671871e-01f; }
	void set_tetrode_plate_drift_depth(FAUSTFLOAT value) { fEntry43 = value + 1.772658e-01f; }
	void set_tetrode_plate_drift_level(FAUSTFLOAT value) { fEntry45 = value + 5.447352e-01f; }
	void set_tetrode_plate_drift_tau(FAUSTFLOAT value) { fEntry44 = value + -2.144346e-01f; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry7 = value + 5.277323e-01f; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry21 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry20 = value + 2.097559e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry28 = value + 3.350247e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry29 = value + 1.208423e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry27 = value + 1.499044e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry26 = value + -1.358095e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry22 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry17 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry30 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry18 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry23 = value + -1.772999e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry14 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry16 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry34 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry15 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry19 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry31 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry33 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry32 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry36 = value + 0.000000e+00f; }
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
		float fSlow5 = std::exp(((2.30258512f * (float(fEntry4) + 1.0f)) + -2.30258512f));
		float fSlow6 = std::exp(((3.45387769f * (float(fEntry5) + 1.0f)) + -6.90775537f));
		float fSlow7 = (1.0f / ((fConst0 * fSlow6) + 1.0f));
		float fSlow8 = (100.0f * (1.0f - (float(fEntry6) + 1.0f)));
		float fSlow9 = (0.0f - fSlow8);
		float fSlow10 = std::exp(((4.60517025f * (float(fEntry7) + 1.0f)) + -4.60517025f));
		float fSlow11 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry8) + 1.0f)) + -2.30258512f))));
		float fSlow12 = (1.0f / fSlow11);
		float fSlow13 = (fSlow12 + 1.0f);
		float fSlow14 = (0.0f - (1.0f / (fSlow13 * fSlow11)));
		float fSlow15 = (float(fEntry9) + 1.0f);
		float fSlow16 = (fSlow2 * std::exp((3.45387769f * fSlow15)));
		float fSlow17 = float(fEntry10);
		int iSlow18 = (fSlow17 < 0.0f);
		float fSlow19 = std::tan((fConst1 * ((iSlow18?(1500.0f * fSlow17):0.0f) + 2000.0f)));
		float fSlow20 = (1.0f / fSlow19);
		float fSlow21 = (1.0f - fSlow20);
		float fSlow22 = float(fEntry11);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (1.0f - (0.5f * fSlow23));
		float fSlow25 = std::tan((fConst1 * ((400.0f * fSlow24) + (25.0f * fSlow23))));
		float fSlow26 = (1.0f / fSlow25);
		float fSlow27 = (fSlow26 + 1.0f);
		float fSlow28 = (0.0f - (1.0f / (fSlow25 * fSlow27)));
		float fSlow29 = float(fEntry12);
		float fSlow30 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow29) + -3.0f));
		float fSlow31 = ((float(fEntry13) + 1.0f) + 1.0f);
		float fSlow32 = AmpMono_faustpower2_f((0.5f * fSlow31));
		float fSlow33 = (0.5f * (fSlow30 / fSlow32));
		float fSlow34 = std::exp(((2.30258512f * (float(fEntry14) + 1.0f)) + -2.30258512f));
		float fSlow35 = std::exp(((3.45387769f * (float(fEntry15) + 1.0f)) + -6.90775537f));
		float fSlow36 = (1.0f / ((fConst0 * fSlow35) + 1.0f));
		float fSlow37 = (100.0f * (1.0f - (float(fEntry16) + 1.0f)));
		float fSlow38 = (0.0f - fSlow37);
		float fSlow39 = (1.0f - (float(fEntry17) + 1.0f));
		float fSlow40 = (1.0f - (float(fEntry18) + 1.0f));
		float fSlow41 = std::exp(((4.60517025f * (float(fEntry19) + 1.0f)) + -4.60517025f));
		float fSlow42 = ((100.0f * (fSlow39 - fSlow40)) + fSlow41);
		float fSlow43 = (float(fEntry20) + 1.0f);
		float fSlow44 = (fSlow43 - (float(fEntry21) + 1.0f));
		float fSlow45 = (2.5f * fSlow44);
		float fSlow46 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f))));
		float fSlow47 = (1.0f / fSlow46);
		float fSlow48 = (fSlow47 + 1.0f);
		float fSlow49 = (0.0f - (1.0f / (fSlow46 * fSlow48)));
		float fSlow50 = std::exp(((3.45387769f * (float(fEntry23) + 1.0f)) + -2.30258512f));
		float fSlow51 = (0.294117659f / fSlow41);
		float fSlow52 = (fSlow32 / fSlow2);
		float fSlow53 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow29) + -1.0f));
		float fSlow54 = (1.0f - (0.5f * fSlow53));
		float fSlow55 = (float(fEntry25) + 1.0f);
		float fSlow56 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry24) + 1.0f)))))) * std::exp((3.45387769f * fSlow55)));
		float fSlow57 = (1.0f / fSlow48);
		float fSlow58 = (1.0f - fSlow47);
		float fSlow59 = (fSlow56 / fSlow46);
		float fSlow60 = std::exp(((3.45387769f * (float(fEntry26) + 1.0f)) + -13.8155107f));
		float fSlow61 = (1.0f / ((fConst0 * (fSlow60 * std::exp(((6.90775537f * (float(fEntry27) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow62 = (1.0f - fSlow61);
		float fSlow63 = (1.0f / ((fConst0 * fSlow60) + 1.0f));
		float fSlow64 = (5.0f * (1.0f - (float(fEntry28) + 1.0f)));
		float fSlow65 = (1.0f / ((fConst0 * (fSlow60 * std::exp(((5.75646257f * (float(fEntry29) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow66 = (1.0f - fSlow65);
		float fSlow67 = (0.117647059f / fSlow43);
		float fSlow68 = std::exp(((4.60517025f * (float(fEntry30) + 1.0f)) + -2.30258512f));
		float fSlow69 = (fSlow68 + (100.0f * fSlow39));
		float fSlow70 = (0.294117659f / fSlow68);
		float fSlow71 = std::exp(((2.30258512f * (float(fEntry31) + 1.0f)) + -2.30258512f));
		float fSlow72 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry32) + 1.0f)) + -6.90775537f)))));
		float fSlow73 = (1.0f - fSlow72);
		float fSlow74 = (100.0f * (1.0f - (float(fEntry33) + 1.0f)));
		float fSlow75 = (0.0f - fSlow74);
		float fSlow76 = (100.0f * fSlow40);
		float fSlow77 = (1.0f / ((fConst0 * (fSlow35 * std::exp((1.15129256f * (float(fEntry34) + 1.0f))))) + 1.0f));
		float fSlow78 = (1.0f - fSlow77);
		float fSlow79 = (1.0f - (float(fEntry35) + 1.0f));
		float fSlow80 = (100.0f * (fSlow40 - fSlow79));
		float fSlow81 = (0.294117659f / fSlow50);
		float fSlow82 = (100.0f * fSlow79);
		float fSlow83 = (fSlow53 / fSlow31);
		float fSlow84 = (0.5f * (fSlow31 / fSlow2));
		float fSlow85 = (fSlow46 * fSlow2);
		float fSlow86 = (0.5f * (fSlow31 / fSlow85));
		float fSlow87 = (1.0f / fSlow85);
		float fSlow88 = (fSlow65 + -1.0f);
		float fSlow89 = (fSlow77 + -1.0f);
		float fSlow90 = (fSlow32 / fSlow85);
		float fSlow91 = (1.0f - (0.5f * fSlow30));
		float fSlow92 = (5.0f * fSlow55);
		int iSlow93 = (fSlow92 < 9.0f);
		int iSlow94 = (fSlow92 < 8.0f);
		int iSlow95 = (fSlow92 < 7.0f);
		int iSlow96 = (fSlow92 < 6.0f);
		int iSlow97 = (fSlow92 < 5.0f);
		int iSlow98 = (fSlow92 < 4.0f);
		int iSlow99 = (fSlow92 < 3.0f);
		int iSlow100 = (fSlow92 < 2.0f);
		int iSlow101 = (fSlow92 < 1.0f);
		float fSlow102 = std::pow(10.0f, (0.0500000007f * (iSlow93?(iSlow94?(iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?((fSlow92 < 0.0f)?0.0324000008f:(iSlow101?(0.0324000008f - (29.9619999f * fSlow55)):-5.96000004f)):(iSlow100?(-5.96000004f - (5.94000006f * (fSlow92 + -1.0f))):-11.8999996f)):(iSlow99?(-11.8999996f - (5.9000001f * (fSlow92 + -2.0f))):-17.7999992f)):(iSlow98?(-17.7999992f - (5.80000019f * (fSlow92 + -3.0f))):-23.6000004f)):(iSlow97?(-23.6000004f - (5.19999981f * (fSlow92 + -4.0f))):-28.7999992f)):(iSlow96?(-28.7999992f - (3.0999999f * (0.0f - (5.0f * (1.0f - fSlow55))))):-31.8999996f)):(iSlow95?(-31.8999996f - (1.10000002f * (fSlow92 + -6.0f))):-33.0f)):(iSlow94?((0.200000003f * (fSlow92 + -7.0f)) + -33.0f):-32.7999992f)):(iSlow93?((0.400000006f * (fSlow92 + -8.0f)) + -32.7999992f):-32.4000015f)):((fSlow92 < 10.0f)?((0.200000003f * (fSlow92 + -9.0f)) + -32.4000015f):-32.2000008f))));
		float fSlow103 = (1.0f / fSlow27);
		float fSlow104 = (1.0f - fSlow26);
		float fSlow105 = (1.0f / (fSlow25 * fSlow2));
		float fSlow106 = std::pow(10.0f, (0.0500000007f * (fSlow22 * ((18.0f * fSlow24) + (4.5f * fSlow23)))));
		float fSlow107 = float(fEntry36);
		float fSlow108 = ((10.0f * fSlow107) + -14.0f);
		int iSlow109 = (fSlow108 > 0.0f);
		float fSlow110 = ((fSlow107 * ((fSlow22 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow111 = ((fConst12 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow108)))) * fSlow110);
		float fSlow112 = (fConst12 * fSlow110);
		float fSlow113 = (iSlow109?fSlow112:fSlow111);
		float fSlow114 = ((fConst11 * (fConst11 - fSlow113)) + 1.0f);
		float fSlow115 = ((fConst11 * (fConst11 + fSlow113)) + 1.0f);
		float fSlow116 = (iSlow109?fSlow111:fSlow112);
		float fSlow117 = ((fConst11 * (fConst11 + fSlow116)) + 1.0f);
		float fSlow118 = ((fConst11 * (fConst11 - fSlow116)) + 1.0f);
		float fSlow119 = (fSlow20 + 1.0f);
		float fSlow120 = (0.0f - (1.0f / (fSlow19 * fSlow119)));
		float fSlow121 = (fSlow19 * fSlow115);
		float fSlow122 = std::pow(10.0f, ((0.0500000007f * fSlow17) * (iSlow18?18.0f:9.0f)));
		float fSlow123 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow124 = (1.0f / fSlow13);
		float fSlow125 = (1.0f - fSlow12);
		float fSlow126 = std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -9.2103405f));
		float fSlow127 = (1.0f / ((fConst0 * fSlow126) + 1.0f));
		float fSlow128 = (100.0f * (1.0f - (float(fEntry39) + 1.0f)));
		float fSlow129 = std::exp((0.0f - (fConst6 / std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -9.2103405f)))));
		float fSlow130 = (1.0f - fSlow129);
		float fSlow131 = (250.0f * (float(fEntry41) + 1.0f));
		float fSlow132 = ((1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -4.60517025f)) * fSlow126)) + 1.0f)) + -1.0f);
		float fSlow133 = std::exp(((2.30258512f * (float(fEntry43) + 1.0f)) + -2.30258512f));
		float fSlow134 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry44) + 1.0f)) + -6.90775537f)))));
		float fSlow135 = (1.0f - fSlow134);
		float fSlow136 = std::exp((0.0f - (10.0f * (1.0f - (float(fEntry45) + 1.0f)))));
		float fSlow137 = (1.0f - (1.0f / ((fConst0 * (fSlow6 * std::exp((1.15129256f * (float(fEntry46) + 1.0f))))) + 1.0f)));
		float fSlow138 = std::exp(((3.45387769f * (float(fEntry47) + 1.0f)) + -2.30258512f));
		float fSlow139 = (0.294117659f / fSlow138);
		float fSlow140 = std::exp(((3.45387769f * (float(fEntry48) + 1.0f)) + -2.30258512f));
		float fSlow141 = (0.294117659f / fSlow140);
		float fSlow142 = (5.0f * fSlow15);
		int iSlow143 = (fSlow142 < 9.0f);
		int iSlow144 = (fSlow142 < 8.0f);
		int iSlow145 = (fSlow142 < 7.0f);
		int iSlow146 = (fSlow142 < 6.0f);
		int iSlow147 = (fSlow142 < 5.0f);
		int iSlow148 = (fSlow142 < 4.0f);
		int iSlow149 = (fSlow142 < 3.0f);
		int iSlow150 = (fSlow142 < 2.0f);
		int iSlow151 = (fSlow142 < 1.0f);
		float fSlow152 = std::pow(10.0f, (0.0500000007f * (iSlow143?(iSlow144?(iSlow145?(iSlow146?(iSlow147?(iSlow148?(iSlow149?(iSlow150?(iSlow151?((fSlow142 < 0.0f)?9.60000038f:(iSlow151?(9.60000038f - (29.8999996f * fSlow15)):3.61999989f)):(iSlow150?(3.61999989f - (5.94999981f * (fSlow142 + -1.0f))):-2.32999992f)):(iSlow149?(-2.32999992f - (5.86000013f * (fSlow142 + -2.0f))):-8.18999958f)):(iSlow148?(-8.18999958f - (5.61000013f * (fSlow142 + -3.0f))):-13.8000002f)):(iSlow147?(-13.8000002f - (4.4000001f * (fSlow142 + -4.0f))):-18.2000008f)):(iSlow146?(-18.2000008f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow15))))):-20.3999996f)):(iSlow145?(-20.3999996f - (0.400000006f * (fSlow142 + -6.0f))):-20.7999992f)):(iSlow144?((0.300000012f * (fSlow142 + -7.0f)) + -20.7999992f):-20.5f)):(iSlow143?((0.600000024f * (fSlow142 + -8.0f)) + -20.5f):-19.8999996f)):((fSlow142 < 10.0f)?((1.20000005f * (fSlow142 + -9.0f)) + -19.8999996f):-18.7000008f))));
		float fSlow153 = float(fEntry49);
		float fSlow154 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow153)));
		float fSlow155 = float(fEntry50);
		float fSlow156 = std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow155))));
		float fSlow157 = (15.0f * fSlow155);
		int iSlow158 = (fSlow157 > 0.0f);
		float fSlow159 = (fConst166 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow157))));
		float fSlow160 = (iSlow158?fConst166:fSlow159);
		float fSlow161 = ((fConst165 * (fConst165 - fSlow160)) + 1.0f);
		float fSlow162 = ((fConst165 * (fConst165 + fSlow160)) + 1.0f);
		float fSlow163 = (iSlow158?fSlow159:fConst166);
		float fSlow164 = ((fConst165 * (fConst165 + fSlow163)) + 1.0f);
		float fSlow165 = ((fConst165 * (fConst165 - fSlow163)) + 1.0f);
		float fSlow166 = (0.0f - (10.0f * fSlow153));
		int iSlow167 = (fSlow166 > 0.0f);
		float fSlow168 = (fConst170 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow166))));
		float fSlow169 = (iSlow167?fConst170:fSlow168);
		float fSlow170 = ((fConst169 * (fConst169 - fSlow169)) + 1.0f);
		float fSlow171 = ((fConst169 * (fConst169 + fSlow169)) + 1.0f);
		float fSlow172 = (iSlow167?fSlow168:fConst170);
		float fSlow173 = ((fConst169 * (fConst169 - fSlow172)) + 1.0f);
		float fSlow174 = ((fConst169 * (fConst169 + fSlow172)) + 1.0f);
		float fSlow175 = (0.0f - (17.0f * fSlow153));
		int iSlow176 = (fSlow175 > 0.0f);
		float fSlow177 = (fConst175 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow175))));
		float fSlow178 = (iSlow176?fConst175:fSlow177);
		float fSlow179 = ((fConst174 * (fConst174 - fSlow178)) + 1.0f);
		float fSlow180 = ((fConst174 * (fConst174 + fSlow178)) + 1.0f);
		float fSlow181 = (iSlow176?fSlow177:fConst175);
		float fSlow182 = ((fConst174 * (fConst174 + fSlow181)) + 1.0f);
		float fSlow183 = ((fConst174 * (fConst174 - fSlow181)) + 1.0f);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow56 * fTemp0);
			fRec10[0] = ((fSlow49 * fVec0[1]) - (fSlow57 * ((fSlow58 * fRec10[1]) - (fSlow59 * fTemp0))));
			fRec12[0] = ((fSlow63 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow64 + fRec10[0])) - fRec12[1]))) + (fSlow66 * fRec12[1]));
			fRec11[0] = ((fSlow62 * fRec11[1]) + (fSlow61 * fRec12[0]));
			float fTemp1 = (fSlow45 + (fRec10[0] - fRec11[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = ((std::fabs(fTemp2) + -2.0f) * fTemp2);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) - (2.5f * (fSlow44 - (fSlow43 * (fTemp3 * (std::fabs(fTemp3) + -2.0f))))))) - fSlow69);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow70 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (std::fabs(fTemp5) + -2.0f);
			float fTemp7 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp4) + (fSlow68 * ((((std::fabs((fTemp5 * fTemp6)) + -2.0f) * fTemp5) * fTemp6) + 1.0f)))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow51 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (std::fabs(fTemp8) + -2.0f);
			float fTemp10 = (std::max<float>(0.0f, fTemp7) + (fSlow41 * (((fTemp8 * (std::fabs((fTemp8 * fTemp9)) + -2.0f)) * fTemp9) + 1.0f)));
			fRec13[0] = ((fSlow73 * (fSlow74 + std::max<float>(fSlow75, (fTemp10 - fSlow76)))) + (fSlow72 * fRec13[1]));
			float fTemp11 = (fSlow71 * fRec13[0]);
			fRec9[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp10 - fTemp11) - fSlow76)) - fRec9[1])))) + (fSlow78 * fRec9[1]));
			float fTemp12 = (fSlow34 * fRec9[0]);
			float fTemp13 = (fSlow50 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow80));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
			float fTemp16 = (((fTemp12 + std::min<float>(0.0f, fTemp13)) - (fSlow50 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) - fSlow82);
			fVec1[0] = (fSlow84 * fTemp16);
			fRec17[0] = ((fSlow49 * fVec1[1]) + (fSlow57 * ((fSlow86 * fTemp16) - (fSlow58 * fRec17[1]))));
			fRec19[0] = ((fSlow63 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow64 + fRec17[0])) - fRec19[1]))) + (fSlow66 * fRec19[1]));
			fRec18[0] = ((fSlow62 * fRec18[1]) + (fSlow61 * fRec19[0]));
			float fTemp17 = (fSlow45 + (fRec17[0] - fRec18[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow44 - (fSlow43 * (((std::fabs((fTemp19 * fTemp18)) + -2.0f) * fTemp19) * fTemp18)))))) - fSlow69);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow70 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow42 + ((fSlow68 * (((fTemp22 * (std::fabs((fTemp22 * fTemp21)) + -2.0f)) * fTemp21) + 1.0f)) + std::max<float>(0.0f, fTemp20))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow51 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (fTemp24 * (std::fabs(fTemp24) + -2.0f));
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow41 * ((fTemp25 * (std::fabs(fTemp25) + -2.0f)) + 1.0f)));
			fRec20[0] = ((fSlow73 * (fSlow74 + std::max<float>(fSlow75, (fTemp26 - fSlow76)))) + (fSlow72 * fRec20[1]));
			float fTemp27 = (fSlow71 * fRec20[0]);
			fRec16[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp26 - fTemp27) - fSlow76)) - fRec16[1])))) + (fSlow78 * fRec16[1]));
			float fTemp28 = (fSlow34 * fRec16[0]);
			float fTemp29 = (fSlow50 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow80));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (fTemp30 * (std::fabs(fTemp30) + -2.0f));
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow50 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow82);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec15[0] = ((fSlow49 * fVec2[1]) - (fSlow57 * ((fSlow58 * fRec15[1]) - (fSlow87 * fTemp32))));
			fRec22[0] = ((fSlow63 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow64 + fRec15[0])) - fRec22[1]))) - (fSlow88 * fRec22[1]));
			fRec21[0] = ((fSlow62 * fRec21[1]) + (fSlow61 * fRec22[0]));
			float fTemp33 = (fSlow45 + (fRec15[0] - fRec21[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow44 - (fSlow43 * ((fTemp34 * (std::fabs((fTemp34 * fTemp35)) + -2.0f)) * fTemp35)))))) - fSlow69);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow70 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = ((std::fabs(fTemp37) + -2.0f) * fTemp37);
			float fTemp39 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp36) + (fSlow68 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow51 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = ((std::fabs(fTemp40) + -2.0f) * fTemp40);
			float fTemp42 = ((fSlow41 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp39));
			fRec23[0] = ((fSlow73 * (fSlow74 + std::max<float>(fSlow75, (fTemp42 - fSlow76)))) + (fSlow72 * fRec23[1]));
			float fTemp43 = (fSlow71 * fRec23[0]);
			fRec14[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp42 - fTemp43) - fSlow76)) - fRec14[1])))) - (fSlow89 * fRec14[1]));
			float fTemp44 = (fSlow34 * fRec14[0]);
			float fTemp45 = (fSlow50 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow80));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (fTemp46 * (std::fabs(fTemp46) + -2.0f));
			float fTemp48 = ((fSlow54 * fTemp16) + (fSlow83 * (((fTemp44 + std::min<float>(0.0f, fTemp45)) - (fSlow50 * (1.0f - (fTemp47 * (std::fabs(fTemp47) + -2.0f))))) - fSlow82)));
			fVec3[0] = (fSlow52 * fTemp48);
			fRec8[0] = ((fSlow49 * fVec3[1]) - (fSlow57 * ((fSlow58 * fRec8[1]) - (fSlow90 * fTemp48))));
			fRec25[0] = ((fSlow66 * fRec25[1]) + (fSlow63 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow64 + fRec8[0])) - fRec25[1]))));
			fRec24[0] = ((fSlow62 * fRec24[1]) + (fSlow61 * fRec25[0]));
			float fTemp49 = (fSlow45 + (fRec8[0] - fRec24[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = (std::fabs(fTemp50) + -2.0f);
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow44 - (fSlow43 * (((std::fabs((fTemp50 * fTemp51)) + -2.0f) * fTemp50) * fTemp51)))))) - fSlow69);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow70 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (std::fabs(fTemp53) + -2.0f);
			float fTemp55 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp52) + (fSlow68 * ((((std::fabs((fTemp53 * fTemp54)) + -2.0f) * fTemp53) * fTemp54) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow51 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = ((fSlow41 * (((fTemp57 * (std::fabs((fTemp57 * fTemp56)) + -2.0f)) * fTemp56) + 1.0f)) + std::max<float>(0.0f, fTemp55));
			fRec26[0] = ((fSlow72 * fRec26[1]) + (fSlow73 * (fSlow74 + std::max<float>(fSlow75, (fTemp58 - fSlow76)))));
			float fTemp59 = (fSlow71 * fRec26[0]);
			fRec27[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp58 - fTemp59) - fSlow76)) - fRec27[1])))) + (fSlow78 * fRec27[1]));
			float fTemp60 = (fSlow34 * fRec27[0]);
			float fTemp61 = (fSlow50 + ((fTemp58 - (fTemp59 + fTemp60)) - fSlow80));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (fTemp62 * (std::fabs(fTemp62) + -2.0f));
			float fTemp64 = (((std::min<float>(0.0f, fTemp61) + fTemp60) - (fSlow50 * (1.0f - (fTemp63 * (std::fabs(fTemp63) + -2.0f))))) - fSlow82);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec7[0] = ((fSlow49 * fVec4[1]) - (fSlow57 * ((fSlow58 * fRec7[1]) - (fSlow87 * fTemp64))));
			fRec29[0] = ((fSlow63 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow64 + fRec7[0])) - fRec29[1]))) - (fSlow88 * fRec29[1]));
			fRec28[0] = ((fSlow61 * fRec29[0]) + (fSlow62 * fRec28[1]));
			float fTemp65 = (fSlow45 + (fRec7[0] - fRec28[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow67 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = ((std::fabs(fTemp66) + -2.0f) * fTemp66);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow44 - (fSlow43 * (fTemp67 * (std::fabs(fTemp67) + -2.0f))))))) - fSlow69);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow70 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow42 + (std::max<float>(0.0f, fTemp68) + (fSlow68 * (((fTemp70 * (std::fabs((fTemp70 * fTemp69)) + -2.0f)) * fTemp69) + 1.0f)))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow51 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = ((std::fabs(fTemp72) + -2.0f) * fTemp72);
			float fTemp74 = (std::max<float>(0.0f, fTemp71) + (fSlow41 * ((fTemp73 * (std::fabs(fTemp73) + -2.0f)) + 1.0f)));
			fRec30[0] = ((fSlow72 * fRec30[1]) + (fSlow73 * (fSlow74 + std::max<float>(fSlow75, (fTemp74 - fSlow76)))));
			float fTemp75 = (fSlow71 * fRec30[0]);
			fRec6[0] = ((fSlow36 * std::max<float>(0.0f, (fSlow37 + (std::max<float>(fSlow38, ((fTemp74 - fTemp75) - fSlow76)) - fRec6[1])))) + (fSlow78 * fRec6[1]));
			float fTemp76 = (fSlow34 * fRec6[0]);
			float fTemp77 = (fSlow50 + ((fTemp74 - (fTemp76 + fTemp75)) - fSlow80));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow81 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = ((std::fabs(fTemp78) + -2.0f) * fTemp78);
			float fTemp80 = (((fSlow33 * (((fTemp76 + std::min<float>(0.0f, fTemp77)) - (fSlow50 * (1.0f - (fTemp79 * (std::fabs(fTemp79) + -2.0f))))) - fSlow82)) + (fSlow91 * fTemp48)) * fSlow102);
			float fTemp81 = (fSlow3 * fTemp80);
			fVec5[0] = fTemp81;
			fRec5[0] = ((fSlow28 * fVec5[1]) - (fSlow103 * ((fSlow104 * fRec5[1]) - (fSlow105 * fTemp80))));
			fRec31[0] = (0.0f - (fSlow103 * ((fSlow104 * fRec31[1]) - (fVec5[1] + fTemp81))));
			float fTemp82 = (fRec5[0] + (fSlow106 * fRec31[0]));
			fVec6[0] = fTemp82;
			fRec4[0] = ((fConst5 * fVec6[1]) - (fConst7 * ((fConst8 * fRec4[1]) - (fConst3 * fTemp82))));
			float fTemp83 = (fConst10 * fRec3[1]);
			fRec3[0] = (fRec4[0] - ((fTemp83 + (fRec3[2] * fSlow114)) / fSlow115));
			float fTemp84 = (((fRec3[0] * fSlow117) + fTemp83) + (fRec3[2] * fSlow118));
			float fTemp85 = (fTemp84 / fSlow115);
			fVec7[0] = fTemp85;
			fRec2[0] = (0.0f - (((fSlow21 * fRec2[1]) - (fVec7[1] + fTemp85)) / fSlow119));
			fRec32[0] = ((fVec7[1] * fSlow120) - (((fSlow21 * fRec32[1]) - (fTemp84 / fSlow121)) / fSlow119));
			float fTemp86 = ((fSlow16 * (fRec2[0] + (fRec32[0] * fSlow122))) - fSlow123);
			fVec8[0] = fTemp86;
			fRec1[0] = ((fSlow14 * fVec8[1]) - (fSlow124 * ((fSlow125 * fRec1[1]) - (fSlow12 * fTemp86))));
			fRec34[0] = ((fSlow129 * fRec34[1]) + (fSlow130 * (fRec1[0] - fSlow131)));
			fRec33[0] = ((fSlow127 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow128 + ((fRec1[0] - fRec34[0]) - fSlow131))) - fRec33[1]))) - (fSlow132 * fRec33[1]));
			float fTemp87 = (fSlow10 * ((fRec1[0] - (fRec33[0] + fRec34[0])) - fSlow131));
			fRec35[0] = ((fSlow134 * fRec35[1]) + (fSlow135 * (std::max<float>(fSlow136, fTemp87) - fSlow136)));
			float fTemp88 = (fSlow133 * fRec35[0]);
			fRec0[0] = ((fSlow7 * std::max<float>(0.0f, (fSlow8 + (std::max<float>(fSlow9, (fTemp87 - fTemp88)) - fRec0[1])))) + (fSlow137 * fRec0[1]));
			float fTemp89 = (fSlow5 * (0.0f - fRec0[0]));
			float fTemp90 = (fSlow138 + ((fTemp87 + (-10.0f - (fTemp89 + fTemp88))) - fSlow4));
			float fTemp91 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp90))));
			float fTemp92 = (std::fabs(fTemp91) + -2.0f);
			float fTemp93 = (fSlow4 + (((fTemp89 + std::min<float>(0.0f, fTemp90)) + (10.0f - (fSlow138 * (1.0f - ((fTemp91 * (std::fabs((fTemp91 * fTemp92)) + -2.0f)) * fTemp92))))) - fSlow140));
			fRec37[0] = ((fSlow134 * fRec37[1]) + (fSlow135 * (std::max<float>(fSlow136, (0.0f - fTemp87)) - fSlow136)));
			float fTemp94 = (fTemp87 + (fSlow133 * fRec37[0]));
			fRec36[0] = ((fSlow7 * std::max<float>(0.0f, (fSlow8 + (std::max<float>(fSlow9, (0.0f - fTemp94)) - fRec36[1])))) + (fSlow137 * fRec36[1]));
			float fTemp95 = (fSlow5 * (0.0f - fRec36[0]));
			float fTemp96 = (fSlow138 + ((-10.0f - (fTemp94 + fTemp95)) - fSlow4));
			float fTemp97 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp96))));
			float fTemp98 = (fTemp97 * (std::fabs(fTemp97) + -2.0f));
			float fTemp99 = (fSlow4 + (((fTemp95 + std::min<float>(0.0f, fTemp96)) + (10.0f - (fSlow138 * (1.0f - (fTemp98 * (std::fabs(fTemp98) + -2.0f)))))) - fSlow140));
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp99))));
			float fTemp101 = (std::fabs(fTemp100) + -2.0f);
			float fTemp102 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp93))));
			float fTemp103 = (std::fabs(fTemp102) + -2.0f);
			float fTemp104 = (fSlow3 * ((std::max<float>(0.0f, fTemp93) - (std::max<float>(0.0f, fTemp99) + (fSlow140 * ((((fTemp100 * (std::fabs((fTemp100 * fTemp101)) + -2.0f)) * fTemp101) + 1.0f) - ((((std::fabs((fTemp103 * fTemp102)) + -2.0f) * fTemp103) * fTemp102) + 1.0f))))) * fSlow152));
			fRec60[0] = (fTemp104 - (fConst109 * ((fConst110 * fRec60[2]) + (fConst111 * fRec60[1]))));
			fRec59[0] = ((fConst109 * ((fConst108 * fRec60[2]) + ((fConst108 * fRec60[0]) + (fConst112 * fRec60[1])))) - (fConst106 * ((fConst113 * fRec59[2]) + (fConst111 * fRec59[1]))));
			float fTemp105 = ((fConst108 * fRec59[2]) + ((fConst112 * fRec59[1]) + (fConst108 * fRec59[0])));
			fVec9[0] = fTemp105;
			fRec58[0] = (0.0f - (fConst102 * ((fConst103 * fRec58[1]) - (fConst106 * (fTemp105 + fVec9[1])))));
			fRec57[0] = (fRec58[0] - (fConst101 * ((fConst114 * fRec57[2]) + (fConst115 * fRec57[1]))));
			float fTemp106 = ((fRec57[0] + (2.0f * fRec57[1])) + fRec57[2]);
			fVec10[0] = fTemp106;
			fRec56[0] = (fConst98 * ((fConst101 * (fVec10[1] + fTemp106)) - (fConst116 * fRec56[1])));
			fRec55[0] = (fRec56[0] - (fConst96 * ((fConst117 * fRec55[2]) + (fConst120 * fRec55[1]))));
			fRec54[0] = ((fConst96 * (fRec55[2] + (fRec55[0] + (2.0f * fRec55[1])))) - (fConst95 * ((fConst120 * fRec54[1]) + (fConst121 * fRec54[2]))));
			fRec53[0] = ((fConst95 * (fRec54[2] + (fRec54[0] + (2.0f * fRec54[1])))) - (fConst94 * ((fConst120 * fRec53[1]) + (fConst122 * fRec53[2]))));
			fRec64[0] = ((fConst101 * ((fConst124 * fTemp106) + (fConst125 * fVec10[1]))) - (fConst126 * fRec64[1]));
			fRec63[0] = (fRec64[0] - (fConst96 * ((fConst117 * fRec63[2]) + (fConst120 * fRec63[1]))));
			fRec62[0] = ((fConst96 * (((fConst123 * fRec63[1]) + (fConst119 * fRec63[0])) + (fConst119 * fRec63[2]))) - (fConst95 * ((fConst120 * fRec62[1]) + (fConst121 * fRec62[2]))));
			fRec61[0] = ((fConst95 * ((fConst119 * fRec62[2]) + ((fConst123 * fRec62[1]) + (fConst119 * fRec62[0])))) - (fConst94 * ((fConst120 * fRec61[1]) + (fConst122 * fRec61[2]))));
			float fTemp107 = (fConst127 * fRec52[1]);
			fRec52[0] = ((fConst94 * ((fRec53[2] + (fRec53[0] + (2.0f * fRec53[1]))) + (0.0316227749f * ((fConst119 * fRec61[2]) + ((fConst123 * fRec61[1]) + (fConst119 * fRec61[0])))))) - (fConst89 * (fTemp107 + (fConst128 * fRec52[2]))));
			float fTemp108 = (fConst130 * fRec51[1]);
			fRec51[0] = ((fConst89 * ((fConst91 * fRec52[2]) + (fTemp107 + (fConst129 * fRec52[0])))) - (fConst82 * (fTemp108 + (fConst131 * fRec51[2]))));
			float fTemp109 = (fConst134 * fRec50[1]);
			fRec50[0] = ((fConst82 * ((fConst84 * fRec51[2]) + ((fConst132 * fRec51[0]) + fTemp108))) - (fConst75 * ((fConst133 * fRec50[2]) + fTemp109)));
			float fTemp110 = (fConst136 * fRec49[1]);
			fRec49[0] = ((fConst75 * ((fConst77 * fRec50[2]) + (fTemp109 + (fConst135 * fRec50[0])))) - (fConst68 * (fTemp110 + (fConst137 * fRec49[2]))));
			float fTemp111 = (fConst139 * fRec48[1]);
			fRec48[0] = ((fConst68 * ((fConst70 * fRec49[2]) + (fTemp110 + (fConst138 * fRec49[0])))) - (fConst60 * (fTemp111 + (fConst140 * fRec48[2]))));
			float fTemp112 = (fConst143 * fRec47[1]);
			fRec47[0] = ((fConst60 * (((fConst62 * fRec48[0]) + fTemp111) + (fConst141 * fRec48[2]))) - (fConst53 * ((fConst142 * fRec47[2]) + fTemp112)));
			float fTemp113 = (fConst146 * fRec46[1]);
			fRec46[0] = ((fConst53 * ((fConst55 * fRec47[2]) + (fTemp112 + (fConst144 * fRec47[0])))) - (fConst46 * ((fConst145 * fRec46[2]) + fTemp113)));
			float fTemp114 = (fConst148 * fRec45[1]);
			fRec45[0] = ((fConst46 * (((fConst48 * fRec46[0]) + fTemp113) + (fConst147 * fRec46[2]))) - (fConst39 * (fTemp114 + (fConst149 * fRec45[2]))));
			float fTemp115 = (fConst152 * fRec44[1]);
			fRec44[0] = ((fConst39 * ((fConst41 * fRec45[2]) + (fTemp114 + (fConst150 * fRec45[0])))) - (fConst32 * ((fConst151 * fRec44[2]) + fTemp115)));
			float fTemp116 = (fConst155 * fRec43[1]);
			fRec43[0] = ((fConst32 * ((fConst34 * fRec44[2]) + (fTemp115 + (fConst153 * fRec44[0])))) - (fConst22 * ((fConst154 * fRec43[2]) + fTemp116)));
			float fTemp117 = ((fConst26 * fRec43[2]) + ((fConst156 * fRec43[0]) + fTemp116));
			fVec11[0] = fTemp117;
			fRec42[0] = ((fConst22 * ((fConst24 * fTemp117) + (fConst157 * fVec11[1]))) - (fConst159 * fRec42[1]));
			fRec41[0] = (fRec42[0] - (fConst15 * ((fConst160 * fRec41[2]) + (fConst162 * fRec41[1]))));
			fRec66[0] = (0.0f - (fConst163 * ((fConst158 * fRec66[1]) - (fConst22 * (fTemp117 + fVec11[1])))));
			fRec65[0] = (fRec66[0] - (fConst15 * ((fConst160 * fRec65[2]) + (fConst162 * fRec65[1]))));
			float fTemp118 = (fConst167 * fRec40[1]);
			fRec40[0] = ((fConst15 * ((((fConst17 * fRec41[1]) + (fConst161 * fRec41[0])) + (fConst161 * fRec41[2])) + (fSlow156 * ((fRec65[0] + (2.0f * fRec65[1])) + fRec65[2])))) - (((fRec40[2] * fSlow161) + fTemp118) / fSlow162));
			float fTemp119 = (fConst171 * fRec39[1]);
			fRec39[0] = (((((fRec40[0] * fSlow164) + fTemp118) + (fRec40[2] * fSlow165)) / fSlow162) - (((fSlow170 * fRec39[2]) + fTemp119) / fSlow171));
			float fTemp120 = (fConst173 * fRec38[1]);
			fRec38[0] = ((((fRec39[2] * fSlow173) + (fTemp119 + (fRec39[0] * fSlow174))) / fSlow171) - ((fTemp120 + (fSlow179 * fRec38[2])) / fSlow180));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fSlow154 * ((((fRec38[0] * fSlow182) + fTemp120) + (fSlow183 * fRec38[2])) / fSlow180)):fTemp104)));
			fVec0[1] = fVec0[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec9[1] = fRec9[0];
			fVec1[1] = fVec1[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec20[1] = fRec20[0];
			fRec16[1] = fRec16[0];
			fVec2[1] = fVec2[0];
			fRec15[1] = fRec15[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fRec14[1] = fRec14[0];
			fVec3[1] = fVec3[0];
			fRec8[1] = fRec8[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec27[1] = fRec27[0];
			fVec4[1] = fVec4[0];
			fRec7[1] = fRec7[0];
			fRec29[1] = fRec29[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec6[1] = fRec6[0];
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
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec35[1] = fRec35[0];
			fRec0[1] = fRec0[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
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
