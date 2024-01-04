export module Vite.Device.Input.Keyboard;

import Vite.Type.Standard;

export namespace Hedron {

/// Forward Declarations
struct EventData;

///
/// @brief Actions
///
enum class KeyboardAction {
    Null		= 0x00,
	Raw			= 0x01,
	Input		= 0x20,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, KeyboardAction action) {
	switch (action) {
        case KeyboardAction::Null:	    { stream << "Null";		break; }
		case KeyboardAction::Raw:		{ stream << "Raw";			break; }
		case KeyboardAction::Input:		{ stream << "Input";		break; }
		case KeyboardAction::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

///
/// @brief Key Codes
///
enum class KeyCode {
	// Source:	https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
    Null		= 0x00,

	// Mouse:	  0x01-02
	Cancel		= 0x03,
	// Mouse:	  0x04-06
	// Undefined: 0x07
	Back		= 0x08,
	Tab			= 0x09,
	// Reserved:  0x0A-0B
	Clear		= 0x0C,
	Return		= 0x0D,
	// Undefined: 0x0E-0F
	Shift		= 0x10,
	Control		= 0x11,
	Alt			= 0x12,
	Pause		= 0x13,
	Capital		= 0x14,
	
	KanaMode	= 0x15,
	HanguelMode	= 0x15,
	HangulMode	= 0x15,
	ImeOn		= 0x16,
	JunjaMode	= 0x17,
	FinalMode	= 0x18,
	HanjaMode	= 0x19,
	KanjiMode	= 0x19,
	ImeOff		= 0x1A,
	
	Escape		= 0x1B,
	
	Convert		= 0x1C,
	NonConvert	= 0x1D,
	Accept		= 0x1E,
	ModeChange	= 0x1F,

	Space		= 0x20,
	PageUp		= 0x21,
	PageDown	= 0x22,
	End			= 0x23,
	Home		= 0x24,

	Left		= 0x25,
	Up			= 0x26,
	Right		= 0x27,
	Down		= 0x28,
	Select		= 0x29,
	Print		= 0x2A,
	Execute		= 0x2B,
	Screen		= 0x2C,
	Insert		= 0x2D,
	Delete		= 0x2E,
	Help		= 0x2F,

	Key0		= 0x30,
	Key1		= 0x31,
	Key2		= 0x32,
	Key3		= 0x33,
	Key4		= 0x34,
	Key5		= 0x35,
	Key6		= 0x36,
	Key7		= 0x37,
	Key8		= 0x38,
	Key9		= 0x39,
	// Undefined: 0x3a-40
	KeyA		= 0x41,
	KeyB		= 0x42,
	KeyC		= 0x43,
	KeyD		= 0x44,
	KeyE		= 0x45,
	KeyF		= 0x46,
	KeyG		= 0x47,
	KeyH		= 0x48,
	KeyI		= 0x49,
	KeyJ		= 0x4A,
	KeyK		= 0x4B,
	KeyL		= 0x4C,
	KeyM		= 0x4D,
	KeyN		= 0x4E,
	KeyO		= 0x4F,
	KeyP		= 0x50,
	KeyQ		= 0x51,
	KeyR		= 0x52,
	KeyS		= 0x53,
	KeyT		= 0x54,
	KeyU		= 0x55,
	KeyV		= 0x56,
	KeyW		= 0x57,
	KeyX		= 0x58,
	KeyY		= 0x59,
	KeyZ		= 0x5A,
	
	Super		= 0x5B,
	RightSuper	= 0x5C,
	Apps		= 0x5D,
	// Reserved:  0x5E
	Sleep		= 0x5F,

	NumPad0		= 0x60,
	NumPad1		= 0x61,
	NumPad2		= 0x62,
	NumPad3		= 0x63,
	NumPad4		= 0x64,
	NumPad5		= 0x65,
	NumPad6		= 0x66,
	NumPad7		= 0x67,
	NumPad8		= 0x68,
	NumPad9		= 0x69,
	Multiply	= 0x6A,
	Add			= 0x6B,
	Seperator	= 0x6C,
	Subtract	= 0x6D,
	Decimal		= 0x6E,
	Divide		= 0x6F,

	F1			= 0x70,
	F2			= 0x71,
	F3			= 0x72,
	F4			= 0x73,
	F5			= 0x74,
	F6			= 0x75,
	F7			= 0x76,
	F8			= 0x77,
	F9			= 0x78,
	F10			= 0x79,
	F11			= 0x7A,
	F12			= 0x7B,
	F13			= 0x7C,
	F14			= 0x7D,
	F15			= 0x7E,
	F16			= 0x7F,
	F17			= 0x80,
	F18			= 0x81,
	F19			= 0x82,
	F20			= 0x83,
	F21			= 0x84,
	F22			= 0x85,
	F23			= 0x86,
	F24			= 0x87,
	// Unassigned:0x88-8F
	Numlock		= 0x90,
	Scroll		= 0x91,

	// OEM Specific: 0x92-96
	// Unassigned: 0x97-9F
	LShift		= 0xA0,
	RShift		= 0xA1,
	LControl	= 0xA2,
	RControl	= 0xA3,
	LAlt		= 0xA4,
	RAlt		= 0xA5,
	
	BrowserBack			= 0xA6,
	BrowserForward		= 0xA7,
	BrowserReload		= 0xA8,
	BrowserStop			= 0xA9,
	BrowserSearch		= 0xAA,
	BrowserFavorites	= 0xAB,
	BrowserHome			= 0xAC,
	VolumeMute			= 0xAD,
	VolumeDown			= 0xAE,
	VolumeUp			= 0xAF,
	MediaNextTrack		= 0xB0,
	MediaPreviousTrack	= 0xB1,
	MediaStop			= 0xB2,
	MediaPlayPause		= 0xB3,
	LaunchMail			= 0xB4,
	LaunchMediaSelect	= 0xB5,
	LaunchApp1			= 0xB6,
	LaunchApp2			= 0xB7,
	// Reserved:		  0xB8-B9

	Oem1		= 0xBA,
	Plus		= 0xBB,
	Comma		= 0xBC,
	Minus		= 0xBD,
	Period		= 0xBE,
	Oem2		= 0xBF,
	Oem3		= 0xC0,
	// Reserved:  0xC1-D7
	// Unassigned:0xD8-DA
	Oem4		= 0xDB,
	Oem5		= 0xDC,
	Oem6		= 0xDD,
	Oem7		= 0xDE,
	Oem8		= 0xDF,
	// Reserved:  0xE0
	Oem9		= 0xE1,
	Oem102		= 0xE2,
	Oem10		= 0xE3,
	Oem11		= 0xE4,
	Process		= 0xE5,
	Oem12		= 0xE6,
	// Packet	= 0xE7, // Used to pass Unicode characters as if they were keystroeks.
	// Unassigned:0xE8
	Oem13		= 0xE9,
	Oem14		= 0xEA,
	Oem15		= 0xEB,
	Oem16		= 0xEC,
	Oem17		= 0xED,
	Oem18		= 0xEE,
	Oem19		= 0xEF,
	Oem20		= 0xF0,
	Oem21		= 0xF1,
	Oem22		= 0xF2,
	Oem23		= 0xF3,
	Oem24		= 0xF4,
	Oem25		= 0xF5,
	
	Attn		= 0xF6,
	CrSel		= 0xF7,
	ExSel		= 0xF8,
	EreaseEoF	= 0xF9,
	Play		= 0xFA,
	Zoom		= 0xFB,
	//NoName	= 0xFC, // Reserved
	A1			= 0xFD,
	OemClear	= 0xFE,

	// Later needed for locale based mappings
	//LeftBracket,
	//RightBracket,
	//Semicolon,
	//Comma,
	//Slash,
	//Backslash,
	//Tilde,
	//Equals,
	//Hyphen,
	//Apostrophe,

	// Alternative Names
	//Backspace	= Back,
	//Enter		= Return,
	//Snapshot	= Screen,

	//AltGr		= LAlt,
	//Menu		= Alt,
	//LMenu		= LAlt,
	//RMenu		= RAlt,

	Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, KeyCode code) {
	switch (code) {
		case KeyCode::Null:				    { stream << "Null";				    break; }
		case KeyCode::Cancel:				{ stream << "Cancel";				break; }
		case KeyCode::Back:					{ stream << "Back";					break; }
		case KeyCode::Tab:					{ stream << "Tab";					break; }
		case KeyCode::Clear:				{ stream << "Clear";				break; }
		case KeyCode::Return:				{ stream << "Return";				break; }
		case KeyCode::Shift:				{ stream << "Shift";				break; }
		case KeyCode::Control:				{ stream << "Control";				break; }
		case KeyCode::Alt:					{ stream << "Alt";					break; }
		case KeyCode::Pause:				{ stream << "Pause";				break; }
		case KeyCode::Capital:				{ stream << "Capital";				break; }
		case KeyCode::KanaMode:				{ stream << "KanaMode";				break; }
		//case KeyCode::HangulMode:			{ stream << "HangulMode";			break; }
		case KeyCode::ImeOn:				{ stream << "ImeOn";				break; }
		case KeyCode::JunjaMode:			{ stream << "JunjaMode";			break; }
		case KeyCode::FinalMode:			{ stream << "FinalMode";			break; }
		//case KeyCode::HanjaMode:			{ stream << "HanjaMode";			break; }
		case KeyCode::KanjiMode:			{ stream << "KanjiMode";			break; }
		case KeyCode::ImeOff:				{ stream << "ImeOff";				break; }
		case KeyCode::Escape:				{ stream << "Escape";				break; }
		case KeyCode::Convert:				{ stream << "Convert";				break; }
		case KeyCode::NonConvert:			{ stream << "NonConvert";			break; }
		case KeyCode::Accept:				{ stream << "Accept";				break; }
		case KeyCode::ModeChange:			{ stream << "ModeChange";			break; }
		case KeyCode::Space:				{ stream << "Space";				break; }
		case KeyCode::PageUp:				{ stream << "PageUp";				break; }
		case KeyCode::PageDown:				{ stream << "PageDown";				break; }
		case KeyCode::End:					{ stream << "End";					break; }
		case KeyCode::Home:					{ stream << "Home";					break; }
		case KeyCode::Left:					{ stream << "Left";					break; }
		case KeyCode::Up:					{ stream << "Up";					break; }
		case KeyCode::Right:				{ stream << "Right";				break; }
		case KeyCode::Down:					{ stream << "Down";					break; }
		case KeyCode::Select:				{ stream << "Select";				break; }
		case KeyCode::Print:				{ stream << "Print";				break; }
		case KeyCode::Execute:				{ stream << "Execute";				break; }
		case KeyCode::Screen:				{ stream << "Screen";				break; }
		case KeyCode::Insert:				{ stream << "Insert";				break; }
		case KeyCode::Delete:				{ stream << "Delete";				break; }
		case KeyCode::Help:					{ stream << "Help";					break; }
		case KeyCode::Key0:					{ stream << "Key0";					break; }
		case KeyCode::Key1:					{ stream << "Key1";					break; }
		case KeyCode::Key2:					{ stream << "Key2";					break; }
		case KeyCode::Key3:					{ stream << "Key3";					break; }
		case KeyCode::Key4:					{ stream << "Key4";					break; }
		case KeyCode::Key5:					{ stream << "Key5";					break; }
		case KeyCode::Key6:					{ stream << "Key6";					break; }
		case KeyCode::Key7:					{ stream << "Key7";					break; }
		case KeyCode::Key8:					{ stream << "Key8";					break; }
		case KeyCode::Key9:					{ stream << "Key9";					break; }
		case KeyCode::KeyA:					{ stream << "KeyA";					break; }
		case KeyCode::KeyB:					{ stream << "KeyB";					break; }
		case KeyCode::KeyC:					{ stream << "KeyC";					break; }
		case KeyCode::KeyD:					{ stream << "KeyD";					break; }
		case KeyCode::KeyE:					{ stream << "KeyE";					break; }
		case KeyCode::KeyF:					{ stream << "KeyF";					break; }
		case KeyCode::KeyG:					{ stream << "KeyG";					break; }
		case KeyCode::KeyH:					{ stream << "KeyH";					break; }
		case KeyCode::KeyI:					{ stream << "KeyI";					break; }
		case KeyCode::KeyJ:					{ stream << "KeyJ";					break; }
		case KeyCode::KeyK:					{ stream << "KeyK";					break; }
		case KeyCode::KeyL:					{ stream << "KeyL";					break; }
		case KeyCode::KeyM:					{ stream << "KeyM";					break; }
		case KeyCode::KeyN:					{ stream << "KeyN";					break; }
		case KeyCode::KeyO:					{ stream << "KeyO";					break; }
		case KeyCode::KeyP:					{ stream << "KeyP";					break; }
		case KeyCode::KeyQ:					{ stream << "KeyQ";					break; }
		case KeyCode::KeyR:					{ stream << "KeyR";					break; }
		case KeyCode::KeyS:					{ stream << "KeyS";					break; }
		case KeyCode::KeyT:					{ stream << "KeyT";					break; }
		case KeyCode::KeyU:					{ stream << "KeyU";					break; }
		case KeyCode::KeyV:					{ stream << "KeyV";					break; }
		case KeyCode::KeyW:					{ stream << "KeyW";					break; }
		case KeyCode::KeyX:					{ stream << "KeyX";					break; }
		case KeyCode::KeyY:					{ stream << "KeyY";					break; }
		case KeyCode::KeyZ:					{ stream << "KeyZ";					break; }
		case KeyCode::Super:				{ stream << "Super";				break; }
		case KeyCode::RightSuper:			{ stream << "RightSuper";			break; }
		case KeyCode::Apps:					{ stream << "Apps";					break; }
		case KeyCode::Sleep:				{ stream << "Sleep";				break; }
		case KeyCode::NumPad0:				{ stream << "NumPad0";				break; }
		case KeyCode::NumPad1:				{ stream << "NumPad1";				break; }
		case KeyCode::NumPad2:				{ stream << "NumPad2";				break; }
		case KeyCode::NumPad3:				{ stream << "NumPad3";				break; }
		case KeyCode::NumPad4:				{ stream << "NumPad4";				break; }
		case KeyCode::NumPad5:				{ stream << "NumPad5";				break; }
		case KeyCode::NumPad6:				{ stream << "NumPad6";				break; }
		case KeyCode::NumPad7:				{ stream << "NumPad7";				break; }
		case KeyCode::NumPad8:				{ stream << "NumPad8";				break; }
		case KeyCode::NumPad9:				{ stream << "NumPad9";				break; }
		case KeyCode::Multiply:				{ stream << "Multiply";				break; }
		case KeyCode::Add:					{ stream << "Add";					break; }
		case KeyCode::Seperator:			{ stream << "Seperator";			break; }
		case KeyCode::Subtract:				{ stream << "Subtract";				break; }
		case KeyCode::Decimal:				{ stream << "Decimal";				break; }
		case KeyCode::Divide:				{ stream << "Divide";				break; }
		case KeyCode::F1:					{ stream << "F1";					break; }
		case KeyCode::F2:					{ stream << "F2";					break; }
		case KeyCode::F3:					{ stream << "F3";					break; }
		case KeyCode::F4:					{ stream << "F4";					break; }
		case KeyCode::F5:					{ stream << "F5";					break; }
		case KeyCode::F6:					{ stream << "F6";					break; }
		case KeyCode::F7:					{ stream << "F7";					break; }
		case KeyCode::F8:					{ stream << "F8";					break; }
		case KeyCode::F9:					{ stream << "F9";					break; }
		case KeyCode::F10:					{ stream << "F10";					break; }
		case KeyCode::F11:					{ stream << "F11";					break; }
		case KeyCode::F12:					{ stream << "F12";					break; }
		case KeyCode::F13:					{ stream << "F13";					break; }
		case KeyCode::F14:					{ stream << "F14";					break; }
		case KeyCode::F15:					{ stream << "F15";					break; }
		case KeyCode::F16:					{ stream << "F16";					break; }
		case KeyCode::F17:					{ stream << "F17";					break; }
		case KeyCode::F18:					{ stream << "F18";					break; }
		case KeyCode::F19:					{ stream << "F19";					break; }
		case KeyCode::F20:					{ stream << "F20";					break; }
		case KeyCode::F21:					{ stream << "F21";					break; }
		case KeyCode::F22:					{ stream << "F22";					break; }
		case KeyCode::F23:					{ stream << "F23";					break; }
		case KeyCode::F24:					{ stream << "F24";					break; }
		case KeyCode::Numlock:				{ stream << "Numlock";				break; }
		case KeyCode::Scroll:				{ stream << "Scroll";				break; }
		case KeyCode::LShift:				{ stream << "LShift";				break; }
		case KeyCode::RShift:				{ stream << "RShift";				break; }
		case KeyCode::LControl:				{ stream << "LControl";				break; }
		case KeyCode::RControl:				{ stream << "RControl";				break; }
		case KeyCode::LAlt:					{ stream << "LAlt";					break; }
		case KeyCode::RAlt:					{ stream << "RAlt";					break; }
		case KeyCode::BrowserBack:			{ stream << "BrowserBack";			break; }
		case KeyCode::BrowserForward:		{ stream << "BrowserForward";		break; }
		case KeyCode::BrowserReload:		{ stream << "BrowserReload";		break; }
		case KeyCode::BrowserStop:			{ stream << "BrowserStop";			break; }
		case KeyCode::BrowserSearch:		{ stream << "BrowserSearch";		break; }
		case KeyCode::BrowserFavorites:		{ stream << "BrowserFavorites";		break; }
		case KeyCode::BrowserHome:			{ stream << "BrowserHome";			break; }
		case KeyCode::VolumeMute:			{ stream << "VolumeMute";			break; }
		case KeyCode::VolumeDown:			{ stream << "VolumeDown";			break; }
		case KeyCode::VolumeUp:				{ stream << "VolumeUp";				break; }
		case KeyCode::MediaNextTrack:		{ stream << "MediaNextTrack";		break; }
		case KeyCode::MediaPreviousTrack:	{ stream << "MediaPreviousTrack";	break; }
		case KeyCode::MediaStop:			{ stream << "MediaStop";			break; }
		case KeyCode::MediaPlayPause:		{ stream << "MediaPlayPause";		break; }
		case KeyCode::LaunchMail:			{ stream << "LaunchMail";			break; }
		case KeyCode::LaunchMediaSelect:	{ stream << "LaunchMediaSelect";	break; }
		case KeyCode::LaunchApp1:			{ stream << "LaunchApp1";			break; }
		case KeyCode::LaunchApp2:			{ stream << "LaunchApp2";			break; }
		case KeyCode::Oem1:					{ stream << "Oem1";					break; }
		case KeyCode::Plus:					{ stream << "Plus";					break; }
		case KeyCode::Comma:				{ stream << "Comma";				break; }
		case KeyCode::Minus:				{ stream << "Minus";				break; }
		case KeyCode::Period:				{ stream << "Period";				break; }
		case KeyCode::Oem2:					{ stream << "Oem2";					break; }
		case KeyCode::Oem3:					{ stream << "Oem3";					break; }
		case KeyCode::Oem4:					{ stream << "Oem4";					break; }
		case KeyCode::Oem5:					{ stream << "Oem5";					break; }
		case KeyCode::Oem6:					{ stream << "Oem6";					break; }
		case KeyCode::Oem7:					{ stream << "Oem7";					break; }
		case KeyCode::Oem8:					{ stream << "Oem8";					break; }
		case KeyCode::Oem9:					{ stream << "Oem9";					break; }
		case KeyCode::Oem102:				{ stream << "Oem102";				break; }
		case KeyCode::Oem10:				{ stream << "Oem10";				break; }
		case KeyCode::Oem11:				{ stream << "Oem11";				break; }
		case KeyCode::Process:				{ stream << "Process";				break; }
		case KeyCode::Oem12:				{ stream << "Oem12";				break; }
		case KeyCode::Oem13:				{ stream << "Oem13";				break; }
		case KeyCode::Oem14:				{ stream << "Oem14";				break; }
		case KeyCode::Oem15:				{ stream << "Oem15";				break; }
		case KeyCode::Oem16:				{ stream << "Oem16";				break; }
		case KeyCode::Oem17:				{ stream << "Oem17";				break; }
		case KeyCode::Oem18:				{ stream << "Oem18";				break; }
		case KeyCode::Oem19:				{ stream << "Oem19";				break; }
		case KeyCode::Oem20:				{ stream << "Oem20";				break; }
		case KeyCode::Oem21:				{ stream << "Oem21";				break; }
		case KeyCode::Oem22:				{ stream << "Oem22";				break; }
		case KeyCode::Oem23:				{ stream << "Oem23";				break; }
		case KeyCode::Oem24:				{ stream << "Oem24";				break; }
		case KeyCode::Oem25:				{ stream << "Oem25";				break; }
		case KeyCode::Attn:					{ stream << "Attn";					break; }
		case KeyCode::CrSel:				{ stream << "CrSel";				break; }
		case KeyCode::ExSel:				{ stream << "ExSel";				break; }
		case KeyCode::EreaseEoF:			{ stream << "EreaseEoF";			break; }
		case KeyCode::Play:					{ stream << "Play";					break; }
		case KeyCode::Zoom:					{ stream << "Zoom";					break; }
		case KeyCode::A1:					{ stream << "A1";					break; }
		case KeyCode::OemClear:				{ stream << "OemClear";				break; }
		case KeyCode::Undefined:			{ stream << "-";					break; }
	}
	return stream;
}

///
/// @brief Key States
///
enum class KeyState {
	Null		= 0x00,
	Press		= 0x01,
	Hold		= 0x02,
	Release		= 0x03,
	Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, KeyState state) {
	switch (state) {
		case KeyState::Null:		{ stream << "Null";			break; }
		case KeyState::Press:		{ stream << "Press";		break; }
		case KeyState::Hold:		{ stream << "Hold";			break; }
		case KeyState::Release:		{ stream << "Release";		break; }
		case KeyState::Undefined:	{ stream << "-";			break; }
	}
	return stream;
}

}
