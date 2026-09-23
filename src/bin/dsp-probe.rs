use swanky_amp::dsp::amp::AmpControls;
use swanky_amp::dsp::diagnostics::{oversampling_impulse, reset_equilibrium};
use swanky_amp::engine::doublings_for;

fn main() {
    println!("{{");
    println!("  \"policy\": [");
    for (rate_index, sample_rate) in [44_100., 48_000., 88_200., 96_000.].into_iter().enumerate() {
        print!("    {{\"sample_rate\": {sample_rate:.0}, \"doublings\": [");
        for choice in 0..4 {
            if choice != 0 {
                print!(", ");
            }
            print!("{}", doublings_for(choice, sample_rate));
        }
        println!("]}}{}", if rate_index == 3 { "" } else { "," });
    }
    println!("  ],");
    println!("  \"impulses\": [");
    for doublings in 1..=2 {
        let impulse = oversampling_impulse(doublings);
        println!(
            "    {{\"factor\": {}, \"reported_latency\": {}, \"peak_sample\": {}, \"peak_value\": {:.9}, \"symmetry_max_error\": {:.9}, \"dc_gain\": {:.9}}}{}",
            impulse.factor,
            impulse.reported_latency,
            impulse.peak_sample,
            impulse.peak_value,
            impulse.symmetry_max_error,
            impulse.dc_gain,
            if doublings == 2 { "" } else { "," },
        );
    }
    println!("  ],");
    println!("  \"reset_extremes\": [");
    let extremes = [
        (
            "minimum",
            AmpControls {
                input: -1.,
                output: -1.,
                low: -1.,
                mid: -1.,
                high: -1.,
                presence: -1.,
                tone_stack: -1.,
                stages: 1.1,
                overhead: -1.,
                low_cut: -1.,
                cabinet_brightness: -1.,
                cabinet_distance: -1.,
                cabinet_dynamic: -1.,
                preamp_drive: -1.,
                preamp_tight: -1.,
                preamp_grit: -1.,
                power_drive: -1.,
                power_tight: -1.,
                power_sag: -1.,
                power_sag_ratio: -1.,
                ..AmpControls::default()
            },
        ),
        (
            "maximum",
            AmpControls {
                input: 1.,
                output: 1.,
                low: 1.,
                mid: 1.,
                high: 1.,
                presence: 1.,
                tone_stack: 1.,
                stages: 5.,
                overhead: 1.,
                low_cut: 1.,
                cabinet_brightness: 1.,
                cabinet_distance: 1.,
                cabinet_dynamic: 1.,
                preamp_drive: 1.,
                preamp_tight: 1.,
                preamp_grit: 1.,
                power_drive: 1.,
                power_tight: 1.,
                power_sag: 1.,
                power_sag_ratio: 1.,
                ..AmpControls::default()
            },
        ),
    ];
    let mut first = true;
    for sample_rate in [44_100., 48_000., 88_200., 96_000.] {
        let doublings = doublings_for(0, sample_rate);
        for (name, controls) in extremes {
            let audit = reset_equilibrium(sample_rate as f32, controls, doublings);
            if !first {
                println!(",");
            }
            first = false;
            print!(
                "    {{\"name\": \"{name}\", \"sample_rate\": {sample_rate:.0}, \"factor\": {}, \"max_error\": {:.9}, \"rms_error\": {:.9}, \"stale_max_error\": {:.9}}}",
                1 << doublings,
                audit.max_error,
                audit.rms_error,
                audit.stale_max_error,
            );
        }
    }
    println!("\n  ]");
    println!("}}");
}
