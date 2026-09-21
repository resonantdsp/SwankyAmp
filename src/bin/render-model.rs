use std::collections::HashMap;
use std::env;
use std::fs;
use std::io::{self, Write};
use std::path::{Path, PathBuf};

use swanky_amp::dsp::amp::{AmpControls, AmpPath, SeamOutput};

const BLOCK_SIZE: usize = 512;

fn option(name: &str) -> Result<String, String> {
    let arguments: Vec<String> = env::args().collect();
    arguments
        .windows(2)
        .find(|pair| pair[0] == name)
        .map(|pair| pair[1].clone())
        .ok_or_else(|| format!("missing option: {name}"))
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

fn io_error(error: io::Error) -> String {
    error.to_string()
}

fn attribute<'a>(line: &'a str, name: &str) -> Option<&'a str> {
    let marker = format!("{name}=\"");
    let start = line.find(&marker)? + marker.len();
    let rest = &line[start..];
    Some(&rest[..rest.find('"')?])
}

fn preset(path: &Path, name: &str) -> Result<AmpControls, String> {
    let xml = fs::read_to_string(path).map_err(|error| format!("{}: {error}", path.display()))?;
    let marker = format!("<APVTSSwankyAmp presetName=\"{name}\">");
    let start = xml
        .find(&marker)
        .ok_or_else(|| format!("unknown preset: {name}"))?;
    let rest = &xml[start + marker.len()..];
    let body = &rest[..rest
        .find("</APVTSSwankyAmp>")
        .ok_or("unterminated preset")?];
    let values: HashMap<&str, f32> = body
        .lines()
        .filter_map(|line| {
            Some((
                attribute(line, "id")?,
                attribute(line, "value")?.parse().ok()?,
            ))
        })
        .collect();
    let get = |id: &str, fallback: f32| values.get(id).copied().unwrap_or(fallback);
    let mut controls = AmpControls::default();
    controls.output = get("idOutputLevel", controls.output);
    controls.low = get("idTsLow", controls.low);
    controls.mid = get("idTsMid", controls.mid);
    controls.high = get("idTsHigh", controls.high);
    controls.presence = get("idTsPresence", controls.presence);
    controls.tone_stack = get("idTsSelection", controls.tone_stack);
    controls.stages = get("idGainStages", controls.stages);
    controls.overhead = get("idGainOverhead", controls.overhead);
    controls.low_cut = get("idLowCut", controls.low_cut);
    controls.cabinet_brightness = get("idCabBrightness", controls.cabinet_brightness);
    controls.cabinet_distance = get("idCabDistance", controls.cabinet_distance);
    controls.cabinet_dynamic = get("idCabDynamic", controls.cabinet_dynamic);
    controls.preamp_drive = get("idPreAmpDrive", controls.preamp_drive);
    controls.preamp_tight = get("idPreAmpTight", controls.preamp_tight);
    controls.preamp_grit = get("idPreAmpGrit", controls.preamp_grit);
    controls.power_drive = get("idPowerAmpDrive", controls.power_drive);
    controls.power_tight = get("idPowerAmpTight", controls.power_tight);
    controls.power_sag = get("idPowerAmpSag", controls.power_sag);
    controls.power_sag_ratio = get("idPowerAmpSagRatio", controls.power_sag_ratio);
    Ok(controls)
}

fn write_seams(directory: &Path, sample_rate: u32, seams: SeamOutput) -> Result<(), String> {
    fs::create_dir_all(directory).map_err(|error| format!("{}: {error}", directory.display()))?;
    for (index, samples) in seams.triodes.iter().enumerate() {
        if !samples.is_empty() {
            write_wav(
                &directory.join(format!("triode_{}.wav", index + 1)),
                sample_rate,
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
            sample_rate,
            &samples,
        )?;
    }
    Ok(())
}

fn run() -> Result<(), String> {
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
    let controls = preset(&presets, &preset_name)?;
    let (input_rate, source) = read_wav(&input)?;
    let mut rendered = resample(&source, input_rate, sample_rate);
    let mut path = AmpPath::new(sample_rate as f32, controls);
    let mut seam_output = SeamOutput::with_capacity(rendered.len());
    for block in rendered.chunks_mut(BLOCK_SIZE) {
        if seams.is_some() {
            path.process_with_seams(block, &mut seam_output);
        } else {
            path.process(block);
        }
    }
    if rendered.iter().any(|sample| !sample.is_finite()) {
        return Err("model produced non-finite output".into());
    }
    write_wav(&output, sample_rate, &rendered)?;
    if let Some(directory) = seams {
        write_seams(&directory, sample_rate, seam_output)?;
    }
    Ok(())
}

fn main() {
    if let Err(error) = run() {
        eprintln!("render-model: {error}");
        std::process::exit(1);
    }
}
