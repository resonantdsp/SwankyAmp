use std::sync::atomic::{AtomicU64, Ordering};

/// The released 1.x input meter, in dBFS after the Input control. A player
/// sets Input by eye: a light strum peaks about one third of the way up with a
/// single coil, about two thirds with a humbucker.
pub const INPUT_SCALE_DB: (f32, f32) = (-26., 8.);

/// The output meter, in dBFS after the cabinet and Output control.
pub const OUTPUT_SCALE_DB: (f32, f32) = (-60., 0.);

/// The scale of each meter, input L/R then output L/R.
pub const SCALES_DB: [(f32, f32); 4] = [
    INPUT_SCALE_DB,
    INPUT_SCALE_DB,
    OUTPUT_SCALE_DB,
    OUTPUT_SCALE_DB,
];

/// Where `db` falls on a meter spanning `scale`, 0 at its foot and 1 at its
/// top.
pub fn scale_fraction(db: f32, (low, high): (f32, f32)) -> f32 {
    ((db - low) / (high - low)).clamp(0., 1.)
}

/// The quietest amplitude the meter on `scale` shows anything at. Below it
/// the meter is dark, so a level that has fallen this far is a still picture
/// and the audio side is free to call it silence.
pub fn floor_amplitude((low, _): (f32, f32)) -> f32 {
    10_f32.powf(low / 20.)
}

/// Peak amplitudes, input L/R then output L/R, as fractions of their meters.
pub fn fractions(amplitudes: [f32; 4]) -> [f32; 4] {
    std::array::from_fn(|meter| {
        let amplitude = amplitudes[meter];
        if amplitude > 0. {
            scale_fraction(20. * amplitude.log10(), SCALES_DB[meter])
        } else {
            0.
        }
    })
}

pub fn active_bars(fraction: f32, bars: u32) -> u32 {
    (fraction.clamp(0., 1.) * bars as f32).floor() as u32
}

/// Meter fractions, input L/R then output L/R.
#[derive(Debug, Clone, Copy)]
pub struct Snapshot {
    pub levels: [f32; 4],
    pub revision: u64,
}

#[derive(Debug, Default)]
pub struct MeterState {
    packed: AtomicU64,
}

impl MeterState {
    pub fn publish(&self, levels: [f32; 4]) {
        self.packed.store(pack(levels), Ordering::Release);
    }

    pub fn revision(&self) -> u64 {
        self.packed.load(Ordering::Acquire)
    }

    pub fn snapshot(&self) -> Snapshot {
        let revision = self.revision();
        Snapshot {
            levels: unpack(revision),
            revision,
        }
    }
}

fn pack(levels: [f32; 4]) -> u64 {
    levels
        .into_iter()
        .enumerate()
        .fold(0, |packed, (index, level)| {
            let value = (level.clamp(0., 1.) * f32::from(u16::MAX)).round() as u16;
            packed | (u64::from(value) << (index * 16))
        })
}

fn unpack(packed: u64) -> [f32; 4] {
    std::array::from_fn(|index| {
        let value = ((packed >> (index * 16)) & u64::from(u16::MAX)) as u16;
        f32::from(value) / f32::from(u16::MAX)
    })
}
