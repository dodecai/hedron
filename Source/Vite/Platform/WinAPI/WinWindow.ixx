export module Vite.Platform.WinWindow;

import <Windows.h>;

import Vite.Core;
import Vite.System.Window;

export namespace Hedron {

//struct PlatformWindowStyle {
//    uint32_t ClassStyle;
//    uint32_t WindowStyle;
//    uint32_t WindowStyleEx;
//};
//
//enum class ClassStyle: uint32_t {
//    Application	= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
//    Global		= CS_GLOBALCLASS | CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
//};
//
//enum class WinWindowStyle: uint32_t {
//    // Contains: WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_VISIBLE
//    Default		= WS_OVERLAPPEDWINDOW,	
//    Aero		= WS_POPUP | WS_THICKFRAME | WS_VISIBLE,
//    Borderless	= WS_POPUP | WS_VISIBLE,
//    Full		= WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
//};
//
//enum class WinWindowStyleX: uint32_t {
//    DefaultX	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
//    FullX		= WS_EX_APPWINDOW,
//    Test		= WS_EX_APPWINDOW | WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
//};
//

class WinWindow: public Window {
public:
    /// Default
    WinWindow(const WindowSettings &settings);
    ~WinWindow();
    virtual void Update() override;

    // Accessors
    Position2D<float> ContentSize() const override { return { 1.0f, 1.0f }; }
    //const Position2D<float> &DisplayPosition() const override { return {}; }
    //const WindowSettings &Settings() const override { return {}; }
    //bool State(WindowState state) const override { return {}; }
    //const string &Title() const override { return {}; }
    
    /// Mutators
    //void CursorPosition(const Position2D<float> &position) override {}
    //void DisplayPosition(const Position2D<float> &position) override {}
    //void Progress(float progress) override {}
    //void Settings(const WindowSettings &properties) override {}
    //void Title(string_view title) override {}

    /// Methods
    //Subject<bool &, void *> EventCallback;
    //intptr_t Message(void *event);

private:
    /// Callbacks
    //static LRESULT CALLBACK MessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /// Casts
    virtual void *AsPlatformHandle() override;

    /// Methods
    //void *LoadIconFile(const string &icon);
    //void *LoadIconResource(const uint32_t id);

private:
    /// Properties
    //WindowData Data;
    WindowSettings Properties {};

    /// Handles
    HINSTANCE mApplicationHandle {};
    HWND mParentWindowHandle {};
    HWND mWindowHandle {};
    HICON mWindowIcon {};
};

}
