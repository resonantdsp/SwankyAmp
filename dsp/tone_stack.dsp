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

tone_stack = tone_stack
with {
    // User inputs, note that these are "controls" which have different impacts
    // on the EQ at different ranges from -1 to +1
    low_ctrl = nentry("ts_low", 0, -1, +1, .1);
    mid_ctrl = nentry("ts_mid", 0, -1, +1, .1);
    high_ctrl = nentry("ts_high", 0, -1, +1, .1);

    interp_ctrl(c, a, b) = (1.0 - (c + 1.0) / 2.0) * a + (c + 1.0) / 2.0 * b;

    low_db = interp_ctrl(low_ctrl, 18.0, 9.0) * low_ctrl;
    low_freq = interp_ctrl(low_ctrl, 400.0, 50.0);

    low_proc = fi.lowshelf(1, low_db, low_freq) : fi.highpass(1, 10.0);

    mid_db = -14.0 + ba.if(mid_ctrl < 0, 9.0, 14.0) * mid_ctrl;
    mid_freq = 500.0;
    mid_band = 1.2e3 + ba.if(low_ctrl < 0, 800.0, 0.0) * mid_ctrl;

    mid_proc = fi.peak_eq(mid_db, mid_freq, mid_band);
    
    high_db = ba.if(high_ctrl < 0, 18.0, 9.0) * high_ctrl;
    high_freq = 2e3 + ba.if(high_ctrl < 0, high_ctrl * 1.5e3, 0.0);

    high_proc = fi.highshelf(1, high_db, high_freq);

    tone_stack = low_proc : mid_proc : high_proc;
};