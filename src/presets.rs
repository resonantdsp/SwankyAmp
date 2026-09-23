//! The 1.x preset XML: `<presets>` holding one `<APVTSSwankyAmp presetName>`
//! element per preset, each a list of `<PARAM id value/>` entries. Version 2
//! keeps this schema for its factory bank so 1.4 presets and 2.0 presets are
//! read by the same importer.

use std::collections::HashMap;

use crate::dsp::amp::AmpControls;

fn attribute<'a>(line: &'a str, name: &str) -> Option<&'a str> {
    let marker = format!("{name}=\"");
    let start = line.find(&marker)? + marker.len();
    let rest = &line[start..];
    Some(&rest[..rest.find('"')?])
}

fn body<'a>(xml: &'a str, name: &str) -> Result<(usize, &'a str), String> {
    let marker = format!("<APVTSSwankyAmp presetName=\"{name}\">");
    let start = xml
        .find(&marker)
        .ok_or_else(|| format!("unknown preset: {name}"))?
        + marker.len();
    let rest = &xml[start..];
    let end = rest
        .find("</APVTSSwankyAmp>")
        .ok_or("unterminated preset")?;
    Ok((start, &rest[..end]))
}

/// Preset names in document order.
pub fn names(xml: &str) -> Vec<String> {
    xml.lines()
        .filter(|line| line.contains("<APVTSSwankyAmp "))
        .filter_map(|line| attribute(line, "presetName").map(str::to_owned))
        .collect()
}

/// A preset's amplifier controls. As on factory selection in 1.4, Input and
/// the cabinet switch keep their session values rather than the stored ones.
pub fn controls(xml: &str, name: &str) -> Result<AmpControls, String> {
    let (_, body) = body(xml, name)?;
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

/// Returns `xml` with the named preset's listed parameters replaced, leaving
/// every other byte as it was.
pub fn with_values(xml: &str, name: &str, values: &[(&str, String)]) -> Result<String, String> {
    let (start, body) = body(xml, name)?;
    let mut replaced = String::with_capacity(body.len());
    let mut remaining: Vec<&str> = values.iter().map(|(id, _)| *id).collect();
    for line in body.split_inclusive('\n') {
        match attribute(line, "id").and_then(|id| values.iter().find(|(key, _)| *key == id)) {
            Some((id, value)) => {
                let old = attribute(line, "value").ok_or("parameter without value")?;
                replaced.push_str(&line.replacen(
                    &format!("value=\"{old}\""),
                    &format!("value=\"{value}\""),
                    1,
                ));
                remaining.retain(|key| key != id);
            }
            None => replaced.push_str(line),
        }
    }
    if let Some(id) = remaining.first() {
        return Err(format!("preset {name} has no {id} parameter"));
    }
    Ok(format!(
        "{}{}{}",
        &xml[..start],
        replaced,
        &xml[start + body.len()..]
    ))
}
