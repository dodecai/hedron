export module Vite.Event.Data;

export import Vite.Base;
export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;
export import Vite.Math.Geometry;
export import Vite.System.Window.Data;

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
    Position2D LastPosition {};
    Position2D Position {};
    Size2D DeltaSize {};
    Size2D LastSize {};
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
    string Utf8Character {}; // UTF-8 Character (1-4 bytes)

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

}

