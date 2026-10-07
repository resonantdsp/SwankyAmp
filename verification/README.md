# Verification

Run the maintained commands in the [product guide](../README.md). The [reference comparison](reference/README.md) holds the released-model renders and their check; `model`, `dsp` and `tone-stack` hold the model comparison, the DSP reports and the tone-stack refit.

## Open limits

These can only be confirmed on a real machine, so qualification confirms them on the candidate's own installers:

- On Windows, Website, Manual and Support in the information panel, and Download when an update is announced, open the default browser at their page.
- On Windows, a host that unloads the plug-in while the update check, a save dialog or a preset import is running does not crash.
- On Windows, saving a preset while another program holds its file reports an error in the footer and leaves the old preset intact.
- On macOS, opening the Audio Unit in GarageBand twice writes the update check's record beside the interface setting.
- On each platform, Save as… in a system dialog pointed at another folder never replaces a preset in the preset folder.
- On macOS, the standalone relaunched with its remembered interface unplugged keeps the input off and opens the information panel naming the interface.
- On macOS, the standalone relaunched with its remembered output unplugged names that output in the panel with the output that is playing.
- On macOS, choosing the computer's own microphone in the standalone shows the feedback warning, and the next launch asks for an input instead of opening that microphone.
- On Windows, the standalone's first launch on ASIO keeps the input off and opens the panel, with both boxes naming the interface; choosing it there turns the input on.
- On Windows, the standalone relaunched on ASIO with its saved interface unplugged and another ASIO driver installed keeps the input off and names the missing interface.
- On Windows, the standalone whose ASIO interface is held by another program plays through Windows audio with the input off and says the interface did not open.
- On Windows, switching the standalone's audio driver from ASIO to Windows audio, and back, turns the input off each time.
- On Windows, the laptop's own microphone chosen in the standalone on Windows audio shows the feedback warning.
- On Windows, long device names in the standalone's panel are cut with an ellipsis.
- On each platform, an oversampling change while playing switches at once in an Audio Unit or VST3 host, with a click at the switch expected, and in a CLAP host applies after the host restarts the plug-in.

The Linux build has never been run on a real machine. Before a release declares a Linux download again, a person confirms there that choosing the standalone's input, input channels and output in the information panel switches the devices.
