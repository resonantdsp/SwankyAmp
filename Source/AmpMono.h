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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fEntry1;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
	float fConst11;
	float fConst12;
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
	FAUSTFLOAT fEntry2;
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
	float fConst120;
	FAUSTFLOAT fEntry13;
	FAUSTFLOAT fEntry14;
	FAUSTFLOAT fEntry15;
	FAUSTFLOAT fEntry16;
	FAUSTFLOAT fEntry17;
	float fConst121;
	float fConst122;
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
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
	float fVec0[2];
	float fRec34[2];
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	float fRec38[2];
	float fRec37[2];
	FAUSTFLOAT fEntry36;
	FAUSTFLOAT fEntry37;
	float fRec36[2];
	float fRec35[2];
	FAUSTFLOAT fEntry38;
	float fRec33[2];
	FAUSTFLOAT fEntry39;
	FAUSTFLOAT fEntry40;
	float fRec32[2];
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fVec1[2];
	float fRec42[2];
	float fRec44[2];
	float fRec43[2];
	float fRec46[2];
	float fRec45[2];
	float fRec41[2];
	float fRec47[2];
	float fVec2[2];
	float fRec40[2];
	float fRec51[2];
	float fRec50[2];
	float fRec49[2];
	float fRec48[2];
	float fRec39[2];
	float fRec52[2];
	float fVec3[2];
	float fRec56[2];
	float fRec58[2];
	float fRec57[2];
	float fRec60[2];
	float fRec59[2];
	float fRec55[2];
	float fRec61[2];
	float fVec4[2];
	float fRec54[2];
	float fRec63[2];
	float fRec62[2];
	float fRec65[2];
	float fRec64[2];
	float fRec53[2];
	float fRec66[2];
	float fVec5[2];
	float fRec31[2];
	float fRec67[2];
	float fVec6[2];
	float fConst129;
	float fConst130;
	float fRec30[2];
	float fConst131;
	float fConst132;
	float fConst133;
	float fConst134;
	float fRec29[3];
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
	float fRec68[3];
	float fVec7[2];
	float fConst145;
	float fRec28[2];
	float fConst146;
	float fRec69[2];
	float fVec8[2];
	float fConst147;
	float fConst148;
	float fConst149;
	float fRec70[2];
	FAUSTFLOAT fEntry43;
	float fVec9[2];
	float fRec27[2];
	FAUSTFLOAT fEntry44;
	float fRec71[2];
	float fRec26[2];
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec73[2];
	FAUSTFLOAT fEntry49;
	FAUSTFLOAT fEntry50;
	float fRec24[2];
	float fRec75[2];
	float fRec77[2];
	float fConst150;
	float fConst151;
	float fVec10[2];
	float fRec22[2];
	float fRec21[2];
	float fConst152;
	float fRec20[2];
	float fConst153;
	float fConst154;
	float fConst155;
	float fConst156;
	float fRec19[3];
	float fConst157;
	float fRec18[3];
	float fConst158;
	float fRec17[3];
	float fConst159;
	float fRec16[3];
	float fConst160;
	float fRec15[3];
	float fConst161;
	float fConst162;
	float fRec83[2];
	float fRec82[3];
	float fRec81[3];
	float fRec80[3];
	float fRec79[3];
	float fRec78[3];
	float fConst163;
	float fConst164;
	float fRec14[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec13[3];
	float fConst168;
	float fConst169;
	float fRec12[3];
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fConst174;
	float fRec11[3];
	float fConst175;
	float fConst176;
	float fConst177;
	float fRec10[3];
	float fConst178;
	float fConst179;
	float fConst180;
	float fRec9[3];
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec8[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fRec7[3];
	float fConst187;
	float fConst188;
	float fConst189;
	float fRec6[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fRec5[3];
	float fConst193;
	float fConst194;
	float fRec4[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fConst198;
	float fRec3[3];
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fConst203;
	float fRec2[3];
	float fConst204;
	float fConst205;
	float fRec1[3];
	float fConst206;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fConst211;
	float fRec0[3];
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
		fConst1 = std::tan((5574.98535f / fConst0));
		fConst2 = (1.0f / fConst1);
		fConst3 = (fConst0 * std::sin((11149.9707f / fConst0)));
		fConst4 = (4376.67188f / fConst3);
		fConst5 = (((fConst2 + fConst4) / fConst1) + 1.0f);
		fConst6 = (0.144011721f / fConst5);
		fConst7 = (2760.92456f / fConst3);
		fConst8 = (((fConst2 - fConst7) / fConst1) + 1.0f);
		fConst9 = std::tan((4288.271f / fConst0));
		fConst10 = (1.0f / fConst9);
		fConst11 = (fConst0 * std::sin((8576.54199f / fConst0)));
		fConst12 = (326.939972f / fConst11);
		fConst13 = (1.0f / (((fConst10 + fConst12) / fConst9) + 1.0f));
		fConst14 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst9))));
		fConst15 = std::tan((3537.37793f / fConst0));
		fConst16 = (1.0f / fConst15);
		fConst17 = (fConst0 * std::sin((7074.75586f / fConst0)));
		fConst18 = (642.945251f / fConst17);
		fConst19 = (1.0f / (((fConst16 + fConst18) / fConst15) + 1.0f));
		fConst20 = (270.569763f / fConst17);
		fConst21 = (((fConst16 - fConst20) / fConst15) + 1.0f);
		fConst22 = std::tan((3081.90234f / fConst0));
		fConst23 = (1.0f / fConst22);
		fConst24 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst25 = (486.410919f / fConst24);
		fConst26 = (1.0f / (((fConst23 + fConst25) / fConst22) + 1.0f));
		fConst27 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst22))));
		fConst28 = std::tan((2592.47217f / fConst0));
		fConst29 = (1.0f / fConst28);
		fConst30 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst31 = (317.628265f / fConst30);
		fConst32 = (1.0f / (((fConst29 + fConst31) / fConst28) + 1.0f));
		fConst33 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
		fConst34 = std::tan((1891.23853f / fConst0));
		fConst35 = (1.0f / fConst34);
		fConst36 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst37 = (265.978119f / fConst36);
		fConst38 = (1.0f / (((fConst35 + fConst37) / fConst34) + 1.0f));
		fConst39 = (116.345184f / fConst36);
		fConst40 = (((fConst35 + fConst39) / fConst34) + 1.0f);
		fConst41 = std::tan((21179.4824f / fConst0));
		fConst42 = (1.0f / fConst41);
		fConst43 = (fConst0 * std::sin((42358.9648f / fConst0)));
		fConst44 = (7223.21826f / fConst43);
		fConst45 = (1.0f / (((fConst42 + fConst44) / fConst41) + 1.0f));
		fConst46 = (1059.12756f / fConst43);
		fConst47 = (((fConst42 + fConst46) / fConst41) + 1.0f);
		fConst48 = std::tan((15066.6357f / fConst0));
		fConst49 = (1.0f / fConst48);
		fConst50 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst51 = (11187.3662f / fConst50);
		fConst52 = (1.0f / (((fConst49 + fConst51) / fConst48) + 1.0f));
		fConst53 = (36783.4805f / fConst50);
		fConst54 = (((fConst49 - fConst53) / fConst48) + 1.0f);
		fConst55 = std::tan((13437.668f / fConst0));
		fConst56 = (1.0f / fConst55);
		fConst57 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst58 = (13245.1885f / fConst57);
		fConst59 = (1.0f / (((fConst56 + fConst58) / fConst55) + 1.0f));
		fConst60 = (4583.19189f / fConst57);
		fConst61 = (((fConst56 + fConst60) / fConst55) + 1.0f);
		fConst62 = std::tan((10058.502f / fConst0));
		fConst63 = (1.0f / fConst62);
		fConst64 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst65 = (4926.20459f / fConst64);
		fConst66 = (1.0f / (((fConst63 + fConst65) / fConst62) + 1.0f));
		fConst67 = (9024.73242f / fConst64);
		fConst68 = (((fConst63 + fConst67) / fConst62) + 1.0f);
		fConst69 = std::tan((8136.54736f / fConst0));
		fConst70 = (1.0f / fConst69);
		fConst71 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst72 = (966.024841f / fConst71);
		fConst73 = (1.0f / (((fConst70 + fConst72) / fConst69) + 1.0f));
		fConst74 = (518.801147f / fConst71);
		fConst75 = (((fConst70 - fConst74) / fConst69) + 1.0f);
		fConst76 = std::tan((8011.02734f / fConst0));
		fConst77 = (1.0f / fConst76);
		fConst78 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst79 = (1613.9762f / fConst78);
		fConst80 = (1.0f / (((fConst77 + fConst79) / fConst76) + 1.0f));
		fConst81 = (3097.15845f / fConst78);
		fConst82 = (((fConst77 + fConst81) / fConst76) + 1.0f);
		fConst83 = std::tan((9456.15234f / fConst0));
		fConst84 = (1.0f / fConst83);
		fConst85 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst86 = (2492.29883f / fConst85);
		fConst87 = (1.0f / (((fConst84 + fConst86) / fConst83) + 1.0f));
		fConst88 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst83))));
		fConst89 = std::tan((2827.43262f / fConst0));
		fConst90 = (1.0f / fConst89);
		fConst91 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst92 = (19634.3262f / fConst91);
		fConst93 = (1.0f / (((fConst90 + fConst92) / fConst89) + 1.0f));
		fConst94 = (106249.391f / fConst91);
		fConst95 = (((fConst90 - fConst94) / fConst89) + 1.0f);
		fConst96 = std::tan((375.293884f / fConst0));
		fConst97 = (1.0f / fConst96);
		fConst98 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst99 = (463.734222f / fConst98);
		fConst100 = (1.0f / (((fConst97 + fConst99) / fConst96) + 1.0f));
		fConst101 = (3220.11475f / fConst98);
		fConst102 = (((fConst97 + fConst101) / fConst96) + 1.0f);
		fConst103 = std::tan((18369.8027f / fConst0));
		fConst104 = (1.0f / fConst103);
		fConst105 = (1.0f / (((fConst104 + 0.284629673f) / fConst103) + 1.0f));
		fConst106 = (1.0f / (((fConst104 + 0.830830038f) / fConst103) + 1.0f));
		fConst107 = (1.0f / (((fConst104 + 1.30972147f) / fConst103) + 1.0f));
		fConst108 = (1.0f / (((fConst104 + 1.68250704f) / fConst103) + 1.0f));
		fConst109 = (1.0f / (((fConst104 + 1.91898596f) / fConst103) + 1.0f));
		fConst110 = (fConst104 + 1.0f);
		fConst111 = (1.0f / fConst110);
		fConst112 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst113 = (1.0f / (fConst112 + 1.0f));
		fConst114 = (1.0f - fConst112);
		fConst115 = std::tan((452.102844f / fConst0));
		fConst116 = (1.0f / fConst115);
		fConst117 = (fConst116 + 1.0f);
		fConst118 = (1.0f / fConst117);
		fConst119 = (0.0199999996f / fConst115);
		fConst120 = (3.14159274f / fConst0);
		fConst121 = std::tan((6283.18555f / fConst0));
		fConst122 = (1.0f / fConst121);
		fConst123 = (fConst122 + 1.0f);
		fConst124 = (1.0f / fConst123);
		fConst125 = std::tan((78.5398178f / fConst0));
		fConst126 = (1.0f / fConst125);
		fConst127 = (fConst126 + 1.0f);
		fConst128 = (0.0f - (1.0f / (fConst125 * fConst127)));
		fConst129 = (1.0f / fConst127);
		fConst130 = (1.0f - fConst126);
		fConst131 = std::tan((1382.30078f / fConst0));
		fConst132 = (1.0f / fConst131);
		fConst133 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst134 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst131))));
		fConst135 = std::tan((1696.46008f / fConst0));
		fConst136 = (fConst0 * fConst135);
		fConst137 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * std::tan((1068.14148f / fConst0))) * fConst135))));
		fConst138 = (2.0f * (((2.0f * fConst136) - (0.5f * (fConst137 / fConst136))) / fConst0));
		fConst139 = (1.0f / fConst0);
		fConst140 = (AmpMono_faustpower2_f(fConst139) * fConst137);
		fConst141 = (1.0f / ((fConst138 + fConst140) + 4.0f));
		fConst142 = (fConst140 + 4.0f);
		fConst143 = (fConst140 + (4.0f - fConst138));
		fConst144 = ((2.0f * fConst140) + -8.0f);
		fConst145 = (1.0f - fConst122);
		fConst146 = (0.0f - (1.0f / (fConst121 * fConst123)));
		fConst147 = (1.0f / std::tan((50265.4844f / fConst0)));
		fConst148 = (1.0f / (fConst147 + 1.0f));
		fConst149 = (1.0f - fConst147);
		fConst150 = (1.0f - fConst116);
		fConst151 = (0.0f - (1.0f / (fConst115 * fConst117)));
		fConst152 = (1.0f - fConst104);
		fConst153 = AmpMono_faustpower2_f(fConst103);
		fConst154 = (1.0f / fConst153);
		fConst155 = (2.0f * (1.0f - fConst154));
		fConst156 = (((fConst104 + -1.91898596f) / fConst103) + 1.0f);
		fConst157 = (((fConst104 + -1.68250704f) / fConst103) + 1.0f);
		fConst158 = (((fConst104 + -1.30972147f) / fConst103) + 1.0f);
		fConst159 = (((fConst104 + -0.830830038f) / fConst103) + 1.0f);
		fConst160 = (((fConst104 + -0.284629673f) / fConst103) + 1.0f);
		fConst161 = (0.0f - (2.0f / fConst153));
		fConst162 = (0.0f - (1.0f / (fConst103 * fConst110)));
		fConst163 = (((fConst97 - fConst99) / fConst96) + 1.0f);
		fConst164 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst96))));
		fConst165 = (((fConst97 - fConst101) / fConst96) + 1.0f);
		fConst166 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst89))));
		fConst167 = (((fConst90 - fConst92) / fConst89) + 1.0f);
		fConst168 = (((fConst90 + fConst94) / fConst89) + 1.0f);
		fConst169 = (((fConst84 - fConst86) / fConst83) + 1.0f);
		fConst170 = (974.257141f / fConst85);
		fConst171 = (((fConst84 + fConst170) / fConst83) + 1.0f);
		fConst172 = (((fConst84 - fConst170) / fConst83) + 1.0f);
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst76))));
		fConst174 = (((fConst77 - fConst79) / fConst76) + 1.0f);
		fConst175 = (((fConst77 - fConst81) / fConst76) + 1.0f);
		fConst176 = (((fConst70 - fConst72) / fConst69) + 1.0f);
		fConst177 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst69))));
		fConst178 = (((fConst70 + fConst74) / fConst69) + 1.0f);
		fConst179 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst62))));
		fConst180 = (((fConst63 - fConst65) / fConst62) + 1.0f);
		fConst181 = (((fConst63 - fConst67) / fConst62) + 1.0f);
		fConst182 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst55))));
		fConst183 = (((fConst56 - fConst58) / fConst55) + 1.0f);
		fConst184 = (((fConst56 - fConst60) / fConst55) + 1.0f);
		fConst185 = (((fConst49 - fConst51) / fConst48) + 1.0f);
		fConst186 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst48))));
		fConst187 = (((fConst49 + fConst53) / fConst48) + 1.0f);
		fConst188 = (((fConst42 - fConst44) / fConst41) + 1.0f);
		fConst189 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst41))));
		fConst190 = (((fConst42 - fConst46) / fConst41) + 1.0f);
		fConst191 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst34))));
		fConst192 = (((fConst35 - fConst37) / fConst34) + 1.0f);
		fConst193 = (((fConst35 - fConst39) / fConst34) + 1.0f);
		fConst194 = (((fConst29 - fConst31) / fConst28) + 1.0f);
		fConst195 = (148.323349f / fConst30);
		fConst196 = (((fConst29 + fConst195) / fConst28) + 1.0f);
		fConst197 = (((fConst29 - fConst195) / fConst28) + 1.0f);
		fConst198 = (((fConst23 - fConst25) / fConst22) + 1.0f);
		fConst199 = (183.178085f / fConst24);
		fConst200 = (((fConst23 + fConst199) / fConst22) + 1.0f);
		fConst201 = (((fConst23 - fConst199) / fConst22) + 1.0f);
		fConst202 = (((fConst16 - fConst18) / fConst15) + 1.0f);
		fConst203 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst15))));
		fConst204 = (((fConst16 + fConst20) / fConst15) + 1.0f);
		fConst205 = (((fConst10 - fConst12) / fConst9) + 1.0f);
		fConst206 = (190.645706f / fConst11);
		fConst207 = (((fConst10 + fConst206) / fConst9) + 1.0f);
		fConst208 = (((fConst10 - fConst206) / fConst9) + 1.0f);
		fConst209 = (1.0f / fConst5);
		fConst210 = (((fConst2 - fConst4) / fConst1) + 1.0f);
		fConst211 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst1))));
		fConst212 = (((fConst2 + fConst7) / fConst1) + 1.0f);

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
			fRec34[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec38[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec37[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec36[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec35[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec33[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec32[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec42[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec44[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec43[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec46[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec45[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec41[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec47[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec2[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec40[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec51[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec50[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec49[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec48[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec39[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec52[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec3[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec56[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec58[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec57[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec60[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec59[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec55[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec61[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec4[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec54[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec63[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec62[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec65[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec64[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec53[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec66[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec5[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec31[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec67[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec6[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec30[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec29[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec68[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec7[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec28[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec69[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec8[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec70[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec9[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec27[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec71[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec26[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec73[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec24[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec75[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec77[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec10[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec22[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec21[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec20[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec19[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec18[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec17[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec16[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec15[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
			fRec83[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec82[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec81[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec80[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec79[l73] = 0.0f;

		}
		for (int l74 = 0; (l74 < 3); l74 = (l74 + 1)) {
			fRec78[l74] = 0.0f;

		}
		for (int l75 = 0; (l75 < 3); l75 = (l75 + 1)) {
			fRec14[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec13[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec12[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec11[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec10[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec9[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec8[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec7[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec6[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec5[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec4[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec3[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec2[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec1[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec0[l89] = 0.0f;

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

	void set_cab_mix(FAUSTFLOAT value) { fEntry1 = value + 1.000000e+00; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry42 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry20 = value + 1.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry29 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry28 = value + 0.000000e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry12 = value + 4.244019e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry43 = value + 4.810579e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry9 = value + -2.048106e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry11 = value + 6.148691e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry10 = value + -6.102038e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry44 = value + 1.980396e-04; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry13 = value + -6.358174e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry7 = value + -1.575095e+00; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry5 = value + 5.307900e-03; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry49 = value + -2.068471e-01; }
	void set_tetrode_plate_level(FAUSTFLOAT value) { fEntry47 = value + -5.551660e-01; }
	void set_tetrode_plate_level_b(FAUSTFLOAT value) { fEntry4 = value + -1.215200e+01; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry45 = value + -1.261398e+01; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00; }
	void set_tetrode_plate_ratio(FAUSTFLOAT value) { fEntry48 = value + 3.132527e-01; }
	void set_tetrode_plate_ratio_b(FAUSTFLOAT value) { fEntry50 = value + 1.903164e+03; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry6 = value + -5.594136e-01; }
	void set_tetrode_plate_tau(FAUSTFLOAT value) { fEntry46 = value + 1.847860e-02; }
	void set_tetrode_plate_tau_b(FAUSTFLOAT value) { fEntry3 = value + 4.243600e-01; }
	void set_triode_clip_level(FAUSTFLOAT value) { fEntry36 = value + 9.067676e-01; }
	void set_triode_clip_ratio(FAUSTFLOAT value) { fEntry37 = value + 1.147704e+00; }
	void set_triode_clip_smooth(FAUSTFLOAT value) { fEntry31 = value + -3.100322e+00; }
	void set_triode_clip_tau(FAUSTFLOAT value) { fEntry30 = value + -1.301785e+00; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry34 = value + 3.380630e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry35 = value + 1.066531e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry33 = value + 1.399600e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry32 = value + -1.121188e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry27 = value + 4.522249e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry18 = value + -1.120198e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry24 = value + 7.278736e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry39 = value + -3.222958e-01; }
	void set_triode_plate_level(FAUSTFLOAT value) { fEntry38 = value + 6.567379e+01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry21 = value + -9.430010e-02; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry19 = value + 0.000000e+00; }
	void set_triode_plate_ratio(FAUSTFLOAT value) { fEntry26 = value + 6.117379e+01; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry40 = value + 8.422808e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.523370e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry22 = value + -3.318985e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry41 = value + -3.580170e+00; }
	void set_triode_plate_tau(FAUSTFLOAT value) { fEntry25 = value + 6.579679e+01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry23 = value + -4.311549e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry17 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry16 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry15 = value + 0.000000e+00; }
	void zero_all() {
		set_cab_mix(0.0f);
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
		set_tetrode_plate_bias(0.0f);
		set_tetrode_plate_clip(0.0f);
		set_tetrode_plate_corner(0.0f);
		set_tetrode_plate_level(0.0f);
		set_tetrode_plate_level_b(0.0f);
		set_tetrode_plate_point(0.0f);
		set_tetrode_plate_power(0.0f);
		set_tetrode_plate_ratio(0.0f);
		set_tetrode_plate_ratio_b(0.0f);
		set_tetrode_plate_scale(0.0f);
		set_tetrode_plate_tau(0.0f);
		set_tetrode_plate_tau_b(0.0f);
		set_triode_clip_level(0.0f);
		set_triode_clip_ratio(0.0f);
		set_triode_clip_smooth(0.0f);
		set_triode_clip_tau(0.0f);
		set_triode_grid_level(0.0f);
		set_triode_grid_ratio(0.0f);
		set_triode_grid_smooth(0.0f);
		set_triode_grid_tau(0.0f);
		set_triode_hp_freq(0.0f);
		set_triode_plate_bias(0.0f);
		set_triode_plate_clip(0.0f);
		set_triode_plate_corner(0.0f);
		set_triode_plate_level(0.0f);
		set_triode_plate_level_b(0.0f);
		set_triode_plate_power(0.0f);
		set_triode_plate_ratio(0.0f);
		set_triode_plate_ratio_b(0.0f);
		set_triode_plate_scale(0.0f);
		set_triode_plate_scale_b(0.0f);
		set_triode_plate_smooth_b(0.0f);
		set_triode_plate_tau(0.0f);
		set_triode_plate_tau_b(0.0f);
		set_ts_high(0.0f);
		set_ts_low(0.0f);
		set_ts_mid(0.0f);
	}

	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = (0.251188636f * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f)))))));
		float fSlow1 = float(fEntry1);
		float fSlow2 = (fConst6 * fSlow1);
		float fSlow3 = (float(fEntry2) + 1.0f);
		float fSlow4 = (fConst119 / fSlow3);
		float fSlow5 = std::exp(((4.60517025f * (float(fEntry3) + 1.0f)) + -9.2103405f));
		float fSlow6 = (1.0f / ((fConst0 * fSlow5) + 1.0f));
		float fSlow7 = (100.0f * (1.0f - (float(fEntry4) + 1.0f)));
		float fSlow8 = (20.0f * (float(fEntry5) + 1.0f));
		float fSlow9 = std::exp(((4.60517025f * (float(fEntry6) + 1.0f)) + -4.60517025f));
		float fSlow10 = (10.0f * (float(fEntry7) + 1.0f));
		float fSlow11 = (fSlow10 + 30.0f);
		float fSlow12 = (0.5f * (float(fEntry8) + 1.0f));
		float fSlow13 = (fSlow12 + 1.0f);
		float fSlow14 = std::pow(fSlow11, fSlow13);
		float fSlow15 = (250.0f * (float(fEntry9) + 1.0f));
		float fSlow16 = (fSlow15 + fSlow10);
		float fSlow17 = std::exp(((4.60517025f * (float(fEntry10) + 1.0f)) + -9.2103405f));
		float fSlow18 = (1.0f - (1.0f / ((fConst0 * (fSlow17 * std::exp(((4.60517025f * (float(fEntry11) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow19 = (1.0f / ((fConst0 * fSlow17) + 1.0f));
		float fSlow20 = (100.0f * (1.0f - (float(fEntry12) + 1.0f)));
		float fSlow21 = std::tan((fConst120 * std::exp(((3.45387769f * (float(fEntry13) + 1.0f)) + -2.30258512f))));
		float fSlow22 = (1.0f / fSlow21);
		float fSlow23 = (fSlow22 + 1.0f);
		float fSlow24 = (0.0f - (1.0f / (fSlow23 * fSlow21)));
		float fSlow25 = (float(fEntry14) + 1.0f);
		float fSlow26 = (50.0f * (fSlow3 * std::exp(((3.80045128f * fSlow25) + -2.30258512f))));
		float fSlow27 = float(fEntry15);
		float fSlow28 = ((fSlow27 > 0.0f)?((13.0f * fSlow27) + -3.0f):((5.0f * fSlow27) + -3.0f));
		float fSlow29 = float(fEntry16);
		int iSlow30 = (fSlow29 > 0.0f);
		float fSlow31 = (iSlow30?((5.0f * fSlow29) + 13.0f):((18.0f * fSlow29) + 13.0f));
		float fSlow32 = float(fEntry17);
		float fSlow33 = ((fSlow32 > 0.0f)?((10.0f * fSlow32) + 13.0f):((18.0f * fSlow32) + 13.0f));
		float fSlow34 = std::pow(10.0f, (0.0f - (0.0500000007f * (((0.600000024f * fSlow28) + (0.400000006f * fSlow31)) + (0.200000003f * fSlow33)))));
		float fSlow35 = std::tan((fConst120 * float((iSlow30?100:50))));
		float fSlow36 = (1.0f / fSlow35);
		float fSlow37 = (fSlow36 + 1.0f);
		float fSlow38 = (0.0f - (1.0f / (fSlow35 * fSlow37)));
		float fSlow39 = (float(fEntry18) + 1.0f);
		float fSlow40 = (10.0f * fSlow39);
		float fSlow41 = (0.5f * (float(fEntry19) + 1.0f));
		float fSlow42 = std::pow(fSlow40, fSlow41);
		float fSlow43 = (1.0f / fSlow42);
		float fSlow44 = float(fEntry20);
		float fSlow45 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow44) + -2.0f));
		float fSlow46 = (1.0f - fSlow45);
		float fSlow47 = std::max<float>(0.0f, (std::min<float>(2.0f, fSlow44) + -1.0f));
		float fSlow48 = (1.0f - fSlow47);
		float fSlow49 = (fSlow41 + 1.0f);
		float fSlow50 = std::pow(fSlow40, fSlow49);
		float fSlow51 = (37.5f * (float(fEntry21) + 1.0f));
		float fSlow52 = (fSlow50 + fSlow51);
		float fSlow53 = std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f));
		float fSlow54 = std::exp(((4.60517025f * (float(fEntry23) + 1.0f)) + -9.2103405f));
		float fSlow55 = (1.0f / ((fConst0 * fSlow54) + 1.0f));
		float fSlow56 = (150.0f * (float(fEntry24) + 1.0f));
		float fSlow57 = std::exp(((4.60517025f * (float(fEntry25) + 1.0f)) + -9.2103405f));
		float fSlow58 = (1.0f / ((fConst0 * (fSlow57 * std::exp(((4.60517025f * (float(fEntry26) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow59 = (1.0f - fSlow58);
		float fSlow60 = (1.0f / ((fConst0 * fSlow57) + 1.0f));
		float fSlow61 = std::tan((fConst120 * std::exp(((3.45387769f * (float(fEntry27) + 1.0f)) + -2.30258512f))));
		float fSlow62 = (1.0f / fSlow61);
		float fSlow63 = (fSlow62 + 1.0f);
		float fSlow64 = (0.0f - (1.0f / (fSlow61 * fSlow63)));
		float fSlow65 = (float(fEntry28) + 1.0f);
		float fSlow66 = (std::exp(((3.45387769f * fSlow65) + -0.693147182f)) * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry29) + 1.0f)))))));
		float fSlow67 = (1.0f / fSlow63);
		float fSlow68 = (fSlow66 / fSlow61);
		float fSlow69 = (1.0f - fSlow62);
		float fSlow70 = std::exp(((4.60517025f * (float(fEntry30) + 1.0f)) + -18.420681f));
		float fSlow71 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((6.90775537f * (float(fEntry31) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = (1.0f / ((fConst0 * fSlow70) + 1.0f));
		float fSlow74 = std::exp(((3.45387769f * (float(fEntry32) + 1.0f)) + -13.8155107f));
		float fSlow75 = (1.0f / ((fConst0 * (fSlow74 * std::exp(((6.90775537f * (float(fEntry33) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow76 = (1.0f - fSlow75);
		float fSlow77 = (1.0f / ((fConst0 * fSlow74) + 1.0f));
		float fSlow78 = (5.0f * (1.0f - (float(fEntry34) + 1.0f)));
		float fSlow79 = (1.0f / ((fConst0 * (fSlow74 * std::exp(((5.75646257f * (float(fEntry35) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow80 = (1.0f - fSlow79);
		float fSlow81 = float(fEntry36);
		float fSlow82 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((5.75646257f * (float(fEntry37) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow83 = (fSlow82 + -1.0f);
		float fSlow84 = (1.0f / fSlow39);
		float fSlow85 = (fSlow42 * fSlow49);
		float fSlow86 = ((75.0f * (float(fEntry38) + 1.0f)) + fSlow50);
		float fSlow87 = std::exp(((4.60517025f * (float(fEntry39) + 1.0f)) + -2.30258512f));
		float fSlow88 = ((fSlow50 + fSlow56) + fSlow87);
		float fSlow89 = (1.0f / fSlow87);
		float fSlow90 = (1.0f / ((fConst0 * (fSlow54 * std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -2.99573231f)))) + 1.0f));
		float fSlow91 = (fSlow90 + -1.0f);
		float fSlow92 = std::exp(((3.45387769f * (float(fEntry41) + 1.0f)) + -2.30258512f));
		float fSlow93 = (fSlow56 + fSlow92);
		float fSlow94 = (1.0f / fSlow92);
		float fSlow95 = ((float(fEntry42) + 1.0f) + 1.0f);
		float fSlow96 = (2.0f * (fSlow47 / fSlow95));
		float fSlow97 = (0.5f * (fSlow95 / fSlow42));
		float fSlow98 = (fSlow61 * fSlow42);
		float fSlow99 = (0.5f * (fSlow95 / fSlow98));
		float fSlow100 = (fSlow79 + -1.0f);
		float fSlow101 = (1.0f - fSlow82);
		float fSlow102 = (fSlow58 + -1.0f);
		float fSlow103 = (1.0f - fSlow90);
		float fSlow104 = (1.0f / fSlow98);
		float fSlow105 = AmpMono_faustpower2_f((0.5f * fSlow95));
		float fSlow106 = (fSlow45 / fSlow105);
		float fSlow107 = (fSlow105 / fSlow42);
		float fSlow108 = (fSlow105 / fSlow98);
		float fSlow109 = (5.0f * fSlow65);
		int iSlow110 = (fSlow109 < 9.0f);
		int iSlow111 = (fSlow109 < 8.0f);
		int iSlow112 = (fSlow109 < 7.0f);
		int iSlow113 = (fSlow109 < 6.0f);
		int iSlow114 = (fSlow109 < 5.0f);
		int iSlow115 = (fSlow109 < 4.0f);
		int iSlow116 = (fSlow109 < 3.0f);
		int iSlow117 = (fSlow109 < 2.0f);
		int iSlow118 = (fSlow109 < 1.0f);
		float fSlow119 = std::pow(10.0f, (0.0500000007f * (iSlow110?(iSlow111?(iSlow112?(iSlow113?(iSlow114?(iSlow115?(iSlow116?(iSlow117?(iSlow118?((fSlow109 < 0.0f)?4.8499999f:(iSlow118?(4.8499999f - (30.1000004f * fSlow65)):-1.16999996f)):(iSlow117?(-1.16999996f - (5.94999981f * (fSlow109 + -1.0f))):-7.11999989f)):(iSlow116?(-7.11999989f - (5.57999992f * (fSlow109 + -2.0f))):-12.6999998f)):(iSlow115?(-12.6999998f - (4.80000019f * (fSlow109 + -3.0f))):-17.5f)):(iSlow114?(-17.5f - (2.70000005f * (fSlow109 + -4.0f))):-20.2000008f)):(iSlow113?(-20.2000008f - (1.29999995f * (0.0f - (5.0f * (1.0f - fSlow65))))):-21.5f)):(iSlow112?(-21.5f - (0.600000024f * (fSlow109 + -6.0f))):-22.1000004f)):(iSlow111?(-22.1000004f - (0.5f * (fSlow109 + -7.0f))):-22.6000004f)):(iSlow110?(-22.6000004f - (0.300000012f * (fSlow109 + -8.0f))):-22.8999996f)):((fSlow109 < 10.0f)?(-22.8999996f - (0.200000003f * (fSlow109 + -9.0f))):-23.1000004f))));
		float fSlow120 = (1.0f - fSlow36);
		float fSlow121 = std::pow(10.0f, (0.0500000007f * fSlow31));
		float fSlow122 = ((fSlow29 < -0.800000012f)?(0.0f - (5.0f * (fSlow29 + 0.800000012f))):0.0f);
		float fSlow123 = (1.0f - fSlow122);
		int iSlow124 = (fSlow28 > 0.0f);
		float fSlow125 = (fConst133 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow28))));
		float fSlow126 = (iSlow124?fConst133:fSlow125);
		float fSlow127 = ((fConst132 * (fConst132 - fSlow126)) + 1.0f);
		float fSlow128 = ((fConst132 * (fConst132 + fSlow126)) + 1.0f);
		float fSlow129 = (iSlow124?fSlow125:fConst133);
		float fSlow130 = ((fConst132 * (fConst132 + fSlow129)) + 1.0f);
		float fSlow131 = ((fConst132 * (fConst132 - fSlow129)) + 1.0f);
		float fSlow132 = ((fSlow27 < -0.800000012f)?(0.0f - (5.0f * (fSlow27 + 0.800000012f))):0.0f);
		float fSlow133 = (1.0f - fSlow132);
		float fSlow134 = std::pow(10.0f, (0.0500000007f * fSlow33));
		float fSlow135 = ((fSlow32 < -0.800000012f)?(0.0f - (5.0f * (fSlow32 + 0.800000012f))):0.0f);
		float fSlow136 = (1.0f - fSlow135);
		float fSlow137 = (250.0f * (float(fEntry43) + 1.0f));
		float fSlow138 = (1.0f / fSlow23);
		float fSlow139 = (1.0f - fSlow22);
		float fSlow140 = std::exp((0.0f - (fConst139 / std::exp(((4.60517025f * (float(fEntry44) + 1.0f)) + -9.2103405f)))));
		float fSlow141 = (1.0f - fSlow140);
		float fSlow142 = (10.0f / fSlow11);
		float fSlow143 = (fSlow13 * std::pow(fSlow11, fSlow12));
		float fSlow144 = std::pow(((2.0f * (float(fEntry45) + 1.0f)) + 40.0f), fSlow13);
		float fSlow145 = std::exp(((4.60517025f * (float(fEntry46) + 1.0f)) + -9.2103405f));
		float fSlow146 = (1.0f / ((fConst0 * fSlow145) + 1.0f));
		float fSlow147 = (50.0f * (float(fEntry47) + 1.0f));
		float fSlow148 = (1.0f - (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry48) + 1.0f)) + -4.60517025f)) * fSlow145)) + 1.0f)));
		float fSlow149 = (float(fEntry49) + 1.0f);
		float fSlow150 = (1.0f - fSlow149);
		float fSlow151 = (fSlow8 + (10.0f * fSlow150));
		float fSlow152 = (0.100000001f / fSlow149);
		float fSlow153 = (1.0f / ((fConst0 * (fSlow5 * std::exp(((4.60517025f * (float(fEntry50) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow154 = (fSlow153 + -1.0f);
		float fSlow155 = (1.0f - fSlow153);
		float fSlow156 = (5.0f * fSlow25);
		int iSlow157 = (fSlow156 < 9.0f);
		int iSlow158 = (fSlow156 < 7.0f);
		int iSlow159 = (fSlow156 < 6.0f);
		int iSlow160 = (fSlow156 < 5.0f);
		int iSlow161 = (fSlow156 < 4.0f);
		int iSlow162 = (fSlow156 < 3.0f);
		int iSlow163 = (fSlow156 < 2.0f);
		int iSlow164 = (fSlow156 < 1.0f);
		float fSlow165 = std::pow(10.0f, (0.0500000007f * (iSlow157?((fSlow156 < 8.0f)?(iSlow158?(iSlow159?(iSlow160?(iSlow161?(iSlow162?(iSlow163?(iSlow164?((fSlow156 < 0.0f)?19.0f:(iSlow164?(19.0f - (33.0f * fSlow25)):12.3999996f)):(iSlow163?(12.3999996f - (6.55000019f * (fSlow156 + -1.0f))):5.8499999f)):(iSlow162?(5.8499999f - (6.0079999f * (fSlow156 + -2.0f))):-0.158000007f)):(iSlow161?(-0.158000007f - (5.25199986f * (fSlow156 + -3.0f))):-5.40999985f)):(iSlow160?(-5.40999985f - (3.57999992f * (fSlow156 + -4.0f))):-8.98999977f)):(iSlow159?(-8.98999977f - (1.40999997f * (0.0f - (5.0f * (1.0f - fSlow25))))):-10.3999996f)):(iSlow158?(-10.3999996f - (0.200000003f * (fSlow156 + -6.0f))):-10.6000004f)):-10.6000004f):(iSlow157?((0.100000001f * (fSlow156 + -8.0f)) + -10.6000004f):-10.5f)):((fSlow156 < 10.0f)?((0.100000001f * (fSlow156 + -9.0f)) + -10.5f):-10.3999996f))));
		float fSlow166 = (0.0199999996f / fSlow3);
		float fSlow167 = (0.0199999996f * ((1.0f - fSlow1) / fSlow3));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow66 * fTemp0);
			fRec34[0] = ((fSlow64 * fVec0[1]) + (fSlow67 * ((fSlow68 * fTemp0) - (fSlow69 * fRec34[1]))));
			fRec38[0] = ((fSlow77 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec34[0])) - fRec38[1]))) + (fSlow80 * fRec38[1]));
			fRec37[0] = ((fSlow76 * fRec37[1]) + (fSlow75 * fRec38[0]));
			fRec36[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec34[0] + (-2.0f - fRec37[0])) - fSlow81)) - fRec36[1]))) - (fSlow83 * fRec36[1]));
			fRec35[0] = ((fSlow72 * fRec35[1]) + (fSlow71 * fRec36[0]));
			float fTemp1 = (fRec34[0] - (fRec35[0] + fRec37[0]));
			float fTemp2 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp1)) + -0.0500000007f)));
			float fTemp3 = (((std::pow(std::max<float>(0.0f, (fSlow40 + fTemp1)), fSlow49) - fSlow50) * fTemp2) + (fSlow85 * (fTemp1 * (1.0f - fTemp2))));
			fRec33[0] = ((fSlow59 * fRec33[1]) + (fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp3 + 100.0f) - fSlow86)) - fRec33[1]))));
			float fTemp4 = ((fRec33[0] + (300.0f - fTemp3)) - fSlow88);
			float fTemp5 = (std::max<float>(0.0f, fTemp4) + (fSlow87 * (float(tanhf(float((fSlow89 * std::min<float>(0.0f, fTemp4))))) + 1.0f)));
			fRec32[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + ((fTemp5 + -250.0f) - fSlow51))) - fRec32[1]))) - (fSlow91 * fRec32[1]));
			float fTemp6 = (fSlow53 * fRec32[0]);
			float fTemp7 = (fSlow93 + ((fTemp5 + (-250.0f - fTemp6)) - fSlow51));
			float fTemp8 = (fSlow52 + (((fTemp6 + std::min<float>(0.0f, fTemp7)) + (fSlow92 * (float(tanhf(float((fSlow94 * std::max<float>(0.0f, fTemp7))))) + -1.0f))) + -50.0f));
			fVec1[0] = (fSlow97 * fTemp8);
			fRec42[0] = ((fSlow64 * fVec1[1]) + (fSlow67 * ((fSlow99 * fTemp8) - (fSlow69 * fRec42[1]))));
			fRec44[0] = ((fSlow77 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec42[0])) - fRec44[1]))) - (fSlow100 * fRec44[1]));
			fRec43[0] = ((fSlow76 * fRec43[1]) + (fSlow75 * fRec44[0]));
			fRec46[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec42[0] + (-2.0f - fRec43[0])) - fSlow81)) - fRec46[1]))) + (fSlow101 * fRec46[1]));
			fRec45[0] = ((fSlow71 * fRec46[0]) + (fSlow72 * fRec45[1]));
			float fTemp9 = (fRec42[0] - (fRec43[0] + fRec45[0]));
			float fTemp10 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp9)) + -0.0500000007f)));
			float fTemp11 = ((fSlow85 * (fTemp9 * (1.0f - fTemp10))) + ((std::pow(std::max<float>(0.0f, (fSlow40 + fTemp9)), fSlow49) - fSlow50) * fTemp10));
			fRec41[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp11 + 100.0f) - fSlow86)) - fRec41[1]))) - (fSlow102 * fRec41[1]));
			float fTemp12 = ((fRec41[0] + (300.0f - fTemp11)) - fSlow88);
			float fTemp13 = (std::max<float>(0.0f, fTemp12) + (fSlow87 * (float(tanhf(float((fSlow89 * std::min<float>(0.0f, fTemp12))))) + 1.0f)));
			fRec47[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + ((fTemp13 + -250.0f) - fSlow51))) - fRec47[1]))) + (fSlow103 * fRec47[1]));
			float fTemp14 = (fSlow53 * fRec47[0]);
			float fTemp15 = (fSlow93 + ((fTemp13 + (-250.0f - fTemp14)) - fSlow51));
			float fTemp16 = (fSlow52 + ((std::min<float>(0.0f, fTemp15) + fTemp14) + (-50.0f - (fSlow92 * (1.0f - float(tanhf(float((fSlow94 * std::max<float>(0.0f, fTemp15))))))))));
			fVec2[0] = (fSlow43 * fTemp16);
			fRec40[0] = ((fSlow64 * fVec2[1]) - (fSlow67 * ((fSlow69 * fRec40[1]) - (fSlow104 * fTemp16))));
			fRec51[0] = ((fSlow80 * fRec51[1]) + (fSlow77 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec40[0])) - fRec51[1]))));
			fRec50[0] = ((fSlow75 * fRec51[0]) + (fSlow76 * fRec50[1]));
			fRec49[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec40[0] + (-2.0f - fRec50[0])) - fSlow81)) - fRec49[1]))) - (fSlow83 * fRec49[1]));
			fRec48[0] = ((fSlow71 * fRec49[0]) + (fSlow72 * fRec48[1]));
			float fTemp17 = (fRec40[0] - (fRec48[0] + fRec50[0]));
			float fTemp18 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp17)) + -0.0500000007f)));
			float fTemp19 = ((fSlow85 * (fTemp17 * (1.0f - fTemp18))) + (fTemp18 * (std::pow(std::max<float>(0.0f, (fSlow40 + fTemp17)), fSlow49) - fSlow50)));
			fRec39[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp19 + 100.0f) - fSlow86)) - fRec39[1]))) - (fSlow102 * fRec39[1]));
			float fTemp20 = ((fRec39[0] + (300.0f - fTemp19)) - fSlow88);
			float fTemp21 = ((fSlow87 * (float(tanhf(float((fSlow89 * std::min<float>(0.0f, fTemp20))))) + 1.0f)) + std::max<float>(0.0f, fTemp20));
			fRec52[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + ((fTemp21 + -250.0f) - fSlow51))) - fRec52[1]))) + (fSlow103 * fRec52[1]));
			float fTemp22 = (fSlow53 * fRec52[0]);
			float fTemp23 = (fSlow93 + ((fTemp21 + (-250.0f - fTemp22)) - fSlow51));
			float fTemp24 = ((fSlow48 * fTemp8) + (fSlow96 * (fSlow52 + ((std::min<float>(0.0f, fTemp23) + fTemp22) + (-50.0f - (fSlow92 * (1.0f - float(tanhf(float((fSlow94 * std::max<float>(0.0f, fTemp23))))))))))));
			fVec3[0] = (fSlow107 * fTemp24);
			fRec56[0] = ((fSlow64 * fVec3[1]) - (fSlow67 * ((fSlow69 * fRec56[1]) - (fSlow108 * fTemp24))));
			fRec58[0] = ((fSlow80 * fRec58[1]) + (fSlow77 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec56[0])) - fRec58[1]))));
			fRec57[0] = ((fSlow76 * fRec57[1]) + (fSlow75 * fRec58[0]));
			fRec60[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec56[0] + (-2.0f - fRec57[0])) - fSlow81)) - fRec60[1]))) - (fSlow83 * fRec60[1]));
			fRec59[0] = ((fSlow72 * fRec59[1]) + (fSlow71 * fRec60[0]));
			float fTemp25 = (fRec56[0] - (fRec57[0] + fRec59[0]));
			float fTemp26 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp25)) + -0.0500000007f)));
			float fTemp27 = (((std::pow(std::max<float>(0.0f, (fSlow40 + fTemp25)), fSlow49) - fSlow50) * fTemp26) + (fSlow85 * ((1.0f - fTemp26) * fTemp25)));
			fRec55[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp27 + 100.0f) - fSlow86)) - fRec55[1]))) + (fSlow59 * fRec55[1]));
			float fTemp28 = ((fRec55[0] + (300.0f - fTemp27)) - fSlow88);
			float fTemp29 = (std::max<float>(0.0f, fTemp28) + (fSlow87 * (float(tanhf(float((fSlow89 * std::min<float>(0.0f, fTemp28))))) + 1.0f)));
			fRec61[0] = ((fSlow103 * fRec61[1]) + (fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + ((fTemp29 + -250.0f) - fSlow51))) - fRec61[1]))));
			float fTemp30 = (fSlow53 * fRec61[0]);
			float fTemp31 = (fSlow93 + ((fTemp29 + (-250.0f - fTemp30)) - fSlow51));
			float fTemp32 = (fSlow52 + ((std::min<float>(0.0f, fTemp31) + fTemp30) + (-50.0f - (fSlow92 * (1.0f - float(tanhf(float((fSlow94 * std::max<float>(0.0f, fTemp31))))))))));
			fVec4[0] = (fSlow43 * fTemp32);
			fRec54[0] = ((fSlow64 * fVec4[1]) - (fSlow67 * ((fSlow69 * fRec54[1]) - (fSlow104 * fTemp32))));
			fRec63[0] = ((fSlow80 * fRec63[1]) + (fSlow77 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow78 + fRec54[0])) - fRec63[1]))));
			fRec62[0] = ((fSlow76 * fRec62[1]) + (fSlow75 * fRec63[0]));
			fRec65[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec54[0] + (-2.0f - fRec62[0])) - fSlow81)) - fRec65[1]))) - (fSlow83 * fRec65[1]));
			fRec64[0] = ((fSlow71 * fRec65[0]) + (fSlow72 * fRec64[1]));
			float fTemp33 = (fRec54[0] - (fRec62[0] + fRec64[0]));
			float fTemp34 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp33)) + -0.0500000007f)));
			float fTemp35 = (((std::pow(std::max<float>(0.0f, (fSlow40 + fTemp33)), fSlow49) - fSlow50) * fTemp34) + (fSlow85 * (fTemp33 * (1.0f - fTemp34))));
			fRec53[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp35 + 100.0f) - fSlow86)) - fRec53[1]))) + (fSlow59 * fRec53[1]));
			float fTemp36 = ((fRec53[0] + (300.0f - fTemp35)) - fSlow88);
			float fTemp37 = ((fSlow87 * (float(tanhf(float((fSlow89 * std::min<float>(0.0f, fTemp36))))) + 1.0f)) + std::max<float>(0.0f, fTemp36));
			fRec66[0] = ((fSlow55 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow56 + ((fTemp37 + -250.0f) - fSlow51))) - fRec66[1]))) + (fSlow103 * fRec66[1]));
			float fTemp38 = (fSlow53 * fRec66[0]);
			float fTemp39 = (fSlow93 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow51));
			float fTemp40 = (((fSlow46 * fTemp24) + (fSlow106 * (fSlow52 + ((std::min<float>(0.0f, fTemp39) + fTemp38) + (-50.0f - (fSlow92 * (1.0f - float(tanhf(float((fSlow94 * std::max<float>(0.0f, fTemp39)))))))))))) * fSlow119);
			float fTemp41 = (fSlow43 * fTemp40);
			fVec5[0] = fTemp41;
			fRec31[0] = ((fSlow38 * fVec5[1]) - (((fRec31[1] * fSlow120) - (fSlow43 * (fTemp40 / fSlow35))) / fSlow37));
			fRec67[0] = (((fVec5[1] + fTemp41) - (fSlow120 * fRec67[1])) / fSlow37);
			float fTemp42 = (fRec31[0] + (fRec67[0] * fSlow121));
			fVec6[0] = fTemp42;
			fRec30[0] = ((fConst128 * fVec6[1]) - (fConst129 * ((fConst130 * fRec30[1]) - (fConst126 * fTemp42))));
			float fTemp43 = (fConst134 * fRec29[1]);
			fRec29[0] = (((fRec30[0] * fSlow122) + (fTemp42 * fSlow123)) - (((fRec29[2] * fSlow127) + fTemp43) / fSlow128));
			float fTemp44 = (((fRec29[0] * fSlow130) + fTemp43) + (fRec29[2] * fSlow131));
			float fTemp45 = (fConst144 * fRec68[1]);
			fRec68[0] = ((fTemp44 / fSlow128) - (fConst141 * ((fConst143 * fRec68[2]) + fTemp45)));
			float fTemp46 = (((fTemp44 * fSlow133) / fSlow128) + (fConst141 * (fSlow132 * (((fConst142 * fRec68[0]) + fTemp45) + (fConst142 * fRec68[2])))));
			fVec7[0] = fTemp46;
			fRec28[0] = (fConst124 * ((fTemp46 + fVec7[1]) - (fConst145 * fRec28[1])));
			fRec69[0] = ((fConst146 * fVec7[1]) - (fConst124 * ((fConst145 * fRec69[1]) - (fConst122 * fTemp46))));
			float fTemp47 = (fRec28[0] + (fRec69[0] * fSlow134));
			fVec8[0] = fTemp47;
			fRec70[0] = (fConst148 * ((fTemp47 + fVec8[1]) - (fConst149 * fRec70[1])));
			float fTemp48 = ((fSlow26 * (fSlow34 * ((fTemp47 * fSlow136) + (fRec70[0] * fSlow135)))) - fSlow137);
			fVec9[0] = fTemp48;
			fRec27[0] = ((fSlow24 * fVec9[1]) - (fSlow138 * ((fSlow139 * fRec27[1]) - (fSlow22 * fTemp48))));
			fRec71[0] = ((fSlow140 * fRec71[1]) + (fSlow141 * (fRec27[0] - fSlow15)));
			fRec26[0] = ((fSlow18 * fRec26[1]) + (fSlow19 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow20 + ((fRec27[0] - fRec71[0]) - fSlow15))) - fRec26[1]))));
			float fRec25 = fRec26[0];
			float fTemp49 = (fRec25 + fRec71[0]);
			float fTemp50 = (0.0f - ((fRec27[0] - fTemp49) - fSlow15));
			float fTemp51 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow142 * std::fabs(fTemp50)) + -0.0500000007f)));
			float fTemp52 = (fSlow9 * (fSlow14 + ((((std::pow(std::max<float>(0.0f, (fSlow16 + (fTemp49 + (30.0f - fRec27[0])))), fSlow13) - fSlow14) * fTemp51) + (fSlow143 * (fTemp50 * (1.0f - fTemp51)))) - fSlow144)));
			fRec73[0] = ((fSlow146 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp52 - fSlow147)) - fRec73[1]))) + (fSlow148 * fRec73[1]));
			float fRec72 = fRec73[0];
			float fTemp53 = ((fTemp52 - fRec72) - fSlow151);
			float fTemp54 = std::max<float>(0.0f, (fSlow8 + (std::min<float>(0.0f, fTemp53) + (10.0f * (fSlow150 + (fSlow149 * float(tanhf(float((fSlow152 * std::max<float>(0.0f, fTemp53)))))))))));
			fRec24[0] = ((fSlow6 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow7 + fTemp54)) - fRec24[1]))) - (fSlow154 * fRec24[1]));
			float fRec23 = fRec24[0];
			float fTemp55 = (0.0f - fTemp50);
			float fTemp56 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow142 * std::fabs(fTemp55)) + -0.0500000007f)));
			float fTemp57 = (fSlow9 * (fSlow14 + (((fTemp56 * (std::pow(std::max<float>(0.0f, (fSlow10 + ((fRec27[0] + (30.0f - fTemp49)) - fSlow15))), fSlow13) - fSlow14)) + (fSlow143 * (fTemp55 * (1.0f - fTemp56)))) - fSlow144)));
			fRec75[0] = ((fSlow146 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp57 - fSlow147)) - fRec75[1]))) + (fSlow148 * fRec75[1]));
			float fRec74 = fRec75[0];
			float fTemp58 = ((fTemp57 - fRec74) - fSlow151);
			float fTemp59 = std::max<float>(0.0f, (fSlow8 + (std::min<float>(0.0f, fTemp58) + (10.0f * (fSlow150 + (fSlow149 * float(tanhf(float((fSlow152 * std::max<float>(0.0f, fTemp58)))))))))));
			fRec77[0] = ((fSlow155 * fRec77[1]) + (fSlow6 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow7 + fTemp59)) - fRec77[1]))));
			float fRec76 = fRec77[0];
			float fTemp60 = (((fRec23 + fTemp59) - (fRec76 + fTemp54)) * fSlow165);
			fVec10[0] = (fSlow166 * fTemp60);
			fRec22[0] = ((fConst118 * ((fSlow4 * fTemp60) - (fConst150 * fRec22[1]))) + (fConst151 * fVec10[1]));
			fRec21[0] = (0.0f - (fConst113 * ((fConst114 * fRec21[1]) - (fRec22[0] + fRec22[1]))));
			fRec20[0] = (fConst111 * ((fRec21[0] + fRec21[1]) - (fConst152 * fRec20[1])));
			fRec19[0] = (fRec20[0] - (fConst109 * ((fConst155 * fRec19[1]) + (fConst156 * fRec19[2]))));
			fRec18[0] = ((fConst109 * (fRec19[2] + (fRec19[0] + (2.0f * fRec19[1])))) - (fConst108 * ((fConst155 * fRec18[1]) + (fConst157 * fRec18[2]))));
			fRec17[0] = ((fConst108 * (fRec18[2] + (fRec18[0] + (2.0f * fRec18[1])))) - (fConst107 * ((fConst155 * fRec17[1]) + (fConst158 * fRec17[2]))));
			fRec16[0] = ((fConst107 * ((fRec17[0] + (2.0f * fRec17[1])) + fRec17[2])) - (fConst106 * ((fConst159 * fRec16[2]) + (fConst155 * fRec16[1]))));
			fRec15[0] = ((fConst106 * (fRec16[2] + (fRec16[0] + (2.0f * fRec16[1])))) - (fConst105 * ((fConst160 * fRec15[2]) + (fConst155 * fRec15[1]))));
			fRec83[0] = ((fConst162 * fRec21[1]) - (fConst111 * ((fConst152 * fRec83[1]) - (fConst104 * fRec21[0]))));
			fRec82[0] = (fRec83[0] - (fConst109 * ((fConst155 * fRec82[1]) + (fConst156 * fRec82[2]))));
			fRec81[0] = ((fConst109 * (((fConst154 * fRec82[0]) + (fConst161 * fRec82[1])) + (fConst154 * fRec82[2]))) - (fConst108 * ((fConst157 * fRec81[2]) + (fConst155 * fRec81[1]))));
			fRec80[0] = ((fConst108 * ((fConst154 * fRec81[2]) + ((fConst161 * fRec81[1]) + (fConst154 * fRec81[0])))) - (fConst107 * ((fConst158 * fRec80[2]) + (fConst155 * fRec80[1]))));
			fRec79[0] = ((fConst107 * (((fConst161 * fRec80[1]) + (fConst154 * fRec80[0])) + (fConst154 * fRec80[2]))) - (fConst106 * ((fConst159 * fRec79[2]) + (fConst155 * fRec79[1]))));
			fRec78[0] = ((fConst106 * (((fConst161 * fRec79[1]) + (fConst154 * fRec79[0])) + (fConst154 * fRec79[2]))) - (fConst105 * ((fConst155 * fRec78[1]) + (fConst160 * fRec78[2]))));
			float fTemp61 = (fConst164 * fRec14[1]);
			fRec14[0] = ((fConst105 * ((fRec15[2] + (fRec15[0] + (2.0f * fRec15[1]))) + (0.13673377f * (((fConst154 * fRec78[0]) + (fConst161 * fRec78[1])) + (fConst154 * fRec78[2]))))) - (fConst100 * ((fConst163 * fRec14[2]) + fTemp61)));
			float fTemp62 = (fConst166 * fRec13[1]);
			fRec13[0] = ((fConst100 * (((fConst102 * fRec14[0]) + fTemp61) + (fConst165 * fRec14[2]))) - (fConst93 * (fTemp62 + (fConst167 * fRec13[2]))));
			float fTemp63 = (fConst88 * fRec12[1]);
			fRec12[0] = ((fConst93 * ((fConst95 * fRec13[2]) + (fTemp62 + (fConst168 * fRec13[0])))) - (fConst87 * (fTemp63 + (fConst169 * fRec12[2]))));
			float fTemp64 = (fConst173 * fRec11[1]);
			fRec11[0] = ((fConst87 * ((fTemp63 + (fConst171 * fRec12[0])) + (fConst172 * fRec12[2]))) - (fConst80 * (fTemp64 + (fConst174 * fRec11[2]))));
			float fTemp65 = (fConst177 * fRec10[1]);
			fRec10[0] = ((fConst80 * (((fConst82 * fRec11[0]) + fTemp64) + (fConst175 * fRec11[2]))) - (fConst73 * ((fConst176 * fRec10[2]) + fTemp65)));
			float fTemp66 = (fConst179 * fRec9[1]);
			fRec9[0] = ((fConst73 * ((fConst75 * fRec10[2]) + (fTemp65 + (fConst178 * fRec10[0])))) - (fConst66 * (fTemp66 + (fConst180 * fRec9[2]))));
			float fTemp67 = (fConst182 * fRec8[1]);
			fRec8[0] = ((fConst66 * (((fConst68 * fRec9[0]) + fTemp66) + (fConst181 * fRec9[2]))) - (fConst59 * (fTemp67 + (fConst183 * fRec8[2]))));
			float fTemp68 = (fConst186 * fRec7[1]);
			fRec7[0] = ((fConst59 * (((fConst61 * fRec8[0]) + fTemp67) + (fConst184 * fRec8[2]))) - (fConst52 * ((fConst185 * fRec7[2]) + fTemp68)));
			float fTemp69 = (fConst189 * fRec6[1]);
			fRec6[0] = ((fConst52 * ((fConst54 * fRec7[2]) + (fTemp68 + (fConst187 * fRec7[0])))) - (fConst45 * ((fConst188 * fRec6[2]) + fTemp69)));
			float fTemp70 = (fConst191 * fRec5[1]);
			fRec5[0] = ((fConst45 * (((fConst47 * fRec6[0]) + fTemp69) + (fConst190 * fRec6[2]))) - (fConst38 * (fTemp70 + (fConst192 * fRec5[2]))));
			float fTemp71 = (fConst33 * fRec4[1]);
			fRec4[0] = ((fConst38 * (((fConst40 * fRec5[0]) + fTemp70) + (fConst193 * fRec5[2]))) - (fConst32 * (fTemp71 + (fConst194 * fRec4[2]))));
			float fTemp72 = (fConst27 * fRec3[1]);
			fRec3[0] = ((fConst32 * ((fTemp71 + (fConst196 * fRec4[0])) + (fConst197 * fRec4[2]))) - (fConst26 * (fTemp72 + (fConst198 * fRec3[2]))));
			float fTemp73 = (fConst203 * fRec2[1]);
			fRec2[0] = ((fConst26 * ((fTemp72 + (fConst200 * fRec3[0])) + (fConst201 * fRec3[2]))) - (fConst19 * ((fConst202 * fRec2[2]) + fTemp73)));
			float fTemp74 = (fConst14 * fRec1[1]);
			fRec1[0] = ((fConst19 * ((fConst21 * fRec2[2]) + ((fConst204 * fRec2[0]) + fTemp73))) - (fConst13 * ((fConst205 * fRec1[2]) + fTemp74)));
			float fTemp75 = (fConst211 * fRec0[1]);
			fRec0[0] = ((fConst13 * ((fTemp74 + (fConst207 * fRec1[0])) + (fConst208 * fRec1[2]))) - (fConst209 * ((fConst210 * fRec0[2]) + fTemp75)));
			output0[i] = FAUSTFLOAT((fSlow0 * ((fSlow2 * ((fConst8 * fRec0[2]) + (fTemp75 + (fConst212 * fRec0[0])))) + (fSlow167 * fTemp60))));
			fVec0[1] = fVec0[0];
			fRec34[1] = fRec34[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec36[1] = fRec36[0];
			fRec35[1] = fRec35[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fVec1[1] = fVec1[0];
			fRec42[1] = fRec42[0];
			fRec44[1] = fRec44[0];
			fRec43[1] = fRec43[0];
			fRec46[1] = fRec46[0];
			fRec45[1] = fRec45[0];
			fRec41[1] = fRec41[0];
			fRec47[1] = fRec47[0];
			fVec2[1] = fVec2[0];
			fRec40[1] = fRec40[0];
			fRec51[1] = fRec51[0];
			fRec50[1] = fRec50[0];
			fRec49[1] = fRec49[0];
			fRec48[1] = fRec48[0];
			fRec39[1] = fRec39[0];
			fRec52[1] = fRec52[0];
			fVec3[1] = fVec3[0];
			fRec56[1] = fRec56[0];
			fRec58[1] = fRec58[0];
			fRec57[1] = fRec57[0];
			fRec60[1] = fRec60[0];
			fRec59[1] = fRec59[0];
			fRec55[1] = fRec55[0];
			fRec61[1] = fRec61[0];
			fVec4[1] = fVec4[0];
			fRec54[1] = fRec54[0];
			fRec63[1] = fRec63[0];
			fRec62[1] = fRec62[0];
			fRec65[1] = fRec65[0];
			fRec64[1] = fRec64[0];
			fRec53[1] = fRec53[0];
			fRec66[1] = fRec66[0];
			fVec5[1] = fVec5[0];
			fRec31[1] = fRec31[0];
			fRec67[1] = fRec67[0];
			fVec6[1] = fVec6[0];
			fRec30[1] = fRec30[0];
			fRec29[2] = fRec29[1];
			fRec29[1] = fRec29[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fVec7[1] = fVec7[0];
			fRec28[1] = fRec28[0];
			fRec69[1] = fRec69[0];
			fVec8[1] = fVec8[0];
			fRec70[1] = fRec70[0];
			fVec9[1] = fVec9[0];
			fRec27[1] = fRec27[0];
			fRec71[1] = fRec71[0];
			fRec26[1] = fRec26[0];
			fRec73[1] = fRec73[0];
			fRec24[1] = fRec24[0];
			fRec75[1] = fRec75[0];
			fRec77[1] = fRec77[0];
			fVec10[1] = fVec10[0];
			fRec22[1] = fRec22[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec19[2] = fRec19[1];
			fRec19[1] = fRec19[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec17[2] = fRec17[1];
			fRec17[1] = fRec17[0];
			fRec16[2] = fRec16[1];
			fRec16[1] = fRec16[0];
			fRec15[2] = fRec15[1];
			fRec15[1] = fRec15[0];
			fRec83[1] = fRec83[0];
			fRec82[2] = fRec82[1];
			fRec82[1] = fRec82[0];
			fRec81[2] = fRec81[1];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec14[2] = fRec14[1];
			fRec14[1] = fRec14[0];
			fRec13[2] = fRec13[1];
			fRec13[1] = fRec13[0];
			fRec12[2] = fRec12[1];
			fRec12[1] = fRec12[0];
			fRec11[2] = fRec11[1];
			fRec11[1] = fRec11[0];
			fRec10[2] = fRec10[1];
			fRec10[1] = fRec10[0];
			fRec9[2] = fRec9[1];
			fRec9[1] = fRec9[0];
			fRec8[2] = fRec8[1];
			fRec8[1] = fRec8[0];
			fRec7[2] = fRec7[1];
			fRec7[1] = fRec7[0];
			fRec6[2] = fRec6[1];
			fRec6[1] = fRec6[0];
			fRec5[2] = fRec5[1];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec2[2] = fRec2[1];
			fRec2[1] = fRec2[0];
			fRec1[2] = fRec1[1];
			fRec1[1] = fRec1[0];
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];

		}

	}


};

#endif
