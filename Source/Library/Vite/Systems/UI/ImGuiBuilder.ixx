///
/// @brief This module contains the needed backends from DearImGui
///

module;

#include "Vite/Base/Platform/Detection.h"

export module Vite.ImGuiBuilder;

// We are not interested in warnings related to DearImGui
#pragma warning(push, 0)

// Graphics Backends
export import <imgui/backends/imgui_impl_opengl3.h>;
export import <imgui/backends/imgui_impl_vulkan.h>;

// System Backends
#ifdef APP_PLATFORM_WINDOWS
    export import <imgui/backends/imgui_impl_win32-patch.h>;
#endif

#pragma warning(pop)

export namespace Hedron {}
