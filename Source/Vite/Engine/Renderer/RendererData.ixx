export module Vite.Renderer.Data;

import Vite.Core;

export namespace Hedron {

///
/// @brief RendererID: Unique identifier for a renderer object
///
using RendererID = uint32;


///
/// @brief Blend Mode [Additive|Alpha|Disabled|Multiply]
///
enum class BlendMode {
    Additive,
    Alpha,
    Disabled,
    Multiply,   // PreMultiplyAlpha
};


///
/// @brief Cull Mode [None|Back|Front|BackAndFront]
///
enum class CullMode {
    None,
    Back,
    Front,
    BackAndFront,
};


///
/// @brief Front Face [CCW|CW]
///
enum class FrontFace {
    CCW,
    CW,
};


///
/// @brief Primitive Type [Triangle|TriangleStrip|Line|LineStrip|Point|Quad]
///
enum class PrimitiveType {
    Triangle,
    TriangleStrip,
    Line,
    LineStrip,
    Point,
    Quad,
};


///
/// @brief Polygon Mode [Solid|Wireframe]
///
enum class PolygonMode {
    Solid,
    Vertices,
    Wireframe,
};


///
/// @brief Renderer Properties
///
struct RendererProperties {
    string Vendor;
    string Model;
    string Version;
    string SLVersion;
    vector<string> Extensions;

    float MaxAnisotropy = 0.0f;
    int MaxSamples = 0;
    int MaxTextureUnits = 0;

    void Log() {
        //LogInfo("[Renderer] Vendor:  '{}'", Vendor);
        //LogInfo("[Renderer] Model:   '{}'", Model);
        //LogInfo("[Renderer] Version: '{}'", Version);
        //LogDebug("[Renderer] Shader Version: '{}'", SLVersion);
        //LogTrace("[Renderer] Max Anisotropy: '{}'", MaxAnisotropy);
        //LogTrace("[Renderer] Max Samples:     '{}'", MaxSamples);
        //LogTrace("[Renderer] Max TextureUnits: '{}'", MaxTextureUnits);

    }
    void ShowExtensions() {
        //LogTrace("[Renderer] Extensions: ...");
        //for (const auto &extension : Extensions) {
        //    LogTrace("... : '", extension);
        //}
    }
};

}
