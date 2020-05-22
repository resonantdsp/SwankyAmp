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

import json
import os

import builddsp


def main():
    # default values for the parameters, when calling `set_value` the values 
    # will be relative to these (0 is default).
    pars = {
        # tone stack
        "ts_low": 0,
        "ts_mid": 0,
        "ts_high": 0,
        # psuh pull amp
        "pre_drive": 0,
        "power_drive": 0,
        "gain_stages": 1,
        "gain_slope": 0,
        "cab_on_off": 1,
        # amp
        "input_level": 0,
        "output_level": 0,
    }

    with open("triode_grid.json", "r") as fio:
        pars.update(json.load(fio))
    with open("triode_plate.json", "r") as fio:
        pars.update(json.load(fio))
    with open("tetrode_grid.json", "r") as fio:
        pars.update(json.load(fio))
    with open("tetrode_plate.json", "r") as fio:
        pars.update(json.load(fio))

    # generate the header code for the DSP object
    os.makedirs("faust_build", exist_ok=True)
    header_code = builddsp.build_header(
        path="faust_build", name="AmpMono", defaults=pars
    )

    with open("../Source/AmpMono.h", "w") as fio:
        fio.write(header_code)


if __name__ == "__main__":
    main()
