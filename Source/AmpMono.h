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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
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
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	float fVec0[2];
	float fRec9[2];
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	float fRec11[2];
	float fRec10[2];
	float fRec12[2];
	float fVec1[2];
	float fRec8[2];
	float fRec14[2];
	float fRec13[2];
	float fRec7[2];
	float fVec2[2];
	float fRec6[2];
	float fRec16[2];
	float fRec15[2];
	float fRec17[2];
	float fVec3[2];
	float fRec20[2];
	float fRec22[2];
	float fRec21[2];
	float fRec23[2];
	float fVec4[2];
	float fRec19[2];
	float fRec25[2];
	float fRec24[2];
	float fRec18[2];
	float fVec5[2];
	float fRec5[2];
	float fRec26[2];
	float fVec6[2];
	float fConst8;
	float fConst9;
	float fRec4[2];
	float fConst10;
	FAUSTFLOAT fEntry33;
	float fConst11;
	float fRec3[3];
	float fVec7[2];
	FAUSTFLOAT fEntry34;
	float fRec2[2];
	float fRec27[2];
	FAUSTFLOAT fEntry35;
	float fVec8[2];
	float fRec1[2];
	float fConst12;
	FAUSTFLOAT fEntry36;
	FAUSTFLOAT fEntry37;
	float fRec28[2];
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	float fRec30[2];
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	float fRec31[2];
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fVec9[2];
	float fRec0[2];
	float fRec33[2];
	float fVec10[2];
	float fRec32[2];
	float fVec11[2];
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
	float fRec56[2];
	float fRec55[2];
	float fConst132;
	float fRec54[2];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fRec53[3];
	float fConst137;
	float fRec52[3];
	float fConst138;
	float fRec51[3];
	float fConst139;
	float fRec50[3];
	float fConst140;
	float fRec49[3];
	float fConst141;
	float fConst142;
	float fRec62[2];
	float fRec61[3];
	float fRec60[3];
	float fRec59[3];
	float fRec58[3];
	float fRec57[3];
	float fConst143;
	float fConst144;
	float fRec48[3];
	float fConst145;
	float fConst146;
	float fRec47[3];
	float fConst147;
	float fConst148;
	float fConst149;
	float fConst150;
	float fRec46[3];
	float fConst151;
	float fConst152;
	float fConst153;
	float fConst154;
	float fConst155;
	float fRec45[3];
	float fConst156;
	float fConst157;
	float fConst158;
	float fRec44[3];
	float fConst159;
	float fConst160;
	float fConst161;
	float fRec43[3];
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec42[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec41[3];
	float fConst168;
	float fConst169;
	float fRec40[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec39[3];
	float fConst175;
	float fConst176;
	float fRec38[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fConst180;
	float fConst181;
	float fRec37[3];
	float fConst182;
	float fConst183;
	float fRec36[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fRec35[3];
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fRec34[3];
	float fConst194;

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
		fConst8 = (1.0f / fConst6);
		fConst9 = (1.0f - fConst5);
		fConst10 = (1.0f / fConst2);
		fConst11 = (3.14159274f / (fConst0 * std::sin((3141.59277f / fConst0))));
		fConst12 = (1.0f / fConst0);
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
		fConst32 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst27))));
		fConst33 = std::tan((3081.90234f / fConst0));
		fConst34 = (1.0f / fConst33);
		fConst35 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst36 = (486.410919f / fConst35);
		fConst37 = (1.0f / (((fConst34 + fConst36) / fConst33) + 1.0f));
		fConst38 = (183.178085f / fConst35);
		fConst39 = (((fConst34 - fConst38) / fConst33) + 1.0f);
		fConst40 = std::tan((2592.47217f / fConst0));
		fConst41 = (1.0f / fConst40);
		fConst42 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst43 = (317.628265f / fConst42);
		fConst44 = (1.0f / (((fConst41 + fConst43) / fConst40) + 1.0f));
		fConst45 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst40))));
		fConst46 = std::tan((1891.23853f / fConst0));
		fConst47 = (1.0f / fConst46);
		fConst48 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst49 = (265.978119f / fConst48);
		fConst50 = (1.0f / (((fConst47 + fConst49) / fConst46) + 1.0f));
		fConst51 = (116.345184f / fConst48);
		fConst52 = (((fConst47 - fConst51) / fConst46) + 1.0f);
		fConst53 = std::tan((21179.4824f / fConst0));
		fConst54 = (1.0f / fConst53);
		fConst55 = (fConst0 * std::sin((42358.9648f / fConst0)));
		fConst56 = (7223.21826f / fConst55);
		fConst57 = (1.0f / (((fConst54 + fConst56) / fConst53) + 1.0f));
		fConst58 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst53))));
		fConst59 = std::tan((15066.6357f / fConst0));
		fConst60 = (1.0f / fConst59);
		fConst61 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst62 = (11187.3662f / fConst61);
		fConst63 = (1.0f / (((fConst60 + fConst62) / fConst59) + 1.0f));
		fConst64 = (36783.4805f / fConst61);
		fConst65 = (((fConst60 + fConst64) / fConst59) + 1.0f);
		fConst66 = std::tan((13437.668f / fConst0));
		fConst67 = (1.0f / fConst66);
		fConst68 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst69 = (13245.1885f / fConst68);
		fConst70 = (1.0f / (((fConst67 + fConst69) / fConst66) + 1.0f));
		fConst71 = (4583.19189f / fConst68);
		fConst72 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst73 = std::tan((10058.502f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst76 = (4926.20459f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (9024.73242f / fConst75);
		fConst79 = (((fConst74 - fConst78) / fConst73) + 1.0f);
		fConst80 = std::tan((8136.54736f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst83 = (966.024841f / fConst82);
		fConst84 = (1.0f / (((fConst81 + fConst83) / fConst80) + 1.0f));
		fConst85 = (518.801147f / fConst82);
		fConst86 = (((fConst81 - fConst85) / fConst80) + 1.0f);
		fConst87 = std::tan((8011.02734f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst90 = (1613.9762f / fConst89);
		fConst91 = (1.0f / (((fConst88 + fConst90) / fConst87) + 1.0f));
		fConst92 = (3097.15845f / fConst89);
		fConst93 = (((fConst88 - fConst92) / fConst87) + 1.0f);
		fConst94 = std::tan((9456.15234f / fConst0));
		fConst95 = (1.0f / fConst94);
		fConst96 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst97 = (2492.29883f / fConst96);
		fConst98 = (1.0f / (((fConst95 + fConst97) / fConst94) + 1.0f));
		fConst99 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst94))));
		fConst100 = std::tan((2827.43262f / fConst0));
		fConst101 = (1.0f / fConst100);
		fConst102 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst103 = (19634.3262f / fConst102);
		fConst104 = (1.0f / (((fConst101 + fConst103) / fConst100) + 1.0f));
		fConst105 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst100))));
		fConst106 = std::tan((375.293884f / fConst0));
		fConst107 = (1.0f / fConst106);
		fConst108 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst109 = (463.734222f / fConst108);
		fConst110 = (1.0f / (((fConst107 + fConst109) / fConst106) + 1.0f));
		fConst111 = (3220.11475f / fConst108);
		fConst112 = (((fConst107 + fConst111) / fConst106) + 1.0f);
		fConst113 = std::tan((18369.8027f / fConst0));
		fConst114 = (1.0f / fConst113);
		fConst115 = (1.0f / (((fConst114 + 0.284629673f) / fConst113) + 1.0f));
		fConst116 = (1.0f / (((fConst114 + 0.830830038f) / fConst113) + 1.0f));
		fConst117 = (1.0f / (((fConst114 + 1.30972147f) / fConst113) + 1.0f));
		fConst118 = (1.0f / (((fConst114 + 1.68250704f) / fConst113) + 1.0f));
		fConst119 = (1.0f / (((fConst114 + 1.91898596f) / fConst113) + 1.0f));
		fConst120 = (fConst114 + 1.0f);
		fConst121 = (1.0f / fConst120);
		fConst122 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst123 = (1.0f / (fConst122 + 1.0f));
		fConst124 = (1.0f - fConst122);
		fConst125 = std::tan((452.102844f / fConst0));
		fConst126 = (1.0f / fConst125);
		fConst127 = (fConst126 + 1.0f);
		fConst128 = (0.0f - (1.0f / (fConst125 * fConst127)));
		fConst129 = (1.0f / fConst127);
		fConst130 = (0.0199999996f / fConst125);
		fConst131 = (1.0f - fConst126);
		fConst132 = (1.0f - fConst114);
		fConst133 = AmpMono_faustpower2_f(fConst113);
		fConst134 = (1.0f / fConst133);
		fConst135 = (2.0f * (1.0f - fConst134));
		fConst136 = (((fConst114 + -1.91898596f) / fConst113) + 1.0f);
		fConst137 = (((fConst114 + -1.68250704f) / fConst113) + 1.0f);
		fConst138 = (((fConst114 + -1.30972147f) / fConst113) + 1.0f);
		fConst139 = (((fConst114 + -0.830830038f) / fConst113) + 1.0f);
		fConst140 = (((fConst114 + -0.284629673f) / fConst113) + 1.0f);
		fConst141 = (0.0f - (2.0f / fConst133));
		fConst142 = (0.0f - (1.0f / (fConst113 * fConst120)));
		fConst143 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst106))));
		fConst144 = (((fConst107 - fConst109) / fConst106) + 1.0f);
		fConst145 = (((fConst107 - fConst111) / fConst106) + 1.0f);
		fConst146 = (((fConst101 - fConst103) / fConst100) + 1.0f);
		fConst147 = (106249.391f / fConst102);
		fConst148 = (((fConst101 + fConst147) / fConst100) + 1.0f);
		fConst149 = (((fConst101 - fConst147) / fConst100) + 1.0f);
		fConst150 = (((fConst95 - fConst97) / fConst94) + 1.0f);
		fConst151 = (974.257141f / fConst96);
		fConst152 = (((fConst95 + fConst151) / fConst94) + 1.0f);
		fConst153 = (((fConst95 - fConst151) / fConst94) + 1.0f);
		fConst154 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst87))));
		fConst155 = (((fConst88 - fConst90) / fConst87) + 1.0f);
		fConst156 = (((fConst88 + fConst92) / fConst87) + 1.0f);
		fConst157 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst80))));
		fConst158 = (((fConst81 - fConst83) / fConst80) + 1.0f);
		fConst159 = (((fConst81 + fConst85) / fConst80) + 1.0f);
		fConst160 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst161 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst162 = (((fConst74 + fConst78) / fConst73) + 1.0f);
		fConst163 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst164 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst165 = (((fConst67 - fConst71) / fConst66) + 1.0f);
		fConst166 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst59))));
		fConst167 = (((fConst60 - fConst62) / fConst59) + 1.0f);
		fConst168 = (((fConst60 - fConst64) / fConst59) + 1.0f);
		fConst169 = (((fConst54 - fConst56) / fConst53) + 1.0f);
		fConst170 = (1059.12756f / fConst55);
		fConst171 = (((fConst54 + fConst170) / fConst53) + 1.0f);
		fConst172 = (((fConst54 - fConst170) / fConst53) + 1.0f);
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst46))));
		fConst174 = (((fConst47 - fConst49) / fConst46) + 1.0f);
		fConst175 = (((fConst47 + fConst51) / fConst46) + 1.0f);
		fConst176 = (((fConst41 - fConst43) / fConst40) + 1.0f);
		fConst177 = (148.323349f / fConst42);
		fConst178 = (((fConst41 + fConst177) / fConst40) + 1.0f);
		fConst179 = (((fConst41 - fConst177) / fConst40) + 1.0f);
		fConst180 = (((fConst34 - fConst36) / fConst33) + 1.0f);
		fConst181 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst33))));
		fConst182 = (((fConst34 + fConst38) / fConst33) + 1.0f);
		fConst183 = (((fConst28 - fConst30) / fConst27) + 1.0f);
		fConst184 = (270.569763f / fConst29);
		fConst185 = (((fConst28 + fConst184) / fConst27) + 1.0f);
		fConst186 = (((fConst28 - fConst184) / fConst27) + 1.0f);
		fConst187 = (((fConst22 - fConst24) / fConst21) + 1.0f);
		fConst188 = (190.645706f / fConst23);
		fConst189 = (((fConst22 + fConst188) / fConst21) + 1.0f);
		fConst190 = (((fConst22 - fConst188) / fConst21) + 1.0f);
		fConst191 = (1.0f / fConst17);
		fConst192 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst193 = (((fConst14 - fConst16) / fConst13) + 1.0f);
		fConst194 = (((fConst14 + fConst19) / fConst13) + 1.0f);

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
			fVec1[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec8[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec14[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec13[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec7[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec2[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec6[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec16[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec15[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec17[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec3[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec20[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec22[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec21[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec23[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec4[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec19[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec25[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec24[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec18[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec5[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec5[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec26[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec6[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec4[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec3[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec7[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec2[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec27[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fVec8[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec1[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec28[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec30[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec31[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fVec9[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec0[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec33[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec10[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec32[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec11[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec56[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec55[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec54[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec53[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec52[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec51[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec50[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec49[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec62[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec61[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec60[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec59[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec58[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec57[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec48[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec47[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec46[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec45[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec44[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec43[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec42[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec41[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec40[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec39[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec38[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec37[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec36[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec35[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec34[l73] = 0.0f;

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

	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry26 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry27 = value + 0.000000e+00; }
	void set_tetrode_grid_cap(FAUSTFLOAT value) { fEntry38 = value + 4.705513e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry40 = value + 4.248187e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry35 = value + 4.772657e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry37 = value + -2.047729e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry41 = value + 6.319992e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry39 = value + -6.194208e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry36 = value + -1.524618e-05; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry8 = value + -8.210805e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry6 = value + -2.549861e+00; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry4 = value + -2.575947e-01; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry44 = value + 1.308648e-01; }
	void set_tetrode_plate_corner_b(FAUSTFLOAT value) { fEntry45 = value + -1.507608e+00; }
	void set_tetrode_plate_hp(FAUSTFLOAT value) { fEntry3 = value + -4.969384e+00; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry42 = value + 9.329082e-01; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry5 = value + -5.029362e-01; }
	void set_tetrode_plate_taus(FAUSTFLOAT value) { fEntry43 = value + 1.474470e-01; }
	void set_triode_grid_cap(FAUSTFLOAT value) { fEntry31 = value + 9.940021e+00; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry20 = value + 3.719299e-01; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry19 = value + -2.609667e-02; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry32 = value + 3.359419e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry30 = value + 1.242548e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry29 = value + 1.562984e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry28 = value + -1.413848e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry21 = value + 4.522095e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry11 = value + -6.074699e-02; }
	void set_triode_plate_cap_b(FAUSTFLOAT value) { fEntry25 = value + -7.208259e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry16 = value + 7.069492e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry18 = value + -2.074368e-01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry15 = value + -2.001175e-01; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry23 = value + 5.666555e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.537254e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry22 = value + -2.343605e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry17 = value + -1.274735e-01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry24 = value + -4.353973e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry33 = value + 0.000000e+00; }
	void zero_all() {
		set_cab_on_off(0.0f);
		set_gain_slope(0.0f);
		set_gain_stages(0.0f);
		set_input_level(0.0f);
		set_output_level(0.0f);
		set_power_drive(0.0f);
		set_pre_drive(0.0f);
		set_tetrode_grid_cap(0.0f);
		set_tetrode_grid_level(0.0f);
		set_tetrode_grid_offset1(0.0f);
		set_tetrode_grid_offset2(0.0f);
		set_tetrode_grid_ratio(0.0f);
		set_tetrode_grid_tau(0.0f);
		set_tetrode_grid_taus(0.0f);
		set_tetrode_hp_freq(0.0f);
		set_tetrode_plate_bias(0.0f);
		set_tetrode_plate_clip(0.0f);
		set_tetrode_plate_corner(0.0f);
		set_tetrode_plate_corner_b(0.0f);
		set_tetrode_plate_hp(0.0f);
		set_tetrode_plate_point(0.0f);
		set_tetrode_plate_power(0.0f);
		set_tetrode_plate_scale(0.0f);
		set_tetrode_plate_taus(0.0f);
		set_triode_grid_cap(0.0f);
		set_triode_grid_clip(0.0f);
		set_triode_grid_corner(0.0f);
		set_triode_grid_level(0.0f);
		set_triode_grid_ratio(0.0f);
		set_triode_grid_smooth(0.0f);
		set_triode_grid_tau(0.0f);
		set_triode_hp_freq(0.0f);
		set_triode_plate_bias(0.0f);
		set_triode_plate_cap_b(0.0f);
		set_triode_plate_clip(0.0f);
		set_triode_plate_corner(0.0f);
		set_triode_plate_level_b(0.0f);
		set_triode_plate_power(0.0f);
		set_triode_plate_ratio_b(0.0f);
		set_triode_plate_scale(0.0f);
		set_triode_plate_scale_b(0.0f);
		set_triode_plate_smooth_b(0.0f);
		set_triode_plate_tau_b(0.0f);
		set_ts_high(0.0f);
		set_ts_low(0.0f);
		set_ts_mid(0.0f);
	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f))))));
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = (float(fEntry2) + 1.0f);
		float fSlow3 = (0.0199999996f / fSlow2);
		float fSlow4 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry3) + 1.0f)) + -2.30258512f))));
		float fSlow5 = (1.0f / fSlow4);
		float fSlow6 = (fSlow5 + 1.0f);
		float fSlow7 = (0.0f - (1.0f / (fSlow4 * fSlow6)));
		float fSlow8 = (20.0f * (float(fEntry4) + 1.0f));
		float fSlow9 = std::exp(((4.60517025f * (float(fEntry5) + 1.0f)) + -4.60517025f));
		float fSlow10 = (10.0f * (float(fEntry6) + 1.0f));
		float fSlow11 = (fSlow10 + 30.0f);
		float fSlow12 = (0.5f * (float(fEntry7) + 1.0f));
		float fSlow13 = (fSlow12 + 1.0f);
		float fSlow14 = std::pow(fSlow11, fSlow13);
		float fSlow15 = (10.0f / fSlow11);
		float fSlow16 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry8) + 1.0f)) + -2.30258512f))));
		float fSlow17 = (1.0f / fSlow16);
		float fSlow18 = (fSlow17 + 1.0f);
		float fSlow19 = (0.0f - (1.0f / (fSlow16 * fSlow18)));
		float fSlow20 = (float(fEntry9) + 1.0f);
		float fSlow21 = (50.0f * (fSlow2 * std::exp(((3.45387769f * fSlow20) + -2.30258512f))));
		float fSlow22 = float(fEntry10);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (1.0f - (0.5f * fSlow23));
		float fSlow25 = std::tan((fConst1 * ((400.0f * fSlow24) + (25.0f * fSlow23))));
		float fSlow26 = (1.0f / fSlow25);
		float fSlow27 = (fSlow26 + 1.0f);
		float fSlow28 = (0.0f - (1.0f / (fSlow25 * fSlow27)));
		float fSlow29 = (float(fEntry11) + 1.0f);
		float fSlow30 = (10.0f * fSlow29);
		float fSlow31 = (0.5f * (float(fEntry12) + 1.0f));
		float fSlow32 = std::pow(fSlow30, fSlow31);
		float fSlow33 = (1.0f / fSlow32);
		float fSlow34 = float(fEntry13);
		float fSlow35 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow34) + -3.0f));
		float fSlow36 = (1.0f - (0.5f * fSlow35));
		float fSlow37 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow34) + -1.0f));
		float fSlow38 = ((float(fEntry14) + 1.0f) + 1.0f);
		float fSlow39 = (fSlow37 / fSlow38);
		float fSlow40 = (fSlow31 + 1.0f);
		float fSlow41 = std::pow(fSlow30, fSlow40);
		float fSlow42 = (37.5f * (float(fEntry15) + 1.0f));
		float fSlow43 = (fSlow41 + fSlow42);
		float fSlow44 = (150.0f * (float(fEntry16) + 1.0f));
		float fSlow45 = std::exp(((3.45387769f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow46 = (fSlow44 + fSlow45);
		float fSlow47 = std::exp(((4.60517025f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow48 = (0.294117659f / fSlow47);
		float fSlow49 = (fSlow40 * fSlow32);
		float fSlow50 = (float(fEntry19) + 1.0f);
		float fSlow51 = (fSlow50 - (float(fEntry20) + 1.0f));
		float fSlow52 = (2.5f * fSlow51);
		float fSlow53 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry21) + 1.0f)) + -2.30258512f))));
		float fSlow54 = (1.0f / fSlow53);
		float fSlow55 = (fSlow54 + 1.0f);
		float fSlow56 = (0.0f - (1.0f / (fSlow53 * fSlow55)));
		float fSlow57 = std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f));
		float fSlow58 = std::exp(((4.60517025f * (float(fEntry24) + 1.0f)) + -9.2103405f));
		float fSlow59 = (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry23) + 1.0f)) + -2.99573231f)) * fSlow58)) + 1.0f));
		float fSlow60 = (1.0f - fSlow59);
		float fSlow61 = (float(fEntry25) + 1.0f);
		float fSlow62 = (0.0199999996f / (fSlow61 * ((fConst0 * fSlow58) + 1.0f)));
		float fSlow63 = (50.0f * fSlow61);
		float fSlow64 = (0.5f * (fSlow38 / fSlow32));
		float fSlow65 = (float(fEntry27) + 1.0f);
		float fSlow66 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry26) + 1.0f)))))) * std::exp(((2.99573231f * fSlow65) + -0.693147182f)));
		float fSlow67 = (1.0f / fSlow55);
		float fSlow68 = (fSlow66 / fSlow53);
		float fSlow69 = (1.0f - fSlow54);
		float fSlow70 = std::exp(((3.45387769f * (float(fEntry28) + 1.0f)) + -13.8155107f));
		float fSlow71 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((6.90775537f * (float(fEntry29) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((5.75646257f * (float(fEntry30) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow74 = (1.0f - fSlow73);
		float fSlow75 = (float(fEntry31) + 1.0f);
		float fSlow76 = (0.200000003f / (fSlow75 * ((fConst0 * fSlow70) + 1.0f)));
		float fSlow77 = (5.0f * fSlow75);
		float fSlow78 = (5.0f * (1.0f - (float(fEntry32) + 1.0f)));
		float fSlow79 = (0.117647059f / fSlow50);
		float fSlow80 = (1.0f / fSlow29);
		float fSlow81 = (fSlow41 + (fSlow44 + fSlow47));
		float fSlow82 = (0.294117659f / fSlow45);
		float fSlow83 = (fSlow53 * fSlow32);
		float fSlow84 = (0.5f * (fSlow38 / fSlow83));
		float fSlow85 = (1.0f / fSlow83);
		float fSlow86 = (1.0f - (0.5f * fSlow37));
		float fSlow87 = AmpMono_faustpower2_f((0.5f * fSlow38));
		float fSlow88 = (0.5f * (fSlow35 / fSlow87));
		float fSlow89 = (fSlow87 / fSlow32);
		float fSlow90 = (fSlow87 / fSlow83);
		float fSlow91 = (fSlow73 + -1.0f);
		float fSlow92 = (fSlow59 + -1.0f);
		float fSlow93 = (5.0f * fSlow65);
		int iSlow94 = (fSlow93 < 9.0f);
		int iSlow95 = (fSlow93 < 8.0f);
		int iSlow96 = (fSlow93 < 7.0f);
		int iSlow97 = (fSlow93 < 6.0f);
		int iSlow98 = (fSlow93 < 5.0f);
		int iSlow99 = (fSlow93 < 4.0f);
		int iSlow100 = (fSlow93 < 3.0f);
		int iSlow101 = (fSlow93 < 2.0f);
		int iSlow102 = (fSlow93 < 1.0f);
		float fSlow103 = std::pow(10.0f, (0.0500000007f * (iSlow94?(iSlow95?(iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?((fSlow93 < 0.0f)?-1.70000005f:(iSlow102?(-1.70000005f - (25.9500008f * fSlow65)):-6.88999987f)):(iSlow101?(-6.88999987f - (4.90999985f * (fSlow93 + -1.0f))):-11.8000002f)):(iSlow100?(-11.8000002f - (4.4000001f * (fSlow93 + -2.0f))):-16.2000008f)):(iSlow99?(-16.2000008f - (3.4000001f * (fSlow93 + -3.0f))):-19.6000004f)):(iSlow98?(-19.6000004f - (2.5f * (fSlow93 + -4.0f))):-22.1000004f)):(iSlow97?(-22.1000004f - (1.29999995f * (0.0f - (5.0f * (1.0f - fSlow65))))):-23.3999996f)):(iSlow96?(-23.3999996f - (0.200000003f * (fSlow93 + -6.0f))):-23.6000004f)):(iSlow95?((0.100000001f * (fSlow93 + -7.0f)) + -23.6000004f):-23.5f)):(iSlow94?(-23.5f - (0.699999988f * (fSlow93 + -8.0f))):-24.2000008f)):((fSlow93 < 10.0f)?(-24.2000008f - (1.60000002f * (fSlow93 + -9.0f))):-25.7999992f))));
		float fSlow104 = (1.0f / fSlow27);
		float fSlow105 = (1.0f - fSlow26);
		float fSlow106 = (1.0f / (fSlow25 * fSlow32));
		float fSlow107 = std::pow(10.0f, (0.0500000007f * (fSlow22 * ((18.0f * fSlow24) + (4.5f * fSlow23)))));
		float fSlow108 = float(fEntry33);
		float fSlow109 = ((fSlow108 * ((fSlow108 < 0.0f)?9.0f:14.0f)) + -14.0f);
		int iSlow110 = (fSlow109 > 0.0f);
		float fSlow111 = ((fSlow108 * ((fSlow22 < 0.0f)?800.0f:0.0f)) + 1200.0f);
		float fSlow112 = (fConst11 * (std::pow(10.0f, (0.0500000007f * std::fabs(fSlow109))) * fSlow111));
		float fSlow113 = (fConst11 * fSlow111);
		float fSlow114 = (iSlow110?fSlow113:fSlow112);
		float fSlow115 = ((fConst10 * (fConst10 - fSlow114)) + 1.0f);
		float fSlow116 = ((fConst10 * (fConst10 + fSlow114)) + 1.0f);
		float fSlow117 = (iSlow110?fSlow112:fSlow113);
		float fSlow118 = ((fConst10 * (fConst10 + fSlow117)) + 1.0f);
		float fSlow119 = ((fConst10 * (fConst10 - fSlow117)) + 1.0f);
		float fSlow120 = float(fEntry34);
		int iSlow121 = (fSlow120 < 0.0f);
		float fSlow122 = std::tan((fConst1 * ((iSlow121?(1500.0f * fSlow120):0.0f) + 2000.0f)));
		float fSlow123 = (1.0f / fSlow122);
		float fSlow124 = (1.0f - fSlow123);
		float fSlow125 = (fSlow123 + 1.0f);
		float fSlow126 = (0.0f - (1.0f / (fSlow122 * fSlow125)));
		float fSlow127 = (fSlow122 * fSlow116);
		float fSlow128 = std::pow(10.0f, ((0.0500000007f * fSlow120) * (iSlow121?18.0f:9.0f)));
		float fSlow129 = (250.0f * (float(fEntry35) + 1.0f));
		float fSlow130 = (1.0f / fSlow18);
		float fSlow131 = (1.0f - fSlow17);
		float fSlow132 = std::exp((0.0f - (fConst12 / std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -9.2103405f)))));
		float fSlow133 = (1.0f - fSlow132);
		float fSlow134 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow135 = (float(fEntry38) + 1.0f);
		float fSlow136 = std::exp(((4.60517025f * (float(fEntry39) + 1.0f)) + -9.2103405f));
		float fSlow137 = (0.0199999996f / (fSlow135 * ((fConst0 * fSlow136) + 1.0f)));
		float fSlow138 = (100.0f * (1.0f - (float(fEntry40) + 1.0f)));
		float fSlow139 = (50.0f * fSlow135);
		float fSlow140 = (1.0f - (1.0f / ((fConst0 * (fSlow136 * std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow141 = (fSlow13 * std::pow(fSlow11, fSlow12));
		float fSlow142 = std::pow((10.0f * (float(fEntry42) + 1.0f)), fSlow13);
		float fSlow143 = std::exp((0.0f - (fConst12 / std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f)))));
		float fSlow144 = (fSlow9 * (1.0f - fSlow143));
		float fSlow145 = (float(fEntry44) + 1.0f);
		float fSlow146 = (1.0f - fSlow145);
		float fSlow147 = ((10.0f * fSlow146) + fSlow8);
		float fSlow148 = (0.0294117648f / fSlow145);
		float fSlow149 = (float(fEntry45) + 1.0f);
		float fSlow150 = (5.0f * fSlow149);
		float fSlow151 = (0.0588235296f / fSlow149);
		float fSlow152 = (1.0f / fSlow6);
		float fSlow153 = (1.0f - fSlow5);
		float fSlow154 = (fSlow134 + fSlow10);
		float fSlow155 = (5.0f * fSlow20);
		int iSlow156 = (fSlow155 < 9.0f);
		int iSlow157 = (fSlow155 < 8.0f);
		int iSlow158 = (fSlow155 < 7.0f);
		int iSlow159 = (fSlow155 < 6.0f);
		int iSlow160 = (fSlow155 < 5.0f);
		int iSlow161 = (fSlow155 < 4.0f);
		int iSlow162 = (fSlow155 < 3.0f);
		int iSlow163 = (fSlow155 < 2.0f);
		int iSlow164 = (fSlow155 < 1.0f);
		float fSlow165 = std::pow(10.0f, (0.0500000007f * (iSlow156?(iSlow157?(iSlow158?(iSlow159?(iSlow160?(iSlow161?(iSlow162?(iSlow163?(iSlow164?((fSlow155 < 0.0f)?27.8999996f:(iSlow164?(27.8999996f - (30.0f * fSlow20)):21.8999996f)):(iSlow163?(21.8999996f - (6.0f * (fSlow155 + -1.0f))):15.8999996f)):(iSlow162?(15.8999996f - (5.94999981f * (fSlow155 + -2.0f))):9.94999981f)):(iSlow161?(9.94999981f - (5.96999979f * (fSlow155 + -3.0f))):3.98000002f)):(iSlow160?(3.98000002f - (5.53999996f * (fSlow155 + -4.0f))):-1.55999994f)):(iSlow159?(-1.55999994f - (4.67000008f * (0.0f - (5.0f * (1.0f - fSlow20))))):-6.23000002f)):(iSlow158?(-6.23000002f - (3.6099999f * (fSlow155 + -6.0f))):-9.84000015f)):(iSlow157?(-9.84000015f - (1.86000001f * (fSlow155 + -7.0f))):-11.6999998f)):(iSlow156?(-11.6999998f - (0.400000006f * (fSlow155 + -8.0f))):-12.1000004f)):((fSlow155 < 10.0f)?(-12.1000004f - (0.200000003f * (fSlow155 + -9.0f))):-12.3000002f))));
		float fSlow166 = (fConst130 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow66 * fTemp0);
			fRec9[0] = ((fSlow56 * fVec0[1]) + (fSlow67 * ((fSlow68 * fTemp0) - (fSlow69 * fRec9[1]))));
			fRec11[0] = ((fSlow74 * fRec11[1]) + (fSlow76 * (std::max<float>(0.0f, (fSlow77 - fRec11[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec9[0])) - fRec11[1])))));
			fRec10[0] = ((fSlow72 * fRec10[1]) + (fSlow71 * fRec11[0]));
			float fTemp1 = (fSlow52 + (fRec9[0] - fRec10[0]));
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = (std::fabs(fTemp2) + -2.0f);
			float fTemp4 = (std::min<float>(0.0f, fTemp1) + (2.5f * ((fSlow50 * (((std::fabs((fTemp3 * fTemp2)) + -2.0f) * fTemp3) * fTemp2)) - fSlow51)));
			float fTemp5 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow80 * std::fabs(fTemp4)) + -0.0500000007f)));
			float fTemp6 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow30 + fTemp4)), fSlow40) - fSlow41) * fTemp5) + (fSlow49 * (fTemp4 * (1.0f - fTemp5))))) - fSlow81);
			float fTemp7 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp6))));
			float fTemp8 = (std::fabs(fTemp7) + -2.0f);
			float fTemp9 = (std::max<float>(0.0f, fTemp6) + (fSlow47 * (((fTemp8 * (std::fabs((fTemp8 * fTemp7)) + -2.0f)) * fTemp7) + 1.0f)));
			fRec12[0] = ((fSlow62 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow44 + ((fTemp9 + -250.0f) - fSlow42))) - fRec12[1])) * std::max<float>(0.0f, (fSlow63 - fRec12[1])))) + (fSlow60 * fRec12[1]));
			float fTemp10 = (fSlow57 * fRec12[0]);
			float fTemp11 = (fSlow46 + ((fTemp9 + (-250.0f - fTemp10)) - fSlow42));
			float fTemp12 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow82 * std::max<float>(0.0f, fTemp11))));
			float fTemp13 = (std::fabs(fTemp12) + -2.0f);
			float fTemp14 = (fSlow43 + ((std::min<float>(0.0f, fTemp11) + (fTemp10 + (fSlow45 * (((fTemp12 * (std::fabs((fTemp12 * fTemp13)) + -2.0f)) * fTemp13) + -1.0f)))) + -50.0f));
			fVec1[0] = (fSlow64 * fTemp14);
			fRec8[0] = ((fSlow56 * fVec1[1]) + (fSlow67 * ((fSlow84 * fTemp14) - (fSlow69 * fRec8[1]))));
			fRec14[0] = ((fSlow74 * fRec14[1]) + (fSlow76 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec8[0])) - fRec14[1])) * std::max<float>(0.0f, (fSlow77 - fRec14[1])))));
			fRec13[0] = ((fSlow72 * fRec13[1]) + (fSlow71 * fRec14[0]));
			float fTemp15 = (fSlow52 + (fRec8[0] - fRec13[0]));
			float fTemp16 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp15))));
			float fTemp17 = (std::fabs(fTemp16) + -2.0f);
			float fTemp18 = (std::min<float>(0.0f, fTemp15) - (2.5f * (fSlow51 - (fSlow50 * (((std::fabs((fTemp16 * fTemp17)) + -2.0f) * fTemp16) * fTemp17)))));
			float fTemp19 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow80 * std::fabs(fTemp18)) + -0.0500000007f)));
			float fTemp20 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow30 + fTemp18)), fSlow40) - fSlow41) * fTemp19) + (fSlow49 * (fTemp18 * (1.0f - fTemp19))))) - fSlow81);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = ((std::fabs(fTemp21) + -2.0f) * fTemp21);
			float fTemp23 = ((fSlow47 * ((fTemp22 * (std::fabs(fTemp22) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp20));
			fRec7[0] = ((fSlow60 * fRec7[1]) + (fSlow62 * (std::max<float>(0.0f, (fSlow63 - fRec7[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow44 + ((fTemp23 + -250.0f) - fSlow42))) - fRec7[1])))));
			float fTemp24 = (fSlow57 * fRec7[0]);
			float fTemp25 = (fSlow46 + ((fTemp23 + (-250.0f - fTemp24)) - fSlow42));
			float fTemp26 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow82 * std::max<float>(0.0f, fTemp25))));
			float fTemp27 = (fTemp26 * (std::fabs(fTemp26) + -2.0f));
			float fTemp28 = (fSlow43 + ((fTemp24 + std::min<float>(0.0f, fTemp25)) + (-50.0f - (fSlow45 * (1.0f - (fTemp27 * (std::fabs(fTemp27) + -2.0f)))))));
			fVec2[0] = (fSlow33 * fTemp28);
			fRec6[0] = ((fSlow56 * fVec2[1]) - (fSlow67 * ((fSlow69 * fRec6[1]) - (fSlow85 * fTemp28))));
			fRec16[0] = ((fSlow74 * fRec16[1]) + (fSlow76 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec6[0])) - fRec16[1])) * std::max<float>(0.0f, (fSlow77 - fRec16[1])))));
			fRec15[0] = ((fSlow72 * fRec15[1]) + (fSlow71 * fRec16[0]));
			float fTemp29 = (fSlow52 + (fRec6[0] - fRec15[0]));
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (std::fabs(fTemp30) + -2.0f);
			float fTemp32 = (std::min<float>(0.0f, fTemp29) - (2.5f * (fSlow51 - (fSlow50 * ((fTemp30 * (std::fabs((fTemp30 * fTemp31)) + -2.0f)) * fTemp31)))));
			float fTemp33 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow80 * std::fabs(fTemp32)) + -0.0500000007f)));
			float fTemp34 = ((300.0f - ((fSlow49 * (fTemp32 * (1.0f - fTemp33))) + (fTemp33 * (std::pow(std::max<float>(0.0f, (fSlow30 + fTemp32)), fSlow40) - fSlow41)))) - fSlow81);
			float fTemp35 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp34))));
			float fTemp36 = ((std::fabs(fTemp35) + -2.0f) * fTemp35);
			float fTemp37 = ((fSlow47 * ((fTemp36 * (std::fabs(fTemp36) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp34));
			fRec17[0] = ((fSlow60 * fRec17[1]) + (fSlow62 * (std::max<float>(0.0f, (fSlow63 - fRec17[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow44 + ((fTemp37 + -250.0f) - fSlow42))) - fRec17[1])))));
			float fTemp38 = (fSlow57 * fRec17[0]);
			float fTemp39 = (fSlow46 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow42));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow82 * std::max<float>(0.0f, fTemp39))));
			float fTemp41 = (std::fabs(fTemp40) + -2.0f);
			float fTemp42 = ((fSlow39 * (fSlow43 + ((std::min<float>(0.0f, fTemp39) + fTemp38) + (-50.0f - (fSlow45 * (1.0f - (((std::fabs((fTemp41 * fTemp40)) + -2.0f) * fTemp41) * fTemp40))))))) + (fSlow86 * fTemp14));
			fVec3[0] = (fSlow89 * fTemp42);
			fRec20[0] = ((fSlow56 * fVec3[1]) - (fSlow67 * ((fSlow69 * fRec20[1]) - (fSlow90 * fTemp42))));
			fRec22[0] = ((fSlow76 * (std::max<float>(0.0f, (fSlow77 - fRec22[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec20[0])) - fRec22[1])))) - (fSlow91 * fRec22[1]));
			fRec21[0] = ((fSlow72 * fRec21[1]) + (fSlow71 * fRec22[0]));
			float fTemp43 = (fSlow52 + (fRec20[0] - fRec21[0]));
			float fTemp44 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp43))));
			float fTemp45 = (std::fabs(fTemp44) + -2.0f);
			float fTemp46 = (std::min<float>(0.0f, fTemp43) - (2.5f * (fSlow51 - (fSlow50 * ((fTemp44 * (std::fabs((fTemp44 * fTemp45)) + -2.0f)) * fTemp45)))));
			float fTemp47 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow80 * std::fabs(fTemp46)) + -0.0500000007f)));
			float fTemp48 = ((300.0f - ((fSlow49 * (fTemp46 * (1.0f - fTemp47))) + ((std::pow(std::max<float>(0.0f, (fSlow30 + fTemp46)), fSlow40) - fSlow41) * fTemp47))) - fSlow81);
			float fTemp49 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp48))));
			float fTemp50 = (std::fabs(fTemp49) + -2.0f);
			float fTemp51 = (std::max<float>(0.0f, fTemp48) + (fSlow47 * (((fTemp49 * (std::fabs((fTemp49 * fTemp50)) + -2.0f)) * fTemp50) + 1.0f)));
			fRec23[0] = ((fSlow62 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow44 + ((fTemp51 + -250.0f) - fSlow42))) - fRec23[1])) * std::max<float>(0.0f, (fSlow63 - fRec23[1])))) - (fSlow92 * fRec23[1]));
			float fTemp52 = (fSlow57 * fRec23[0]);
			float fTemp53 = (fSlow46 + ((fTemp51 + (-250.0f - fTemp52)) - fSlow42));
			float fTemp54 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow82 * std::max<float>(0.0f, fTemp53))));
			float fTemp55 = (std::fabs(fTemp54) + -2.0f);
			float fTemp56 = (fSlow43 + ((std::min<float>(0.0f, fTemp53) + fTemp52) + (-50.0f - (fSlow45 * (1.0f - ((fTemp55 * (std::fabs((fTemp55 * fTemp54)) + -2.0f)) * fTemp54))))));
			fVec4[0] = (fSlow33 * fTemp56);
			fRec19[0] = ((fSlow56 * fVec4[1]) - (fSlow67 * ((fSlow69 * fRec19[1]) - (fSlow85 * fTemp56))));
			fRec25[0] = ((fSlow76 * (std::max<float>(0.0f, (fSlow77 - fRec25[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec19[0])) - fRec25[1])))) + (fSlow74 * fRec25[1]));
			fRec24[0] = ((fSlow71 * fRec25[0]) + (fSlow72 * fRec24[1]));
			float fTemp57 = (fSlow52 + (fRec19[0] - fRec24[0]));
			float fTemp58 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow79 * std::max<float>(0.0f, fTemp57))));
			float fTemp59 = (std::fabs(fTemp58) + -2.0f);
			float fTemp60 = (std::min<float>(0.0f, fTemp57) - (2.5f * (fSlow51 - (fSlow50 * (((std::fabs((fTemp58 * fTemp59)) + -2.0f) * fTemp58) * fTemp59)))));
			float fTemp61 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow80 * std::fabs(fTemp60)) + -0.0500000007f)));
			float fTemp62 = ((300.0f - ((fTemp61 * (std::pow(std::max<float>(0.0f, (fSlow30 + fTemp60)), fSlow40) - fSlow41)) + (fSlow49 * (fTemp60 * (1.0f - fTemp61))))) - fSlow81);
			float fTemp63 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow48 * std::min<float>(0.0f, fTemp62))));
			float fTemp64 = (std::fabs(fTemp63) + -2.0f);
			float fTemp65 = ((fSlow47 * ((((std::fabs((fTemp64 * fTemp63)) + -2.0f) * fTemp64) * fTemp63) + 1.0f)) + std::max<float>(0.0f, fTemp62));
			fRec18[0] = ((fSlow60 * fRec18[1]) + (fSlow62 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow44 + ((fTemp65 + -250.0f) - fSlow42))) - fRec18[1])) * std::max<float>(0.0f, (fSlow63 - fRec18[1])))));
			float fTemp66 = (fSlow57 * fRec18[0]);
			float fTemp67 = (fSlow46 + ((fTemp65 + (-250.0f - fTemp66)) - fSlow42));
			float fTemp68 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow82 * std::max<float>(0.0f, fTemp67))));
			float fTemp69 = ((std::fabs(fTemp68) + -2.0f) * fTemp68);
			float fTemp70 = (((fSlow36 * fTemp42) + (fSlow88 * (fSlow43 + ((fTemp66 + std::min<float>(0.0f, fTemp67)) + (-50.0f - (fSlow45 * (1.0f - (fTemp69 * (std::fabs(fTemp69) + -2.0f))))))))) * fSlow103);
			float fTemp71 = (fSlow33 * fTemp70);
			fVec5[0] = fTemp71;
			fRec5[0] = ((fSlow28 * fVec5[1]) - (fSlow104 * ((fSlow105 * fRec5[1]) - (fSlow106 * fTemp70))));
			fRec26[0] = (0.0f - (fSlow104 * ((fSlow105 * fRec26[1]) - (fVec5[1] + fTemp71))));
			float fTemp72 = (fRec5[0] + (fSlow107 * fRec26[0]));
			fVec6[0] = fTemp72;
			fRec4[0] = ((fConst7 * fVec6[1]) - (fConst8 * ((fConst9 * fRec4[1]) - (fConst5 * fTemp72))));
			float fTemp73 = (fConst3 * fRec3[1]);
			fRec3[0] = (fRec4[0] - ((fTemp73 + (fRec3[2] * fSlow115)) / fSlow116));
			float fTemp74 = ((fTemp73 + (fRec3[0] * fSlow118)) + (fRec3[2] * fSlow119));
			float fTemp75 = (fTemp74 / fSlow116);
			fVec7[0] = fTemp75;
			fRec2[0] = (((fTemp75 + fVec7[1]) - (fSlow124 * fRec2[1])) / fSlow125);
			fRec27[0] = ((fSlow126 * fVec7[1]) - (((fRec27[1] * fSlow124) - (fTemp74 / fSlow127)) / fSlow125));
			float fTemp76 = ((fSlow21 * (fRec2[0] + (fRec27[0] * fSlow128))) - fSlow129);
			fVec8[0] = fTemp76;
			fRec1[0] = ((fSlow19 * fVec8[1]) - (fSlow130 * ((fSlow131 * fRec1[1]) - (fSlow17 * fTemp76))));
			fRec28[0] = ((fSlow132 * fRec28[1]) + (fSlow133 * (fRec1[0] - fSlow134)));
			fRec30[0] = ((fSlow137 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow138 + ((fRec1[0] - fRec28[0]) - fSlow134))) - fRec30[1])) * std::max<float>(0.0f, (fSlow139 - fRec30[1])))) + (fSlow140 * fRec30[1]));
			float fRec29 = fRec30[0];
			float fTemp77 = (fRec28[0] + fRec29);
			float fTemp78 = (0.0f - ((fRec1[0] - fTemp77) - fSlow134));
			float fTemp79 = (0.0f - fTemp78);
			float fTemp80 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow15 * std::fabs(fTemp79)) + -0.0500000007f)));
			float fTemp81 = (fSlow14 + (((fTemp80 * (std::pow(std::max<float>(0.0f, (fSlow10 + ((fRec1[0] + (30.0f - fTemp77)) - fSlow134))), fSlow13) - fSlow14)) + (fSlow141 * ((1.0f - fTemp80) * fTemp79))) - fSlow142));
			fRec31[0] = ((fSlow143 * fRec31[1]) + (fSlow144 * fTemp81));
			float fTemp82 = (((fSlow9 * fTemp81) - fRec31[0]) - fSlow147);
			float fTemp83 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow148 * std::max<float>(0.0f, fTemp82))));
			float fTemp84 = ((std::fabs(fTemp83) + -2.0f) * fTemp83);
			float fTemp85 = (fSlow8 + ((std::min<float>(0.0f, fTemp82) + (10.0f * (fSlow146 + (fSlow145 * (fTemp84 * (std::fabs(fTemp84) + -2.0f)))))) - fSlow150));
			float fTemp86 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow151 * std::min<float>(0.0f, fTemp85))));
			float fTemp87 = (std::fabs(fTemp86) + -2.0f);
			float fTemp88 = (std::max<float>(0.0f, fTemp85) + (fSlow150 * (((fTemp86 * (std::fabs((fTemp86 * fTemp87)) + -2.0f)) * fTemp87) + 1.0f)));
			fVec9[0] = fTemp88;
			fRec0[0] = ((fSlow7 * fVec9[1]) - (fSlow152 * ((fSlow153 * fRec0[1]) - (fSlow5 * fTemp88))));
			float fTemp89 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow15 * std::fabs(fTemp78)) + -0.0500000007f)));
			float fTemp90 = (fSlow14 + (((fTemp89 * (std::pow(std::max<float>(0.0f, (fSlow154 + (fTemp77 + (30.0f - fRec1[0])))), fSlow13) - fSlow14)) + (fSlow141 * (fTemp78 * (1.0f - fTemp89)))) - fSlow142));
			fRec33[0] = ((fSlow143 * fRec33[1]) + (fSlow144 * fTemp90));
			float fTemp91 = (((fSlow9 * fTemp90) - fRec33[0]) - fSlow147);
			float fTemp92 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow148 * std::max<float>(0.0f, fTemp91))));
			float fTemp93 = (std::fabs(fTemp92) + -2.0f);
			float fTemp94 = (fSlow8 + ((std::min<float>(0.0f, fTemp91) + (10.0f * (fSlow146 + (fSlow145 * (((std::fabs((fTemp92 * fTemp93)) + -2.0f) * fTemp92) * fTemp93))))) - fSlow150));
			float fTemp95 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow151 * std::min<float>(0.0f, fTemp94))));
			float fTemp96 = (std::fabs(fTemp95) + -2.0f);
			float fTemp97 = (std::max<float>(0.0f, fTemp94) + (fSlow150 * (((fTemp95 * (std::fabs((fTemp95 * fTemp96)) + -2.0f)) * fTemp96) + 1.0f)));
			fVec10[0] = fTemp97;
			fRec32[0] = ((fSlow7 * fVec10[1]) - (fSlow152 * ((fSlow153 * fRec32[1]) - (fSlow5 * fTemp97))));
			float fTemp98 = ((fRec0[0] - fRec32[0]) * fSlow165);
			float fTemp99 = (fSlow3 * fTemp98);
			fVec11[0] = fTemp99;
			fRec56[0] = ((fConst128 * fVec11[1]) + (fConst129 * ((fSlow166 * fTemp98) - (fConst131 * fRec56[1]))));
			fRec55[0] = (0.0f - (fConst123 * ((fConst124 * fRec55[1]) - (fRec56[0] + fRec56[1]))));
			fRec54[0] = (fConst121 * ((fRec55[0] + fRec55[1]) - (fConst132 * fRec54[1])));
			fRec53[0] = (fRec54[0] - (fConst119 * ((fConst135 * fRec53[1]) + (fConst136 * fRec53[2]))));
			fRec52[0] = ((fConst119 * (fRec53[2] + (fRec53[0] + (2.0f * fRec53[1])))) - (fConst118 * ((fConst137 * fRec52[2]) + (fConst135 * fRec52[1]))));
			fRec51[0] = ((fConst118 * ((fRec52[0] + (2.0f * fRec52[1])) + fRec52[2])) - (fConst117 * ((fConst138 * fRec51[2]) + (fConst135 * fRec51[1]))));
			fRec50[0] = ((fConst117 * ((fRec51[0] + (2.0f * fRec51[1])) + fRec51[2])) - (fConst116 * ((fConst135 * fRec50[1]) + (fConst139 * fRec50[2]))));
			fRec49[0] = ((fConst116 * ((fRec50[0] + (2.0f * fRec50[1])) + fRec50[2])) - (fConst115 * ((fConst140 * fRec49[2]) + (fConst135 * fRec49[1]))));
			fRec62[0] = ((fConst142 * fRec55[1]) - (fConst121 * ((fConst132 * fRec62[1]) - (fConst114 * fRec55[0]))));
			fRec61[0] = (fRec62[0] - (fConst119 * ((fConst136 * fRec61[2]) + (fConst135 * fRec61[1]))));
			fRec60[0] = ((fConst119 * (((fConst141 * fRec61[1]) + (fConst134 * fRec61[0])) + (fConst134 * fRec61[2]))) - (fConst118 * ((fConst137 * fRec60[2]) + (fConst135 * fRec60[1]))));
			fRec59[0] = ((fConst118 * ((fConst134 * fRec60[2]) + ((fConst134 * fRec60[0]) + (fConst141 * fRec60[1])))) - (fConst117 * ((fConst138 * fRec59[2]) + (fConst135 * fRec59[1]))));
			fRec58[0] = ((fConst117 * ((fConst134 * fRec59[2]) + ((fConst134 * fRec59[0]) + (fConst141 * fRec59[1])))) - (fConst116 * ((fConst139 * fRec58[2]) + (fConst135 * fRec58[1]))));
			fRec57[0] = ((fConst116 * (((fConst141 * fRec58[1]) + (fConst134 * fRec58[0])) + (fConst134 * fRec58[2]))) - (fConst115 * ((fConst140 * fRec57[2]) + (fConst135 * fRec57[1]))));
			float fTemp100 = (fConst143 * fRec48[1]);
			fRec48[0] = ((fConst115 * ((fRec49[2] + (fRec49[0] + (2.0f * fRec49[1]))) + (0.13673377f * ((fConst134 * fRec57[2]) + ((fConst134 * fRec57[0]) + (fConst141 * fRec57[1])))))) - (fConst110 * (fTemp100 + (fConst144 * fRec48[2]))));
			float fTemp101 = (fConst105 * fRec47[1]);
			fRec47[0] = ((fConst110 * (((fConst112 * fRec48[0]) + fTemp100) + (fConst145 * fRec48[2]))) - (fConst104 * ((fConst146 * fRec47[2]) + fTemp101)));
			float fTemp102 = (fConst99 * fRec46[1]);
			fRec46[0] = ((fConst104 * ((fTemp101 + (fConst148 * fRec47[0])) + (fConst149 * fRec47[2]))) - (fConst98 * (fTemp102 + (fConst150 * fRec46[2]))));
			float fTemp103 = (fConst154 * fRec45[1]);
			fRec45[0] = ((fConst98 * ((fTemp102 + (fConst152 * fRec46[0])) + (fConst153 * fRec46[2]))) - (fConst91 * (fTemp103 + (fConst155 * fRec45[2]))));
			float fTemp104 = (fConst157 * fRec44[1]);
			fRec44[0] = ((fConst91 * ((fConst93 * fRec45[2]) + (fTemp103 + (fConst156 * fRec45[0])))) - (fConst84 * (fTemp104 + (fConst158 * fRec44[2]))));
			float fTemp105 = (fConst161 * fRec43[1]);
			fRec43[0] = ((fConst84 * ((fConst86 * fRec44[2]) + (fTemp104 + (fConst159 * fRec44[0])))) - (fConst77 * ((fConst160 * fRec43[2]) + fTemp105)));
			float fTemp106 = (fConst164 * fRec42[1]);
			fRec42[0] = ((fConst77 * ((fConst79 * fRec43[2]) + (fTemp105 + (fConst162 * fRec43[0])))) - (fConst70 * ((fConst163 * fRec42[2]) + fTemp106)));
			float fTemp107 = (fConst166 * fRec41[1]);
			fRec41[0] = ((fConst70 * (((fConst72 * fRec42[0]) + fTemp106) + (fConst165 * fRec42[2]))) - (fConst63 * (fTemp107 + (fConst167 * fRec41[2]))));
			float fTemp108 = (fConst58 * fRec40[1]);
			fRec40[0] = ((fConst63 * (((fConst65 * fRec41[0]) + fTemp107) + (fConst168 * fRec41[2]))) - (fConst57 * (fTemp108 + (fConst169 * fRec40[2]))));
			float fTemp109 = (fConst173 * fRec39[1]);
			fRec39[0] = ((fConst57 * ((fTemp108 + (fConst171 * fRec40[0])) + (fConst172 * fRec40[2]))) - (fConst50 * (fTemp109 + (fConst174 * fRec39[2]))));
			float fTemp110 = (fConst45 * fRec38[1]);
			fRec38[0] = ((fConst50 * ((fConst52 * fRec39[2]) + ((fConst175 * fRec39[0]) + fTemp109))) - (fConst44 * ((fConst176 * fRec38[2]) + fTemp110)));
			float fTemp111 = (fConst181 * fRec37[1]);
			fRec37[0] = ((fConst44 * ((fTemp110 + (fConst178 * fRec38[0])) + (fConst179 * fRec38[2]))) - (fConst37 * ((fConst180 * fRec37[2]) + fTemp111)));
			float fTemp112 = (fConst32 * fRec36[1]);
			fRec36[0] = ((fConst37 * ((fConst39 * fRec37[2]) + (fTemp111 + (fConst182 * fRec37[0])))) - (fConst31 * ((fConst183 * fRec36[2]) + fTemp112)));
			float fTemp113 = (fConst26 * fRec35[1]);
			fRec35[0] = ((fConst31 * ((fTemp112 + (fConst185 * fRec36[0])) + (fConst186 * fRec36[2]))) - (fConst25 * (fTemp113 + (fConst187 * fRec35[2]))));
			float fTemp114 = (fConst192 * fRec34[1]);
			fRec34[0] = ((fConst25 * ((fTemp113 + (fConst189 * fRec35[0])) + (fConst190 * fRec35[2]))) - (fConst191 * (fTemp114 + (fConst193 * fRec34[2]))));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst18 * ((fConst20 * fRec34[2]) + (fTemp114 + (fConst194 * fRec34[0])))):fTemp99)));
			fVec0[1] = fVec0[0];
			fRec9[1] = fRec9[0];
			fRec11[1] = fRec11[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fVec1[1] = fVec1[0];
			fRec8[1] = fRec8[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec7[1] = fRec7[0];
			fVec2[1] = fVec2[0];
			fRec6[1] = fRec6[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fRec17[1] = fRec17[0];
			fVec3[1] = fVec3[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec23[1] = fRec23[0];
			fVec4[1] = fVec4[0];
			fRec19[1] = fRec19[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec18[1] = fRec18[0];
			fVec5[1] = fVec5[0];
			fRec5[1] = fRec5[0];
			fRec26[1] = fRec26[0];
			fVec6[1] = fVec6[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fVec7[1] = fVec7[0];
			fRec2[1] = fRec2[0];
			fRec27[1] = fRec27[0];
			fVec8[1] = fVec8[0];
			fRec1[1] = fRec1[0];
			fRec28[1] = fRec28[0];
			fRec30[1] = fRec30[0];
			fRec31[1] = fRec31[0];
			fVec9[1] = fVec9[0];
			fRec0[1] = fRec0[0];
			fRec33[1] = fRec33[0];
			fVec10[1] = fVec10[0];
			fRec32[1] = fRec32[0];
			fVec11[1] = fVec11[0];
			fRec56[1] = fRec56[0];
			fRec55[1] = fRec55[0];
			fRec54[1] = fRec54[0];
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
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			fRec35[2] = fRec35[1];
			fRec35[1] = fRec35[0];
			fRec34[2] = fRec34[1];
			fRec34[1] = fRec34[0];

		}

	}


};

#endif
