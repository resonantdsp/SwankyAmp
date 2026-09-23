//! Public artwork packaging. Blender is not required to build or open the plugin.
use crate::{layout, params::SwankyAmpParams, style, widgets::Msg};
use exr::prelude::{
    Compression, Encoding, Image, Layer, LayerAttributes, SampleType, SpecificChannels, Vec2,
    WritableImage, read_first_rgba_layer_from_file,
};
use iced_core::{Element, Length, Rectangle, Theme, mouse};
use iced_wgpu::{
    primitive::{Pipeline, Primitive},
    wgpu,
};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::{
    collections::BTreeMap,
    path::{Component as PathComponent, Path, PathBuf},
    sync::OnceLock,
};

const SIGNATURE: &[u8; 8] = b"SWFREE01";
const PACKAGE: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/artwork.pack"));
const MAX_HEADER_BYTES: usize = 4 * 1024 * 1024;
const MAX_LAYERS: usize = 256;
const MAX_DIMENSION: u32 = 16_384;
/// Receipt and package schema 2 added the switch sprite after the response
/// library; schema 3 replaces schema 2's pill cap with the disc, whose layers
/// a schema-2 reader would mistake for the cap.
const RECEIPT_SCHEMA: u32 = 3;
const PACKAGE_SCHEMA: u32 = 3;
/// The disc sprite's three layers in package order: the disc's own
/// premultiplied radiance, the shadow it casts, and the coverage that
/// composites both.
const DISC_LAYERS: [(&str, &str, &str); 3] = [
    ("disc-color", "disc/color.exr", "scene-linear-radiance"),
    (
        "disc-shadow",
        "disc/shadow.exr",
        "display-linear-multiplicative",
    ),
    ("disc-coverage", "disc/coverage.exr", "coverage"),
];

/// Roles whose values are fractions: a factor or a coverage above one would
/// brighten what it is meant to darken or cover.
fn bounded(role: &str) -> bool {
    matches!(role, "shadow" | "disc-shadow" | "disc-coverage")
}

/// The disc sprite's plan size in interface pixels and in texels.
fn disc_sprite() -> ([f32; 2], [u32; 2]) {
    let sprite = style::PhysicalStyle::default().disc_sprite();
    (
        sprite,
        sprite.map(|side| side as u32 * style::DISC_SUPERSAMPLE),
    )
}

#[derive(Debug, Serialize, Deserialize)]
struct Receipt {
    schema: u32,
    manifest: ReceiptManifest,
    #[allow(dead_code)]
    producer: serde_json::Value,
    render: RenderReceipt,
    response_library: ResponseLibrary,
    layers: Vec<ReceiptLayer>,
}

#[derive(Debug, Serialize, Deserialize)]
struct ReceiptManifest {
    schema: u32,
    view: String,
    content_sha256: String,
    physical_sha256: String,
    logical_size: [f32; 2],
    surface_counts: BTreeMap<String, usize>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(deny_unknown_fields)]
struct RenderReceipt {
    blender: String,
    engine: String,
    samples: u32,
    seed: u64,
    max_bounces: u32,
    base_denoised: bool,
    responses_denoised: bool,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct ResponseLibrary {
    pub ring_radii: Vec<f32>,
    pub ring_steps: u32,
    pub meter_sizes: Vec<[f32; 2]>,
    pub resolution: [u32; 2],
}

#[derive(Debug, Serialize, Deserialize)]
struct ReceiptLayer {
    role: String,
    file: String,
    width: u32,
    height: u32,
    channels: String,
    semantics: String,
    row_origin: String,
    sha256: String,
    family: Option<u32>,
    radius: Option<f32>,
    step: Option<u32>,
    value: Option<f32>,
    size: Option<[f32; 2]>,
    peak: Option<f32>,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct PackedLayer {
    pub role: String,
    pub file: String,
    pub width: u32,
    pub height: u32,
    pub semantics: String,
    pub source_sha256: String,
    pub encoded_sha256: String,
    pub offset: usize,
    pub length: usize,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub family: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub radius: Option<f32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub step: Option<u32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub value: Option<f32>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub size: Option<[f32; 2]>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub peak: Option<f32>,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct PackageHeader {
    pub schema: u32,
    pub view: String,
    pub logical_size: [u32; 2],
    pub layout_content_sha256: String,
    pub physical_sha256: String,
    pub surface_counts: BTreeMap<String, usize>,
    pub response_library: ResponseLibrary,
    pub render: PackedRender,
    pub layers: Vec<PackedLayer>,
}

#[derive(Debug, Clone, Serialize, Deserialize, PartialEq)]
pub struct PackedRender {
    pub blender: String,
    pub engine: String,
    pub samples: u32,
    pub seed: u64,
    pub max_bounces: u32,
    pub base_denoised: bool,
    pub responses_denoised: bool,
}

struct DecodedExr {
    width: u32,
    height: u32,
    pixels: Vec<[f32; 3]>,
}

pub fn pack(layers_directory: &Path, package_path: &Path) -> Result<PackageHeader, String> {
    let bytes = build_package(layers_directory)?;
    let header = validate_package_bytes(&bytes, true)?;
    if let Some(parent) = package_path
        .parent()
        .filter(|path| !path.as_os_str().is_empty())
    {
        std::fs::create_dir_all(parent).map_err(|error| error.to_string())?;
    }
    std::fs::write(package_path, bytes).map_err(|error| error.to_string())?;
    Ok(header)
}

pub fn validate_file(package_path: &Path) -> Result<PackageHeader, String> {
    let bytes = std::fs::read(package_path)
        .map_err(|error| format!("cannot read {}: {error}", package_path.display()))?;
    validate_package_bytes(&bytes, true)
}

#[derive(Debug)]
struct RuntimeScene {
    physical_sha256: String,
    data_start: usize,
    base: PackedLayer,
    shadow: PackedLayer,
    ring_responses: Vec<PackedLayer>,
    ring_steps: u32,
    disc: Vec<PackedLayer>,
}

fn runtime_scene() -> Option<&'static RuntimeScene> {
    static SCENE: OnceLock<Option<RuntimeScene>> = OnceLock::new();
    SCENE.get_or_init(load_runtime_scene).as_ref()
}

fn load_runtime_scene() -> Option<RuntimeScene> {
    let header = validate_package_bytes(PACKAGE, true).ok()?;
    let header_length = u32::from_le_bytes(PACKAGE.get(8..12)?.try_into().ok()?) as usize;
    let base = header
        .layers
        .iter()
        .find(|layer| layer.role == "base")?
        .clone();
    let shadow = header
        .layers
        .iter()
        .find(|layer| layer.role == "shadow")?
        .clone();
    let ring_responses: Vec<_> = header
        .layers
        .iter()
        .filter(|layer| layer.role == "ring-response")
        .cloned()
        .collect();
    let disc: Vec<_> = DISC_LAYERS
        .iter()
        .map(|(role, ..)| {
            header
                .layers
                .iter()
                .find(|layer| layer.role == *role)
                .cloned()
        })
        .collect::<Option<_>>()?;
    if [base.width, base.height] != [shadow.width, shadow.height] {
        return None;
    }
    Some(RuntimeScene {
        physical_sha256: header.physical_sha256,
        data_start: 12 + header_length,
        base,
        shadow,
        ring_responses,
        ring_steps: header.response_library.ring_steps,
        disc,
    })
}

pub fn loaded() -> bool {
    runtime_scene().is_some()
}

pub fn backdrop<'a, R>(
    params: &truce_iced::ParamCache<SwankyAmpParams>,
) -> Option<Element<'a, Msg, Theme, R>>
where
    R: iced_core::Renderer + iced_wgpu::primitive::Renderer + 'a,
{
    let scene = runtime_scene()?;
    let uniform = Uniform::new(params, scene.ring_steps);
    Some(
        iced_widget::shader(SceneProgram { scene, uniform })
            .width(Length::Fill)
            .height(Length::Fill)
            .into(),
    )
}

#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
#[repr(C)]
struct Control {
    geometry: [f32; 4],
    state: [f32; 4],
}

#[derive(Debug, Clone, Copy, bytemuck::Pod, bytemuck::Zeroable)]
#[repr(C)]
struct Uniform {
    scene: [f32; 4],
    ring: [f32; 4],
    emission: [f32; 4],
    marker: [f32; 4],
    polar: [f32; 4],
    extent: [f32; 4],
    /// The disc sprite's top-left corner and size, in interface pixels.
    disc: [f32; 4],
    controls: [Control; 32],
}

impl Uniform {
    fn new(params: &truce_iced::ParamCache<SwankyAmpParams>, ring_steps: u32) -> Self {
        let physical = style::PhysicalStyle::default();
        let marker = style::MarkerStyle::default();
        let mut result = Self {
            scene: [style::WIDTH, style::HEIGHT, 0.0, ring_steps as f32],
            ring: [
                physical.ring_radius,
                physical.ring_half_width,
                physical.ring_start.to_radians(),
                physical.ring_sweep.to_radians(),
            ],
            emission: [
                physical.ring_radiance[0],
                physical.ring_radiance[1],
                physical.ring_radiance[2],
                0.0,
            ],
            marker: [marker.radius, marker.half_width, marker.depth, 0.0],
            polar: [
                physical.reflection_radial_knots[0],
                physical.reflection_radial_knots[1],
                physical.reflection_radial_rows[0],
                physical.reflection_radial_rows[1],
            ],
            extent: [
                physical.reflection_extent,
                physical.reflection_extent * 2.0_f32.sqrt(),
                0.0,
                0.0,
            ],
            disc: style::disc_sprite_bounds(
                layout::SWITCH.bounds,
                params.get(layout::CABINET_SWITCH) >= 0.5,
            ),
            controls: [Control {
                geometry: [0.0; 4],
                state: [0.0; 4],
            }; 32],
        };
        for (index, control) in layout::CONTROLS
            .iter()
            .filter(|control| control.kind == layout::ControlKind::Knob)
            .enumerate()
        {
            let radius = if control.large {
                style::KNOB_LARGE_RADIUS
            } else {
                style::KNOB_SMALL_RADIUS
            };
            result.controls[index] = Control {
                geometry: [
                    control.center[0],
                    control.center[1],
                    radius,
                    if control.large { 0.0 } else { -1.0 },
                ],
                state: [params.get(control.id) as f32, 1.0, 0.0, 0.0],
            };
            result.scene[2] += 1.0;
        }
        result
    }
}

struct SceneProgram {
    scene: &'static RuntimeScene,
    uniform: Uniform,
}

impl iced_widget::shader::Program<Msg> for SceneProgram {
    type State = ();
    type Primitive = ScenePrimitive;

    fn draw(&self, _: &(), _: mouse::Cursor, _: Rectangle) -> ScenePrimitive {
        ScenePrimitive {
            scene: self.scene,
            uniform: self.uniform,
        }
    }
}

#[derive(Debug)]
struct ScenePrimitive {
    scene: &'static RuntimeScene,
    uniform: Uniform,
}

struct ScenePipeline {
    pipeline: wgpu::RenderPipeline,
    layout: wgpu::BindGroupLayout,
    sampler: wgpu::Sampler,
    controls: wgpu::Buffer,
    binding: Option<(String, wgpu::BindGroup)>,
    bounds: Option<Rectangle>,
}

impl Pipeline for ScenePipeline {
    fn new(device: &wgpu::Device, _: &wgpu::Queue, format: wgpu::TextureFormat) -> Self {
        let texture_entry = |binding, view_dimension| wgpu::BindGroupLayoutEntry {
            binding,
            visibility: wgpu::ShaderStages::FRAGMENT,
            ty: wgpu::BindingType::Texture {
                sample_type: wgpu::TextureSampleType::Float { filterable: true },
                view_dimension,
                multisampled: false,
            },
            count: None,
        };
        let layout = device.create_bind_group_layout(&wgpu::BindGroupLayoutDescriptor {
            label: Some("Free artwork resources"),
            entries: &[
                texture_entry(0, wgpu::TextureViewDimension::D2),
                texture_entry(1, wgpu::TextureViewDimension::D2),
                texture_entry(2, wgpu::TextureViewDimension::D2Array),
                texture_entry(5, wgpu::TextureViewDimension::D2Array),
                wgpu::BindGroupLayoutEntry {
                    binding: 3,
                    visibility: wgpu::ShaderStages::FRAGMENT,
                    ty: wgpu::BindingType::Buffer {
                        ty: wgpu::BufferBindingType::Uniform,
                        has_dynamic_offset: false,
                        min_binding_size: None,
                    },
                    count: None,
                },
                wgpu::BindGroupLayoutEntry {
                    binding: 4,
                    visibility: wgpu::ShaderStages::FRAGMENT,
                    ty: wgpu::BindingType::Sampler(wgpu::SamplerBindingType::Filtering),
                    count: None,
                },
            ],
        });
        let controls = device.create_buffer(&wgpu::BufferDescriptor {
            label: Some("Free artwork controls"),
            size: std::mem::size_of::<Uniform>() as u64,
            usage: wgpu::BufferUsages::UNIFORM | wgpu::BufferUsages::COPY_DST,
            mapped_at_creation: false,
        });
        let sampler = device.create_sampler(&wgpu::SamplerDescriptor {
            address_mode_u: wgpu::AddressMode::Repeat,
            address_mode_v: wgpu::AddressMode::ClampToEdge,
            mag_filter: wgpu::FilterMode::Linear,
            min_filter: wgpu::FilterMode::Linear,
            ..Default::default()
        });
        let shader = device.create_shader_module(wgpu::ShaderModuleDescriptor {
            label: Some("Free linear-light artwork compositor"),
            source: wgpu::ShaderSource::Wgsl(include_str!("artwork.wgsl").into()),
        });
        let pipeline_layout = device.create_pipeline_layout(&wgpu::PipelineLayoutDescriptor {
            label: Some("Free artwork pipeline layout"),
            bind_group_layouts: &[&layout],
            push_constant_ranges: &[],
        });
        let pipeline = device.create_render_pipeline(&wgpu::RenderPipelineDescriptor {
            label: Some("Free artwork"),
            layout: Some(&pipeline_layout),
            vertex: wgpu::VertexState {
                module: &shader,
                entry_point: Some("vs_main"),
                compilation_options: Default::default(),
                buffers: &[],
            },
            fragment: Some(wgpu::FragmentState {
                module: &shader,
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
            sampler,
            controls,
            binding: None,
            bounds: None,
        }
    }
}

impl Primitive for ScenePrimitive {
    type Pipeline = ScenePipeline;

    fn prepare(
        &self,
        pipeline: &mut ScenePipeline,
        device: &wgpu::Device,
        queue: &wgpu::Queue,
        bounds: &Rectangle,
        viewport: &iced_graphics::Viewport,
    ) {
        if pipeline.binding.as_ref().map(|(key, _)| key) != Some(&self.scene.physical_sha256) {
            let base = upload_layer(device, queue, self.scene, &self.scene.base);
            let shadow = upload_layer(device, queue, self.scene, &self.scene.shadow);
            let responses = upload_array(device, queue, self.scene, &self.scene.ring_responses);
            let disc = upload_array(device, queue, self.scene, &self.scene.disc);
            let binding = device.create_bind_group(&wgpu::BindGroupDescriptor {
                label: Some("Free artwork binding"),
                layout: &pipeline.layout,
                entries: &[
                    wgpu::BindGroupEntry {
                        binding: 0,
                        resource: wgpu::BindingResource::TextureView(&base),
                    },
                    wgpu::BindGroupEntry {
                        binding: 1,
                        resource: wgpu::BindingResource::TextureView(&shadow),
                    },
                    wgpu::BindGroupEntry {
                        binding: 2,
                        resource: wgpu::BindingResource::TextureView(&responses),
                    },
                    wgpu::BindGroupEntry {
                        binding: 3,
                        resource: pipeline.controls.as_entire_binding(),
                    },
                    wgpu::BindGroupEntry {
                        binding: 4,
                        resource: wgpu::BindingResource::Sampler(&pipeline.sampler),
                    },
                    wgpu::BindGroupEntry {
                        binding: 5,
                        resource: wgpu::BindingResource::TextureView(&disc),
                    },
                ],
            });
            pipeline.binding = Some((self.scene.physical_sha256.clone(), binding));
        }
        queue.write_buffer(&pipeline.controls, 0, bytemuck::bytes_of(&self.uniform));
        let scale = viewport.scale_factor();
        pipeline.bounds = Some(Rectangle {
            x: bounds.x * scale,
            y: bounds.y * scale,
            width: bounds.width * scale,
            height: bounds.height * scale,
        });
    }

    fn render(
        &self,
        pipeline: &ScenePipeline,
        encoder: &mut wgpu::CommandEncoder,
        target: &wgpu::TextureView,
        clip: &Rectangle<u32>,
    ) {
        let (Some(bounds), Some((_, binding))) = (pipeline.bounds, pipeline.binding.as_ref())
        else {
            return;
        };
        if clip.width == 0 || clip.height == 0 {
            return;
        }
        let mut pass = encoder.begin_render_pass(&wgpu::RenderPassDescriptor {
            label: Some("Free artwork composite"),
            color_attachments: &[Some(wgpu::RenderPassColorAttachment {
                view: target,
                resolve_target: None,
                ops: wgpu::Operations {
                    load: wgpu::LoadOp::Load,
                    store: wgpu::StoreOp::Store,
                },
                depth_slice: None,
            })],
            depth_stencil_attachment: None,
            timestamp_writes: None,
            occlusion_query_set: None,
        });
        pass.set_viewport(bounds.x, bounds.y, bounds.width, bounds.height, 0.0, 1.0);
        pass.set_scissor_rect(clip.x, clip.y, clip.width, clip.height);
        pass.set_pipeline(&pipeline.pipeline);
        pass.set_bind_group(0, binding, &[]);
        pass.draw(0..3, 0..1);
    }
}

fn upload_layer(
    device: &wgpu::Device,
    queue: &wgpu::Queue,
    scene: &RuntimeScene,
    layer: &PackedLayer,
) -> wgpu::TextureView {
    let texture = device.create_texture(&wgpu::TextureDescriptor {
        label: Some("Free artwork RGB9E5"),
        size: wgpu::Extent3d {
            width: layer.width,
            height: layer.height,
            depth_or_array_layers: 1,
        },
        mip_level_count: 1,
        sample_count: 1,
        dimension: wgpu::TextureDimension::D2,
        format: wgpu::TextureFormat::Rgb9e5Ufloat,
        usage: wgpu::TextureUsages::TEXTURE_BINDING | wgpu::TextureUsages::COPY_DST,
        view_formats: &[],
    });
    let start = scene.data_start + layer.offset;
    let bytes = &PACKAGE[start..start + layer.length];
    let source_stride = layer.width as usize * 4;
    let stride = source_stride.div_ceil(wgpu::COPY_BYTES_PER_ROW_ALIGNMENT as usize)
        * wgpu::COPY_BYTES_PER_ROW_ALIGNMENT as usize;
    let padded;
    let bytes = if stride == source_stride {
        bytes
    } else {
        padded = bytes
            .chunks_exact(source_stride)
            .flat_map(|row| {
                row.iter()
                    .copied()
                    .chain(std::iter::repeat_n(0, stride - source_stride))
            })
            .collect::<Vec<_>>();
        &padded
    };
    queue.write_texture(
        texture.as_image_copy(),
        bytes,
        wgpu::TexelCopyBufferLayout {
            offset: 0,
            bytes_per_row: Some(stride as u32),
            rows_per_image: Some(layer.height),
        },
        texture.size(),
    );
    texture.create_view(&wgpu::TextureViewDescriptor::default())
}

fn upload_array(
    device: &wgpu::Device,
    queue: &wgpu::Queue,
    scene: &RuntimeScene,
    layers: &[PackedLayer],
) -> wgpu::TextureView {
    let first = &layers[0];
    let texture = device.create_texture(&wgpu::TextureDescriptor {
        label: Some("Free artwork response library"),
        size: wgpu::Extent3d {
            width: first.width,
            height: first.height,
            depth_or_array_layers: layers.len() as u32,
        },
        mip_level_count: 1,
        sample_count: 1,
        dimension: wgpu::TextureDimension::D2,
        format: wgpu::TextureFormat::Rgb9e5Ufloat,
        usage: wgpu::TextureUsages::TEXTURE_BINDING | wgpu::TextureUsages::COPY_DST,
        view_formats: &[],
    });
    let source_stride = first.width as usize * 4;
    let stride = source_stride.div_ceil(wgpu::COPY_BYTES_PER_ROW_ALIGNMENT as usize)
        * wgpu::COPY_BYTES_PER_ROW_ALIGNMENT as usize;
    let mut data = Vec::with_capacity(stride * first.height as usize * layers.len());
    for layer in layers {
        let start = scene.data_start + layer.offset;
        for row in PACKAGE[start..start + layer.length].chunks_exact(source_stride) {
            data.extend_from_slice(row);
            data.resize(data.len() + stride - source_stride, 0);
        }
    }
    queue.write_texture(
        texture.as_image_copy(),
        &data,
        wgpu::TexelCopyBufferLayout {
            offset: 0,
            bytes_per_row: Some(stride as u32),
            rows_per_image: Some(first.height),
        },
        texture.size(),
    );
    texture.create_view(&wgpu::TextureViewDescriptor {
        dimension: Some(wgpu::TextureViewDimension::D2Array),
        ..Default::default()
    })
}

pub fn validate_assets(
    package_path: &Path,
    layers_directory: &Path,
) -> Result<PackageHeader, String> {
    let bytes = std::fs::read(package_path)
        .map_err(|error| format!("cannot read {}: {error}", package_path.display()))?;
    let header = validate_package_bytes(&bytes, true)?;
    let first = build_package(layers_directory)?;
    let second = build_package(layers_directory)?;
    if first != second {
        return Err("packing the same artwork twice produced different bytes".into());
    }
    if bytes != first {
        return Err(
            "artwork package is not the deterministic result of its editable layers".into(),
        );
    }
    Ok(header)
}

pub fn unpack(package_path: &Path, destination: &Path) -> Result<PackageHeader, String> {
    let bytes = std::fs::read(package_path)
        .map_err(|error| format!("cannot read {}: {error}", package_path.display()))?;
    let header = validate_package_bytes(&bytes, false)?;
    let header_length = u32::from_le_bytes(bytes[8..12].try_into().unwrap()) as usize;
    let payload = &bytes[12 + header_length..];
    std::fs::create_dir_all(destination).map_err(|error| error.to_string())?;
    let mut receipt_layers = Vec::with_capacity(header.layers.len());
    for layer in &header.layers {
        let path = safe_layer_path(destination, &layer.file)?;
        if let Some(parent) = path.parent() {
            std::fs::create_dir_all(parent).map_err(|error| error.to_string())?;
        }
        let encoded = &payload[layer.offset..layer.offset + layer.length];
        let pixels: Vec<[f32; 3]> = encoded
            .chunks_exact(4)
            .map(|word| decode_rgb9e5(u32::from_le_bytes(word.try_into().unwrap())))
            .collect();
        write_exr(&path, layer.width, layer.height, &pixels)?;
        let source = std::fs::read(&path).map_err(|error| error.to_string())?;
        let peak = pixels.iter().flatten().copied().fold(0.0f32, f32::max);
        receipt_layers.push(ReceiptLayer {
            role: layer.role.clone(),
            file: layer.file.clone(),
            width: layer.width,
            height: layer.height,
            channels: "RGB".into(),
            semantics: layer.semantics.clone(),
            row_origin: "top-left".into(),
            sha256: sha256(&source),
            family: layer.family,
            radius: layer.radius,
            step: layer.step,
            value: layer.value,
            size: layer.size,
            peak: matches!(layer.role.as_str(), "ring-response" | "meter-response").then_some(peak),
        });
    }
    let receipt = Receipt {
        schema: RECEIPT_SCHEMA,
        manifest: ReceiptManifest {
            schema: layout::SCHEMA,
            view: header.view.clone(),
            content_sha256: header.layout_content_sha256.clone(),
            physical_sha256: header.physical_sha256.clone(),
            logical_size: [header.logical_size[0] as f32, header.logical_size[1] as f32],
            surface_counts: header.surface_counts.clone(),
        },
        producer: serde_json::json!({
            "revision": "public-rgb9e5-unpack-v1",
            "source_sha256": sha256(&bytes),
            "product_revision": header.physical_sha256,
        }),
        render: RenderReceipt {
            blender: "not-used".into(),
            engine: "public-rgb9e5-unpack".into(),
            samples: header.render.samples,
            seed: header.render.seed,
            max_bounces: header.render.max_bounces,
            base_denoised: header.render.base_denoised,
            responses_denoised: header.render.responses_denoised,
        },
        response_library: header.response_library.clone(),
        layers: receipt_layers,
    };
    write_receipt(destination, &receipt)?;
    Ok(header)
}

fn build_package(directory: &Path) -> Result<Vec<u8>, String> {
    let receipt_path = directory.join("receipt.json");
    let receipt_bytes = std::fs::read(&receipt_path)
        .map_err(|error| format!("cannot read {}: {error}", receipt_path.display()))?;
    let receipt: Receipt = serde_json::from_slice(&receipt_bytes)
        .map_err(|error| format!("invalid {}: {error}", receipt_path.display()))?;
    validate_receipt(&receipt)?;

    let mut payload = Vec::new();
    let mut layers = Vec::with_capacity(receipt.layers.len());
    for source in &receipt.layers {
        let path = safe_layer_path(directory, &source.file)?;
        let source_bytes = std::fs::read(&path)
            .map_err(|error| format!("cannot read {}: {error}", path.display()))?;
        let source_sha256 = sha256(&source_bytes);
        if source_sha256 != source.sha256 {
            return Err(format!("{} does not match its receipt hash", source.file));
        }
        let decoded = decode_exr(&path)?;
        if decoded.width != source.width || decoded.height != source.height {
            return Err(format!(
                "{} is {}x{}, receipt says {}x{}",
                source.file, decoded.width, decoded.height, source.width, source.height
            ));
        }
        let offset = payload.len();
        for pixel in decoded.pixels {
            let word = encode_rgb9e5(pixel)
                .map_err(|error| format!("{} contains {error}", source.file))?;
            if bounded(&source.role)
                && decode_rgb9e5(word)
                    .into_iter()
                    .any(|channel| channel > 1.001)
            {
                return Err(format!(
                    "{} values must stay between zero and one",
                    source.role
                ));
            }
            payload.extend_from_slice(&word.to_le_bytes());
        }
        let length = payload.len() - offset;
        layers.push(PackedLayer {
            role: source.role.clone(),
            file: source.file.clone(),
            width: source.width,
            height: source.height,
            semantics: source.semantics.clone(),
            source_sha256,
            encoded_sha256: sha256(&payload[offset..offset + length]),
            offset,
            length,
            family: source.family,
            radius: source.radius,
            step: source.step,
            value: source.value,
            size: source.size,
            peak: source.peak,
        });
    }
    let header = PackageHeader {
        schema: PACKAGE_SCHEMA,
        view: receipt.manifest.view,
        logical_size: [
            receipt.manifest.logical_size[0] as u32,
            receipt.manifest.logical_size[1] as u32,
        ],
        layout_content_sha256: receipt.manifest.content_sha256,
        physical_sha256: receipt.manifest.physical_sha256,
        surface_counts: receipt.manifest.surface_counts,
        response_library: receipt.response_library,
        render: PackedRender {
            blender: receipt.render.blender,
            engine: receipt.render.engine,
            samples: receipt.render.samples,
            seed: receipt.render.seed,
            max_bounces: receipt.render.max_bounces,
            base_denoised: receipt.render.base_denoised,
            responses_denoised: receipt.render.responses_denoised,
        },
        layers,
    };
    let header_bytes = serde_json::to_vec(&header).map_err(|error| error.to_string())?;
    if header_bytes.len() > MAX_HEADER_BYTES {
        return Err("artwork header is too large".into());
    }
    let header_length =
        u32::try_from(header_bytes.len()).map_err(|_| "artwork header is too large")?;
    let mut package = Vec::with_capacity(12 + header_bytes.len() + payload.len());
    package.extend_from_slice(SIGNATURE);
    package.extend_from_slice(&header_length.to_le_bytes());
    package.extend_from_slice(&header_bytes);
    package.extend_from_slice(&payload);
    Ok(package)
}

fn validate_receipt(receipt: &Receipt) -> Result<(), String> {
    let current = layout::manifest();
    layout::validate(&current)?;
    if receipt.schema != RECEIPT_SCHEMA
        || receipt.manifest.schema != layout::SCHEMA
        || receipt.manifest.view != "amp"
    {
        return Err(format!(
            "receipt must describe the schema-{} amp view",
            layout::SCHEMA
        ));
    }
    let logical = receipt.manifest.logical_size;
    if !logical.into_iter().all(f32::is_finite)
        || logical != current.logical_size
        || logical
            .into_iter()
            .any(|value| value <= 0.0 || value.fract() != 0.0)
    {
        return Err("receipt logical size differs from the live interface".into());
    }
    require_hash("receipt content", &receipt.manifest.content_sha256)?;
    require_hash("receipt physical", &receipt.manifest.physical_sha256)?;
    if receipt.manifest.content_sha256 != layout::content_sha256(&current) {
        return Err("artwork was rendered from a stale layout manifest".into());
    }
    if receipt.manifest.physical_sha256 != current.physical_sha256 {
        return Err("artwork physical layout differs from the live interface".into());
    }
    let mut actual_counts = BTreeMap::new();
    for surface in &current.physical.surfaces {
        *actual_counts.entry(surface.kind.clone()).or_insert(0usize) += 1;
    }
    if receipt.manifest.surface_counts != actual_counts {
        return Err("receipt surface counts differ from the live interface".into());
    }
    let library = &receipt.response_library;
    if library.ring_radii.is_empty()
        || library.ring_steps < 2
        || library.ring_steps > 64
        || library.meter_sizes.is_empty()
        || library
            .resolution
            .into_iter()
            .any(|value| value == 0 || value > MAX_DIMENSION)
        || library
            .ring_radii
            .iter()
            .any(|value| !value.is_finite() || *value <= 0.0)
        || library.ring_radii.windows(2).any(|pair| pair[0] >= pair[1])
        || library
            .meter_sizes
            .iter()
            .flatten()
            .any(|value| !value.is_finite() || *value <= 0.0)
        || library
            .meter_sizes
            .windows(2)
            .any(|pair| pair[0] >= pair[1])
    {
        return Err("receipt response library is invalid".into());
    }
    let expected_layers = 2usize
        .checked_add(
            library
                .ring_radii
                .len()
                .checked_mul(library.ring_steps as usize)
                .ok_or("response layer count overflow")?,
        )
        .and_then(|count| count.checked_add(library.meter_sizes.len() + DISC_LAYERS.len()))
        .ok_or("response layer count overflow")?;
    if receipt.layers.len() != expected_layers || receipt.layers.len() > MAX_LAYERS {
        return Err("receipt response layer count is invalid".into());
    }
    validate_receipt_layer(
        &receipt.layers[0],
        "base",
        "base.exr",
        [logical[0] as u32, logical[1] as u32],
        "scene-linear-radiance",
    )?;
    validate_receipt_layer(
        &receipt.layers[1],
        "shadow",
        "shadow.exr",
        [logical[0] as u32, logical[1] as u32],
        "display-linear-multiplicative",
    )?;
    let mut index = 2;
    for (family, radius) in library.ring_radii.iter().copied().enumerate() {
        for step in 1..=library.ring_steps {
            let layer = &receipt.layers[index];
            validate_receipt_layer(
                layer,
                "ring-response",
                &format!("responses/ring-{family:02}-step-{step:03}.exr"),
                library.resolution,
                "scene-linear-radiance",
            )?;
            if layer.family != Some(family as u32)
                || layer.radius != Some(radius)
                || layer.step != Some(step)
                || layer.value != Some(step as f32 / library.ring_steps as f32)
                || layer.size.is_some()
                || layer
                    .peak
                    .is_none_or(|peak| !peak.is_finite() || peak < 0.0)
            {
                return Err(format!("ring response {family}/{step} metadata is invalid"));
            }
            index += 1;
        }
    }
    for (family, size) in library.meter_sizes.iter().copied().enumerate() {
        let layer = &receipt.layers[index];
        validate_receipt_layer(
            layer,
            "meter-response",
            &format!("responses/meter-{family:02}.exr"),
            library.resolution,
            "scene-linear-radiance",
        )?;
        if layer.family != Some(family as u32)
            || layer.size != Some(size)
            || layer.radius.is_some()
            || layer.step.is_some()
            || layer.value.is_some()
            || layer
                .peak
                .is_none_or(|peak| !peak.is_finite() || peak < 0.0)
        {
            return Err(format!("meter response {family} metadata is invalid"));
        }
        index += 1;
    }
    let (sprite, texels) = disc_sprite();
    for (role, file, semantics) in DISC_LAYERS {
        let layer = &receipt.layers[index];
        validate_receipt_layer(layer, role, file, texels, semantics)?;
        if layer.size != Some(sprite)
            || layer.family.is_some()
            || layer.radius.is_some()
            || layer.step.is_some()
            || layer.value.is_some()
            || layer.peak.is_some()
        {
            return Err(format!("{file} metadata does not describe the disc sprite"));
        }
        index += 1;
    }
    Ok(())
}

fn validate_receipt_layer(
    layer: &ReceiptLayer,
    role: &str,
    file: &str,
    dimensions: [u32; 2],
    semantics: &str,
) -> Result<(), String> {
    if layer.role != role
        || layer.file != file
        || [layer.width, layer.height] != dimensions
        || layer.width == 0
        || layer.height == 0
        || layer.width > MAX_DIMENSION
        || layer.height > MAX_DIMENSION
        || layer.channels != "RGB"
        || layer.semantics != semantics
        || layer.row_origin != "top-left"
    {
        return Err(format!("{file} does not satisfy the {role} layer contract"));
    }
    require_hash(file, &layer.sha256)
}

fn validate_package_bytes(
    bytes: &[u8],
    require_current_layout: bool,
) -> Result<PackageHeader, String> {
    if bytes.get(..8) != Some(SIGNATURE) {
        return Err("invalid artwork package signature".into());
    }
    let header_length = u32::from_le_bytes(
        bytes
            .get(8..12)
            .ok_or("truncated artwork package")?
            .try_into()
            .unwrap(),
    ) as usize;
    if header_length == 0 || header_length > MAX_HEADER_BYTES {
        return Err("invalid artwork header length".into());
    }
    let payload_start = 12usize
        .checked_add(header_length)
        .ok_or("artwork header overflow")?;
    let header: PackageHeader = serde_json::from_slice(
        bytes
            .get(12..payload_start)
            .ok_or("truncated artwork header")?,
    )
    .map_err(|error| format!("invalid artwork header: {error}"))?;
    if header.schema != PACKAGE_SCHEMA
        || header.view != "amp"
        || header.layers.is_empty()
        || header.layers.len() > MAX_LAYERS
    {
        return Err("unsupported artwork package contract".into());
    }
    require_hash("layout content", &header.layout_content_sha256)?;
    require_hash("physical layout", &header.physical_sha256)?;
    if require_current_layout {
        let current = layout::manifest();
        if header.logical_size
            != [
                current.logical_size[0] as u32,
                current.logical_size[1] as u32,
            ]
            || header.layout_content_sha256 != layout::content_sha256(&current)
            || header.physical_sha256 != current.physical_sha256
        {
            return Err("artwork package was built for a different interface layout".into());
        }
    }
    let payload = bytes
        .get(payload_start..)
        .ok_or("truncated artwork payload")?;
    let mut expected_offset = 0usize;
    for layer in &header.layers {
        require_hash("source layer", &layer.source_sha256)?;
        require_hash("encoded layer", &layer.encoded_sha256)?;
        let expected_length = (layer.width as usize)
            .checked_mul(layer.height as usize)
            .and_then(|pixels| pixels.checked_mul(4))
            .ok_or("artwork layer size overflow")?;
        if layer.width == 0
            || layer.height == 0
            || layer.width > MAX_DIMENSION
            || layer.height > MAX_DIMENSION
            || layer.offset != expected_offset
            || layer.length != expected_length
        {
            return Err(format!("invalid packed {} layer geometry", layer.role));
        }
        let end = layer
            .offset
            .checked_add(layer.length)
            .ok_or("artwork layer end overflow")?;
        let encoded = payload
            .get(layer.offset..end)
            .ok_or("truncated artwork pixels")?;
        if sha256(encoded) != layer.encoded_sha256 {
            return Err(format!("packed {} layer checksum mismatch", layer.role));
        }
        for word in encoded.chunks_exact(4) {
            let decoded = decode_rgb9e5(u32::from_le_bytes(word.try_into().unwrap()));
            if decoded
                .into_iter()
                .any(|channel| !channel.is_finite() || channel > 65_408.0)
                || (bounded(&layer.role) && decoded.into_iter().any(|channel| channel > 1.001))
            {
                return Err(format!(
                    "packed {} layer contains invalid values",
                    layer.role
                ));
            }
        }
        expected_offset = end;
    }
    if expected_offset != payload.len() {
        return Err("artwork package contains trailing or unreferenced payload bytes".into());
    }
    validate_packed_order(&header)?;
    Ok(header)
}

fn validate_packed_order(header: &PackageHeader) -> Result<(), String> {
    let expected = 2usize
        .checked_add(
            header.response_library.ring_radii.len() * header.response_library.ring_steps as usize,
        )
        .and_then(|count| {
            count.checked_add(header.response_library.meter_sizes.len() + DISC_LAYERS.len())
        })
        .ok_or("packed response count overflow")?;
    if header.layers.len() != expected
        || header.layers[0].role != "base"
        || header.layers[1].role != "shadow"
        || header.layers[0].semantics != "scene-linear-radiance"
        || header.layers[1].semantics != "display-linear-multiplicative"
    {
        return Err("packed artwork layer order is invalid".into());
    }
    let mut index = 2;
    for (family, radius) in header
        .response_library
        .ring_radii
        .iter()
        .copied()
        .enumerate()
    {
        for step in 1..=header.response_library.ring_steps {
            let layer = &header.layers[index];
            if layer.role != "ring-response"
                || layer.family != Some(family as u32)
                || layer.radius != Some(radius)
                || layer.step != Some(step)
            {
                return Err("packed ring response order is invalid".into());
            }
            index += 1;
        }
    }
    for (family, size) in header
        .response_library
        .meter_sizes
        .iter()
        .copied()
        .enumerate()
    {
        let layer = &header.layers[index];
        if layer.role != "meter-response"
            || layer.family != Some(family as u32)
            || layer.size != Some(size)
        {
            return Err("packed meter response order is invalid".into());
        }
        index += 1;
    }
    // The compositor stamps the sprite at a size it computes from the physical
    // profile, so a sprite of any other size would draw the wrong disc.
    let (sprite, texels) = disc_sprite();
    for (role, file, semantics) in DISC_LAYERS {
        let layer = &header.layers[index];
        if layer.role != role
            || layer.file != file
            || layer.semantics != semantics
            || [layer.width, layer.height] != texels
            || layer.size != Some(sprite)
        {
            return Err("packed switch disc sprite is invalid".into());
        }
        index += 1;
    }
    Ok(())
}

fn decode_exr(path: &Path) -> Result<DecodedExr, String> {
    let image = read_first_rgba_layer_from_file(
        path,
        |resolution, channels| {
            (
                resolution,
                channels.clone(),
                vec![vec![[0.0f32; 3]; resolution.width()]; resolution.height()],
            )
        },
        |storage, position, (red, green, blue, _alpha): (f32, f32, f32, f32)| {
            storage.2[position.y()][position.x()] = [red, green, blue];
        },
    )
    .map_err(|error| format!("cannot decode {}: {error}", path.display()))?;
    let channels = &image.layer_data.channel_data.channels;
    if channels.3.is_some()
        || [
            channels.0.sample_type,
            channels.1.sample_type,
            channels.2.sample_type,
        ]
        .into_iter()
        .any(|sample| sample != SampleType::F32)
        || !matches!(
            image.layer_data.encoding.compression,
            Compression::ZIP1 | Compression::ZIP16
        )
    {
        return Err(format!(
            "{} must be ZIP float32 RGB with no alpha",
            path.display()
        ));
    }
    let (resolution, _, rows) = image.layer_data.channel_data.pixels;
    let width = u32::try_from(resolution.width()).map_err(|_| "EXR width overflow")?;
    let height = u32::try_from(resolution.height()).map_err(|_| "EXR height overflow")?;
    let pixels = rows.into_iter().flatten().collect();
    Ok(DecodedExr {
        width,
        height,
        pixels,
    })
}

fn write_exr(path: &Path, width: u32, height: u32, pixels: &[[f32; 3]]) -> Result<(), String> {
    let expected = (width as usize)
        .checked_mul(height as usize)
        .ok_or("EXR dimensions overflow")?;
    if pixels.len() != expected {
        return Err("EXR pixel count differs from its dimensions".into());
    }
    let layer = Layer::new(
        (width as usize, height as usize),
        LayerAttributes::default(),
        Encoding::SMALL_LOSSLESS,
        SpecificChannels::rgb(|position: Vec2<usize>| {
            let pixel = pixels[position.y() * width as usize + position.x()];
            (pixel[0], pixel[1], pixel[2])
        }),
    );
    Image::from_layer(layer)
        .write()
        .to_file(path)
        .map_err(|error| format!("cannot write {}: {error}", path.display()))
}

fn write_receipt(directory: &Path, receipt: &Receipt) -> Result<(), String> {
    let mut bytes = serde_json::to_vec_pretty(receipt).map_err(|error| error.to_string())?;
    bytes.push(b'\n');
    std::fs::write(directory.join("receipt.json"), bytes).map_err(|error| error.to_string())
}

pub fn refresh_receipt(directory: &Path) -> Result<(), String> {
    let path = directory.join("receipt.json");
    let bytes =
        std::fs::read(&path).map_err(|error| format!("cannot read {}: {error}", path.display()))?;
    let mut receipt: Receipt = serde_json::from_slice(&bytes)
        .map_err(|error| format!("invalid {}: {error}", path.display()))?;
    let mut source_fingerprint = Sha256::new();
    for layer in &mut receipt.layers {
        let layer_path = safe_layer_path(directory, &layer.file)?;
        let source = std::fs::read(&layer_path)
            .map_err(|error| format!("cannot read {}: {error}", layer_path.display()))?;
        let decoded = decode_exr(&layer_path)?;
        if [decoded.width, decoded.height] != [layer.width, layer.height] {
            return Err(format!("{} dimensions changed", layer.file));
        }
        layer.sha256 = sha256(&source);
        if matches!(layer.role.as_str(), "ring-response" | "meter-response") {
            layer.peak = Some(
                decoded
                    .pixels
                    .iter()
                    .flatten()
                    .copied()
                    .fold(0.0f32, f32::max),
            );
        }
        source_fingerprint.update(layer.file.as_bytes());
        source_fingerprint.update([0]);
        source_fingerprint.update(layer.sha256.as_bytes());
    }
    receipt.producer = serde_json::json!({
        "revision": "public-artwork-edit-v1",
        "source_sha256": format!("{:x}", source_fingerprint.finalize()),
        "product_revision": receipt.manifest.physical_sha256,
    });
    validate_receipt(&receipt)?;
    write_receipt(directory, &receipt)
}

fn safe_layer_path(directory: &Path, relative: &str) -> Result<PathBuf, String> {
    let relative = Path::new(relative);
    if relative.is_absolute()
        || relative
            .components()
            .any(|component| !matches!(component, PathComponent::Normal(_)))
    {
        return Err("artwork receipt contains an unsafe layer path".into());
    }
    Ok(directory.join(relative))
}

fn require_hash(name: &str, value: &str) -> Result<(), String> {
    if value.len() != 64
        || !value
            .bytes()
            .all(|byte| byte.is_ascii_digit() || (b'a'..=b'f').contains(&byte))
    {
        return Err(format!(
            "{name} hash must be 64 lowercase hexadecimal characters"
        ));
    }
    Ok(())
}

fn sha256(bytes: &[u8]) -> String {
    format!("{:x}", Sha256::digest(bytes))
}

pub fn encode_rgb9e5(rgb: [f32; 3]) -> Result<u32, &'static str> {
    if rgb.into_iter().any(|channel| !channel.is_finite()) {
        return Err("a non-finite RGB value");
    }
    if rgb
        .into_iter()
        .any(|channel| !(0.0..=65_408.0).contains(&channel))
    {
        return Err("an RGB value outside 0..=65408");
    }
    let maximum = rgb.into_iter().fold(0.0f32, f32::max).max(2.0f32.powi(-16));
    let mut exponent = maximum.log2().floor().max(-16.0) as i32 + 16;
    let mut scale = 2.0f32.powi(exponent - 24);
    if (maximum / scale + 0.5).floor() == 512.0 {
        exponent += 1;
        scale = 2.0f32.powi(exponent - 24);
    }
    if exponent > 31 {
        return Err("an RGB value outside RGB9E5 range");
    }
    let mantissa = |channel: f32| ((channel / scale + 0.5).floor() as u32).min(511);
    Ok(mantissa(rgb[0])
        | (mantissa(rgb[1]) << 9)
        | (mantissa(rgb[2]) << 18)
        | ((exponent as u32) << 27))
}

pub fn decode_rgb9e5(word: u32) -> [f32; 3] {
    let scale = 2.0f32.powi(((word >> 27) & 31) as i32 - 24);
    [
        (word & 0x1ff) as f32 * scale,
        ((word >> 9) & 0x1ff) as f32 * scale,
        ((word >> 18) & 0x1ff) as f32 * scale,
    ]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn rgb9e5_contract_rejects_invalid_hdr_and_round_trips_representative_values() {
        for rgb in [[0.0, 0.0, 0.0], [0.25, 1.0, 4.0], [65_408.0; 3]] {
            let word = encode_rgb9e5(rgb).unwrap();
            let decoded = decode_rgb9e5(word);
            assert!(decoded.into_iter().all(f32::is_finite));
            assert!(
                decoded
                    .into_iter()
                    .all(|value| (0.0..=65_408.0).contains(&value))
            );
        }
        assert!(encode_rgb9e5([f32::NAN, 0.0, 0.0]).is_err());
        assert!(encode_rgb9e5([-0.1, 0.0, 0.0]).is_err());
        assert!(encode_rgb9e5([65_409.0, 0.0, 0.0]).is_err());
    }

    #[test]
    fn bundled_artwork_rejects_corrupt_and_unreferenced_payload_bytes() {
        let header = validate_package_bytes(PACKAGE, true).unwrap();
        // The bundle carries the switch disc the compositor stamps.
        assert!(
            DISC_LAYERS
                .iter()
                .all(|(role, ..)| header.layers.iter().any(|layer| layer.role == *role))
        );

        let mut corrupt = PACKAGE.to_vec();
        let header_length = u32::from_le_bytes(corrupt[8..12].try_into().unwrap()) as usize;
        corrupt[12 + header_length] ^= 1;
        assert!(
            validate_package_bytes(&corrupt, true)
                .unwrap_err()
                .contains("checksum mismatch")
        );

        let mut trailing = PACKAGE.to_vec();
        trailing.push(0);
        assert!(
            validate_package_bytes(&trailing, true)
                .unwrap_err()
                .contains("trailing or unreferenced")
        );
    }
}
