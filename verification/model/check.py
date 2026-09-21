#!/usr/bin/env python3
"""Compare the Rust Free model with the warmed released 1.4.0 chain."""

from __future__ import annotations

import argparse
import math
import struct
import subprocess
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
REFERENCE = ROOT / "verification" / "reference" / "render-comparison.sh"
INPUT = ROOT / "verification" / "reference" / "input" / "single-coil.wav"
PRESETS = ROOT / "verification" / "reference" / "released" / "Resources" / "presets.xml"
SAMPLE_RATE = 44_100
PRESET_NAMES = (
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

# These bounds describe numerical agreement between two translations of the
# released equations. Spectral level is the audible acceptance criterion;
# waveform bounds catch polarity, timing, and state errors that level can hide.
RELATIVE_RMS_TOLERANCE = 0.002
RELATIVE_PEAK_TOLERANCE = 0.006
BAND_LEVEL_TOLERANCE_DB = 0.02
BANDS = ("low", "mid", "high")


def read_float_wav(path: Path) -> tuple[int, tuple[float, ...]]:
    data = path.read_bytes()
    if data[:4] != b"RIFF" or data[8:12] != b"WAVE":
        raise RuntimeError(f"not WAV: {path}")
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


def biquad(samples: tuple[float, ...], frequency: float, highpass: bool) -> tuple[float, ...]:
    omega = 2.0 * math.pi * frequency / SAMPLE_RATE
    cosine = math.cos(omega)
    alpha = math.sin(omega) / (2.0 * math.sqrt(0.5))
    if highpass:
        b0, b1, b2 = (1.0 + cosine) / 2.0, -(1.0 + cosine), (1.0 + cosine) / 2.0
    else:
        b0, b1, b2 = (1.0 - cosine) / 2.0, 1.0 - cosine, (1.0 - cosine) / 2.0
    divisor = 1.0 + alpha
    b0, b1, b2 = b0 / divisor, b1 / divisor, b2 / divisor
    a1, a2 = -2.0 * cosine / divisor, (1.0 - alpha) / divisor
    x1 = x2 = y1 = y2 = 0.0
    output = []
    for sample in samples:
        value = b0 * sample + b1 * x1 + b2 * x2 - a1 * y1 - a2 * y2
        output.append(value)
        x2, x1, y2, y1 = x1, sample, y1, value
    return tuple(output)


def band_levels(samples: tuple[float, ...]) -> dict[str, float]:
    bands = {
        "low": biquad(samples, 250.0, False),
        "mid": biquad(biquad(samples, 250.0, True), 2_000.0, False),
        "high": biquad(samples, 2_000.0, True),
    }
    return {
        name: 20.0 * math.log10(max(1.0e-30, rms(values)))
        for name, values in bands.items()
    }


def rms(samples: tuple[float, ...]) -> float:
    return math.sqrt(sum(sample * sample for sample in samples) / len(samples))


def slug(index: int, name: str) -> str:
    return f"{index:02d}-{name.replace(' ', '-')}-{SAMPLE_RATE}"


def render_model(binary: Path, destination: Path, index: int, name: str) -> None:
    stem = slug(index, name)
    subprocess.run(
        [
            str(binary),
            "--input",
            str(INPUT),
            "--presets",
            str(PRESETS),
            "--preset",
            name,
            "--sample-rate",
            str(SAMPLE_RATE),
            "--output",
            str(destination / f"{stem}.wav"),
            "--seams-dir",
            str(destination / f"{stem}-seams"),
        ],
        check=True,
        cwd=ROOT,
    )


def compare(reference: Path, model: Path) -> tuple[float, float, dict[str, float]]:
    reference_rate, expected = read_float_wav(reference)
    model_rate, actual = read_float_wav(model)
    if reference_rate != model_rate or len(expected) != len(actual):
        raise RuntimeError(f"WAV shape differs: {model}")
    expected_rms = rms(expected)
    expected_peak = max(map(abs, expected), default=0.0)
    differences = tuple(left - right for left, right in zip(expected, actual))
    relative_rms = rms(differences) / max(expected_rms, 1.0e-30)
    relative_peak = max(map(abs, differences), default=0.0) / max(expected_peak, 1.0e-30)
    expected_bands = band_levels(expected)
    actual_bands = band_levels(actual)
    band_errors = {
        band: abs(expected_bands[band] - actual_bands[band]) for band in BANDS
    }
    return relative_rms, relative_peak, band_errors


def run(binary: Path) -> None:
    worst: dict[str, dict[str, tuple[float, str]]] = {}
    failures = []
    with tempfile.TemporaryDirectory(prefix="swanky-free-model-") as temporary:
        temporary = Path(temporary)
        reference = temporary / "reference"
        model = temporary / "model"
        model.mkdir()
        subprocess.run(
            [
                str(REFERENCE),
                str(reference),
                "--sample-rate",
                str(SAMPLE_RATE),
                "--silence-preroll",
                str(SAMPLE_RATE),
            ],
            check=True,
            cwd=ROOT,
        )
        for index, name in enumerate(PRESET_NAMES, start=1):
            render_model(binary, model, index, name)
            stem = slug(index, name)
            reference_seams = reference / f"{stem}-seams"
            model_seams = model / f"{stem}-seams"
            expected_names = {path.name for path in reference_seams.glob("*.wav")}
            actual_names = {path.name for path in model_seams.glob("*.wav")}
            if expected_names != actual_names:
                raise RuntimeError(f"active seam set differs for {name}")
            for filename in sorted(expected_names):
                seam = filename.removesuffix(".wav")
                relative_rms, relative_peak, bands = compare(
                    reference_seams / filename, model_seams / filename
                )
                values = {
                    "relative RMS": relative_rms,
                    "relative peak": relative_peak,
                    **{f"{band} band dB": error for band, error in bands.items()},
                }
                seam_worst = worst.setdefault(seam, {})
                for measure, value in values.items():
                    if value > seam_worst.get(measure, (-1.0, ""))[0]:
                        seam_worst[measure] = (value, name)
                if relative_rms > RELATIVE_RMS_TOLERANCE:
                    failures.append(f"{name} {seam} relative RMS {relative_rms:.6g}")
                if relative_peak > RELATIVE_PEAK_TOLERANCE:
                    failures.append(f"{name} {seam} relative peak {relative_peak:.6g}")
                for band, error in bands.items():
                    if error > BAND_LEVEL_TOLERANCE_DB:
                        failures.append(f"{name} {seam} {band} band {error:.6g} dB")

    print(
        "model comparison tolerances: "
        f"relative RMS {RELATIVE_RMS_TOLERANCE:g}, "
        f"relative peak {RELATIVE_PEAK_TOLERANCE:g}, "
        f"band level {BAND_LEVEL_TOLERANCE_DB:g} dB"
    )
    for seam, measures in sorted(worst.items()):
        rms_value, rms_case = measures["relative RMS"]
        peak_value, peak_case = measures["relative peak"]
        band_measure, (band_value, band_case) = max(
            ((measure, result) for measure, result in measures.items() if "band" in measure),
            key=lambda item: item[1][0],
        )
        print(
            f"{seam:12} RMS {rms_value:.6g} ({rms_case}); "
            f"peak {peak_value:.6g} ({peak_case}); "
            f"{band_measure} {band_value:.6g} ({band_case})"
        )
    if failures:
        raise RuntimeError("model comparison failed:\n  " + "\n  ".join(failures))


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("binary", type=Path)
    args = parser.parse_args()
    run(args.binary.resolve())


if __name__ == "__main__":
    main()
