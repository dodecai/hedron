module;

#pragma warning(push, 0)

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define VC_EXTRALEAN
#include <ShObjIdl.h>
#include <Windows.h>

#pragma warning(pop)

export module Vite.Bridge.WinAPI;

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
using ::LRESULT;
using ::UINT;
using ::WPARAM;
using ::LPARAM;
using ::ITaskbarList3;

namespace WinAPI {
    [[nodiscard]] inline HICON LoadIconA(HINSTANCE hInstance, const char *lpIconName) noexcept {
        return ::LoadIconA(hInstance, lpIconName);
    }

    [[nodiscard]] inline HICON LoadIconW(HINSTANCE hInstance, const wchar_t* lpIconName) noexcept {
        return ::LoadIconW(hInstance, lpIconName);
    }

    [[nodiscard]] inline HMODULE LoadLibraryA(const char *lpLibFileName) noexcept {
        return ::LoadLibraryA(lpLibFileName);
    }

    [[nodiscard]] inline HMODULE LoadLibraryW(const wchar_t* lpLibFileName) noexcept {
        return ::LoadLibraryW(lpLibFileName);
    }

    [[nodiscard]] inline HINSTANCE GetModuleHandleA(const char *lpModuleName) noexcept {
        return ::GetModuleHandleA(lpModuleName);
    }

    [[nodiscard]] inline HMODULE GetModuleHandleW(const wchar_t *lpModuleName) noexcept {
        return ::GetModuleHandleW(lpModuleName);
    }



    [[nodiscard]] inline HWND GetActiveWindow() noexcept {
        return ::GetActiveWindow();
    }

    [[nodiscard]] inline HWND GetAncestor(HWND hWnd, unsigned int gaFlags) noexcept {
        return ::GetAncestor(hWnd, gaFlags);
    }

    [[nodiscard]] inline HWND GetFocus() noexcept {
        return ::GetFocus();
    }

    [[nodiscard]] inline HWND GetForegroundWindow() noexcept {
        return ::GetForegroundWindow();
    }

    [[nodiscard]] inline HWND GetParent(HWND hWnd) noexcept {
        return ::GetParent(hWnd);
    }

    [[nodiscard]] inline HWND GetWindow(HWND hWnd, unsigned int uCmd) noexcept {
        return ::GetWindow(hWnd, uCmd);
    }
}

}
#pragma warning(pop)
