module;

#pragma warning(push, 0)

namespace stb {

#include <stb/stb_image.h>

}

#pragma warning(pop)

export module Vite.Bridge.STB;

///
/// @brief Bridge: STB Library
/// @detail Sean Barrett's ToolBox
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace stb {

using namespace ::stb;

}
#pragma warning(pop)
