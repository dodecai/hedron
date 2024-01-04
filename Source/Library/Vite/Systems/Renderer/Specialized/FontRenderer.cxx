﻿module;

//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include FT_GLYPH_H
//#include FT_BITMAP_H
//
//#undef INFINITE
//#define MSDF_ATLAS_PUBLIC
//#include <msdf-atlas-gen/msdf-atlas-gen.h>
//#include <msdf-atlas-gen/FontGeometry.h>
//#include <msdf-atlas-gen/GlyphGeometry.h>

module Vite.FontRenderer;

import Vite.AssetManager;
import Vite.UIRenderer;

// ToDo: Use Atlas instead of individual textures
namespace Hedron {

//// Helpers
//template<typename T, typename S, int N, msdf_atlas::GeneratorFunction<S, N> GenFunc>
//static Reference<Texture2D> CreateAndCacheAtlas(
//    string_view name,
//    const vector<msdf_atlas::GlyphGeometry> &glyphs,
//    [[maybe_unused]] const msdf_atlas::FontGeometry &fontGeometry,
//    uint32_t width, uint32_t height) {
//
//    msdf_atlas::ImmediateAtlasGenerator<S, N, GenFunc, msdf_atlas::BitmapAtlasStorage<T, N>> generator(width, height);
//    msdf_atlas::GeneratorAttributes attributes;
//    attributes.config.overlapSupport = true;
//    attributes.scanlinePass = true;
//    generator.setAttributes(attributes);
//    generator.setThreadCount(Font::sThreadCount);
//    generator.generate(glyphs.data(), static_cast<int>(glyphs.size()));
//
//    msdfgen::BitmapConstRef<T, N> bitmap = (msdfgen::BitmapConstRef<T, N>)generator.atlasStorage();
//    msdfgen::saveBmp(bitmap, std::format("Data/Cache/Fonts/{}.bmp", name).c_str());
//
//    TextureProperties properties;
//    properties.Format = TextureFormat::RGB8;
//    properties.Width = bitmap.width;
//    properties.Height = bitmap.height;
//    Reference<Texture2D> texture = Texture2D::Create(properties, (void *)bitmap.pixels, bitmap.width * bitmap.height * 3);
//    return texture;
//}
//
//inline uint32_t DecodeUtf8(string_view::iterator &begin, string_view::iterator end) {
//    unsigned char byte = *begin;
//    uint32_t codepoint = 0;
//    int additionalBytes = 0;
//
//    // 1-Byte Character (ASCII)
//    if (byte <= 0x7F) {
//        codepoint = byte;
//    // 2-Byte Character
//    } else if ((byte & 0xE0) == 0xC0) {
//        codepoint = byte & 0x1F;
//        additionalBytes = 1;
//    // 3-Byte Character
//    } else if ((byte & 0xF0) == 0xE0) {
//        codepoint = byte & 0x0F;
//        additionalBytes = 2;
//    // 4-Byte Character
//    } else if ((byte & 0xF8) == 0xF0) {
//        codepoint = byte & 0x07;
//        additionalBytes = 3;
//    // Invalid UTF-8 start byte
//    } else {
//        begin++;
//        return 0xFFFD; // Unicode replacement character
//    }
//
//    begin++;
//
//    while (additionalBytes > 0) {
//        if (begin == end || (*begin & 0xC0) != 0x80) {
//            // Premature end or invalid UTF-8 continuation byte
//            return 0xFFFD; // Unicode replacement character
//        }
//
//        codepoint = (codepoint << 6) | (*begin & 0x3F);
//        begin++;
//        additionalBytes--;
//    }
//
//    return codepoint;
//}
//
//
//Font::Font(string_view name, uint32_t size): mMSDFData(new MSDFData()) {
//    if (!mLibrary) FT_Init_FreeType(&mLibrary);
//    auto path = AssetManager::Instance().Resolve(AssetType::Font, name.data());
//    mData = CreateScope<FontData>();
//
//    if (FT_New_Face(mLibrary, path.c_str(), 0, &mData->Handle)) {
//        LogFatal("Failed to load font '{}' from {}!", name, path);
//        mData.reset();
//        return;
//    }
//    FT_Set_Pixel_Sizes(mData->Handle, 0, size);
//
//    Load(path, size);
//}
//
//Font::~Font() {
//    delete mMSDFData;
//}
//
//
//int Font::GetLineHeight() {
//    return mData->Handle->size->metrics.height >> 6;
//}
//
//Size Font::GetSize(string_view text) {
//    Size size {};
//
//    auto begin = text.begin();
//    auto end = text.end();
//    uint32_t lastGlyph = 0;
//    while (begin != end) {
//        uint32_t codepoint = DecodeUtf8(begin, end);
//        auto *glyph = GetGlyph(codepoint);
//        if (!glyph) {
//            lastGlyph = 0;
//            continue;
//        }
//
//        if (lastGlyph) size.Width += GetKerning(lastGlyph, glyph->UniqueID);
//        lastGlyph = glyph->UniqueID;
//
//        size.Width += glyph->Advance;
//        size.Height = std::max(size.Height, (float)-glyph->Y + 1.0f);
//    }
//    return size;
//}
//
//FontSize Font::GetSizeFull(string_view text) {
//    int x = 0;
//    int y = 0;
//    array<int, 2> lower = { INT_MAX, INT_MAX };
//    array<int, 2> upper = { INT_MIN, INT_MIN };
//
//    auto begin = text.begin();
//    auto end = text.end();
//    uint32_t lastGlyph = 0;
//
//    while (begin != end) {
//        uint32_t codepoint = DecodeUtf8(begin, end);
//        auto *glyph = GetGlyph(codepoint);
//        if (!glyph) {
//            lastGlyph = 0;
//            continue;
//        }
//
//        if (lastGlyph) x += GetKerning(lastGlyph, glyph->UniqueID);
//        lastGlyph = glyph->UniqueID;
//
//        lower[0] = std::min(lower[0], x + glyph->X);
//        lower[1] = std::min(lower[1], y + glyph->Y);
//        upper[0] = std::max(upper[0], x + (glyph->X + glyph->Width));
//        upper[1] = std::max(upper[1], y + (glyph->Y + glyph->Height));
//        x += glyph->Advance;
//    }
//
//    return { (float)lower[0], (float)lower[1], (float)upper[0] - lower[0], (float)upper[1] - lower[1] };
//}
//
//
//Glyph *Font::GetGlyph(uint32_t codepoint) {
//    if (codepoint < 256 && mData->AsciiGlyphs[codepoint]) return mData->AsciiGlyphs[codepoint].get();
//    Glyph *hashed = mData->Glyphs[codepoint].get();
//    if (hashed) return hashed;
//
//    FT_Face face = mData->Handle;
//    int glyph = FT_Get_Char_Index(face, codepoint);
//    if (glyph == 0) return 0;
//    if (FT_Load_Glyph(face, glyph, FT_LOAD_FORCE_AUTOHINT | FT_LOAD_RENDER)) return 0;
//
//    FT_Bitmap const *bitmap = &face->glyph->bitmap;
//    unsigned char const *pBitmap = bitmap->buffer;
//
//    // Create a new glyph and fill out metrics
//    auto g = CreateScope<Glyph>();
//    g->UniqueID = glyph;
//    g->Advance = face->glyph->advance.x >> 6;
//    g->Width = bitmap->width;
//    g->Height = bitmap->rows;
//    g->X = face->glyph->bitmap_left;
//    g->Y = -face->glyph->bitmap_top;
//
//    vector<array<float, 4>> buffer {};
//    buffer.reserve(g->Width * g->Height);
//
//    // Copy rendered bitmap into buffer
//    for (uint32_t dy = 0; dy < bitmap->rows; ++dy) {
//        for (uint32_t dx = 0; dx < bitmap->width; ++dx) {
//            float a = std::pow((float)(pBitmap[dx]) / 255.0f, kRcpGamma);
//            buffer.push_back({ 1.0f, 1.0f, 1.0f, a });
//        }
//        pBitmap += bitmap->pitch;
//    }
//
//    // Upload to texture
//    g->Texture = Texture::Create({ (uint32_t)g->Width, (uint32_t)g->Height, TextureFormat::RGBA16F }, buffer.data(), sizeof(buffer.data()) * sizeof(float));
//
//    // Add to glyph cache
//    auto result = g.get();
//    if (codepoint < 256) {
//        mData->AsciiGlyphs[codepoint] = std::move(g);
//    } else {
//        mData->Glyphs[codepoint] = std::move(g);
//    }
//    return result;
//}
//
//int32_t Font::GetKerning(uint32_t leftGlyph, uint32_t rightGlyph) {
//    FT_Vector kern {};
//    FT_Get_Kerning(mData->Handle, leftGlyph, rightGlyph, FT_KERNING_DEFAULT, &kern);
//    return kern.x >> 6;
//}
//
//
//void Font::Load(string_view path, uint32_t size) {
//    auto cache = std::format("Data/Cache/Fonts/{}.bmp", File::GetName(string(path)));
//    // ToDo: Finish atlas support
//    auto test = false;
//    if (test && File::Exists(cache)) {
//        TextureProperties properties;
//        properties.Format = TextureFormat::RGB8;
//        mAtlasTexture = Texture2D::Create(properties, cache);
//    } else {
//        auto *ft = msdfgen::initializeFreetype();
//        if (!ft) {
//            LogFatal("Failed to initialize FreeType!");
//            return;
//        }
//
//        auto *font = msdfgen::loadFont(ft, path.data());
//        if (!font) {
//            LogFatal("Failed to load MSDF font data from {}!", path);
//            return;
//        }
//
//        mMSDFData->FontGeometry = msdf_atlas::FontGeometry(&mMSDFData->Glyphs);
//        msdf_atlas::Charset charset {};
//        for (auto &range : Font::sCharsetRanges) {
//            for (auto current = range.Begin; current <= range.End; current++) {
//                charset.add(current);
//            }
//        }
//        [[maybe_unused]] auto glyphs = mMSDFData->FontGeometry.loadCharset(font, 1.0, charset);
//
//        // ToDo: Add support for selection MSDF or MTSDF
//        auto coloringSeed = 0ull;
//        if constexpr (sExpensiveColoring) {
//            msdf_atlas::Workload([&glyphs = mMSDFData->Glyphs, &coloringSeed](int i, [[maybe_unused]] int threadNo) -> bool {
//                unsigned long long glyphSeed = (sLCGMultiplier * (coloringSeed ^ i) + sLCGIncrement) * !!coloringSeed;
//                glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, sMaxCornerAngle, glyphSeed);
//                return true;
//            }, static_cast<int>(mMSDFData->Glyphs.size())).finish(sThreadCount);
//        } else {
//            unsigned long long glyphSeed = coloringSeed;
//            for (msdf_atlas::GlyphGeometry &glyph : mMSDFData->Glyphs) {
//                glyphSeed *= sLCGMultiplier;
//                glyph.edgeColoring(msdfgen::edgeColoringInkTrap, sMaxCornerAngle, glyphSeed);
//            }
//        }
//
//        size = 24;
//        msdf_atlas::TightAtlasPacker packer;
//        packer.setDimensionsConstraint(msdf_atlas::TightAtlasPacker::DimensionsConstraint::SQUARE);
//        packer.setMiterLimit(1.0);
//        packer.setPixelRange(2.0);
//        packer.setPadding(0);
//        packer.setScale(size);
//        packer.pack(mMSDFData->Glyphs.data(), static_cast<int>(mMSDFData->Glyphs.size()));
//
//        int width {};
//        int height {};
//        packer.getDimensions(width, height);
//
//        mAtlasTexture = CreateAndCacheAtlas<uint8_t, float, 3, msdf_atlas::msdfGenerator>(
//            File::GetName(string(path)),
//            mMSDFData->Glyphs,
//            mMSDFData->FontGeometry,
//            width,
//            height
//        );
//
//        msdfgen::destroyFont(font);
//        msdfgen::deinitializeFreetype(ft);
//    }
//}
//
//Reference<Font> Font::GetDefault() {
//    static Reference<Font> defaultFont = CreateReference<Font>("Assets/Roboto/Roboto-Regular.ttf", 24);
//    return defaultFont;
//}

}
