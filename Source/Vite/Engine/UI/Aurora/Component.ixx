export module Vite.Aurora.Component;

import Vite.Core;
import Vite.FontRenderer;

export namespace Hedron::UI {

///
/// @brief Enumeration and Types
///
enum class ComponentType {
    // Containers
    None = 0x00,
    Container = 0x01,
    Window = 0x02,
    Panel = 0x03,
    Popup = 0x04,
    ScrollView = 0x05,
    Containers = 0x1F, // Used as less than boundary

    // Controls
    Button = 0x20,
    Cursor = 0x21,
    CheckBox = 0x22,
    ColorPicker = 0x23,
    Grid = 0x24,
    Image = 0x25,
    Input = 0x26,
    Label = 0x27,
    Selection = 0x28,
    Seperator = 0x29,
    Slider = 0x2A,
    Table = 0x2B,
    Tree = 0x2C,
    Controls = 0x4F, // Used as less than boundary

    // Information
    Badge = 0x50,
    Notification = 0x51,
    Tooltip = 0x52,
    Information = 0x6F, // Used as less than boundary

    // Navigation (multiple-controls)
    MenuBar = 0x70,
    SideBar = 0x71,
    TabBar = 0x72,
    Navigations = 0x8F, // Used as less than boundary
};

enum class FocusStyle {
    None,
    Fill,
    Outline,
    Scroll,
    Underline,
};

enum class FocusType {
    Mouse,
    Keyboard,
    Scroll,
};

enum class Layout {
    None,
    Stack,
    Vertical,
    Horizontal,
};


///
/// @brief Base Types and Component Interface
///

struct Alignment {
    float X {};
    float Y {};
};

struct ClipArea {
    Position2D TopLeft {};
    Position2D BottomRight {};
};

struct Padding {
    float Left {};
    float Top {};
    float Bottom {};
    float Right {};
};

struct Stretch {
    float X {};
    float Y {};
};

struct Style {
    Color ColorDebugBorder { 1.0f, 1.0f, 1.0f, 0.5f };

    Color ColorPrimary { 0.1f, 0.5f, 1.0f, 1.0f };
    Color ColorSecondary { 0.1f, 1.0f, 0.5f, 1.0f };
    Color ColorTernary {};
    Color ColorFrame { 0.1f, 0.1f, 0.1f, 0.5f };
    Color ColorText { 1.0f, 1.0f, 1.0f, 1.0f };

    Color ColorFillNone { 0.15f, 0.15f, 0.15f, 0.8f };  // Panel
    Color ColorFillPressed { 0.2f, 0.7f, 1.0f, 1.0f };     // Panel
    Color ColorFillHovered { 0.1f, 0.5f, 1.0f, 1.0f };     // Panel
    Color ColorFocusUnderlineActive { 0.4f, 0.5f, 0.5f, 1.0 };      // Rect + FrameOpacity
    Color ColorFocusUnderline { 0.3f, 0.3f, 0.3f, 0.5 };      // Rect


    Color ColorFocusNone { 0.1f, 0.12f, 0.13f, 1.0f };   // Panel
    Color ColorFocusOutline { 0.1f, 0.5f, 1.0f, 1.0f };     // Rect

    Reference<Font> Font { nullptr };

    float Spacing { 6.0f };
};


///
/// @brief Component: Base for Containers and Controls
///
class Component {
public:
    Component(const string &id, const ComponentType &type):
        ID(id),
        Hash(mHasher(id)),
        Type(type) {}
    virtual ~Component() = default;

    // Comparison
    bool operator==(const Component &other) const {
        return Hash == other.Hash;
    }
    bool operator==(const string &id) const {
        return Hash == mHasher(id);
    }

    // Converters
    template<typename T>
    T *As() {
        return reinterpret_cast<T *>(this);
    }

    // Interface
    virtual void Draw() {}
    virtual void Update() {}

    // Methods
    void CalculateLayout(const Position2D &position, const Size2D &size) {
        // Update position and size of a control based on its alignment and stretch factors
        Position = position;
        Size = MinSize;

        Size.Width += Stretch.X * (size.Width - MinSize.Width);
        Size.Height += Stretch.Y * (size.Height - MinSize.Height);

        Position.X += Alignment.X * (size.Width - Size.Width);
        Position.Y += Alignment.Y * (size.Height - Size.Height);
    }
    bool Hovered(const Position2D &hoverPosition) const {
        return (
            hoverPosition.X >= Position.X &&
            hoverPosition.X <= Position.X + Size.Width &&
            hoverPosition.Y >= Position.Y &&
            hoverPosition.Y <= Position.Y + Size.Height
        );
    }

public:
    const Component *Parent {};
    const string ID;
    const size_t Hash;
    const ComponentType Type;

    // States
    bool Active {};
    bool Disabled {};
    bool Focused {};
    bool Interactive { true };
    bool Visible { true };

    // Style
    Color Color {};
    FocusStyle FocusStyle {};
    float FrameOpacity { 1.0f };

    // Transformation
    Position2D Position {};
    Size2D Size {};
    Position2D Offset {};
    Size2D MinSize {};
    Alignment Alignment {};
    Stretch Stretch {};
    Padding Padding {};
    Size2D OriginalSize {};

private:
    std::hash<std::string> mHasher;
};

}
