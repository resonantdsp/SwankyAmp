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


def toml_text(path: Path, table: str, key: str) -> str:
    current = ""
    for line in path.read_text(encoding="utf-8").splitlines():
        stripped = line.strip()
        if stripped.startswith("["):
            current = stripped
            continue
        if current != table:
            continue
        match = re.fullmatch(rf'{re.escape(key)}\s*=\s*"([^"]+)"\s*', stripped)
        if match:
            return match.group(1)
    raise ValueError(f"{path.name} {table} has no string {key}")


def git(*args: str, root: Path = ROOT) -> str:
    return subprocess.run(
        ["git", *args], cwd=root, check=True, text=True, capture_output=True
    ).stdout.strip()


def source_metadata(root: Path = ROOT) -> dict:
    cargo = root / "Cargo.toml"
    truce = root / "truce.toml"
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


def version(root: Path = ROOT) -> str:
    return toml_text(root / "Cargo.toml", "[package]", "version")


def tag_version(tag: str, kind: str) -> str:
    pattern = CANDIDATE_TAG if kind == "candidate" else STABLE_TAG
    match = pattern.fullmatch(tag)
    if not match:
        expected = "vX.Y.Z-rc.N" if kind == "candidate" else "vX.Y.Z"
        raise ValueError(f"'{tag}' is not a {kind} tag; expected {expected}")
    return match.group("version")


def validate_source_tag(tag: str, kind: str, root: Path = ROOT) -> str:
    tagged_version = tag_version(tag, kind)
    crate_version = version(root)
    if tagged_version != crate_version:
        raise ValueError(
            f"{tag} names {tagged_version}, but Cargo.toml is {crate_version}"
        )
    changelog = (root / "CHANGELOG.md").read_text(encoding="utf-8")
    if not re.search(rf"^## {re.escape(crate_version)}(?:\s|$)", changelog, re.MULTILINE):
        raise ValueError(f"CHANGELOG.md has no '## {crate_version}' section")
    return crate_version


def artifact_kind(name: str) -> tuple[str, str, str] | None:
    for suffix, details in KINDS.items():
        if name.endswith(suffix):
            return details
    return None


def artifacts(directory: Path, release_version: str) -> list[dict]:
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
    actual = [item["kind"] for item in found]
    mandatory = {"macos-pkg", "windows-exe"}
    if not mandatory.issubset(actual) or any(actual.count(kind) != 1 for kind in mandatory):
        raise ValueError("candidate needs exactly one macOS .pkg and Windows .exe")
    if actual.count("linux-tarball") > 1:
        raise ValueError("candidate contains more than one Linux bundle")
    return found


def make_record(label: str, directory: Path, root: Path = ROOT) -> dict:
    release_version = (
        tag_version(label, "candidate")
        if CANDIDATE_TAG.fullmatch(label)
        else version(root)
    )
    if not CANDIDATE_TAG.fullmatch(label) and not REHEARSAL.fullmatch(label):
        raise ValueError("record label must be a candidate tag or commit hash")
    artwork = root / "assets" / "artwork.pack"
    if not artwork.is_file():
        raise ValueError("assets/artwork.pack is missing; merge and validate the public artwork first")
    toolchain = toml_text(root / "rust-toolchain.toml", "[toolchain]", "channel")
    return {
        "schema": 1,
        "candidate": label,
        "commit": git("rev-parse", "HEAD", root=root),
        "version": release_version,
        "toolchain": toolchain,
        "cargo_truce": "6.3.0+resonantdsp.1",
        "cargo_lock_sha256": sha256(root / "Cargo.lock"),
        "artwork_sha256": sha256(artwork),
        "product": source_metadata(root),
        "artifacts": artifacts(directory, release_version),
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
        "version": stable_version,
        "toolchain": toml_text(root / "rust-toolchain.toml", "[toolchain]", "channel"),
        "cargo_truce": "6.3.0+resonantdsp.1",
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
    actual = artifacts(directory, stable_version)
    if recorded != actual:
        raise ValueError("candidate artifacts do not match their recorded bytes")
    checksum = directory / "release-record.sha256"
    checksum_parts = checksum.read_text(encoding="utf-8").split() if checksum.is_file() else []
    if not checksum_parts or checksum_parts[0] != expected_record_sha256:
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
    args = parser.parse_args(argv)
    try:
        if args.command == "check-tag":
            release_version = validate_source_tag(args.tag, args.kind)
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
        else:
            print(version())
    except (KeyError, OSError, ValueError, subprocess.CalledProcessError, json.JSONDecodeError) as error:
        print(str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
