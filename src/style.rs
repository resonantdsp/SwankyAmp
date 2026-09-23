use iced_core::{Color, Font};
use serde::{Deserialize, Serialize};

pub const FONT: Font = Font::with_name("PT Sans");
pub const BOLD: Font = Font {
    weight: iced_core::font::Weight::Bold,
    ..FONT
};
pub const FONT_BYTES: &[u8] = include_bytes!("../assets/fonts/PTSans-Regular.ttf");
pub const BOLD_BYTES: &[u8] = include_bytes!("../assets/fonts/PTSans-Bold.ttf");
/// Swanky Amp 1.4's highlight (`colourHighlight`, HSV 0.98, 0.60, 0.75) stays
/// Free's accent, so Free keeps its own identity inside Pro's material
/// language: lit knob rings, the selected outline, the edition tag and the
/// output meter all take it from here.
pub const ACCENT: Color = Color::from_rgb(0.75, 0.30, 0.354);
/// The input meter keeps Pro's blue; the output meter is the accent.
pub const METER_INPUT: Color = Color::from_rgb(0.06, 0.54, 0.96);
pub const METER_OUTPUT: Color = ACCENT;
/// Peak emitted radiance of a lit meter cell's brightest channel.
const METER_PEAK: f32 = 4.2;
pub const INK: Color = Color::from_rgb(0.86, 0.88, 0.89);
pub const MUTED: Color = Color::from_rgb(0.53, 0.59, 0.61);
/// Corner radius shared by every outlined control.
pub const CONTROL_RADIUS: f32 = 6.0;
/// Texels per interface pixel in the switch disc sprite: every edge the disc
/// has comes from the sprite, so it is drawn sharper than the 1x bake to hold
/// up on a Retina display.
pub const DISC_SUPERSAMPLE: u32 = 2;
/// The cabinet switch's disc diameter, half a small knob's: the whole switch
/// is a track two discs tall, about a small knob's height.
pub const SWITCH_DIAMETER: f32 = 24.0;
/// Corner radius of a group's groove outline.
pub const SECTION_RADIUS: f32 = 10.0;
/// How much brighter than the accent a lit ring reads, before the display
/// compression in the compositor.
const RING_GLOW: f32 = 1.25;

pub fn load_fonts() {
    static ONCE: std::sync::Once = std::sync::Once::new();
    ONCE.call_once(|| {
        let mut fonts = iced_graphics::text::font_system().write().unwrap();
        fonts.load_font(FONT_BYTES.into());
        fonts.load_font(BOLD_BYTES.into());
    });
}

pub const WIDTH: f32 = 1080.0;
pub const HEIGHT: f32 = 640.0;
pub const HEADER_HEIGHT: f32 = 64.0;
pub const FOOTER_HEIGHT: f32 = 32.0;
pub const UTILITY_X: f32 = 760.0;

pub const KNOB_LARGE_RADIUS: f32 = 32.0;
pub const KNOB_SMALL_RADIUS: f32 = 24.0;
pub const METER_BARS: u32 = 10;
pub const METER_GAP: f32 = 0.25;

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct PhysicalStyle {
    pub panel_color: [f32; 3],
    pub monitor_color: [f32; 3],
    pub header_color: [f32; 3],
    pub metal_color: [f32; 3],
    pub metal_roughness: f32,
    pub metal_anisotropy: f32,
    pub panel_depth: f32,
    pub panel_bevel: f32,
    pub groove_depth: f32,
    pub groove_bevel: f32,
    pub groove_width: f32,
    pub knob_height: f32,
    pub knob_bevel: f32,
    pub collar_radius: f32,
    pub ring_radius: f32,
    pub ring_half_width: f32,
    pub ring_start: f32,
    pub ring_sweep: f32,
    pub ring_radiance: [f32; 3],
    pub reflection_extent: f32,
    pub reflection_radial_knots: Vec<f32>,
    pub reflection_radial_rows: Vec<f32>,
    pub reflection_resolution: [u32; 2],
    pub reflection_steps: u32,
    pub diffuser_color: [f32; 3],
    pub diffuser_roughness: f32,
    pub diffuser_transmission: f32,
    pub diffuser_ior: f32,
    pub meter_recess: f32,
    pub meter_diffuser_depth: f32,
    pub meter_diffuser_thickness: f32,
    pub meter_emitter_depth: f32,
    pub meter_cell_inset: f32,
    pub meter_bars: u32,
    pub meter_gap: f32,
    pub meter_reflection_extent: f32,
    pub meter_radiance: [[f32; 3]; 2],
    /// The cabinet switch's disc diameter. Its track is a stadium exactly
    /// this wide and twice this tall, so the disc sits flush in one end or
    /// the other with no travel beyond them.
    pub switch_diameter: f32,
    /// The disc's top face above the faceplate.
    pub disc_height: f32,
    pub disc_bevel: f32,
    /// Clearance baked around the disc in its sprite, which is what its cast
    /// shadow needs.
    pub disc_margin: f32,
    /// Depth of the track's V below the faceplate: deeper than the section
    /// grooves, so the empty half of the track reads as a recess at 1x.
    pub slot_depth: f32,
}

impl Default for PhysicalStyle {
    fn default() -> Self {
        Self {
            panel_color: [0.014, 0.020, 0.026],
            monitor_color: [0.008, 0.012, 0.016],
            header_color: [0.007, 0.010, 0.013],
            metal_color: [0.46, 0.49, 0.53],
            metal_roughness: 0.32,
            metal_anisotropy: 0.38,
            panel_depth: 5.0,
            panel_bevel: 0.8,
            groove_depth: 2.2,
            groove_bevel: 0.12,
            groove_width: 2.0,
            knob_height: 32.91,
            knob_bevel: 1.7,
            collar_radius: 1.09,
            ring_radius: 1.22,
            ring_half_width: 0.046,
            ring_start: 225.0,
            ring_sweep: 270.0,
            ring_radiance: ring_radiance(ACCENT),
            reflection_extent: 4.0,
            reflection_radial_knots: vec![0.86, 1.28],
            reflection_radial_rows: vec![0.125, 0.875],
            reflection_resolution: [256, 96],
            reflection_steps: 12,
            diffuser_color: [0.62, 0.65, 0.69],
            diffuser_roughness: 0.42,
            diffuser_transmission: 1.0,
            diffuser_ior: 1.46,
            meter_recess: 4.2,
            meter_diffuser_depth: 1.4,
            meter_diffuser_thickness: 0.8,
            meter_emitter_depth: 2.8,
            meter_cell_inset: 0.7,
            meter_bars: METER_BARS,
            meter_gap: METER_GAP,
            meter_reflection_extent: 20.0,
            meter_radiance: [[0.084, 1.512, METER_PEAK], meter_radiance(METER_OUTPUT)],
            switch_diameter: SWITCH_DIAMETER,
            disc_height: 4.0,
            disc_bevel: 1.2,
            disc_margin: 12.0,
            slot_depth: 10.0,
        }
    }
}

/// The emitted radiance whose compressed display value is the accent, lifted
/// by [`RING_GLOW`]. Deriving it keeps the baked spill light and the runtime
/// ring on the one accent definition.
fn ring_radiance(color: Color) -> [f32; 3] {
    linear(color).map(|channel| {
        let display = (channel * RING_GLOW).min(0.95);
        display / (1.0 - display)
    })
}

/// A lit cell's emitter in the colour's hue, as bright as the input meter.
fn meter_radiance(color: Color) -> [f32; 3] {
    let rgb = linear(color);
    let peak = rgb.into_iter().fold(f32::MIN, f32::max);
    rgb.map(|channel| channel / peak * METER_PEAK)
}

fn linear(color: Color) -> [f32; 3] {
    [color.r, color.g, color.b].map(|channel| {
        if channel <= 0.04045 {
            channel / 12.92
        } else {
            ((channel + 0.055) / 1.055).powf(2.4)
        }
    })
}

/// One outline treatment for every header action, as Pro's buttons: the
/// outline takes the accent when the action is lit and the text colour stays
/// constant.
pub fn outlined(lit: bool) -> iced_widget::container::Style {
    iced_widget::container::Style {
        text_color: Some(INK),
        border: iced_core::Border {
            color: if lit { ACCENT } else { MUTED.scale_alpha(0.5) },
            width: 1.0,
            radius: CONTROL_RADIUS.into(),
        },
        ..Default::default()
    }
}

impl PhysicalStyle {
    /// The disc sprite's plan size in interface pixels.
    pub fn disc_sprite(&self) -> [f32; 2] {
        [(self.switch_diameter + 2.0 * self.disc_margin).round(); 2]
    }
}

/// The disc's sprite placement for a switch whose track has these bounds: in
/// the top half when on, the bottom half when off, on whole pixels so the
/// sprite's texels land where they were baked.
pub fn disc_sprite_bounds(track: [f32; 4], on: bool) -> [f32; 4] {
    let p = PhysicalStyle::default();
    let [x, y, width, height] = track;
    let sprite = p.disc_sprite();
    let center_y = y + if on { height / 4.0 } else { height * 3.0 / 4.0 };
    [
        (x + width / 2.0 - sprite[0] / 2.0).round(),
        (center_y - sprite[1] / 2.0).round(),
        sprite[0],
        sprite[1],
    ]
}

/// The knob marker is Pro's glossy black divot. It is drawn at runtime by the
/// compositor and the canvas fallback, never baked, so it stays outside the
/// physical profile.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct MarkerStyle {
    /// Marker centre as a fraction of the knob radius.
    pub radius: f32,
    /// Marker rim radius as a fraction of the knob radius.
    pub half_width: f32,
    /// Divot depth as a fraction of its rim radius.
    pub depth: f32,
}

impl Default for MarkerStyle {
    fn default() -> Self {
        Self {
            radius: 0.77,
            half_width: 0.1067,
            depth: 0.4,
        }
    }
}
