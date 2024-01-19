export module Vite.Device.Input.Touch;

import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Touch Actions
///
enum class TouchAction {
    Undefined,
	Start,
	Cancel,
	End,
	Move,
};

inline std::ostream &operator<<(std::ostream &stream, TouchAction action) {
	switch (action) {
		case TouchAction::Start:		{ stream << "Start";		break; }
		case TouchAction::Cancel:		{ stream << "Cancel";		break; }
		case TouchAction::End:			{ stream << "End";			break; }
		case TouchAction::Move:			{ stream << "Move";			break; }
		default:	                    { stream << "Undefined";	break; }
	}
	return stream;
}

///
/// @brief Touch Styles
///
enum class TouchStyle {
    Undefined,

    Hold,
	Tap,
	DoubleTap,

	Expand,
	Swipe,
	Pitch,
	Rotate,
};

inline std::ostream &operator<<(std::ostream &stream, TouchStyle style) {
	switch (style) {
        case TouchStyle::Hold:	        { stream << "Hold";	        break; }
		case TouchStyle::Tap:			{ stream << "Tap";			break; }
		case TouchStyle::DoubleTap:		{ stream << "DoubleTap";	break; }
		case TouchStyle::Expand:		{ stream << "Expand";		break; }
		case TouchStyle::Swipe:			{ stream << "Swipe";		break; }
		case TouchStyle::Pitch:			{ stream << "Pitch";		break; }
		case TouchStyle::Rotate:		{ stream << "Rotate";		break; }
		default:                		{ stream << "-";			break; }
	}
	return stream;
}

}
