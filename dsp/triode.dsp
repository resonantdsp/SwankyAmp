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

triode_grid = triode_grid
with {
    // High pass frequency for the signal coming into the tridoe, this is the 
    // result of the capacitor after the input signal and also means we don't
    // have to worry about signal biases. This has an audible impact on the
    // signal and can be used to shape it into the desired tone.
    hp_freq = nentry("triode_hp_freq", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;
    
    // Observed a soft compression on the upper portion of the signal before 
    // grid conduction regime. This is well modelled by `cap_comp`. Suspect
    // this is the result of some capacitance between grid and plate?
    grid_tau = nentry("triode_grid_tau", 0, -1, +1, .1) : uscale(log(1e-6), log(1e-3)) : exp;
    grid_ratio = nentry("triode_grid_ratio", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+4)) : exp;
    grid_smooth = nentry("triode_grid_smooth", 0, -1, +1, .1) : uscale(log(1e-5), log(1e+1)) : exp;
    grid_level = nentry("triode_grid_level", 0, -1, +1, .1) : uscale(-5, +5);
    
    // This is mean to emulate grid conduction regime. The level is higher 
    // than the previous compression and the time scale is shorter, this is a
    // more pronounced effect. It is well modelled by `cap_comp` though its
    // not obvious to me why that should be.
    clip_tau = nentry("triode_clip_tau", 0, -1, +1, .1) : uscale(log(1e-8), log(1e-4)) : exp;
    clip_ratio = nentry("triode_clip_ratio", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+4)) : exp;
    clip_smooth = nentry("triode_clip_smooth", 0, -1, +1, .1) : uscale(log(1e-5), log(1e+1)) : exp;
    clip_level = nentry("triode_clip_level", 0, -1, +1, .1) : uscale(1, 3);
    
    // Convert to `cap_comp` parameters
    grid_tau1 = grid_tau : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau2 = grid_tau * grid_ratio : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau3 = grid_tau * grid_smooth : 1.0 / (ba.sec2samp(_) + 1);
    
    clip_tau1 = clip_tau : 1.0 / (ba.sec2samp(_) + 1);
    clip_tau2 = clip_tau * clip_ratio : 1.0 / (ba.sec2samp(_) + 1);
    clip_tau3 = clip_tau * clip_smooth : 1.0 / (ba.sec2samp(_) + 1);

    triode_grid = _ 
        : fi.highpass(1, hp_freq) 
        : cap_comp(grid_level, grid_tau1, grid_tau2, grid_tau3)
        : cap_comp(clip_level, clip_tau1, clip_tau2, clip_tau3)
        : _;
};

triode_plate = environment {
    // Plate bias
    bias = nentry("triode_plate_bias", 0, -1, +1, .1) : uscale(0, +20);
    // Plate power (typically 1.5)
    power = nentry("triode_plate_power", 0, -1, +1, .1) : uscale(0.5, 2.5);

    // the level where to start compressing the signal leading to the lower clip
    corner = nentry("triode_plate_corner", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+3)) : exp;
    // the clip level at the bottom of the signal
    clip = nentry("triode_plate_clip", 0, -1, +1, .1) : uscale(-300, 0);

    // compression of the signal above level
    level = nentry("triode_plate_level", 0, -1, +1, .1) : uscale(-100, 50);
    tau = nentry("triode_plate_tau", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio = nentry("triode_plate_ratio", 0, -1, +1, .1) : uscale(log(1e-2), log(1e+2)) : exp;

    // compression of the signal w.r.t to a variable level
    level_b = nentry("triode_plate_level_b", 0, -1, +1, .1) : uscale(-50, 25);
    tau_b = nentry("triode_plate_tau_b", 0, -1, +1, .1) : uscale(log(1e-4), log(1e+0)) : exp;
    ratio_b = nentry("triode_plate_ratio_b", 0, -1, +1, .1) : uscale(log(5e-2), log(5e+2)) : exp;
    // for computing the variable level
    scale_b = nentry("triode_plate_scale_b", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;
    smooth_b = nentry("triode_plate_smooth_b", 0, -1, +1, .1) : uscale(log(1e-1), log(1e+2)) : exp;

    tau1 = tau : 1.0 / (ba.sec2samp(_) + 1);
    tau2 = tau * ratio : 1.0 / (ba.sec2samp(_) + 1);

    tau1_b = tau_b : 1.0 / (ba.sec2samp(_) + 1);
    tau2_b = tau_b * ratio_b : 1.0 / (ba.sec2samp(_) + 1);

    mixab(m, a, b) = m * a + (1 - m) * b;

    // NOTE: the parameters are fit w.r.t. to the bias value, but it is
    // subtracted in the signal, the +bias^power is added to remove it from
    // the parameters

    full = _ 
        // Loss of float precision happens for small signal when subtracting
        // bias, so instead for small signal use a taylor series approximation
        // of the power clip which doesn't require the offset.
        <: mixab(
            // When the signal is less than 5% of bias, use approximation, and
            // between 5 and 15% interpolate to full power clip
            max(0, min(1, abs(_) / (bias * 0.1) - 0.05 )),

            // Full power clip, not that we are removing the bias afterwards
            _ : power_clip(power, bias) : -(bias^power), 
            
            // Taylor series of the power clip with bias already removed
            bias^(power - 1) * power * _ 
        )
        : *(-1)

        // The power clipping is not continuous, smoothen it
        : soft_clip_down(corner, (clip + bias^power))

        // Compress the signal above level, not sure if this is a tube effect
        // or maybe related to voltage changes on the plate.
        <: _, max(0, _ - (level + bias^power))
        : _, calc_charge(tau1, tau2)
        : -

        // Noticed a clip level that drifts and found the drift can be modelled
        // by the same sort of capacitive compression mechanism.
        <: max(0, _ - (level_b + bias^power)), _
        : calc_charge(tau1_b, tau2_b) * scale_b + (level_b + bias^power), _
        : soft_clip_up(smooth_b)

        // Remove scaling imparted by power law so that the output is just the
        // distortion on the signal, no additional scaling
        : /( bias^(power-1) ) 

        : _;

    // Simplified version just runs the signal throughh the power law, and
    // softens the clipping happening at zero.
    simplified = _ 
        <: mixab(
            max(0, min(1, abs(_) / (bias * 0.1) - 0.05 )),
            _ : power_clip(power, bias) : -(bias^power), 
            bias^(power - 1) * power * _ 
        )
        : *(-1)
        : soft_clip_down(corner, (clip + bias^power))
        : /( bias^(power-1) ) 
        : _;
};