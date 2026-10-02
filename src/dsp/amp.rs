use super::cabinet::Cabinet;
pub use super::filters::ClipKnee;
pub use super::mapping::AmpControls;
use super::mapping::AmpVoicing;
use super::oversample::Oversampler;
use super::stage::{STAGES, Tetrode, Triode, TubeFilters};
pub use super::tone_stack::ToneMapping;
use super::tone_stack::ToneStack;

pub(crate) const MAX_OVERSAMPLING: usize = 2;

const SETTLE_SECONDS: f32 = 1.;
const TRIODE_SCALE: f32 = 35.013_34;
const PREAMP_TARGET: f32 = 32.288_06;
const CABINET_SCALE: f32 = 1. / 2.821_151;

#[allow(clippy::excessive_precision)] // Released calibration values are kept verbatim.
const RELEASED_PREAMP_SWEEP: [f32; 11] = [
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
const RELEASED_POWER_SWEEP: [f32; 11] = [
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

/// The level compensation. The preamp scale against Drive and the tone
/// stack's gain set the level into the power stage; the output gains against
/// Power Drive, Drive and Grit follow the cabinet, so they change loudness
/// without changing the sound. Each table holds 11 evenly spaced points of
/// its control from -1 to 1, shaped for Drive and Power Drive.
#[derive(Debug, Clone, Copy, PartialEq)]
pub struct LevelTables {
    pub preamp: [f32; TABLE_POINTS],
    pub tone_stack: f32,
    pub power: [f32; TABLE_POINTS],
    pub drive: [f32; TABLE_POINTS],
    pub grit: [f32; TABLE_POINTS],
    /// The most Grit may raise the triode compressor's threshold, in its
    /// control units. Above about 0.72 the threshold of the most detuned
    /// stage sits above its plate signal, the compressor never charges, its
    /// ceiling falls to zero and the stage's output collapses to a constant:
    /// 1.4.0 lost 52 dB at full Grit this way.
    pub grit_compression: f32,
}

impl LevelTables {
    /// The 1.4.0 values, which the legacy path keeps.
    pub const RELEASED: Self = Self {
        preamp: RELEASED_PREAMP_SWEEP,
        tone_stack: 1. / 0.530_222,
        power: RELEASED_POWER_SWEEP,
        drive: [1.; TABLE_POINTS],
        grit: [1.; TABLE_POINTS],
        grit_compression: 1.,
    };

    /// The values `calibrate` measured for the shipping path.
    pub const CALIBRATED: Self = Self {
        preamp: super::calibration_data::PREAMP_SWEEP,
        tone_stack: super::calibration_data::TONE_STACK_SCALE,
        power: super::calibration_data::POWER_SWEEP,
        drive: super::calibration_data::DRIVE_GAIN,
        grit: super::calibration_data::GRIT_GAIN,
        grit_compression: GRIT_COMPRESSION_LIMIT,
    };
}

pub const TABLE_POINTS: usize = 11;
/// Fender, Marshall and AC30.
pub const TONE_STACKS: usize = 3;

/// Keeps the compressor threshold just below the collapse at about 0.72,
/// where it still reaches the plate signal at every input level measured.
pub(crate) const GRIT_COMPRESSION_LIMIT: f32 = 0.7;

pub(crate) fn interpolate(value: f32, table: &[f32; TABLE_POINTS]) -> f32 {
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

/// A gain multiplier that glides linearly to its target across the next
/// block, so a control change never steps. At rest every sample gets exactly
/// the target, which keeps resting renders unchanged.
#[derive(Debug, Clone, Copy)]
struct Ramp {
    current: f32,
    target: f32,
}

impl Ramp {
    fn new(value: f32) -> Self {
        Self {
            current: value,
            target: value,
        }
    }

    /// Lands on the target immediately, for a prepare or a state restore.
    fn snap(&mut self) {
        self.current = self.target;
    }

    fn block(&mut self, frames: usize) -> impl Iterator<Item = f32> + use<> {
        let start = self.current;
        let step = (self.target - start) / frames.max(1) as f32;
        if frames > 0 {
            self.current = self.target;
        }
        (1..=frames).map(move |frame| start + step * frame as f32)
    }
}

#[derive(Debug, Default)]
pub struct SeamOutput {
    pub triodes: [Vec<f32>; STAGES],
    pub tone_stack: Vec<f32>,
    /// What the power stage is fed: the tone-stack seam with the level
    /// compensation and Power Drive's gain applied.
    pub power_input: Vec<f32>,
    pub power_amp: Vec<f32>,
    pub cabinet: Vec<f32>,
    pub raw_output: Vec<f32>,
}

impl SeamOutput {
    pub fn with_capacity(frames: usize) -> Self {
        Self {
            triodes: std::array::from_fn(|_| Vec::with_capacity(frames)),
            tone_stack: Vec::with_capacity(frames),
            power_input: Vec::with_capacity(frames),
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
    tables: LevelTables,
    input_gain: Ramp,
    preamp_gain: Ramp,
    power_gain: Ramp,
}

impl TubePath {
    fn new(
        sample_rate: f32,
        controls: AmpControls,
        filters: TubeFilters,
        tone_mapping: ToneMapping,
        knee: ClipKnee,
        tables: LevelTables,
    ) -> Self {
        let voicing = AmpVoicing::from_controls(controls);
        let triodes = std::array::from_fn(|stage| {
            Triode::new(stage, TRIODE_SCALE, sample_rate, filters, knee)
        });
        let mut path = Self {
            sample_rate,
            voicing,
            triodes,
            tone_stack: ToneStack::new(sample_rate, tone_mapping),
            tetrode: Tetrode::new(sample_rate, filters),
            tables,
            input_gain: Ramp::new(1.),
            preamp_gain: Ramp::new(1.),
            power_gain: Ramp::new(1.),
        };
        path.apply_voicing(voicing);
        path.snap_gains();
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
        self.snap_gains();
    }

    fn configure(&mut self, voicing: AmpVoicing) {
        if voicing != self.voicing {
            self.apply_voicing(voicing);
        }
    }

    fn apply_voicing(&mut self, voicing: AmpVoicing) {
        for (triode, mut controls) in self.triodes.iter_mut().zip(voicing.triodes) {
            controls.comp_level = controls.comp_level.min(self.tables.grit_compression);
            triode.configure(controls);
        }
        self.tone_stack.configure(voicing.tone);
        self.tetrode.configure(voicing.tetrode);
        let post_tone_gain = self.tables.tone_stack
            * interpolate(voicing.preamp_drive, &self.tables.preamp)
            * PREAMP_TARGET;
        self.input_gain.target = voicing.input_gain;
        self.preamp_gain.target = voicing.preamp_gain;
        self.power_gain.target = post_tone_gain * voicing.power_gain;
        self.voicing = voicing;
    }

    fn snap_gains(&mut self) {
        self.input_gain.snap();
        self.preamp_gain.snap();
        self.power_gain.snap();
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
        self.snap_gains();
        let mut value = 0.;
        for triode in &mut self.triodes {
            value = triode.settle(value);
        }
        value *= TRIODE_SCALE;
        value = self.tone_stack.settle(value);
        value *= self.power_gain.target;
        self.tetrode.settle(value);
    }

    fn process(&mut self, buffer: &mut [f32], mut seams: Option<&mut SeamOutput>) {
        let frames = buffer.len();
        let gains = self
            .input_gain
            .block(frames)
            .zip(self.preamp_gain.block(frames))
            .zip(self.power_gain.block(frames));
        for (sample, ((input_gain, preamp_gain), power_gain)) in buffer.iter_mut().zip(gains) {
            let mut value = *sample * input_gain * preamp_gain;
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
            value *= power_gain;
            if let Some(output) = seams.as_deref_mut() {
                output.power_input.push(value);
            }
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
    tables: LevelTables,
    output_gain: Ramp,
}

impl AmpPath {
    pub fn new_legacy(sample_rate: f32, controls: AmpControls) -> Self {
        let mut path = Self::new(
            sample_rate,
            controls,
            TubeFilters::Released44k1,
            ToneMapping::Released,
            ClipKnee::Released,
            LevelTables::RELEASED,
        );
        path.tubes.settle();
        path
    }

    fn new_shipping(
        sample_rate: f32,
        controls: AmpControls,
        tone_mapping: ToneMapping,
        knee: ClipKnee,
        tables: LevelTables,
    ) -> Self {
        Self::new(
            sample_rate,
            controls,
            TubeFilters::AsAt96k,
            tone_mapping,
            knee,
            tables,
        )
    }

    fn new(
        sample_rate: f32,
        controls: AmpControls,
        filters: TubeFilters,
        tone_mapping: ToneMapping,
        knee: ClipKnee,
        tables: LevelTables,
    ) -> Self {
        let voicing = AmpVoicing::from_controls(controls);
        let mut path = Self {
            tubes: TubePath::new(sample_rate, controls, filters, tone_mapping, knee, tables),
            cabinet: Cabinet::new(sample_rate),
            voicing,
            tables,
            output_gain: Ramp::new(1.),
        };
        path.apply_voicing(voicing);
        path.output_gain.snap();
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
        self.output_gain.snap();
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
        self.output_gain.target = interpolate(voicing.power_drive, &self.tables.power)
            * interpolate(voicing.preamp_drive, &self.tables.drive)
            * interpolate(voicing.preamp_grit, &self.tables.grit)
            * voicing.output_gain;
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
        let gains = self.output_gain.block(buffer.len());
        for (sample, output_gain) in buffer.iter_mut().zip(gains) {
            *sample *= cabinet_gain * output_gain;
        }
        if let Some(output) = seams {
            output.raw_output.extend_from_slice(buffer);
        }
    }

    fn reset_realtime(&mut self) {
        self.output_gain.snap();
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
        Self::with_corrections(
            sample_rate,
            max_block,
            controls,
            doublings,
            ToneMapping::Standard,
            ClipKnee::UnitSlope,
            LevelTables::CALIBRATED,
        )
    }

    fn with_corrections(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
        tone_mapping: ToneMapping,
        knee: ClipKnee,
        tables: LevelTables,
    ) -> Self {
        let prepared_doublings = crate::engine::doublings_cap(f64::from(sample_rate));
        let mut channel = Self {
            host: AmpPath::new_shipping(sample_rate, controls, tone_mapping, knee, tables),
            oversampled: std::array::from_fn(|index| {
                TubePath::new(
                    sample_rate * (2 << index) as f32,
                    controls,
                    TubeFilters::AsAt96k,
                    tone_mapping,
                    knee,
                    tables,
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
    /// `doublings`; `switch` settles another when the factor changes. Each
    /// settle renders a second of audio at its internal rate, and hosts
    /// re-prepare on every latency change, so settling unused paths multiplied
    /// that cost.
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
        let tubes = self.tubes(doublings);
        tubes.settle();
        // Waking from rest thumps the power stage's grid, and at a low Power
        // Tight the charge takes seconds to drain, so the first notes would
        // play quieter than the rest. The rendered state is kept wherever the
        // grid stayed uncharged, as for Init and the factory voicing, which
        // were judged from it.
        if tubes.tetrode.grid_charged() {
            tubes.settle_equilibrium();
        }
    }

    fn tubes(&mut self, doublings: usize) -> &mut TubePath {
        match doublings {
            0 => &mut self.host.tubes,
            doublings => &mut self.oversampled[doublings - 1],
        }
    }

    /// Moves the audio to another prepared factor without allocating or
    /// rendering, so it can happen on the audio thread: the incoming path
    /// starts from the current controls' equilibrium, as a real-time reset
    /// leaves it.
    pub(crate) fn switch(&mut self, doublings: usize) {
        debug_assert!(doublings <= self.prepared_doublings);
        self.tubes(doublings).settle_equilibrium();
        for oversampler in &mut self.oversamplers {
            oversampler.reset();
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
/// `ToneMapping::Standard` with `ClipKnee::UnitSlope` and
/// `LevelTables::CALIBRATED` is the shipping sound; the released choices
/// isolate the other corrections in measurements.
pub struct CorrectedPath {
    channel: AmpChannel,
    doublings: usize,
}

impl CorrectedPath {
    /// The path the plugin engine runs, with whatever corrections it ships,
    /// so long-run checks follow the product without restating them.
    pub fn shipping(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
    ) -> Self {
        assert!(doublings <= crate::engine::doublings_cap(f64::from(sample_rate)));
        Self {
            channel: AmpChannel::new(sample_rate, max_block, controls, doublings),
            doublings,
        }
    }

    pub fn new(
        sample_rate: f32,
        max_block: usize,
        controls: AmpControls,
        doublings: usize,
        tone_mapping: ToneMapping,
        knee: ClipKnee,
        tables: LevelTables,
    ) -> Self {
        assert!(doublings <= crate::engine::doublings_cap(f64::from(sample_rate)));
        Self {
            channel: AmpChannel::with_corrections(
                sample_rate,
                max_block,
                controls,
                doublings,
                tone_mapping,
                knee,
                tables,
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

#[cfg(test)]
mod tests {
    use super::*;

    fn controls() -> AmpControls {
        AmpControls {
            cabinet_on: false,
            ..AmpControls::default()
        }
    }

    fn tube_path(sample_rate: f32) -> TubePath {
        tube_path_with(sample_rate, controls())
    }

    fn tube_path_with(sample_rate: f32, controls: AmpControls) -> TubePath {
        TubePath::new(
            sample_rate,
            controls,
            TubeFilters::AsAt96k,
            ToneMapping::Standard,
            ClipKnee::UnitSlope,
            LevelTables::CALIBRATED,
        )
    }

    fn sine(sample_rate: f32, frequency: f32, amplitude: f32) -> Vec<f32> {
        (0..(sample_rate * 0.05) as usize)
            .map(|frame| {
                amplitude * (std::f32::consts::TAU * frequency * frame as f32 / sample_rate).sin()
            })
            .collect()
    }

    fn level_db(samples: &[f32]) -> f32 {
        let power = samples.iter().map(|sample| sample * sample).sum::<f32>();
        10. * (power / samples.len() as f32 + 1e-30).log10()
    }

    /// The level of a quiet tone through tubes at `sample_rate`, after half
    /// the tone has passed.
    fn tone_level(sample_rate: f32, frequency: f32) -> f32 {
        let mut path = tube_path(sample_rate);
        path.settle_equilibrium();
        let mut tone = sine(sample_rate, frequency, 0.01);
        path.process(&mut tone, None);
        level_db(&tone[tone.len() / 2..])
    }

    #[test]
    fn the_tubes_keep_their_tone_at_every_rate() {
        for frequency in [5_000., 7_000., 10_000.] {
            let voiced = tone_level(96_000., frequency);
            for sample_rate in [44_100., 48_000., 88_200., 176_400., 192_000., 384_000.] {
                let difference = tone_level(sample_rate, frequency) - voiced;
                assert!(
                    difference.abs() < 0.2,
                    "tubes at {sample_rate} Hz play {frequency} Hz {difference:+.2} dB from 96 kHz"
                );
            }
        }
    }

    #[test]
    fn real_time_reset_keeps_the_amp_playing_at_high_rates() {
        // Low settings whose bass section rounds its pole onto z = 1 at these
        // rates once held in single precision.
        for sample_rate in [352_800., 384_000.] {
            for step in 0..=50 {
                let low = step as f32 / 25. - 1.;
                let mut path = tube_path_with(sample_rate, AmpControls { low, ..controls() });
                path.settle_equilibrium();
                let mut tone = sine(sample_rate, 1_000., 0.1);
                tone.truncate(1_000);
                path.process(&mut tone, None);
                let level = level_db(&tone);
                assert!(
                    tone.iter().all(|sample| sample.is_finite()) && level > -60.,
                    "tubes at {sample_rate} Hz with Low {low} played {level:.0} dB after a \
                     real-time reset"
                );
            }
        }
    }

    #[test]
    fn activation_starts_at_the_level_it_holds() {
        // Settings whose start-up thump charges the power stage's grid, which
        // a low Power Tight drains over seconds.
        let controls = AmpControls {
            low: 1.,
            overhead: 1.,
            preamp_drive: -0.93,
            preamp_grit: 1.,
            power_tight: -1.,
            ..controls()
        };
        let sample_rate = 16_000.;
        let input = sine(sample_rate, 220., 0.2);
        let level_after = |seconds: f32| {
            let mut channel = AmpChannel::new(sample_rate, input.len(), controls, 0);
            let mut silence = vec![0.; (sample_rate * seconds) as usize];
            channel.process(&mut silence, 0);
            let mut played = input.clone();
            channel.process(&mut played, 0);
            level_db(&played)
        };
        // Eight seconds of rest drain any start-up charge to the level the
        // amp holds.
        let difference = level_after(0.) - level_after(8.);
        assert!(
            difference.abs() < 0.5,
            "the first notes after activation played {difference:+.1} dB from the level held \
             after a rest"
        );
    }
}
