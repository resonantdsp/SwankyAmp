#!/usr/bin/env bash
# Install the exact build tool version used to stage and validate bundles.
set -euo pipefail
cd "$(dirname "$0")/.."

cargo install cargo-truce --version "${TRUCE_VERSION:?}" --locked --force \
  --root tools/cargo-truce --target-dir target/cargo-truce
