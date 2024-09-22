module;

#pragma warning(push, 0)

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

#pragma warning(pop)

export module Vite.Bridge.DearImGui;

///
/// @brief Bridge: Dear ImGui
/// @detail Dear Immediate Mode Graphical User Interface
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace ImGui {

using namespace ::ImGui;

}
#pragma warning(pop)
