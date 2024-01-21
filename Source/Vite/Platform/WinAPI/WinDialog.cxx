module;

#define NOMINMAX
#define VC_EXTRALEAN

#include <Windows.h>

module Vite.Platform.WinDialog;

///
/// Helpers
///
namespace {

#pragma warning(push)
#pragma warning(disable: 4996)

inline std::wstring ConvertChar2WChar(const std::string_view &source) {
    wchar_t buffer[256] = {};
    std::mbstowcs(buffer, source.data(), source.length());
    std::wstring result = buffer;
    return result;
}

inline std::string ConvertWChar2Char(const std::wstring_view &source) {
    char buffer[256] = {};
    std::wcstombs(buffer, source.data(), source.length());
    std::string result = buffer;
    return result;
}

#pragma warning(pop)

}

namespace Hedron {

/// Default
WinDialog::WinDialog(void *window) {
    mWindowHandle = reinterpret_cast<HWND>(window);
}

WinDialog::~WinDialog() {
    mWindowHandle = nullptr;
}


/// Methods
string WinDialog::OpenFile(string_view title, const vector<string> &filter) const {
    // Convert filter to platform specific format
    wstring filters = {};
    for (const auto &f : filter) {
        filters += ConvertChar2WChar(f);
        filters += L'\0';
    }
    wstring nativeTitle = ConvertChar2WChar(title);

    WCHAR szFile[MAX_PATH] { 0 };
    OPENFILENAME dialog = {
        .lStructSize = sizeof(OPENFILENAME),
        .hwndOwner = mWindowHandle,
        .lpstrFilter = filters.c_str(),
        .nFilterIndex = 1,
        .lpstrFile = szFile,
        .nMaxFile = sizeof(szFile),
        .lpstrFileTitle = nativeTitle.data(),
        .nMaxFileTitle = static_cast<DWORD>(nativeTitle.size()),
        .lpstrInitialDir = nullptr,
        .Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR,
    };

    if (GetOpenFileName(&dialog) == TRUE) {
        return ConvertWChar2Char(dialog.lpstrFile);
    }
    return {};
}

string WinDialog::SaveFile(string_view title, const vector<string> &filter) const {
    // Convert filter to platform specific format
    wstring filters = {};
    for (const auto &f : filter) {
        filters += ConvertChar2WChar(f);
        filters += L'\0';
    }
    wstring nativeTitle = ConvertChar2WChar(title);

    WCHAR szFile[MAX_PATH] { 0 };
    OPENFILENAME dialog = {
        .lStructSize = sizeof(OPENFILENAME),
        .hwndOwner = mWindowHandle,
        .lpstrFilter = filters.c_str(),
        .nFilterIndex = 1,
        .lpstrFile = szFile,
        .nMaxFile = sizeof(szFile),
        .lpstrFileTitle = nativeTitle.data(),
        .nMaxFileTitle = static_cast<DWORD>(nativeTitle.size()),
        .lpstrInitialDir = nullptr,
        .Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR,
    };
    if (GetSaveFileName(&dialog) == TRUE) {
        return ConvertWChar2Char(dialog.lpstrFile);
    }
    return {};
}

}
