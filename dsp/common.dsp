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

ftanh = ftanh
with {
    ftanh1 = max(-1, min(+1, _ / 3.4));
    ftanh2 = _ <: (abs(ftanh1) - 2), ftanh1 : * ;
    ftanh = _ <: (abs(ftanh2) - 2), ftanh2 : * ;
    
};

// Linear transformation of a value such that its range [-1, +1] maps to the
// range [vmin, vmax]
uscale(vmin, vmax) = +(1) : /(2) : *(vmax - vmin) : +(vmin);

// Build up a charge when a signal is greater than the current charge, and
// decay that charge otherwise. Versatile for modelling effects wherein some
// bias is drifting, as this is often related to some effective capcitance
// charging and discharging.
calc_charge(cap, tau1, tau2, s) = c
letrec {
    'c = c + tau1 * max(0, s - c) * max(0, cap - c) / cap -tau2 * c;
};

// Compression of signal due to charge buildup that biases the signal.
cap_comp(level, cap, tau1, tau2, tau3) = _ 
    <: _, max(0, _ - level)
    : _, calc_charge(cap, tau1, tau2)
    : _, si.smooth(1 - tau3)
    : -
    : _;

// Apply soft clipping (tanh) to the portion of a signal between `scale` and
// `level`. The signal won't exceed `level`.
soft_clip_up(scale, level) = _ 
    : -(level - scale)
    <: min(0), max(0)
    : _, ftanh(_ / scale) * scale
    : +
    : +(level - scale)
    : _;

// Like `soft_clip_up` but applies to the portion of a signal below `scale`.
// It is possible to acheive the same effect by reversing the polarity of a
// signal and using `soft_clip_up` but this is provided as a convenience.
soft_clip_down(scale, level) = _ 
    : -(level + scale)
    <: min(0), max(0)
    : ftanh(_ / scale) * scale, _
    : +
    : +(level + scale)
    : _;

// Applies power scaling to a signal, and clips the signal below 0.
power_clip(power, level) = _
    : +(level)
    : max(0)
    : ^(power)
    : _;

// Given 3 channels, mixes the 2nd channel with weight given in the first
// channel, and mixes the 3rd channel with remaining weight. Note that the
// mix value should be in the range (0, 1).
mix_wet_dry(mix, wet, dry) = mix * wet + (1 - mix) * dry;