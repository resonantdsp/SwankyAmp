#!/usr/bin/env bash
# Run the format validators against the installed bundles.
#
# Usage: scripts/validate.sh <platform> [truce flags...]
# CLAP_BUNDLE names the bundle for the Windows pass, which packaged candidates
# need: `cargo truce package` leaves no staging manifest to read the name from.
#
# Windows needs its own CLAP run: cargo-truce 6.3.0 invokes clap-validator with
# `--test-filter preset-discovery --invert-filter`, which the pinned 0.4.1 build
# replaced with `-t` / `-x`, so truce's own CLAP pass dies on an unexpected
# argument there. Drop this branch once truce speaks the current options.
set -euo pipefail
cd "$(dirname "$0")/.."

platform=$1
shift

clap_bundle=${CLAP_BUNDLE:-}

if [ "$platform" != "windows" ]; then
  exec bash scripts/truce.sh validate --clap --pluginval "$@"
fi

bash scripts/truce.sh validate --pluginval "$@"

validator=$CLAP_VALIDATOR
# just reports a native Windows path; Git Bash runs the POSIX form of it.
if command -v cygpath >/dev/null 2>&1; then
  validator=$(cygpath -u "$validator")
fi

if [ -z "$clap_bundle" ]; then
  # `cargo truce build` records what it staged, so the bundle name stays with
  # truce.toml instead of being spelled out again here.
  filename=$(awk -F' = ' '
    { sub(/\r$/, "") }
    /^\[\[bundle\]\]/ { format = ""; filename = "" }
    /^format = / { gsub(/"/, "", $2); format = $2 }
    /^filename = / { gsub(/"/, "", $2); filename = $2 }
    format == "clap" && filename != "" { print filename; exit }
  ' target/bundles/manifest.toml)
  if [ -z "$filename" ]; then
    echo "target/bundles/manifest.toml lists no CLAP bundle; run 'just build'." >&2
    exit 1
  fi
  # Prefer the installed bundle, the way truce's own CLAP pass does on the
  # other platforms, so the validators judge what the install laid down.
  clap_bundle="target/bundles/$filename"
  common_files=${COMMONPROGRAMFILES:-${CommonProgramFiles:-}}
  for candidate in \
    "$common_files/CLAP/$filename" \
    "${LOCALAPPDATA:-}/Programs/Common/CLAP/$filename"; do
    if [ -e "$candidate" ]; then
      clap_bundle=$candidate
      break
    fi
  done
fi

if [ ! -e "$clap_bundle" ]; then
  echo "No CLAP bundle at $clap_bundle." >&2
  exit 1
fi

echo
echo "CLAP"
echo
# clap-validator requires preset locations to start with '/', which no
# spec-compliant Windows path does, so its preset discovery tests can never pass
# on this platform; truce excludes them for the same reason.
status=0
output=$("$validator" validate --exclude preset-discovery "$clap_bundle" 2>&1) || status=$?
printf '%s\n' "$output"
# The report is read as well as the exit status, the way truce reads a
# clap-validator run.
if [ "$status" -ne 0 ] || printf '%s' "$output" | grep -q FAILED; then
  exit 1
fi
