export module Vite.Device.Input.Touch;

import Vite.Extension;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Touch Actions [DoubleTap|Expand|Hold|Pitch|Rotate|Swipe|Tap]
///
enum class TouchAction {
    Undefined,
    DoubleTap,
    Expand,
    Hold,
    Pitch,
    Rotate,
    Swipe,
    Tap,
};

// Touch Action Names
template<>
struct NamedEnumTraits<TouchAction> {
    static constexpr string_view Names[] = {
        "Undefined",
        "DoubleTap",
        "Expand",
        "Hold",
        "Pitch",
        "Rotate",
        "Swipe",
        "Tap",
    };
};


///
/// @brief Touch States [Cancel|End|Move|Start]
///
enum class TouchState {
    Undefined,
    Cancel,
    End,
    Move,
    Start,
};

// Touch State Names
template<>
struct NamedEnumTraits<TouchState> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Cancel",
        "End",
        "Move",
        "Start",
    };
};


///
/// Overloads
///

/// Formatter
template<>
struct EnableNamedEnumFormatter<TouchAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<TouchState> {
    static const bool Enable = true;
};

/// Stream
template<>
struct EnableNamedEnumStreamOperators<TouchAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<TouchState> {
    static const bool Enable = true;
};

}
