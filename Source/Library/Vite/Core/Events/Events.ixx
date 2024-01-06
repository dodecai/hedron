export module Vite.Event;

export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;
export import Vite.Event.Emitter;

import Vite.Base;

///
/// Event Data
/// @todo: Move to appropriate module
///

export namespace Hedron {

///
/// Enumerations
///

// Category
enum class EventCategory {
	Default		= 0x00,
	System		= 0x10,
	Application	= 0xA0,
	Library		= 0xB0,
    User        = 0xC0,
	Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, EventCategory category) {
	switch (category) {
		case EventCategory::Default:		{ stream << "Default";		break; }
		case EventCategory::System:			{ stream << "System";		break; }
		case EventCategory::Application:	{ stream << "Application";	break; }
		case EventCategory::Library:		{ stream << "Library";		break; }
        case EventCategory::User:		    { stream << "User";		    break; }
		case EventCategory::Undefined:		{ stream << "-";			break; }
	}
	return stream;
}

// Priority
enum class EventPriority {
    Realtime    = 0x00,
    High        = 0x01,
    Default     = 0x02,
    Low         = 0x03,
    Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, EventPriority priority) {
    switch (priority) {
        case EventPriority::Realtime:		{ stream << "Realtime";	    break; }
        case EventPriority::High:			{ stream << "High";		    break; }
        case EventPriority::Default:		{ stream << "Default";		break; }
        case EventPriority::Low:			{ stream << "Low";			break; }
        default:                            { stream << "-";            break; }
    }
    return stream;
}

// Source
enum class EventSource {
    // Default
    Default		= 0x00,

    // System
	Device		= 0x11,
	Power		= 0x12,
    State		= 0x13,

    // Application
    Window		= 0xA1,
    Context		= 0xA2,

    // Library
    Core        = 0xB1,
    Graphics    = 0xB2,
    Interface   = 0xB3,

    // User
    Controller	= 0xC1,
    Keyboard	= 0xC2,
    Mouse		= 0xC3,
    Touch		= 0xC4,

    // ~
	Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, EventSource source) {
    switch (source) {
        // Default
        case EventSource::Default:	    { stream << "Default";		break; }
        
        // System
        case EventSource::Device:		{ stream << "Device";		break; }
        case EventSource::Power:		{ stream << "Power";		break; }
        case EventSource::State:		{ stream << "State";		break; }

        // Application
        case EventSource::Window:		{ stream << "Window";		break; }
        case EventSource::Context:	    { stream << "Context";		break; }
        
        // Library
        case EventSource::Core:	        { stream << "Core";		    break; }
        case EventSource::Graphics:		{ stream << "Graphics";		break; }
        case EventSource::Interface:	{ stream << "Interface";	break; }
        
        // User
        case EventSource::Controller:   { stream << "Controller";	break; }
        case EventSource::Keyboard:	    { stream << "Keyboard";		break; }
        case EventSource::Mouse:		{ stream << "Mouse";		break; }
        case EventSource::Touch:		{ stream << "Touch";		break; }
        
        // ~
        default:                        { stream << "-";            break; }
    }
    return stream;
}

///
/// Helpers
///

inline bool IsEventCategory(EventSource source, EventCategory category) {
    if (GetEnumType(source) & 1 << GetEnumType(category)) { return true; }
    return false;
}

///
/// Actions
///
enum class WindowAction {
    Null		= 0x00,

    Create		= 0x01,
    Destroy		= 0x02,

    Activate	= 0x10,
    Focus		= 0x11,
    Maximize	= 0x12,
    Minimize	= 0x13,
    Show		= 0x14,

    Draw		= 0x20,
    DpiUpdate	= 0x21,
    Move		= 0x22,
    Resize		= 0x23,
    Restore		= 0x24,

    DragNDrop	= 0x31,

    Undefined	= 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, WindowAction action) {
    switch (action) {
        case WindowAction::Null:		{ stream << "Null";	    	break; }

        case WindowAction::Create:		{ stream << "Create";		break; }
        case WindowAction::Destroy:		{ stream << "Destroy";		break; }

        case WindowAction::Activate:	{ stream << "Activate";		break; }
        case WindowAction::Focus:		{ stream << "Focus";		break; }
        case WindowAction::Maximize:	{ stream << "Maximize";		break; }
        case WindowAction::Minimize:	{ stream << "Minimize";		break; }
        case WindowAction::Show:		{ stream << "Show";			break; }

        case WindowAction::Draw:		{ stream << "Draw";			break; }
        case WindowAction::DpiUpdate:	{ stream << "DpiUpdate";	break; }
        case WindowAction::Move:		{ stream << "Move";			break; }
        case WindowAction::Resize:		{ stream << "Resize";		break; }
        case WindowAction::Restore:		{ stream << "Restore";		break; }

        case WindowAction::DragNDrop:	{ stream << "DragNDrop";	break; }

        case WindowAction::Undefined:	{ stream << "-";			break; }
    }
    return stream;
}

enum class ContextAction {
    Null		= 0x00,
    Buffer		= 0x01,
    Draw		= 0x02,
    Reload		= 0x03,
    Resize		= 0x04,
    Switch		= 0x05,
    Undefined   = 0xFF,
};

inline std::ostream &operator<<(std::ostream &stream, ContextAction action) {
    switch (action) {
        case ContextAction::Null:	    { stream << "Null";		    break; }
        case ContextAction::Buffer:		{ stream << "Buffer";		break; }
        case ContextAction::Draw:		{ stream << "Draw";		    break; }
        case ContextAction::Reload:		{ stream << "Reload";		break; }
        case ContextAction::Resize:		{ stream << "Resize";		break; }
        case ContextAction::Switch:		{ stream << "Switch";		break; }
        case ContextAction::Undefined:	{ stream << "-";			break; }
    }
    return stream;
}

///
/// States
///
struct ModifierState {
	bool Alt        = false;
	bool Control    = false;
	bool Shift      = false;
	bool Super      = false;
};

inline std::ostream &operator<<(std::ostream &stream, ModifierState state) {
	stream	<< "Alt:"		<< state.Alt		<< "|"
		    << "Control:"	<< state.Control	<< "|"
		    << "Shift:"		<< state.Shift		<< "|"
		    << "Super:"		<< state.Super;
	return stream;
}

enum class ModifierStateE: uint16 {
	Ctrl	    = BitMask(0),	Control		        = Ctrl,
	Shift	    = BitMask(1),
	Alt		    = BitMask(2),	Alternate	        = Alt,		Option	= Alt,
	AltGr	    = BitMask(3),	AlternateGraphic	= AltGr,
	Meta	    = BitMask(4),
	Super	    = BitMask(5),	Windows		        = Super,	Command	= Super,
	Fn		    = BitMask(6),	Function	        = Fn,

	MouseLeft	= BitMask(7),
	MouseMiddle	= BitMask(8),
	MouseRight  = BitMask(9),
	MouseX1		= BitMask(10),
	MouseX2		= BitMask(11),
};

struct ModifierStateMask {
	uint16 Mask = 0;
};

inline std::ostream &operator<<(std::ostream &stream, ModifierStateMask state) {
	//stream	<< "Alt:"		<< (state.Mask & (uint16_t)ModifierStateE::Alt)		<< "|"
	//		<< "Ctrl:"		<< (state.Mask & (uint16_t)ModifierStateE::Ctrl)	<< "|"
	//		<< "Shift:"		<< (state.Mask & (uint16_t)ModifierStateE::Shift)	<< "|"
	//		<< "Super:"		<< (state.Mask & (uint16_t)ModifierStateE::Super)	;
	stream << std::bitset<8>(state.Mask);
	return stream;
}

///
/// Data
///

// Interface
struct EventData {
    bool Handled = false;

    // Specification
    EventCategory Category = EventCategory::Undefined;
    EventPriority Priority = EventPriority::Undefined;
    EventSource Source = EventSource::Undefined;
};

// Library
struct WindowEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::Application;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Window;

    // Data
    WindowAction Action = WindowAction::Undefined;

    bool Active = false;
    bool Focus = false;
    bool Visible = true;

    float DpiValue = 0.0f;
    uint32 Height = 0;
    uint32 Width = 0;

    int32 DeltaX = 0;
    int32 DeltaY = 0;
    int32 LastX = 0;
    int32 LastY = 0;
    int32 X = 0;
    int32 Y = 0;
};

struct ContextEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::Application;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Context;

    // Data
    ContextAction Action = ContextAction::Undefined;
};

// User
struct ControllerEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::User;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Controller;

    // Data
	ControllerAction Action = ControllerAction::Undefined;
	ControllerButton Button = ControllerButton::Undefined;
    ControllerButtonState State = ControllerButtonState::Undefined;

	bool Connected = false;
	string ID = "";
	size Index = 0;
	string Mapping = "";

	int32 DeltaX = 0;
	int32 DeltaY = 0;
	int32 LastX = 0;
	int32 LastY = 0;
	int32 X = 0;
	int32 Y = 0;
};

struct KeyboardEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::User;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Keyboard;

    // Data
	KeyboardAction Action = KeyboardAction::Undefined;
	char Character = 0;
	KeyCode Key = KeyCode::Undefined;
	KeyState State = KeyState::Undefined;
	ModifierState Modifier;

};

struct MouseEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::User;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Mouse;

    // Data
	MouseAction Action = MouseAction::Undefined;
	MouseButton Button = MouseButton::Undefined;
	MouseButtonState State = MouseButtonState::Undefined;
	ModifierState Modifier;

	float DeltaTime = 0.0f;
	float DeltaWheelX = 0.0f;
	float DeltaWheelY = 0.0f;
	
	int32 DeltaX = 0;
	int32 DeltaY = 0;
	int32 LastX = 0;
	int32 LastY = 0;
	int32 X = 0;
	int32 Y = 0;
};

struct TouchEventData: public EventData {
    // Specification
    EventCategory Category  = EventCategory::User;
    EventPriority Priority  = EventPriority::Default;
    EventSource Source      = EventSource::Touch;

    // Data
	TouchAction Action = TouchAction::Undefined;
	TouchStyle Style = TouchStyle::Undefined;

	size_t ID = {};
	float DeltaTime = 0.0f;
	
	int32 DeltaX = 0;
	int32 DeltaY = 0;
	int32 LastX = 0;
	int32 LastY = 0;
	int32 X = 0;
	int32 Y = 0;
};

}

export namespace Hedron {

///
/// @brief Event Listener
///
class EventListener {
public:
    // Default
    EventListener() = default;
    virtual ~EventListener() = default;
    static Scope<EventListener> Create();

    // Methods
    virtual bool Callback(void *event) = 0;
    virtual void Update() = 0;

    // Event Emitter
    //struct EventEmitter: public Emitter<EventEmitter> {} Emitter;
};

///
/// Event Interface
///
struct Event {
    // Constructors and Deconstructor
    Event() = delete;
    Event(std::shared_ptr<EventData> &&data): Data(std::move(data)) {};
    virtual ~Event() = default;

    // Conversions
    template<typename T>
    T *As() {
        return reinterpret_cast<T *>(this);
    }

    // Properties
    std::shared_ptr<EventData> Data = nullptr;
    bool Handled = false;
};

}
