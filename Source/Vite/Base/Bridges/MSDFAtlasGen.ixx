module;

#pragma warning(push, 0)

#undef INFINITE
#define MSDF_ATLAS_PUBLIC
#include <msdf-atlas-gen/msdf-atlas-gen.h>
#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>

#pragma warning(pop)

export module Vite.Bridge.MsdfAtlasGen;

///
/// @brief Bridge: MSDFGen | MSDF-Atlas-Gen Library
/// @detail Multi-channel Signed Distance Field [Atlas] Generator
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace msdfgen {

using namespace ::msdfgen;

}
#pragma warning(pop)
