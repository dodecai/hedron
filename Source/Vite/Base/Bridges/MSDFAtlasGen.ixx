module;

#undef INFINITE
#define MSDF_ATLAS_PUBLIC

#pragma warning(push, 0)

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H
#include FT_GLYPH_H

#include <msdf-atlas-gen/msdf-atlas-gen.h>
#include <msdf-atlas-gen/FontGeometry.h>
#include <msdf-atlas-gen/GlyphGeometry.h>

#pragma warning(pop)

export module Vite.Bridge.MsdfAtlasGen;

import Vite.Type.SmartPointer;
import Vite.Type.Standard;
import Vite.Renderer.Texture;

///
/// @brief Bridge: MSDFGen | MSDF-Atlas-Gen Library
/// @detail Multi-channel Signed Distance Field [Atlas] Generator
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)

export namespace msdfgen {

using namespace ::msdfgen;

/// Helpers
inline FontHandle *loadVarFont(FreetypeHandle *library, const char *filename) {
    std::string buffer;
    while (*filename && *filename != '?') buffer.push_back(*filename++);
    FontHandle *font = loadFont(library, buffer.c_str());
    if (font && *filename++ == '?') {
        do {
            buffer.clear();
            while (*filename && *filename != '=')
                buffer.push_back(*filename++);
            if (*filename == '=') {
                double value = 0;
                int skip = 0;
                if (sscanf(++filename, "%lf%n", &value, &skip) == 1) {
                    setFontVariationAxis(library, font, buffer.c_str(), value);
                    filename += skip;
                }
            }
        } while (*filename++ == '&');
    }
    return font;
}

}

export namespace msdf_atlas {

using namespace ::msdf_atlas;

/// Helpers
template<typename T, typename S, int N, GeneratorFunction<S, N> GenFunc>
inline Hedron::Reference<Hedron::Texture2D> CreateAndCacheAtlas(
    string_view name,
    float size,
    const vector<GlyphGeometry> &glyphs,
    const FontGeometry &fontGeometry,
    uint32_t width, uint32_t height) {

    ImmediateAtlasGenerator<S, N, GenFunc, BitmapAtlasStorage<T, N>> generator(width, height);
    GeneratorAttributes attributes;
    attributes.config.overlapSupport = true;
    attributes.scanlinePass = true;
    generator.setAttributes(attributes);
    //generator.setThreadCount(Font::sThreadCount);
    generator.generate(glyphs.data(), static_cast<int>(glyphs.size()));

    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
    msdfgen::saveBmp(bitmap, std::format("Data/Cache/Fonts/{}.bmp", name).c_str());

    Hedron::TextureProperties properties;
    properties.Format = Hedron::TextureFormat::RGB8;
    properties.GenerateMips = false;
    properties.Width = bitmap.width;
    properties.Height = bitmap.height;
    Hedron::Reference<Hedron::Texture2D> texture = Hedron::Texture2D::Create(properties, (void *)bitmap.pixels, bitmap.width * bitmap.height * 3);
    return texture;
}

}

#pragma warning(pop)
