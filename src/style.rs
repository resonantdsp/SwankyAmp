use iced_core::{Color, Font};
use serde::{Deserialize, Serialize};

pub const FONT: Font = Font::with_name("PT Sans");
pub const BOLD: Font = Font {
    weight: iced_core::font::Weight::Bold,
    ..FONT
};
pub const FONT_BYTES: &[u8] = include_bytes!("../assets/fonts/PTSans-Regular.ttf");
pub const BOLD_BYTES: &[u8] = include_bytes!("../assets/fonts/PTSans-Bold.ttf");
pub const ORANGE: Color = Color::from_rgb(0.96, 0.45, 0.20);

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
            ring_radiance: [2.7, 0.42, 0.045],
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
            meter_radiance: [[0.084, 1.512, 4.2], [4.2, 0.546, 0.0924]],
        }
    }
}
