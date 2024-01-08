module;

#pragma warning(push, 0)

#include <entt/entt.hpp>

#pragma warning(pop)

export module Vite.Bridge.EnTT;

///
/// @brief Bridge: EnTT Library
/// @detail Entity Component System Library
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace entt {

using namespace ::entt;

}
#pragma warning(pop)
