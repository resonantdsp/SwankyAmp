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
    cargo test --no-default-features --features clap,standalone,rt-paranoid adapter_

release-tests:
    python3 -m unittest discover -s .github/scripts -p 'test_*.py'
    node --test '.github/scripts/*.test.mjs'

reference-check:
    bash verification/reference/check.sh

model-check:
    cargo build --quiet --no-default-features --bin render-model
    python3 verification/model/check.py target/debug/render-model

# Regenerate the measured oversampling and plate-filter evidence.
dsp-report output="verification/dsp/oversampling-plate.json":
    cargo build --quiet --no-default-features --bin render-model --bin dsp-probe
    python3 verification/dsp/report.py \
        target/debug/render-model target/debug/dsp-probe "{{ output }}"

# Refit the factory presets to the standard tone-stack mapping and rewrite the
# version 2 bank and its residual report.
refit:
    cargo build --quiet --no-default-features --bin refit-tone
    target/debug/refit-tone --presets verification/reference/released/Resources/presets.xml \
        --report-dir verification/tone-stack --factory presets/factory-2.0.xml

# Regenerates the refit and fails unless the committed bank and report match
# it, which also proves the refit is reproducible.
refit-check:
    cargo build --quiet --no-default-features --bin refit-tone
    target/debug/refit-tone --presets verification/reference/released/Resources/presets.xml \
        --report-dir verification/tone-stack --factory presets/factory-2.0.xml --check

# Regenerate the unit-knee seam residuals per factory preset and input level.
knee-report output="verification/dsp/knee.json":
    cargo build --quiet --no-default-features --bin render-model
    python3 verification/dsp/knee.py target/debug/render-model "{{ output }}"

# Render one released factory preset through the Rust baseline, including the
# internal seam WAVs used to localize any model drift.
render-model preset="clean" output="verification/model-output.wav":
    cargo run --quiet --no-default-features --bin render-model -- \
        --input verification/reference/input/single-coil.wav \
        --presets verification/reference/released/Resources/presets.xml \
        --preset "{{ preset }}" --sample-rate 44100 \
        --output "{{ output }}" --seams-dir "{{ output }}-seams"

# Start the release soak for issue #34 in the background: three presets on the
# shipping path plus level 11 on the legacy path, logs under target/soak.
soak hours="4":
    cargo build --release --quiet --no-default-features --bin soak
    bash scripts/soak.sh start "{{ hours }}"

# Print the soak verdict from target/soak, finished or still running.
soak-check:
    bash scripts/soak.sh check

export-layout output="assets/layout":
    cargo run --quiet --bin swanky-amp-2 -- export-layout "{{ output }}"

capture output="verification/interface":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}"

# Capture after a deterministic stereo note so the meters are lit.
capture-live output="verification/interface-live":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" live

pack-artwork layers package="assets/artwork.pack":
    cargo run --quiet --bin swanky-amp-2 -- pack-artwork "{{ layers }}" "{{ package }}"

unpack-artwork package="assets/artwork.pack" output="verification/artwork-unpacked":
    cargo run --quiet --bin swanky-amp-2 -- unpack-artwork "{{ package }}" "{{ output }}"

validate-assets package="assets/artwork.pack" layers="assets/artwork":
    cargo run --quiet --bin swanky-amp-2 -- validate-assets "{{ package }}" "{{ layers }}"

refresh-artwork layers="assets/artwork":
    cargo run --quiet --bin swanky-amp-2 -- refresh-artwork "{{ layers }}"

check: fmt clippy test release-tests reference-check model-check refit-check validate-assets

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

validate-installed *flags:
    bash scripts/validate.sh {{ os() }} {{ flags }}

package *flags:
    bash scripts/truce.sh package {{ flags }}

version version:
    bash .github/scripts/version.sh "{{ version }}"

tag-candidate:
    bash .github/scripts/release_tag.sh candidate

tag-release:
    bash .github/scripts/release_tag.sh release

release-check kind tag:
    python3 .github/scripts/release_contract.py check-tag "{{ kind }}" "{{ tag }}"

promote-check candidate_tag tag record_sha256 directory:
    python3 .github/scripts/release_contract.py verify-candidate \
        "{{ candidate_tag }}" "{{ tag }}" "{{ record_sha256 }}" "{{ directory }}"

ci-checks: check

ci-bundles: build-standalone (validate "--skip-gui-tests")
