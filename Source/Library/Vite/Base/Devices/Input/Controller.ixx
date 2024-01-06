export module Vite.Device.Input.Controller;

import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Controller Actions
///
enum class ControllerAction {
    Null		= 0x00,
    Analog		= 0x10,
    Digital		= 0x20,
    Button		= 0x30,
    Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, ControllerAction action) {
    switch (action) {
        case ControllerAction::Null:	    { stream << "Null";	    break; }
        case ControllerAction::Analog:		{ stream << "Analog";	break; }
        case ControllerAction::Digital:		{ stream << "Digital";	break; }
        case ControllerAction::Button:		{ stream << "Button";	break; }
        case ControllerAction::Undefined:	{ stream << "-";		break; }
    }
    return stream;
}

///
/// @brief Controller Buttons
///
enum class ControllerButton {
    // Null
    Null				= 0x00,

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

    // ~
	Undefined			= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, ControllerButton button) {
	switch (button) {
        // Null
		case ControllerButton::Null:				{ stream << "Null";		    	break; }
                                   
        // Analog Sticks
        case ControllerButton::AStickLeftPress:		{ stream << "AStickLeftPress";	break; }
        case ControllerButton::AStickLeftX:			{ stream << "AStickLeftX";		break; }
        case ControllerButton::AStickLeftY:			{ stream << "AStickLeftY";		break; }
        case ControllerButton::AStickRightPress:	{ stream << "AStickLeftPress";	break; }
        case ControllerButton::AStickRightX:		{ stream << "AStickRightX";		break; }
        case ControllerButton::AStickRightY:		{ stream << "AStickRightY";		break; }

        // Digital Pad
		case ControllerButton::DPadLeft:			{ stream << "DPadLeft";			break; }
		case ControllerButton::DPadUp:				{ stream << "DPadUp";			break; }
		case ControllerButton::DPadRight:			{ stream << "DPadRight";		break; }
		case ControllerButton::DPadDown:			{ stream << "DPadDown";			break; }

        // Buttons
		case ControllerButton::Button0:				{ stream << "Button0";			break; }
		case ControllerButton::Button1:				{ stream << "Button1";			break; }
		case ControllerButton::Button2:				{ stream << "Button2";			break; }
		case ControllerButton::Button3:				{ stream << "Button3";			break; }
		case ControllerButton::Button4:				{ stream << "Button4";			break; }
		case ControllerButton::Button5:				{ stream << "Button5";			break; }
		case ControllerButton::Button6:				{ stream << "Button6";			break; }
		case ControllerButton::Button7:				{ stream << "Button7";			break; }
		case ControllerButton::Button8:				{ stream << "Button8";			break; }
		case ControllerButton::Button9:				{ stream << "Button9";			break; }
		case ControllerButton::Button10:			{ stream << "Button10";			break; }
		case ControllerButton::Button11:			{ stream << "Button11";			break; }
		case ControllerButton::Button12:			{ stream << "Button12";			break; }
		case ControllerButton::Button13:			{ stream << "Button13";			break; }
		case ControllerButton::Button14:			{ stream << "Button14";			break; }
		case ControllerButton::Button15:			{ stream << "Button15";			break; }
		case ControllerButton::ShoulderLeft1:		{ stream << "ShoulderLeft1";	break; }
		case ControllerButton::ShoulderLeft2:		{ stream << "ShoulderLeft2";	break; }
		case ControllerButton::ShoulderRight1:		{ stream << "ShoulderRight1";	break; }
		case ControllerButton::ShoulderRight2:		{ stream << "ShoulderRight2";	break; }
                                             
        // Named Buttons
        case ControllerButton::Start:				{ stream << "Start";			break; }

        // ~
		case ControllerButton::Undefined:			{ stream << "-";				break; }
	}
	return stream;
}

///
/// @Button Controller States
///
enum class ControllerButtonState {
	Null		= 0x00,
	Press		= 0x01,
	Hold		= 0x02,
	Release		= 0x03,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, ControllerButtonState state) {
	switch (state) {
		case ControllerButtonState::Null:		{ stream << "Null";			break; }
		case ControllerButtonState::Press:		{ stream << "Press";		break; }
		case ControllerButtonState::Hold:		{ stream << "Hold";			break; }
		case ControllerButtonState::Release:	{ stream << "Release";		break; }
		case ControllerButtonState::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

}
