#!/usr/bin/env bash
# Write THIRD-PARTY-NOTICES.txt from the shipped dependency tree and the
# bundled fonts. The candidate workflow runs this before packaging and names
# the file in THIRD_PARTY_NOTICES, which build.rs embeds for the information
# panel.
set -euo pipefail
cd "$(dirname "$0")/.."

# Pinned by release and checksum so the notices do not change with the tool.
CARGO_ABOUT_VERSION=0.9.2
case "$(uname -s)-$(uname -m)" in
Darwin-arm64)
  target=aarch64-apple-darwin
  sha=ae72f0df0c399a1e96336f696fa55b1b28679fd725632eba8cf8e4568467cc3e
  ;;
Linux-x86_64)
  target=x86_64-unknown-linux-musl
  sha=9099a59e820c38a68b9d65f300662a567d56562f9a10f6aa4c7e86c17c2566af
  ;;
MINGW*-x86_64 | MSYS*-x86_64)
  target=x86_64-pc-windows-msvc
  sha=1c03e5890238562497c2d89a3b75b02560af349c1fc3e713d3284f532a5cd748
  ;;
*)
  echo "No pinned cargo-about for $(uname -s) $(uname -m)." >&2
  exit 1
  ;;
esac

tool="tools/cargo-about-${CARGO_ABOUT_VERSION}"
case "$target" in *windows*) tool="$tool.exe" ;; esac
if [ ! -x "$tool" ]; then
  mkdir -p tools
  work=$(mktemp -d "${TMPDIR:-/tmp}/cargo-about.XXXXXX")
  trap 'rm -rf "$work"' EXIT
  archive="cargo-about-${CARGO_ABOUT_VERSION}-${target}.tar.gz"
  curl --fail --location --silent --show-error --output "$work/$archive" \
    "https://github.com/EmbarkStudios/cargo-about/releases/download/${CARGO_ABOUT_VERSION}/${archive}"
  actual=$( (sha256sum "$work/$archive" 2>/dev/null || shasum -a 256 "$work/$archive") | cut -d' ' -f1)
  if [ "$actual" != "$sha" ]; then
    echo "$archive is $actual, expected $sha." >&2
    exit 1
  fi
  tar -xzf "$work/$archive" -C "$work"
  cp "$(find "$work" -type f \( -name cargo-about -o -name cargo-about.exe \) -print -quit)" "$tool"
  chmod +x "$tool"
fi

# The Truce crates name a licence of their own, which cargo-about cannot find
# the text of in the published crates; the vendored copy carries it unchanged.
truce_version=$(grep -A1 '^name = "truce-core"$' Cargo.lock | sed -n 's/^version = "\(.*\)"$/\1/p')

generate() {
  cat <<'HEADER'
Swanky Amp is free software under the GNU General Public License, version 3
or later; its source and licence are at https://github.com/resonantdsp/SwankyAmp.
It includes the third-party fonts and software listed below, each under the
licence that follows its name.

HEADER
  for font in assets/fonts/*-OFL.txt; do
    echo "--------------------------------------------------------------------------------"
    echo "$(basename "$font" -OFL.txt) font"
    echo
    cat "$font"
    echo
  done
  "$tool" generate --features asio about.hbs 2>/dev/null
  echo "--------------------------------------------------------------------------------"
  echo "The Truce License 1.0"
  echo
  echo "Used by:"
  echo "  the truce ${truce_version} crates (https://github.com/truce-audio/truce)"
  echo
  cat vendor/truce-clap/LICENSE
}

generate > THIRD-PARTY-NOTICES.txt
