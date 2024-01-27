﻿export module Vite.Renderer.Texture;

export import Vite.Core;
export import Vite.Renderer.Data;

export namespace Hedron {

///
/// Texture Data
///

enum class TextureDimension {
    Texture1D,
    Texture2D,
    Texture3D,
    TextureCube,
};
 
enum class TextureFilter {
    Linear,             // (Bi)Linear Filtering
    LinearMipPoint,     // (Bi)Linear Filtering + MipMapping
    LinearMipLinear,    // (Bi)Linear Filtering + Trilinear Filtering
    Nearest,            // Nearest Neighbor Filtering
    Cubic,              // Cubic Filtering
    Point,              // Point Filtering
    PointMipPoint,      // Point Filtering + MipMapping
    PointMipLinear,     // Point Filtering + Trilinear Filtering
};

enum class TextureFormat {
    R8,
    R16,
    R16F,
    R32F,
    RG8,
    RG16,
    RG16F,
    RG32F,

    RGB8,
    RGBA8,
    RGBA16,
    RGBA16F,
    RGBA32F,

    Depth16,
    Depth24,
    Depth32F,
    Dept24Stencil8,
};

enum class TextureType {
    Undefined,

    Diffuse,
    Normal,
    Specular,

    Height,
    Ambient,
    Emissive,
    Opacity,
    Shininess,
    Displacement,
    Lightmap,
    Reflection,
    Roughness,
    Metallic,
    Occlusion,
};

enum class TextureUsage {
    Attachment,
    Texture,
};

enum class TextureWrap {
    Clamp,          // Clamp To Border
    MirrorClamp,    // Clamp To Edge
    MirrorRepeat,   // Mirrored Repeat
    Repeat,         // Repeated
};

enum class TextureDataType {
    Byte,
    Float,
};

struct TextureProperties {
    uint32 Width = 1;
    uint32 Height = 1;
    TextureFormat Format = TextureFormat::RGBA8;
    TextureDataType DataType = TextureDataType::Byte;

    string Name;

    TextureDimension Dimension = TextureDimension::Texture2D;

    TextureFilter SamplerFilter = TextureFilter::Linear;
    TextureWrap SamplerWrap = TextureWrap::Repeat;

    uint32_t Mips = 1;
    uint32_t Layers = 1;

    bool GenerateMips = false;
};


/// 
/// @brief Agnostic Texture
///
/// @example: How-To
/// auto texture = Texture::Create({512, 512, TextureFormat::RGBA }, file);
/// auto texture = Texture::Create({512, 512, TextureFormat::RGBA }, data, size);
/// 
class Texture {
    /// Default
protected:
    Texture(const TextureProperties &properties, const void *data, size_t size): mProperties(properties), mData(data), mSize(size) {}
public:
    virtual ~Texture() = default;
    static Scope<Texture> Create(const TextureProperties &properties, const void *data, size_t size);
    static Reference<Texture> Create(const TextureProperties &properties, const string &path);

    /// Accessors
    RendererID GetRendererID() const { return mTextureID; }
    const TextureProperties &GetProperties() const { return mProperties; }

    /// Operators
    bool operator==(const Texture &other) const { return mTextureID == other.mTextureID; }

    /// Methods
    virtual void Bind(uint32_t slot = 0) const = 0;
    virtual void Unbind(uint32_t slot = 0) const = 0;

protected:
    /// Properties
    RendererID mTextureID;
    const void *mData;
    TextureProperties mProperties;
    size_t mSize;
};

using Texture2D = Texture;
using Texture3D = Texture;
using TextureCube = Texture;


namespace Helpers {

inline uint32_t GetTextureFormatComponents(TextureFormat self) {
    switch (self) {
        case TextureFormat::R8:
        case TextureFormat::R16:
        case TextureFormat::R16F:
        case TextureFormat::R32F:
        case TextureFormat::Depth16:
        case TextureFormat::Depth24:
        case TextureFormat::Depth32F:
            return 1;
        case TextureFormat::RG8:
        case TextureFormat::RG16:
        case TextureFormat::RG16F:
        case TextureFormat::RG32F:
            return 2;
        case TextureFormat::RGB8:
            return 3;
        case TextureFormat::RGBA8:
        case TextureFormat::RGBA16:
        case TextureFormat::RGBA16F:
        case TextureFormat::RGBA32F:
            return 4;
    }
    return 0;
}

inline uint32_t GetTextureFormatBPP(TextureFormat format) {
    switch (format) {
        case TextureFormat::R8:
            return 1;
        case TextureFormat::R16:
        case TextureFormat::R16F:
        case TextureFormat::RG8:
        case TextureFormat::Depth16:
            return 2;
        case TextureFormat::RGB8:
        case TextureFormat::Depth24:
            return 3;
        case TextureFormat::R32F:
        case TextureFormat::RG16:
        case TextureFormat::RG16F:
        case TextureFormat::RGBA8:
        case TextureFormat::Depth32F:
            return 4;
        case TextureFormat::RG32F:
        case TextureFormat::RGBA16:
        case TextureFormat::RGBA16F:
            return 8;
        case TextureFormat::RGBA32F:
            return 16;
    }
    return 0;
}

inline double CalculateMipCount(uint32_t width, uint32_t height) {
    return std::floor(std::log2(std::min(width, height))) + 1;
}

inline uint32_t GetImageMemorySize(TextureFormat format, uint32_t width, uint32_t height) {
    return width * height * GetTextureFormatBPP(format);
}

inline bool IsDepthFormat(TextureFormat format) {
    switch (format) {
        case TextureFormat::Depth16:
        case TextureFormat::Depth24:
        case TextureFormat::Depth32F:
        case TextureFormat::Dept24Stencil8:
            return true;
    }
    return false;
}

}

}
