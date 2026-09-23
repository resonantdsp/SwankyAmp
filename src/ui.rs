use crate::{
    layout::{self, Component, ControlKind, SurfaceSpec},
    params::SwankyAmpParams,
    release_notice::{self, Notice},
    style,
    widgets::{FreeRenderer, Knob, Msg, NoticeGlyph, Target},
};
use iced_core::{Element, Length, Padding, Theme, mouse, text::LineHeight};
use std::sync::Arc;
use truce::prelude::Params;
use truce_iced::iced::widget::{Column, Space, column, container, mouse_area, row, stack, text};
use truce_iced::iced::{Alignment, Border, Color, Task};
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
const HEADER_CONTROL: [f32; 2] = [17.0, 30.0];
/// Pro's gap between header groups, wider than any gap inside a group.
const HEADER_GROUP_GAP: f32 = 14.0;
const OVERSAMPLING_ID: u32 = 21;
const CONTROL_WIDTH: f32 = 104.0;
const KNOB_ROW_HEIGHT: f32 = 84.0;

#[derive(Debug, Clone)]
pub enum Action {
    OpenReleaseNotice,
}

pub struct FreeUi {
    releases: Option<release_notice::Service>,
    notice: Option<Notice>,
}

impl FreeUi {
    /// The editor without a release check, as layout export and other
    /// offline tools draw it.
    pub fn resting() -> Self {
        Self {
            releases: None,
            notice: None,
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
        if baked && let Some(backdrop) = crate::artwork::backdrop::<R>(params) {
            layers.push(backdrop);
        }
        for section in layout::SECTIONS {
            layers.push(place(
                [
                    section.bounds[0] + 16.0,
                    section.bounds[1] + 12.0,
                    180.0,
                    18.0,
                ],
                text(section.appearance.replace('-', " ").to_uppercase())
                    .size(13)
                    .font(style::BOLD)
                    .line_height(LineHeight::Absolute(14.0.into()))
                    .color(INK),
            ));
        }
        layers.extend(header(self.notice.as_ref(), params));
        layers.extend(levels_meters());
        for control in layout::CONTROLS {
            layers.push(match control.kind {
                ControlKind::Knob => control_column(control, params),
                ControlKind::Toggle => cabinet_switch(control, params),
            });
        }
        layers.push(place(
            [18.0, 614.0, 680.0, 16.0],
            text("DRAG TO TURN   ·   SHIFT FOR FINE CONTROL   ·   RIGHT-CLICK TO RESET")
                .size(10)
                .color(DIM),
        ));
        layers.push(place(
            [938.0, 614.0, 124.0, 16.0],
            text("RESONANT DSP").size(10).color(DIM),
        ));
        stack(layers)
            .width(style::WIDTH)
            .height(style::HEIGHT)
            .into()
    }
}

impl IcedPlugin<SwankyAmpParams> for FreeUi {
    type Message = Action;

    fn new(_: Arc<SwankyAmpParams>) -> Self {
        Self {
            releases: Some(release_notice::Service::start()),
            notice: None,
        }
    }

    fn update(
        &mut self,
        message: Msg,
        _: &ParamCache<SwankyAmpParams>,
        _: &PluginContext<SwankyAmpParams>,
    ) -> Task<Msg> {
        match message {
            Message::Tick => self.notice = self.latest_notice(),
            Message::Plugin(Action::OpenReleaseNotice) => {
                if let Some(notice) = &self.notice {
                    notice.open();
                }
            }
            _ => {}
        }
        Task::none()
    }

    // A notice lands from the worker while the editor may be idle; asking
    // for a frame lets the next tick pick it up.
    fn needs_redraw(&self) -> bool {
        self.releases.is_some() && self.latest_notice() != self.notice
    }

    fn title(&self) -> String {
        "Swanky Amp 2".into()
    }

    fn view<'a>(
        &'a self,
        params: &'a ParamCache<SwankyAmpParams>,
    ) -> Element<'a, Msg, Theme, iced_wgpu::Renderer> {
        self.view_content(params)
    }
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

fn place<'a, R: iced_core::Renderer + 'a>(
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

fn header<'a, R: FreeRenderer + 'a>(
    notice: Option<&Notice>,
    params: &ParamCache<SwankyAmpParams>,
) -> Vec<Element<'a, Msg, Theme, R>> {
    let [top, height] = HEADER_CONTROL;
    // Pro's wordmark: the name in bold ink and the edition beside it at the
    // same size, here in the accent rather than Pro's muted grey.
    let wordmark = row![
        text("SWANKY AMP").size(29).font(style::BOLD).color(INK),
        text("FREE 2.0").size(29).font(style::FONT).color(ACCENT),
    ]
    .spacing(8)
    .align_y(Alignment::Center);
    // Right to left from the boxes' edge, one group gap between actions.
    let oversampling = [1066.0 - 72.0, 72.0];
    let preset = [oversampling[0] - HEADER_GROUP_GAP - 150.0, 150.0];
    let notice_x = preset[0] - HEADER_GROUP_GAP - height;
    vec![
        place(
            [22.0, 0.0, 400.0, style::HEADER_HEIGHT],
            container(wordmark).center_y(Length::Fill),
        ),
        place(
            [notice_x, top, height, height],
            notice_control(notice_action(notice)),
        ),
        place([preset[0], top, preset[1], height], preset_bar()),
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
        container(text(label).size(14).color(if lit { INK } else { DIM }))
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

/// The factory preset stepper as one outlined field; the chevrons sit inside
/// it so the preset name reads as the thing they step through.
fn preset_bar<'a, R: FreeRenderer + 'a>() -> Element<'a, Msg, Theme, R> {
    let chevron = |glyph| {
        container(text(glyph).size(20).color(DIM))
            .width(28)
            .height(Length::Fill)
            .center(Length::Fill)
    };
    container(
        row![
            chevron("‹"),
            container(text("INIT").size(14).color(INK))
                .width(Length::Fill)
                .height(Length::Fill)
                .center(Length::Fill),
            chevron("›"),
        ]
        .height(Length::Fill),
    )
    .width(Length::Fill)
    .height(Length::Fill)
    .style(|_| style::outlined(false))
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

fn notice_control<'a, R: FreeRenderer + 'a>(action: NoticeAction) -> Element<'a, Msg, Theme, R> {
    let download = action == NoticeAction::Download;
    let body = container(NoticeGlyph {
        download,
        color: if download { ACCENT } else { DIM },
    })
    .width(Length::Fill)
    .height(Length::Fill)
    .style(move |_| style::outlined(download));
    if download {
        mouse_area(body)
            .on_press(Message::Plugin(Action::OpenReleaseNotice))
            .interaction(mouse::Interaction::Pointer)
            .into()
    } else {
        body.into()
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
) -> Element<'a, Msg, Theme, R> {
    let knob = Knob {
        target: Target {
            id: spec.id,
            value: params.get(spec.id) as f32,
            default: default_normalized(params, spec.id),
        },
        large: spec.large,
    };
    let label = text(spec.label)
        .size(13)
        .line_height(LineHeight::Absolute(18.0.into()))
        .width(Length::Fill)
        .align_x(iced_core::text::Alignment::Center)
        .color(INK);
    let value = text(display_value(spec.id, params.get(spec.id) as f32))
        .size(14)
        .line_height(LineHeight::Absolute(20.0.into()))
        .width(Length::Fill)
        .align_x(iced_core::text::Alignment::Center)
        .color(DIM);
    let body = column![
        container(knob)
            .height(KNOB_ROW_HEIGHT)
            .center_y(Length::Fill),
        label,
        value,
    ]
    .spacing(4)
    .width(CONTROL_WIDTH);
    place(
        [
            spec.center[0] - CONTROL_WIDTH / 2.0,
            spec.center[1] - KNOB_ROW_HEIGHT / 2.0,
            CONTROL_WIDTH,
            KNOB_ROW_HEIGHT + 46.0,
        ],
        body,
    )
}

fn display_value(id: u32, normalized: f32) -> String {
    if matches!(id, 0 | 1) {
        format!("{:+.0} dB", normalized.mul_add(70.0, -35.0))
    } else if id == 7 {
        format!("{:02.0}", normalized.mul_add(4.0, 1.0))
    } else {
        format!("{:02.0}", normalized * 10.0)
    }
}

/// The cabinet switch: Pro's slider slot and cap stood on end with two
/// positions, up for on. A press anywhere on its column flips it and a
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
            cy + KNOB_ROW_HEIGHT / 2.0 + 4.0,
            CONTROL_WIDTH,
            18.0,
        ],
        text(if on { "ON" } else { "OFF" })
            .size(13)
            .line_height(LineHeight::Absolute(18.0.into()))
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
            KNOB_ROW_HEIGHT + 22.0,
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

/// The switch without its bake: the slot and a flat cap at the same place
/// the compositor would stamp the baked one.
fn flat_switch<'a, R: FreeRenderer + 'a>(
    slot: [f32; 4],
    on: bool,
) -> Vec<Element<'a, Msg, Theme, R>> {
    let physical = style::PhysicalStyle::default();
    let [x, y, width, height] = style::cap_sprite_bounds(slot, on);
    let [cap_width, cap_length] = physical.cap_size;
    let cap = [
        x + (width - cap_width) / 2.0,
        y + (height - cap_length) / 2.0,
        cap_width,
        cap_length,
    ];
    let divot = physical.cap_divot;
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
        place(slot, blank().style(fill(GROOVE, slot[2] / 2.0))),
        place(
            cap,
            blank().style(fill(Color::from_rgb(0.48, 0.51, 0.53), cap_width / 2.0)),
        ),
        place(
            [
                cap[0] + cap_width / 2.0 - divot,
                cap[1] + cap_length / 2.0 - divot,
                2.0 * divot,
                2.0 * divot,
            ],
            blank().style(fill(Color::from_rgb(0.025, 0.03, 0.032), divot)),
        ),
    ]
}

fn levels_meters<'a, R: FreeRenderer + 'a>() -> Vec<Element<'a, Msg, Theme, R>> {
    let mut layers = Vec::new();
    for meter in layout::METERS {
        let color = if meter.appearance.starts_with("output") {
            style::METER_OUTPUT
        } else {
            style::METER_INPUT
        };
        let component = Component::new(meter.id, meter.kind, meter.appearance);
        let [x, y, width, height] = meter.bounds;
        layers.push(place(
            meter.bounds,
            layout::mark(component, meter_column(color, height)),
        ));
        // The caption shares the knob readout's line, as in Pro.
        let caption = if meter.appearance.ends_with("left") {
            "L"
        } else {
            "R"
        };
        layers.push(place(
            [x - 4.0, y + height + 4.0, width + 8.0, 20.0],
            text(caption)
                .size(11)
                .font(style::BOLD)
                .line_height(LineHeight::Absolute(20.0.into()))
                .width(Length::Fill)
                .align_x(iced_core::text::Alignment::Center)
                .color(DIM),
        ));
    }
    layers
}

fn meter_column<'a, R: FreeRenderer + 'a>(color: Color, height: f32) -> Element<'a, Msg, Theme, R> {
    let pitch = height / style::METER_BARS as f32;
    let gap = pitch * style::METER_GAP;
    let bar_height = pitch - gap;
    let bars: Vec<Element<'a, Msg, Theme, R>> = (0..style::METER_BARS)
        .map(|_| {
            let alpha = if R::LOAD_ARTWORK && crate::artwork::loaded() {
                0.0
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
    use super::{NoticeAction, display_value, notice_action, oversampling_label};
    use crate::release_notice::notice_for;

    #[test]
    fn readouts_preserve_the_released_free_scale() {
        assert_eq!(display_value(0, 0.0), "-35 dB");
        assert_eq!(display_value(1, 0.5), "+0 dB");
        assert_eq!(display_value(0, 1.0), "+35 dB");
        assert_eq!(display_value(7, 0.5), "03");
        assert_eq!(display_value(14, 0.3), "03");
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
