use std::sync::atomic::{AtomicU64, Ordering};

/// The quietest amplitude a meter can show anything at, -60 dBFS. Below it the
/// meter is dark, so a level that has fallen this far is a still picture and
/// the audio side is free to call it silence.
pub const METER_FLOOR: f32 = 0.001;

/// Silence must stay dark, and 0 dBFS must occupy the full meter.
pub fn meter_fraction(amplitude: f32) -> f32 {
    ((20. * amplitude.max(METER_FLOOR).log10() + 60.) / 60.).clamp(0., 1.)
}

pub fn active_bars(amplitude: f32, bars: u32) -> u32 {
    (meter_fraction(amplitude) * bars as f32).floor() as u32
}

/// Peak amplitudes, input L/R then output L/R. The packing holds 0 to 1,
/// which is all a meter ending at 0 dBFS can show.
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn meter_changes_only_at_whole_bar_boundaries() {
        assert_eq!(active_bars(0., 10), 0);
        assert_eq!(active_bars(1., 10), 10);
        for bar in 1..10 {
            let threshold = 10_f32.powf((-60. + bar as f32 * 6.) / 20.);
            assert_eq!(active_bars(threshold * 0.999, 10), bar - 1);
            assert_eq!(active_bars(threshold * 1.001, 10), bar);
        }
    }
}
