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

    grid_clip = nentry("triode_grid_clip", 0, -1, +1, .1) : uscale(0, +5);
    grid_corner = nentry("triode_grid_corner", 0, -1, +1, .1) : uscale(0, +5);
    
    // Convert to `cap_comp` parameters
    grid_tau1 = grid_tau : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau2 = grid_tau * grid_ratio : 1.0 / (ba.sec2samp(_) + 1);
    grid_tau3 = grid_tau * grid_smooth : 1.0 / (ba.sec2samp(_) + 1);

    triode_grid = _ 
        : fi.highpass(1, hp_freq) 

        <: _, max(0, _ - grid_level)
        : _, calc_charge(grid_tau1, grid_tau2)
        : _, si.smooth(1 - grid_tau3)
        : -
        
        : soft_clip_up(grid_corner, grid_clip)
        : _;
};
