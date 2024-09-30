module;

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "uxtheme.lib")

#define NOCOMM
#define NODRAWTEXT
#define NOMENUS
#define NOMCX
#define NOMINMAX
#define NOHELP
#define NOSERVICE
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#pragma warning(push, 0)

#include <DwmApi.h>
#include <shellapi.h>
#include <ShlObj_core.h>
#include <Windows.h>
#include <WindowsX.h>
#include <commdlg.h>

#pragma warning(pop)

export module Vite.Bridge.WinAPI;

import Vite.Extension;
import Vite.Math.Geometry;
import Vite.Type;

///
/// @brief Bridge: Windows API
/// @detail Windows Application Programming Interface
/// @note The export is reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

export namespace WinAPI {

///
/// Types
///
using DeviceContextHandle = ::HDC;
using GenericHandle = ::HANDLE;
using InstanceHandle = ::HINSTANCE;
using ModuleHandle = ::HMODULE;
using WindowHandle = ::HWND;

/// Function Wrappers

class Error: Hedron::StaticObject {
public:
    /// Default
    [[nodiscard]] static inline string Message() noexcept {
        DWORD errorCode = ::GetLastError();
        if (errorCode == 0) return {};

        LPSTR messageBuffer = nullptr;
        size_t size = ::FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            errorCode,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&messageBuffer),
            0,
            nullptr
        );
        string message(messageBuffer, size);
        ::LocalFree(messageBuffer);
        return message;
    }
};

class Window: Hedron::StaticObject {
public:
    /// Default
    
    [[no_discard]] static inline WindowHandle Create(const string &title, const Hedron::Position2D &position, const Hedron::Size2D &size) {
        return ::CreateWindowExA(
            0,
            "Hedron",
            title.c_str(),
            static_cast<DWORD>(0),
            static_cast<int>(position.X),
            static_cast<int>(position.Y),
            static_cast<int>(size.Width),
            static_cast<int>(size.Height),
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );
    }

    [[no_discard]] static inline WindowHandle Create(const wstring &title, const Hedron::Position2D &position, const Hedron::Size2D &size) {
        return ::CreateWindowExW(
            0,
            L"Hedron",
            title.c_str(),
            static_cast<DWORD>(0),
            static_cast<int>(position.X),
            static_cast<int>(position.Y),
            static_cast<int>(size.Width),
            static_cast<int>(size.Height),
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );
    }

    /// Commands

    static inline void Close(WindowHandle window) noexcept {
        ::CloseWindow(window);
    }

    static inline void Destroy(WindowHandle window) noexcept {
        ::DestroyWindow(window);
    }

    static inline void Hide(WindowHandle window) noexcept {
        ::ShowWindow(window, SW_HIDE);
    }

    static inline void Maximize(WindowHandle window) noexcept {
        ::ShowWindow(window, SW_MAXIMIZE);
    }

    static inline void Minimize(WindowHandle window) noexcept {
        ::ShowWindow(window, SW_MINIMIZE);
    }

    static inline void Restore(WindowHandle window) noexcept {
        ::ShowWindow(window, SW_RESTORE);
    }

    static inline void Show(WindowHandle window) noexcept {
        ::ShowWindow(window, SW_SHOW);
    }

    /// Accessors

    [[no_discard]] static inline Hedron::Size2D ContentSize(WindowHandle window) noexcept {
        RECT rect;
        ::GetClientRect(window, &rect);
        return Hedron::Size2D { static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top) };
    }

    [[no_discard]] static inline Hedron::Position2D Position(WindowHandle window) noexcept {
        RECT rect;
        ::GetWindowRect(window, &rect);
        return Hedron::Position2D { static_cast<float>(rect.left), static_cast<float>(rect.top) };
    }

    [[no_discard]] static inline Hedron::Size2D Size(WindowHandle window) noexcept {
        RECT rect;
        ::GetWindowRect(window, &rect);
        return Hedron::Size2D { static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top) };
    }

    /// Mutators

    static inline void SetActive(WindowHandle window) noexcept {
        ::SetActiveWindow(window);
    }

    static inline void SetFocus(WindowHandle window) noexcept {
        ::SetFocus(window);
    }

    static inline void SetTitle(WindowHandle window, const string &title) noexcept {
        ::SetWindowTextA(window, title.c_str());
    }

    static inline void SetTitle(WindowHandle window, const wstring &title) noexcept {
        ::SetWindowTextW(window, title.c_str());
    }
};

}
