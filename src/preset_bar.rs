//! The header's preset field and its menu: Pro's preset bar reduced to the
//! single field Free has room for, with the actions in the menu.

use std::path::PathBuf;
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

use iced_core::{Element, Length, Padding, Theme, mouse, text::LineHeight};
use iced_core::{Shadow, Vector};
use truce::prelude::Params;
use truce_iced::iced::widget::{
    Column, Space, button, column, container, mouse_area, row, scrollable, text,
};
use truce_iced::iced::{Border, Color};
use truce_iced::{Message, ParamCache, PluginContext};

use crate::params::SwankyAmpParams;
use crate::presets::{Entry, ImportJob, Library, Scope, legacy_root};
use crate::style;
use crate::widgets::{FreeRenderer, Msg};

const DIM: Color = Color::from_rgb(0.49, 0.53, 0.56);
const MENU_WIDTH: f32 = 196.0;
const ITEM_HEIGHT: f32 = 24.0;
/// The menu stops short of the footer; a longer user list scrolls.
const MENU_BOTTOM: f32 = style::HEIGHT - style::FOOTER_HEIGHT - 8.0;
/// Long enough to read a sentence, short enough not to linger over playing.
const STATUS_SECONDS: u64 = 6;
/// Names longer than the field abbreviate; the menu shows them whole.
const NAME_CHARS: usize = 13;

#[derive(Debug, Clone)]
pub enum PresetMsg {
    Toggle,
    Close,
    Select(String),
    Previous,
    Next,
    Save,
    SaveAs,
    Remove,
    Import,
    OpenFolder,
}

type Pending<T> = Arc<Mutex<Option<T>>>;

pub struct PresetBar {
    library: Library,
    entries: Vec<Entry>,
    current: Entry,
    /// The values the current preset set, for telling when it is modified.
    baseline: Vec<(u32, f64)>,
    host_revision: u64,
    pub open: bool,
    status: Option<(String, Instant)>,
    import: Option<ImportJob>,
    naming: Option<Pending<Option<PathBuf>>>,
}

impl PresetBar {
    /// A bar that never touches the disk, for layout export and captures.
    pub fn offline() -> Self {
        Self::with_library(Library::with_user_root(None))
    }

    /// The editor's bar: the user's folder listed, and the 1.x presets
    /// imported the first time version 2 runs.
    pub fn live(params: &SwankyAmpParams) -> Self {
        let mut bar = Self::with_library(Library::default());
        bar.entries = bar.library.list().entries;
        bar.import = ImportJob::first_run(&bar.library);
        bar.sync(params);
        bar
    }

    fn with_library(library: Library) -> Self {
        let entries = library.builtin();
        let current = entries[0].clone();
        let baseline = library.tone(&current);
        Self {
            library,
            entries,
            current,
            baseline,
            host_revision: 0,
            open: false,
            status: None,
            import: None,
            naming: None,
        }
    }

    /// Follows the preset host state names, which a session restore changes
    /// without the editor asking.
    pub fn sync(&mut self, params: &SwankyAmpParams) {
        let revision = params.preset.revision();
        if revision == self.host_revision {
            return;
        }
        self.host_revision = revision;
        let key = params.preset.read();
        let key = if key.is_empty() {
            Entry::INIT.to_owned()
        } else {
            key
        };
        if key == self.current.key {
            return;
        }
        let entry = self
            .entries
            .iter()
            .find(|entry| entry.key == key)
            .cloned()
            .or_else(|| self.library.find(&key));
        // A preset removed from disk leaves the restored sound under Init.
        let entry = entry.unwrap_or_else(|| self.entries[0].clone());
        self.baseline = self.library.tone(&entry);
        self.current = entry;
    }

    /// Picks up work finished off the editor thread. Returns whether the
    /// view changed.
    pub fn poll(&mut self, params: &ParamCache<SwankyAmpParams>) -> bool {
        let mut changed = false;
        if let Some(job) = &self.import
            && let Some(outcome) = job.take()
        {
            self.import = None;
            self.refresh();
            self.report(outcome.map(|report| report.summary()));
            changed = true;
        }
        if let Some(pending) = &self.naming
            && let Some(chosen) = pending.lock().ok().and_then(|mut slot| slot.take())
        {
            self.naming = None;
            if let Some(path) = chosen {
                self.save_as(&path, params);
            }
            changed = true;
        }
        if self
            .status
            .as_ref()
            .is_some_and(|(_, shown)| shown.elapsed() >= Duration::from_secs(STATUS_SECONDS))
        {
            self.status = None;
            changed = true;
        }
        changed
    }

    pub fn needs_redraw(&self, params: &SwankyAmpParams) -> bool {
        params.preset.revision() != self.host_revision
            || self.import.as_ref().is_some_and(ImportJob::finished)
            || self
                .naming
                .as_ref()
                .is_some_and(|pending| pending.lock().is_ok_and(|slot| slot.is_some()))
            || self.status.is_some()
    }

    /// A sentence for the footer while one is fresh.
    pub fn status(&self) -> Option<&str> {
        self.status.as_ref().map(|(status, _)| status.as_str())
    }

    fn report(&mut self, outcome: Result<String, String>) {
        let message = match outcome {
            Ok(message) | Err(message) => message,
        };
        self.status = Some((message, Instant::now()));
    }

    fn refresh(&mut self) {
        let listing = self.library.list();
        self.entries = listing.entries;
        if !listing.unreadable.is_empty() {
            self.report(Err(format!(
                "Skipped unreadable presets: {}",
                listing.unreadable.join(", ")
            )));
        }
    }

    /// Init never reads as modified: it is the absence of a preset.
    pub fn modified(&self, params: &ParamCache<SwankyAmpParams>) -> bool {
        self.current.scope != Scope::Init
            && self
                .baseline
                .iter()
                .any(|(id, value)| (params.get_plain(*id) - value).abs() > 1e-4)
    }

    /// The presets ‹ and › step through: the factory set, then the user's.
    fn stepping(&self) -> Vec<&Entry> {
        self.entries
            .iter()
            .filter(|entry| entry.scope != Scope::Init)
            .collect()
    }

    fn step(&self, forward: bool) -> Option<Entry> {
        let stepping = self.stepping();
        let position = stepping
            .iter()
            .position(|entry| entry.key == self.current.key);
        let target = match (position, forward) {
            (None, true) => Some(0),
            (None, false) => None,
            (Some(index), true) => Some(index + 1),
            (Some(index), false) => index.checked_sub(1),
        }?;
        stepping.get(target).map(|entry| (*entry).clone())
    }

    pub fn update(
        &mut self,
        message: PresetMsg,
        params: &ParamCache<SwankyAmpParams>,
        ctx: &PluginContext<SwankyAmpParams>,
    ) {
        self.sync(params.params());
        let close = !matches!(message, PresetMsg::Toggle);
        match message {
            PresetMsg::Toggle => {
                self.open = !self.open;
                if self.open {
                    self.refresh();
                }
            }
            PresetMsg::Close => {}
            PresetMsg::Select(key) => match self.library.find(&key) {
                Some(entry) => self.apply(entry, params, ctx),
                None => self.report(Err("That preset is no longer available.".into())),
            },
            PresetMsg::Previous | PresetMsg::Next => {
                if let Some(entry) = self.step(matches!(message, PresetMsg::Next)) {
                    self.apply(entry, params, ctx);
                }
            }
            PresetMsg::Save => {
                let outcome = if self.current.scope == Scope::User {
                    let name = self.current.name.clone();
                    self.save_named(&name, params)
                } else {
                    Err("Use Save as… to keep a copy of this preset.".into())
                };
                if let Err(error) = outcome {
                    self.report(Err(error));
                }
            }
            PresetMsg::SaveAs => self.ask_name(),
            PresetMsg::Remove => {
                let outcome = self.library.remove(&self.current).map(|()| {
                    let removed = self.current.name.clone();
                    // As in 1.4, the sound stays and the field returns to Init.
                    self.remember(self.entries[0].clone(), params.params());
                    format!("Removed {removed}")
                });
                self.refresh();
                self.report(outcome);
            }
            PresetMsg::Import => match legacy_root() {
                Some(source) => match ImportJob::start(self.library.clone(), source) {
                    Some(job) => {
                        self.import = Some(job);
                        self.report(Ok("Importing 1.x presets…".into()));
                    }
                    None => self.report(Ok("An import is already running.".into())),
                },
                None => self.report(Err("No Swanky Amp 1.x presets were found.".into())),
            },
            PresetMsg::OpenFolder => {
                let outcome = self
                    .library
                    .root()
                    .and_then(|root| crate::presets::reveal(&root));
                if let Err(error) = outcome {
                    self.report(Err(error));
                }
            }
        }
        if close {
            self.open = false;
        }
    }

    /// Sets the preset's values through the host, so automation and undo
    /// see the change in every format.
    fn apply(
        &mut self,
        entry: Entry,
        params: &ParamCache<SwankyAmpParams>,
        ctx: &PluginContext<SwankyAmpParams>,
    ) {
        let preset = match self.library.load(&entry) {
            Ok(preset) => preset,
            Err(error) => {
                self.report(Err(error));
                return;
            }
        };
        let tone = preset.map_or_else(|| self.library.tone(&entry), |preset| preset.tone());
        let infos = params.params().param_infos();
        for (id, value) in &tone {
            if let Some(info) = infos.iter().find(|info| info.id == *id) {
                ctx.automate(*id, info.range.normalize(*value));
            }
        }
        self.remember(entry, params.params());
    }

    fn remember(&mut self, entry: Entry, params: &SwankyAmpParams) {
        params.preset.set(entry.key.clone());
        self.host_revision = params.preset.revision();
        self.baseline = self.library.tone(&entry);
        self.current = entry;
    }

    fn save_named(
        &mut self,
        name: &str,
        params: &ParamCache<SwankyAmpParams>,
    ) -> Result<(), String> {
        let entry = self.library.save(name, &params.params().snapshot())?;
        self.refresh();
        self.report(Ok(format!("Saved {}", entry.name)));
        self.remember(entry, params.params());
        Ok(())
    }

    /// The name comes from the chosen file; the preset always lands in the
    /// preset folder so the menu lists it.
    fn save_as(&mut self, path: &std::path::Path, params: &ParamCache<SwankyAmpParams>) {
        let name = path
            .file_stem()
            .map(|stem| stem.to_string_lossy().into_owned())
            .unwrap_or_default();
        if let Err(error) = self.save_named(&name, params) {
            self.report(Err(error));
        }
    }

    fn ask_name(&mut self) {
        if self.naming.is_some() {
            return;
        }
        let directory = match self.library.root() {
            Ok(directory) => directory,
            Err(error) => {
                self.report(Err(error));
                return;
            }
        };
        let suggested = if self.current.scope == Scope::Init {
            "My preset".to_owned()
        } else {
            self.current.name.clone()
        };
        let pending: Pending<Option<PathBuf>> = Arc::new(Mutex::new(None));
        let shared = Arc::clone(&pending);
        // A native modal loop must not run inside the editor's frame
        // callback, so the dialog runs on its own thread as in Pro.
        let spawned = std::thread::Builder::new()
            .name("swanky-preset-name".into())
            .spawn(move || {
                let chosen = rfd::FileDialog::new()
                    .set_title("Save preset as")
                    .add_filter("Swanky Amp preset", &["xml"])
                    .set_directory(directory)
                    .set_file_name(format!("{suggested}.xml"))
                    .save_file();
                if let Ok(mut slot) = shared.lock() {
                    *slot = Some(chosen);
                }
            });
        match spawned {
            Ok(_) => self.naming = Some(pending),
            Err(_) => self.report(Err("The save dialog could not open. Try again.".into())),
        }
    }

    /// The outlined field: ‹, the preset name, ›. A press on the name opens
    /// the menu.
    pub fn field<'a, R: FreeRenderer + 'a>(
        &self,
        params: &ParamCache<SwankyAmpParams>,
    ) -> Element<'a, Msg, Theme, R> {
        let mut name = abbreviate(&self.current.name);
        if self.modified(params) {
            name.push_str(" •");
        }
        let chevron = |glyph, message: Option<PresetMsg>| {
            let available = message.is_some();
            let glyph = container(text(glyph).size(20).color(DIM.scale_alpha(if available {
                1.0
            } else {
                0.35
            })))
            .width(28)
            .height(Length::Fill)
            .center(Length::Fill);
            match message {
                Some(message) => mouse_area(glyph)
                    .on_press(preset(message))
                    .interaction(mouse::Interaction::Pointer)
                    .into(),
                None => Element::from(glyph),
            }
        };
        let previous = self.step(false).map(|_| PresetMsg::Previous);
        let next = self.step(true).map(|_| PresetMsg::Next);
        let open = self.open;
        container(
            row![
                chevron("‹", previous),
                mouse_area(
                    container(
                        text(name)
                            .size(14)
                            .wrapping(iced_core::text::Wrapping::None)
                            .color(style::INK),
                    )
                    .width(Length::Fill)
                    .height(Length::Fill)
                    .center(Length::Fill),
                )
                .on_press(preset(PresetMsg::Toggle))
                .interaction(mouse::Interaction::Pointer),
                chevron("›", next),
            ]
            .height(Length::Fill),
        )
        .width(Length::Fill)
        .height(Length::Fill)
        .style(move |_| style::outlined(open))
        .into()
    }

    /// The open menu as layers over the whole editor: a catch-all that closes
    /// it, then the list under the field.
    pub fn menu<'a, R: FreeRenderer + 'a>(
        &self,
        field: [f32; 4],
        params: &ParamCache<SwankyAmpParams>,
    ) -> Vec<Element<'a, Msg, Theme, R>> {
        if !self.open {
            return Vec::new();
        }
        let modified = self.modified(params);
        let item = |label: String, message: Option<PresetMsg>, current: bool| {
            menu_item::<R>(label, message, current)
        };
        let mut presets: Vec<Element<'a, Msg, Theme, R>> = Vec::new();
        let mut previous_scope = None;
        for entry in &self.entries {
            if previous_scope.is_some_and(|scope| scope != entry.scope) {
                presets.push(divider());
            }
            previous_scope = Some(entry.scope);
            presets.push(item(
                entry.name.clone(),
                Some(PresetMsg::Select(entry.key.clone())),
                entry.key == self.current.key,
            ));
        }
        let user = self.current.scope == Scope::User;
        let actions: Vec<Element<'a, Msg, Theme, R>> = vec![
            item(
                "Save".into(),
                (user && modified).then_some(PresetMsg::Save),
                false,
            ),
            item("Save as…".into(), Some(PresetMsg::SaveAs), false),
            item("Remove".into(), user.then_some(PresetMsg::Remove), false),
            item(
                "Import 1.x presets".into(),
                self.import.is_none().then_some(PresetMsg::Import),
                false,
            ),
            item("Open folder".into(), Some(PresetMsg::OpenFolder), false),
        ];
        let dividers = self
            .entries
            .windows(2)
            .filter(|pair| pair[0].scope != pair[1].scope)
            .count();
        let list_height = self.entries.len() as f32 * ITEM_HEIGHT + dividers as f32 * DIVIDER;
        let top = field[1] + field[3] + 4.0;
        let chrome = 2.0 * MENU_PADDING + DIVIDER + actions.len() as f32 * ITEM_HEIGHT;
        let list_room = MENU_BOTTOM - top - chrome;
        let list: Element<'a, Msg, Theme, R> = if list_height > list_room {
            scrollable(Column::with_children(presets).width(Length::Fill))
                .height(list_room)
                .direction(scrollable::Direction::Vertical(
                    scrollable::Scrollbar::new().width(4).scroller_width(4),
                ))
                .style(|theme, status| {
                    let mut style = scrollable::default(theme, status);
                    style.vertical_rail.background = None;
                    style.vertical_rail.border = Border::default();
                    style.vertical_rail.scroller.background = style::MUTED.scale_alpha(0.4).into();
                    style.vertical_rail.scroller.border = Border {
                        radius: 2.0.into(),
                        ..Border::default()
                    };
                    style
                })
                .into()
        } else {
            Column::with_children(presets).width(Length::Fill).into()
        };
        let panel =
            container(column![list, divider(), Column::with_children(actions)].width(Length::Fill))
                .padding(Padding::from([MENU_PADDING, 0.0]))
                .width(Length::Fill)
                .style(|_| menu_style());
        let height = chrome + list_height.min(list_room);
        vec![
            place(
                [0.0, 0.0, style::WIDTH, style::HEIGHT],
                mouse_area(Space::new().width(Length::Fill).height(Length::Fill))
                    .on_press(preset(PresetMsg::Close))
                    .on_right_press(preset(PresetMsg::Close)),
            ),
            place([field[0], top, MENU_WIDTH, height], panel),
        ]
    }
}

const MENU_PADDING: f32 = 4.0;
const DIVIDER: f32 = 9.0;

fn preset(message: PresetMsg) -> Msg {
    Message::Plugin(crate::ui::Action::Preset(message))
}

fn abbreviate(name: &str) -> String {
    if name.chars().count() <= NAME_CHARS {
        return name.to_owned();
    }
    let mut short: String = name.chars().take(NAME_CHARS - 1).collect();
    short.push('…');
    short
}

/// Pro's selector menu: a raised dark panel sharing the controls' corner
/// radius, the hovered row lifted, the current preset in the accent.
fn menu_style() -> truce_iced::iced::widget::container::Style {
    truce_iced::iced::widget::container::Style {
        background: Some(Color::from_rgb(0.11, 0.125, 0.135).into()),
        border: Border {
            color: style::MUTED.scale_alpha(0.4),
            width: 1.0,
            radius: style::CONTROL_RADIUS.into(),
        },
        shadow: Shadow {
            color: Color::BLACK.scale_alpha(0.3),
            offset: Vector::new(0.0, 4.0),
            blur_radius: 10.0,
        },
        ..Default::default()
    }
}

fn menu_item<'a, R: FreeRenderer + 'a>(
    label: String,
    message: Option<PresetMsg>,
    current: bool,
) -> Element<'a, Msg, Theme, R> {
    let available = message.is_some();
    button(
        text(label)
            .size(14)
            .line_height(LineHeight::Absolute(18.0.into())),
    )
    .width(Length::Fill)
    .height(ITEM_HEIGHT)
    .padding(Padding::from([3.0, 12.0]))
    .style(move |_, status| {
        let hovered = matches!(status, button::Status::Hovered | button::Status::Pressed);
        button::Style {
            background: hovered.then(|| Color::from_rgb(0.18, 0.20, 0.21).into()),
            text_color: if !available {
                DIM.scale_alpha(0.5)
            } else if current || hovered {
                style::ACCENT
            } else {
                style::INK
            },
            ..button::Style::default()
        }
    })
    .on_press_maybe(message.map(preset))
    .into()
}

fn divider<'a, R: FreeRenderer + 'a>() -> Element<'a, Msg, Theme, R> {
    container(
        container(Space::new())
            .width(Length::Fill)
            .height(1)
            .style(|_| truce_iced::iced::widget::container::Style {
                background: Some(style::MUTED.scale_alpha(0.25).into()),
                ..Default::default()
            }),
    )
    .height(DIVIDER)
    .padding(Padding::from([4.0, 8.0]))
    .into()
}

fn place<'a, R: iced_core::Renderer + 'a>(
    bounds: [f32; 4],
    content: impl Into<Element<'a, Msg, Theme, R>>,
) -> Element<'a, Msg, Theme, R> {
    crate::ui::place(bounds, content)
}
