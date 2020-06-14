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

import("stdfaust.lib");
import("common.dsp");

cab = cab
with {
    // offset = nentry("offset", 0, -1, +1, .1);
    // hp_f = nentry("hp_f", 0, -1, +1, .1);
    // lp_f = nentry("lp_f", 0, -1, +1, .1);
    // shelf_f = nentry("shelf_f", 0, -1, +1, .1);
    // shelf_l = nentry("shelf_l", 0, -1, +1, .1);
    // scoop_f = nentry("scoop_f", 0, -1, +1, .1);
    // scoop_l = nentry("scoop_l", 0, -1, +1, .1);
    // scoop_b = nentry("scoop_b", 0, -1, +1, .1);
    // peak_1_f = nentry("peak_1_f", 0, -1, +1, .1);
    // peak_1_l = nentry("peak_1_l", 0, -1, +1, .1);
    // peak_1_b = nentry("peak_1_b", 0, -1, +1, .1);
    // peak_2_f = nentry("peak_2_f", 0, -1, +1, .1);
    // peak_2_l = nentry("peak_2_l", 0, -1, +1, .1);
    // peak_2_b = nentry("peak_2_b", 0, -1, +1, .1);
    // peak_3_f = nentry("peak_3_f", 0, -1, +1, .1);
    // peak_3_l = nentry("peak_3_l", 0, -1, +1, .1);
    // peak_3_b = nentry("peak_3_b", 0, -1, +1, .1);
    // peak_4_f = nentry("peak_4_f", 0, -1, +1, .1);
    // peak_4_l = nentry("peak_4_l", 0, -1, +1, .1);
    // peak_4_b = nentry("peak_4_b", 0, -1, +1, .1);
    // peak_5_f = nentry("peak_5_f", 0, -1, +1, .1);
    // peak_5_l = nentry("peak_5_l", 0, -1, +1, .1);
    // peak_5_b = nentry("peak_5_b", 0, -1, +1, .1);
    // peak_6_f = nentry("peak_6_f", 0, -1, +1, .1);
    // peak_6_l = nentry("peak_6_l", 0, -1, +1, .1);
    // peak_6_b = nentry("peak_6_b", 0, -1, +1, .1);
    // peak_7_f = nentry("peak_7_f", 0, -1, +1, .1);
    // peak_7_l = nentry("peak_7_l", 0, -1, +1, .1);
    // peak_7_b = nentry("peak_7_b", 0, -1, +1, .1);
    // peak_8_f = nentry("peak_8_f", 0, -1, +1, .1);
    // peak_8_l = nentry("peak_8_l", 0, -1, +1, .1);
    // peak_8_b = nentry("peak_8_b", 0, -1, +1, .1);
    // peak_9_f = nentry("peak_9_f", 0, -1, +1, .1);
    // peak_9_l = nentry("peak_9_l", 0, -1, +1, .1);
    // peak_9_b = nentry("peak_9_b", 0, -1, +1, .1);

    offset = 15;
    hp_f = 110;
    lp_f = 11000;
    scoop_f = 950;
    scoop_l = -10;
    scoop_b = 2800;
    shelf_f = 5600;
    shelf_l = -30;
    peak_1_f = 590;
    peak_1_l = -15;
    peak_1_b = 60;
    peak_2_f = 640;
    peak_2_l = 10;
    peak_2_b = 140;
    peak_3_f = 1120;
    peak_3_l = -12;
    peak_3_b = 70;
    peak_4_f = 1180;
    peak_4_l = 9;
    peak_4_b = 160;
    peak_5_f = 1660;
    peak_5_l = -3.5;
    peak_5_b = 790;
    peak_6_f = 3050;
    peak_6_l = -9;
    peak_6_b = 330;
    peak_7_f = 3800;
    peak_7_l = -6;
    peak_7_b = 750;
    peak_8_f = 6800;
    peak_8_l = -30;
    peak_8_b = 200;
    peak_9_f = 12000;
    peak_9_l = -30;
    peak_9_b = 250;

    brightness = nentry("cab_brightness", 0, -1, +1, .1);
    distance = nentry("cab_distance", 0, -1, +1, .1);

    cab = _
        : fi.highpass(4, hp_f)
        : fi.lowpass(3, lp_f)
        : fi.highshelf(7, shelf_l, shelf_f)

        : fi.peak_eq(peak_1_l, peak_1_f, peak_1_b)
        : fi.peak_eq(peak_2_l, peak_2_f, peak_2_b)

        : fi.peak_eq(peak_3_l, peak_3_f, peak_3_b)
        : fi.peak_eq(peak_4_l, peak_4_f, peak_4_b)

        : fi.peak_eq(peak_5_l, peak_5_f, peak_5_b)

        : fi.peak_eq(peak_6_l, peak_6_f, peak_6_b)
        : fi.peak_eq(peak_7_l, peak_7_f, peak_7_b)

        : fi.peak_eq(peak_8_l, peak_8_f, peak_8_b)
        : fi.peak_eq(peak_9_l, peak_9_f, peak_9_b)

        : fi.peak_eq(scoop_l, scoop_f, scoop_b)

        : fi.low_shelf(-3 * brightness, 1100)
        : fi.peak_eq(15 * brightness, 6000, 1000)

        : fi.peak_eq(-10 * distance, 70, 100)
        : fi.peak_eq(-17 * distance, 1200, 300)
        : *(ba.db2linear(2 * distance))

        : *(ba.db2linear(offset))

        : _ ;
};