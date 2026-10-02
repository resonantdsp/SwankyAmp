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

# The Windows standalone runs on ASIO when a driver is installed. Its builds
# there compile the ASIO SDK that `setup` fetches, and need libclang.
export CPAL_ASIO_DIR := tools / "ASIOSDK"
bundle_features := if os() == "windows" { "--features asio" } else { "" }

# The Audio Unit is macOS-only, and the formats are named rather than taken
# from the default features, which would also build Audio Unit version 3;
# truce.toml says why that is not shipped.
bundle_formats := if os() == "macos" { "--clap --vst3 --au2" } else { "" }

default: check

# One-time: the pinned build tool, the pinned format validators and, on
# Windows, the ASIO SDK.
setup:
    bash scripts/install-truce.sh
    bash scripts/install-validators.sh
    bash scripts/install-asio-sdk.sh

fmt:
    cargo fmt --all --check

# The default features (the plug-in formats and the standalone) compile the
# most of the crate: everything the set without them does, plus the format
# adapters and the standalone binary.
clippy:
    cargo clippy --all-targets --features tools -- -D warnings

# Also lints without the default features, where code only they use would be
# dead.
clippy-all: clippy
    cargo clippy --all-targets --no-default-features --features tools -- -D warnings

test:
    cargo test --no-default-features --features tools

# Also tests the format adapters, the standalone's audio panel and the
# vendored standalone host, a patched dependency whose tests the crate's own
# run leaves out.
test-all: test
    cargo test --no-default-features --features clap,standalone,rt-paranoid -- adapter_ standalone_audio
    cargo test -p truce-standalone

release-tests:
    python3 -m unittest discover -s .github/scripts -p 'test_*.py'
    node --test '.github/scripts/*.test.mjs'

reference-check:
    bash verification/reference/check.sh

model-check:
    cargo build --quiet --no-default-features --features tools --bin render-model
    python3 verification/model/check.py target/debug/render-model

# Measure oversampling and the plate filter against the legacy path.
dsp-report output="target/dsp/oversampling-plate.json":
    cargo build --quiet --no-default-features --features tools --bin render-model --bin dsp-probe
    python3 verification/dsp/report.py \
        target/debug/render-model target/debug/dsp-probe "{{ output }}"

recordings := "verification/reference/input"
recording_args := "--single-coil " + recordings / "single-coil-plucks-strum-chord.wav" + " --humbucker " + recordings / "humbucker-plucks-strum-chord.wav"

# Rewrite the version 2 factory bank and its report from the 1.4.0 presets on
# the guitar recordings: keep the bank's Low, Mid, High and Presence, match
# Power Drive to 1.4.0's power-stage feed and balance Output to Init's strike
# level. Rerun after `just calibrate` and listen; minutes in a release build.
refit:
    cargo build --release --quiet --no-default-features --features tools --bin refit-tone
    target/release/refit-tone --presets verification/reference/released/Resources/presets.xml \
        {{ recording_args }} --report verification/tone-stack/refit-report.md \
        --factory presets/factory-2.0.xml

# Measure the shipping path's preamp and output level tables against the
# released path and rewrite them as source.
calibrate:
    cargo build --quiet --no-default-features --features tools --bin calibrate
    target/debug/calibrate {{ recording_args }} --data src/dsp/calibration_data.rs

# Measure the unit knee's seam residuals per factory preset and input level.
knee-report output="target/dsp/knee.json":
    cargo build --quiet --no-default-features --features tools --bin render-model
    python3 verification/dsp/knee.py target/debug/render-model "{{ output }}"

# Render one released factory preset through the Rust baseline, including the
# internal seam WAVs used to localize any model drift.
render-model preset="clean" output="verification/model-output.wav":
    cargo run --quiet --no-default-features --features tools --bin render-model -- \
        --input verification/reference/input/single-coil.wav \
        --presets verification/reference/released/Resources/presets.xml \
        --preset "{{ preset }}" --sample-rate 44100 \
        --output "{{ output }}" --seams-dir "{{ output }}-seams"

# Pre-release: drive the shipping tone stack alone for 24 hours of samples at
# 44.1, 88.2 and 176.4 kHz and fail on any drift. Minutes in a release build.
tone-stack-soak hours="24":
    cargo build --release --quiet --no-default-features --features tools --bin tone-stack-soak
    target/release/tone-stack-soak "{{ hours }}"

# Start the long-run diagnostic soak (issue #34) in the background: three
# presets on the shipping path plus level 11 on the legacy path, logs under
# target/soak.
soak hours="4":
    cargo build --release --quiet --no-default-features --features tools --bin soak
    bash scripts/soak.sh start "{{ hours }}"

# Print the soak verdict from target/soak, finished or still running.
soak-check:
    bash scripts/soak.sh check

export-layout output="assets/layout":
    cargo run --quiet --bin swanky-amp-2 -- export-layout "{{ output }}"

capture output="verification/interface":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}"

# Capture with a factory preset applied, its name in the header.
capture-preset name="high gain" output="verification/interface-preset":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" preset "{{ name }}"

# Capture after a deterministic stereo note so the meters are lit.
capture-live output="verification/interface-live":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" live

# Capture with the information panel open; name a newer release, such as
# 2.0.1, to show its notice.
capture-information output="verification/interface-information" release="":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" information {{ release }}

# Capture the standalone's audio choices in the information panel, in one of
# the states choose, own-microphone, missing, built-in, interface, long-names,
# asio or fell-back; off shows the Input knob's OFF with the panel closed.
capture-audio state="choose" output="verification/interface-audio":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" audio "{{ state }}"

# Capture with the preset menu open under a user preset of this name, and
# the pointer over the field so the footer names it.
capture-menu name="Friday night rehearsal lead with the extra gain on the neck pickup" output="verification/interface-menu":
    cargo run --quiet --bin swanky-amp-2 -- capture "{{ output }}" menu "{{ name }}"

pack-artwork layers package="assets/artwork.pack":
    cargo run --quiet --bin swanky-amp-2 -- pack-artwork "{{ layers }}" "{{ package }}"

unpack-artwork package="assets/artwork.pack" output="verification/artwork-unpacked":
    cargo run --quiet --bin swanky-amp-2 -- unpack-artwork "{{ package }}" "{{ output }}"

validate-assets package="assets/artwork.pack" layers="assets/artwork":
    cargo run --quiet --bin swanky-amp-2 -- validate-assets "{{ package }}" "{{ layers }}"

refresh-artwork layers="assets/artwork":
    cargo run --quiet --bin swanky-amp-2 -- refresh-artwork "{{ layers }}"

# Write THIRD-PARTY-NOTICES.txt from the shipped dependency tree, the ASIO SDK
# and the bundled fonts; candidates embed it for the information panel.
notices:
    bash scripts/notices.sh

# The per-change gate. CI runs `ci-checks`; the README says which of its
# checks to run locally for which kind of change.
check: fmt clippy test

build:
    bash scripts/truce.sh build {{ bundle_formats }} {{ bundle_features }}

build-standalone:
    cargo build --release --no-default-features --features standalone {{ bundle_features }} --bin swanky-amp-2

# Open the standalone shell for local interface and audio checks.
run:
    bash scripts/truce.sh run {{ bundle_features }}

validate *flags: build
    bash scripts/truce.sh install --user --no-build {{ bundle_formats }}
    bash scripts/validate.sh {{ os() }} {{ flags }}

validate-installed *flags:
    bash scripts/validate.sh {{ os() }} {{ flags }}

package *flags:
    bash scripts/truce.sh package {{ bundle_features }} {{ flags }}

version version:
    bash .github/scripts/version.sh "{{ version }}"

tag-candidate:
    bash .github/scripts/release_tag.sh candidate

# Tag the accepted candidate's commit as the stable release.
tag-release candidate_tag:
    bash .github/scripts/release_tag.sh release "{{ candidate_tag }}"

release-check kind tag:
    python3 .github/scripts/release_contract.py check-tag "{{ kind }}" "{{ tag }}"

promote-check candidate_tag tag record_sha256 directory:
    python3 .github/scripts/release_contract.py verify-candidate \
        "{{ candidate_tag }}" "{{ tag }}" "{{ record_sha256 }}" "{{ directory }}"

# Everything CI's Linux job proves before any bundle is built, besides the
# reference and model comparisons, which it runs when their inputs change.
ci-checks: fmt clippy-all test-all release-tests

ci-bundles: build-standalone (validate "--skip-gui-tests")
