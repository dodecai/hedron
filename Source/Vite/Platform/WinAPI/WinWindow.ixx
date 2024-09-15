export module Vite.Platform.WinWindow;

import Vite.Bridge.WinAPI;
import Vite.Core;
import Vite.System.Window;

export namespace Hedron {

class WinWindow: public Window {
public:
    /// Default
    WinWindow(const WindowSettings &settings);
    ~WinWindow();
    virtual void Update() override;

    /// Controls
    void FullScreen(bool fullScreen) override;
    void Transparent(bool transparent) override;

    /// Accessors
    Size2D ContentSize() const override;
    const Position2D &Position() const override;
    const WindowSettings &Settings() const override;
    const Size2D &Size() const override;
    bool State(WindowState state) const override;
    const string &Title() const override;
    
    /// Mutators
    void CursorPosition(const Position2D &position) override;
    void Position(const Position2D &position) override;
    void Progress(float progress) override;
    void Settings(const WindowSettings &settings) override;
    void Size(const Size2D &size) override;
    void Title(string_view title) override;

private:
    /// Callbacks
    static LRESULT MessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    /// Casts
    virtual void *AsPlatformHandle() override;

    /// Methods
    LRESULT Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    //HICON LoadIconFile(const string &icon);
    //HICON *LoadIconResource(const uint32 id);

private:
    /// Properties
    WindowSettings mSettings {};
    wstring mWindowClass = L"Hedron::Window";

    /// Handles
    HINSTANCE mApplicationHandle {};
    HICON mApplicationIcon {};
    HWND mParentWindowHandle {};
    HWND mWindowHandle {};
    WinAPI::TaskbarList *mTaskbarList;
};

}
