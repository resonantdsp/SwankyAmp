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

// Transform a value in the range (-inf, +inf) to (-1, +1)
nscale(vmin, vmax) = ma.tanh : +(1) : /(2) : *(vmax - vmin) : +(vmin);

// Linear transformation of a value such that its range [-1, +1] maps to the
// range [vmin, vmax]
uscale(vmin, vmax) = +(1) : /(2) : *(vmax - vmin) : +(vmin);

// Build up a charge when a signal is greater than the current charge, and
// decay that charge otherwise. Versatile for modelling effects wherein some
// bias is drifting, as this is often related to some effective capcitance
// somewhere charging and discharging.
calc_charge(tau1, tau2, s) = c
letrec {
    'c = c + tau1 * max(0, s - c) -tau2 * c;
};

// Compression of signal due to charge buildup that biases the signal.
cap_comp(level, tau1, tau2, tau3) = _ 
    <: _, max(0, _ - level)
    : _, calc_charge(tau1, tau2)
    : _, si.smooth(1 - tau3)
    : -
    : _;

// Apply soft clipping (tanh) to the portion of a signal above `level`. The
// `scale` determines over what range the signal is being compressed as it
// reaches `level`. The output signal will not exceed `level`.
soft_clip_up(scale, level) = _ 
    : -(level - scale)
    <: min(0), max(0)
    : _, ma.tanh(_ / scale) * scale
    : +
    : +(level - scale)
    : _;

// Like `soft_clip_up` but applies to the portion of a signal below `level`.
// It is possible to acheive the same effect by reversing the polarity of a
// signal and using `soft_clip_up` but this is provided as a convenience.
soft_clip_down(scale, level) = _ 
    : -(level + scale)
    <: min(0), max(0)
    : ma.tanh(_ / scale) * scale, _
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