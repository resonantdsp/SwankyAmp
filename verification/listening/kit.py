#!/usr/bin/env python3
"""Render a blind listening kit: every factory preset as released in 1.4.0
against the version 2 shipping path with the refitted bank and, optionally,
that bank with High moved."""

from __future__ import annotations

import argparse
import json
import math
import random
import struct
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "verification" / "reference"))
import reference  # noqa: E402

RELEASED_BANK = ROOT / "verification" / "reference" / "released" / "Resources" / "presets.xml"
VERSION_2_BANK = ROOT / "presets" / "factory-2.0.xml"
REFIT = ROOT / "verification" / "tone-stack" / "refit.json"
SINGLE_COIL = ROOT / "verification" / "reference" / "input" / "single-coil.wav"
SAMPLE_RATE = 44_100
# Both sides run a settled amplifier, as a player hears it mid-session, and
# keep a tail so the last note's decay is heard in full.
PREROLL_SECONDS = 1
TAIL_SECONDS = 0.5
# Extra input silence past the kept tail, so the oversampler's latency never
# runs a render short of its aligned length.
LATENCY_SLACK_SECONDS = 0.1
# Just under -1 dBFS so 24-bit rounding cannot land a peak on it.
PEAK_CEILING_DB = -1.1
SHUFFLE_SEED = 20260923
CONTROLS = (
    ("low", "Low"),
    ("mid", "Mid"),
    ("high", "High"),
    ("power_drive", "Power Drive"),
)


def read_pcm24(path: Path) -> tuple[int, list[float]]:
    data = path.read_bytes()
    position, rate, samples = 12, None, None
    while position + 8 <= len(data):
        kind = data[position : position + 4]
        size = struct.unpack_from("<I", data, position + 4)[0]
        body = data[position + 8 : position + 8 + size]
        if kind == b"fmt ":
            encoding, channels, rate, _, _, bits = struct.unpack_from("<HHIIHH", body)
            if (encoding, channels, bits) != (1, 1, 24):
                raise RuntimeError(f"{path} is not mono 24-bit PCM")
        elif kind == b"data":
            samples = [
                int.from_bytes(body[i : i + 3], "little", signed=True) / 8_388_608
                for i in range(0, len(body) - 2, 3)
            ]
        position += 8 + size + (size & 1)
    if rate is None or samples is None:
        raise RuntimeError(f"incomplete WAV: {path}")
    return rate, samples


def write_pcm24(path: Path, rate: int, samples: list[float]) -> None:
    body = bytearray()
    for sample in samples:
        value = max(-8_388_608, min(8_388_607, round(sample * 8_388_608)))
        body += value.to_bytes(3, "little", signed=True)
    if len(body) & 1:
        body += b"\0"
    header = struct.pack(
        "<4sI4s4sIHHIIHH4sI",
        b"RIFF", 36 + len(body), b"WAVE", b"fmt ", 16, 1, 1, rate, rate * 3, 3, 24,
        b"data", len(samples) * 3,
    )
    path.write_bytes(header + bytes(body))


def rms(samples: list[float]) -> float:
    return math.sqrt(sum(x * x for x in samples) / len(samples))


def db(value: float) -> float:
    return 20 * math.log10(value)


def padded_input(source: Path, destination: Path) -> int:
    rate, samples = read_pcm24(source)
    tail = int((TAIL_SECONDS + LATENCY_SLACK_SECONDS) * rate)
    padded = [0.0] * (PREROLL_SECONDS * rate) + samples + [0.0] * tail
    write_pcm24(destination, rate, padded)
    return round((len(samples) + TAIL_SECONDS * rate) * SAMPLE_RATE / rate)


def aligned(render: Path, latency: int, frames: int) -> list[float]:
    _, samples = read_float(render)
    start = PREROLL_SECONDS * SAMPLE_RATE + latency
    clip = samples[start : start + frames]
    if len(clip) != frames:
        raise RuntimeError(f"{render} is shorter than its input")
    return clip


def read_float(path: Path) -> tuple[int, list[float]]:
    data = path.read_bytes()
    position = 12
    while position + 8 <= len(data):
        kind = data[position : position + 4]
        size = struct.unpack_from("<I", data, position + 4)[0]
        if kind == b"data":
            body = data[position + 8 : position + 8 + size]
            return SAMPLE_RATE, list(struct.unpack(f"<{len(body) // 4}f", body))
        position += 8 + size + (size & 1)
    raise RuntimeError(f"no data in {path}")


def released(renderer: Path, work: Path, input_path: Path, preset: str) -> Path:
    output = work / "released.wav"
    subprocess.run(
        [
            str(renderer), "--input", str(input_path), "--presets", str(RELEASED_BANK),
            "--preset", preset, "--sample-rate", str(SAMPLE_RATE),
            "--output", str(output), "--report", str(work / "released.json"),
        ],
        check=True, cwd=ROOT, stdout=subprocess.DEVNULL,
    )
    return output


def version_2(
    render_model: Path, work: Path, input_path: Path, preset: str, high: float | None
) -> tuple[Path, int]:
    output, report = work / "version-2.wav", work / "version-2.json"
    command = [
        str(render_model), "--model", "shipping", "--oversampling", "auto",
        "--input", str(input_path), "--presets", str(VERSION_2_BANK),
        "--preset", preset, "--sample-rate", str(SAMPLE_RATE),
        "--output", str(output), "--report", str(report),
    ]
    if high is not None:
        command += ["--high", repr(high)]
    subprocess.run(command, check=True, cwd=ROOT)
    return output, json.loads(report.read_text())["latency_samples"]


def moved_controls(refit: dict) -> str:
    moves = [
        f"{label} {refit['original'][key]:+.2f}→{refit['refit'][key]:+.2f}"
        for key, label in CONTROLS
        if refit["original"][key] != refit["refit"][key]
    ]
    return ", ".join(moves) or "none"


def high_variants(refit_tone: Path, steps: str) -> dict[str, list[dict]]:
    """Each preset's variants with their High and tone-stack residuals, as the
    refit measures them against the released mapping."""
    result = subprocess.run(
        [
            str(refit_tone), "--presets", str(RELEASED_BANK),
            "--factory", str(VERSION_2_BANK), "--high-steps", steps,
        ],
        check=True, cwd=ROOT, text=True, stdout=subprocess.PIPE,
    )
    return {preset["name"]: preset["variants"] for preset in json.loads(result.stdout)}


def variant_label(step: str) -> str:
    if step == "as-is":
        return "version 2"
    if step == "orig":
        return "original High"
    return f"High {float(step):+.1f}"


def build(
    render_model: Path, output: Path, inputs: list[str], refit_tone: Path | None, steps: str
) -> None:
    output.mkdir(parents=True, exist_ok=True)
    refits = {preset["name"]: preset for preset in json.loads(REFIT.read_text())["presets"]}
    variants = high_variants(refit_tone, steps) if steps else None
    shuffle = random.Random(SHUFFLE_SEED)
    rows = []
    with tempfile.TemporaryDirectory(prefix="swanky-listening-") as temporary:
        work = Path(temporary)
        renderer, _, _ = reference.build_renderer(work)
        pluck = work / "pluck-source.wav"
        subprocess.run([str(render_model), "--write-pluck", str(pluck)], check=True)
        sources = {"single-coil": SINGLE_COIL, "pluck": pluck}
        padded = {
            name: (work / f"{name}.wav", padded_input(sources[name], work / f"{name}.wav"))
            for name in inputs
        }
        for index, preset in enumerate(reference.PRESET_NAMES, start=1):
            sides = (
                [(variant_label(v["variant"]), v["high"], v) for v in variants[preset]]
                if variants
                else [("version 2", None, None)]
            )
            for input_name, (input_path, frames) in padded.items():
                reference_audio = aligned(released(renderer, work, input_path, preset), 0, frames)
                target = rms(reference_audio)
                group = [{"side": "1.4.0", "audio": reference_audio, "trim_db": 0.0}]
                for label, high, measured in sides:
                    path, latency = version_2(render_model, work, input_path, preset, high)
                    audio = aligned(path, latency, frames)
                    trim_db = db(target / rms(audio))
                    group.append(
                        {
                            "side": label, "high": high, "measured": measured,
                            "trim_db": trim_db,
                            "audio": [x * 10 ** (trim_db / 20) for x in audio],
                        }
                    )
                peak = max(max(map(abs, side["audio"])) for side in group)
                headroom_db = min(0.0, PEAK_CEILING_DB - db(peak))
                gain = 10 ** (headroom_db / 20)
                for side in group:
                    side["audio"] = [x * gain for x in side["audio"]]
                    if not all(math.isfinite(x) for x in side["audio"]):
                        raise RuntimeError(f"{preset} {input_name} {side['side']}: non-finite audio")
                for first, second in zip(group, group[1:]):
                    if first["audio"] == second["audio"]:
                        raise RuntimeError(
                            f"{preset} {input_name}: {first['side']} and {second['side']} are identical"
                        )
                letters = list("XY" if len(group) == 2 else "ABCDEFGHIJ"[: len(group)])
                shuffle.shuffle(letters)
                stem = f"{index:02d}-{preset.replace(' ', '-')}-{input_name}"
                for letter, side in zip(letters, group):
                    write_pcm24(output / f"{stem}-{letter}.wav", SAMPLE_RATE, side.pop("audio"))
                    side["letter"] = letter
                rows.append(
                    {
                        "stem": stem, "preset": preset, "input": input_name,
                        "sides": group, "headroom_db": headroom_db,
                        "moved": moved_controls(refits[preset]),
                    }
                )
    write_key(output / "KEY.txt", rows)
    if variants:
        write_groups(output / "groups.md", rows)
    else:
        write_table(output / "pairs.md", rows)


def write_key(path: Path, rows: list[dict]) -> None:
    lines = [
        "Swanky Amp 1.4.0 against version 2: answer key. Read after listening.",
        "",
        "Trim is the gain applied to each version 2 file to match the 1.4.0 RMS",
        "over the whole clip; it is the residual output level difference.",
        "Headroom is a common gain applied to a whole group when any file",
        f"peaked above {PEAK_CEILING_DB:g} dBFS.",
        "",
    ]
    for row in rows:
        lines.append(f"{row['stem']}  headroom {row['headroom_db']:+.2f} dB")
        for side in sorted(row["sides"], key=lambda side: side["letter"]):
            lines.append(f"  {side['letter']}  {side['side']:14} trim {side['trim_db']:+.2f} dB")
    path.write_text("\n".join(lines) + "\n")


def write_table(path: Path, rows: list[dict]) -> None:
    lines = [
        "# Listening pairs, unblinded",
        "",
        "Side A is Swanky Amp 1.4.0 from the C++ reference renderer with the",
        "released bank; side B is the version 2 shipping path with Auto",
        "oversampling and `presets/factory-2.0.xml`, both at 44.1 kHz from a",
        "settled amplifier. The level residual is the version 2 output level",
        "relative to 1.4.0 (the negative of the trim applied to it).",
        "",
        "| Preset | Input | Refit moved | Level residual dB | Headroom dB |",
        "|---|---|---|---|---|",
    ]
    for row in rows:
        lines.append(
            f"| {row['preset']} | {row['input']} | {row['moved']} | "
            f"{-row['sides'][1]['trim_db']:+.2f} | {row['headroom_db']:+.2f} |"
        )
    path.write_text("\n".join(lines) + "\n")


def write_groups(path: Path, rows: list[dict]) -> None:
    lines = [
        "# Listening groups, unblinded",
        "",
        "Each group is Swanky Amp 1.4.0 from the C++ reference renderer with the",
        "released bank, then the version 2 shipping path with Auto oversampling",
        "and `presets/factory-2.0.xml` as refitted and with only High changed,",
        "all at 44.1 kHz from a settled amplifier. The level residual is each",
        "variant's output level relative to 1.4.0 (the negative of its trim).",
        "Seam shape and level are the refit's tone-stack residuals against the",
        "preset on the released mapping, measured on the pluck at 48 kHz.",
        "",
        "| Preset | Input | Variant | Letter | High | Seam shape dB RMS | Seam level dB | Level residual dB |",
        "|---|---|---|---|---|---|---|---|",
    ]
    for row in rows:
        for side in row["sides"]:
            if side["side"] == "1.4.0":
                lines.append(
                    f"| {row['preset']} | {row['input']} | 1.4.0 | {side['letter']} | "
                    f"{refit_original_high(row):+.2f} | | | |"
                )
                continue
            seam = side["measured"]["measurement"]["tone_stack"]
            lines.append(
                f"| {row['preset']} | {row['input']} | {side['side']} | {side['letter']} | "
                f"{side['high']:+.2f} | {seam['shape_db']:.2f} | {seam['level_db']:+.2f} | "
                f"{-side['trim_db']:+.2f} |"
            )
    lines += ["", f"Headroom applied: " + (", ".join(
        f"{row['stem']} {row['headroom_db']:+.2f} dB" for row in rows if row["headroom_db"]
    ) or "none") + "."]
    path.write_text("\n".join(lines) + "\n")


def refit_original_high(row: dict) -> float:
    return next(
        side["high"] for side in row["sides"] if side["side"] == "original High"
    )


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("render_model", type=Path)
    parser.add_argument("output", type=Path)
    parser.add_argument(
        "--inputs", default="single-coil,pluck",
        help="comma-separated inputs from single-coil and pluck",
    )
    parser.add_argument(
        "--high-steps", default="",
        help="comma-separated changes to the refitted High, or orig for the 1.4.0 value",
    )
    parser.add_argument("--refit-tone", type=Path, help="needed with --high-steps")
    arguments = parser.parse_args()
    inputs = [name.strip() for name in arguments.inputs.split(",") if name.strip()]
    if not inputs or any(name not in ("single-coil", "pluck") for name in inputs):
        parser.error("--inputs takes single-coil and/or pluck")
    if arguments.high_steps and arguments.refit_tone is None:
        parser.error("--high-steps needs --refit-tone")
    build(
        arguments.render_model.resolve(), arguments.output.resolve(), inputs,
        arguments.refit_tone.resolve() if arguments.refit_tone else None,
        arguments.high_steps,
    )


if __name__ == "__main__":
    main()
