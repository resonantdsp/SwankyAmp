use objc2_app_kit::NSCursor;

use crate::MouseCursor;

/// Apply a cursor to the current view. Must be called on the main thread.
pub(super) unsafe fn set_cursor(cursor: MouseCursor) {
    if cursor == MouseCursor::Hidden {
        NSCursor::hide();
        return;
    }
    NSCursor::unhide();

    let ns_cursor = match cursor {
        MouseCursor::Default => NSCursor::arrowCursor(),
        MouseCursor::Hand => NSCursor::pointingHandCursor(),
        MouseCursor::HandGrabbing => NSCursor::closedHandCursor(),
        MouseCursor::Help => NSCursor::contextualMenuCursor(),
        MouseCursor::Hidden => return,

        MouseCursor::Text => NSCursor::IBeamCursor(),
        MouseCursor::VerticalText => NSCursor::IBeamCursorForVerticalLayout(),

        // macOS has no built-in busy/working cursor — use the arrow.
        MouseCursor::Working => NSCursor::arrowCursor(),
        MouseCursor::PtrWorking => NSCursor::arrowCursor(),

        MouseCursor::NotAllowed => NSCursor::operationNotAllowedCursor(),
        MouseCursor::PtrNotAllowed => NSCursor::operationNotAllowedCursor(),

        MouseCursor::ZoomIn => NSCursor::arrowCursor(),
        MouseCursor::ZoomOut => NSCursor::arrowCursor(),

        MouseCursor::Alias => NSCursor::dragLinkCursor(),
        MouseCursor::Copy => NSCursor::dragCopyCursor(),
        MouseCursor::Move => NSCursor::openHandCursor(),
        MouseCursor::AllScroll => NSCursor::openHandCursor(),
        MouseCursor::Cell => NSCursor::crosshairCursor(),
        MouseCursor::Crosshair => NSCursor::crosshairCursor(),

        #[allow(deprecated)]
        MouseCursor::EResize => NSCursor::resizeRightCursor(),
        #[allow(deprecated)]
        MouseCursor::WResize => NSCursor::resizeLeftCursor(),
        #[allow(deprecated)]
        MouseCursor::EwResize => NSCursor::resizeLeftRightCursor(),
        #[allow(deprecated)]
        MouseCursor::ColResize => NSCursor::resizeLeftRightCursor(),

        #[allow(deprecated)]
        MouseCursor::NResize => NSCursor::resizeUpCursor(),
        #[allow(deprecated)]
        MouseCursor::SResize => NSCursor::resizeDownCursor(),
        #[allow(deprecated)]
        MouseCursor::NsResize => NSCursor::resizeUpDownCursor(),
        #[allow(deprecated)]
        MouseCursor::RowResize => NSCursor::resizeUpDownCursor(),

        MouseCursor::NeResize
        | MouseCursor::NwResize
        | MouseCursor::SeResize
        | MouseCursor::SwResize
        | MouseCursor::NwseResize
        | MouseCursor::NeswResize => NSCursor::arrowCursor(),
    };

    ns_cursor.set();
}
