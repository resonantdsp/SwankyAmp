#!/usr/bin/env bash
# Invoke the checkout-local cargo-truce through a path both native Bash and
# Git Bash understand.
set -euo pipefail
cd "$(dirname "$0")/.."

tool=${CARGO_TRUCE:?Run through a Justfile recipe so CARGO_TRUCE is set}
if command -v cygpath >/dev/null 2>&1; then
  tool=$(cygpath -u "$tool")
fi
exec "$tool" "$@"
