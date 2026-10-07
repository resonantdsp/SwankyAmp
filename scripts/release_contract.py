#!/usr/bin/env python3
"""The release contract: check a tag, record a candidate, fetch and verify it.

The same file in Swanky Amp and Swanky Amp Pro apart from the product block.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
import shutil
import subprocess
import sys
import urllib.request
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]

# The product block: everything in it differs between the two products.
WEBSITE_PRODUCT_ID = "SwankyAmp"
ARTIFACT_PREFIX = "swanky-amp"


def asset_field(root: Path) -> tuple[str, str]:
    """The record field naming the artwork the binaries embed."""
    return "artwork_sha256", sha256(root / "assets" / "artwork.pack")


def declared_kinds(root: Path) -> list[str]:
    """`[package.metadata.release]` says whether a release ships Linux."""
    return ["macos-pkg", "windows-exe"] + (["linux-tarball"] if ships_linux(root) else [])


def ships_linux(root: Path) -> bool:
    text = source(root, "Cargo.toml")
    return toml_value(text, "[package.metadata.release]", "linux", r"(true|false)") == "true"


# The rest is the same in both products.
CANDIDATE_TAG = re.compile(r"^v(?P<version>\d+\.\d+\.\d+)-rc\.[1-9]\d*$")
STABLE_TAG = re.compile(r"^v(?P<version>\d+\.\d+\.\d+)$")
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


def version(root: Path = ROOT, commit: str | None = None) -> str:
    return toml_text(source(root, "Cargo.toml", commit), "[package]", "version")


def build_number(root: Path) -> int:
    """The number build.rs bakes in: the commits behind HEAD."""
    return int(git("rev-list", "--count", "HEAD", root=root))


def inputs(root: Path) -> dict:
    """What the candidate was built from, as the checked-out tree states it."""
    truce = source(root, "truce.toml")
    field, value = asset_field(root)
    return {
        "build": build_number(root),
        "toolchain": toml_text(source(root, "rust-toolchain.toml"), "[toolchain]", "channel"),
        "cargo_truce": toml_text(source(root, "vendor/cargo-truce/Cargo.toml"), "[package]", "version"),
        "cargo_lock_sha256": sha256(root / "Cargo.lock"),
        field: value,
        "product": {
            "website_product_id": WEBSITE_PRODUCT_ID,
            "plugin_name": toml_text(truce, "[[plugin]]", "name"),
            "bundle_id": f'{toml_text(truce, "[vendor]", "id")}.{toml_text(truce, "[[plugin]]", "bundle_id")}',
            "fourcc": toml_text(truce, "[[plugin]]", "fourcc"),
            "crate": toml_text(source(root, "Cargo.toml"), "[package]", "name"),
        },
    }


def tag_version(tag: str, kind: str) -> str:
    match = (CANDIDATE_TAG if kind == "candidate" else STABLE_TAG).fullmatch(tag)
    if not match:
        expected = "vX.Y.Z-rc.N" if kind == "candidate" else "vX.Y.Z"
        raise ValueError(f"'{tag}' is not a {kind} tag; expected {expected}")
    return match.group("version")


def check_tag(tag: str, kind: str, root: Path = ROOT, commit: str | None = None) -> str:
    """A candidate needs the version's changelog section, not "in development";
    a stable release needs its heading dated."""
    tagged = tag_version(tag, kind)
    crate = version(root, commit)
    if tagged != crate:
        raise ValueError(f"{tag} names {tagged}, but Cargo.toml is {crate}")
    heading = re.search(
        rf"^## {re.escape(crate)}(?:[ \t](.*))?$", source(root, "CHANGELOG.md", commit), re.MULTILINE
    )
    if not heading:
        raise ValueError(f"CHANGELOG.md has no '## {crate}' section")
    title = heading.group(1) or ""
    if "in development" in title.lower():
        raise ValueError(f"CHANGELOG.md's '## {crate}' heading says it is in development")
    if kind == "stable" and not re.search(r"\b\d{4}-\d{2}-\d{2}\b", title):
        raise ValueError(f"CHANGELOG.md's '## {crate}' heading has no release date")
    return crate


def artifacts(directory: Path, release_version: str, root: Path) -> list[dict]:
    found = []
    for path in sorted(directory.iterdir()):
        details = next((kind for suffix, kind in KINDS.items() if path.name.endswith(suffix)), None)
        if details is None:
            continue
        if not path.is_file() or path.is_symlink():
            raise ValueError(f"release artifact is not a regular file: {path.name}")
        if not path.name.startswith(f"{ARTIFACT_PREFIX}-{release_version}-"):
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
    declared = declared_kinds(root)
    if sorted(item["kind"] for item in found) != sorted(declared):
        raise ValueError(f"a candidate needs exactly one of each declared download: {', '.join(declared)}")
    return found


def record(tag: str, directory: Path, root: Path = ROOT) -> dict:
    release_version = tag_version(tag, "candidate")
    built = inputs(root)
    if built["build"] < 100:
        raise ValueError(f"build number {built['build']} is too low; check out the full history")
    return {
        "schema": 1,
        "candidate": tag,
        "commit": git("rev-parse", "HEAD", root=root),
        "version": release_version,
        **built,
        "artifacts": artifacts(directory, release_version, root),
    }


def fetch(url: str, directory: Path) -> None:
    """Download a stored candidate: its record, the record's checksum and every
    artifact the record names."""
    directory.mkdir(parents=True, exist_ok=True)

    def download(name: str) -> Path:
        # Cloudflare refuses urllib's default user agent.
        request = urllib.request.Request(f"{url.rstrip('/')}/{name}", headers={"User-Agent": "resonantdsp-release"})
        with urllib.request.urlopen(request, timeout=300) as response:
            with (directory / name).open("wb") as target:
                shutil.copyfileobj(response, target)
        return directory / name

    stored = json.loads(download("release-record.json").read_text(encoding="utf-8"))
    download("release-record.sha256")
    for artifact in stored["artifacts"]:
        download(artifact["name"])


def verify(candidate_tag: str, stable_tag: str, accepted: str, directory: Path, root: Path = ROOT) -> dict:
    """The candidate in `directory` is the one a person accepted, built from the
    commit both tags and the checkout name."""
    if tag_version(candidate_tag, "candidate") != check_tag(stable_tag, "stable", root):
        raise ValueError("candidate and stable tags name different versions")
    commit = git("rev-list", "-n", "1", candidate_tag, root=root)
    if {commit, git("rev-list", "-n", "1", stable_tag, root=root), git("rev-parse", "HEAD", root=root)} != {commit}:
        raise ValueError("the candidate tag, the stable tag and the checkout must be one commit")
    path = directory / "release-record.json"
    if sha256(path) != accepted:
        raise ValueError("release-record.json does not match the accepted SHA-256")
    if (directory / "release-record.sha256").read_text(encoding="utf-8").split() != [accepted, path.name]:
        raise ValueError("release-record.sha256 does not name the accepted record")
    stored = json.loads(path.read_text(encoding="utf-8"))
    expected = {
        "schema": 1,
        "candidate": candidate_tag,
        "commit": commit,
        "version": tag_version(stable_tag, "stable"),
        **inputs(root),
    }
    for field, value in expected.items():
        if stored.get(field) != value:
            raise ValueError(f"the record's {field} does not match the stable tag's tree")
    if stored.get("artifacts") != artifacts(directory, expected["version"], root):
        raise ValueError("the candidate's artifacts do not match their recorded bytes")
    return stored


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    commands = parser.add_subparsers(dest="command", required=True)
    check = commands.add_parser("check-tag")
    check.add_argument("kind", choices=("candidate", "stable"))
    check.add_argument("tag")
    check.add_argument("--commit", help="check the files committed here, not the working tree")
    recording = commands.add_parser("record")
    recording.add_argument("tag")
    recording.add_argument("directory", type=Path)
    fetching = commands.add_parser("fetch")
    fetching.add_argument("url")
    fetching.add_argument("directory", type=Path)
    verifying = commands.add_parser("verify")
    verifying.add_argument("candidate_tag")
    verifying.add_argument("stable_tag")
    verifying.add_argument("record_sha256")
    verifying.add_argument("directory", type=Path)
    commands.add_parser("version")
    commands.add_parser("kinds")
    args = parser.parse_args(argv)
    try:
        if args.command == "check-tag":
            checked = check_tag(args.tag, args.kind, commit=args.commit)
            print(f"{args.tag} agrees with Cargo.toml and CHANGELOG.md at {checked}")
        elif args.command == "record":
            print(json.dumps(record(args.tag, args.directory), indent=2))
        elif args.command == "fetch":
            fetch(args.url, args.directory)
        elif args.command == "verify":
            stored = verify(args.candidate_tag, args.stable_tag, args.record_sha256, args.directory)
            print(f"{args.candidate_tag} is the accepted candidate for {args.stable_tag} at {stored['commit']}")
        elif args.command == "kinds":
            print("\n".join(declared_kinds(ROOT)))
        else:
            print(version())
    except (KeyError, OSError, ValueError, subprocess.CalledProcessError, json.JSONDecodeError) as error:
        print(str(error), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
