#!/usr/bin/env bash
# Install the pinned source copy locally. It is cargo-truce 6.3.0 plus the
# credential-chain patch described in vendor/cargo-truce/UPSTREAM.md.
set -euo pipefail
cd "$(dirname "$0")/.."

cargo install --path vendor/cargo-truce --locked --force \
  --root tools/cargo-truce --target-dir target/cargo-truce
