#pragma once

///
/// @brief Bridge: Windows API Header
/// @detail Windows Application Programming Interface
///

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
