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

// API conventions:
//
// The `nentry` function is used by faust to construct a UI. But in this case 
// it is used to track which parameters should be exposed to the plugin.
// Variables aassigned from `nentry` get setters in the standalone header file.
//
// Assume the parameters will be given in the range (-1, +1), and scale them
// here to the appropriate value.

triode_plate = environment {
    // Plate bias
    bias = nentry("triode_plate_bias", 0, -1, +1, .1) : uscale(0, +20);
    // Plate power (typically 1.5)
    power = nentry("triode_plate_power", 0, -1, +1, .1) : uscale(1.0, 2.0);

    scale = nentry("triode_plate_scale", 0, -1, +1, .1) : uscale(0, 100);

    // the level where to start compressing the signal leading to the lower clip
    corner = nentry("triode_plate_corner", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+3)) : exp;
    // the clip level at the bottom of the signal
    clip = nentry("triode_plate_clip", 0, -1, +1, .1) : uscale(-300, 0);

    // compression of the signal w.r.t to a variable level
    level_b = nentry("triode_plate_level_b", 0, -1, +1, .1) : uscale(-50, 25);
    tau_b = nentry("triode_plate_tau_b", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio_b = nentry("triode_plate_ratio_b", 0, -1, +1, .1) : uscale(log(5e-2), log(5e+2)) : exp;
    cap_b = nentry("triode_plate_cap_b", 0, -1, +1, .1) : uscale(0, 100);
    // for computing the variable level
    scale_b = nentry("triode_plate_scale_b", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;
    smooth_b = nentry("triode_plate_smooth_b", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;

    tau1 = tau : 1.0 / (ba.sec2samp(_) + 1);
    tau2 = tau * ratio : 1.0 / (ba.sec2samp(_) + 1);

    tau1_b = tau_b : 1.0 / (ba.sec2samp(_) + 1);
    tau2_b = tau_b * ratio_b : 1.0 / (ba.sec2samp(_) + 1);

    // NOTE: the parameter values were estimated using a signal that has the
    // bias, but here the bias is removed after the power clip. So need to
    // remove it also from the parameters, accouting for phase inversion also
    clip_unscaled = clip + bias^power;
    level_unscaled = level + bias^power;
    level_b_unscaled = level_b + bias^power;

    full = _ 
        // Loss of float precision happens for small signal when subtracting
        // bias, so instead for small signal use a taylor series approximation
        // of the power clip which doesn't require the offset.
        <: mix_wet_dry(
            // When the signal is less than 5% of bias, use approximation, and
            // between 5 and 15% interpolate to full power clip
            max(0, min(1, abs(_) / (bias * 0.1) - 0.05 )),

            // Full power clip, not that we are removing the bias afterwards
            _ : power_clip(power, bias) : -(bias^power), 
            
            // Taylor series of the power clip with bias already removed
            bias^(power - 1) * power * _ 
        )

        : *(-1)

        // There is some additional clipping at the bottom of the the waveform
        : soft_clip_down(corner, clip_unscaled)

        // Noticed a clip level that drifts and found the drift can be modelled
        // by calculating a capacitive-like charging and discharging.
        <: max(0, _ - level_b_unscaled), _
        : calc_charge(cap_b, tau1_b, tau2_b) * scale_b + (level_b_unscaled), _
        : soft_clip_up(smooth_b)

        // Remove scaling imparted by power law so that the output is just the
        // distortion on the signal, no additional scaling
        : /( bias^(power-1) ) 

        // Apply the scale observed in the circuit
        : *(scale)

        : _;
};