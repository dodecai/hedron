export module Vite.Device.Input.Mouse;

import Vite.Extension;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Mouse Actions
///
enum class MouseAction {
    Undefined,
	Click,
	DoubleClick,
    Hold,
    Move,
    Raw,
	Wheel,
};

// Mouse Action Names
template<>
struct NamedEnumTraits<MouseAction> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Click",
        "DoubleClick",
        "Hold",
        "Move",
        "Raw",
        "Wheel",
    };
};


///
/// @brief Mouse Buttons
///
enum class MouseButton {
    Undefined,
	Left,
	Middle,
	Right,
	Wheel,
	Extra1,
	Extra2,
};

// Mouse Button Names
template<>
struct NamedEnumTraits<MouseButton> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Left",
        "Middle",
        "Right",
        "Wheel",
        "Extra1",
        "Extra2",
    };
};


///
/// @brief Mouse Button States
///
enum class MouseButtonState {
    Undefined,
	Press,
	Hold,
	Release,
};

// Mouse Button State Names
template<>
struct NamedEnumTraits<MouseButtonState> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Press",
        "Hold",
        "Release",
    };
};


///
/// Overloads
///

/// Formatter
template<>
struct EnableNamedEnumFormatter<MouseAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<MouseButton> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<MouseButtonState> {
    static const bool Enable = true;
};

/// Stream
template<>
struct EnableNamedEnumStreamOperators<MouseAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<MouseButton> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<MouseButtonState> {
    static const bool Enable = true;
};

}
