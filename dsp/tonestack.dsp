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

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

tone_stack = tone_stack
with {
    // User inputs, note that these are "controls" which have different impacts
    // on the EQ at different ranges from -1 to +1
    low_ctrl = nentry("ts_low", 0, -1, +1, .1);
    mid_ctrl = nentry("ts_mid", 0, -1, +1, .1);
    high_ctrl = nentry("ts_high", 0, -1, +1, .1);

    // two different db scales, used for different control ranges
    db_high = 13;
    db_low = 5;
    // control switches to cut behaviour below this value
    cut_level = -0.8;

    low_freq_ref = 100;
    mid_freq = 440.0;
    mid_band = 1000.0;
    mid_cut_width = 100.0;
    high_freq = 2000;

    // lowshelf db level, scales more strongly when control < 0
    low_db = ba.if(
        low_ctrl > 0,
        low_ctrl * 5 + db_high,  // ranges from +13 to +18
        low_ctrl * 18 + db_high  // ranges from +13 to -5
    );

    // when low control is below 0, the shelf frequency is lower
    low_freq = ba.if(
        low_ctrl > 0,
        low_freq_ref,
        low_freq_ref / 2
    );

    // if the low control goes into cut mode, mix this low cut with the shelf
    low_cut = ba.if(low_ctrl < cut_level, (low_ctrl - cut_level) / (-1 - cut_level), 0);
    // the low control process
    low_proc = 
        fi.lowshelf(1, low_db, low_freq) 
        <: *(1 - low_cut), low_cut * fi.highpass(1, low_freq_ref / 4) 
        : + ;

    // mid control scales more strongly when > 0, and mid db defaults to -3
    mid_db = ba.if(
        mid_ctrl > 0,
        mid_ctrl * db_high - 3,
        mid_ctrl * db_low - 3
    );

    mid_cut = ba.if(mid_ctrl < cut_level, (mid_ctrl - cut_level) / (-1 - cut_level), 0);
    mid_proc = 
        fi.peak_eq(mid_db, mid_freq, mid_band) 
        <: *(1 - mid_cut), mid_cut * fi.bandstop(1, mid_freq - mid_cut_width, mid_freq + mid_cut_width) 
        : + ;

    // limilar to low
    high_db = ba.if(
        high_ctrl > 0,
        high_ctrl * 10 + db_high,  // ranges from +13 to +23
        high_ctrl * 18 + db_high  // ranges from +13 to -5
    );

    high_cut = ba.if(high_ctrl < cut_level, (high_ctrl - cut_level) / (-1 - cut_level), 0);
    high_proc = 
        fi.highshelf(1, high_db, high_freq) 
        <: *(1 - high_cut), high_cut * fi.lowpass(1, 8 * high_freq) 
        : + ;

    // NOTE: these parameters are hand tuned to avoid sounding like the volume
    // changes when the tone is changed. If the frequencies and/or bandwidths
    // are change significantly these will need to be re-calibrated.
    db_corr = 0.4 * low_db + 0.6 * mid_db + 0.2 * high_db;

    tone_stack = low_proc : mid_proc : high_proc : *(ba.db2linear(-db_corr));
};