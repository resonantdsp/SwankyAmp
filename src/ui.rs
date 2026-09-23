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
use truce_iced::iced::widget::{
    Column, Space, column, container, mouse_area, row, stack, text, toggler,
};
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
        layers.extend(header(self.notice.as_ref()));
        layers.extend(levels_meters());
        for control in layout::CONTROLS {
            layers.push(match control.kind {
                ControlKind::Knob => control_column(control, params),
                ControlKind::Toggle => cabinet_toggle(control, params),
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

fn header<'a, R: FreeRenderer + 'a>(notice: Option<&Notice>) -> Vec<Element<'a, Msg, Theme, R>> {
    let [top, height] = HEADER_CONTROL;
    vec![
        place(
            [22.0, 7.0, 250.0, 50.0],
            column![
                text("SWANKY AMP").size(24).font(style::BOLD).color(INK),
                text("FREE 2.0").size(10).font(style::BOLD).color(ACCENT),
            ]
            .spacing(1),
        ),
        place(
            [716.0, top, height, height],
            notice_control(notice_action(notice)),
        ),
        place([756.0, top, 150.0, height], preset_bar()),
        place(
            [918.0, top, 80.0, height],
            container(text("OVERSAMPLING").size(10).color(DIM))
                .width(Length::Fill)
                .height(Length::Fill)
                .align_x(Alignment::End)
                .center_y(Length::Fill),
        ),
        place(
            [1006.0, top, 60.0, height],
            container(text("AUTO").size(12).font(style::BOLD).color(INK))
                .width(Length::Fill)
                .height(Length::Fill)
                .center(Length::Fill)
                .style(|_| style::outlined(true)),
        ),
    ]
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
            container(text("INIT").size(12).font(style::BOLD).color(INK))
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

fn cabinet_toggle<'a, R: FreeRenderer + 'a>(
    spec: layout::ControlSpec,
    params: &'a ParamCache<SwankyAmpParams>,
) -> Element<'a, Msg, Theme, R> {
    let id = spec.id;
    let toggle = toggler(params.get(id) >= 0.5)
        .on_toggle(move |on| {
            Message::Param(ParamMessage::Batch(vec![
                ParamMessage::BeginEdit(id),
                ParamMessage::SetNormalized(id, if on { 1.0 } else { 0.0 }),
                ParamMessage::EndEdit(id),
            ]))
        })
        .size(18.0)
        .style(|_, status| {
            // A toggler that has not seen an event yet reports itself
            // disabled; only the switch position decides the colour.
            let (toggler::Status::Active { is_toggled: on }
            | toggler::Status::Hovered { is_toggled: on }
            | toggler::Status::Disabled { is_toggled: on }) = status;
            toggler::Style {
                background: if on { ACCENT } else { DIM.scale_alpha(0.35) }.into(),
                background_border_width: 0.0,
                background_border_color: Color::TRANSPARENT,
                foreground: INK.into(),
                foreground_border_width: 0.0,
                foreground_border_color: Color::TRANSPARENT,
                text_color: None,
                border_radius: None,
                padding_ratio: 0.1,
            }
        });
    let mut component = Component::new(format!("parameter.{id}.toggle"), "toggle", "native");
    component.parameter = Some(id);
    place(
        [spec.center[0] - 42.0, spec.center[1] - 11.0, 70.0, 24.0],
        row![
            text(spec.label).size(11).color(DIM),
            layout::mark(component, toggle)
        ]
        .align_y(Alignment::Center)
        .spacing(8),
    )
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
    use super::{NoticeAction, display_value, notice_action};
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
}
