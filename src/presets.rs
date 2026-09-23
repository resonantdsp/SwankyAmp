//! Presets in the 1.x XML schema. A bank is `<presets>` holding one
//! `<APVTSSwankyAmp presetName>` element per preset; a preset file is one
//! `<APVTSSwankyAmp pluginVersion>` element. Each lists `<PARAM id value/>`
//! entries under the 1.x parameter ids. Version 2 reads and writes the same
//! schema, so 1.x and 2.0 presets stay one format.

use std::collections::HashMap;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex};

use crate::dsp::amp::AmpControls;
use crate::dsp::refit;

/// The version 2 factory bank, refitted by `just refit`.
pub const FACTORY_BANK: &str = include_str!("../presets/factory-2.0.xml");
/// The bank 1.4.0 shipped, which it also copied into its preset folder.
const RELEASED_BANK: &str =
    include_str!("../verification/reference/released/Resources/presets.xml");

const PRESET_TAG: &str = "APVTSSwankyAmp";
/// The tag before the product was renamed, which 1.4.0 still accepted.
const RENAMED_TAG: &str = "APVTSResonantAmp";
const EXTENSION: &str = "xml";

/// 1.x parameter ids and the version 2 parameter each one sets.
pub const PARAMETERS: [(&str, u32); 21] = [
    ("idInputLevel", 0),
    ("idOutputLevel", 1),
    ("idTsLow", 2),
    ("idTsMid", 3),
    ("idTsHigh", 4),
    ("idTsPresence", 5),
    ("idTsSelection", 6),
    ("idGainStages", 7),
    ("idGainOverhead", 8),
    ("idLowCut", 9),
    ("idCabOnOff", 10),
    ("idCabBrightness", 11),
    ("idCabDistance", 12),
    ("idCabDynamic", 13),
    ("idPreAmpDrive", 14),
    ("idPreAmpTight", 15),
    ("idPreAmpGrit", 16),
    ("idPowerAmpDrive", 17),
    ("idPowerAmpTight", 18),
    ("idPowerAmpSag", 19),
    ("idPowerAmpSagRatio", 20),
];

/// Input and the cabinet switch belong to the session: 1.4.0 stored them in
/// every preset but never applied them on load, and changing them never
/// marked a preset modified.
pub fn session_level(parameter: u32) -> bool {
    matches!(parameter, 0 | 10)
}

fn value(controls: &AmpControls, id: &str) -> Option<f32> {
    let mut copy = *controls;
    slot(&mut copy, id).map(|value| *value)
}

fn slot<'a>(controls: &'a mut AmpControls, id: &str) -> Option<&'a mut f32> {
    Some(match id {
        "idInputLevel" => &mut controls.input,
        "idOutputLevel" => &mut controls.output,
        "idTsLow" => &mut controls.low,
        "idTsMid" => &mut controls.mid,
        "idTsHigh" => &mut controls.high,
        "idTsPresence" => &mut controls.presence,
        "idTsSelection" => &mut controls.tone_stack,
        "idGainStages" => &mut controls.stages,
        "idGainOverhead" => &mut controls.overhead,
        "idLowCut" => &mut controls.low_cut,
        "idCabBrightness" => &mut controls.cabinet_brightness,
        "idCabDistance" => &mut controls.cabinet_distance,
        "idCabDynamic" => &mut controls.cabinet_dynamic,
        "idPreAmpDrive" => &mut controls.preamp_drive,
        "idPreAmpTight" => &mut controls.preamp_tight,
        "idPreAmpGrit" => &mut controls.preamp_grit,
        "idPowerAmpDrive" => &mut controls.power_drive,
        "idPowerAmpTight" => &mut controls.power_tight,
        "idPowerAmpSag" => &mut controls.power_sag,
        "idPowerAmpSagRatio" => &mut controls.power_sag_ratio,
        _ => return None,
    })
}

/// The plain value a preset gives a version 2 parameter.
pub fn parameter_value(controls: &AmpControls, parameter: u32) -> Option<f64> {
    let (id, _) = PARAMETERS.iter().find(|(_, param)| *param == parameter)?;
    if *id == "idCabOnOff" {
        return Some(if controls.cabinet_on { 1.0 } else { 0.0 });
    }
    value(controls, id).map(f64::from)
}

/// One preset's controls, including the Input and cabinet switch it was
/// saved with even though loading leaves those to the session.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Preset {
    pub controls: AmpControls,
}

impl Preset {
    /// The version 2 parameters a preset sets when it is applied, as plain
    /// values.
    pub fn tone(&self) -> Vec<(u32, f64)> {
        PARAMETERS
            .iter()
            .filter(|(_, parameter)| !session_level(*parameter))
            .filter_map(|(_, parameter)| {
                parameter_value(&self.controls, *parameter).map(|value| (*parameter, value))
            })
            .collect()
    }
}

type Version = (i64, i64, i64);

/// JUCE's `parseVersionString`: dot-separated sections read by their leading
/// integer, missing sections zero.
fn parse_version(text: &str) -> Version {
    let mut sections = text.split('.').map(|section| {
        let digits: String = section
            .trim_start()
            .chars()
            .take_while(char::is_ascii_digit)
            .collect();
        digits.parse().unwrap_or(0)
    });
    (
        sections.next().unwrap_or(0),
        sections.next().unwrap_or(0),
        sections.next().unwrap_or(0),
    )
}

fn remap_xy(x: f32, x1: f32, x2: f32, y1: f32, y2: f32) -> f32 {
    let x = x.clamp(x1, x2);
    (x - x1) / (x2 - x1) * (y2 - y1) + y1
}

fn remap_sinh(x: f32, x0: f32, scale: f32) -> f32 {
    let mapped = ((x - x0) * scale).sinh();
    let lower = ((-1. - x0) * scale).sinh();
    let upper = ((1. - x0) * scale).sinh();
    (mapped - lower) / (upper - lower) * 2. - 1.
}

fn invert_remap_sinh(x: f32, x0: f32, scale: f32) -> f32 {
    let lower = ((-1. - x0) * scale).sinh();
    let upper = ((1. - x0) * scale).sinh();
    let unscaled = (x + 1.) / 2. * (upper - lower) + lower;
    unscaled.asinh() / scale + x0
}

fn transform_unit_scale(
    value: f64,
    lower: f64,
    upper: f64,
    lower_post: f64,
    upper_post: f64,
) -> f64 {
    let post = 2. / (upper_post - lower_post)
        * ((value + 1.) / 2. * (upper - lower) + lower - lower_post)
        - 1.;
    post.clamp(-1., 1.)
}

/// The control remappings 1.4.0 applied to presets saved by older versions,
/// in its order. Presets without a version are taken as current, as 1.4.0
/// took them.
fn migrate(values: &mut HashMap<String, f32>, version: Option<Version>) {
    let Some(version) = version else {
        return;
    };
    let mut change = |id: &str, remap: &dyn Fn(f32) -> f32| {
        if let Some(value) = values.get_mut(id) {
            *value = remap(*value);
        }
    };
    if version < (0, 7, 0) {
        change("idPowerAmpDrive", &|value| {
            let (from, to) = ((1f64.ln(), 1e3f64.ln()), (0.5f64.ln(), 5e2f64.ln()));
            transform_unit_scale(f64::from(value), from.0, from.1, to.0, to.1) as f32
        });
        change("idPowerAmpSag", &|value| {
            transform_unit_scale(f64::from(value), 0., 1., 0., 0.5) as f32
        });
    }
    if version < (1, 2, 0) {
        change("idPreAmpDrive", &|value| {
            remap_xy(value, -1., 1., -0.67, 0.86)
        });
        change("idPowerAmpDrive", &|value| {
            invert_remap_sinh(remap_xy(value, -1., 1., -0.85, 1.14), -0.2, 1.)
        });
        change("idPowerAmpSag", &|value| remap_sinh(value, 0., 1.));
    }
    if version < (1, 3, 1) {
        change("idPreAmpDrive", &|value| invert_remap_sinh(value, 0.5, 1.));
    }
    if version < (1, 4, 0) {
        change("idLowCut", &|value| {
            remap_xy(invert_remap_sinh(value, 0.5, 1.), 0., 1.23, -1., 1.)
        });
    }
}

fn read_state(element: roxmltree::Node) -> Preset {
    let mut values: HashMap<String, f32> = element
        .children()
        .filter(|child| child.has_tag_name("PARAM"))
        .filter_map(|child| {
            Some((
                child.attribute("id")?.to_owned(),
                child.attribute("value")?.trim().parse().ok()?,
            ))
        })
        .collect();
    migrate(
        &mut values,
        element.attribute("pluginVersion").map(parse_version),
    );
    let mut controls = AmpControls::default();
    for (id, value) in &values {
        if id == "idCabOnOff" {
            controls.cabinet_on = *value >= 0.5;
        } else if let Some(slot) = slot(&mut controls, id) {
            *slot = *value;
        }
    }
    Preset { controls }
}

/// Reads one preset file as 1.4.0 wrote it or version 2 writes it. A file
/// that is not well-formed XML or not a Swanky Amp preset is an error.
pub fn parse_state(xml: &str) -> Result<Preset, String> {
    let document = roxmltree::Document::parse(xml).map_err(|error| format!("not XML ({error})"))?;
    let root = document.root_element();
    let tag = root.tag_name().name();
    if tag != PRESET_TAG && tag != RENAMED_TAG {
        return Err(format!("not a Swanky Amp preset (<{tag}>)"));
    }
    Ok(read_state(root))
}

/// Reads a bank of named presets in document order.
pub fn parse_bank(xml: &str) -> Result<Vec<(String, Preset)>, String> {
    let document = roxmltree::Document::parse(xml).map_err(|error| format!("not XML ({error})"))?;
    let root = document.root_element();
    if !root.has_tag_name("presets") {
        return Err(format!("not a preset bank (<{}>)", root.tag_name().name()));
    }
    Ok(root
        .children()
        .filter(|child| child.has_tag_name(PRESET_TAG))
        .filter_map(|child| Some((child.attribute("presetName")?.to_owned(), read_state(child))))
        .collect())
}

fn escape(text: &str) -> String {
    text.replace('&', "&amp;")
        .replace('<', "&lt;")
        .replace('>', "&gt;")
        .replace('"', "&quot;")
}

fn xml_value(value: f32) -> String {
    if value.fract() == 0. {
        format!("{value:.1}")
    } else {
        format!("{value}")
    }
}

/// What a version 2 preset file records about its origin beyond its values.
#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct Provenance {
    /// The 1.x version a preset was imported from, or `"1.x"` when the
    /// file did not say.
    pub imported_from: Option<String>,
}

/// Writes one preset file in the 1.x schema, with every parameter 1.4.0
/// would read, so either version can load it.
pub fn write_state(controls: &AmpControls, provenance: &Provenance) -> String {
    let mut attributes = format!(" pluginVersion=\"{}\"", env!("CARGO_PKG_VERSION"));
    if let Some(source) = &provenance.imported_from {
        attributes.push_str(&format!(
            " importedFrom=\"{}\" refit=\"standard tone stack\"",
            escape(source)
        ));
    }
    let mut ids: Vec<&str> = PARAMETERS.iter().map(|(id, _)| *id).collect();
    ids.sort_unstable();
    let mut xml =
        format!("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n<{PRESET_TAG}{attributes}>\n");
    for id in ids {
        let value = if id == "idCabOnOff" {
            if controls.cabinet_on { 1. } else { 0. }
        } else {
            value(controls, id).unwrap_or_default()
        };
        xml.push_str(&format!(
            "  <PARAM id=\"{id}\" value=\"{}\"/>\n",
            xml_value(value)
        ));
    }
    xml.push_str(&format!("</{PRESET_TAG}>\n"));
    xml
}

fn provenance(xml: &str) -> Provenance {
    let imported_from = roxmltree::Document::parse(xml).ok().and_then(|document| {
        document
            .root_element()
            .attribute("importedFrom")
            .map(str::to_owned)
    });
    Provenance { imported_from }
}

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

/// Preset names in a bank, in document order.
pub fn names(xml: &str) -> Vec<String> {
    xml.lines()
        .filter(|line| line.contains("<APVTSSwankyAmp "))
        .filter_map(|line| attribute(line, "presetName").map(str::to_owned))
        .collect()
}

/// A bank preset's amplifier controls. As on preset selection in 1.4, Input
/// and the cabinet switch keep their session values rather than the stored
/// ones.
pub fn controls(xml: &str, name: &str) -> Result<AmpControls, String> {
    let (_, preset) = parse_bank(xml)?
        .into_iter()
        .find(|(preset, _)| preset == name)
        .ok_or_else(|| format!("unknown preset: {name}"))?;
    let defaults = AmpControls::default();
    Ok(AmpControls {
        input: defaults.input,
        cabinet_on: defaults.cabinet_on,
        ..preset.controls
    })
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

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum Scope {
    /// Every preset parameter at its default. There is no Reset button.
    Init,
    /// Shipped in the plugin and read-only.
    Factory,
    /// A file in the user's preset folder.
    User,
}

/// One selectable preset. The key is what host state remembers, so a
/// session finds its preset by name rather than by list position.
#[derive(Debug, Clone, PartialEq)]
pub struct Entry {
    pub key: String,
    pub name: String,
    pub scope: Scope,
    pub path: Option<PathBuf>,
}

impl Entry {
    pub const INIT: &str = "init";

    fn init() -> Self {
        Self {
            key: Self::INIT.into(),
            name: "Init".into(),
            scope: Scope::Init,
            path: None,
        }
    }
}

/// Where version 2 keeps the user's presets: the platform's audio preset
/// folder on macOS, as Pro does, and the per-user data folder elsewhere.
pub fn default_user_root() -> Option<PathBuf> {
    preset_base().map(|base| base.join("Resonant DSP").join("Swanky Amp 2"))
}

/// Where 1.4.0 kept its presets: JUCE's user application data folder, under
/// `Audio/Presets` on macOS.
pub fn legacy_root() -> Option<PathBuf> {
    let base = if cfg!(target_os = "macos") {
        preset_base()
    } else if cfg!(target_os = "windows") {
        dirs::data_dir()
    } else {
        dirs::config_dir()
    };
    base.map(|base| base.join("Resonant DSP").join("Swanky Amp"))
}

fn preset_base() -> Option<PathBuf> {
    if cfg!(target_os = "macos") {
        dirs::home_dir().map(|home| home.join("Library").join("Audio").join("Presets"))
    } else {
        dirs::data_dir()
    }
}

/// Characters no preset name may carry, so a name is always one file on
/// every platform.
fn valid_name(name: &str) -> Result<String, String> {
    let name = name.trim();
    if name.is_empty() || name.starts_with('.') {
        return Err("Choose a preset name.".into());
    }
    if name.chars().any(|c| {
        c.is_control() || matches!(c, '/' | '\\' | ':' | '*' | '?' | '"' | '<' | '>' | '|')
    }) {
        return Err("A preset name cannot contain / \\ : * ? \" < > |.".into());
    }
    Ok(name.to_owned())
}

/// 1.4.0 kept its menu order by prefixing file names with a number and a
/// space, which is not part of the name.
fn legacy_name(stem: &str) -> &str {
    let digits = stem.chars().take_while(char::is_ascii_digit).count();
    match stem[digits..].strip_prefix(' ') {
        Some(name) if digits > 0 && !name.is_empty() => name,
        _ => stem,
    }
}

fn xml_files(directory: &Path) -> Vec<PathBuf> {
    let mut files: Vec<PathBuf> = std::fs::read_dir(directory)
        .into_iter()
        .flatten()
        .filter_map(|entry| entry.ok().map(|entry| entry.path()))
        .filter(|path| {
            path.is_file()
                && path
                    .extension()
                    .is_some_and(|extension| extension.eq_ignore_ascii_case(EXTENSION))
        })
        .collect();
    files.sort();
    files
}

/// The listing a menu shows, and the files it had to leave out.
#[derive(Debug, Clone, Default)]
pub struct Listing {
    pub entries: Vec<Entry>,
    pub unreadable: Vec<String>,
}

/// Init, the factory bank and the user's preset folder.
#[derive(Debug, Clone)]
pub struct Library {
    factory: Vec<(String, Preset)>,
    user_root: Option<PathBuf>,
}

impl Default for Library {
    fn default() -> Self {
        Self::with_user_root(default_user_root())
    }
}

impl Library {
    /// Tests keep user presets away from the real folder.
    pub fn with_user_root(user_root: Option<PathBuf>) -> Self {
        Self {
            // The bank is refitted and checked by `just`, so a failure here
            // is a build defect; an empty factory list keeps the editor up.
            factory: parse_bank(FACTORY_BANK).unwrap_or_default(),
            user_root,
        }
    }

    pub fn user_root(&self) -> Option<&Path> {
        self.user_root.as_deref()
    }

    /// Init and the factory bank, which need no disk access.
    pub fn builtin(&self) -> Vec<Entry> {
        std::iter::once(Entry::init())
            .chain(self.factory.iter().map(|(name, _)| Entry {
                key: format!("factory:{name}"),
                name: name.clone(),
                scope: Scope::Factory,
                path: None,
            }))
            .collect()
    }

    /// Init, the factory presets, then the user's presets by name. Files that
    /// cannot be read are left out and named in the listing.
    pub fn list(&self) -> Listing {
        let mut listing = Listing {
            entries: self.builtin(),
            unreadable: Vec::new(),
        };
        let Some(root) = &self.user_root else {
            return listing;
        };
        let mut user = Vec::new();
        for path in xml_files(root) {
            let Some(stem) = path
                .file_stem()
                .map(|stem| stem.to_string_lossy().into_owned())
            else {
                continue;
            };
            match std::fs::read_to_string(&path)
                .map_err(|error| error.to_string())
                .and_then(|xml| parse_state(&xml))
            {
                Ok(_) => user.push(Entry {
                    key: format!(
                        "user:{}",
                        path.file_name().unwrap_or_default().to_string_lossy()
                    ),
                    name: stem,
                    scope: Scope::User,
                    path: Some(path),
                }),
                Err(_) => listing.unreadable.push(stem),
            }
        }
        user.sort_by_key(|entry| entry.name.to_lowercase());
        listing.entries.extend(user);
        listing
    }

    pub fn find(&self, key: &str) -> Option<Entry> {
        let builtin = self.builtin();
        if let Some(entry) = builtin.into_iter().find(|entry| entry.key == key) {
            return Some(entry);
        }
        self.list()
            .entries
            .into_iter()
            .find(|entry| entry.key == key)
    }

    /// The preset an entry names, or `None` for Init.
    pub fn load(&self, entry: &Entry) -> Result<Option<Preset>, String> {
        match entry.scope {
            Scope::Init => Ok(None),
            Scope::Factory => self
                .factory
                .iter()
                .find(|(name, _)| *name == entry.name)
                .map(|(_, preset)| Some(*preset))
                .ok_or_else(|| format!("Factory preset {} is not shipped.", entry.name)),
            Scope::User => {
                let path = entry
                    .path
                    .as_ref()
                    .ok_or_else(|| format!("Preset {} has no file.", entry.name))?;
                std::fs::read_to_string(path)
                    .map_err(|error| error.to_string())
                    .and_then(|xml| parse_state(&xml))
                    .map(Some)
                    .map_err(|error| format!("Preset {} could not be read: {error}.", entry.name))
            }
        }
    }

    /// The values applying an entry sets: the preset's, or every default for
    /// Init and for a preset that can no longer be read.
    pub fn tone(&self, entry: &Entry) -> Vec<(u32, f64)> {
        let controls = self
            .load(entry)
            .ok()
            .flatten()
            .map_or_else(AmpControls::default, |preset| preset.controls);
        Preset { controls }.tone()
    }

    /// The user folder, created if it does not exist yet.
    pub fn root(&self) -> Result<PathBuf, String> {
        let root = self
            .user_root
            .clone()
            .ok_or("No preset folder is available on this system.")?;
        std::fs::create_dir_all(&root)
            .map_err(|error| format!("The preset folder could not be created: {error}."))?;
        Ok(root)
    }

    fn path_for(&self, name: &str) -> Result<PathBuf, String> {
        Ok(self
            .root()?
            .join(format!("{}.{EXTENSION}", valid_name(name)?)))
    }

    /// Saves the controls as a user preset, replacing one of the same name.
    pub fn save(&self, name: &str, controls: &AmpControls) -> Result<Entry, String> {
        let path = self.path_for(name)?;
        // Resaving an imported preset keeps the record of where it came from.
        let provenance = std::fs::read_to_string(&path)
            .map(|xml| provenance(&xml))
            .unwrap_or_default();
        std::fs::write(&path, write_state(controls, &provenance))
            .map_err(|error| format!("The preset could not be saved: {error}."))?;
        self.entry_for(&path)
    }

    fn entry_for(&self, path: &Path) -> Result<Entry, String> {
        self.list()
            .entries
            .into_iter()
            .find(|entry| entry.path.as_deref() == Some(path))
            .ok_or_else(|| "The saved preset could not be read back.".into())
    }

    pub fn remove(&self, entry: &Entry) -> Result<(), String> {
        match (&entry.scope, &entry.path) {
            (Scope::User, Some(path)) => std::fs::remove_file(path)
                .map_err(|error| format!("Preset {} could not be removed: {error}.", entry.name)),
            _ => Err("Only your own presets can be removed.".into()),
        }
    }

    /// Copies 1.x presets from `source` into the user folder, refitting each
    /// to the standard tone stack. The 1.x files are only read. A preset
    /// whose name is already taken in the user folder is left alone, as is
    /// an unchanged copy of a 1.4.0 factory preset, which the version 2
    /// factory bank already carries refitted.
    pub fn import_legacy(&self, source: &Path) -> Result<ImportReport, String> {
        let mut report = ImportReport::default();
        let released = parse_bank(RELEASED_BANK).unwrap_or_default();
        let mut pluck = None;
        for path in xml_files(source) {
            let stem = path.file_stem().unwrap_or_default().to_string_lossy();
            let name = legacy_name(&stem).to_owned();
            let xml = match std::fs::read_to_string(&path) {
                Ok(xml) => xml,
                Err(_) => {
                    report.unreadable.push(name);
                    continue;
                }
            };
            let preset = match parse_state(&xml) {
                Ok(preset) => preset,
                Err(_) => {
                    report.unreadable.push(name);
                    continue;
                }
            };
            if released
                .iter()
                .any(|(factory, released)| *factory == name && released.tone() == preset.tone())
            {
                report.factory_copies += 1;
                continue;
            }
            let Ok(target) = self.path_for(&name) else {
                report.unreadable.push(name);
                continue;
            };
            if target.exists() {
                report.existing.push(name);
                continue;
            }
            let input = pluck.get_or_insert_with(|| refit::pluck(refit::SAMPLE_RATE));
            let fitted = refit::fit(session_neutral(preset.controls), input);
            let controls = AmpControls {
                low: fitted.low,
                mid: fitted.mid,
                high: fitted.high,
                power_drive: fitted.power_drive,
                ..preset.controls
            };
            let source_version = roxmltree::Document::parse(&xml)
                .ok()
                .and_then(|document| {
                    document
                        .root_element()
                        .attribute("pluginVersion")
                        .map(str::to_owned)
                })
                .unwrap_or_else(|| "1.x".into());
            let provenance = Provenance {
                imported_from: Some(source_version),
            };
            // Another editor may be importing the same folder; whichever
            // creates the file first keeps it.
            match std::fs::OpenOptions::new()
                .write(true)
                .create_new(true)
                .open(&target)
            {
                Ok(mut file) => {
                    file.write_all(write_state(&controls, &provenance).as_bytes())
                        .map_err(|error| format!("{name} could not be written: {error}."))?;
                    report.imported.push(name);
                }
                Err(error) if error.kind() == std::io::ErrorKind::AlreadyExists => {
                    report.existing.push(name);
                }
                Err(error) => return Err(format!("{name} could not be written: {error}.")),
            }
        }
        Ok(report)
    }
}

/// The fit measures a preset the way the factory refit did, with Input and
/// the cabinet switch at their defaults, since the preset does not set them.
fn session_neutral(controls: AmpControls) -> AmpControls {
    let defaults = AmpControls::default();
    AmpControls {
        input: defaults.input,
        cabinet_on: defaults.cabinet_on,
        ..controls
    }
}

#[derive(Debug, Clone, Default, PartialEq, Eq)]
pub struct ImportReport {
    pub imported: Vec<String>,
    /// Names already taken in the version 2 folder, left untouched.
    pub existing: Vec<String>,
    /// Unchanged 1.4.0 factory presets, which were not copied.
    pub factory_copies: usize,
    pub unreadable: Vec<String>,
}

impl ImportReport {
    pub fn summary(&self) -> String {
        let mut parts = vec![match self.imported.len() {
            0 => "No 1.x presets to import".to_owned(),
            1 => "Imported 1 preset from 1.x, refitted".to_owned(),
            count => format!("Imported {count} presets from 1.x, refitted"),
        }];
        if !self.existing.is_empty() {
            parts.push(format!("{} already here, kept", self.existing.len()));
        }
        if !self.unreadable.is_empty() {
            parts.push(format!("skipped unreadable {}", self.unreadable.join(", ")));
        }
        parts.join(" · ")
    }
}

/// An import running off the editor thread: the fit renders every preset
/// through the amplifier, which takes too long for a frame.
pub struct ImportJob {
    result: Arc<Mutex<Option<Result<ImportReport, String>>>>,
}

static IMPORTING: AtomicBool = AtomicBool::new(false);

impl ImportJob {
    /// Starts an import unless one is already running in this process.
    pub fn start(library: Library, source: PathBuf) -> Option<Self> {
        if IMPORTING.swap(true, Ordering::AcqRel) {
            return None;
        }
        let result = Arc::new(Mutex::new(None));
        let shared = Arc::clone(&result);
        let spawned = std::thread::Builder::new()
            .name("swanky-preset-import".into())
            .spawn(move || {
                let outcome = if source.is_dir() {
                    library.import_legacy(&source)
                } else {
                    Err("No Swanky Amp 1.x presets were found.".into())
                };
                if let Ok(mut slot) = shared.lock() {
                    *slot = Some(outcome);
                }
                IMPORTING.store(false, Ordering::Release);
            });
        if spawned.is_err() {
            IMPORTING.store(false, Ordering::Release);
            return None;
        }
        Some(Self { result })
    }

    /// The first-run import: only while version 2 has no preset folder yet
    /// and 1.4.0 left one behind.
    pub fn first_run(library: &Library) -> Option<Self> {
        let source = legacy_root()?;
        if library.user_root()?.exists() || !source.is_dir() {
            return None;
        }
        Self::start(library.clone(), source)
    }

    pub fn finished(&self) -> bool {
        self.result.lock().is_ok_and(|result| result.is_some())
    }

    pub fn take(&self) -> Option<Result<ImportReport, String>> {
        self.result.lock().ok().and_then(|mut result| result.take())
    }
}

/// Sets a preset's values directly on the parameters and names it in the
/// state, for tools that have no host to automate.
pub fn apply_offline(
    library: &Library,
    key: &str,
    params: &crate::SwankyAmpParams,
) -> Result<(), String> {
    use truce::prelude::Params;
    let entry = library
        .find(key)
        .ok_or_else(|| format!("unknown preset: {key}"))?;
    for (id, value) in library.tone(&entry) {
        params.set_plain(id, value);
    }
    params.preset.set(entry.key);
    Ok(())
}

/// Shows a folder in the system file browser.
pub fn reveal(path: &Path) -> Result<(), String> {
    let opener = if cfg!(target_os = "macos") {
        "open"
    } else if cfg!(target_os = "windows") {
        "explorer"
    } else {
        "xdg-open"
    };
    std::process::Command::new(opener)
        .arg(path)
        .spawn()
        .map(|_| ())
        .map_err(|_| "The preset folder could not be opened.".into())
}

#[cfg(test)]
mod tests {
    use super::*;

    const RELEASED: &str = RELEASED_BANK;

    fn scratch(name: &str) -> PathBuf {
        let path = std::env::temp_dir().join(format!(
            "swanky-presets-{name}-{}-{:?}",
            std::process::id(),
            std::thread::current().id()
        ));
        let _ = std::fs::remove_dir_all(&path);
        std::fs::create_dir_all(&path).unwrap();
        path
    }

    /// A preset file as 1.4.0 wrote one: the bank element without its name,
    /// stamped with the running version.
    fn legacy_file(name: &str) -> String {
        let (_, body) = body(RELEASED, name).unwrap();
        format!(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n<APVTSSwankyAmp pluginVersion=\"1.4.0\">{body}</APVTSSwankyAmp>\n"
        )
    }

    #[test]
    fn a_released_preset_file_reads_as_the_model_gate_reads_the_bank() {
        for name in names(RELEASED) {
            let file = parse_state(&legacy_file(&name)).unwrap().controls;
            let gate = controls(RELEASED, &name).unwrap();
            assert_eq!(
                session_neutral(file),
                gate,
                "{name} read differently from a file"
            );
        }
    }

    #[test]
    fn corrupt_and_foreign_files_are_reported_and_skipped() {
        let root = scratch("corrupt");
        let whole = legacy_file("edge");
        std::fs::write(root.join("truncated.xml"), &whole[..whole.len() / 2]).unwrap();
        std::fs::write(
            root.join("foreign.xml"),
            "<?xml version=\"1.0\"?><APVTSSwankyAmpPro><PARAM id=\"idTsLow\" value=\"1\"/></APVTSSwankyAmpPro>",
        )
        .unwrap();
        std::fs::write(root.join("good.xml"), &whole).unwrap();
        let library = Library::with_user_root(Some(root.clone()));
        let listing = library.list();
        let user: Vec<&str> = listing
            .entries
            .iter()
            .filter(|entry| entry.scope == Scope::User)
            .map(|entry| entry.name.as_str())
            .collect();
        assert_eq!(user, ["good"]);
        assert_eq!(listing.unreadable, ["foreign", "truncated"]);
        std::fs::remove_dir_all(root).unwrap();
    }

    #[test]
    fn a_saved_preset_reloads_with_the_same_values() {
        let root = scratch("save");
        let library = Library::with_user_root(Some(root.join("Swanky Amp 2")));
        let mut controls = controls(RELEASED, "high gain").unwrap();
        controls.low = 0.123_456_7;
        controls.cabinet_on = false;
        controls.input = -0.25;
        let entry = library.save("my tone", &controls).unwrap();
        assert_eq!(entry.name, "my tone");
        let reloaded = library.find(&entry.key).unwrap();
        assert_eq!(library.load(&reloaded).unwrap().unwrap().controls, controls);
        std::fs::remove_dir_all(root).unwrap();
    }

    #[test]
    fn import_refits_1x_presets_and_never_overwrites() {
        let root = scratch("import");
        let legacy = root.join("Swanky Amp");
        let library = Library::with_user_root(Some(root.join("Swanky Amp 2")));
        std::fs::create_dir_all(&legacy).unwrap();
        let mine = legacy_file("pre drive").replace(
            "<PARAM id=\"idCabDistance\" value=\"0.6000000238418579\"/>",
            "<PARAM id=\"idCabDistance\" value=\"0.8\"/>",
        );
        assert!(
            mine.contains("value=\"0.8\""),
            "fixture did not change the preset"
        );
        std::fs::write(legacy.join("11 mine.xml"), &mine).unwrap();
        std::fs::write(legacy.join("01 clean.xml"), legacy_file("clean")).unwrap();
        std::fs::write(legacy.join("12 kept.xml"), legacy_file("edge")).unwrap();
        std::fs::write(legacy.join("13 broken.xml"), "<APVTSSwankyAmp><PARAM").unwrap();
        let kept = library.save("kept", &AmpControls::default()).unwrap();
        let kept_before = std::fs::read(kept.path.as_ref().unwrap()).unwrap();
        let legacy_before: Vec<Vec<u8>> = xml_files(&legacy)
            .iter()
            .map(|path| std::fs::read(path).unwrap())
            .collect();

        let report = library.import_legacy(&legacy).unwrap();

        assert_eq!(report.imported, ["mine"]);
        assert_eq!(report.existing, ["kept"]);
        assert_eq!(report.factory_copies, 1);
        assert_eq!(report.unreadable, ["broken"]);
        assert_eq!(std::fs::read(kept.path.unwrap()).unwrap(), kept_before);
        let legacy_after: Vec<Vec<u8>> = xml_files(&legacy)
            .iter()
            .map(|path| std::fs::read(path).unwrap())
            .collect();
        assert_eq!(legacy_after, legacy_before, "the 1.x folder was modified");

        let original = parse_state(&mine).unwrap().controls;
        let fitted = refit::fit(session_neutral(original), &refit::pluck(refit::SAMPLE_RATE));
        let entry = library.find("user:mine.xml").unwrap();
        let imported = library.load(&entry).unwrap().unwrap().controls;
        assert_eq!(
            imported,
            AmpControls {
                low: fitted.low,
                mid: fitted.mid,
                high: fitted.high,
                power_drive: fitted.power_drive,
                ..original
            }
        );
        assert_ne!(
            (imported.low, imported.mid, imported.high),
            (original.low, original.mid, original.high),
            "the imported preset was not refitted"
        );
        let file = std::fs::read_to_string(entry.path.unwrap()).unwrap();
        assert_eq!(provenance(&file).imported_from.as_deref(), Some("1.4.0"));

        let again = library.import_legacy(&legacy).unwrap();
        assert!(again.imported.is_empty());
        assert_eq!(again.existing, ["mine", "kept"]);
        std::fs::remove_dir_all(root).unwrap();
    }
}
