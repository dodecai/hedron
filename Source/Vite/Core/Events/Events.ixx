export module Vite.Event;

export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;
import Vite.Event.Emitter;
import Vite.Math.Geometry;
import Vite.System.Window;

import Vite.Base;

export namespace Hedron {

///
/// Event Properties
///

///
/// @brief Event Category [App|Input]
///
enum class EventCategory {
    Undefined,
    App,
    Input
};

///
/// @brief Event Priority [Low|Normal|High|Realtime]
///
enum class EventPriority {
    Undefined,
    Low,
    Normal,
    High,
    Realtime,
};

///
/// @brief App Event Sources: App [Device|State|Window], Input [Controller|Keyboard|Mouse|Touch]
///
enum class EventSource {
    Undefined,

    // App
    Device,
    State,
    Window,

    // Input
    Controller,
    Keyboard,
    Mouse,
    Touch,
};


///
/// Event Data
///

///
/// @brief Base Event
///
struct BaseEvent {
    mutable bool Handled = false;
    mutable EventCategory Category {};
    mutable EventPriority Priority {};
};

///
/// @brief Window Event
///
struct WindowEvent: public BaseEvent {
    // Data
    WindowAction Action {};
    WindowState State {};

    float DpiValue {};
    Position2D DeltaPosition {};
    Size2D DeltaSize {};
    Position2D LastPosition {};
    Size2D LastSize {};
    Position2D Position {};
    Size2D Size {};

    // Specification
    const EventSource Source = EventSource::Window;
};

///
/// @brief Controller Event
///
struct ControllerEvent: public BaseEvent {
    // Data
    ControllerAction Action {};
    ControllerButton Button {};
    DeltaTime DeltaTime {};
    ControllerButtonState State {};

    string ID = "";
    bool Connected = false;

    // Specification
    const EventSource Source = EventSource::Controller;
};

///
/// @brief Keyboard Event
///
struct KeyboardEvent: public BaseEvent {
    // Data
    KeyAction Action {};
    wchar_t Character {};
    DeltaTime DeltaTime {};
    KeyCode Key {};
    KeyModifier Modifiers;
    uint16 Repeats {};
    KeyState State {};

    // Specification
    const EventSource Source = EventSource::Keyboard;
};

///
/// @brief Mouse Event
///
struct MouseEvent: public BaseEvent {
    // Data
    MouseAction Action {};
    MouseButton Button {};
    DeltaTime DeltaTime {};
    KeyModifier Modifiers {};
    MouseButtonState State {};

    Position2D DeltaPosition {};
    Position2D LastPosition {};
    Position2D Position {};
    Position2D DeltaWheel {};

    // Specification
    const EventSource Source = EventSource::Mouse;
};

///
/// @brief Touch Event
///
struct TouchEvent: public BaseEvent {
    // Data
    TouchAction Action {};
    TouchState State {};

    DeltaTime DeltaTime {};
    Position2D DeltaPosition {};
    Position2D LastPosition {};
    Position2D Position {};

    // Specification
    const EventSource Source = EventSource::Touch;
};


///
/// Event Handler
///

///
/// @brief Event Handler Interface
///
class EventHandler: public EventEmitter {
public:
    /// Default
    EventHandler() = default;
    virtual ~EventHandler() = default;
    static Scope<EventHandler> Create();

    /// Methods
    virtual bool Callback(void *event) = 0;
    virtual void Update() = 0;

protected:
    /// Properties
    Position2D mMouseDeltaPosition {};
    Position2D mMouseLastPosition {};
    Position2D mMousePosition {};
    Position2D mMouseDeltaWheel {};
    Position2D mMouseLastDeltaWheel {};
};

}
