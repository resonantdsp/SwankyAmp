use crate::{
    layout::{self, Component, ControlKind, SurfaceSpec},
    meters::MeterState,
    params::SwankyAmpParams,
    preset_bar::{PresetBar, PresetMsg},
    release_notice::{self, Notice},
    style,
    widgets::{FreeRenderer, Knob, Msg, NoticeGlyph, Target},
};
use iced_core::{Element, Length, Padding, Theme, mouse, text::LineHeight};
use std::path::PathBuf;
use std::sync::{Arc, OnceLock};
use truce::prelude::Params;
use truce_iced::iced::widget::{
    Column, Row, Space, button, center, column, container, mouse_area, opaque, row, rule, stack,
    text,
};
use truce_iced::iced::{Alignment, Border, Color, Subscription, Task, event, keyboard, window};
use truce_iced::{IcedPlugin, Message, ParamCache, ParamMessage, PluginContext};

const INK: Color = style::INK;
const DIM: Color = Color::from_rgb(0.49, 0.53, 0.56);
const PANEL: Color = Color::from_rgb(0.014, 0.020, 0.026);
const HEADER: Color = Color::from_rgb(0.007, 0.010, 0.013);
/// Without a bake the groove leaves no mark, so each section rules its
/// outline in the groove floor's colour to keep the grouping legible.
const GROOVE: Color = Color::from_rgb(0.002, 0.004, 0.006);
const ACCENT: Color = style::ACCENT;
/// Every header action shares one height and one centre line.
const HEADER_CONTROL: [f32; 2] = [14.0, 24.0];
/// Pro's gap between header groups, wider than any gap inside a group.
const HEADER_GROUP_GAP: f32 = 10.0;
const OVERSAMPLING_ID: u32 = 21;
const CONTROL_WIDTH: f32 = 88.0;
const KNOB_ROW_HEIGHT: f32 = 68.0;

#[derive(Debug, Clone)]
pub enum Action {
    Information(bool),
    Browse(&'static str),
    CopyDiagnostics,
    Notices,
    /// Escape: closes whichever of the panel and the preset menu is open.
    Dismiss,
    Preset(PresetMsg),
    Focus(bool),
    Pointer(bool),
    /// The interface size, in percent, for this installation.
    InterfaceSize(u16),
}

pub struct FreeUi {
    releases: Option<release_notice::Service>,
    notice: Option<Notice>,
    /// Whether the information panel is over the editor.
    information: bool,
    /// Whether the diagnostics were copied since the panel opened.
    diagnostics_copied: bool,
    meters: Option<Arc<MeterState>>,
    meter_levels: [f32; 4],
    meter_revision: u64,
    focused: bool,
    hovered: bool,
    presets: PresetBar,
    owner: Option<Arc<SwankyAmpParams>>,
    /// The knob a pointer gesture is turning, whose readout shows tenths.
    turning: Option<u32>,
    /// How large this installation draws the interface, in percent.
    interface_size: u16,
    /// Where the size is remembered, or nothing for an editor that must not
    /// touch the machine's settings.
    settings: Option<PathBuf>,
    /// Why the last chosen size could not be remembered.
    size_error: Option<String>,
}

impl FreeUi {
    /// The editor without a release check, as layout export and other
    /// offline tools draw it.
    pub fn resting() -> Self {
        Self {
            releases: None,
            notice: None,
            information: false,
            diagnostics_copied: false,
            meters: None,
            meter_levels: [0.0; 4],
            meter_revision: 0,
            focused: true,
            hovered: false,
            presets: PresetBar::offline(),
            owner: None,
            turning: None,
            interface_size: crate::interface::DEFAULT,
            settings: None,
            size_error: None,
        }
    }

    /// The resting editor at the size the installation in `settings` chose,
    /// remembering a new choice there.
    fn installed(settings: Option<PathBuf>) -> Self {
        Self {
            interface_size: crate::interface::load(settings.as_deref()),
            settings,
            ..Self::resting()
        }
    }

    /// Meters go dark while the window has lost focus and the pointer is
    /// elsewhere, so a background editor stops repainting under running
    /// audio.
    fn displays_live(&self) -> bool {
        self.focused || self.hovered
    }

    fn sync_meters(&mut self) {
        match &self.meters {
            Some(meters) if self.displays_live() => {
                let snapshot = meters.snapshot();
                self.meter_levels = snapshot.levels;
                self.meter_revision = snapshot.revision;
            }
            _ => self.meter_levels = [0.0; 4],
        }
    }

    fn latest_notice(&self) -> Option<Notice> {
        self.releases
            .as_ref()
            .map_or_else(|| self.notice.clone(), release_notice::Service::current)
    }

    pub fn view_content<'a, R: FreeRenderer + 'a>(
        &'a self,
        params: &'a ParamCache<SwankyAmpParams>,
    ) -> Element<'a, Msg, Theme, R> {
        let mut layers: Vec<Element<'a, Msg, Theme, R>> = Vec::new();
        let baked = R::LOAD_ARTWORK && crate::artwork::loaded();
        for panel in layout::PANELS {
            let color = if baked {
                None
            } else if panel.appearance == "graphite-header" {
                Some(HEADER)
            } else {
                Some(PANEL)
            };
            layers.push(surface(panel, color));
        }
        for section in layout::SECTIONS {
            layers.push(surface(section, None));
        }
        layers.push(surface(layout::SWITCH, None));
        if baked && let Some(backdrop) = crate::artwork::backdrop::<R>(params, self.meter_levels) {
            layers.push(backdrop);
        }
        for section in layout::SECTIONS {
            layers.push(place(
                [
                    section.bounds[0] + 12.0,
                    section.bounds[1] + 9.0,
                    150.0,
                    14.0,
                ],
                text(section.appearance.replace('-', " ").to_uppercase())
                    .size(12)
                    .font(style::BOLD)
                    .line_height(LineHeight::Absolute(12.0.into()))
                    .color(INK),
            ));
        }
        layers.extend(header(
            self.notice.as_ref(),
            self.information,
            &self.presets,
            params,
        ));
        layers.extend(levels_meters(self.meter_levels));
        for control in layout::CONTROLS {
            layers.push(match control.kind {
                ControlKind::Knob => {
                    control_column(control, params, self.turning == Some(control.id))
                }
                ControlKind::Toggle => cabinet_switch(control, params),
            });
        }
        let (line, color) = match (self.presets.status(), self.presets.footer(params)) {
            (Some(status), _) => (status.to_owned(), INK),
            (None, Some(name)) => (name, INK),
            (None, None) => (
                "DRAG TO TURN   ·   SHIFT FOR FINE CONTROL   ·   RIGHT-CLICK TO RESET".to_owned(),
                DIM,
            ),
        };
        let mut spec = Component::new("footer.line", "text", "native");
        spec.text = Some(line.clone());
        layers.push(footer(
            FOOTER_TEXT,
            layout::mark(
                spec,
                text(line)
                    .size(FOOTER_TEXT_SIZE)
                    .font(style::FONT)
                    .color(color),
            ),
        ));
        layers.push(footer(
            [RIGHT_EDGE - 124.0, 124.0],
            text("RESONANT DSP")
                .size(10)
                .color(DIM)
                .width(Length::Fill)
                .align_x(iced_core::text::Alignment::Right),
        ));
        layers.extend(self.presets.menu(PRESET_FIELD, params));
        if self.information {
            layers.push(information_overlay(
                self.notice.as_ref(),
                self.diagnostics_copied,
                self.interface_size,
                self.size_error.as_deref(),
            ));
        }
        stack(layers)
            .width(style::WIDTH)
            .height(style::HEIGHT)
            .into()
    }
}

impl IcedPlugin<SwankyAmpParams> for FreeUi {
    type Message = Action;

    fn new(params: Arc<SwankyAmpParams>) -> Self {
        let mut ui = Self {
            releases: Some(release_notice::Service::start()),
            meters: Some(Arc::clone(&params.meter_state)),
            presets: PresetBar::live(&params),
            owner: Some(Arc::clone(&params)),
            // Some hosts never send focus to an embedded editor, so it
            // starts live until a focus or pointer event says otherwise.
            ..Self::installed(crate::interface::folder())
        };
        if let Some(name) = CAPTURED_MENU.get() {
            ui.presets = PresetBar::captured_menu(name);
        }
        if let Some(release) = CAPTURED_INFORMATION.get() {
            ui.releases = None;
            ui.notice = release_notice::notice_for(release.as_deref());
            ui.information = true;
        }
        ui.sync_meters();
        ui
    }

    fn subscription(&self) -> Subscription<Msg> {
        event::listen_with(|event, _, _| window_action(&event).map(Message::Plugin))
    }

    fn update(
        &mut self,
        message: Msg,
        params: &ParamCache<SwankyAmpParams>,
        ctx: &PluginContext<SwankyAmpParams>,
    ) -> Task<Msg> {
        match message {
            Message::Tick => {
                self.notice = self.latest_notice();
                self.sync_meters();
                self.presets.sync(params.params());
                self.presets.poll(params);
            }
            // A bare BeginEdit opens a drag on a knob; one-shot changes
            // arrive as a batch and never touch the readout's precision.
            Message::Param(ParamMessage::BeginEdit(id)) => self.turning = Some(id),
            Message::Param(ParamMessage::EndEdit(id)) if self.turning == Some(id) => {
                self.turning = None;
            }
            Message::Plugin(Action::Preset(message)) => {
                self.presets.update(message, params, ctx);
            }
            Message::Plugin(Action::Information(open)) => {
                self.information = open;
                self.diagnostics_copied = false;
                self.size_error = None;
            }
            Message::Plugin(Action::InterfaceSize(size)) => {
                self.interface_size = size;
                self.size_error = self
                    .settings
                    .as_deref()
                    .and_then(|folder| crate::interface::save(folder, size).err());
            }
            Message::Plugin(Action::CopyDiagnostics) => {
                truce_iced::clipboard::write(
                    iced_core::clipboard::Kind::Standard,
                    crate::diagnostics::report(params.params()),
                );
                self.diagnostics_copied = true;
            }
            Message::Plugin(Action::Browse(url)) => release_notice::open_in_browser(url),
            Message::Plugin(Action::Notices) => release_notice::show_notices(),
            Message::Plugin(Action::Dismiss) => {
                self.information = false;
                self.presets.update(PresetMsg::Close, params, ctx);
            }
            Message::Plugin(Action::Focus(focused)) => {
                self.focused = focused;
                self.sync_meters();
            }
            Message::Plugin(Action::Pointer(hovered)) => {
                self.hovered = hovered;
                self.sync_meters();
                // The window goes on reporting the last position after the
                // pointer leaves, so the field never hears it go.
                if !hovered {
                    self.presets.update(PresetMsg::Hover(false), params, ctx);
                }
            }
            _ => {}
        }
        Task::none()
    }

    // A notice lands from the worker and meter levels from the audio thread
    // while the editor may be idle; asking for a frame lets the next tick
    // pick them up. Settled meters publish no new revision, so a quiet
    // instance stops asking.
    fn needs_redraw(&self) -> bool {
        let notice = self.releases.is_some() && self.latest_notice() != self.notice;
        let meters = self.displays_live()
            && self
                .meters
                .as_ref()
                .is_some_and(|meters| meters.revision() != self.meter_revision);
        let presets = self
            .owner
            .as_ref()
            .is_some_and(|params| self.presets.needs_redraw(params));
        notice || meters || presets
    }

    fn title(&self) -> String {
        "Swanky Amp 2".into()
    }

    fn zoom(&self) -> f64 {
        crate::interface::zoom(self.interface_size)
    }

    fn view<'a>(
        &'a self,
        params: &'a ParamCache<SwankyAmpParams>,
    ) -> Element<'a, Msg, Theme, iced_wgpu::Renderer> {
        self.view_content(params)
    }
}

/// What the editor makes of window-wide events, whichever widget is under
/// the pointer.
fn window_action(event: &iced_core::Event) -> Option<Action> {
    Some(match event {
        iced_core::Event::Window(window::Event::Focused) => Action::Focus(true),
        iced_core::Event::Window(window::Event::Unfocused) => Action::Focus(false),
        iced_core::Event::Mouse(mouse::Event::CursorMoved { .. }) => Action::Pointer(true),
        iced_core::Event::Mouse(mouse::Event::CursorLeft) => Action::Pointer(false),
        iced_core::Event::Keyboard(keyboard::Event::KeyPressed {
            key: keyboard::Key::Named(keyboard::key::Named::Escape),
            ..
        }) => Action::Dismiss,
        _ => return None,
    })
}

fn surface<'a, R: FreeRenderer + 'a>(
    spec: SurfaceSpec,
    color: Option<Color>,
) -> Element<'a, Msg, Theme, R> {
    let mut component = Component::new(spec.id, spec.kind, spec.appearance);
    component.radius = spec.radius;
    let outline = (!R::LOAD_ARTWORK || !crate::artwork::loaded())
        .then_some(spec.radius)
        .flatten();
    place(
        spec.bounds,
        layout::mark(
            component,
            container(Space::new())
                .width(Length::Fill)
                .height(Length::Fill)
                .style(move |_| truce_iced::iced::widget::container::Style {
                    background: color.map(Into::into),
                    border: outline.map_or_else(Border::default, |radius| Border {
                        color: GROOVE,
                        width: 2.0,
                        radius: radius.into(),
                    }),
                    ..Default::default()
                }),
        ),
    )
}

pub(crate) fn place<'a, R: iced_core::Renderer + 'a>(
    bounds: [f32; 4],
    content: impl Into<Element<'a, Msg, Theme, R>>,
) -> Element<'a, Msg, Theme, R> {
    let [x, y, width, height] = bounds;
    container(
        container(content)
            .width(width)
            .height(height)
            .align_x(Alignment::Start)
            .align_y(Alignment::Start),
    )
    .width(Length::Fill)
    .height(Length::Fill)
    .padding(Padding {
        top: y,
        right: 0.0,
        bottom: 0.0,
        left: x,
    })
    .align_x(Alignment::Start)
    .align_y(Alignment::Start)
    .into()
}

/// Footer text between `x` and `x + width`, on the footer bar's centre line.
fn footer<'a, R: iced_core::Renderer + 'a>(
    [x, width]: [f32; 2],
    content: impl Into<Element<'a, Msg, Theme, R>>,
) -> Element<'a, Msg, Theme, R> {
    place(
        [
            x,
            style::HEIGHT - style::FOOTER_HEIGHT,
            width,
            style::FOOTER_HEIGHT,
        ],
        container(content).center_y(Length::Fill),
    )
}

/// Where the footer's line of help or status sets, and at what size.
pub(crate) const FOOTER_TEXT: [f32; 2] = [style::MARGIN, 680.0];
pub(crate) const FOOTER_TEXT_SIZE: f32 = 10.0;

/// How wide a single line of text sets.
pub(crate) fn text_width(body: &str, size: f32, font: iced_core::Font) -> f32 {
    use iced_core::text::{Paragraph, Shaping, Text, Wrapping};
    style::load_fonts();
    iced_graphics::text::Paragraph::with_text(Text {
        content: body,
        bounds: iced_core::Size::INFINITE,
        size: iced_core::Pixels(size),
        line_height: LineHeight::default(),
        font,
        align_x: Default::default(),
        align_y: iced_core::alignment::Vertical::Top,
        shaping: Shaping::default(),
        wrapping: Wrapping::None,
    })
    .min_width()
}

/// The group boxes' right edge, where the header's last action and the
/// footer's mark end too.
const RIGHT_EDGE: f32 = style::WIDTH - style::MARGIN;

/// Where the preset field sits: right to left from the boxes' edge, one
/// group gap between header actions.
const OVERSAMPLING_FIELD: [f32; 2] = [RIGHT_EDGE - 58.0, 58.0];
const PRESET_FIELD: [f32; 4] = [
    OVERSAMPLING_FIELD[0] - HEADER_GROUP_GAP - crate::preset_bar::FIELD_WIDTH,
    HEADER_CONTROL[0],
    crate::preset_bar::FIELD_WIDTH,
    HEADER_CONTROL[1],
];

fn header<'a, R: FreeRenderer + 'a>(
    notice: Option<&Notice>,
    information: bool,
    presets: &PresetBar,
    params: &ParamCache<SwankyAmpParams>,
) -> Vec<Element<'a, Msg, Theme, R>> {
    let [top, height] = HEADER_CONTROL;
    // Pro's wordmark: the name in bold ink and the edition beside it at the
    // same size in the product's accent, rose here where Pro's is orange.
    let wordmark = row![
        text("SWANKY AMP").size(25).font(style::BOLD).color(INK),
        text("FREE").size(25).font(style::FONT).color(ACCENT),
    ]
    .spacing(6)
    .align_y(Alignment::Center);
    let oversampling = OVERSAMPLING_FIELD;
    let notice_x = PRESET_FIELD[0] - HEADER_GROUP_GAP - height;
    vec![
        place(
            [style::MARGIN, 0.0, 400.0, style::HEADER_HEIGHT],
            container(wordmark).center_y(Length::Fill),
        ),
        place(
            [notice_x, top, height, height],
            notice_control(notice_action(notice), information),
        ),
        place(PRESET_FIELD, presets.field(params)),
        place(
            [oversampling[0], top, oversampling[1], height],
            oversampling_toggle(params),
        ),
    ]
}

/// Choices the Oversampling parameter steps through: Auto, then 1x, 2x, 4x.
const OVERSAMPLING_CHOICES: usize = 4;

/// The button reads as Pro's: the factor the engine runs when it is known,
/// lit whenever it oversamples or is left to choose.
fn oversampling_label(choice: usize, resolved: Option<usize>) -> (String, bool) {
    let factor = resolved
        .or_else(|| choice.checked_sub(1))
        .map(|doublings| 1usize << doublings);
    let label = match factor {
        None => "Auto".to_string(),
        Some(factor) if choice == 0 => format!("Auto {factor}×"),
        Some(factor) => format!("{factor}×"),
    };
    (label, factor.is_none_or(|factor| factor > 1))
}

fn oversampling_toggle<'a, R: FreeRenderer + 'a>(
    params: &ParamCache<SwankyAmpParams>,
) -> Element<'a, Msg, Theme, R> {
    let choice = (params.get(OVERSAMPLING_ID) * (OVERSAMPLING_CHOICES - 1) as f64)
        .round()
        .clamp(0.0, (OVERSAMPLING_CHOICES - 1) as f64) as usize;
    let (label, lit) = oversampling_label(choice, params.params().resolved_oversampling.get());
    let next = (choice + 1) % OVERSAMPLING_CHOICES;
    mouse_area(
        container(text(label).size(12).color(if lit { INK } else { DIM }))
            .width(Length::Fill)
            .height(Length::Fill)
            .center(Length::Fill)
            .style(move |_| style::outlined(lit)),
    )
    .on_press(Message::Param(ParamMessage::Batch(vec![
        ParamMessage::BeginEdit(OVERSAMPLING_ID),
        ParamMessage::SetNormalized(
            OVERSAMPLING_ID,
            next as f64 / (OVERSAMPLING_CHOICES - 1) as f64,
        ),
        ParamMessage::EndEdit(OVERSAMPLING_ID),
    ])))
    .interaction(mouse::Interaction::Pointer)
    .into()
}

#[derive(Debug, PartialEq, Eq)]
enum NoticeAction {
    Information,
    Download,
}

fn notice_action(notice: Option<&Notice>) -> NoticeAction {
    if notice.is_some() {
        NoticeAction::Download
    } else {
        NoticeAction::Information
    }
}

fn notice_control<'a, R: FreeRenderer + 'a>(
    action: NoticeAction,
    information: bool,
) -> Element<'a, Msg, Theme, R> {
    let download = action == NoticeAction::Download;
    let body = container(NoticeGlyph {
        download,
        color: if download { ACCENT } else { INK },
    })
    .width(Length::Fill)
    .height(Length::Fill)
    .style(move |_| style::outlined(download || information));
    layout::mark(
        Component::new("action.information", "button", "native"),
        mouse_area(body)
            .on_press(Message::Plugin(Action::Information(!information)))
            .interaction(mouse::Interaction::Pointer),
    )
}

/// Set by the capture command: a review capture renders a freshly created
/// editor and cannot press the button, so it asks for the panel here, with
/// the release that stands in for the website's answer.
static CAPTURED_INFORMATION: OnceLock<Option<String>> = OnceLock::new();

/// Editors created after this open with the information panel showing, and
/// announce `release` if it is newer than this build.
pub fn capture_information(release: Option<String>) {
    let _ = CAPTURED_INFORMATION.set(release);
}

/// Like the panel, the capture tool cannot open the preset menu itself.
static CAPTURED_MENU: OnceLock<String> = OnceLock::new();

/// Editors created after this open with `name` as the chosen user preset, its
/// menu open and the pointer over the field.
pub fn capture_menu(name: String) {
    let _ = CAPTURED_MENU.set(name);
}

const INFORMATION_WIDTH: f32 = 340.0;

/// Pro's Settings panel without its licensing: what this is, a newer release
/// when there is one, the interface size, and where to find more. It dims the
/// editor behind it, and a press anywhere outside closes it.
fn information_overlay<'a, R: FreeRenderer + 'a>(
    notice: Option<&Notice>,
    diagnostics_copied: bool,
    interface_size: u16,
    size_error: Option<&str>,
) -> Element<'a, Msg, Theme, R> {
    let line = |id: &str, body: String, size: f32, font, color| {
        let mut spec = Component::new(id, "text", "native");
        spec.text = Some(body.clone());
        layout::mark(
            spec,
            text(body)
                .size(size)
                .font(font)
                .line_height(LineHeight::Absolute(17.0.into()))
                .color(color),
        )
    };
    let mut content = Column::new().spacing(11).push(line(
        "information.product",
        format!("Swanky Amp Free {}", env!("CARGO_PKG_VERSION")),
        15.0,
        style::BOLD,
        INK,
    ));
    if let Some(notice) = notice {
        content = content.push(
            row![
                line(
                    "information.release",
                    format!("Swanky Amp Free {} is available", notice.version),
                    13.0,
                    style::FONT,
                    ACCENT,
                ),
                link("Download", Action::Browse(notice.url)),
            ]
            .spacing(8)
            .align_y(Alignment::Center),
        );
    }
    content = content.push(size_selector(interface_size));
    if let Some(error) = size_error {
        content = content.push(line(
            "information.size-error",
            error.to_owned(),
            12.0,
            style::FONT,
            ACCENT,
        ));
    }
    let copy = if diagnostics_copied {
        "Copied"
    } else {
        "Copy diagnostics"
    };
    let links = Row::with_children(
        release_notice::LINKS
            .iter()
            .map(|(body, url)| link(body, Action::Browse(url))),
    )
    .push(layout::mark(
        Component::new("information.diagnostics", "button", "native"),
        link(copy, Action::CopyDiagnostics),
    ))
    .spacing(14);
    content = content
        .push(rule::horizontal(1).style(|_| rule::Style {
            color: style::MUTED.scale_alpha(0.25),
            radius: 0.0.into(),
            fill_mode: rule::FillMode::Full,
            snap: false,
        }))
        .push(links)
        .push(layout::mark(
            Component::new("information.notices", "button", "native"),
            link("Third-party licences", Action::Notices),
        ));
    if let Some(notice) = asio_notice() {
        content = content.push(
            row![
                crate::asio_logo::AsioLogo { height: 26.0 },
                line(
                    "information.asio",
                    notice.to_owned(),
                    10.0,
                    style::FONT,
                    DIM,
                )
            ]
            .spacing(9)
            .align_y(Alignment::Center),
        );
    }
    let panel = layout::mark(
        Component::new("information", "dialog", "native"),
        container(content)
            .width(INFORMATION_WIDTH)
            .padding(15)
            .style(|_| truce_iced::iced::widget::container::Style {
                background: Some(Color::from_rgb(0.085, 0.095, 0.105).into()),
                border: Border {
                    color: style::MUTED.scale_alpha(0.4),
                    width: 1.0,
                    radius: style::CONTROL_RADIUS.into(),
                },
                shadow: iced_core::Shadow {
                    color: Color::BLACK.scale_alpha(0.45),
                    offset: iced_core::Vector::new(0.0, 5.0),
                    blur_radius: 14.0,
                },
                ..Default::default()
            }),
    );
    opaque(
        mouse_area(
            center(opaque(panel)).style(|_| truce_iced::iced::widget::container::Style {
                background: Some(Color::BLACK.scale_alpha(0.85).into()),
                ..Default::default()
            }),
        )
        .on_press(Message::Plugin(Action::Information(false))),
    )
}

/// Every size on offer at once, the chosen one outlined in the accent as a
/// lit header action is: there are few enough that one press should do.
fn size_selector<'a, R: FreeRenderer + 'a>(chosen: u16) -> Element<'a, Msg, Theme, R> {
    let choices = crate::interface::SIZES.map(|size| {
        let lit = size == chosen;
        let mut spec = Component::new(format!("information.size.{size}"), "button", "native");
        spec.text = Some(crate::interface::label(size));
        layout::mark(
            spec,
            mouse_area(
                container(text(crate::interface::label(size)).size(12).color(if lit {
                    INK
                } else {
                    DIM
                }))
                .center_x(48.0)
                .center_y(HEADER_CONTROL[1])
                .style(move |_| style::outlined(lit)),
            )
            .on_press(Message::Plugin(Action::InterfaceSize(size)))
            .interaction(mouse::Interaction::Pointer),
        )
    });
    let mut spec = Component::new("information.interface-size", "selector", "native");
    spec.text = Some(crate::interface::label(chosen));
    layout::mark(
        spec,
        row![
            text("Interface size")
                .size(13)
                .font(style::FONT)
                .color(INK)
                .width(Length::Fill),
            Row::with_children(choices).spacing(4),
        ]
        .align_y(Alignment::Center),
    )
}

/// Steinberg's ASIO usage guidelines ask for the ASIO Compatible logo with
/// this attribution, in their wording, in the About panel of a product that
/// runs on ASIO by default. Only the Windows standalone built with ASIO does;
/// the plug-ins play through whatever driver their host has open.
fn asio_notice() -> Option<&'static str> {
    #[cfg(feature = "standalone")]
    if truce_standalone::driver::asio_built() {
        return Some("ASIO is a registered trademark of Steinberg Media Technologies GmbH.");
    }
    None
}

/// Plain text that acts, as Pro's panel links are, lit in the accent under
/// the pointer.
fn link<'a, R: FreeRenderer + 'a>(
    body: &'static str,
    action: Action,
) -> Element<'a, Msg, Theme, R> {
    button(text(body).size(12).font(style::FONT))
        .padding([3, 0])
        .style(link_style)
        .on_press(Message::Plugin(action))
        .into()
}

fn link_style(_: &Theme, status: button::Status) -> button::Style {
    button::Style {
        text_color: if matches!(status, button::Status::Hovered | button::Status::Pressed) {
            ACCENT
        } else {
            style::MUTED
        },
        ..Default::default()
    }
}

fn default_normalized(params: &ParamCache<SwankyAmpParams>, id: u32) -> f32 {
    params
        .params()
        .param_infos()
        .into_iter()
        .find(|info| info.id == id)
        .map_or(0.0, |info| info.range.normalize(info.default_plain) as f32)
}

fn control_column<'a, R: FreeRenderer + 'a>(
    spec: layout::ControlSpec,
    params: &'a ParamCache<SwankyAmpParams>,
    turning: bool,
) -> Element<'a, Msg, Theme, R> {
    let enabled = spec.in_effect(params.get(layout::CABINET_SWITCH) >= 0.5);
    let fade = if enabled { 1.0 } else { style::DISABLED_ALPHA };
    let knob = Knob {
        target: Target {
            id: spec.id,
            value: params.get(spec.id) as f32,
            default: default_normalized(params, spec.id),
        },
        large: spec.large,
        enabled,
    };
    let label = text(spec.label)
        .size(13)
        .line_height(LineHeight::Absolute(16.0.into()))
        .width(Length::Fill)
        .align_x(iced_core::text::Alignment::Center)
        .color(INK.scale_alpha(fade));
    let value = text(display_value(spec.id, params.get(spec.id) as f32, turning))
        .size(13)
        .line_height(LineHeight::Absolute(16.0.into()))
        .width(Length::Fill)
        .align_x(iced_core::text::Alignment::Center)
        .color(DIM.scale_alpha(fade));
    let body = column![
        container(knob)
            .height(KNOB_ROW_HEIGHT)
            .center_y(Length::Fill),
        label,
        value,
    ]
    .spacing(3)
    .width(CONTROL_WIDTH);
    place(
        [
            spec.center[0] - CONTROL_WIDTH / 2.0,
            spec.center[1] - KNOB_ROW_HEIGHT / 2.0,
            CONTROL_WIDTH,
            KNOB_ROW_HEIGHT + 38.0,
        ],
        body,
    )
}

/// Whole units at rest, as 1.4 showed them, and tenths while the knob is
/// turned so a fine move is visible.
fn display_value(id: u32, normalized: f32, turning: bool) -> String {
    let (value, decibels) = match id {
        0 | 1 => (normalized.mul_add(70.0, -35.0), true),
        7 => (normalized.mul_add(4.0, 1.0), false),
        _ => (normalized * 10.0, false),
    };
    match (decibels, turning) {
        (true, false) => format!("{value:+.0} dB"),
        (true, true) => format!("{value:+.1} dB"),
        (false, false) => format!("{value:02.0}"),
        (false, true) => format!("{value:.1}"),
    }
}

/// The cabinet switch: a brushed aluminium disc in a V track two discs
/// tall, up for on. A press anywhere on its column flips it and a
/// right-click restores the default, as the knobs reset.
fn cabinet_switch<'a, R: FreeRenderer + 'a>(
    spec: layout::ControlSpec,
    params: &'a ParamCache<SwankyAmpParams>,
) -> Element<'a, Msg, Theme, R> {
    let id = spec.id;
    let on = params.get(id) >= 0.5;
    let set = move |value: bool| {
        Message::Param(ParamMessage::Batch(vec![
            ParamMessage::BeginEdit(id),
            ParamMessage::SetNormalized(id, if value { 1.0 } else { 0.0 }),
            ParamMessage::EndEdit(id),
        ]))
    };
    let default_on = default_normalized(params, id) >= 0.5;
    let baked = R::LOAD_ARTWORK && crate::artwork::loaded();
    let [cx, cy] = spec.center;
    let mut layers: Vec<Element<'a, Msg, Theme, R>> = Vec::new();
    if !baked {
        layers.extend(flat_switch(layout::SWITCH.bounds, on));
    }
    layers.push(place(
        [
            cx - CONTROL_WIDTH / 2.0,
            cy + KNOB_ROW_HEIGHT / 2.0 + 3.0,
            CONTROL_WIDTH,
            16.0,
        ],
        text(if on { "ON" } else { "OFF" })
            .size(13)
            .line_height(LineHeight::Absolute(16.0.into()))
            .width(Length::Fill)
            .align_x(iced_core::text::Alignment::Center)
            .color(if on { ACCENT } else { DIM }),
    ));
    let mut component = Component::new(format!("parameter.{id}.switch"), "toggle", "native");
    component.parameter = Some(id);
    layers.push(place(
        [
            cx - CONTROL_WIDTH / 2.0,
            cy - KNOB_ROW_HEIGHT / 2.0,
            CONTROL_WIDTH,
            KNOB_ROW_HEIGHT + 19.0,
        ],
        layout::mark(
            component,
            mouse_area(Space::new().width(Length::Fill).height(Length::Fill))
                .on_press(set(!on))
                .on_right_press(set(default_on))
                .interaction(mouse::Interaction::Pointer),
        ),
    ));
    stack(layers).into()
}

/// The switch without its bake: the track and a flat disc at the same place
/// the compositor would stamp the baked one.
fn flat_switch<'a, R: FreeRenderer + 'a>(
    track: [f32; 4],
    on: bool,
) -> Vec<Element<'a, Msg, Theme, R>> {
    let [x, y, width, height] = style::disc_sprite_bounds(track, on);
    let diameter = style::PhysicalStyle::default().switch_diameter;
    let disc = [
        x + (width - diameter) / 2.0,
        y + (height - diameter) / 2.0,
        diameter,
        diameter,
    ];
    let fill = move |color: Color, radius: f32| {
        move |_: &Theme| truce_iced::iced::widget::container::Style {
            background: Some(color.into()),
            border: Border {
                radius: radius.into(),
                ..Border::default()
            },
            ..Default::default()
        }
    };
    let blank = || {
        container(Space::new())
            .width(Length::Fill)
            .height(Length::Fill)
    };
    vec![
        place(track, blank().style(fill(GROOVE, track[2] / 2.0))),
        place(
            disc,
            blank().style(fill(Color::from_rgb(0.48, 0.51, 0.53), diameter / 2.0)),
        ),
    ]
}

fn levels_meters<'a, R: FreeRenderer + 'a>(levels: [f32; 4]) -> Vec<Element<'a, Msg, Theme, R>> {
    let mut layers = Vec::new();
    for (meter, level) in layout::METERS.into_iter().zip(levels) {
        let color = if meter.appearance.starts_with("output") {
            style::METER_OUTPUT
        } else {
            style::METER_INPUT
        };
        let component = Component::new(meter.id, meter.kind, meter.appearance);
        let [x, y, width, height] = meter.bounds;
        layers.push(place(
            meter.bounds,
            layout::mark(component, meter_column(color, height, level)),
        ));
        // The caption shares the knob readout's line, as in Pro.
        let caption = if meter.appearance.ends_with("left") {
            "L"
        } else {
            "R"
        };
        layers.push(place(
            [x - 4.0, y + height + 3.0, width + 8.0, 16.0],
            text(caption)
                .size(10)
                .font(style::BOLD)
                .line_height(LineHeight::Absolute(16.0.into()))
                .width(Length::Fill)
                .align_x(iced_core::text::Alignment::Center)
                .color(DIM),
        ));
    }
    layers
}

/// Without a bake the cells are flat: lit cells in full colour from the
/// bottom, matching which cells the baked compositor lights.
fn meter_column<'a, R: FreeRenderer + 'a>(
    color: Color,
    height: f32,
    fraction: f32,
) -> Element<'a, Msg, Theme, R> {
    let pitch = height / style::METER_BARS as f32;
    let gap = pitch * style::METER_GAP;
    let bar_height = pitch - gap;
    let baked = R::LOAD_ARTWORK && crate::artwork::loaded();
    let lit = crate::meters::active_bars(fraction, style::METER_BARS);
    let bars: Vec<Element<'a, Msg, Theme, R>> = (0..style::METER_BARS)
        .rev()
        .map(|bar| {
            let alpha = if baked {
                0.0
            } else if bar < lit {
                1.0
            } else {
                0.12
            };
            container(Space::new())
                .width(Length::Fill)
                .height(bar_height)
                .style(move |_| truce_iced::iced::widget::container::Style {
                    background: Some(color.scale_alpha(alpha).into()),
                    border: Border {
                        color: color.scale_alpha(alpha * 0.7),
                        width: 0.75,
                        radius: 1.5.into(),
                    },
                    ..Default::default()
                })
                .into()
        })
        .collect();
    Column::with_children(bars)
        .spacing(gap)
        .padding([gap / 2.0, 0.0])
        .into()
}

#[cfg(test)]
mod tests {
    use super::{Action, FreeUi, NoticeAction, display_value, notice_action, oversampling_label};
    use crate::layout::{self, Measure};
    use crate::{NullHost, params::SwankyAmpParams, release_notice::notice_for, style};
    use iced_core::{Event, Point, Size, clipboard, mouse};
    use iced_runtime::user_interface::{Cache, UserInterface};
    use std::sync::Arc;
    use truce_iced::{IcedPlugin, Message, ParamCache, PluginContext};

    /// An editor driven as a player drives it, by pressing where things are.
    struct Editor {
        ui: FreeUi,
        params: ParamCache<SwankyAmpParams>,
        ctx: PluginContext<SwankyAmpParams>,
        /// The widgets' state between events, such as what the pointer is
        /// over, as the editor's window keeps it.
        cache: Option<Cache>,
    }

    impl Editor {
        fn new(release: Option<&str>) -> Self {
            let params = Arc::new(SwankyAmpParams::default());
            let mut ui = FreeUi::resting();
            ui.notice = notice_for(release);
            Self {
                ui,
                params: ParamCache::new(Arc::clone(&params)),
                ctx: PluginContext::new(Arc::new(NullHost), params),
                cache: None,
            }
        }

        fn bounds(&self, id: &str) -> Option<[f32; 4]> {
            layout::components(&self.ui, &self.params, &mut Measure)
                .into_iter()
                .find(|component| component.id == id)
                .map(|component| component.bounds)
        }

        fn text(&self, id: &str) -> Option<String> {
            layout::components(&self.ui, &self.params, &mut Measure)
                .into_iter()
                .find(|component| component.id == id)
                .and_then(|component| component.text)
        }

        fn press(&mut self, at: [f32; 2]) {
            self.send(mouse::Event::ButtonPressed(mouse::Button::Left), at);
            self.send(mouse::Event::ButtonReleased(mouse::Button::Left), at);
        }

        fn point(&mut self, at: [f32; 2]) {
            self.send(
                mouse::Event::CursorMoved {
                    position: Point::new(at[0], at[1]),
                },
                at,
            );
        }

        /// The window reports the last position with the pointer's leaving.
        fn leave(&mut self, last: [f32; 2]) {
            self.send(mouse::Event::CursorLeft, last);
        }

        fn send(&mut self, event: mouse::Event, [x, y]: [f32; 2]) {
            let mut renderer = Measure;
            let mut messages = Vec::new();
            let event = Event::Mouse(event);
            // What the window's subscription hears arrives first, as it
            // does in the editor.
            messages.extend(super::window_action(&event).map(Message::Plugin));
            let mut interface = UserInterface::build(
                self.ui.view_content::<Measure>(&self.params),
                Size::new(style::WIDTH, style::HEIGHT),
                self.cache.take().unwrap_or_default(),
                &mut renderer,
            );
            interface.update(
                &[event],
                mouse::Cursor::Available(Point::new(x, y)),
                &mut renderer,
                &mut clipboard::Null,
                &mut messages,
            );
            self.cache = Some(interface.into_cache());
            for message in messages {
                let _ = self.ui.update(message, &self.params, &self.ctx);
            }
        }

        fn centre(&self, id: &str) -> [f32; 2] {
            let [x, y, width, height] = self
                .bounds(id)
                .unwrap_or_else(|| panic!("{id} must be on screen"));
            [x + width / 2.0, y + height / 2.0]
        }

        fn press_button(&mut self) {
            let [x, y, width, height] = self.bounds("action.information").unwrap();
            self.press([x + width / 2.0, y + height / 2.0]);
        }
    }

    #[test]
    fn the_information_button_opens_a_panel_naming_this_version() {
        let mut editor = Editor::new(None);
        assert_eq!(editor.bounds("information"), None);
        editor.press_button();
        assert_eq!(
            editor.text("information.product"),
            Some(format!("Swanky Amp Free {}", env!("CARGO_PKG_VERSION")))
        );
        assert_eq!(editor.text("information.release"), None);

        let [x, y, ..] = editor.bounds("information").unwrap();
        editor.press([x + 4.0, y + 4.0]);
        assert!(
            editor.bounds("information").is_some(),
            "a press inside the panel closed it"
        );
    }

    #[test]
    fn the_panel_closes_on_the_button_a_press_outside_or_escape() {
        let mut editor = Editor::new(None);
        editor.press_button();
        editor.press_button();
        assert_eq!(editor.bounds("information"), None, "the button again");

        editor.press_button();
        editor.press([style::WIDTH - 4.0, style::HEIGHT - 4.0]);
        assert_eq!(editor.bounds("information"), None, "a press outside");

        editor.press_button();
        let _ = editor.ui.update(
            Message::Plugin(Action::Dismiss),
            &editor.params,
            &editor.ctx,
        );
        assert_eq!(editor.bounds("information"), None, "Escape");
    }

    #[test]
    fn an_interface_size_is_the_installations_and_opens_every_later_editor_at_it() {
        use truce::prelude::Params;
        let folder =
            std::env::temp_dir().join(format!("swanky-amp-interface-size-{}", std::process::id()));
        let _ = std::fs::remove_dir_all(&folder);
        let mut editor = Editor::new(None);
        editor.ui = FreeUi::installed(Some(folder.clone()));
        editor.press_button();
        assert_eq!(
            editor.text("information.interface-size").as_deref(),
            Some("100%"),
            "the information panel must offer the interface size, starting at 100 %"
        );
        let state = (
            editor.params.params().collect_values(),
            editor.params.params().serialize_persist(),
        );
        editor.press(editor.centre("information.size.150"));
        assert_eq!(
            editor.ui.zoom(),
            1.5,
            "the editor must ask for the chosen size"
        );
        assert_eq!(
            editor.text("information.interface-size").as_deref(),
            Some("150%")
        );
        assert_eq!(
            (
                editor.params.params().collect_values(),
                editor.params.params().serialize_persist(),
            ),
            state,
            "the size belongs to the computer, never to host state or presets"
        );

        let next = FreeUi::installed(Some(folder.clone()));
        assert_eq!(next.zoom(), 1.5, "a later editor must open at the size");
        let window = crate::editor_at(
            Arc::new(SwankyAmpParams::default()),
            crate::interface::load(Some(&folder)),
        )
        .size();
        assert_eq!(
            window,
            (1296, 768),
            "the host must be told the window of the chosen size"
        );
        let _ = std::fs::remove_dir_all(&folder);
    }

    /// An editor whose preset folder holds `names`, empty when it is dropped.
    struct UserPresets(std::path::PathBuf);

    impl UserPresets {
        /// The folder is `tag`'s own, so tests running at once never share it.
        /// Returns the saved presets' keys too.
        fn new(editor: &mut Editor, tag: &str, names: &[&str]) -> (Self, Vec<String>) {
            use crate::presets::Library;
            let root =
                std::env::temp_dir().join(format!("swanky-amp-{tag}-{}", std::process::id()));
            let _ = std::fs::remove_dir_all(&root);
            let library = Library::with_user_root(Some(root.clone()));
            let keys = names
                .iter()
                .map(|name| {
                    library
                        .save(name, &crate::dsp::amp::AmpControls::default())
                        .unwrap()
                        .key
                })
                .collect();
            editor.ui.presets = crate::preset_bar::PresetBar::with_library(library);
            (Self(root), keys)
        }
    }

    impl Drop for UserPresets {
        fn drop(&mut self) {
            let _ = std::fs::remove_dir_all(&self.0);
        }
    }

    fn field_centre() -> [f32; 2] {
        let [x, y, width, height] = super::PRESET_FIELD;
        [x + width / 2.0, y + height / 2.0]
    }

    #[test]
    fn a_long_preset_name_reads_whole_in_a_menu_that_stays_in_the_window() {
        let long = "Friday night rehearsal lead with the extra gain";
        let endless = "An endless name ".repeat(12);
        let mut editor = Editor::new(None);
        let _presets = UserPresets::new(&mut editor, "menu-width", &[long, endless.trim()]);
        editor.press(field_centre());

        let [x, _, width, _] = editor.bounds("preset.menu").expect("the menu opens");
        assert!(
            x >= 0.0 && x + width <= style::WIDTH,
            "the menu runs off the window at {x}..{}",
            x + width
        );
        let rows = editor.text("preset.menu").unwrap();
        assert!(
            rows.lines().any(|row| row == long),
            "{long:?} is not listed whole in {rows:?}"
        );
        assert!(
            rows.lines().any(|row| row.starts_with("An endless name")),
            "the longest name is not listed in {rows:?}"
        );
    }

    /// A shared preset is named by its file, which can hold line breaks, tabs
    /// and as many characters as the file system allows. It still lists as a
    /// short single line, and naming it in the footer keeps the edited mark;
    /// a file whose name shows nothing lists as Untitled.
    #[test]
    fn a_shared_preset_with_an_unruly_file_name_lists_on_one_line() {
        use crate::preset_bar::PresetMsg;
        use truce::prelude::Params;
        let mut editor = Editor::new(None);
        let (presets, _) = UserPresets::new(&mut editor, "unruly-names", &["Plain"]);
        let saved = presets.0.join("Plain.xml");
        let unruly = format!("Shared\rlead\tfrom a friend {}", "x".repeat(200));
        for name in [unruly.as_str(), "\u{200B}"] {
            std::fs::copy(&saved, presets.0.join(format!("{name}.xml"))).unwrap();
        }
        editor.press(field_centre());

        let rows = editor.text("preset.menu").unwrap();
        let shared = rows
            .lines()
            .find(|row| row.starts_with("Shared lead from a friend"))
            .unwrap_or_else(|| panic!("the shared preset does not list on one line in {rows:?}"));
        assert!(
            shared.chars().count() <= 128 && shared.ends_with('…'),
            "{shared:?} is not capped with an ellipsis"
        );
        assert!(
            rows.lines().any(|row| row == "Untitled"),
            "a name with nothing visible is not listed as Untitled in {rows:?}"
        );

        let key = format!("user:{unruly}.xml");
        let _ = editor.ui.update(
            Message::Plugin(Action::Preset(PresetMsg::Select(key))),
            &editor.params,
            &editor.ctx,
        );
        let output = editor.params.params().output.id();
        editor.params.params().set_plain(output, 0.5);
        editor.point(field_centre());
        let line = editor.text("footer.line").unwrap();
        let set = super::text_width(&line, super::FOOTER_TEXT_SIZE, style::FONT);
        assert!(
            line.starts_with("Shared lead from a friend") && line.ends_with(" (edited)"),
            "the footer names the shared preset as {line:?}"
        );
        assert!(
            set <= super::FOOTER_TEXT[1],
            "{line:?} sets {set:.1} px in a footer of {} px",
            super::FOOTER_TEXT[1]
        );
    }

    #[test]
    fn hovering_the_preset_field_names_the_preset_in_full_within_the_footer() {
        use crate::preset_bar::PresetMsg;
        use truce::prelude::Params;
        let long = "Friday night rehearsal lead with the extra gain on the neck pickup";
        let mut editor = Editor::new(None);
        let (_presets, keys) = UserPresets::new(&mut editor, "hover-name", &[long]);
        let _ = editor.ui.update(
            Message::Plugin(Action::Preset(PresetMsg::Select(keys[0].clone()))),
            &editor.params,
            &editor.ctx,
        );
        let output = editor.params.params().output.id();
        editor.params.params().set_plain(output, 0.5);

        editor.point(field_centre());
        let line = editor.text("footer.line").unwrap();
        assert_eq!(line, format!("{long} (edited)"));
        let set = super::text_width(&line, super::FOOTER_TEXT_SIZE, style::FONT);
        assert!(
            set <= super::FOOTER_TEXT[1],
            "{line:?} sets {set:.1} px in a footer of {} px",
            super::FOOTER_TEXT[1]
        );

        editor.point([style::WIDTH / 2.0, style::HEIGHT / 2.0]);
        assert_ne!(
            editor.text("footer.line").as_deref(),
            Some(line.as_str()),
            "the name stays in the footer after the pointer leaves the field"
        );

        editor.point(field_centre());
        editor.leave(field_centre());
        assert_ne!(
            editor.text("footer.line").as_deref(),
            Some(line.as_str()),
            "the name stays in the footer after the pointer leaves the window from the field"
        );
    }

    #[test]
    fn the_panel_announces_a_newer_release() {
        let mut editor = Editor::new(Some("99.0.0"));
        editor.press_button();
        assert_eq!(
            editor.text("information.release"),
            Some("Swanky Amp Free 99.0.0 is available".into())
        );
    }

    #[test]
    fn readouts_preserve_the_released_free_scale() {
        assert_eq!(display_value(0, 0.0, false), "-35 dB");
        assert_eq!(display_value(1, 0.5, false), "+0 dB");
        assert_eq!(display_value(0, 1.0, false), "+35 dB");
        assert_eq!(display_value(7, 0.5, false), "03");
        assert_eq!(display_value(14, 0.3, false), "03");
    }

    #[test]
    fn a_turned_knob_reads_in_tenths_so_fine_moves_show() {
        assert_eq!(display_value(1, 0.52, true), "+1.4 dB");
        assert_eq!(display_value(7, 0.51, true), "3.0");
        assert_eq!(display_value(14, 0.337, true), "3.4");
        assert_eq!(display_value(14, 0.337, false), "03");
    }

    #[test]
    fn the_header_offers_a_download_only_for_a_reported_newer_release() {
        let action = |version| notice_action(notice_for(version).as_ref());
        assert_eq!(action(Some("99.0.0")), NoticeAction::Download);
        assert_eq!(
            action(Some(env!("CARGO_PKG_VERSION"))),
            NoticeAction::Information
        );
        assert_eq!(action(Some("1.4.0")), NoticeAction::Information);
        assert_eq!(action(Some("99.0")), NoticeAction::Information);
        assert_eq!(action(None), NoticeAction::Information);
    }

    #[test]
    fn the_oversampling_button_names_the_running_factor_and_lights_when_it_oversamples() {
        let cases = [
            (0, None, "Auto", true),
            (0, Some(0), "Auto 1×", false),
            (0, Some(1), "Auto 2×", true),
            (1, None, "1×", false),
            (2, None, "2×", true),
            (3, None, "4×", true),
            // A fixed choice the host rate caps shows what actually runs.
            (3, Some(1), "2×", true),
            (2, Some(0), "1×", false),
        ];
        for (choice, resolved, label, lit) in cases {
            assert_eq!(
                oversampling_label(choice, resolved),
                (label.to_string(), lit),
                "choice {choice} with {resolved:?} resolved"
            );
        }
    }
}
