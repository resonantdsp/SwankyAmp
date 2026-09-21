use truce::prelude::*;
use truce_iced::iced::widget::{column, container, text};
use truce_iced::iced::{Alignment, Element, Length};
use truce_iced::{IcedPlugin, Message, ParamCache};

const EDITOR_SIZE: (u32, u32) = (640, 360);

#[derive(Params)]
pub struct SwankyAmpParams {
    #[param(id = 65535, name = "Reserved", default = false, flags = "hidden")]
    _reserved: BoolParam,
}

pub struct SwankyAmp;

impl PluginLogic for SwankyAmp {
    type Params = SwankyAmpParams;
    type DspState = ();

    fn init(_: &Self::Params, _: &InitContext) -> Self::DspState {}

    fn process(
        _: &mut Self::DspState,
        _: &Self::Params,
        buffer: &mut AudioBuffer,
        _: &EventList,
        _: &mut ProcessContext,
    ) -> ProcessStatus {
        for channel in 0..buffer.channels() {
            let (input, output) = buffer.io(channel);
            output.copy_from_slice(input);
        }
        for channel in buffer.channels()..buffer.num_output_channels() {
            buffer.output(channel).fill(0.0);
        }
        ProcessStatus::Normal
    }

    fn editor(params: Arc<Self::Params>) -> Box<dyn Editor> {
        truce_iced::IcedEditor::<_, ShellUi>::new(params, EDITOR_SIZE).into_editor()
    }
}

struct ShellUi;

impl IcedPlugin<SwankyAmpParams> for ShellUi {
    type Message = ();

    fn new(_: Arc<SwankyAmpParams>) -> Self {
        Self
    }

    fn title(&self) -> String {
        "Swanky Amp 2".into()
    }

    fn view<'a>(
        &'a self,
        _: &'a ParamCache<SwankyAmpParams>,
    ) -> Element<'a, Message<Self::Message>> {
        container(
            column![text("SWANKY AMP 2").size(30)]
                .align_x(Alignment::Center)
                .spacing(12),
        )
        .center(Length::Fill)
        .into()
    }
}

truce::plugin! { logic: SwankyAmp, params: SwankyAmpParams }

#[cfg(test)]
mod tests {
    use super::*;
    use truce_test::BlockRunner;

    #[test]
    fn host_contract_and_state_round_trip() {
        truce_test::assert_valid_info::<Plugin>();
        truce_test::assert_bus_config_effect::<Plugin>();
        truce_test::assert_has_editor::<Plugin>();
        truce_test::assert_state_round_trip::<Plugin>();
    }

    #[test]
    fn mono_and_stereo_audio_pass_through_across_blocks() {
        let params = SwankyAmpParams::default();
        let mut runner = BlockRunner::<SwankyAmp>::new(&params);
        let events = EventList::default();

        let mono = [-1.0, -0.25, 0.0, 0.5, 1.0];
        let rendered = runner.run(&params, &[&mono], &events);
        assert_eq!(rendered.audio, vec![mono.to_vec()]);

        let left = [0.1, 0.2, 0.3, 0.4];
        let right = [-0.4, -0.3, -0.2, -0.1];
        let rendered = runner.run(&params, &[&left, &right], &events);
        assert_eq!(rendered.audio, vec![left.to_vec(), right.to_vec()]);
    }
}
