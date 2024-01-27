export module Vite.Renderer.Swapchain;

export import Vite.Core;
export import Vite.Renderer.Data;

export import Vite.Renderer.Texture;

export namespace Hedron {

/// 
/// @brief Agnostic Swapchain
///
class Swapchain {
    /// Default
protected:
    Swapchain() = default;
public:
    virtual ~Swapchain() = default;
    static Scope<Swapchain> Create(const Size2D &size);

    /// Accessors
    virtual Reference<Texture> CurrentImage() = 0;
    virtual RendererID CurrentImageIndex() = 0;

    /// Methods
    virtual void Present() = 0;
    virtual void Resize(float width, float height) = 0;
};

}
