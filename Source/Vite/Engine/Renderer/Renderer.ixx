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

    /// Accessors
    bool Capturing() const { return mCapturing; }
    bool Presenting() const { return mPresenting; }

    /// Commands
    void Capture();
    void DrawIndexed();
    void Present();

    /// Debug
    Scope<CommandBuffer> &GetCommandBuffer() { return mCommandBuffer; }

private:
    /// Properties
    Scope<RenderDevice> mRenderDevice;
    Scope<CommandBuffer> mCommandBuffer;
    Scope<Swapchain> mSwapchain;

    /// States
    atomic<bool> mCapturing = false;
    atomic<bool> mPresenting = false;
};

}
