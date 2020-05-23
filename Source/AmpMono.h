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
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
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
	float fVec0[2];
	float fRec10[2];
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	float fRec12[2];
	float fRec11[2];
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec9[2];
	float fVec1[2];
	float fRec8[2];
	float fRec14[2];
	float fRec13[2];
	float fRec15[2];
	float fVec2[2];
	float fRec7[2];
	float fRec17[2];
	float fRec16[2];
	float fRec18[2];
	float fVec3[2];
	float fRec22[2];
	float fRec24[2];
	float fRec23[2];
	float fRec21[2];
	float fVec4[2];
	float fRec20[2];
	float fRec26[2];
	float fRec25[2];
	float fRec19[2];
	float fVec5[2];
	float fRec6[2];
	float fRec27[2];
	float fVec6[2];
	float fConst16;
	float fConst17;
	float fRec5[2];
	float fConst18;
	float fConst19;
	float fRec4[3];
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
	float fConst29;
	float fVec7[2];
	float fRec3[2];
	float fConst30;
	float fRec29[2];
	float fVec8[2];
	float fRec2[2];
	FAUSTFLOAT fEntry37;
	float fVec9[2];
	float fRec1[2];
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	float fRec30[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	float fRec32[2];
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fRec33[2];
	float fVec10[2];
	float fRec0[2];
	float fRec35[2];
	float fVec11[2];
	float fRec34[2];
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
	float fConst153;
	float fRec58[2];
	float fRec57[2];
	float fConst154;
	float fConst155;
	float fRec56[2];
	float fConst156;
	float fConst157;
	float fRec55[3];
	float fConst158;
	float fRec54[3];
	float fConst159;
	float fRec53[3];
	float fConst160;
	float fRec52[3];
	float fConst161;
	float fRec51[3];
	float fRec64[2];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fRec60[3];
	float fRec59[3];
	float fConst162;
	float fConst163;
	float fRec50[3];
	float fConst164;
	float fConst165;
	float fRec49[3];
	float fConst166;
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec48[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec47[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec46[3];
	float fConst178;
	float fConst179;
	float fRec45[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec44[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec43[3];
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec42[3];
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec41[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec40[3];
	float fConst198;
	float fConst199;
	float fConst200;
	float fRec39[3];
	float fConst201;
	float fConst202;
	float fConst203;
	float fRec38[3];
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec37[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec36[3];
	float fConst210;
	float fConst211;
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
		fConst4 = (1.0f - fConst2);
		fConst5 = std::tan((6283.18555f / fConst0));
		fConst6 = (1.0f / fConst5);
		fConst7 = (fConst6 + 1.0f);
		fConst8 = (1.0f / fConst7);
		fConst9 = (1.0f - fConst6);
		fConst10 = std::tan((1382.30078f / fConst0));
		fConst11 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst10))));
		fConst12 = std::tan((78.5398178f / fConst0));
		fConst13 = (1.0f / fConst12);
		fConst14 = (fConst13 + 1.0f);
		fConst15 = (0.0f - (1.0f / (fConst12 * fConst14)));
		fConst16 = (1.0f / fConst14);
		fConst17 = (1.0f - fConst13);
		fConst18 = (1.0f / fConst10);
		fConst19 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst20 = (1.0f / fConst0);
		fConst21 = std::tan((1696.46008f / fConst0));
		fConst22 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * fConst21) * std::tan((1068.14148f / fConst0))))));
		fConst23 = (AmpMono_faustpower2_f(fConst20) * fConst22);
		fConst24 = (fConst0 * fConst21);
		fConst25 = (2.0f * (((2.0f * fConst24) - (0.5f * (fConst22 / fConst24))) / fConst0));
		fConst26 = (1.0f / ((fConst23 + fConst25) + 4.0f));
		fConst27 = ((2.0f * fConst23) + -8.0f);
		fConst28 = (fConst23 + (4.0f - fConst25));
		fConst29 = (fConst23 + 4.0f);
		fConst30 = (0.0f - (1.0f / (fConst5 * fConst7)));
		fConst31 = std::tan((5574.98535f / fConst0));
		fConst32 = (1.0f / fConst31);
		fConst33 = (fConst0 * std::sin((11149.9707f / fConst0)));
		fConst34 = (4376.67188f / fConst33);
		fConst35 = (((fConst32 + fConst34) / fConst31) + 1.0f);
		fConst36 = (0.144011721f / fConst35);
		fConst37 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst31))));
		fConst38 = std::tan((4288.271f / fConst0));
		fConst39 = (1.0f / fConst38);
		fConst40 = (fConst0 * std::sin((8576.54199f / fConst0)));
		fConst41 = (326.939972f / fConst40);
		fConst42 = (1.0f / (((fConst39 + fConst41) / fConst38) + 1.0f));
		fConst43 = (190.645706f / fConst40);
		fConst44 = (((fConst39 - fConst43) / fConst38) + 1.0f);
		fConst45 = std::tan((3537.37793f / fConst0));
		fConst46 = (1.0f / fConst45);
		fConst47 = (fConst0 * std::sin((7074.75586f / fConst0)));
		fConst48 = (642.945251f / fConst47);
		fConst49 = (1.0f / (((fConst46 + fConst48) / fConst45) + 1.0f));
		fConst50 = (270.569763f / fConst47);
		fConst51 = (((fConst46 - fConst50) / fConst45) + 1.0f);
		fConst52 = std::tan((3081.90234f / fConst0));
		fConst53 = (1.0f / fConst52);
		fConst54 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst55 = (486.410919f / fConst54);
		fConst56 = (1.0f / (((fConst53 + fConst55) / fConst52) + 1.0f));
		fConst57 = (183.178085f / fConst54);
		fConst58 = (((fConst53 + fConst57) / fConst52) + 1.0f);
		fConst59 = std::tan((2592.47217f / fConst0));
		fConst60 = (1.0f / fConst59);
		fConst61 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst62 = (317.628265f / fConst61);
		fConst63 = (1.0f / (((fConst60 + fConst62) / fConst59) + 1.0f));
		fConst64 = (148.323349f / fConst61);
		fConst65 = (((fConst60 - fConst64) / fConst59) + 1.0f);
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
		fConst79 = (((fConst74 - fConst78) / fConst73) + 1.0f);
		fConst80 = std::tan((15066.6357f / fConst0));
		fConst81 = (1.0f / fConst80);
		fConst82 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst83 = (11187.3662f / fConst82);
		fConst84 = (1.0f / (((fConst81 + fConst83) / fConst80) + 1.0f));
		fConst85 = (36783.4805f / fConst82);
		fConst86 = (((fConst81 - fConst85) / fConst80) + 1.0f);
		fConst87 = std::tan((13437.668f / fConst0));
		fConst88 = (1.0f / fConst87);
		fConst89 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst90 = (13245.1885f / fConst89);
		fConst91 = (1.0f / (((fConst88 + fConst90) / fConst87) + 1.0f));
		fConst92 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst87))));
		fConst93 = std::tan((10058.502f / fConst0));
		fConst94 = (1.0f / fConst93);
		fConst95 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst96 = (4926.20459f / fConst95);
		fConst97 = (1.0f / (((fConst94 + fConst96) / fConst93) + 1.0f));
		fConst98 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst93))));
		fConst99 = std::tan((8136.54736f / fConst0));
		fConst100 = (1.0f / fConst99);
		fConst101 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst102 = (966.024841f / fConst101);
		fConst103 = (1.0f / (((fConst100 + fConst102) / fConst99) + 1.0f));
		fConst104 = (518.801147f / fConst101);
		fConst105 = (((fConst100 + fConst104) / fConst99) + 1.0f);
		fConst106 = std::tan((8011.02734f / fConst0));
		fConst107 = (1.0f / fConst106);
		fConst108 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst109 = (1613.9762f / fConst108);
		fConst110 = (1.0f / (((fConst107 + fConst109) / fConst106) + 1.0f));
		fConst111 = (3097.15845f / fConst108);
		fConst112 = (((fConst107 - fConst111) / fConst106) + 1.0f);
		fConst113 = std::tan((9456.15234f / fConst0));
		fConst114 = (1.0f / fConst113);
		fConst115 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst116 = (2492.29883f / fConst115);
		fConst117 = (1.0f / (((fConst114 + fConst116) / fConst113) + 1.0f));
		fConst118 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst113))));
		fConst119 = std::tan((2827.43262f / fConst0));
		fConst120 = (1.0f / fConst119);
		fConst121 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst122 = (19634.3262f / fConst121);
		fConst123 = (1.0f / (((fConst120 + fConst122) / fConst119) + 1.0f));
		fConst124 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst119))));
		fConst125 = std::tan((375.293884f / fConst0));
		fConst126 = (1.0f / fConst125);
		fConst127 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst128 = (463.734222f / fConst127);
		fConst129 = (1.0f / (((fConst126 + fConst128) / fConst125) + 1.0f));
		fConst130 = (3220.11475f / fConst127);
		fConst131 = (((fConst126 - fConst130) / fConst125) + 1.0f);
		fConst132 = std::tan((18369.8027f / fConst0));
		fConst133 = (1.0f / fConst132);
		fConst134 = (1.0f / (((fConst133 + 0.284629673f) / fConst132) + 1.0f));
		fConst135 = AmpMono_faustpower2_f(fConst132);
		fConst136 = (1.0f / fConst135);
		fConst137 = (1.0f / (((fConst133 + 0.830830038f) / fConst132) + 1.0f));
		fConst138 = (0.0f - (2.0f / fConst135));
		fConst139 = (1.0f / (((fConst133 + 1.30972147f) / fConst132) + 1.0f));
		fConst140 = (1.0f / (((fConst133 + 1.68250704f) / fConst132) + 1.0f));
		fConst141 = (1.0f / (((fConst133 + 1.91898596f) / fConst132) + 1.0f));
		fConst142 = (fConst133 + 1.0f);
		fConst143 = (0.0f - (1.0f / (fConst132 * fConst142)));
		fConst144 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst145 = (1.0f / (fConst144 + 1.0f));
		fConst146 = (1.0f - fConst144);
		fConst147 = std::tan((452.102844f / fConst0));
		fConst148 = (1.0f / fConst147);
		fConst149 = (fConst148 + 1.0f);
		fConst150 = (0.0f - (1.0f / (fConst147 * fConst149)));
		fConst151 = (1.0f / fConst149);
		fConst152 = (0.0199999996f / fConst147);
		fConst153 = (1.0f - fConst148);
		fConst154 = (1.0f / fConst142);
		fConst155 = (1.0f - fConst133);
		fConst156 = (((fConst133 + -1.91898596f) / fConst132) + 1.0f);
		fConst157 = (2.0f * (1.0f - fConst136));
		fConst158 = (((fConst133 + -1.68250704f) / fConst132) + 1.0f);
		fConst159 = (((fConst133 + -1.30972147f) / fConst132) + 1.0f);
		fConst160 = (((fConst133 + -0.830830038f) / fConst132) + 1.0f);
		fConst161 = (((fConst133 + -0.284629673f) / fConst132) + 1.0f);
		fConst162 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst125))));
		fConst163 = (((fConst126 - fConst128) / fConst125) + 1.0f);
		fConst164 = (((fConst126 + fConst130) / fConst125) + 1.0f);
		fConst165 = (((fConst120 - fConst122) / fConst119) + 1.0f);
		fConst166 = (106249.391f / fConst121);
		fConst167 = (((fConst120 + fConst166) / fConst119) + 1.0f);
		fConst168 = (((fConst120 - fConst166) / fConst119) + 1.0f);
		fConst169 = (((fConst114 - fConst116) / fConst113) + 1.0f);
		fConst170 = (974.257141f / fConst115);
		fConst171 = (((fConst114 + fConst170) / fConst113) + 1.0f);
		fConst172 = (((fConst114 - fConst170) / fConst113) + 1.0f);
		fConst173 = (((fConst107 - fConst109) / fConst106) + 1.0f);
		fConst174 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst106))));
		fConst175 = (((fConst107 + fConst111) / fConst106) + 1.0f);
		fConst176 = (((fConst100 - fConst102) / fConst99) + 1.0f);
		fConst177 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst99))));
		fConst178 = (((fConst100 - fConst104) / fConst99) + 1.0f);
		fConst179 = (((fConst94 - fConst96) / fConst93) + 1.0f);
		fConst180 = (9024.73242f / fConst95);
		fConst181 = (((fConst94 + fConst180) / fConst93) + 1.0f);
		fConst182 = (((fConst94 - fConst180) / fConst93) + 1.0f);
		fConst183 = (((fConst88 - fConst90) / fConst87) + 1.0f);
		fConst184 = (4583.19189f / fConst89);
		fConst185 = (((fConst88 + fConst184) / fConst87) + 1.0f);
		fConst186 = (((fConst88 - fConst184) / fConst87) + 1.0f);
		fConst187 = (((fConst81 - fConst83) / fConst80) + 1.0f);
		fConst188 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst80))));
		fConst189 = (((fConst81 + fConst85) / fConst80) + 1.0f);
		fConst190 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst191 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst192 = (((fConst74 + fConst78) / fConst73) + 1.0f);
		fConst193 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst194 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst195 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst196 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst59))));
		fConst197 = (((fConst60 - fConst62) / fConst59) + 1.0f);
		fConst198 = (((fConst60 + fConst64) / fConst59) + 1.0f);
		fConst199 = (((fConst53 - fConst55) / fConst52) + 1.0f);
		fConst200 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst52))));
		fConst201 = (((fConst53 - fConst57) / fConst52) + 1.0f);
		fConst202 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst45))));
		fConst203 = (((fConst46 - fConst48) / fConst45) + 1.0f);
		fConst204 = (((fConst46 + fConst50) / fConst45) + 1.0f);
		fConst205 = (((fConst39 - fConst41) / fConst38) + 1.0f);
		fConst206 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst38))));
		fConst207 = (((fConst39 + fConst43) / fConst38) + 1.0f);
		fConst208 = (1.0f / fConst35);
		fConst209 = (((fConst32 - fConst34) / fConst31) + 1.0f);
		fConst210 = (2760.92456f / fConst33);
		fConst211 = (((fConst32 + fConst210) / fConst31) + 1.0f);
		fConst212 = (((fConst32 - fConst210) / fConst31) + 1.0f);

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
			fRec10[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec12[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec11[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec9[l4] = 0.0f;

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
			fRec15[l9] = 0.0f;

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
			fRec18[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fVec3[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec22[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec24[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec23[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec21[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fVec4[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec20[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec26[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec25[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fRec19[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fVec5[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec6[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec27[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fVec6[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec5[l29] = 0.0f;

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
			fRec33[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fVec10[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec0[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec35[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fVec11[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec34[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec12[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec58[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec57[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fRec56[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec55[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec54[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec53[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec52[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec51[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec64[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec63[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec62[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec61[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec60[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec59[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec50[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec49[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec48[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec47[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec46[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec45[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec44[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec43[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec42[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec41[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec40[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec39[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec38[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec37[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec36[l76] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry18 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry17 = value + 0.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry27 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry28 = value + 0.000000e+00; }
	void set_tetrode_grid_cap(FAUSTFLOAT value) { fEntry42 = value + 4.705513e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry43 = value + 4.248187e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry37 = value + 4.772657e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry39 = value + -2.047729e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry40 = value + 6.319992e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry41 = value + -6.194208e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry38 = value + -1.524618e-05; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry10 = value + -8.210805e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry8 = value + -2.549861e+00; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry5 = value + -2.575947e-01; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry6 = value + 1.308648e-01; }
	void set_tetrode_plate_corner_b(FAUSTFLOAT value) { fEntry4 = value + -1.507608e+00; }
	void set_tetrode_plate_hp(FAUSTFLOAT value) { fEntry3 = value + -4.969384e+00; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry44 = value + 9.329082e-01; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry7 = value + -5.029362e-01; }
	void set_tetrode_plate_taus(FAUSTFLOAT value) { fEntry45 = value + 1.474470e-01; }
	void set_triode_grid_cap(FAUSTFLOAT value) { fEntry31 = value + 9.940021e+00; }
	void set_triode_grid_clip(FAUSTFLOAT value) { fEntry34 = value + 3.719299e-01; }
	void set_triode_grid_corner(FAUSTFLOAT value) { fEntry35 = value + -2.609667e-02; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry32 = value + 3.359419e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry33 = value + 1.242548e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry29 = value + 1.562984e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry30 = value + -1.413848e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry23 = value + 4.522095e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry15 = value + -6.074699e-02; }
	void set_triode_plate_cap_b(FAUSTFLOAT value) { fEntry25 = value + -7.208259e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry20 = value + 7.069492e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry22 = value + -2.074368e-01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry19 = value + -2.001175e-01; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry16 = value + 0.000000e+00; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry36 = value + 5.666555e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.537254e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry24 = value + -2.343605e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry21 = value + -1.274735e-01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry26 = value + -4.353973e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00; }
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
		float fSlow0 = (0.501187205f * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f)))))));
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = (float(fEntry2) + 1.0f);
		float fSlow3 = (0.0199999996f / fSlow2);
		float fSlow4 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry3) + 1.0f)) + -2.30258512f))));
		float fSlow5 = (1.0f / fSlow4);
		float fSlow6 = (fSlow5 + 1.0f);
		float fSlow7 = (0.0f - (1.0f / (fSlow6 * fSlow4)));
		float fSlow8 = (float(fEntry4) + 1.0f);
		float fSlow9 = (5.0f * fSlow8);
		float fSlow10 = (0.0588235296f / fSlow8);
		float fSlow11 = (20.0f * (float(fEntry5) + 1.0f));
		float fSlow12 = (float(fEntry6) + 1.0f);
		float fSlow13 = (1.0f - fSlow12);
		float fSlow14 = (0.0294117648f / fSlow12);
		float fSlow15 = std::exp(((4.60517025f * (float(fEntry7) + 1.0f)) + -4.60517025f));
		float fSlow16 = (10.0f * (float(fEntry8) + 1.0f));
		float fSlow17 = (fSlow16 + 30.0f);
		float fSlow18 = (0.5f * (float(fEntry9) + 1.0f));
		float fSlow19 = (fSlow18 + 1.0f);
		float fSlow20 = std::pow(fSlow17, fSlow19);
		float fSlow21 = (10.0f / fSlow17);
		float fSlow22 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry10) + 1.0f)) + -2.30258512f))));
		float fSlow23 = (1.0f / fSlow22);
		float fSlow24 = (fSlow23 + 1.0f);
		float fSlow25 = (0.0f - (1.0f / (fSlow22 * fSlow24)));
		float fSlow26 = (float(fEntry11) + 1.0f);
		float fSlow27 = (50.0f * (fSlow2 * std::exp(((3.45387769f * fSlow26) + -2.30258512f))));
		float fSlow28 = float(fEntry12);
		int iSlow29 = (fSlow28 > 0.0f);
		float fSlow30 = (iSlow29?((5.0f * fSlow28) + 13.0f):((18.0f * fSlow28) + 13.0f));
		float fSlow31 = float(fEntry13);
		float fSlow32 = ((fSlow31 > 0.0f)?((13.0f * fSlow31) + -3.0f):((5.0f * fSlow31) + -3.0f));
		float fSlow33 = float(fEntry14);
		float fSlow34 = ((fSlow33 > 0.0f)?((10.0f * fSlow33) + 13.0f):((18.0f * fSlow33) + 13.0f));
		float fSlow35 = std::pow(10.0f, (0.0f - (0.0500000007f * (((0.400000006f * fSlow30) + (0.600000024f * fSlow32)) + (0.200000003f * fSlow34)))));
		float fSlow36 = std::tan((fConst1 * float((iSlow29?100:50))));
		float fSlow37 = (1.0f / fSlow36);
		float fSlow38 = (fSlow37 + 1.0f);
		float fSlow39 = (0.0f - (1.0f / (fSlow36 * fSlow38)));
		float fSlow40 = (float(fEntry15) + 1.0f);
		float fSlow41 = (10.0f * fSlow40);
		float fSlow42 = (0.5f * (float(fEntry16) + 1.0f));
		float fSlow43 = std::pow(fSlow41, fSlow42);
		float fSlow44 = (1.0f / fSlow43);
		float fSlow45 = float(fEntry17);
		float fSlow46 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow45) + -3.0f));
		float fSlow47 = (1.0f - (0.5f * fSlow46));
		float fSlow48 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow45) + -1.0f));
		float fSlow49 = ((float(fEntry18) + 1.0f) + 1.0f);
		float fSlow50 = (fSlow48 / fSlow49);
		float fSlow51 = (fSlow42 + 1.0f);
		float fSlow52 = std::pow(fSlow41, fSlow51);
		float fSlow53 = (37.5f * (float(fEntry19) + 1.0f));
		float fSlow54 = (fSlow52 + fSlow53);
		float fSlow55 = (150.0f * (float(fEntry20) + 1.0f));
		float fSlow56 = std::exp(((3.45387769f * (float(fEntry21) + 1.0f)) + -2.30258512f));
		float fSlow57 = (fSlow55 + fSlow56);
		float fSlow58 = std::exp(((4.60517025f * (float(fEntry22) + 1.0f)) + -2.30258512f));
		float fSlow59 = (0.294117659f / fSlow58);
		float fSlow60 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry23) + 1.0f)) + -2.30258512f))));
		float fSlow61 = (1.0f / fSlow60);
		float fSlow62 = (fSlow61 + 1.0f);
		float fSlow63 = (0.0f - (1.0f / (fSlow60 * fSlow62)));
		float fSlow64 = (1.0f / fSlow40);
		float fSlow65 = (0.5f * (fSlow49 / fSlow43));
		float fSlow66 = std::exp(((3.45387769f * (float(fEntry24) + 1.0f)) + -2.30258512f));
		float fSlow67 = (float(fEntry25) + 1.0f);
		float fSlow68 = std::exp(((4.60517025f * (float(fEntry26) + 1.0f)) + -9.2103405f));
		float fSlow69 = (0.0199999996f / (fSlow67 * ((fConst0 * fSlow68) + 1.0f)));
		float fSlow70 = (float(fEntry28) + 1.0f);
		float fSlow71 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry27) + 1.0f)))))) * std::exp(((2.99573231f * fSlow70) + -0.693147182f)));
		float fSlow72 = (1.0f / fSlow62);
		float fSlow73 = (1.0f - fSlow61);
		float fSlow74 = (fSlow71 / fSlow60);
		float fSlow75 = std::exp(((3.45387769f * (float(fEntry30) + 1.0f)) + -13.8155107f));
		float fSlow76 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry29) + 1.0f)) + -11.5129251f)) * fSlow75)) + 1.0f));
		float fSlow77 = (1.0f - fSlow76);
		float fSlow78 = (float(fEntry31) + 1.0f);
		float fSlow79 = (0.200000003f / (fSlow78 * ((fConst0 * fSlow75) + 1.0f)));
		float fSlow80 = (5.0f * fSlow78);
		float fSlow81 = (5.0f * (1.0f - (float(fEntry32) + 1.0f)));
		float fSlow82 = (1.0f / ((fConst0 * (fSlow75 * std::exp(((5.75646257f * (float(fEntry33) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow83 = (1.0f - fSlow82);
		float fSlow84 = (float(fEntry35) + 1.0f);
		float fSlow85 = ((float(fEntry34) + 1.0f) - fSlow84);
		float fSlow86 = (2.5f * fSlow85);
		float fSlow87 = (0.117647059f / fSlow84);
		float fSlow88 = (fSlow51 * fSlow43);
		float fSlow89 = (fSlow52 + (fSlow58 + fSlow55));
		float fSlow90 = (50.0f * fSlow67);
		float fSlow91 = (1.0f / ((fConst0 * (fSlow68 * std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -2.99573231f)))) + 1.0f));
		float fSlow92 = (1.0f - fSlow91);
		float fSlow93 = (0.294117659f / fSlow56);
		float fSlow94 = (fSlow60 * fSlow43);
		float fSlow95 = (0.5f * (fSlow49 / fSlow94));
		float fSlow96 = (1.0f / fSlow94);
		float fSlow97 = (fSlow82 + -1.0f);
		float fSlow98 = (1.0f - (0.5f * fSlow48));
		float fSlow99 = AmpMono_faustpower2_f((0.5f * fSlow49));
		float fSlow100 = (0.5f * (fSlow46 / fSlow99));
		float fSlow101 = (fSlow99 / fSlow43);
		float fSlow102 = (fSlow99 / fSlow94);
		float fSlow103 = (fSlow91 + -1.0f);
		float fSlow104 = (5.0f * fSlow70);
		int iSlow105 = (fSlow104 < 9.0f);
		int iSlow106 = (fSlow104 < 8.0f);
		int iSlow107 = (fSlow104 < 6.0f);
		int iSlow108 = (fSlow104 < 5.0f);
		int iSlow109 = (fSlow104 < 4.0f);
		int iSlow110 = (fSlow104 < 3.0f);
		int iSlow111 = (fSlow104 < 2.0f);
		int iSlow112 = (fSlow104 < 1.0f);
		float fSlow113 = std::pow(10.0f, (0.0500000007f * (iSlow105?(iSlow106?((fSlow104 < 7.0f)?(iSlow107?(iSlow108?(iSlow109?(iSlow110?(iSlow111?(iSlow112?((fSlow104 < 0.0f)?-3.1500001f:(iSlow112?(-3.1500001f - (25.8999996f * fSlow70)):-8.32999992f)):(iSlow111?(-8.32999992f - (4.86999989f * (fSlow104 + -1.0f))):-13.1999998f)):(iSlow110?(-13.1999998f - (4.30000019f * (fSlow104 + -2.0f))):-17.5f)):(iSlow109?(-17.5f - (3.5f * (fSlow104 + -3.0f))):-21.0f)):(iSlow108?(-21.0f - (2.4000001f * (fSlow104 + -4.0f))):-23.3999996f)):(iSlow107?((5.0f * (1.0f - fSlow70)) + -23.3999996f):-24.3999996f)):-24.3999996f):(iSlow106?((0.400000006f * (fSlow104 + -7.0f)) + -24.3999996f):-24.0f)):(iSlow105?(-24.0f - (0.600000024f * (fSlow104 + -8.0f))):-24.6000004f)):((fSlow104 < 10.0f)?(-24.6000004f - (1.70000005f * (fSlow104 + -9.0f))):-26.2999992f))));
		float fSlow114 = (1.0f - fSlow37);
		float fSlow115 = std::pow(10.0f, (0.0500000007f * fSlow30));
		float fSlow116 = ((fSlow28 < -0.800000012f)?(0.0f - (5.0f * (fSlow28 + 0.800000012f))):0.0f);
		float fSlow117 = (1.0f - fSlow116);
		int iSlow118 = (fSlow32 > 0.0f);
		float fSlow119 = (fConst19 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow32))));
		float fSlow120 = (iSlow118?fConst19:fSlow119);
		float fSlow121 = ((fConst18 * (fConst18 - fSlow120)) + 1.0f);
		float fSlow122 = ((fConst18 * (fConst18 + fSlow120)) + 1.0f);
		float fSlow123 = (iSlow118?fSlow119:fConst19);
		float fSlow124 = ((fConst18 * (fConst18 + fSlow123)) + 1.0f);
		float fSlow125 = ((fConst18 * (fConst18 - fSlow123)) + 1.0f);
		float fSlow126 = ((fSlow31 < -0.800000012f)?(0.0f - (5.0f * (fSlow31 + 0.800000012f))):0.0f);
		float fSlow127 = (1.0f - fSlow126);
		float fSlow128 = std::pow(10.0f, (0.0500000007f * fSlow34));
		float fSlow129 = ((fSlow33 < -0.800000012f)?(0.0f - (5.0f * (fSlow33 + 0.800000012f))):0.0f);
		float fSlow130 = (1.0f - fSlow129);
		float fSlow131 = (250.0f * (float(fEntry37) + 1.0f));
		float fSlow132 = (1.0f / fSlow24);
		float fSlow133 = (1.0f - fSlow23);
		float fSlow134 = std::exp((0.0f - (fConst20 / std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -9.2103405f)))));
		float fSlow135 = (1.0f - fSlow134);
		float fSlow136 = (250.0f * (float(fEntry39) + 1.0f));
		float fSlow137 = std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -9.2103405f));
		float fSlow138 = (1.0f - (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -4.60517025f)) * fSlow137)) + 1.0f)));
		float fSlow139 = (float(fEntry42) + 1.0f);
		float fSlow140 = (0.0199999996f / (fSlow139 * ((fConst0 * fSlow137) + 1.0f)));
		float fSlow141 = (100.0f * (1.0f - (float(fEntry43) + 1.0f)));
		float fSlow142 = (50.0f * fSlow139);
		float fSlow143 = (fSlow19 * std::pow(fSlow17, fSlow18));
		float fSlow144 = std::pow((10.0f * (float(fEntry44) + 1.0f)), fSlow19);
		float fSlow145 = std::exp((0.0f - (fConst20 / std::exp(((4.60517025f * (float(fEntry45) + 1.0f)) + -9.2103405f)))));
		float fSlow146 = (fSlow15 * (1.0f - fSlow145));
		float fSlow147 = (fSlow11 + (10.0f * fSlow13));
		float fSlow148 = (1.0f / fSlow6);
		float fSlow149 = (1.0f - fSlow5);
		float fSlow150 = (fSlow136 + fSlow16);
		float fSlow151 = (5.0f * fSlow26);
		int iSlow152 = (fSlow151 < 9.0f);
		int iSlow153 = (fSlow151 < 8.0f);
		int iSlow154 = (fSlow151 < 7.0f);
		int iSlow155 = (fSlow151 < 6.0f);
		int iSlow156 = (fSlow151 < 5.0f);
		int iSlow157 = (fSlow151 < 4.0f);
		int iSlow158 = (fSlow151 < 3.0f);
		int iSlow159 = (fSlow151 < 2.0f);
		int iSlow160 = (fSlow151 < 1.0f);
		float fSlow161 = std::pow(10.0f, (0.0500000007f * (iSlow152?(iSlow153?(iSlow154?(iSlow155?(iSlow156?(iSlow157?(iSlow158?(iSlow159?(iSlow160?((fSlow151 < 0.0f)?22.6000004f:(iSlow160?(22.6000004f - (30.0f * fSlow26)):16.6000004f)):(iSlow159?(16.6000004f - (5.9000001f * (fSlow151 + -1.0f))):10.6999998f)):(iSlow158?(10.6999998f - (6.01000023f * (fSlow151 + -2.0f))):4.69000006f)):(iSlow157?(4.69000006f - (5.59100008f * (fSlow151 + -3.0f))):-0.901000023f)):(iSlow156?(-0.901000023f - (4.68900013f * (fSlow151 + -4.0f))):-5.59000015f)):(iSlow155?(-5.59000015f - (3.75f * (0.0f - (5.0f * (1.0f - fSlow26))))):-9.34000015f)):(iSlow154?(-9.34000015f - (2.05999994f * (fSlow151 + -6.0f))):-11.3999996f)):(iSlow153?(-11.3999996f - (0.5f * (fSlow151 + -7.0f))):-11.8999996f)):(iSlow152?(-11.8999996f - (0.200000003f * (fSlow151 + -8.0f))):-12.1000004f)):((fSlow151 < 10.0f)?(-12.1000004f - (0.100000001f * (fSlow151 + -9.0f))):-12.1999998f))));
		float fSlow162 = (fConst152 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow71 * fTemp0);
			fRec10[0] = ((fSlow63 * fVec0[1]) - (fSlow72 * ((fSlow73 * fRec10[1]) - (fSlow74 * fTemp0))));
			fRec12[0] = ((fSlow79 * (std::max<float>(0.0f, (fSlow80 - fRec12[1])) * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow81 + fRec10[0])) - fRec12[1])))) + (fSlow83 * fRec12[1]));
			fRec11[0] = ((fSlow77 * fRec11[1]) + (fSlow76 * fRec12[0]));
			float fTemp1 = ((fRec10[0] - fRec11[0]) - fSlow86);
			float fTemp2 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow87 * std::max<float>(0.0f, fTemp1))));
			float fTemp3 = ((std::fabs(fTemp2) + -2.0f) * fTemp2);
			float fTemp4 = (std::min<float>(0.0f, fTemp1) + (2.5f * (fSlow85 + (fSlow84 * (fTemp3 * (std::fabs(fTemp3) + -2.0f))))));
			float fTemp5 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow64 * std::fabs(fTemp4)) + -0.0500000007f)));
			float fTemp6 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow41 + fTemp4)), fSlow51) - fSlow52) * fTemp5) + (fSlow88 * ((1.0f - fTemp5) * fTemp4)))) - fSlow89);
			float fTemp7 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::min<float>(0.0f, fTemp6))));
			float fTemp8 = (fTemp7 * (std::fabs(fTemp7) + -2.0f));
			float fTemp9 = (std::max<float>(0.0f, fTemp6) + (fSlow58 * ((fTemp8 * (std::fabs(fTemp8) + -2.0f)) + 1.0f)));
			fRec9[0] = ((fSlow69 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow55 + ((fTemp9 + -250.0f) - fSlow53))) - fRec9[1])) * std::max<float>(0.0f, (fSlow90 - fRec9[1])))) + (fSlow92 * fRec9[1]));
			float fTemp10 = (fSlow66 * fRec9[0]);
			float fTemp11 = (fSlow57 + ((fTemp9 + (-250.0f - fTemp10)) - fSlow53));
			float fTemp12 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow93 * std::max<float>(0.0f, fTemp11))));
			float fTemp13 = ((std::fabs(fTemp12) + -2.0f) * fTemp12);
			float fTemp14 = (fSlow54 + ((fTemp10 + std::min<float>(0.0f, fTemp11)) + (-50.0f - (fSlow56 * (1.0f - (fTemp13 * (std::fabs(fTemp13) + -2.0f)))))));
			fVec1[0] = (fSlow65 * fTemp14);
			fRec8[0] = ((fSlow63 * fVec1[1]) + (fSlow72 * ((fSlow95 * fTemp14) - (fSlow73 * fRec8[1]))));
			fRec14[0] = ((fSlow79 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow81 + fRec8[0])) - fRec14[1])) * std::max<float>(0.0f, (fSlow80 - fRec14[1])))) + (fSlow83 * fRec14[1]));
			fRec13[0] = ((fSlow76 * fRec14[0]) + (fSlow77 * fRec13[1]));
			float fTemp15 = ((fRec8[0] - fRec13[0]) - fSlow86);
			float fTemp16 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow87 * std::max<float>(0.0f, fTemp15))));
			float fTemp17 = (std::fabs(fTemp16) + -2.0f);
			float fTemp18 = (std::min<float>(0.0f, fTemp15) + (2.5f * (fSlow85 + (fSlow84 * ((fTemp16 * (std::fabs((fTemp16 * fTemp17)) + -2.0f)) * fTemp17)))));
			float fTemp19 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow64 * std::fabs(fTemp18)) + -0.0500000007f)));
			float fTemp20 = ((300.0f - ((fTemp19 * (std::pow(std::max<float>(0.0f, (fSlow41 + fTemp18)), fSlow51) - fSlow52)) + (fSlow88 * (fTemp18 * (1.0f - fTemp19))))) - fSlow89);
			float fTemp21 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::min<float>(0.0f, fTemp20))));
			float fTemp22 = (std::fabs(fTemp21) + -2.0f);
			float fTemp23 = ((fSlow58 * (((fTemp21 * (std::fabs((fTemp21 * fTemp22)) + -2.0f)) * fTemp22) + 1.0f)) + std::max<float>(0.0f, fTemp20));
			fRec15[0] = ((fSlow69 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow55 + ((fTemp23 + -250.0f) - fSlow53))) - fRec15[1])) * std::max<float>(0.0f, (fSlow90 - fRec15[1])))) + (fSlow92 * fRec15[1]));
			float fTemp24 = (fSlow66 * fRec15[0]);
			float fTemp25 = (fSlow57 + ((fTemp23 + (-250.0f - fTemp24)) - fSlow53));
			float fTemp26 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow93 * std::max<float>(0.0f, fTemp25))));
			float fTemp27 = (std::fabs(fTemp26) + -2.0f);
			float fTemp28 = (fSlow54 + ((std::min<float>(0.0f, fTemp25) + fTemp24) + (-50.0f - (fSlow56 * (1.0f - ((fTemp26 * (std::fabs((fTemp26 * fTemp27)) + -2.0f)) * fTemp27))))));
			fVec2[0] = (fSlow44 * fTemp28);
			fRec7[0] = ((fSlow63 * fVec2[1]) - (fSlow72 * ((fSlow73 * fRec7[1]) - (fSlow96 * fTemp28))));
			fRec17[0] = ((fSlow79 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow81 + fRec7[0])) - fRec17[1])) * std::max<float>(0.0f, (fSlow80 - fRec17[1])))) - (fSlow97 * fRec17[1]));
			fRec16[0] = ((fSlow76 * fRec17[0]) + (fSlow77 * fRec16[1]));
			float fTemp29 = ((fRec7[0] - fRec16[0]) - fSlow86);
			float fTemp30 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow87 * std::max<float>(0.0f, fTemp29))));
			float fTemp31 = (fTemp30 * (std::fabs(fTemp30) + -2.0f));
			float fTemp32 = (std::min<float>(0.0f, fTemp29) + (2.5f * (fSlow85 + (fSlow84 * (fTemp31 * (std::fabs(fTemp31) + -2.0f))))));
			float fTemp33 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow64 * std::fabs(fTemp32)) + -0.0500000007f)));
			float fTemp34 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow41 + fTemp32)), fSlow51) - fSlow52) * fTemp33) + (fSlow88 * ((1.0f - fTemp33) * fTemp32)))) - fSlow89);
			float fTemp35 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::min<float>(0.0f, fTemp34))));
			float fTemp36 = (std::fabs(fTemp35) + -2.0f);
			float fTemp37 = ((fSlow58 * ((((std::fabs((fTemp36 * fTemp35)) + -2.0f) * fTemp36) * fTemp35) + 1.0f)) + std::max<float>(0.0f, fTemp34));
			fRec18[0] = ((fSlow69 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow55 + ((fTemp37 + -250.0f) - fSlow53))) - fRec18[1])) * std::max<float>(0.0f, (fSlow90 - fRec18[1])))) + (fSlow92 * fRec18[1]));
			float fTemp38 = (fSlow66 * fRec18[0]);
			float fTemp39 = (fSlow57 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow53));
			float fTemp40 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow93 * std::max<float>(0.0f, fTemp39))));
			float fTemp41 = (std::fabs(fTemp40) + -2.0f);
			float fTemp42 = ((fSlow50 * (fSlow54 + ((std::min<float>(0.0f, fTemp39) + fTemp38) + (-50.0f - (fSlow56 * (1.0f - (((std::fabs((fTemp40 * fTemp41)) + -2.0f) * fTemp40) * fTemp41))))))) + (fSlow98 * fTemp14));
			fVec3[0] = (fSlow101 * fTemp42);
			fRec22[0] = ((fSlow63 * fVec3[1]) - (fSlow72 * ((fSlow73 * fRec22[1]) - (fSlow102 * fTemp42))));
			fRec24[0] = ((fSlow83 * fRec24[1]) + (fSlow79 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow81 + fRec22[0])) - fRec24[1])) * std::max<float>(0.0f, (fSlow80 - fRec24[1])))));
			fRec23[0] = ((fSlow77 * fRec23[1]) + (fSlow76 * fRec24[0]));
			float fTemp43 = ((fRec22[0] - fRec23[0]) - fSlow86);
			float fTemp44 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow87 * std::max<float>(0.0f, fTemp43))));
			float fTemp45 = ((std::fabs(fTemp44) + -2.0f) * fTemp44);
			float fTemp46 = ((2.5f * (fSlow85 + (fSlow84 * (fTemp45 * (std::fabs(fTemp45) + -2.0f))))) + std::min<float>(0.0f, fTemp43));
			float fTemp47 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow64 * std::fabs(fTemp46)) + -0.0500000007f)));
			float fTemp48 = ((300.0f - ((fTemp47 * (std::pow(std::max<float>(0.0f, (fSlow41 + fTemp46)), fSlow51) - fSlow52)) + (fSlow88 * ((1.0f - fTemp47) * fTemp46)))) - fSlow89);
			float fTemp49 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::min<float>(0.0f, fTemp48))));
			float fTemp50 = (std::fabs(fTemp49) + -2.0f);
			float fTemp51 = ((fSlow58 * ((((std::fabs((fTemp50 * fTemp49)) + -2.0f) * fTemp50) * fTemp49) + 1.0f)) + std::max<float>(0.0f, fTemp48));
			fRec21[0] = ((fSlow92 * fRec21[1]) + (fSlow69 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow55 + ((fTemp51 + -250.0f) - fSlow53))) - fRec21[1])) * std::max<float>(0.0f, (fSlow90 - fRec21[1])))));
			float fTemp52 = (fSlow66 * fRec21[0]);
			float fTemp53 = (fSlow57 + ((fTemp51 + (-250.0f - fTemp52)) - fSlow53));
			float fTemp54 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow93 * std::max<float>(0.0f, fTemp53))));
			float fTemp55 = (std::fabs(fTemp54) + -2.0f);
			float fTemp56 = (fSlow54 + ((fTemp52 + std::min<float>(0.0f, fTemp53)) + (-50.0f - (fSlow56 * (1.0f - ((fTemp54 * (std::fabs((fTemp54 * fTemp55)) + -2.0f)) * fTemp55))))));
			fVec4[0] = (fSlow44 * fTemp56);
			fRec20[0] = ((fSlow63 * fVec4[1]) - (fSlow72 * ((fSlow73 * fRec20[1]) - (fSlow96 * fTemp56))));
			fRec26[0] = ((fSlow83 * fRec26[1]) + (fSlow79 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow81 + fRec20[0])) - fRec26[1])) * std::max<float>(0.0f, (fSlow80 - fRec26[1])))));
			fRec25[0] = ((fSlow77 * fRec25[1]) + (fSlow76 * fRec26[0]));
			float fTemp57 = ((fRec20[0] - fRec25[0]) - fSlow86);
			float fTemp58 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow87 * std::max<float>(0.0f, fTemp57))));
			float fTemp59 = (std::fabs(fTemp58) + -2.0f);
			float fTemp60 = ((2.5f * (fSlow85 + (fSlow84 * ((fTemp59 * (std::fabs((fTemp59 * fTemp58)) + -2.0f)) * fTemp58)))) + std::min<float>(0.0f, fTemp57));
			float fTemp61 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow64 * std::fabs(fTemp60)) + -0.0500000007f)));
			float fTemp62 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow41 + fTemp60)), fSlow51) - fSlow52) * fTemp61) + (fSlow88 * ((1.0f - fTemp61) * fTemp60)))) - fSlow89);
			float fTemp63 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow59 * std::min<float>(0.0f, fTemp62))));
			float fTemp64 = (std::fabs(fTemp63) + -2.0f);
			float fTemp65 = (std::max<float>(0.0f, fTemp62) + (fSlow58 * ((((std::fabs((fTemp64 * fTemp63)) + -2.0f) * fTemp64) * fTemp63) + 1.0f)));
			fRec19[0] = ((fSlow69 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow55 + ((fTemp65 + -250.0f) - fSlow53))) - fRec19[1])) * std::max<float>(0.0f, (fSlow90 - fRec19[1])))) - (fSlow103 * fRec19[1]));
			float fTemp66 = (fSlow66 * fRec19[0]);
			float fTemp67 = (fSlow57 + ((fTemp65 + (-250.0f - fTemp66)) - fSlow53));
			float fTemp68 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow93 * std::max<float>(0.0f, fTemp67))));
			float fTemp69 = ((std::fabs(fTemp68) + -2.0f) * fTemp68);
			float fTemp70 = (((fSlow47 * fTemp42) + (fSlow100 * (fSlow54 + ((fTemp66 + std::min<float>(0.0f, fTemp67)) + (-50.0f - (fSlow56 * (1.0f - (fTemp69 * (std::fabs(fTemp69) + -2.0f))))))))) * fSlow113);
			float fTemp71 = (fSlow44 * fTemp70);
			fVec5[0] = fTemp71;
			fRec6[0] = ((fSlow39 * fVec5[1]) - (((fRec6[1] * fSlow114) - (fSlow44 * (fTemp70 / fSlow36))) / fSlow38));
			fRec27[0] = (0.0f - (((fSlow114 * fRec27[1]) - (fTemp71 + fVec5[1])) / fSlow38));
			float fTemp72 = (fRec6[0] + (fRec27[0] * fSlow115));
			fVec6[0] = fTemp72;
			fRec5[0] = ((fConst15 * fVec6[1]) - (fConst16 * ((fConst17 * fRec5[1]) - (fConst13 * fTemp72))));
			float fTemp73 = (fConst11 * fRec4[1]);
			fRec4[0] = (((fRec5[0] * fSlow116) + (fTemp72 * fSlow117)) - (((fRec4[2] * fSlow121) + fTemp73) / fSlow122));
			float fTemp74 = ((fTemp73 + (fRec4[0] * fSlow124)) + (fRec4[2] * fSlow125));
			float fTemp75 = (fConst27 * fRec28[1]);
			fRec28[0] = ((fTemp74 / fSlow122) - (fConst26 * (fTemp75 + (fConst28 * fRec28[2]))));
			float fTemp76 = (((fTemp74 * fSlow127) / fSlow122) + (fConst26 * (fSlow126 * ((fTemp75 + (fConst29 * fRec28[0])) + (fConst29 * fRec28[2])))));
			fVec7[0] = fTemp76;
			fRec3[0] = (0.0f - (fConst8 * ((fConst9 * fRec3[1]) - (fVec7[1] + fTemp76))));
			fRec29[0] = ((fConst30 * fVec7[1]) - (fConst8 * ((fConst9 * fRec29[1]) - (fConst6 * fTemp76))));
			float fTemp77 = (fRec3[0] + (fRec29[0] * fSlow128));
			fVec8[0] = fTemp77;
			fRec2[0] = (0.0f - (fConst3 * ((fConst4 * fRec2[1]) - (fTemp77 + fVec8[1]))));
			float fTemp78 = ((fSlow27 * (fSlow35 * ((fRec2[0] * fSlow129) + (fTemp77 * fSlow130)))) - fSlow131);
			fVec9[0] = fTemp78;
			fRec1[0] = ((fSlow25 * fVec9[1]) - (fSlow132 * ((fSlow133 * fRec1[1]) - (fSlow23 * fTemp78))));
			fRec30[0] = ((fSlow135 * (fRec1[0] - fSlow136)) + (fSlow134 * fRec30[1]));
			fRec32[0] = ((fSlow138 * fRec32[1]) + (fSlow140 * (std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow141 + ((fRec1[0] - fRec30[0]) - fSlow136))) - fRec32[1])) * std::max<float>(0.0f, (fSlow142 - fRec32[1])))));
			float fRec31 = fRec32[0];
			float fTemp79 = (fRec30[0] + fRec31);
			float fTemp80 = (0.0f - ((fRec1[0] - fTemp79) - fSlow136));
			float fTemp81 = (0.0f - fTemp80);
			float fTemp82 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow21 * std::fabs(fTemp81)) + -0.0500000007f)));
			float fTemp83 = (fSlow20 + (((fTemp82 * (std::pow(std::max<float>(0.0f, (fSlow16 + ((fRec1[0] + (30.0f - fTemp79)) - fSlow136))), fSlow19) - fSlow20)) + (fSlow143 * (fTemp81 * (1.0f - fTemp82)))) - fSlow144));
			fRec33[0] = ((fSlow146 * fTemp83) + (fSlow145 * fRec33[1]));
			float fTemp84 = (((fSlow15 * fTemp83) - fRec33[0]) - fSlow147);
			float fTemp85 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow14 * std::max<float>(0.0f, fTemp84))));
			float fTemp86 = ((std::fabs(fTemp85) + -2.0f) * fTemp85);
			float fTemp87 = (fSlow11 + (((10.0f * (fSlow13 + (fSlow12 * (fTemp86 * (std::fabs(fTemp86) + -2.0f))))) + std::min<float>(0.0f, fTemp84)) - fSlow9));
			float fTemp88 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow10 * std::min<float>(0.0f, fTemp87))));
			float fTemp89 = (fTemp88 * (std::fabs(fTemp88) + -2.0f));
			float fTemp90 = ((fSlow9 * ((fTemp89 * (std::fabs(fTemp89) + -2.0f)) + 1.0f)) + std::max<float>(0.0f, fTemp87));
			fVec10[0] = fTemp90;
			fRec0[0] = ((fSlow7 * fVec10[1]) - (fSlow148 * ((fSlow149 * fRec0[1]) - (fSlow5 * fTemp90))));
			float fTemp91 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow21 * std::fabs(fTemp80)) + -0.0500000007f)));
			float fTemp92 = (fSlow20 + ((((std::pow(std::max<float>(0.0f, (fSlow150 + (fTemp79 + (30.0f - fRec1[0])))), fSlow19) - fSlow20) * fTemp91) + (fSlow143 * (fTemp80 * (1.0f - fTemp91)))) - fSlow144));
			fRec35[0] = ((fSlow146 * fTemp92) + (fSlow145 * fRec35[1]));
			float fTemp93 = (((fSlow15 * fTemp92) - fRec35[0]) - fSlow147);
			float fTemp94 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow14 * std::max<float>(0.0f, fTemp93))));
			float fTemp95 = (fTemp94 * (std::fabs(fTemp94) + -2.0f));
			float fTemp96 = (fSlow11 + ((std::min<float>(0.0f, fTemp93) + (10.0f * (fSlow13 + (fSlow12 * (fTemp95 * (std::fabs(fTemp95) + -2.0f)))))) - fSlow9));
			float fTemp97 = std::max<float>(-1.0f, std::min<float>(1.0f, (fSlow10 * std::min<float>(0.0f, fTemp96))));
			float fTemp98 = (std::fabs(fTemp97) + -2.0f);
			float fTemp99 = (std::max<float>(0.0f, fTemp96) + (fSlow9 * ((((std::fabs((fTemp98 * fTemp97)) + -2.0f) * fTemp98) * fTemp97) + 1.0f)));
			fVec11[0] = fTemp99;
			fRec34[0] = ((fSlow7 * fVec11[1]) - (fSlow148 * ((fSlow149 * fRec34[1]) - (fSlow5 * fTemp99))));
			float fTemp100 = ((fRec0[0] - fRec34[0]) * fSlow161);
			float fTemp101 = (fSlow3 * fTemp100);
			fVec12[0] = fTemp101;
			fRec58[0] = ((fConst150 * fVec12[1]) + (fConst151 * ((fSlow162 * fTemp100) - (fConst153 * fRec58[1]))));
			fRec57[0] = (0.0f - (fConst145 * ((fConst146 * fRec57[1]) - (fRec58[0] + fRec58[1]))));
			fRec56[0] = ((fConst143 * fRec57[1]) - (fConst154 * ((fConst155 * fRec56[1]) - (fConst133 * fRec57[0]))));
			fRec55[0] = (fRec56[0] - (fConst141 * ((fConst156 * fRec55[2]) + (fConst157 * fRec55[1]))));
			fRec54[0] = ((fConst141 * ((fConst136 * fRec55[2]) + ((fConst136 * fRec55[0]) + (fConst138 * fRec55[1])))) - (fConst140 * ((fConst157 * fRec54[1]) + (fConst158 * fRec54[2]))));
			fRec53[0] = ((fConst140 * ((fConst136 * fRec54[2]) + ((fConst136 * fRec54[0]) + (fConst138 * fRec54[1])))) - (fConst139 * ((fConst159 * fRec53[2]) + (fConst157 * fRec53[1]))));
			fRec52[0] = ((fConst139 * (((fConst138 * fRec53[1]) + (fConst136 * fRec53[0])) + (fConst136 * fRec53[2]))) - (fConst137 * ((fConst160 * fRec52[2]) + (fConst157 * fRec52[1]))));
			fRec51[0] = ((fConst137 * (((fConst138 * fRec52[1]) + (fConst136 * fRec52[0])) + (fConst136 * fRec52[2]))) - (fConst134 * ((fConst161 * fRec51[2]) + (fConst157 * fRec51[1]))));
			fRec64[0] = (0.0f - (fConst154 * ((fConst155 * fRec64[1]) - (fRec57[0] + fRec57[1]))));
			fRec63[0] = (fRec64[0] - (fConst141 * ((fConst157 * fRec63[1]) + (fConst156 * fRec63[2]))));
			fRec62[0] = ((fConst141 * (fRec63[2] + (fRec63[0] + (2.0f * fRec63[1])))) - (fConst140 * ((fConst157 * fRec62[1]) + (fConst158 * fRec62[2]))));
			fRec61[0] = ((fConst140 * (fRec62[2] + (fRec62[0] + (2.0f * fRec62[1])))) - (fConst139 * ((fConst159 * fRec61[2]) + (fConst157 * fRec61[1]))));
			fRec60[0] = ((fConst139 * (fRec61[2] + (fRec61[0] + (2.0f * fRec61[1])))) - (fConst137 * ((fConst157 * fRec60[1]) + (fConst160 * fRec60[2]))));
			fRec59[0] = ((fConst137 * ((fRec60[0] + (2.0f * fRec60[1])) + fRec60[2])) - (fConst134 * ((fConst157 * fRec59[1]) + (fConst161 * fRec59[2]))));
			float fTemp102 = (fConst162 * fRec50[1]);
			fRec50[0] = ((fConst134 * ((0.13673377f * ((fConst136 * fRec51[2]) + ((fConst138 * fRec51[1]) + (fConst136 * fRec51[0])))) + (fRec59[2] + (fRec59[0] + (2.0f * fRec59[1]))))) - (fConst129 * (fTemp102 + (fConst163 * fRec50[2]))));
			float fTemp103 = (fConst124 * fRec49[1]);
			fRec49[0] = ((fConst129 * ((fConst131 * fRec50[2]) + ((fConst164 * fRec50[0]) + fTemp102))) - (fConst123 * (fTemp103 + (fConst165 * fRec49[2]))));
			float fTemp104 = (fConst118 * fRec48[1]);
			fRec48[0] = ((fConst123 * ((fTemp103 + (fConst167 * fRec49[0])) + (fConst168 * fRec49[2]))) - (fConst117 * ((fConst169 * fRec48[2]) + fTemp104)));
			float fTemp105 = (fConst174 * fRec47[1]);
			fRec47[0] = ((fConst117 * ((fTemp104 + (fConst171 * fRec48[0])) + (fConst172 * fRec48[2]))) - (fConst110 * ((fConst173 * fRec47[2]) + fTemp105)));
			float fTemp106 = (fConst177 * fRec46[1]);
			fRec46[0] = ((fConst110 * ((fConst112 * fRec47[2]) + (fTemp105 + (fConst175 * fRec47[0])))) - (fConst103 * ((fConst176 * fRec46[2]) + fTemp106)));
			float fTemp107 = (fConst98 * fRec45[1]);
			fRec45[0] = ((fConst103 * (((fConst105 * fRec46[0]) + fTemp106) + (fConst178 * fRec46[2]))) - (fConst97 * ((fConst179 * fRec45[2]) + fTemp107)));
			float fTemp108 = (fConst92 * fRec44[1]);
			fRec44[0] = ((fConst97 * ((fTemp107 + (fConst181 * fRec45[0])) + (fConst182 * fRec45[2]))) - (fConst91 * ((fConst183 * fRec44[2]) + fTemp108)));
			float fTemp109 = (fConst188 * fRec43[1]);
			fRec43[0] = ((fConst91 * ((fTemp108 + (fConst185 * fRec44[0])) + (fConst186 * fRec44[2]))) - (fConst84 * ((fConst187 * fRec43[2]) + fTemp109)));
			float fTemp110 = (fConst190 * fRec42[1]);
			fRec42[0] = ((fConst84 * ((fConst86 * fRec43[2]) + ((fConst189 * fRec43[0]) + fTemp109))) - (fConst77 * (fTemp110 + (fConst191 * fRec42[2]))));
			float fTemp111 = (fConst193 * fRec41[1]);
			fRec41[0] = ((fConst77 * ((fConst79 * fRec42[2]) + (fTemp110 + (fConst192 * fRec42[0])))) - (fConst70 * (fTemp111 + (fConst194 * fRec41[2]))));
			float fTemp112 = (fConst196 * fRec40[1]);
			fRec40[0] = ((fConst70 * ((fConst72 * fRec41[2]) + (fTemp111 + (fConst195 * fRec41[0])))) - (fConst63 * (fTemp112 + (fConst197 * fRec40[2]))));
			float fTemp113 = (fConst200 * fRec39[1]);
			fRec39[0] = ((fConst63 * ((fConst65 * fRec40[2]) + ((fConst198 * fRec40[0]) + fTemp112))) - (fConst56 * ((fConst199 * fRec39[2]) + fTemp113)));
			float fTemp114 = (fConst202 * fRec38[1]);
			fRec38[0] = ((fConst56 * (((fConst58 * fRec39[0]) + fTemp113) + (fConst201 * fRec39[2]))) - (fConst49 * (fTemp114 + (fConst203 * fRec38[2]))));
			float fTemp115 = (fConst206 * fRec37[1]);
			fRec37[0] = ((fConst49 * ((fConst51 * fRec38[2]) + (fTemp114 + (fConst204 * fRec38[0])))) - (fConst42 * ((fConst205 * fRec37[2]) + fTemp115)));
			float fTemp116 = (fConst37 * fRec36[1]);
			fRec36[0] = ((fConst42 * ((fConst44 * fRec37[2]) + (fTemp115 + (fConst207 * fRec37[0])))) - (fConst208 * ((fConst209 * fRec36[2]) + fTemp116)));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst36 * ((fTemp116 + (fConst211 * fRec36[0])) + (fConst212 * fRec36[2]))):fTemp101)));
			fVec0[1] = fVec0[0];
			fRec10[1] = fRec10[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec9[1] = fRec9[0];
			fVec1[1] = fVec1[0];
			fRec8[1] = fRec8[0];
			fRec14[1] = fRec14[0];
			fRec13[1] = fRec13[0];
			fRec15[1] = fRec15[0];
			fVec2[1] = fVec2[0];
			fRec7[1] = fRec7[0];
			fRec17[1] = fRec17[0];
			fRec16[1] = fRec16[0];
			fRec18[1] = fRec18[0];
			fVec3[1] = fVec3[0];
			fRec22[1] = fRec22[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec21[1] = fRec21[0];
			fVec4[1] = fVec4[0];
			fRec20[1] = fRec20[0];
			fRec26[1] = fRec26[0];
			fRec25[1] = fRec25[0];
			fRec19[1] = fRec19[0];
			fVec5[1] = fVec5[0];
			fRec6[1] = fRec6[0];
			fRec27[1] = fRec27[0];
			fVec6[1] = fVec6[0];
			fRec5[1] = fRec5[0];
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
			fRec33[1] = fRec33[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
			fRec35[1] = fRec35[0];
			fVec11[1] = fVec11[0];
			fRec34[1] = fRec34[0];
			fVec12[1] = fVec12[0];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
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
			fRec37[2] = fRec37[1];
			fRec37[1] = fRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];

		}

	}


};

#endif
