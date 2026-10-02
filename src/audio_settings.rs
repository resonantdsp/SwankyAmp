//! The standalone app's audio choices in the information panel: Input, its
//! channels and Output, the same choices as the native Settings menu, with
//! what needs the player said under the box it concerns.

use crate::{
    layout::{self, Component},
    style,
    ui::{Action, DIM},
    widgets::{FreeRenderer, Msg},
};
use iced_core::{Element, Length, Padding, Theme, text::LineHeight};
use std::fmt;
use truce_iced::Message;
use truce_iced::iced::widget::{overlay::menu, pick_list, row, text};
use truce_iced::iced::{Alignment, Border, Color};
use truce_standalone::audio::ChannelRoute;
use truce_standalone::setup::{self, InputNeed, OutputNeed, Setup};

#[derive(Debug, Clone)]
pub enum AudioChoice {
    /// A device to play through, or `None` to turn the input off.
    Input(Option<String>),
    Output(String),
    InputChannels(ChannelRoute),
    /// A picker opened: list the devices again for the next look.
    Refresh,
}

/// Acts on the player's choice through the standalone, which remembers it.
pub fn apply(choice: AudioChoice) {
    match choice {
        AudioChoice::Input(name) => setup::choose_input(name),
        AudioChoice::Output(name) => setup::choose_output(name),
        AudioChoice::InputChannels(route) => setup::choose_input_channels(route),
        AudioChoice::Refresh => setup::refresh(),
    }
}

/// The rows the panel shows for `setup`.
pub fn rows<'a, R: FreeRenderer + 'a>(setup: &Setup) -> Vec<Element<'a, Msg, Theme, R>> {
    let mut rows = Vec::new();
    if setup.takes_input {
        let mut inputs = vec![choice(None, OFF)];
        inputs.extend(
            setup
                .inputs
                .iter()
                .map(|name| choice(Some(name.clone()), name)),
        );
        let shown = setup.input.as_deref().unwrap_or(OFF);
        let need = setup.input_need.as_ref().map(input_need);
        rows.push(field_row(
            "information.input",
            "Input",
            inputs,
            choice(setup.input.clone(), shown),
            need.is_some(),
            AudioChoice::Input,
        ));
        if let Some(need) = need {
            rows.push(note("information.input.note", need, style::ACCENT));
        }
        if setup.built_in_microphone {
            rows.push(note(
                "information.input.warning",
                BUILT_IN_MICROPHONE.to_owned(),
                style::ACCENT,
            ));
        }
        if let Some((count, route)) = setup.input_channels {
            let routes = setup::channel_choices(count)
                .into_iter()
                .map(|route| choice(route, &route.label()))
                .collect();
            rows.push(field_row(
                "information.input-channels",
                "Input channels",
                routes,
                choice(route, &route.label()),
                false,
                AudioChoice::InputChannels,
            ));
        }
    }
    let outputs = setup
        .outputs
        .iter()
        .map(|name| choice(name.clone(), name))
        .collect();
    let output = setup.output.clone().unwrap_or_default();
    let need = setup
        .output_need
        .as_ref()
        .map(|need| output_need(need, setup.output.as_deref()));
    rows.push(field_row(
        "information.output",
        "Output",
        outputs,
        choice(output.clone(), &output),
        need.is_some(),
        AudioChoice::Output,
    ));
    if let Some(need) = need {
        rows.push(note("information.output.note", need, style::ACCENT));
    }
    if setup.one_interface {
        rows.push(note("information.asio", ONE_INTERFACE.to_owned(), DIM));
    }
    rows
}

const OFF: &str = "Off";
const BUILT_IN_MICROPHONE: &str = "This is the computer's own microphone, which will feed back \
                                   through its speakers. Use headphones.";
const ONE_INTERFACE: &str = "With ASIO, one interface is the input and the output.";

fn input_need(need: &InputNeed) -> String {
    match need {
        InputNeed::Choose => "Choose the input your guitar is plugged into.".to_owned(),
        InputNeed::NotConnected(name) => {
            format!("{name} is not connected. Connect it, then choose it again.")
        }
        InputNeed::DidNotOpen(name) => {
            format!("{name} could not be opened. Another app may be using it.")
        }
        InputNeed::FellBack(name) => format!(
            "{name} did not open, so Windows audio is playing. Once it is free, \
             choose ASIO under Settings › Audio Driver."
        ),
    }
}

fn output_need(need: &OutputNeed, playing: Option<&str>) -> String {
    match (need, playing) {
        (OutputNeed::NotConnected(name), Some(playing)) => {
            format!("{name} is not connected. {playing} is playing.")
        }
        (OutputNeed::NotConnected(name), None) => format!("{name} is not connected."),
    }
}

/// The selectors' width, the interface size buttons' together, so the
/// panel's controls share one edge on each side.
const FIELD_WIDTH: f32 = 4.0 * 48.0 + 3.0 * 4.0;
const FIELD_PADDING: f32 = 8.0;
const HANDLE_ROOM: f32 = 14.0;
const TEXT_SIZE: f32 = 12.0;

/// One entry of a picker: what it chooses and how it reads, cut to fit.
#[derive(Clone, PartialEq)]
struct Choice<T> {
    value: T,
    label: String,
}

impl<T> fmt::Display for Choice<T> {
    fn fmt(&self, formatter: &mut fmt::Formatter<'_>) -> fmt::Result {
        formatter.write_str(&self.label)
    }
}

fn choice<T>(value: T, label: &str) -> Choice<T> {
    Choice {
        value,
        label: crate::preset_bar::fitted(
            label,
            "",
            FIELD_WIDTH - 2.0 * FIELD_PADDING - HANDLE_ROOM,
            TEXT_SIZE,
        ),
    }
}

fn field_row<'a, T, R>(
    id: &str,
    label: &'static str,
    options: Vec<Choice<T>>,
    selected: Choice<T>,
    attention: bool,
    on_choose: fn(T) -> AudioChoice,
) -> Element<'a, Msg, Theme, R>
where
    T: Clone + PartialEq + 'a,
    R: FreeRenderer + 'a,
{
    let mut spec = Component::new(id, "selector", "native");
    spec.text = Some(selected.label.clone());
    let off = selected.label == OFF;
    let picker = pick_list(options, Some(selected), move |chosen: Choice<T>| {
        Message::Plugin(Action::Audio(on_choose(chosen.value)))
    })
    .on_open(Message::Plugin(Action::Audio(AudioChoice::Refresh)))
    .width(FIELD_WIDTH)
    .padding(Padding {
        top: 4.5,
        bottom: 4.5,
        left: FIELD_PADDING,
        right: FIELD_PADDING,
    })
    .text_size(TEXT_SIZE)
    .text_line_height(LineHeight::Absolute(15.0.into()))
    .font(style::FONT)
    .handle(pick_list::Handle::Arrow {
        size: Some(9.0.into()),
    })
    .style(move |_, status| field_style(attention, off, status))
    .menu_style(|_| menu_style());
    row![
        text(label)
            .size(13)
            .font(style::FONT)
            .color(style::INK)
            .width(Length::Fill),
        layout::mark(spec, picker),
    ]
    .align_y(Alignment::Center)
    .into()
}

/// The header's outlined treatment: the accent marks the box that needs
/// the player, as it marks an open selector, and an input that is off reads
/// dimmed as an unlit size does.
fn field_style(attention: bool, off: bool, status: pick_list::Status) -> pick_list::Style {
    let lit = attention || matches!(status, pick_list::Status::Opened { .. });
    pick_list::Style {
        text_color: if off { DIM } else { style::INK },
        placeholder_color: DIM,
        handle_color: DIM,
        background: Color::TRANSPARENT.into(),
        border: Border {
            color: if lit {
                style::ACCENT
            } else {
                style::MUTED.scale_alpha(0.5)
            },
            width: 1.0,
            radius: style::CONTROL_RADIUS.into(),
        },
    }
}

/// The preset menu's raised panel, the row under the pointer lifted and
/// set in the accent.
fn menu_style() -> menu::Style {
    let panel = crate::preset_bar::menu_style();
    menu::Style {
        background: panel
            .background
            .unwrap_or_else(|| Color::from_rgb(0.11, 0.125, 0.135).into()),
        border: panel.border,
        text_color: style::INK,
        selected_text_color: style::ACCENT,
        selected_background: crate::preset_bar::MENU_HOVER.into(),
        shadow: panel.shadow,
    }
}

fn note<'a, R: FreeRenderer + 'a>(
    id: &str,
    body: String,
    color: Color,
) -> Element<'a, Msg, Theme, R> {
    let mut spec = Component::new(id, "text", "native");
    spec.text = Some(body.clone());
    layout::mark(
        spec,
        text(body)
            .size(TEXT_SIZE)
            .font(style::FONT)
            .line_height(LineHeight::Absolute(16.0.into()))
            .color(color),
    )
}
