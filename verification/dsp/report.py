#!/usr/bin/env python3
"""Measure the corrected Free tube path against its legacy diagnostic path."""

from __future__ import annotations

import json
import math
import struct
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
INPUT = ROOT / "verification" / "reference" / "input" / "single-coil.wav"
PRESETS = ROOT / "verification" / "reference" / "released" / "Resources" / "presets.xml"
RATES = (44_100, 48_000, 88_200, 96_000)
FACTORY_PRESETS = (
    "clean",
    "bright",
    "edge",
    "distort",
    "dirty distort",
    "pre drive",
    "power drive",
    "full drive",
    "high gain",
    "level 11",
)
BLOCK_TRIM = 1_024


def read_float_wav(path: Path) -> tuple[int, tuple[float, ...]]:
    data = path.read_bytes()
    position = 12
    sample_rate = None
    samples = None
    while position + 8 <= len(data):
        kind = data[position : position + 4]
        size = struct.unpack_from("<I", data, position + 4)[0]
        body = data[position + 8 : position + 8 + size]
        if kind == b"fmt ":
            encoding, channels, sample_rate, _, _, bits = struct.unpack_from(
                "<HHIIHH", body
            )
            if (encoding, channels, bits) != (3, 1, 32):
                raise RuntimeError(f"unexpected WAV format: {path}")
        elif kind == b"data":
            samples = struct.unpack(f"<{len(body) // 4}f", body)
        position += 8 + size + (size & 1)
    if sample_rate is None or samples is None:
        raise RuntimeError(f"incomplete WAV: {path}")
    if any(not math.isfinite(sample) for sample in samples):
        raise RuntimeError(f"non-finite audio: {path}")
    return sample_rate, samples


def write_tone(path: Path, sample_rate: int, frequency: float = 7_000.0) -> None:
    frames = sample_rate
    samples = [
        round(0.08 * math.sin(2.0 * math.pi * frequency * frame / sample_rate) * 8_388_608)
        for frame in range(frames)
    ]
    payload = bytearray()
    for sample in samples:
        value = sample & 0xFF_FFFF
        payload.extend((value & 0xFF, (value >> 8) & 0xFF, (value >> 16) & 0xFF))
    size = len(payload)
    header = struct.pack(
        "<4sI4s4sIHHIIHH4sI",
        b"RIFF",
        36 + size,
        b"WAVE",
        b"fmt ",
        16,
        1,
        1,
        sample_rate,
        sample_rate * 3,
        3,
        24,
        b"data",
        size,
    )
    path.write_bytes(header + payload)


def level(samples: tuple[float, ...]) -> dict[str, float]:
    if len(samples) > 2 * BLOCK_TRIM:
        samples = samples[BLOCK_TRIM:-BLOCK_TRIM]
    rms = math.sqrt(sum(sample * sample for sample in samples) / len(samples))
    peak = max(map(abs, samples), default=0.0)
    return {
        "rms_dbfs": 20.0 * math.log10(max(rms, 1.0e-30)),
        "peak_dbfs": 20.0 * math.log10(max(peak, 1.0e-30)),
    }


def amplitude(samples: tuple[float, ...], sample_rate: int, frequency: float) -> float:
    samples = samples[len(samples) // 2 :]
    real = 0.0
    imaginary = 0.0
    for index, sample in enumerate(samples):
        phase = 2.0 * math.pi * frequency * index / sample_rate
        real += sample * math.cos(phase)
        imaginary -= sample * math.sin(phase)
    return math.hypot(real, imaginary)


def alias_level(samples: tuple[float, ...], sample_rate: int) -> float:
    fundamental = 7_000.0
    nyquist = sample_rate / 2.0
    in_band = [fundamental * harmonic for harmonic in range(1, 7) if fundamental * harmonic < nyquist]
    aliases: list[float] = []
    for harmonic in range(2, 17):
        frequency = fundamental * harmonic
        if frequency < nyquist:
            continue
        folded = abs((frequency + nyquist) % sample_rate - nyquist)
        if folded < 20.0 or any(abs(folded - known) < 1.0 for known in in_band):
            continue
        if all(abs(folded - known) >= 1.0 for known in aliases):
            aliases.append(folded)
    alias_energy = math.sqrt(sum(amplitude(samples, sample_rate, value) ** 2 for value in aliases))
    carrier = amplitude(samples, sample_rate, fundamental)
    return 20.0 * math.log10(max(alias_energy, 1.0e-30) / max(carrier, 1.0e-30))


def render(
    binary: Path,
    directory: Path,
    input_path: Path,
    sample_rate: int,
    model: str,
    oversampling: str | None,
    seams: bool,
    cabinet_off: bool = False,
) -> tuple[Path, dict[str, object]]:
    stem = f"{sample_rate}-{model}-{oversampling or 'released'}"
    if cabinet_off:
        stem += "-alias"
    output = directory / f"{stem}.wav"
    report = directory / f"{stem}.json"
    command = [
        str(binary),
        "--input",
        str(input_path),
        "--presets",
        str(PRESETS),
        "--preset",
        "level 11" if cabinet_off else "high gain",
        "--sample-rate",
        str(sample_rate),
        "--output",
        str(output),
        "--model",
        model,
        "--report",
        str(report),
    ]
    if oversampling is not None:
        command.extend(("--oversampling", oversampling))
    if model == "corrected":
        # This report isolates oversampling and the plate filter, so it keeps
        # the released tone mapping; the tone-stack refit has its own report.
        command.extend(("--tone-mapping", "released"))
    if seams:
        command.extend(("--seams-dir", str(directory / f"{stem}-seams")))
    if cabinet_off:
        command.append("--cabinet-off")
    subprocess.run(command, check=True, cwd=ROOT)
    return output, json.loads(report.read_text())


def reset_audit(
    binary: Path, directory: Path, preset: str, sample_rate: int
) -> dict[str, object]:
    report = directory / f"reset-{preset.replace(' ', '-')}-{sample_rate}.json"
    subprocess.run(
        [
            str(binary),
            "--input",
            str(INPUT),
            "--presets",
            str(PRESETS),
            "--preset",
            preset,
            "--sample-rate",
            str(sample_rate),
            "--output",
            str(report),
            "--oversampling",
            "auto",
            "--reset-audit",
        ],
        check=True,
        cwd=ROOT,
    )
    return json.loads(report.read_text())


def seam_levels(directory: Path, stem: str) -> dict[str, dict[str, float]]:
    return {
        path.stem: level(read_float_wav(path)[1])
        for path in sorted((directory / f"{stem}-seams").glob("*.wav"))
    }


def deltas(
    reference: dict[str, dict[str, float]], actual: dict[str, dict[str, float]]
) -> dict[str, dict[str, float]]:
    return {
        seam: {
            measure.replace("_dbfs", "_delta_db"): actual[seam][measure] - values[measure]
            for measure in ("rms_dbfs", "peak_dbfs")
        }
        for seam, values in reference.items()
        if seam in actual
    }


def run(render_binary: Path, probe_binary: Path, destination: Path) -> None:
    probe = json.loads(subprocess.run(
        [str(probe_binary)], check=True, text=True, stdout=subprocess.PIPE, cwd=ROOT
    ).stdout)
    expected_policy = {
        44_100: [1, 0, 1, 2],
        48_000: [1, 0, 1, 2],
        88_200: [0, 0, 1, 1],
        96_000: [0, 0, 1, 1],
    }
    if {
        int(case["sample_rate"]): case["doublings"] for case in probe["policy"]
    } != expected_policy:
        raise RuntimeError(f"oversampling policy changed: {probe['policy']}")
    for impulse in probe["impulses"]:
        if impulse["reported_latency"] != impulse["peak_sample"]:
            raise RuntimeError(f"reported latency misses impulse peak: {impulse}")
        if impulse["symmetry_max_error"] > 1.0e-6:
            raise RuntimeError(f"round-trip impulse is not linear phase: {impulse}")

    results: dict[str, object] = {
        "scope": "oversampling and 20 kHz plate filter only; released knee and tone mapping retained",
        "policy": probe["policy"],
        "latency_impulses": probe["impulses"],
        "reset_control_extremes": probe["reset_extremes"],
        "rates": {},
    }
    with tempfile.TemporaryDirectory(prefix="swanky-free-dsp-") as temporary:
        temporary = Path(temporary)
        for sample_rate in RATES:
            legacy_output, legacy_report = render(
                render_binary, temporary, INPUT, sample_rate, "legacy", None, True
            )
            one_output, one_report = render(
                render_binary, temporary, INPUT, sample_rate, "corrected", "1x", True
            )
            auto_output, auto_report = render(
                render_binary, temporary, INPUT, sample_rate, "corrected", "auto", True
            )
            legacy_stem = f"{sample_rate}-legacy-released"
            one_stem = f"{sample_rate}-corrected-1x"
            auto_stem = f"{sample_rate}-corrected-auto"
            legacy_levels = seam_levels(temporary, legacy_stem)
            one_levels = seam_levels(temporary, one_stem)
            auto_levels = seam_levels(temporary, auto_stem)

            tone = temporary / f"tone-{sample_rate}.wav"
            write_tone(tone, sample_rate)
            alias_outputs = {}
            alias_reports = {}
            for choice in ("1x", "auto"):
                output, report = render(
                    render_binary,
                    temporary,
                    tone,
                    sample_rate,
                    "corrected",
                    choice,
                    False,
                    cabinet_off=True,
                )
                alias_outputs[choice] = alias_level(read_float_wav(output)[1], sample_rate)
                alias_reports[choice] = report

            results["rates"][str(sample_rate)] = {
                "legacy": legacy_report,
                "corrected_1x": one_report,
                "corrected_auto": auto_report,
                "seam_level_auto_minus_legacy": deltas(legacy_levels, auto_levels),
                "seam_level_corrected_1x_minus_legacy": deltas(legacy_levels, one_levels),
                "seam_level_auto_minus_corrected_1x": deltas(one_levels, auto_levels),
                "alias_dbc": alias_outputs,
                "alias_auto_minus_1x_db": alias_outputs["auto"] - alias_outputs["1x"],
                "output_level_dbfs": {
                    "legacy": level(read_float_wav(legacy_output)[1]),
                    "corrected_1x": level(read_float_wav(one_output)[1]),
                    "corrected_auto": level(read_float_wav(auto_output)[1]),
                },
                "alias_factors": {
                    choice: alias_reports[choice]["factor"] for choice in ("1x", "auto")
                },
            }
            alias_change = alias_outputs["auto"] - alias_outputs["1x"]
            if sample_rate < 88_200 and alias_change > -3.0:
                raise RuntimeError(
                    f"Auto alias reduction at {sample_rate} Hz is only {-alias_change:.3f} dB"
                )
            if sample_rate >= 88_200 and abs(alias_change) > 1.0e-9:
                raise RuntimeError(f"Auto should resolve to 1x at {sample_rate} Hz")
            if sample_rate == 44_100:
                neutral = deltas(legacy_levels, one_levels)
                if any(
                    abs(value) > 1.0e-6
                    for seam in neutral.values()
                    for value in seam.values()
                ):
                    raise RuntimeError("the corrected 20 kHz plate filter is not neutral at 44.1 kHz")

        reset_cases = [
            reset_audit(render_binary, temporary, preset, sample_rate)
            for sample_rate in RATES
            for preset in FACTORY_PRESETS
        ]
        results["realtime_reset_equilibrium"] = {
            "cases": reset_cases,
            "worst_max_error": max(case["max_error"] for case in reset_cases),
            "worst_rms_error": max(case["rms_error"] for case in reset_cases),
            "smallest_stale_max_error": min(
                case["stale_max_error"] for case in reset_cases
            ),
        }
        if any(
            not math.isfinite(case[measure])
            for case in reset_cases
            for measure in ("max_error", "rms_error", "stale_max_error")
        ):
            raise RuntimeError("real-time reset equilibrium audit produced non-finite evidence")
        all_reset_cases = reset_cases + probe["reset_extremes"]
        worst_peak = max(case["max_error"] for case in all_reset_cases)
        worst_rms = max(case["rms_error"] for case in all_reset_cases)
        if worst_peak > 1.0e-3 or worst_rms > 5.0e-4:
            raise RuntimeError(
                f"real-time reset differs from prepared equilibrium: peak {worst_peak}, RMS {worst_rms}"
            )
        driven_cases = reset_cases + [
            case for case in probe["reset_extremes"] if case["name"] == "maximum"
        ]
        if min(case["stale_max_error"] for case in driven_cases) < 1.0e-3:
            raise RuntimeError("reset audit did not establish materially driven state")

    destination.parent.mkdir(parents=True, exist_ok=True)
    destination.write_text(json.dumps(results, indent=2, sort_keys=True) + "\n")
    print(f"wrote DSP measurement report to {destination}")


def main() -> None:
    if len(sys.argv) != 4:
        raise SystemExit("usage: report.py RENDER_MODEL DSP_PROBE OUTPUT")
    run(Path(sys.argv[1]).resolve(), Path(sys.argv[2]).resolve(), Path(sys.argv[3]).resolve())


if __name__ == "__main__":
    main()
