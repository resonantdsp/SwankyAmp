#!/usr/bin/env python3
"""Measure the unit-slope knee against the released knee at every seam."""

from __future__ import annotations

import json
import math
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from report import FACTORY_PRESETS, INPUT, PRESETS, ROOT, level, read_float_wav

SAMPLE_RATE = 44_100
INPUT_LEVELS_DB = (-12, -6, 0, 6)
TRIODE_SEAMS = tuple(f"triode_{stage}" for stage in range(1, 6))

# The makeup gains are fitted at 0 dB input. These bounds hold every factory
# preset's seams near the released levels there; the other input levels are
# recorded, not bounded, because they show how compression moved.
# The widest preamp residuals are presets whose stages move in opposite
# directions (pre drive +0.43 dB and level 11 -0.60 dB after the fifth
# triode), which one gain per stage cannot separate; the power stage then
# compresses them.
TRIODE_TOLERANCE_DB = 0.6
TONE_STACK_TOLERANCE_DB = 1.05
POWER_TOLERANCE_DB = 0.5


def tolerance(seam: str) -> float:
    if seam in TRIODE_SEAMS:
        return TRIODE_TOLERANCE_DB
    if seam == "tone_stack":
        return TONE_STACK_TOLERANCE_DB
    return POWER_TOLERANCE_DB


def render(binary: Path, directory: Path, preset: str, gain_db: int, knee: str) -> Path:
    stem = directory / f"{preset.replace(' ', '-')}-{gain_db:+d}-{knee}"
    command = [
        str(binary),
        "--input",
        str(INPUT),
        "--presets",
        str(PRESETS),
        "--preset",
        preset,
        "--sample-rate",
        str(SAMPLE_RATE),
        "--output",
        str(stem.with_suffix(".wav")),
        "--seams-dir",
        str(stem),
        "--model",
        "corrected",
        "--oversampling",
        "1x",
        "--tone-mapping",
        "released",
        "--knee",
        knee,
        "--tables",
        "released",
        "--input-gain-db",
        str(gain_db),
    ]
    subprocess.run(command, check=True, cwd=ROOT)
    return stem


def seams(stem: Path) -> dict[str, dict[str, float]]:
    measured = {}
    for path in sorted(stem.glob("*.wav")):
        values = level(read_float_wav(path)[1])
        values["crest_db"] = values["peak_dbfs"] - values["rms_dbfs"]
        measured[path.stem] = values
    return measured


def compare(
    released: dict[str, dict[str, float]], unit: dict[str, dict[str, float]]
) -> dict[str, dict[str, float]]:
    return {
        seam: {
            "released_rms_dbfs": round(reference["rms_dbfs"], 4),
            "rms_ratio_db": round(unit[seam]["rms_dbfs"] - reference["rms_dbfs"], 4),
            "released_crest_db": round(reference["crest_db"], 4),
            "crest_change_db": round(unit[seam]["crest_db"] - reference["crest_db"], 4),
        }
        for seam, reference in released.items()
    }


def run(binary: Path, destination: Path) -> None:
    cases = [
        (preset, gain_db) for gain_db in INPUT_LEVELS_DB for preset in FACTORY_PRESETS
    ]
    with tempfile.TemporaryDirectory(prefix="swanky-free-knee-") as temporary:
        directory = Path(temporary)

        def measure(case: tuple[str, int]) -> dict[str, dict[str, float]]:
            preset, gain_db = case
            released = seams(render(binary, directory, preset, gain_db, "released"))
            unit = seams(render(binary, directory, preset, gain_db, "unit"))
            return compare(released, unit)

        with ThreadPoolExecutor() as pool:
            measured = list(pool.map(measure, cases))

    levels: dict[str, dict[str, object]] = {}
    for (preset, gain_db), result in zip(cases, measured):
        levels.setdefault(f"{gain_db:+d}", {})[preset] = result
    worst: dict[str, dict[str, float]] = {}
    for gain, presets in levels.items():
        for result in presets.values():
            for seam, values in result.items():
                entry = worst.setdefault(gain, {}).setdefault(
                    seam, {"rms_ratio_db": 0.0, "crest_change_db": 0.0}
                )
                for measure in entry:
                    if abs(values[measure]) > abs(entry[measure]):
                        entry[measure] = values[measure]

    failures = []
    for preset, result in levels["+0"].items():
        for seam, values in result.items():
            if abs(values["rms_ratio_db"]) > tolerance(seam):
                failures.append(f"{preset} {seam} {values['rms_ratio_db']:+.3f} dB")
    if failures:
        raise RuntimeError("unit knee left the released levels:\n  " + "\n  ".join(failures))

    results = {
        "scope": (
            "corrected path at 44.1 kHz and 1x with the released tone mapping, "
            "unit-slope triode knee with its makeup against the released knee; "
            "tetrode and calibration tables released"
        ),
        "measure": (
            "rms_ratio_db is unit minus released seam RMS; crest_change_db is "
            "unit minus released peak-to-RMS; 1024 samples trimmed at each end"
        ),
        "tolerance_db_at_0db_input": {
            "triodes": TRIODE_TOLERANCE_DB,
            "tone_stack": TONE_STACK_TOLERANCE_DB,
            "power_amp_cabinet_output": POWER_TOLERANCE_DB,
        },
        "worst_by_input_level": worst,
        "input_levels": levels,
    }
    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(results, indent=2, sort_keys=True) + "\n")
    print(f"wrote knee measurement report to {destination}")


def main() -> None:
    if len(sys.argv) != 3:
        raise SystemExit("usage: knee.py RENDER_MODEL OUTPUT")
    run(Path(sys.argv[1]).resolve(), Path(sys.argv[2]).resolve())


if __name__ == "__main__":
    main()
