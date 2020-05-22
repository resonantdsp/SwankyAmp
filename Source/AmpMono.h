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
	FAUSTFLOAT fEntry11;
	FAUSTFLOAT fEntry12;
	FAUSTFLOAT fEntry13;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	float fConst6;
	float fConst7;
	float fConst8;
	float fConst9;
	float fConst10;
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
	float fRec8[2];
	FAUSTFLOAT fEntry25;
	FAUSTFLOAT fEntry26;
	FAUSTFLOAT fEntry27;
	FAUSTFLOAT fEntry28;
	float fRec10[2];
	float fRec9[2];
	FAUSTFLOAT fEntry29;
	FAUSTFLOAT fEntry30;
	FAUSTFLOAT fEntry31;
	FAUSTFLOAT fEntry32;
	float fRec12[2];
	float fRec11[2];
	FAUSTFLOAT fEntry33;
	FAUSTFLOAT fEntry34;
	float fRec7[2];
	FAUSTFLOAT fEntry35;
	FAUSTFLOAT fEntry36;
	float fRec6[2];
	FAUSTFLOAT fEntry37;
	FAUSTFLOAT fEntry38;
	float fVec1[2];
	float fRec17[2];
	float fRec19[2];
	float fRec18[2];
	float fRec21[2];
	float fRec20[2];
	float fRec16[2];
	float fRec15[2];
	float fVec2[2];
	float fRec14[2];
	float fRec25[2];
	float fRec24[2];
	float fRec23[2];
	float fRec22[2];
	float fRec13[2];
	float fRec26[2];
	float fVec3[2];
	float fRec31[2];
	float fRec33[2];
	float fRec32[2];
	float fRec35[2];
	float fRec34[2];
	float fRec30[2];
	float fRec36[2];
	float fVec4[2];
	float fRec29[2];
	float fRec38[2];
	float fRec37[2];
	float fRec40[2];
	float fRec39[2];
	float fRec28[2];
	float fRec27[2];
	float fVec5[2];
	float fRec5[2];
	float fRec41[2];
	float fVec6[2];
	float fConst11;
	float fConst12;
	float fRec4[2];
	float fConst13;
	float fConst14;
	float fConst15;
	float fConst16;
	float fRec3[3];
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
	float fRec42[3];
	float fVec7[2];
	float fRec2[2];
	float fConst27;
	float fRec43[2];
	float fVec8[2];
	float fConst28;
	float fConst29;
	float fConst30;
	float fRec44[2];
	FAUSTFLOAT fEntry39;
	float fVec9[2];
	float fRec1[2];
	FAUSTFLOAT fEntry40;
	FAUSTFLOAT fEntry41;
	FAUSTFLOAT fEntry42;
	FAUSTFLOAT fEntry43;
	FAUSTFLOAT fEntry44;
	float fRec47[2];
	float fRec46[2];
	FAUSTFLOAT fEntry45;
	FAUSTFLOAT fEntry46;
	FAUSTFLOAT fEntry47;
	FAUSTFLOAT fEntry48;
	float fRec49[2];
	FAUSTFLOAT fEntry49;
	float fVec10[2];
	float fRec0[2];
	float fRec52[2];
	float fVec11[2];
	float fRec50[2];
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
	float fRec75[2];
	float fRec74[2];
	float fRec73[2];
	float fConst149;
	float fConst150;
	float fConst151;
	float fConst152;
	float fRec72[3];
	float fConst153;
	float fRec71[3];
	float fConst154;
	float fRec70[3];
	float fConst155;
	float fRec69[3];
	float fConst156;
	float fRec68[3];
	float fConst157;
	float fConst158;
	float fRec81[2];
	float fRec80[3];
	float fRec79[3];
	float fRec78[3];
	float fRec77[3];
	float fRec76[3];
	float fConst159;
	float fRec67[3];
	float fConst160;
	float fConst161;
	float fConst162;
	float fConst163;
	float fRec66[3];
	float fConst164;
	float fConst165;
	float fConst166;
	float fConst167;
	float fRec65[3];
	float fConst168;
	float fConst169;
	float fConst170;
	float fConst171;
	float fRec64[3];
	float fConst172;
	float fConst173;
	float fConst174;
	float fConst175;
	float fConst176;
	float fRec63[3];
	float fConst177;
	float fConst178;
	float fConst179;
	float fRec62[3];
	float fConst180;
	float fConst181;
	float fConst182;
	float fRec61[3];
	float fConst183;
	float fConst184;
	float fConst185;
	float fRec60[3];
	float fConst186;
	float fConst187;
	float fConst188;
	float fRec59[3];
	float fConst189;
	float fConst190;
	float fConst191;
	float fRec58[3];
	float fConst192;
	float fConst193;
	float fConst194;
	float fRec57[3];
	float fConst195;
	float fConst196;
	float fRec56[3];
	float fConst197;
	float fConst198;
	float fConst199;
	float fConst200;
	float fRec55[3];
	float fConst201;
	float fConst202;
	float fConst203;
	float fConst204;
	float fRec54[3];
	float fConst205;
	float fConst206;
	float fConst207;
	float fConst208;
	float fConst209;
	float fRec53[3];
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
		fConst6 = (1.0f - fConst3);
		fConst7 = std::tan((78.5398178f / fConst0));
		fConst8 = (1.0f / fConst7);
		fConst9 = (fConst8 + 1.0f);
		fConst10 = (1.0f / fConst9);
		fConst11 = (1.0f - fConst8);
		fConst12 = (0.0f - (1.0f / (fConst7 * fConst9)));
		fConst13 = std::tan((1382.30078f / fConst0));
		fConst14 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst13))));
		fConst15 = (1.0f / fConst13);
		fConst16 = (3141.59277f / (fConst0 * std::sin((2764.60156f / fConst0))));
		fConst17 = (1.0f / fConst0);
		fConst18 = std::tan((1696.46008f / fConst0));
		fConst19 = AmpMono_faustpower2_f(std::sqrt((4.0f * ((AmpMono_faustpower2_f(fConst0) * std::tan((1068.14148f / fConst0))) * fConst18))));
		fConst20 = (AmpMono_faustpower2_f(fConst17) * fConst19);
		fConst21 = (fConst0 * fConst18);
		fConst22 = (2.0f * (((2.0f * fConst21) - (0.5f * (fConst19 / fConst21))) / fConst0));
		fConst23 = (1.0f / ((fConst20 + fConst22) + 4.0f));
		fConst24 = (fConst20 + 4.0f);
		fConst25 = ((2.0f * fConst20) + -8.0f);
		fConst26 = (fConst20 + (4.0f - fConst22));
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
		fConst43 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst38))));
		fConst44 = std::tan((3537.37793f / fConst0));
		fConst45 = (1.0f / fConst44);
		fConst46 = (fConst0 * std::sin((7074.75586f / fConst0)));
		fConst47 = (642.945251f / fConst46);
		fConst48 = (1.0f / (((fConst45 + fConst47) / fConst44) + 1.0f));
		fConst49 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst44))));
		fConst50 = std::tan((3081.90234f / fConst0));
		fConst51 = (1.0f / fConst50);
		fConst52 = (fConst0 * std::sin((6163.80469f / fConst0)));
		fConst53 = (486.410919f / fConst52);
		fConst54 = (1.0f / (((fConst51 + fConst53) / fConst50) + 1.0f));
		fConst55 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst50))));
		fConst56 = std::tan((2592.47217f / fConst0));
		fConst57 = (1.0f / fConst56);
		fConst58 = (fConst0 * std::sin((5184.94434f / fConst0)));
		fConst59 = (317.628265f / fConst58);
		fConst60 = (1.0f / (((fConst57 + fConst59) / fConst56) + 1.0f));
		fConst61 = (148.323349f / fConst58);
		fConst62 = (((fConst57 - fConst61) / fConst56) + 1.0f);
		fConst63 = std::tan((1891.23853f / fConst0));
		fConst64 = (1.0f / fConst63);
		fConst65 = (fConst0 * std::sin((3782.47705f / fConst0)));
		fConst66 = (265.978119f / fConst65);
		fConst67 = (1.0f / (((fConst64 + fConst66) / fConst63) + 1.0f));
		fConst68 = (116.345184f / fConst65);
		fConst69 = (((fConst64 - fConst68) / fConst63) + 1.0f);
		fConst70 = std::tan((21179.4824f / fConst0));
		fConst71 = (1.0f / fConst70);
		fConst72 = (fConst0 * std::sin((42358.9648f / fConst0)));
		fConst73 = (7223.21826f / fConst72);
		fConst74 = (1.0f / (((fConst71 + fConst73) / fConst70) + 1.0f));
		fConst75 = (1059.12756f / fConst72);
		fConst76 = (((fConst71 - fConst75) / fConst70) + 1.0f);
		fConst77 = std::tan((15066.6357f / fConst0));
		fConst78 = (1.0f / fConst77);
		fConst79 = (fConst0 * std::sin((30133.2715f / fConst0)));
		fConst80 = (11187.3662f / fConst79);
		fConst81 = (1.0f / (((fConst78 + fConst80) / fConst77) + 1.0f));
		fConst82 = (36783.4805f / fConst79);
		fConst83 = (((fConst78 - fConst82) / fConst77) + 1.0f);
		fConst84 = std::tan((13437.668f / fConst0));
		fConst85 = (1.0f / fConst84);
		fConst86 = (fConst0 * std::sin((26875.3359f / fConst0)));
		fConst87 = (13245.1885f / fConst86);
		fConst88 = (1.0f / (((fConst85 + fConst87) / fConst84) + 1.0f));
		fConst89 = (4583.19189f / fConst86);
		fConst90 = (((fConst85 - fConst89) / fConst84) + 1.0f);
		fConst91 = std::tan((10058.502f / fConst0));
		fConst92 = (1.0f / fConst91);
		fConst93 = (fConst0 * std::sin((20117.0039f / fConst0)));
		fConst94 = (4926.20459f / fConst93);
		fConst95 = (1.0f / (((fConst92 + fConst94) / fConst91) + 1.0f));
		fConst96 = (9024.73242f / fConst93);
		fConst97 = (((fConst92 - fConst96) / fConst91) + 1.0f);
		fConst98 = std::tan((8136.54736f / fConst0));
		fConst99 = (1.0f / fConst98);
		fConst100 = (fConst0 * std::sin((16273.0947f / fConst0)));
		fConst101 = (966.024841f / fConst100);
		fConst102 = (1.0f / (((fConst99 + fConst101) / fConst98) + 1.0f));
		fConst103 = (518.801147f / fConst100);
		fConst104 = (((fConst99 - fConst103) / fConst98) + 1.0f);
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
		fConst116 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst111))));
		fConst117 = std::tan((2827.43262f / fConst0));
		fConst118 = (1.0f / fConst117);
		fConst119 = (fConst0 * std::sin((5654.86523f / fConst0)));
		fConst120 = (19634.3262f / fConst119);
		fConst121 = (1.0f / (((fConst118 + fConst120) / fConst117) + 1.0f));
		fConst122 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst117))));
		fConst123 = std::tan((375.293884f / fConst0));
		fConst124 = (1.0f / fConst123);
		fConst125 = (fConst0 * std::sin((750.587769f / fConst0)));
		fConst126 = (463.734222f / fConst125);
		fConst127 = (1.0f / (((fConst124 + fConst126) / fConst123) + 1.0f));
		fConst128 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst123))));
		fConst129 = std::tan((18369.8027f / fConst0));
		fConst130 = (1.0f / fConst129);
		fConst131 = (1.0f / (((fConst130 + 0.284629673f) / fConst129) + 1.0f));
		fConst132 = (1.0f / (((fConst130 + 0.830830038f) / fConst129) + 1.0f));
		fConst133 = (1.0f / (((fConst130 + 1.30972147f) / fConst129) + 1.0f));
		fConst134 = (1.0f / (((fConst130 + 1.68250704f) / fConst129) + 1.0f));
		fConst135 = (1.0f / (((fConst130 + 1.91898596f) / fConst129) + 1.0f));
		fConst136 = (fConst130 + 1.0f);
		fConst137 = (1.0f / fConst136);
		fConst138 = (1.0f - fConst130);
		fConst139 = (1.0f / std::tan((56756.0547f / fConst0)));
		fConst140 = (1.0f / (fConst139 + 1.0f));
		fConst141 = (1.0f - fConst139);
		fConst142 = std::tan((452.102844f / fConst0));
		fConst143 = (1.0f / fConst142);
		fConst144 = (fConst143 + 1.0f);
		fConst145 = (1.0f / fConst144);
		fConst146 = (0.0199999996f / fConst142);
		fConst147 = (1.0f - fConst143);
		fConst148 = (0.0f - (1.0f / (fConst142 * fConst144)));
		fConst149 = (((fConst130 + -1.91898596f) / fConst129) + 1.0f);
		fConst150 = AmpMono_faustpower2_f(fConst129);
		fConst151 = (1.0f / fConst150);
		fConst152 = (2.0f * (1.0f - fConst151));
		fConst153 = (((fConst130 + -1.68250704f) / fConst129) + 1.0f);
		fConst154 = (((fConst130 + -1.30972147f) / fConst129) + 1.0f);
		fConst155 = (((fConst130 + -0.830830038f) / fConst129) + 1.0f);
		fConst156 = (((fConst130 + -0.284629673f) / fConst129) + 1.0f);
		fConst157 = (0.0f - (2.0f / fConst150));
		fConst158 = (0.0f - (1.0f / (fConst129 * fConst136)));
		fConst159 = (((fConst124 - fConst126) / fConst123) + 1.0f);
		fConst160 = (3220.11475f / fConst125);
		fConst161 = (((fConst124 + fConst160) / fConst123) + 1.0f);
		fConst162 = (((fConst124 - fConst160) / fConst123) + 1.0f);
		fConst163 = (((fConst118 - fConst120) / fConst117) + 1.0f);
		fConst164 = (106249.391f / fConst119);
		fConst165 = (((fConst118 + fConst164) / fConst117) + 1.0f);
		fConst166 = (((fConst118 - fConst164) / fConst117) + 1.0f);
		fConst167 = (((fConst112 - fConst114) / fConst111) + 1.0f);
		fConst168 = (974.257141f / fConst113);
		fConst169 = (((fConst112 + fConst168) / fConst111) + 1.0f);
		fConst170 = (((fConst112 - fConst168) / fConst111) + 1.0f);
		fConst171 = (((fConst106 - fConst108) / fConst105) + 1.0f);
		fConst172 = (3097.15845f / fConst107);
		fConst173 = (((fConst106 + fConst172) / fConst105) + 1.0f);
		fConst174 = (((fConst106 - fConst172) / fConst105) + 1.0f);
		fConst175 = (((fConst99 - fConst101) / fConst98) + 1.0f);
		fConst176 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst98))));
		fConst177 = (((fConst99 + fConst103) / fConst98) + 1.0f);
		fConst178 = (((fConst92 - fConst94) / fConst91) + 1.0f);
		fConst179 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst91))));
		fConst180 = (((fConst92 + fConst96) / fConst91) + 1.0f);
		fConst181 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst84))));
		fConst182 = (((fConst85 - fConst87) / fConst84) + 1.0f);
		fConst183 = (((fConst85 + fConst89) / fConst84) + 1.0f);
		fConst184 = (((fConst78 - fConst80) / fConst77) + 1.0f);
		fConst185 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst77))));
		fConst186 = (((fConst78 + fConst82) / fConst77) + 1.0f);
		fConst187 = (((fConst71 - fConst73) / fConst70) + 1.0f);
		fConst188 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst70))));
		fConst189 = (((fConst71 + fConst75) / fConst70) + 1.0f);
		fConst190 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst63))));
		fConst191 = (((fConst64 - fConst66) / fConst63) + 1.0f);
		fConst192 = (((fConst64 + fConst68) / fConst63) + 1.0f);
		fConst193 = (((fConst57 - fConst59) / fConst56) + 1.0f);
		fConst194 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst56))));
		fConst195 = (((fConst57 + fConst61) / fConst56) + 1.0f);
		fConst196 = (((fConst51 - fConst53) / fConst50) + 1.0f);
		fConst197 = (183.178085f / fConst52);
		fConst198 = (((fConst51 + fConst197) / fConst50) + 1.0f);
		fConst199 = (((fConst51 - fConst197) / fConst50) + 1.0f);
		fConst200 = (((fConst45 - fConst47) / fConst44) + 1.0f);
		fConst201 = (270.569763f / fConst46);
		fConst202 = (((fConst45 + fConst201) / fConst44) + 1.0f);
		fConst203 = (((fConst45 - fConst201) / fConst44) + 1.0f);
		fConst204 = (((fConst39 - fConst41) / fConst38) + 1.0f);
		fConst205 = (190.645706f / fConst40);
		fConst206 = (((fConst39 + fConst205) / fConst38) + 1.0f);
		fConst207 = (((fConst39 - fConst205) / fConst38) + 1.0f);
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
			fRec6[l7] = 0.0f;

		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;

		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			fRec17[l9] = 0.0f;

		}
		for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
			fRec19[l10] = 0.0f;

		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			fRec18[l11] = 0.0f;

		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fRec21[l12] = 0.0f;

		}
		for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
			fRec20[l13] = 0.0f;

		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec16[l14] = 0.0f;

		}
		for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
			fRec15[l15] = 0.0f;

		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fVec2[l16] = 0.0f;

		}
		for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
			fRec14[l17] = 0.0f;

		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fRec25[l18] = 0.0f;

		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fRec24[l19] = 0.0f;

		}
		for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
			fRec23[l20] = 0.0f;

		}
		for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
			fRec22[l21] = 0.0f;

		}
		for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
			fRec13[l22] = 0.0f;

		}
		for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
			fRec26[l23] = 0.0f;

		}
		for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
			fVec3[l24] = 0.0f;

		}
		for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
			fRec31[l25] = 0.0f;

		}
		for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
			fRec33[l26] = 0.0f;

		}
		for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
			fRec32[l27] = 0.0f;

		}
		for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
			fRec35[l28] = 0.0f;

		}
		for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
			fRec34[l29] = 0.0f;

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
			fRec27[l39] = 0.0f;

		}
		for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
			fVec5[l40] = 0.0f;

		}
		for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
			fRec5[l41] = 0.0f;

		}
		for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
			fRec41[l42] = 0.0f;

		}
		for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
			fVec6[l43] = 0.0f;

		}
		for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
			fRec4[l44] = 0.0f;

		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec3[l45] = 0.0f;

		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec42[l46] = 0.0f;

		}
		for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
			fVec7[l47] = 0.0f;

		}
		for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
			fRec2[l48] = 0.0f;

		}
		for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
			fRec43[l49] = 0.0f;

		}
		for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
			fVec8[l50] = 0.0f;

		}
		for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
			fRec44[l51] = 0.0f;

		}
		for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
			fVec9[l52] = 0.0f;

		}
		for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
			fRec1[l53] = 0.0f;

		}
		for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
			fRec47[l54] = 0.0f;

		}
		for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
			fRec46[l55] = 0.0f;

		}
		for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
			fRec49[l56] = 0.0f;

		}
		for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
			fVec10[l57] = 0.0f;

		}
		for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
			fRec0[l58] = 0.0f;

		}
		for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
			fRec52[l59] = 0.0f;

		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			fVec11[l60] = 0.0f;

		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			fRec50[l61] = 0.0f;

		}
		for (int l62 = 0; (l62 < 2); l62 = (l62 + 1)) {
			fVec12[l62] = 0.0f;

		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec75[l63] = 0.0f;

		}
		for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
			fRec74[l64] = 0.0f;

		}
		for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
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
		for (int l69 = 0; (l69 < 3); l69 = (l69 + 1)) {
			fRec69[l69] = 0.0f;

		}
		for (int l70 = 0; (l70 < 3); l70 = (l70 + 1)) {
			fRec68[l70] = 0.0f;

		}
		for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
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
			fRec77[l75] = 0.0f;

		}
		for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
			fRec76[l76] = 0.0f;

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
		for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
			fRec54[l90] = 0.0f;

		}
		for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
			fRec53[l91] = 0.0f;

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
	void set_gain_slope(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00; }
	void set_gain_stages(FAUSTFLOAT value) { fEntry16 = value + 0.000000e+00; }
	void set_input_level(FAUSTFLOAT value) { fEntry23 = value + 0.000000e+00; }
	void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00; }
	void set_power_drive(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00; }
	void set_pre_drive(FAUSTFLOAT value) { fEntry24 = value + 0.000000e+00; }
	void set_tetrode_grid_level(FAUSTFLOAT value) { fEntry42 = value + 4.244019e-01; }
	void set_tetrode_grid_offset1(FAUSTFLOAT value) { fEntry39 = value + 4.810579e-02; }
	void set_tetrode_grid_offset2(FAUSTFLOAT value) { fEntry44 = value + -2.048106e+00; }
	void set_tetrode_grid_ratio(FAUSTFLOAT value) { fEntry40 = value + 6.148691e-01; }
	void set_tetrode_grid_tau(FAUSTFLOAT value) { fEntry41 = value + -6.102038e-01; }
	void set_tetrode_grid_taus(FAUSTFLOAT value) { fEntry43 = value + 1.980396e-04; }
	void set_tetrode_hp_freq(FAUSTFLOAT value) { fEntry9 = value + -6.358174e+00; }
	void set_tetrode_plate_bias(FAUSTFLOAT value) { fEntry7 = value + -1.523123e+00; }
	void set_tetrode_plate_clip(FAUSTFLOAT value) { fEntry5 = value + 9.287699e-02; }
	void set_tetrode_plate_corner(FAUSTFLOAT value) { fEntry49 = value + 2.699145e-02; }
	void set_tetrode_plate_corner_b(FAUSTFLOAT value) { fEntry4 = value + 3.892749e-01; }
	void set_tetrode_plate_hp(FAUSTFLOAT value) { fEntry3 = value + -9.838880e-02; }
	void set_tetrode_plate_level(FAUSTFLOAT value) { fEntry47 = value + -5.337840e-01; }
	void set_tetrode_plate_point(FAUSTFLOAT value) { fEntry45 = value + 5.188755e-01; }
	void set_tetrode_plate_power(FAUSTFLOAT value) { fEntry8 = value + 0.000000e+00; }
	void set_tetrode_plate_ratio(FAUSTFLOAT value) { fEntry48 = value + 2.930971e-01; }
	void set_tetrode_plate_scale(FAUSTFLOAT value) { fEntry6 = value + -5.469312e-01; }
	void set_tetrode_plate_tau(FAUSTFLOAT value) { fEntry46 = value + 1.805051e-02; }
	void set_triode_clip_level(FAUSTFLOAT value) { fEntry32 = value + 9.067676e-01; }
	void set_triode_clip_ratio(FAUSTFLOAT value) { fEntry31 = value + 1.147704e+00; }
	void set_triode_clip_smooth(FAUSTFLOAT value) { fEntry29 = value + -3.100322e+00; }
	void set_triode_clip_tau(FAUSTFLOAT value) { fEntry30 = value + -1.301785e+00; }
	void set_triode_grid_level(FAUSTFLOAT value) { fEntry27 = value + 3.380630e-01; }
	void set_triode_grid_ratio(FAUSTFLOAT value) { fEntry28 = value + 1.066531e+00; }
	void set_triode_grid_smooth(FAUSTFLOAT value) { fEntry26 = value + 1.399600e+00; }
	void set_triode_grid_tau(FAUSTFLOAT value) { fEntry25 = value + -1.121188e+00; }
	void set_triode_hp_freq(FAUSTFLOAT value) { fEntry22 = value + 4.522249e-01; }
	void set_triode_plate_bias(FAUSTFLOAT value) { fEntry14 = value + -1.120198e-01; }
	void set_triode_plate_clip(FAUSTFLOAT value) { fEntry20 = value + 7.278736e-01; }
	void set_triode_plate_corner(FAUSTFLOAT value) { fEntry35 = value + -3.222958e-01; }
	void set_triode_plate_level(FAUSTFLOAT value) { fEntry33 = value + 6.567379e+01; }
	void set_triode_plate_level_b(FAUSTFLOAT value) { fEntry17 = value + -9.430010e-02; }
	void set_triode_plate_power(FAUSTFLOAT value) { fEntry15 = value + 0.000000e+00; }
	void set_triode_plate_ratio(FAUSTFLOAT value) { fEntry34 = value + 6.117379e+01; }
	void set_triode_plate_ratio_b(FAUSTFLOAT value) { fEntry36 = value + 8.422808e-01; }
	void set_triode_plate_scale(FAUSTFLOAT value) { fEntry2 = value + -5.523370e-01; }
	void set_triode_plate_scale_b(FAUSTFLOAT value) { fEntry18 = value + -3.318985e-01; }
	void set_triode_plate_smooth_b(FAUSTFLOAT value) { fEntry37 = value + -3.580170e+00; }
	void set_triode_plate_tau(FAUSTFLOAT value) { fEntry21 = value + 6.579679e+01; }
	void set_triode_plate_tau_b(FAUSTFLOAT value) { fEntry19 = value + -4.311549e-01; }
	void set_ts_high(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00; }
	void set_ts_low(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00; }
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
		set_tetrode_plate_corner_b(0.0f);
		set_tetrode_plate_hp(0.0f);
		set_tetrode_plate_level(0.0f);
		set_tetrode_plate_point(0.0f);
		set_tetrode_plate_power(0.0f);
		set_tetrode_plate_ratio(0.0f);
		set_tetrode_plate_scale(0.0f);
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
		float fSlow0 = (0.501187205f * std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f)))))));
		int iSlow1 = (float(fEntry1) > 0.0f);
		float fSlow2 = (float(fEntry2) + 1.0f);
		float fSlow3 = (0.0199999996f / fSlow2);
		float fSlow4 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry3) + 1.0f)) + -2.30258512f))));
		float fSlow5 = (1.0f / fSlow4);
		float fSlow6 = (fSlow5 + 1.0f);
		float fSlow7 = (0.0f - (1.0f / (fSlow4 * fSlow6)));
		float fSlow8 = (float(fEntry4) + 1.0f);
		float fSlow9 = (5.0f * fSlow8);
		float fSlow10 = (0.200000003f / fSlow8);
		float fSlow11 = (20.0f * (float(fEntry5) + 1.0f));
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
		float fSlow22 = (0.0f - (1.0f / (fSlow19 * fSlow21)));
		float fSlow23 = (float(fEntry10) + 1.0f);
		float fSlow24 = (50.0f * (fSlow2 * std::exp(((3.45387769f * fSlow23) + -2.30258512f))));
		float fSlow25 = float(fEntry11);
		float fSlow26 = ((fSlow25 > 0.0f)?((10.0f * fSlow25) + 13.0f):((18.0f * fSlow25) + 13.0f));
		float fSlow27 = float(fEntry12);
		float fSlow28 = ((fSlow27 > 0.0f)?((13.0f * fSlow27) + -3.0f):((5.0f * fSlow27) + -3.0f));
		float fSlow29 = float(fEntry13);
		int iSlow30 = (fSlow29 > 0.0f);
		float fSlow31 = (iSlow30?((5.0f * fSlow29) + 13.0f):((18.0f * fSlow29) + 13.0f));
		float fSlow32 = std::pow(10.0f, (0.0f - (0.0500000007f * ((0.200000003f * fSlow26) + ((0.600000024f * fSlow28) + (0.400000006f * fSlow31))))));
		float fSlow33 = ((fSlow25 < -0.800000012f)?(0.0f - (5.0f * (fSlow25 + 0.800000012f))):0.0f);
		float fSlow34 = (1.0f - fSlow33);
		float fSlow35 = ((fSlow27 < -0.800000012f)?(0.0f - (5.0f * (fSlow27 + 0.800000012f))):0.0f);
		float fSlow36 = (1.0f - fSlow35);
		float fSlow37 = std::tan((fConst1 * float((iSlow30?100:50))));
		float fSlow38 = (1.0f / fSlow37);
		float fSlow39 = (fSlow38 + 1.0f);
		float fSlow40 = (0.0f - (1.0f / (fSlow39 * fSlow37)));
		float fSlow41 = (float(fEntry14) + 1.0f);
		float fSlow42 = (10.0f * fSlow41);
		float fSlow43 = (0.5f * (float(fEntry15) + 1.0f));
		float fSlow44 = std::pow(fSlow42, fSlow43);
		float fSlow45 = (1.0f / fSlow44);
		float fSlow46 = float(fEntry16);
		float fSlow47 = std::max<float>(0.0f, (std::min<float>(5.0f, fSlow46) + -3.0f));
		float fSlow48 = (1.0f - (0.5f * fSlow47));
		float fSlow49 = std::max<float>(0.0f, (std::min<float>(3.0f, fSlow46) + -1.0f));
		float fSlow50 = (1.0f - (0.5f * fSlow49));
		float fSlow51 = (fSlow43 + 1.0f);
		float fSlow52 = std::pow(fSlow42, fSlow51);
		float fSlow53 = (37.5f * (float(fEntry17) + 1.0f));
		float fSlow54 = (fSlow52 + fSlow53);
		float fSlow55 = std::exp(((3.45387769f * (float(fEntry18) + 1.0f)) + -2.30258512f));
		float fSlow56 = std::exp(((4.60517025f * (float(fEntry19) + 1.0f)) + -9.2103405f));
		float fSlow57 = (1.0f / ((fConst0 * fSlow56) + 1.0f));
		float fSlow58 = (150.0f * (float(fEntry20) + 1.0f));
		float fSlow59 = std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -9.2103405f));
		float fSlow60 = (1.0f / ((fConst0 * fSlow59) + 1.0f));
		float fSlow61 = std::tan((fConst1 * std::exp(((3.45387769f * (float(fEntry22) + 1.0f)) + -2.30258512f))));
		float fSlow62 = (1.0f / fSlow61);
		float fSlow63 = (fSlow62 + 1.0f);
		float fSlow64 = (0.0f - (1.0f / (fSlow63 * fSlow61)));
		float fSlow65 = (float(fEntry24) + 1.0f);
		float fSlow66 = (std::pow(10.0f, (0.0500000007f * (0.0f - (35.0f * (1.0f - (float(fEntry23) + 1.0f)))))) * std::exp(((2.99573231f * fSlow65) + -0.693147182f)));
		float fSlow67 = (1.0f / fSlow63);
		float fSlow68 = (1.0f - fSlow62);
		float fSlow69 = (fSlow66 / fSlow61);
		float fSlow70 = std::exp(((3.45387769f * (float(fEntry25) + 1.0f)) + -13.8155107f));
		float fSlow71 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((6.90775537f * (float(fEntry26) + 1.0f)) + -11.5129251f)))) + 1.0f));
		float fSlow72 = (1.0f - fSlow71);
		float fSlow73 = (1.0f / ((fConst0 * fSlow70) + 1.0f));
		float fSlow74 = (5.0f * (1.0f - (float(fEntry27) + 1.0f)));
		float fSlow75 = (1.0f / ((fConst0 * (fSlow70 * std::exp(((5.75646257f * (float(fEntry28) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow76 = (1.0f - fSlow75);
		float fSlow77 = std::exp(((4.60517025f * (float(fEntry30) + 1.0f)) + -18.420681f));
		float fSlow78 = (1.0f / ((fConst0 * (std::exp(((6.90775537f * (float(fEntry29) + 1.0f)) + -11.5129251f)) * fSlow77)) + 1.0f));
		float fSlow79 = (1.0f - fSlow78);
		float fSlow80 = (1.0f / ((fConst0 * (fSlow77 * std::exp(((5.75646257f * (float(fEntry31) + 1.0f)) + -2.30258512f)))) + 1.0f));
		float fSlow81 = (1.0f - fSlow80);
		float fSlow82 = (1.0f / ((fConst0 * fSlow77) + 1.0f));
		float fSlow83 = float(fEntry32);
		float fSlow84 = (1.0f / fSlow41);
		float fSlow85 = (fSlow51 * fSlow44);
		float fSlow86 = (fSlow52 + (75.0f * (float(fEntry33) + 1.0f)));
		float fSlow87 = (1.0f / ((fConst0 * (fSlow59 * std::exp(((4.60517025f * (float(fEntry34) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow88 = (fSlow87 + -1.0f);
		float fSlow89 = std::exp(((4.60517025f * (float(fEntry35) + 1.0f)) + -2.30258512f));
		float fSlow90 = ((fSlow52 + fSlow58) + fSlow89);
		float fSlow91 = (1.0f / fSlow89);
		float fSlow92 = (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry36) + 1.0f)) + -2.99573231f)) * fSlow56)) + 1.0f));
		float fSlow93 = (1.0f - fSlow92);
		float fSlow94 = std::exp(((3.45387769f * (float(fEntry37) + 1.0f)) + -2.30258512f));
		float fSlow95 = (fSlow58 + fSlow94);
		float fSlow96 = (1.0f / fSlow94);
		float fSlow97 = ((float(fEntry38) + 1.0f) + 1.0f);
		float fSlow98 = (fSlow49 / fSlow97);
		float fSlow99 = (0.5f * (fSlow97 / fSlow44));
		float fSlow100 = (fSlow61 * fSlow44);
		float fSlow101 = (0.5f * (fSlow97 / fSlow100));
		float fSlow102 = (fSlow75 + -1.0f);
		float fSlow103 = (fSlow92 + -1.0f);
		float fSlow104 = (1.0f / fSlow100);
		float fSlow105 = (fSlow80 + -1.0f);
		float fSlow106 = AmpMono_faustpower2_f((0.5f * fSlow97));
		float fSlow107 = (0.5f * (fSlow47 / fSlow106));
		float fSlow108 = (fSlow106 / fSlow44);
		float fSlow109 = (fSlow106 / fSlow100);
		float fSlow110 = (1.0f - fSlow87);
		float fSlow111 = (5.0f * fSlow65);
		int iSlow112 = (fSlow111 < 9.0f);
		int iSlow113 = (fSlow111 < 8.0f);
		int iSlow114 = (fSlow111 < 7.0f);
		int iSlow115 = (fSlow111 < 6.0f);
		int iSlow116 = (fSlow111 < 5.0f);
		int iSlow117 = (fSlow111 < 4.0f);
		int iSlow118 = (fSlow111 < 3.0f);
		int iSlow119 = (fSlow111 < 2.0f);
		int iSlow120 = (fSlow111 < 1.0f);
		float fSlow121 = std::pow(10.0f, (0.0500000007f * (iSlow112?(iSlow113?(iSlow114?(iSlow115?(iSlow116?(iSlow117?(iSlow118?(iSlow119?(iSlow120?((fSlow111 < 0.0f)?1.04999995f:(iSlow120?(1.04999995f - (26.1000004f * fSlow65)):-4.17000008f)):(iSlow119?(-4.17000008f - (5.19999981f * (fSlow111 + -1.0f))):-9.36999989f)):(iSlow118?(-9.36999989f - (4.92999983f * (fSlow111 + -2.0f))):-14.3000002f)):(iSlow117?(-14.3000002f - (4.5f * (fSlow111 + -3.0f))):-18.7999992f)):(iSlow116?(-18.7999992f - (3.5f * (fSlow111 + -4.0f))):-22.2999992f)):(iSlow115?(-22.2999992f - (1.60000002f * (0.0f - (5.0f * (1.0f - fSlow65))))):-23.8999996f)):(iSlow114?(-23.8999996f - (0.200000003f * (fSlow111 + -6.0f))):-24.1000004f)):(iSlow113?((0.300000012f * (fSlow111 + -7.0f)) + -24.1000004f):-23.7999992f)):(iSlow112?((0.400000006f * (fSlow111 + -8.0f)) + -23.7999992f):-23.3999996f)):((fSlow111 < 10.0f)?((0.200000003f * (fSlow111 + -9.0f)) + -23.3999996f):-23.2000008f))));
		float fSlow122 = (1.0f - fSlow38);
		float fSlow123 = std::pow(10.0f, (0.0500000007f * fSlow31));
		float fSlow124 = ((fSlow29 < -0.800000012f)?(0.0f - (5.0f * (fSlow29 + 0.800000012f))):0.0f);
		float fSlow125 = (1.0f - fSlow124);
		int iSlow126 = (fSlow28 > 0.0f);
		float fSlow127 = (fConst16 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow28))));
		float fSlow128 = (iSlow126?fConst16:fSlow127);
		float fSlow129 = ((fConst15 * (fConst15 - fSlow128)) + 1.0f);
		float fSlow130 = ((fConst15 * (fConst15 + fSlow128)) + 1.0f);
		float fSlow131 = (iSlow126?fSlow127:fConst16);
		float fSlow132 = ((fConst15 * (fConst15 - fSlow131)) + 1.0f);
		float fSlow133 = ((fConst15 * (fConst15 + fSlow131)) + 1.0f);
		float fSlow134 = std::pow(10.0f, (0.0500000007f * fSlow26));
		float fSlow135 = (250.0f * (float(fEntry39) + 1.0f));
		float fSlow136 = (1.0f / fSlow21);
		float fSlow137 = (1.0f - fSlow20);
		float fSlow138 = std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) + -9.2103405f));
		float fSlow139 = (1.0f - (1.0f / ((fConst0 * (std::exp(((4.60517025f * (float(fEntry40) + 1.0f)) + -4.60517025f)) * fSlow138)) + 1.0f)));
		float fSlow140 = (1.0f / ((fConst0 * fSlow138) + 1.0f));
		float fSlow141 = (100.0f * (1.0f - (float(fEntry42) + 1.0f)));
		float fSlow142 = std::exp((0.0f - (fConst17 / std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f)))));
		float fSlow143 = (1.0f - fSlow142);
		float fSlow144 = (250.0f * (float(fEntry44) + 1.0f));
		float fSlow145 = (fSlow16 * std::pow(fSlow14, fSlow15));
		float fSlow146 = std::pow((10.0f * (float(fEntry45) + 1.0f)), fSlow16);
		float fSlow147 = std::exp(((4.60517025f * (float(fEntry46) + 1.0f)) + -9.2103405f));
		float fSlow148 = (1.0f / ((fConst0 * fSlow147) + 1.0f));
		float fSlow149 = (50.0f * (float(fEntry47) + 1.0f));
		float fSlow150 = (1.0f / ((fConst0 * (fSlow147 * std::exp(((4.60517025f * (float(fEntry48) + 1.0f)) + -4.60517025f)))) + 1.0f));
		float fSlow151 = (1.0f - fSlow150);
		float fSlow152 = (float(fEntry49) + 1.0f);
		float fSlow153 = (1.0f - fSlow152);
		float fSlow154 = (fSlow11 + (10.0f * fSlow153));
		float fSlow155 = (0.100000001f / fSlow152);
		float fSlow156 = (1.0f / fSlow6);
		float fSlow157 = (1.0f - fSlow5);
		float fSlow158 = (fSlow144 + fSlow13);
		float fSlow159 = (fSlow150 + -1.0f);
		float fSlow160 = (5.0f * fSlow23);
		int iSlow161 = (fSlow160 < 8.0f);
		int iSlow162 = (fSlow160 < 7.0f);
		int iSlow163 = (fSlow160 < 6.0f);
		int iSlow164 = (fSlow160 < 5.0f);
		int iSlow165 = (fSlow160 < 4.0f);
		int iSlow166 = (fSlow160 < 3.0f);
		int iSlow167 = (fSlow160 < 2.0f);
		int iSlow168 = (fSlow160 < 1.0f);
		float fSlow169 = std::pow(10.0f, (0.0500000007f * ((fSlow160 < 9.0f)?(iSlow161?(iSlow162?(iSlow163?(iSlow164?(iSlow165?(iSlow166?(iSlow167?(iSlow168?((fSlow160 < 0.0f)?22.7999992f:(iSlow168?(22.7999992f - (30.0f * fSlow23)):16.7999992f)):(iSlow167?(16.7999992f - (5.9000001f * (fSlow160 + -1.0f))):10.8999996f)):(iSlow166?(10.8999996f - (5.80999994f * (fSlow160 + -2.0f))):5.09000015f)):(iSlow165?(5.09000015f - (5.44099998f * (fSlow160 + -3.0f))):-0.351000011f)):(iSlow164?(-0.351000011f - (4.95900011f * (fSlow160 + -4.0f))):-5.30999994f)):(iSlow163?(-5.30999994f - (3.45000005f * (0.0f - (5.0f * (1.0f - fSlow23))))):-8.76000023f)):(iSlow162?(-8.76000023f - (1.53999996f * (fSlow160 + -6.0f))):-10.3000002f)):(iSlow161?(-10.3000002f - (0.5f * (fSlow160 + -7.0f))):-10.8000002f)):-10.8000002f):((fSlow160 < 10.0f)?((0.100000001f * (fSlow160 + -9.0f)) + -10.8000002f):-10.6999998f))));
		float fSlow170 = (fConst146 / fSlow2);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input0[i]);
			fVec0[0] = (fSlow66 * fTemp0);
			fRec8[0] = ((fSlow64 * fVec0[1]) - (fSlow67 * ((fSlow68 * fRec8[1]) - (fSlow69 * fTemp0))));
			fRec10[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec8[0])) - fRec10[1]))) + (fSlow76 * fRec10[1]));
			fRec9[0] = ((fSlow72 * fRec9[1]) + (fSlow71 * fRec10[0]));
			fRec12[0] = ((fSlow81 * fRec12[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec8[0] + (-2.0f - fRec9[0])) - fSlow83)) - fRec12[1]))));
			fRec11[0] = ((fSlow79 * fRec11[1]) + (fSlow78 * fRec12[0]));
			float fTemp1 = (fRec8[0] - (fRec9[0] + fRec11[0]));
			float fTemp2 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp1)) + -0.0500000007f)));
			float fTemp3 = (((std::pow(std::max<float>(0.0f, (fSlow42 + fTemp1)), fSlow51) - fSlow52) * fTemp2) + (fSlow85 * (fTemp1 * (1.0f - fTemp2))));
			fRec7[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp3 + 100.0f) - fSlow86)) - fRec7[1]))) - (fSlow88 * fRec7[1]));
			float fTemp4 = ((fRec7[0] + (300.0f - fTemp3)) - fSlow90);
			float fTemp5 = (std::max<float>(0.0f, fTemp4) + (fSlow89 * (float(tanhf(float((fSlow91 * std::min<float>(0.0f, fTemp4))))) + 1.0f)));
			fRec6[0] = ((fSlow57 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow58 + ((fTemp5 + -250.0f) - fSlow53))) - fRec6[1]))) + (fSlow93 * fRec6[1]));
			float fTemp6 = (fSlow55 * fRec6[0]);
			float fTemp7 = (fSlow95 + ((fTemp5 + (-250.0f - fTemp6)) - fSlow53));
			float fTemp8 = (fSlow54 + ((fTemp6 + std::min<float>(0.0f, fTemp7)) + (-50.0f - (fSlow94 * (1.0f - float(tanhf(float((fSlow96 * std::max<float>(0.0f, fTemp7))))))))));
			fVec1[0] = (fSlow99 * fTemp8);
			fRec17[0] = ((fSlow64 * fVec1[1]) + (fSlow67 * ((fSlow101 * fTemp8) - (fSlow68 * fRec17[1]))));
			fRec19[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec17[0])) - fRec19[1]))) - (fSlow102 * fRec19[1]));
			fRec18[0] = ((fSlow72 * fRec18[1]) + (fSlow71 * fRec19[0]));
			fRec21[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec17[0] + (-2.0f - fRec18[0])) - fSlow83)) - fRec21[1]))) + (fSlow81 * fRec21[1]));
			fRec20[0] = ((fSlow79 * fRec20[1]) + (fSlow78 * fRec21[0]));
			float fTemp9 = (fRec17[0] - (fRec18[0] + fRec20[0]));
			float fTemp10 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp9)) + -0.0500000007f)));
			float fTemp11 = ((fTemp10 * (std::pow(std::max<float>(0.0f, (fSlow42 + fTemp9)), fSlow51) - fSlow52)) + (fSlow85 * (fTemp9 * (1.0f - fTemp10))));
			fRec16[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp11 + 100.0f) - fSlow86)) - fRec16[1]))) - (fSlow88 * fRec16[1]));
			float fTemp12 = ((fRec16[0] + (300.0f - fTemp11)) - fSlow90);
			float fTemp13 = (std::max<float>(0.0f, fTemp12) + (fSlow89 * (float(tanhf(float((fSlow91 * std::min<float>(0.0f, fTemp12))))) + 1.0f)));
			fRec15[0] = ((fSlow57 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow58 + ((fTemp13 + -250.0f) - fSlow53))) - fRec15[1]))) - (fSlow103 * fRec15[1]));
			float fTemp14 = (fSlow55 * fRec15[0]);
			float fTemp15 = (fSlow95 + ((fTemp13 + (-250.0f - fTemp14)) - fSlow53));
			float fTemp16 = (fSlow54 + ((fTemp14 + std::min<float>(0.0f, fTemp15)) + (-50.0f - (fSlow94 * (1.0f - float(tanhf(float((fSlow96 * std::max<float>(0.0f, fTemp15))))))))));
			fVec2[0] = (fSlow45 * fTemp16);
			fRec14[0] = ((fSlow64 * fVec2[1]) - (fSlow67 * ((fSlow68 * fRec14[1]) - (fSlow104 * fTemp16))));
			fRec25[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec14[0])) - fRec25[1]))) - (fSlow102 * fRec25[1]));
			fRec24[0] = ((fSlow72 * fRec24[1]) + (fSlow71 * fRec25[0]));
			fRec23[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec14[0] + (-2.0f - fRec24[0])) - fSlow83)) - fRec23[1]))) - (fSlow105 * fRec23[1]));
			fRec22[0] = ((fSlow79 * fRec22[1]) + (fSlow78 * fRec23[0]));
			float fTemp17 = (fRec14[0] - (fRec22[0] + fRec24[0]));
			float fTemp18 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp17)) + -0.0500000007f)));
			float fTemp19 = ((fTemp18 * (std::pow(std::max<float>(0.0f, (fSlow42 + fTemp17)), fSlow51) - fSlow52)) + (fSlow85 * ((1.0f - fTemp18) * fTemp17)));
			fRec13[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp19 + 100.0f) - fSlow86)) - fRec13[1]))) - (fSlow88 * fRec13[1]));
			float fTemp20 = ((fRec13[0] + (300.0f - fTemp19)) - fSlow90);
			float fTemp21 = (std::max<float>(0.0f, fTemp20) + (fSlow89 * (float(tanhf(float((fSlow91 * std::min<float>(0.0f, fTemp20))))) + 1.0f)));
			fRec26[0] = ((fSlow57 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow58 + ((fTemp21 + -250.0f) - fSlow53))) - fRec26[1]))) + (fSlow93 * fRec26[1]));
			float fTemp22 = (fSlow55 * fRec26[0]);
			float fTemp23 = (fSlow95 + ((fTemp21 + (-250.0f - fTemp22)) - fSlow53));
			float fTemp24 = ((fSlow50 * fTemp8) + (fSlow98 * (fSlow54 + ((std::min<float>(0.0f, fTemp23) + fTemp22) + (-50.0f - (fSlow94 * (1.0f - float(tanhf(float((fSlow96 * std::max<float>(0.0f, fTemp23))))))))))));
			fVec3[0] = (fSlow108 * fTemp24);
			fRec31[0] = ((fSlow64 * fVec3[1]) - (fSlow67 * ((fSlow68 * fRec31[1]) - (fSlow109 * fTemp24))));
			fRec33[0] = ((fSlow76 * fRec33[1]) + (fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec31[0])) - fRec33[1]))));
			fRec32[0] = ((fSlow72 * fRec32[1]) + (fSlow71 * fRec33[0]));
			fRec35[0] = ((fSlow81 * fRec35[1]) + (fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec31[0] + (-2.0f - fRec32[0])) - fSlow83)) - fRec35[1]))));
			fRec34[0] = ((fSlow79 * fRec34[1]) + (fSlow78 * fRec35[0]));
			float fTemp25 = (fRec31[0] - (fRec32[0] + fRec34[0]));
			float fTemp26 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp25)) + -0.0500000007f)));
			float fTemp27 = (((std::pow(std::max<float>(0.0f, (fSlow42 + fTemp25)), fSlow51) - fSlow52) * fTemp26) + (fSlow85 * (fTemp25 * (1.0f - fTemp26))));
			fRec30[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp27 + 100.0f) - fSlow86)) - fRec30[1]))) + (fSlow110 * fRec30[1]));
			float fTemp28 = ((fRec30[0] + (300.0f - fTemp27)) - fSlow90);
			float fTemp29 = ((fSlow89 * (float(tanhf(float((fSlow91 * std::min<float>(0.0f, fTemp28))))) + 1.0f)) + std::max<float>(0.0f, fTemp28));
			fRec36[0] = ((fSlow93 * fRec36[1]) + (fSlow57 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow58 + ((fTemp29 + -250.0f) - fSlow53))) - fRec36[1]))));
			float fTemp30 = (fSlow55 * fRec36[0]);
			float fTemp31 = (fSlow95 + ((fTemp29 + (-250.0f - fTemp30)) - fSlow53));
			float fTemp32 = (fSlow54 + ((std::min<float>(0.0f, fTemp31) + fTemp30) + (-50.0f - (fSlow94 * (1.0f - float(tanhf(float((fSlow96 * std::max<float>(0.0f, fTemp31))))))))));
			fVec4[0] = (fSlow45 * fTemp32);
			fRec29[0] = ((fSlow64 * fVec4[1]) - (fSlow67 * ((fSlow68 * fRec29[1]) - (fSlow104 * fTemp32))));
			fRec38[0] = ((fSlow73 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow74 + fRec29[0])) - fRec38[1]))) - (fSlow102 * fRec38[1]));
			fRec37[0] = ((fSlow71 * fRec38[0]) + (fSlow72 * fRec37[1]));
			fRec40[0] = ((fSlow82 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fRec29[0] + (-2.0f - fRec37[0])) - fSlow83)) - fRec40[1]))) + (fSlow81 * fRec40[1]));
			fRec39[0] = ((fSlow79 * fRec39[1]) + (fSlow78 * fRec40[0]));
			float fTemp33 = (fRec29[0] - (fRec37[0] + fRec39[0]));
			float fTemp34 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow84 * std::fabs(fTemp33)) + -0.0500000007f)));
			float fTemp35 = ((fSlow85 * ((1.0f - fTemp34) * fTemp33)) + ((std::pow(std::max<float>(0.0f, (fSlow42 + fTemp33)), fSlow51) - fSlow52) * fTemp34));
			fRec28[0] = ((fSlow60 * std::max<float>(0.0f, (std::max<float>(0.0f, ((fTemp35 + 100.0f) - fSlow86)) - fRec28[1]))) + (fSlow110 * fRec28[1]));
			float fTemp36 = ((fRec28[0] + (300.0f - fTemp35)) - fSlow90);
			float fTemp37 = ((fSlow89 * (float(tanhf(float((fSlow91 * std::min<float>(0.0f, fTemp36))))) + 1.0f)) + std::max<float>(0.0f, fTemp36));
			fRec27[0] = ((fSlow57 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow58 + ((fTemp37 + -250.0f) - fSlow53))) - fRec27[1]))) - (fSlow103 * fRec27[1]));
			float fTemp38 = (fSlow55 * fRec27[0]);
			float fTemp39 = (fSlow95 + ((fTemp37 + (-250.0f - fTemp38)) - fSlow53));
			float fTemp40 = (((fSlow48 * fTemp24) + (fSlow107 * (fSlow54 + ((fTemp38 + std::min<float>(0.0f, fTemp39)) + (-50.0f - (fSlow94 * (1.0f - float(tanhf(float((fSlow96 * std::max<float>(0.0f, fTemp39)))))))))))) * fSlow121);
			float fTemp41 = (fSlow45 * fTemp40);
			fVec5[0] = fTemp41;
			fRec5[0] = ((fSlow40 * fVec5[1]) - (((fRec5[1] * fSlow122) - (fSlow45 * (fTemp40 / fSlow37))) / fSlow39));
			fRec41[0] = (0.0f - (((fSlow122 * fRec41[1]) - (fTemp41 + fVec5[1])) / fSlow39));
			float fTemp42 = (fRec5[0] + (fRec41[0] * fSlow123));
			fVec6[0] = fTemp42;
			fRec4[0] = ((fConst10 * ((fConst8 * fTemp42) - (fConst11 * fRec4[1]))) + (fConst12 * fVec6[1]));
			float fTemp43 = (fConst14 * fRec3[1]);
			fRec3[0] = (((fRec4[0] * fSlow124) + (fTemp42 * fSlow125)) - ((fTemp43 + (fSlow129 * fRec3[2])) / fSlow130));
			float fTemp44 = ((fRec3[2] * fSlow132) + (fTemp43 + (fRec3[0] * fSlow133)));
			float fTemp45 = (fConst25 * fRec42[1]);
			fRec42[0] = ((fTemp44 / fSlow130) - (fConst23 * (fTemp45 + (fConst26 * fRec42[2]))));
			float fTemp46 = (((fSlow36 * fTemp44) / fSlow130) + (fConst23 * (fSlow35 * ((fConst24 * fRec42[2]) + (fTemp45 + (fConst24 * fRec42[0]))))));
			fVec7[0] = fTemp46;
			fRec2[0] = (0.0f - (fConst5 * ((fConst6 * fRec2[1]) - (fVec7[1] + fTemp46))));
			fRec43[0] = ((fConst27 * fVec7[1]) - (fConst5 * ((fConst6 * fRec43[1]) - (fConst3 * fTemp46))));
			float fTemp47 = (fRec2[0] + (fRec43[0] * fSlow134));
			fVec8[0] = fTemp47;
			fRec44[0] = (fConst29 * ((fTemp47 + fVec8[1]) - (fConst30 * fRec44[1])));
			float fTemp48 = ((fSlow24 * (fSlow32 * ((fSlow34 * fTemp47) + (fRec44[0] * fSlow33)))) - fSlow135);
			fVec9[0] = fTemp48;
			fRec1[0] = ((fSlow22 * fVec9[1]) - (fSlow136 * ((fSlow137 * fRec1[1]) - (fSlow20 * fTemp48))));
			fRec47[0] = ((fSlow142 * fRec47[1]) + (fSlow143 * (fRec1[0] - fSlow144)));
			fRec46[0] = ((fSlow139 * fRec46[1]) + (fSlow140 * std::max<float>(0.0f, (std::max<float>(0.0f, (fSlow141 + ((fRec1[0] - fRec47[0]) - fSlow144))) - fRec46[1]))));
			float fRec45 = fRec46[0];
			float fTemp49 = (fRec45 + fRec47[0]);
			float fTemp50 = (0.0f - ((fRec1[0] - fTemp49) - fSlow144));
			float fTemp51 = (0.0f - fTemp50);
			float fTemp52 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow18 * std::fabs(fTemp51)) + -0.0500000007f)));
			float fTemp53 = (fSlow12 * (fSlow17 + (((fTemp52 * (std::pow(std::max<float>(0.0f, (fSlow13 + ((fRec1[0] + (30.0f - fTemp49)) - fSlow144))), fSlow16) - fSlow17)) + (fSlow145 * (fTemp51 * (1.0f - fTemp52)))) - fSlow146)));
			fRec49[0] = ((fSlow148 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp53 - fSlow149)) - fRec49[1]))) + (fSlow151 * fRec49[1]));
			float fRec48 = fRec49[0];
			float fTemp54 = ((fTemp53 - fRec48) - fSlow154);
			float fTemp55 = (std::max<float>(0.0f, (fSlow11 + (std::min<float>(0.0f, fTemp54) + (10.0f * (fSlow153 + (fSlow152 * float(tanhf(float((fSlow155 * std::max<float>(0.0f, fTemp54))))))))))) - fSlow9);
			float fTemp56 = ((fSlow9 * (float(tanhf(float((fSlow10 * std::min<float>(0.0f, fTemp55))))) + 1.0f)) + std::max<float>(0.0f, fTemp55));
			fVec10[0] = fTemp56;
			fRec0[0] = ((fSlow7 * fVec10[1]) - (fSlow156 * ((fSlow157 * fRec0[1]) - (fSlow5 * fTemp56))));
			float fTemp57 = std::max<float>(0.0f, std::min<float>(1.0f, ((fSlow18 * std::fabs(fTemp50)) + -0.0500000007f)));
			float fTemp58 = (fSlow12 * (fSlow17 + (((fSlow145 * (fTemp50 * (1.0f - fTemp57))) + (fTemp57 * (std::pow(std::max<float>(0.0f, (fSlow158 + (fTemp49 + (30.0f - fRec1[0])))), fSlow16) - fSlow17))) - fSlow146)));
			fRec52[0] = ((fSlow148 * std::max<float>(0.0f, (std::max<float>(0.0f, (fTemp58 - fSlow149)) - fRec52[1]))) - (fSlow159 * fRec52[1]));
			float fRec51 = fRec52[0];
			float fTemp59 = ((fTemp58 - fRec51) - fSlow154);
			float fTemp60 = (std::max<float>(0.0f, (fSlow11 + ((10.0f * (fSlow153 + (fSlow152 * float(tanhf(float((fSlow155 * std::max<float>(0.0f, fTemp59)))))))) + std::min<float>(0.0f, fTemp59)))) - fSlow9);
			float fTemp61 = (std::max<float>(0.0f, fTemp60) + (fSlow9 * (float(tanhf(float((fSlow10 * std::min<float>(0.0f, fTemp60))))) + 1.0f)));
			fVec11[0] = fTemp61;
			fRec50[0] = ((fSlow7 * fVec11[1]) - (fSlow156 * ((fSlow157 * fRec50[1]) - (fSlow5 * fTemp61))));
			float fTemp62 = ((fRec0[0] - fRec50[0]) * fSlow169);
			float fTemp63 = (fSlow3 * fTemp62);
			fVec12[0] = fTemp63;
			fRec75[0] = ((fConst145 * ((fSlow170 * fTemp62) - (fConst147 * fRec75[1]))) + (fConst148 * fVec12[1]));
			fRec74[0] = (0.0f - (fConst140 * ((fConst141 * fRec74[1]) - (fRec75[0] + fRec75[1]))));
			fRec73[0] = (0.0f - (fConst137 * ((fConst138 * fRec73[1]) - (fRec74[0] + fRec74[1]))));
			fRec72[0] = (fRec73[0] - (fConst135 * ((fConst149 * fRec72[2]) + (fConst152 * fRec72[1]))));
			fRec71[0] = ((fConst135 * ((fRec72[0] + (2.0f * fRec72[1])) + fRec72[2])) - (fConst134 * ((fConst153 * fRec71[2]) + (fConst152 * fRec71[1]))));
			fRec70[0] = ((fConst134 * (fRec71[2] + (fRec71[0] + (2.0f * fRec71[1])))) - (fConst133 * ((fConst154 * fRec70[2]) + (fConst152 * fRec70[1]))));
			fRec69[0] = ((fConst133 * ((fRec70[0] + (2.0f * fRec70[1])) + fRec70[2])) - (fConst132 * ((fConst152 * fRec69[1]) + (fConst155 * fRec69[2]))));
			fRec68[0] = ((fConst132 * (fRec69[2] + (fRec69[0] + (2.0f * fRec69[1])))) - (fConst131 * ((fConst152 * fRec68[1]) + (fConst156 * fRec68[2]))));
			fRec81[0] = ((fConst158 * fRec74[1]) - (fConst137 * ((fConst138 * fRec81[1]) - (fConst130 * fRec74[0]))));
			fRec80[0] = (fRec81[0] - (fConst135 * ((fConst152 * fRec80[1]) + (fConst149 * fRec80[2]))));
			fRec79[0] = ((fConst135 * ((fConst151 * fRec80[2]) + ((fConst151 * fRec80[0]) + (fConst157 * fRec80[1])))) - (fConst134 * ((fConst152 * fRec79[1]) + (fConst153 * fRec79[2]))));
			fRec78[0] = ((fConst134 * ((fConst151 * fRec79[2]) + ((fConst151 * fRec79[0]) + (fConst157 * fRec79[1])))) - (fConst133 * ((fConst154 * fRec78[2]) + (fConst152 * fRec78[1]))));
			fRec77[0] = ((fConst133 * ((fConst151 * fRec78[2]) + ((fConst157 * fRec78[1]) + (fConst151 * fRec78[0])))) - (fConst132 * ((fConst155 * fRec77[2]) + (fConst152 * fRec77[1]))));
			fRec76[0] = ((fConst132 * (((fConst157 * fRec77[1]) + (fConst151 * fRec77[0])) + (fConst151 * fRec77[2]))) - (fConst131 * ((fConst156 * fRec76[2]) + (fConst152 * fRec76[1]))));
			float fTemp64 = (fConst128 * fRec67[1]);
			fRec67[0] = ((fConst131 * ((fRec68[2] + (fRec68[0] + (2.0f * fRec68[1]))) + (0.13673377f * (((fConst157 * fRec76[1]) + (fConst151 * fRec76[0])) + (fConst151 * fRec76[2]))))) - (fConst127 * (fTemp64 + (fConst159 * fRec67[2]))));
			float fTemp65 = (fConst122 * fRec66[1]);
			fRec66[0] = ((fConst127 * ((fTemp64 + (fConst161 * fRec67[0])) + (fConst162 * fRec67[2]))) - (fConst121 * (fTemp65 + (fConst163 * fRec66[2]))));
			float fTemp66 = (fConst116 * fRec65[1]);
			fRec65[0] = ((fConst121 * ((fTemp65 + (fConst165 * fRec66[0])) + (fConst166 * fRec66[2]))) - (fConst115 * (fTemp66 + (fConst167 * fRec65[2]))));
			float fTemp67 = (fConst110 * fRec64[1]);
			fRec64[0] = ((fConst115 * ((fTemp66 + (fConst169 * fRec65[0])) + (fConst170 * fRec65[2]))) - (fConst109 * ((fConst171 * fRec64[2]) + fTemp67)));
			float fTemp68 = (fConst176 * fRec63[1]);
			fRec63[0] = ((fConst109 * ((fTemp67 + (fConst173 * fRec64[0])) + (fConst174 * fRec64[2]))) - (fConst102 * ((fConst175 * fRec63[2]) + fTemp68)));
			float fTemp69 = (fConst179 * fRec62[1]);
			fRec62[0] = ((fConst102 * ((fConst104 * fRec63[2]) + (fTemp68 + (fConst177 * fRec63[0])))) - (fConst95 * ((fConst178 * fRec62[2]) + fTemp69)));
			float fTemp70 = (fConst181 * fRec61[1]);
			fRec61[0] = ((fConst95 * ((fConst97 * fRec62[2]) + (fTemp69 + (fConst180 * fRec62[0])))) - (fConst88 * (fTemp70 + (fConst182 * fRec61[2]))));
			float fTemp71 = (fConst185 * fRec60[1]);
			fRec60[0] = ((fConst88 * ((fConst90 * fRec61[2]) + (fTemp70 + (fConst183 * fRec61[0])))) - (fConst81 * ((fConst184 * fRec60[2]) + fTemp71)));
			float fTemp72 = (fConst188 * fRec59[1]);
			fRec59[0] = ((fConst81 * ((fConst83 * fRec60[2]) + (fTemp71 + (fConst186 * fRec60[0])))) - (fConst74 * ((fConst187 * fRec59[2]) + fTemp72)));
			float fTemp73 = (fConst190 * fRec58[1]);
			fRec58[0] = ((fConst74 * ((fConst76 * fRec59[2]) + (fTemp72 + (fConst189 * fRec59[0])))) - (fConst67 * (fTemp73 + (fConst191 * fRec58[2]))));
			float fTemp74 = (fConst194 * fRec57[1]);
			fRec57[0] = ((fConst67 * ((fConst69 * fRec58[2]) + (fTemp73 + (fConst192 * fRec58[0])))) - (fConst60 * ((fConst193 * fRec57[2]) + fTemp74)));
			float fTemp75 = (fConst55 * fRec56[1]);
			fRec56[0] = ((fConst60 * ((fConst62 * fRec57[2]) + (fTemp74 + (fConst195 * fRec57[0])))) - (fConst54 * ((fConst196 * fRec56[2]) + fTemp75)));
			float fTemp76 = (fConst49 * fRec55[1]);
			fRec55[0] = ((fConst54 * ((fTemp75 + (fConst198 * fRec56[0])) + (fConst199 * fRec56[2]))) - (fConst48 * (fTemp76 + (fConst200 * fRec55[2]))));
			float fTemp77 = (fConst43 * fRec54[1]);
			fRec54[0] = ((fConst48 * ((fTemp76 + (fConst202 * fRec55[0])) + (fConst203 * fRec55[2]))) - (fConst42 * ((fConst204 * fRec54[2]) + fTemp77)));
			float fTemp78 = (fConst37 * fRec53[1]);
			fRec53[0] = ((fConst42 * ((fTemp77 + (fConst206 * fRec54[0])) + (fConst207 * fRec54[2]))) - (fConst208 * ((fConst209 * fRec53[2]) + fTemp78)));
			output0[i] = FAUSTFLOAT((fSlow0 * (iSlow1?(fConst36 * ((fTemp78 + (fConst211 * fRec53[0])) + (fConst212 * fRec53[2]))):fTemp63)));
			fVec0[1] = fVec0[0];
			fRec8[1] = fRec8[0];
			fRec10[1] = fRec10[0];
			fRec9[1] = fRec9[0];
			fRec12[1] = fRec12[0];
			fRec11[1] = fRec11[0];
			fRec7[1] = fRec7[0];
			fRec6[1] = fRec6[0];
			fVec1[1] = fVec1[0];
			fRec17[1] = fRec17[0];
			fRec19[1] = fRec19[0];
			fRec18[1] = fRec18[0];
			fRec21[1] = fRec21[0];
			fRec20[1] = fRec20[0];
			fRec16[1] = fRec16[0];
			fRec15[1] = fRec15[0];
			fVec2[1] = fVec2[0];
			fRec14[1] = fRec14[0];
			fRec25[1] = fRec25[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			fRec22[1] = fRec22[0];
			fRec13[1] = fRec13[0];
			fRec26[1] = fRec26[0];
			fVec3[1] = fVec3[0];
			fRec31[1] = fRec31[0];
			fRec33[1] = fRec33[0];
			fRec32[1] = fRec32[0];
			fRec35[1] = fRec35[0];
			fRec34[1] = fRec34[0];
			fRec30[1] = fRec30[0];
			fRec36[1] = fRec36[0];
			fVec4[1] = fVec4[0];
			fRec29[1] = fRec29[0];
			fRec38[1] = fRec38[0];
			fRec37[1] = fRec37[0];
			fRec40[1] = fRec40[0];
			fRec39[1] = fRec39[0];
			fRec28[1] = fRec28[0];
			fRec27[1] = fRec27[0];
			fVec5[1] = fVec5[0];
			fRec5[1] = fRec5[0];
			fRec41[1] = fRec41[0];
			fVec6[1] = fVec6[0];
			fRec4[1] = fRec4[0];
			fRec3[2] = fRec3[1];
			fRec3[1] = fRec3[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fVec7[1] = fVec7[0];
			fRec2[1] = fRec2[0];
			fRec43[1] = fRec43[0];
			fVec8[1] = fVec8[0];
			fRec44[1] = fRec44[0];
			fVec9[1] = fVec9[0];
			fRec1[1] = fRec1[0];
			fRec47[1] = fRec47[0];
			fRec46[1] = fRec46[0];
			fRec49[1] = fRec49[0];
			fVec10[1] = fVec10[0];
			fRec0[1] = fRec0[0];
			fRec52[1] = fRec52[0];
			fVec11[1] = fVec11[0];
			fRec50[1] = fRec50[0];
			fVec12[1] = fVec12[0];
			fRec75[1] = fRec75[0];
			fRec74[1] = fRec74[0];
			fRec73[1] = fRec73[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec81[1] = fRec81[0];
			fRec80[2] = fRec80[1];
			fRec80[1] = fRec80[0];
			fRec79[2] = fRec79[1];
			fRec79[1] = fRec79[0];
			fRec78[2] = fRec78[1];
			fRec78[1] = fRec78[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
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
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];

		}

	}


};

#endif
