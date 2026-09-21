use super::cabinet::Cabinet;
pub use super::mapping::AmpControls;
use super::mapping::AmpVoicing;
use super::stage::{STAGES, Tetrode, Triode};
use super::tone_stack::ToneStack;

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

pub struct AmpPath {
    sample_rate: f32,
    voicing: AmpVoicing,
    triodes: [Triode; STAGES],
    tone_stack: ToneStack,
    tetrode: Tetrode,
    cabinet: Cabinet,
    post_tone_gain: f32,
    output_gain: f32,
}

impl AmpPath {
    pub fn new(sample_rate: f32, controls: AmpControls) -> Self {
        let voicing = AmpVoicing::from_controls(controls);
        let triodes = std::array::from_fn(|stage| Triode::new(stage, TRIODE_SCALE, sample_rate));
        let mut path = Self {
            sample_rate,
            voicing,
            triodes,
            tone_stack: ToneStack::new(sample_rate),
            tetrode: Tetrode::new(sample_rate),
            cabinet: Cabinet::new(sample_rate),
            post_tone_gain: 1.,
            output_gain: 1.,
        };
        path.apply_voicing(voicing);
        path.settle();
        path
    }

    pub fn prepare(&mut self, sample_rate: f32, controls: AmpControls) {
        self.sample_rate = sample_rate;
        self.voicing = AmpVoicing::from_controls(controls);
        for triode in &mut self.triodes {
            triode.prepare(sample_rate);
        }
        self.tone_stack.prepare(sample_rate);
        self.tetrode.prepare(sample_rate);
        self.cabinet.prepare(sample_rate);
        self.apply_voicing(self.voicing);
        self.settle();
    }

    pub fn reset(&mut self) {
        for triode in &mut self.triodes {
            triode.reset();
        }
        self.tone_stack.reset();
        self.tetrode.reset();
        self.cabinet.reset();
        self.settle();
    }

    pub fn configure(&mut self, controls: AmpControls) {
        let voicing = AmpVoicing::from_controls(controls);
        if voicing == self.voicing {
            return;
        }
        self.apply_voicing(voicing);
    }

    fn apply_voicing(&mut self, voicing: AmpVoicing) {
        for stage in 0..STAGES {
            self.triodes[stage].configure(voicing.triodes[stage]);
        }
        self.tone_stack.configure(voicing.tone);
        self.tetrode.configure(voicing.tetrode);
        self.cabinet.set_brightness(voicing.cabinet_brightness);
        self.cabinet.set_distance(voicing.cabinet_distance);
        self.cabinet.set_dynamic(voicing.cabinet_dynamic);
        self.cabinet
            .set_dynamic_level(voicing.cabinet_dynamic_level);
        self.post_tone_gain =
            TONE_STACK_SCALE * interpolate(voicing.preamp_drive, &PREAMP_SWEEP) * PREAMP_TARGET;
        self.output_gain = interpolate(voicing.power_drive, &POWER_SWEEP) * voicing.output_gain;
        self.voicing = voicing;
    }

    fn settle(&mut self) {
        let frames = (self.sample_rate * SETTLE_SECONDS) as usize;
        let mut sample = [0.];
        for _ in 0..frames {
            sample[0] = 0.;
            self.process_core(&mut sample, None);
            if self.voicing.cabinet_on {
                self.cabinet.process(&mut sample);
            }
        }
    }

    fn process_core(&mut self, buffer: &mut [f32], mut seams: Option<&mut SeamOutput>) {
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

    pub fn process(&mut self, buffer: &mut [f32]) {
        self.process_core(buffer, None);
        if self.voicing.cabinet_on {
            self.cabinet.process(buffer);
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
    }

    pub fn process_with_seams(&mut self, buffer: &mut [f32], seams: &mut SeamOutput) {
        self.process_core(buffer, Some(seams));
        if self.voicing.cabinet_on {
            self.cabinet.process(buffer);
        }
        seams.cabinet.extend_from_slice(buffer);
        let cabinet_gain = if self.voicing.cabinet_on {
            CABINET_SCALE
        } else {
            1.
        };
        let gain = cabinet_gain * self.output_gain;
        for sample in &mut *buffer {
            *sample *= gain;
        }
        seams.raw_output.extend_from_slice(buffer);
    }
}
