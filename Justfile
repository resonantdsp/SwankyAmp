# Local and hosted checks call the same recipes so failures reproduce directly.
set shell := ["bash", "-euo", "pipefail", "-c"]
set windows-shell := ["bash", "-euo", "pipefail", "-c"]

tools := justfile_directory() / "tools"
cargo_truce := if os() == "windows" {
    tools / "cargo-truce/bin/cargo-truce.exe"
} else {
    tools / "cargo-truce/bin/cargo-truce"
}

export TRUCE_VERSION := "6.3.0"
export CARGO_TRUCE := cargo_truce
export PLUGINVAL := if os() == "macos" {
    tools / "pluginval.app/Contents/MacOS/pluginval"
} else if os() == "windows" {
    tools / "pluginval.exe"
} else {
    tools / "pluginval"
}
export CLAP_VALIDATOR := if os() == "windows" {
    tools / "clap-validator.exe"
} else {
    tools / "clap-validator"
}

default: check

setup:
    bash scripts/install-truce.sh
    bash scripts/install-validators.sh

fmt:
    cargo fmt --all --check

clippy:
    cargo clippy --all-targets --no-default-features -- -D warnings
    cargo clippy --all-targets -- -D warnings

test:
    cargo test --no-default-features

reference-check:
    bash verification/reference/check.sh

check: fmt clippy test reference-check

build:
    bash scripts/truce.sh build

build-standalone:
    cargo build --release --no-default-features --features standalone --bin swanky-amp-2

# Open the standalone shell for local interface and audio checks.
run:
    bash scripts/truce.sh run

validate *flags: build
    bash scripts/truce.sh install --user --no-build
    bash scripts/validate.sh {{ os() }} {{ flags }}

ci-checks: check

ci-bundles: build-standalone (validate "--skip-gui-tests")
