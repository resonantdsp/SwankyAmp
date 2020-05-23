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

tetrode_plate = environment {
    // See `triode_plate.dsp` for more info on common functionality

    power = nentry("tetrode_plate_power", 0, -1, +1, 1) : uscale(1.0, 2.0);
    bias = nentry("tetrode_plate_bias", 0, -1, +1, 1) : uscale(30, 50);

    scale = nentry("tetrode_plate_scale", 0, -1, +1, 1) : uscale(log(1e-2), log(1e2)) : exp;
    // The working point
    point = nentry("tetrode_plate_point", 0, -1, +1, 1) : uscale(0, 20);

    level = nentry("tetrode_plate_level", 0, -1, +1, .1) : uscale(0, 100);
    tau = nentry("tetrode_plate_tau", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio = nentry("tetrode_plate_ratio", 0, -1, +1, .1) : uscale(log(1e-2), log(1e+2)) : exp;
    cap = nentry("tetrode_plate_cap", 0, -1, +1, .1) : uscale(0, 100);

    tau1 = tau : 1.0 / (ba.sec2samp(_) + 1);
    tau2 = tau * ratio : 1.0 / (ba.sec2samp(_) + 1);

    corner = nentry("tetrode_plate_corner", 0, -1, +1, 1) : uscale(0, 20);
    clip = nentry("tetrode_plate_clip", 0, -1, +1, 1) : uscale(10, 50);

    corner_b = nentry("tetrode_plate_corner_b", 0, -1, +1, 1) : uscale(0, 10);
    hp_freq = nentry("tetrode_plate_hp", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;

    // This is the common process for both sides of the signal
    side = _ 
        : *(-1)

        // See triode code for notes on this
        <: mix_wet_dry(
            // When the signal is less than 5% of bias, use approximation, and
            // between 5 and 15% interpolate to full power clip
            max(0, min(1, abs(_) / (bias * 0.1) - 0.05 )),

            // Full power clip, not that we are removing the bias afterwards
            _ : power_clip(power, bias) : -(bias^power), 
            
            // Taylor series of the power clip with bias already removed
            bias^(power - 1) * power * _ 
        )
        // current centered about bias, but want to be centered about working 
        // point
        : -(point^power - bias^power)

        // Scaling to get something like the plate signal (the parameters
        // were first estimated by measuring the plate signal)
        : *(scale)

        // Some compression can be observed, this is also what will cause the
        // cross over distortion
        : cap_comp(level, cap, tau1, tau2, 1.0)

        // There appears to be a ceiling to the signal, so apply clipping. The
        // difference in signal scales very non-linearly.
        : soft_clip_up(corner, clip)

        // Keep just one side of the signal (push-pull)
        : max(0)
        // Soften the cross over distortion edge
        : soft_clip_down(corner_b, 0)

        // Noticed lack of low featurse (no flat edges)
        : fi.highpass(1, hp_freq) 

        : *(-1)

        : _;
    
    // Combine both sides in push-pull fashion
    full = _
        <: *(-1), _
        : side, side
        : *(-1), _
        : +
        : _;
};