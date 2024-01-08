module;

#pragma warning(push, 0)

#include <assimp/Importer.hpp>

#pragma warning(pop)

export module Vite.Bridge.Assimp;

///
/// @brief Bridge: Assimp Library
/// @detail Open Asset Importer Library
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace Assimp {

using namespace ::Assimp;

}
#pragma warning(pop)
