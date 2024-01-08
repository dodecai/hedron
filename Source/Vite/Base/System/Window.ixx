export module Vite.System.Window;

//import Vite.Math;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief  Collection of platform independet window related types
///

//enum class WindowState: uint32_t {
//	Active		= BitMask(0u),
//	Alive		= BitMask(1u),
//	Cursor		= BitMask(2u),
//	Decorated	= BitMask(3u),
//	Focused		= BitMask(4u),
//	FullScreen	= BitMask(5u),
//	Maximized	= BitMask(6u),
//	Minimized	= BitMask(7u),
//	Visible		= BitMask(8u),
//};
//

///
/// @brief  Collection of platform independet window related data and properties
///

enum class WindowState {
    Active,
    Alive,
    Cursor,
    Decorated,
    Focused,
    FullScreen,
    Maximized,
    Minimized,
    Visible,
};

enum class WindowStyle {
    Default,
    Borderless,
    FullScreen,
};

struct WindowSettings {
    /// Properties
    string Title { "Hedron" };
    //Size2D<float> Size { 1280.0f, 1024.0f };
    //Position2D<float> Position { 0.0f, 0.0f };

    //string Icon { "Hedron" };

    //string ID { "Hedron" };
    //Size2D<float> MaxSize { 0.0f, 0.0f };
    //Size2D<float> MinSize { 640.0f, 512.0f };

    /// States
    //WindowState State {};
    //WindowStyle Style { WindowStyle::Default };

//	// Static
//	static constexpr uint32_t BorderWidth = 12;
//	static constexpr uint32_t TitleBarWidth = 5;

};

}

export namespace Hedron {

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

    /// Accessors
    //virtual Position2D<float> ContentSize() const = 0;
    //virtual const Position2D<float> &DisplayPosition() const = 0;
    //virtual const WindowSettings &Settings() const = 0;
    //virtual bool State(WindowState state) const = 0;
    //virtual const string &Title() const = 0;

    /// Mutators
    //virtual void CursorPosition(const Position2D<float> &position) = 0;
    //virtual void DisplayPosition(const Position2D<float> &position) = 0;
    //virtual void Progress(float progress) = 0;
    //virtual void Settings(const WindowSettings &properties) = 0;
    //virtual void Title(string_view title) = 0;

protected:
    /// Casts
    virtual void *AsPlatformHandle() = 0;

protected:
    /// Callbacks
    //function<bool(void *)> mExternalInputEventListener = {};
};

}
