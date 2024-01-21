export module Vite.Device.Input.Controller;

import Vite.Extension;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Controller Actions
///
enum class ControllerAction {
    Undefined,
    Analog,
    Button,
    Digital,
};

// Controller Action Names
template<>
struct NamedEnumTraits<ControllerAction> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Analog",
        "Button",
        "Digital",
    };
};

///
/// @brief Controller Buttons
///
enum class ControllerButton {
    Undefined			= 0x00,

    // Analog Sticks
    AStickLeftPress		= 0x10,
    AStickLeftX			= 0x11,
    AStickLeftY			= 0x12,
    AStickRightPress	= 0x13,
    AStickRightX		= 0x14,
    AStickRightY		= 0x15,

    // Digital Pad
	DPadLeft			= 0x21,
	DPadUp				= 0x22,
	DPadRight			= 0x23,
	DPadDown			= 0x24,

    // Buttons
	Button0				= 0x30,
	Button1				= 0x31,
	Button2				= 0x32,
	Button3				= 0x33,
	Button4				= 0x34,
	Button5				= 0x35,
	Button6				= 0x36,
	Button7				= 0x37,
	Button8				= 0x38,
	Button9				= 0x39,
	Button10			= 0x3A,
	Button11			= 0x3B,
	Button12			= 0x3C,
	Button13			= 0x3D,
	Button14			= 0x3E,
	Button15			= 0x3F,
	ShoulderLeft1		= 0x40,
	ShoulderLeft2		= 0x41,
	ShoulderRight1		= 0x42,
	ShoulderRight2		= 0x43,

    // Named Buttons
    Start				= 0x50,

	Unknown 			= 0xFF,
};

// Controller Button Names
template<>
struct NamedEnumTraits<ControllerButton> {
    static constexpr string_view Names[] = {
        "Undefined",

        // Analog Sticks
        "AStickLeftPress",
        "AStickLeftX",
        "AStickLeftY",
        "AStickRightPress",
        "AStickRightX",
        "AStickRightY",

        // Digital Pad
        "DPadLeft",
        "DPadUp",
        "DPadRight",
        "DPadDown",

        // Buttons
        "Button0",
        "Button1",
        "Button2",
        "Button3",
        "Button4",
        "Button5",
        "Button6",
        "Button7",
        "Button8",
        "Button9",
        "Button10",
        "Button11",
        "Button12",
        "Button13",
        "Button14",
        "Button15",
        "ShoulderLeft1",
        "ShoulderLeft2",
        "ShoulderRight1",
        "ShoulderRight2",

        // Named Buttons
        "Start",

        "Unknown",
    };
};

///
/// @Button Controller States
///
enum class ControllerButtonState {
    Undefined,
	Press,
	Release,
};

// Controller Button State Names
template<>
struct NamedEnumTraits<ControllerButtonState> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Press",
        "Release",
    };
};


///
/// Overloads
///

/// Formatter
template<>
struct EnableNamedEnumFormatter<ControllerAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<ControllerButton> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<ControllerButtonState> {
    static const bool Enable = true;
};

/// Stream
template<>
struct EnableNamedEnumStreamOperators<ControllerAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<ControllerButton> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<ControllerButtonState> {
    static const bool Enable = true;
};

}
