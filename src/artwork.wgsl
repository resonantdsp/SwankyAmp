struct Control {
    geometry: vec4<f32>,
    state: vec4<f32>,
}

struct Controls {
    scene: vec4<f32>,
    ring: vec4<f32>,
    emission: vec4<f32>,
    marker: vec4<f32>,
    polar: vec4<f32>,
    extent: vec4<f32>,
    cap: vec4<f32>,
    cap_style: vec4<f32>,
    controls: array<Control, 32>,
}

@group(0) @binding(0) var base: texture_2d<f32>;
@group(0) @binding(1) var shadow: texture_2d<f32>;
@group(0) @binding(2) var responses: texture_2d_array<f32>;
@group(0) @binding(3) var<uniform> controls: Controls;
@group(0) @binding(4) var linear_sampler: sampler;
@group(0) @binding(5) var cap: texture_2d_array<f32>;

struct VertexOut {
    @builtin(position) position: vec4<f32>,
    @location(0) uv: vec2<f32>,
}

@vertex
fn vs_main(@builtin(vertex_index) index: u32) -> VertexOut {
    let positions = array<vec2<f32>, 3>(
        vec2(-1.0, -1.0),
        vec2(3.0, -1.0),
        vec2(-1.0, 3.0),
    );
    let point = positions[index];
    return VertexOut(
        vec4(point, 0.0, 1.0),
        vec2(point.x * 0.5 + 0.5, 0.5 - point.y * 0.5),
    );
}

fn segment_nearest(point: vec2<f32>, radius: f32, start: f32, sweep: f32) -> vec2<f32> {
    let angle = atan2(-point.y, point.x);
    let relative = (start - angle + 6.283185307) % 6.283185307;
    if relative <= sweep {
        return point / max(length(point), 0.0001) * radius;
    }
    let a = radius * vec2(cos(start), -sin(start));
    let b = radius * vec2(cos(start - sweep), -sin(start - sweep));
    return select(b, a, length(point - a) < length(point - b));
}

fn arc_distance(point: vec2<f32>, radius: f32, value: f32) -> f32 {
    return length(point - segment_nearest(point, radius, controls.ring.z, controls.ring.w * value));
}

fn response_uv(point: vec2<f32>) -> vec2<f32> {
    let radius = length(point);
    let a = controls.polar.x;
    let b = controls.polar.y;
    let low = controls.polar.z;
    let high = controls.polar.w;
    var row: f32;
    if radius < a {
        row = radius / a * low;
    } else if radius < b {
        row = low + (radius - a) / (b - a) * (high - low);
    } else {
        row = high + (radius - b) / (controls.extent.y - b) * (1.0 - high);
    }
    return vec2(atan2(-point.y, point.x) / 6.283185307, row);
}

fn divot_paint(outward: vec2<f32>, amount: f32, depth: f32) -> vec3<f32> {
    let light_direction = normalize(vec3(0.0, -0.55, 0.83));
    let normal = normalize(vec3(-outward * 2.0 * depth * amount, 1.0));
    let diffuse = max(dot(normal, light_direction), 0.0);
    let glint = pow(max(dot(normal, normalize(light_direction + vec3(0.0, 0.0, 1.0))), 0.0), 14.0);
    let occlusion = 1.0 - 0.45 * amount * amount;
    return vec3(0.010, 0.012, 0.015) * (0.5 + 0.5 * diffuse) * occlusion
        + vec3(0.9, 0.92, 0.96) * glint * 0.05;
}

@fragment
fn fs_main(input: VertexOut) -> @location(0) vec4<f32> {
    let point = input.uv * controls.scene.xy;
    var multiplier = textureSampleLevel(shadow, linear_sampler, input.uv, 0.0).rgb;
    // The cap moves, so neither it nor the shadow it casts is in the view's
    // bake: its sprite is stamped over the baked slot here.
    let cap_uv = (point - controls.cap.xy) / controls.cap.zw;
    let on_cap = controls.cap_style.y > 0.5 && all(cap_uv >= vec2(0.0)) && all(cap_uv <= vec2(1.0));
    if on_cap {
        multiplier *= textureSampleLevel(cap, linear_sampler, cap_uv, 1, 0.0).rgb;
    }
    let aa = max(length(fwidth(point)) * 0.7071, 0.001);
    var radiance = textureSampleLevel(base, linear_sampler, input.uv, 0.0).rgb;
    var light = vec3(0.0);

    for (var index = 0u; index < 32u; index++) {
        if f32(index) >= controls.scene.z {
            break;
        }
        let knob = controls.controls[index];
        let radius = knob.geometry.z;
        let local = point - knob.geometry.xy;
        let value = clamp(knob.state.x, 0.0, 1.0);
        if knob.geometry.w >= 0.0 {
            let normalized = local / radius;
            let uv = response_uv(normalized);
            let tail = 1.0 - smoothstep(
                controls.extent.x * 0.875,
                controls.extent.x,
                length(normalized),
            );
            let position = value * controls.scene.w;
            let upper = min(i32(floor(position)), i32(controls.scene.w) - 1);
            let fraction = position - f32(upper);
            let previous = textureSampleLevel(responses, linear_sampler, uv, max(upper - 1, 0), 0.0).rgb;
            let next = textureSampleLevel(responses, linear_sampler, uv, upper, 0.0).rgb;
            light += mix(select(vec3(0.0), previous, upper > 0), next, fraction) * tail;

            let distance = arc_distance(local, radius * controls.ring.x, value);
            let width = radius * controls.ring.y;
            let coverage = 1.0 - smoothstep(width - aa * 0.5, width + aa * 0.5, distance);
            let outside = max(distance - width, 0.0);
            let halo = 0.035 * exp(-0.5 * pow(outside / 1.2, 2.0))
                + 0.008 * exp(-0.5 * pow(outside / 4.0, 2.0));
            let onset = clamp(value * controls.ring.w * radius * controls.ring.x / aa, 0.0, 1.0);
            light += controls.emission.rgb * (coverage + halo) * onset;
        }

        let marker_radius = radius * controls.marker.x;
        let nearest = segment_nearest(local, marker_radius, controls.ring.z - value * controls.ring.w, 0.0);
        let offset = local - nearest;
        let distance = length(offset);
        let outward = offset / max(distance, 0.001);
        let width = radius * controls.marker.y;
        let inside = 1.0 - smoothstep(width - aa * 0.5, width + aa * 0.5, distance);
        let amount = clamp(distance / width, 0.0, 1.0);
        radiance = mix(radiance, divot_paint(outward, amount, controls.marker.z), inside);
        let bevel = 1.0 - smoothstep(0.2, 0.2 + aa, abs(distance - width - 0.3));
        radiance += vec3(0.14) * bevel * max(dot(outward, normalize(vec2(0.15, 1.0))), 0.0) * (1.0 - inside);
        radiance *= 1.0 - 0.14 * bevel * max(-outward.y, 0.0) * (1.0 - inside);
    }

    if on_cap {
        let sprite = textureSampleLevel(cap, linear_sampler, cap_uv, 0, 0.0).rgb;
        let cover = textureSampleLevel(cap, linear_sampler, cap_uv, 2, 0.0).r;
        radiance = radiance * (1.0 - cover) + sprite;
        // The knobs' glossy black divot, at the cap's centre.
        let offset = point - (controls.cap.xy + controls.cap.zw * 0.5);
        let distance = length(offset);
        let outward = offset / max(distance, 0.001);
        let width = controls.cap_style.x;
        let inside = 1.0 - smoothstep(width - aa * 0.5, width + aa * 0.5, distance);
        radiance = mix(radiance, divot_paint(outward, clamp(distance / width, 0.0, 1.0), controls.marker.z), inside);
        let bevel = 1.0 - smoothstep(0.2, 0.2 + aa, abs(distance - width - 0.3));
        radiance += vec3(0.14) * bevel * max(dot(outward, normalize(vec2(0.15, 1.0))), 0.0) * (1.0 - inside);
        radiance *= 1.0 - 0.14 * bevel * max(-outward.y, 0.0) * (1.0 - inside);
    }

    let display_linear = (radiance + light) / (vec3(1.0) + radiance + light) * multiplier;
    return vec4(display_linear, 1.0);
}
