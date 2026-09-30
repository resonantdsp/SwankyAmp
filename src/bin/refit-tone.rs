//! Voices the 1.4.0 factory presets for the corrected tone stack and writes
//! the version 2 factory bank with a report. Low, Mid, High and Presence come
//! from the bank being rewritten, the voicing accepted by ear, and are searched
//! only for a preset it lacks; Power Drive and Output are measured on every
//! run. The bank is judged by ear, not by the report.

use std::env;
use std::fs;
use std::path::{Path, PathBuf};

use swanky_amp::dsp::amp::{AmpControls, LevelTables};
use swanky_amp::dsp::calibration::{self, Clips, PresetLevels, RECORDING_GAIN_DB};
use swanky_amp::dsp::refit::{
    self, Comparison, FEED_COST, RAIL, RESOLUTION_DB, STRIKE_FRACTION, Voiced, Voicing,
};
use swanky_amp::presets;

/// The Output control spans -35..+35 dB over its stored -1..+1.
const OUTPUT_RANGE_DB: f64 = 35.;

fn option(name: &str) -> Result<String, String> {
    let arguments: Vec<String> = env::args().collect();
    arguments
        .windows(2)
        .find(|pair| pair[0] == name)
        .map(|pair| pair[1].clone())
        .ok_or_else(|| format!("missing option: {name}"))
}

fn read(path: &Path) -> Result<String, String> {
    fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))
}

fn clips() -> Result<Clips, String> {
    let bytes = |name: &str| -> Result<Vec<u8>, String> {
        let path = option(name)?;
        fs::read(&path).map_err(|error| format!("{path}: {error}"))
    };
    Clips::new(&bytes("--single-coil")?, &bytes("--humbucker")?)
}

struct Preset {
    name: String,
    voiced: Voiced,
    /// Output as stored before and after bringing the preset to Init's
    /// strike level on the humbucker, and the levels that result.
    output_before: f32,
    output_after: f32,
    levels: PresetLevels,
}

fn xml_value(value: f32) -> String {
    let text = format!("{value:.6}");
    let text = text.trim_end_matches('0');
    if text.ends_with('.') {
        format!("{text}0")
    } else {
        text.to_owned()
    }
}

/// Voices every 1.4.0 factory preset, starting from the accepted bank
/// `current`, when given.
fn voice_all(
    released: &str,
    current: Option<&str>,
    clips: &Clips,
    target: PresetLevels,
) -> Result<Vec<Preset>, String> {
    let jobs = presets::names(released)
        .into_iter()
        .map(|name| {
            let accepted = current
                .map(|bank| presets::controls(bank, &name))
                .transpose()
                .map_err(|error| format!("accepted bank: {error}"))?
                .map(Voicing::of);
            Ok((presets::controls(released, &name)?, accepted, name))
        })
        .collect::<Result<Vec<_>, String>>()?;
    Ok(std::thread::scope(|scope| {
        let handles: Vec<_> = jobs
            .into_iter()
            .map(|(controls, accepted, name)| {
                scope.spawn(move || {
                    let voiced = refit::voice(controls, accepted, clips);
                    let voiced_controls = voiced.voiced.apply(controls);
                    let measured =
                        calibration::preset_levels(voiced_controls, clips, LevelTables::CALIBRATED);
                    let change_db = target.strike.humbucker - measured.strike.humbucker;
                    let output_after: f32 = xml_value(
                        (f64::from(controls.output) + change_db / OUTPUT_RANGE_DB) as f32,
                    )
                    .parse()
                    .expect("Output is a number");
                    let levels = calibration::preset_levels(
                        AmpControls {
                            output: output_after,
                            ..voiced_controls
                        },
                        clips,
                        LevelTables::CALIBRATED,
                    );
                    Preset {
                        name,
                        voiced,
                        output_before: controls.output,
                        output_after,
                        levels,
                    }
                })
            })
            .collect();
        handles
            .into_iter()
            .map(|handle| handle.join().expect("voicing thread panicked"))
            .collect()
    }))
}

fn factory_bank(released: &str, presets: &[Preset]) -> Result<String, String> {
    let mut xml = released.to_owned();
    for preset in presets {
        let (old, new) = (preset.voiced.original, preset.voiced.voiced);
        let mut values: Vec<(&str, String)> = [
            ("idTsLow", old.low, new.low),
            ("idTsMid", old.mid, new.mid),
            ("idTsHigh", old.high, new.high),
            ("idTsPresence", old.presence, new.presence),
            ("idPowerAmpDrive", old.power_drive, new.power_drive),
        ]
        .into_iter()
        .filter(|(_, old, new)| old != new)
        .map(|(id, _, new)| (id, xml_value(new)))
        .collect();
        values.push(("idOutputLevel", xml_value(preset.output_after)));
        xml = presets::with_values(&xml, &preset.name, &values)?;
    }
    Ok(xml)
}

/// A control as the panel shows it, 0 to 10.
fn knob(value: f32) -> f32 {
    (value + 1.) * 5.
}

fn settings(voicing: Voicing) -> String {
    format!(
        "{} / {} / {} / {} / {}",
        panel(voicing.low),
        panel(voicing.mid),
        panel(voicing.high),
        panel(voicing.presence),
        panel(voicing.power_drive)
    )
}

/// A panel value with as many decimals as it needs, up to two.
fn panel(value: f32) -> String {
    let text = format!("{:.2}", knob(value));
    let text = text.trim_end_matches('0');
    if text.ends_with('.') {
        format!("{text}0")
    } else {
        text.to_owned()
    }
}

fn pair(values: [f64; 2], signed: bool) -> String {
    if signed {
        format!("{:+.1} / {:+.1}", values[0], values[1])
    } else {
        format!("{:.1} / {:.1}", values[0], values[1])
    }
}

fn change(before: [f64; 2], after: [f64; 2], signed: bool) -> String {
    format!("{} → {}", pair(before, signed), pair(after, signed))
}

fn band_table(title: &str, presets: &[Preset]) -> String {
    let centres = refit::band_centres();
    let shown: Vec<usize> = (0..centres.len())
        .step_by(4)
        .chain([centres.len() - 1])
        .collect();
    let mut text = format!("{title}\n\n| Preset |");
    for &band in &shown {
        text.push_str(&format!(" {:.0} |", centres[band]));
    }
    text.push_str("\n|---|");
    text.push_str(&"---|".repeat(shown.len()));
    text.push('\n');
    for preset in presets {
        text.push_str(&format!("| {} |", preset.name));
        for &band in &shown {
            text.push_str(&format!(" {:+.1} |", preset.voiced.strike_bands_db[band]));
        }
        text.push('\n');
    }
    text
}

fn markdown(presets: &[Preset], init: PresetLevels) -> String {
    let mut text = format!(
        "# Factory voicing\n\n\
         Generated by `just refit`.\n\n\
         Version 2 discretises the tone stack with the standard bilinear constant\n\
         `2·SR`. Swanky Amp 1.4.0 used `SR`, which voiced every tone-stack\n\
         feature an octave above the circuit. The factory presets were made on\n\
         that stack, so each is revoiced to keep its character: the same\n\
         balance between bands at the output, and the power stage driven as\n\
         hard. The corrected stack cannot reproduce the octave-high scoop\n\
         exactly, so the aim is the right range, not a replica.\n\n\
         ## Method\n\n\
         - Input: the two guitar recordings in `verification/reference/input`, single\n\
           coil and humbucker, played at Input 0 with `RECORDING_GAIN_DB` ({RECORDING_GAIN_DB} dB)\n\
           applied to both.\n\
         - Each preset is rendered through 1.4.0 (the legacy path, which `just\n\
           model-check` holds to the released renders) and through the shipping\n\
           path at {} Hz with Auto oversampling.\n\
         - Balance is the output's sixth-octave band levels from 80 Hz to 16 kHz,\n\
           each render's bands taken about their own mean, so level does not\n\
           count. It is judged at the strikes: the loudest {:.0} % of each\n\
           recording's momentary-loudness blocks (the blocks the strike level\n\
           ranks, below), picked on the recording, where the player struck, so\n\
           every render is measured over the same stretches. That share takes in\n\
           the first plucks as well as the strum and the chord. The error is the\n\
           band difference from 1.4.0 averaged at the fourth power, so a narrow\n\
           peak counts, averaged over the recordings. The whole-recording error,\n\
           which the ring-out dominates, is reported beside it.\n\
         - Low, Mid, High, Presence and Power Drive sit on a grid of half marks\n\
           on the 0 to 10 scale. The tone controls start from the bank being\n\
           replaced, the voicing accepted by ear, on whichever neighbouring grid\n\
           values match best; among roundings within {RESOLUTION_DB} dB of the best,\n\
           the one off the rails and nearest 1.4.0's settings. They then move a\n\
           step at a time while a step lowers the error by {RESOLUTION_DB} dB or more,\n\
           and stay within {:.0} to {:.0}, so presets leave room either way.\n\
         - Every candidate is judged with Power Drive set so the power stage's\n\
           input level, averaged over the recordings, matches 1.4.0's; where it\n\
           runs out of range, the miss costs {FEED_COST} dB² per dB². The bank\n\
           then takes the grid value nearest that setting in gain.\n\
         - Output then brings each preset's strike level on the humbucker to\n\
           Init's. The strike level is the 95th percentile of momentary\n\
           loudness (BS.1770-4 K-weighted 400 ms blocks at a 100 ms hop, those\n\
           above -70 LUFS) over the whole recording. Integrated loudness\n\
           averages over the ring-out, where a driven amp sustains and a clean\n\
           one decays, so a driven preset level with Init on it strikes\n\
           softer. A clean amp follows the pickup and a driven one does not,\n\
           so on the single coil the driven presets come out louder than Init.\n\n\
         ## Results\n\n\
         Controls are Low / Mid / High / Presence / Power Drive on the panel's 0\n\
         to 10 scale. Errors are the band difference from 1.4.0 in dB and\n\
         feed is the power stage's input level minus 1.4.0's in dB, each for the\n\
         single coil / humbucker, from the bank replaced to the voiced one.\n\
         Exact feed is the voiced tone with Power Drive off the grid, set to\n\
         restore the feed exactly. Output is 1.4.0's and then version 2's, in dB.\n\n\
         | Preset | 1.4.0 | Replaced | Voiced | Strike error | Whole error | Feed | Exact feed | Output dB |\n\
         |---|---|---|---|---|---|---|---|---|\n",
        calibration::SAMPLE_RATE,
        STRIKE_FRACTION * 100.,
        knob(-RAIL),
        knob(RAIL),
    );
    for preset in presets {
        let voiced = &preset.voiced;
        let (before, after): (Comparison, Comparison) =
            (voiced.current_comparison, voiced.voiced_comparison);
        text.push_str(&format!(
            "| {} | {} | {} | {} | {} | {} | {} | {} | {:+.1} → {:+.1} |\n",
            preset.name,
            settings(voiced.original),
            settings(voiced.current),
            settings(voiced.voiced),
            change(before.strike_db, after.strike_db, false),
            change(before.whole_db, after.whole_db, false),
            change(before.feed_db, after.feed_db, true),
            pair(voiced.exact_feed_db, true),
            f64::from(preset.output_before) * OUTPUT_RANGE_DB,
            f64::from(preset.output_after) * OUTPUT_RANGE_DB,
        ));
    }
    text.push_str(&band_table(
        "\n## Remaining balance\n\n\
         Voiced output band levels minus 1.4.0's in dB at the strikes, averaged\n\
         over the recordings, at every other third-octave band and 16 kHz.",
        presets,
    ));
    text.push_str(
        "\n## Levels\n\n\
         After the Output change, each preset's integrated loudness and strike\n\
         level minus Init's, in dB, for the single coil / humbucker.\n\n\
         | Preset | Integrated | Strike |\n\
         |---|---|---|\n",
    );
    for preset in presets {
        let (integrated, strike) = (preset.levels.integrated, preset.levels.strike);
        text.push_str(&format!(
            "| {} | {} | {} |\n",
            preset.name,
            pair(
                [
                    integrated.single_coil - init.integrated.single_coil,
                    integrated.humbucker - init.integrated.humbucker,
                ],
                true
            ),
            pair(
                [
                    strike.single_coil - init.strike.single_coil,
                    strike.humbucker - init.strike.humbucker,
                ],
                true
            ),
        ));
    }
    text.push_str(&format!(
        "\nInit's integrated loudness is {:.1} / {:.1} LUFS and its strike level\n\
         {:.1} / {:.1} LUFS.\n\n\
         The Swanky Amp 1.4.0 build stays installable beside version 2 for\n\
         anyone who wants the original voicing exactly.\n",
        init.integrated.single_coil,
        init.integrated.humbucker,
        init.strike.single_coil,
        init.strike.humbucker,
    ));
    text
}

fn run() -> Result<(), String> {
    let released = read(&PathBuf::from(option("--presets")?))?;
    let report = PathBuf::from(option("--report")?);
    let factory = PathBuf::from(option("--factory")?);
    let clips = clips()?;
    // Without a bank there is nothing accepted to keep; any other failure
    // must stop the run rather than fall back to searching the tone controls.
    let current = match fs::read_to_string(&factory) {
        Ok(bank) => Some(bank),
        Err(error) if error.kind() == std::io::ErrorKind::NotFound => None,
        Err(error) => return Err(format!("{}: {error}", factory.display())),
    };
    let init = calibration::preset_levels(AmpControls::default(), &clips, LevelTables::CALIBRATED);
    let presets = voice_all(&released, current.as_deref(), &clips, init)?;
    let text = markdown(&presets, init);
    fs::write(&report, &text).map_err(|error| format!("{}: {error}", report.display()))?;
    fs::write(&factory, factory_bank(&released, &presets)?)
        .map_err(|error| format!("{}: {error}", factory.display()))?;
    print!("{text}");
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        eprintln!("refit-tone: {error}");
        std::process::exit(1);
    }
}
