module;

#pragma warning(push, 0)

namespace ft {

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_GLYPH_H

}

#pragma warning(pop)

export module Vite.Bridge.FreeType;

///
/// @brief Bridge: FreeType Library
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace ft {

using namespace ::ft;

}
#pragma warning(pop)
