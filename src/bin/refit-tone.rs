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
use swanky_amp::dsp::refit::{self, FEED_COST, RAIL, VOICING_RESTRAINT, Voiced, Voicing};
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

/// Voices every 1.4.0 factory preset, keeping the tone controls of the
/// accepted bank `current`, when given.
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
                .map(|bank| [bank.low, bank.mid, bank.high, bank.presence]);
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
        "{:.1} / {:.1} / {:.1} / {:.1} / {:.2}",
        knob(voicing.low),
        knob(voicing.mid),
        knob(voicing.high),
        knob(voicing.presence),
        knob(voicing.power_drive)
    )
}

fn pair(values: [f64; 2], signed: bool) -> String {
    if signed {
        format!("{:+.1} / {:+.1}", values[0], values[1])
    } else {
        format!("{:.1} / {:.1}", values[0], values[1])
    }
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
         - Balance is the output's third-octave band levels from 80 Hz to 8 kHz,\n\
           each render's bands taken about their own mean, so level does not\n\
           count. The error is the mean squared band difference from 1.4.0,\n\
           averaged over the recordings.\n\
         - Low, Mid, High and Presence keep the values of the bank being\n\
           rewritten, the voicing accepted by ear. Only for a preset it lacks are\n\
           they searched, from the 1.4.0 settings in\n\
           steps of 1, 0.5, 0.25 and 0.125 on the 0 to 10 scale. Moving a\n\
           control costs {VOICING_RESTRAINT} dB² per half range squared, and the\n\
           controls stay within {:.0} to {:.0}, so presets leave room either way.\n\
         - For every candidate, Power Drive is set so the power stage's input\n\
           level, averaged over the recordings, matches 1.4.0's. Where Power\n\
           Drive runs out of range, the miss costs {FEED_COST} dB² per dB².\n\
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
         to 10 scale. Balance is the RMS band difference from 1.4.0 in dB and\n\
         feed is the power stage's input level minus 1.4.0's in dB, each for the\n\
         single coil / humbucker. Unvoiced is version 2 with the 1.4.0 settings.\n\
         Output is 1.4.0's and then version 2's, in dB.\n\n\
         | Preset | 1.4.0 | Voiced | Balance unvoiced | Balance voiced | Feed unvoiced | Feed voiced | Output dB |\n\
         |---|---|---|---|---|---|---|---|\n",
        calibration::SAMPLE_RATE,
        knob(-RAIL),
        knob(RAIL),
    );
    for preset in presets {
        let voiced = &preset.voiced;
        text.push_str(&format!(
            "| {} | {} | {} | {} | {} | {} | {} | {:+.1} → {:+.1} |\n",
            preset.name,
            settings(voiced.original),
            settings(voiced.voiced),
            pair(voiced.unvoiced_balance_db, false),
            pair(voiced.voiced_balance_db, false),
            pair(voiced.unvoiced_feed_db, true),
            pair(voiced.voiced_feed_db, true),
            f64::from(preset.output_before) * OUTPUT_RANGE_DB,
            f64::from(preset.output_after) * OUTPUT_RANGE_DB,
        ));
    }
    text.push_str(
        "\n## Remaining balance\n\n\
         Voiced output band levels minus 1.4.0's in dB, averaged over the\n\
         recordings, at every other third-octave band.\n\n",
    );
    let centres = refit::band_centres();
    let shown: Vec<usize> = (0..centres.len()).step_by(2).collect();
    text.push_str("| Preset |");
    for &band in &shown {
        text.push_str(&format!(" {:.0} |", centres[band]));
    }
    text.push_str("\n|---|");
    text.push_str(&"---|".repeat(shown.len()));
    text.push('\n');
    for preset in presets {
        text.push_str(&format!("| {} |", preset.name));
        for &band in &shown {
            text.push_str(&format!(" {:+.1} |", preset.voiced.voiced_bands_db[band]));
        }
        text.push('\n');
    }
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
