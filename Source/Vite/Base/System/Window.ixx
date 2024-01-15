export module Vite.System.Window;

import Vite.Extension;
import Vite.Math;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief  Collection of platform independet window related types and settings
///

enum class WindowState {
    Active      = BitMask(0),
    Alive       = BitMask(1),
    Focused     = BitMask(2),
    Drawing     = BitMask(3),
    FullScreen  = BitMask(4),
    Maximized   = BitMask(5),
    Minimized   = BitMask(6),
    Visible     = BitMask(7),
};

inline WindowState operator~(WindowState state) {
    return static_cast<WindowState>(~static_cast<std::underlying_type<WindowState>::type>(state));
}

inline WindowState operator|(WindowState a, WindowState b) {
    return static_cast<WindowState>(
        static_cast<std::underlying_type<WindowState>::type>(a) |
        static_cast<std::underlying_type<WindowState>::type>(b));
}

inline WindowState operator&(WindowState a, WindowState b) {
    return static_cast<WindowState>(
        static_cast<std::underlying_type<WindowState>::type>(a) &
        static_cast<std::underlying_type<WindowState>::type>(b));
}

inline WindowState &operator|=(WindowState &a, WindowState b) {
    a = a | b;
    return a;
}

inline WindowState &operator&=(WindowState &a, WindowState b) {
    a = a & b;
    return a;
}

enum class WindowStyle {
    Default,
    Borderless,
    FullScreen,
    Transparent,
};

struct WindowSettings {
    /// Properties
    string Title { "Hedron" };
    Size2D Size { 1280.0f, 1024.0f };
    Position2D Position { 0.0f, 0.0f };

    string Icon { "Hedron" };
    Size2D MinSize { 640.0f, 512.0f };
    Size2D MaxSize { 0.0f, 0.0f };

    /// States
    WindowState State { WindowState::Alive };
    WindowStyle Style { WindowStyle::Default };
    Position2D LastMousePosition { 0.0f, 0.0f };

    // Static
    const uint32 BorderWidth = 12;
    const uint32 TitleBarWidth = 5;
};

///
/// @brief Window Interface
///
class Window {
    /// Friends
    friend class Application;

public:
    /// Default
    Window() = default;
    virtual ~Window() = default;
    static Scope<Window> Create(const WindowSettings &settings = WindowSettings());
    virtual void Update() = 0;

    /// Controls
    virtual void FullScreen(bool fullScreen) = 0;
    virtual void Transparency(bool transparency) = 0;

    /// Accessors
    virtual Size2D ContentSize() const = 0;
    virtual const Position2D &Position() const = 0;
    virtual const WindowSettings &Settings() const = 0;
    virtual const Size2D &Size() const = 0;
    virtual bool State(WindowState state) const = 0;
    virtual const string &Title() const = 0;

    /// Mutators
    virtual void CursorPosition(const Position2D &position) = 0;
    virtual void Position(const Position2D &position) = 0;
    virtual void Progress(float progress) = 0;
    virtual void Settings(const WindowSettings &settings) = 0;
    virtual void Size(const Size2D &size) = 0;
    virtual void Title(string_view title) = 0;

protected:
    /// Casts
    virtual void *AsPlatformHandle() = 0;

protected:
    /// Callbacks
    function<bool(void *)> mExternalInputEventListener = {};
};

}
