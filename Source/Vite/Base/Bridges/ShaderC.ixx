module;

#pragma warning(push, 0)

#include <shaderc/shaderc.hpp>

#pragma warning(pop)

export module Vite.Bridge.ShaderC;

///
/// @brief Bridge: ShaderC
/// @detail Shader Compiler Library
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace shaderc {

using namespace ::shaderc;

}
#pragma warning(pop)
