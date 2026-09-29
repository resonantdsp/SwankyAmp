//! Steinberg's ASIO Compatible logo, which its ASIO usage guidelines ask for
//! in the About (here information) panel of a product that runs on ASIO by
//! default, as the Windows standalone does. The artwork is Steinberg's own
//! file, the white version made for a dark background, drawn as the vector
//! outlines it holds so it stays sharp at any display scale without an image
//! decoder.
use crate::widgets::{FreeRenderer, Msg};
use iced_core::{
    Color, Element, Length, Point, Rectangle, Size, Theme, layout, mouse, renderer,
    widget::{Tree, Widget},
};
use std::sync::OnceLock;

const ARTWORK: &str = include_str!("../assets/asio-compatible.svg");

#[derive(Debug, Clone, Copy, PartialEq)]
enum Segment {
    Move(Point),
    Line(Point),
    Cubic(Point, Point, Point),
    Close,
}

struct Artwork {
    size: Size,
    outline: Vec<Segment>,
}

fn artwork() -> &'static Artwork {
    static ARTWORK_OUTLINE: OnceLock<Artwork> = OnceLock::new();
    ARTWORK_OUTLINE.get_or_init(|| parse(ARTWORK))
}

/// The logo at a given height, as wide as its artwork's proportions make it.
pub struct AsioLogo {
    pub height: f32,
}
impl AsioLogo {
    fn width(&self) -> f32 {
        let size = artwork().size;
        self.height * size.width / size.height
    }
}
impl<R: FreeRenderer> Widget<Msg, Theme, R> for AsioLogo {
    fn size(&self) -> Size<Length> {
        Size::new(Length::Fixed(self.width()), Length::Fixed(self.height))
    }
    fn layout(&mut self, _: &mut Tree, _: &R, limits: &layout::Limits) -> layout::Node {
        layout::atomic(limits, self.width(), self.height)
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
        use iced_graphics::geometry::{Fill, Path, fill};
        let art = artwork();
        let scale = self.height / art.size.height;
        let at = move |p: Point| Point::new(p.x * scale, p.y * scale);
        renderer.graphic(layout.bounds(), move |frame| {
            let path = Path::new(|b| {
                for segment in &art.outline {
                    match *segment {
                        Segment::Move(p) => b.move_to(at(p)),
                        Segment::Line(p) => b.line_to(at(p)),
                        Segment::Cubic(a, c, p) => b.bezier_curve_to(at(a), at(c), at(p)),
                        Segment::Close => b.close(),
                    }
                }
            });
            frame.fill(
                &path,
                Fill {
                    style: fill::Style::Solid(Color::WHITE),
                    rule: fill::Rule::NonZero,
                },
            );
        });
    }
}
impl<'a, R: FreeRenderer + 'a> From<AsioLogo> for Element<'a, Msg, Theme, R> {
    fn from(logo: AsioLogo) -> Self {
        Element::new(logo)
    }
}

/// The view box and the filled outlines of an SVG whose shapes are all paths
/// and polygons in one fill, as Steinberg's file is. Shapes with no outline
/// attribute, like its invisible backing rectangle, are skipped.
fn parse(svg: &str) -> Artwork {
    let view_box = numbers(attribute(svg, "viewBox").expect("the logo has a view box"));
    let size = Size::new(view_box[2], view_box[3]);
    let mut outline = Vec::new();
    let mut rest = svg;
    while let Some(start) = rest.find('<') {
        rest = &rest[start + 1..];
        let end = rest.find('>').unwrap_or(rest.len());
        let element = &rest[..end];
        if element.starts_with("path") {
            if let Some(d) = attribute(element, "d") {
                path_data(d, &mut outline);
            }
        } else if element.starts_with("polygon")
            && let Some(points) = attribute(element, "points")
        {
            let points = numbers(points);
            for (i, pair) in points.chunks_exact(2).enumerate() {
                let p = Point::new(pair[0], pair[1]);
                outline.push(if i == 0 {
                    Segment::Move(p)
                } else {
                    Segment::Line(p)
                });
            }
            outline.push(Segment::Close);
        }
        rest = &rest[end..];
    }
    Artwork { size, outline }
}

fn attribute<'a>(element: &'a str, name: &str) -> Option<&'a str> {
    let key = format!(" {name}=\"");
    let start = element.find(&key)? + key.len();
    let len = element[start..].find('"')?;
    Some(&element[start..start + len])
}

/// SVG numbers run together wherever a minus sign or a second decimal point
/// makes the boundary unambiguous, as in `-.35.92`. The logo has no exponents.
fn numbers(text: &str) -> Vec<f32> {
    let mut out = Vec::new();
    let mut current = String::new();
    let flush = |current: &mut String, out: &mut Vec<f32>| {
        if !current.is_empty() {
            out.push(current.parse().expect("the logo's numbers parse"));
            current.clear();
        }
    };
    for c in text.chars() {
        match c {
            '0'..='9' => current.push(c),
            '.' => {
                if current.contains('.') {
                    flush(&mut current, &mut out);
                }
                current.push(c);
            }
            '-' => {
                flush(&mut current, &mut out);
                current.push(c);
            }
            _ => flush(&mut current, &mut out),
        }
    }
    flush(&mut current, &mut out);
    out
}

/// The path commands the logo uses: moves, lines, horizontal and vertical
/// lines, cubic curves and their smooth continuations, absolute or relative.
fn path_data(d: &str, outline: &mut Vec<Segment>) {
    let mut current = Point::ORIGIN;
    let mut start = Point::ORIGIN;
    let mut last_control: Option<Point> = None;
    let mut commands = d
        .match_indices(|c: char| c.is_ascii_alphabetic())
        .peekable();
    while let Some((at, command)) = commands.next() {
        let end = commands.peek().map_or(d.len(), |(next, _)| *next);
        let args = numbers(&d[at + 1..end]);
        let command = command.chars().next().expect("a command letter");
        let relative = command.is_ascii_lowercase();
        let point = |current: Point, x: f32, y: f32| {
            if relative {
                Point::new(current.x + x, current.y + y)
            } else {
                Point::new(x, y)
            }
        };
        match command.to_ascii_uppercase() {
            'M' => {
                for (i, pair) in args.chunks_exact(2).enumerate() {
                    current = point(current, pair[0], pair[1]);
                    if i == 0 {
                        start = current;
                        outline.push(Segment::Move(current));
                    } else {
                        outline.push(Segment::Line(current));
                    }
                }
                last_control = None;
            }
            'L' => {
                for pair in args.chunks_exact(2) {
                    current = point(current, pair[0], pair[1]);
                    outline.push(Segment::Line(current));
                }
                last_control = None;
            }
            'H' => {
                for x in args {
                    current = Point::new(if relative { current.x + x } else { x }, current.y);
                    outline.push(Segment::Line(current));
                }
                last_control = None;
            }
            'V' => {
                for y in args {
                    current = Point::new(current.x, if relative { current.y + y } else { y });
                    outline.push(Segment::Line(current));
                }
                last_control = None;
            }
            'C' => {
                for c in args.chunks_exact(6) {
                    let a = point(current, c[0], c[1]);
                    let b = point(current, c[2], c[3]);
                    let p = point(current, c[4], c[5]);
                    outline.push(Segment::Cubic(a, b, p));
                    last_control = Some(b);
                    current = p;
                }
            }
            'S' => {
                for c in args.chunks_exact(4) {
                    let a = last_control.map_or(current, |control| {
                        Point::new(2. * current.x - control.x, 2. * current.y - control.y)
                    });
                    let b = point(current, c[0], c[1]);
                    let p = point(current, c[2], c[3]);
                    outline.push(Segment::Cubic(a, b, p));
                    last_control = Some(b);
                    current = p;
                }
            }
            'Z' => {
                outline.push(Segment::Close);
                current = start;
                last_control = None;
            }
            other => panic!("the logo uses path command {other}, which is not drawn"),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    /// The Windows information panel draws Steinberg's ASIO logo from its SVG
    /// outlines; a misread path would draw a broken or empty logo that only a
    /// Windows ASIO build ever shows. Every outline point lies in the view box,
    /// and the marks reach across it: the arrowheads from the left to the ® at
    /// the right, the ® at the top down to COMPATIBLE at the bottom.
    #[test]
    fn outlines_fill_their_view_box() {
        let art = artwork();
        let points: Vec<_> = art
            .outline
            .iter()
            .flat_map(|segment| match *segment {
                Segment::Move(p) | Segment::Line(p) => vec![p],
                Segment::Cubic(a, b, p) => vec![a, b, p],
                Segment::Close => vec![],
            })
            .collect();
        let (w, h) = (art.size.width, art.size.height);
        for p in &points {
            assert!(
                (0.0..=w).contains(&p.x) && (0.0..=h).contains(&p.y),
                "{p:?} lies outside the {w}x{h} view box"
            );
        }
        let span = |axis: fn(&Point) -> f32| {
            let values = points.iter().map(axis);
            values.clone().fold(f32::MIN, f32::max) - values.fold(f32::MAX, f32::min)
        };
        assert!(
            span(|p| p.x) > 0.9 * w,
            "the logo's marks do not span its width"
        );
        assert!(
            span(|p| p.y) > 0.65 * h,
            "the logo's marks do not span its height"
        );
    }
}
