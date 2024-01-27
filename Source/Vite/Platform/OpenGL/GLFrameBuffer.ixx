export module Vite.Platform.GLFramebuffer;

import Vite.Renderer.Framebuffer;

export namespace Hedron {

class GLFramebuffer: public Framebuffer {
public:
    /// Default
    GLFramebuffer(const FramebufferProperties &properties);
    virtual ~GLFramebuffer();

    /// Accessors
    Reference<Texture> ColorAttachment() const override;
    Reference<Texture> DepthAttachment() const override;

    /// Methods
    void Bind() const override;
    void Unbind() const override;
};

}
