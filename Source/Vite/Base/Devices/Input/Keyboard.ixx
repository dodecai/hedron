export module Vite.Device.Input.Keyboard;

import Vite.Extension;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Keyboard Key Actions [Raw|Input]
///
enum class KeyAction {
    Undefined,
    Input,
	Raw,
};

// Key Action Names
template<>
struct NamedEnumTraits<KeyAction> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Input",
        "Raw",
        "Repeat",
    };
};


///
/// @brief Key Codes
/// @note We use the Windows Virtual Key Codes, cause they can be mapped to characters.
/// @source: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
///
enum class KeyCode {
    Undefined 	    = 0x00,

	LeftButton      = 0x01,
    RightButton     = 0x02,
	Cancel		    = 0x03,
	MiddleButton    = 0x04,
    ExtraButton1    = 0x05,
    ExtraButton2    = 0x06,
	Reserved07      = 0x07,

	Back		    = 0x08,
	Tab			    = 0x09,
	LineFeed        = 0x0A,
    Reserved0B      = 0x0B,

	Clear		    = 0x0C,
	Return		    = 0x0D,
	Unassigned0E    = 0x0E,
    Unassigned0F    = 0x0F,

	Shift		    = 0x10,
	Control		    = 0x11,
	Alt			    = 0x12,
	Pause		    = 0x13,
	Capital		    = 0x14,
	
	Kana        	= 0x15,
	ImeOn		    = 0x16,
	Junja	        = 0x17,
	Final	        = 0x18,
	Kanji   	    = 0x19,
	ImeOff		    = 0x1A,
	
	Escape		    = 0x1B,
	
	IMEConvert	    = 0x1C,
	IMENonConvert	= 0x1D,
	IMEAccept		= 0x1E,
	IMEModeChange	= 0x1F,

	Space		    = 0x20,
	PageUp		    = 0x21,
	PageDown	    = 0x22,
	End			    = 0x23,
	Home		    = 0x24,

	Left		    = 0x25,
	Up			    = 0x26,
	Right		    = 0x27,
	Down		    = 0x28,

	Select		    = 0x29,
	Print		    = 0x2A,
	Execute		    = 0x2B,
	Screen		    = 0x2C,
	Insert		    = 0x2D,
	Delete		    = 0x2E,
	Help		    = 0x2F,

	D0  		    = 0x30,
	D1  		    = 0x31,
	D2  		    = 0x32,
	D3  		    = 0x33,
	D4  		    = 0x34,
	D5  		    = 0x35,
	D6  		    = 0x36,
	D7  		    = 0x37,
	D8  		    = 0x38,
	D9  		    = 0x39,
	
    Undefined3A     = 0x3A,
    Undefined3B     = 0x3B,
    Undefined3C     = 0x3C,
    Undefined3D     = 0x3D,
    Undefined3E     = 0x3E,
    Undefined3F     = 0x3F,
    Undefined40     = 0x40,
    
	A		        = 0x41,
	B		        = 0x42,
	C		        = 0x43,
	D		        = 0x44,
	E		        = 0x45,
	F		        = 0x46,
	G		        = 0x47,
	H		        = 0x48,
	I		        = 0x49,
	J		        = 0x4A,
	K		        = 0x4B,
	L		        = 0x4C,
	M		        = 0x4D,
	N		        = 0x4E,
	O		        = 0x4F,
	P		        = 0x50,
	Q		        = 0x51,
	R		        = 0x52,
	S		        = 0x53,
	T		        = 0x54,
	U		        = 0x55,
	V		        = 0x56,
	W		        = 0x57,
	X		        = 0x58,
	Y		        = 0x59,
	Z		        = 0x5A,
	
	LeftSuper       = 0x5B,
	RightSuper	    = 0x5C,
	Apps		    = 0x5D,
	Reserved5E	    = 0x5E,
	Sleep		    = 0x5F,

	NumPad0		    = 0x60,
	NumPad1		    = 0x61,
	NumPad2		    = 0x62,
	NumPad3		    = 0x63,
	NumPad4		    = 0x64,
	NumPad5		    = 0x65,
	NumPad6		    = 0x66,
	NumPad7		    = 0x67,
	NumPad8		    = 0x68,
	NumPad9		    = 0x69,
	Multiply	    = 0x6A,
	Add			    = 0x6B,
	Seperator	    = 0x6C,
	Subtract	    = 0x6D,
	Decimal		    = 0x6E,
	Divide		    = 0x6F,

	F1			    = 0x70,
	F2			    = 0x71,
	F3			    = 0x72,
	F4			    = 0x73,
	F5			    = 0x74,
	F6			    = 0x75,
	F7			    = 0x76,
	F8			    = 0x77,
	F9			    = 0x78,
	F10			    = 0x79,
	F11			    = 0x7A,
	F12			    = 0x7B,
	F13			    = 0x7C,
	F14			    = 0x7D,
	F15			    = 0x7E,
	F16			    = 0x7F,
	F17			    = 0x80,
	F18			    = 0x81,
	F19			    = 0x82,
	F20			    = 0x83,
	F21			    = 0x84,
	F22			    = 0x85,
	F23			    = 0x86,
	F24			    = 0x87,
    Reserved88      = 0x88,
    Reserved89      = 0x89,
    Reserved8A      = 0x8A,
    Reserved8B      = 0x8B,
    Reserved8C      = 0x8C,
    Reserved8D      = 0x8D,
    Reserved8E      = 0x8E,
    Reserved8F      = 0x8F,

	NumLock		    = 0x90,
	Scroll		    = 0x91,

    OemSpecific92   = 0x92,
    OemSpecific93   = 0x93,
    OemSpecific94   = 0x94,
    OemSpecific95   = 0x95,
    OemSpecific96   = 0x96,

    Unassigned97    = 0x97,
    Unassigned98    = 0x98,
    Unassigned99    = 0x99,
    Unassigned9A    = 0x9A,
    Unassigned9B    = 0x9B,
    Unassigned9C    = 0x9C,
    Unassigned9D    = 0x9D,
    Unassigned9E    = 0x9E,
    Unassigned9F    = 0x9F,

	LeftShift	    = 0xA0,
	RightShift	    = 0xA1,
	LeftControl	    = 0xA2,
	RightControl    = 0xA3,
	LeftAlt		    = 0xA4,
	RightAlt	    = 0xA5,
	
	BrowserBack			= 0xA6,
	BrowserForward		= 0xA7,
	BrowserRefresh		= 0xA8,
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
	SelectMedia     	= 0xB5,
	LaunchApp1			= 0xB6,
	LaunchApp2			= 0xB7,
    ReservedB8          = 0xB8,
    ReservedB9          = 0xB9,

	Oem1    	    = 0xBA,
	Plus		    = 0xBB,
	Comma		    = 0xBC,
	Minus		    = 0xBD,
	Period		    = 0xBE,
	Oem2    	    = 0xBF,
	Oem3		    = 0xC0,
    ReservedC1      = 0xC1,
    ReservedC2      = 0xC2,
    ReservedC3      = 0xC3,
    ReservedC4      = 0xC4,
    ReservedC5      = 0xC5,
    ReservedC6      = 0xC6,
    ReservedC7      = 0xC7,
    ReservedC8      = 0xC8,
    ReservedC9      = 0xC9,
    ReservedCA      = 0xCA,
    ReservedCB      = 0xCB,
    ReservedCC      = 0xCC,
    ReservedCD      = 0xCD,
    ReservedCE      = 0xCE,
    ReservedCF      = 0xCF,
    ReservedD0      = 0xD0,
    ReservedD1      = 0xD1,
    ReservedD2      = 0xD2,
    ReservedD3      = 0xD3,
    ReservedD4      = 0xD4,
    ReservedD5      = 0xD5,
    ReservedD6      = 0xD6,
    ReservedD7      = 0xD7,
    ReservedD8      = 0xD8,
    ReservedD9      = 0xD9,
    ReservedDA      = 0xDA,
	Oem4            = 0xDB,
	Oem5		    = 0xDC,
	Oem6            = 0xDD,
	Oem7		    = 0xDE,
	Oem8		    = 0xDF,
    ReservedE0      = 0xE0,
	OemSpecificE1	= 0xE1,
    Oem102         	= 0xE2,
    OemSpecificE3	= 0xE3,
    OemSpecificE4	= 0xE4,
	Process		    = 0xE5,
    OemSpecificE6	= 0xE6,
    Packet		    = 0xE7, // Used to pass Unicode characters as if they were keystrokes.
    UnassignedE8	= 0xE8,
    OemSpecificE9	= 0xE9,
    OemSpecificEA	= 0xEA,
    OemSpecificEB	= 0xEB,
    OemSpecificEC	= 0xEC,
    OemSpecificED	= 0xED,
    OemSpecificEE	= 0xEE,
    OemSpecificEF	= 0xEF,
    OemSpecificF0	= 0xF0,
    OemSpecificF1	= 0xF1,
    OemSpecificF2	= 0xF2,
    OemSpecificF3	= 0xF3,
    OemSpecificF4	= 0xF4,
    OemSpecificF5	= 0xF5,
	
	Attn		    = 0xF6,
	CrSel		    = 0xF7,
	ExSel		    = 0xF8,
	EraseEoF	    = 0xF9,
	Play		    = 0xFA,
	Zoom		    = 0xFB,
	NoName	        = 0xFC, // Reserved
    ReservedFD      = 0xFD,
	OemClear        = 0xFE,
	Unknown    	    = 0xFF,

    // Alternative Names
    Backspace	    = Back,
    Enter		    = Return,
    Menu            = Alt,
    CapsLock	    = Capital,

    Hunguel		    = Kana,
    Hungul          = Kana,
    Hanja		    = Kanji,

    Prior		    = PageUp,
    Next		    = PageDown,

    Snapshot	    = Screen,

    LeftWindows	    = LeftSuper,
    RightWindows    = RightSuper,
    LeftMenu	    = LeftAlt,
    RightMenu	    = RightAlt,
};

// Key Code Names
template<>
struct NamedEnumTraits<KeyCode> {
    static constexpr string_view Names[] = {
        "Undefined",

        "Left Button",
        "Right Button",
        "Cancel",
        "Middle Button",
        "Extra Button 1",
        "Extra Button 2",
        "Reserved 0x07",

        "Back",
        "Tab",
        "Line Feed",
        "Reserved 0x0B",

        "Clear",
        "Return",
        "Unassigned 0x0E",
        "Unassigned 0x0F",

        "Shift",
        "Control",
        "Alt",
        "Pause",
        "Capital",

        "Kana",
        "ImeOn",
        "Junja",
        "Final",
        "Kanji",
        "ImeOff",

        "Escape",

        "IME Convert",
        "IME Non Convert",
        "IME Accept",
        "IME Mode Change",

        "Space",
        "Page Up",
        "Page Down",
        "End",
        "Home",

        "Left",
        "Up",
        "Right",
        "Down",

        "Select",
        "Print",
        "Execute",
        "Screen",
        "Insert",
        "Delete",
        "Help",

        "D0",
        "D1",
        "D2",
        "D3",
        "D4",
        "D5",
        "D6",
        "D7",
        "D8",
        "D9",

        "Undefined 0x3A",
        "Undefined 0x3B",
        "Undefined 0x3C",
        "Undefined 0x3D",
        "Undefined 0x3E",
        "Undefined 0x3F",
        "Undefined 0x40",

        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",

        "Left Super",
        "Right Super",
        "Apps",
        "Reserved 0x5E",
        "Sleep",

        "NumPad0",
        "NumPad1",
        "NumPad2",
        "NumPad3",
        "NumPad4",
        "NumPad5",
        "NumPad6",
        "NumPad7",
        "NumPad8",
        "NumPad9",
        "Multiply",
        "Add",
        "Separator",
        "Subtract",
        "Decimal",
        "Divide",

        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "F13",
        "F14",
        "F15",
        "F16",
        "F17",
        "F18",
        "F19",
        "F20",
        "F21",
        "F22",
        "F23",
        "F24",
        "Reserved 0x88",
        "Reserved 0x89",
        "Reserved 0x8A",
        "Reserved 0x8B",
        "Reserved 0x8C",
        "Reserved 0x8D",
        "Reserved 0x8E",
        "Reserved 0x8F",

        "NumLock",
        "Scroll",

        "OemSpecific 0x92",
        "OemSpecific 0x93",
        "OemSpecific 0x94",
        "OemSpecific 0x95",
        "OemSpecific 0x96",

        "Unassigned 0x97",
        "Unassigned 0x98",
        "Unassigned 0x99",
        "Unassigned 0x9A",
        "Unassigned 0x9B",
        "Unassigned 0x9C",
        "Unassigned 0x9D",
        "Unassigned 0x9E",
        "Unassigned 0x9F",

        "Left Shift",
        "Right Shift",
        "Left Control",
        "Right Control",
        "Left Alt",
        "Right Alt",

        "Browser Back",
        "Browser Forward",
        "Browser Reload",
        "Browser Stop",
        "Browser Search",
        "Browser Favorites",
        "Browser Home",
        "Volume Mute",
        "Volume Down",
        "Volume Up",
        "Media Next Track",
        "Media Previous Track",
        "Media Stop",
        "Media Play/Pause",
        "Launch Mail",
        "Select Media",
        "Launch App 1",
        "Launch App 2",
        "Reserved 0xB8",
        "Reserved 0xB9",

        "Oem1",
        "Plus",
        "Comma",
        "Minus",
        "Period",
        "Oem2",
        "Oem3",
        "Reserved 0xC1",
        "Reserved 0xC2",
        "Reserved 0xC3",
        "Reserved 0xC4",
        "Reserved 0xC5",
        "Reserved 0xC6",
        "Reserved 0xC7",
        "Reserved 0xC8",
        "Reserved 0xC9",
        "Reserved 0xCA",
        "Reserved 0xCB",
        "Reserved 0xCC",
        "Reserved 0xCD",
        "Reserved 0xCE",
        "Reserved 0xCF",
        "Reserved 0xD0",
        "Reserved 0xD1",
        "Reserved 0xD2",
        "Reserved 0xD3",
        "Reserved 0xD4",
        "Reserved 0xD5",
        "Reserved 0xD6",
        "Reserved 0xD7",
        "Reserved 0xD8",
        "Reserved 0xD9",
        "Reserved 0xDA",
        "Oem4",
        "Oem5",
        "Oem6",
        "Oem7",
        "Oem8",
        "Reserved 0xE0",
        "Oem Specific 0xE1",
        "Oem Specific 0xE2",
        "Oem 102",
        "Oem Specific 0xE4",
        "Process",
        "OemSpecific0xE6",
        "Packet",
        "Unassigned 0xE8",
        "Oem Specific 0xE9",
        "Oem Specific 0xEA",
        "Oem Specific 0xEB",
        "Oem Specific 0xEC",
        "Oem Specific 0xED",
        "Oem Specific 0xEE",
        "Oem Specific 0xEF",
        "Oem Specific 0xF0",
        "Oem Specific 0xF1",
        "Oem Specific 0xF2",
        "Oem Specific 0xF3",
        "Oem Specific 0xF4",
        "Oem Specific 0xF5",

        "Attn",
        "CrSel",
        "ExSel",
        "Erase EoF",
        "Play",
        "Zoom",
        "NoName",
        "Reserved 0xFD",
        "Oem Clear",

        "Unknown",
    };
};


///
///  @brief Keyboard Key Modifiers [Alt|Control|Shift|Super]
///
enum class KeyModifier {
    None    = BitMask(0),
    Alt     = BitMask(1),
    Control = BitMask(2),
    Shift   = BitMask(3),
    Super   = BitMask(4),
};

// Enable BitMask Operators
template<> struct EnableBitMaskOperators<KeyModifier> {
    static const bool enable = true;
};

// Key Modifier Names
template<>
struct NamedEnumTraits<KeyModifier> {
    static constexpr string_view Names[] = {
        "None",
        "Alt",
        "Control",
        "Shift",
        "Super",
    };
};


///
/// @brief Keyboard Key States
///
enum class KeyState {
    Undefined,
    Press,
	Repeat,
    Release,
};

// Key State Names
template<>
struct NamedEnumTraits<KeyState> {
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
struct EnableNamedEnumFormatter<KeyAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<KeyCode> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<KeyModifier> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumFormatter<KeyState> {
    static const bool Enable = true;
};

/// Stream
template<>
struct EnableNamedEnumStreamOperators<KeyAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<KeyCode> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<KeyModifier> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<KeyState> {
    static const bool Enable = true;
};

}
