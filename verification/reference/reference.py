#!/usr/bin/env python3
"""Build, render, and verify the released Swanky Amp 1.4.0 reference."""

from __future__ import annotations

import argparse
import hashlib
import json
import math
import os
import platform
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parent
RENDERER_SOURCE = ROOT / "renderer.cpp"
RELEASED = ROOT / "released"
PRESETS = RELEASED / "Resources" / "presets.xml"
INPUT = ROOT / "input" / "single-coil.wav"
FROZEN = ROOT / "frozen"
RATES = (44100, 48000, 96000)
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
BASELINE_COMMIT = "5c32004862e5dcce8a453e1310da926dc9712464"
ABSOLUTE_TOLERANCE = 2.0e-4
RMS_TOLERANCE = 2.0e-5
LEVEL_TOLERANCE_DB = 0.02
BAND_EDGES_HZ = (120.0, 400.0, 1200.0, 3500.0, 8000.0)


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def released_hashes() -> dict[str, str]:
    return {
        path.relative_to(ROOT).as_posix(): sha256(path)
        for path in sorted(RELEASED.rglob("*"))
        if path.is_file()
    }


def toolchain() -> tuple[list[str], dict[str, str]]:
    requested = os.environ.get("CXX")
    if requested:
        return [requested], os.environ.copy()
    if sys.platform == "darwin" and Path("/Applications/Xcode.app").exists():
        environment = os.environ.copy()
        environment["DEVELOPER_DIR"] = "/Applications/Xcode.app/Contents/Developer"
        return ["xcrun", "--sdk", "macosx", "clang++"], environment
    return ["c++"], os.environ.copy()


def build_renderer(build_dir: Path) -> tuple[Path, str]:
    compiler, environment = toolchain()
    binary = build_dir / "reference-renderer"
    subprocess.run(
        [*compiler, "-std=c++20", "-O2", str(RENDERER_SOURCE), "-o", str(binary)],
        check=True,
        cwd=ROOT,
        env=environment,
    )
    version = subprocess.run(
        [*compiler, "--version"],
        check=True,
        text=True,
        stdout=subprocess.PIPE,
        env=environment,
    ).stdout.splitlines()[0]
    return binary, version


def slug(index: int, name: str) -> str:
    return f"{index:02d}-{name.replace(' ', '-')}"


def run_renderer(binary: Path, destination: Path) -> list[dict[str, object]]:
    destination.mkdir(parents=True, exist_ok=True)
    renders: list[dict[str, object]] = []
    for index, name in enumerate(PRESET_NAMES, start=1):
        for rate in RATES:
            stem = f"{slug(index, name)}-{rate}"
            wav = destination / f"{stem}.wav"
            report = destination / f"{stem}.json"
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
                    str(rate),
                    "--output",
                    str(wav),
                    "--report",
                    str(report),
                ],
                check=True,
                cwd=ROOT,
            )
            report_data = json.loads(report.read_text())
            comparison = report_data["instrumented_comparison"]
            if comparison["bit_mismatches"] != 0:
                raise RuntimeError(f"instrumentation changed output for {stem}")
            renders.append(
                {
                    "preset": name,
                    "sample_rate": rate,
                    "wav": wav.name,
                    "wav_sha256": sha256(wav),
                    "report": report.name,
                    "report_sha256": sha256(report),
                }
            )
    return renders


def detuning(binary: Path) -> dict[str, list[float]]:
    completed = subprocess.run(
        [str(binary), "--detuning"],
        check=True,
        text=True,
        stdout=subprocess.PIPE,
        cwd=ROOT,
    )
    return json.loads(completed.stdout)


def manifest(binary: Path, compiler: str, renders: list[dict[str, object]]) -> dict:
    return {
        "schema": 1,
        "baseline": {
            "product": "Swanky Amp 1.4.0",
            "git_commit": BASELINE_COMMIT,
            "git_tag": "juce-1.4.0",
            "source_repository": "resonantdsp/SwankyAmp",
        },
        "input": {
            "path": "input/single-coil.wav",
            "sha256": sha256(INPUT),
            "sample_rate": 48000,
            "channels": 1,
            "format": "24-bit PCM",
            "samples": 68704,
            "level_before_factory_preset": "0 dB fixture precondition: a fresh session's Input Level 0.0 maps to 0 dB; factory selection preserves the live Input Level",
            "cabinet": "enabled fixture precondition: a fresh session starts enabled; factory selection preserves the live cabinet switch even though the XML carries idCabOnOff",
            "origin": "Owner-recorded DI copied from code/SwankyAmpPro/verification/calibration/single-coil.wav; no Pro DSP is used",
        },
        "render_contract": {
            "frozen_sample_rates": list(RATES),
            "block_size": 512,
            "output": "mono 32-bit IEEE-float WAV",
            "resampling": "linear interpolation from the versioned 48 kHz DI; output frame count is round(input_frames * output_rate / 48000)",
            "startup": "cold released state; raw seams retain samples 0..1023 while the rendered output applies the released 1024-sample mute",
            "post_mute": "samples from 1024 onward; this name makes no claim that nonlinear state has settled",
            "seams": {
                "triode_N": "immediately after each active Triode::process, before the shared triodeScale; inactive stage entries contain zero samples",
                "tone_stack": "immediately after ToneStack::process, before toneStackScale * preAmpScale * preAmpTarget",
                "power_amp": "immediately after grid and plate processing, before division by preAmpTarget",
                "cabinet": "immediately after Cabinet::process, before cabinetScale, powerAmpScale, and outputScale",
                "raw_output": "after all released compensation and output scaling, before the legacy startup mute",
            },
        },
        "detuning": {
            "algorithm": "released std::minstd_rand seeds 123+n with std::uniform_real_distribution<float>(-0.2, 0.2)",
            "values_on_freeze_toolchain": detuning(binary),
            "portability": "minstd_rand is specified, but uniform_real_distribution mapping is implementation-defined; these libc++ values are frozen and other standard libraries may differ",
        },
        "generation": {
            "compiler": compiler,
            "platform": platform.platform(),
            "machine": platform.machine(),
            "renderer_sha256": sha256(RENDERER_SOURCE),
        },
        "released_source_sha256": released_hashes(),
        "verification_tolerances": {
            "waveform_max_absolute": ABSOLUTE_TOLERANCE,
            "waveform_rms_error": RMS_TOLERANCE,
            "seam_level_db": LEVEL_TOLERANCE_DB,
            "note": "Same-process untouched-versus-instrumented output is always bit exact. Frozen re-renders use tolerances for compiler, libm, and C++ standard-library differences.",
        },
        "renders": renders,
    }


def read_float_wav(path: Path) -> tuple[int, tuple[float, ...]]:
    data = path.read_bytes()
    if data[:4] != b"RIFF" or data[8:12] != b"WAVE":
        raise RuntimeError(f"not WAV: {path}")
    position = 12
    fmt = None
    rate = None
    payload = None
    while position + 8 <= len(data):
        chunk = data[position : position + 4]
        size = struct.unpack_from("<I", data, position + 4)[0]
        body = data[position + 8 : position + 8 + size]
        if chunk == b"fmt ":
            fmt, channels, rate, _, _, bits = struct.unpack_from("<HHIIHH", body)
            if (fmt, channels, bits) != (3, 1, 32):
                raise RuntimeError(f"unexpected output WAV format: {path}")
        elif chunk == b"data":
            payload = body
        position += 8 + size + (size & 1)
    if payload is None or rate is None:
        raise RuntimeError(f"incomplete WAV: {path}")
    return rate, struct.unpack(f"<{len(payload) // 4}f", payload)


def measure_wav_drift(frozen: Path, actual: Path) -> tuple[float, float]:
    expected_rate, expected = read_float_wav(frozen)
    actual_rate, observed = read_float_wav(actual)
    if expected_rate != actual_rate or len(expected) != len(observed):
        raise RuntimeError(f"WAV shape differs: {actual.name}")
    if any(not math.isfinite(value) for value in expected):
        raise RuntimeError(f"frozen WAV contains non-finite audio: {frozen.name}")
    if any(not math.isfinite(value) for value in observed):
        raise RuntimeError(f"rendered WAV contains non-finite audio: {actual.name}")
    differences = [abs(a - b) for a, b in zip(expected, observed)]
    maximum = max(differences, default=0.0)
    rms = math.sqrt(sum(value * value for value in differences) / len(differences))
    return maximum, rms


def band_levels(sample_rate: int, samples: tuple[float, ...]) -> dict[str, float | None]:
    edges = tuple(min(edge, sample_rate * 0.45) for edge in BAND_EDGES_HZ)
    coefficients = tuple(math.exp(-2.0 * math.pi * edge / sample_rate) for edge in edges)
    states = [0.0] * len(edges)
    square_sums = [0.0] * (len(edges) + 1)
    for sample in samples:
        lows = []
        for index, coefficient in enumerate(coefficients):
            states[index] = (
                (1.0 - coefficient) * sample + coefficient * states[index]
            )
            lows.append(states[index])
        bands = [lows[0]]
        bands.extend(lows[index] - lows[index - 1] for index in range(1, len(lows)))
        bands.append(sample - lows[-1])
        for index, value in enumerate(bands):
            square_sums[index] += value * value
    labels = (
        "under_120",
        "120_400",
        "400_1200",
        "1200_3500",
        "3500_8000",
        "over_8000",
    )
    return {
        label: (
            None
            if square_sum == 0.0
            else 10.0 * math.log10(square_sum / len(samples))
        )
        for label, square_sum in zip(labels, square_sums)
    }


def measure_band_level_drift(frozen: Path, actual: Path) -> dict[str, float]:
    expected_rate, expected = read_float_wav(frozen)
    actual_rate, observed = read_float_wav(actual)
    if expected_rate != actual_rate or len(expected) != len(observed):
        raise RuntimeError(f"WAV shape differs: {actual.name}")
    expected_levels = band_levels(expected_rate, expected)
    observed_levels = band_levels(actual_rate, observed)
    drift: dict[str, float] = {}
    for band, expected_level in expected_levels.items():
        observed_level = observed_levels[band]
        if expected_level is None or observed_level is None:
            if expected_level != observed_level:
                raise RuntimeError(f"band silence drift for {actual.name} {band}")
            drift[band] = 0.0
        else:
            drift[band] = abs(expected_level - observed_level)
    return drift


def measure_level_drift(expected: dict, observed: dict, name: str) -> dict[str, float]:
    if observed["instrumented_comparison"]["bit_mismatches"] != 0:
        raise RuntimeError(f"instrumented renderer differs for {name}")
    drift: dict[str, float] = {}
    for seam, expected_stats in expected["seams"].items():
        observed_stats = observed["seams"][seam]
        maximum = 0.0
        for window in ("startup", "post_mute"):
            if expected_stats[window]["samples"] != observed_stats[window]["samples"]:
                raise RuntimeError(f"seam sample count drift for {name} {seam}")
            for measure in ("rms_dbfs", "peak_dbfs"):
                left = expected_stats[window][measure]
                right = observed_stats[window][measure]
                if left is None or right is None:
                    if left != right:
                        raise RuntimeError(f"seam silence drift for {name} {seam}")
                else:
                    maximum = max(maximum, abs(left - right))
        drift[seam] = maximum
    return drift


def render(destination: Path, replace_frozen: bool = False) -> None:
    if destination == FROZEN.resolve() and not replace_frozen:
        raise RuntimeError(
            "refusing to replace the versioned baseline without --replace-frozen"
        )
    with tempfile.TemporaryDirectory(prefix="swanky-free-reference-build-") as temp:
        binary, compiler = build_renderer(Path(temp))
        if destination == FROZEN.resolve() and (
            sys.platform != "darwin"
            or platform.machine() != "arm64"
            or "Apple clang" not in compiler
        ):
            raise RuntimeError(
                "the frozen baseline must be generated on canonical macOS arm64/libc++"
            )
        renders = run_renderer(binary, destination)
        data = manifest(binary, compiler, renders)
        (destination / "manifest.json").write_text(
            json.dumps(data, indent=2, sort_keys=True) + "\n"
        )
    print(f"rendered {len(renders)} references to {destination}")


def check() -> None:
    frozen_manifest = json.loads((FROZEN / "manifest.json").read_text())
    if frozen_manifest["baseline"]["git_commit"] != BASELINE_COMMIT:
        raise RuntimeError("frozen baseline commit is not the released commit")
    if frozen_manifest["input"]["sha256"] != sha256(INPUT):
        raise RuntimeError("versioned DI hash differs from frozen provenance")
    if frozen_manifest["released_source_sha256"] != released_hashes():
        raise RuntimeError("released source extraction differs from provenance")
    if frozen_manifest["generation"]["renderer_sha256"] != sha256(RENDERER_SOURCE):
        raise RuntimeError("renderer source differs from the source that froze the baseline")

    frozen_by_key = {
        (entry["preset"], entry["sample_rate"]): entry
        for entry in frozen_manifest["renders"]
    }
    expected_keys = {
        (preset, rate) for preset in PRESET_NAMES for rate in RATES
    }
    if set(frozen_by_key) != expected_keys or len(frozen_manifest["renders"]) != 30:
        raise RuntimeError("frozen manifest does not contain the required 10 x 3 corpus")
    for entry in frozen_manifest["renders"]:
        frozen_wav = FROZEN / entry["wav"]
        frozen_report = FROZEN / entry["report"]
        if sha256(frozen_wav) != entry["wav_sha256"]:
            raise RuntimeError(f"frozen WAV digest differs: {entry['wav']}")
        if sha256(frozen_report) != entry["report_sha256"]:
            raise RuntimeError(f"frozen report digest differs: {entry['report']}")

    with tempfile.TemporaryDirectory(prefix="swanky-free-reference-check-") as temp:
        temp_path = Path(temp)
        binary, compiler = build_renderer(temp_path)
        actual_dir = temp_path / "renders"
        actual_renders = run_renderer(binary, actual_dir)
        worst_max = 0.0
        worst_rms = 0.0
        worst_level = 0.0
        worst_band = 0.0
        exact = 0
        violations: list[str] = []
        for actual in actual_renders:
            key = (actual["preset"], actual["sample_rate"])
            expected = frozen_by_key[key]
            frozen_wav = FROZEN / expected["wav"]
            actual_wav = actual_dir / actual["wav"]
            maximum, rms = measure_wav_drift(frozen_wav, actual_wav)
            worst_max = max(worst_max, maximum)
            worst_rms = max(worst_rms, rms)
            if sha256(frozen_wav) == sha256(actual_wav):
                exact += 1
            level_drift = measure_level_drift(
                json.loads((FROZEN / expected["report"]).read_text()),
                json.loads((actual_dir / actual["report"]).read_text()),
                actual["wav"],
            )
            case_level = max(level_drift.values(), default=0.0)
            worst_level = max(worst_level, case_level)
            band_drift = measure_band_level_drift(frozen_wav, actual_wav)
            case_band = max(band_drift.values(), default=0.0)
            worst_band = max(worst_band, case_band)
            seam_summary = " ".join(
                f"{seam}={value:.6g}dB"
                for seam, value in sorted(level_drift.items())
            )
            print(
                f"reference-case: {actual['wav']} max={maximum:.6g} "
                f"rms={rms:.6g} seam-max={case_level:.6g}dB "
                f"band-max={case_band:.6g}dB {seam_summary} bands="
                + ",".join(
                    f"{band}:{value:.6g}dB"
                    for band, value in band_drift.items()
                )
            )
            if (
                maximum > ABSOLUTE_TOLERANCE
                or rms > RMS_TOLERANCE
                or case_level > LEVEL_TOLERANCE_DB
            ):
                violations.append(actual["wav"])

        current_detuning = detuning(binary)
        frozen_detuning = frozen_manifest["detuning"]["values_on_freeze_toolchain"]
        detuning_status = "exact" if current_detuning == frozen_detuning else "different standard-library mapping"
        detuning_delta = max(
            abs(current - frozen)
            for family, values in frozen_detuning.items()
            for current, frozen in zip(current_detuning[family], values)
        )
        print(
            f"reference: 30 renders compared; {exact}/30 byte exact; "
            f"worst max error {worst_max:.3g}, rms error {worst_rms:.3g}; "
            f"worst seam level {worst_level:.3g} dB, band level "
            f"{worst_band:.3g} dB; detuning {detuning_status} "
            f"(max delta {detuning_delta:.3g}); compiler {compiler}"
        )
        if current_detuning != frozen_detuning:
            print("reference-detuning-current: " + json.dumps(current_detuning, sort_keys=True))
        if violations:
            raise RuntimeError(
                f"{len(violations)}/30 renders exceeded portability tolerances: "
                + ", ".join(violations)
            )


def main() -> None:
    parser = argparse.ArgumentParser()
    subparsers = parser.add_subparsers(dest="command", required=True)
    render_parser = subparsers.add_parser("render")
    render_parser.add_argument("destination", nargs="?", type=Path, default=ROOT / "generated")
    render_parser.add_argument("--replace-frozen", action="store_true")
    subparsers.add_parser("check")
    args = parser.parse_args()
    if args.command == "render":
        render(args.destination.resolve(), args.replace_frozen)
    else:
        check()


if __name__ == "__main__":
    try:
        main()
    except (RuntimeError, subprocess.CalledProcessError) as error:
        print(f"reference: {error}", file=sys.stderr)
        raise SystemExit(1) from None
