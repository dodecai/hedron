export module Vite.Renderer.Framebuffer;

export import Vite.Core;
export import Vite.Renderer.Texture;

export namespace Hedron {

/// 
/// @brief Framebuffer Properties
///
struct FramebufferProperties {
    Size2D Size = {};
    vector<TextureFormat> Attachments = { TextureFormat::RGBA32F };

    uint32 Samples = 1;
    float Scale = 1.0f;
    string Name = {};
};


/// 
/// @brief Agnostic Framebuffer
///
/// @example: How-To
/// auto framebuffer = Framebuffer::Create({ 1024, 768, TextureFormat::RGBA });
/// 
class Framebuffer {
    /// Default
protected:
    Framebuffer() = default;
public:
    virtual ~Framebuffer() = default;
    static Scope<Framebuffer> Create(const FramebufferProperties &properties);

    /// Accessors
    virtual Reference<Texture> ColorAttachment() const = 0;
    virtual Reference<Texture> DepthAttachment() const = 0;

    /// Methods
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

protected:
    /// Properties
    RendererID mFramebufferID;
    RendererID mColorTextureID;
    RendererID mDepthTextureID;
};

}
