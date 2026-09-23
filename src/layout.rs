//! The exported bake geometry is collected from the same iced tree users operate.
use crate::{params::SwankyAmpParams, style, widgets::FreeRenderer};
use iced_core::{
    Background, Clipboard, Color, Element, Event, Font, Length, Pixels, Point, Rectangle, Shell,
    Size, Theme, Transformation, Vector, layout, mouse, overlay, renderer, text,
    widget::{self, Operation, Tree, Widget},
};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::{
    path::{Path, PathBuf},
    sync::Arc,
};

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum ControlKind {
    Knob,
    Toggle,
}

#[derive(Debug, Clone, Copy)]
pub struct ControlSpec {
    pub id: u32,
    pub label: &'static str,
    pub group: &'static str,
    pub center: [f32; 2],
    pub large: bool,
    pub kind: ControlKind,
}

impl ControlSpec {
    const fn knob(
        id: u32,
        label: &'static str,
        group: &'static str,
        center: [f32; 2],
        large: bool,
    ) -> Self {
        Self {
            id,
            label,
            group,
            center,
            large,
            kind: ControlKind::Knob,
        }
    }

    const fn toggle(id: u32, label: &'static str, group: &'static str, center: [f32; 2]) -> Self {
        Self {
            id,
            label,
            group,
            center,
            large: false,
            kind: ControlKind::Toggle,
        }
    }
}

/// One inventory is used by the UI, host bindings, and exported artwork geometry.
pub const CONTROLS: [ControlSpec; 20] = [
    ControlSpec::knob(0, "INPUT", "LEVELS", [182.0, 148.0], true),
    ControlSpec::knob(1, "OUTPUT", "LEVELS", [391.0, 148.0], true),
    ControlSpec::knob(11, "BRIGHT", "CABINET", [611.0, 148.0], false),
    ControlSpec::knob(12, "DISTANCE", "CABINET", [787.0, 148.0], false),
    ControlSpec::knob(13, "DYNAMIC", "CABINET", [963.0, 148.0], false),
    ControlSpec::toggle(10, "ON", "CABINET", [1022.0, 97.0]),
    ControlSpec::knob(14, "DRIVE", "PREAMP", [99.0, 324.0], true),
    ControlSpec::knob(15, "TIGHT", "PREAMP", [239.0, 324.0], false),
    ControlSpec::knob(16, "GRIT", "PREAMP", [379.0, 324.0], false),
    ControlSpec::knob(7, "STAGES", "STAGING", [561.0, 324.0], false),
    ControlSpec::knob(8, "OVERHEAD", "STAGING", [701.0, 324.0], false),
    ControlSpec::knob(9, "LOW CUT", "STAGING", [841.0, 324.0], false),
    ControlSpec::knob(6, "TONE STACK", "STAGING", [981.0, 324.0], false),
    ControlSpec::knob(17, "DRIVE", "POWER AMP", [99.0, 500.0], true),
    ControlSpec::knob(18, "TIGHT", "POWER AMP", [239.0, 500.0], false),
    ControlSpec::knob(19, "SAG", "POWER AMP", [379.0, 500.0], false),
    ControlSpec::knob(2, "LOW", "TONE", [561.0, 500.0], false),
    ControlSpec::knob(3, "MID", "TONE", [701.0, 500.0], false),
    ControlSpec::knob(4, "HIGH", "TONE", [841.0, 500.0], false),
    ControlSpec::knob(5, "PRESENCE", "TONE", [981.0, 500.0], false),
];

#[derive(Debug, Clone, Copy)]
pub struct SurfaceSpec {
    pub id: &'static str,
    pub kind: &'static str,
    pub appearance: &'static str,
    pub bounds: [f32; 4],
    /// Corner radius of the groove that outlines a section; other surfaces
    /// carry none.
    pub radius: Option<f32>,
}

impl SurfaceSpec {
    const fn plain(
        id: &'static str,
        kind: &'static str,
        appearance: &'static str,
        bounds: [f32; 4],
    ) -> Self {
        Self {
            id,
            kind,
            appearance,
            bounds,
            radius: None,
        }
    }

    const fn section(id: &'static str, appearance: &'static str, bounds: [f32; 4]) -> Self {
        Self {
            id,
            kind: "section",
            appearance,
            bounds,
            radius: Some(style::SECTION_RADIUS),
        }
    }
}

pub const PANELS: [SurfaceSpec; 3] = [
    SurfaceSpec::plain(
        "panel.header",
        "panel",
        "graphite-header",
        [0.0, 0.0, 1080.0, 64.0],
    ),
    SurfaceSpec::plain(
        "panel.main",
        "panel",
        "graphite",
        [0.0, 64.0, 1080.0, 544.0],
    ),
    SurfaceSpec::plain(
        "panel.footer",
        "panel",
        "graphite-header",
        [0.0, 608.0, 1080.0, 32.0],
    ),
];

/// The six Free groups as separate rounded boxes, after 1.4.0: a gap of
/// graphite between them, each traced by its own groove, so no group has to
/// share an edge with another.
pub const SECTIONS: [SurfaceSpec; 6] = [
    SurfaceSpec::section("section.levels", "levels", [14.0, 78.0, 482.0, 164.0]),
    SurfaceSpec::section("section.cabinet", "cabinet", [508.0, 78.0, 558.0, 164.0]),
    SurfaceSpec::section("section.preamp", "preamp", [14.0, 254.0, 450.0, 164.0]),
    SurfaceSpec::section("section.staging", "staging", [476.0, 254.0, 590.0, 164.0]),
    SurfaceSpec::section("section.power", "power-amp", [14.0, 430.0, 450.0, 164.0]),
    SurfaceSpec::section("section.tone", "tone", [476.0, 430.0, 590.0, 164.0]),
];

/// Pro's meter columns: 20 px wide, 4 px apart, rising from the top of the
/// lit ring to the knob's label row so the L/R captions share the readout line.
pub const METERS: [SurfaceSpec; 4] = [
    SurfaceSpec::plain(
        "meter.input.left",
        "meter",
        "input-left",
        [78.0, 108.0, 20.0, 104.0],
    ),
    SurfaceSpec::plain(
        "meter.input.right",
        "meter",
        "input-right",
        [102.0, 108.0, 20.0, 104.0],
    ),
    SurfaceSpec::plain(
        "meter.output.left",
        "meter",
        "output-left",
        [287.0, 108.0, 20.0, 104.0],
    ),
    SurfaceSpec::plain(
        "meter.output.right",
        "meter",
        "output-right",
        [311.0, 108.0, 20.0, 104.0],
    ),
];

#[derive(Debug, Clone)]
pub struct Component {
    pub id: String,
    pub kind: String,
    pub appearance: String,
    pub parameter: Option<u32>,
    pub bounds: [f32; 4],
    pub radius: Option<f32>,
}

impl Component {
    pub fn new(id: impl Into<String>, kind: &str, appearance: &str) -> Self {
        Self {
            id: id.into(),
            kind: kind.into(),
            appearance: appearance.into(),
            parameter: None,
            bounds: [0.0; 4],
            radius: None,
        }
    }
}

pub struct Mark<'a, M, R: iced_core::Renderer> {
    spec: Component,
    content: Element<'a, M, Theme, R>,
}

pub fn mark<'a, M: 'a, R: iced_core::Renderer + 'a>(
    spec: Component,
    content: impl Into<Element<'a, M, Theme, R>>,
) -> Element<'a, M, Theme, R> {
    Element::new(Mark {
        spec,
        content: content.into(),
    })
}

impl<M, R: iced_core::Renderer> Widget<M, Theme, R> for Mark<'_, M, R> {
    fn size(&self) -> Size<Length> {
        self.content.as_widget().size()
    }
    fn children(&self) -> Vec<Tree> {
        vec![Tree::new(self.content.as_widget())]
    }
    fn diff(&self, tree: &mut Tree) {
        tree.diff_children(&[self.content.as_widget()]);
    }
    fn layout(&mut self, tree: &mut Tree, renderer: &R, limits: &layout::Limits) -> layout::Node {
        self.content
            .as_widget_mut()
            .layout(&mut tree.children[0], renderer, limits)
    }
    fn operate(
        &mut self,
        tree: &mut Tree,
        layout: layout::Layout<'_>,
        renderer: &R,
        op: &mut dyn Operation,
    ) {
        let mut spec = self.spec.clone();
        op.custom(None, layout.bounds(), &mut spec);
        self.content
            .as_widget_mut()
            .operate(&mut tree.children[0], layout, renderer, op);
    }
    fn draw(
        &self,
        tree: &Tree,
        renderer: &mut R,
        theme: &Theme,
        style: &renderer::Style,
        layout: layout::Layout<'_>,
        cursor: mouse::Cursor,
        viewport: &Rectangle,
    ) {
        self.content.as_widget().draw(
            &tree.children[0],
            renderer,
            theme,
            style,
            layout,
            cursor,
            viewport,
        );
    }
    fn update(
        &mut self,
        tree: &mut Tree,
        event: &Event,
        layout: layout::Layout<'_>,
        cursor: mouse::Cursor,
        renderer: &R,
        clipboard: &mut dyn Clipboard,
        shell: &mut Shell<'_, M>,
        viewport: &Rectangle,
    ) {
        self.content.as_widget_mut().update(
            &mut tree.children[0],
            event,
            layout,
            cursor,
            renderer,
            clipboard,
            shell,
            viewport,
        );
    }
    fn mouse_interaction(
        &self,
        tree: &Tree,
        layout: layout::Layout<'_>,
        cursor: mouse::Cursor,
        viewport: &Rectangle,
        renderer: &R,
    ) -> mouse::Interaction {
        self.content.as_widget().mouse_interaction(
            &tree.children[0],
            layout,
            cursor,
            viewport,
            renderer,
        )
    }
    fn overlay<'a>(
        &'a mut self,
        tree: &'a mut Tree,
        layout: layout::Layout<'a>,
        renderer: &R,
        viewport: &Rectangle,
        translation: Vector,
    ) -> Option<overlay::Element<'a, M, Theme, R>> {
        self.content.as_widget_mut().overlay(
            &mut tree.children[0],
            layout,
            renderer,
            viewport,
            translation,
        )
    }
}

#[derive(Default)]
struct Collect(Vec<Component>);
impl Operation for Collect {
    fn traverse(&mut self, visit: &mut dyn FnMut(&mut dyn Operation)) {
        visit(self);
    }
    fn custom(&mut self, _: Option<&widget::Id>, bounds: Rectangle, state: &mut dyn std::any::Any) {
        if let Some(component) = state.downcast_ref::<Component>() {
            let mut component = component.clone();
            component.bounds = [bounds.x, bounds.y, bounds.width, bounds.height];
            self.0.push(component);
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct Surface {
    pub kind: String,
    pub appearance: String,
    pub bounds: [f32; 4],
    #[serde(default, skip_serializing_if = "Option::is_none")]
    pub radius: Option<f32>,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct PhysicalLayout {
    pub size: [f32; 2],
    pub profile: style::PhysicalStyle,
    pub surfaces: Vec<Surface>,
}

/// Schema 2 adds the section outline radius. An older producer would bake
/// square outlines without noticing the field, so the number changes.
pub const SCHEMA: u32 = 2;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct Manifest {
    pub schema: u32,
    pub view: String,
    pub logical_size: [f32; 2],
    pub physical_sha256: String,
    pub physical: PhysicalLayout,
}

pub struct Measure;
impl iced_core::Renderer for Measure {
    fn start_layer(&mut self, _: Rectangle) {}
    fn end_layer(&mut self) {}
    fn start_transformation(&mut self, _: Transformation) {}
    fn end_transformation(&mut self) {}
    fn reset(&mut self, _: Rectangle) {}
    fn fill_quad(&mut self, _: renderer::Quad, _: impl Into<Background>) {}
    fn allocate_image(
        &mut self,
        _: &iced_core::image::Handle,
        callback: impl FnOnce(Result<iced_core::image::Allocation, iced_core::image::Error>)
        + Send
        + 'static,
    ) {
        callback(Err(iced_core::image::Error::Unsupported));
    }
}
impl text::Renderer for Measure {
    type Font = Font;
    type Paragraph = iced_graphics::text::Paragraph;
    type Editor = iced_graphics::text::Editor;
    const ICON_FONT: Font = <iced_wgpu::Renderer as text::Renderer>::ICON_FONT;
    const CHECKMARK_ICON: char = <iced_wgpu::Renderer as text::Renderer>::CHECKMARK_ICON;
    const ARROW_DOWN_ICON: char = <iced_wgpu::Renderer as text::Renderer>::ARROW_DOWN_ICON;
    const SCROLL_UP_ICON: char = <iced_wgpu::Renderer as text::Renderer>::SCROLL_UP_ICON;
    const SCROLL_DOWN_ICON: char = <iced_wgpu::Renderer as text::Renderer>::SCROLL_DOWN_ICON;
    const SCROLL_LEFT_ICON: char = <iced_wgpu::Renderer as text::Renderer>::SCROLL_LEFT_ICON;
    const SCROLL_RIGHT_ICON: char = <iced_wgpu::Renderer as text::Renderer>::SCROLL_RIGHT_ICON;
    const ICED_LOGO: char = <iced_wgpu::Renderer as text::Renderer>::ICED_LOGO;
    fn default_font(&self) -> Font {
        style::FONT
    }
    fn default_size(&self) -> Pixels {
        Pixels(14.0)
    }
    fn fill_paragraph(&mut self, _: &Self::Paragraph, _: Point, _: Color, _: Rectangle) {}
    fn fill_editor(&mut self, _: &Self::Editor, _: Point, _: Color, _: Rectangle) {}
    fn fill_text(&mut self, _: text::Text, _: Point, _: Color, _: Rectangle) {}
}
impl iced_wgpu::primitive::Renderer for Measure {
    fn draw_primitive(&mut self, _: Rectangle, _: impl iced_wgpu::primitive::Primitive) {}
}

pub fn manifest() -> Manifest {
    let params = Arc::new(SwankyAmpParams::default());
    let cache = truce_iced::ParamCache::new(params);
    resolve(&crate::ui::FreeUi::resting(), &cache, &mut Measure)
}

pub fn resolve<R: FreeRenderer>(
    ui: &crate::ui::FreeUi,
    params: &truce_iced::ParamCache<SwankyAmpParams>,
    renderer: &mut R,
) -> Manifest {
    style::load_fonts();
    let element = ui.view_content::<R>(params);
    let mut tree = iced_runtime::UserInterface::build(
        element,
        Size::new(style::WIDTH, style::HEIGHT),
        iced_runtime::user_interface::Cache::new(),
        renderer,
    );
    let mut collect = Collect::default();
    tree.operate(renderer, &mut collect);
    let physical = PhysicalLayout {
        size: [style::WIDTH, style::HEIGHT],
        profile: style::PhysicalStyle::default(),
        surfaces: collect
            .0
            .iter()
            .filter(|component| {
                matches!(
                    component.kind.as_str(),
                    "panel" | "section" | "knob" | "meter"
                )
            })
            .map(|component| Surface {
                kind: component.kind.clone(),
                appearance: component.appearance.clone(),
                bounds: component.bounds,
                radius: component.radius,
            })
            .collect(),
    };
    let physical_sha256 = format!(
        "{:x}",
        Sha256::digest(serde_json::to_vec(&physical).expect("physical layout serializes"))
    );
    Manifest {
        schema: SCHEMA,
        view: "amp".into(),
        logical_size: [style::WIDTH, style::HEIGHT],
        physical_sha256,
        physical,
    }
}

pub fn content_sha256(manifest: &Manifest) -> String {
    let mut bytes = serde_json::to_vec_pretty(manifest).expect("layout manifest serializes");
    bytes.push(b'\n');
    format!("{:x}", Sha256::digest(bytes))
}

pub fn validate(manifest: &Manifest) -> Result<(), String> {
    if manifest.schema != SCHEMA || manifest.view != "amp" {
        return Err(format!("layout must be the schema-{SCHEMA} amp view"));
    }
    if manifest.logical_size != [style::WIDTH, style::HEIGHT]
        || manifest.physical.size != manifest.logical_size
    {
        return Err("logical and physical sizes differ".into());
    }
    let expected_hash = format!(
        "{:x}",
        Sha256::digest(serde_json::to_vec(&manifest.physical).map_err(|error| error.to_string())?)
    );
    if manifest.physical_sha256 != expected_hash {
        return Err("physical layout hash differs".into());
    }
    let mut counts = [0usize; 4];
    for surface in &manifest.physical.surfaces {
        let index = match surface.kind.as_str() {
            "panel" => 0,
            "section" => 1,
            "knob" => 2,
            "meter" => 3,
            kind => return Err(format!("unsupported surface kind {kind}")),
        };
        counts[index] += 1;
        let [x, y, width, height] = surface.bounds;
        if surface.appearance.is_empty()
            || !surface.bounds.iter().all(|value| value.is_finite())
            || x < 0.0
            || y < 0.0
            || width <= 0.0
            || height <= 0.0
            || x + width > style::WIDTH + 0.1
            || y + height > style::HEIGHT + 0.1
        {
            return Err(format!(
                "invalid {} surface bounds {:?}",
                surface.kind, surface.bounds
            ));
        }
        let radius_valid = match (surface.kind.as_str(), surface.radius) {
            ("section", Some(radius)) => {
                radius.is_finite() && radius > 0.0 && radius <= width.min(height) / 2.0
            }
            ("section", None) => false,
            (_, radius) => radius.is_none(),
        };
        if !radius_valid {
            return Err(format!(
                "{} surface has an invalid outline radius {:?}",
                surface.kind, surface.radius
            ));
        }
    }
    if counts != [3, 6, 19, 4] {
        return Err(format!("unexpected physical surface counts: {counts:?}"));
    }
    separate_sections(manifest)
}

/// Each section's groove must stay its own outline: two boxes closer than a
/// groove's width would merge their grooves into one channel.
fn separate_sections(manifest: &Manifest) -> Result<(), String> {
    let clearance = manifest.physical.profile.groove_width;
    let sections: Vec<_> = manifest
        .physical
        .surfaces
        .iter()
        .filter(|surface| surface.kind == "section")
        .collect();
    for (index, a) in sections.iter().enumerate() {
        for b in &sections[index + 1..] {
            let [ax, ay, aw, ah] = a.bounds;
            let [bx, by, bw, bh] = b.bounds;
            let gap_x = (bx - (ax + aw)).max(ax - (bx + bw));
            let gap_y = (by - (ay + ah)).max(ay - (by + bh));
            if gap_x.max(gap_y) < clearance {
                return Err(format!(
                    "sections {} and {} are closer than a groove",
                    a.appearance, b.appearance
                ));
            }
        }
    }
    Ok(())
}

pub fn export(directory: &Path) -> Result<PathBuf, Box<dyn std::error::Error>> {
    let manifest = manifest();
    validate(&manifest)?;
    std::fs::create_dir_all(directory)?;
    let path = directory.join("amp.json");
    let mut bytes = serde_json::to_vec_pretty(&manifest)?;
    bytes.push(b'\n');
    std::fs::write(&path, bytes)?;
    Ok(path)
}
