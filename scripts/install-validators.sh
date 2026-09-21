#!/usr/bin/env bash
# Download the pinned format validators into tools/. Pinned by release tag and
# verified by checksum so a validator report names a known binary, and so an
# upstream re-release cannot silently change what CI accepts.
set -euo pipefail
cd "$(dirname "$0")/.."

PLUGINVAL_TAG=v1.0.4
CLAP_VALIDATOR_TAG=0.4.1
CLAP_VALIDATOR_BUILD=0.4.1-127-g152b982

case "$(uname -s)" in
Darwin)
  pluginval_asset=pluginval_macOS.zip
  pluginval_sha=3c4c533bda0c5059eea3ddaea752d757ee2025041f0f47e6bcb0e87f6082b29f
  clap_asset="clap-validator-${CLAP_VALIDATOR_BUILD}-macos-universal.zip"
  clap_sha=bbec8cd7d18274e549d5d8c12ece3cec54be966129388dd2e742b9957f2ba9f1
  ;;
Linux)
  pluginval_asset=pluginval_Linux.zip
  pluginval_sha=c01c49d8063965c4c2dea8324468336768f5c9139e0b1caebde14c2400b55352
  clap_asset="clap-validator-${CLAP_VALIDATOR_BUILD}-ubuntu-22.04.zip"
  clap_sha=49edadcfb407ea0dd946ce418300e853fbd2660fa4b0d00e4f19ff8eef24ad90
  ;;
*)
  pluginval_asset=pluginval_Windows.zip
  pluginval_sha=c08e61ce3b96db41636f8ec7e76f4c7e2c13ebdac7fa1b5a1f52b4f32ec715ab
  clap_asset="clap-validator-${CLAP_VALIDATOR_BUILD}-windows.zip"
  clap_sha=d935c3af0a45c3911ea2e900f4aa5d6709dac82bb485f0c4ce28648ab2cd0c10
  ;;
esac

sha256_of() {
  if command -v sha256sum >/dev/null 2>&1; then
    sha256sum "$1" | cut -d' ' -f1
  else
    shasum -a 256 "$1" | cut -d' ' -f1
  fi
}

# Git for Windows ships bsdtar but no unzip; the Linux runners are the reverse.
unpack_zip() {
  if command -v unzip >/dev/null 2>&1; then
    unzip -o -q "$1" -d "$2"
  else
    tar -x -f "$1" -C "$2"
  fi
}

download() {
  local url=$1 destination=$2 expected=$3
  curl --fail --location --silent --show-error --output "$destination" "$url"
  local actual
  actual=$(sha256_of "$destination")
  if [ "$actual" != "$expected" ]; then
    echo "$url is $actual, expected $expected." >&2
    exit 1
  fi
}

mkdir -p tools
work=$(mktemp -d "${TMPDIR:-/tmp}/validators.XXXXXX")
trap 'rm -rf "$work"' EXIT

download "https://github.com/Tracktion/pluginval/releases/download/${PLUGINVAL_TAG}/${pluginval_asset}" \
  "$work/pluginval.zip" "$pluginval_sha"
download "https://github.com/free-audio/clap-validator/releases/download/${CLAP_VALIDATOR_TAG}/${clap_asset}" \
  "$work/clap-validator.zip" "$clap_sha"

unpack_zip "$work/pluginval.zip" "$work/pluginval"
rm -rf tools/pluginval tools/pluginval.exe tools/pluginval.app
cp -R "$work"/pluginval/* tools/

unpack_zip "$work/clap-validator.zip" "$work/clap-validator"
# The non-Windows assets wrap the binary in a further tarball, and the macOS
# one nests it under binaries/ where the Linux one does not.
tarball=$(find "$work/clap-validator" -name '*.tar.gz' -print -quit)
if [ -n "$tarball" ]; then
  tar -x -f "$tarball" -C "$work/clap-validator"
  cp "$(find "$work/clap-validator" -type f -name clap-validator -print -quit)" tools/clap-validator
else
  cp "$work/clap-validator/clap-validator.exe" tools/clap-validator.exe
fi

chmod +x tools/clap-validator 2>/dev/null || true
chmod +x tools/pluginval 2>/dev/null || true
chmod +x tools/pluginval.app/Contents/MacOS/pluginval 2>/dev/null || true

echo "pluginval ${PLUGINVAL_TAG} and clap-validator ${CLAP_VALIDATOR_TAG} are in tools/"
