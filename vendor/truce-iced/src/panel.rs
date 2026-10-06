//! The finished editor kept between frames, so a frame that changes only the
//! plugin's live displays copies one image instead of building, laying out
//! and drawing the whole interface again (see
//! [`crate::IcedPlugin::retains_displays`]).
//!
//! iced draws a frame into whatever target it is handed and keeps nothing,
//! so the panel is a texture iced draws into on a full frame, and every frame
//! then copies it onto the swapchain image with one draw. A draw rather than
//! a texture copy, because a swapchain image may only be written by drawing
//! unless the surface is configured for copies, which not every platform
//! offers.
use iced_core::{Color, Rectangle, Renderer as _};
use iced_wgpu::{
    graphics::Viewport,
    primitive::{Pipeline, Primitive, Renderer as _},
    wgpu,
};

/// An image of the editor without its live displays, the size of the frame.
pub struct Panel {
    view: wgpu::TextureView,
}

impl Panel {
    pub fn new(
        device: &wgpu::Device,
        format: wgpu::TextureFormat,
        width: u32,
        height: u32,
    ) -> Self {
        let view = device
            .create_texture(&wgpu::TextureDescriptor {
                label: Some("truce-iced panel"),
                size: wgpu::Extent3d {
                    width,
                    height,
                    depth_or_array_layers: 1,
                },
                mip_level_count: 1,
                sample_count: 1,
                dimension: wgpu::TextureDimension::D2,
                format,
                usage: wgpu::TextureUsages::RENDER_ATTACHMENT
                    | wgpu::TextureUsages::TEXTURE_BINDING,
                view_formats: &[],
            })
            .create_view(&wgpu::TextureViewDescriptor::default());
        Self { view }
    }

    /// The panel's size in physical pixels.
    pub fn size(&self) -> (u32, u32) {
        let texture = self.view.texture();
        (texture.width(), texture.height())
    }

    /// Draws what `renderer` holds into the panel, then leaves the renderer
    /// holding only the panel's copy, for the displays to be drawn over before
    /// the frame is presented.
    pub fn retain(
        &self,
        renderer: &mut iced_wgpu::Renderer,
        background: Color,
        viewport: &Viewport,
    ) {
        let _ = renderer.present(
            Some(background),
            self.view.texture().format(),
            &self.view,
            viewport,
        );
        self.show(renderer, viewport);
    }

    /// Leaves `renderer` holding only the panel's copy.
    pub fn show(&self, renderer: &mut iced_wgpu::Renderer, viewport: &Viewport) {
        let bounds = Rectangle::with_size(viewport.logical_size());
        renderer.reset(bounds);
        renderer.draw_primitive(
            bounds,
            Copy {
                view: self.view.clone(),
            },
        );
    }
}

#[derive(Debug)]
struct Copy {
    view: wgpu::TextureView,
}

struct CopyPipeline {
    pipeline: wgpu::RenderPipeline,
    layout: wgpu::BindGroupLayout,
    bound: Option<(wgpu::TextureView, wgpu::BindGroup)>,
}

const COPY_SHADER: &str = "
@group(0) @binding(0) var panel: texture_2d<f32>;
@vertex fn vs_main(@builtin(vertex_index) index: u32) -> @builtin(position) vec4<f32> {
    let positions = array<vec2<f32>, 3>(vec2(-1., -1.), vec2(3., -1.), vec2(-1., 3.));
    return vec4(positions[index], 0., 1.);
}
@fragment fn fs_main(@builtin(position) position: vec4<f32>) -> @location(0) vec4<f32> {
    return textureLoad(panel, vec2<i32>(position.xy), 0);
}";

impl Pipeline for CopyPipeline {
    fn new(device: &wgpu::Device, _: &wgpu::Queue, format: wgpu::TextureFormat) -> Self {
        let layout = device.create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
            label: Some("truce-iced panel"),
            entries: &[wgpu::BindGroupLayoutEntry {
                binding: 0,
                visibility: wgpu::ShaderStages::FRAGMENT,
                ty: wgpu::BindingType::Texture {
                    sample_type: wgpu::TextureSampleType::Float { filterable: false },
                    view_dimension: wgpu::TextureViewDimension::D2,
                    multisampled: false,
                },
                count: None,
            }],
        });
        let module = device.create_shader_module(wgpu::ShaderModuleDescriptor {
            label: Some("truce-iced panel"),
            source: wgpu::ShaderSource::Wgsl(COPY_SHADER.into()),
        });
        let pipeline_layout = device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
            label: Some("truce-iced panel"),
            bind_group_layouts: &[&layout],
            push_constant_ranges: &[],
        });
        let pipeline = device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
            label: Some("truce-iced panel"),
            layout: Some(&pipeline_layout),
            vertex: wgpu::VertexState {
                module: &module,
                entry_point: Some("vs_main"),
                compilation_options: Default::default(),
                buffers: &[],
            },
            fragment: Some(wgpu::FragmentState {
                module: &module,
                entry_point: Some("fs_main"),
                compilation_options: Default::default(),
                targets: &[Some(wgpu::ColorTargetState {
                    format,
                    blend: None,
                    write_mask: wgpu::ColorWrites::ALL,
                })],
            }),
            primitive: Default::default(),
            depth_stencil: None,
            multisample: Default::default(),
            multiview: None,
            cache: None,
        });
        Self {
            pipeline,
            layout,
            bound: None,
        }
    }
}

impl Primitive for Copy {
    type Pipeline = CopyPipeline;
    fn prepare(
        &self,
        pipeline: &mut CopyPipeline,
        device: &wgpu::Device,
        _: &wgpu::Queue,
        _: &Rectangle,
        _: &Viewport,
    ) {
        if pipeline
            .bound
            .as_ref()
            .is_some_and(|(view, _)| *view == self.view)
        {
            return;
        }
        let bind = device.create_bind_group(&wgpu::BindGroupDescriptor {
            label: Some("truce-iced panel"),
            layout: &pipeline.layout,
            entries: &[wgpu::BindGroupEntry {
                binding: 0,
                resource: wgpu::BindingResource::TextureView(&self.view),
            }],
        });
        pipeline.bound = Some((self.view.clone(), bind));
    }
    fn draw(&self, pipeline: &CopyPipeline, pass: &mut wgpu::RenderPass<'_>) -> bool {
        if let Some((_, bind)) = &pipeline.bound {
            pass.set_pipeline(&pipeline.pipeline);
            pass.set_bind_group(0, bind, &[]);
            pass.draw(0..3, 0..1);
        }
        true
    }
}
