export module Vite.Renderer;

import Vite.Core;
export import Vite.Renderer.Data;
export import Vite.Renderer.CommandBuffer;
export import Vite.Renderer.PipelineState;
export import Vite.Renderer.RenderDevice;
export import Vite.Renderer.Swapchain;

export namespace Hedron {

/// 
/// @brief Agnostic Renderer
/// 
/// @example: How-To
/// auto renderer = Renderer::Create();
/// while (...) { renderer->RenderFrame();
///
class Renderer {
    /// Default
protected:
    Renderer() = default;
public:
    virtual ~Renderer() = default;
    static Scope<Renderer> Create();

    /// Methods
    void BeginScene();
    void EndScene();
    void RenderScene();

protected:
    /// Accessors
    // Retrieve the command buffer (only for debugging purposes)
    const CommandBuffer *GetCommandBuffer() const { return mCommandBuffer.get(); }

protected:
    /// Properties
    Scope<RenderDevice> mRenderDevice;
    Scope<CommandBuffer> mCommandBuffer;
    Scope<Swapchain> mSwapchain;
};

}
