module;

#pragma warning(push, 0)

#include <imgui/imgui.h>

#pragma warning(pop)

export module Vite.Bridge.DearImGui;

///
/// @brief Bridge: Dear ImGui
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace ImGui {

using namespace ::ImGui;

}
#pragma warning(pop)
