#!/usr/bin/env bash
# Download the pinned ASIO SDK into tools/ASIOSDK, where the Justfile points
# CPAL_ASIO_DIR, for the Windows standalone's ASIO driver support. Steinberg
# licenses this package under GPLv3 or its proprietary agreement; Swanky Amp,
# being GPL, takes the GPLv3 option. Pinned by file and checksum because the
# build's third-party notices name this exact package as the SDK's source.
# Other platforms never build it.
set -euo pipefail
cd "$(dirname "$0")/.."

case "$(uname -s)" in
MINGW* | MSYS* | CYGWIN*) ;;
*) exit 0 ;;
esac

SDK_URL=https://download.steinberg.net/sdk_downloads/ASIO-SDK_2.3.4_2025-10-15.zip
SDK_SHA256=d5ebf0c20dd2c5f43771fd0c1418f4b361bf52434ee670097cfa6b3a335e2eca

if [ -f tools/ASIOSDK/common/asio.h ]; then
  exit 0
fi

mkdir -p tools
archive=tools/asio-sdk.zip
curl --fail --location --silent --show-error --output "$archive" "$SDK_URL"
actual=$(sha256sum "$archive" | cut -d' ' -f1)
if [ "$actual" != "$SDK_SHA256" ]; then
  echo "$SDK_URL is $actual, expected $SDK_SHA256." >&2
  exit 1
fi
rm -rf tools/ASIOSDK
# Git Bash has no unzip and its tar may be GNU tar, which cannot read a zip;
# PowerShell is on every Windows machine. The archive's root is ASIOSDK/.
powershell.exe -NoProfile -Command \
  "Expand-Archive -LiteralPath '$(cygpath -w "$archive")' -DestinationPath '$(cygpath -w tools)' -Force"
rm "$archive"
test -f tools/ASIOSDK/common/asio.h
