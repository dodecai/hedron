module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define VC_EXTRALEAN

#pragma warning(push, 0)

#include <DwmApi.h>
#include <ShObjIdl.h>
#include <Windows.h>
#include <WindowsX.h>

#pragma warning(pop)

export module Vite.Bridge.WinAPI;

import Vite.Extension;
import Vite.Type;

///
/// @brief Bridge: Windows API
/// @detail Windows Application Programming Interface
/// @note The export is reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export {

namespace WinAPI {
    ///
    /// Data
    ///
    
    // Constants
    enum Setting: DWORD {
        #undef ENUM_CURRENT_SETTINGS
        ENUM_CURRENT_SETTINGS = ((DWORD)-1),
        #undef ENUM_REGISTRY_SETTINGS
        ENUM_REGISTRY_SETTINGS = ((DWORD)-2),
    };
    enum SystemSettings: uin32 {
        Current = ENUM_CURRENT_SETTINGS,
        Registry = ENUM_REGISTRY_SETTINGS,
    };
    constexpr auto gEnumerateCurrentSettings = ENUM_CURRENT_SETTINGS;
    constexpr auto gEnumerateRegistrySettings = ENUM_REGISTRY_SETTINGS;

    // Enumerations
    enum DisplayDeviceConstants {
        #undef DISPLAY_DEVICE_ACTIVE
        DISPLAY_DEVICE_ACTIVE = 0x00000001,
        #undef DISPLAY_DEVICE_ATTACHED_TO_DESKTOP
        DISPLAY_DEVICE_ATTACHED_TO_DESKTOP = 0x00000001,
        #undef DISPLAY_DEVICE_PRIMARY_DEVICE
        DISPLAY_DEVICE_PRIMARY_DEVICE = 0x00000004,
        #undef DISPLAY_DEVICE_REMOTE
        DISPLAY_DEVICE_REMOTE = 0x04000000,
    };
    enum DisplayDeviceState: unsigned long {
        Active = DISPLAY_DEVICE_ACTIVE,
        Attached = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP,
        Primary = DISPLAY_DEVICE_PRIMARY_DEVICE,
        Remote = DISPLAY_DEVICE_REMOTE,
    };
    
    enum SystemMetricConstants {
        #undef SM_CMONITORS
        SM_CMONITORS = 80,
        #undef SM_CXSCREEN
        SM_CXSCREEN = 0,
        #undef SM_CYSCREEN
        SM_CYSCREEN = 1,
        #undef SM_SHUTTINGDOWN
        SM_SHUTTINGDOWN = 0x2000,
        #undef SM_CXBORDER
        SM_CXBORDER = 5,
        #undef SM_CYBORDER
        SM_CYBORDER = 6,
        #undef SM_CXSIZEFRAME
        SM_CXSIZEFRAME = 32,
        #undef SM_CYSIZEFRAME
        SM_CYSIZEFRAME = 33,
    };
    enum SystemMetrics: int {
        ScreenCount = SM_CMONITORS,         // Number of display monitors on the desktop.
        ScreenX = SM_CXSCREEN,              // Width of the current screen, in pixels.
        ScreenY = SM_CYSCREEN,              // Height of the current screen, in pixels.
        SystemShutdown = SM_SHUTTINGDOWN,   // The system is being shut down.
        WindowBorderX = SM_CXBORDER,        // Width of the current window border, in pixels.
        WindowBorderY = SM_CYBORDER,        // Height of the current window border, in pixels.
        WindowFrameSizeX = SM_CXSIZEFRAME,  // Width of the current window frame, in pixels.
        WindowFrameSizeY = SM_CYSIZEFRAME,  // Height of the current window frame, in pixels.
    };

    // Handles
    using ::HDC;
    using ::HANDLE;
    using ::HICON;
    using ::HINSTANCE;
    using ::HMODULE;
    using ::HWND;
    using DeviceContextHandle = ::HDC;
    using GenericHandle = ::HANDLE;
    using IconHandle = ::HICON;
    using InstanceHandle = ::HINSTANCE;
    using ModuleHandle = ::HMODULE;
    using WindowHandle = ::HWND;

    // Types
    using ::DWORD;      // uint32
    using ::LPARAM;     // uintptr
    using ::LRESULT;    // uintptr
    using ::UINT;       // uint32
    using ::WPARAM;     // uintptr

    // Structures
    using ::DEVMODE;
    using ::DISPLAY_DEVICE;
    using ::MONITORINFOEX;
    using ::MSG;
    using ::POINT;
    using ::RAWINPUTDEVICE;
    using ::ITaskbarList3;
    using DeviceMode = ::DEVMODE;
    using DisplayDevice = ::DISPLAY_DEVICE;
    using Message = ::MSG;
    using MonitorInfoExtended = ::MONITORINFOEX;
    using Point = ::POINT;
    using RawInputDevice = ::RAWINPUTDEVICE;
    using TaskbarList = ::ITaskbarList3;

    ///
    /// Functions
    ///
    
    #undef EnumDisplayDevices
    #undef EnumDisplaySettings
    #undef GetMonitorInfo
    #undef LoadLibrary
    #undef GetModuleHandle
    #undef LoadIcon
#ifdef _UNICODE
    inline auto EnumDisplayDevices = ::EnumDisplayDevicesW;
    inline auto EnumDisplaySettings = ::EnumDisplaySettingsW;
    inline auto GetMonitorInfo = ::GetMonitorInfoW;
    inline auto LoadLibrary = ::LoadLibraryW;
    inline auto GetModuleHandle = ::GetModuleHandleW;
    inline auto LoadIcon = ::LoadIconW;
#else 
    inline auto EnumDisplayDevices = ::EnumDisplayDevicesA;
    inline auto EnumDisplaySettings = ::EnumDisplaySettingsA;
    inline auto GetMonitorInfo = ::GetMonitorInfoA;
    inline auto LoadLibrary = ::LoadLibraryA;
    inline auto GetModuleHandle = ::GetModuleHandleA;
    inline auto LoadIcon = ::LoadIconA;
#endif
    using ::EnumDisplayMonitors;
    using ::GetActiveWindow;
    using ::GetAncestor;
    using ::GetFocus;
    using ::GetForegroundWindow;
    using ::GetParent;
    using ::GetSystemMetrics;
    using ::GetWindow;

    ///
    /// Function Wrappers
    ///

    // Device
    class Device: public Hedron::StaticObject {
        #undef EnumDisplayDevices
        #undef EnumDisplaySettings
        #undef GetMonitorInfo
    public:
        [[nodiscard]] static inline auto EnumDisplayDevices(const wchar *lpDevice, DWORD iDevEnum, DISPLAY_DEVICE *lpDisplayDevice, DWORD dwFlags) noexcept {
            return ::EnumDisplayDevicesW(lpDevice, iDevEnum, lpDisplayDevice, dwFlags);
        }

        [[nodiscard]] static inline auto EnumDisplayMonitors(HDC hdc, LPRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData) {
            return ::EnumDisplayMonitors(hdc, lprcClip, lpfnEnum, dwData);
        }

        [[nodiscard]] static inline auto EnumDisplaySettings(const wchar *deviceName, DWORD iModeNum, DEVMODE *lpDevMode) noexcept {
            return ::EnumDisplaySettingsW(deviceName, iModeNum, lpDevMode);
        }

        [[nodiscard]] static inline auto GetMonitorInfo(HMONITOR hMonitor, MONITORINFOEX *lpmi) noexcept {
            return ::GetMonitorInfoW(hMonitor, lpmi);
        }
    };

    // Library
    class Library: public Hedron::StaticObject {
    public:
        // Load a library.
        [[nodiscard]] static inline auto Load(const char *name) noexcept {
            return (ModuleHandle)::LoadLibraryA(name);
        }
        [[nodiscard]] static inline auto Load(const wchar_t *name) noexcept {
            return (ModuleHandle)::LoadLibraryW(name);
        }

        // Get the handle of a module.
        [[nodiscard]] static inline auto Handle(const char *name) noexcept {
            return (ModuleHandle)::GetModuleHandleA(name);
        }
        [[nodiscard]] static inline auto Handle(const wchar_t *name) noexcept {
            return (ModuleHandle)::GetModuleHandleW(name);
        }
    };

    // System
    class System: public Hedron::StaticObject {
        #undef LoadIcon
    public:
        // Get specified system metrics.
        [[nodiscard]] static inline auto GetMetrics(SystemMetrics index) noexcept {
            return ::GetSystemMetrics(index);
        }

        // Load an icon.
        [[nodiscard]] static inline auto LoadIcon(InstanceHandle handle, const char *name) noexcept {
            return (IconHandle)::LoadIconA(handle, name);
        }
        [[nodiscard]] static inline auto LoadIcon(InstanceHandle handle, const wchar_t *name) noexcept {
            return (IconHandle)::LoadIconW(handle, name);
        }
    };

    // Window
    class Window: public Hedron::StaticObject {
    public:
        /// Common
        // Get the current active window.
        [[nodiscard]] static inline auto ActiveWindow() noexcept {
            return (WindowHandle)::GetActiveWindow();
        }
        // Get the current focused window.
        [[nodiscard]] static inline auto FocusedWindow() noexcept {
            return (WindowHandle)::GetFocus();
        }
        // Get the current foreground window.
        [[nodiscard]] static inline auto ForegroundWindow() noexcept {
            return (WindowHandle)::GetForegroundWindow();
        }

        /// Accessors
        // Get the ancestor of window.
        [[nodiscard]] static inline auto GetAncestor(WindowHandle handle, uint32 flags) noexcept {
            return (WindowHandle)::GetAncestor(handle, flags);
        }
        // Get a related window, by command.
        [[nodiscard]] static inline auto GetRelated(WindowHandle handle, uint32 command) noexcept {
            return (WindowHandle)::GetWindow(handle, command);
        }
        // Get the parent window.
        [[nodiscard]] static inline auto GetParent(WindowHandle handle) noexcept {
            return (WindowHandle)::GetParent(handle);
        }

        /// States
        // Check if the current window is active.
        [[nodiscard]] static inline auto Active(WindowHandle handle) noexcept {
            return handle ? handle == ::GetActiveWindow() : false;
        }
        // Check if the current window is focused.
        [[nodiscard]] static inline auto Focused(WindowHandle handle) noexcept {
            return handle ? handle == ::GetFocus() : false;
        }
        // Check if the current window is in the foreground.
        [[nodiscard]] static inline auto Foreground(WindowHandle handle) noexcept {
            return handle ? handle == ::GetForegroundWindow() : false;
        }
    };
}

}

#pragma warning(pop)
