module;

#include "Vite/Base/Platform/Detection.h"

// We are not interested in warnings related to DearImGui
#pragma warning(push, 0)

// Graphics Backends
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_vulkan.h>

// System Backends
#ifdef APP_PLATFORM_WINDOWS
    #include <imgui/backends/imgui_impl_win32-patch.h>
#endif

#pragma warning(pop)

export module Vite.DearImGui.Builder;

///
/// @brief Dear ImGui Builder
/// @detail This module contains the needed backends from the library to build.
///
