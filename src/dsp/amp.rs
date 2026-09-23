use super::cabinet::Cabinet;
pub use super::mapping::AmpControls;
use super::mapping::AmpVoicing;
use super::oversample::Oversampler;
use super::stage::{PlateFilter, STAGES, Tetrode, Triode};
pub use super::tone_stack::ToneMapping;
use super::tone_stack::ToneStack;

pub(crate) const MAX_OVERSAMPLING: usize = 2;

const SETTLE_SECONDS: f32 = 1.;
const TRIODE_SCALE: f32 = 35.013_34;
const PREAMP_TARGET: f32 = 32.288_06;
const TONE_STACK_SCALE: f32 = 1. / 0.530_222;
const CABINET_SCALE: f32 = 1. / 2.821_151;

#[allow(clippy::excessive_precision)] // Released calibration values are kept verbatim.
const PREAMP_SWEEP: [f32; 11] = [
    4.487_723e-3,
    3.323_652e-3,
    1.606_984e-3,
    6.262_808e-4,
    2.279_750e-4,
    7.981_833e-5,
    2.851_987e-5,
    1.361_236e-5,
    1.102_758e-5,
    1.065_001e-5,
    9.354_531e-6,
];

#[allow(clippy::excessive_precision)] // Released calibration values are kept verbatim.
const POWER_SWEEP: [f32; 11] = [
    8.572_513e-1,
    4.489_064e-1,
    2.412_848e-1,
    1.278_829e-1,
    6.694_987e-2,
    4.332_370e-2,
    3.664_175e-2,
    3.589_781e-2,
    3.497_760e-2,
    3.313_881e-2,
    3.162_063e-2,
];

fn interpolate(value: f32, table: &[f32; 11]) -> f32 {
    let bin = (value + 1.) * 5.;
    let index = if bin >= 10. {
        9
    } else if bin >= 0. {
        bin as usize
    } else {
        0
    };
    table[index] + (table[index + 1] - table[index]) * (bin - index as f32)
}

#[derive(Debug, Default)]
pub struct SeamOutput {
    pub triodes: [Vec<f32>; STAGES],
    pub tone_stack: Vec<f32>,
    pub power_amp: Vec<f32>,
    pub cabinet: Vec<f32>,
    pub raw_output: Vec<f32>,
}

impl SeamOutput {
    pub fn with_capacity(frames: usize) -> Self {
        Self {
            triodes: std::array::from_fn(|_| Vec::with_capacity(frames)),
            tone_stack: Vec::with_capacity(frames),
            power_amp: Vec::with_capacity(frames),
            cabinet: Vec::with_capacity(frames),
            raw_output: Vec::with_capacity(frames),
        }
    }
}

struct TubePath {
    sample_rate: f32,
    voicing: AmpVoicing,
    triodes: [Triode; STAGES],
    tone_stack: ToneStack,
    tetrode: Tetrode,
    post_tone_gain: f32,
}

impl TubePath {
    fn new(
        sample_rate: f32,
        controls: AmpControls,
        plate_filter: PlateFilter,
        tone_mapping: ToneMapping,
    ) -> Self {
        let voicing = AmpVoicing::from_controls(controls);
        let triodes = std::array::from_fn(|stage| {
            Triode::new(stage, TRIODE_SCALE, sample_rate, plate_filter)
        });
        let mut path = Self {
            sample_rate,
            voicing,
            triodes,
            tone_stack: ToneStack::new(sample_rate, tone_mapping),
            tetrode: Tetrode::new(sample_rate),
            post_tone_gain: 1.,
        };
        path.apply_voicing(voicing);
        path
    }

    fn prepare(&mut self, sample_rate: f32, controls: AmpControls) {
        self.sample_rate = sample_rate;
        self.voicing = AmpVoicing::from_controls(controls);
        for triode in &mut self.triodes {
            triode.prepare(sample_rate);
        }
        self.tone_stack.prepare(sample_rate);
        self.tetrode.prepare(sample_rate);
        self.apply_voicing(self.voicing);
    }

    fn configure(&mut self, voicing: AmpVoicing) {
        if voicing != self.voicing {
            self.apply_voicing(voicing);
        }
    }

    fn apply_voicing(&mut self, voicing: AmpVoicing) {
        for (triode, controls) in self.triodes.iter_mut().zip(voicing.triodes) {
            triode.configure(controls);
        }
        self.tone_stack.configure(voicing.tone);
        self.tetrode.configure(voicing.tetrode);
        self.post_tone_gain =
            TONE_STACK_SCALE * interpolate(voicing.preamp_drive, &PREAMP_SWEEP) * PREAMP_TARGET;
        self.voicing = voicing;
    }

    fn settle(&mut self) {
        let frames = (self.sample_rate * SETTLE_SECONDS) as usize;
        let mut sample = [0.];
        for _ in 0..frames {
            sample[0] = 0.;
            self.process(&mut sample, None);
        }
    }

    fn settle_equilibrium(&mut self) {
        let mut value = 0.;
        for triode in &mut self.triodes {
            value = triode.settle(value);
        }
        value *= TRIODE_SCALE;
        value = self.tone_stack.settle(value);
        value *= self.post_tone_gain * self.voicing.power_gain;
        self.tetrode.settle(value);
    }

    fn process(&mut self, buffer: &mut [f32], mut seams: Option<&mut SeamOutput>) {
        for sample in buffer {
            let mut value = *sample * self.voicing.input_gain * self.voicing.preamp_gain;
            for (stage, triode) in self.triodes.iter_mut().enumerate() {
                value = triode.process(value);
                if triode.controls().mix != 0.
                    && let Some(output) = seams.as_deref_mut()
                {
                    output.triodes[stage].push(value);
                }
            }
            value *= TRIODE_SCALE;
            value = self.tone_stack.process(value);
            if let Some(output) = seams.as_deref_mut() {
                output.tone_stack.push(value);
            }
            value *= self.post_tone_gain * self.voicing.power_gain;
            value = self.tetrode.process(value);
            if let Some(output) = seams.as_deref_mut() {
                output.power_amp.push(value);
            }
            *sample = value / PREAMP_TARGET;
        }
    }
}

pub struct AmpPath {
    tubes: TubePath,
    cabinet: Cabinet,
    voicing: AmpVoicing,
    output_gain: f32,
}

impl AmpPath {
    pub fn new_legacy(sample_rate: f32, controls: AmpControls) -> Self {
        let mut path = Self::new(
            sample_rate,
            controls,
            PlateFilter::Released44k1,
            ToneMapping::Released,
        );
        path.tubes.settle();
        path
    }

    fn new_shipping(sample_rate: f32, controls: AmpControls, tone_mapping: ToneMapping) -> Self {
        Self::new(sample_rate, controls, PlateFilter::Fixed20k, tone_mapping)
    }

    fn new(
        sample_rate: f32,
        controls: AmpControls,
        plate_filter: PlateFilter,
        tone_mapping: ToneMapping,
    ) -> Self {
        let voicing = AmpVoicing::from_controls(controls);
        let mut path = Self {
            tubes: TubePath::new(sample_rate, controls, plate_filter, tone_mapping),
            cabinet: Cabinet::new(sample_rate),
            voicing,
            output_gain: 1.,
        };
        path.apply_voicing(voicing);
        path
    }

    /// Leaves the tubes unsettled; the caller settles them only when this
    /// path's tubes will carry audio.
    fn prepare(&mut self, sample_rate: f32, controls: AmpControls) {
        let voicing = AmpVoicing::from_controls(controls);
        self.tubes.prepare(sample_rate, controls);
        self.cabinet.prepare(sample_rate);
        self.cabinet.reset();
        self.apply_voicing(voicing);
    }

    fn configure(&mut self, voicing: AmpVoicing) {
        if voicing != self.voicing {
            self.apply_voicing(voicing);
        }
    }

    fn apply_voicing(&mut self, voicing: AmpVoicing) {
        self.tubes.configure(voicing);
        self.cabinet.set_brightness(voicing.cabinet_brightness);
        self.cabinet.set_distance(voicing.cabinet_distance);
        self.cabinet.set_dynamic(voicing.cabinet_dynamic);
        self.cabinet
            .set_dynamic_level(voicing.cabinet_dynamic_level);
        self.output_gain = interpolate(voicing.power_drive, &POWER_SWEEP) * voicing.output_gain;
        self.voicing = voicing;
    }

    fn finish(&mut self, buffer: &mut [f32], seams: Option<&mut SeamOutput>) {
        if self.voicing.cabinet_on {
            self.cabinet.process(buffer);
        }
        let mut seams = seams;
        if let Some(output) = seams.as_deref_mut() {
            output.cabinet.extend_from_slice(buffer);
        }
        let cabinet_gain = if self.voicing.cabinet_on {
            CABINET_SCALE
        } else {
            1.
        };
        let gain = cabinet_gain * self.output_gain;
        for sample in &mut *buffer {
            *sample *= gain;
        }
        if let Some(output) = seams {
            output.raw_output.extend_from_slice(buffer);
        }
    }

    fn reset_realtime(&mut self) {
        self.tubes.settle_equilibrium();
        self.cabinet.reset();
    }

    pub fn process(&mut self, buffer: &mut [f32]) {
        self.tubes.process(buffer, None);
        self.finish(buffer, None);
    }

    pub fn process_with_seams(&mut self, buffer: &mut [f32], seams: &mut SeamOutput) {
        self.tubes.process(buffer, Some(seams));
        self.finish(buffer, Some(seams));
    }
}

pub(crate) struct AmpChannel {
    host: AmpPath,
    oversampled: [TubePath; MAX_OVERSAMPLING],
    oversamplers: [Oversampler; MAX_OVERSAMPLING],
    high_rate: Vec<f32>,
    prepared_doublings: usize,
}

impl AmpChannel {
    pub(crate) fn new(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
    ) -> Self {
        Self::with_tone_mapping(
            sample_rate,
            max_block,
            controls,
            doublings,
            ToneMapping::Standard,
        )
    }

    fn with_tone_mapping(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
        tone_mapping: ToneMapping,
    ) -> Self {
        let prepared_doublings = crate::engine::doublings_cap(f64::from(sample_rate));
        let mut channel = Self {
            host: AmpPath::new_shipping(sample_rate, controls, tone_mapping),
            oversampled: std::array::from_fn(|index| {
                TubePath::new(
                    sample_rate * (2 << index) as f32,
                    controls,
                    PlateFilter::Fixed20k,
                    tone_mapping,
                )
            }),
            oversamplers: std::array::from_fn(|index| {
                Oversampler::new(index + 1, max_block.max(1))
            }),
            high_rate: vec![0.; max_block.max(1) << prepared_doublings],
            prepared_doublings,
        };
        channel.settle(doublings);
        channel
    }

    /// Prepares every path the rate allows but settles only the one serving
    /// `doublings`, which changes only through another prepare. Each settle
    /// renders a second of audio at its internal rate, and hosts re-prepare on
    /// every latency change, so settling unused paths multiplied that cost.
    pub(crate) fn prepare(
        &mut self,
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
    ) {
        self.prepared_doublings = crate::engine::doublings_cap(f64::from(sample_rate));
        self.host.prepare(sample_rate, controls);
        for (index, path) in self.oversampled[..self.prepared_doublings]
            .iter_mut()
            .enumerate()
        {
            path.prepare(sample_rate * (2 << index) as f32, controls);
        }
        self.oversamplers =
            std::array::from_fn(|index| Oversampler::new(index + 1, max_block.max(1)));
        self.high_rate
            .resize(max_block.max(1) << self.prepared_doublings, 0.);
        self.settle(doublings);
    }

    fn settle(&mut self, doublings: usize) {
        debug_assert!(doublings <= self.prepared_doublings);
        match doublings {
            0 => self.host.tubes.settle(),
            doublings => self.oversampled[doublings - 1].settle(),
        }
    }

    pub(crate) fn configure(&mut self, controls: AmpControls) {
        let voicing = AmpVoicing::from_controls(controls);
        self.host.configure(voicing);
        for path in &mut self.oversampled[..self.prepared_doublings] {
            path.configure(voicing);
        }
    }

    pub(crate) fn reset_realtime(&mut self, controls: AmpControls) {
        self.configure(controls);
        self.host.reset_realtime();
        for path in &mut self.oversampled[..self.prepared_doublings] {
            path.settle_equilibrium();
        }
        for oversampler in &mut self.oversamplers {
            oversampler.reset();
        }
        self.high_rate.fill(0.);
    }

    pub(crate) fn process(&mut self, buffer: &mut [f32], doublings: usize) {
        if doublings == 0 {
            self.host.process(buffer);
            return;
        }
        debug_assert!(doublings <= self.prepared_doublings);
        let high = &mut self.high_rate[..buffer.len() << doublings];
        let oversampler = &mut self.oversamplers[doublings - 1];
        oversampler.up(buffer, high);
        self.oversampled[doublings - 1].process(high, None);
        oversampler.down(high, buffer);
        self.host.finish(buffer, None);
    }

    pub(crate) fn process_with_seams(
        &mut self,
        buffer: &mut [f32],
        doublings: usize,
        seams: &mut SeamOutput,
    ) {
        if doublings == 0 {
            self.host.process_with_seams(buffer, seams);
            return;
        }
        debug_assert!(doublings <= self.prepared_doublings);
        let high = &mut self.high_rate[..buffer.len() << doublings];
        let oversampler = &mut self.oversamplers[doublings - 1];
        oversampler.up(buffer, high);
        self.oversampled[doublings - 1].process(high, Some(seams));
        oversampler.down(high, buffer);
        self.host.finish(buffer, Some(seams));
    }

    pub(crate) fn latency(&self, doublings: usize) -> usize {
        if doublings == 0 {
            0
        } else {
            self.oversamplers[doublings - 1].latency()
        }
    }
}

/// Offline corrected-model path used by the public measurement commands.
/// `ToneMapping::Standard` is the shipping sound; `Released` isolates the
/// other corrections from the tone-stack change.
pub struct CorrectedPath {
    channel: AmpChannel,
    doublings: usize,
}

impl CorrectedPath {
    pub fn new(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
        tone_mapping: ToneMapping,
    ) -> Self {
        assert!(doublings <= crate::engine::doublings_cap(f64::from(sample_rate)));
        Self {
            channel: AmpChannel::with_tone_mapping(
                sample_rate,
                max_block,
                controls,
                doublings,
                tone_mapping,
            ),
            doublings,
        }
    }

    pub fn process_with_seams(&mut self, buffer: &mut [f32], seams: &mut SeamOutput) {
        self.channel
            .process_with_seams(buffer, self.doublings, seams);
    }

    pub fn process(&mut self, buffer: &mut [f32]) {
        self.channel.process(buffer, self.doublings);
    }

    pub fn latency(&self) -> usize {
        self.channel.latency(self.doublings)
    }

    pub fn factor(&self) -> usize {
        1 << self.doublings
    }
}
