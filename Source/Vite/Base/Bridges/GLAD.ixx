module;

#pragma warning(push, 0)

namespace gl {

#include <glad/gl.h>

}

#pragma warning(pop)

export module Vite.Bridge.Glad;

///
/// @brief Bridge: GLAD Library
/// @detail GL Loader-Generator
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export {

using namespace ::gl;

}
#pragma warning(pop)
