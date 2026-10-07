#!/usr/bin/env python3
"""Identify, record, and verify immutable Swanky Amp 2 release candidates."""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
CANDIDATE_TAG = re.compile(r"^v(?P<version>\d+\.\d+\.\d+)-rc\.(?P<number>[1-9]\d*)$")
STABLE_TAG = re.compile(r"^v(?P<version>\d+\.\d+\.\d+)$")
REHEARSAL = re.compile(r"^[0-9a-f]{7,40}$")
KINDS = {
    ".pkg": ("macos-pkg", "macOS", "universal"),
    ".exe": ("windows-exe", "Windows", "x86_64"),
    ".tar.gz": ("linux-tarball", "Linux", "x86_64"),
}


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as source:
        for block in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def git(*args: str, root: Path = ROOT) -> str:
    return subprocess.run(
        ["git", *args], cwd=root, check=True, capture_output=True, encoding="utf-8"
    ).stdout.strip()


def source(root: Path, name: str, commit: str | None = None) -> str:
    """A source file from the working tree, or as committed at `commit`."""
    if commit is None:
        return (root / name).read_text(encoding="utf-8")
    return git("show", f"{commit}:{name}", root=root)


def toml_value(text: str, table: str, key: str, value: str) -> str:
    current = ""
    for line in text.splitlines():
        stripped = line.strip()
        if stripped.startswith("["):
            current = stripped
            continue
        if current != table:
            continue
        match = re.fullmatch(rf"{re.escape(key)}\s*=\s*{value}", stripped)
        if match:
            return match.group(1)
    raise ValueError(f"{table} has no {key}")


def toml_text(text: str, table: str, key: str) -> str:
    return toml_value(text, table, key, r'"([^"]+)"')


def build_number(root: Path = ROOT) -> int:
    """The number build.rs bakes in: the commits behind HEAD."""
    return int(git("rev-list", "--count", "HEAD", root=root))


def cargo_truce_version(root: Path = ROOT) -> str:
    """The version of the vendored cargo-truce the candidate was packaged with."""
    return toml_text(source(root, "vendor/cargo-truce/Cargo.toml"), "[package]", "version")


def ships_linux(root: Path = ROOT) -> bool:
    text = source(root, "Cargo.toml")
    return toml_value(text, "[package.metadata.release]", "linux", r"(true|false)") == "true"


def source_metadata(root: Path = ROOT) -> dict:
    cargo = source(root, "Cargo.toml")
    truce = source(root, "truce.toml")
    vendor_id = toml_text(truce, "[vendor]", "id")
    plugin_id = toml_text(truce, "[[plugin]]", "bundle_id")
    return {
        "website_product_id": "SwankyAmp",
        "plugin_name": toml_text(truce, "[[plugin]]", "name"),
        "plugin_identity": "SwankyAmp2",
        "bundle_id": f"{vendor_id}.{plugin_id}",
        "fourcc": toml_text(truce, "[[plugin]]", "fourcc"),
        "crate": toml_text(cargo, "[package]", "name"),
        "repository": toml_text(cargo, "[package]", "repository"),
        "license": toml_text(cargo, "[package]", "license"),
    }


def version(root: Path = ROOT, commit: str | None = None) -> str:
    return toml_text(source(root, "Cargo.toml", commit), "[package]", "version")


def toolchain(root: Path) -> str:
    return toml_text(source(root, "rust-toolchain.toml"), "[toolchain]", "channel")


def tag_version(tag: str, kind: str) -> str:
    pattern = CANDIDATE_TAG if kind == "candidate" else STABLE_TAG
    match = pattern.fullmatch(tag)
    if not match:
        expected = "vX.Y.Z-rc.N" if kind == "candidate" else "vX.Y.Z"
        raise ValueError(f"'{tag}' is not a {kind} tag; expected {expected}")
    return match.group("version")


def validate_source_tag(
    tag: str, kind: str, root: Path = ROOT, commit: str | None = None
) -> str:
    tagged_version = tag_version(tag, kind)
    crate_version = version(root, commit)
    if tagged_version != crate_version:
        raise ValueError(
            f"{tag} names {tagged_version}, but Cargo.toml is {crate_version}"
        )
    changelog = source(root, "CHANGELOG.md", commit)
    heading = re.search(
        rf"^## {re.escape(crate_version)}(?:[ \t](.*))?$", changelog, re.MULTILINE
    )
    if not heading:
        raise ValueError(f"CHANGELOG.md has no '## {crate_version}' section")
    # The tagged source is public and permanent, so its changelog would say
    # "in development" for a released version forever.
    if kind == "stable" and not re.search(r"\b\d{4}-\d{2}-\d{2}\b", heading.group(1) or ""):
        raise ValueError(f"CHANGELOG.md's '## {crate_version}' heading has no release date")
    return crate_version


def artifact_kind(name: str) -> tuple[str, str, str] | None:
    for suffix, details in KINDS.items():
        if name.endswith(suffix):
            return details
    return None


def artifacts(directory: Path, release_version: str, root: Path = ROOT) -> list[dict]:
    found = []
    for path in sorted(directory.iterdir()):
        details = artifact_kind(path.name)
        if details is None:
            continue
        if not path.is_file() or path.is_symlink():
            raise ValueError(f"release artifact is not a regular file: {path.name}")
        if not path.name.startswith(f"swanky-amp-{release_version}-"):
            raise ValueError(f"unexpected artifact name for {release_version}: {path.name}")
        kind, platform, architecture = details
        found.append(
            {
                "name": path.name,
                "kind": kind,
                "platform": platform,
                "architecture": architecture,
                "bytes": path.stat().st_size,
                "sha256": sha256(path),
            }
        )
    declared = ["macos-pkg", "windows-exe"] + (["linux-tarball"] if ships_linux(root) else [])
    if sorted(item["kind"] for item in found) != sorted(declared):
        raise ValueError(f"candidate needs exactly one of each declared download: {', '.join(declared)}")
    return found


def make_record(label: str, directory: Path, root: Path = ROOT) -> dict:
    release_version = (
        tag_version(label, "candidate")
        if CANDIDATE_TAG.fullmatch(label)
        else version(root)
    )
    if not CANDIDATE_TAG.fullmatch(label) and not REHEARSAL.fullmatch(label):
        raise ValueError("record label must be a candidate tag or commit hash")
    build = build_number(root)
    if build < 100:
        raise ValueError(f"build number {build} is too low; check out the full history")
    artwork = root / "assets" / "artwork.pack"
    if not artwork.is_file():
        raise ValueError("assets/artwork.pack is missing; merge and validate the public artwork first")
    return {
        "schema": 1,
        "candidate": label,
        "commit": git("rev-parse", "HEAD", root=root),
        "build": build,
        "version": release_version,
        "toolchain": toolchain(root),
        "cargo_truce": cargo_truce_version(root),
        "cargo_lock_sha256": sha256(root / "Cargo.lock"),
        "artwork_sha256": sha256(artwork),
        "product": source_metadata(root),
        "artifacts": artifacts(directory, release_version, root),
    }


def verify_candidate(
    candidate_tag: str,
    stable_tag: str,
    expected_record_sha256: str,
    directory: Path,
    root: Path = ROOT,
) -> dict:
    candidate_version = tag_version(candidate_tag, "candidate")
    stable_version = validate_source_tag(stable_tag, "stable", root)
    if candidate_version != stable_version:
        raise ValueError("candidate and stable tags name different versions")
    if not re.fullmatch(r"[0-9a-f]{64}", expected_record_sha256):
        raise ValueError("expected record SHA-256 must be 64 lowercase hexadecimal characters")

    candidate_commit = git("rev-list", "-n", "1", candidate_tag, root=root)
    stable_commit = git("rev-list", "-n", "1", stable_tag, root=root)
    head = git("rev-parse", "HEAD", root=root)
    if candidate_commit != stable_commit or stable_commit != head:
        raise ValueError("candidate tag, stable tag, and checked-out commit must be identical")

    record_path = directory / "release-record.json"
    if sha256(record_path) != expected_record_sha256:
        raise ValueError("release-record.json does not match the accepted SHA-256")
    record = json.loads(record_path.read_text(encoding="utf-8"))
    if record.get("schema") != 1:
        raise ValueError("unsupported release-record schema")
    expected_fields = {
        "candidate": candidate_tag,
        "commit": candidate_commit,
        "build": build_number(root),
        "version": stable_version,
        "toolchain": toolchain(root),
        "cargo_truce": cargo_truce_version(root),
        "cargo_lock_sha256": sha256(root / "Cargo.lock"),
        "artwork_sha256": sha256(root / "assets" / "artwork.pack"),
        "product": source_metadata(root),
    }
    for field, expected in expected_fields.items():
        if record.get(field) != expected:
            raise ValueError(f"candidate record {field} does not match the stable tag")

    recorded = record.get("artifacts")
    if not isinstance(recorded, list):
        raise ValueError("candidate record has no artifact list")
    actual = artifacts(directory, stable_version, root)
    if recorded != actual:
        raise ValueError("candidate artifacts do not match their recorded bytes")
    checksum = directory / "release-record.sha256"
    checksum_parts = checksum.read_text(encoding="utf-8").split() if checksum.is_file() else []
    # Names the record beside it, so `sha256sum -c` checks it in place.
    if checksum_parts != [expected_record_sha256, "release-record.json"]:
        raise ValueError("candidate checksum file does not name the accepted release record")
    allowed = {
        "release-record.json",
        "release-record.sha256",
        *(artifact["name"] for artifact in recorded),
    }
    present = {path.name for path in directory.iterdir()}
    if present != allowed or any(not path.is_file() or path.is_symlink() for path in directory.iterdir()):
        raise ValueError("candidate draft contains files outside the recorded release set")
    return record


def verify_stable_assets(candidate: Path, published: Path) -> None:
    record = json.loads((candidate / "release-record.json").read_text(encoding="utf-8"))
    expected = {
        "release-record.json",
        "release-record.sha256",
        "qualification.md",
        *(artifact["name"] for artifact in record.get("artifacts", [])),
    }
    present = {path.name for path in published.iterdir()}
    if present != expected:
        raise ValueError("existing stable release has a different asset inventory")
    for name in sorted(expected):
        source = candidate / name
        destination = published / name
        if (
            not source.is_file()
            or source.is_symlink()
            or not destination.is_file()
            or destination.is_symlink()
            or sha256(source) != sha256(destination)
        ):
            raise ValueError(f"existing stable release asset differs: {name}")


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    commands = parser.add_subparsers(dest="command", required=True)
    check = commands.add_parser("check-tag")
    check.add_argument("kind", choices=("candidate", "stable"))
    check.add_argument("tag")
    check.add_argument("--commit", help="check the files committed here, not the working tree")
    record = commands.add_parser("record")
    record.add_argument("label")
    record.add_argument("directory", type=Path)
    verify = commands.add_parser("verify-candidate")
    verify.add_argument("candidate_tag")
    verify.add_argument("stable_tag")
    verify.add_argument("record_sha256")
    verify.add_argument("directory", type=Path)
    stable = commands.add_parser("verify-stable-assets")
    stable.add_argument("candidate", type=Path)
    stable.add_argument("published", type=Path)
    commands.add_parser("version")
    commands.add_parser("ships-linux")
    args = parser.parse_args(argv)
    try:
        if args.command == "check-tag":
            release_version = validate_source_tag(args.tag, args.kind, commit=args.commit)
            print(f"{args.tag} agrees with Cargo.toml and CHANGELOG.md at {release_version}")
        elif args.command == "record":
            print(json.dumps(make_record(args.label, args.directory), indent=2))
        elif args.command == "verify-candidate":
            result = verify_candidate(
                args.candidate_tag,
                args.stable_tag,
                args.record_sha256,
                args.directory,
            )
            print(
                f"{args.candidate_tag} supplies {len(result['artifacts'])} recorded artifacts "
                f"for {args.stable_tag} at {result['commit']}"
            )
        elif args.command == "verify-stable-assets":
            verify_stable_assets(args.candidate, args.published)
            print("Existing stable release assets exactly match the accepted candidate")
        elif args.command == "ships-linux":
            print("true" if ships_linux() else "false")
        else:
            print(version())
    except (KeyError, OSError, ValueError, subprocess.CalledProcessError, json.JSONDecodeError) as error:
        print(str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
