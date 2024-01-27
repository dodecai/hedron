export module Vite.Platform.GLSwapchain;

import Vite.Renderer.Swapchain;

export namespace Hedron {

class GLSwapchain: public Swapchain {
public:
    /// Default
    GLSwapchain(const Size2D &size);
    virtual ~GLSwapchain();

    /// Accessors
    virtual Reference<Texture> CurrentImage() override;
    virtual RendererID CurrentImageIndex() override;

    /// Methods
    virtual void Present() override;
    virtual void Resize(float width, float height) override;
};

}
