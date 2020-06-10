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
	FAUSTFLOAT fEntry26;
	float fVec0[2];
	float fRec12[2];
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	float fRec14[2];
	float fRec13[2];
	FAUSTFLOAT fEntry31;
	float fConst6;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	float fRec15[2];
	FAUSTFLOAT fEntry34;
	float fRec16[2];
	FAUSTFLOAT fEntry35;
	float fVec1[2];
	float fRec11[2];
	float fRec18[2];
	float fRec17[2];
	float fRec19[2];
	float fRec10[2];
	float fVec2[2];
	float fRec9[2];
	float fRec21[2];
	float fRec20[2];
	float fRec22[2];
	float fRec23[2];
	float fVec3[2];
	float fRec8[2];
	float fRec25[2];
	float fRec24[2];
	float fRec26[2];
	float fRec7[2];
	float fVec4[2];
	float fRec6[2];
	float fRec28[2];
	float fRec27[2];
	float fRec29[2];
	float fRec30[2];
	float fVec5[2];
	float fRec5[2];
	float fRec31[2];
	float fVec6[2];
	float fConst7;
	float fConst8;
	float fRec4[2];
	float fConst9;
	float fConst10;
	FAUSTFLOAT fEntry36;
	float fConst11;
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
	float fRec33[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fRec34[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fRec35[2];
	FAUSTFLOAT fEntry46;
	float fRec0[2];
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec36[2];
	float fRec37[2];
	float fVec9[2];
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
	float fRec60[2];
	float fRec59[2];
	float fConst132;
	float fConst133;
	float fRec58[2];
	float fConst134;
	float fConst135;
	float fRec57[3];
	float fConst136;
	float fRec56[3];
	float fConst137;
	float fRec55[3];
	float fConst138;
	float fRec54[3];
	float fConst139;
	float fRec53[3];
	float fRec66[2];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fConst140;
	float fRec52[3];
	float fConst141;
	float fConst142;
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec51[3];
	float fConst146;
	float fConst147;
	float fRec50[3];
	float fConst148;
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec49[3];
	float fConst153;
	float fConst154;
	float fRec48[3];
	float fConst155;
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec47[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fConst162;
	float fRec46[3];
	float fConst163;
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec45[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec44[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec43[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec42[3];
	float fConst178;
	float fConst179;
	float fRec41[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec40[3];
	float fConst185;
	float fConst186;
	float fRec39[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec38[3];
	float fConst193;

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
		fConst13 = std::tan((5574.98535f / fConst0));
		fConst14 = (1.0f / fConst13);
		fConst15 = (fConst0 * std::sin((11149.9707f / fConst0)));
		fConst16 = (4376.67188f / fConst15);
		fConst17 = (((fConst14 + fConst16) / fConst13) + 1.0f);
		fConst18 = (0.144011721f / fConst17);
		fConst19 = (2760.92456f / fConst15);
		fConst20 = (((fConst14 - fConst19) / fConst13) + 1.0f);
		fConst21 = std::tan((4288.271f / fConst0));
		fConst22 = (1.0f / fConst21);
		fConst23 = (fConst0 * std::sin((8576.54199f / fConst0)));
		fConst24 = (326.939972f / fConst23);
		fConst25 = (1.0f / (((fConst22 + fConst24) / fConst21) + 1.0f));
		fConst26 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst21))));
		fConst27 = std::tan((3537.37793f / fConst0));
		fConst28 = (1.0f / fConst27);
		fConst29 = (fConst0 * std::sin((7074.75586f / fConst0)));
		fConst30 = (642.945251f / fConst29);
		fConst31 = (1.0f / (((fConst28 + fConst30) / fConst27) + 1.0f));
		fConst32 = (270.569763f / fConst29);
		fConst33 = (((fConst28 + fConst32) / fConst27) + 1.0f);
		fConst34 = std::tan((3081.90234f / fConst0));
		fConst35 = (1.0f / fConst34);
		fConst36 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst37 = (486.410919f / fConst36);
		fConst38 = (1.0f / (((fConst35 + fConst37) / fConst34) + 1.0f));
		fConst39 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst34))));
		fConst40 = std::tan((2592.47217f / fConst0));
		fConst41 = (1.0f / fConst40);
		fConst42 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst43 = (317.628265f / fConst42);
		fConst44 = (1.0f / (((fConst41 + fConst43) / fConst40) + 1.0f));
		fConst45 = (148.323349f / fConst42);
		fConst46 = (((fConst41 + fConst45) / fConst40) + 1.0f);
		fConst47 = std::tan((1891.23853f / fConst0));
		fConst48 = (1.0f / fConst47);
		fConst49 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst50 = (265.978119f / fConst49);
		fConst51 = (1.0f / (((fConst48 + fConst50) / fConst47) + 1.0f));
		fConst52 = (116.345184f / fConst49);
		fConst53 = (((fConst48 + fConst52) / fConst47) + 1.0f);
		fConst54 = std::tan((21179.4824f / fConst0));
		fConst55 = (1.0f / fConst54);
		fConst56 = (fConst0 * std::sin((42358.9648f / fConst0)));
		fConst57 = (7223.21826f / fConst56);
		fConst58 = (1.0f / (((fConst55 + fConst57) / fConst54) + 1.0f));
		fConst59 = (1059.12756f / fConst56);
		fConst60 = (((fConst55 - fConst59) / fConst54) + 1.0f);
		fConst61 = std::tan((15066.6357f / fConst0));
		fConst62 = (1.0f / fConst61);
		fConst63 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst64 = (11187.3662f / fConst63);
		fConst65 = (1.0f / (((fConst62 + fConst64) / fConst61) + 1.0f));
		fConst66 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst61))));
		fConst67 = std::tan((13437.668f / fConst0));
		fConst68 = (1.0f / fConst67);
		fConst69 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst70 = (13245.1885f / fConst69);
		fConst71 = (1.0f / (((fConst68 + fConst70) / fConst67) + 1.0f));
		fConst72 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst67))));
		fConst73 = std::tan((10058.502f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst76 = (4926.20459f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst79 = std::tan((8136.54736f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst82 = (966.024841f / fConst81);
		fConst83 = (1.0f / (((fConst80 + fConst82) / fConst79) + 1.0f));
		fConst84 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst79))));
		fConst85 = std::tan((8011.02734f / fConst0));
		fConst86 = (1.0f / fConst85);
		fConst87 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst88 = (1613.9762f / fConst87);
		fConst89 = (1.0f / (((fConst86 + fConst88) / fConst85) + 1.0f));
		fConst90 = (3097.15845f / fConst87);
		fConst91 = (((fConst86 + fConst90) / fConst85) + 1.0f);
		fConst92 = std::tan((9456.15234f / fConst0));
		fConst93 = (1.0f / fConst92);
		fConst94 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst95 = (2492.29883f / fConst94);
		fConst96 = (1.0f / (((fConst93 + fConst95) / fConst92) + 1.0f));
		fConst97 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst92))));
		fConst98 = std::tan((2827.43262f / fConst0));
		fConst99 = (1.0f / fConst98);
		fConst100 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst101 = (19634.3262f / fConst100);
		fConst102 = (1.0f / (((fConst99 + fConst101) / fConst98) + 1.0f));
		fConst103 = (106249.391f / fConst100);
		fConst104 = (((fConst99 - fConst103) / fConst98) + 1.0f);
		fConst105 = std::tan((375.293884f / fConst0));
		fConst106 = (1.0f / fConst105);
		fConst107 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst108 = (463.734222f / fConst107);
		fConst109 = (1.0f / (((fConst106 + fConst108) / fConst105) + 1.0f));
		fConst110 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst105))));
		fConst111 = std::tan((18369.8027f / fConst0));
		fConst112 = (1.0f / fConst111);
		fConst113 = (1.0f / (((fConst112 + 0.284629673f) / fConst111) + 1.0f));
		fConst114 = AmpMono_faustpower2_f(fConst111);
		fConst115 = (1.0f / fConst114);
		fConst116 = (1.0f / (((fConst112 + 0.830830038f) / fConst111) + 1.0f));
		fConst117 = (1.0f / (((fConst112 + 1.30972147f) / fConst111) + 1.0f));
		fConst118 = (0.0f - (2.0f / fConst114));
		fConst119 = (1.0f / (((fConst112 + 1.68250704f) / fConst111) + 1.0f));
		fConst120 = (1.0f / (((fConst112 + 1.91898596f) / fConst111) + 1.0f));
		fConst121 = (fConst112 + 1.0f);
		fConst122 = (0.0f - (1.0f / (fConst111 * fConst121)));
		fConst123 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst124 = (1.0f / (fConst123 + 1.0f));
		fConst125 = (1.0f - fConst123);
		fConst126 = std::tan((452.102844f / fConst0));
		fConst127 = (1.0f / fConst126);
		fConst128 = (fConst127 + 1.0f);
		fConst129 = (0.0f - (1.0f / (fConst126 * fConst128)));
		fConst130 = (1.0f / fConst128);
		fConst131 = (1.0f - fConst127);
		fConst132 = (1.0f / fConst121);
		fConst133 = (1.0f - fConst112);
		fConst134 = (2.0f * (1.0f - fConst115));
		fConst135 = (((fConst112 + -1.91898596f) / fConst111) + 1.0f);
		fConst136 = (((fConst112 + -1.68250704f) / fConst111) + 1.0f);
		fConst137 = (((fConst112 + -1.30972147f) / fConst111) + 1.0f);
		fConst138 = (((fConst112 + -0.830830038f) / fConst111) + 1.0f);
		fConst139 = (((fConst112 + -0.284629673f) / fConst111) + 1.0f);
		fConst140 = (((fConst106 - fConst108) / fConst105) + 1.0f);
		fConst141 = (3220.11475f / fConst107);
		fConst142 = (((fConst106 + fConst141) / fConst105) + 1.0f);
		fConst143 = (((fConst106 - fConst141) / fConst105) + 1.0f);
		fConst144 = (((fConst99 - fConst101) / fConst98) + 1.0f);
		fConst145 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst98))));
		fConst146 = (((fConst99 + fConst103) / fConst98) + 1.0f);
		fConst147 = (((fConst93 - fConst95) / fConst92) + 1.0f);
		fConst148 = (974.257141f / fConst94);
		fConst149 = (((fConst93 + fConst148) / fConst92) + 1.0f);
		fConst150 = (((fConst93 - fConst148) / fConst92) + 1.0f);
		fConst151 = (((fConst86 - fConst88) / fConst85) + 1.0f);
		fConst152 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst85))));
		fConst153 = (((fConst86 - fConst90) / fConst85) + 1.0f);
		fConst154 = (((fConst80 - fConst82) / fConst79) + 1.0f);
		fConst155 = (518.801147f / fConst81);
		fConst156 = (((fConst80 + fConst155) / fConst79) + 1.0f);
		fConst157 = (((fConst80 - fConst155) / fConst79) + 1.0f);
		fConst158 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst159 = (9024.73242f / fConst75);
		fConst160 = (((fConst74 + fConst159) / fConst73) + 1.0f);
		fConst161 = (((fConst74 - fConst159) / fConst73) + 1.0f);
		fConst162 = (((fConst68 - fConst70) / fConst67) + 1.0f);
		fConst163 = (4583.19189f / fConst69);
		fConst164 = (((fConst68 + fConst163) / fConst67) + 1.0f);
		fConst165 = (((fConst68 - fConst163) / fConst67) + 1.0f);
		fConst166 = (((fConst62 - fConst64) / fConst61) + 1.0f);
		fConst167 = (36783.4805f / fConst63);
		fConst168 = (((fConst62 + fConst167) / fConst61) + 1.0f);
		fConst169 = (((fConst62 - fConst167) / fConst61) + 1.0f);
		fConst170 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst54))));
		fConst171 = (((fConst55 - fConst57) / fConst54) + 1.0f);
		fConst172 = (((fConst55 + fConst59) / fConst54) + 1.0f);
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst47))));
		fConst174 = (((fConst48 - fConst50) / fConst47) + 1.0f);
		fConst175 = (((fConst48 - fConst52) / fConst47) + 1.0f);
		fConst176 = (((fConst41 - fConst43) / fConst40) + 1.0f);
		fConst177 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst40))));
		fConst178 = (((fConst41 - fConst45) / fConst40) + 1.0f);
		fConst179 = (((fConst35 - fConst37) / fConst34) + 1.0f);
		fConst180 = (183.178085f / fConst36);
		fConst181 = (((fConst35 + fConst180) / fConst34) + 1.0f);
		fConst182 = (((fConst35 - fConst180) / fConst34) + 1.0f);
		fConst183 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst27))));
		fConst184 = (((fConst28 - fConst30) / fConst27) + 1.0f);
		fConst185 = (((fConst28 - fConst32) / fConst27) + 1.0f);
		fConst186 = (((fConst22 - fConst24) / fConst21) + 1.0f);
		fConst187 = (190.645706f / fConst23);
		fConst188 = (((fConst22 + fConst187) / fConst21) + 1.0f);
		fConst189 = (((fConst22 - fConst187) / fConst21) + 1.0f);
		fConst190 = (1.0f / fConst17);
		fConst191 = (((fConst14 - fConst16) / fConst13) + 1.0f);
		fConst192 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst193 = (((fConst14 + fConst19) / fConst13) + 1.0f);

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

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec12[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec14[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec13[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec15[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec16[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fVec1[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec11[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec18[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec17[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec19[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec10[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec9[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec21[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec20[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec22[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec23[l17] = 0.0f;

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
			fRec7[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec4[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec6[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec28[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec27[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec29[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec30[l29] = 0.0f;

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
			fVec9[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec60[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec59[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec58[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec57[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec56[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec55[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec54[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec53[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec66[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec65[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec64[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec63[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec62[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec61[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec52[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec51[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec50[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec49[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec48[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec47[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec46[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec45[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec44[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec43[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec42[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec41[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec40[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec39[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec38[l76] = 0.0f;

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

	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
	void set_input_level(FAUSTFLOAT value) { fEntry25 = value + 0.000000e+00f; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
	void set_power_drive(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry26 = value + 0.000000e+00f; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry41 = value + 4.244063e-01f; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry37 = value + 4.772624e-02f; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry39 = value + -2.047726e+00f; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry42 = value + 6.149204e-01f; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry40 = value + -6.103268e-01f; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry38 = value + 1.755841e-04f; }
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
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry20 = value + 6.033136e-01f; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry19 = value + 2.097769e-01f; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry29 = value + 3.349904e-01f; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry30 = value + 1.208396e+00f; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry28 = value + 1.499057e+00f; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry27 = value + -1.358083e+00f; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry21 = value + 4.527706e-01f; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry16 = value + 2.382051e+00f; }
	void set_triode_plate_bias_corner(FAUSTFLOAT value) { fEntry18 = value + 4.922733e-01f; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry17 = value + -1.033060e+00f; }
	void set_triode_plate_comp_corner(FAUSTFLOAT value) { fEntry14 = value + -1.719012e-02f; }
	void set_triode_plate_comp_depth(FAUSTFLOAT value) { fEntry22 = value + -2.307199e-01f; }
	void set_triode_plate_comp_level(FAUSTFLOAT value) { fEntry24 = value + -1.426725e+00f; }
	void set_triode_plate_comp_offset(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00f; }
	void set_triode_plate_comp_ratio(FAUSTFLOAT value) { fEntry34 = value + 1.956985e+00f; }
	void set_triode_plate_comp_tau(FAUSTFLOAT value) { fEntry23 = value + -9.488480e-01f; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry15 = value + -7.082447e-02f; }
	void set_triode_plate_drift_depth(FAUSTFLOAT value) { fEntry31 = value + -8.273638e-01f; }
	void set_triode_plate_drift_level(FAUSTFLOAT value) { fEntry33 = value + 1.023179e-01f; }
	void set_triode_plate_drift_tau(FAUSTFLOAT value) { fEntry32 = value + -1.084916e+00f; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + 1.524034e+00f; }
	void set_ts_high(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
	void set_ts_low(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry36 = value + 0.000000e+00f; }
	void zero_all() {
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
		float fSlow25 = std::tan((fConst1 * ((25.0f * fSlow23) + (400.0f * fSlow24))));
		float fSlow26 = (1.0f / fSlow25);
		float fSlow27 = (fSlow26 + 1.0f);
		float fSlow28 = (0.0f - (1.0f / (fSlow25 * fSlow27)));
		float fSlow29 = float(fEntry12);
		float fSlow30 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow29) + -3.0f));
		float fSlow31 = ((float(fEntry13) + 1.0f) + 1.0f);
		float fSlow32 = AmpMono_faustpower2_f((0.5f * fSlow31));
		float fSlow33 = (0.5f * (fSlow30 / fSlow32));
		float fSlow34 = std::exp(((3.45387769f * (float(fEntry14) + 1.0f)) + -2.30258512f));
		float fSlow35 = std::exp(((4.60517025f * (float(fEntry15) + 1.0f)) + -4.60517025f));
		float fSlow36 = (0.294117659f / fSlow35);
		float fSlow37 = (1.0f - (float(fEntry16) + 1.0f));
		float fSlow38 = (1.0f - (float(fEntry17) + 1.0f));
		float fSlow39 = ((100.0f * (fSlow37 - fSlow38)) + fSlow35);
		float fSlow40 = std::exp(((4.60517025f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow41 = (0.294117659f / fSlow40);
		float fSlow42 = (float(fEntry19) + 1.0f);
		float fSlow43 = (fSlow42 - (float(fEntry20) + 1.0f));
		float fSlow44 = (2.5f * fSlow43);
		float fSlow45 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry21) + 1.0f)) + -2.30258512f))));
		float fSlow46 = (1.0f / fSlow45);
		float fSlow47 = (fSlow46 + 1.0f);
		float fSlow48 = (0.0f - (1.0f / (fSlow47 * fSlow45)));
		float fSlow49 = std::exp(((2.30258512f * (float(fEntry22) + 1.0f)) + -2.30258512f));
		float fSlow50 = std::exp(((3.45387769f * (float(fEntry23) + 1.0f)) + -6.90775537f));
		float fSlow51 = (1.0f / ((fConst0 * fSlow50) + 1.0f));
		float fSlow52 = (100.0f * (1.0f - (float(fEntry24) + 1.0f)));
		float fSlow53 = (0.0f - fSlow52);
		float fSlow54 = (1.0f / fSlow47);
		float fSlow55 = (fSlow45 * fSlow2);
		float fSlow56 = (fSlow32 / fSlow55);
		float fSlow57 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow29) + -1.0f));
		float fSlow58 = (fSlow57 / fSlow31);
		float fSlow59 = (0.5f * (fSlow31 / fSlow2));
		float fSlow60 = (0.294117659f / fSlow34);
		float fSlow61 = (float(fEntry26) + 1.0f);
		float fSlow62 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry25) + 1.0f)))))) * std::exp((3.45387769f * fSlow61)));
		float fSlow63 = (1.0f - fSlow46);
		float fSlow64 = (fSlow62 / fSlow45);
		float fSlow65 = std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -13.8155107f));
		float fSlow66 = (1.0f / ((fConst0 * (fSlow65 * std::exp(((6.90775537f * (float(fEntry28) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow67 = (1.0f - fSlow66);
		float fSlow68 = (1.0f / ((fConst0 * fSlow65) + 1.0f));
		float fSlow69 = (5.0f * (1.0f - (float(fEntry29) + 1.0f)));
		float fSlow70 = (1.0f / ((fConst0 * (fSlow65 * std::exp(((5.75646257f * (float(fEntry30) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow71 = (1.0f - fSlow70);
		float fSlow72 = (0.117647059f / fSlow42);
		float fSlow73 = ((100.0f * fSlow37) + fSlow40);
		float fSlow74 = std::exp(((2.30258512f * (float(fEntry31) + 1.0f)) + -2.30258512f));
		float fSlow75 = std::exp((0.0f - (fConst6 / std::exp(((3.45387769f * (float(fEntry32) + 1.0f)) + -6.90775537f)))));
		float fSlow76 = (1.0f - fSlow75);
		float fSlow77 = (100.0f * (1.0f - (float(fEntry33) + 1.0f)));
		float fSlow78 = (0.0f - fSlow77);
		float fSlow79 = (100.0f * fSlow38);
		float fSlow80 = (1.0f / ((fConst0 * (fSlow50 * std::exp((1.15129256f * (float(fEntry34) + 1.0f))))) + 1.0f));
		float fSlow81 = (fSlow80 + -1.0f);
		float fSlow82 = (1.0f - (float(fEntry35) + 1.0f));
		float fSlow83 = (100.0f * (fSlow38 - fSlow82));
		float fSlow84 = (100.0f * fSlow82);
		float fSlow85 = (0.5f * (fSlow31 / fSlow55));
		float fSlow86 = (fSlow70 + -1.0f);
		float fSlow87 = (1.0f / fSlow55);
		float fSlow88 = (1.0f - fSlow80);
		float fSlow89 = (1.0f - (0.5f * fSlow57));
		float fSlow90 = (fSlow32 / fSlow2);
		float fSlow91 = (1.0f - (0.5f * fSlow30));
		float fSlow92 = (5.0f * fSlow61);
		int iSlow93 = (fSlow92 < 9.0f);
		int iSlow94 = (fSlow92 < 8.0f);
		int iSlow95 = (fSlow92 < 7.0f);
		int iSlow96 = (fSlow92 < 6.0f);
		int iSlow97 = (fSlow92 < 5.0f);
		int iSlow98 = (fSlow92 < 4.0f);
		int iSlow99 = (fSlow92 < 3.0f);
		int iSlow100 = (fSlow92 < 2.0f);
		int iSlow101 = (fSlow92 < 1.0f);
		float fSlow102 = std::pow(10.0f, (0.0500000007f * (iSlow93?(iSlow94?(iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?((fSlow92 < 0.0f)?0.0324000008f:(iSlow101?(0.0324000008f - (29.9619999f * fSlow61)):-5.96000004f)):(iSlow100?(-5.96000004f - (5.94000006f * (fSlow92 + -1.0f))):-11.8999996f)):(iSlow99?(-11.8999996f - (5.9000001f * (fSlow92 + -2.0f))):-17.7999992f)):(iSlow98?(-17.7999992f - (5.80000019f * (fSlow92 + -3.0f))):-23.6000004f)):(iSlow97?(-23.6000004f - (5.19999981f * (fSlow92 + -4.0f))):-28.7999992f)):(iSlow96?(-28.7999992f - (3.0999999f * (0.0f - (5.0f * (1.0f - fSlow61))))):-31.8999996f)):(iSlow95?(-31.8999996f - (1.10000002f * (fSlow92 + -6.0f))):-33.0f)):(iSlow94?((0.200000003f * (fSlow92 + -7.0f)) + -33.0f):-32.7999992f)):(iSlow93?((0.400000006f * (fSlow92 + -8.0f)) + -32.7999992f):-32.4000015f)):((fSlow92 < 10.0f)?((0.200000003f * (fSlow92 + -9.0f)) + -32.4000015f):-32.2000008f))));
		float fSlow103 = (1.0f / fSlow27);
		float fSlow104 = (1.0f - fSlow26);
		float fSlow105 = (1.0f / (fSlow25 * fSlow2));
		float fSlow106 = std::pow(10.0f, (0.0500000007f * (fSlow22 * ((4.5f * fSlow23) + (18.0f * fSlow24)))));
		float fSlow107 = float(fEntry36);
		float fSlow108 = ((10.0f * fSlow107) + -14.0f);
		int iSlow109 = (fSlow108 > 0.0f);
		float fSlow110 = ((fSlow107 * ((fSlow22 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow111 = ((fConst11 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow108)))) * fSlow110);
		float fSlow112 = (fConst11 * fSlow110);
		float fSlow113 = (iSlow109?fSlow112:fSlow111);
		float fSlow114 = ((fConst10 * (fConst10 - fSlow113)) + 1.0f);
		float fSlow115 = ((fConst10 * (fConst10 + fSlow113)) + 1.0f);
		float fSlow116 = (iSlow109?fSlow111:fSlow112);
		float fSlow117 = ((fConst10 * (fConst10 + fSlow116)) + 1.0f);
		float fSlow118 = ((fConst10 * (fConst10 - fSlow116)) + 1.0f);
		float fSlow119 = (fSlow20 + 1.0f);
		float fSlow120 = (0.0f - (1.0f / (fSlow19 * fSlow119)));
		float fSlow121 = (fSlow19 * fSlow115);
		float fSlow122 = std::pow(10.0f, ((0.0500000007f * fSlow17) * (iSlow18?18.0f:9.0f)));
		float fSlow123 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow124 = (1.0f / fSlow13);
		float fSlow125 = (1.0f - fSlow12);
		float fSlow126 = std::exp((0.0f - (fConst6 / std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -9.2103405f)))));
		float fSlow127 = (1.0f - fSlow126);
		float fSlow128 = (250.0f * (float(fEntry39) + 1.0f));
		float fSlow129 = std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -9.2103405f));
		float fSlow130 = (1.0f / ((fConst0 * fSlow129) + 1.0f));
		float fSlow131 = (100.0f * (1.0f - (float(fEntry41) + 1.0f)));
		float fSlow132 = (1.0f - (1.0f / ((fConst0 * (fSlow129 * std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -4.60517025f)))) + 1.0f)));
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
		float fSlow152 = std::pow(10.0f, (0.0500000007f * (iSlow143?(iSlow144?(iSlow145?(iSlow146?(iSlow147?(iSlow148?(iSlow149?(iSlow150?(iSlow151?((fSlow142 < 0.0f)?8.23999977f:(iSlow151?(8.23999977f - (29.8999996f * fSlow15)):2.25999999f)):(iSlow150?(2.25999999f - (5.94999981f * (fSlow142 + -1.0f))):-3.69000006f)):(iSlow149?(-3.69000006f - (5.86000013f * (fSlow142 + -2.0f))):-9.55000019f)):(iSlow148?(-9.55000019f - (5.6500001f * (fSlow142 + -3.0f))):-15.1999998f)):(iSlow147?(-15.1999998f - (4.4000001f * (fSlow142 + -4.0f))):-19.6000004f)):(iSlow146?(-19.6000004f - (2.20000005f * (0.0f - (5.0f * (1.0f - fSlow15))))):-21.7999992f)):(iSlow145?(-21.7999992f - (0.400000006f * (fSlow142 + -6.0f))):-22.2000008f)):(iSlow144?((0.300000012f * (fSlow142 + -7.0f)) + -22.2000008f):-21.8999996f)):(iSlow143?((0.699999988f * (fSlow142 + -8.0f)) + -21.8999996f):-21.2000008f)):((fSlow142 < 10.0f)?((1.10000002f * (fSlow142 + -9.0f)) + -21.2000008f):-20.1000004f))));
		float fSlow153 = (fConst127 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow62 * fTemp0);
			fRec12[0] = ((fSlow48 * fVec0[1]) - (fSlow54 * ((fSlow63 * fRec12[1]) - (fSlow64 * fTemp0))));
			fRec14[0] = ((fSlow68 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow69 + fRec12[0])) - fRec14[1]))) + (fSlow71 * fRec14[1]));
			fRec13[0] = ((fSlow67 * fRec13[1]) + (fSlow66 * fRec14[0]));
			float fTemp1 = (fSlow44 + (fRec12[0] - fRec13[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow72 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = ((fSlow2 * (std::min<float>(0.0f, fTemp1) + (2.5f * ((fSlow42 * (((std::fabs((fTemp2 * fTemp3)) + -2.0f) * fTemp2) * fTemp3)) - fSlow43)))) - fSlow73);
			float fTemp5 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::min<float>(0.0f, fTemp4))));
			float fTemp6 = (fTemp5 * (std::fabs(fTemp5) + -2.0f));
			float fTemp7 = (0.0f - (fSlow39 + ((fSlow40 * ((fTemp6 * (std::fabs(fTemp6) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp4))));
			float fTemp8 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow36 * std::min<float>(0.0f, fTemp7))));
			float fTemp9 = (fTemp8 * (std::fabs(fTemp8) + -2.0f));
			float fTemp10 = ((fSlow35 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp7));
			fRec15[0] = ((fSlow75 * fRec15[1]) + (fSlow76 * (fSlow77 + std::max<float>(fSlow78, (fTemp10 - fSlow79)))));
			float fTemp11 = (fSlow74 * fRec15[0]);
			fRec16[0] = ((fSlow51 * std::max<float>(0.0f, (fSlow52 + (std::max<float>(fSlow53, ((fTemp10 - fTemp11) - fSlow79)) - fRec16[1])))) - (fSlow81 * fRec16[1]));
			float fTemp12 = (fSlow49 * fRec16[0]);
			float fTemp13 = (fSlow34 + ((fTemp10 - (fTemp11 + fTemp12)) - fSlow83));
			float fTemp14 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp13))));
			float fTemp15 = (std::fabs(fTemp14) + -2.0f);
			float fTemp16 = (((fSlow34 * (((fTemp14 * (std::fabs((fTemp14 * fTemp15)) + -2.0f)) * fTemp15) + -1.0f)) + (std::min<float>(0.0f, fTemp13) + fTemp12)) - fSlow84);
			fVec1[0] = (fSlow59 * fTemp16);
			fRec11[0] = ((fSlow48 * fVec1[1]) + (fSlow54 * ((fSlow85 * fTemp16) - (fSlow63 * fRec11[1]))));
			fRec18[0] = ((fSlow68 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow69 + fRec11[0])) - fRec18[1]))) - (fSlow86 * fRec18[1]));
			fRec17[0] = ((fSlow66 * fRec18[0]) + (fSlow67 * fRec17[1]));
			float fTemp17 = (fSlow44 + (fRec11[0] - fRec17[0]));
			float fTemp18 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow72 * std::max<float>(0.0f, fTemp17))));
			float fTemp19 = (std::fabs(fTemp18) + -2.0f);
			float fTemp20 = ((fSlow2 * (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow43 - (fSlow42 * ((fTemp19 * (std::fabs((fTemp19 * fTemp18)) + -2.0f)) * fTemp18)))))) - fSlow73);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp20) + (fSlow40 * ((((std::fabs((fTemp21 * fTemp22)) + -2.0f) * fTemp21) * fTemp22) + 1.0f)))));
			float fTemp24 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow36 * std::min<float>(0.0f, fTemp23))));
			float fTemp25 = (std::fabs(fTemp24) + -2.0f);
			float fTemp26 = (std::max<float>(0.0f, fTemp23) + (fSlow35 * (((fTemp24 * (std::fabs((fTemp24 * fTemp25)) + -2.0f)) * fTemp25) + 1.0f)));
			fRec19[0] = ((fSlow76 * (fSlow77 + std::max<float>(fSlow78, (fTemp26 - fSlow79)))) + (fSlow75 * fRec19[1]));
			float fTemp27 = (fSlow74 * fRec19[0]);
			fRec10[0] = ((fSlow51 * std::max<float>(0.0f, (fSlow52 + (std::max<float>(fSlow53, ((fTemp26 - fTemp27) - fSlow79)) - fRec10[1])))) - (fSlow81 * fRec10[1]));
			float fTemp28 = (fSlow49 * fRec10[0]);
			float fTemp29 = (fSlow34 + ((fTemp26 - (fTemp27 + fTemp28)) - fSlow83));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = ((std::fabs(fTemp30) + -2.0f) * fTemp30);
			float fTemp32 = (((fTemp28 + std::min<float>(0.0f, fTemp29)) - (fSlow34 * (1.0f - (fTemp31 * (std::fabs(fTemp31) + -2.0f))))) - fSlow84);
			fVec2[0] = (fSlow3 * fTemp32);
			fRec9[0] = ((fSlow48 * fVec2[1]) - (fSlow54 * ((fSlow63 * fRec9[1]) - (fSlow87 * fTemp32))));
			fRec21[0] = ((fSlow71 * fRec21[1]) + (fSlow68 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow69 + fRec9[0])) - fRec21[1]))));
			fRec20[0] = ((fSlow67 * fRec20[1]) + (fSlow66 * fRec21[0]));
			float fTemp33 = (fSlow44 + (fRec9[0] - fRec20[0]));
			float fTemp34 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow72 * std::max<float>(0.0f, fTemp33))));
			float fTemp35 = (std::fabs(fTemp34) + -2.0f);
			float fTemp36 = ((fSlow2 * (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow43 - (fSlow42 * (((std::fabs((fTemp35 * fTemp34)) + -2.0f) * fTemp35) * fTemp34)))))) - fSlow73);
			float fTemp37 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::min<float>(0.0f, fTemp36))));
			float fTemp38 = (fTemp37 * (std::fabs(fTemp37) + -2.0f));
			float fTemp39 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp36) + (fSlow40 * ((fTemp38 * (std::fabs(fTemp38) + -2.0f)) + 1.0f)))));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow36 * std::min<float>(0.0f, fTemp39))));
			float fTemp41 = ((std::fabs(fTemp40) + -2.0f) * fTemp40);
			float fTemp42 = (std::max<float>(0.0f, fTemp39) + (fSlow35 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)));
			fRec22[0] = ((fSlow75 * fRec22[1]) + (fSlow76 * (fSlow77 + std::max<float>(fSlow78, (fTemp42 - fSlow79)))));
			float fTemp43 = (fSlow74 * fRec22[0]);
			fRec23[0] = ((fSlow51 * std::max<float>(0.0f, (fSlow52 + (std::max<float>(fSlow53, ((fTemp42 - fTemp43) - fSlow79)) - fRec23[1])))) + (fSlow88 * fRec23[1]));
			float fTemp44 = (fSlow49 * fRec23[0]);
			float fTemp45 = (fSlow34 + ((fTemp42 - (fTemp43 + fTemp44)) - fSlow83));
			float fTemp46 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp45))));
			float fTemp47 = (std::fabs(fTemp46) + -2.0f);
			float fTemp48 = ((fSlow58 * (((std::min<float>(0.0f, fTemp45) + fTemp44) - (fSlow34 * (1.0f - ((fTemp46 * (std::fabs((fTemp46 * fTemp47)) + -2.0f)) * fTemp47)))) - fSlow84)) + (fSlow89 * fTemp16));
			fVec3[0] = (fSlow90 * fTemp48);
			fRec8[0] = ((fSlow54 * ((fSlow56 * fTemp48) - (fSlow63 * fRec8[1]))) + (fSlow48 * fVec3[1]));
			fRec25[0] = ((fSlow68 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow69 + fRec8[0])) - fRec25[1]))) - (fSlow86 * fRec25[1]));
			fRec24[0] = ((fSlow67 * fRec24[1]) + (fSlow66 * fRec25[0]));
			float fTemp49 = (fSlow44 + (fRec8[0] - fRec24[0]));
			float fTemp50 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow72 * std::max<float>(0.0f, fTemp49))));
			float fTemp51 = ((std::fabs(fTemp50) + -2.0f) * fTemp50);
			float fTemp52 = ((fSlow2 * (std::min<float>(0.0f, fTemp49) - (2.5f * (fSlow43 - (fSlow42 * (fTemp51 * (std::fabs(fTemp51) + -2.0f))))))) - fSlow73);
			float fTemp53 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::min<float>(0.0f, fTemp52))));
			float fTemp54 = (std::fabs(fTemp53) + -2.0f);
			float fTemp55 = (0.0f - (fSlow39 + (std::max<float>(0.0f, fTemp52) + (fSlow40 * (((fTemp54 * (std::fabs((fTemp54 * fTemp53)) + -2.0f)) * fTemp53) + 1.0f)))));
			float fTemp56 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow36 * std::min<float>(0.0f, fTemp55))));
			float fTemp57 = (std::fabs(fTemp56) + -2.0f);
			float fTemp58 = (std::max<float>(0.0f, fTemp55) + (fSlow35 * (((fTemp56 * (std::fabs((fTemp56 * fTemp57)) + -2.0f)) * fTemp57) + 1.0f)));
			fRec26[0] = ((fSlow75 * fRec26[1]) + (fSlow76 * (fSlow77 + std::max<float>(fSlow78, (fTemp58 - fSlow79)))));
			float fTemp59 = (fSlow74 * fRec26[0]);
			fRec7[0] = ((fSlow51 * std::max<float>(0.0f, (fSlow52 + (std::max<float>(fSlow53, ((fTemp58 - fTemp59) - fSlow79)) - fRec7[1])))) + (fSlow88 * fRec7[1]));
			float fTemp60 = (fSlow49 * fRec7[0]);
			float fTemp61 = (fSlow34 + ((fTemp58 - (fTemp59 + fTemp60)) - fSlow83));
			float fTemp62 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp61))));
			float fTemp63 = (fTemp62 * (std::fabs(fTemp62) + -2.0f));
			float fTemp64 = (((fTemp60 + std::min<float>(0.0f, fTemp61)) - (fSlow34 * (1.0f - (fTemp63 * (std::fabs(fTemp63) + -2.0f))))) - fSlow84);
			fVec4[0] = (fSlow3 * fTemp64);
			fRec6[0] = ((fSlow48 * fVec4[1]) - (fSlow54 * ((fSlow63 * fRec6[1]) - (fSlow87 * fTemp64))));
			fRec28[0] = ((fSlow71 * fRec28[1]) + (fSlow68 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow69 + fRec6[0])) - fRec28[1]))));
			fRec27[0] = ((fSlow67 * fRec27[1]) + (fSlow66 * fRec28[0]));
			float fTemp65 = (fSlow44 + (fRec6[0] - fRec27[0]));
			float fTemp66 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow72 * std::max<float>(0.0f, fTemp65))));
			float fTemp67 = (std::fabs(fTemp66) + -2.0f);
			float fTemp68 = ((fSlow2 * (std::min<float>(0.0f, fTemp65) - (2.5f * (fSlow43 - (fSlow42 * (((std::fabs((fTemp66 * fTemp67)) + -2.0f) * fTemp66) * fTemp67)))))) - fSlow73);
			float fTemp69 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow41 * std::min<float>(0.0f, fTemp68))));
			float fTemp70 = (std::fabs(fTemp69) + -2.0f);
			float fTemp71 = (0.0f - (fSlow39 + ((fSlow40 * ((((std::fabs((fTemp69 * fTemp70)) + -2.0f) * fTemp69) * fTemp70) + 1.0f)) + std::max<float>(0.0f, fTemp68))));
			float fTemp72 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow36 * std::min<float>(0.0f, fTemp71))));
			float fTemp73 = (std::fabs(fTemp72) + -2.0f);
			float fTemp74 = ((fSlow35 * ((((std::fabs((fTemp72 * fTemp73)) + -2.0f) * fTemp72) * fTemp73) + 1.0f)) + std::max<float>(0.0f, fTemp71));
			fRec29[0] = ((fSlow75 * fRec29[1]) + (fSlow76 * (fSlow77 + std::max<float>(fSlow78, (fTemp74 - fSlow79)))));
			float fTemp75 = (fSlow74 * fRec29[0]);
			fRec30[0] = ((fSlow51 * std::max<float>(0.0f, (fSlow52 + (std::max<float>(fSlow53, ((fTemp74 - fTemp75) - fSlow79)) - fRec30[1])))) + (fSlow88 * fRec30[1]));
			float fTemp76 = (fSlow49 * fRec30[0]);
			float fTemp77 = (fSlow34 + ((fTemp74 - (fTemp75 + fTemp76)) - fSlow83));
			float fTemp78 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow60 * std::max<float>(0.0f, fTemp77))));
			float fTemp79 = (std::fabs(fTemp78) + -2.0f);
			float fTemp80 = (((fSlow33 * (((std::min<float>(0.0f, fTemp77) + fTemp76) - (fSlow34 * (1.0f - ((fTemp78 * (std::fabs((fTemp78 * fTemp79)) + -2.0f)) * fTemp79)))) - fSlow84)) + (fSlow91 * fTemp48)) * fSlow102);
			float fTemp81 = (fSlow3 * fTemp80);
			fVec5[0] = fTemp81;
			fRec5[0] = ((fSlow28 * fVec5[1]) - (fSlow103 * ((fSlow104 * fRec5[1]) - (fSlow105 * fTemp80))));
			fRec31[0] = (0.0f - (fSlow103 * ((fSlow104 * fRec31[1]) - (fVec5[1] + fTemp81))));
			float fTemp82 = (fRec5[0] + (fSlow106 * fRec31[0]));
			fVec6[0] = fTemp82;
			fRec4[0] = ((fConst5 * fVec6[1]) - (fConst7 * ((fConst8 * fRec4[1]) - (fConst3 * fTemp82))));
			float fTemp83 = (fConst12 * fRec3[1]);
			fRec3[0] = (fRec4[0] - (((fSlow114 * fRec3[2]) + fTemp83) / fSlow115));
			float fTemp84 = (((fRec3[0] * fSlow117) + fTemp83) + (fSlow118 * fRec3[2]));
			float fTemp85 = (fTemp84 / fSlow115);
			fVec7[0] = fTemp85;
			fRec2[0] = (0.0f - (((fSlow21 * fRec2[1]) - (fVec7[1] + fTemp85)) / fSlow119));
			fRec32[0] = ((fSlow120 * fVec7[1]) - (((fRec32[1] * fSlow21) - (fTemp84 / fSlow121)) / fSlow119));
			float fTemp86 = ((fSlow16 * (fRec2[0] + (fRec32[0] * fSlow122))) - fSlow123);
			fVec8[0] = fTemp86;
			fRec1[0] = ((fSlow14 * fVec8[1]) - (fSlow124 * ((fSlow125 * fRec1[1]) - (fSlow12 * fTemp86))));
			fRec33[0] = ((fSlow127 * (fRec1[0] - fSlow128)) + (fSlow126 * fRec33[1]));
			fRec34[0] = ((fSlow130 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow131 + ((fRec1[0] - fRec33[0]) - fSlow128))) - fRec34[1]))) + (fSlow132 * fRec34[1]));
			float fTemp87 = (fSlow10 * ((fRec1[0] - (fRec33[0] + fRec34[0])) - fSlow128));
			fRec35[0] = ((fSlow135 * (std::max<float>(fSlow136, fTemp87) - fSlow136)) + (fSlow134 * fRec35[1]));
			float fTemp88 = (fSlow133 * fRec35[0]);
			fRec0[0] = ((fSlow7 * std::max<float>(0.0f, (fSlow8 + (std::max<float>(fSlow9, (fTemp87 - fTemp88)) - fRec0[1])))) + (fSlow137 * fRec0[1]));
			float fTemp89 = (fSlow5 * (0.0f - fRec0[0]));
			float fTemp90 = (fSlow138 + ((fTemp87 + (-10.0f - (fTemp88 + fTemp89))) - fSlow4));
			float fTemp91 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp90))));
			float fTemp92 = (fTemp91 * (std::fabs(fTemp91) + -2.0f));
			float fTemp93 = (fSlow4 + (((fTemp89 + std::min<float>(0.0f, fTemp90)) + (10.0f - (fSlow138 * (1.0f - (fTemp92 * (std::fabs(fTemp92) + -2.0f)))))) - fSlow140));
			fRec36[0] = ((fSlow134 * fRec36[1]) + (fSlow135 * (std::max<float>(fSlow136, (0.0f - fTemp87)) - fSlow136)));
			float fTemp94 = (fTemp87 + (fSlow133 * fRec36[0]));
			fRec37[0] = ((fSlow7 * std::max<float>(0.0f, (fSlow8 + (std::max<float>(fSlow9, (0.0f - fTemp94)) - fRec37[1])))) + (fSlow137 * fRec37[1]));
			float fTemp95 = (fSlow5 * (0.0f - fRec37[0]));
			float fTemp96 = (fSlow138 + ((-10.0f - (fTemp94 + fTemp95)) - fSlow4));
			float fTemp97 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow139 * std::max<float>(0.0f, fTemp96))));
			float fTemp98 = ((std::fabs(fTemp97) + -2.0f) * fTemp97);
			float fTemp99 = (fSlow4 + (((std::min<float>(0.0f, fTemp96) + fTemp95) + (10.0f - (fSlow138 * (1.0f - (fTemp98 * (std::fabs(fTemp98) + -2.0f)))))) - fSlow140));
			float fTemp100 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp99))));
			float fTemp101 = (std::fabs(fTemp100) + -2.0f);
			float fTemp102 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow141 * std::min<float>(0.0f, fTemp93))));
			float fTemp103 = (std::fabs(fTemp102) + -2.0f);
			float fTemp104 = ((std::max<float>(0.0f, fTemp93) - (std::max<float>(0.0f, fTemp99) + (fSlow140 * ((((fTemp100 * (std::fabs((fTemp100 * fTemp101)) + -2.0f)) * fTemp101) + 1.0f) - ((((std::fabs((fTemp103 * fTemp102)) + -2.0f) * fTemp103) * fTemp102) + 1.0f))))) * fSlow152);
			float fTemp105 = (fSlow3 * fTemp104);
			fVec9[0] = fTemp105;
			fRec60[0] = ((fConst129 * fVec9[1]) - (fConst130 * ((fConst131 * fRec60[1]) - (fSlow153 * fTemp104))));
			fRec59[0] = (0.0f - (fConst124 * ((fConst125 * fRec59[1]) - (fRec60[0] + fRec60[1]))));
			fRec58[0] = ((fConst122 * fRec59[1]) - (fConst132 * ((fConst133 * fRec58[1]) - (fConst112 * fRec59[0]))));
			fRec57[0] = (fRec58[0] - (fConst120 * ((fConst134 * fRec57[1]) + (fConst135 * fRec57[2]))));
			fRec56[0] = ((fConst120 * (((fConst115 * fRec57[0]) + (fConst118 * fRec57[1])) + (fConst115 * fRec57[2]))) - (fConst119 * ((fConst134 * fRec56[1]) + (fConst136 * fRec56[2]))));
			fRec55[0] = ((fConst119 * ((fConst115 * fRec56[2]) + ((fConst115 * fRec56[0]) + (fConst118 * fRec56[1])))) - (fConst117 * ((fConst134 * fRec55[1]) + (fConst137 * fRec55[2]))));
			fRec54[0] = ((fConst117 * (((fConst118 * fRec55[1]) + (fConst115 * fRec55[0])) + (fConst115 * fRec55[2]))) - (fConst116 * ((fConst138 * fRec54[2]) + (fConst134 * fRec54[1]))));
			fRec53[0] = ((fConst116 * (((fConst115 * fRec54[0]) + (fConst118 * fRec54[1])) + (fConst115 * fRec54[2]))) - (fConst113 * ((fConst139 * fRec53[2]) + (fConst134 * fRec53[1]))));
			fRec66[0] = (0.0f - (fConst132 * ((fConst133 * fRec66[1]) - (fRec59[0] + fRec59[1]))));
			fRec65[0] = (fRec66[0] - (fConst120 * ((fConst135 * fRec65[2]) + (fConst134 * fRec65[1]))));
			fRec64[0] = ((fConst120 * (fRec65[2] + (fRec65[0] + (2.0f * fRec65[1])))) - (fConst119 * ((fConst136 * fRec64[2]) + (fConst134 * fRec64[1]))));
			fRec63[0] = ((fConst119 * (fRec64[2] + (fRec64[0] + (2.0f * fRec64[1])))) - (fConst117 * ((fConst137 * fRec63[2]) + (fConst134 * fRec63[1]))));
			fRec62[0] = ((fConst117 * (fRec63[2] + (fRec63[0] + (2.0f * fRec63[1])))) - (fConst116 * ((fConst138 * fRec62[2]) + (fConst134 * fRec62[1]))));
			fRec61[0] = ((fConst116 * ((fRec62[0] + (2.0f * fRec62[1])) + fRec62[2])) - (fConst113 * ((fConst134 * fRec61[1]) + (fConst139 * fRec61[2]))));
			float fTemp106 = (fConst110 * fRec52[1]);
			fRec52[0] = ((fConst113 * ((0.13673377f * (((fConst115 * fRec53[0]) + (fConst118 * fRec53[1])) + (fConst115 * fRec53[2]))) + (fRec61[2] + (fRec61[0] + (2.0f * fRec61[1]))))) - (fConst109 * ((fConst140 * fRec52[2]) + fTemp106)));
			float fTemp107 = (fConst145 * fRec51[1]);
			fRec51[0] = ((fConst109 * ((fTemp106 + (fConst142 * fRec52[0])) + (fConst143 * fRec52[2]))) - (fConst102 * ((fConst144 * fRec51[2]) + fTemp107)));
			float fTemp108 = (fConst97 * fRec50[1]);
			fRec50[0] = ((fConst102 * ((fConst104 * fRec51[2]) + (fTemp107 + (fConst146 * fRec51[0])))) - (fConst96 * (fTemp108 + (fConst147 * fRec50[2]))));
			float fTemp109 = (fConst152 * fRec49[1]);
			fRec49[0] = ((fConst96 * ((fTemp108 + (fConst149 * fRec50[0])) + (fConst150 * fRec50[2]))) - (fConst89 * ((fConst151 * fRec49[2]) + fTemp109)));
			float fTemp110 = (fConst84 * fRec48[1]);
			fRec48[0] = ((fConst89 * (((fConst91 * fRec49[0]) + fTemp109) + (fConst153 * fRec49[2]))) - (fConst83 * (fTemp110 + (fConst154 * fRec48[2]))));
			float fTemp111 = (fConst78 * fRec47[1]);
			fRec47[0] = ((fConst83 * ((fTemp110 + (fConst156 * fRec48[0])) + (fConst157 * fRec48[2]))) - (fConst77 * (fTemp111 + (fConst158 * fRec47[2]))));
			float fTemp112 = (fConst72 * fRec46[1]);
			fRec46[0] = ((fConst77 * ((fTemp111 + (fConst160 * fRec47[0])) + (fConst161 * fRec47[2]))) - (fConst71 * (fTemp112 + (fConst162 * fRec46[2]))));
			float fTemp113 = (fConst66 * fRec45[1]);
			fRec45[0] = ((fConst71 * ((fTemp112 + (fConst164 * fRec46[0])) + (fConst165 * fRec46[2]))) - (fConst65 * (fTemp113 + (fConst166 * fRec45[2]))));
			float fTemp114 = (fConst170 * fRec44[1]);
			fRec44[0] = ((fConst65 * ((fTemp113 + (fConst168 * fRec45[0])) + (fConst169 * fRec45[2]))) - (fConst58 * (fTemp114 + (fConst171 * fRec44[2]))));
			float fTemp115 = (fConst173 * fRec43[1]);
			fRec43[0] = ((fConst58 * ((fConst60 * fRec44[2]) + ((fConst172 * fRec44[0]) + fTemp114))) - (fConst51 * (fTemp115 + (fConst174 * fRec43[2]))));
			float fTemp116 = (fConst177 * fRec42[1]);
			fRec42[0] = ((fConst51 * (((fConst53 * fRec43[0]) + fTemp115) + (fConst175 * fRec43[2]))) - (fConst44 * ((fConst176 * fRec42[2]) + fTemp116)));
			float fTemp117 = (fConst39 * fRec41[1]);
			fRec41[0] = ((fConst44 * (((fConst46 * fRec42[0]) + fTemp116) + (fConst178 * fRec42[2]))) - (fConst38 * ((fConst179 * fRec41[2]) + fTemp117)));
			float fTemp118 = (fConst183 * fRec40[1]);
			fRec40[0] = ((fConst38 * ((fTemp117 + (fConst181 * fRec41[0])) + (fConst182 * fRec41[2]))) - (fConst31 * (fTemp118 + (fConst184 * fRec40[2]))));
			float fTemp119 = (fConst26 * fRec39[1]);
			fRec39[0] = ((fConst31 * (((fConst33 * fRec40[0]) + fTemp118) + (fConst185 * fRec40[2]))) - (fConst25 * (fTemp119 + (fConst186 * fRec39[2]))));
			float fTemp120 = (fConst192 * fRec38[1]);
			fRec38[0] = ((fConst25 * ((fTemp119 + (fConst188 * fRec39[0])) + (fConst189 * fRec39[2]))) - (fConst190 * ((fConst191 * fRec38[2]) + fTemp120)));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst18 * ((fConst20 * fRec38[2]) + (fTemp120 + (fConst193 * fRec38[0])))):fTemp105)));
			fVec0[1] = fVec0[0];
			fRec12[1] = fRec12[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fRec16[1] = fRec16[0];
			fVec1[1] = fVec1[0];
			fRec11[1] = fRec11[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec10[1] = fRec10[0];
			fVec2[1] = fVec2[0];
			fRec9[1] = fRec9[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec23[1] = fRec23[0];
			fVec3[1] = fVec3[0];
			fRec8[1] = fRec8[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec26[1] = fRec26[0];
			fRec7[1] = fRec7[0];
			fVec4[1] = fVec4[0];
			fRec6[1] = fRec6[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fRec29[1] = fRec29[0];
			fRec30[1] = fRec30[0];
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
			fVec9[1] = fVec9[0];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
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
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
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
