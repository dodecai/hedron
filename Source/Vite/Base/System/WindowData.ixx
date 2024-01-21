export module Vite.System.Window.Data;

export import Vite.Extension;
export import Vite.Math.Geometry;
export import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Window Actions [Activate|Create|Deactivate|Defocus|Destroy|DpiUpdate|DragNDrop|Draw|Focus|Hide|Maximize|Minimize|Move|Resize|Show|Update]
///
enum class WindowAction {
    Undefined,
    Activate,
    Create,
    Deactivate,
    Defocus,
    Destroy,
    DpiUpdate,
    DragNDrop,
    Draw,
    Focus,
    Hide,
    Maximize,
    Minimize,
    Move,
    Resize,
    Show,
    Update,
};

// Window Action Names
template<>
struct NamedEnumTraits<WindowAction> {
    static constexpr string_view Names[] = {
        "Undefined",
        "Activate",
        "Create",
        "Deactivate",
        "Defocus",
        "Destroy",
        "DpiUpdate",
        "DragNDrop",
        "Draw",
        "Focus",
        "Hide",
        "Maximize",
        "Minimize",
        "Move",
        "Resize",
        "Show",
        "Update",
    };
};

// Enable Formatter and Stream Operators
template<>
struct EnableNamedEnumFormatter<WindowAction> {
    static const bool Enable = true;
};

template<>
struct EnableNamedEnumStreamOperators<WindowAction> {
    static const bool Enable = true;
};


///
/// @brief  Window States [Active|Alive|Focused|FullScreen|Maximized|Minimized|Restored|Visible]
///
enum class WindowState {
    Active      = BitMask(0),
    Alive       = BitMask(1),
    Drawing     = BitMask(2),
    Focused     = BitMask(3),
    FullScreen  = BitMask(4),
    Maximized   = BitMask(5),
    Minimized   = BitMask(6),
    Restored    = BitMask(7),
    Visible     = BitMask(8),
};

// Enable BitMask Operators
template<> struct EnableBitMaskOperators<WindowState> {
    static const bool enable = true;
};


///
/// @brief Window Styles [Default|Borderless|FullScreen|Transparent]
///
enum class WindowStyle {
    CustomTitleBar  = BitMask(0),
    FullScreen      = BitMask(1),
    Transparent     = BitMask(2),
    TitleBar        = BitMask(3),

    Default = TitleBar,
};

// Enable BitMask Operators
template<> struct EnableBitMaskOperators<WindowStyle> {
    static const bool enable = true;
};

}
