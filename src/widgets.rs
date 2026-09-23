use crate::{layout::Component, style};
use iced_core::{
    Clipboard, Color, Element, Event, Font, Length, Point, Rectangle, Shell, Size, Theme, keyboard,
    layout, mouse, renderer,
    widget::{Operation, Tree, Widget, tree},
};
use truce_iced::{Message, ParamMessage};

pub type Msg = Message<crate::ui::Action>;

pub trait FreeRenderer:
    iced_core::text::Renderer<Font = Font> + iced_wgpu::primitive::Renderer
{
    const LOAD_ARTWORK: bool;

    fn knob(&mut self, bounds: Rectangle, radius: f32, value: f32, ring: bool) {
        draw_knob(self, bounds, radius, value, ring);
    }
}

impl FreeRenderer for crate::layout::Measure {
    const LOAD_ARTWORK: bool = false;

    fn knob(&mut self, _: Rectangle, _: f32, _: f32, _: bool) {}
}
impl FreeRenderer for iced_wgpu::Renderer {
    const LOAD_ARTWORK: bool = true;
}

#[derive(Debug, Clone, Copy)]
pub struct Target {
    pub id: u32,
    pub value: f32,
    pub default: f32,
}

pub struct Knob {
    pub target: Target,
    pub large: bool,
}

#[derive(Default)]
struct Drag {
    live: Option<(f32, f32)>,
    pointer: Option<Point>,
    outside: bool,
    fine: bool,
    focused: bool,
}

impl Knob {
    fn radius(&self) -> f32 {
        if self.large {
            style::KNOB_LARGE_RADIUS
        } else {
            style::KNOB_SMALL_RADIUS
        }
    }

    fn height(&self) -> f32 {
        if self.large { 84.0 } else { 58.0 }
    }

    fn hit(&self, bounds: Rectangle, cursor: mouse::Cursor) -> bool {
        cursor
            .position()
            .is_some_and(|point| point.distance(bounds.center()) <= self.radius() * 1.3)
    }

    fn set(&self, value: f32) -> Msg {
        Message::Param(ParamMessage::Batch(vec![
            ParamMessage::BeginEdit(self.target.id),
            ParamMessage::SetNormalized(self.target.id, value.clamp(0.0, 1.0) as f64),
            ParamMessage::EndEdit(self.target.id),
        ]))
    }
}

impl<R: FreeRenderer> Widget<Msg, Theme, R> for Knob {
    fn size(&self) -> Size<Length> {
        Size::new(Length::Fill, Length::Fixed(self.height()))
    }

    fn tag(&self) -> tree::Tag {
        tree::Tag::of::<Drag>()
    }

    fn state(&self) -> tree::State {
        tree::State::new(Drag::default())
    }

    fn layout(&mut self, _: &mut Tree, _: &R, limits: &layout::Limits) -> layout::Node {
        layout::atomic(limits, Length::Fill, self.height())
    }

    fn operate(&mut self, _: &mut Tree, layout: layout::Layout<'_>, _: &R, op: &mut dyn Operation) {
        let bounds = layout.bounds();
        let radius = self.radius();
        let mut component = Component::new(
            format!("parameter.{}.knob", self.target.id),
            "knob",
            if self.large {
                "aluminum-ring"
            } else {
                "aluminum"
            },
        );
        component.parameter = Some(self.target.id);
        op.custom(
            None,
            Rectangle::new(
                Point::new(bounds.center_x() - radius, bounds.center_y() - radius),
                Size::new(radius * 2.0, radius * 2.0),
            ),
            &mut component,
        );
    }

    fn update(
        &mut self,
        tree: &mut Tree,
        event: &Event,
        layout: layout::Layout<'_>,
        cursor: mouse::Cursor,
        _: &R,
        _: &mut dyn Clipboard,
        shell: &mut Shell<'_, Msg>,
        _: &Rectangle,
    ) {
        let state = tree.state.downcast_mut::<Drag>();
        match event {
            Event::Mouse(mouse::Event::CursorMoved { position }) => {
                state.pointer = Some(*position);
                state.outside = false;
            }
            Event::Mouse(mouse::Event::CursorLeft) => {
                state.pointer = None;
                state.outside = true;
            }
            _ => {}
        }
        let cursor = state
            .pointer
            .map(mouse::Cursor::Available)
            .unwrap_or(cursor);
        let hit = !state.outside && self.hit(layout.bounds(), cursor);
        if matches!(
            event,
            Event::Window(iced_core::window::Event::Unfocused | iced_core::window::Event::Closed)
        ) {
            state.focused = false;
            state.fine = false;
            state.pointer = None;
            if state.live.take().is_some() {
                shell.publish(Message::Param(ParamMessage::EndEdit(self.target.id)));
                shell.request_redraw();
            }
            return;
        }
        if let Event::Keyboard(
            keyboard::Event::ModifiersChanged(modifiers)
            | keyboard::Event::KeyPressed { modifiers, .. }
            | keyboard::Event::KeyReleased { modifiers, .. },
        ) = event
        {
            state.fine = modifiers.shift();
        }
        let step = if state.fine { 0.001 } else { 0.01 };
        let message = match event {
            Event::Mouse(mouse::Event::ButtonPressed(mouse::Button::Left)) => {
                state.focused = hit;
                if !hit {
                    return;
                }
                state.live = Some((cursor.position().unwrap().y, self.target.value));
                Message::Param(ParamMessage::BeginEdit(self.target.id))
            }
            Event::Mouse(mouse::Event::CursorMoved { position }) if state.live.is_some() => {
                let (y, value) = state.live.unwrap();
                let value = (value + (y - position.y) / if state.fine { 1800.0 } else { 240.0 })
                    .clamp(0.0, 1.0);
                state.live = Some((position.y, value));
                Message::Param(ParamMessage::SetNormalized(self.target.id, value as f64))
            }
            Event::Mouse(mouse::Event::ButtonReleased(mouse::Button::Left))
                if state.live.is_some() =>
            {
                state.live = None;
                Message::Param(ParamMessage::EndEdit(self.target.id))
            }
            Event::Keyboard(keyboard::Event::KeyPressed {
                key: keyboard::Key::Named(keyboard::key::Named::Escape),
                ..
            }) if state.live.is_some() => {
                state.live = None;
                Message::Param(ParamMessage::EndEdit(self.target.id))
            }
            Event::Mouse(mouse::Event::ButtonPressed(mouse::Button::Right))
                if hit && state.live.is_none() =>
            {
                self.set(self.target.default)
            }
            Event::Mouse(mouse::Event::WheelScrolled { delta }) if hit && state.live.is_none() => {
                let delta = match delta {
                    mouse::ScrollDelta::Lines { y, .. } => *y,
                    mouse::ScrollDelta::Pixels { y, .. } => *y / 30.0,
                };
                self.set(self.target.value + delta * step)
            }
            Event::Keyboard(keyboard::Event::KeyPressed { key, .. })
                if state.focused && state.live.is_none() =>
            {
                use keyboard::key::Named;
                match key {
                    keyboard::Key::Named(Named::ArrowUp | Named::ArrowRight) => {
                        self.set(self.target.value + step)
                    }
                    keyboard::Key::Named(Named::ArrowDown | Named::ArrowLeft) => {
                        self.set(self.target.value - step)
                    }
                    keyboard::Key::Named(Named::Home) => self.set(0.0),
                    keyboard::Key::Named(Named::End) => self.set(1.0),
                    _ => return,
                }
            }
            _ => return,
        };
        shell.publish(message);
        shell.capture_event();
        shell.request_redraw();
    }

    fn mouse_interaction(
        &self,
        tree: &Tree,
        layout: layout::Layout<'_>,
        cursor: mouse::Cursor,
        _: &Rectangle,
        _: &R,
    ) -> mouse::Interaction {
        if tree.state.downcast_ref::<Drag>().live.is_some() {
            mouse::Interaction::Grabbing
        } else if self.hit(layout.bounds(), cursor) {
            mouse::Interaction::Grab
        } else {
            mouse::Interaction::default()
        }
    }

    fn draw(
        &self,
        _: &Tree,
        renderer: &mut R,
        _: &Theme,
        _: &renderer::Style,
        layout: layout::Layout<'_>,
        _: mouse::Cursor,
        _: &Rectangle,
    ) {
        renderer.knob(
            layout.bounds(),
            self.radius(),
            self.target.value,
            self.large,
        );
    }
}

impl<'a, R: FreeRenderer + 'a> From<Knob> for Element<'a, Msg, Theme, R> {
    fn from(knob: Knob) -> Self {
        Element::new(knob)
    }
}

/// The release-notice mark: an information sign at rest, a download arrow
/// when a newer release is known. It is drawn from round-capped strokes so
/// it needs neither an image asset nor arrow coverage in the interface font.
pub struct NoticeGlyph {
    pub download: bool,
    pub color: Color,
}

const GLYPH_STROKE: f32 = 0.75;

impl<R: iced_core::Renderer> Widget<Msg, Theme, R> for NoticeGlyph {
    fn size(&self) -> Size<Length> {
        Size::new(Length::Fill, Length::Fill)
    }

    fn layout(&mut self, _: &mut Tree, _: &R, limits: &layout::Limits) -> layout::Node {
        layout::atomic(limits, Length::Fill, Length::Fill)
    }

    fn draw(
        &self,
        _: &Tree,
        renderer: &mut R,
        _: &Theme,
        _: &renderer::Style,
        layout: layout::Layout<'_>,
        _: mouse::Cursor,
        _: &Rectangle,
    ) {
        let c = layout.bounds().center();
        let at = |dx: f32, dy: f32| Point::new(c.x + dx, c.y + dy);
        if self.download {
            stroke(renderer, &[at(0.0, -6.5), at(0.0, 2.5)], self.color);
            stroke(
                renderer,
                &[at(-3.75, -1.25), at(0.0, 2.5), at(3.75, -1.25)],
                self.color,
            );
            stroke(
                renderer,
                &[at(-5.5, 3.75), at(-5.5, 6.0), at(5.5, 6.0), at(5.5, 3.75)],
                self.color,
            );
        } else {
            let radius = 7.0;
            renderer.fill_quad(
                renderer::Quad {
                    bounds: Rectangle::new(
                        at(-radius, -radius),
                        Size::new(radius * 2.0, radius * 2.0),
                    ),
                    border: iced_core::Border {
                        color: self.color,
                        width: 1.25,
                        radius: radius.into(),
                    },
                    ..Default::default()
                },
                Color::TRANSPARENT,
            );
            disk(renderer, at(0.0, -3.25), 1.0, self.color);
            stroke(renderer, &[at(0.0, -0.75), at(0.0, 3.75)], self.color);
        }
    }
}

impl<'a, R: iced_core::Renderer + 'a> From<NoticeGlyph> for Element<'a, Msg, Theme, R> {
    fn from(glyph: NoticeGlyph) -> Self {
        Element::new(glyph)
    }
}

fn stroke<R: iced_core::Renderer + ?Sized>(renderer: &mut R, points: &[Point], color: Color) {
    for pair in points.windows(2) {
        let (start, end) = (pair[0], pair[1]);
        let steps = (start.distance(end) / 0.35).ceil().max(1.0) as usize;
        for step in 0..=steps {
            let amount = step as f32 / steps as f32;
            disk(
                renderer,
                Point::new(
                    start.x + (end.x - start.x) * amount,
                    start.y + (end.y - start.y) * amount,
                ),
                GLYPH_STROKE,
                color,
            );
        }
    }
}

fn disk<R: iced_core::Renderer + ?Sized>(
    renderer: &mut R,
    center: Point,
    radius: f32,
    color: Color,
) {
    renderer.fill_quad(
        renderer::Quad {
            bounds: Rectangle::new(
                Point::new(center.x - radius, center.y - radius),
                Size::new(radius * 2.0, radius * 2.0),
            ),
            border: iced_core::Border {
                radius: radius.into(),
                ..Default::default()
            },
            ..Default::default()
        },
        color,
    );
}

fn draw_knob<R: iced_core::Renderer + ?Sized>(
    renderer: &mut R,
    bounds: Rectangle,
    radius: f32,
    value: f32,
    ring: bool,
) {
    if crate::artwork::loaded() {
        return;
    }
    let center = bounds.center();
    disk(
        renderer,
        Point::new(center.x, center.y + 4.0),
        radius + 3.0,
        Color::from_rgb(0.04, 0.05, 0.055),
    );
    disk(renderer, center, radius, Color::from_rgb(0.48, 0.51, 0.53));
    disk(
        renderer,
        center,
        radius - 2.0,
        Color::from_rgb(0.31, 0.34, 0.36),
    );
    if ring {
        let physical = style::PhysicalStyle::default();
        let steps = (physical.ring_sweep / 3.0).ceil() as usize;
        for index in 0..=steps {
            let amount = index as f32 / steps as f32;
            let angle = (physical.ring_start - amount * physical.ring_sweep).to_radians();
            let point = Point::new(
                center.x + angle.cos() * radius * physical.ring_radius,
                center.y - angle.sin() * radius * physical.ring_radius,
            );
            disk(
                renderer,
                point,
                radius * physical.ring_half_width,
                if amount <= value {
                    style::ACCENT
                } else {
                    Color::from_rgb(0.12, 0.14, 0.15)
                },
            );
        }
    }
    let physical = style::PhysicalStyle::default();
    let angle = (physical.ring_start - value.clamp(0.0, 1.0) * physical.ring_sweep).to_radians();
    disk(
        renderer,
        Point::new(
            center.x + angle.cos() * radius * 0.58,
            center.y - angle.sin() * radius * 0.58,
        ),
        radius * 0.065,
        Color::from_rgb(0.025, 0.03, 0.032),
    );
}
