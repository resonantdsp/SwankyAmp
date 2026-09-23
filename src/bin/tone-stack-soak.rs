//! Pre-release check that the shipping tone stack stays numerically stable
//! over a day of continuous play.
//!
//! The 12-hour amplifier soak found level 11 collapsing after about ten hours
//! at 2x: a spurious pole on the unit circle in the treble sections, rounded
//! outside it, grew from rounding noise until it swamped the signal. That
//! growth is a few parts in 10⁹ per sample, so only hours of samples show it,
//! and the stack alone renders those in minutes. Every case drives the stack
//! with white noise at the level it sees at level 11 for 24 hours of samples
//! and fails if any hour's level or offset moves.

use std::process::ExitCode;
use std::thread;

use swanky_amp::dsp::amp::AmpControls;
use swanky_amp::dsp::diagnostics::tone_stack_soak;
use swanky_amp::presets;

/// Tone-stack input RMS at level 11: the soak's fifth-triode seam of
/// -11.2 dB times the 35.0 triode scale.
const INPUT_RMS: f64 = 9.7;
const HOURS: f64 = 24.;
const RATES: [f32; 3] = [44_100., 88_200., 176_400.];
/// The hourly level may wander by no more than this from the first hour.
const LEVEL_TOLERANCE_DB: f64 = 0.01;
/// The hourly mean may not exceed this share of the output RMS.
const OFFSET_TOLERANCE: f64 = 1e-4;

fn cases() -> Result<Vec<(String, AmpControls)>, String> {
    let mut cases = vec![(
        "level 11".to_owned(),
        presets::controls(presets::FACTORY_BANK, "level 11")?,
    )];
    for (model, name) in [(0., "Fender"), (1., "Marshall"), (2., "AC30")] {
        for knobs in [-1., 1.] {
            cases.push((
                format!("{name} Low/Mid/High {knobs:+}"),
                AmpControls {
                    low: knobs,
                    mid: knobs,
                    high: knobs,
                    presence: knobs,
                    tone_stack: model,
                    ..AmpControls::default()
                },
            ));
        }
    }
    Ok(cases)
}

fn main() -> ExitCode {
    let hours: f64 = std::env::args()
        .nth(1)
        .map_or(Ok(HOURS), |value| value.parse())
        .unwrap_or(HOURS);
    let cases = match cases() {
        Ok(cases) => cases,
        Err(error) => {
            eprintln!("tone-stack-soak: {error}");
            return ExitCode::FAILURE;
        }
    };
    let runs: Vec<_> = cases
        .iter()
        .flat_map(|case| RATES.map(|rate| (case, rate)))
        .collect();
    let results: Vec<_> = thread::scope(|scope| {
        let handles: Vec<_> = runs
            .iter()
            .map(|&((_, controls), rate)| {
                scope.spawn(move || {
                    tone_stack_soak(rate, *controls, INPUT_RMS, hours * 3600., 3600.)
                })
            })
            .collect();
        handles
            .into_iter()
            .map(|handle| handle.join().unwrap())
            .collect()
    });
    println!(
        "tone stack alone, {hours} h of white noise at {INPUT_RMS} RMS; \
         bounds {LEVEL_TOLERANCE_DB} dB level, {OFFSET_TOLERANCE:e} offset/RMS"
    );
    let mut failed = false;
    for (((name, _), rate), windows) in runs.iter().zip(&results) {
        let first = windows[0].rms;
        let drift = windows
            .iter()
            .map(|window| 20. * (window.rms / first).log10())
            .fold(0_f64, |worst, value| {
                if value.abs() > worst.abs() {
                    value
                } else {
                    worst
                }
            });
        let offset = windows
            .iter()
            .map(|window| (window.mean / window.rms).abs())
            .fold(0_f64, f64::max);
        let pass = drift.abs().is_finite()
            && drift.abs() <= LEVEL_TOLERANCE_DB
            && offset <= OFFSET_TOLERANCE;
        failed |= !pass;
        println!(
            "{} {name:28} {rate:>8} Hz  level {:+.4} dB  worst drift {drift:+.5} dB  worst offset/RMS {offset:.2e}",
            if pass { "PASS" } else { "FAIL" },
            20. * first.log10(),
        );
    }
    if failed {
        ExitCode::FAILURE
    } else {
        ExitCode::SUCCESS
    }
}
