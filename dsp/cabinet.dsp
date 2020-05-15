//  Resonant Amp tube amplifier simulation
//  Copyright (C) 2020  Garrin McGoldrick
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.

cab = cab
with {
    // fit parmeters
    hp_f = 143.90880212893683;
    lp_f = 18066.01335304503;
    hshelf5k_f = 5847.289563996711;
    hshelf5k_l = -17.282484388209873;
    bband150_f = 119.4597583331697;
    bband150_l = 16.832043582883152;
    bband150_q = 0.8092865892227618;
    bband900_f = 899.9997595265272;
    bband900_l = 14.666208917048642;
    bband900_q = 0.14400456547145543;
    nband3k_f = 3009.986891260162;
    nband3k_l = -8.158529858054802;
    nband3k_q = 9.706012982882706;
    nband2_4k_f = 2549.989277861244;
    nband2_4k_l = 5.661325835805933;
    nband2_4k_q = 4.963535206412702;
    nband2_6k_f = 2589.9434207333493;
    nband2_6k_l = -5.399747650020267;
    nband2_6k_q = 15.683364472667014;
    nband3_2k_f = 3201.720511050278;
    nband3_2k_l = 5.258437941356628;
    nband3_2k_q = 2.041835913931366;
    nband4_2k_f = 4277.34257145966;
    nband4_2k_l = -9.21780161572439;
    nband4_2k_q = 2.931945190155691;
    nband4_8k_f = 4795.8591935019285;
    nband4_8k_l = 10.338499026151846;
    nband4_8k_q = 1.346754496703414;
    nband6_7k_f = 6741.63879029361;
    nband6_7k_l = -16.67564915674005;
    nband6_7k_q = 19.99710202404625;
    nband600_f = 601.9999195042174;
    nband600_l = -7.181949517918536;
    nband600_q = 16.2554082997895;
    nband820_f = 825.2095562105882;
    nband820_l = -6.614192318352746;
    nband820_q = 17.478517841309525;
    nband990_f = 981.0000006386933;
    nband990_l = -8.482596344025758;
    nband990_q = 16.82462426781975;
    nband1_1k_f = 1125.9823511404866;
    nband1_1k_l = -7.5178945568579785;
    nband1_1k_q = 13.073810276044432;
    nband1_3k_f = 1364.9990929777402;
    nband1_3k_l = -4.684819517899527;
    nband1_3k_q = 22.493404706589892;
    nband1_7k_f = 1774.573022017944;
    nband1_7k_l = -4.001788606962911;
    nband1_7k_q = 2.0192458013159458;

    cab = _
        : fi.highpass(1, hp_f)
        : fi.lowpass(1, lp_f)
        : fi.highshelf(11, hshelf5k_l, hshelf5k_f)
        : fi.peak_eq_cq(bband150_l, bband150_f, bband150_q)
        : fi.peak_eq_cq(bband900_l, bband900_f, bband900_q)
        : fi.peak_eq_cq(nband3k_l, nband3k_f, nband3k_q)
        : fi.peak_eq_cq(nband2_4k_l, nband2_4k_f, nband2_4k_q)
        : fi.peak_eq_cq(nband2_6k_l, nband2_6k_f, nband2_6k_q)
        : fi.peak_eq_cq(nband3_2k_l, nband3_2k_f, nband3_2k_q)
        : fi.peak_eq_cq(nband4_2k_l, nband4_2k_f, nband4_2k_q)
        : fi.peak_eq_cq(nband4_8k_l, nband4_8k_f, nband4_8k_q)
        : fi.peak_eq_cq(nband6_7k_l, nband6_7k_f, nband6_7k_q)
        : fi.peak_eq_cq(nband600_l, nband600_f, nband600_q)
        : fi.peak_eq_cq(nband820_l, nband820_f, nband820_q)
        : fi.peak_eq_cq(nband990_l, nband990_f, nband990_q)
        : fi.peak_eq_cq(nband1_1k_l, nband1_1k_f, nband1_1k_q)
        : fi.peak_eq_cq(nband1_3k_l, nband1_3k_f, nband1_3k_q)
        : fi.peak_eq_cq(nband1_7k_l, nband1_7k_f, nband1_7k_q)
        // the fit can boost up the peak level, bring it back down to zero
        : *(ba.db2linear(-bband150_l))
        : _ ;
};