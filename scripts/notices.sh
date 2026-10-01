#!/usr/bin/env bash
# Write THIRD-PARTY-NOTICES.txt from the shipped dependency tree, the ASIO SDK
# and the bundled fonts. The candidate workflow runs this before packaging
# and names the file in THIRD_PARTY_NOTICES, which build.rs embeds for the
# information panel.
set -euo pipefail
cd "$(dirname "$0")/.."

# `verify` runs after packaging: a build that never received the notices embeds
# a placeholder without failing, so every plug-in and app binary staged for the
# installers must carry the generated text. Small binaries are loader shims
# that hold no product code.
if [ "${1:-}" = "verify" ]; then
  marker="the third-party fonts and software listed below"
  found=0
  while IFS= read -r -d '' file; do
    [ "$(wc -c < "$file")" -gt 1000000 ] || continue
    case "$(head -c 4 "$file" | od -An -tx1 | tr -d ' \n')" in
    cffaedfe | cafebabe | 7f454c46 | 4d5a*) ;;
    *) continue ;;
    esac
    if ! LC_ALL=C grep -q -a -F "$marker" "$file"; then
      echo "$file carries no third-party notices." >&2
      exit 1
    fi
    found=$((found + 1))
  done < <(find target/package -type f -print0)
  if [ "$found" -eq 0 ]; then
    echo "No packaged binaries under target/package to check." >&2
    exit 1
  fi
  echo "$found packaged binaries carry the third-party notices."
  exit 0
fi

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
  # A download host's transient error (a 5xx or a timeout) is retried rather
  # than failing the run; the timeouts stop a hung download.
  curl --fail --location --silent --show-error --retry 4 --connect-timeout 30 --max-time 600 --output "$work/$archive" \
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

# The Windows standalone links Steinberg's ASIO SDK, which is not a crate, so
# cargo-about never sees it. Taken under GPLv3, it must travel with that
# licence and directions to its source; its host helpers are BSD-licensed.
asio_sdk() {
  local url sha
  url=$(sed -n 's/^SDK_URL=//p' scripts/install-asio-sdk.sh)
  sha=$(sed -n 's/^SDK_SHA256=//p' scripts/install-asio-sdk.sh)
  echo "--------------------------------------------------------------------------------"
  echo "Steinberg ASIO SDK"
  echo
  echo "Used by:"
  echo "  the Windows standalone app, through asio-sys"
  echo
  echo "Its complete source is Steinberg's package at"
  echo "  ${url}"
  echo "  (SHA-256 ${sha})."
  echo "Swanky Amp uses the SDK under the GNU General Public License, version 3,"
  echo "the open-source option of the dual licence below; the text of that licence"
  echo "follows, after the BSD licence of the SDK's host helpers."
  echo
  cat assets/asio-sdk/LICENSE.txt
  echo
  cat assets/asio-sdk/host-LICENSE.txt
  echo
  cat LICENSE
  echo
}

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
  "$tool" generate --features asio,au about.hbs
  asio_sdk
  echo "--------------------------------------------------------------------------------"
  echo "The Truce License 1.0"
  echo
  echo "Used by:"
  echo "  the truce ${truce_version} crates (https://github.com/truce-audio/truce)"
  echo
  cat vendor/truce-clap/LICENSE
}

generate > THIRD-PARTY-NOTICES.txt
