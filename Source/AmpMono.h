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
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	FAUSTFLOAT fEntry8;
	FAUSTFLOAT fEntry9;
	float fConst1;
	FAUSTFLOAT fEntry10;
	FAUSTFLOAT fEntry11;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	FAUSTFLOAT fEntry12;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
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
	float fVec0[2];
	float fRec8[2];
	FAUSTFLOAT fEntry23;
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	float fRec10[2];
	float fRec9[2];
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	float fRec12[2];
	float fRec11[2];
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	float fRec7[2];
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec13[2];
	FAUSTFLOAT fEntry37;
	float fVec1[2];
	float fRec19[2];
	float fRec21[2];
	float fRec20[2];
	float fRec23[2];
	float fRec22[2];
	float fRec18[2];
	float fRec17[2];
	float fVec2[2];
	float fRec16[2];
	float fRec25[2];
	float fRec24[2];
	float fRec27[2];
	float fRec26[2];
	float fRec15[2];
	float fRec14[2];
	float fVec3[2];
	float fRec31[2];
	float fRec35[2];
	float fRec34[2];
	float fRec33[2];
	float fRec32[2];
	float fRec30[2];
	float fRec36[2];
	float fVec4[2];
	float fRec29[2];
	float fRec38[2];
	float fRec37[2];
	float fRec40[2];
	float fRec39[2];
	float fRec28[2];
	float fRec41[2];
	float fVec5[2];
	FAUSTFLOAT fEntry38;
	float fRec6[2];
	float fRec42[2];
	float fVec6[2];
	float fConst10;
	float fConst11;
	float fRec5[2];
	float fConst12;
	float fConst13;
	float fConst14;
	float fConst15;
	float fRec4[3];
	float fConst16;
	float fConst17;
	float fConst18;
	float fConst19;
	float fConst20;
	float fConst21;
	float fConst22;
	float fConst23;
	float fConst24;
	float fRec43[3];
	float fConst25;
	float fVec7[2];
	float fConst26;
	float fRec3[2];
	float fConst27;
	float fRec44[2];
	FAUSTFLOAT fEntry39;
	float fVec8[2];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec45[2];
	FAUSTFLOAT fEntry40;
	float fVec9[2];
	float fRec2[2];
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	float fRec46[2];
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	FAUSTFLOAT fEntry45;
	float fRec48[2];
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	FAUSTFLOAT fEntry49;
	float fRec50[2];
	FAUSTFLOAT fEntry50;
	float fRec1[2];
	float fRec52[2];
	float fRec54[2];
	float fVec10[2];
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
	float fRec77[2];
	float fRec76[2];
	float fConst152;
	float fConst153;
	float fRec75[2];
	float fConst154;
	float fConst155;
	float fRec74[3];
	float fConst156;
	float fConst157;
	float fRec73[3];
	float fConst158;
	float fRec72[3];
	float fConst159;
	float fRec71[3];
	float fConst160;
	float fRec70[3];
	float fRec83[2];
	float fRec82[3];
	float fRec81[3];
	float fRec80[3];
	float fRec79[3];
	float fRec78[3];
	float fConst161;
	float fConst162;
	float fRec69[3];
	float fConst163;
	float fConst164;
	float fRec68[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fConst169;
	float fRec67[3];
	float fConst170;
	float fConst171;
	float fRec66[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fRec65[3];
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec64[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fConst184;
	float fRec63[3];
	float fConst185;
	float fConst186;
	float fConst187;
	float fRec62[3];
	float fConst188;
	float fConst189;
	float fRec61[3];
	float fConst190;
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec60[3];
	float fConst195;
	float fConst196;
	float fConst197;
	float fRec59[3];
	float fConst198;
	float fConst199;
	float fConst200;
	float fRec58[3];
	float fConst201;
	float fConst202;
	float fConst203;
	float fRec57[3];
	float fConst204;
	float fConst205;
	float fConst206;
	float fRec56[3];
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec55[3];
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
		fConst2 = std::tan((6283.18555f / fConst0));
		fConst3 = (1.0f / fConst2);
		fConst4 = (fConst3 + 1.0f);
		fConst5 = (1.0f / fConst4);
		fConst6 = std::tan((78.5398178f / fConst0));
		fConst7 = (1.0f / fConst6);
		fConst8 = (fConst7 + 1.0f);
		fConst9 = (0.0f - (1.0f / (fConst6 * fConst8)));
		fConst10 = (1.0f / fConst8);
		fConst11 = (1.0f - fConst7);
		fConst12 = std::tan((1382.30078f / fConst0));
		fConst13 = (1.0f / fConst12);
		fConst14 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst15 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst12))));
		fConst16 = (1.0f / fConst0);
		fConst17 = std::tan((1696.46008f / fConst0));
		fConst18 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * std::tan((1068.14148f / fConst0))) * fConst17))));
		fConst19 = (AmpMono_faustpower2_f(fConst16) * fConst18);
		fConst20 = (fConst0 * fConst17);
		fConst21 = (2.0f * (((2.0f * fConst20) - (0.5f * (fConst18 / fConst20))) / fConst0));
		fConst22 = (1.0f / ((fConst19 + fConst21) + 4.0f));
		fConst23 = ((2.0f * fConst19) + -8.0f);
		fConst24 = (fConst19 + (4.0f - fConst21));
		fConst25 = (fConst19 + 4.0f);
		fConst26 = (1.0f - fConst3);
		fConst27 = (0.0f - (1.0f / (fConst2 * fConst4)));
		fConst28 = (1.0f / std::tan((50265.4844f / fConst0)));
		fConst29 = (1.0f / (fConst28 + 1.0f));
		fConst30 = (1.0f - fConst28);
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
		fConst78 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst79 = std::tan((15066.6357f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst82 = (11187.3662f / fConst81);
		fConst83 = (1.0f / (((fConst80 + fConst82) / fConst79) + 1.0f));
		fConst84 = (36783.4805f / fConst81);
		fConst85 = (((fConst80 - fConst84) / fConst79) + 1.0f);
		fConst86 = std::tan((13437.668f / fConst0));
		fConst87 = (1.0f / fConst86);
		fConst88 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst89 = (13245.1885f / fConst88);
		fConst90 = (1.0f / (((fConst87 + fConst89) / fConst86) + 1.0f));
		fConst91 = (4583.19189f / fConst88);
		fConst92 = (((fConst87 - fConst91) / fConst86) + 1.0f);
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
		fConst123 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst118))));
		fConst124 = std::tan((375.293884f / fConst0));
		fConst125 = (1.0f / fConst124);
		fConst126 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst127 = (463.734222f / fConst126);
		fConst128 = (1.0f / (((fConst125 + fConst127) / fConst124) + 1.0f));
		fConst129 = (3220.11475f / fConst126);
		fConst130 = (((fConst125 - fConst129) / fConst124) + 1.0f);
		fConst131 = std::tan((18369.8027f / fConst0));
		fConst132 = (1.0f / fConst131);
		fConst133 = (1.0f / (((fConst132 + 0.284629673f) / fConst131) + 1.0f));
		fConst134 = AmpMono_faustpower2_f(fConst131);
		fConst135 = (1.0f / fConst134);
		fConst136 = (1.0f / (((fConst132 + 0.830830038f) / fConst131) + 1.0f));
		fConst137 = (1.0f / (((fConst132 + 1.30972147f) / fConst131) + 1.0f));
		fConst138 = (1.0f / (((fConst132 + 1.68250704f) / fConst131) + 1.0f));
		fConst139 = (1.0f / (((fConst132 + 1.91898596f) / fConst131) + 1.0f));
		fConst140 = (fConst132 + 1.0f);
		fConst141 = (0.0f - (1.0f / (fConst131 * fConst140)));
		fConst142 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst143 = (1.0f / (fConst142 + 1.0f));
		fConst144 = (1.0f - fConst142);
		fConst145 = std::tan((452.102844f / fConst0));
		fConst146 = (1.0f / fConst145);
		fConst147 = (fConst146 + 1.0f);
		fConst148 = (0.0f - (1.0f / (fConst145 * fConst147)));
		fConst149 = (1.0f / fConst147);
		fConst150 = (0.0199999996f / fConst145);
		fConst151 = (1.0f - fConst146);
		fConst152 = (1.0f / fConst140);
		fConst153 = (1.0f - fConst132);
		fConst154 = (((fConst132 + -1.91898596f) / fConst131) + 1.0f);
		fConst155 = (2.0f * (1.0f - fConst135));
		fConst156 = (0.0f - (2.0f / fConst134));
		fConst157 = (((fConst132 + -1.68250704f) / fConst131) + 1.0f);
		fConst158 = (((fConst132 + -1.30972147f) / fConst131) + 1.0f);
		fConst159 = (((fConst132 + -0.830830038f) / fConst131) + 1.0f);
		fConst160 = (((fConst132 + -0.284629673f) / fConst131) + 1.0f);
		fConst161 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst124))));
		fConst162 = (((fConst125 - fConst127) / fConst124) + 1.0f);
		fConst163 = (((fConst125 + fConst129) / fConst124) + 1.0f);
		fConst164 = (((fConst119 - fConst121) / fConst118) + 1.0f);
		fConst165 = (106249.391f / fConst120);
		fConst166 = (((fConst119 + fConst165) / fConst118) + 1.0f);
		fConst167 = (((fConst119 - fConst165) / fConst118) + 1.0f);
		fConst168 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst111))));
		fConst169 = (((fConst112 - fConst114) / fConst111) + 1.0f);
		fConst170 = (((fConst112 + fConst116) / fConst111) + 1.0f);
		fConst171 = (((fConst106 - fConst108) / fConst105) + 1.0f);
		fConst172 = (3097.15845f / fConst107);
		fConst173 = (((fConst106 + fConst172) / fConst105) + 1.0f);
		fConst174 = (((fConst106 - fConst172) / fConst105) + 1.0f);
		fConst175 = (((fConst100 - fConst102) / fConst99) + 1.0f);
		fConst176 = (518.801147f / fConst101);
		fConst177 = (((fConst100 + fConst176) / fConst99) + 1.0f);
		fConst178 = (((fConst100 - fConst176) / fConst99) + 1.0f);
		fConst179 = (((fConst94 - fConst96) / fConst93) + 1.0f);
		fConst180 = (9024.73242f / fConst95);
		fConst181 = (((fConst94 + fConst180) / fConst93) + 1.0f);
		fConst182 = (((fConst94 - fConst180) / fConst93) + 1.0f);
		fConst183 = (((fConst87 - fConst89) / fConst86) + 1.0f);
		fConst184 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst86))));
		fConst185 = (((fConst87 + fConst91) / fConst86) + 1.0f);
		fConst186 = (((fConst80 - fConst82) / fConst79) + 1.0f);
		fConst187 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst79))));
		fConst188 = (((fConst80 + fConst84) / fConst79) + 1.0f);
		fConst189 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst190 = (1059.12756f / fConst75);
		fConst191 = (((fConst74 + fConst190) / fConst73) + 1.0f);
		fConst192 = (((fConst74 - fConst190) / fConst73) + 1.0f);
		fConst193 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst194 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst195 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst196 = (((fConst60 - fConst62) / fConst59) + 1.0f);
		fConst197 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst59))));
		fConst198 = (((fConst60 - fConst64) / fConst59) + 1.0f);
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
			fRec8[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec10[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec9[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec12[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec11[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec7[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec13[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec19[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec21[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec20[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec23[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec22[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec18[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec17[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec2[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec16[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec25[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec24[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec27[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec26[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec15[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec14[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec3[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec31[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec35[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec34[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec33[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec32[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
			fRec30[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fRec36[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fVec4[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec29[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fRec38[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec37[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fRec40[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec39[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec28[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec41[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec5[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec6[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec42[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec6[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec5[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec4[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec43[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec7[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec3[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec44[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec8[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec45[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec9[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec2[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec46[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec48[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec50[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fRec1[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec52[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec54[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec10[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec77[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fRec76[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec75[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec74[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec73[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec72[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec71[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec70[l68] = 0.0f;

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
			fRec69[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec68[l76] = 0.0f;

		}
		for (int l77 = 0; (l77 < 3); l77 = (l77 + 1)) {
			fRec67[l77] = 0.0f;

		}
		for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
			fRec66[l78] = 0.0f;

		}
		for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
			fRec65[l79] = 0.0f;

		}
		for (int l80 = 0; (l80 < 3); l80 = (l80 + 1)) {
			fRec64[l80] = 0.0f;

		}
		for (int l81 = 0; (l81 < 3); l81 = (l81 + 1)) {
			fRec63[l81] = 0.0f;

		}
		for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
			fRec62[l82] = 0.0f;

		}
		for (int l83 = 0; (l83 < 3); l83 = (l83 + 1)) {
			fRec61[l83] = 0.0f;

		}
		for (int l84 = 0; (l84 < 3); l84 = (l84 + 1)) {
			fRec60[l84] = 0.0f;

		}
		for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
			fRec59[l85] = 0.0f;

		}
		for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
			fRec58[l86] = 0.0f;

		}
		for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
			fRec57[l87] = 0.0f;

		}
		for (int l88 = 0; (l88 < 3); l88 = (l88 + 1)) {
			fRec56[l88] = 0.0f;

		}
		for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
			fRec55[l89] = 0.0f;

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

	void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 1.000000e+00; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry37 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry15 = value + 1.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry21 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry22 = value + 0.000000e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry45 = value + 4.244019e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry40 = value + 4.810579e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry42 = value + -2.048106e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry44 = value + 6.148691e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry43 = value + -6.102038e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry41 = value + 1.980396e-04; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry10 = value + -6.358174e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry8 = value + -1.575095e+00; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry5 = value + 5.307900e-03; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry6 = value + -2.068471e-01; }
	void set_tetrode_plate_level(FAUSTFLOAT value) { fEntry48 = value + -5.551660e-01; }
	void set_tetrode_plate_level_b(FAUSTFLOAT value) { fEntry4 = value + -1.215200e+01; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry46 = value + -1.261398e+01; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00; }
	void set_tetrode_plate_ratio(FAUSTFLOAT value) { fEntry49 = value + 3.132527e-01; }
	void set_tetrode_plate_ratio_b(FAUSTFLOAT value) { fEntry50 = value + 1.903164e+03; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry7 = value + -5.594136e-01; }
	void set_tetrode_plate_tau(FAUSTFLOAT value) { fEntry47 = value + 1.847860e-02; }
	void set_tetrode_plate_tau_b(FAUSTFLOAT value) { fEntry3 = value + 4.243600e-01; }
	void set_triode_clip_level(FAUSTFLOAT value) { fEntry29 = value + 9.067676e-01; }
	void set_triode_clip_ratio(FAUSTFLOAT value) { fEntry30 = value + 1.147704e+00; }
	void set_triode_clip_smooth(FAUSTFLOAT value) { fEntry28 = value + -3.100322e+00; }
	void set_triode_clip_tau(FAUSTFLOAT value) { fEntry27 = value + -1.301785e+00; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry25 = value + 3.380630e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry26 = value + 1.066531e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry24 = value + 1.399600e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry23 = value + -1.121188e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry20 = value + 4.522249e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry13 = value + -1.120198e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry18 = value + 7.278736e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry33 = value + -3.222958e-01; }
	void set_triode_plate_level(FAUSTFLOAT value) { fEntry31 = value + 6.567379e+01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry16 = value + -9.430010e-02; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry14 = value + 0.000000e+00; }
	void set_triode_plate_ratio(FAUSTFLOAT value) { fEntry32 = value + 6.117379e+01; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry36 = value + 8.422808e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.523370e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry34 = value + -3.318985e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry17 = value + -3.580170e+00; }
	void set_triode_plate_tau(FAUSTFLOAT value) { fEntry19 = value + 6.579679e+01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry35 = value + -4.311549e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry39 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00; }
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
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = (float(fEntry2) + 1.0f);
		float fSlow3 = (0.0199999996f / fSlow2);
		float fSlow4 = std::exp(((4.60517025f * (float(fEntry3) + 1.0f)) + -9.2103405f));
		float fSlow5 = (1.0f / ((fConst0 * fSlow4) + 1.0f));
		float fSlow6 = (100.0f * (1.0f - (float(fEntry4) + 1.0f)));
		float fSlow7 = (20.0f * (float(fEntry5) + 1.0f));
		float fSlow8 = (float(fEntry6) + 1.0f);
		float fSlow9 = (1.0f - fSlow8);
		float fSlow10 = (0.100000001f / fSlow8);
		float fSlow11 = std::exp(((4.60517025f * (float(fEntry7) + 1.0f)) + -4.60517025f));
		float fSlow12 = (10.0f * (float(fEntry8) + 1.0f));
		float fSlow13 = (fSlow12 + 30.0f);
		float fSlow14 = (0.5f * (float(fEntry9) + 1.0f));
		float fSlow15 = (fSlow14 + 1.0f);
		float fSlow16 = std::pow(fSlow13, fSlow15);
		float fSlow17 = (10.0f / fSlow13);
		float fSlow18 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry10) + 1.0f)) + -2.30258512f))));
		float fSlow19 = (1.0f / fSlow18);
		float fSlow20 = (fSlow19 + 1.0f);
		float fSlow21 = (0.0f - (1.0f / (fSlow20 * fSlow18)));
		float fSlow22 = (float(fEntry11) + 1.0f);
		float fSlow23 = (50.0f * (fSlow2 * std::exp(((3.80045128f * fSlow22) + -2.30258512f))));
		float fSlow24 = float(fEntry12);
		float fSlow25 = ((fSlow24 < -0.800000012f)?(0.0f - (5.0f * (fSlow24 + 0.800000012f))):0.0f);
		float fSlow26 = (1.0f - fSlow25);
		float fSlow27 = (float(fEntry13) + 1.0f);
		float fSlow28 = (10.0f * fSlow27);
		float fSlow29 = (0.5f * (float(fEntry14) + 1.0f));
		float fSlow30 = std::pow(fSlow28, fSlow29);
		float fSlow31 = (1.0f / fSlow30);
		float fSlow32 = float(fEntry15);
		float fSlow33 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow32) + -2.0f));
		float fSlow34 = (1.0f - fSlow33);
		float fSlow35 = std::max<float>(0.0f, (std::min<float>(2.0f, fSlow32) + -1.0f));
		float fSlow36 = (1.0f - fSlow35);
		float fSlow37 = (fSlow29 + 1.0f);
		float fSlow38 = std::pow(fSlow28, fSlow37);
		float fSlow39 = (37.5f * (float(fEntry16) + 1.0f));
		float fSlow40 = (fSlow38 + fSlow39);
		float fSlow41 = std::exp(((3.45387769f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow42 = (1.0f / fSlow41);
		float fSlow43 = (150.0f * (float(fEntry18) + 1.0f));
		float fSlow44 = (fSlow43 + fSlow41);
		float fSlow45 = std::exp(((4.60517025f * (float(fEntry19) + 1.0f)) + -9.2103405f));
		float fSlow46 = (1.0f / ((fConst0 * fSlow45) + 1.0f));
		float fSlow47 = (1.0f / fSlow27);
		float fSlow48 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry20) + 1.0f)) + -2.30258512f))));
		float fSlow49 = (1.0f / fSlow48);
		float fSlow50 = (fSlow49 + 1.0f);
		float fSlow51 = (0.0f - (1.0f / (fSlow48 * fSlow50)));
		float fSlow52 = (float(fEntry22) + 1.0f);
		float fSlow53 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry21) + 1.0f)))))) * std::exp(((3.45387769f * fSlow52) + -0.693147182f)));
		float fSlow54 = (1.0f / fSlow50);
		float fSlow55 = (1.0f - fSlow49);
		float fSlow56 = (fSlow53 / fSlow48);
		float fSlow57 = std::exp(((3.45387769f * (float(fEntry23) + 1.0f)) + -13.8155107f));
		float fSlow58 = (1.0f / ((fConst0 * (fSlow57 * std::exp(((6.90775537f * (float(fEntry24) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow59 = (1.0f - fSlow58);
		float fSlow60 = (1.0f / ((fConst0 * fSlow57) + 1.0f));
		float fSlow61 = (5.0f * (1.0f - (float(fEntry25) + 1.0f)));
		float fSlow62 = (1.0f / ((fConst0 * (fSlow57 * std::exp(((5.75646257f * (float(fEntry26) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow63 = (1.0f - fSlow62);
		float fSlow64 = std::exp(((4.60517025f * (float(fEntry27) + 1.0f)) + -18.420681f));
		float fSlow65 = (1.0f / ((fConst0 * (fSlow64 * std::exp(((6.90775537f * (float(fEntry28) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow66 = (1.0f - fSlow65);
		float fSlow67 = (1.0f / ((fConst0 * fSlow64) + 1.0f));
		float fSlow68 = float(fEntry29);
		float fSlow69 = (1.0f / ((fConst0 * (fSlow64 * std::exp(((5.75646257f * (float(fEntry30) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow70 = (1.0f - fSlow69);
		float fSlow71 = (fSlow37 * fSlow30);
		float fSlow72 = (fSlow38 + (75.0f * (float(fEntry31) + 1.0f)));
		float fSlow73 = (1.0f / ((fConst0 * (fSlow45 * std::exp(((4.60517025f * (float(fEntry32) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow74 = (1.0f - fSlow73);
		float fSlow75 = std::exp(((4.60517025f * (float(fEntry33) + 1.0f)) + -2.30258512f));
		float fSlow76 = (fSlow75 + (fSlow38 + fSlow43));
		float fSlow77 = (1.0f / fSlow75);
		float fSlow78 = std::exp(((3.45387769f * (float(fEntry34) + 1.0f)) + -2.30258512f));
		float fSlow79 = std::exp(((4.60517025f * (float(fEntry35) + 1.0f)) + -9.2103405f));
		float fSlow80 = (1.0f / ((fConst0 * fSlow79) + 1.0f));
		float fSlow81 = (1.0f - (1.0f / ((fConst0 * (fSlow79 * std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -2.99573231f)))) + 1.0f)));
		float fSlow82 = ((float(fEntry37) + 1.0f) + 1.0f);
		float fSlow83 = (2.0f * (fSlow35 / fSlow82));
		float fSlow84 = (0.5f * (fSlow82 / fSlow30));
		float fSlow85 = (fSlow48 * fSlow30);
		float fSlow86 = (0.5f * (fSlow82 / fSlow85));
		float fSlow87 = (1.0f / fSlow85);
		float fSlow88 = (fSlow62 + -1.0f);
		float fSlow89 = (fSlow69 + -1.0f);
		float fSlow90 = (fSlow73 + -1.0f);
		float fSlow91 = AmpMono_faustpower2_f((0.5f * fSlow82));
		float fSlow92 = (fSlow33 / fSlow91);
		float fSlow93 = (fSlow91 / fSlow30);
		float fSlow94 = (fSlow91 / fSlow85);
		float fSlow95 = (5.0f * fSlow52);
		int iSlow96 = (fSlow95 < 9.0f);
		int iSlow97 = (fSlow95 < 8.0f);
		int iSlow98 = (fSlow95 < 7.0f);
		int iSlow99 = (fSlow95 < 6.0f);
		int iSlow100 = (fSlow95 < 5.0f);
		int iSlow101 = (fSlow95 < 4.0f);
		int iSlow102 = (fSlow95 < 3.0f);
		int iSlow103 = (fSlow95 < 2.0f);
		int iSlow104 = (fSlow95 < 1.0f);
		float fSlow105 = std::pow(10.0f, (0.0500000007f * (iSlow96?(iSlow97?(iSlow98?(iSlow99?(iSlow100?(iSlow101?(iSlow102?(iSlow103?(iSlow104?((fSlow95 < 0.0f)?4.8499999f:(iSlow104?(4.8499999f - (30.1000004f * fSlow52)):-1.16999996f)):(iSlow103?(-1.16999996f - (5.94999981f * (fSlow95 + -1.0f))):-7.11999989f)):(iSlow102?(-7.11999989f - (5.57999992f * (fSlow95 + -2.0f))):-12.6999998f)):(iSlow101?(-12.6999998f - (4.80000019f * (fSlow95 + -3.0f))):-17.5f)):(iSlow100?(-17.5f - (2.70000005f * (fSlow95 + -4.0f))):-20.2000008f)):(iSlow99?(-20.2000008f - (1.29999995f * (0.0f - (5.0f * (1.0f - fSlow52))))):-21.5f)):(iSlow98?(-21.5f - (0.600000024f * (fSlow95 + -6.0f))):-22.1000004f)):(iSlow97?(-22.1000004f - (0.5f * (fSlow95 + -7.0f))):-22.6000004f)):(iSlow96?(-22.6000004f - (0.300000012f * (fSlow95 + -8.0f))):-22.8999996f)):((fSlow95 < 10.0f)?(-22.8999996f - (0.200000003f * (fSlow95 + -9.0f))):-23.1000004f))));
		float fSlow106 = float(fEntry38);
		int iSlow107 = (fSlow106 > 0.0f);
		float fSlow108 = std::tan((fConst1 * float((iSlow107?100:50))));
		float fSlow109 = (1.0f / fSlow108);
		float fSlow110 = (fSlow109 + 1.0f);
		float fSlow111 = (0.0f - (1.0f / (fSlow108 * fSlow110)));
		float fSlow112 = (1.0f - fSlow109);
		float fSlow113 = (iSlow107?((5.0f * fSlow106) + 13.0f):((18.0f * fSlow106) + 13.0f));
		float fSlow114 = std::pow(10.0f, (0.0500000007f * fSlow113));
		float fSlow115 = ((fSlow106 < -0.800000012f)?(0.0f - (5.0f * (fSlow106 + 0.800000012f))):0.0f);
		float fSlow116 = (1.0f - fSlow115);
		float fSlow117 = ((fSlow24 > 0.0f)?((13.0f * fSlow24) + -3.0f):((5.0f * fSlow24) + -3.0f));
		int iSlow118 = (fSlow117 > 0.0f);
		float fSlow119 = (fConst14 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow117))));
		float fSlow120 = (iSlow118?fConst14:fSlow119);
		float fSlow121 = ((fConst13 * (fConst13 - fSlow120)) + 1.0f);
		float fSlow122 = ((fConst13 * (fConst13 + fSlow120)) + 1.0f);
		float fSlow123 = (iSlow118?fSlow119:fConst14);
		float fSlow124 = ((fConst13 * (fConst13 + fSlow123)) + 1.0f);
		float fSlow125 = ((fConst13 * (fConst13 - fSlow123)) + 1.0f);
		float fSlow126 = float(fEntry39);
		float fSlow127 = ((fSlow126 > 0.0f)?((10.0f * fSlow126) + 13.0f):((18.0f * fSlow126) + 13.0f));
		float fSlow128 = std::pow(10.0f, (0.0500000007f * fSlow127));
		float fSlow129 = ((fSlow126 < -0.800000012f)?(0.0f - (5.0f * (fSlow126 + 0.800000012f))):0.0f);
		float fSlow130 = (1.0f - fSlow129);
		float fSlow131 = std::pow(10.0f, (0.0f - (0.0500000007f * (((0.400000006f * fSlow113) + (0.600000024f * fSlow117)) + (0.200000003f * fSlow127)))));
		float fSlow132 = (250.0f * (float(fEntry40) + 1.0f));
		float fSlow133 = (1.0f / fSlow20);
		float fSlow134 = (1.0f - fSlow19);
		float fSlow135 = std::exp((0.0f - (fConst16 / std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -9.2103405f)))));
		float fSlow136 = (1.0f - fSlow135);
		float fSlow137 = (250.0f * (float(fEntry42) + 1.0f));
		float fSlow138 = std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f));
		float fSlow139 = (1.0f - (1.0f / ((fConst0 * (fSlow138 * std::exp(((4.60517025f * (float(fEntry44) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow140 = (1.0f / ((fConst0 * fSlow138) + 1.0f));
		float fSlow141 = (100.0f * (1.0f - (float(fEntry45) + 1.0f)));
		float fSlow142 = (fSlow137 + fSlow12);
		float fSlow143 = (std::pow(fSlow13, fSlow14) * fSlow15);
		float fSlow144 = std::pow(((2.0f * (float(fEntry46) + 1.0f)) + 40.0f), fSlow15);
		float fSlow145 = std::exp(((4.60517025f * (float(fEntry47) + 1.0f)) + -9.2103405f));
		float fSlow146 = (1.0f / ((fConst0 * fSlow145) + 1.0f));
		float fSlow147 = (50.0f * (float(fEntry48) + 1.0f));
		float fSlow148 = (1.0f - (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry49) + 1.0f)) + -4.60517025f)) * fSlow145)) + 1.0f)));
		float fSlow149 = (fSlow7 + (10.0f * fSlow9));
		float fSlow150 = (1.0f - (1.0f / ((fConst0 * (fSlow4 * std::exp(((4.60517025f * (float(fEntry50) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow151 = (5.0f * fSlow22);
		int iSlow152 = (fSlow151 < 9.0f);
		int iSlow153 = (fSlow151 < 7.0f);
		int iSlow154 = (fSlow151 < 6.0f);
		int iSlow155 = (fSlow151 < 5.0f);
		int iSlow156 = (fSlow151 < 4.0f);
		int iSlow157 = (fSlow151 < 3.0f);
		int iSlow158 = (fSlow151 < 2.0f);
		int iSlow159 = (fSlow151 < 1.0f);
		float fSlow160 = std::pow(10.0f, (0.0500000007f * (iSlow152?((fSlow151 < 8.0f)?(iSlow153?(iSlow154?(iSlow155?(iSlow156?(iSlow157?(iSlow158?(iSlow159?((fSlow151 < 0.0f)?19.0f:(iSlow159?(19.0f - (33.0f * fSlow22)):12.3999996f)):(iSlow158?(12.3999996f - (6.55000019f * (fSlow151 + -1.0f))):5.8499999f)):(iSlow157?(5.8499999f - (6.0079999f * (fSlow151 + -2.0f))):-0.158000007f)):(iSlow156?(-0.158000007f - (5.25199986f * (fSlow151 + -3.0f))):-5.40999985f)):(iSlow155?(-5.40999985f - (3.57999992f * (fSlow151 + -4.0f))):-8.98999977f)):(iSlow154?(-8.98999977f - (1.40999997f * (0.0f - (5.0f * (1.0f - fSlow22))))):-10.3999996f)):(iSlow153?(-10.3999996f - (0.200000003f * (fSlow151 + -6.0f))):-10.6000004f)):-10.6000004f):(iSlow152?((0.100000001f * (fSlow151 + -8.0f)) + -10.6000004f):-10.5f)):((fSlow151 < 10.0f)?((0.100000001f * (fSlow151 + -9.0f)) + -10.5f):-10.3999996f))));
		float fSlow161 = (fConst150 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow53 * fTemp0);
			fRec8[0] = ((fSlow51 * fVec0[1]) - (fSlow54 * ((fSlow55 * fRec8[1]) - (fSlow56 * fTemp0))));
			fRec10[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec8[0])) - fRec10[1]))) + (fSlow63 * fRec10[1]));
			fRec9[0] = ((fSlow59 * fRec9[1]) + (fSlow58 * fRec10[0]));
			fRec12[0] = ((fSlow67 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec8[0] + (-2.0f - fRec9[0])) - fSlow68)) - fRec12[1]))) + (fSlow70 * fRec12[1]));
			fRec11[0] = ((fSlow66 * fRec11[1]) + (fSlow65 * fRec12[0]));
			float fTemp1 = (fRec8[0] - (fRec9[0] + fRec11[0]));
			float fTemp2 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow47 * std::fabs(fTemp1)) + -0.0500000007f)));
			float fTemp3 = ((fTemp2 * (std::pow(std::max<float>(0.0f, (fSlow28 + fTemp1)), fSlow37) - fSlow38)) + (fSlow71 * ((1.0f - fTemp2) * fTemp1)));
			fRec7[0] = ((fSlow46 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp3 + 100.0f) - fSlow72)) - fRec7[1]))) + (fSlow74 * fRec7[1]));
			float fTemp4 = ((fRec7[0] + (300.0f - fTemp3)) - fSlow76);
			float fTemp5 = (std::max<float>(0.0f, fTemp4) + (fSlow75 * (float(tanhf(float((fSlow77 * std::min<float>(0.0f, fTemp4))))) + 1.0f)));
			fRec13[0] = ((fSlow80 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow43 + ((fTemp5 + -250.0f) - fSlow39))) - fRec13[1]))) + (fSlow81 * fRec13[1]));
			float fTemp6 = (fSlow78 * fRec13[0]);
			float fTemp7 = (fSlow44 + ((fTemp5 + (-250.0f - fTemp6)) - fSlow39));
			float fTemp8 = (fSlow40 + ((((fSlow41 * (float(tanhf(float((fSlow42 * std::max<float>(0.0f, fTemp7))))) + -1.0f)) + std::min<float>(0.0f, fTemp7)) + fTemp6) + -50.0f));
			fVec1[0] = (fSlow84 * fTemp8);
			fRec19[0] = ((fSlow51 * fVec1[1]) + (fSlow54 * ((fSlow86 * fTemp8) - (fSlow55 * fRec19[1]))));
			fRec21[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec19[0])) - fRec21[1]))) + (fSlow63 * fRec21[1]));
			fRec20[0] = ((fSlow58 * fRec21[0]) + (fSlow59 * fRec20[1]));
			fRec23[0] = ((fSlow70 * fRec23[1]) + (fSlow67 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec19[0] + (-2.0f - fRec20[0])) - fSlow68)) - fRec23[1]))));
			fRec22[0] = ((fSlow66 * fRec22[1]) + (fSlow65 * fRec23[0]));
			float fTemp9 = (fRec19[0] - (fRec20[0] + fRec22[0]));
			float fTemp10 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow47 * std::fabs(fTemp9)) + -0.0500000007f)));
			float fTemp11 = (((std::pow(std::max<float>(0.0f, (fSlow28 + fTemp9)), fSlow37) - fSlow38) * fTemp10) + (fSlow71 * ((1.0f - fTemp10) * fTemp9)));
			fRec18[0] = ((fSlow46 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp11 + 100.0f) - fSlow72)) - fRec18[1]))) + (fSlow74 * fRec18[1]));
			float fTemp12 = ((fRec18[0] + (300.0f - fTemp11)) - fSlow76);
			float fTemp13 = (std::max<float>(0.0f, fTemp12) + (fSlow75 * (float(tanhf(float((fSlow77 * std::min<float>(0.0f, fTemp12))))) + 1.0f)));
			fRec17[0] = ((fSlow81 * fRec17[1]) + (fSlow80 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow43 + ((fTemp13 + -250.0f) - fSlow39))) - fRec17[1]))));
			float fTemp14 = (fSlow78 * fRec17[0]);
			float fTemp15 = (fSlow44 + ((fTemp13 + (-250.0f - fTemp14)) - fSlow39));
			float fTemp16 = (fSlow40 + ((fTemp14 + std::min<float>(0.0f, fTemp15)) + (-50.0f - (fSlow41 * (1.0f - float(tanhf(float((fSlow42 * std::max<float>(0.0f, fTemp15))))))))));
			fVec2[0] = (fSlow31 * fTemp16);
			fRec16[0] = ((fSlow51 * fVec2[1]) - (fSlow54 * ((fSlow55 * fRec16[1]) - (fSlow87 * fTemp16))));
			fRec25[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec16[0])) - fRec25[1]))) - (fSlow88 * fRec25[1]));
			fRec24[0] = ((fSlow58 * fRec25[0]) + (fSlow59 * fRec24[1]));
			fRec27[0] = ((fSlow67 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec16[0] + (-2.0f - fRec24[0])) - fSlow68)) - fRec27[1]))) - (fSlow89 * fRec27[1]));
			fRec26[0] = ((fSlow65 * fRec27[0]) + (fSlow66 * fRec26[1]));
			float fTemp17 = (fRec16[0] - (fRec24[0] + fRec26[0]));
			float fTemp18 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow47 * std::fabs(fTemp17)) + -0.0500000007f)));
			float fTemp19 = ((fTemp18 * (std::pow(std::max<float>(0.0f, (fSlow28 + fTemp17)), fSlow37) - fSlow38)) + (fSlow71 * (fTemp17 * (1.0f - fTemp18))));
			fRec15[0] = ((fSlow46 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp19 + 100.0f) - fSlow72)) - fRec15[1]))) - (fSlow90 * fRec15[1]));
			float fTemp20 = ((fRec15[0] + (300.0f - fTemp19)) - fSlow76);
			float fTemp21 = (std::max<float>(0.0f, fTemp20) + (fSlow75 * (float(tanhf(float((fSlow77 * std::min<float>(0.0f, fTemp20))))) + 1.0f)));
			fRec14[0] = ((fSlow81 * fRec14[1]) + (fSlow80 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow43 + ((fTemp21 + -250.0f) - fSlow39))) - fRec14[1]))));
			float fTemp22 = (fSlow78 * fRec14[0]);
			float fTemp23 = (fSlow44 + ((fTemp21 + (-250.0f - fTemp22)) - fSlow39));
			float fTemp24 = ((fSlow36 * fTemp8) + (fSlow83 * (fSlow40 + ((fTemp22 + std::min<float>(0.0f, fTemp23)) + (-50.0f - (fSlow41 * (1.0f - float(tanhf(float((fSlow42 * std::max<float>(0.0f, fTemp23))))))))))));
			fVec3[0] = (fSlow93 * fTemp24);
			fRec31[0] = ((fSlow51 * fVec3[1]) - (fSlow54 * ((fSlow55 * fRec31[1]) - (fSlow94 * fTemp24))));
			fRec35[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec31[0])) - fRec35[1]))) + (fSlow63 * fRec35[1]));
			fRec34[0] = ((fSlow59 * fRec34[1]) + (fSlow58 * fRec35[0]));
			fRec33[0] = ((fSlow70 * fRec33[1]) + (fSlow67 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec31[0] + (-2.0f - fRec34[0])) - fSlow68)) - fRec33[1]))));
			fRec32[0] = ((fSlow66 * fRec32[1]) + (fSlow65 * fRec33[0]));
			float fTemp25 = (fRec31[0] - (fRec32[0] + fRec34[0]));
			float fTemp26 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow47 * std::fabs(fTemp25)) + -0.0500000007f)));
			float fTemp27 = ((fTemp26 * (std::pow(std::max<float>(0.0f, (fSlow28 + fTemp25)), fSlow37) - fSlow38)) + (fSlow71 * ((1.0f - fTemp26) * fTemp25)));
			fRec30[0] = ((fSlow46 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp27 + 100.0f) - fSlow72)) - fRec30[1]))) + (fSlow74 * fRec30[1]));
			float fTemp28 = ((fRec30[0] + (300.0f - fTemp27)) - fSlow76);
			float fTemp29 = (std::max<float>(0.0f, fTemp28) + (fSlow75 * (float(tanhf(float((fSlow77 * std::min<float>(0.0f, fTemp28))))) + 1.0f)));
			fRec36[0] = ((fSlow81 * fRec36[1]) + (fSlow80 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow43 + ((fTemp29 + -250.0f) - fSlow39))) - fRec36[1]))));
			float fTemp30 = (fSlow78 * fRec36[0]);
			float fTemp31 = (fSlow44 + ((fTemp29 + (-250.0f - fTemp30)) - fSlow39));
			float fTemp32 = (fSlow40 + ((std::min<float>(0.0f, fTemp31) + fTemp30) + (-50.0f - (fSlow41 * (1.0f - float(tanhf(float((fSlow42 * std::max<float>(0.0f, fTemp31))))))))));
			fVec4[0] = (fSlow31 * fTemp32);
			fRec29[0] = ((fSlow51 * fVec4[1]) - (fSlow54 * ((fSlow55 * fRec29[1]) - (fSlow87 * fTemp32))));
			fRec38[0] = ((fSlow63 * fRec38[1]) + (fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow61 + fRec29[0])) - fRec38[1]))));
			fRec37[0] = ((fSlow59 * fRec37[1]) + (fSlow58 * fRec38[0]));
			fRec40[0] = ((fSlow67 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec29[0] + (-2.0f - fRec37[0])) - fSlow68)) - fRec40[1]))) - (fSlow89 * fRec40[1]));
			fRec39[0] = ((fSlow66 * fRec39[1]) + (fSlow65 * fRec40[0]));
			float fTemp33 = (fRec29[0] - (fRec37[0] + fRec39[0]));
			float fTemp34 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow47 * std::fabs(fTemp33)) + -0.0500000007f)));
			float fTemp35 = (((std::pow(std::max<float>(0.0f, (fSlow28 + fTemp33)), fSlow37) - fSlow38) * fTemp34) + (fSlow71 * (fTemp33 * (1.0f - fTemp34))));
			fRec28[0] = ((fSlow74 * fRec28[1]) + (fSlow46 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp35 + 100.0f) - fSlow72)) - fRec28[1]))));
			float fTemp36 = ((fRec28[0] + (300.0f - fTemp35)) - fSlow76);
			float fTemp37 = (std::max<float>(0.0f, fTemp36) + (fSlow75 * (float(tanhf(float((fSlow77 * std::min<float>(0.0f, fTemp36))))) + 1.0f)));
			fRec41[0] = ((fSlow80 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow43 + ((fTemp37 + -250.0f) - fSlow39))) - fRec41[1]))) + (fSlow81 * fRec41[1]));
			float fTemp38 = (fSlow78 * fRec41[0]);
			float fTemp39 = (fSlow44 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow39));
			float fTemp40 = (((fSlow34 * fTemp24) + (fSlow92 * (fSlow40 + ((std::min<float>(0.0f, fTemp39) + fTemp38) + (-50.0f - (fSlow41 * (1.0f - float(tanhf(float((fSlow42 * std::max<float>(0.0f, fTemp39)))))))))))) * fSlow105);
			float fTemp41 = (fSlow31 * fTemp40);
			fVec5[0] = fTemp41;
			fRec6[0] = ((fVec5[1] * fSlow111) - (((fRec6[1] * fSlow112) - (fSlow31 * (fTemp40 / fSlow108))) / fSlow110));
			fRec42[0] = (0.0f - (((fSlow112 * fRec42[1]) - (fVec5[1] + fTemp41)) / fSlow110));
			float fTemp42 = (fRec6[0] + (fRec42[0] * fSlow114));
			fVec6[0] = fTemp42;
			fRec5[0] = ((fConst9 * fVec6[1]) - (fConst10 * ((fConst11 * fRec5[1]) - (fConst7 * fTemp42))));
			float fTemp43 = (fConst15 * fRec4[1]);
			fRec4[0] = (((fRec5[0] * fSlow115) + (fSlow116 * fTemp42)) - (((fRec4[2] * fSlow121) + fTemp43) / fSlow122));
			float fTemp44 = (((fRec4[0] * fSlow124) + fTemp43) + (fRec4[2] * fSlow125));
			float fTemp45 = (fConst23 * fRec43[1]);
			fRec43[0] = ((fTemp44 / fSlow122) - (fConst22 * (fTemp45 + (fConst24 * fRec43[2]))));
			float fTemp46 = (((fSlow26 * fTemp44) / fSlow122) + (fConst22 * (fSlow25 * ((fTemp45 + (fConst25 * fRec43[0])) + (fConst25 * fRec43[2])))));
			fVec7[0] = fTemp46;
			fRec3[0] = (fConst5 * ((fVec7[1] + fTemp46) - (fConst26 * fRec3[1])));
			fRec44[0] = ((fConst27 * fVec7[1]) - (fConst5 * ((fConst26 * fRec44[1]) - (fConst3 * fTemp46))));
			float fTemp47 = (fRec3[0] + (fRec44[0] * fSlow128));
			fVec8[0] = fTemp47;
			fRec45[0] = (0.0f - (fConst29 * ((fConst30 * fRec45[1]) - (fTemp47 + fVec8[1]))));
			float fTemp48 = ((fSlow23 * (((fTemp47 * fSlow130) + (fRec45[0] * fSlow129)) * fSlow131)) - fSlow132);
			fVec9[0] = fTemp48;
			fRec2[0] = ((fSlow21 * fVec9[1]) - (fSlow133 * ((fSlow134 * fRec2[1]) - (fSlow19 * fTemp48))));
			fRec46[0] = ((fSlow136 * (fRec2[0] - fSlow137)) + (fSlow135 * fRec46[1]));
			fRec48[0] = ((fSlow139 * fRec48[1]) + (fSlow140 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow141 + ((fRec2[0] - fRec46[0]) - fSlow137))) - fRec48[1]))));
			float fRec47 = fRec48[0];
			float fTemp49 = (fRec46[0] + fRec47);
			float fTemp50 = (0.0f - ((fRec2[0] - fTemp49) - fSlow137));
			float fTemp51 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow17 * std::fabs(fTemp50)) + -0.0500000007f)));
			float fTemp52 = (fSlow11 * (fSlow16 + (((fTemp51 * (std::pow(std::max<float>(0.0f, (fSlow142 + (fTemp49 + (30.0f - fRec2[0])))), fSlow15) - fSlow16)) + (fSlow143 * (fTemp50 * (1.0f - fTemp51)))) - fSlow144)));
			fRec50[0] = ((fSlow146 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp52 - fSlow147)) - fRec50[1]))) + (fSlow148 * fRec50[1]));
			float fRec49 = fRec50[0];
			float fTemp53 = ((fTemp52 - fRec49) - fSlow149);
			float fTemp54 = std::max<float>(0.0f, (fSlow7 + ((10.0f * (fSlow9 + (fSlow8 * float(tanhf(float((fSlow10 * std::max<float>(0.0f, fTemp53)))))))) + std::min<float>(0.0f, fTemp53))));
			fRec1[0] = ((fSlow5 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow6 + fTemp54)) - fRec1[1]))) + (fSlow150 * fRec1[1]));
			float fRec0 = fRec1[0];
			float fTemp55 = (0.0f - fTemp50);
			float fTemp56 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow17 * std::fabs(fTemp55)) + -0.0500000007f)));
			float fTemp57 = (fSlow11 * (fSlow16 + (((fTemp56 * (std::pow(std::max<float>(0.0f, (fSlow12 + ((fRec2[0] + (30.0f - fTemp49)) - fSlow137))), fSlow15) - fSlow16)) + (fSlow143 * (fTemp55 * (1.0f - fTemp56)))) - fSlow144)));
			fRec52[0] = ((fSlow146 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp57 - fSlow147)) - fRec52[1]))) + (fSlow148 * fRec52[1]));
			float fRec51 = fRec52[0];
			float fTemp58 = ((fTemp57 - fRec51) - fSlow149);
			float fTemp59 = std::max<float>(0.0f, (fSlow7 + (std::min<float>(0.0f, fTemp58) + (10.0f * (fSlow9 + (fSlow8 * float(tanhf(float((fSlow10 * std::max<float>(0.0f, fTemp58)))))))))));
			fRec54[0] = ((fSlow150 * fRec54[1]) + (fSlow5 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow6 + fTemp59)) - fRec54[1]))));
			float fRec53 = fRec54[0];
			float fTemp60 = (((fRec0 + fTemp59) - (fRec53 + fTemp54)) * fSlow160);
			float fTemp61 = (fSlow3 * fTemp60);
			fVec10[0] = fTemp61;
			fRec77[0] = ((fConst148 * fVec10[1]) + (fConst149 * ((fSlow161 * fTemp60) - (fConst151 * fRec77[1]))));
			fRec76[0] = (0.0f - (fConst143 * ((fConst144 * fRec76[1]) - (fRec77[0] + fRec77[1]))));
			fRec75[0] = ((fConst141 * fRec76[1]) - (fConst152 * ((fConst153 * fRec75[1]) - (fConst132 * fRec76[0]))));
			fRec74[0] = (fRec75[0] - (fConst139 * ((fConst154 * fRec74[2]) + (fConst155 * fRec74[1]))));
			fRec73[0] = ((fConst139 * ((fConst135 * fRec74[2]) + ((fConst135 * fRec74[0]) + (fConst156 * fRec74[1])))) - (fConst138 * ((fConst157 * fRec73[2]) + (fConst155 * fRec73[1]))));
			fRec72[0] = ((fConst138 * (((fConst135 * fRec73[0]) + (fConst156 * fRec73[1])) + (fConst135 * fRec73[2]))) - (fConst137 * ((fConst158 * fRec72[2]) + (fConst155 * fRec72[1]))));
			fRec71[0] = ((fConst137 * (((fConst135 * fRec72[0]) + (fConst156 * fRec72[1])) + (fConst135 * fRec72[2]))) - (fConst136 * ((fConst155 * fRec71[1]) + (fConst159 * fRec71[2]))));
			fRec70[0] = ((fConst136 * (((fConst135 * fRec71[0]) + (fConst156 * fRec71[1])) + (fConst135 * fRec71[2]))) - (fConst133 * ((fConst160 * fRec70[2]) + (fConst155 * fRec70[1]))));
			fRec83[0] = (0.0f - (fConst152 * ((fConst153 * fRec83[1]) - (fRec76[0] + fRec76[1]))));
			fRec82[0] = (fRec83[0] - (fConst139 * ((fConst155 * fRec82[1]) + (fConst154 * fRec82[2]))));
			fRec81[0] = ((fConst139 * (fRec82[2] + (fRec82[0] + (2.0f * fRec82[1])))) - (fConst138 * ((fConst157 * fRec81[2]) + (fConst155 * fRec81[1]))));
			fRec80[0] = ((fConst138 * ((fRec81[0] + (2.0f * fRec81[1])) + fRec81[2])) - (fConst137 * ((fConst158 * fRec80[2]) + (fConst155 * fRec80[1]))));
			fRec79[0] = ((fConst137 * (fRec80[2] + (fRec80[0] + (2.0f * fRec80[1])))) - (fConst136 * ((fConst159 * fRec79[2]) + (fConst155 * fRec79[1]))));
			fRec78[0] = ((fConst136 * (fRec79[2] + (fRec79[0] + (2.0f * fRec79[1])))) - (fConst133 * ((fConst160 * fRec78[2]) + (fConst155 * fRec78[1]))));
			float fTemp62 = (fConst161 * fRec69[1]);
			fRec69[0] = ((fConst133 * ((0.13673377f * ((fConst135 * fRec70[2]) + ((fConst156 * fRec70[1]) + (fConst135 * fRec70[0])))) + (fRec78[2] + (fRec78[0] + (2.0f * fRec78[1]))))) - (fConst128 * (fTemp62 + (fConst162 * fRec69[2]))));
			float fTemp63 = (fConst123 * fRec68[1]);
			fRec68[0] = ((fConst128 * ((fConst130 * fRec69[2]) + (fTemp62 + (fConst163 * fRec69[0])))) - (fConst122 * ((fConst164 * fRec68[2]) + fTemp63)));
			float fTemp64 = (fConst168 * fRec67[1]);
			fRec67[0] = ((fConst122 * ((fTemp63 + (fConst166 * fRec68[0])) + (fConst167 * fRec68[2]))) - (fConst115 * (fTemp64 + (fConst169 * fRec67[2]))));
			float fTemp65 = (fConst110 * fRec66[1]);
			fRec66[0] = ((fConst115 * ((fConst117 * fRec67[2]) + (fTemp64 + (fConst170 * fRec67[0])))) - (fConst109 * (fTemp65 + (fConst171 * fRec66[2]))));
			float fTemp66 = (fConst104 * fRec65[1]);
			fRec65[0] = ((fConst109 * ((fTemp65 + (fConst173 * fRec66[0])) + (fConst174 * fRec66[2]))) - (fConst103 * (fTemp66 + (fConst175 * fRec65[2]))));
			float fTemp67 = (fConst98 * fRec64[1]);
			fRec64[0] = ((fConst103 * ((fTemp66 + (fConst177 * fRec65[0])) + (fConst178 * fRec65[2]))) - (fConst97 * ((fConst179 * fRec64[2]) + fTemp67)));
			float fTemp68 = (fConst184 * fRec63[1]);
			fRec63[0] = ((fConst97 * ((fTemp67 + (fConst181 * fRec64[0])) + (fConst182 * fRec64[2]))) - (fConst90 * ((fConst183 * fRec63[2]) + fTemp68)));
			float fTemp69 = (fConst187 * fRec62[1]);
			fRec62[0] = ((fConst90 * ((fConst92 * fRec63[2]) + (fTemp68 + (fConst185 * fRec63[0])))) - (fConst83 * ((fConst186 * fRec62[2]) + fTemp69)));
			float fTemp70 = (fConst78 * fRec61[1]);
			fRec61[0] = ((fConst83 * ((fConst85 * fRec62[2]) + (fTemp69 + (fConst188 * fRec62[0])))) - (fConst77 * (fTemp70 + (fConst189 * fRec61[2]))));
			float fTemp71 = (fConst193 * fRec60[1]);
			fRec60[0] = ((fConst77 * ((fTemp70 + (fConst191 * fRec61[0])) + (fConst192 * fRec61[2]))) - (fConst70 * (fTemp71 + (fConst194 * fRec60[2]))));
			float fTemp72 = (fConst197 * fRec59[1]);
			fRec59[0] = ((fConst70 * ((fConst72 * fRec60[2]) + (fTemp71 + (fConst195 * fRec60[0])))) - (fConst63 * ((fConst196 * fRec59[2]) + fTemp72)));
			float fTemp73 = (fConst200 * fRec58[1]);
			fRec58[0] = ((fConst63 * (((fConst65 * fRec59[0]) + fTemp72) + (fConst198 * fRec59[2]))) - (fConst56 * ((fConst199 * fRec58[2]) + fTemp73)));
			float fTemp74 = (fConst202 * fRec57[1]);
			fRec57[0] = ((fConst56 * (((fConst58 * fRec58[0]) + fTemp73) + (fConst201 * fRec58[2]))) - (fConst49 * (fTemp74 + (fConst203 * fRec57[2]))));
			float fTemp75 = (fConst206 * fRec56[1]);
			fRec56[0] = ((fConst49 * ((fConst51 * fRec57[2]) + (fTemp74 + (fConst204 * fRec57[0])))) - (fConst42 * ((fConst205 * fRec56[2]) + fTemp75)));
			float fTemp76 = (fConst37 * fRec55[1]);
			fRec55[0] = ((fConst42 * ((fConst44 * fRec56[2]) + (fTemp75 + (fConst207 * fRec56[0])))) - (fConst208 * (fTemp76 + (fConst209 * fRec55[2]))));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst36 * ((fTemp76 + (fConst211 * fRec55[0])) + (fConst212 * fRec55[2]))):fTemp61)));
			fVec0[1] = fVec0[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fRec13[1] = fRec13[0];
			fVec1[1] = fVec1[0];
			fRec19[1] = fRec19[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec18[1] = fRec18[0];
			fRec17[1] = fRec17[0];
			fVec2[1] = fVec2[0];
			fRec16[1] = fRec16[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec27[1] = fRec27[0];
			fRec26[1] = fRec26[0];
			fRec15[1] = fRec15[0];
			fRec14[1] = fRec14[0];
			fVec3[1] = fVec3[0];
			fRec31[1] = fRec31[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec30[1] = fRec30[0];
			fRec36[1] = fRec36[0];
			fVec4[1] = fVec4[0];
			fRec29[1] = fRec29[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec28[1] = fRec28[0];
			fRec41[1] = fRec41[0];
			fVec5[1] = fVec5[0];
			fRec6[1] = fRec6[0];
			fRec42[1] = fRec42[0];
			fVec6[1] = fVec6[0];
			fRec5[1] = fRec5[0];
			fRec4[2] = fRec4[1];
			fRec4[1] = fRec4[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fVec7[1] = fVec7[0];
			fRec3[1] = fRec3[0];
			fRec44[1] = fRec44[0];
			fVec8[1] = fVec8[0];
			fRec45[1] = fRec45[0];
			fVec9[1] = fVec9[0];
			fRec2[1] = fRec2[0];
			fRec46[1] = fRec46[0];
			fRec48[1] = fRec48[0];
			fRec50[1] = fRec50[0];
			fRec1[1] = fRec1[0];
			fRec52[1] = fRec52[0];
			fRec54[1] = fRec54[0];
			fVec10[1] = fVec10[0];
			fRec77[1] = fRec77[0];
			fRec76[1] = fRec76[0];
			fRec75[1] = fRec75[0];
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
			fRec64[2] = fRec64[1];
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
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];

		}

	}


};

#endif
