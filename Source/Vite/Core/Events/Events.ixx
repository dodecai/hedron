export module Vite.Event;

export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;
import Vite.Event.Emitter;

import Vite.Base;

// ToDo: Move to Window and GFXContext
export namespace Hedron {

// Context Action
enum class ContextAction {
    Null,
    Buffer,
    Draw,
    Reload,
    Resize,
    Switch,
    Undefined,
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

// Window Action
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

}

export namespace Hedron {

///
/// Enumerations
///

// Category
enum class EventCategory {
	Default,
	Application,
    User,
	Undefined,
};

inline std::ostream &operator<<(std::ostream &stream, EventCategory category) {
	switch (category) {
		case EventCategory::Default:		{ stream << "Default";		break; }
		case EventCategory::Application:	{ stream << "Application";	break; }
        case EventCategory::User:		    { stream << "User";		    break; }
		case EventCategory::Undefined:		{ stream << "-";			break; }
	}
	return stream;
}

// Priority
enum class EventPriority {
    Realtime    = 0x0,
    High        = 0x1,
    Default     = 0x2,
    Low         = 0x3,
    Undefined   = 0xF,
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
    Default,

    // Application
    Context,
    Device,
	Power,
    State,
    Window,

    // User
    Controller,
    Keyboard,
    Mouse,
    Touch,

	Undefined,
};

inline std::ostream &operator<<(std::ostream &stream, EventSource source) {
    switch (source) {
        // Default
        case EventSource::Default:	    { stream << "Default";		break; }
        
        // Application
        case EventSource::Device:		{ stream << "Device";		break; }
        case EventSource::Power:		{ stream << "Power";		break; }
        case EventSource::State:		{ stream << "State";		break; }
        case EventSource::Window:		{ stream << "Window";		break; }
        
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
/// Event Data Interface
///
struct EventData {
    bool Handled = false;

    // Specification
    EventCategory Category = EventCategory::Undefined;
    EventPriority Priority = EventPriority::Undefined;
    EventSource Source = EventSource::Undefined;
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

///
/// Event Data
///

// Modifier States
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

// Application
struct WindowEventData: public EventData {
    // Specification
    EventCategory Category = EventCategory::Application;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Window;

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
    EventCategory Category = EventCategory::Application;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Context;

    // Data
    ContextAction Action = ContextAction::Undefined;
};

// User
struct ControllerEventData: public EventData {
    // Specification
    EventCategory Category = EventCategory::User;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Controller;

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
    EventCategory Category = EventCategory::User;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Keyboard;

    // Data
    KeyboardAction Action = KeyboardAction::Undefined;
    char Character = 0;
    KeyCode Key = KeyCode::Undefined;
    KeyState State = KeyState::Undefined;
    ModifierState Modifier;

};

struct MouseEventData: public EventData {
    // Specification
    EventCategory Category = EventCategory::User;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Mouse;

    // Data
    MouseAction Action = MouseAction::Undefined;
    MouseButton Button = MouseButton::Undefined;
    MouseButtonState State = MouseButtonState::Undefined;
    ModifierState Modifier;

    float DeltaTime = 0.0f;
    float DeltaWheelX = 0.0f;
    float DeltaWheelY = 0.0f;

    int32 X = 0;
    int32 Y = 0;
    int32 DeltaX = 0;
    int32 DeltaY = 0;
    int32 LastX = 0;
    int32 LastY = 0;
};

struct TouchEventData: public EventData {
    // Specification
    EventCategory Category = EventCategory::User;
    EventPriority Priority = EventPriority::Default;
    EventSource Source = EventSource::Touch;

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


///
/// @brief Event Handler Interface
///
class EventHandler {
public:
    // Default
    EventHandler() = default;
    virtual ~EventHandler() = default;
    static Scope<EventHandler> Create();

    // Methods
    virtual bool Callback(void *event) = 0;
    virtual void Update() = 0;

    // Event Emitter
    EventEmitter Emitter;
    //struct EventEmitter: public Emitter<EventEmitter, std::allocator<void>> {} Emitter;
};

}
