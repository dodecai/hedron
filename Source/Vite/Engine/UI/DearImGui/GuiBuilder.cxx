module;

#include "Vite/Base/Platform/Detection.h"

// Properties
#define IMGUI_IMPL_OPENGL_LOADER_GLAD2

// Graphics Backends
#include <imgui/../../source/backends/imgui_impl_opengl3.cpp>
#include <imgui/../../source/backends/imgui_impl_vulkan.cpp>

// System Backends
#ifdef APP_PLATFORM_WINDOWS
    #include <imgui/../../source/backends/imgui_impl_win32-patch.cpp>
#endif

module Vite.DearImGui.Builder;
