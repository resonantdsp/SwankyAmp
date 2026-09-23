//! Long-run soak of the amplifier on stationary low-level input.
//!
//! Swanky Amp 1.2 was reported to "start sounding like a tremolo" after hours
//! of running (issue #34), and the Rust stages keep the same drift and
//! compression envelopes. Only hours of continuous audio can show whether that
//! state creeps, so this tool renders a long deterministic input as fast as
//! possible and records level, seam levels and envelope modulation per window.
//!
//! Two independent channels run side by side, as a stereo host would:
//! `noise` is stationary white noise at -40 dBFS RMS, and `pluck` adds a
//! decaying two-partial burst every two seconds to the same floor so the
//! drift and compression envelopes charge and release repeatedly. The input
//! never changes character, so any modulation or level change in the output
//! is the amplifier's.
//!
//! `soak run` writes one CSV row per window and channel, flushed as it goes,
//! and prints the verdict at the end. `soak check CSV...` prints the same
//! verdict from any set of CSVs, including runs still in progress.

use std::env;
use std::f64::consts::TAU;
use std::fs;
use std::io::{BufWriter, Write};
use std::path::{Path, PathBuf};
use std::time::Instant;

use swanky_amp::SwankyAmpParams;
use swanky_amp::dsp::amp::{AmpControls, AmpPath, CorrectedPath, SeamOutput};
use swanky_amp::engine::doublings_for;
use swanky_amp::presets;

const SAMPLE_RATE: u32 = 44_100;
/// One envelope frame per block keeps windows, blocks and the 100 Hz envelope
/// aligned exactly over hours of audio.
const BLOCK: usize = 441;
const ENVELOPE_RATE: f64 = SAMPLE_RATE as f64 / BLOCK as f64;
const NOISE_RMS: f64 = 0.01;
const PLUCK_PERIOD: u64 = 2 * SAMPLE_RATE as u64;
const PLUCK_PEAK: f64 = 0.1;
const PLUCK_DECAY_SECONDS: f64 = 0.25;
const PLUCK_HZ: f64 = 110.;
const MODULATION_BAND: (f64, f64) = (0.5, 15.);
const DRIFT_SPAN_SECONDS: f64 = 1_800.;
const HOUR_SPAN_SECONDS: f64 = 3_600.;
const BASELINE_SPAN_SECONDS: f64 = 600.;
const DRIFT_LIMIT_DB: f64 = 0.1;
/// Estimator noise on a stationary input moves the 10 s index by roughly 8%;
/// the relative margin keeps a 4-hour run from failing on that scatter alone
/// while a coherent tremolo of about 0.4 dB depth still exceeds it.
const MODULATION_MARGIN_RELATIVE: f64 = 0.25;
const MODULATION_MARGIN_ABSOLUTE: f64 = 0.005;
/// The shipping path plays the version 2 factory bank; the legacy path plays
/// the released bank it was voiced with.
const SHIPPING_PRESETS: &str = "presets/factory-2.0.xml";
const RELEASED_PRESETS: &str = "verification/reference/released/Resources/presets.xml";
const SEAMS: [&str; 9] = [
    "triode_1",
    "triode_2",
    "triode_3",
    "triode_4",
    "triode_5",
    "tone_stack",
    "power_amp",
    "cabinet",
    "output",
];
const SIGNALS: [Signal; 2] = [Signal::Noise, Signal::Pluck];

fn usage() -> String {
    "usage:\n  soak run --csv PATH [--preset NAME|init] [--presets XML] [--path corrected|legacy]\n           [--oversampling auto|1x|2x|4x]\n           [--hours H | --seconds S] [--window SECONDS] [--signal both|noise|pluck] [--seed N]\n  soak check CSV...".into()
}

fn option(arguments: &[String], name: &str) -> Option<String> {
    arguments
        .windows(2)
        .find(|pair| pair[0] == name)
        .map(|pair| pair[1].clone())
}

fn parsed<T: std::str::FromStr>(
    arguments: &[String],
    name: &str,
    fallback: T,
) -> Result<T, String> {
    option(arguments, name).map_or(Ok(fallback), |value| {
        value
            .parse()
            .map_err(|_| format!("invalid value for {name}: {value}"))
    })
}

#[derive(Clone, Copy, PartialEq)]
enum Signal {
    Noise,
    Pluck,
}

impl Signal {
    fn name(self) -> &'static str {
        match self {
            Self::Noise => "noise",
            Self::Pluck => "pluck",
        }
    }
}

/// Deterministic input: SplitMix64 white noise plus the optional pluck, both
/// derived from the absolute sample index so hours of audio never accumulate
/// phase error.
struct Source {
    signal: Signal,
    state: u64,
    frame: u64,
}

impl Source {
    fn new(signal: Signal, seed: u64) -> Self {
        Self {
            signal,
            state: seed
                ^ if signal == Signal::Noise {
                    0
                } else {
                    0x9e37_79b9
                },
            frame: 0,
        }
    }

    fn uniform(&mut self) -> f64 {
        self.state = self.state.wrapping_add(0x9e37_79b9_7f4a_7c15);
        let mut z = self.state;
        z = (z ^ (z >> 30)).wrapping_mul(0xbf58_476d_1ce4_e5b9);
        z = (z ^ (z >> 27)).wrapping_mul(0x94d0_49bb_1331_11eb);
        z ^= z >> 31;
        (z >> 11) as f64 / (1_u64 << 53) as f64 * 2. - 1.
    }

    fn fill(&mut self, block: &mut [f32]) {
        for sample in block {
            let mut value = self.uniform() * NOISE_RMS * 3_f64.sqrt();
            if self.signal == Signal::Pluck {
                let t = (self.frame % PLUCK_PERIOD) as f64 / f64::from(SAMPLE_RATE);
                let phase = TAU * PLUCK_HZ * t;
                value += PLUCK_PEAK
                    * (-t / PLUCK_DECAY_SECONDS).exp()
                    * (0.8 * phase.sin() + 0.2 * (2. * phase).sin());
            }
            *sample = value as f32;
            self.frame += 1;
        }
    }
}

enum Model {
    Corrected(Box<CorrectedPath>),
    Legacy(Box<AmpPath>),
}

impl Model {
    fn process(&mut self, block: &mut [f32], seams: &mut SeamOutput) {
        match self {
            Self::Corrected(path) => path.process_with_seams(block, seams),
            Self::Legacy(path) => path.process_with_seams(block, seams),
        }
    }
}

#[derive(Default)]
struct Level {
    energy: f64,
    count: u64,
}

impl Level {
    fn add(&mut self, samples: &[f32]) {
        self.energy += samples
            .iter()
            .map(|&sample| f64::from(sample) * f64::from(sample))
            .sum::<f64>();
        self.count += samples.len() as u64;
    }

    fn db(&self) -> Option<f64> {
        (self.count > 0).then(|| to_db((self.energy / self.count as f64).sqrt()))
    }
}

fn to_db(value: f64) -> f64 {
    20. * value.max(1e-30).log10()
}

struct Channel {
    signal: Signal,
    source: Source,
    model: Model,
    seam_output: SeamOutput,
    seams: [Level; 9],
    envelope: Vec<f64>,
    peak: f32,
    nonfinite: u64,
    subnormal: u64,
}

impl Channel {
    fn new(signal: Signal, seed: u64, model: Model) -> Self {
        Self {
            signal,
            source: Source::new(signal, seed),
            model,
            seam_output: SeamOutput::with_capacity(BLOCK * 4),
            seams: Default::default(),
            envelope: Vec::new(),
            peak: 0.,
            nonfinite: 0,
            subnormal: 0,
        }
    }

    fn process_block(&mut self, block: &mut [f32]) {
        self.source.fill(block);
        self.model.process(block, &mut self.seam_output);
        let output = &self.seam_output;
        let taps: [&[f32]; 9] = [
            &output.triodes[0],
            &output.triodes[1],
            &output.triodes[2],
            &output.triodes[3],
            &output.triodes[4],
            &output.tone_stack,
            &output.power_amp,
            &output.cabinet,
            block,
        ];
        for (level, samples) in self.seams.iter_mut().zip(taps) {
            level.add(samples);
            for &sample in samples {
                if !sample.is_finite() {
                    self.nonfinite += 1;
                } else if sample.is_subnormal() {
                    self.subnormal += 1;
                }
            }
        }
        let energy: f64 = block
            .iter()
            .map(|&sample| f64::from(sample) * f64::from(sample))
            .sum();
        self.envelope.push((energy / block.len() as f64).sqrt());
        self.peak = block
            .iter()
            .fold(self.peak, |peak, sample| peak.max(sample.abs()));
        let seams = &mut self.seam_output;
        for triode in &mut seams.triodes {
            triode.clear();
        }
        seams.tone_stack.clear();
        seams.power_amp.clear();
        seams.cabinet.clear();
        seams.raw_output.clear();
    }

    fn take_row(&mut self, end_seconds: f64, wall_seconds: f64) -> String {
        let modulation = modulation(&self.envelope, ENVELOPE_RATE);
        let mut row = format!(
            "{end_seconds:.1},{},{:.4},{:.4},{:.6},{:.6},{:.3},{},{}",
            self.signal.name(),
            self.seams[8].db().unwrap_or(f64::NAN),
            to_db(f64::from(self.peak)),
            modulation.index,
            modulation.peak,
            modulation.peak_hz,
            self.nonfinite,
            self.subnormal,
        );
        for level in &self.seams {
            row.push_str(&level.db().map_or(",".into(), |db| format!(",{db:.4}")));
        }
        row.push_str(&format!(",{wall_seconds:.3}"));
        self.seams = Default::default();
        self.envelope.clear();
        self.peak = 0.;
        self.nonfinite = 0;
        self.subnormal = 0;
        row
    }
}

struct Modulation {
    index: f64,
    peak: f64,
    peak_hz: f64,
}

/// Amplitude-modulation depth of an RMS envelope in the tremolo band.
///
/// `index` is the equivalent sinusoidal depth of all band energy relative to
/// the mean level, so a pure tremolo `1 + m cos(wt)` reads as `m`; `peak` is
/// the strongest single frequency's depth, which singles out a coherent
/// tremolo from broadband estimator noise.
fn modulation(envelope: &[f64], rate: f64) -> Modulation {
    let n = envelope.len();
    let none = Modulation {
        index: 0.,
        peak: 0.,
        peak_hz: 0.,
    };
    if n < 4 {
        return none;
    }
    let window: Vec<f64> = (0..n)
        .map(|i| 0.5 - 0.5 * (TAU * i as f64 / n as f64).cos())
        .collect();
    let window_sum: f64 = window.iter().sum();
    let window_energy: f64 = window.iter().map(|w| w * w).sum();
    let mean = envelope
        .iter()
        .zip(&window)
        .map(|(e, w)| e * w)
        .sum::<f64>()
        / window_sum;
    if mean <= 0. {
        return none;
    }
    let weighted: Vec<f64> = envelope
        .iter()
        .zip(&window)
        .map(|(e, w)| (e - mean) * w)
        .collect();
    let (cos, sin): (Vec<f64>, Vec<f64>) = (0..n)
        .map(|i| (TAU * i as f64 / n as f64).sin_cos())
        .map(|(s, c)| (c, s))
        .unzip();
    let resolution = rate / n as f64;
    let first = (MODULATION_BAND.0 / resolution).ceil().max(1.) as usize;
    let last = ((MODULATION_BAND.1 / resolution).floor() as usize).min(n / 2);
    let mut band_energy = 0.;
    let mut peak = (0., 0.);
    for k in first..=last {
        let (mut re, mut im) = (0., 0.);
        for (i, value) in weighted.iter().enumerate() {
            let t = (k * i) % n;
            re += value * cos[t];
            im -= value * sin[t];
        }
        let power = re * re + im * im;
        band_energy += power;
        let depth = 2. * power.sqrt() / window_sum / mean;
        if depth > peak.0 {
            peak = (depth, k as f64 * resolution);
        }
    }
    Modulation {
        index: 2. * (band_energy / (n as f64 * window_energy)).sqrt() / mean,
        peak: peak.0,
        peak_hz: peak.1,
    }
}

fn header() -> String {
    let mut header =
        "end_s,signal,rms_db,peak_db,mod_index,mod_peak,mod_peak_hz,nonfinite,subnormal"
            .to_string();
    for seam in SEAMS {
        header.push_str(&format!(",{seam}_db"));
    }
    header.push_str(",wall_s");
    header
}

fn controls(arguments: &[String], preset: &str, path: &str) -> Result<AmpControls, String> {
    if preset.eq_ignore_ascii_case("init") {
        return Ok(SwankyAmpParams::default().snapshot());
    }
    let bank = option(arguments, "--presets").unwrap_or_else(|| {
        if path == "legacy" {
            RELEASED_PRESETS
        } else {
            SHIPPING_PRESETS
        }
        .into()
    });
    let xml = fs::read_to_string(&bank).map_err(|error| format!("{bank}: {error}"))?;
    presets::controls(&xml, preset)
}

fn run(arguments: &[String]) -> Result<bool, String> {
    let csv = PathBuf::from(option(arguments, "--csv").ok_or_else(usage)?);
    let preset = option(arguments, "--preset").unwrap_or_else(|| "init".into());
    let path = option(arguments, "--path").unwrap_or_else(|| "corrected".into());
    let seconds = match option(arguments, "--seconds") {
        Some(_) => parsed(arguments, "--seconds", 0.)?,
        None => parsed(arguments, "--hours", 4.)? * 3_600.,
    };
    let window_seconds: f64 = parsed(arguments, "--window", 10.)?;
    let seed: u64 = parsed(arguments, "--seed", 1)?;
    let signals: Vec<Signal> = match option(arguments, "--signal").as_deref() {
        None | Some("both") => SIGNALS.to_vec(),
        Some("noise") => vec![Signal::Noise],
        Some("pluck") => vec![Signal::Pluck],
        Some(value) => return Err(format!("unknown signal: {value}")),
    };
    let frames_per_window = (window_seconds * ENVELOPE_RATE).round() as u64;
    if frames_per_window < 4 {
        return Err("window must be at least 0.04 s".into());
    }
    let windows = (seconds / window_seconds).round() as u64;
    if windows == 0 {
        return Err("duration must be at least one window".into());
    }
    let controls = controls(arguments, &preset, &path)?;
    let choice = match option(arguments, "--oversampling").as_deref() {
        None | Some("auto") => 0,
        Some("1x") => 1,
        Some("2x") => 2,
        Some("4x") => 3,
        Some(value) => return Err(format!("unknown oversampling choice: {value}")),
    };
    let doublings = doublings_for(choice, f64::from(SAMPLE_RATE));
    let factor = match path.as_str() {
        "corrected" => 1 << doublings,
        "legacy" => 1,
        value => return Err(format!("unknown path: {value}")),
    };
    let model = || match path.as_str() {
        "legacy" => Model::Legacy(Box::new(AmpPath::new_legacy(SAMPLE_RATE as f32, controls))),
        _ => Model::Corrected(Box::new(CorrectedPath::shipping(
            SAMPLE_RATE as f32,
            BLOCK,
            controls,
            doublings,
        ))),
    };
    let mut channels: Vec<Channel> = signals
        .iter()
        .map(|&signal| Channel::new(signal, seed, model()))
        .collect();

    if let Some(parent) = csv.parent() {
        fs::create_dir_all(parent).map_err(|error| format!("{}: {error}", parent.display()))?;
    }
    let file = fs::File::create(&csv).map_err(|error| format!("{}: {error}", csv.display()))?;
    let mut writer = BufWriter::new(file);
    let write_error = |error: std::io::Error| format!("{}: {error}", csv.display());
    writeln!(
        writer,
        "# preset={preset}\n# path={path}\n# sample_rate={SAMPLE_RATE}\n# factor={factor}\n# block={BLOCK}\n# seconds={:.1}\n# window_s={window_seconds}\n# seed={seed}\n# noise_rms_dbfs={:.1}\n# pluck_peak_dbfs={:.1}\n{}",
        windows as f64 * window_seconds,
        to_db(NOISE_RMS),
        to_db(PLUCK_PEAK),
        header()
    )
    .map_err(write_error)?;
    writer.flush().map_err(write_error)?;

    let started = Instant::now();
    let mut block = [0_f32; BLOCK];
    for window in 1..=windows {
        let window_started = Instant::now();
        for _ in 0..frames_per_window {
            for channel in &mut channels {
                channel.process_block(&mut block);
            }
        }
        let wall = window_started.elapsed().as_secs_f64();
        let end = window as f64 * frames_per_window as f64 / ENVELOPE_RATE;
        for channel in &mut channels {
            writeln!(writer, "{}", channel.take_row(end, wall)).map_err(write_error)?;
        }
        writer.flush().map_err(write_error)?;
    }
    writeln!(
        writer,
        "# finished wall_s={:.1}",
        started.elapsed().as_secs_f64()
    )
    .map_err(write_error)?;
    writer.flush().map_err(write_error)?;
    drop(writer);
    check(&[csv])
}

struct Row {
    end: f64,
    signal: String,
    rms_db: f64,
    mod_index: f64,
    mod_peak: f64,
    mod_peak_hz: f64,
    nonfinite: u64,
    subnormal: u64,
    seams: Vec<Option<f64>>,
    wall: f64,
}

struct Run {
    name: String,
    gated: bool,
    finished: bool,
    planned: f64,
    window: f64,
    rows: Vec<Row>,
}

fn load(path: &Path) -> Result<Run, String> {
    let text = fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let mut meta = std::collections::HashMap::new();
    let mut finished = false;
    let mut columns: Vec<String> = Vec::new();
    let mut rows = Vec::new();
    for line in text.lines() {
        if let Some(comment) = line.strip_prefix("# ") {
            if comment.starts_with("finished") {
                finished = true;
            } else if let Some((key, value)) = comment.split_once('=') {
                meta.insert(key.to_string(), value.to_string());
            }
            continue;
        }
        if columns.is_empty() {
            columns = line.split(',').map(str::to_string).collect();
            continue;
        }
        let fields: Vec<&str> = line.split(',').collect();
        if fields.len() != columns.len() {
            // A run still writing may leave its last line partial.
            continue;
        }
        let get = |name: &str| {
            columns
                .iter()
                .position(|column| column == name)
                .map(|index| fields[index])
                .ok_or_else(|| format!("{}: missing column {name}", path.display()))
        };
        let number = |name: &str| -> Result<f64, String> {
            get(name)?
                .parse()
                .map_err(|_| format!("{}: bad {name} value", path.display()))
        };
        rows.push(Row {
            end: number("end_s")?,
            signal: get("signal")?.to_string(),
            rms_db: number("rms_db")?,
            mod_index: number("mod_index")?,
            mod_peak: number("mod_peak")?,
            mod_peak_hz: number("mod_peak_hz")?,
            nonfinite: number("nonfinite")? as u64,
            subnormal: number("subnormal")? as u64,
            seams: SEAMS
                .iter()
                .map(|seam| get(&format!("{seam}_db")).map(|value| value.parse().ok()))
                .collect::<Result<_, _>>()?,
            wall: number("wall_s")?,
        });
    }
    let value = |key: &str| meta.get(key).cloned().unwrap_or_else(|| "?".into());
    let path_name = value("path");
    Ok(Run {
        name: format!("{} {} {}x", path_name, value("preset"), value("factor")),
        gated: path_name == "corrected",
        finished,
        planned: value("seconds").parse().unwrap_or(f64::NAN),
        window: value("window_s").parse().unwrap_or(10.),
        rows,
    })
}

/// Power-mean level in dB over rows ending within `(from, to]`.
fn mean_db(levels: &[(f64, f64)], from: f64, to: f64) -> Option<f64> {
    let selected: Vec<f64> = levels
        .iter()
        .filter(|(end, _)| *end > from + 1e-6 && *end <= to + 1e-6)
        .map(|(_, db)| 10_f64.powf(db / 10.))
        .collect();
    (!selected.is_empty())
        .then(|| 10. * (selected.iter().sum::<f64>() / selected.len() as f64).log10())
}

fn drift_db(levels: &[(f64, f64)], duration: f64, span: f64) -> Option<f64> {
    let span = span.min(duration / 2.);
    Some(mean_db(levels, duration - span, duration)? - mean_db(levels, 0., span)?)
}

fn format_db(value: Option<f64>) -> String {
    value.map_or("n/a".into(), |db| format!("{db:+.4}"))
}

/// Prints each run's summary and returns whether every gated run passes.
fn check(paths: &[PathBuf]) -> Result<bool, String> {
    let mut all_pass = true;
    for path in paths {
        let run = load(path)?;
        let status = if run.finished { "finished" } else { "running" };
        let first_minute: f64 = run
            .rows
            .iter()
            .filter(|row| row.end <= 60. + 1e-6)
            .map(|row| row.wall)
            .step_by(signal_count(&run))
            .sum();
        println!(
            "{} ({status}, {}; {:.0} of {:.0} s audio; first minute took {:.1} s wall)",
            run.name,
            path.display(),
            run.rows.last().map_or(0., |row| row.end),
            run.planned,
            first_minute
        );
        for signal in SIGNALS {
            let rows: Vec<&Row> = run
                .rows
                .iter()
                .filter(|row| row.signal == signal.name())
                .collect();
            let Some(last) = rows.last() else {
                continue;
            };
            let duration = last.end;
            let levels: Vec<(f64, f64)> = rows.iter().map(|row| (row.end, row.rms_db)).collect();
            let drift = drift_db(&levels, duration, DRIFT_SPAN_SECONDS);
            let hour_drift = drift_db(&levels, duration, HOUR_SPAN_SECONDS);
            let baseline_span = BASELINE_SPAN_SECONDS.min(duration / 3.).max(run.window);
            let baseline = rows
                .iter()
                .filter(|row| row.end <= baseline_span + 1e-6)
                .map(|row| row.mod_index)
                .fold(0., f64::max);
            let limit = baseline * (1. + MODULATION_MARGIN_RELATIVE) + MODULATION_MARGIN_ABSOLUTE;
            let worst = rows
                .iter()
                .max_by(|a, b| a.mod_index.total_cmp(&b.mod_index))
                .unwrap();
            let worst_peak = rows
                .iter()
                .max_by(|a, b| a.mod_peak.total_cmp(&b.mod_peak))
                .unwrap();
            let nonfinite: u64 = rows.iter().map(|row| row.nonfinite).sum();
            let subnormal: u64 = rows.iter().map(|row| row.subnormal).sum();
            let mut walls: Vec<f64> = rows.iter().map(|row| row.wall).collect();
            walls.sort_by(f64::total_cmp);
            let slowest = walls.last().copied().unwrap_or(0.) / walls[walls.len() / 2].max(1e-9);
            let seam_drifts: Vec<String> = SEAMS
                .iter()
                .enumerate()
                .filter_map(|(index, seam)| {
                    let levels: Vec<(f64, f64)> = rows
                        .iter()
                        .filter_map(|row| Some((row.end, row.seams[index]?)))
                        .collect();
                    (!levels.is_empty()).then(|| {
                        format!(
                            "{seam}={}",
                            format_db(drift_db(&levels, duration, DRIFT_SPAN_SECONDS))
                        )
                    })
                })
                .collect();
            let finite = nonfinite == 0;
            let steady = drift.is_some_and(|db| db.abs() <= DRIFT_LIMIT_DB);
            let unmodulated = worst.mod_index <= limit;
            let pass = finite && steady && unmodulated;
            let verdict = match (run.gated, pass, run.finished) {
                (false, _, _) => "CONTEXT",
                (true, false, _) => "FAIL",
                (true, true, true) => "PASS",
                (true, true, false) => "PASSING",
            };
            if run.gated && !pass {
                all_pass = false;
            }
            println!(
                "  {} nonfinite={nonfinite} subnormal={subnormal} rms_drift_30min_db={} rms_drift_1h_db={} max_modulation={:.4}@{:.0}s baseline_modulation={baseline:.4} modulation_limit={limit:.4} max_peak_modulation={:.4}@{:.2}Hz,{:.0}s slowest_window_vs_median={slowest:.2} verdict={verdict}",
                signal.name(),
                format_db(drift),
                format_db(hour_drift),
                worst.mod_index,
                worst.end,
                worst_peak.mod_peak,
                worst_peak.mod_peak_hz,
                worst_peak.end,
            );
            println!("    seam_drift_30min_db {}", seam_drifts.join(" "));
        }
    }
    Ok(all_pass)
}

fn signal_count(run: &Run) -> usize {
    let first = run.rows.first().map(|row| row.end);
    run.rows
        .iter()
        .take_while(|row| Some(row.end) == first)
        .count()
        .max(1)
}

fn main() {
    let arguments: Vec<String> = env::args().collect();
    let result = match arguments.get(1).map(String::as_str) {
        Some("run") => run(&arguments),
        Some("check") if arguments.len() > 2 => {
            check(&arguments[2..].iter().map(PathBuf::from).collect::<Vec<_>>())
        }
        _ => Err(usage()),
    };
    match result {
        Ok(true) => {}
        Ok(false) => std::process::exit(1),
        Err(error) => {
            eprintln!("soak: {error}");
            std::process::exit(2);
        }
    }
}
