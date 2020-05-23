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
	FAUSTFLOAT fEntry10;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
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
	float fRec11[2];
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	float fRec13[2];
	float fRec12[2];
	FAUSTFLOAT fEntry32;
	float fRec10[2];
	FAUSTFLOAT fEntry33;
	float fVec1[2];
	float fRec9[2];
	float fRec15[2];
	float fRec14[2];
	float fRec8[2];
	float fVec2[2];
	float fRec7[2];
	float fRec17[2];
	float fRec16[2];
	float fRec6[2];
	float fVec3[2];
	float fRec20[2];
	float fRec22[2];
	float fRec21[2];
	float fRec19[2];
	float fVec4[2];
	float fRec18[2];
	float fRec24[2];
	float fRec23[2];
	float fRec25[2];
	float fVec5[2];
	float fRec5[2];
	float fRec26[2];
	float fVec6[2];
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fRec27[2];
	float fConst15;
	float fConst16;
	FAUSTFLOAT fEntry34;
	float fConst17;
	float fConst18;
	float fRec4[3];
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
	float fRec28[3];
	float fVec7[2];
	float fRec3[2];
	float fConst29;
	float fRec29[2];
	FAUSTFLOAT fEntry35;
	float fVec8[2];
	float fConst30;
	float fRec2[2];
	FAUSTFLOAT fEntry36;
	float fVec9[2];
	float fRec1[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	float fRec30[2];
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fRec32[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	float fRec34[2];
	FAUSTFLOAT fEntry48;
	float fVec10[2];
	float fRec0[2];
	float fRec37[2];
	float fVec11[2];
	float fRec35[2];
	float fVec12[2];
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
	float fConst152;
	float fRec60[2];
	float fRec59[2];
	float fConst153;
	float fConst154;
	float fRec58[2];
	float fConst155;
	float fConst156;
	float fRec57[3];
	float fConst157;
	float fConst158;
	float fRec56[3];
	float fConst159;
	float fRec55[3];
	float fConst160;
	float fRec54[3];
	float fConst161;
	float fRec53[3];
	float fRec66[2];
	float fRec65[3];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fConst162;
	float fConst163;
	float fRec52[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fRec51[3];
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec50[3];
	float fConst170;
	float fConst171;
	float fRec49[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec48[3];
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec47[3];
	float fConst181;
	float fConst182;
	float fRec46[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec45[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec44[3];
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec43[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec42[3];
	float fConst198;
	float fConst199;
	float fConst200;
	float fRec41[3];
	float fConst201;
	float fConst202;
	float fRec40[3];
	float fConst203;
	float fConst204;
	float fConst205;
	float fConst206;
	float fConst207;
	float fRec39[3];
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec38[3];
	float fConst212;

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
		fConst2 = (1.0f / std::tan((50265.4844f / fConst0)));
		fConst3 = (1.0f / (fConst2 + 1.0f));
		fConst4 = std::tan((6283.18555f / fConst0));
		fConst5 = (1.0f / fConst4);
		fConst6 = (fConst5 + 1.0f);
		fConst7 = (1.0f / fConst6);
		fConst8 = (1.0f - fConst5);
		fConst9 = std::tan((78.5398178f / fConst0));
		fConst10 = (1.0f / fConst9);
		fConst11 = (fConst10 + 1.0f);
		fConst12 = (0.0f - (1.0f / (fConst9 * fConst11)));
		fConst13 = (1.0f / fConst11);
		fConst14 = (1.0f - fConst10);
		fConst15 = std::tan((1382.30078f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst18 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst15))));
		fConst19 = (1.0f / fConst0);
		fConst20 = std::tan((1696.46008f / fConst0));
		fConst21 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * fConst20) * std::tan((1068.14148f / fConst0))))));
		fConst22 = (AmpMono_faustpower2_f(fConst19) * fConst21);
		fConst23 = (fConst0 * fConst20);
		fConst24 = (2.0f * (((2.0f * fConst23) - (0.5f * (fConst21 / fConst23))) / fConst0));
		fConst25 = (1.0f / ((fConst22 + fConst24) + 4.0f));
		fConst26 = (fConst22 + 4.0f);
		fConst27 = (fConst22 + (4.0f - fConst24));
		fConst28 = ((2.0f * fConst22) + -8.0f);
		fConst29 = (0.0f - (1.0f / (fConst4 * fConst6)));
		fConst30 = (1.0f - fConst2);
		fConst31 = std::tan((5574.98535f / fConst0));
		fConst32 = (1.0f / fConst31);
		fConst33 = (fConst0 * std::sin((11149.9707f / fConst0)));
		fConst34 = (4376.67188f / fConst33);
		fConst35 = (((fConst32 + fConst34) / fConst31) + 1.0f);
		fConst36 = (0.144011721f / fConst35);
		fConst37 = (2760.92456f / fConst33);
		fConst38 = (((fConst32 - fConst37) / fConst31) + 1.0f);
		fConst39 = std::tan((4288.271f / fConst0));
		fConst40 = (1.0f / fConst39);
		fConst41 = (fConst0 * std::sin((8576.54199f / fConst0)));
		fConst42 = (326.939972f / fConst41);
		fConst43 = (1.0f / (((fConst40 + fConst42) / fConst39) + 1.0f));
		fConst44 = (190.645706f / fConst41);
		fConst45 = (((fConst40 + fConst44) / fConst39) + 1.0f);
		fConst46 = std::tan((3537.37793f / fConst0));
		fConst47 = (1.0f / fConst46);
		fConst48 = (fConst0 * std::sin((7074.75586f / fConst0)));
		fConst49 = (642.945251f / fConst48);
		fConst50 = (1.0f / (((fConst47 + fConst49) / fConst46) + 1.0f));
		fConst51 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst46))));
		fConst52 = std::tan((3081.90234f / fConst0));
		fConst53 = (1.0f / fConst52);
		fConst54 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst55 = (486.410919f / fConst54);
		fConst56 = (1.0f / (((fConst53 + fConst55) / fConst52) + 1.0f));
		fConst57 = (183.178085f / fConst54);
		fConst58 = (((fConst53 - fConst57) / fConst52) + 1.0f);
		fConst59 = std::tan((2592.47217f / fConst0));
		fConst60 = (1.0f / fConst59);
		fConst61 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst62 = (317.628265f / fConst61);
		fConst63 = (1.0f / (((fConst60 + fConst62) / fConst59) + 1.0f));
		fConst64 = (148.323349f / fConst61);
		fConst65 = (((fConst60 + fConst64) / fConst59) + 1.0f);
		fConst66 = std::tan((1891.23853f / fConst0));
		fConst67 = (1.0f / fConst66);
		fConst68 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst69 = (265.978119f / fConst68);
		fConst70 = (1.0f / (((fConst67 + fConst69) / fConst66) + 1.0f));
		fConst71 = (116.345184f / fConst68);
		fConst72 = (((fConst67 - fConst71) / fConst66) + 1.0f);
		fConst73 = std::tan((21179.4824f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((42358.9648f / fConst0)));
		fConst76 = (7223.21826f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (1059.12756f / fConst75);
		fConst79 = (((fConst74 + fConst78) / fConst73) + 1.0f);
		fConst80 = std::tan((15066.6357f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst83 = (11187.3662f / fConst82);
		fConst84 = (1.0f / (((fConst81 + fConst83) / fConst80) + 1.0f));
		fConst85 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst80))));
		fConst86 = std::tan((13437.668f / fConst0));
		fConst87 = (1.0f / fConst86);
		fConst88 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst89 = (13245.1885f / fConst88);
		fConst90 = (1.0f / (((fConst87 + fConst89) / fConst86) + 1.0f));
		fConst91 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst86))));
		fConst92 = std::tan((10058.502f / fConst0));
		fConst93 = (1.0f / fConst92);
		fConst94 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst95 = (4926.20459f / fConst94);
		fConst96 = (1.0f / (((fConst93 + fConst95) / fConst92) + 1.0f));
		fConst97 = (9024.73242f / fConst94);
		fConst98 = (((fConst93 - fConst97) / fConst92) + 1.0f);
		fConst99 = std::tan((8136.54736f / fConst0));
		fConst100 = (1.0f / fConst99);
		fConst101 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst102 = (966.024841f / fConst101);
		fConst103 = (1.0f / (((fConst100 + fConst102) / fConst99) + 1.0f));
		fConst104 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst99))));
		fConst105 = std::tan((8011.02734f / fConst0));
		fConst106 = (1.0f / fConst105);
		fConst107 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst108 = (1613.9762f / fConst107);
		fConst109 = (1.0f / (((fConst106 + fConst108) / fConst105) + 1.0f));
		fConst110 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst105))));
		fConst111 = std::tan((9456.15234f / fConst0));
		fConst112 = (1.0f / fConst111);
		fConst113 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst114 = (2492.29883f / fConst113);
		fConst115 = (1.0f / (((fConst112 + fConst114) / fConst111) + 1.0f));
		fConst116 = (974.257141f / fConst113);
		fConst117 = (((fConst112 - fConst116) / fConst111) + 1.0f);
		fConst118 = std::tan((2827.43262f / fConst0));
		fConst119 = (1.0f / fConst118);
		fConst120 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst121 = (19634.3262f / fConst120);
		fConst122 = (1.0f / (((fConst119 + fConst121) / fConst118) + 1.0f));
		fConst123 = (106249.391f / fConst120);
		fConst124 = (((fConst119 + fConst123) / fConst118) + 1.0f);
		fConst125 = std::tan((375.293884f / fConst0));
		fConst126 = (1.0f / fConst125);
		fConst127 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst128 = (463.734222f / fConst127);
		fConst129 = (1.0f / (((fConst126 + fConst128) / fConst125) + 1.0f));
		fConst130 = (3220.11475f / fConst127);
		fConst131 = (((fConst126 + fConst130) / fConst125) + 1.0f);
		fConst132 = std::tan((18369.8027f / fConst0));
		fConst133 = (1.0f / fConst132);
		fConst134 = (1.0f / (((fConst133 + 0.284629673f) / fConst132) + 1.0f));
		fConst135 = AmpMono_faustpower2_f(fConst132);
		fConst136 = (1.0f / fConst135);
		fConst137 = (1.0f / (((fConst133 + 0.830830038f) / fConst132) + 1.0f));
		fConst138 = (1.0f / (((fConst133 + 1.30972147f) / fConst132) + 1.0f));
		fConst139 = (1.0f / (((fConst133 + 1.68250704f) / fConst132) + 1.0f));
		fConst140 = (1.0f / (((fConst133 + 1.91898596f) / fConst132) + 1.0f));
		fConst141 = (fConst133 + 1.0f);
		fConst142 = (0.0f - (1.0f / (fConst132 * fConst141)));
		fConst143 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst144 = (1.0f / (fConst143 + 1.0f));
		fConst145 = (1.0f - fConst143);
		fConst146 = std::tan((452.102844f / fConst0));
		fConst147 = (1.0f / fConst146);
		fConst148 = (fConst147 + 1.0f);
		fConst149 = (1.0f / fConst148);
		fConst150 = (0.0199999996f / fConst146);
		fConst151 = (1.0f - fConst147);
		fConst152 = (0.0f - (1.0f / (fConst146 * fConst148)));
		fConst153 = (1.0f / fConst141);
		fConst154 = (1.0f - fConst133);
		fConst155 = (((fConst133 + -1.91898596f) / fConst132) + 1.0f);
		fConst156 = (2.0f * (1.0f - fConst136));
		fConst157 = (0.0f - (2.0f / fConst135));
		fConst158 = (((fConst133 + -1.68250704f) / fConst132) + 1.0f);
		fConst159 = (((fConst133 + -1.30972147f) / fConst132) + 1.0f);
		fConst160 = (((fConst133 + -0.830830038f) / fConst132) + 1.0f);
		fConst161 = (((fConst133 + -0.284629673f) / fConst132) + 1.0f);
		fConst162 = (((fConst126 - fConst128) / fConst125) + 1.0f);
		fConst163 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst125))));
		fConst164 = (((fConst126 - fConst130) / fConst125) + 1.0f);
		fConst165 = (((fConst119 - fConst121) / fConst118) + 1.0f);
		fConst166 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst118))));
		fConst167 = (((fConst119 - fConst123) / fConst118) + 1.0f);
		fConst168 = (((fConst112 - fConst114) / fConst111) + 1.0f);
		fConst169 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst111))));
		fConst170 = (((fConst112 + fConst116) / fConst111) + 1.0f);
		fConst171 = (((fConst106 - fConst108) / fConst105) + 1.0f);
		fConst172 = (3097.15845f / fConst107);
		fConst173 = (((fConst106 + fConst172) / fConst105) + 1.0f);
		fConst174 = (((fConst106 - fConst172) / fConst105) + 1.0f);
		fConst175 = (((fConst100 - fConst102) / fConst99) + 1.0f);
		fConst176 = (518.801147f / fConst101);
		fConst177 = (((fConst100 + fConst176) / fConst99) + 1.0f);
		fConst178 = (((fConst100 - fConst176) / fConst99) + 1.0f);
		fConst179 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst92))));
		fConst180 = (((fConst93 - fConst95) / fConst92) + 1.0f);
		fConst181 = (((fConst93 + fConst97) / fConst92) + 1.0f);
		fConst182 = (((fConst87 - fConst89) / fConst86) + 1.0f);
		fConst183 = (4583.19189f / fConst88);
		fConst184 = (((fConst87 + fConst183) / fConst86) + 1.0f);
		fConst185 = (((fConst87 - fConst183) / fConst86) + 1.0f);
		fConst186 = (((fConst81 - fConst83) / fConst80) + 1.0f);
		fConst187 = (36783.4805f / fConst82);
		fConst188 = (((fConst81 + fConst187) / fConst80) + 1.0f);
		fConst189 = (((fConst81 - fConst187) / fConst80) + 1.0f);
		fConst190 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst191 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst192 = (((fConst74 - fConst78) / fConst73) + 1.0f);
		fConst193 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst194 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst195 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst196 = (((fConst60 - fConst62) / fConst59) + 1.0f);
		fConst197 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst59))));
		fConst198 = (((fConst60 - fConst64) / fConst59) + 1.0f);
		fConst199 = (((fConst53 - fConst55) / fConst52) + 1.0f);
		fConst200 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst52))));
		fConst201 = (((fConst53 + fConst57) / fConst52) + 1.0f);
		fConst202 = (((fConst47 - fConst49) / fConst46) + 1.0f);
		fConst203 = (270.569763f / fConst48);
		fConst204 = (((fConst47 + fConst203) / fConst46) + 1.0f);
		fConst205 = (((fConst47 - fConst203) / fConst46) + 1.0f);
		fConst206 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst39))));
		fConst207 = (((fConst40 - fConst42) / fConst39) + 1.0f);
		fConst208 = (((fConst40 - fConst44) / fConst39) + 1.0f);
		fConst209 = (1.0f / fConst35);
		fConst210 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst31))));
		fConst211 = (((fConst32 - fConst34) / fConst31) + 1.0f);
		fConst212 = (((fConst32 + fConst37) / fConst31) + 1.0f);

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
			fRec11[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec13[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec12[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec10[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fVec1[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec9[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec15[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fRec14[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec8[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fVec2[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec7[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec17[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec16[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec6[l14] = 0.0f;

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
			fRec19[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec4[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec18[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec24[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec23[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec25[l24] = 0.0f;

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
			fRec27[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec4[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec28[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec7[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec3[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec29[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fVec8[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec2[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fVec9[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec1[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec30[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fRec32[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec34[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec10[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec0[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec37[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec11[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec35[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec12[l47] = 0.0f;

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

	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry15 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry25 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry26 = value + 0.000000e+00; }
	void set_tetrode_grid_cap(FAUSTFLOAT value) { fEntry39 = value + 4.705513e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry41 = value + 4.248187e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry36 = value + 4.772657e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry38 = value + -2.047729e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry42 = value + 6.319992e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry40 = value + -6.194208e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry37 = value + -1.524618e-05; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry9 = value + -8.210805e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry7 = value + 2.877502e+00; }
	void set_tetrode_plate_cap(FAUSTFLOAT value) { fEntry44 = value + -3.345749e-01; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry4 = value + 9.485173e-02; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry5 = value + -1.863619e-01; }
	void set_tetrode_plate_corner_b(FAUSTFLOAT value) { fEntry48 = value + 4.841291e-01; }
	void set_tetrode_plate_hp(FAUSTFLOAT value) { fEntry3 = value + -1.340787e-01; }
	void set_tetrode_plate_level(FAUSTFLOAT value) { fEntry46 = value + -3.287533e-01; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry43 = value + 5.323228e+00; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00; }
	void set_tetrode_plate_ratio(FAUSTFLOAT value) { fEntry47 = value + 1.490313e+01; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry6 = value + -6.237636e-01; }
	void set_tetrode_plate_tau(FAUSTFLOAT value) { fEntry45 = value + -1.587482e-01; }
	void set_triode_grid_cap(FAUSTFLOAT value) { fEntry29 = value + 9.879311e+00; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry23 = value + 1.826776e-01; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry22 = value + -4.062809e-01; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry30 = value + 3.382156e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry31 = value + 1.241746e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry28 = value + 1.569347e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry27 = value + -1.412077e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry24 = value + 4.521873e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry12 = value + -6.884415e-02; }
	void set_triode_plate_cap_b(FAUSTFLOAT value) { fEntry18 = value + -7.078197e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry20 = value + 7.121018e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry21 = value + -3.080321e-01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry16 = value + -1.911161e-01; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry32 = value + 6.690960e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.534145e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry17 = value + -2.505888e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry33 = value + -1.098385e-01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry19 = value + -4.565296e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry35 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry34 = value + 0.000000e+00; }
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
		set_tetrode_plate_cap(0.0f);
		set_tetrode_plate_clip(0.0f);
		set_tetrode_plate_corner(0.0f);
		set_tetrode_plate_corner_b(0.0f);
		set_tetrode_plate_hp(0.0f);
		set_tetrode_plate_level(0.0f);
		set_tetrode_plate_point(0.0f);
		set_tetrode_plate_power(0.0f);
		set_tetrode_plate_ratio(0.0f);
		set_tetrode_plate_scale(0.0f);
		set_tetrode_plate_tau(0.0f);
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
		float fSlow0 = (0.501187205f * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f)))))));
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = (float(fEntry2) + 1.0f);
		float fSlow3 = (0.0199999996f / fSlow2);
		float fSlow4 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry3) + 1.0f)) + -2.30258512f))));
		float fSlow5 = (1.0f / fSlow4);
		float fSlow6 = (fSlow5 + 1.0f);
		float fSlow7 = (0.0f - (1.0f / (fSlow4 * fSlow6)));
		float fSlow8 = (20.0f * (float(fEntry4) + 1.0f));
		float fSlow9 = (float(fEntry5) + 1.0f);
		float fSlow10 = (1.0f - fSlow9);
		float fSlow11 = (0.100000001f / fSlow9);
		float fSlow12 = std::exp(((4.60517025f * (float(fEntry6) + 1.0f)) + -4.60517025f));
		float fSlow13 = (10.0f * (float(fEntry7) + 1.0f));
		float fSlow14 = (fSlow13 + 30.0f);
		float fSlow15 = (0.5f * (float(fEntry8) + 1.0f));
		float fSlow16 = (fSlow15 + 1.0f);
		float fSlow17 = std::pow(fSlow14, fSlow16);
		float fSlow18 = (10.0f / fSlow14);
		float fSlow19 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry9) + 1.0f)) + -2.30258512f))));
		float fSlow20 = (1.0f / fSlow19);
		float fSlow21 = (fSlow20 + 1.0f);
		float fSlow22 = (0.0f - (1.0f / (fSlow21 * fSlow19)));
		float fSlow23 = (float(fEntry10) + 1.0f);
		float fSlow24 = (50.0f * (fSlow2 * std::exp(((3.45387769f * fSlow23) + -2.30258512f))));
		float fSlow25 = float(fEntry11);
		int iSlow26 = (fSlow25 > 0.0f);
		float fSlow27 = std::tan((fConst1 * float((iSlow26?100:50))));
		float fSlow28 = (1.0f / fSlow27);
		float fSlow29 = (fSlow28 + 1.0f);
		float fSlow30 = (0.0f - (1.0f / (fSlow27 * fSlow29)));
		float fSlow31 = (float(fEntry12) + 1.0f);
		float fSlow32 = (10.0f * fSlow31);
		float fSlow33 = (0.5f * (float(fEntry13) + 1.0f));
		float fSlow34 = std::pow(fSlow32, fSlow33);
		float fSlow35 = (1.0f / fSlow34);
		float fSlow36 = float(fEntry14);
		float fSlow37 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow36) + -3.0f));
		float fSlow38 = (1.0f - (0.5f * fSlow37));
		float fSlow39 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow36) + -1.0f));
		float fSlow40 = ((float(fEntry15) + 1.0f) + 1.0f);
		float fSlow41 = (fSlow39 / fSlow40);
		float fSlow42 = (fSlow33 + 1.0f);
		float fSlow43 = std::pow(fSlow32, fSlow42);
		float fSlow44 = (37.5f * (float(fEntry16) + 1.0f));
		float fSlow45 = (fSlow43 + fSlow44);
		float fSlow46 = std::exp(((3.45387769f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow47 = (float(fEntry18) + 1.0f);
		float fSlow48 = std::exp(((4.60517025f * (float(fEntry19) + 1.0f)) + -9.2103405f));
		float fSlow49 = (0.0199999996f / (fSlow47 * ((fConst0 * fSlow48) + 1.0f)));
		float fSlow50 = (150.0f * (float(fEntry20) + 1.0f));
		float fSlow51 = std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -2.30258512f));
		float fSlow52 = (1.0f / fSlow51);
		float fSlow53 = (float(fEntry22) + 1.0f);
		float fSlow54 = (fSlow53 - (float(fEntry23) + 1.0f));
		float fSlow55 = (2.5f * fSlow54);
		float fSlow56 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry24) + 1.0f)) + -2.30258512f))));
		float fSlow57 = (1.0f / fSlow56);
		float fSlow58 = (fSlow57 + 1.0f);
		float fSlow59 = (0.0f - (1.0f / (fSlow58 * fSlow56)));
		float fSlow60 = (1.0f / fSlow31);
		float fSlow61 = (0.5f * (fSlow40 / fSlow34));
		float fSlow62 = (0.400000006f / fSlow53);
		float fSlow63 = (float(fEntry26) + 1.0f);
		float fSlow64 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry25) + 1.0f)))))) * std::exp(((2.99573231f * fSlow63) + -0.693147182f)));
		float fSlow65 = (1.0f / fSlow58);
		float fSlow66 = (1.0f - fSlow57);
		float fSlow67 = (fSlow64 / fSlow56);
		float fSlow68 = std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -13.8155107f));
		float fSlow69 = (1.0f / ((fConst0 * (fSlow68 * std::exp(((6.90775537f * (float(fEntry28) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow70 = (1.0f - fSlow69);
		float fSlow71 = (float(fEntry29) + 1.0f);
		float fSlow72 = (0.200000003f / (fSlow71 * ((fConst0 * fSlow68) + 1.0f)));
		float fSlow73 = (5.0f * fSlow71);
		float fSlow74 = (5.0f * (1.0f - (float(fEntry30) + 1.0f)));
		float fSlow75 = (1.0f / ((fConst0 * (fSlow68 * std::exp(((5.75646257f * (float(fEntry31) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow76 = (1.0f - fSlow75);
		float fSlow77 = (fSlow34 * fSlow42);
		float fSlow78 = ((fSlow43 + fSlow50) + fSlow51);
		float fSlow79 = (50.0f * fSlow47);
		float fSlow80 = (1.0f / ((fConst0 * (fSlow48 * std::exp(((4.60517025f * (float(fEntry32) + 1.0f)) + -2.99573231f)))) + 1.0f));
		float fSlow81 = (fSlow80 + -1.0f);
		float fSlow82 = std::exp(((3.45387769f * (float(fEntry33) + 1.0f)) + -2.30258512f));
		float fSlow83 = (fSlow50 + fSlow82);
		float fSlow84 = (1.0f / fSlow82);
		float fSlow85 = (fSlow56 * fSlow34);
		float fSlow86 = (0.5f * (fSlow40 / fSlow85));
		float fSlow87 = (1.0f - fSlow80);
		float fSlow88 = (1.0f / fSlow85);
		float fSlow89 = (fSlow75 + -1.0f);
		float fSlow90 = (1.0f - (0.5f * fSlow39));
		float fSlow91 = AmpMono_faustpower2_f((0.5f * fSlow40));
		float fSlow92 = (0.5f * (fSlow37 / fSlow91));
		float fSlow93 = (fSlow91 / fSlow34);
		float fSlow94 = (fSlow91 / fSlow85);
		float fSlow95 = (5.0f * fSlow63);
		int iSlow96 = (fSlow95 < 9.0f);
		int iSlow97 = (fSlow95 < 8.0f);
		int iSlow98 = (fSlow95 < 6.0f);
		int iSlow99 = (fSlow95 < 5.0f);
		int iSlow100 = (fSlow95 < 4.0f);
		int iSlow101 = (fSlow95 < 3.0f);
		int iSlow102 = (fSlow95 < 2.0f);
		int iSlow103 = (fSlow95 < 1.0f);
		float fSlow104 = std::pow(10.0f, (0.0500000007f * (iSlow96?(iSlow97?((fSlow95 < 7.0f)?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?(iSlow103?((fSlow95 < 0.0f)?-3.1500001f:(iSlow103?(-3.1500001f - (25.7999992f * fSlow63)):-8.31000042f)):(iSlow102?(-8.31000042f - (4.88999987f * (fSlow95 + -1.0f))):-13.1999998f)):(iSlow101?(-13.1999998f - (4.30000019f * (fSlow95 + -2.0f))):-17.5f)):(iSlow100?(-17.5f - (3.5f * (fSlow95 + -3.0f))):-21.0f)):(iSlow99?(-21.0f - (2.4000001f * (fSlow95 + -4.0f))):-23.3999996f)):(iSlow98?((5.0f * (1.0f - fSlow63)) + -23.3999996f):-24.3999996f)):-24.3999996f):(iSlow97?((0.400000006f * (fSlow95 + -7.0f)) + -24.3999996f):-24.0f)):(iSlow96?(-24.0f - (0.600000024f * (fSlow95 + -8.0f))):-24.6000004f)):((fSlow95 < 10.0f)?(-24.6000004f - (1.60000002f * (fSlow95 + -9.0f))):-26.2000008f))));
		float fSlow105 = (1.0f - fSlow28);
		float fSlow106 = (iSlow26?((5.0f * fSlow25) + 13.0f):((18.0f * fSlow25) + 13.0f));
		float fSlow107 = std::pow(10.0f, (0.0500000007f * fSlow106));
		float fSlow108 = ((fSlow25 < -0.800000012f)?(0.0f - (5.0f * (fSlow25 + 0.800000012f))):0.0f);
		float fSlow109 = (1.0f - fSlow108);
		float fSlow110 = float(fEntry34);
		float fSlow111 = ((fSlow110 > 0.0f)?((13.0f * fSlow110) + -3.0f):((5.0f * fSlow110) + -3.0f));
		int iSlow112 = (fSlow111 > 0.0f);
		float fSlow113 = (fConst17 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow111))));
		float fSlow114 = (iSlow112?fConst17:fSlow113);
		float fSlow115 = ((fConst16 * (fConst16 - fSlow114)) + 1.0f);
		float fSlow116 = ((fConst16 * (fConst16 + fSlow114)) + 1.0f);
		float fSlow117 = (iSlow112?fSlow113:fConst17);
		float fSlow118 = ((fConst16 * (fConst16 - fSlow117)) + 1.0f);
		float fSlow119 = ((fConst16 * (fConst16 + fSlow117)) + 1.0f);
		float fSlow120 = ((fSlow110 < -0.800000012f)?(0.0f - (5.0f * (fSlow110 + 0.800000012f))):0.0f);
		float fSlow121 = (1.0f - fSlow120);
		float fSlow122 = float(fEntry35);
		float fSlow123 = ((fSlow122 > 0.0f)?((10.0f * fSlow122) + 13.0f):((18.0f * fSlow122) + 13.0f));
		float fSlow124 = std::pow(10.0f, (0.0500000007f * fSlow123));
		float fSlow125 = ((fSlow122 < -0.800000012f)?(0.0f - (5.0f * (fSlow122 + 0.800000012f))):0.0f);
		float fSlow126 = (1.0f - fSlow125);
		float fSlow127 = std::pow(10.0f, (0.0f - (0.0500000007f * (((0.400000006f * fSlow106) + (0.600000024f * fSlow111)) + (0.200000003f * fSlow123)))));
		float fSlow128 = (250.0f * (float(fEntry36) + 1.0f));
		float fSlow129 = (1.0f / fSlow21);
		float fSlow130 = (1.0f - fSlow20);
		float fSlow131 = std::exp((0.0f - (fConst19 / std::exp(((4.60517025f * (float(fEntry37) + 1.0f)) + -9.2103405f)))));
		float fSlow132 = (1.0f - fSlow131);
		float fSlow133 = (250.0f * (float(fEntry38) + 1.0f));
		float fSlow134 = (float(fEntry39) + 1.0f);
		float fSlow135 = std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -9.2103405f));
		float fSlow136 = (0.0199999996f / (fSlow134 * ((fConst0 * fSlow135) + 1.0f)));
		float fSlow137 = (100.0f * (1.0f - (float(fEntry41) + 1.0f)));
		float fSlow138 = (50.0f * fSlow134);
		float fSlow139 = (1.0f - (1.0f / ((fConst0 * (fSlow135 * std::exp(((4.60517025f * (float(fEntry42) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow140 = (fSlow16 * std::pow(fSlow14, fSlow15));
		float fSlow141 = std::pow((10.0f * (float(fEntry43) + 1.0f)), fSlow16);
		float fSlow142 = (float(fEntry44) + 1.0f);
		float fSlow143 = std::exp(((4.60517025f * (float(fEntry45) + 1.0f)) + -9.2103405f));
		float fSlow144 = (0.0199999996f / (fSlow142 * ((fConst0 * fSlow143) + 1.0f)));
		float fSlow145 = (50.0f * fSlow142);
		float fSlow146 = (50.0f * (float(fEntry46) + 1.0f));
		float fSlow147 = (1.0f / ((fConst0 * (fSlow143 * std::exp(((4.60517025f * (float(fEntry47) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow148 = (fSlow147 + -1.0f);
		float fSlow149 = ((10.0f * fSlow10) + fSlow8);
		float fSlow150 = (float(fEntry48) + 1.0f);
		float fSlow151 = (5.0f * fSlow150);
		float fSlow152 = (0.200000003f / fSlow150);
		float fSlow153 = (1.0f / fSlow6);
		float fSlow154 = (1.0f - fSlow5);
		float fSlow155 = (fSlow133 + fSlow13);
		float fSlow156 = (1.0f - fSlow147);
		float fSlow157 = (5.0f * fSlow23);
		int iSlow158 = (fSlow157 < 9.0f);
		int iSlow159 = (fSlow157 < 8.0f);
		int iSlow160 = (fSlow157 < 7.0f);
		int iSlow161 = (fSlow157 < 6.0f);
		int iSlow162 = (fSlow157 < 5.0f);
		int iSlow163 = (fSlow157 < 4.0f);
		int iSlow164 = (fSlow157 < 3.0f);
		int iSlow165 = (fSlow157 < 2.0f);
		int iSlow166 = (fSlow157 < 1.0f);
		float fSlow167 = std::pow(10.0f, (0.0500000007f * (iSlow158?(iSlow159?(iSlow160?(iSlow161?(iSlow162?(iSlow163?(iSlow164?(iSlow165?(iSlow166?((fSlow157 < 0.0f)?22.7000008f:(iSlow166?(22.7000008f - (30.0f * fSlow23)):16.7000008f)):(iSlow165?(16.7000008f - (6.0f * (fSlow157 + -1.0f))):10.6999998f)):(iSlow164?(10.6999998f - (5.76999998f * (fSlow157 + -2.0f))):4.92999983f)):(iSlow163?(4.92999983f - (5.14300013f * (fSlow157 + -3.0f))):-0.213f)):(iSlow162?(-0.213f - (5.07700014f * (fSlow157 + -4.0f))):-5.28999996f)):(iSlow161?(-5.28999996f - (1.38999999f * (0.0f - (5.0f * (1.0f - fSlow23))))):-6.67999983f)):(iSlow160?(-6.67999983f - (2.49000001f * (fSlow157 + -6.0f))):-9.17000008f)):(iSlow159?(-9.17000008f - (1.63f * (fSlow157 + -7.0f))):-10.8000002f)):(iSlow158?(-10.8000002f - (1.5f * (fSlow157 + -8.0f))):-12.3000002f)):((fSlow157 < 10.0f)?(-12.3000002f - (1.10000002f * (fSlow157 + -9.0f))):-13.3999996f))));
		float fSlow168 = (fConst150 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow64 * fTemp0);
			fRec11[0] = ((fSlow59 * fVec0[1]) - (fSlow65 * ((fSlow66 * fRec11[1]) - (fSlow67 * fTemp0))));
			fRec13[0] = ((fSlow72 * (std::max<float>(0.0f, (fSlow73 - fRec13[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec11[0])) - fRec13[1])))) + (fSlow76 * fRec13[1]));
			fRec12[0] = ((fSlow70 * fRec12[1]) + (fSlow69 * fRec13[0]));
			float fTemp1 = (fSlow55 + (fRec11[0] - fRec12[0]));
			float fTemp2 = ((2.5f * ((fSlow53 * float(tanhf(float((fSlow62 * std::max<float>(0.0f, fTemp1)))))) - fSlow54)) + std::min<float>(0.0f, fTemp1));
			float fTemp3 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow60 * std::fabs(fTemp2)) + -0.0500000007f)));
			float fTemp4 = ((300.0f - ((fTemp3 * (std::pow(std::max<float>(0.0f, (fSlow32 + fTemp2)), fSlow42) - fSlow43)) + (fSlow77 * (fTemp2 * (1.0f - fTemp3))))) - fSlow78);
			float fTemp5 = (std::max<float>(0.0f, fTemp4) + (fSlow51 * (float(tanhf(float((fSlow52 * std::min<float>(0.0f, fTemp4))))) + 1.0f)));
			fRec10[0] = ((fSlow49 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow50 + ((fTemp5 + -250.0f) - fSlow44))) - fRec10[1])) * std::max<float>(0.0f, (fSlow79 - fRec10[1])))) - (fSlow81 * fRec10[1]));
			float fTemp6 = (fSlow46 * fRec10[0]);
			float fTemp7 = (fSlow83 + ((fTemp5 + (-250.0f - fTemp6)) - fSlow44));
			float fTemp8 = (fSlow45 + ((fTemp6 + std::min<float>(0.0f, fTemp7)) + (-50.0f - (fSlow82 * (1.0f - float(tanhf(float((fSlow84 * std::max<float>(0.0f, fTemp7))))))))));
			fVec1[0] = (fSlow61 * fTemp8);
			fRec9[0] = ((fSlow59 * fVec1[1]) + (fSlow65 * ((fSlow86 * fTemp8) - (fSlow66 * fRec9[1]))));
			fRec15[0] = ((fSlow76 * fRec15[1]) + (fSlow72 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec9[0])) - fRec15[1])) * std::max<float>(0.0f, (fSlow73 - fRec15[1])))));
			fRec14[0] = ((fSlow69 * fRec15[0]) + (fSlow70 * fRec14[1]));
			float fTemp9 = (fSlow55 + (fRec9[0] - fRec14[0]));
			float fTemp10 = (std::min<float>(0.0f, fTemp9) - (2.5f * (fSlow54 - (fSlow53 * float(tanhf(float((fSlow62 * std::max<float>(0.0f, fTemp9)))))))));
			float fTemp11 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow60 * std::fabs(fTemp10)) + -0.0500000007f)));
			float fTemp12 = ((300.0f - ((fTemp11 * (std::pow(std::max<float>(0.0f, (fSlow32 + fTemp10)), fSlow42) - fSlow43)) + (fSlow77 * ((1.0f - fTemp11) * fTemp10)))) - fSlow78);
			float fTemp13 = (std::max<float>(0.0f, fTemp12) + (fSlow51 * (float(tanhf(float((fSlow52 * std::min<float>(0.0f, fTemp12))))) + 1.0f)));
			fRec8[0] = ((fSlow49 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow50 + ((fTemp13 + -250.0f) - fSlow44))) - fRec8[1])) * std::max<float>(0.0f, (fSlow79 - fRec8[1])))) + (fSlow87 * fRec8[1]));
			float fTemp14 = (fSlow46 * fRec8[0]);
			float fTemp15 = (fSlow83 + ((fTemp13 + (-250.0f - fTemp14)) - fSlow44));
			float fTemp16 = (fSlow45 + ((fTemp14 + std::min<float>(0.0f, fTemp15)) + (-50.0f - (fSlow82 * (1.0f - float(tanhf(float((fSlow84 * std::max<float>(0.0f, fTemp15))))))))));
			fVec2[0] = (fSlow35 * fTemp16);
			fRec7[0] = ((fSlow59 * fVec2[1]) - (fSlow65 * ((fSlow66 * fRec7[1]) - (fSlow88 * fTemp16))));
			fRec17[0] = ((fSlow72 * (std::max<float>(0.0f, (fSlow73 - fRec17[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec7[0])) - fRec17[1])))) - (fSlow89 * fRec17[1]));
			fRec16[0] = ((fSlow69 * fRec17[0]) + (fSlow70 * fRec16[1]));
			float fTemp17 = (fSlow55 + (fRec7[0] - fRec16[0]));
			float fTemp18 = (std::min<float>(0.0f, fTemp17) - (2.5f * (fSlow54 - (fSlow53 * float(tanhf(float((fSlow62 * std::max<float>(0.0f, fTemp17)))))))));
			float fTemp19 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow60 * std::fabs(fTemp18)) + -0.0500000007f)));
			float fTemp20 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow32 + fTemp18)), fSlow42) - fSlow43) * fTemp19) + (fSlow77 * (fTemp18 * (1.0f - fTemp19))))) - fSlow78);
			float fTemp21 = ((fSlow51 * (float(tanhf(float((fSlow52 * std::min<float>(0.0f, fTemp20))))) + 1.0f)) + std::max<float>(0.0f, fTemp20));
			fRec6[0] = ((fSlow49 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow50 + ((fTemp21 + -250.0f) - fSlow44))) - fRec6[1])) * std::max<float>(0.0f, (fSlow79 - fRec6[1])))) - (fSlow81 * fRec6[1]));
			float fTemp22 = (fSlow46 * fRec6[0]);
			float fTemp23 = (fSlow83 + ((fTemp21 + (-250.0f - fTemp22)) - fSlow44));
			float fTemp24 = ((fSlow41 * (fSlow45 + ((fTemp22 + std::min<float>(0.0f, fTemp23)) + (-50.0f - (fSlow82 * (1.0f - float(tanhf(float((fSlow84 * std::max<float>(0.0f, fTemp23))))))))))) + (fSlow90 * fTemp8));
			fVec3[0] = (fSlow93 * fTemp24);
			fRec20[0] = ((fSlow59 * fVec3[1]) - (fSlow65 * ((fSlow66 * fRec20[1]) - (fSlow94 * fTemp24))));
			fRec22[0] = ((fSlow72 * (std::max<float>(0.0f, (fSlow73 - fRec22[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec20[0])) - fRec22[1])))) - (fSlow89 * fRec22[1]));
			fRec21[0] = ((fSlow70 * fRec21[1]) + (fSlow69 * fRec22[0]));
			float fTemp25 = (fSlow55 + (fRec20[0] - fRec21[0]));
			float fTemp26 = (std::min<float>(0.0f, fTemp25) - (2.5f * (fSlow54 - (fSlow53 * float(tanhf(float((fSlow62 * std::max<float>(0.0f, fTemp25)))))))));
			float fTemp27 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow60 * std::fabs(fTemp26)) + -0.0500000007f)));
			float fTemp28 = ((300.0f - ((fSlow77 * (fTemp26 * (1.0f - fTemp27))) + ((std::pow(std::max<float>(0.0f, (fSlow32 + fTemp26)), fSlow42) - fSlow43) * fTemp27))) - fSlow78);
			float fTemp29 = (std::max<float>(0.0f, fTemp28) + (fSlow51 * (float(tanhf(float((fSlow52 * std::min<float>(0.0f, fTemp28))))) + 1.0f)));
			fRec19[0] = ((fSlow49 * (std::max<float>(0.0f, (fSlow79 - fRec19[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow50 + ((fTemp29 + -250.0f) - fSlow44))) - fRec19[1])))) - (fSlow81 * fRec19[1]));
			float fTemp30 = (fSlow46 * fRec19[0]);
			float fTemp31 = (fSlow83 + ((fTemp29 + (-250.0f - fTemp30)) - fSlow44));
			float fTemp32 = (fSlow45 + ((fTemp30 + std::min<float>(0.0f, fTemp31)) + (-50.0f - (fSlow82 * (1.0f - float(tanhf(float((fSlow84 * std::max<float>(0.0f, fTemp31))))))))));
			fVec4[0] = (fSlow35 * fTemp32);
			fRec18[0] = ((fSlow59 * fVec4[1]) - (fSlow65 * ((fSlow66 * fRec18[1]) - (fSlow88 * fTemp32))));
			fRec24[0] = ((fSlow76 * fRec24[1]) + (fSlow72 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec18[0])) - fRec24[1])) * std::max<float>(0.0f, (fSlow73 - fRec24[1])))));
			fRec23[0] = ((fSlow70 * fRec23[1]) + (fSlow69 * fRec24[0]));
			float fTemp33 = (fSlow55 + (fRec18[0] - fRec23[0]));
			float fTemp34 = (std::min<float>(0.0f, fTemp33) - (2.5f * (fSlow54 - (fSlow53 * float(tanhf(float((fSlow62 * std::max<float>(0.0f, fTemp33)))))))));
			float fTemp35 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow60 * std::fabs(fTemp34)) + -0.0500000007f)));
			float fTemp36 = ((300.0f - ((fSlow77 * (fTemp34 * (1.0f - fTemp35))) + (fTemp35 * (std::pow(std::max<float>(0.0f, (fSlow32 + fTemp34)), fSlow42) - fSlow43)))) - fSlow78);
			float fTemp37 = ((fSlow51 * (float(tanhf(float((fSlow52 * std::min<float>(0.0f, fTemp36))))) + 1.0f)) + std::max<float>(0.0f, fTemp36));
			fRec25[0] = ((fSlow49 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow50 + ((fTemp37 + -250.0f) - fSlow44))) - fRec25[1])) * std::max<float>(0.0f, (fSlow79 - fRec25[1])))) + (fSlow87 * fRec25[1]));
			float fTemp38 = (fSlow46 * fRec25[0]);
			float fTemp39 = (fSlow83 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow44));
			float fTemp40 = (((fSlow38 * fTemp24) + (fSlow92 * (fSlow45 + ((std::min<float>(0.0f, fTemp39) + fTemp38) + (-50.0f - (fSlow82 * (1.0f - float(tanhf(float((fSlow84 * std::max<float>(0.0f, fTemp39)))))))))))) * fSlow104);
			float fTemp41 = (fSlow35 * fTemp40);
			fVec5[0] = fTemp41;
			fRec5[0] = ((fSlow30 * fVec5[1]) - (((fRec5[1] * fSlow105) - (fSlow35 * (fTemp40 / fSlow27))) / fSlow29));
			fRec26[0] = (0.0f - (((fSlow105 * fRec26[1]) - (fTemp41 + fVec5[1])) / fSlow29));
			float fTemp42 = (fRec5[0] + (fRec26[0] * fSlow107));
			fVec6[0] = fTemp42;
			fRec27[0] = ((fConst12 * fVec6[1]) + (fConst13 * ((fConst10 * fTemp42) - (fConst14 * fRec27[1]))));
			float fTemp43 = (fConst18 * fRec4[1]);
			fRec4[0] = (((fTemp42 * fSlow109) + (fRec27[0] * fSlow108)) - (((fRec4[2] * fSlow115) + fTemp43) / fSlow116));
			float fTemp44 = ((fRec4[2] * fSlow118) + (fTemp43 + (fRec4[0] * fSlow119)));
			float fTemp45 = (fConst28 * fRec28[1]);
			fRec28[0] = ((fTemp44 / fSlow116) - (fConst25 * ((fConst27 * fRec28[2]) + fTemp45)));
			float fTemp46 = (((fTemp44 * fSlow121) / fSlow116) + (fConst25 * (fSlow120 * ((fConst26 * fRec28[2]) + ((fConst26 * fRec28[0]) + fTemp45)))));
			fVec7[0] = fTemp46;
			fRec3[0] = (0.0f - (fConst7 * ((fConst8 * fRec3[1]) - (fVec7[1] + fTemp46))));
			fRec29[0] = ((fConst29 * fVec7[1]) - (fConst7 * ((fConst8 * fRec29[1]) - (fConst5 * fTemp46))));
			float fTemp47 = (fRec3[0] + (fRec29[0] * fSlow124));
			fVec8[0] = fTemp47;
			fRec2[0] = (fConst3 * ((fTemp47 + fVec8[1]) - (fConst30 * fRec2[1])));
			float fTemp48 = ((fSlow24 * (((fRec2[0] * fSlow125) + (fTemp47 * fSlow126)) * fSlow127)) - fSlow128);
			fVec9[0] = fTemp48;
			fRec1[0] = ((fSlow22 * fVec9[1]) - (fSlow129 * ((fSlow130 * fRec1[1]) - (fSlow20 * fTemp48))));
			fRec30[0] = ((fSlow131 * fRec30[1]) + (fSlow132 * (fRec1[0] - fSlow133)));
			fRec32[0] = ((fSlow136 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow137 + ((fRec1[0] - fRec30[0]) - fSlow133))) - fRec32[1])) * std::max<float>(0.0f, (fSlow138 - fRec32[1])))) + (fSlow139 * fRec32[1]));
			float fRec31 = fRec32[0];
			float fTemp49 = (fRec30[0] + fRec31);
			float fTemp50 = (0.0f - ((fRec1[0] - fTemp49) - fSlow133));
			float fTemp51 = (0.0f - fTemp50);
			float fTemp52 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow18 * std::fabs(fTemp51)) + -0.0500000007f)));
			float fTemp53 = (fSlow12 * (fSlow17 + (((fTemp52 * (std::pow(std::max<float>(0.0f, (fSlow13 + ((fRec1[0] + (30.0f - fTemp49)) - fSlow133))), fSlow16) - fSlow17)) + (fSlow140 * ((1.0f - fTemp52) * fTemp51))) - fSlow141)));
			fRec34[0] = ((fSlow144 * (std::max<float>(0.0f, (fSlow145 - fRec34[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp53 - fSlow146)) - fRec34[1])))) - (fSlow148 * fRec34[1]));
			float fRec33 = fRec34[0];
			float fTemp54 = ((fTemp53 - fRec33) - fSlow149);
			float fTemp55 = (std::max<float>(0.0f, (fSlow8 + ((10.0f * (fSlow10 + (fSlow9 * float(tanhf(float((fSlow11 * std::max<float>(0.0f, fTemp54)))))))) + std::min<float>(0.0f, fTemp54)))) - fSlow151);
			float fTemp56 = (std::max<float>(0.0f, fTemp55) + (fSlow151 * (float(tanhf(float((fSlow152 * std::min<float>(0.0f, fTemp55))))) + 1.0f)));
			fVec10[0] = fTemp56;
			fRec0[0] = ((fSlow7 * fVec10[1]) - (fSlow153 * ((fSlow154 * fRec0[1]) - (fSlow5 * fTemp56))));
			float fTemp57 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow18 * std::fabs(fTemp50)) + -0.0500000007f)));
			float fTemp58 = (fSlow12 * (fSlow17 + (((fTemp57 * (std::pow(std::max<float>(0.0f, (fSlow155 + (fTemp49 + (30.0f - fRec1[0])))), fSlow16) - fSlow17)) + (fSlow140 * (fTemp50 * (1.0f - fTemp57)))) - fSlow141)));
			fRec37[0] = ((fSlow156 * fRec37[1]) + (fSlow144 * (std::max<float>(0.0f, (fSlow145 - fRec37[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp58 - fSlow146)) - fRec37[1])))));
			float fRec36 = fRec37[0];
			float fTemp59 = ((fTemp58 - fRec36) - fSlow149);
			float fTemp60 = (std::max<float>(0.0f, (fSlow8 + (std::min<float>(0.0f, fTemp59) + (10.0f * (fSlow10 + (fSlow9 * float(tanhf(float((fSlow11 * std::max<float>(0.0f, fTemp59))))))))))) - fSlow151);
			float fTemp61 = ((fSlow151 * (float(tanhf(float((fSlow152 * std::min<float>(0.0f, fTemp60))))) + 1.0f)) + std::max<float>(0.0f, fTemp60));
			fVec11[0] = fTemp61;
			fRec35[0] = ((fSlow7 * fVec11[1]) - (fSlow153 * ((fSlow154 * fRec35[1]) - (fSlow5 * fTemp61))));
			float fTemp62 = ((fRec0[0] - fRec35[0]) * fSlow167);
			float fTemp63 = (fSlow3 * fTemp62);
			fVec12[0] = fTemp63;
			fRec60[0] = ((fConst149 * ((fSlow168 * fTemp62) - (fConst151 * fRec60[1]))) + (fConst152 * fVec12[1]));
			fRec59[0] = (0.0f - (fConst144 * ((fConst145 * fRec59[1]) - (fRec60[0] + fRec60[1]))));
			fRec58[0] = ((fConst142 * fRec59[1]) - (fConst153 * ((fConst154 * fRec58[1]) - (fConst133 * fRec59[0]))));
			fRec57[0] = (fRec58[0] - (fConst140 * ((fConst155 * fRec57[2]) + (fConst156 * fRec57[1]))));
			fRec56[0] = ((fConst140 * ((fConst136 * fRec57[2]) + ((fConst136 * fRec57[0]) + (fConst157 * fRec57[1])))) - (fConst139 * ((fConst158 * fRec56[2]) + (fConst156 * fRec56[1]))));
			fRec55[0] = ((fConst139 * ((fConst136 * fRec56[2]) + ((fConst157 * fRec56[1]) + (fConst136 * fRec56[0])))) - (fConst138 * ((fConst159 * fRec55[2]) + (fConst156 * fRec55[1]))));
			fRec54[0] = ((fConst138 * ((fConst136 * fRec55[2]) + ((fConst136 * fRec55[0]) + (fConst157 * fRec55[1])))) - (fConst137 * ((fConst160 * fRec54[2]) + (fConst156 * fRec54[1]))));
			fRec53[0] = ((fConst137 * ((fConst136 * fRec54[2]) + ((fConst157 * fRec54[1]) + (fConst136 * fRec54[0])))) - (fConst134 * ((fConst156 * fRec53[1]) + (fConst161 * fRec53[2]))));
			fRec66[0] = (0.0f - (fConst153 * ((fConst154 * fRec66[1]) - (fRec59[0] + fRec59[1]))));
			fRec65[0] = (fRec66[0] - (fConst140 * ((fConst155 * fRec65[2]) + (fConst156 * fRec65[1]))));
			fRec64[0] = ((fConst140 * ((fRec65[0] + (2.0f * fRec65[1])) + fRec65[2])) - (fConst139 * ((fConst156 * fRec64[1]) + (fConst158 * fRec64[2]))));
			fRec63[0] = ((fConst139 * ((fRec64[0] + (2.0f * fRec64[1])) + fRec64[2])) - (fConst138 * ((fConst156 * fRec63[1]) + (fConst159 * fRec63[2]))));
			fRec62[0] = ((fConst138 * ((fRec63[0] + (2.0f * fRec63[1])) + fRec63[2])) - (fConst137 * ((fConst160 * fRec62[2]) + (fConst156 * fRec62[1]))));
			fRec61[0] = ((fConst137 * (fRec62[2] + (fRec62[0] + (2.0f * fRec62[1])))) - (fConst134 * ((fConst156 * fRec61[1]) + (fConst161 * fRec61[2]))));
			float fTemp64 = (fConst163 * fRec52[1]);
			fRec52[0] = ((fConst134 * ((0.13673377f * ((fConst136 * fRec53[2]) + ((fConst136 * fRec53[0]) + (fConst157 * fRec53[1])))) + ((fRec61[0] + (2.0f * fRec61[1])) + fRec61[2]))) - (fConst129 * ((fConst162 * fRec52[2]) + fTemp64)));
			float fTemp65 = (fConst166 * fRec51[1]);
			fRec51[0] = ((fConst129 * (((fConst131 * fRec52[0]) + fTemp64) + (fConst164 * fRec52[2]))) - (fConst122 * ((fConst165 * fRec51[2]) + fTemp65)));
			float fTemp66 = (fConst169 * fRec50[1]);
			fRec50[0] = ((fConst122 * (((fConst124 * fRec51[0]) + fTemp65) + (fConst167 * fRec51[2]))) - (fConst115 * ((fConst168 * fRec50[2]) + fTemp66)));
			float fTemp67 = (fConst110 * fRec49[1]);
			fRec49[0] = ((fConst115 * ((fConst117 * fRec50[2]) + (fTemp66 + (fConst170 * fRec50[0])))) - (fConst109 * ((fConst171 * fRec49[2]) + fTemp67)));
			float fTemp68 = (fConst104 * fRec48[1]);
			fRec48[0] = ((fConst109 * ((fTemp67 + (fConst173 * fRec49[0])) + (fConst174 * fRec49[2]))) - (fConst103 * (fTemp68 + (fConst175 * fRec48[2]))));
			float fTemp69 = (fConst179 * fRec47[1]);
			fRec47[0] = ((fConst103 * ((fTemp68 + (fConst177 * fRec48[0])) + (fConst178 * fRec48[2]))) - (fConst96 * (fTemp69 + (fConst180 * fRec47[2]))));
			float fTemp70 = (fConst91 * fRec46[1]);
			fRec46[0] = ((fConst96 * ((fConst98 * fRec47[2]) + (fTemp69 + (fConst181 * fRec47[0])))) - (fConst90 * (fTemp70 + (fConst182 * fRec46[2]))));
			float fTemp71 = (fConst85 * fRec45[1]);
			fRec45[0] = ((fConst90 * ((fTemp70 + (fConst184 * fRec46[0])) + (fConst185 * fRec46[2]))) - (fConst84 * (fTemp71 + (fConst186 * fRec45[2]))));
			float fTemp72 = (fConst190 * fRec44[1]);
			fRec44[0] = ((fConst84 * ((fTemp71 + (fConst188 * fRec45[0])) + (fConst189 * fRec45[2]))) - (fConst77 * (fTemp72 + (fConst191 * fRec44[2]))));
			float fTemp73 = (fConst194 * fRec43[1]);
			fRec43[0] = ((fConst77 * (((fConst79 * fRec44[0]) + fTemp72) + (fConst192 * fRec44[2]))) - (fConst70 * ((fConst193 * fRec43[2]) + fTemp73)));
			float fTemp74 = (fConst197 * fRec42[1]);
			fRec42[0] = ((fConst70 * ((fConst72 * fRec43[2]) + ((fConst195 * fRec43[0]) + fTemp73))) - (fConst63 * ((fConst196 * fRec42[2]) + fTemp74)));
			float fTemp75 = (fConst200 * fRec41[1]);
			fRec41[0] = ((fConst63 * (((fConst65 * fRec42[0]) + fTemp74) + (fConst198 * fRec42[2]))) - (fConst56 * ((fConst199 * fRec41[2]) + fTemp75)));
			float fTemp76 = (fConst51 * fRec40[1]);
			fRec40[0] = ((fConst56 * ((fConst58 * fRec41[2]) + (fTemp75 + (fConst201 * fRec41[0])))) - (fConst50 * (fTemp76 + (fConst202 * fRec40[2]))));
			float fTemp77 = (fConst206 * fRec39[1]);
			fRec39[0] = ((fConst50 * ((fTemp76 + (fConst204 * fRec40[0])) + (fConst205 * fRec40[2]))) - (fConst43 * (fTemp77 + (fConst207 * fRec39[2]))));
			float fTemp78 = (fConst210 * fRec38[1]);
			fRec38[0] = ((fConst43 * (((fConst45 * fRec39[0]) + fTemp77) + (fConst208 * fRec39[2]))) - (fConst209 * (fTemp78 + (fConst211 * fRec38[2]))));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst36 * ((fConst38 * fRec38[2]) + (fTemp78 + (fConst212 * fRec38[0])))):fTemp63)));
			fVec0[1] = fVec0[0];
			fRec11[1] = fRec11[0];
			fRec13[1] = fRec13[0];
			fRec12[1] = fRec12[0];
			fRec10[1] = fRec10[0];
			fVec1[1] = fVec1[0];
			fRec9[1] = fRec9[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fRec8[1] = fRec8[0];
			fVec2[1] = fVec2[0];
			fRec7[1] = fRec7[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec6[1] = fRec6[0];
			fVec3[1] = fVec3[0];
			fRec20[1] = fRec20[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec19[1] = fRec19[0];
			fVec4[1] = fVec4[0];
			fRec18[1] = fRec18[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec25[1] = fRec25[0];
			fVec5[1] = fVec5[0];
			fRec5[1] = fRec5[0];
			fRec26[1] = fRec26[0];
			fVec6[1] = fVec6[0];
			fRec27[1] = fRec27[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec28[2] = fRec28[1];
			fRec28[1] = fRec28[0];
			fVec7[1] = fVec7[0];
			fRec3[1] = fRec3[0];
			fRec29[1] = fRec29[0];
			fVec8[1] = fVec8[0];
			fRec2[1] = fRec2[0];
			fVec9[1] = fVec9[0];
			fRec1[1] = fRec1[0];
			fRec30[1] = fRec30[0];
			fRec32[1] = fRec32[0];
			fRec34[1] = fRec34[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
			fRec37[1] = fRec37[0];
			fVec11[1] = fVec11[0];
			fRec35[1] = fRec35[0];
			fVec12[1] = fVec12[0];
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
