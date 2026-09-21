use std::sync::atomic::{AtomicU64, Ordering};

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
