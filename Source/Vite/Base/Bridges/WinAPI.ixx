module;

#pragma warning(push, 0)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define VC_EXTRALEAN
#include <ShObjIdl.h>
#include <Windows.h>

#pragma warning(pop)

export module Vite.Bridge.WinAPI;

import Vite.Extension;

///
/// @brief Bridge: Windows API
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export {

using ::HINSTANCE;
using ::HICON;
using ::HMODULE;
using ::HWND;
using ::LPARAM;
using ::LRESULT;
using ::UINT;
using ::WPARAM;


namespace WinAPI {
    ///
    /// Data
    ///
    // Constants
    constexpr auto gEnumerateCurrentSettings = ENUM_CURRENT_SETTINGS;
    constexpr auto gEnumerateRegistrySettings = ENUM_REGISTRY_SETTINGS;

    // Enumerations
    enum class DisplayDeviceState: DWORD {
        Active = DISPLAY_DEVICE_ACTIVE,
        Attached = DISPLAY_DEVICE_ATTACHED_TO_DESKTOP,
        Primary = DISPLAY_DEVICE_PRIMARY_DEVICE,
        Remote = DISPLAY_DEVICE_REMOTE,
    };

    enum class SystemMetrics: int {
        ScreenCount = SM_CMONITORS,
        ScreenX = SM_CXSCREEN,
        ScreenY = SM_CYSCREEN,
    };

    // Types
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

    // Display
    #undef EnumDisplayDevices
    [[nodiscard]] inline auto EnumDisplayDevices(LPCWSTR lpDevice, DWORD iDevEnum, DISPLAY_DEVICE *lpDisplayDevice, DWORD dwFlags) noexcept {
        return ::EnumDisplayDevicesW(lpDevice, iDevEnum, lpDisplayDevice, dwFlags);
    }

    [[nodiscard]] inline auto EnumDisplayMonitors(HDC hdc, LPRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData) {
        return ::EnumDisplayMonitors(hdc, lprcClip, lpfnEnum, dwData);
    }

    #undef EnumDisplaySettings
    [[nodiscard]] inline auto EnumDisplaySettings(LPCWSTR deviceName, DWORD iModeNum, DEVMODE *lpDevMode) noexcept {
        return ::EnumDisplaySettingsW(deviceName, iModeNum, lpDevMode);
    }

    #undef GetMonitorInfo
    [[nodiscard]] inline auto GetMonitorInfo(HMONITOR hMonitor, MONITORINFOEX *lpmi) noexcept {
        return ::GetMonitorInfoW(hMonitor, lpmi);
    }

    // Icon
    #undef LoadIcon
    [[nodiscard]] inline auto LoadIcon(HINSTANCE hInstance, LPCSTR lpIconName) noexcept {
        return ::LoadIconA(hInstance, lpIconName);
    }

    [[nodiscard]] inline auto LoadIcon(HINSTANCE hInstance, LPCWSTR lpIconName) noexcept {
        return ::LoadIconW(hInstance, lpIconName);
    }

    // Library
    #undef LoadLibrary
    [[nodiscard]] inline auto LoadLibrary(LPCSTR lpLibFileName) noexcept {
        return ::LoadLibraryA(lpLibFileName);
    }

    [[nodiscard]] inline auto LoadLibrary(LPCWSTR lpLibFileName) noexcept {
        return ::LoadLibraryW(lpLibFileName);
    }

    #undef GetModuleHandle
    [[nodiscard]] inline auto GetModuleHandle(LPCSTR lpModuleName) noexcept {
        return ::GetModuleHandleA(lpModuleName);
    }

    [[nodiscard]] inline auto GetModuleHandle(LPCWSTR lpModuleName) noexcept {
        return ::GetModuleHandleW(lpModuleName);
    }

    // System
    [[nodiscard]] inline auto GetSystemMetrics(int nIndex) noexcept {
        return ::GetSystemMetrics(nIndex);
    }

    // Window
    [[nodiscard]] inline auto GetActiveWindow() noexcept {
        return ::GetActiveWindow();
    }

    [[nodiscard]] inline auto GetAncestor(HWND hWnd, UINT gaFlags) noexcept {
        return ::GetAncestor(hWnd, gaFlags);
    }

    [[nodiscard]] inline auto GetFocus() noexcept {
        return ::GetFocus();
    }

    [[nodiscard]] inline auto GetForegroundWindow() noexcept {
        return ::GetForegroundWindow();
    }

    [[nodiscard]] inline auto GetParent(HWND hWnd) noexcept {
        return ::GetParent(hWnd);
    }

    [[nodiscard]] inline auto GetWindow(HWND hWnd, UINT uCmd) noexcept {
        return ::GetWindow(hWnd, uCmd);
    }
}

}

#pragma warning(pop)
