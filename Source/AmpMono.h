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
	int fSamplingFreq;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	FAUSTFLOAT fEntry2;
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
	FAUSTFLOAT fEntry3;
	FAUSTFLOAT fEntry4;
	FAUSTFLOAT fEntry5;
	float fConst117;
	FAUSTFLOAT fEntry6;
	FAUSTFLOAT fEntry7;
	float fConst118;
	float fConst119;
	float fConst120;
	float fConst121;
	float fConst122;
	FAUSTFLOAT fEntry8;
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
	float fVec0[2];
	float fRec31[2];
	FAUSTFLOAT fEntry23;
	FAUSTFLOAT fEntry24;
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	FAUSTFLOAT fEntry29;
	float fRec35[2];
	float fRec34[2];
	FAUSTFLOAT fEntry30;
	float fRec33[2];
	float fRec32[2];
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	FAUSTFLOAT fEntry33;
	float fRec36[2];
	float fRec30[2];
	float fVec1[2];
	float fRec29[2];
	float fRec38[2];
	float fRec37[2];
	float fRec40[2];
	float fRec39[2];
	float fRec41[2];
	float fRec28[2];
	float fVec2[2];
	float fRec27[2];
	float fRec43[2];
	float fRec42[2];
	float fRec45[2];
	float fRec44[2];
	float fRec46[2];
	float fRec47[2];
	float fVec3[2];
	float fRec26[2];
	float fRec48[2];
	float fVec4[2];
	float fConst123;
	float fConst124;
	float fConst125;
	float fConst126;
	float fConst127;
	float fConst128;
	float fRec49[2];
	float fConst129;
	float fConst130;
	float fConst131;
	float fConst132;
	float fRec25[3];
	float fConst133;
	float fConst134;
	float fConst135;
	float fConst136;
	float fConst137;
	float fConst138;
	float fConst139;
	float fConst140;
	float fConst141;
	float fRec50[3];
	float fVec5[2];
	float fRec24[2];
	float fConst142;
	float fRec51[2];
	float fVec6[2];
	float fConst143;
	float fConst144;
	float fConst145;
	float fRec52[2];
	float fVec7[2];
	float fRec23[2];
	FAUSTFLOAT fEntry34;
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec54[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	FAUSTFLOAT fEntry39;
	float fRec55[2];
	FAUSTFLOAT fEntry40;
	float fVec8[2];
	float fRec56[2];
	float fRec58[2];
	float fRec59[2];
	float fVec9[2];
	float fConst146;
	float fConst147;
	float fConst148;
	float fRec22[2];
	float fRec21[2];
	float fConst149;
	float fConst150;
	float fRec20[2];
	float fConst151;
	float fConst152;
	float fRec19[3];
	float fConst153;
	float fRec18[3];
	float fConst154;
	float fRec17[3];
	float fConst155;
	float fRec16[3];
	float fConst156;
	float fRec15[3];
	float fRec65[2];
	float fRec64[3];
	float fRec63[3];
	float fRec62[3];
	float fRec61[3];
	float fRec60[3];
	float fConst157;
	float fConst158;
	float fRec14[3];
	float fConst159;
	float fConst160;
	float fRec13[3];
	float fConst161;
	float fConst162;
	float fConst163;
	float fConst164;
	float fRec12[3];
	float fConst165;
	float fConst166;
	float fConst167;
	float fConst168;
	float fRec11[3];
	float fConst169;
	float fConst170;
	float fConst171;
	float fConst172;
	float fConst173;
	float fRec10[3];
	float fConst174;
	float fConst175;
	float fRec9[3];
	float fConst176;
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec8[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fConst183;
	float fRec7[3];
	float fConst184;
	float fConst185;
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec6[3];
	float fConst189;
	float fConst190;
	float fRec5[3];
	float fConst191;
	float fConst192;
	float fConst193;
	float fConst194;
	float fConst195;
	float fRec4[3];
	float fConst196;
	float fConst197;
	float fRec3[3];
	float fConst198;
	float fConst199;
	float fConst200;
	float fConst201;
	float fConst202;
	float fRec2[3];
	float fConst203;
	float fConst204;
	float fRec1[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fConst208;
	float fConst209;
	float fConst210;
	float fRec0[3];
	float fConst211;

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
		fConst33 = (148.323349f / fConst30);
		fConst34 = (((fConst29 - fConst33) / fConst28) + 1.0f);
		fConst35 = std::tan((1891.23853f / fConst0));
		fConst36 = (1.0f / fConst35);
		fConst37 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst38 = (265.978119f / fConst37);
		fConst39 = (1.0f / (((fConst36 + fConst38) / fConst35) + 1.0f));
		fConst40 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst35))));
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
		fConst53 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst48))));
		fConst54 = std::tan((13437.668f / fConst0));
		fConst55 = (1.0f / fConst54);
		fConst56 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst57 = (13245.1885f / fConst56);
		fConst58 = (1.0f / (((fConst55 + fConst57) / fConst54) + 1.0f));
		fConst59 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst54))));
		fConst60 = std::tan((10058.502f / fConst0));
		fConst61 = (1.0f / fConst60);
		fConst62 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst63 = (4926.20459f / fConst62);
		fConst64 = (1.0f / (((fConst61 + fConst63) / fConst60) + 1.0f));
		fConst65 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst60))));
		fConst66 = std::tan((8136.54736f / fConst0));
		fConst67 = (1.0f / fConst66);
		fConst68 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst69 = (966.024841f / fConst68);
		fConst70 = (1.0f / (((fConst67 + fConst69) / fConst66) + 1.0f));
		fConst71 = (518.801147f / fConst68);
		fConst72 = (((fConst67 + fConst71) / fConst66) + 1.0f);
		fConst73 = std::tan((8011.02734f / fConst0));
		fConst74 = (1.0f / fConst73);
		fConst75 = (fConst0 * std::sin((16022.0547f / fConst0)));
		fConst76 = (1613.9762f / fConst75);
		fConst77 = (1.0f / (((fConst74 + fConst76) / fConst73) + 1.0f));
		fConst78 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst73))));
		fConst79 = std::tan((9456.15234f / fConst0));
		fConst80 = (1.0f / fConst79);
		fConst81 = (fConst0 * std::sin((18912.3047f / fConst0)));
		fConst82 = (2492.29883f / fConst81);
		fConst83 = (1.0f / (((fConst80 + fConst82) / fConst79) + 1.0f));
		fConst84 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst79))));
		fConst85 = std::tan((2827.43262f / fConst0));
		fConst86 = (1.0f / fConst85);
		fConst87 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst88 = (19634.3262f / fConst87);
		fConst89 = (1.0f / (((fConst86 + fConst88) / fConst85) + 1.0f));
		fConst90 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst85))));
		fConst91 = std::tan((375.293884f / fConst0));
		fConst92 = (1.0f / fConst91);
		fConst93 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst94 = (463.734222f / fConst93);
		fConst95 = (1.0f / (((fConst92 + fConst94) / fConst91) + 1.0f));
		fConst96 = (3220.11475f / fConst93);
		fConst97 = (((fConst92 - fConst96) / fConst91) + 1.0f);
		fConst98 = std::tan((18369.8027f / fConst0));
		fConst99 = (1.0f / fConst98);
		fConst100 = (1.0f / (((fConst99 + 0.284629673f) / fConst98) + 1.0f));
		fConst101 = AmpMono_faustpower2_f(fConst98);
		fConst102 = (0.0f - (2.0f / fConst101));
		fConst103 = (1.0f / (((fConst99 + 0.830830038f) / fConst98) + 1.0f));
		fConst104 = (1.0f / fConst101);
		fConst105 = (1.0f / (((fConst99 + 1.30972147f) / fConst98) + 1.0f));
		fConst106 = (1.0f / (((fConst99 + 1.68250704f) / fConst98) + 1.0f));
		fConst107 = (1.0f / (((fConst99 + 1.91898596f) / fConst98) + 1.0f));
		fConst108 = (fConst99 + 1.0f);
		fConst109 = (0.0f - (1.0f / (fConst98 * fConst108)));
		fConst110 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst111 = (1.0f / (fConst110 + 1.0f));
		fConst112 = (1.0f - fConst110);
		fConst113 = std::tan((452.102844f / fConst0));
		fConst114 = (1.0f / fConst113);
		fConst115 = (fConst114 + 1.0f);
		fConst116 = (0.0f - (1.0f / (fConst113 * fConst115)));
		fConst117 = (3.14159274f / fConst0);
		fConst118 = std::tan((6283.18555f / fConst0));
		fConst119 = (1.0f / fConst118);
		fConst120 = (fConst119 + 1.0f);
		fConst121 = (1.0f / fConst120);
		fConst122 = (1.0f - fConst119);
		fConst123 = std::tan((78.5398178f / fConst0));
		fConst124 = (1.0f / fConst123);
		fConst125 = (fConst124 + 1.0f);
		fConst126 = (0.0f - (1.0f / (fConst123 * fConst125)));
		fConst127 = (1.0f / fConst125);
		fConst128 = (1.0f - fConst124);
		fConst129 = std::tan((1382.30078f / fConst0));
		fConst130 = (1.0f / fConst129);
		fConst131 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst132 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst129))));
		fConst133 = std::tan((1696.46008f / fConst0));
		fConst134 = (fConst0 * fConst133);
		fConst135 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * fConst133) * std::tan((1068.14148f / fConst0))))));
		fConst136 = (2.0f * (((2.0f * fConst134) - (0.5f * (fConst135 / fConst134))) / fConst0));
		fConst137 = (AmpMono_faustpower2_f((1.0f / fConst0)) * fConst135);
		fConst138 = (1.0f / ((fConst136 + fConst137) + 4.0f));
		fConst139 = (fConst137 + 4.0f);
		fConst140 = (fConst137 + (4.0f - fConst136));
		fConst141 = ((2.0f * fConst137) + -8.0f);
		fConst142 = (0.0f - (1.0f / (fConst118 * fConst120)));
		fConst143 = (1.0f / std::tan((50265.4844f / fConst0)));
		fConst144 = (1.0f / (fConst143 + 1.0f));
		fConst145 = (1.0f - fConst143);
		fConst146 = (1.0f / fConst115);
		fConst147 = (0.0500000007f / fConst113);
		fConst148 = (1.0f - fConst114);
		fConst149 = (1.0f / fConst108);
		fConst150 = (1.0f - fConst99);
		fConst151 = (2.0f * (1.0f - fConst104));
		fConst152 = (((fConst99 + -1.91898596f) / fConst98) + 1.0f);
		fConst153 = (((fConst99 + -1.68250704f) / fConst98) + 1.0f);
		fConst154 = (((fConst99 + -1.30972147f) / fConst98) + 1.0f);
		fConst155 = (((fConst99 + -0.830830038f) / fConst98) + 1.0f);
		fConst156 = (((fConst99 + -0.284629673f) / fConst98) + 1.0f);
		fConst157 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst91))));
		fConst158 = (((fConst92 - fConst94) / fConst91) + 1.0f);
		fConst159 = (((fConst92 + fConst96) / fConst91) + 1.0f);
		fConst160 = (((fConst86 - fConst88) / fConst85) + 1.0f);
		fConst161 = (106249.391f / fConst87);
		fConst162 = (((fConst86 + fConst161) / fConst85) + 1.0f);
		fConst163 = (((fConst86 - fConst161) / fConst85) + 1.0f);
		fConst164 = (((fConst80 - fConst82) / fConst79) + 1.0f);
		fConst165 = (974.257141f / fConst81);
		fConst166 = (((fConst80 + fConst165) / fConst79) + 1.0f);
		fConst167 = (((fConst80 - fConst165) / fConst79) + 1.0f);
		fConst168 = (((fConst74 - fConst76) / fConst73) + 1.0f);
		fConst169 = (3097.15845f / fConst75);
		fConst170 = (((fConst74 + fConst169) / fConst73) + 1.0f);
		fConst171 = (((fConst74 - fConst169) / fConst73) + 1.0f);
		fConst172 = (((fConst67 - fConst69) / fConst66) + 1.0f);
		fConst173 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst66))));
		fConst174 = (((fConst67 - fConst71) / fConst66) + 1.0f);
		fConst175 = (((fConst61 - fConst63) / fConst60) + 1.0f);
		fConst176 = (9024.73242f / fConst62);
		fConst177 = (((fConst61 + fConst176) / fConst60) + 1.0f);
		fConst178 = (((fConst61 - fConst176) / fConst60) + 1.0f);
		fConst179 = (((fConst55 - fConst57) / fConst54) + 1.0f);
		fConst180 = (4583.19189f / fConst56);
		fConst181 = (((fConst55 + fConst180) / fConst54) + 1.0f);
		fConst182 = (((fConst55 - fConst180) / fConst54) + 1.0f);
		fConst183 = (((fConst49 - fConst51) / fConst48) + 1.0f);
		fConst184 = (36783.4805f / fConst50);
		fConst185 = (((fConst49 + fConst184) / fConst48) + 1.0f);
		fConst186 = (((fConst49 - fConst184) / fConst48) + 1.0f);
		fConst187 = (((fConst42 - fConst44) / fConst41) + 1.0f);
		fConst188 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst41))));
		fConst189 = (((fConst42 - fConst46) / fConst41) + 1.0f);
		fConst190 = (((fConst36 - fConst38) / fConst35) + 1.0f);
		fConst191 = (116.345184f / fConst37);
		fConst192 = (((fConst36 + fConst191) / fConst35) + 1.0f);
		fConst193 = (((fConst36 - fConst191) / fConst35) + 1.0f);
		fConst194 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
		fConst195 = (((fConst29 - fConst31) / fConst28) + 1.0f);
		fConst196 = (((fConst29 + fConst33) / fConst28) + 1.0f);
		fConst197 = (((fConst23 - fConst25) / fConst22) + 1.0f);
		fConst198 = (183.178085f / fConst24);
		fConst199 = (((fConst23 + fConst198) / fConst22) + 1.0f);
		fConst200 = (((fConst23 - fConst198) / fConst22) + 1.0f);
		fConst201 = (((fConst16 - fConst18) / fConst15) + 1.0f);
		fConst202 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst15))));
		fConst203 = (((fConst16 + fConst20) / fConst15) + 1.0f);
		fConst204 = (((fConst10 - fConst12) / fConst9) + 1.0f);
		fConst205 = (190.645706f / fConst11);
		fConst206 = (((fConst10 + fConst205) / fConst9) + 1.0f);
		fConst207 = (((fConst10 - fConst205) / fConst9) + 1.0f);
		fConst208 = (1.0f / fConst5);
		fConst209 = (((fConst2 - fConst4) / fConst1) + 1.0f);
		fConst210 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst1))));
		fConst211 = (((fConst2 + fConst7) / fConst1) + 1.0f);

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

		zero_all();
	}

	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			fVec0[l0] = 0.0f;

		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec31[l1] = 0.0f;

		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fRec35[l2] = 0.0f;

		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec34[l3] = 0.0f;

		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec33[l4] = 0.0f;

		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec32[l5] = 0.0f;

		}
		for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
			fRec36[l6] = 0.0f;

		}
		for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
			fRec30[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec29[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec38[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec37[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec40[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec39[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec41[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec28[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec2[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec27[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec43[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec42[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec45[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec44[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec46[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec47[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec3[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec26[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec48[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fVec4[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec49[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec25[l29] = 0.0f;

		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec50[l30] = 0.0f;

		}
		for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
			fVec5[l31] = 0.0f;

		}
		for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
			fRec24[l32] = 0.0f;

		}
		for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
			fRec51[l33] = 0.0f;

		}
		for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
			fVec6[l34] = 0.0f;

		}
		for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
			fRec52[l35] = 0.0f;

		}
		for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
			fVec7[l36] = 0.0f;

		}
		for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
			fRec23[l37] = 0.0f;

		}
		for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
			fRec54[l38] = 0.0f;

		}
		for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
			fRec55[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec8[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec56[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec58[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fRec59[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fVec9[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
			fRec22[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
			fRec21[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fRec20[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec19[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec18[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec17[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec16[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec15[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec65[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec64[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec63[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec62[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec61[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec60[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec14[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 3); l60 = (l60 + 1)) {
			fRec13[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
			fRec12[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
			fRec11[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 3); l63 = (l63 + 1)) {
			fRec10[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 3); l64 = (l64 + 1)) {
			fRec9[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 3); l65 = (l65 + 1)) {
			fRec8[l65] = 0.0f;

		}
		for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
			fRec7[l66] = 0.0f;

		}
		for (int l67 = 0; (l67 < 3); l67 = (l67 + 1)) {
			fRec6[l67] = 0.0f;

		}
		for (int l68 = 0; (l68 < 3); l68 = (l68 + 1)) {
			fRec5[l68] = 0.0f;

		}
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec4[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec3[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 3); l71 = (l71 + 1)) {
			fRec2[l71] = 0.0f;

		}
		for (int l72 = 0; (l72 < 3); l72 = (l72 + 1)) {
			fRec1[l72] = 0.0f;

		}
		for (int l73 = 0; (l73 < 3); l73 = (l73 + 1)) {
			fRec0[l73] = 0.0f;

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

	void set_cab_mix(FAUSTFLOAT value) { fEntry2 = value; }
	void set_gain_slope(FAUSTFLOAT value) { fEntry12 = value; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry1 = value; }
	void set_input_level(FAUSTFLOAT value) { fEntry22 = value; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value; }
	void set_power_drive(FAUSTFLOAT value) { fEntry4 = value; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry15 = value; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry35 = value + 4.533000e-01; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry36 = value + -1.091000e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry34 = value + -1.107000e-01; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry6 = value + 5.073000e-01; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry3 = value + -2.362000e-02; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry5 = value + 2.116000e-01; }
	void set_tetrode_plate_level(FAUSTFLOAT value) { fEntry39 = value + 3.277000e-02; }
	void set_tetrode_plate_ratio(FAUSTFLOAT value) { fEntry38 = value + -1.430000e-01; }
	void set_tetrode_plate_smooth(FAUSTFLOAT value) { fEntry40 = value; }
	void set_tetrode_plate_tau(FAUSTFLOAT value) { fEntry37 = value + 1.959000e-01; }
	void set_triode_clip_level(FAUSTFLOAT value) { fEntry30 = value + 3.612000e+03; }
	void set_triode_clip_ratio(FAUSTFLOAT value) { fEntry25 = value + 1.583000e+00; }
	void set_triode_clip_smooth(FAUSTFLOAT value) { fEntry24 = value + 2.778000e+02; }
	void set_triode_clip_tau(FAUSTFLOAT value) { fEntry23 = value + -1.533000e+01; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry28 = value + 3.521000e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry29 = value + 7.121000e-01; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry27 = value + 7.747000e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry26 = value + -3.802000e-01; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry18 = value + 4.943000e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry10 = value + -1.156000e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry13 = value + -2.068000e-02; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry14 = value + 3.787000e-01; }
	void set_triode_plate_level(FAUSTFLOAT value) { fEntry33 = value + 7.368000e-04; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry16 = value + -1.179000e-01; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry11 = value + 1.343000e-02; }
	void set_triode_plate_ratio(FAUSTFLOAT value) { fEntry32 = value + -4.118000e-01; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry21 = value + 4.089000e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry19 = value + -3.789000e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry17 = value + -2.361000e-01; }
	void set_triode_plate_tau(FAUSTFLOAT value) { fEntry31 = value + -1.602000e-01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry20 = value + -4.299000e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry7 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00; }
	void set_ts_mid(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00; }
	void zero_all() {
		set_cab_mix(0.0f);
		set_gain_slope(0.0f);
		set_gain_stages(0.0f);
		set_input_level(0.0f);
		set_output_level(0.0f);
		set_power_drive(0.0f);
		set_pre_drive(0.0f);
		set_tetrode_grid_level(0.0f);
		set_tetrode_grid_ratio(0.0f);
		set_tetrode_grid_tau(0.0f);
		set_tetrode_hp_freq(0.0f);
		set_tetrode_plate_clip(0.0f);
		set_tetrode_plate_corner(0.0f);
		set_tetrode_plate_level(0.0f);
		set_tetrode_plate_ratio(0.0f);
		set_tetrode_plate_smooth(0.0f);
		set_tetrode_plate_tau(0.0f);
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
		float fSlow0 = float(fEntry1);
		float fSlow1 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f)))))) * std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow0)))));
		float fSlow2 = float(fEntry2);
		float fSlow3 = (fConst6 * fSlow2);
		float fSlow4 = (float(fEntry3) + 1.0f);
		float fSlow5 = std::exp(((3.45387769f * (float(fEntry4) + 1.0f)) + -2.30258512f));
		float fSlow6 = std::min<float>((6.25f * fSlow4), fSlow5);
		float fSlow7 = (0.0500000007f / fSlow6);
		float fSlow8 = (37.5f * fSlow4);
		float fSlow9 = std::exp(((4.60517025f * (float(fEntry5) + 1.0f)) + -2.30258512f));
		float fSlow10 = std::tan((fConst117 * std::exp(((3.45387769f * (float(fEntry6) + 1.0f)) + -2.30258512f))));
		float fSlow11 = (1.0f / fSlow10);
		float fSlow12 = (fSlow11 + 1.0f);
		float fSlow13 = (1.0f / (fSlow12 * fSlow10));
		float fSlow14 = (0.0f - fSlow13);
		float fSlow15 = (20.0f * fSlow5);
		float fSlow16 = float(fEntry7);
		float fSlow17 = ((fSlow16 < -0.800000012f)?(0.0f - (5.0f * (fSlow16 + 0.800000012f))):0.0f);
		float fSlow18 = (1.0f - fSlow17);
		float fSlow19 = float(fEntry8);
		float fSlow20 = ((fSlow19 < -0.800000012f)?(0.0f - (5.0f * (fSlow19 + 0.800000012f))):0.0f);
		float fSlow21 = (1.0f - fSlow20);
		float fSlow22 = float(fEntry9);
		float fSlow23 = ((fSlow22 < -0.800000012f)?(0.0f - (5.0f * (fSlow22 + 0.800000012f))):0.0f);
		float fSlow24 = (1.0f - fSlow23);
		float fSlow25 = (float(fEntry10) + 1.0f);
		float fSlow26 = (10.0f * fSlow25);
		float fSlow27 = float(fEntry11);
		float fSlow28 = std::pow(fSlow26, (fSlow27 + 0.5f));
		float fSlow29 = (1.0f / fSlow28);
		float fSlow30 = std::max<float>(0.0f, (std::min<float>(4.0f, fSlow0) + -3.0f));
		float fSlow31 = ((0.300000012f * (float(fEntry12) + 1.0f)) + 0.699999988f);
		float fSlow32 = AmpMono_faustpower3_f(fSlow31);
		float fSlow33 = (fSlow30 / fSlow32);
		float fSlow34 = (fSlow27 + 1.5f);
		float fSlow35 = std::pow(fSlow26, fSlow34);
		float fSlow36 = (150.0f * (float(fEntry13) + 1.0f));
		float fSlow37 = (fSlow35 + fSlow36);
		float fSlow38 = std::exp(((4.60517025f * (float(fEntry14) + 1.0f)) + -2.30258512f));
		float fSlow39 = (1.0f / fSlow38);
		float fSlow40 = (1.0f / fSlow25);
		float fSlow41 = float(fEntry15);
		float fSlow42 = ((fSlow41 <= -1.0f)?0.100000001f:std::exp((2.30258512f * (fSlow41 + 1.0f))));
		float fSlow43 = (fSlow32 / fSlow28);
		float fSlow44 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow0) + -2.0f));
		float fSlow45 = AmpMono_faustpower2_f(fSlow31);
		float fSlow46 = (fSlow44 / fSlow45);
		float fSlow47 = (fSlow45 / fSlow28);
		float fSlow48 = std::max<float>(0.0f, (std::min<float>(2.0f, fSlow0) + -1.0f));
		float fSlow49 = (fSlow48 / fSlow31);
		float fSlow50 = (37.5f * (float(fEntry16) + 1.0f));
		float fSlow51 = (fSlow35 + fSlow50);
		float fSlow52 = std::exp(((3.45387769f * (float(fEntry17) + 1.0f)) + -2.30258512f));
		float fSlow53 = (fSlow36 + fSlow52);
		float fSlow54 = (fSlow34 * fSlow28);
		float fSlow55 = std::tan((fConst117 * std::exp(((3.45387769f * (float(fEntry18) + 1.0f)) + -2.30258512f))));
		float fSlow56 = (1.0f / fSlow55);
		float fSlow57 = (fSlow56 + 1.0f);
		float fSlow58 = (0.0f - (1.0f / (fSlow55 * fSlow57)));
		float fSlow59 = std::exp(((3.45387769f * (float(fEntry19) + 1.0f)) + -2.30258512f));
		float fSlow60 = std::exp(((4.60517025f * (float(fEntry20) + 1.0f)) + -9.2103405f));
		float fSlow61 = (1.0f - (1.0f / ((fConst0 * (fSlow60 * std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -2.99573231f)))) + 1.0f)));
		float fSlow62 = (1.0f / ((fConst0 * fSlow60) + 1.0f));
		float fSlow63 = (fSlow31 / fSlow28);
		float fSlow64 = std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry22) + 1.0f))))));
		float fSlow65 = (1.0f / fSlow57);
		float fSlow66 = (1.0f - fSlow56);
		float fSlow67 = (fSlow64 / fSlow55);
		float fSlow68 = std::exp(((4.60517025f * (float(fEntry23) + 1.0f)) + -18.420681f));
		float fSlow69 = (1.0f / ((fConst0 * (fSlow68 * std::exp(((6.90775537f * (float(fEntry24) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow70 = (1.0f - fSlow69);
		float fSlow71 = (1.0f - (1.0f / ((fConst0 * (fSlow68 * std::exp(((5.75646257f * (float(fEntry25) + 1.0f)) + -2.30258512f)))) + 1.0f)));
		float fSlow72 = (1.0f / ((fConst0 * fSlow68) + 1.0f));
		float fSlow73 = std::exp(((3.45387769f * (float(fEntry26) + 1.0f)) + -13.8155107f));
		float fSlow74 = (1.0f / ((fConst0 * (fSlow73 * std::exp(((6.90775537f * (float(fEntry27) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow75 = (1.0f - fSlow74);
		float fSlow76 = (1.0f / ((fConst0 * fSlow73) + 1.0f));
		float fSlow77 = (5.0f * (1.0f - (float(fEntry28) + 1.0f)));
		float fSlow78 = (1.0f / ((fConst0 * (fSlow73 * std::exp(((5.75646257f * (float(fEntry29) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow79 = (1.0f - fSlow78);
		float fSlow80 = float(fEntry30);
		float fSlow81 = (fSlow38 + fSlow37);
		float fSlow82 = std::exp(((4.60517025f * (float(fEntry31) + 1.0f)) + -9.2103405f));
		float fSlow83 = (1.0f - (1.0f / ((fConst0 * (fSlow82 * std::exp(((4.60517025f * (float(fEntry32) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow84 = (1.0f / ((fConst0 * fSlow82) + 1.0f));
		float fSlow85 = (75.0f * (float(fEntry33) + 1.0f));
		float fSlow86 = (1.0f / fSlow52);
		float fSlow87 = std::min<float>((0.5f * (fSlow26 + (300.0f - fSlow36))), fSlow42);
		float fSlow88 = (fSlow55 * fSlow28);
		float fSlow89 = (fSlow31 / fSlow88);
		float fSlow90 = (1.0f / fSlow88);
		float fSlow91 = (fSlow78 + -1.0f);
		float fSlow92 = (1.0f - fSlow48);
		float fSlow93 = (fSlow34 * fSlow45);
		float fSlow94 = (1.0f - fSlow44);
		float fSlow95 = (fSlow34 * fSlow32);
		float fSlow96 = (1.0f - fSlow30);
		int iSlow97 = (fSlow22 > 0.0f);
		float fSlow98 = std::tan((fConst117 * float((iSlow97?100:50))));
		float fSlow99 = (1.0f / fSlow98);
		float fSlow100 = (fSlow99 + 1.0f);
		float fSlow101 = (0.0f - (1.0f / (fSlow98 * fSlow100)));
		float fSlow102 = (1.0f - fSlow99);
		float fSlow103 = (fSlow98 * fSlow87);
		float fSlow104 = (iSlow97?((5.0f * fSlow22) + 13.0f):((18.0f * fSlow22) + 13.0f));
		float fSlow105 = std::pow(10.0f, (0.0500000007f * fSlow104));
		float fSlow106 = ((fSlow19 > 0.0f)?((13.0f * fSlow19) + -3.0f):((5.0f * fSlow19) + -3.0f));
		int iSlow107 = (fSlow106 > 0.0f);
		float fSlow108 = (fConst131 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow106))));
		float fSlow109 = (iSlow107?fConst131:fSlow108);
		float fSlow110 = ((fConst130 * (fConst130 - fSlow109)) + 1.0f);
		float fSlow111 = ((fConst130 * (fConst130 + fSlow109)) + 1.0f);
		float fSlow112 = (iSlow107?fSlow108:fConst131);
		float fSlow113 = ((fConst130 * (fConst130 - fSlow112)) + 1.0f);
		float fSlow114 = ((fConst130 * (fConst130 + fSlow112)) + 1.0f);
		float fSlow115 = ((fSlow16 > 0.0f)?((10.0f * fSlow16) + 13.0f):((18.0f * fSlow16) + 13.0f));
		float fSlow116 = std::pow(10.0f, (0.0500000007f * fSlow115));
		float fSlow117 = std::pow(10.0f, (0.0f - (0.0500000007f * (((0.600000024f * fSlow106) + (0.400000006f * fSlow104)) + (0.200000003f * fSlow115)))));
		float fSlow118 = (1.0f / fSlow12);
		float fSlow119 = (20.0f * (fSlow5 / fSlow10));
		float fSlow120 = (1.0f - fSlow11);
		float fSlow121 = std::exp(((4.60517025f * (float(fEntry34) + 1.0f)) + -11.5129251f));
		float fSlow122 = (1.0f / ((fConst0 * fSlow121) + 1.0f));
		float fSlow123 = (100.0f * (1.0f - (float(fEntry35) + 1.0f)));
		float fSlow124 = (1.0f - (1.0f / ((fConst0 * (fSlow121 * std::exp(((5.75646257f * (float(fEntry36) + 1.0f)) + -2.30258512f)))) + 1.0f)));
		float fSlow125 = (1.0f / fSlow9);
		float fSlow126 = std::exp(((4.60517025f * (float(fEntry37) + 1.0f)) + -9.2103405f));
		float fSlow127 = (1.0f - (1.0f / ((fConst0 * (fSlow126 * std::exp(((4.60517025f * (float(fEntry38) + 1.0f)) + -4.60517025f)))) + 1.0f)));
		float fSlow128 = (1.0f / ((fConst0 * fSlow126) + 1.0f));
		float fSlow129 = (100.0f * (1.0f - (float(fEntry39) + 1.0f)));
		float fSlow130 = std::exp(((2.30258512f * (float(fEntry40) + 1.0f)) + -2.30258512f));
		float fSlow131 = (1.0f / fSlow130);
		float fSlow132 = (fSlow120 / fSlow12);
		float fSlow133 = (fConst147 / fSlow6);
		float fSlow134 = (0.0500000007f * ((1.0f - fSlow2) / fSlow6));
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = (float(input0[i]) * fSlow42);
			fVec0[0] = (fSlow64 * fTemp0);
			fRec31[0] = ((fSlow58 * fVec0[1]) - (fSlow65 * ((fSlow66 * fRec31[1]) - (fSlow67 * fTemp0))));
			fRec35[0] = ((fSlow76 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow77 + fRec31[0])) - fRec35[1]))) + (fSlow79 * fRec35[1]));
			fRec34[0] = ((fSlow75 * fRec34[1]) + (fSlow74 * fRec35[0]));
			fRec33[0] = ((fSlow71 * fRec33[1]) + (fSlow72 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec31[0] + (-2.0f - fRec34[0])) - fSlow80)) - fRec33[1]))));
			fRec32[0] = ((fSlow70 * fRec32[1]) + (fSlow69 * fRec33[0]));
			float fTemp1 = (fRec31[0] - (fRec32[0] + fRec34[0]));
			float fTemp2 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp1)) + -0.0500000007f)));
			float fTemp3 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp1)), fSlow34) - fSlow35) * fTemp2) + (fSlow54 * ((1.0f - fTemp2) * fTemp1)))) - fSlow81);
			float fTemp4 = ((fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp3))))) + 1.0f)) + std::max<float>(0.0f, fTemp3));
			fRec36[0] = ((fSlow83 * fRec36[1]) + (fSlow84 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp4 + -200.0f) - fSlow85))) - fRec36[1]))));
			fRec30[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp4 + (-250.0f - fRec36[0])) - fSlow50))) - fRec30[1]))) + (fSlow61 * fRec30[1]));
			float fTemp5 = (fSlow59 * fRec30[0]);
			float fTemp6 = (fSlow53 + ((fTemp4 + (-250.0f - (fRec36[0] + fTemp5))) - fSlow50));
			float fTemp7 = (fSlow51 + (((fTemp5 + std::min<float>(0.0f, fTemp6)) + (fSlow52 * (float(tanhf(float((fSlow86 * std::max<float>(0.0f, fTemp6))))) + -1.0f))) + -50.0f));
			float fTemp8 = ((fSlow42 * fTemp7) / fSlow87);
			fVec1[0] = (fSlow63 * fTemp8);
			fRec29[0] = ((fSlow58 * fVec1[1]) - (fSlow65 * ((fSlow66 * fRec29[1]) - (fSlow89 * fTemp8))));
			fRec38[0] = ((fSlow76 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow77 + fRec29[0])) - fRec38[1]))) + (fSlow79 * fRec38[1]));
			fRec37[0] = ((fSlow75 * fRec37[1]) + (fSlow74 * fRec38[0]));
			fRec40[0] = ((fSlow71 * fRec40[1]) + (fSlow72 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec29[0] + (-2.0f - fRec37[0])) - fSlow80)) - fRec40[1]))));
			fRec39[0] = ((fSlow70 * fRec39[1]) + (fSlow69 * fRec40[0]));
			float fTemp9 = (fRec29[0] - (fRec37[0] + fRec39[0]));
			float fTemp10 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp9)) + -0.0500000007f)));
			float fTemp11 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp9)), fSlow34) - fSlow35) * fTemp10) + (fSlow54 * (fTemp9 * (1.0f - fTemp10))))) - fSlow81);
			float fTemp12 = (std::max<float>(0.0f, fTemp11) + (fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp11))))) + 1.0f)));
			fRec41[0] = ((fSlow83 * fRec41[1]) + (fSlow84 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp12 + -200.0f) - fSlow85))) - fRec41[1]))));
			fRec28[0] = ((fSlow61 * fRec28[1]) + (fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp12 + (-250.0f - fRec41[0])) - fSlow50))) - fRec28[1]))));
			float fTemp13 = (fSlow59 * fRec28[0]);
			float fTemp14 = (fSlow53 + ((fTemp12 + (-250.0f - (fRec41[0] + fTemp13))) - fSlow50));
			float fTemp15 = ((fSlow42 * (fSlow51 + ((fTemp13 + std::min<float>(0.0f, fTemp14)) + (-50.0f - (fSlow52 * (1.0f - float(tanhf(float((fSlow86 * std::max<float>(0.0f, fTemp14))))))))))) / fSlow87);
			fVec2[0] = (fSlow29 * fTemp15);
			fRec27[0] = ((fSlow58 * fVec2[1]) - (fSlow65 * ((fSlow66 * fRec27[1]) - (fSlow90 * fTemp15))));
			fRec43[0] = ((fSlow76 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow77 + fRec27[0])) - fRec43[1]))) - (fSlow91 * fRec43[1]));
			fRec42[0] = ((fSlow74 * fRec43[0]) + (fSlow75 * fRec42[1]));
			fRec45[0] = ((fSlow72 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec27[0] + (-2.0f - fRec42[0])) - fSlow80)) - fRec45[1]))) + (fSlow71 * fRec45[1]));
			fRec44[0] = ((fSlow70 * fRec44[1]) + (fSlow69 * fRec45[0]));
			float fTemp16 = (fRec27[0] - (fRec42[0] + fRec44[0]));
			float fTemp17 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp16)) + -0.0500000007f)));
			float fTemp18 = ((300.0f - ((fSlow54 * ((1.0f - fTemp17) * fTemp16)) + ((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp16)), fSlow34) - fSlow35) * fTemp17))) - fSlow81);
			float fTemp19 = (std::max<float>(0.0f, fTemp18) + (fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp18))))) + 1.0f)));
			fRec46[0] = ((fSlow84 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp19 + -200.0f) - fSlow85))) - fRec46[1]))) + (fSlow83 * fRec46[1]));
			fRec47[0] = ((fSlow62 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow36 + ((fTemp19 + (-250.0f - fRec46[0])) - fSlow50))) - fRec47[1]))) + (fSlow61 * fRec47[1]));
			float fTemp20 = (fSlow59 * fRec47[0]);
			float fTemp21 = (fSlow53 + ((fTemp19 + (-250.0f - (fRec46[0] + fTemp20))) - fSlow50));
			float fTemp22 = ((fSlow49 * (fSlow51 + ((std::min<float>(0.0f, fTemp21) + fTemp20) + (-50.0f - (fSlow52 * (1.0f - float(tanhf(float((fSlow86 * std::max<float>(0.0f, fTemp21))))))))))) + (fSlow92 * fTemp7));
			float fTemp23 = (fSlow47 * ((fSlow42 * fTemp22) / fSlow87));
			float fTemp24 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp23)) + -0.0500000007f)));
			float fTemp25 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp23)), fSlow34) - fSlow35) * fTemp24) + (fSlow93 * (((fSlow42 * (1.0f - fTemp24)) * fTemp22) / fSlow87)))) - fSlow81);
			float fTemp26 = (fSlow42 * (fSlow37 + (((fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp25))))) + 1.0f)) + std::max<float>(0.0f, fTemp25)) + -300.0f)));
			float fTemp27 = (fSlow29 * (fTemp26 / fSlow87));
			float fTemp28 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp27)) + -0.0500000007f)));
			float fTemp29 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp27)), fSlow34) - fSlow35) * fTemp28) + (fSlow34 * ((fTemp26 * (1.0f - fTemp28)) / fSlow87)))) - fSlow81);
			float fTemp30 = ((fSlow46 * (fSlow37 + ((std::max<float>(0.0f, fTemp29) + (fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp29))))) + 1.0f))) + -300.0f))) + (fSlow94 * fTemp22));
			float fTemp31 = (fSlow42 * fTemp30);
			float fTemp32 = (fSlow43 * (fTemp31 / fSlow87));
			float fTemp33 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp32)) + -0.0500000007f)));
			float fTemp34 = ((300.0f - (((std::pow(std::max<float>(0.0f, (fSlow26 + fTemp32)), fSlow34) - fSlow35) * fTemp33) + (fSlow95 * ((fTemp31 * (1.0f - fTemp33)) / fSlow87)))) - fSlow81);
			float fTemp35 = (fSlow42 * (fSlow37 + ((std::max<float>(0.0f, fTemp34) + (fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp34))))) + 1.0f))) + -300.0f)));
			float fTemp36 = (fSlow29 * (fTemp35 / fSlow87));
			float fTemp37 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow40 * std::fabs(fTemp36)) + -0.0500000007f)));
			float fTemp38 = ((300.0f - ((fTemp37 * (std::pow(std::max<float>(0.0f, (fSlow26 + fTemp36)), fSlow34) - fSlow35)) + (fSlow34 * ((fTemp35 * (1.0f - fTemp37)) / fSlow87)))) - fSlow81);
			float fTemp39 = ((fSlow33 * (fSlow37 + (((fSlow38 * (float(tanhf(float((fSlow39 * std::min<float>(0.0f, fTemp38))))) + 1.0f)) + std::max<float>(0.0f, fTemp38)) + -300.0f))) + (fSlow96 * fTemp30));
			float fTemp40 = (fSlow29 * (fTemp39 / fSlow87));
			fVec3[0] = fTemp40;
			fRec26[0] = ((fVec3[1] * fSlow101) - (((fSlow102 * fRec26[1]) - (fSlow29 * (fTemp39 / fSlow103))) / fSlow100));
			fRec48[0] = (0.0f - (((fSlow102 * fRec48[1]) - (fTemp40 + fVec3[1])) / fSlow100));
			float fTemp41 = (fRec26[0] + (fRec48[0] * fSlow105));
			fVec4[0] = fTemp41;
			fRec49[0] = ((fConst126 * fVec4[1]) - (fConst127 * ((fConst128 * fRec49[1]) - (fConst124 * fTemp41))));
			float fTemp42 = (fConst132 * fRec25[1]);
			fRec25[0] = (((fSlow24 * fTemp41) + (fRec49[0] * fSlow23)) - (((fSlow110 * fRec25[2]) + fTemp42) / fSlow111));
			float fTemp43 = ((fRec25[2] * fSlow113) + (fTemp42 + (fRec25[0] * fSlow114)));
			float fTemp44 = (fConst141 * fRec50[1]);
			fRec50[0] = ((fTemp43 / fSlow111) - (fConst138 * ((fConst140 * fRec50[2]) + fTemp44)));
			float fTemp45 = (((fSlow21 * fTemp43) / fSlow111) + (fConst138 * (fSlow20 * ((fConst139 * fRec50[2]) + (fTemp44 + (fConst139 * fRec50[0]))))));
			fVec5[0] = fTemp45;
			fRec24[0] = (0.0f - (fConst121 * ((fConst122 * fRec24[1]) - (fVec5[1] + fTemp45))));
			fRec51[0] = ((fConst142 * fVec5[1]) - (fConst121 * ((fConst122 * fRec51[1]) - (fConst119 * fTemp45))));
			float fTemp46 = (fRec24[0] + (fRec51[0] * fSlow116));
			fVec6[0] = fTemp46;
			fRec52[0] = (fConst144 * ((fVec6[1] + fTemp46) - (fConst145 * fRec52[1])));
			float fTemp47 = (((fSlow18 * fTemp46) + (fRec52[0] * fSlow17)) * fSlow117);
			fVec7[0] = (fSlow15 * fTemp47);
			fRec23[0] = ((fSlow14 * fVec7[1]) + (fSlow118 * ((fSlow119 * fTemp47) - (fSlow120 * fRec23[1]))));
			fRec54[0] = ((fSlow122 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow123 + fRec23[0])) - fRec54[1]))) + (fSlow124 * fRec54[1]));
			float fRec53 = fRec54[0];
			float fTemp48 = (fSlow9 + ((fRec23[0] - fRec53) - fSlow8));
			float fTemp49 = std::max<float>(0.0f, (fSlow8 + (std::min<float>(0.0f, fTemp48) - (fSlow9 * (1.0f - float(tanhf(float((fSlow125 * std::max<float>(0.0f, fTemp48))))))))));
			fRec55[0] = ((fSlow127 * fRec55[1]) + (fSlow128 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow129 + fTemp49)) - fRec55[1]))));
			float fTemp50 = ((fTemp49 - fRec55[0]) - fSlow130);
			float fTemp51 = (0.0f - (fSlow5 * fTemp47));
			fVec8[0] = fTemp51;
			fRec56[0] = ((20.0f * ((fSlow13 * fTemp51) + (fSlow14 * fVec8[1]))) - (fSlow132 * fRec56[1]));
			fRec58[0] = ((fSlow122 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow123 + fRec56[0])) - fRec58[1]))) + (fSlow124 * fRec58[1]));
			float fRec57 = fRec58[0];
			float fTemp52 = (fSlow9 + ((fRec56[0] - fRec57) - fSlow8));
			float fTemp53 = std::max<float>(0.0f, (fSlow8 + ((fSlow9 * (float(tanhf(float((fSlow125 * std::max<float>(0.0f, fTemp52))))) + -1.0f)) + std::min<float>(0.0f, fTemp52))));
			fRec59[0] = ((fSlow128 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow129 + fTemp53)) - fRec59[1]))) + (fSlow127 * fRec59[1]));
			float fTemp54 = ((fTemp53 - fRec59[0]) - fSlow130);
			float fTemp55 = ((std::max<float>(0.0f, fTemp50) + (fSlow130 * (float(tanhf(float((fSlow131 * std::min<float>(0.0f, fTemp50))))) + 1.0f))) - ((fSlow130 * (float(tanhf(float((fSlow131 * std::min<float>(0.0f, fTemp54))))) + 1.0f)) + std::max<float>(0.0f, fTemp54)));
			fVec9[0] = (fSlow7 * fTemp55);
			fRec22[0] = ((fConst116 * fVec9[1]) + (fConst146 * ((fSlow133 * fTemp55) - (fConst148 * fRec22[1]))));
			fRec21[0] = (0.0f - (fConst111 * ((fConst112 * fRec21[1]) - (fRec22[0] + fRec22[1]))));
			fRec20[0] = ((fConst109 * fRec21[1]) - (fConst149 * ((fConst150 * fRec20[1]) - (fConst99 * fRec21[0]))));
			fRec19[0] = (fRec20[0] - (fConst107 * ((fConst151 * fRec19[1]) + (fConst152 * fRec19[2]))));
			fRec18[0] = ((fConst107 * ((fConst104 * fRec19[2]) + ((fConst104 * fRec19[0]) + (fConst102 * fRec19[1])))) - (fConst106 * ((fConst153 * fRec18[2]) + (fConst151 * fRec18[1]))));
			fRec17[0] = ((fConst106 * ((fConst104 * fRec18[2]) + ((fConst102 * fRec18[1]) + (fConst104 * fRec18[0])))) - (fConst105 * ((fConst154 * fRec17[2]) + (fConst151 * fRec17[1]))));
			fRec16[0] = ((fConst105 * (((fConst104 * fRec17[0]) + (fConst102 * fRec17[1])) + (fConst104 * fRec17[2]))) - (fConst103 * ((fConst155 * fRec16[2]) + (fConst151 * fRec16[1]))));
			fRec15[0] = ((fConst103 * ((fConst104 * fRec16[2]) + ((fConst104 * fRec16[0]) + (fConst102 * fRec16[1])))) - (fConst100 * ((fConst151 * fRec15[1]) + (fConst156 * fRec15[2]))));
			fRec65[0] = (fConst149 * ((fRec21[0] + fRec21[1]) - (fConst150 * fRec65[1])));
			fRec64[0] = (fRec65[0] - (fConst107 * ((fConst152 * fRec64[2]) + (fConst151 * fRec64[1]))));
			fRec63[0] = ((fConst107 * (fRec64[2] + (fRec64[0] + (2.0f * fRec64[1])))) - (fConst106 * ((fConst151 * fRec63[1]) + (fConst153 * fRec63[2]))));
			fRec62[0] = ((fConst106 * (fRec63[2] + (fRec63[0] + (2.0f * fRec63[1])))) - (fConst105 * ((fConst151 * fRec62[1]) + (fConst154 * fRec62[2]))));
			fRec61[0] = ((fConst105 * (fRec62[2] + (fRec62[0] + (2.0f * fRec62[1])))) - (fConst103 * ((fConst151 * fRec61[1]) + (fConst155 * fRec61[2]))));
			fRec60[0] = ((fConst103 * (fRec61[2] + (fRec61[0] + (2.0f * fRec61[1])))) - (fConst100 * ((fConst156 * fRec60[2]) + (fConst151 * fRec60[1]))));
			float fTemp56 = (fConst157 * fRec14[1]);
			fRec14[0] = ((fConst100 * ((0.13673377f * (((fConst102 * fRec15[1]) + (fConst104 * fRec15[0])) + (fConst104 * fRec15[2]))) + (fRec60[2] + (fRec60[0] + (2.0f * fRec60[1]))))) - (fConst95 * (fTemp56 + (fConst158 * fRec14[2]))));
			float fTemp57 = (fConst90 * fRec13[1]);
			fRec13[0] = ((fConst95 * ((fConst97 * fRec14[2]) + (fTemp56 + (fConst159 * fRec14[0])))) - (fConst89 * ((fConst160 * fRec13[2]) + fTemp57)));
			float fTemp58 = (fConst84 * fRec12[1]);
			fRec12[0] = ((fConst89 * ((fTemp57 + (fConst162 * fRec13[0])) + (fConst163 * fRec13[2]))) - (fConst83 * ((fConst164 * fRec12[2]) + fTemp58)));
			float fTemp59 = (fConst78 * fRec11[1]);
			fRec11[0] = ((fConst83 * ((fTemp58 + (fConst166 * fRec12[0])) + (fConst167 * fRec12[2]))) - (fConst77 * (fTemp59 + (fConst168 * fRec11[2]))));
			float fTemp60 = (fConst173 * fRec10[1]);
			fRec10[0] = ((fConst77 * ((fTemp59 + (fConst170 * fRec11[0])) + (fConst171 * fRec11[2]))) - (fConst70 * ((fConst172 * fRec10[2]) + fTemp60)));
			float fTemp61 = (fConst65 * fRec9[1]);
			fRec9[0] = ((fConst70 * (((fConst72 * fRec10[0]) + fTemp60) + (fConst174 * fRec10[2]))) - (fConst64 * (fTemp61 + (fConst175 * fRec9[2]))));
			float fTemp62 = (fConst59 * fRec8[1]);
			fRec8[0] = ((fConst64 * ((fTemp61 + (fConst177 * fRec9[0])) + (fConst178 * fRec9[2]))) - (fConst58 * ((fConst179 * fRec8[2]) + fTemp62)));
			float fTemp63 = (fConst53 * fRec7[1]);
			fRec7[0] = ((fConst58 * ((fTemp62 + (fConst181 * fRec8[0])) + (fConst182 * fRec8[2]))) - (fConst52 * ((fConst183 * fRec7[2]) + fTemp63)));
			float fTemp64 = (fConst188 * fRec6[1]);
			fRec6[0] = ((fConst52 * ((fTemp63 + (fConst185 * fRec7[0])) + (fConst186 * fRec7[2]))) - (fConst45 * ((fConst187 * fRec6[2]) + fTemp64)));
			float fTemp65 = (fConst40 * fRec5[1]);
			fRec5[0] = ((fConst45 * (((fConst47 * fRec6[0]) + fTemp64) + (fConst189 * fRec6[2]))) - (fConst39 * (fTemp65 + (fConst190 * fRec5[2]))));
			float fTemp66 = (fConst194 * fRec4[1]);
			fRec4[0] = ((fConst39 * ((fTemp65 + (fConst192 * fRec5[0])) + (fConst193 * fRec5[2]))) - (fConst32 * (fTemp66 + (fConst195 * fRec4[2]))));
			float fTemp67 = (fConst27 * fRec3[1]);
			fRec3[0] = ((fConst32 * ((fConst34 * fRec4[2]) + (fTemp66 + (fConst196 * fRec4[0])))) - (fConst26 * ((fConst197 * fRec3[2]) + fTemp67)));
			float fTemp68 = (fConst202 * fRec2[1]);
			fRec2[0] = ((fConst26 * ((fTemp67 + (fConst199 * fRec3[0])) + (fConst200 * fRec3[2]))) - (fConst19 * ((fConst201 * fRec2[2]) + fTemp68)));
			float fTemp69 = (fConst14 * fRec1[1]);
			fRec1[0] = ((fConst19 * ((fConst21 * fRec2[2]) + (fTemp68 + (fConst203 * fRec2[0])))) - (fConst13 * ((fConst204 * fRec1[2]) + fTemp69)));
			float fTemp70 = (fConst210 * fRec0[1]);
			fRec0[0] = ((fConst13 * ((fTemp69 + (fConst206 * fRec1[0])) + (fConst207 * fRec1[2]))) - (fConst208 * ((fConst209 * fRec0[2]) + fTemp70)));
			output0[i] = FAUSTFLOAT((fSlow1 * ((fSlow3 * ((fConst8 * fRec0[2]) + (fTemp70 + (fConst211 * fRec0[0])))) + (fSlow134 * fTemp55))));
			fVec0[1] = fVec0[0];
			fRec31[1] = fRec31[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec36[1] = fRec36[0];
			fRec30[1] = fRec30[0];
			fVec1[1] = fVec1[0];
			fRec29[1] = fRec29[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec41[1] = fRec41[0];
			fRec28[1] = fRec28[0];
			fVec2[1] = fVec2[0];
			fRec27[1] = fRec27[0];
			fRec43[1] = fRec43[0];
			fRec42[1] = fRec42[0];
			fRec45[1] = fRec45[0];
			fRec44[1] = fRec44[0];
			fRec46[1] = fRec46[0];
			fRec47[1] = fRec47[0];
			fVec3[1] = fVec3[0];
			fRec26[1] = fRec26[0];
			fRec48[1] = fRec48[0];
			fVec4[1] = fVec4[0];
			fRec49[1] = fRec49[0];
			fRec25[2] = fRec25[1];
			fRec25[1] = fRec25[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fVec5[1] = fVec5[0];
			fRec24[1] = fRec24[0];
			fRec51[1] = fRec51[0];
			fVec6[1] = fVec6[0];
			fRec52[1] = fRec52[0];
			fVec7[1] = fVec7[0];
			fRec23[1] = fRec23[0];
			fRec54[1] = fRec54[0];
			fRec55[1] = fRec55[0];
			fVec8[1] = fVec8[0];
			fRec56[1] = fRec56[0];
			fRec58[1] = fRec58[0];
			fRec59[1] = fRec59[0];
			fVec9[1] = fVec9[0];
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
