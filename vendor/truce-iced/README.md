# truce-iced

Iced GUI backend for truce audio plugins.

## Overview

Provides an alternative GUI backend using
[Iced](https://github.com/iced-rs/iced)'s retained-mode widget toolkit with
its Elm-inspired architecture. Use this when you want a declarative,
message-driven UI with Iced's layout engine and widget ecosystem.

`AutoPlugin` can auto-generate a parameter UI from a `GridLayout`, while
`IcedPlugin` gives full control for custom designs.

## Key types

- **`IcedEditor`** -- the `Editor` implementation
- **`IcedPlugin`** -- trait for defining a fully custom iced UI (view, update, message)
- **`AutoPlugin`** -- auto-generated UI from parameter definitions and `GridLayout`

## Usage

```rust
struct MyIcedUi;

impl<P: Params> IcedPlugin<P> for MyIcedUi {
    type Message = MyMessage;

    fn new(params: Arc<P>) -> Self { /* build initial model */ }

    fn view<'a>(&'a self, params: &'a ParamCache<P>) -> Element<'a, Message<MyMessage>> {
        // Build your iced widget tree here
    }

    fn update(
        &mut self,
        message: Message<MyMessage>,
        params: &ParamCache<P>,
        ctx: &PluginContext<P>,
    ) -> Task<Message<MyMessage>> {
        // Handle messages
        Task::none()
    }
}
```

## Dependencies

Beyond iced's sub-crates and truce's own, the desktop targets depend on
[`arboard`](https://crates.io/crates/arboard) (MIT OR Apache-2.0) for the
system clipboard `truce_iced::clipboard` hands iced's widgets. Its default
features are off, so it adds no image support and no `image` crate. What it
needs is already here but for the Windows backend: `objc2`, `objc2-app-kit` and
`objc2-foundation` on macOS, `x11rb`, `parking_lot` and `percent-encoding` on
Linux, and `windows-sys` 0.52 on Windows are all in the tree already, so the
only crates this adds are `arboard` itself and, for Windows, `clipboard-win`
and `error-code`. iOS has no clipboard backend and pastes through the
platform's own text input.

Part of [truce](https://github.com/truce-audio/truce). [Docs](https://truce.audio/docs/).
