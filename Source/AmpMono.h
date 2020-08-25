/* ------------------------------------------------------------
name: "AmpMono"
Code generated with Faust 2.14.4 (https://faust.grame.fr)
Compilation options: -scal -ftz 0
------------------------------------------------------------ */

#ifndef __AmpMono_H__
#define __AmpMono_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <algorithm>
#include <cmath>
#include <math.h>

static float AmpMono_faustpower2_f(float value) { return (value * value); }
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
  FAUSTFLOAT fEntry2;
  int fSamplingFreq;
  float fConst0;
  float fConst1;
  float fConst2;
  float fConst3;
  float fConst4;
  FAUSTFLOAT fEntry3;
  float fConst5;
  float fConst6;
  FAUSTFLOAT fEntry4;
  float fConst7;
  float fConst8;
  FAUSTFLOAT fEntry5;
  FAUSTFLOAT fEntry6;
  FAUSTFLOAT fEntry7;
  FAUSTFLOAT fEntry8;
  FAUSTFLOAT fEntry9;
  FAUSTFLOAT fEntry10;
  float fConst9;
  float fConst10;
  float fConst11;
  float fConst12;
  FAUSTFLOAT fEntry11;
  FAUSTFLOAT fEntry12;
  FAUSTFLOAT fEntry13;
  FAUSTFLOAT fEntry14;
  float fConst13;
  FAUSTFLOAT fEntry15;
  FAUSTFLOAT fEntry16;
  FAUSTFLOAT fEntry17;
  FAUSTFLOAT fEntry18;
  FAUSTFLOAT fEntry19;
  FAUSTFLOAT fEntry20;
  FAUSTFLOAT fEntry21;
  FAUSTFLOAT fEntry22;
  FAUSTFLOAT fEntry23;
  float fConst14;
  FAUSTFLOAT fEntry24;
  FAUSTFLOAT fEntry25;
  FAUSTFLOAT fEntry26;
  float fConst15;
  float fConst16;
  float fConst17;
  FAUSTFLOAT fEntry27;
  FAUSTFLOAT fEntry28;
  float fVec0[2];
  float fRec20[2];
  float fConst18;
  FAUSTFLOAT fEntry29;
  FAUSTFLOAT fEntry30;
  float fConst19;
  FAUSTFLOAT fEntry31;
  FAUSTFLOAT fEntry32;
  FAUSTFLOAT fEntry33;
  float fRec22[2];
  float fRec21[2];
  FAUSTFLOAT fEntry34;
  float fConst20;
  FAUSTFLOAT fEntry35;
  FAUSTFLOAT fEntry36;
  float fRec23[2];
  FAUSTFLOAT fEntry37;
  float fRec19[2];
  float fVec1[2];
  float fRec18[2];
  float fVec2[2];
  float fRec17[2];
  float fConst21;
  float fConst22;
  float fRec25[2];
  float fRec24[2];
  float fConst23;
  float fRec26[2];
  float fConst24;
  float fRec27[2];
  float fVec3[2];
  float fRec16[2];
  float fVec4[2];
  float fRec15[2];
  float fConst25;
  float fRec29[2];
  float fRec28[2];
  float fRec30[2];
  float fRec14[2];
  float fVec5[2];
  float fRec13[2];
  float fVec6[2];
  float fRec36[2];
  float fRec38[2];
  float fRec37[2];
  float fRec39[2];
  float fRec35[2];
  float fVec7[2];
  float fRec34[2];
  float fVec8[2];
  float fRec33[2];
  float fRec41[2];
  float fRec40[2];
  float fRec42[2];
  float fRec32[2];
  float fVec9[2];
  float fRec31[2];
  float fVec10[2];
  float fRec12[2];
  float fRec44[2];
  float fRec43[2];
  float fRec45[2];
  float fRec46[2];
  float fVec11[2];
  float fRec11[2];
  float fVec12[2];
  float fRec10[2];
  float fRec48[2];
  float fRec47[2];
  float fRec49[2];
  float fRec9[2];
  float fVec13[2];
  float fRec8[2];
  float fVec14[2];
  float fRec7[2];
  float fRec50[2];
  float fVec15[2];
  float fConst26;
  float fConst27;
  float fRec6[2];
  float fConst28;
  float fConst29;
  float fConst30;
  FAUSTFLOAT fEntry38;
  float fConst31;
  float fConst32;
  float fRec5[3];
  float fConst33;
  float fRec4[3];
  float fVec16[2];
  float fRec3[2];
  float fRec51[2];
  float fConst34;
  float fConst35;
  float fConst36;
  FAUSTFLOAT fEntry39;
  float fConst37;
  float fRec2[3];
  FAUSTFLOAT fEntry40;
  float fVec17[2];
  float fRec1[2];
  FAUSTFLOAT fEntry41;
  FAUSTFLOAT fEntry42;
  float fRec52[2];
  FAUSTFLOAT fEntry43;
  FAUSTFLOAT fEntry44;
  FAUSTFLOAT fEntry45;
  FAUSTFLOAT fEntry46;
  float fRec53[2];
  FAUSTFLOAT fEntry47;
  FAUSTFLOAT fEntry48;
  FAUSTFLOAT fEntry49;
  float fRec54[2];
  FAUSTFLOAT fEntry50;
  FAUSTFLOAT fEntry51;
  FAUSTFLOAT fEntry52;
  float fRec55[2];
  FAUSTFLOAT fEntry53;
  float fRec57[2];
  float fRec56[2];
  FAUSTFLOAT fEntry54;
  FAUSTFLOAT fEntry55;
  FAUSTFLOAT fEntry56;
  float fRec58[2];
  float fConst38;
  float fRec0[3];
  FAUSTFLOAT fEntry57;
  FAUSTFLOAT fEntry58;
  float fRec59[2];
  FAUSTFLOAT fEntry59;
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
  float fRec82[3];
  float fConst146;
  float fRec81[3];
  float fVec18[2];
  float fRec80[2];
  float fConst147;
  float fConst148;
  float fRec79[3];
  float fVec19[2];
  float fConst149;
  float fConst150;
  float fConst151;
  float fRec78[2];
  float fConst152;
  float fConst153;
  float fRec77[3];
  float fConst154;
  float fConst155;
  float fRec76[3];
  float fConst156;
  float fRec75[3];
  float fConst157;
  float fRec86[2];
  float fRec85[3];
  float fRec84[3];
  float fRec83[3];
  float fConst158;
  float fConst159;
  float fRec74[3];
  float fConst160;
  float fConst161;
  float fConst162;
  float fRec73[3];
  float fConst163;
  float fConst164;
  float fConst165;
  float fRec72[3];
  float fConst166;
  float fConst167;
  float fRec71[3];
  float fConst168;
  float fConst169;
  float fConst170;
  float fConst171;
  float fConst172;
  float fRec70[3];
  float fConst173;
  float fConst174;
  float fConst175;
  float fRec69[3];
  float fConst176;
  float fConst177;
  float fConst178;
  float fRec68[3];
  float fConst179;
  float fConst180;
  float fRec67[3];
  float fConst181;
  float fConst182;
  float fConst183;
  float fConst184;
  float fConst185;
  float fRec66[3];
  float fConst186;
  float fConst187;
  float fConst188;
  float fRec65[3];
  float fConst189;
  float fVec20[2];
  float fConst190;
  float fConst191;
  float fConst192;
  float fRec64[2];
  float fConst193;
  float fConst194;
  float fConst195;
  float fRec63[3];
  FAUSTFLOAT fEntry60;
  float fConst196;
  float fRec88[2];
  float fRec87[3];
  float fConst197;
  float fConst198;
  float fRec62[3];
  float fConst199;
  float fRec61[3];
  float fConst200;
  float fConst201;
  float fRec60[3];

public:
  virtual int getNumInputs() { return 1; }
  virtual int getNumOutputs() { return 1; }
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

  static void classInit(int samplingFreq) {}

  virtual void instanceConstants(int samplingFreq) {
    fSamplingFreq = samplingFreq;
    fConst0 =
        std::min<float>(192000.0f, std::max<float>(1.0f, float(fSamplingFreq)));
    fConst1 = (2.0f / fConst0);
    fConst2 = (2.0f * fConst0);
    fConst3 = (3.14159274f / fConst0);
    fConst4 = (0.5f * fConst0);
    fConst5 = (0.5f / fConst0);
    fConst6 = (4.0f * AmpMono_faustpower2_f(fConst0));
    fConst7 = (1.0f / fConst0);
    fConst8 = AmpMono_faustpower2_f(fConst7);
    fConst9 = std::tan((31.415926f / fConst0));
    fConst10 = (1.0f / fConst9);
    fConst11 = (fConst10 + 1.0f);
    fConst12 = (0.0f - (1.0f / (fConst9 * fConst11)));
    fConst13 = (0.889999986f * fConst0);
    fConst14 = (3.39292002f / fConst0);
    fConst15 = (3.48716784f / fConst0);
    fConst16 = (1.13f * fConst0);
    fConst17 = (2.70176959f / fConst0);
    fConst18 = (0.874800026f * fConst0);
    fConst19 = (0.810000002f * fConst0);
    fConst20 = (1.16279066f / fConst0);
    fConst21 = (0.864799976f * fConst0);
    fConst22 = (0.920000017f * fConst0);
    fConst23 = (1.12359548f / fConst0);
    fConst24 = (0.980000019f * fConst0);
    fConst25 = (0.959999979f * fConst0);
    fConst26 = (1.0f / fConst11);
    fConst27 = (1.0f - fConst10);
    fConst28 = std::tan((1570.79639f / fConst0));
    fConst29 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst28))));
    fConst30 = (1.0f / fConst28);
    fConst31 = (fConst0 * std::sin((3141.59277f / fConst0)));
    fConst32 = (3.14159274f / fConst31);
    fConst33 = (3141.59277f / fConst31);
    fConst34 = std::tan((12566.3711f / fConst0));
    fConst35 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst34))));
    fConst36 = (1.0f / fConst34);
    fConst37 = (6283.18555f / (fConst0 * std::sin((25132.7422f / fConst0))));
    fConst38 = (2.0f * fConst8);
    fConst39 = std::tan((3769.91113f / fConst0));
    fConst40 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst39))));
    fConst41 = std::tan((219.911484f / fConst0));
    fConst42 = (1.0f / fConst41);
    fConst43 = (314.159271f / (fConst0 * std::sin((439.822968f / fConst0))));
    fConst44 = std::tan((18849.5566f / fConst0));
    fConst45 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst44))));
    fConst46 = std::tan((3455.75195f / fConst0));
    fConst47 = (1.0f / fConst46);
    fConst48 = (1.0f / (((fConst47 + 1.0f) / fConst46) + 1.0f));
    fConst49 = AmpMono_faustpower2_f(fConst46);
    fConst50 = (0.0f - (2.0f / fConst49));
    fConst51 = std::tan((2984.51294f / fConst0));
    fConst52 = (1.0f / fConst51);
    fConst53 = (fConst0 * std::sin((5969.02588f / fConst0)));
    fConst54 = (27816.8476f / fConst53);
    fConst55 = (1.0f / (((fConst52 + fConst54) / fConst51) + 1.0f));
    fConst56 = (fConst47 + 1.0f);
    fConst57 = (1.0f / (fConst46 * fConst56));
    fConst58 = (8796.45898f / fConst53);
    fConst59 = (((fConst52 - fConst58) / fConst51) + 1.0f);
    fConst60 = (37699.1133f / fConst0);
    fConst61 = std::tan(fConst60);
    fConst62 = (1.0f / fConst61);
    fConst63 = (fConst0 * std::sin((75398.2266f / fConst0)));
    fConst64 = (24836.4707f / fConst63);
    fConst65 = (1.0f / (((fConst62 + fConst64) / fConst61) + 1.0f));
    fConst66 = (785.398193f / fConst63);
    fConst67 = (((fConst62 - fConst66) / fConst61) + 1.0f);
    fConst68 = std::tan((21362.8301f / fConst0));
    fConst69 = (1.0f / fConst68);
    fConst70 = (fConst0 * std::sin((42725.6602f / fConst0)));
    fConst71 = (19869.1758f / fConst70);
    fConst72 = (1.0f / (((fConst69 + fConst71) / fConst68) + 1.0f));
    fConst73 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst68))));
    fConst74 = std::tan((11938.0518f / fConst0));
    fConst75 = (1.0f / fConst74);
    fConst76 = (fConst0 * std::sin((23876.1035f / fConst0)));
    fConst77 = (4701.22607f / fConst76);
    fConst78 = (1.0f / (((fConst75 + fConst77) / fConst74) + 1.0f));
    fConst79 = (2356.19458f / fConst76);
    fConst80 = (((fConst75 + fConst79) / fConst74) + 1.0f);
    fConst81 = std::tan((9581.85742f / fConst0));
    fConst82 = (1.0f / fConst81);
    fConst83 = (fConst0 * std::sin((19163.7148f / fConst0)));
    fConst84 = (2921.88965f / fConst83);
    fConst85 = (1.0f / (((fConst82 + fConst84) / fConst81) + 1.0f));
    fConst86 = (1036.72558f / fConst83);
    fConst87 = (((fConst82 + fConst86) / fConst81) + 1.0f);
    fConst88 = std::tan((5215.04394f / fConst0));
    fConst89 = (1.0f / fConst88);
    fConst90 = (fConst0 * std::sin((10430.0879f / fConst0)));
    fConst91 = (3713.44482f / fConst90);
    fConst92 = (1.0f / (((fConst89 + fConst91) / fConst88) + 1.0f));
    fConst93 = (2481.85815f / fConst90);
    fConst94 = (((fConst89 - fConst93) / fConst88) + 1.0f);
    fConst95 = (3707.07935f / fConst0);
    fConst96 = std::tan(fConst95);
    fConst97 = (1.0f / fConst96);
    fConst98 = (fConst0 * std::sin((7414.15869f / fConst0)));
    fConst99 = (502.654816f / fConst98);
    fConst100 = (1.0f / (((fConst97 + fConst99) / fConst96) + 1.0f));
    fConst101 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst96))));
    fConst102 = std::tan((3518.58374f / fConst0));
    fConst103 = (1.0f / fConst102);
    fConst104 = (fConst0 * std::sin((7037.16748f / fConst0)));
    fConst105 = (875.483398f / fConst104);
    fConst106 = (1.0f / (((fConst103 + fConst105) / fConst102) + 1.0f));
    fConst107 = (219.911484f / fConst104);
    fConst108 = (((fConst103 + fConst107) / fConst102) + 1.0f);
    fConst109 = std::tan((2010.61926f / fConst0));
    fConst110 = (1.0f / fConst109);
    fConst111 = (fConst0 * std::sin((4021.23853f / fConst0)));
    fConst112 = (439.822968f / fConst111);
    fConst113 = (1.0f / (((fConst110 + fConst112) / fConst109) + 1.0f));
    fConst114 = (1390.84241f / fConst111);
    fConst115 = (((fConst110 - fConst114) / fConst109) + 1.0f);
    fConst116 = std::tan((1853.53967f / fConst0));
    fConst117 = (1.0f / fConst116);
    fConst118 = (fConst0 * std::sin(fConst95));
    fConst119 = (1059.9884f / fConst118);
    fConst120 = (1.0f / (((fConst117 + fConst119) / fConst116) + 1.0f));
    fConst121 = (188.49556f / fConst118);
    fConst122 = (((fConst117 - fConst121) / fConst116) + 1.0f);
    fConst123 = std::tan((17592.918f / fConst0));
    fConst124 = (1.0f / fConst123);
    fConst125 = (1.0f / (((fConst124 + 0.445041865f) / fConst123) + 1.0f));
    fConst126 = AmpMono_faustpower2_f(fConst123);
    fConst127 = (1.0f / fConst126);
    fConst128 = (1.0f / (((fConst124 + 1.24697959f) / fConst123) + 1.0f));
    fConst129 = (1.0f / (((fConst124 + 1.8019377f) / fConst123) + 1.0f));
    fConst130 = std::tan((34557.5195f / fConst0));
    fConst131 = (1.0f / fConst130);
    fConst132 = (1.0f / (((fConst131 + 1.0f) / fConst130) + 1.0f));
    fConst133 = (fConst124 + 1.0f);
    fConst134 = (1.0f / (fConst123 * fConst133));
    fConst135 = (1.0f / (fConst131 + 1.0f));
    fConst136 = (1.0f - fConst131);
    fConst137 = std::tan((345.575195f / fConst0));
    fConst138 = (1.0f / fConst137);
    fConst139 = (1.0f / (((fConst138 + 0.765366852f) / fConst137) + 1.0f));
    fConst140 = AmpMono_faustpower2_f(fConst137);
    fConst141 = (0.0f - (2.0f / fConst140));
    fConst142 = (1.0f / (((fConst138 + 1.84775901f) / fConst137) + 1.0f));
    fConst143 = (1.0f / fConst140);
    fConst144 = (((fConst138 + -1.84775901f) / fConst137) + 1.0f);
    fConst145 = (2.0f * (1.0f - fConst143));
    fConst146 = (((fConst138 + -0.765366852f) / fConst137) + 1.0f);
    fConst147 = (((fConst131 + -1.0f) / fConst130) + 1.0f);
    fConst148 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst130))));
    fConst149 = (0.0f - fConst134);
    fConst150 = (1.0f - fConst124);
    fConst151 = (fConst150 / fConst133);
    fConst152 = (((fConst124 + -1.8019377f) / fConst123) + 1.0f);
    fConst153 = (2.0f * (1.0f - fConst127));
    fConst154 = (0.0f - (2.0f / fConst126));
    fConst155 = (((fConst124 + -1.24697959f) / fConst123) + 1.0f);
    fConst156 = (((fConst124 + -0.445041865f) / fConst123) + 1.0f);
    fConst157 = (1.0f / fConst133);
    fConst158 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst116))));
    fConst159 = (((fConst117 - fConst119) / fConst116) + 1.0f);
    fConst160 = (((fConst117 + fConst121) / fConst116) + 1.0f);
    fConst161 = (((fConst110 - fConst112) / fConst109) + 1.0f);
    fConst162 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst109))));
    fConst163 = (((fConst110 + fConst114) / fConst109) + 1.0f);
    fConst164 = (((fConst103 - fConst105) / fConst102) + 1.0f);
    fConst165 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst102))));
    fConst166 = (((fConst103 - fConst107) / fConst102) + 1.0f);
    fConst167 = (((fConst97 - fConst99) / fConst96) + 1.0f);
    fConst168 = (1416.67383f / fConst98);
    fConst169 = (((fConst97 + fConst168) / fConst96) + 1.0f);
    fConst170 = (((fConst97 - fConst168) / fConst96) + 1.0f);
    fConst171 = (((fConst89 - fConst91) / fConst88) + 1.0f);
    fConst172 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst88))));
    fConst173 = (((fConst89 + fConst93) / fConst88) + 1.0f);
    fConst174 = (((fConst82 - fConst84) / fConst81) + 1.0f);
    fConst175 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst81))));
    fConst176 = (((fConst82 - fConst86) / fConst81) + 1.0f);
    fConst177 = (((fConst75 - fConst77) / fConst74) + 1.0f);
    fConst178 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst74))));
    fConst179 = (((fConst75 - fConst79) / fConst74) + 1.0f);
    fConst180 = (((fConst69 - fConst71) / fConst68) + 1.0f);
    fConst181 = (628.318542f / fConst70);
    fConst182 = (((fConst69 + fConst181) / fConst68) + 1.0f);
    fConst183 = (((fConst69 - fConst181) / fConst68) + 1.0f);
    fConst184 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst61))));
    fConst185 = (((fConst62 - fConst64) / fConst61) + 1.0f);
    fConst186 = (((fConst62 + fConst66) / fConst61) + 1.0f);
    fConst187 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst51))));
    fConst188 = (((fConst52 - fConst54) / fConst51) + 1.0f);
    fConst189 = (((fConst52 + fConst58) / fConst51) + 1.0f);
    fConst190 = (0.0f - fConst57);
    fConst191 = (1.0f - fConst47);
    fConst192 = (fConst191 / fConst56);
    fConst193 = (((fConst47 + -1.0f) / fConst46) + 1.0f);
    fConst194 = (1.0f / fConst49);
    fConst195 = (2.0f * (1.0f - fConst194));
    fConst196 = (1.0f / fConst56);
    fConst197 = (1.0f / fConst44);
    fConst198 = (3141.59277f / (fConst0 * std::sin(fConst60)));
    fConst199 = (2.0f * (1.0f - (1.0f / AmpMono_faustpower2_f(fConst41))));
    fConst200 = (1.0f / fConst39);
    fConst201 = (942.477783f / (fConst0 * std::sin((7539.82226f / fConst0))));
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
    fEntry51 = FAUSTFLOAT(0.0f);
    fEntry52 = FAUSTFLOAT(0.0f);
    fEntry53 = FAUSTFLOAT(0.0f);
    fEntry54 = FAUSTFLOAT(0.0f);
    fEntry55 = FAUSTFLOAT(0.0f);
    fEntry56 = FAUSTFLOAT(0.0f);
    fEntry57 = FAUSTFLOAT(0.0f);
    fEntry58 = FAUSTFLOAT(0.0f);
    fEntry59 = FAUSTFLOAT(0.0f);
    fEntry60 = FAUSTFLOAT(0.0f);

    zero_all();
  }

  virtual void instanceClear() {
    for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
      fVec0[l0] = 0.0f;
    }
    for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
      fRec20[l1] = 0.0f;
    }
    for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
      fRec22[l2] = 0.0f;
    }
    for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
      fRec21[l3] = 0.0f;
    }
    for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
      fRec23[l4] = 0.0f;
    }
    for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
      fRec19[l5] = 0.0f;
    }
    for (int l6 = 0; (l6 < 2); l6 = (l6 + 1)) {
      fVec1[l6] = 0.0f;
    }
    for (int l7 = 0; (l7 < 2); l7 = (l7 + 1)) {
      fRec18[l7] = 0.0f;
    }
    for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
      fVec2[l8] = 0.0f;
    }
    for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
      fRec17[l9] = 0.0f;
    }
    for (int l10 = 0; (l10 < 2); l10 = (l10 + 1)) {
      fRec25[l10] = 0.0f;
    }
    for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
      fRec24[l11] = 0.0f;
    }
    for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
      fRec26[l12] = 0.0f;
    }
    for (int l13 = 0; (l13 < 2); l13 = (l13 + 1)) {
      fRec27[l13] = 0.0f;
    }
    for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
      fVec3[l14] = 0.0f;
    }
    for (int l15 = 0; (l15 < 2); l15 = (l15 + 1)) {
      fRec16[l15] = 0.0f;
    }
    for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
      fVec4[l16] = 0.0f;
    }
    for (int l17 = 0; (l17 < 2); l17 = (l17 + 1)) {
      fRec15[l17] = 0.0f;
    }
    for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
      fRec29[l18] = 0.0f;
    }
    for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
      fRec28[l19] = 0.0f;
    }
    for (int l20 = 0; (l20 < 2); l20 = (l20 + 1)) {
      fRec30[l20] = 0.0f;
    }
    for (int l21 = 0; (l21 < 2); l21 = (l21 + 1)) {
      fRec14[l21] = 0.0f;
    }
    for (int l22 = 0; (l22 < 2); l22 = (l22 + 1)) {
      fVec5[l22] = 0.0f;
    }
    for (int l23 = 0; (l23 < 2); l23 = (l23 + 1)) {
      fRec13[l23] = 0.0f;
    }
    for (int l24 = 0; (l24 < 2); l24 = (l24 + 1)) {
      fVec6[l24] = 0.0f;
    }
    for (int l25 = 0; (l25 < 2); l25 = (l25 + 1)) {
      fRec36[l25] = 0.0f;
    }
    for (int l26 = 0; (l26 < 2); l26 = (l26 + 1)) {
      fRec38[l26] = 0.0f;
    }
    for (int l27 = 0; (l27 < 2); l27 = (l27 + 1)) {
      fRec37[l27] = 0.0f;
    }
    for (int l28 = 0; (l28 < 2); l28 = (l28 + 1)) {
      fRec39[l28] = 0.0f;
    }
    for (int l29 = 0; (l29 < 2); l29 = (l29 + 1)) {
      fRec35[l29] = 0.0f;
    }
    for (int l30 = 0; (l30 < 2); l30 = (l30 + 1)) {
      fVec7[l30] = 0.0f;
    }
    for (int l31 = 0; (l31 < 2); l31 = (l31 + 1)) {
      fRec34[l31] = 0.0f;
    }
    for (int l32 = 0; (l32 < 2); l32 = (l32 + 1)) {
      fVec8[l32] = 0.0f;
    }
    for (int l33 = 0; (l33 < 2); l33 = (l33 + 1)) {
      fRec33[l33] = 0.0f;
    }
    for (int l34 = 0; (l34 < 2); l34 = (l34 + 1)) {
      fRec41[l34] = 0.0f;
    }
    for (int l35 = 0; (l35 < 2); l35 = (l35 + 1)) {
      fRec40[l35] = 0.0f;
    }
    for (int l36 = 0; (l36 < 2); l36 = (l36 + 1)) {
      fRec42[l36] = 0.0f;
    }
    for (int l37 = 0; (l37 < 2); l37 = (l37 + 1)) {
      fRec32[l37] = 0.0f;
    }
    for (int l38 = 0; (l38 < 2); l38 = (l38 + 1)) {
      fVec9[l38] = 0.0f;
    }
    for (int l39 = 0; (l39 < 2); l39 = (l39 + 1)) {
      fRec31[l39] = 0.0f;
    }
    for (int l40 = 0; (l40 < 2); l40 = (l40 + 1)) {
      fVec10[l40] = 0.0f;
    }
    for (int l41 = 0; (l41 < 2); l41 = (l41 + 1)) {
      fRec12[l41] = 0.0f;
    }
    for (int l42 = 0; (l42 < 2); l42 = (l42 + 1)) {
      fRec44[l42] = 0.0f;
    }
    for (int l43 = 0; (l43 < 2); l43 = (l43 + 1)) {
      fRec43[l43] = 0.0f;
    }
    for (int l44 = 0; (l44 < 2); l44 = (l44 + 1)) {
      fRec45[l44] = 0.0f;
    }
    for (int l45 = 0; (l45 < 2); l45 = (l45 + 1)) {
      fRec46[l45] = 0.0f;
    }
    for (int l46 = 0; (l46 < 2); l46 = (l46 + 1)) {
      fVec11[l46] = 0.0f;
    }
    for (int l47 = 0; (l47 < 2); l47 = (l47 + 1)) {
      fRec11[l47] = 0.0f;
    }
    for (int l48 = 0; (l48 < 2); l48 = (l48 + 1)) {
      fVec12[l48] = 0.0f;
    }
    for (int l49 = 0; (l49 < 2); l49 = (l49 + 1)) {
      fRec10[l49] = 0.0f;
    }
    for (int l50 = 0; (l50 < 2); l50 = (l50 + 1)) {
      fRec48[l50] = 0.0f;
    }
    for (int l51 = 0; (l51 < 2); l51 = (l51 + 1)) {
      fRec47[l51] = 0.0f;
    }
    for (int l52 = 0; (l52 < 2); l52 = (l52 + 1)) {
      fRec49[l52] = 0.0f;
    }
    for (int l53 = 0; (l53 < 2); l53 = (l53 + 1)) {
      fRec9[l53] = 0.0f;
    }
    for (int l54 = 0; (l54 < 2); l54 = (l54 + 1)) {
      fVec13[l54] = 0.0f;
    }
    for (int l55 = 0; (l55 < 2); l55 = (l55 + 1)) {
      fRec8[l55] = 0.0f;
    }
    for (int l56 = 0; (l56 < 2); l56 = (l56 + 1)) {
      fVec14[l56] = 0.0f;
    }
    for (int l57 = 0; (l57 < 2); l57 = (l57 + 1)) {
      fRec7[l57] = 0.0f;
    }
    for (int l58 = 0; (l58 < 2); l58 = (l58 + 1)) {
      fRec50[l58] = 0.0f;
    }
    for (int l59 = 0; (l59 < 2); l59 = (l59 + 1)) {
      fVec15[l59] = 0.0f;
    }
    for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
      fRec6[l60] = 0.0f;
    }
    for (int l61 = 0; (l61 < 3); l61 = (l61 + 1)) {
      fRec5[l61] = 0.0f;
    }
    for (int l62 = 0; (l62 < 3); l62 = (l62 + 1)) {
      fRec4[l62] = 0.0f;
    }
    for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
      fVec16[l63] = 0.0f;
    }
    for (int l64 = 0; (l64 < 2); l64 = (l64 + 1)) {
      fRec3[l64] = 0.0f;
    }
    for (int l65 = 0; (l65 < 2); l65 = (l65 + 1)) {
      fRec51[l65] = 0.0f;
    }
    for (int l66 = 0; (l66 < 3); l66 = (l66 + 1)) {
      fRec2[l66] = 0.0f;
    }
    for (int l67 = 0; (l67 < 2); l67 = (l67 + 1)) {
      fVec17[l67] = 0.0f;
    }
    for (int l68 = 0; (l68 < 2); l68 = (l68 + 1)) {
      fRec1[l68] = 0.0f;
    }
    for (int l69 = 0; (l69 < 2); l69 = (l69 + 1)) {
      fRec52[l69] = 0.0f;
    }
    for (int l70 = 0; (l70 < 2); l70 = (l70 + 1)) {
      fRec53[l70] = 0.0f;
    }
    for (int l71 = 0; (l71 < 2); l71 = (l71 + 1)) {
      fRec54[l71] = 0.0f;
    }
    for (int l72 = 0; (l72 < 2); l72 = (l72 + 1)) {
      fRec55[l72] = 0.0f;
    }
    for (int l73 = 0; (l73 < 2); l73 = (l73 + 1)) {
      fRec57[l73] = 0.0f;
    }
    for (int l74 = 0; (l74 < 2); l74 = (l74 + 1)) {
      fRec56[l74] = 0.0f;
    }
    for (int l75 = 0; (l75 < 2); l75 = (l75 + 1)) {
      fRec58[l75] = 0.0f;
    }
    for (int l76 = 0; (l76 < 3); l76 = (l76 + 1)) {
      fRec0[l76] = 0.0f;
    }
    for (int l77 = 0; (l77 < 2); l77 = (l77 + 1)) {
      fRec59[l77] = 0.0f;
    }
    for (int l78 = 0; (l78 < 3); l78 = (l78 + 1)) {
      fRec82[l78] = 0.0f;
    }
    for (int l79 = 0; (l79 < 3); l79 = (l79 + 1)) {
      fRec81[l79] = 0.0f;
    }
    for (int l80 = 0; (l80 < 2); l80 = (l80 + 1)) {
      fVec18[l80] = 0.0f;
    }
    for (int l81 = 0; (l81 < 2); l81 = (l81 + 1)) {
      fRec80[l81] = 0.0f;
    }
    for (int l82 = 0; (l82 < 3); l82 = (l82 + 1)) {
      fRec79[l82] = 0.0f;
    }
    for (int l83 = 0; (l83 < 2); l83 = (l83 + 1)) {
      fVec19[l83] = 0.0f;
    }
    for (int l84 = 0; (l84 < 2); l84 = (l84 + 1)) {
      fRec78[l84] = 0.0f;
    }
    for (int l85 = 0; (l85 < 3); l85 = (l85 + 1)) {
      fRec77[l85] = 0.0f;
    }
    for (int l86 = 0; (l86 < 3); l86 = (l86 + 1)) {
      fRec76[l86] = 0.0f;
    }
    for (int l87 = 0; (l87 < 3); l87 = (l87 + 1)) {
      fRec75[l87] = 0.0f;
    }
    for (int l88 = 0; (l88 < 2); l88 = (l88 + 1)) {
      fRec86[l88] = 0.0f;
    }
    for (int l89 = 0; (l89 < 3); l89 = (l89 + 1)) {
      fRec85[l89] = 0.0f;
    }
    for (int l90 = 0; (l90 < 3); l90 = (l90 + 1)) {
      fRec84[l90] = 0.0f;
    }
    for (int l91 = 0; (l91 < 3); l91 = (l91 + 1)) {
      fRec83[l91] = 0.0f;
    }
    for (int l92 = 0; (l92 < 3); l92 = (l92 + 1)) {
      fRec74[l92] = 0.0f;
    }
    for (int l93 = 0; (l93 < 3); l93 = (l93 + 1)) {
      fRec73[l93] = 0.0f;
    }
    for (int l94 = 0; (l94 < 3); l94 = (l94 + 1)) {
      fRec72[l94] = 0.0f;
    }
    for (int l95 = 0; (l95 < 3); l95 = (l95 + 1)) {
      fRec71[l95] = 0.0f;
    }
    for (int l96 = 0; (l96 < 3); l96 = (l96 + 1)) {
      fRec70[l96] = 0.0f;
    }
    for (int l97 = 0; (l97 < 3); l97 = (l97 + 1)) {
      fRec69[l97] = 0.0f;
    }
    for (int l98 = 0; (l98 < 3); l98 = (l98 + 1)) {
      fRec68[l98] = 0.0f;
    }
    for (int l99 = 0; (l99 < 3); l99 = (l99 + 1)) {
      fRec67[l99] = 0.0f;
    }
    for (int l100 = 0; (l100 < 3); l100 = (l100 + 1)) {
      fRec66[l100] = 0.0f;
    }
    for (int l101 = 0; (l101 < 3); l101 = (l101 + 1)) {
      fRec65[l101] = 0.0f;
    }
    for (int l102 = 0; (l102 < 2); l102 = (l102 + 1)) {
      fVec20[l102] = 0.0f;
    }
    for (int l103 = 0; (l103 < 2); l103 = (l103 + 1)) {
      fRec64[l103] = 0.0f;
    }
    for (int l104 = 0; (l104 < 3); l104 = (l104 + 1)) {
      fRec63[l104] = 0.0f;
    }
    for (int l105 = 0; (l105 < 2); l105 = (l105 + 1)) {
      fRec88[l105] = 0.0f;
    }
    for (int l106 = 0; (l106 < 3); l106 = (l106 + 1)) {
      fRec87[l106] = 0.0f;
    }
    for (int l107 = 0; (l107 < 3); l107 = (l107 + 1)) {
      fRec62[l107] = 0.0f;
    }
    for (int l108 = 0; (l108 < 3); l108 = (l108 + 1)) {
      fRec61[l108] = 0.0f;
    }
    for (int l109 = 0; (l109 < 3); l109 = (l109 + 1)) {
      fRec60[l109] = 0.0f;
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

  virtual AmpMono *clone() { return new AmpMono(); }
  virtual int getSampleRate() { return fSamplingFreq; }

  void set_cab_brightness(FAUSTFLOAT value) {
    fEntry60 = value + 0.000000e+00f;
  }
  void set_cab_distance(FAUSTFLOAT value) { fEntry59 = value + 0.000000e+00f; }
  void set_cab_on_off(FAUSTFLOAT value) { fEntry1 = value + 0.000000e+00f; }
  void set_gain_slope(FAUSTFLOAT value) { fEntry13 = value + 0.000000e+00f; }
  void set_gain_stages(FAUSTFLOAT value) { fEntry12 = value + 0.000000e+00f; }
  void set_input_level(FAUSTFLOAT value) { fEntry28 = value + 0.000000e+00f; }
  void set_output_level(FAUSTFLOAT value) { fEntry0 = value + 0.000000e+00f; }
  void set_power_drive(FAUSTFLOAT value) { fEntry9 = value + 0.000000e+00f; }
  void set_pre_drive(FAUSTFLOAT value) { fEntry27 = value + 0.000000e+00f; }
  void set_tetrode_grid_cap(FAUSTFLOAT value) {
    fEntry44 = value + 2.464347e+00f;
  }
  void set_tetrode_grid_level(FAUSTFLOAT value) {
    fEntry45 = value + 4.247939e-01f;
  }
  void set_tetrode_grid_offset1(FAUSTFLOAT value) {
    fEntry40 = value + 4.772563e-02f;
  }
  void set_tetrode_grid_offset2(FAUSTFLOAT value) {
    fEntry42 = value + -2.047726e+00f;
  }
  void set_tetrode_grid_ratio(FAUSTFLOAT value) {
    fEntry46 = value + 6.315747e-01f;
  }
  void set_tetrode_grid_tau(FAUSTFLOAT value) {
    fEntry43 = value + -6.191922e-01f;
  }
  void set_tetrode_grid_taus(FAUSTFLOAT value) {
    fEntry41 = value + -3.828938e-05f;
  }
  void set_tetrode_hp_freq(FAUSTFLOAT value) {
    fEntry4 = value + -2.881448e+00f;
  }
  void set_tetrode_lp_freq(FAUSTFLOAT value) {
    fEntry3 = value + 4.861658e-01f;
  }
  void set_tetrode_plate_clip(FAUSTFLOAT value) {
    fEntry50 = value + 5.106009e-01f;
  }
  void set_tetrode_plate_clip_corner(FAUSTFLOAT value) {
    fEntry7 = value + 1.071034e+00f;
  }
  void set_tetrode_plate_comp_depth(FAUSTFLOAT value) {
    fEntry51 = value + -5.419920e-01f;
  }
  void set_tetrode_plate_comp_tau(FAUSTFLOAT value) {
    fEntry52 = value + -1.311079e+00f;
  }
  void set_tetrode_plate_cross_corner(FAUSTFLOAT value) {
    fEntry53 = value + 5.972299e-01f;
  }
  void set_tetrode_plate_drift2_depth(FAUSTFLOAT value) {
    fEntry57 = value + -1.112544e-02f;
  }
  void set_tetrode_plate_drift2_level(FAUSTFLOAT value) {
    fEntry58 = value + 5.639156e-01f;
  }
  void set_tetrode_plate_drift_depth(FAUSTFLOAT value) {
    fEntry47 = value + 1.738535e-01f;
  }
  void set_tetrode_plate_drift_level(FAUSTFLOAT value) {
    fEntry49 = value + 1.148487e+00f;
  }
  void set_tetrode_plate_drift_tau(FAUSTFLOAT value) {
    fEntry48 = value + -2.438887e-01f;
  }
  void set_tetrode_plate_sag_depth(FAUSTFLOAT value) {
    fEntry6 = value + 0.000000e+00f;
  }
  void set_tetrode_plate_sag_onset(FAUSTFLOAT value) {
    fEntry55 = value + 0.000000e+00f;
  }
  void set_tetrode_plate_sag_ratio(FAUSTFLOAT value) {
    fEntry56 = value + 0.000000e+00f;
  }
  void set_tetrode_plate_sag_tau(FAUSTFLOAT value) {
    fEntry54 = value + 0.000000e+00f;
  }
  void set_tetrode_plate_sag_toggle(FAUSTFLOAT value) {
    fEntry5 = value + -1.000000e+00f;
  }
  void set_tetrode_plate_scale(FAUSTFLOAT value) {
    fEntry8 = value + 3.358314e-01f;
  }
  void set_triode_grid_cap(FAUSTFLOAT value) {
    fEntry31 = value + 1.743836e+00f;
  }
  void set_triode_grid_clip(FAUSTFLOAT value) {
    fEntry22 = value + 5.547782e-01f;
  }
  void set_triode_grid_corner(FAUSTFLOAT value) {
    fEntry23 = value + 1.641426e-01f;
  }
  void set_triode_grid_level(FAUSTFLOAT value) {
    fEntry32 = value + 3.352703e-01f;
  }
  void set_triode_grid_ratio(FAUSTFLOAT value) {
    fEntry33 = value + 1.209338e+00f;
  }
  void set_triode_grid_smooth(FAUSTFLOAT value) {
    fEntry30 = value + 1.510794e+00f;
  }
  void set_triode_grid_tau(FAUSTFLOAT value) {
    fEntry29 = value + -1.357839e+00f;
  }
  void set_triode_hp_freq(FAUSTFLOAT value) {
    fEntry24 = value + 4.527303e-01f;
  }
  void set_triode_plate_bias(FAUSTFLOAT value) {
    fEntry19 = value + 2.364891e+00f;
  }
  void set_triode_plate_bias_corner(FAUSTFLOAT value) {
    fEntry21 = value + 4.887126e-01f;
  }
  void set_triode_plate_clip(FAUSTFLOAT value) {
    fEntry18 = value + -1.077285e+00f;
  }
  void set_triode_plate_comp_cap(FAUSTFLOAT value) {
    fEntry16 = value + 2.530666e+00f;
  }
  void set_triode_plate_comp_corner(FAUSTFLOAT value) {
    fEntry25 = value + 1.733029e-02f;
  }
  void set_triode_plate_comp_depth(FAUSTFLOAT value) {
    fEntry14 = value + -1.562768e-01f;
  }
  void set_triode_plate_comp_level(FAUSTFLOAT value) {
    fEntry17 = value + -1.007034e+00f;
  }
  void set_triode_plate_comp_offset(FAUSTFLOAT value) {
    fEntry26 = value + 0.000000e+00f;
  }
  void set_triode_plate_comp_ratio(FAUSTFLOAT value) {
    fEntry37 = value + 3.113354e+00f;
  }
  void set_triode_plate_comp_tau(FAUSTFLOAT value) {
    fEntry15 = value + -1.099083e+00f;
  }
  void set_triode_plate_corner(FAUSTFLOAT value) {
    fEntry20 = value + 2.359280e-01f;
  }
  void set_triode_plate_drift_depth(FAUSTFLOAT value) {
    fEntry34 = value + -8.258674e-01f;
  }
  void set_triode_plate_drift_level(FAUSTFLOAT value) {
    fEntry36 = value + 1.020547e-01f;
  }
  void set_triode_plate_drift_tau(FAUSTFLOAT value) {
    fEntry35 = value + -1.084001e+00f;
  }
  void set_triode_plate_scale(FAUSTFLOAT value) {
    fEntry2 = value + 1.524131e+00f;
  }
  void set_ts_high(FAUSTFLOAT value) { fEntry10 = value + 0.000000e+00f; }
  void set_ts_low(FAUSTFLOAT value) { fEntry11 = value + 0.000000e+00f; }
  void set_ts_mid(FAUSTFLOAT value) { fEntry38 = value + 0.000000e+00f; }
  void set_ts_presence(FAUSTFLOAT value) { fEntry39 = value + 0.000000e+00f; }
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
    set_tetrode_grid_cap(0.0f);
    set_tetrode_grid_level(0.0f);
    set_tetrode_grid_offset1(0.0f);
    set_tetrode_grid_offset2(0.0f);
    set_tetrode_grid_ratio(0.0f);
    set_tetrode_grid_tau(0.0f);
    set_tetrode_grid_taus(0.0f);
    set_tetrode_hp_freq(0.0f);
    set_tetrode_lp_freq(0.0f);
    set_tetrode_plate_clip(0.0f);
    set_tetrode_plate_clip_corner(0.0f);
    set_tetrode_plate_comp_depth(0.0f);
    set_tetrode_plate_comp_tau(0.0f);
    set_tetrode_plate_cross_corner(0.0f);
    set_tetrode_plate_drift2_depth(0.0f);
    set_tetrode_plate_drift2_level(0.0f);
    set_tetrode_plate_drift_depth(0.0f);
    set_tetrode_plate_drift_level(0.0f);
    set_tetrode_plate_drift_tau(0.0f);
    set_tetrode_plate_sag_depth(0.0f);
    set_tetrode_plate_sag_onset(0.0f);
    set_tetrode_plate_sag_ratio(0.0f);
    set_tetrode_plate_sag_tau(0.0f);
    set_tetrode_plate_sag_toggle(0.0f);
    set_tetrode_plate_scale(0.0f);
    set_triode_grid_cap(0.0f);
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
    set_triode_plate_comp_cap(0.0f);
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
    set_ts_presence(0.0f);
  }

  virtual void compute(int count, FAUSTFLOAT **inputs, FAUSTFLOAT **outputs) {
    FAUSTFLOAT *input0 = inputs[0];
    FAUSTFLOAT *output0 = outputs[0];
    float fSlow0 =
        std::pow(10.0f, (0.0500000007f *
                         (0.0f - (35.0f * (1.0f - (float(fEntry0) + 1.0f))))));
    int iSlow1 = (float(fEntry1) > 0.0f);
    float fSlow2 =
        std::exp(((2.30258512f * (float(fEntry2) + 1.0f)) + -2.30258512f));
    float fSlow3 = (1.0f / fSlow2);
    float fSlow4 = std::tan(
        (fConst3 *
         std::min<float>(fConst4,
                         std::exp(((0.549306154f * (float(fEntry3) + 1.0f)) +
                                   8.51719284f)))));
    float fSlow5 = (float(fEntry4) + 1.0f);
    float fSlow6 = AmpMono_faustpower2_f(std::sqrt(
        (fConst6 *
         (fSlow4 *
          std::tan((fConst3 *
                    std::min<float>(fConst4, std::exp(((1.15129256f * fSlow5) +
                                                       2.30258512f)))))))));
    float fSlow7 = ((fConst2 * fSlow4) - (fConst5 * (fSlow6 / fSlow4)));
    float fSlow8 = (fConst8 * fSlow6);
    float fSlow9 = (fConst1 * fSlow7);
    float fSlow10 = ((fSlow8 + fSlow9) + 4.0f);
    float fSlow11 = (fConst1 * (fSlow7 / fSlow10));
    float fSlow12 = (0.0f - fSlow11);
    float fSlow13 =
        (0.5f *
         ((float(fEntry5) + 1.0f) *
          std::exp(((2.30258512f * (float(fEntry6) + 1.0f)) + -2.30258512f))));
    float fSlow14 = (fSlow13 + 1.0f);
    float fSlow15 =
        std::exp(((3.45387769f * (float(fEntry7) + 1.0f)) + -2.30258512f));
    float fSlow16 =
        std::exp(((4.60517025f * (float(fEntry8) + 1.0f)) + -4.60517025f));
    float fSlow17 =
        std::tan((fConst3 * std::exp(((3.45387769f * fSlow5) + -2.30258512f))));
    float fSlow18 = (1.0f / fSlow17);
    float fSlow19 = (fSlow18 + 1.0f);
    float fSlow20 = (0.0f - (1.0f / (fSlow19 * fSlow17)));
    float fSlow21 = (float(fEntry9) + 1.0f);
    float fSlow22 =
        (fSlow2 * std::exp(((3.45387769f * fSlow21) + -0.693147182f)));
    float fSlow23 = float(fEntry10);
    int iSlow24 = (fSlow23 < 0.0f);
    float fSlow25 = std::tan(
        (fConst3 * ((iSlow24 ? (1500.0f * fSlow23) : 0.0f) + 2000.0f)));
    float fSlow26 = (1.0f / fSlow25);
    float fSlow27 = (1.0f - fSlow26);
    float fSlow28 = float(fEntry11);
    float fSlow29 = (fSlow28 + 1.0f);
    float fSlow30 = (1.0f - (0.5f * fSlow29));
    float fSlow31 =
        std::tan((fConst3 * ((400.0f * fSlow30) + (25.0f * fSlow29))));
    float fSlow32 = (1.0f / fSlow31);
    float fSlow33 = (fSlow32 + 1.0f);
    float fSlow34 = (0.0f - (1.0f / (fSlow31 * fSlow33)));
    float fSlow35 = float(fEntry12);
    float fSlow36 =
        std::max<float>(0.0f, (std::min<float>(7.0f, fSlow35) + -5.0f));
    float fSlow37 = ((float(fEntry13) + 1.0f) + 1.0f);
    float fSlow38 = (0.5f * fSlow37);
    float fSlow39 = AmpMono_faustpower3_f(fSlow38);
    float fSlow40 = (0.5f * (fSlow36 / fSlow39));
    float fSlow41 =
        std::exp(((2.30258512f * (float(fEntry14) + 1.0f)) + -2.30258512f));
    float fSlow42 =
        std::exp(((3.45387769f * (float(fEntry15) + 1.0f)) + -6.90775537f));
    float fSlow43 =
        std::exp(((2.30258512f * (float(fEntry16) + 1.0f)) + -2.30258512f));
    float fSlow44 = (1.0f / (((fConst13 * fSlow42) + 1.0f) * fSlow43));
    float fSlow45 = (0.0f - (100.0f * (1.0f - (float(fEntry17) + 1.0f))));
    float fSlow46 = (0.889999986f * fSlow45);
    float fSlow47 = (0.0f - (100.0f * (1.0f - (float(fEntry18) + 1.0f))));
    float fSlow48 = (0.99000001f * fSlow47);
    float fSlow49 = (0.0f - (100.0f * (1.0f - (float(fEntry19) + 1.0f))));
    float fSlow50 = (1.08000004f * fSlow49);
    float fSlow51 =
        std::exp(((4.60517025f * (float(fEntry20) + 1.0f)) + -4.60517025f));
    float fSlow52 = (fSlow51 + fSlow48);
    float fSlow53 =
        std::exp(((4.60517025f * (float(fEntry21) + 1.0f)) + -2.30258512f));
    float fSlow54 = (0.294117659f / fSlow53);
    float fSlow55 = (0.810000002f * fSlow2);
    float fSlow56 = (float(fEntry22) + 1.0f);
    float fSlow57 = (2.2249999f * fSlow56);
    float fSlow58 = (float(fEntry23) + 1.0f);
    float fSlow59 = (2.5f * fSlow58);
    float fSlow60 =
        std::exp(((3.45387769f * (float(fEntry24) + 1.0f)) + -2.30258512f));
    float fSlow61 = std::tan((fConst14 * fSlow60));
    float fSlow62 = (1.0f / fSlow61);
    float fSlow63 = (fSlow62 + 1.0f);
    float fSlow64 = (0.0f - (1.0f / (fSlow61 * fSlow63)));
    float fSlow65 =
        std::exp(((3.45387769f * (float(fEntry25) + 1.0f)) + -2.30258512f));
    float fSlow66 = (100.0f * (1.0f - (float(fEntry26) + 1.0f)));
    float fSlow67 = (0.970000029f * fSlow47);
    float fSlow68 = (fSlow65 + (fSlow66 + fSlow67));
    float fSlow69 = (1.11000001f * fSlow49);
    float fSlow70 = (fSlow51 + fSlow67);
    float fSlow71 = (0.959999979f * fSlow2);
    float fSlow72 = (2.375f * fSlow56);
    float fSlow73 = std::tan((fConst15 * fSlow60));
    float fSlow74 = (1.0f / fSlow73);
    float fSlow75 = (fSlow74 + 1.0f);
    float fSlow76 = (0.0f - (1.0f / (fSlow75 * fSlow73)));
    float fSlow77 = (fSlow39 / fSlow2);
    float fSlow78 =
        std::max<float>(0.0f, (std::min<float>(5.0f, fSlow35) + -3.0f));
    float fSlow79 = (1.0f - (0.5f * fSlow78));
    float fSlow80 =
        std::max<float>(0.0f, (std::min<float>(3.0f, fSlow35) + -1.0f));
    float fSlow81 = (fSlow80 / fSlow37);
    float fSlow82 = (1.0f / (fSlow43 * ((fConst16 * fSlow42) + 1.0f)));
    float fSlow83 = (0.949999988f * fSlow45);
    float fSlow84 = (0.294117659f / fSlow51);
    float fSlow85 = (fSlow65 + (fSlow48 + fSlow66));
    float fSlow86 = (0.860000014f * fSlow49);
    float fSlow87 = (0.920000017f * fSlow2);
    float fSlow88 = (2.4000001f * fSlow56);
    float fSlow89 = std::tan((fConst17 * fSlow60));
    float fSlow90 = (1.0f / fSlow89);
    float fSlow91 = (fSlow90 + 1.0f);
    float fSlow92 = (1.0f / fSlow91);
    float fSlow93 = (fSlow89 * fSlow2);
    float fSlow94 = (0.5f * (fSlow37 / fSlow93));
    float fSlow95 = (float(fEntry27) + 1.0f);
    float fSlow96 =
        (std::exp((3.80045128f * fSlow95)) *
         std::pow(10.0f,
                  (0.0500000007f *
                   (0.0f - (35.0f * (1.0f - (float(fEntry28) + 1.0f)))))));
    float fSlow97 = (1.0f / fSlow63);
    float fSlow98 = (1.0f - fSlow62);
    float fSlow99 = (fSlow96 / fSlow61);
    float fSlow100 =
        std::exp(((3.45387769f * (float(fEntry29) + 1.0f)) + -13.8155107f));
    float fSlow101 =
        (fSlow100 *
         std::exp(((6.90775537f * (float(fEntry30) + 1.0f)) + -11.5129251f)));
    float fSlow102 = (1.0f / ((fConst18 * fSlow101) + 1.0f));
    float fSlow103 = (1.0f - fSlow102);
    float fSlow104 =
        std::exp(((2.30258512f * (float(fEntry31) + 1.0f)) + -2.30258512f));
    float fSlow105 = (1.0f / (((fConst19 * fSlow100) + 1.0f) * fSlow104));
    float fSlow106 = (0.0f - (5.0f * (1.0f - (float(fEntry32) + 1.0f))));
    float fSlow107 = (0.860000014f * fSlow106);
    float fSlow108 =
        (fSlow100 *
         std::exp(((5.75646257f * (float(fEntry33) + 1.0f)) + -2.30258512f)));
    float fSlow109 = (1.0f / ((fConst19 * fSlow108) + 1.0f));
    float fSlow110 = (1.0f - fSlow109);
    float fSlow111 = (0.117647059f / fSlow58);
    float fSlow112 =
        std::exp(((2.30258512f * (float(fEntry34) + 1.0f)) + -2.30258512f));
    float fSlow113 =
        std::exp(((3.45387769f * (float(fEntry35) + 1.0f)) + -6.90775537f));
    float fSlow114 = std::exp((0.0f - (fConst20 / fSlow113)));
    float fSlow115 = (1.0f - fSlow114);
    float fSlow116 = (100.0f * (1.0f - (float(fEntry36) + 1.0f)));
    float fSlow117 = (0.0f - fSlow116);
    float fSlow118 = (1.08000004f * fSlow117);
    float fSlow119 =
        (fSlow42 * std::exp((1.15129256f * (float(fEntry37) + 1.0f))));
    float fSlow120 = (1.0f / ((fConst13 * fSlow119) + 1.0f));
    float fSlow121 = (1.0f - fSlow120);
    float fSlow122 = (0.294117659f / fSlow65);
    float fSlow123 = (1.0f - fSlow90);
    float fSlow124 = (0.0f - (1.0f / (fSlow89 * fSlow91)));
    float fSlow125 = (0.5f * (fSlow37 / fSlow2));
    float fSlow126 = (1.0f / ((fConst21 * fSlow101) + 1.0f));
    float fSlow127 = (1.0f - fSlow126);
    float fSlow128 = (1.0f / (fSlow104 * ((fConst22 * fSlow100) + 1.0f)));
    float fSlow129 = (0.889999986f * fSlow106);
    float fSlow130 = (1.0f - (1.0f / ((fConst22 * fSlow108) + 1.0f)));
    float fSlow131 = std::exp((0.0f - (fConst23 / fSlow113)));
    float fSlow132 = (1.0f - fSlow131);
    float fSlow133 = (0.939999998f * fSlow117);
    float fSlow134 = (1.0f / (fSlow43 * ((fConst24 * fSlow42) + 1.0f)));
    float fSlow135 = (0.959999979f * fSlow45);
    float fSlow136 = (1.0f / ((fConst24 * fSlow119) + 1.0f));
    float fSlow137 = (1.0f - fSlow136);
    float fSlow138 = (1.0f / fSlow75);
    float fSlow139 = (1.0f - fSlow74);
    float fSlow140 = (fSlow73 * fSlow2);
    float fSlow141 = (1.0f / fSlow140);
    float fSlow142 = (1.0f / ((fConst25 * fSlow101) + 1.0f));
    float fSlow143 = (1.0f / (fSlow104 * ((fConst25 * fSlow100) + 1.0f)));
    float fSlow144 = ((1.0f / ((fConst25 * fSlow108) + 1.0f)) + -1.0f);
    float fSlow145 = (1.0f - fSlow142);
    float fSlow146 = (1.0f - (1.0f / ((fConst16 * fSlow119) + 1.0f)));
    float fSlow147 = (1.0f - (0.5f * fSlow80));
    float fSlow148 = AmpMono_faustpower2_f(fSlow38);
    float fSlow149 = (0.5f * (fSlow78 / fSlow148));
    float fSlow150 = (fSlow148 / fSlow2);
    float fSlow151 = (fSlow61 * fSlow2);
    float fSlow152 = (fSlow148 / fSlow151);
    float fSlow153 = (1.0f / fSlow93);
    float fSlow154 = (fSlow136 + -1.0f);
    float fSlow155 = (fSlow39 / fSlow140);
    float fSlow156 = (1.0f / fSlow151);
    float fSlow157 = (fSlow109 + -1.0f);
    float fSlow158 = (fSlow120 + -1.0f);
    float fSlow159 = (1.0f - (0.5f * fSlow36));
    float fSlow160 = (1.0f / fSlow33);
    float fSlow161 = (1.0f - fSlow32);
    float fSlow162 = (1.0f / (fSlow31 * fSlow2));
    float fSlow163 =
        std::pow(10.0f, (0.0500000007f *
                         (fSlow28 * ((18.0f * fSlow30) + (4.5f * fSlow29)))));
    float fSlow164 = float(fEntry38);
    float fSlow165 = (fSlow164 + 1.0f);
    float fSlow166 = ((fSlow164 * ((10.0f * (1.0f - (0.5f * fSlow165))) +
                                   (2.5f * fSlow165))) +
                      -14.0f);
    int iSlow167 = (fSlow166 > 0.0f);
    float fSlow168 = ((800.0f * fSlow164) + 1200.0f);
    float fSlow169 =
        (fConst32 *
         (fSlow168 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow166)))));
    float fSlow170 = (fConst32 * fSlow168);
    float fSlow171 = (iSlow167 ? fSlow170 : fSlow169);
    float fSlow172 = ((fConst30 * (fConst30 - fSlow171)) + 1.0f);
    float fSlow173 = ((fConst30 * (fConst30 + fSlow171)) + 1.0f);
    float fSlow174 = (iSlow167 ? fSlow169 : fSlow170);
    float fSlow175 = ((fConst30 * (fConst30 - fSlow174)) + 1.0f);
    float fSlow176 = ((fConst30 * (fConst30 + fSlow174)) + 1.0f);
    float fSlow177 = (fSlow164 * ((fSlow164 > 0.0f) ? 5.0f : 0.0f));
    int iSlow178 = (fSlow177 > 0.0f);
    float fSlow179 =
        (fConst33 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow177))));
    float fSlow180 = (iSlow178 ? fConst33 : fSlow179);
    float fSlow181 = ((fConst30 * (fConst30 - fSlow180)) + 1.0f);
    float fSlow182 = ((fConst30 * (fConst30 + fSlow180)) + 1.0f);
    float fSlow183 = (iSlow178 ? fSlow179 : fConst33);
    float fSlow184 = ((fConst30 * (fConst30 - fSlow183)) + 1.0f);
    float fSlow185 = ((fConst30 * (fConst30 + fSlow183)) + 1.0f);
    float fSlow186 = (fSlow26 + 1.0f);
    float fSlow187 = (0.0f - (1.0f / (fSlow25 * fSlow186)));
    float fSlow188 = (fSlow25 * fSlow182);
    float fSlow189 =
        std::pow(10.0f, ((0.0500000007f * fSlow23) * (iSlow24 ? 18.0f : 9.0f)));
    float fSlow190 = (10.0f * float(fEntry39));
    int iSlow191 = (fSlow190 > 0.0f);
    float fSlow192 =
        (fConst37 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow190))));
    float fSlow193 = (iSlow191 ? fConst37 : fSlow192);
    float fSlow194 = ((fConst36 * (fConst36 - fSlow193)) + 1.0f);
    float fSlow195 = ((fConst36 * (fConst36 + fSlow193)) + 1.0f);
    float fSlow196 = (iSlow191 ? fSlow192 : fConst37);
    float fSlow197 = ((fConst36 * (fConst36 + fSlow196)) + 1.0f);
    float fSlow198 = ((fConst36 * (fConst36 - fSlow196)) + 1.0f);
    float fSlow199 = (5.0f * fSlow95);
    int iSlow200 = (fSlow199 < 9.0f);
    int iSlow201 = (fSlow199 < 8.0f);
    int iSlow202 = (fSlow199 < 7.0f);
    int iSlow203 = (fSlow199 < 6.0f);
    int iSlow204 = (fSlow199 < 5.0f);
    int iSlow205 = (fSlow199 < 4.0f);
    int iSlow206 = (fSlow199 < 3.0f);
    int iSlow207 = (fSlow199 < 2.0f);
    int iSlow208 = (fSlow199 < 1.0f);
    float fSlow209 = std::pow(
        10.0f,
        (0.0500000007f *
         (iSlow200
              ? (iSlow201
                     ? (iSlow202
                            ? (iSlow203
                                   ? (iSlow204
                                          ? (iSlow205
                                                 ? (iSlow206
                                                        ? (iSlow207
                                                               ? (iSlow208
                                                                      ? ((fSlow199 <
                                                                          0.0f)
                                                                             ? 13.6999998f
                                                                             : (iSlow208
                                                                                    ? (13.6999998f -
                                                                                       (32.9500008f *
                                                                                        fSlow95))
                                                                                    : 7.11000013f))
                                                                      : (iSlow207
                                                                             ? (7.11000013f -
                                                                                (6.57700014f *
                                                                                 (fSlow199 +
                                                                                  -1.0f)))
                                                                             : 0.532999992f))
                                                               : (iSlow206
                                                                      ? (0.532999992f -
                                                                         (6.5630002f *
                                                                          (fSlow199 +
                                                                           -2.0f)))
                                                                      : -6.03000021f))
                                                        : (iSlow205
                                                               ? (-6.03000021f -
                                                                  (6.57000017f *
                                                                   (fSlow199 +
                                                                    -3.0f)))
                                                               : -12.6000004f))
                                                 : (iSlow204
                                                        ? (-12.6000004f -
                                                           (5.19999981f *
                                                            (fSlow199 + -4.0f)))
                                                        : -17.7999992f))
                                          : (iSlow203 ? (-17.7999992f -
                                                         (2.79999995f *
                                                          (0.0f -
                                                           (5.0f *
                                                            (1.0f - fSlow95)))))
                                                      : -20.6000004f))
                                   : (iSlow202
                                          ? (-20.6000004f -
                                             (1.39999998f * (fSlow199 + -6.0f)))
                                          : -22.0f))
                            : (iSlow201 ? (-22.0f -
                                           (1.10000002f * (fSlow199 + -7.0f)))
                                        : -23.1000004f))
                     : (iSlow200 ? (-23.1000004f -
                                    (2.20000005f * (fSlow199 + -8.0f)))
                                 : -25.2999992f))
              : ((fSlow199 < 10.0f)
                     ? (-25.2999992f - (1.70000005f * (fSlow199 + -9.0f)))
                     : -27.0f))));
    float fSlow210 = (250.0f * (float(fEntry40) + 1.0f));
    float fSlow211 = (1.0f / fSlow19);
    float fSlow212 = (1.0f - fSlow18);
    float fSlow213 = std::exp(
        (0.0f - (fConst7 / std::exp(((4.60517025f * (float(fEntry41) + 1.0f)) +
                                     -9.2103405f)))));
    float fSlow214 = (1.0f - fSlow213);
    float fSlow215 = (250.0f * (float(fEntry42) + 1.0f));
    float fSlow216 =
        std::exp(((4.60517025f * (float(fEntry43) + 1.0f)) + -9.2103405f));
    float fSlow217 =
        std::exp(((2.30258512f * (float(fEntry44) + 1.0f)) + -2.30258512f));
    float fSlow218 = (1.0f / (((fConst0 * fSlow216) + 1.0f) * fSlow217));
    float fSlow219 = (100.0f * (1.0f - (float(fEntry45) + 1.0f)));
    float fSlow220 =
        (1.0f -
         (1.0f / ((fConst0 * (fSlow216 * std::exp(((4.60517025f *
                                                    (float(fEntry46) + 1.0f)) +
                                                   -4.60517025f)))) +
                  1.0f)));
    float fSlow221 =
        std::exp(((2.30258512f * (float(fEntry47) + 1.0f)) + -2.30258512f));
    float fSlow222 = std::exp(
        (0.0f - (fConst7 / std::exp(((3.45387769f * (float(fEntry48) + 1.0f)) +
                                     -6.90775537f)))));
    float fSlow223 = (1.0f - fSlow222);
    float fSlow224 = (100.0f * (1.0f - (float(fEntry49) + 1.0f)));
    float fSlow225 = (0.0f - fSlow224);
    float fSlow226 = ((20.0f * (float(fEntry50) + 1.0f)) + 10.0f);
    float fSlow227 =
        std::exp(((2.30258512f * (float(fEntry51) + 1.0f)) + -2.30258512f));
    float fSlow228 = std::exp(
        (0.0f - (fConst7 / std::exp(((3.45387769f * (float(fEntry52) + 1.0f)) +
                                     -6.90775537f)))));
    float fSlow229 = (1.0f - fSlow228);
    float fSlow230 = (1.0f / fSlow226);
    float fSlow231 = (0.294117659f / fSlow15);
    float fSlow232 =
        std::exp(((3.45387769f * (float(fEntry53) + 1.0f)) + -2.30258512f));
    float fSlow233 = (0.294117659f / fSlow232);
    float fSlow234 =
        std::exp(((1.95601153f * (float(fEntry54) + 1.0f)) + -4.60517025f));
    float fSlow235 = (1.0f / ((fConst0 * fSlow234) + 1.0f));
    float fSlow236 = (fSlow16 / fSlow226);
    float fSlow237 =
        std::exp(((2.30258512f * (float(fEntry55) + 1.0f)) + -2.30258512f));
    float fSlow238 =
        (1.0f -
         (1.0f /
          ((fConst0 *
            (fSlow234 * std::exp((1.15129256f * (float(fEntry56) + 1.0f))))) +
           1.0f)));
    float fSlow239 = (1.0f / fSlow10);
    float fSlow240 = ((fConst38 * fSlow6) + -8.0f);
    float fSlow241 = (fSlow8 + (4.0f - fSlow9));
    float fSlow242 =
        std::exp(((2.30258512f * (float(fEntry57) + 1.0f)) + -2.30258512f));
    float fSlow243 = (50.0f * (1.0f - (float(fEntry58) + 1.0f)));
    float fSlow244 = (0.0f - fSlow243);
    float fSlow245 = float(fEntry59);
    float fSlow246 = (1.77827942f * std::pow(10.0f, (0.100000001f * fSlow245)));
    float fSlow247 = (0.0f - (10.0f * fSlow245));
    int iSlow248 = (fSlow247 > 0.0f);
    float fSlow249 =
        (fConst43 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow247))));
    float fSlow250 = (iSlow248 ? fSlow249 : fConst43);
    float fSlow251 = ((fConst42 * (fConst42 - fSlow250)) + 1.0f);
    float fSlow252 = float(fEntry60);
    float fSlow253 =
        std::pow(10.0f, (0.0500000007f * (0.0f - (3.0f * fSlow252))));
    float fSlow254 = (15.0f * fSlow252);
    int iSlow255 = (fSlow254 > 0.0f);
    float fSlow256 =
        (fConst198 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow254))));
    float fSlow257 = (iSlow255 ? fConst198 : fSlow256);
    float fSlow258 = ((fConst197 * (fConst197 - fSlow257)) + 1.0f);
    float fSlow259 = ((fConst197 * (fConst197 + fSlow257)) + 1.0f);
    float fSlow260 = (iSlow255 ? fSlow256 : fConst198);
    float fSlow261 = ((fConst197 * (fConst197 + fSlow260)) + 1.0f);
    float fSlow262 = ((fConst197 * (fConst197 - fSlow260)) + 1.0f);
    float fSlow263 = (iSlow248 ? fConst43 : fSlow249);
    float fSlow264 = ((fConst42 * (fConst42 - fSlow263)) + 1.0f);
    float fSlow265 = ((fConst42 * (fConst42 + fSlow263)) + 1.0f);
    float fSlow266 = ((fConst42 * (fConst42 + fSlow250)) + 1.0f);
    float fSlow267 = (0.0f - (17.0f * fSlow245));
    int iSlow268 = (fSlow267 > 0.0f);
    float fSlow269 =
        (fConst201 * std::pow(10.0f, (0.0500000007f * std::fabs(fSlow267))));
    float fSlow270 = (iSlow268 ? fConst201 : fSlow269);
    float fSlow271 = ((fConst200 * (fConst200 - fSlow270)) + 1.0f);
    float fSlow272 = ((fConst200 * (fConst200 + fSlow270)) + 1.0f);
    float fSlow273 = (iSlow268 ? fSlow269 : fConst201);
    float fSlow274 = ((fConst200 * (fConst200 + fSlow273)) + 1.0f);
    float fSlow275 = ((fConst200 * (fConst200 - fSlow273)) + 1.0f);
    float fSlow276 = (5.0f * fSlow21);
    int iSlow277 = (fSlow276 < 9.0f);
    int iSlow278 = (fSlow276 < 8.0f);
    int iSlow279 = (fSlow276 < 7.0f);
    int iSlow280 = (fSlow276 < 6.0f);
    int iSlow281 = (fSlow276 < 5.0f);
    int iSlow282 = (fSlow276 < 4.0f);
    int iSlow283 = (fSlow276 < 3.0f);
    int iSlow284 = (fSlow276 < 2.0f);
    int iSlow285 = (fSlow276 < 1.0f);
    float fSlow286 = std::pow(
        10.0f,
        (0.0500000007f *
         (iSlow277
              ? (iSlow278
                     ? (iSlow279
                            ? (iSlow280
                                   ? (iSlow281
                                          ? (iSlow282
                                                 ? (iSlow283
                                                        ? (iSlow284
                                                               ? (iSlow285
                                                                      ? ((fSlow276 <
                                                                          0.0f)
                                                                             ? 5.28000021f
                                                                             : (iSlow285
                                                                                    ? (5.28000021f -
                                                                                       (27.9400005f *
                                                                                        fSlow21))
                                                                                    : -0.307999998f))
                                                                      : (iSlow284
                                                                             ? (-0.307999998f -
                                                                                (5.28200006f *
                                                                                 (fSlow276 +
                                                                                  -1.0f)))
                                                                             : -5.59000015f))
                                                               : (iSlow283
                                                                      ? (-5.59000015f -
                                                                         (5.40999985f *
                                                                          (fSlow276 +
                                                                           -2.0f)))
                                                                      : -11.0f))
                                                        : (iSlow282
                                                               ? (-11.0f -
                                                                  (5.4000001f *
                                                                   (fSlow276 +
                                                                    -3.0f)))
                                                               : -16.3999996f))
                                                 : (iSlow281
                                                        ? (-16.3999996f -
                                                           (3.20000005f *
                                                            (fSlow276 + -4.0f)))
                                                        : -19.6000004f))
                                          : (iSlow280
                                                 ? ((5.0f * (1.0f - fSlow21)) +
                                                    -19.6000004f)
                                                 : -20.6000004f))
                                   : (iSlow279 ? (-20.6000004f -
                                                  (0.300000012f *
                                                   (fSlow276 + -6.0f)))
                                               : -20.8999996f))
                            : (iSlow278 ? (-20.8999996f -
                                           (0.200000003f * (fSlow276 + -7.0f)))
                                        : -21.1000004f))
                     : (iSlow277 ? (-21.1000004f -
                                    (0.300000012f * (fSlow276 + -8.0f)))
                                 : -21.3999996f))
              : ((fSlow276 < 10.0f)
                     ? (-21.3999996f - (0.100000001f * (fSlow276 + -9.0f)))
                     : -21.5f))));
    for (int i = 0; (i < count); i = (i + 1)) {
      float fTemp0 = float(input0[i]);
      fVec0[0] = (fSlow96 * fTemp0);
      fRec20[0] = ((fSlow64 * fVec0[1]) -
                   (fSlow97 * ((fSlow98 * fRec20[1]) - (fSlow99 * fTemp0))));
      fRec22[0] = ((fSlow105 *
                    (std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec20[0] - fSlow107)) -
                                fRec22[1])) *
                     std::max<float>(0.0f, (fSlow104 - fRec22[1])))) +
                   (fSlow110 * fRec22[1]));
      fRec21[0] = ((fSlow103 * fRec21[1]) + (fSlow102 * fRec22[0]));
      float fTemp1 = (fSlow59 + ((fRec20[0] - fRec21[0]) - fSlow57));
      float fTemp2 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp1))));
      float fTemp3 = (fTemp2 * (std::fabs(fTemp2) + -2.0f));
      float fTemp4 =
          (fSlow50 +
           ((fSlow55 *
             (fSlow57 +
              (std::min<float>(0.0f, fTemp1) -
               (fSlow59 * (1.0f - (fTemp3 * (std::fabs(fTemp3) + -2.0f))))))) -
            fSlow53));
      float fTemp5 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp4))));
      float fTemp6 = (std::fabs(fTemp5) + -2.0f);
      float fTemp7 =
          (fSlow50 -
           (fSlow52 +
            ((fSlow53 *
              (((fTemp6 * (std::fabs((fTemp6 * fTemp5)) + -2.0f)) * fTemp5) +
               1.0f)) +
             std::max<float>(0.0f, fTemp4))));
      float fTemp8 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp7))));
      float fTemp9 = (fTemp8 * (std::fabs(fTemp8) + -2.0f));
      float fTemp10 =
          ((fSlow51 * ((fTemp9 * (std::fabs(fTemp9) + -2.0f)) + 1.0f)) +
           std::max<float>(0.0f, fTemp7));
      fRec23[0] = ((fSlow115 * (std::max<float>(fSlow118, (fSlow48 + fTemp10)) -
                                fSlow118)) +
                   (fSlow114 * fRec23[1]));
      float fTemp11 = (fSlow112 * fRec23[0]);
      fRec19[0] =
          ((fSlow44 *
            (std::max<float>(0.0f, (fSlow43 - fRec19[1])) *
             std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow46, (fSlow48 + (fTemp10 - fTemp11))) -
                   fRec19[1]) -
                  fSlow46)))) +
           (fSlow121 * fRec19[1]));
      float fTemp12 = (fSlow41 * fRec19[0]);
      float fTemp13 = (fSlow85 + (fTemp10 - (fTemp11 + fTemp12)));
      float fTemp14 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp13))));
      float fTemp15 = (fTemp14 * (std::fabs(fTemp14) + -2.0f));
      float fTemp16 =
          (((fTemp12 + std::min<float>(0.0f, fTemp13)) -
            (fSlow65 * (1.0f - (fTemp15 * (std::fabs(fTemp15) + -2.0f))))) -
           fSlow66);
      fVec1[0] = fTemp16;
      fRec18[0] =
          ((0.900575519f * (fTemp16 + fVec1[1])) - (0.801151097f * fRec18[1]));
      fVec2[0] = (fSlow125 * fRec18[0]);
      fRec17[0] =
          ((fSlow92 * ((fSlow94 * fRec18[0]) - (fSlow123 * fRec17[1]))) +
           (fSlow124 * fVec2[1]));
      fRec25[0] = ((fSlow128 *
                    (std::max<float>(0.0f, (fSlow104 - fRec25[1])) *
                     std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec17[0] - fSlow129)) -
                                fRec25[1])))) +
                   (fSlow130 * fRec25[1]));
      fRec24[0] = ((fSlow127 * fRec24[1]) + (fSlow126 * fRec25[0]));
      float fTemp17 = (fSlow59 + ((fRec17[0] - fRec24[0]) - fSlow88));
      float fTemp18 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp17))));
      float fTemp19 = ((std::fabs(fTemp18) + -2.0f) * fTemp18);
      float fTemp20 =
          (fSlow86 +
           ((fSlow87 *
             (fSlow88 + (std::min<float>(0.0f, fTemp17) -
                         (fSlow59 * (1.0f - (fTemp19 * (std::fabs(fTemp19) +
                                                        -2.0f))))))) -
            fSlow53));
      float fTemp21 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp20))));
      float fTemp22 = (std::fabs(fTemp21) + -2.0f);
      float fTemp23 =
          (fSlow86 -
           (fSlow52 +
            ((fSlow53 * ((((std::fabs((fTemp22 * fTemp21)) + -2.0f) * fTemp22) *
                          fTemp21) +
                         1.0f)) +
             std::max<float>(0.0f, fTemp20))));
      float fTemp24 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp23))));
      float fTemp25 = (std::fabs(fTemp24) + -2.0f);
      float fTemp26 =
          (std::max<float>(0.0f, fTemp23) +
           (fSlow51 *
            ((((std::fabs((fTemp25 * fTemp24)) + -2.0f) * fTemp25) * fTemp24) +
             1.0f)));
      fRec26[0] = ((fSlow132 * (std::max<float>(fSlow133, (fSlow48 + fTemp26)) -
                                fSlow133)) +
                   (fSlow131 * fRec26[1]));
      float fTemp27 = (fSlow112 * fRec26[0]);
      fRec27[0] =
          ((fSlow134 *
            (std::max<float>(0.0f, (fSlow43 - fRec27[1])) *
             std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow135, (fSlow48 + (fTemp26 - fTemp27))) -
                   fRec27[1]) -
                  fSlow135)))) +
           (fSlow137 * fRec27[1]));
      float fTemp28 = (fSlow41 * fRec27[0]);
      float fTemp29 = (fSlow85 + (fTemp26 - (fTemp27 + fTemp28)));
      float fTemp30 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp29))));
      float fTemp31 = (std::fabs(fTemp30) + -2.0f);
      float fTemp32 =
          (((std::min<float>(0.0f, fTemp29) + fTemp28) -
            (fSlow65 *
             (1.0f - (((std::fabs((fTemp30 * fTemp31)) + -2.0f) * fTemp30) *
                      fTemp31)))) -
           fSlow66);
      fVec3[0] = fTemp32;
      fRec16[0] =
          ((0.900575519f * (fTemp32 + fVec3[1])) - (0.801151097f * fRec16[1]));
      fVec4[0] = (fSlow3 * fRec16[0]);
      fRec15[0] =
          ((fSlow76 * fVec4[1]) -
           (fSlow138 * ((fSlow139 * fRec15[1]) - (fSlow141 * fRec16[0]))));
      fRec29[0] = ((fSlow143 *
                    (std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec15[0] - fSlow129)) -
                                fRec29[1])) *
                     std::max<float>(0.0f, (fSlow104 - fRec29[1])))) -
                   (fSlow144 * fRec29[1]));
      fRec28[0] = ((fSlow142 * fRec29[0]) + (fSlow145 * fRec28[1]));
      float fTemp33 = (fSlow59 + ((fRec15[0] - fRec28[0]) - fSlow72));
      float fTemp34 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp33))));
      float fTemp35 = (std::fabs(fTemp34) + -2.0f);
      float fTemp36 =
          (fSlow69 +
           ((fSlow71 *
             (fSlow72 +
              (std::min<float>(0.0f, fTemp33) -
               (fSlow59 *
                (1.0f - ((fTemp34 * (std::fabs((fTemp34 * fTemp35)) + -2.0f)) *
                         fTemp35)))))) -
            fSlow53));
      float fTemp37 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp36))));
      float fTemp38 = (std::fabs(fTemp37) + -2.0f);
      float fTemp39 =
          (fSlow69 -
           (fSlow70 +
            (std::max<float>(0.0f, fTemp36) +
             (fSlow53 * ((((std::fabs((fTemp38 * fTemp37)) + -2.0f) * fTemp38) *
                          fTemp37) +
                         1.0f)))));
      float fTemp40 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp39))));
      float fTemp41 = (fTemp40 * (std::fabs(fTemp40) + -2.0f));
      float fTemp42 =
          ((fSlow51 * ((fTemp41 * (std::fabs(fTemp41) + -2.0f)) + 1.0f)) +
           std::max<float>(0.0f, fTemp39));
      fRec30[0] =
          ((fSlow132 *
            (fSlow116 + std::max<float>(fSlow117, (fSlow67 + fTemp42)))) +
           (fSlow131 * fRec30[1]));
      float fTemp43 = (fSlow112 * fRec30[0]);
      fRec14[0] =
          ((fSlow82 *
            (std::max<float>(0.0f, (fSlow43 - fRec14[1])) *
             std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow83, (fSlow67 + (fTemp42 - fTemp43))) -
                   fRec14[1]) -
                  fSlow83)))) +
           (fSlow146 * fRec14[1]));
      float fTemp44 = (fSlow41 * fRec14[0]);
      float fTemp45 = (fSlow68 + (fTemp42 - (fTemp43 + fTemp44)));
      float fTemp46 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp45))));
      float fTemp47 = (std::fabs(fTemp46) + -2.0f);
      float fTemp48 =
          (((fTemp44 + std::min<float>(0.0f, fTemp45)) -
            (fSlow65 *
             (1.0f - (((std::fabs((fTemp46 * fTemp47)) + -2.0f) * fTemp46) *
                      fTemp47)))) -
           fSlow66);
      fVec5[0] = fTemp48;
      fRec13[0] =
          ((0.900575519f * (fTemp48 + fVec5[1])) - (0.801151097f * fRec13[1]));
      float fTemp49 = ((fSlow81 * fRec13[0]) + (fSlow147 * fRec18[0]));
      fVec6[0] = (fSlow150 * fTemp49);
      fRec36[0] = ((fSlow64 * fVec6[1]) -
                   (fSlow97 * ((fSlow98 * fRec36[1]) - (fSlow152 * fTemp49))));
      fRec38[0] = ((fSlow105 *
                    (std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec36[0] - fSlow107)) -
                                fRec38[1])) *
                     std::max<float>(0.0f, (fSlow104 - fRec38[1])))) +
                   (fSlow110 * fRec38[1]));
      fRec37[0] = ((fSlow103 * fRec37[1]) + (fSlow102 * fRec38[0]));
      float fTemp50 = (fSlow59 + ((fRec36[0] - fRec37[0]) - fSlow57));
      float fTemp51 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp50))));
      float fTemp52 = (std::fabs(fTemp51) + -2.0f);
      float fTemp53 =
          (fSlow50 +
           ((fSlow55 *
             (fSlow57 +
              (std::min<float>(0.0f, fTemp50) -
               (fSlow59 *
                (1.0f - ((fTemp51 * (std::fabs((fTemp51 * fTemp52)) + -2.0f)) *
                         fTemp52)))))) -
            fSlow53));
      float fTemp54 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp53))));
      float fTemp55 = (fTemp54 * (std::fabs(fTemp54) + -2.0f));
      float fTemp56 =
          (fSlow50 -
           (fSlow52 +
            ((fSlow53 * ((fTemp55 * (std::fabs(fTemp55) + -2.0f)) + 1.0f)) +
             std::max<float>(0.0f, fTemp53))));
      float fTemp57 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp56))));
      float fTemp58 = (std::fabs(fTemp57) + -2.0f);
      float fTemp59 =
          ((fSlow51 *
            (((fTemp57 * (std::fabs((fTemp57 * fTemp58)) + -2.0f)) * fTemp58) +
             1.0f)) +
           std::max<float>(0.0f, fTemp56));
      fRec39[0] = ((fSlow114 * fRec39[1]) +
                   (fSlow115 * (std::max<float>(fSlow118, (fSlow48 + fTemp59)) -
                                fSlow118)));
      float fTemp60 = (fSlow112 * fRec39[0]);
      fRec35[0] =
          ((fSlow121 * fRec35[1]) +
           (fSlow44 *
            (std::max<float>(0.0f, (fSlow43 - fRec35[1])) *
             std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow46, (fSlow48 + (fTemp59 - fTemp60))) -
                   fRec35[1]) -
                  fSlow46)))));
      float fTemp61 = (fSlow41 * fRec35[0]);
      float fTemp62 = (fSlow85 + (fTemp59 - (fTemp60 + fTemp61)));
      float fTemp63 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp62))));
      float fTemp64 = (fTemp63 * (std::fabs(fTemp63) + -2.0f));
      float fTemp65 =
          (((fTemp61 + std::min<float>(0.0f, fTemp62)) -
            (fSlow65 * (1.0f - (fTemp64 * (std::fabs(fTemp64) + -2.0f))))) -
           fSlow66);
      fVec7[0] = fTemp65;
      fRec34[0] =
          ((0.900575519f * (fTemp65 + fVec7[1])) - (0.801151097f * fRec34[1]));
      fVec8[0] = (fSlow3 * fRec34[0]);
      fRec33[0] =
          ((fSlow124 * fVec8[1]) -
           (fSlow92 * ((fSlow123 * fRec33[1]) - (fSlow153 * fRec34[0]))));
      fRec41[0] = ((fSlow128 *
                    (std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec33[0] - fSlow129)) -
                                fRec41[1])) *
                     std::max<float>(0.0f, (fSlow104 - fRec41[1])))) +
                   (fSlow130 * fRec41[1]));
      fRec40[0] = ((fSlow126 * fRec41[0]) + (fSlow127 * fRec40[1]));
      float fTemp66 = (fSlow59 + ((fRec33[0] - fRec40[0]) - fSlow88));
      float fTemp67 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp66))));
      float fTemp68 = ((std::fabs(fTemp67) + -2.0f) * fTemp67);
      float fTemp69 =
          (fSlow86 +
           ((fSlow87 *
             (fSlow88 + (std::min<float>(0.0f, fTemp66) -
                         (fSlow59 * (1.0f - (fTemp68 * (std::fabs(fTemp68) +
                                                        -2.0f))))))) -
            fSlow53));
      float fTemp70 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp69))));
      float fTemp71 = (std::fabs(fTemp70) + -2.0f);
      float fTemp72 =
          (fSlow86 -
           (fSlow52 +
            ((fSlow53 * ((((std::fabs((fTemp70 * fTemp71)) + -2.0f) * fTemp70) *
                          fTemp71) +
                         1.0f)) +
             std::max<float>(0.0f, fTemp69))));
      float fTemp73 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp72))));
      float fTemp74 = (std::fabs(fTemp73) + -2.0f);
      float fTemp75 =
          (std::max<float>(0.0f, fTemp72) +
           (fSlow51 *
            (((fTemp73 * (std::fabs((fTemp73 * fTemp74)) + -2.0f)) * fTemp74) +
             1.0f)));
      fRec42[0] = ((fSlow131 * fRec42[1]) +
                   (fSlow132 * (std::max<float>(fSlow133, (fSlow48 + fTemp75)) -
                                fSlow133)));
      float fTemp76 = (fSlow112 * fRec42[0]);
      fRec32[0] =
          ((fSlow134 *
            (std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow135, (fSlow48 + (fTemp75 - fTemp76))) -
                   fRec32[1]) -
                  fSlow135)) *
             std::max<float>(0.0f, (fSlow43 - fRec32[1])))) -
           (fSlow154 * fRec32[1]));
      float fTemp77 = (fSlow41 * fRec32[0]);
      float fTemp78 = (fSlow85 + (fTemp75 - (fTemp76 + fTemp77)));
      float fTemp79 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp78))));
      float fTemp80 = (std::fabs(fTemp79) + -2.0f);
      float fTemp81 =
          (((fTemp77 + std::min<float>(0.0f, fTemp78)) -
            (fSlow65 *
             (1.0f - ((fTemp80 * (std::fabs((fTemp80 * fTemp79)) + -2.0f)) *
                      fTemp79)))) -
           fSlow66);
      fVec9[0] = fTemp81;
      fRec31[0] =
          ((0.900575519f * (fTemp81 + fVec9[1])) - (0.801151097f * fRec31[1]));
      float fTemp82 = ((fSlow79 * fTemp49) + (fSlow149 * fRec31[0]));
      fVec10[0] = (fSlow77 * fTemp82);
      fRec12[0] =
          ((fSlow76 * fVec10[1]) -
           (fSlow138 * ((fSlow139 * fRec12[1]) - (fSlow155 * fTemp82))));
      fRec44[0] = ((fSlow143 *
                    (std::max<float>(0.0f, (fSlow104 - fRec44[1])) *
                     std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec12[0] - fSlow129)) -
                                fRec44[1])))) -
                   (fSlow144 * fRec44[1]));
      fRec43[0] = ((fSlow145 * fRec43[1]) + (fSlow142 * fRec44[0]));
      float fTemp83 = (fSlow59 + ((fRec12[0] - fRec43[0]) - fSlow72));
      float fTemp84 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp83))));
      float fTemp85 = (std::fabs(fTemp84) + -2.0f);
      float fTemp86 =
          (fSlow69 +
           ((fSlow71 *
             (fSlow72 +
              (std::min<float>(0.0f, fTemp83) -
               (fSlow59 *
                (1.0f - ((fTemp85 * (std::fabs((fTemp85 * fTemp84)) + -2.0f)) *
                         fTemp84)))))) -
            fSlow53));
      float fTemp87 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp86))));
      float fTemp88 = (std::fabs(fTemp87) + -2.0f);
      float fTemp89 =
          (fSlow69 -
           (fSlow70 +
            ((fSlow53 * ((((std::fabs((fTemp88 * fTemp87)) + -2.0f) * fTemp88) *
                          fTemp87) +
                         1.0f)) +
             std::max<float>(0.0f, fTemp86))));
      float fTemp90 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp89))));
      float fTemp91 = ((std::fabs(fTemp90) + -2.0f) * fTemp90);
      float fTemp92 =
          (std::max<float>(0.0f, fTemp89) +
           (fSlow51 * ((fTemp91 * (std::fabs(fTemp91) + -2.0f)) + 1.0f)));
      fRec45[0] =
          ((fSlow132 *
            (fSlow116 + std::max<float>(fSlow117, (fSlow67 + fTemp92)))) +
           (fSlow131 * fRec45[1]));
      float fTemp93 = (fSlow112 * fRec45[0]);
      fRec46[0] =
          ((fSlow82 *
            (std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow83, (fSlow67 + (fTemp92 - fTemp93))) -
                   fRec46[1]) -
                  fSlow83)) *
             std::max<float>(0.0f, (fSlow43 - fRec46[1])))) +
           (fSlow146 * fRec46[1]));
      float fTemp94 = (fSlow41 * fRec46[0]);
      float fTemp95 = (fSlow68 + (fTemp92 - (fTemp93 + fTemp94)));
      float fTemp96 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp95))));
      float fTemp97 = (std::fabs(fTemp96) + -2.0f);
      float fTemp98 =
          (((std::min<float>(0.0f, fTemp95) + fTemp94) -
            (fSlow65 *
             (1.0f - (((std::fabs((fTemp97 * fTemp96)) + -2.0f) * fTemp97) *
                      fTemp96)))) -
           fSlow66);
      fVec11[0] = fTemp98;
      fRec11[0] =
          ((0.900575519f * (fTemp98 + fVec11[1])) - (0.801151097f * fRec11[1]));
      fVec12[0] = (fSlow3 * fRec11[0]);
      fRec10[0] =
          ((fSlow64 * fVec12[1]) -
           (fSlow97 * ((fSlow98 * fRec10[1]) - (fSlow156 * fRec11[0]))));
      fRec48[0] = ((fSlow105 *
                    (std::max<float>(
                         0.0f, (std::max<float>(0.0f, (fRec10[0] - fSlow107)) -
                                fRec48[1])) *
                     std::max<float>(0.0f, (fSlow104 - fRec48[1])))) -
                   (fSlow157 * fRec48[1]));
      fRec47[0] = ((fSlow103 * fRec47[1]) + (fSlow102 * fRec48[0]));
      float fTemp99 = (fSlow59 + ((fRec10[0] - fRec47[0]) - fSlow57));
      float fTemp100 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow111 * std::max<float>(0.0f, fTemp99))));
      float fTemp101 = ((std::fabs(fTemp100) + -2.0f) * fTemp100);
      float fTemp102 =
          (fSlow50 +
           ((fSlow55 *
             (fSlow57 + (std::min<float>(0.0f, fTemp99) -
                         (fSlow59 * (1.0f - (fTemp101 * (std::fabs(fTemp101) +
                                                         -2.0f))))))) -
            fSlow53));
      float fTemp103 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow54 * std::min<float>(0.0f, fTemp102))));
      float fTemp104 = (std::fabs(fTemp103) + -2.0f);
      float fTemp105 =
          (fSlow50 -
           (fSlow52 +
            ((fSlow53 *
              ((((std::fabs((fTemp103 * fTemp104)) + -2.0f) * fTemp103) *
                fTemp104) +
               1.0f)) +
             std::max<float>(0.0f, fTemp102))));
      float fTemp106 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow84 * std::min<float>(0.0f, fTemp105))));
      float fTemp107 = (fTemp106 * (std::fabs(fTemp106) + -2.0f));
      float fTemp108 =
          (std::max<float>(0.0f, fTemp105) +
           (fSlow51 * ((fTemp107 * (std::fabs(fTemp107) + -2.0f)) + 1.0f)));
      fRec49[0] =
          ((fSlow115 *
            (std::max<float>(fSlow118, (fSlow48 + fTemp108)) - fSlow118)) +
           (fSlow114 * fRec49[1]));
      float fTemp109 = (fSlow112 * fRec49[0]);
      fRec9[0] =
          ((fSlow44 *
            (std::max<float>(0.0f, (fSlow43 - fRec9[1])) *
             std::max<float>(
                 0.0f,
                 ((std::max<float>(fSlow46, (fSlow48 + (fTemp108 - fTemp109))) -
                   fRec9[1]) -
                  fSlow46)))) -
           (fSlow158 * fRec9[1]));
      float fTemp110 = (fSlow41 * fRec9[0]);
      float fTemp111 = (fSlow85 + (fTemp108 - (fTemp110 + fTemp109)));
      float fTemp112 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow122 * std::max<float>(0.0f, fTemp111))));
      float fTemp113 = (std::fabs(fTemp112) + -2.0f);
      float fTemp114 =
          (((fTemp110 + std::min<float>(0.0f, fTemp111)) -
            (fSlow65 *
             (1.0f - ((fTemp112 * (std::fabs((fTemp112 * fTemp113)) + -2.0f)) *
                      fTemp113)))) -
           fSlow66);
      fVec13[0] = fTemp114;
      fRec8[0] =
          ((0.900575519f * (fTemp114 + fVec13[1])) - (0.801151097f * fRec8[1]));
      float fTemp115 = ((fSlow40 * fRec8[0]) + (fSlow159 * fTemp82));
      float fTemp116 = (fSlow3 * fTemp115);
      fVec14[0] = fTemp116;
      fRec7[0] = ((fSlow34 * fVec14[1]) -
                  (fSlow160 * ((fSlow161 * fRec7[1]) - (fSlow162 * fTemp115))));
      fRec50[0] = (0.0f - (fSlow160 *
                           ((fSlow161 * fRec50[1]) - (fTemp116 + fVec14[1]))));
      float fTemp117 = (fRec7[0] + (fSlow163 * fRec50[0]));
      fVec15[0] = fTemp117;
      fRec6[0] = ((fConst12 * fVec15[1]) -
                  (fConst26 * ((fConst27 * fRec6[1]) - (fConst10 * fTemp117))));
      float fTemp118 = (fConst29 * fRec5[1]);
      fRec5[0] = (fRec6[0] - ((fTemp118 + (fRec5[2] * fSlow172)) / fSlow173));
      float fTemp119 = (fConst29 * fRec4[1]);
      fRec4[0] =
          ((((fRec5[2] * fSlow175) + (fTemp118 + (fRec5[0] * fSlow176))) /
            fSlow173) -
           (((fSlow181 * fRec4[2]) + fTemp119) / fSlow182));
      float fTemp120 =
          ((fRec4[2] * fSlow184) + (fTemp119 + (fRec4[0] * fSlow185)));
      float fTemp121 = (fTemp120 / fSlow182);
      fVec16[0] = fTemp121;
      fRec3[0] =
          (0.0f - (((fSlow27 * fRec3[1]) - (fTemp121 + fVec16[1])) / fSlow186));
      fRec51[0] =
          ((fVec16[1] * fSlow187) -
           (((fSlow27 * fRec51[1]) - (fTemp120 / fSlow188)) / fSlow186));
      float fTemp122 = (fConst35 * fRec2[1]);
      fRec2[0] = ((fRec3[0] + (fRec51[0] * fSlow189)) -
                  ((fTemp122 + (fSlow194 * fRec2[2])) / fSlow195));
      float fTemp123 =
          ((fSlow22 *
            (((((fRec2[0] * fSlow197) + fTemp122) + (fSlow198 * fRec2[2])) *
              fSlow209) /
             fSlow195)) -
           fSlow210);
      fVec17[0] = fTemp123;
      fRec1[0] = ((fSlow20 * fVec17[1]) -
                  (fSlow211 * ((fSlow212 * fRec1[1]) - (fSlow18 * fTemp123))));
      fRec52[0] = ((fSlow214 * (fRec1[0] - fSlow215)) + (fSlow213 * fRec52[1]));
      fRec53[0] =
          ((fSlow218 *
            (std::max<float>(0.0f, (fSlow217 - fRec53[1])) *
             std::max<float>(
                 0.0f,
                 (std::max<float>(
                      0.0f, (fSlow219 + ((fRec1[0] - fRec52[0]) - fSlow215))) -
                  fRec53[1])))) +
           (fSlow220 * fRec53[1]));
      float fTemp124 = ((fRec1[0] - (fRec52[0] + fRec53[0])) - fSlow215);
      float fTemp125 = (fSlow16 * fTemp124);
      fRec54[0] =
          ((fSlow223 * (fSlow224 + std::max<float>(fSlow225, fTemp125))) +
           (fSlow222 * fRec54[1]));
      float fTemp126 = (fSlow221 * fRec54[0]);
      fRec55[0] = ((fSlow228 * fRec55[1]) +
                   (fSlow229 *
                    std::min<float>(
                        1.0f, std::fabs((fSlow230 * (fTemp125 - fTemp126))))));
      float fTemp127 = (fSlow226 / ((fSlow227 * fRec55[0]) + 1.0f));
      float fTemp128 = (fSlow15 + (fTemp125 - (fTemp126 + fTemp127)));
      float fTemp129 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow231 * std::max<float>(0.0f, fTemp128))));
      float fTemp130 = (std::fabs(fTemp129) + -2.0f);
      float fTemp131 =
          (((std::min<float>(0.0f, fTemp128) + fTemp127) -
            (fSlow15 *
             (1.0f - ((fTemp130 * (std::fabs((fTemp130 * fTemp129)) + -2.0f)) *
                      fTemp129)))) -
           fSlow232);
      fRec57[0] = ((fSlow222 * fRec57[1]) +
                   (fSlow223 *
                    (fSlow224 + std::max<float>(fSlow225, (0.0f - fTemp125)))));
      float fTemp132 = (fTemp125 + (fSlow221 * fRec57[0]));
      fRec56[0] =
          ((fSlow228 * fRec56[1]) +
           (fSlow229 *
            std::min<float>(1.0f, std::fabs((fSlow230 * (0.0f - fTemp132))))));
      float fTemp133 = (fSlow226 / ((fSlow227 * fRec56[0]) + 1.0f));
      float fTemp134 = (fSlow15 - (fTemp132 + fTemp133));
      float fTemp135 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow231 * std::max<float>(0.0f, fTemp134))));
      float fTemp136 = (std::fabs(fTemp135) + -2.0f);
      float fTemp137 =
          (((fTemp133 + std::min<float>(0.0f, fTemp134)) -
            (fSlow15 *
             (1.0f - ((fTemp135 * (std::fabs((fTemp135 * fTemp136)) + -2.0f)) *
                      fTemp136)))) -
           fSlow232);
      float fTemp138 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow233 * std::min<float>(0.0f, fTemp137))));
      float fTemp139 = (std::fabs(fTemp138) + -2.0f);
      float fTemp140 = std::max<float>(
          -1.0f,
          std::min<float>(1.0f, (fSlow233 * std::min<float>(0.0f, fTemp131))));
      float fTemp141 = ((std::fabs(fTemp140) + -2.0f) * fTemp140);
      float fTemp142 = std::fabs((fSlow236 * fTemp124));
      fRec58[0] = ((fSlow235 *
                    std::max<float>(
                        0.0f, ((std::max<float>(1.0f, fTemp142) +
                                (fSlow237 * std::min<float>(1.0f, fTemp142))) +
                               (-1.0f - fRec58[1])))) +
                   (fSlow238 * fRec58[1]));
      fRec0[0] =
          ((fSlow14 *
            ((std::max<float>(0.0f, fTemp131) -
              (std::max<float>(0.0f, fTemp137) +
               (fSlow232 *
                ((((fTemp138 * (std::fabs((fTemp138 * fTemp139)) + -2.0f)) *
                   fTemp139) +
                  1.0f) -
                 ((fTemp141 * (std::fabs(fTemp141) + -2.0f)) + 1.0f))))) /
             ((fSlow13 * fRec58[0]) + 1.0f))) -
           (fSlow239 * ((fSlow240 * fRec0[1]) + (fSlow241 * fRec0[2]))));
      float fTemp143 = ((fSlow12 * fRec0[2]) + (fSlow11 * fRec0[0]));
      fRec59[0] =
          ((fSlow222 * fRec59[1]) +
           (fSlow223 *
            (fSlow243 + std::max<float>(fSlow244, std::fabs(fTemp143)))));
      float fTemp144 = (fSlow3 * (fTemp143 + (fSlow242 * fRec59[0])));
      fRec82[0] =
          (fTemp144 -
           (fConst142 * ((fConst144 * fRec82[2]) + (fConst145 * fRec82[1]))));
      fRec81[0] =
          ((fConst142 * ((fConst143 * fRec82[2]) +
                         ((fConst143 * fRec82[0]) + (fConst141 * fRec82[1])))) -
           (fConst139 * ((fConst145 * fRec81[1]) + (fConst146 * fRec81[2]))));
      float fTemp145 = (((fConst141 * fRec81[1]) + (fConst143 * fRec81[0])) +
                        (fConst143 * fRec81[2]));
      fVec18[0] = fTemp145;
      fRec80[0] = (0.0f - (fConst135 * ((fConst136 * fRec80[1]) -
                                        (fConst139 * (fVec18[1] + fTemp145)))));
      fRec79[0] =
          (fRec80[0] -
           (fConst132 * ((fConst147 * fRec79[2]) + (fConst148 * fRec79[1]))));
      float fTemp146 = (fRec79[2] + (fRec79[0] + (2.0f * fRec79[1])));
      fVec19[0] = fTemp146;
      fRec78[0] =
          ((fConst132 * ((fConst134 * fTemp146) + (fConst149 * fVec19[1]))) -
           (fConst151 * fRec78[1]));
      fRec77[0] =
          (fRec78[0] -
           (fConst129 * ((fConst152 * fRec77[2]) + (fConst153 * fRec77[1]))));
      fRec76[0] =
          ((fConst129 * ((fConst127 * fRec77[2]) +
                         ((fConst127 * fRec77[0]) + (fConst154 * fRec77[1])))) -
           (fConst128 * ((fConst153 * fRec76[1]) + (fConst155 * fRec76[2]))));
      fRec75[0] =
          ((fConst128 * ((fConst127 * fRec76[2]) +
                         ((fConst127 * fRec76[0]) + (fConst154 * fRec76[1])))) -
           (fConst125 * ((fConst156 * fRec75[2]) + (fConst153 * fRec75[1]))));
      fRec86[0] = (0.0f - (fConst157 * ((fConst150 * fRec86[1]) -
                                        (fConst132 * (fVec19[1] + fTemp146)))));
      fRec85[0] =
          (fRec86[0] -
           (fConst129 * ((fConst153 * fRec85[1]) + (fConst152 * fRec85[2]))));
      fRec84[0] =
          ((fConst129 * (fRec85[2] + (fRec85[0] + (2.0f * fRec85[1])))) -
           (fConst128 * ((fConst155 * fRec84[2]) + (fConst153 * fRec84[1]))));
      fRec83[0] =
          ((fConst128 * (fRec84[2] + (fRec84[0] + (2.0f * fRec84[1])))) -
           (fConst125 * ((fConst153 * fRec83[1]) + (fConst156 * fRec83[2]))));
      float fTemp147 = (fConst158 * fRec74[1]);
      fRec74[0] =
          ((fConst125 * ((0.0316227749f * ((fConst127 * fRec75[2]) +
                                           ((fConst154 * fRec75[1]) +
                                            (fConst127 * fRec75[0])))) +
                         ((fRec83[0] + (2.0f * fRec83[1])) + fRec83[2]))) -
           (fConst120 * (fTemp147 + (fConst159 * fRec74[2]))));
      float fTemp148 = (fConst162 * fRec73[1]);
      fRec73[0] = ((fConst120 * ((fConst122 * fRec74[2]) +
                                 (fTemp147 + (fConst160 * fRec74[0])))) -
                   (fConst113 * ((fConst161 * fRec73[2]) + fTemp148)));
      float fTemp149 = (fConst165 * fRec72[1]);
      fRec72[0] = ((fConst113 * ((fConst115 * fRec73[2]) +
                                 (fTemp148 + (fConst163 * fRec73[0])))) -
                   (fConst106 * ((fConst164 * fRec72[2]) + fTemp149)));
      float fTemp150 = (fConst101 * fRec71[1]);
      fRec71[0] = ((fConst106 * (((fConst108 * fRec72[0]) + fTemp149) +
                                 (fConst166 * fRec72[2]))) -
                   (fConst100 * ((fConst167 * fRec71[2]) + fTemp150)));
      float fTemp151 = (fConst172 * fRec70[1]);
      fRec70[0] = ((fConst100 * ((fTemp150 + (fConst169 * fRec71[0])) +
                                 (fConst170 * fRec71[2]))) -
                   (fConst92 * ((fConst171 * fRec70[2]) + fTemp151)));
      float fTemp152 = (fConst175 * fRec69[1]);
      fRec69[0] = ((fConst92 * ((fConst94 * fRec70[2]) +
                                (fTemp151 + (fConst173 * fRec70[0])))) -
                   (fConst85 * ((fConst174 * fRec69[2]) + fTemp152)));
      float fTemp153 = (fConst178 * fRec68[1]);
      fRec68[0] = ((fConst85 * (((fConst87 * fRec69[0]) + fTemp152) +
                                (fConst176 * fRec69[2]))) -
                   (fConst78 * ((fConst177 * fRec68[2]) + fTemp153)));
      float fTemp154 = (fConst73 * fRec67[1]);
      fRec67[0] = ((fConst78 * (((fConst80 * fRec68[0]) + fTemp153) +
                                (fConst179 * fRec68[2]))) -
                   (fConst72 * ((fConst180 * fRec67[2]) + fTemp154)));
      float fTemp155 = (fConst184 * fRec66[1]);
      fRec66[0] = ((fConst72 * ((fTemp154 + (fConst182 * fRec67[0])) +
                                (fConst183 * fRec67[2]))) -
                   (fConst65 * (fTemp155 + (fConst185 * fRec66[2]))));
      float fTemp156 = (fConst187 * fRec65[1]);
      fRec65[0] = ((fConst65 * ((fConst67 * fRec66[2]) +
                                (fTemp155 + (fConst186 * fRec66[0])))) -
                   (fConst55 * (fTemp156 + (fConst188 * fRec65[2]))));
      float fTemp157 =
          ((fConst59 * fRec65[2]) + ((fConst189 * fRec65[0]) + fTemp156));
      fVec20[0] = fTemp157;
      fRec64[0] =
          ((fConst55 * ((fConst57 * fTemp157) + (fConst190 * fVec20[1]))) -
           (fConst192 * fRec64[1]));
      fRec63[0] =
          (fRec64[0] -
           (fConst48 * ((fConst193 * fRec63[2]) + (fConst195 * fRec63[1]))));
      fRec88[0] = (fConst196 * ((fConst55 * (fVec20[1] + fTemp157)) -
                                (fConst191 * fRec88[1])));
      fRec87[0] =
          (fRec88[0] -
           (fConst48 * ((fConst193 * fRec87[2]) + (fConst195 * fRec87[1]))));
      float fTemp158 = (fConst45 * fRec62[1]);
      fRec62[0] =
          ((fConst48 *
            ((((fConst50 * fRec63[1]) + (fConst194 * fRec63[0])) +
              (fConst194 * fRec63[2])) +
             (fSlow253 * (fRec87[2] + (fRec87[0] + (2.0f * fRec87[1])))))) -
           ((fTemp158 + (fSlow258 * fRec62[2])) / fSlow259));
      float fTemp159 = (fConst199 * fRec61[1]);
      fRec61[0] =
          ((((fTemp158 + (fRec62[0] * fSlow261)) + (fRec62[2] * fSlow262)) /
            fSlow259) -
           (((fRec61[2] * fSlow264) + fTemp159) / fSlow265));
      float fTemp160 = (fConst40 * fRec60[1]);
      fRec60[0] =
          ((((fSlow251 * fRec61[2]) + ((fRec61[0] * fSlow266) + fTemp159)) /
            fSlow265) -
           ((fTemp160 + (fSlow271 * fRec60[2])) / fSlow272));
      output0[i] = FAUSTFLOAT(
          (fSlow0 *
           ((iSlow1 ? (fSlow246 * (((fTemp160 + (fRec60[0] * fSlow274)) +
                                    (fRec60[2] * fSlow275)) /
                                   fSlow272))
                    : fTemp144) *
            fSlow286)));
      fVec0[1] = fVec0[0];
      fRec20[1] = fRec20[0];
      fRec22[1] = fRec22[0];
      fRec21[1] = fRec21[0];
      fRec23[1] = fRec23[0];
      fRec19[1] = fRec19[0];
      fVec1[1] = fVec1[0];
      fRec18[1] = fRec18[0];
      fVec2[1] = fVec2[0];
      fRec17[1] = fRec17[0];
      fRec25[1] = fRec25[0];
      fRec24[1] = fRec24[0];
      fRec26[1] = fRec26[0];
      fRec27[1] = fRec27[0];
      fVec3[1] = fVec3[0];
      fRec16[1] = fRec16[0];
      fVec4[1] = fVec4[0];
      fRec15[1] = fRec15[0];
      fRec29[1] = fRec29[0];
      fRec28[1] = fRec28[0];
      fRec30[1] = fRec30[0];
      fRec14[1] = fRec14[0];
      fVec5[1] = fVec5[0];
      fRec13[1] = fRec13[0];
      fVec6[1] = fVec6[0];
      fRec36[1] = fRec36[0];
      fRec38[1] = fRec38[0];
      fRec37[1] = fRec37[0];
      fRec39[1] = fRec39[0];
      fRec35[1] = fRec35[0];
      fVec7[1] = fVec7[0];
      fRec34[1] = fRec34[0];
      fVec8[1] = fVec8[0];
      fRec33[1] = fRec33[0];
      fRec41[1] = fRec41[0];
      fRec40[1] = fRec40[0];
      fRec42[1] = fRec42[0];
      fRec32[1] = fRec32[0];
      fVec9[1] = fVec9[0];
      fRec31[1] = fRec31[0];
      fVec10[1] = fVec10[0];
      fRec12[1] = fRec12[0];
      fRec44[1] = fRec44[0];
      fRec43[1] = fRec43[0];
      fRec45[1] = fRec45[0];
      fRec46[1] = fRec46[0];
      fVec11[1] = fVec11[0];
      fRec11[1] = fRec11[0];
      fVec12[1] = fVec12[0];
      fRec10[1] = fRec10[0];
      fRec48[1] = fRec48[0];
      fRec47[1] = fRec47[0];
      fRec49[1] = fRec49[0];
      fRec9[1] = fRec9[0];
      fVec13[1] = fVec13[0];
      fRec8[1] = fRec8[0];
      fVec14[1] = fVec14[0];
      fRec7[1] = fRec7[0];
      fRec50[1] = fRec50[0];
      fVec15[1] = fVec15[0];
      fRec6[1] = fRec6[0];
      fRec5[2] = fRec5[1];
      fRec5[1] = fRec5[0];
      fRec4[2] = fRec4[1];
      fRec4[1] = fRec4[0];
      fVec16[1] = fVec16[0];
      fRec3[1] = fRec3[0];
      fRec51[1] = fRec51[0];
      fRec2[2] = fRec2[1];
      fRec2[1] = fRec2[0];
      fVec17[1] = fVec17[0];
      fRec1[1] = fRec1[0];
      fRec52[1] = fRec52[0];
      fRec53[1] = fRec53[0];
      fRec54[1] = fRec54[0];
      fRec55[1] = fRec55[0];
      fRec57[1] = fRec57[0];
      fRec56[1] = fRec56[0];
      fRec58[1] = fRec58[0];
      fRec0[2] = fRec0[1];
      fRec0[1] = fRec0[0];
      fRec59[1] = fRec59[0];
      fRec82[2] = fRec82[1];
      fRec82[1] = fRec82[0];
      fRec81[2] = fRec81[1];
      fRec81[1] = fRec81[0];
      fVec18[1] = fVec18[0];
      fRec80[1] = fRec80[0];
      fRec79[2] = fRec79[1];
      fRec79[1] = fRec79[0];
      fVec19[1] = fVec19[0];
      fRec78[1] = fRec78[0];
      fRec77[2] = fRec77[1];
      fRec77[1] = fRec77[0];
      fRec76[2] = fRec76[1];
      fRec76[1] = fRec76[0];
      fRec75[2] = fRec75[1];
      fRec75[1] = fRec75[0];
      fRec86[1] = fRec86[0];
      fRec85[2] = fRec85[1];
      fRec85[1] = fRec85[0];
      fRec84[2] = fRec84[1];
      fRec84[1] = fRec84[0];
      fRec83[2] = fRec83[1];
      fRec83[1] = fRec83[0];
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
      fVec20[1] = fVec20[0];
      fRec64[1] = fRec64[0];
      fRec63[2] = fRec63[1];
      fRec63[1] = fRec63[0];
      fRec88[1] = fRec88[0];
      fRec87[2] = fRec87[1];
      fRec87[1] = fRec87[0];
      fRec62[2] = fRec62[1];
      fRec62[1] = fRec62[0];
      fRec61[2] = fRec61[1];
      fRec61[1] = fRec61[0];
      fRec60[2] = fRec60[1];
      fRec60[1] = fRec60[0];
    }
  }
};

#endif
