//! Checks the capture command runs beside its review captures.
use crate::{params::SwankyAmpParams, style, ui::FreeUi};
use std::sync::Arc;
use truce_iced::{IcedPlugin, ParamCache};

/// A headless renderer, its viewport for the interface at `scale` device
/// pixels per point, and the device it draws with.
fn gpu(
    scale: f32,
) -> Result<
    (
        iced_wgpu::Renderer,
        iced_graphics::Viewport,
        iced_wgpu::wgpu::Device,
    ),
    Box<dyn std::error::Error>,
> {
    use iced_wgpu::wgpu;
    let instance = wgpu::Instance::new(&wgpu::InstanceDescriptor::default());
    gpu_on(&instance, scale)
}

fn gpu_on(
    instance: &iced_wgpu::wgpu::Instance,
    scale: f32,
) -> Result<
    (
        iced_wgpu::Renderer,
        iced_graphics::Viewport,
        iced_wgpu::wgpu::Device,
    ),
    Box<dyn std::error::Error>,
> {
    use iced_wgpu::wgpu;
    let adapter = pollster::block_on(instance.request_adapter(&wgpu::RequestAdapterOptions {
        // The adapter the live editor asks for.
        power_preference: wgpu::PowerPreference::LowPower,
        ..Default::default()
    }))?;
    let (device, queue) = pollster::block_on(adapter.request_device(&wgpu::DeviceDescriptor {
        label: Some("Swanky Amp verification"),
        required_limits: adapter.limits(),
        ..Default::default()
    }))?;
    let engine = iced_wgpu::Engine::new(
        &adapter,
        device.clone(),
        queue,
        wgpu::TextureFormat::Bgra8UnormSrgb,
        Some(iced_graphics::Antialiasing::MSAAx4),
        iced_graphics::Shell::headless(),
    );
    style::load_fonts();
    let renderer = iced_wgpu::Renderer::new(engine, style::FONT, iced_core::Pixels(14.0));
    let viewport = iced_graphics::Viewport::with_physical_size(
        iced_core::Size::new(
            (style::WIDTH * scale).round() as u32,
            (style::HEIGHT * scale).round() as u32,
        ),
        scale,
    );
    Ok((renderer, viewport, device))
}

/// A frame that draws only the live displays, over a panel kept from a frame
/// with silent meters, must show what a frame drawing everything shows. The
/// panel is kept from silence, so anything the meters move outside the
/// displays' own rectangles shows here as a difference. `scale` is the
/// display scale times the interface zoom.
pub fn retained_frame_matches(
    params: Arc<SwankyAmpParams>,
    scale: f32,
) -> Result<(), Box<dyn std::error::Error>> {
    let mut ui = FreeUi::new(Arc::clone(&params));
    ui.windowed = true;
    let cache = ParamCache::new(params);
    if !ui.retains_displays(&cache) {
        return Ok(());
    }
    let (mut renderer, viewport, device) = gpu(scale)?;
    // The panels cover the whole window, so no background shows.
    let background = iced_core::Color::BLACK;
    let full = paint_tree(
        &mut renderer,
        &viewport,
        ui.compose(&cache, false),
        |renderer| renderer.screenshot(&viewport, background),
    );
    let shown = std::mem::take(&mut ui.meter_levels);
    let size = viewport.physical_size();
    let panel = truce_iced::panel::Panel::new(
        &device,
        iced_wgpu::wgpu::TextureFormat::Bgra8UnormSrgb,
        size.width,
        size.height,
    );
    paint_tree(
        &mut renderer,
        &viewport,
        ui.compose(&cache, true),
        |renderer| panel.retain(renderer, background, &viewport),
    );
    ui.meter_levels = shown;
    ui.draw_displays(&cache, &mut renderer);
    let retained = renderer.screenshot(&viewport, background);
    let differing = full
        .chunks(4)
        .zip(retained.chunks(4))
        .filter(|(a, b)| a != b)
        .count();
    if differing > 0 {
        return Err(
            format!("A display-only frame differs from a full one in {differing} pixels").into(),
        );
    }
    Ok(())
}

/// Lays out and draws `element` into `renderer`, as a frame with no pointer,
/// and hands the renderer to `finish` while the tree its text lives in is
/// still there.
fn paint_tree<T>(
    renderer: &mut iced_wgpu::Renderer,
    viewport: &iced_graphics::Viewport,
    element: iced_core::Element<'_, crate::widgets::Msg, iced_core::Theme, iced_wgpu::Renderer>,
    finish: impl FnOnce(&mut iced_wgpu::Renderer) -> T,
) -> T {
    use iced_core::Renderer;
    renderer.reset(iced_core::Rectangle::with_size(viewport.logical_size()));
    let cursor = iced_core::mouse::Cursor::Unavailable;
    let mut tree = iced_runtime::UserInterface::build(
        element,
        viewport.logical_size(),
        iced_runtime::user_interface::Cache::new(),
        renderer,
    );
    tree.update(
        &[iced_core::Event::Window(
            iced_core::window::Event::RedrawRequested(std::time::Instant::now()),
        )],
        cursor,
        renderer,
        &mut iced_core::clipboard::Null,
        &mut Vec::new(),
    );
    tree.draw(
        renderer,
        &iced_core::Theme::Dark,
        &iced_core::renderer::Style {
            text_color: style::INK,
        },
        cursor,
    );
    finish(renderer)
}

#[cfg(all(test, target_os = "windows"))]
mod tests {
    use super::*;

    /// Windows compiles every shader through Direct3D's own compiler, which
    /// refuses programs Metal accepts and takes seconds on the editor's thread
    /// to do so. Drawing the baked editor and retaining its panel with live
    /// meters builds every pipeline the editor uses: iced's, the artwork
    /// compositor's, the meter light's and the panel copy. A shader the
    /// compiler rejects fails here with the compiler's message. The compiler
    /// runs on the host, not the adapter, so a runner with only Windows'
    /// software adapter checks it as well as a GPU.
    #[test]
    fn every_editor_shader_compiles_on_direct3d_12() {
        use iced_wgpu::wgpu;
        // The released editor's instance: Direct3D 12, wgpu's default
        // compiler (FXC) and no debug flags, which would compile shaders
        // unoptimised and so pass programs the optimiser rejects.
        let instance = wgpu::Instance::new(&wgpu::InstanceDescriptor {
            backends: wgpu::Backends::DX12,
            flags: wgpu::InstanceFlags::empty(),
            ..Default::default()
        });
        let (mut renderer, viewport, device) =
            gpu_on(&instance, 1.0).expect("a Direct3D 12 adapter");
        let params = Arc::new(SwankyAmpParams::default());
        let mut ui = FreeUi::new(Arc::clone(&params));
        ui.windowed = true;
        ui.meter_levels = [0.5; 4];
        let cache = ParamCache::new(params);
        // Without the bake the editor draws natively and would leave the
        // compositor and meter pipelines unbuilt.
        assert!(
            ui.retains_displays(&cache),
            "the editor has no matching bake"
        );
        let size = viewport.physical_size();
        let panel = truce_iced::panel::Panel::new(
            &device,
            wgpu::TextureFormat::Bgra8UnormSrgb,
            size.width,
            size.height,
        );
        let background = iced_core::Color::BLACK;
        paint_tree(
            &mut renderer,
            &viewport,
            ui.compose(&cache, true),
            |renderer| panel.retain(renderer, background, &viewport),
        );
        ui.draw_displays(&cache, &mut renderer);
        renderer.screenshot(&viewport, background);
    }
}
