export module Vite.System.Window;

import Vite.Extension;
import Vite.Math;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief  Window States [Active|Alive|Focused|Drawing|FullScreen|Maximized|Minimized|Visible]
///
enum class WindowState {
    Active      = BitMask(0),
    Alive       = BitMask(1),
    //Created   = BitMask(x),
    //Destroy   = BitMask(x),
    //DpiUpdate = BitMask(x),
    //DragNDrop = BitMask(x),
    Focused     = BitMask(2),
    Drawing     = BitMask(3),
    FullScreen  = BitMask(4),
    Maximized   = BitMask(5),
    Minimized   = BitMask(6),
    //Moving    = BitMask(x),
    //Resizing  = BitMask(x),
    Visible     = BitMask(7),
};

// Enable BitMask Operators
template<> struct EnableBitMaskOperators<WindowState> {
    static const bool enable = true;
};

///
/// @brief Window Styles [Default|Borderless|FullScreen|Transparent]
///
enum class WindowStyle {
    Default,
    Borderless,
    FullScreen,
    Transparent,
};

///
/// @brief Window Settings
///
struct WindowSettings {
    /// Properties
    string Title { "Hedron" };
    Position2D Position { 0.0f, 0.0f };
    Size2D Size { 1280.0f, 1024.0f };
    WindowStyle Style { WindowStyle::Default };

    /// Limits
    Size2D MinSize { 640.0f, 512.0f };
    Size2D MaxSize { 0.0f, 0.0f };

    /// Resources
    string Icon { "Hedron" };
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
    // Toggle between full screen and windowed mode
    virtual void FullScreen(bool fullScreen) = 0;
    // Toggle the transparency of the window
    virtual void Transparent(bool transparent) = 0;

    /// Accessors
    // Retrieve the content size of the window
    virtual Size2D ContentSize() const = 0;
    // Retrieve the position of the window
    virtual const Position2D &Position() const = 0;
    // Retrieve the settings of the window
    virtual const WindowSettings &Settings() const = 0;
    // Retrieve the size of the window
    virtual const Size2D &Size() const = 0;
    // Retrieve the state of the window
    virtual bool State(WindowState state) const = 0;
    // Retrieve the title of the window
    virtual const string &Title() const = 0;

    /// Mutators
    // Set an external event handler
    void ExternalEventHandler(function<bool(void *)> handler) { mExternalEventHandler = { handler }; };
    // Set the cursor position
    virtual void CursorPosition(const Position2D &position) = 0;
    // Set the position of the window
    virtual void Position(const Position2D &position) = 0;
    // Update the progress bar in title bar
    virtual void Progress(float progress) = 0;
    // Set the settings of the window
    virtual void Settings(const WindowSettings &settings) = 0;
    // Set the size of the window
    virtual void Size(const Size2D &size) = 0;
    // Set the title of the window
    virtual void Title(string_view title) = 0;

protected:
    /// Casts
    // Retrieves the platform specific handle.
    virtual void *AsPlatformHandle() = 0;

protected:
    /// Callbacks
    function<bool(void *)> mExternalEventHandler = {};

    /// States
    Position2D mLastMousePosition {};
    WindowState mState {};
};

}
