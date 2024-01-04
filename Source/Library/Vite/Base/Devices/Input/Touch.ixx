export module Vite.Device.Input.Touch;

import Vite.Type.Standard;

export namespace Hedron {

/// Forward Declarations
struct EventData;

///
/// @brief Actions
///
enum class TouchAction {
    Null		= 0x00,
	Start		= 0x01,
	Cancel		= 0x02,
	End			= 0x03,
	Move		= 0x30,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, TouchAction action) {
	switch (action) {
		case TouchAction::Null:		    { stream << "Null";		    break; }
		case TouchAction::Start:		{ stream << "Start";		break; }
		case TouchAction::Cancel:		{ stream << "Cancel";		break; }
		case TouchAction::End:			{ stream << "End";			break; }
		case TouchAction::Move:			{ stream << "Move";			break; }
		case TouchAction::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

///
/// @brief Styles
///
enum class TouchStyle {
	Null		= 0x00,

    Hold	    = 0x10,
	Tap			= 0x11,
	DoubleTap	= 0x12,

	Expand		= 0x20,
	Swipe		= 0x30,
	Pich		= 0x40,
	Rotate		= 0x50,

	Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, TouchStyle style) {
	switch (style) {
		case TouchStyle::Null:			{ stream << "Null";			break; }
        case TouchStyle::Hold:	        { stream << "Hold";	        break; }
		case TouchStyle::Tap:			{ stream << "Tap";			break; }
		case TouchStyle::DoubleTap:		{ stream << "DoubleTap";	break; }
		case TouchStyle::Expand:		{ stream << "Expand";		break; }
		case TouchStyle::Swipe:			{ stream << "Swipe";		break; }
		case TouchStyle::Pich:			{ stream << "Pich";			break; }
		case TouchStyle::Rotate:		{ stream << "Rotate";		break; }
		case TouchStyle::Undefined:		{ stream << "-";			break; }
	}
	return stream;
}

}
