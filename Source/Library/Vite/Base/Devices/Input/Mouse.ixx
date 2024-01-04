export module Vite.Device.Input.Mouse;

import Vite.Type.Standard;

export namespace Hedron {

/// Forward Declarations
struct EventData;

///
/// @brief Actions
///
enum class MouseAction {
    Null		= 0x00,
	Raw			= 0x01,
	Click		= 0x10,
	DoubleClick = 0x11,
	Wheel		= 0x20,
	Move		= 0x30,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, MouseAction action) {
	switch (action) {
		case MouseAction::Null:		    { stream << "Null";	    	break; }
		case MouseAction::Raw:			{ stream << "Raw";			break; }
		case MouseAction::Click:		{ stream << "Click";		break; }
		case MouseAction::DoubleClick:	{ stream << "DoubleClick";	break; }
		case MouseAction::Wheel:		{ stream << "Wheel";		break; }
		case MouseAction::Move:			{ stream << "Move";			break; }
		case MouseAction::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

///
/// @brief Buttons
///
enum class MouseButton {
    Null		= 0x00,
	Left		= 0x01,
	Middle		= 0x02,
	Right		= 0x03,
	Wheel		= 0x04,
	X1			= 0x05,
	X2			= 0x06,
	X3			= 0x07,
	X4			= 0x08,
	X5			= 0x09,
	Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, MouseButton button) {
	switch (button) {
		case MouseButton::Null:	    	{ stream << "Default";		break; }
		case MouseButton::Left:			{ stream << "Left";			break; }
		case MouseButton::Middle:		{ stream << "Middle";		break; }
		case MouseButton::Right:		{ stream << "Right";		break; }
		case MouseButton::Wheel:		{ stream << "Wheel";		break; }
		case MouseButton::X1:			{ stream << "X1";			break; }
		case MouseButton::X2:			{ stream << "X2";			break; }
		case MouseButton::X3:			{ stream << "X3";			break; }
		case MouseButton::X4:			{ stream << "X4";			break; }
		case MouseButton::X5:			{ stream << "X5";			break; }
		case MouseButton::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

///
/// @brief Button States
///
enum class MouseButtonState {
	Null		= 0x00,
	Press		= 0x01,
	Hold		= 0x02,
	Release		= 0x03,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, MouseButtonState state) {
	switch (state) {
		case MouseButtonState::Null:		{ stream << "Null";			break; }
		case MouseButtonState::Press:		{ stream << "Press";		break; }
		case MouseButtonState::Hold:		{ stream << "Hold";			break; }
		case MouseButtonState::Release:		{ stream << "Release";		break; }
		case MouseButtonState::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

}
