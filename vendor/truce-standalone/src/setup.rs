//! The standalone's audio choices as the plugin's own interface offers
//! them: the input, its channels and the output, what needs the player's
//! attention, and whether the input is the computer's own microphone.
//!
//! A windowed app has no console and the native menu is easy to miss, so
//! the plugin's editor reads [`current`] and changes the same choices the
//! Settings menu does. Outside a running standalone, as in a plug-in host,
//! [`current`] is `None`.

use std::sync::{Arc, Mutex};

use crate::audio::{ChannelRoute, DeviceCache, InputController, OutputController};
use crate::driver;
use crate::settings::SettingsStore;

/// What the player sees and chooses, as of the call.
#[derive(Clone, Debug, Default, PartialEq, Eq)]
pub struct Setup {
    /// Whether the plugin takes an input at all.
    pub takes_input: bool,
    /// On ASIO one interface serves the input and the output, so choosing
    /// either chooses both.
    pub one_interface: bool,
    pub inputs: Vec<String>,
    pub outputs: Vec<String>,
    /// The input that plays, or `None` while the input is off.
    pub input: Option<String>,
    pub output: Option<String>,
    /// The input channels on offer and the ones that feed the plugin, when
    /// the playing input has more than one.
    pub input_channels: Option<(usize, ChannelRoute)>,
    /// Why the input box needs the player.
    pub input_need: Option<InputNeed>,
    /// Why the output box needs the player.
    pub output_need: Option<OutputNeed>,
    /// The playing input is the computer's own microphone, which feeds
    /// back through its speakers.
    pub built_in_microphone: bool,
}

impl Setup {
    /// Whether the editor should open its panel at launch: only for what
    /// the launch itself found, never for a worker's later report.
    #[must_use]
    pub fn needs_attention(&self) -> bool {
        self.output_need.is_some()
            || matches!(
                self.input_need,
                Some(InputNeed::Choose | InputNeed::NotConnected(_) | InputNeed::FellBack(_))
            )
    }
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum InputNeed {
    /// No input was ever chosen, so the input waits for one.
    Choose,
    /// The input remembered or named is not connected.
    NotConnected(String),
    /// The input is connected but would not open.
    DidNotOpen(String),
    /// The ASIO interface would not open, so Windows audio is playing.
    FellBack(String),
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub enum OutputNeed {
    /// The output remembered is not connected; another is playing.
    NotConnected(String),
    /// The output is there but would not start, so nothing plays until
    /// another is chosen.
    DidNotStart(String),
}

/// What the launch found, which stays true until the player changes it.
#[derive(Clone, Debug, Default)]
pub(crate) struct Launch {
    /// A flag named the input, which counts as a choice.
    pub input_named: bool,
    /// The input remembered or named that was not connected.
    pub input_missing: Option<String>,
    /// The output remembered that was not connected.
    pub output_missing: Option<String>,
}

struct Registry {
    input: InputController,
    output: OutputController,
    devices: DeviceCache,
    settings: SettingsStore,
    channels: usize,
    takes_input: bool,
    launch: Launch,
}

static REGISTRY: Mutex<Option<Arc<Registry>>> = Mutex::new(None);
/// The last input that failed, reported by the audio workers until the
/// input plays or the player chooses again.
static FAILURE: Mutex<Option<InputNeed>> = Mutex::new(None);
/// The output the launch could not start, until it or another output plays.
static REFUSED_OUTPUT: Mutex<Option<String>> = Mutex::new(None);

#[allow(clippy::too_many_arguments)]
pub(crate) fn register(
    input: InputController,
    output: OutputController,
    settings: SettingsStore,
    channels: usize,
    takes_input: bool,
    launch: Launch,
) {
    let registry = Registry {
        input,
        output,
        devices: DeviceCache::new(),
        settings,
        channels,
        takes_input,
        launch,
    };
    if let Ok(mut slot) = REGISTRY.lock() {
        *slot = Some(Arc::new(registry));
    }
}

/// Lets the audio workers go once the window has closed.
pub(crate) fn unregister() {
    if let Ok(mut slot) = REGISTRY.lock() {
        *slot = None;
    }
}

pub(crate) fn report_failure(need: Option<InputNeed>) {
    if let Ok(mut failure) = FAILURE.lock() {
        *failure = need;
    }
}

pub(crate) fn report_refused_output(name: Option<String>) {
    if let Ok(mut refused) = REFUSED_OUTPUT.lock() {
        *refused = name;
    }
}

fn registry() -> Option<Arc<Registry>> {
    REGISTRY.lock().ok().and_then(|slot| slot.clone())
}

/// The choices as they stand, or `None` outside a running standalone.
#[must_use]
pub fn current() -> Option<Setup> {
    let registry = registry()?;
    let one_interface = driver::on_asio();
    let enabled = registry.takes_input && registry.input.is_enabled();
    let output = registry.output.current_name();
    let input_name = if one_interface {
        output.clone()
    } else {
        registry.input.current_name()
    };
    let input = input_name.filter(|_| enabled);
    let saved = registry.settings.saved();
    let remembered = if one_interface {
        saved.asio_device
    } else {
        saved.input_device
    };
    let failure = FAILURE.lock().ok().and_then(|failure| failure.clone());
    let input_need = registry
        .takes_input
        .then(|| input_need(&registry.launch, enabled, remembered.as_deref(), failure));
    let refused = REFUSED_OUTPUT
        .lock()
        .ok()
        .and_then(|refused| refused.clone());
    let output_need = refused.map(OutputNeed::DidNotStart).or_else(|| {
        registry
            .launch
            .output_missing
            .as_ref()
            .filter(|name| {
                !one_interface
                    && saved.output_device.as_ref() == Some(*name)
                    && output.as_ref() != Some(*name)
            })
            .map(|name| OutputNeed::NotConnected(name.clone()))
    });
    let details = registry.devices.peek_inputs();
    let detail = input
        .as_ref()
        .and_then(|name| details.iter().find(|detail| &detail.name == name));
    let channel_count = if one_interface {
        registry.channels
    } else {
        registry.input.opened_channels().min(registry.channels)
    };
    Some(Setup {
        takes_input: registry.takes_input,
        one_interface,
        inputs: details.iter().map(|detail| detail.name.clone()).collect(),
        outputs: registry.devices.peek_outputs(),
        input_channels: (input.is_some() && channel_count > 1)
            .then(|| (channel_count, registry.input.channel_route())),
        built_in_microphone: detail.is_some_and(|detail| detail.built_in_microphone),
        input,
        output,
        input_need: input_need.flatten(),
        output_need,
    })
}

/// What the input box says, given what the launch found, whether the input
/// plays, the input remembered for this driver and the last failure.
fn input_need(
    launch: &Launch,
    enabled: bool,
    remembered: Option<&str>,
    failure: Option<InputNeed>,
) -> Option<InputNeed> {
    if enabled {
        return None;
    }
    if failure.is_some() {
        return failure;
    }
    if let Some(missing) = &launch.input_missing
        && remembered.is_none_or(|name| name == missing)
    {
        return Some(InputNeed::NotConnected(missing.clone()));
    }
    (remembered.is_none() && !launch.input_named).then_some(InputNeed::Choose)
}

/// List the devices again in the background, so the next [`current`]
/// reflects what was plugged in or removed.
pub fn refresh() {
    if let Some(registry) = registry() {
        registry.devices.refresh_async();
    }
}

/// Play through `name`, remembered for the next launch, or turn the input
/// off for `None`. On ASIO this chooses the interface, for output too, and
/// the input goes live only once the interface has opened.
pub fn choose_input(name: Option<String>) {
    let Some(registry) = registry() else {
        return;
    };
    report_failure(None);
    match name {
        Some(name) => registry.input.choose(name),
        None => registry.input.set_enabled(false),
    }
}

/// Play through `name`, remembered for the next launch. On ASIO this
/// chooses the interface, for the input too.
pub fn choose_output(name: String) {
    if let Some(registry) = registry() {
        registry.output.set_device(Some(name));
    }
}

/// Feed the plugin from these input channels, remembered for the next launch.
pub fn choose_input_channels(route: ChannelRoute) {
    if let Some(registry) = registry() {
        registry.input.set_channel_route(route);
    }
}

/// Every channel routing a device with `count` channels offers, in the
/// Settings menu's order.
#[must_use]
pub fn channel_choices(count: usize) -> Vec<ChannelRoute> {
    let mut choices = vec![ChannelRoute::Direct];
    choices.extend(
        (0..count.saturating_sub(1))
            .step_by(2)
            .map(|base| ChannelRoute::Stereo { base }),
    );
    choices.extend((0..count).map(|base| ChannelRoute::Mono { base }));
    choices
}

#[cfg(test)]
mod tests {
    use super::{InputNeed, Launch, input_need};

    #[test]
    fn an_input_never_chosen_waits_for_one_until_the_player_turns_it_on() {
        let launch = Launch::default();
        assert_eq!(
            input_need(&launch, false, None, None),
            Some(InputNeed::Choose)
        );
        assert_eq!(input_need(&launch, true, None, None), None);
        assert_eq!(
            input_need(&launch, false, Some("UMC202HD 192k"), None),
            None
        );
        let named = Launch {
            input_named: true,
            ..Launch::default()
        };
        assert_eq!(input_need(&named, false, None, None), None);
    }

    #[test]
    fn a_missing_input_is_named_until_another_is_chosen() {
        let launch = Launch {
            input_missing: Some("UMC202HD 192k".to_owned()),
            ..Launch::default()
        };
        let missing = Some(InputNeed::NotConnected("UMC202HD 192k".to_owned()));
        assert_eq!(
            input_need(&launch, false, Some("UMC202HD 192k"), None),
            missing
        );
        assert_eq!(input_need(&launch, false, None, None), missing);
        assert_eq!(input_need(&launch, false, Some("Scarlett 2i2"), None), None);
        assert_eq!(input_need(&launch, true, Some("UMC202HD 192k"), None), None);
    }

    #[test]
    fn a_failure_is_shown_while_the_input_is_off() {
        let failure = Some(InputNeed::DidNotOpen("Scarlett 2i2".to_owned()));
        let launch = Launch::default();
        assert_eq!(
            input_need(&launch, false, Some("Scarlett 2i2"), failure.clone()),
            failure
        );
        assert_eq!(
            input_need(&launch, true, Some("Scarlett 2i2"), failure),
            None
        );
    }
}
