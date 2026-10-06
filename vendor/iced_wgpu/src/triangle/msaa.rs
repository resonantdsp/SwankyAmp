use crate::core::{Rectangle, Size, Transformation};
use crate::graphics;

use wgpu::util::DeviceExt;

#[derive(Debug, Clone)]
pub struct Pipeline {
    format: wgpu::TextureFormat,
    raw: wgpu::RenderPipeline,
    constants: wgpu::BindGroup,
    texture_layout: wgpu::BindGroupLayout,
    sample_count: u32,
}

impl Pipeline {
    pub fn new(
        device: &wgpu::Device,
        format: wgpu::TextureFormat,
        antialiasing: graphics::Antialiasing,
    ) -> Pipeline {
        let sampler =
            device.create_sampler(&wgpu::SamplerDescriptor::default());

        let constant_layout =
            device.create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
                label: Some("iced_wgpu::triangle:msaa uniforms layout"),
                entries: &[
                    wgpu::BindGroupLayoutEntry {
                        binding: 0,
                        visibility: wgpu::ShaderStages::FRAGMENT,
                        ty: wgpu::BindingType::Sampler(
                            wgpu::SamplerBindingType::NonFiltering,
                        ),
                        count: None,
                    },
                    wgpu::BindGroupLayoutEntry {
                        binding: 1,
                        visibility: wgpu::ShaderStages::VERTEX,
                        ty: wgpu::BindingType::Buffer {
                            ty: wgpu::BufferBindingType::Uniform,
                            has_dynamic_offset: false,
                            min_binding_size: None,
                        },
                        count: None,
                    },
                ],
            });

        let texture_layout =
            device.create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
                label: Some("iced_wgpu::triangle::msaa texture layout"),
                entries: &[wgpu::BindGroupLayoutEntry {
                    binding: 0,
                    visibility: wgpu::ShaderStages::FRAGMENT,
                    ty: wgpu::BindingType::Texture {
                        sample_type: wgpu::TextureSampleType::Float {
                            filterable: false,
                        },
                        view_dimension: wgpu::TextureViewDimension::D2,
                        multisampled: false,
                    },
                    count: None,
                }],
            });

        let layout =
            device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
                label: Some("iced_wgpu::triangle::msaa pipeline layout"),
                push_constant_ranges: &[],
                bind_group_layouts: &[&constant_layout, &texture_layout],
            });

        let shader =
            device.create_shader_module(wgpu::ShaderModuleDescriptor {
                label: Some("iced_wgpu triangle blit_shader"),
                source: wgpu::ShaderSource::Wgsl(std::borrow::Cow::Borrowed(
                    include_str!("../shader/blit.wgsl"),
                )),
            });

        let pipeline =
            device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
                label: Some("iced_wgpu::triangle::msaa pipeline"),
                layout: Some(&layout),
                vertex: wgpu::VertexState {
                    module: &shader,
                    entry_point: Some("vs_main"),
                    buffers: &[],
                    compilation_options:
                        wgpu::PipelineCompilationOptions::default(),
                },
                fragment: Some(wgpu::FragmentState {
                    module: &shader,
                    entry_point: Some("fs_main"),
                    targets: &[Some(wgpu::ColorTargetState {
                        format,
                        blend: Some(
                            wgpu::BlendState::PREMULTIPLIED_ALPHA_BLENDING,
                        ),
                        write_mask: wgpu::ColorWrites::ALL,
                    })],
                    compilation_options:
                        wgpu::PipelineCompilationOptions::default(),
                }),
                primitive: wgpu::PrimitiveState {
                    topology: wgpu::PrimitiveTopology::TriangleList,
                    front_face: wgpu::FrontFace::Cw,
                    ..Default::default()
                },
                depth_stencil: None,
                multisample: wgpu::MultisampleState {
                    count: 1,
                    mask: !0,
                    alpha_to_coverage_enabled: false,
                },
                multiview: None,
                cache: None,
            });

        // Each target is exactly its region's size, so the blit samples
        // all of it.
        let ratio = Ratio {
            u: 1.0,
            v: 1.0,
            _padding: [0.0; 2],
        };

        let ratio = device.create_buffer_init(&wgpu::util::BufferInitDescriptor {
            label: Some("iced_wgpu::triangle::msaa ratio"),
            contents: bytemuck::bytes_of(&ratio),
            usage: wgpu::BufferUsages::UNIFORM,
        });

        let constants = device.create_bind_group(&wgpu::BindGroupDescriptor {
            label: Some("iced_wgpu::triangle::msaa uniforms bind group"),
            layout: &constant_layout,
            entries: &[
                wgpu::BindGroupEntry {
                    binding: 0,
                    resource: wgpu::BindingResource::Sampler(&sampler),
                },
                wgpu::BindGroupEntry {
                    binding: 1,
                    resource: ratio.as_entire_binding(),
                },
            ],
        });

        Self {
            format,
            raw: pipeline,
            constants,
            texture_layout,
            sample_count: antialiasing.sample_count(),
        }
    }
}

#[derive(Debug, Clone)]
struct Targets {
    attachment: wgpu::TextureView,
    resolve: wgpu::TextureView,
    bind_group: wgpu::BindGroup,
    size: Size<u32>,
}

impl Targets {
    pub fn new(
        device: &wgpu::Device,
        format: wgpu::TextureFormat,
        texture_layout: &wgpu::BindGroupLayout,
        sample_count: u32,
        size: Size<u32>,
    ) -> Targets {
        let extent = wgpu::Extent3d {
            width: size.width,
            height: size.height,
            depth_or_array_layers: 1,
        };

        let attachment = device.create_texture(&wgpu::TextureDescriptor {
            label: Some("iced_wgpu::triangle::msaa attachment"),
            size: extent,
            mip_level_count: 1,
            sample_count,
            dimension: wgpu::TextureDimension::D2,
            format,
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT,
            view_formats: &[],
        });

        let resolve = device.create_texture(&wgpu::TextureDescriptor {
            label: Some("iced_wgpu::triangle::msaa resolve target"),
            size: extent,
            mip_level_count: 1,
            sample_count: 1,
            dimension: wgpu::TextureDimension::D2,
            format,
            usage: wgpu::TextureUsages::RENDER_ATTACHMENT
                | wgpu::TextureUsages::TEXTURE_BINDING,
            view_formats: &[],
        });

        let attachment =
            attachment.create_view(&wgpu::TextureViewDescriptor::default());

        let resolve =
            resolve.create_view(&wgpu::TextureViewDescriptor::default());

        let bind_group = device.create_bind_group(&wgpu::BindGroupDescriptor {
            label: Some("iced_wgpu::triangle::msaa texture bind group"),
            layout: texture_layout,
            entries: &[wgpu::BindGroupEntry {
                binding: 0,
                resource: wgpu::BindingResource::TextureView(&resolve),
            }],
        });

        Targets {
            attachment,
            resolve,
            bind_group,
            size,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, bytemuck::Pod, bytemuck::Zeroable)]
#[repr(C)]
struct Ratio {
    u: f32,
    v: f32,
    // Padding field for 16-byte alignment.
    // See https://docs.rs/wgpu/latest/wgpu/struct.DownlevelFlags.html#associatedconstant.BUFFER_BINDINGS_NOT_16_BYTE_ALIGNED
    _padding: [f32; 2],
}

/// One mesh layer's region of the frame, in physical pixels, and the
/// multisampled target that covers exactly that region.
struct Region {
    bounds: Rectangle<u32>,
    targets: Targets,
}

/// Each mesh layer draws into a target the size of the frame region its
/// meshes can reach, rather than the whole frame, so clearing, resolving and
/// blitting it costs what the meshes cover. Every layer is prepared before
/// any is drawn, so each keeps its own target.
#[derive(Default)]
pub struct State {
    regions: Vec<Region>,
    prepared: usize,
    rendered: usize,
}

impl State {
    /// Readies the next layer to draw into `bounds` of the frame and returns
    /// the projection onto its target.
    pub fn prepare(
        &mut self,
        device: &wgpu::Device,
        pipeline: &Pipeline,
        bounds: Rectangle<u32>,
    ) -> Transformation {
        let size = Size::new(bounds.width, bounds.height);
        let targets = || {
            Targets::new(
                device,
                pipeline.format,
                &pipeline.texture_layout,
                pipeline.sample_count,
                size,
            )
        };

        match self.regions.get_mut(self.prepared) {
            Some(region) => {
                if region.targets.size != size {
                    region.targets = targets();
                }

                region.bounds = bounds;
            }
            None => self.regions.push(Region {
                bounds,
                targets: targets(),
            }),
        }

        self.prepared += 1;

        Transformation::orthographic(size.width, size.height)
            * Transformation::translate(-(bounds.x as f32), -(bounds.y as f32))
    }

    /// The index of the next layer to render, in the order they were prepared.
    pub fn next_render(&mut self) -> usize {
        self.rendered += 1;
        self.rendered - 1
    }

    pub fn bounds(&self, index: usize) -> Rectangle<u32> {
        self.regions[index].bounds
    }

    pub fn trim(&mut self) {
        self.regions.truncate(self.prepared);
        self.prepared = 0;
        self.rendered = 0;
    }

    pub fn render_pass<'a>(
        &self,
        index: usize,
        encoder: &'a mut wgpu::CommandEncoder,
    ) -> wgpu::RenderPass<'a> {
        let targets = &self.regions[index].targets;

        encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
            label: Some("iced_wgpu.triangle.render_pass"),
            color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                view: &targets.attachment,
                depth_slice: None,
                resolve_target: Some(&targets.resolve),
                ops: wgpu::Operations {
                    load: wgpu::LoadOp::Clear(wgpu::Color::TRANSPARENT),
                    store: wgpu::StoreOp::Store,
                },
            })],
            depth_stencil_attachment: None,
            timestamp_writes: None,
            occlusion_query_set: None,
        })
    }

    pub fn render(
        &self,
        pipeline: &Pipeline,
        encoder: &mut wgpu::CommandEncoder,
        target: &wgpu::TextureView,
        index: usize,
    ) {
        let region = &self.regions[index];

        let mut render_pass =
            encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
                label: Some("iced_wgpu::triangle::msaa render pass"),
                color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                    view: target,
                    depth_slice: None,
                    resolve_target: None,
                    ops: wgpu::Operations {
                        load: wgpu::LoadOp::Load,
                        store: wgpu::StoreOp::Store,
                    },
                })],
                depth_stencil_attachment: None,
                timestamp_writes: None,
                occlusion_query_set: None,
            });

        render_pass.set_viewport(
            region.bounds.x as f32,
            region.bounds.y as f32,
            region.bounds.width as f32,
            region.bounds.height as f32,
            0.0,
            1.0,
        );
        render_pass.set_pipeline(&pipeline.raw);
        render_pass.set_bind_group(0, &pipeline.constants, &[]);
        render_pass.set_bind_group(1, &region.targets.bind_group, &[]);
        render_pass.draw(0..6, 0..1);
    }
}
