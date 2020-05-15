#!/usr/bin/env python

#  Resonant Amp tube amplifier simulation
#  Copyright (C) 2020  Garrin McGoldrick
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <https://www.gnu.org/licenses/>.

import os

import builddsp


def main():
    # default values for the parameters, when calling `set_value` the values 
    # will be relative to these (0 is default).
    pars = {
        # triode grid
        "triode_hp_freq": +4.943e-01,
        "triode_clip_tau": -1.533e01,
        "triode_clip_ratio": +1.583e00,
        "triode_clip_smooth": +2.778e02,
        "triode_clip_level": +3.612e03,
        "triode_grid_tau": -3.802e-01,
        "triode_grid_ratio": +7.121e-01,
        "triode_grid_smooth": +7.747e00,
        "triode_grid_level": +3.521e-01,
        # triode plate
        "triode_plate_power": +1.343e-02,
        "triode_plate_bias": -1.156e-01,
        "triode_plate_corner": +3.787e-01,
        "triode_plate_clip": -2.068e-02,
        "triode_plate_level": +7.368e-04,
        "triode_plate_tau": -1.602e-01,
        "triode_plate_ratio": -4.118e-01,
        "triode_plate_level_b": -1.179e-01,
        "triode_plate_tau_b": -4.299e-01,
        "triode_plate_ratio_b": +4.089e-01,
        "triode_plate_scale_b": -3.789e-01,
        "triode_plate_smooth_b": -2.361e-01,
        # tetrode grid
        "tetrode_hp_freq": +5.073e-01,
        "tetrode_grid_tau": -1.107e-01,
        "tetrode_grid_ratio": -1.091e-01,
        "tetrode_grid_level": +4.533e-01,
        # tetrode plate
        "tetrode_plate_corner": +2.116e-01,
        "tetrode_plate_clip": -2.362e-02,
        "tetrode_plate_level": +3.277e-02,
        "tetrode_plate_tau": +1.959e-01,
        "tetrode_plate_ratio": -1.430e-01,
        # tone stack
        "ts_low": 0,
        "ts_mid": 0,
        "ts_high": 0,
    }

    # generate the header code for the DSP object
    os.makedirs("faust_build", exist_ok=True)
    header_code = builddsp.build_header(
        path="faust_build", name="AmpMono", defaults=pars
    )

    with open("../Source/AmpMono.h", "w") as fio:
        fio.write(header_code)


if __name__ == "__main__":
    main()
