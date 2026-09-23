use truce::prelude::*;

#[cfg(feature = "rt-paranoid")]
truce::enable_rt_paranoid!();

pub mod artwork;
pub mod dsp;
pub mod engine;
pub mod layout;
pub mod params;
pub mod presets;
pub mod release_notice;
pub mod style;
pub mod ui;
pub mod widgets;

pub use params::SwankyAmpParams;

pub struct SwankyAmp;

impl PluginLogic for SwankyAmp {
    type Params = SwankyAmpParams;
    type DspState = engine::Engine;

    fn init(params: &Self::Params, _: &InitContext) -> Self::DspState {
        engine::Engine::new(params)
    }

    fn reset(engine: &mut Self::DspState, params: &Self::Params, config: &AudioConfig) {
        engine.reset(params, config.sample_rate, config.max_block_size);
    }

    fn reset_realtime(engine: &mut Self::DspState, params: &Self::Params) {
        engine.reset_realtime(params);
    }

    fn process(
        engine: &mut Self::DspState,
        params: &Self::Params,
        buffer: &mut AudioBuffer,
        _: &EventList,
        _: &mut ProcessContext,
    ) -> ProcessStatus {
        engine.process(params, buffer);
        ProcessStatus::Normal
    }

    fn latency(engine: &Self::DspState) -> u32 {
        engine.latency()
    }

    fn editor(params: Arc<Self::Params>) -> Box<dyn Editor> {
        style::load_fonts();
        truce_iced::IcedEditor::<_, ui::FreeUi>::new(
            params,
            (style::WIDTH as u32, style::HEIGHT as u32),
        )
        .with_font(style::FONT_BYTES)
        .into_editor()
    }
}

truce::plugin! { logic: SwankyAmp, params: SwankyAmpParams }

#[cfg(test)]
mod tests {
    use super::*;
    use truce::core::PluginRuntime;

    fn signal(frames: usize, phase: f32) -> Vec<f32> {
        (0..frames)
            .map(|frame| {
                let x = frame as f32 + phase;
                0.18 * (x * 0.071).sin() + 0.07 * (x * 0.193).cos()
            })
            .collect()
    }

    fn render(
        engine: &mut engine::Engine,
        params: &SwankyAmpParams,
        inputs: &[Vec<f32>],
        host_block: usize,
    ) -> Vec<Vec<f32>> {
        let frames = inputs.first().map_or(0, Vec::len);
        let mut rendered = vec![Vec::with_capacity(frames); inputs.len()];
        let mut start = 0;
        while start < frames {
            let end = (start + host_block).min(frames);
            let input_refs: Vec<&[f32]> =
                inputs.iter().map(|channel| &channel[start..end]).collect();
            let mut block = vec![vec![0.; end - start]; inputs.len()];
            let mut output_refs: Vec<&mut [f32]> =
                block.iter_mut().map(Vec::as_mut_slice).collect();
            let mut buffer =
                AudioBuffer::from_slices_checked(&input_refs, &mut output_refs, end - start);
            engine.process(params, &mut buffer);
            for (output, samples) in rendered.iter_mut().zip(block) {
                output.extend(samples);
            }
            start = end;
        }
        if frames == 0 {
            let input_refs: Vec<&[f32]> = inputs.iter().map(Vec::as_slice).collect();
            let mut block = vec![Vec::new(); inputs.len()];
            let mut output_refs: Vec<&mut [f32]> =
                block.iter_mut().map(Vec::as_mut_slice).collect();
            let mut buffer = AudioBuffer::from_slices_checked(&input_refs, &mut output_refs, 0);
            engine.process(params, &mut buffer);
        }
        rendered
    }

    fn assert_close(left: &[f32], right: &[f32], tolerance: f32) {
        assert_eq!(left.len(), right.len());
        let difference = left
            .iter()
            .zip(right)
            .map(|(left, right)| (left - right).abs())
            .fold(0., f32::max);
        assert!(
            difference <= tolerance,
            "maximum sample difference {difference} exceeds {tolerance}"
        );
    }

    #[test]
    fn host_contract_and_state_round_trip() {
        truce_test::assert_valid_info::<Plugin>();
        truce_test::assert_bus_config_effect::<Plugin>();
        truce_test::assert_has_editor::<Plugin>();
        truce_test::assert_state_round_trip::<Plugin>();
    }

    #[test]
    fn mono_and_stereo_layouts_are_advertised() {
        let layouts = <Plugin as PluginRuntime>::bus_layouts();
        let widths: Vec<(u32, u32)> = layouts
            .iter()
            .map(|layout| {
                (
                    layout.total_input_channels(),
                    layout.total_output_channels(),
                )
            })
            .collect();
        assert_eq!(widths, vec![(2, 2), (1, 1)]);
    }

    #[test]
    fn host_block_size_does_not_change_audio() {
        let params = SwankyAmpParams::default();
        let input = vec![signal(2_113, 0.)];
        let mut small = engine::Engine::new(&params);
        small.reset(&params, 44_100., 31);
        let small = render(&mut small, &params, &input, 17);
        let mut large = engine::Engine::new(&params);
        large.reset(&params, 44_100., 1_024);
        let large = render(&mut large, &params, &input, 2_113);
        assert_close(&small[0], &large[0], 1e-6);

        let empty = vec![Vec::new()];
        let mut engine = engine::Engine::new(&params);
        engine.reset(&params, 44_100., 0);
        assert!(render(&mut engine, &params, &empty, 64)[0].is_empty());
    }

    #[test]
    fn oversampling_policy_reports_its_resolved_host_latency() {
        let params = SwankyAmpParams::default();
        let mut engine = engine::Engine::new(&params);
        for (sample_rate, latency) in [(44_100., 32), (48_000., 32), (88_200., 0), (96_000., 0)] {
            engine.reset(&params, sample_rate, 64);
            assert_eq!(<SwankyAmp as PluginLogic>::latency(&engine), latency);
        }

        params.oversampling.set_value(3);
        engine.reset(&params, 44_100., 64);
        assert_eq!(<SwankyAmp as PluginLogic>::latency(&engine), 48);
        engine.reset(&params, 96_000., 64);
        assert_eq!(<SwankyAmp as PluginLogic>::latency(&engine), 32);
    }

    #[test]
    fn oversampling_reentry_does_not_restore_stale_driven_state() {
        let params = SwankyAmpParams::default();
        params.cabinet_on.set_value(false);
        params.oversampling.set_value(2);
        let mut engine = engine::Engine::new(&params);
        engine.reset(&params, 44_100., 64);
        let settled = render(&mut engine, &params, &[vec![0.; 2_048]], 127);
        let settled_peak = settled[0].iter().copied().map(f32::abs).fold(0., f32::max);
        let _ = render(&mut engine, &params, &[signal(4_096, 0.)], 127);

        params.oversampling.set_value(1);
        engine.reset(&params, 44_100., 64);
        let _ = render(&mut engine, &params, &[vec![0.; 8_192]], 127);
        params.oversampling.set_value(2);
        engine.reset(&params, 44_100., 64);
        let reentry = render(&mut engine, &params, &[vec![0.; 2_048]], 127);
        assert!(
            reentry[0].iter().all(|sample| sample.is_finite()),
            "returning to 2x after silence produced non-finite output"
        );
        let peak = reentry[0].iter().copied().map(f32::abs).fold(0., f32::max);
        let allowed_peak = settled_peak + 1e-8;
        assert!(
            peak <= allowed_peak,
            "returning to 2x emitted a {peak} peak after the other mode had settled; the prepared 2x silence floor was {settled_peak} and the allowed peak was {allowed_peak}"
        );
    }

    #[test]
    fn oversampling_reentry_uses_the_current_control_equilibrium() {
        let params = SwankyAmpParams::default();
        params.cabinet_on.set_value(false);
        params.oversampling.set_value(1);
        let mut switched = engine::Engine::new(&params);
        switched.reset(&params, 44_100., 64);

        params.stages.set_value(5.);
        params.preamp_drive.set_value(0.9);
        params.preamp_grit.set_value(0.7);
        params.power_drive.set_value(0.8);
        params.power_sag.set_value(0.5);
        let _ = render(&mut switched, &params, &[signal(4_096, 0.)], 127);
        params.oversampling.set_value(2);
        switched.reset(&params, 44_100., 64);
        let switched = render(&mut switched, &params, &[vec![0.; 2_048]], 127);

        let mut fresh = engine::Engine::new(&params);
        fresh.reset(&params, 44_100., 64);
        let fresh = render(&mut fresh, &params, &[vec![0.; 2_048]], 127);
        assert_close(&switched[0], &fresh[0], 1e-6);
    }

    #[test]
    fn choices_resolving_to_the_same_factor_keep_audio_state() {
        let params = SwankyAmpParams::default();
        params.cabinet_on.set_value(false);
        let input = signal(4_096, 0.);

        let mut continuous = engine::Engine::new(&params);
        continuous.reset(&params, 44_100., 64);
        let continuous = render(&mut continuous, &params, std::slice::from_ref(&input), 127);

        let mut selected = engine::Engine::new(&params);
        selected.reset(&params, 44_100., 64);
        let first = render(&mut selected, &params, &[input[..2_048].to_vec()], 127);
        params.oversampling.set_value(2);
        let second = render(&mut selected, &params, &[input[2_048..].to_vec()], 127);
        let selected: Vec<f32> = first[0].iter().chain(&second[0]).copied().collect();
        assert_close(&selected, &continuous[0], 1e-6);
    }

    #[cfg(feature = "standalone")]
    #[test]
    fn standalone_adapter_restarts_the_current_controls_for_latency_changes() {
        let transition = truce_standalone::audio::dynamic_latency_transition::<
            __truce_runtime::__HotShellWrapper,
            _,
        >(|params| {
            params.stages.set_value(5.);
            params.preamp_drive.set_value(0.9);
            params.preamp_grit.set_value(0.7);
            params.power_drive.set_value(0.8);
            params.oversampling.set_value(1);
        });
        assert_eq!(transition.active_before, 32);
        assert_eq!(transition.requested_after_process, 0);
        assert!(
            transition.restart_queued,
            "standalone did not hand the changed latency to its output worker"
        );
        assert_eq!(transition.active_after_restart, 0);
    }

    #[cfg(feature = "clap")]
    #[test]
    fn clap_adapter_keeps_active_latency_until_restart() {
        let transition =
            truce_clap::dynamic_latency_transition::<__truce_runtime::__HotShellWrapper>(21, 1.);
        assert_eq!(transition.active_before, 32);
        assert_eq!(transition.reported_while_active, 32);
        assert_eq!(transition.callback_requests, 1);
        assert_eq!(transition.restart_requests, 1);
        assert_eq!(transition.active_after_restart, 0);
        assert_eq!(transition.latency_notifications, 1);
        assert!(
            transition.active_output_peak > 1e-4,
            "CLAP adapter check did not process meaningful audio"
        );
        assert!(
            transition.active_reset_max_error <= 2.5e-4,
            "CLAP real-time reset did not return the active path to its prepared equilibrium (audio error {})",
            transition.active_reset_max_error
        );
        assert!(
            transition.uncleared_state_error >= 1e-3,
            "CLAP adapter check did not establish materially driven state before reset (unreset error {})",
            transition.uncleared_state_error
        );
        assert_eq!(
            transition.active_reset_allocations, 0,
            "CLAP active reset allocated on the real-time thread"
        );
    }

    #[test]
    fn increasing_stage_count_after_silence_reenters_warm() {
        let params = SwankyAmpParams::default();
        let mut engine = engine::Engine::new(&params);
        engine.reset(&params, 44_100., 64);
        let silence = vec![vec![0.; 2_048]];
        let settled = render(&mut engine, &params, &silence, 127);
        assert!(
            settled[0].iter().all(|sample| sample.is_finite()),
            "settled 3-stage silence contained non-finite output before the stage-count change"
        );
        let settled_peak = settled[0].iter().copied().map(f32::abs).fold(0., f32::max);

        params.stages.set_value(5.);
        let reentry = render(&mut engine, &params, &silence, 127);
        assert!(
            reentry[0].iter().all(|sample| sample.is_finite()),
            "raising Stages from 3 to 5 produced non-finite output after settled silence"
        );
        let reentry_peak = reentry[0].iter().copied().map(f32::abs).fold(0., f32::max);
        let allowed_peak = settled_peak + 1e-7;
        assert!(
            reentry_peak <= allowed_peak,
            "raising Stages from 3 to 5 emitted a {reentry_peak} peak after settled silence; \
             the measured silence floor was {settled_peak} and the allowed peak was {allowed_peak}"
        );
    }

    #[test]
    fn mono_and_stereo_paths_are_finite_silent_and_independent() {
        let params = SwankyAmpParams::default();
        let left = signal(1_027, 0.);
        let right = signal(1_027, 37.);

        let mut stereo_engine = engine::Engine::new(&params);
        stereo_engine.reset(&params, 44_100., 64);
        let stereo = render(
            &mut stereo_engine,
            &params,
            &[left.clone(), right.clone()],
            127,
        );
        let mut left_engine = engine::Engine::new(&params);
        left_engine.reset(&params, 44_100., 64);
        let mono_left = render(&mut left_engine, &params, &[left], 127);
        let mut right_engine = engine::Engine::new(&params);
        right_engine.reset(&params, 44_100., 64);
        let mono_right = render(&mut right_engine, &params, &[right], 127);

        assert_close(&stereo[0], &mono_left[0], 1e-6);
        assert_close(&stereo[1], &mono_right[0], 1e-6);
        assert!(stereo.iter().flatten().all(|sample| sample.is_finite()));

        let mut silence_engine = engine::Engine::new(&params);
        silence_engine.reset(&params, 44_100., 64);
        let silence = render(&mut silence_engine, &params, &[vec![0.; 2_048]], 257);
        let silence_peak = silence[0].iter().copied().map(f32::abs).fold(0., f32::max);
        assert!(
            silence_peak < 3e-7,
            "Auto oversampling emitted a {silence_peak} peak for silent input"
        );
    }

    #[test]
    fn supported_rates_are_finite_and_rate_reset_is_repeatable() {
        let params = SwankyAmpParams::default();
        let input = vec![signal(521, 11.)];
        let mut engine = engine::Engine::new(&params);
        for sample_rate in [8_000., 44_100., 96_000., 192_000., 384_000.] {
            engine.reset(&params, sample_rate, 73);
            let output = render(&mut engine, &params, &input, 131);
            assert!(
                output[0].iter().all(|sample| sample.is_finite()),
                "non-finite output at {sample_rate} Hz"
            );
        }

        let mut reused = engine::Engine::new(&params);
        reused.reset(&params, 96_000., 73);
        let _ = render(&mut reused, &params, &input, 131);
        reused.reset(&params, 48_000., 73);
        let reused = render(&mut reused, &params, &input, 131);
        let mut fresh = engine::Engine::new(&params);
        fresh.reset(&params, 48_000., 73);
        let fresh = render(&mut fresh, &params, &input, 131);
        assert_close(&reused[0], &fresh[0], 1e-6);
    }
}
