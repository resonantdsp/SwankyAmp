use std::env;
use std::fs;
use std::io::{self, Write};
use std::path::{Path, PathBuf};

use swanky_amp::dsp::amp::{
    AmpControls, AmpPath, ClipKnee, CorrectedPath, LevelTables, SeamOutput, ToneMapping,
};
use swanky_amp::dsp::diagnostics::reset_equilibrium;
use swanky_amp::dsp::refit;
use swanky_amp::engine::doublings_for;
use swanky_amp::presets;

const BLOCK_SIZE: usize = 512;

fn option(name: &str) -> Result<String, String> {
    let arguments: Vec<String> = env::args().collect();
    arguments
        .windows(2)
        .find(|pair| pair[0] == name)
        .map(|pair| pair[1].clone())
        .ok_or_else(|| format!("missing option: {name}"))
}

fn optional_option(name: &str) -> Option<String> {
    let arguments: Vec<String> = env::args().collect();
    arguments
        .windows(2)
        .find(|pair| pair[0] == name)
        .map(|pair| pair[1].clone())
}

fn flag(name: &str) -> bool {
    env::args().any(|argument| argument == name)
}

fn read_u16(bytes: &[u8], offset: usize) -> Result<u16, String> {
    let value = bytes
        .get(offset..offset + 2)
        .ok_or("truncated WAV")?
        .try_into()
        .map_err(|_| "truncated WAV")?;
    Ok(u16::from_le_bytes(value))
}

fn read_u32(bytes: &[u8], offset: usize) -> Result<u32, String> {
    let value = bytes
        .get(offset..offset + 4)
        .ok_or("truncated WAV")?
        .try_into()
        .map_err(|_| "truncated WAV")?;
    Ok(u32::from_le_bytes(value))
}

fn read_wav(path: &Path) -> Result<(u32, Vec<f32>), String> {
    let bytes = fs::read(path).map_err(|error| format!("{}: {error}", path.display()))?;
    if bytes.get(0..4) != Some(b"RIFF") || bytes.get(8..12) != Some(b"WAVE") {
        return Err("input is not a RIFF/WAVE file".into());
    }
    let mut offset = 12;
    let mut format = None;
    let mut data = None;
    while offset + 8 <= bytes.len() {
        let id = &bytes[offset..offset + 4];
        let size = read_u32(&bytes, offset + 4)? as usize;
        let start = offset + 8;
        let end = start.checked_add(size).ok_or("WAV chunk is too large")?;
        if end > bytes.len() {
            return Err("truncated WAV chunk".into());
        }
        if id == b"fmt " {
            format = Some((
                read_u16(&bytes, start)?,
                read_u16(&bytes, start + 2)?,
                read_u32(&bytes, start + 4)?,
                read_u16(&bytes, start + 14)?,
            ));
        } else if id == b"data" {
            data = Some(&bytes[start..end]);
        }
        offset = end + (size & 1);
    }
    let (encoding, channels, sample_rate, bits) = format.ok_or("WAV has no format chunk")?;
    let data = data.ok_or("WAV has no data chunk")?;
    if (encoding, channels, bits) != (1, 1, 24) {
        return Err("input must be mono 24-bit PCM WAV".into());
    }
    let samples = data
        .chunks_exact(3)
        .map(|bytes| {
            let mut value =
                i32::from(bytes[0]) | (i32::from(bytes[1]) << 8) | (i32::from(bytes[2]) << 16);
            if value & 0x80_0000 != 0 {
                value |= !0xff_ffff;
            }
            value as f32 / 8_388_608.
        })
        .collect();
    Ok((sample_rate, samples))
}

fn resample(input: &[f32], input_rate: u32, output_rate: u32) -> Vec<f32> {
    if input_rate == output_rate {
        return input.to_vec();
    }
    let frames =
        ((input.len() as f64 * f64::from(output_rate) / f64::from(input_rate)).round()) as usize;
    (0..frames)
        .map(|frame| {
            let position = frame as f64 * f64::from(input_rate) / f64::from(output_rate);
            let lower = position as usize;
            let upper = (lower + 1).min(input.len() - 1);
            let fraction = (position - lower as f64) as f32;
            input[lower] + fraction * (input[upper] - input[lower])
        })
        .collect()
}

fn write_wav(path: &Path, sample_rate: u32, samples: &[f32]) -> Result<(), String> {
    let mut output =
        fs::File::create(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let size = u32::try_from(samples.len() * 4).map_err(|_| "output WAV is too large")?;
    output.write_all(b"RIFF").map_err(io_error)?;
    output
        .write_all(&(36 + size).to_le_bytes())
        .map_err(io_error)?;
    output.write_all(b"WAVEfmt ").map_err(io_error)?;
    output.write_all(&16_u32.to_le_bytes()).map_err(io_error)?;
    output.write_all(&3_u16.to_le_bytes()).map_err(io_error)?;
    output.write_all(&1_u16.to_le_bytes()).map_err(io_error)?;
    output
        .write_all(&sample_rate.to_le_bytes())
        .map_err(io_error)?;
    output
        .write_all(&(sample_rate * 4).to_le_bytes())
        .map_err(io_error)?;
    output.write_all(&4_u16.to_le_bytes()).map_err(io_error)?;
    output.write_all(&32_u16.to_le_bytes()).map_err(io_error)?;
    output.write_all(b"data").map_err(io_error)?;
    output.write_all(&size.to_le_bytes()).map_err(io_error)?;
    for sample in samples {
        output.write_all(&sample.to_le_bytes()).map_err(io_error)?;
    }
    Ok(())
}

fn write_pcm24_wav(path: &Path, sample_rate: u32, samples: &[f32]) -> Result<(), String> {
    let size = u32::try_from(samples.len() * 3).map_err(|_| "output WAV is too large")?;
    let mut bytes = Vec::with_capacity(44 + samples.len() * 3);
    bytes.extend_from_slice(b"RIFF");
    bytes.extend_from_slice(&(36 + size + (size & 1)).to_le_bytes());
    bytes.extend_from_slice(b"WAVEfmt ");
    bytes.extend_from_slice(&16_u32.to_le_bytes());
    bytes.extend_from_slice(&1_u16.to_le_bytes());
    bytes.extend_from_slice(&1_u16.to_le_bytes());
    bytes.extend_from_slice(&sample_rate.to_le_bytes());
    bytes.extend_from_slice(&(sample_rate * 3).to_le_bytes());
    bytes.extend_from_slice(&3_u16.to_le_bytes());
    bytes.extend_from_slice(&24_u16.to_le_bytes());
    bytes.extend_from_slice(b"data");
    bytes.extend_from_slice(&size.to_le_bytes());
    for sample in samples {
        let value = (f64::from(*sample) * 8_388_608.).round() as i32;
        bytes.extend_from_slice(&value.clamp(-8_388_608, 8_388_607).to_le_bytes()[..3]);
    }
    if size & 1 == 1 {
        bytes.push(0);
    }
    fs::write(path, bytes).map_err(|error| format!("{}: {error}", path.display()))
}

fn io_error(error: io::Error) -> String {
    error.to_string()
}

fn preset(path: &Path, name: &str) -> Result<AmpControls, String> {
    let xml = fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))?;
    presets::controls(&xml, name)
}

fn write_seams(
    directory: &Path,
    host_rate: u32,
    tube_rate: u32,
    seams: SeamOutput,
) -> Result<(), String> {
    fs::create_dir_all(directory).map_err(|error| format!("{}: {error}", directory.display()))?;
    for (index, samples) in seams.triodes.iter().enumerate() {
        if !samples.is_empty() {
            write_wav(
                &directory.join(format!("triode_{}.wav", index + 1)),
                tube_rate,
                samples,
            )?;
        }
    }
    for (name, samples) in [
        ("tone_stack", seams.tone_stack),
        ("power_amp", seams.power_amp),
        ("cabinet", seams.cabinet),
        ("raw_output", seams.raw_output),
    ] {
        write_wav(
            &directory.join(format!("{name}.wav")),
            if matches!(name, "cabinet" | "raw_output") {
                host_rate
            } else {
                tube_rate
            },
            &samples,
        )?;
    }
    Ok(())
}

fn run() -> Result<(), String> {
    // The refit's pluck as a 24-bit file, so the C++ reference renderer and
    // listening comparisons can play the same input the refit measured.
    if let Some(path) = optional_option("--write-pluck") {
        let path = PathBuf::from(path);
        return write_pcm24_wav(&path, refit::SAMPLE_RATE, &refit::pluck(refit::SAMPLE_RATE));
    }
    let input = PathBuf::from(option("--input")?);
    let presets = PathBuf::from(option("--presets")?);
    let preset_name = option("--preset")?;
    let sample_rate: u32 = option("--sample-rate")?
        .parse()
        .map_err(|_| "sample rate must be an integer")?;
    if !(8_000..=384_000).contains(&sample_rate) {
        return Err("sample rate must be between 8000 and 384000 Hz".into());
    }
    let output = PathBuf::from(option("--output")?);
    let seams = env::args()
        .collect::<Vec<_>>()
        .windows(2)
        .find(|pair| pair[0] == "--seams-dir")
        .map(|pair| PathBuf::from(&pair[1]));
    let mut controls = preset(&presets, &preset_name)?;
    if flag("--cabinet-off") {
        controls.cabinet_on = false;
    }
    if let Some(high) = optional_option("--high") {
        controls.high = high
            .parse::<f32>()
            .map_err(|_| "High must be a number")?
            .clamp(-1., 1.);
    }
    if flag("--reset-audit") {
        let choice = match optional_option("--oversampling")
            .as_deref()
            .unwrap_or("auto")
        {
            "auto" => 0,
            "1x" => 1,
            "2x" => 2,
            "4x" => 3,
            value => return Err(format!("unknown oversampling choice: {value}")),
        };
        let doublings = doublings_for(choice, f64::from(sample_rate));
        let audit = reset_equilibrium(sample_rate as f32, controls, doublings);
        fs::write(
            &output,
            format!(
                "{{\n  \"preset\": \"{preset_name}\",\n  \"sample_rate\": {sample_rate},\n  \"factor\": {},\n  \"max_error\": {:.9},\n  \"rms_error\": {:.9},\n  \"stale_max_error\": {:.9}\n}}\n",
                1 << doublings,
                audit.max_error,
                audit.rms_error,
                audit.stale_max_error,
            ),
        )
        .map_err(|error| format!("{}: {error}", output.display()))?;
        return Ok(());
    }
    let (input_rate, source) = read_wav(&input)?;
    let mut rendered = resample(&source, input_rate, sample_rate);
    if let Some(gain_db) = optional_option("--input-gain-db") {
        let gain_db: f32 = gain_db
            .parse()
            .map_err(|_| "input gain must be a number of decibels")?;
        let gain = 10_f32.powf(gain_db / 20.);
        for sample in &mut rendered {
            *sample *= gain;
        }
    }
    let mut seam_output = SeamOutput::with_capacity(rendered.len());
    let model = optional_option("--model").unwrap_or_else(|| "legacy".into());
    let oversampling = || match optional_option("--oversampling")
        .as_deref()
        .unwrap_or("auto")
    {
        "auto" => Ok(0),
        "1x" => Ok(1),
        "2x" => Ok(2),
        "4x" => Ok(3),
        value => Err(format!("unknown oversampling choice: {value}")),
    };
    let (factor, latency) = if model == "legacy" {
        let mut path = AmpPath::new_legacy(sample_rate as f32, controls);
        for block in rendered.chunks_mut(BLOCK_SIZE) {
            if seams.is_some() {
                path.process_with_seams(block, &mut seam_output);
            } else {
                path.process(block);
            }
        }
        (1, 0)
    } else if model == "shipping" {
        let doublings = doublings_for(oversampling()?, f64::from(sample_rate));
        let mut path = CorrectedPath::shipping(sample_rate as f32, BLOCK_SIZE, controls, doublings);
        for block in rendered.chunks_mut(BLOCK_SIZE) {
            if seams.is_some() {
                path.process_with_seams(block, &mut seam_output);
            } else {
                path.process(block);
            }
        }
        (path.factor(), path.latency())
    } else if model == "corrected" {
        let doublings = doublings_for(oversampling()?, f64::from(sample_rate));
        let tone_mapping = match optional_option("--tone-mapping")
            .as_deref()
            .unwrap_or("standard")
        {
            "standard" => ToneMapping::Standard,
            "released" => ToneMapping::Released,
            value => return Err(format!("unknown tone mapping: {value}")),
        };
        let knee = match optional_option("--knee").as_deref().unwrap_or("unit") {
            "unit" => ClipKnee::UnitSlope,
            "released" => ClipKnee::Released,
            value => return Err(format!("unknown knee: {value}")),
        };
        let tables = match optional_option("--tables")
            .as_deref()
            .unwrap_or("calibrated")
        {
            "calibrated" => LevelTables::CALIBRATED,
            "released" => LevelTables::RELEASED,
            value => return Err(format!("unknown level tables: {value}")),
        };
        let mut path = CorrectedPath::new(
            sample_rate as f32,
            BLOCK_SIZE,
            controls,
            doublings,
            tone_mapping,
            knee,
            tables,
        );
        for block in rendered.chunks_mut(BLOCK_SIZE) {
            if seams.is_some() {
                path.process_with_seams(block, &mut seam_output);
            } else {
                path.process(block);
            }
        }
        (path.factor(), path.latency())
    } else {
        return Err(format!("unknown model: {model}"));
    };
    if rendered.iter().any(|sample| !sample.is_finite()) {
        return Err("model produced non-finite output".into());
    }
    write_wav(&output, sample_rate, &rendered)?;
    if let Some(directory) = seams {
        write_seams(
            &directory,
            sample_rate,
            sample_rate * factor as u32,
            seam_output,
        )?;
    }
    if let Some(report) = optional_option("--report") {
        fs::write(
            &report,
            format!(
                "{{\n  \"model\": \"{model}\",\n  \"sample_rate\": {sample_rate},\n  \"factor\": {factor},\n  \"internal_rate\": {},\n  \"latency_samples\": {latency}\n}}\n",
                sample_rate * factor as u32,
            ),
        )
        .map_err(|error| format!("{report}: {error}"))?;
    }
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        eprintln!("render-model: {error}");
        std::process::exit(1);
    }
}
