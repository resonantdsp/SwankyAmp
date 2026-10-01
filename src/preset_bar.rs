//! The header's preset field and its menu: Pro's preset bar reduced to the
//! single field Free has room for, with the actions in the menu.

use std::cell::RefCell;
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

use crate::layout::{self, Component};
use crate::params::SwankyAmpParams;
use crate::presets::{Entry, ImportJob, Library, Scope, legacy_root};
use crate::style;
use crate::widgets::{FreeRenderer, Msg};

const DIM: Color = Color::from_rgb(0.49, 0.53, 0.56);
/// The field's width, and the narrowest its menu gets. It holds the longest
/// factory name with its modified mark, and every action in the menu.
pub const FIELD_WIDTH: f32 = 164.0;
/// Each arrow's share of the field, either side of the name.
const ARROW_WIDTH: f32 = 22.0;
/// What the name keeps clear of each arrow's share, so a name filling its
/// room still reads apart from the arrows.
const NAME_INSET: f32 = 4.0;
/// The widest a name with its mark can set in the field.
const NAME_ROOM: f32 = FIELD_WIDTH - 2.0 * (ARROW_WIDTH + NAME_INSET);
/// The field's name and the menu's rows set at one size, which the fitting
/// measures with.
const TEXT_SIZE: f32 = 12.0;
/// Marks a preset whose controls have moved since it was chosen.
const MODIFIED: &str = " •";
/// The menu's question before a user preset is removed: this, the name, "?".
const REMOVE_PREFIX: &str = "Remove ";
/// Names the current preset in the footer, where there is room to say it.
const EDITED: &str = " (edited)";
const ITEM_HEIGHT: f32 = 20.0;
const ITEM_PADDING: f32 = 10.0;
/// What a menu wider than the field keeps clear of the window's edges: the
/// editor's margin, so one pushed left ends in line with the header.
const MENU_MARGIN: f32 = style::MARGIN;
/// The menu's outline, which a row's text keeps clear of.
const MENU_BORDER: f32 = 1.0;
/// The menu stops short of the footer; a longer user list scrolls.
const MENU_BOTTOM: f32 = style::HEIGHT - style::FOOTER_HEIGHT - 6.0;
/// Long enough to read a sentence, short enough not to linger over playing.
const STATUS_SECONDS: u64 = 6;

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
    /// The pointer arrived over the field or left it.
    Hover(bool),
}

type Pending<T> = Arc<Mutex<Option<T>>>;

pub struct PresetBar {
    library: Library,
    entries: Vec<Entry>,
    /// The menu's rows for `entries`, measured once per listing.
    rows: MenuRows,
    current: Entry,
    /// The values the current preset set, for telling when it is modified.
    baseline: Vec<(u32, f64)>,
    host_revision: u64,
    pub open: bool,
    /// Whether the pointer is over the field, whose full name the footer
    /// then shows.
    hovered: bool,
    status: Option<(String, Instant)>,
    import: Option<ImportJob>,
    naming: Option<Pending<Option<PathBuf>>>,
    /// The user preset a first press on Remove asked about. Deleting a file
    /// cannot be undone, so only a second press on the same preset does it.
    removing: Option<String>,
    /// The current name as the field and the menu set it, kept until the
    /// preset or its modified state changes, since the view is rebuilt with
    /// every display frame.
    shown: RefCell<Option<Shown>>,
}

/// The current preset's name fitted to the field, to the menu's Remove
/// question and to the footer, for one name, modified state and menu width.
struct Shown {
    name: String,
    modified: bool,
    menu_width: f32,
    field: String,
    remove: String,
    footer: String,
}

impl Shown {
    fn new(name: &str, modified: bool, menu_width: f32) -> Self {
        let mark = if modified { MODIFIED } else { "" };
        let room = row_room(menu_width) - measure(REMOVE_PREFIX, TEXT_SIZE);
        Self {
            name: name.to_owned(),
            modified,
            menu_width,
            field: fitted(name, mark, NAME_ROOM, TEXT_SIZE),
            remove: format!("{REMOVE_PREFIX}{}", fitted(name, "?", room, TEXT_SIZE)),
            footer: footer_name(name, modified),
        }
    }
}

/// The footer line while the pointer is over the field: the whole name, which
/// the field may have had to cut, marked when edited. Only a name wider than
/// the footer itself is cut, and never its mark.
fn footer_name(name: &str, modified: bool) -> String {
    let mark = if modified { EDITED } else { "" };
    fitted(
        name,
        mark,
        crate::ui::FOOTER_TEXT[1],
        crate::ui::FOOTER_TEXT_SIZE,
    )
}

/// The open menu's preset rows as they read, and the width the widest needs.
#[derive(Default)]
struct MenuRows {
    labels: Vec<String>,
    width: f32,
}

impl MenuRows {
    /// Each name whole where the window allows, cut to end in an ellipsis
    /// only where it does not; the menu is never narrower than the field.
    fn new(entries: &[Entry]) -> Self {
        let widest = style::WIDTH - 2.0 * MENU_MARGIN;
        let room = row_room(widest);
        let mut width = FIELD_WIDTH;
        let labels = entries
            .iter()
            .map(|entry| {
                let label = fitted(&entry.name, "", room, TEXT_SIZE);
                width = width.max(widest - room + measure(&label, TEXT_SIZE));
                label
            })
            .collect();
        Self {
            labels,
            // Whole pixels keep the text and the outline crisp.
            width: width.ceil().min(widest),
        }
    }
}

/// What a row's text has in a menu `width` wide.
fn row_room(width: f32) -> f32 {
    width - 2.0 * (ITEM_PADDING + MENU_BORDER)
}

fn measure(body: &str, size: f32) -> f32 {
    crate::ui::text_width(body, size, style::FONT)
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
        bar.list(bar.library.list().entries);
        bar.import = legacy_root().and_then(|source| ImportJob::first_run(&bar.library, source));
        bar.sync(params);
        bar
    }

    /// Editors created by the capture tool open with this bar: `name` listed
    /// as the player's own preset and chosen, and the menu open under the
    /// pointer, which rests on the field.
    pub fn captured_menu(name: &str) -> Self {
        let mut bar = Self::offline();
        let entry = Entry::user(PathBuf::from(format!("{name}.xml")));
        let mut entries = bar.entries.clone();
        entries.push(entry.clone());
        bar.list(entries);
        bar.current = entry;
        bar.open = true;
        bar.hovered = true;
        bar
    }

    pub(crate) fn with_library(library: Library) -> Self {
        let entries = library.builtin();
        let current = entries[0].clone();
        let baseline = library.tone(&current);
        Self {
            library,
            rows: MenuRows::new(&entries),
            entries,
            current,
            baseline,
            host_revision: 0,
            open: false,
            hovered: false,
            status: None,
            import: None,
            naming: None,
            removing: None,
            shown: RefCell::new(None),
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

    fn list(&mut self, entries: Vec<Entry>) {
        self.rows = MenuRows::new(&entries);
        self.entries = entries;
    }

    fn refresh(&mut self) {
        let listing = self.library.list();
        self.list(listing.entries);
        if !listing.unreadable.is_empty() {
            self.report(Err(format!(
                "Skipped unreadable presets: {}",
                listing.unreadable.join(", ")
            )));
        }
    }

    /// The current name fitted for the field, the Remove question and the
    /// footer.
    fn shown<T>(&self, params: &ParamCache<SwankyAmpParams>, pick: impl Fn(&Shown) -> T) -> T {
        let modified = self.modified(params);
        let mut shown = self.shown.borrow_mut();
        let current = shown.as_ref().is_some_and(|shown| {
            shown.name == self.current.name
                && shown.modified == modified
                && shown.menu_width == self.rows.width
        });
        if !current {
            *shown = Some(Shown::new(&self.current.name, modified, self.rows.width));
        }
        pick(shown.as_ref().expect("the fitted name was just set"))
    }

    /// The footer line naming the current preset in full while the pointer
    /// is over the field. A fresh status wins: the arrows sit inside the
    /// field, so a failed step would otherwise go unread.
    pub fn footer(&self, params: &ParamCache<SwankyAmpParams>) -> Option<String> {
        (self.hovered && self.status.is_none())
            .then(|| self.shown(params, |shown| shown.footer.clone()))
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
        if let PresetMsg::Hover(over) = message {
            self.hovered = over;
            return;
        }
        self.sync(params.params());
        let armed = self.removing.take();
        let mut close = !matches!(message, PresetMsg::Toggle);
        match message {
            PresetMsg::Toggle => {
                self.open = !self.open;
                if self.open {
                    self.refresh();
                }
            }
            PresetMsg::Close | PresetMsg::Hover(_) => {}
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
                let outcome = match (&self.current.scope, self.current.path.clone()) {
                    (Scope::User, Some(path)) => {
                        let saved = self.library.save_to(&path, &params.params().snapshot());
                        if saved.is_err() {
                            // The file may be gone; the menu should list what
                            // the folder holds now.
                            self.refresh();
                        }
                        self.keep(saved, params)
                    }
                    _ => Err("Use Save as… to keep a copy of this preset.".into()),
                };
                if let Err(error) = outcome {
                    self.report(Err(error));
                }
            }
            PresetMsg::SaveAs => self.ask_name(),
            PresetMsg::Remove if armed.as_deref() != Some(self.current.key.as_str()) => {
                self.removing = Some(self.current.key.clone());
                close = false;
            }
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

    /// Lists and chooses a preset just saved.
    fn keep(
        &mut self,
        saved: Result<Entry, String>,
        params: &ParamCache<SwankyAmpParams>,
    ) -> Result<(), String> {
        let entry = saved?;
        self.refresh();
        self.report(Ok(format!("Saved {}", entry.name)));
        self.remember(entry, params.params());
        Ok(())
    }

    /// The name comes from the chosen file. Some dialogs return the name
    /// without the extension, so only a trailing .xml is dropped and a name
    /// like "Lead v1.2" keeps its dots.
    fn save_as(&mut self, path: &std::path::Path, params: &ParamCache<SwankyAmpParams>) {
        let named_xml = path
            .extension()
            .is_some_and(|extension| extension.eq_ignore_ascii_case("xml"));
        let name = if named_xml {
            path.file_stem()
        } else {
            path.file_name()
        }
        .map(|name| name.to_string_lossy().into_owned())
        .unwrap_or_default();
        let saved = self
            .library
            .save_as(path, &name, &params.params().snapshot());
        if let Err(error) = self.keep(saved, params) {
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
        let name = self.shown(params, |shown| shown.field.clone());
        let chevron = |glyph, message: Option<PresetMsg>| {
            let available = message.is_some();
            let glyph = container(text(glyph).size(17).color(DIM.scale_alpha(if available {
                1.0
            } else {
                0.35
            })))
            .center_x(ARROW_WIDTH)
            .center_y(Length::Fill);
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
        let field = container(
            row![
                chevron("‹", previous),
                mouse_area(
                    container(
                        text(name)
                            .size(TEXT_SIZE)
                            .font(style::FONT)
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
        .style(move |_| style::outlined(open));
        mouse_area(field)
            .on_enter(preset(PresetMsg::Hover(true)))
            .on_exit(preset(PresetMsg::Hover(false)))
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
        for (entry, label) in self.entries.iter().zip(&self.rows.labels) {
            if previous_scope.is_some_and(|scope| scope != entry.scope) {
                presets.push(divider());
            }
            previous_scope = Some(entry.scope);
            presets.push(item(
                label.clone(),
                Some(PresetMsg::Select(entry.key.clone())),
                entry.key == self.current.key,
            ));
        }
        let user = self.current.scope == Scope::User;
        let confirming = self.removing.as_deref() == Some(self.current.key.as_str());
        let remove = if confirming {
            self.shown(params, |shown| shown.remove.clone())
        } else {
            "Remove".into()
        };
        let actions: Vec<Element<'a, Msg, Theme, R>> = vec![
            item(
                "Save".into(),
                (user && modified).then_some(PresetMsg::Save),
                false,
            ),
            item("Save as…".into(), Some(PresetMsg::SaveAs), false),
            item(remove, user.then_some(PresetMsg::Remove), confirming),
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
        let top = field[1] + field[3] + 3.0;
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
        let width = self.rows.width;
        let left = field[0].min(style::WIDTH - MENU_MARGIN - width);
        let mut spec = Component::new("preset.menu", "menu", "native");
        spec.text = Some(self.rows.labels.join("\n"));
        vec![
            place(
                [0.0, 0.0, style::WIDTH, style::HEIGHT],
                mouse_area(Space::new().width(Length::Fill).height(Length::Fill))
                    .on_press(preset(PresetMsg::Close))
                    .on_right_press(preset(PresetMsg::Close)),
            ),
            place([left, top, width, height], layout::mark(spec, panel)),
        ]
    }
}

const MENU_PADDING: f32 = 3.0;
const DIVIDER: f32 = 7.0;

fn preset(message: PresetMsg) -> Msg {
    Message::Plugin(crate::ui::Action::Preset(message))
}

/// The name followed by `mark`, set at `size` within `room`: whole when it
/// fits, or cut to end in an ellipsis before the mark.
fn fitted(name: &str, mark: &str, room: f32, size: f32) -> String {
    let fits = |body: &str| measure(body, size) <= room;
    let whole = format!("{name}{mark}");
    if fits(&whole) {
        return whole;
    }
    use unicode_segmentation::UnicodeSegmentation;
    let clusters: Vec<&str> = name.graphemes(true).collect();
    let cut = |kept: usize| format!("{}…{mark}", clusters[..kept].concat().trim_end());
    // Measuring is what costs, so the cut is found by bisection rather than by
    // trying every length.
    let (mut fitting, mut over) = (0, clusters.len());
    while over - fitting > 1 {
        let kept = (fitting + over) / 2;
        if fits(&cut(kept)) {
            fitting = kept;
        } else {
            over = kept;
        }
    }
    cut(fitting)
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
            offset: Vector::new(0.0, 3.0),
            blur_radius: 8.0,
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
            .size(TEXT_SIZE)
            .font(style::FONT)
            .wrapping(iced_core::text::Wrapping::None)
            .line_height(LineHeight::Absolute(15.0.into())),
    )
    .width(Length::Fill)
    .height(ITEM_HEIGHT)
    .padding(Padding::from([2.5, ITEM_PADDING]))
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
    .padding(Padding::from([3.0, 6.0]))
    .into()
}

fn place<'a, R: iced_core::Renderer + 'a>(
    bounds: [f32; 4],
    content: impl Into<Element<'a, Msg, Theme, R>>,
) -> Element<'a, Msg, Theme, R> {
    crate::ui::place(bounds, content)
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::NullHost;
    use crate::dsp::amp::AmpControls;

    /// A shared file's name can read differently once listed: a double space
    /// collapses and a zero-width character is dropped. Saving that preset
    /// must rewrite its own file, never write a second one under the listed
    /// name, which could replace another preset.
    #[test]
    fn saving_a_user_preset_rewrites_its_own_file() {
        use truce::prelude::Params;
        let root = std::env::temp_dir().join(format!("swanky-save-own-{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&root);
        let library = Library::with_user_root(Some(root.clone()));
        let plain = crate::presets::saved_as(&library, "plain", &AmpControls::default());
        let plain = plain.path.unwrap();
        let params = Arc::new(SwankyAmpParams::default());
        let cache = ParamCache::new(Arc::clone(&params));
        let ctx = PluginContext::new(Arc::new(NullHost), Arc::clone(&params));
        let mut bar = PresetBar::with_library(library);
        for name in ["Double  space", "Zero\u{200B}width"] {
            let file = root.join(format!("{name}.xml"));
            std::fs::copy(&plain, &file).unwrap();
            let before = std::fs::read(&file).unwrap();
            let files = || {
                let mut names: Vec<_> = std::fs::read_dir(&root)
                    .unwrap()
                    .map(|entry| entry.unwrap().file_name())
                    .collect();
                names.sort();
                names
            };
            let listed = files();

            bar.update(PresetMsg::Select(format!("user:{name}.xml")), &cache, &ctx);
            params.set_plain(params.output.id(), 0.5);
            bar.update(PresetMsg::Save, &cache, &ctx);
            assert_eq!(
                files(),
                listed,
                "saving {name:?} changed the folder's files"
            );
            assert_ne!(
                std::fs::read(&file).unwrap(),
                before,
                "saving {name:?} left its file as it was"
            );
        }
        std::fs::remove_dir_all(root).unwrap();
    }

    #[test]
    fn remove_deletes_a_user_preset_only_when_pressed_twice() {
        let root = std::env::temp_dir().join(format!("swanky-remove-{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&root);
        let library = Library::with_user_root(Some(root.clone()));
        let saved = crate::presets::saved_as(&library, "mine", &AmpControls::default());
        let file = saved.path.clone().unwrap();
        let params = Arc::new(SwankyAmpParams::default());
        let cache = ParamCache::new(Arc::clone(&params));
        let ctx = PluginContext::new(Arc::new(NullHost), Arc::clone(&params));
        let mut bar = PresetBar::with_library(library);
        let mut press = |message| bar.update(message, &cache, &ctx);

        press(PresetMsg::Select(saved.key.clone()));
        press(PresetMsg::Toggle);
        press(PresetMsg::Remove);
        assert!(
            file.exists(),
            "the first press on Remove deleted the preset"
        );
        // Leaving the menu forgets the question.
        press(PresetMsg::Close);
        press(PresetMsg::Toggle);
        press(PresetMsg::Remove);
        assert!(
            file.exists(),
            "a press after reopening the menu deleted the preset"
        );
        press(PresetMsg::Remove);
        assert!(!file.exists(), "confirming Remove kept the preset");
        std::fs::remove_dir_all(root).unwrap();
    }

    struct Folder {
        root: PathBuf,
        params: Arc<SwankyAmpParams>,
        cache: ParamCache<SwankyAmpParams>,
        ctx: PluginContext<SwankyAmpParams>,
    }

    impl Folder {
        fn new(name: &str) -> Self {
            let root = std::env::temp_dir().join(format!("swanky-{name}-{}", std::process::id()));
            let _ = std::fs::remove_dir_all(&root);
            std::fs::create_dir_all(&root).unwrap();
            let params = Arc::new(SwankyAmpParams::default());
            Self {
                root,
                cache: ParamCache::new(Arc::clone(&params)),
                ctx: PluginContext::new(Arc::new(NullHost), Arc::clone(&params)),
                params,
            }
        }

        fn library(&self) -> Library {
            Library::with_user_root(Some(self.root.clone()))
        }

        fn files(&self) -> Vec<String> {
            let mut names: Vec<String> = std::fs::read_dir(&self.root)
                .unwrap()
                .map(|entry| entry.unwrap().file_name().to_string_lossy().into_owned())
                .collect();
            names.sort();
            names
        }

        fn turn_output(&self) {
            use truce::prelude::Params;
            self.params.set_plain(self.params.output.id(), 0.5);
        }

        /// The preset the host state now names, as the folder holds it.
        fn remembered(&self) -> AmpControls {
            let library = self.library();
            let entry = library
                .find(&self.params.preset.read())
                .expect("the remembered preset is not listed");
            library.load(&entry).unwrap().unwrap().controls
        }
    }

    impl Drop for Folder {
        fn drop(&mut self) {
            let _ = std::fs::remove_dir_all(&self.root);
        }
    }

    /// On a case-insensitive file system saving as "lead" writes into an
    /// existing "Lead.xml"; the save still succeeds and is chosen.
    #[test]
    fn save_as_a_name_differing_only_in_case_chooses_the_saved_preset() {
        let folder = Folder::new("save-as-case");
        crate::presets::saved_as(&folder.library(), "Lead", &AmpControls::default());
        let mut bar = PresetBar::with_library(folder.library());
        folder.turn_output();

        bar.save_as(&folder.root.join("lead.xml"), &folder.cache);

        let status = bar.status().unwrap_or_default().to_owned();
        assert!(
            status.eq_ignore_ascii_case("Saved lead"),
            "saving as lead reported {status:?}"
        );
        assert_eq!(folder.remembered(), folder.params.snapshot());
    }

    /// A preset renamed or removed outside the editor is not recreated
    /// under its old name; the player is told it is gone.
    #[test]
    fn save_after_the_file_is_renamed_away_reports_it_is_gone() {
        let folder = Folder::new("save-renamed");
        let saved = crate::presets::saved_as(&folder.library(), "mine", &AmpControls::default());
        let mut bar = PresetBar::with_library(folder.library());
        bar.update(PresetMsg::Select(saved.key), &folder.cache, &folder.ctx);
        std::fs::rename(saved.path.unwrap(), folder.root.join("renamed.xml")).unwrap();
        folder.turn_output();

        bar.update(PresetMsg::Save, &folder.cache, &folder.ctx);

        assert_eq!(
            folder.files(),
            ["renamed.xml"],
            "Save recreated the old file"
        );
        let status = bar.status().unwrap_or_default();
        assert!(
            status.contains("no longer"),
            "Save of a missing preset reported {status:?}"
        );
    }

    /// The system dialog asks before replacing only the file it returns, so
    /// Save As replaces a preset only when the dialog returned that very file.
    /// Any other way to the same name writes nothing.
    #[test]
    fn save_as_replaces_only_the_file_the_dialog_returned() {
        let folder = Folder::new("save-as-asked");
        let elsewhere = folder.root.join("elsewhere");
        std::fs::create_dir_all(&elsewhere).unwrap();
        let kept = crate::presets::saved_as(&folder.library(), "Lead", &AmpControls::default());
        let lead = kept.path.clone().unwrap();
        let before = std::fs::read(&lead).unwrap();
        let mut bar = PresetBar::with_library(folder.library());
        folder.turn_output();

        // Another folder, and the preset folder without the extension as a
        // Linux dialog returns it.
        for unasked in [elsewhere.join("Lead.xml"), folder.root.join("Lead")] {
            bar.save_as(&unasked, &folder.cache);
            assert_eq!(
                std::fs::read(&lead).unwrap(),
                before,
                "Save As to {} replaced the preset folder's Lead",
                unasked.display()
            );
            assert!(bar.status().is_some(), "the refused save said nothing");
        }

        bar.save_as(&elsewhere.join("Rhythm.xml"), &folder.cache);
        assert_eq!(
            folder.remembered(),
            folder.params.snapshot(),
            "a new name from another folder was not saved into the preset folder"
        );
        assert_eq!(folder.files(), ["Lead.xml", "Rhythm.xml", "elsewhere"]);

        bar.save_as(&lead, &folder.cache);
        assert_ne!(
            std::fs::read(&lead).unwrap(),
            before,
            "Save As onto the file the dialog returned did not replace it"
        );
    }

    /// Some save dialogs return the name without the extension.
    #[test]
    fn a_name_with_dots_keeps_them() {
        let folder = Folder::new("save-as-dots");
        let mut bar = PresetBar::with_library(folder.library());
        bar.save_as(&folder.root.join("Lead v1.2"), &folder.cache);
        bar.save_as(&folder.root.join("Lead v1.2.xml"), &folder.cache);
        assert_eq!(folder.files(), ["Lead v1.2.xml"]);
    }
}
