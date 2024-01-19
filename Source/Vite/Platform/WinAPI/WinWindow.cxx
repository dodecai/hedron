module;

#include "Vite/Base/Platform/Detection.h"

#pragma comment(lib, "dwmapi.lib")
//#pragma comment(lib, "uxtheme.lib")

#define NOMINMAX
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <DwmApi.h>
#include <ShObjIdl.h>
#include <Windows.h>
#include <WindowsX.h>

module Vite.Platform.WinWindow;

///
/// Helpers
/// ToDo: Export these to Platform Helpers
///
namespace {

struct PlatformWindowStyle {
    DWORD ClassStyle;
    DWORD WindowStyle;
    DWORD WindowStyleEx;
};

enum class ClassStyle: DWORD {
    Application	= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
    Global		= CS_GLOBALCLASS | CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW,
};

enum class WinWindowStyle: DWORD {
    Default		= WS_OVERLAPPEDWINDOW, // Contains: WS_SYSMENU | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_VISIBLE
    Aero		= WS_POPUP | WS_THICKFRAME | WS_VISIBLE,
    Borderless	= WS_POPUP | WS_THICKFRAME | WS_VISIBLE,
    Full		= WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE,
};

enum class WinWindowStyleX: DWORD {
    DefaultX	= WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
    FullX		= WS_EX_APPWINDOW,
    Test		= WS_EX_APPWINDOW | WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE,
};


inline std::wstring ConvertChar2WChar(const std::string &source) {
    int bufferSize = MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, nullptr, 0);
    if (bufferSize == 0) return L"";

    std::wstring result(bufferSize, L'\0');
    if (MultiByteToWideChar(CP_UTF8, 0, source.c_str(), -1, &result[0], bufferSize) == 0) return L"";

    return result;
}

inline std::string GetLastErrorAsString() {
    //Get the error message ID, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0) {
        return std::string(); //No error message has been recorded
    }

    LPSTR messageBuffer = nullptr;

    // Ask Win32 to give us the string version of that message ID.
    //T he parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

    //Copy the error message into a std::string.
    std::string message(messageBuffer, size);

    // Free the Win32's string's buffer.
    LocalFree(messageBuffer);

    return message;
}

///
/// @brief Missing types for acrylic background
///
enum WINDOWCOMPOSITIONATTRIB {
    WCA_UNDEFINED                       = 0,
    WCA_NCRENDERING_ENABLED             = 1,
    WCA_NCRENDERING_POLICY              = 2,
    WCA_TRANSITIONS_FORCEDISABLED       = 3,
    WCA_ALLOW_NCPAINT                   = 4,
    WCA_CAPTION_BUTTON_BOUNDS           = 5,
    WCA_NONCLIENT_RTL_LAYOUT            = 6,
    WCA_FORCE_ICONIC_REPRESENTATION     = 7,
    WCA_EXTENDED_FRAME_BOUNDS           = 8,
    WCA_HAS_ICONIC_BITMAP               = 9,
    WCA_THEME_ATTRIBUTES                = 10,
    WCA_NCRENDERING_EXILED              = 11,
    WCA_NCADORNMENTINFO                 = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW       = 13,
    WCA_VIDEO_OVERLAY_ACTIVE            = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE   = 15,
    WCA_DISALLOW_PEEK                   = 16,
    WCA_CLOAK                           = 17,
    WCA_CLOAKED                         = 18,
    WCA_ACCENT_POLICY                   = 19,
    WCA_FREEZE_REPRESENTATION           = 20,
    WCA_EVER_UNCLOAKED                  = 21,
    WCA_VISUAL_OWNER                    = 22,
    WCA_HOLOGRAPHIC                     = 23,
    WCA_EXCLUDED_FROM_DDA               = 24,
    WCA_PASSIVEUPDATEMODE               = 25,
    WCA_LAST                            = 26
};

struct WINDOWCOMPOSITIONATTRIBDATA {
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
};

enum PreferredAppMode {
    Default,
    AllowDark,
    ForceDark,
    ForceLight
};

enum ACCENT_STATE {
    ACCENT_DISABLED                     = 0,
    ACCENT_ENABLE_GRADIENT              = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT   = 2,
    ACCENT_ENABLE_BLURBEHIND            = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND     = 4,    // RS4 1803
    ACCENT_ENABLE_HOSTBACKDROP          = 5,    // RS5 1809
    ACCENT_INVALID_STATE                = 6
};

struct ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
};

// Symbols
typedef BOOL (WINAPI *AllowDarkModeForAppFunc)(BOOL);
typedef BOOL (WINAPI *AllowDarkModeForWindowFunc)(HWND, BOOL);
typedef BOOL (WINAPI *GetWindowCompositionAttributeFunction)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
typedef BOOL (WINAPI *SetWindowCompositionAttributeFunction)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

}

namespace Hedron {

/// Default
WinWindow::WinWindow(const WindowSettings &settings): mSettings { settings } {
    // Application Information
    mApplicationHandle = GetModuleHandle(nullptr);
    LPWSTR lpCmdLine = GetCommandLine();
    STARTUPINFO StartupInfo {};
    GetStartupInfo(&StartupInfo);

    auto Test = true;

    PlatformWindowStyle windowStyle = {};
    wstring title = ConvertChar2WChar(mSettings.Title);

    // Settings
    windowStyle.ClassStyle = static_cast<DWORD>(ClassStyle::Application);
    //SetThreadExecutionState(ES_DISPLAY_REQUIRED && ES_SYSTEM_REQUIRED);

    // Load Resources
    //mWindowIcon = LoadIcon(NULL, IDI_APPLICATION);
    //mWindowIcon = (HICON)LoadImage(NULL, L"icon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    //mWindowIcon = (HICON)LoadIconFile(Properties.Icon);

    // Register Window Class
    static HBRUSH ClearColor = (HBRUSH)GetStockObject(NULL_BRUSH);
    WNDCLASSEX classProperties = {
        .cbSize	= sizeof(WNDCLASSEX),			// Structure Size (in bytes)
        .style = windowStyle.ClassStyle,		// Separate device context for window and redraw on move
        .lpfnWndProc = MessageCallback,			// Message Callback (WndProc)
        .cbClsExtra = 0,						// Extra class data
        .cbWndExtra = WS_EX_TOPMOST,			// Extra window data
        .hInstance = mApplicationHandle,		// Application Intance
        .hIcon = mApplicationIcon,  			// Load Icon (Default: LoadIcon(NULL, IDI_APPLICATION);)
        .hCursor = LoadCursor(NULL, IDC_ARROW),	// Load Cursor (Default: IDC_ARROW)
        .hbrBackground = ClearColor,			// Background (Not required for GL -> NULL)
        .lpszMenuName = NULL,					// We Don't Want A Menu
        .lpszClassName = mWindowClass.c_str(),   // Class Name should be unique per window
        .hIconSm = mApplicationIcon,			// Load Icon Symbol (Default: LoadIcon(NULL, IDI_WINLOGO);)
    };
    if (!RegisterClassEx(&classProperties)) {
        LogFatal("Failed to register the window class!");
        return;
    }

    // Switch to FullScreen Mode if requested
    if (mSettings.Style == WindowStyle::FullScreen) FullScreen(true);

    unsigned int screenWidth = GetSystemMetricsForDpi(SM_CXSCREEN, GetDpiForSystem());
    unsigned int screenHeight = GetSystemMetricsForDpi(SM_CYSCREEN, GetDpiForSystem());
    RECT dimension = {};
    switch (mSettings.Style) {
        case WindowStyle::Default: {
            windowStyle.WindowStyle = (DWORD)WinWindowStyle::Default;
            windowStyle.WindowStyleEx = (DWORD)WinWindowStyleX::DefaultX;
            break;
        }
        case WindowStyle::Borderless: {
            windowStyle.WindowStyle = (DWORD)WinWindowStyle::Borderless;
            windowStyle.WindowStyleEx = (DWORD)WinWindowStyleX::DefaultX;
            break;
        }
        case WindowStyle::FullScreen: {
            windowStyle.WindowStyle = (DWORD)WinWindowStyle::Full;
            windowStyle.WindowStyleEx = (DWORD)WinWindowStyleX::FullX;
            break;
        }
    }
    dimension.left = static_cast<LONG>(mSettings.Position.X);
    dimension.top = static_cast<LONG>(mSettings.Position.Y);
    dimension.right = (mSettings.Style == WindowStyle::FullScreen) ? (long)screenWidth : (long)mSettings.Size.Width;
    dimension.bottom = (mSettings.Style == WindowStyle::FullScreen) ? (long)screenHeight : (long)mSettings.Size.Height;
    AdjustWindowRectEx(&dimension, windowStyle.WindowStyle, FALSE, windowStyle.WindowStyleEx);

    // Create Window
    mWindowHandle = CreateWindowEx(
        windowStyle.WindowStyleEx,	// Window Style (extended)
        mWindowClass.c_str(),		// Window ClassName
        title.c_str(),	            // Window Title
        windowStyle.WindowStyle,	// Window Style

        // Window Position and Size (if not centered, system should decide where to position the window)
        CW_USEDEFAULT, CW_USEDEFAULT, dimension.right - dimension.left, dimension.bottom - dimension.top,

        mParentWindowHandle,		// Parent Window
        nullptr,					// Menu
        mApplicationHandle,			// Instance Handle
        this						// Application Data
    );
    if (!mWindowHandle) {
        LogFatal("Failed to create the window!");
        Log("{}", GetLastErrorAsString());
        //Destroy();
        return;
    }
    if (!mParentWindowHandle) { mParentWindowHandle = mWindowHandle; }

    // Center Window
    if (!(mSettings.Style == WindowStyle::FullScreen)/* && Properties.Position.Centered*/) {
        unsigned int x = (GetSystemMetrics(SM_CXSCREEN) - dimension.right) / 2;
        unsigned int y = (GetSystemMetrics(SM_CYSCREEN) - dimension.bottom) / 2;
        SetWindowPos(mWindowHandle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }

    // Show window
    if (true/*Data.Visible*/) {
        ShowWindow(mWindowHandle, SW_SHOW);
        SetForegroundWindow(mWindowHandle);
        SetFocus(mWindowHandle);
    }

    // Taskbar Settings
    //RegisterWindowMessage(L"TaskbarButtonCreated");
    //[[maybe_unused]] HRESULT hrf = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (LPVOID *)&TaskbarList);

    // Flash on Taskbar
    FlashWindow(mWindowHandle, true);
}

WinWindow::~WinWindow() {
    // Switch back to Standard mode if in FullScreen mode
    if (mSettings.Style == WindowStyle::FullScreen) {
        ChangeDisplaySettings(nullptr, 0);
        ShowCursor(true);
    }
    
    // Ensure that the Window Class gets released
    if (mApplicationHandle) {
        //if (!UnregisterClass(ConvertChar2WChar(Properties.ID).c_str(), mApplicationHandle)) {
        //    LogError("Could not unregister window class.");
        //    Log("{}", GetLastErrorAsString());
        //}
    }
}

void WinWindow::Update() {
    MSG message {};
    while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }
}


/// Controls
void WinWindow::FullScreen(bool fullScreen) {
    // Switch to FullScreen Mode if requested
    unsigned int screenWidth = GetSystemMetricsForDpi(SM_CXSCREEN, GetDpiForSystem());
    unsigned int screenHeight = GetSystemMetricsForDpi(SM_CYSCREEN, GetDpiForSystem());
    RECT dimension = {};
    dimension.left = static_cast<LONG>(mSettings.Position.X);
    dimension.top = static_cast<LONG>(mSettings.Position.Y);
    dimension.right = (mSettings.Style == WindowStyle::FullScreen) ? (long)screenWidth : (long)mSettings.Size.Width;
    dimension.bottom = (mSettings.Style == WindowStyle::FullScreen) ? (long)screenHeight : (long)mSettings.Size.Height;

    // Device Mode
    DEVMODE screenProperties = {
        .dmSize = sizeof(DEVMODE),				// Structure Size
        .dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT,
        .dmBitsPerPel = 32,						// Selected Bits Per Pixel
        .dmPelsWidth = screenWidth,		// Selected Screen Width
        .dmPelsHeight = screenHeight,	// Selected Screen Height
    };

    // Try to set selected Fullscreen mode
    if ((mSettings.Size.Width != screenWidth) && (mSettings.Size.Height != screenHeight)) {
        // If the switching fails, offer the user an option to switch to windowed mode
        if (ChangeDisplaySettings(&screenProperties, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL) {
            if (MessageBox(NULL, (LPCWSTR)L"The requested mode 'FullScreen' isn't supported by\nyour graphics card. Switch to windowed mode Instead?", (LPCWSTR)__FUNCTION__, MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
                mSettings.Style = WindowStyle::Default;
            } else {
                LogFatal("[Window]: ", "Switching to Fullscreen mode failed!");
                return;
            }
        }
    }

    //// Get the current window style
    //LONG windowStyle = GetWindowLong(mWindowHandle, GWL_STYLE);

    //if (fullScreen) {
    //    // Set the window style to fullscreen
    //    SetWindowLong(mWindowHandle, GWL_STYLE, windowStyle & ~WS_OVERLAPPEDWINDOW);

    //    // Set the window position and size to cover the entire screen
    //    SetWindowPos(mWindowHandle, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), SWP_FRAMECHANGED);
    //} else {
    //    // Restore the window style to normal
    //    SetWindowLong(mWindowHandle, GWL_STYLE, windowStyle | WS_OVERLAPPEDWINDOW);

    //    // Set the window position and size based on the stored settings
    //    SetWindowPos(mWindowHandle, HWND_TOP, mSettings.Position.X, mSettings.Position.Y, mSettings.Size.Width, mSettings.Size.Height, SWP_FRAMECHANGED);
    //}
    // FullScreen more convenient?
    //mSettings.Style = WindowStyle::FullScreen;
    //HMONITOR hmon = MonitorFromWindow(WindowHandle, MONITOR_DEFAULTTONEAREST);
    //MONITORINFO mi = { sizeof(mi) };
    //GetMonitorInfo(hmon, &mi);
    //dimension.left = mi.rcMonitor.left;
    //dimension.top = mi.rcMonitor.top;
    //dimension.right = mi.rcMonitor.right;
    //dimension.bottom = mi.rcMonitor.bottom;
    //// Configure Window
    //ShowCursor(!);
}

void WinWindow::Transparent(bool transparent) {
    // Transparency
    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (transparent && hUser) {
        auto SetWindowCompositionAttribute = (SetWindowCompositionAttributeFunction)GetProcAddress(hUser, "SetWindowCompositionAttribute");
        if (SetWindowCompositionAttribute) {
            ACCENT_POLICY accent = { // AGBR
                ACCENT_ENABLE_BLURBEHIND,
                0x00000000,
                0x27000000,
                0x00000000,
            };

            WINDOWCOMPOSITIONATTRIBDATA data = {
                .Attrib = WCA_ACCENT_POLICY,
                .pvData = &accent,
                .cbData = sizeof(accent)
            };
            SetWindowCompositionAttribute(mWindowHandle, &data);
            //BOOL value = TRUE;
            //DwmSetWindowAttribute(mWindowHandle, DWMWA_USE_HOSTBACKDROPBRUSH, reinterpret_cast<void *>(&value), sizeof(accent));
            //SetLayeredWindowAttributes(mWindowHandle, 0, 128, LWA_ALPHA);
        }
    }

    SetWindowLong(mWindowHandle, GWL_EXSTYLE, GetWindowLong(mWindowHandle, GWL_EXSTYLE) | WS_EX_LAYERED);

    // Simple Transparency (Requires: WS_EX_LAYERED)
    //SetLayeredWindowAttributes(mWindowHandle, NULL, 224, LWA_ALPHA);
}


/// Accessors
Size2D WinWindow::ContentSize() const {
	RECT dimension;
	GetClientRect(mWindowHandle, &dimension);
    auto width = static_cast<float>(dimension.right - dimension.left);
    auto height = static_cast<float>(dimension.bottom - dimension.top);

    return { width, height };
}

const Position2D &WinWindow::Position() const {
	//WINDOWPLACEMENT position;
	//GetWindowPlacement(mWindowHandle, &position);
    //return { static_cast<float>(position.ptMinPosition.x), static_cast<float>(position.ptMinPosition.y) };

    return mSettings.Position;
}

const WindowSettings &WinWindow::Settings() const {
    return mSettings;
}

const Size2D &WinWindow::Size() const {
    return mSettings.Size;
}

bool WinWindow::State(WindowState state) const {
    return (mState & state) == state;
}

const string &WinWindow::Title() const {
    //vector<wchar_t> title(1024);
	//GetWindowText(mWindowHandle, title.data(), sizeof_vector(title));

    return mSettings.Title;
}


/// Mutators
void Hedron::WinWindow::CursorPosition(const Position2D &position) {
    if (!SetCursorPos(static_cast<int>(position.X), static_cast<int>(position.Y))) {
		LogError("Error occurred while setting cursor position!");
    }
}

void WinWindow::Position(const Position2D &position) {
    if (!SetWindowPos(mWindowHandle, 0, static_cast<int>(position.X), static_cast<int>(position.Y), 0, 0, SWP_NOSIZE | SWP_NOZORDER)) {
        LogError("Error occurred while setting display position!");
    }
    mSettings.Position = position;
}

void WinWindow::Progress(float progress) {
    //static uint32_t max = 100;
    //uint32_t current = (uint32_t)(progress * (float)max);
    //TaskbarList->SetProgressValue(WindowHandle, current, max);
}

void WinWindow::Settings(const WindowSettings &settings) {
    //mSettings = settings;
    
    //SetDisplayPosition(properties.Position.X, properties.Position.Y);
    //SetDisplaySize(properties.Size.Width, properties.Size.Height);
    //SetTitle(properties.Title);
}

void WinWindow::Size(const Size2D &size) {
    auto width = static_cast<int>(size.Width);
    auto height = static_cast<int>(size.Height);

    if (!SetWindowPos(mWindowHandle, 0, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER)) {
        LogError("Error occurred while setting display size!");
    }
    mSettings.Size = size;
}

void WinWindow::Title(string_view title) {
    mSettings.Title = title;
    //if (!SetWindowText(WindowHandle, ConvertChar2WChar(title.data()).c_str())) {
    //       LogError("Error occurred while setting title!");
    //	return;
    //}
}


/// Callbacks
LRESULT CALLBACK WinWindow::MessageCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// Properties
	WinWindow *pCurrentWindow = nullptr;

	// Get/Set the current window class pointer as userdata in WinAPI window
	switch (uMsg) {
		case WM_NCCREATE: {
			pCurrentWindow = reinterpret_cast<WinWindow *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);
			SetLastError(0);
			if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCurrentWindow))) {
				if (GetLastError() != 0) { return FALSE; }
			}
			break;
		}

		default: {
			pCurrentWindow = reinterpret_cast<WinWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

			// Capture Mouse while button is down
			if (uMsg == WM_LBUTTONDOWN) { SetCapture(hWnd); }
            if (uMsg == WM_LBUTTONUP)   { ReleaseCapture(); }
			break;
		}
	}
	
	// Dispatch Message or ...
    if (pCurrentWindow) {
        return pCurrentWindow->Message(hWnd, uMsg, wParam, lParam);
    }
	// ... return it as unhandled
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


/// Casts
void *WinWindow::AsPlatformHandle() {
    //AppAssert(mWindowHandle, "The requested platform handle is null!");
    return reinterpret_cast<void *>(mWindowHandle);
}


/// Methods
LRESULT WinWindow::Message(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    ///
    /// @brief	Window Messages
    /// @source:
    ///  - https://docs.microsoft.com/en-us/windows/win32/winmsg/window-messages
    ///	 - https://docs.microsoft.com/en-us/windows/win32/winmsg/window-notifications
    ///	 - https://docs.microsoft.com/en-us/windows/win32/inputdev/keyboard-input-notifications
    ///	 - https://docs.microsoft.com/en-us/windows/win32/gdi/painting-and-drawing-messages
    ///
    // Process important window related events internally
    switch (uMsg) {
        // Pre-Check: Does this message belong to the current window?
        case WM_NULL: {
            // Note: Could be useful in the future.
            break;
        }

        // Preparation
        case WM_NCCREATE: {
            // Note: Could be useful in the future.
            break;
        }
        case WM_NCDESTROY : {
            // Note: Could be useful in the future.
            break;
        }

        // Custom Title Bar
        case WM_NCCALCSIZE: {
            if (mSettings.Style == WindowStyle::Borderless && lParam) {
                const int borderX = GetSystemMetrics(SM_CXSIZEFRAME) / 2;
                const int borderY = GetSystemMetrics(SM_CYSIZEFRAME) / 2;

                auto hasThickFrame = GetWindowLongPtr(hWnd, GWL_STYLE) & WS_THICKFRAME;
                if (!hasThickFrame) { break; }

                auto *params = reinterpret_cast<NCCALCSIZE_PARAMS *>(lParam);
                params->rgrc[0].left += borderX;
                params->rgrc[0].top += borderY;
                params->rgrc[0].right -= borderX;
                params->rgrc[0].bottom -= borderY;

                return WVR_ALIGNLEFT | WVR_ALIGNTOP | WVR_ALIGNBOTTOM | WVR_ALIGNRIGHT;
            }
        }
        case WM_NCHITTEST: {
            auto hasThickFrame = GetWindowLongPtr(hWnd, GWL_STYLE) & WS_THICKFRAME;
            if (mSettings.Style != WindowStyle::Borderless || !hasThickFrame) break;
            break;

            // Test for custom frames
            POINT cursorPosition = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            ScreenToClient(hWnd, &cursorPosition);
            if (false /*!Data.Maximized*/) {
                RECT clientRect {};
                GetClientRect(hWnd, &clientRect);

                const int borderSizeVertical = GetSystemMetrics(SM_CYFRAME);
                int hit = 0;
                enum { left = 1, top = 2, right = 4, bottom = 8 };
                
                static RECT borderThickness { 4, 4, 4, 4 };
                if (cursorPosition.x <= borderThickness.left) hit |= left;
                if (cursorPosition.x >= clientRect.right - borderThickness.right) hit |= right;
                if (cursorPosition.y <= borderThickness.top || cursorPosition.y < borderSizeVertical) hit |= top;
                if (cursorPosition.y >= clientRect.bottom - borderThickness.bottom) hit |= bottom;
                
                if (hit & top && hit & left)        return HTTOPLEFT;
                if (hit & top && hit & right)       return HTTOPRIGHT;
                if (hit & bottom && hit & left)     return HTBOTTOMLEFT;
                if (hit & bottom && hit & right)    return HTBOTTOMRIGHT;
                if (hit & left)                     return HTLEFT;
                if (hit & top)                      return HTTOP;
                if (hit & right)                    return HTRIGHT;
                if (hit & bottom)                   return HTBOTTOM;
            }

            auto testTitleBarHit = 0;
            if (testTitleBarHit) {
                return HTCAPTION;
            };
        }

        // Creation and Destruction
        case WM_CLOSE: {
            // Ensure that the Window gets destroyed and release the handle to it
            if (DestroyWindow(mWindowHandle)) {
                mWindowHandle = nullptr;
            } else {
                LogError("Could not release handle to window.\n");
            }

            return TRUE;
            break;
        }
        case WM_CREATE: {
            mState |= WindowState::Alive;
            break;
        }
        case WM_DESTROY: {
            mState &= ~WindowState::Alive;

            PostQuitMessage(0);
            return TRUE;
            break;
        }

        // Information
        case WM_DPICHANGED: {
            // Note: Could be useful in the future.
            break;
        }
        case WM_GETMINMAXINFO: {
            if (mSettings.Style == WindowStyle::FullScreen) { break; }
            
            MINMAXINFO *bounds = reinterpret_cast<MINMAXINFO *>(lParam);
            auto maxWidth = static_cast<LONG>(mSettings.MaxSize.Width);
            auto maxHeight = static_cast<LONG>(mSettings.MaxSize.Height);
            auto minWidth = static_cast<LONG>(mSettings.MinSize.Width);
            auto minHeight = static_cast<LONG>(mSettings.MinSize.Height);

            if (maxWidth > 0 && maxHeight > 0) {
                bounds->ptMaxTrackSize.x = maxWidth;
                bounds->ptMaxTrackSize.y = maxHeight;
            }
            if (minWidth > 0 && minHeight > 0) {
                bounds->ptMinTrackSize.x = minWidth;
                bounds->ptMinTrackSize.y = minHeight;
            }
            
            return TRUE;
            break;
        }

        // Drawing
        case WM_PAINT: {
            mState |= WindowState::Drawing;

            PAINTSTRUCT ps {};
            HDC deviceContext = BeginPaint(hWnd, &ps);
            // ToDo: Implement Software Rendering
            //FillRect(deviceContext, &ps.rcPaint, ClearColor);
            EndPaint(hWnd, &ps);

            mState &= ~WindowState::Drawing;
            break;
        }
        case WM_ERASEBKGND: {
            // Prevent system clearing the window.
            return TRUE;
            break;
        }
        case WM_MOVE: {
            // Note: Could be useful in the future.
            break;
        }
        case WM_SHOWWINDOW: {
            if (wParam == TRUE) {
                mState |= WindowState::Visible;
            } else {
                mState &= ~WindowState::Visible;
            }
            break;
        }
        case WM_SIZE: {
            switch (wParam) {
                case SIZE_MAXIMIZED: {
                    mState |= WindowState::Maximized;
                    mState &= ~WindowState::Minimized;
                    break;
                }
                case SIZE_MINIMIZED: {
                    mState |= WindowState::Minimized;
                    mState &= ~WindowState::Maximized;
                    break;
                }
                case SIZE_RESTORED: {
                    mState &= ~WindowState::FullScreen;
                    mState &= ~WindowState::Maximized;
                    mState &= ~WindowState::Minimized;
                }
            }

            auto width = static_cast<float>(LOWORD(lParam));
            auto height = static_cast<float>(HIWORD(lParam));
            mSettings.Size = { width, height };

            break;
        }
        case WM_SIZING: {
            //RedrawWindow(hWnd, nullptr, nullptr, RDW_UPDATENOW | RDW_NOERASE);
            break;
        }

        // State
        case WM_ACTIVATE: {
            if (wParam == WA_INACTIVE) {
                mState &= ~WindowState::Active;
            } else {
                mState |= WindowState::Active;
            }
            break;
        }
        case WM_CAPTURECHANGED: {
            break;
        }
        case WM_KILLFOCUS: {
            mState &= ~WindowState::Focused;

            //POINT position {};
            //if (GetCursorPos(&position)) {
            //    ScreenToClient(hWnd, &position);
            //    auto x = static_cast<float>(position.x);
            //    auto y = static_cast<float>(position.y);

            //    mSettings.LastMousePosition = { x, y };
            //}
            break;
        }
        case WM_SETFOCUS: {
            mState |= WindowState::Focused;

            //auto x = static_cast<LONG>(mSettings.LastMousePosition.X);
            //auto y = static_cast<LONG>(mSettings.LastMousePosition.Y);

            //POINT position = { x, y };
            //ClientToScreen(hWnd, &position);
            //SetCursorPos(position.x, position.y);
            break;
        }

        // System
        case WM_SYSCOMMAND: {
            // Disable the menu system commands (ALT, F10), so that they don't steal the focus
            if (wParam == SC_KEYMENU) return TRUE;
            
            switch (wParam) {
                // FulLScree-Mode: Prevent ScreenSaver or Monitor PowerSaver
                case SC_SCREENSAVE: [[fallthrough]];
                case SC_MONITORPOWER: {
                    if (mSettings.Style == WindowStyle::FullScreen) { return TRUE; }
                    break;
                }
            
                default: {
                    break;
                }
            }
            break;
        }

        // Default: Currently nothing of interest
        default: {
            break;
        }
    }

    // Publish events to an external event system
    if (mExternalEventHandler) {
        MSG message = { hWnd, uMsg, wParam, lParam };
        auto externalResult = mExternalEventHandler(&message);
        if (externalResult) return TRUE;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef LEGACY_CODE
void *WinWindow::LoadIconFile(const string &icon) {
    return LoadImage(
        NULL,				// Handle Instance must be NULL when loading from a files
        ConvertChar2WChar(icon).c_str(),		// Icon File
        IMAGE_ICON,			// Specifies that the file is an icon
        0,					// Width of the image (we'll specify default later on)
        0,					// Height of the image
        LR_LOADFROMFILE |	// Load a file (as opposed to a resource)
        LR_DEFAULTSIZE |	// Default metrics based on the type (IMAGE_ICON, 32x32)
        LR_SHARED			// Let the system release the handle when it's no longer used
    );
}
#endif

}
