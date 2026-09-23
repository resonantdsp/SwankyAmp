//! Refits the factory presets to the standard tone-stack mapping and writes
//! the version 2 factory bank with its residual report. `--check` proves the
//! committed files are what this tool produces. The bank also carries the
//! factory loudness balance, an Output change per preset. `--high-steps` measures the
//! committed bank with High moved, for listening comparisons.

use std::env;
use std::fs;
use std::path::{Path, PathBuf};

use serde::{Deserialize, Serialize};
use swanky_amp::dsp::calibration;
use swanky_amp::dsp::refit::{
    self, DRIVE_DEADBAND_DB, Measurement, POWER_DRIVE_LIMIT, PresetRefit, RESTRAINT, Residual,
    ToneSettings,
};
use swanky_amp::presets;

/// Cross-platform libm differences move measurements by far less than this;
/// a real change to the model or the fit moves them by more.
const CONTROL_TOLERANCE: f32 = 0.011;
const DB_TOLERANCE: f64 = 0.05;

/// Output change per factory preset in dB, chosen by ear on the single-coil
/// clip on September 23, 2026 to equalise the presets' RMS through the
/// shipping path. 1.4.0's bank was never balanced.
const FACTORY_BALANCE_DB: [(&str, f64); 10] = [
    ("clean", -0.3),
    ("bright", 0.3),
    ("edge", 0.8),
    ("distort", -2.2),
    ("dirty distort", 2.8),
    ("pre drive", -1.0),
    ("power drive", -2.2),
    ("full drive", -0.8),
    ("high gain", 1.5),
    ("level 11", 5.4),
];
/// The Output control spans -35..+35 dB over its stored -1..+1.
const OUTPUT_RANGE_DB: f64 = 35.;

#[derive(Debug, Serialize, Deserialize)]
struct Report {
    sample_rate: u32,
    pluck_seed: u32,
    pluck_notes: Vec<u8>,
    presets: Vec<PresetRefit>,
    balance: Vec<Balance>,
}

/// One preset's Output change and the level it produces on the single-coil
/// clip, with Output as stored before and after.
#[derive(Debug, Serialize, Deserialize)]
struct Balance {
    name: String,
    change_db: f64,
    output_before: f32,
    output_after: f32,
    rms_dbfs: f64,
}

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

fn write(path: &Path, contents: &str) -> Result<(), String> {
    if let Some(parent) = path.parent() {
        fs::create_dir_all(parent).map_err(|error| format!("{}: {error}", parent.display()))?;
    }
    fs::write(path, contents).map_err(|error| format!("{}: {error}", path.display()))
}

fn compute(xml: &str, clip: &[f32]) -> Result<Report, String> {
    let input = refit::pluck(refit::SAMPLE_RATE);
    let names = presets::names(xml);
    let controls = names
        .iter()
        .map(|name| presets::controls(xml, name))
        .collect::<Result<Vec<_>, _>>()?;
    let presets = std::thread::scope(|scope| {
        let handles: Vec<_> = names
            .iter()
            .zip(&controls)
            .map(|(name, controls)| {
                let input = &input;
                scope.spawn(move || refit::refit(name, *controls, input))
            })
            .collect();
        handles
            .into_iter()
            .map(|handle| handle.join().expect("refit thread panicked"))
            .collect::<Vec<_>>()
    });
    let balance = balance(xml, &factory_bank(xml, &presets)?, clip)?;
    Ok(Report {
        sample_rate: refit::SAMPLE_RATE,
        pluck_seed: refit::PLUCK_SEED,
        pluck_notes: refit::PLUCK_NOTES.to_vec(),
        presets,
        balance,
    })
}

fn balance_db(name: &str) -> Result<f64, String> {
    FACTORY_BALANCE_DB
        .iter()
        .find(|(preset, _)| *preset == name)
        .map(|(_, change)| *change)
        .ok_or_else(|| format!("no factory balance for {name}"))
}

/// Six decimals resolve Output to under 0.0001 dB, and match the bank the
/// balance was auditioned as.
fn balanced_output(output: f32, change_db: f64) -> String {
    let text = format!("{:.6}", f64::from(output) + change_db / OUTPUT_RANGE_DB);
    let text = text.trim_end_matches('0');
    if text.ends_with('.') {
        format!("{text}0")
    } else {
        text.to_owned()
    }
}

fn balance(released: &str, factory: &str, clip: &[f32]) -> Result<Vec<Balance>, String> {
    let names = presets::names(factory);
    let jobs = names
        .iter()
        .map(|name| {
            Ok((
                name,
                balance_db(name)?,
                presets::controls(released, name)?.output,
                presets::controls(factory, name)?,
            ))
        })
        .collect::<Result<Vec<_>, String>>()?;
    Ok(std::thread::scope(|scope| {
        let handles: Vec<_> = jobs
            .into_iter()
            .map(|(name, change_db, output_before, controls)| {
                scope.spawn(move || Balance {
                    name: name.clone(),
                    change_db,
                    output_before,
                    output_after: controls.output,
                    rms_dbfs: refit::output_rms_db(controls, clip),
                })
            })
            .collect();
        handles
            .into_iter()
            .map(|handle| handle.join().expect("balance thread panicked"))
            .collect()
    }))
}

fn xml_value(value: f32) -> String {
    if value.fract() == 0. {
        format!("{value:.1}")
    } else {
        format!("{value}")
    }
}

fn factory_bank(released: &str, presets: &[PresetRefit]) -> Result<String, String> {
    let mut xml = released.to_owned();
    for preset in presets {
        let (old, new) = (preset.original, preset.refit);
        let mut values: Vec<(&str, String)> = [
            ("idTsLow", old.low, new.low),
            ("idTsMid", old.mid, new.mid),
            ("idTsHigh", old.high, new.high),
            ("idPowerAmpDrive", old.power_drive, new.power_drive),
        ]
        .into_iter()
        .filter(|(_, old, new)| old != new)
        .map(|(id, _, new)| (id, xml_value(new)))
        .collect();
        let change_db = balance_db(&preset.name)?;
        if change_db != 0. {
            let output = presets::controls(released, &preset.name)?.output;
            values.push(("idOutputLevel", balanced_output(output, change_db)));
        }
        xml = presets::with_values(&xml, &preset.name, &values)?;
    }
    Ok(xml)
}

fn settings(settings: ToneSettings) -> String {
    format!(
        "{:+.2} / {:+.2} / {:+.2} / {:+.3}",
        settings.low, settings.mid, settings.high, settings.power_drive
    )
}

fn residual(residual: Residual) -> String {
    format!("{:.2} / {:+.2}", residual.shape_db, residual.level_db)
}

fn markdown(report: &Report) -> String {
    let mut text = String::from(
        "# Tone-stack refit\n\n\
         Generated by `just refit`; `just refit-check` proves it is current.\n\n\
         Version 2 discretises the tone stack with the standard bilinear constant\n\
         `2·SR`. Swanky Amp 1.4.0 used `SR`, which voiced every tone-stack\n\
         feature an octave above the circuit. The factory presets were voiced on\n\
         that octave-high stack, so they are refitted to sound roughly as they\n\
         did, not to replicate it: an exact match drives Low, Mid and High to\n\
         their limits.\n\n\
         ## Method\n\n",
    );
    text.push_str(&format!(
        "- Input: a Karplus-Strong pluck generated in code from seed `{:#010x}`, \
         one 0.5 s note at each of MIDI notes {:?}, peaking at the level of the \
         reference single-coil DI.\n\
         - Each preset is rendered through the shipping path at {} Hz with Auto \
         oversampling, once with the released mapping (the reference) and once \
         with the standard mapping.\n\
         - Measurements use 48 points log-spaced from 80 Hz to 8 kHz. Shape is \
         the band levels in dB about their mean; level is the total level. The \
         error is the mean-squared shape difference plus the squared level \
         difference, so one dB of level counts as one dB of shape. Moving Low, \
         Mid or High from the preset's setting adds {RESTRAINT} dB² per control \
         range squared, so a control moves only as far as the match improves: \
         without it most presets end with Mid near its maximum.\n\
         - Low, Mid and High are fitted on the tone-stack seam over a coarse \
         0.25 grid and two refinements to 0.01. The stack is linear and nothing \
         before it depends on its controls, so the seam for any setting is \
         predicted from the reference render and the ratio of the two stack \
         responses in slices of about 1/28 octave.\n\
         - Power Drive moves only when the fitted stack still changes the level \
         into the power stage by more than {DRIVE_DEADBAND_DB} dB, by bisection \
         on its gain curve and never by more than {POWER_DRIVE_LIMIT} of its \
         range.\n\
         - Every fitted preset is then rendered through the whole amplifier; the \
         table reports those renders against the reference.\n\n",
        report.pluck_seed, report.pluck_notes, report.sample_rate,
    ));
    text.push_str(
        "## Results\n\n\
         Controls are Low / Mid / High / Power Drive. Residuals are shape dB RMS\n\
         / level dB against the released mapping. Drive is the level change into\n\
         the power stage: the seam level plus Power Drive's gain change.\n\n\
         | Preset | Original | Refit | Seam unrefit | Seam refit | Drive refit dB | Output unrefit | Output refit | Limits |\n\
         |---|---|---|---|---|---|---|---|---|\n",
    );
    for preset in &report.presets {
        text.push_str(&format!(
            "| {} | {} | {} | {} | {} | {:+.2} | {} | {} | {} |\n",
            preset.name,
            settings(preset.original),
            settings(preset.refit),
            residual(preset.unrefit.tone_stack),
            residual(preset.refitted.tone_stack),
            preset.refitted.drive_db,
            residual(preset.unrefit.output),
            residual(preset.refitted.output),
            if preset.limits.is_empty() {
                "none".to_owned()
            } else {
                preset.limits.join(", ")
            },
        ));
    }
    let limited: Vec<&str> = report
        .presets
        .iter()
        .filter(|preset| !preset.limits.is_empty())
        .map(|preset| preset.name.as_str())
        .collect();
    let worst = |select: fn(&PresetRefit) -> f64| {
        report
            .presets
            .iter()
            .map(|preset| (select(preset), preset.name.as_str()))
            .fold(
                (0., ""),
                |worst, item| if item.0 > worst.0 { item } else { worst },
            )
    };
    let (seam_shape, seam_case) = worst(|preset| preset.refitted.tone_stack.shape_db);
    let (drive, drive_case) = worst(|preset| preset.refitted.drive_db.abs());
    let (output_shape, output_case) = worst(|preset| preset.refitted.output.shape_db);
    let (output_level, output_level_case) = worst(|preset| preset.refitted.output.level_db.abs());
    text.push_str(&balance_markdown(&report.balance));
    text.push_str(&format!(
        "\n## Summary\n\n\
         - Worst seam shape residual: {seam_shape:.2} dB RMS ({seam_case}).\n\
         - Worst drive change into the power stage: {drive:.2} dB ({drive_case}).\n\
         - Worst output shape residual: {output_shape:.2} dB RMS ({output_case}).\n\
         - Worst output level change: {output_level:.2} dB ({output_level_case}).\n\
         - Presets with a control at a limit: {}.\n\n\
         The Swanky Amp 1.4.0 build stays installable beside version 2 for\n\
         anyone who wants the original voicing exactly.\n",
        if limited.is_empty() {
            "none".to_owned()
        } else {
            limited.join(", ")
        },
    ));
    text
}

fn balance_markdown(balance: &[Balance]) -> String {
    let mut text = format!(
        "\n## Factory balance\n\n\
         Swanky Amp 1.4.0's factory presets were never balanced for loudness.\n\
         Version 2 moves each preset's Output by the change below, chosen by ear\n\
         on the single-coil clip on September 23, 2026 to equalise the presets'\n\
         RMS. Output stores -1..+1 for -35..+35 dB. RMS is the output on the\n\
         single-coil DI through the shipping path at {} Hz with Auto\n\
         oversampling, from an amplifier settled on a second of silence, over the\n\
         clip and half a second of tail. The balance holds for this clip: on the\n\
         sparser pluck the drive presets, which compress it harder, measure\n\
         quieter than the clean ones.\n\n\
         | Preset | Output change dB | Output before → after dB | RMS dBFS |\n\
         |---|---|---|---|\n",
        refit::BALANCE_SAMPLE_RATE,
    );
    for preset in balance {
        text.push_str(&format!(
            "| {} | {:+.1} | {:+.2} → {:+.2} | {:.2} |\n",
            preset.name,
            preset.change_db,
            f64::from(preset.output_before) * OUTPUT_RANGE_DB,
            f64::from(preset.output_after) * OUTPUT_RANGE_DB,
            preset.rms_dbfs,
        ));
    }
    let levels = balance.iter().map(|preset| preset.rms_dbfs);
    let (quietest, loudest) = levels
        .fold((f64::INFINITY, f64::NEG_INFINITY), |(low, high), level| {
            (low.min(level), high.max(level))
        });
    text.push_str(&format!(
        "\nSpread: {:.2} dB, from {quietest:.2} to {loudest:.2} dBFS.\n",
        loudest - quietest
    ));
    text
}

fn close(left: f64, right: f64, tolerance: f64) -> bool {
    (left - right).abs() <= tolerance
}

fn compare(committed: &Report, fresh: &Report) -> Vec<String> {
    let mut failures = Vec::new();
    if committed.presets.len() != fresh.presets.len() {
        failures.push("preset count differs".into());
    }
    for (old, new) in committed.presets.iter().zip(&fresh.presets) {
        let controls = [
            (old.refit.low, new.refit.low),
            (old.refit.mid, new.refit.mid),
            (old.refit.high, new.refit.high),
            (old.refit.power_drive, new.refit.power_drive),
        ];
        if old.name != new.name
            || old.original != new.original
            || controls
                .iter()
                .any(|(old, new)| (old - new).abs() > CONTROL_TOLERANCE)
        {
            failures.push(format!(
                "{}: refit {} is now {}",
                old.name,
                settings(old.refit),
                settings(new.refit)
            ));
            continue;
        }
        for (label, before, after) in [
            ("unrefit", old.unrefit, new.unrefit),
            ("refitted", old.refitted, new.refitted),
        ] {
            let pairs = [
                (before.tone_stack.shape_db, after.tone_stack.shape_db),
                (before.tone_stack.level_db, after.tone_stack.level_db),
                (before.drive_db, after.drive_db),
                (before.output.shape_db, after.output.shape_db),
                (before.output.level_db, after.output.level_db),
            ];
            if pairs
                .iter()
                .any(|(before, after)| !close(*before, *after, DB_TOLERANCE))
            {
                failures.push(format!("{}: {label} residuals moved", old.name));
            }
        }
    }
    if committed.balance.len() != fresh.balance.len() {
        failures.push("balanced preset count differs".into());
    }
    for (old, new) in committed.balance.iter().zip(&fresh.balance) {
        if old.name != new.name
            || old.change_db != new.change_db
            || old.output_before != new.output_before
            || old.output_after != new.output_after
        {
            failures.push(format!("{}: factory balance changed", old.name));
        } else if !close(old.rms_dbfs, new.rms_dbfs, DB_TOLERANCE) {
            failures.push(format!(
                "{}: balanced RMS {:.2} dBFS is now {:.2}",
                old.name, old.rms_dbfs, new.rms_dbfs
            ));
        }
    }
    failures
}

#[derive(Serialize)]
struct Variant {
    variant: String,
    high: f32,
    measurement: Measurement,
}

#[derive(Serialize)]
struct PresetVariants {
    name: String,
    variants: Vec<Variant>,
}

/// Each step is a signed change to the refitted High or `orig` for the
/// released value; `as-is` always comes first.
fn high_variants(released: &str, factory: &str, steps: &str) -> Result<String, String> {
    let input = refit::pluck(refit::SAMPLE_RATE);
    let steps: Vec<&str> = std::iter::once("as-is")
        .chain(
            steps
                .split(',')
                .map(str::trim)
                .filter(|step| !step.is_empty()),
        )
        .collect();
    let mut jobs = Vec::new();
    for name in presets::names(released) {
        let original = presets::controls(released, &name)?;
        let fitted = presets::controls(factory, &name)?;
        let highs = steps
            .iter()
            .map(|step| match *step {
                "as-is" => Ok(fitted.high),
                "orig" => Ok(original.high),
                step => step
                    .parse::<f32>()
                    .map(|change| (fitted.high + change).clamp(-1., 1.))
                    .map_err(|_| format!("unknown High step: {step}")),
            })
            .collect::<Result<Vec<_>, _>>()?;
        jobs.push((name, original, fitted, highs));
    }
    let presets: Vec<PresetVariants> = std::thread::scope(|scope| {
        let handles: Vec<_> = jobs
            .iter()
            .map(|(name, original, fitted, highs)| {
                let (input, steps) = (&input, &steps);
                scope.spawn(move || {
                    let candidates: Vec<_> = highs
                        .iter()
                        .map(|&high| swanky_amp::dsp::amp::AmpControls { high, ..*fitted })
                        .collect();
                    let measurements = refit::measure_candidates(*original, &candidates, input);
                    PresetVariants {
                        name: name.clone(),
                        variants: steps
                            .iter()
                            .zip(highs)
                            .zip(measurements)
                            .map(|((step, high), measurement)| Variant {
                                variant: (*step).to_owned(),
                                high: *high,
                                measurement,
                            })
                            .collect(),
                    }
                })
            })
            .collect();
        handles
            .into_iter()
            .map(|handle| handle.join().expect("measurement thread panicked"))
            .collect()
    });
    serde_json::to_string_pretty(&presets).map_err(|error| error.to_string())
}

fn run() -> Result<(), String> {
    if let Ok(steps) = option("--high-steps") {
        let released = read(&PathBuf::from(option("--presets")?))?;
        let factory = read(&PathBuf::from(option("--factory")?))?;
        println!("{}", high_variants(&released, &factory, &steps)?);
        return Ok(());
    }
    let presets_path = PathBuf::from(option("--presets")?);
    let report_dir = PathBuf::from(option("--report-dir")?);
    let factory_path = PathBuf::from(option("--factory")?);
    let json_path = report_dir.join("refit.json");
    let markdown_path = report_dir.join("refit-report.md");
    let released = read(&presets_path)?;
    let clip_path = option("--clip")?;
    let clip_bytes = fs::read(&clip_path).map_err(|error| format!("{clip_path}: {error}"))?;
    let clip = calibration::clip(&clip_bytes)?;

    if env::args().any(|argument| argument == "--check") {
        let committed: Report = serde_json::from_str(&read(&json_path)?)
            .map_err(|error| format!("{}: {error}", json_path.display()))?;
        let mut failures = Vec::new();
        if read(&markdown_path)? != markdown(&committed) {
            failures.push(format!(
                "{} is not generated from refit.json",
                markdown_path.display()
            ));
        }
        if read(&factory_path)? != factory_bank(&released, &committed.presets)? {
            failures.push(format!(
                "{} is not generated from refit.json",
                factory_path.display()
            ));
        }
        failures.extend(compare(&committed, &compute(&released, &clip)?));
        if !failures.is_empty() {
            return Err(format!(
                "refit is stale; run `just refit`:\n  {}",
                failures.join("\n  ")
            ));
        }
        println!("tone-stack refit is current");
        return Ok(());
    }

    let report = compute(&released, &clip)?;
    let json = serde_json::to_string_pretty(&report).map_err(|error| error.to_string())? + "\n";
    write(&json_path, &json)?;
    write(&markdown_path, &markdown(&report))?;
    write(&factory_path, &factory_bank(&released, &report.presets)?)?;
    print!("{}", markdown(&report));
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        eprintln!("refit-tone: {error}");
        std::process::exit(1);
    }
}
