export module Vite.Renderer.CommandBuffer;

import Vite.Core;

import Vite.Renderer.Data;
//import Vite.Renderer.Buffer;
//import Vite.Renderer.Framebuffer;
//import Vite.Renderer.PipelineState;
import Vite.Renderer.RenderDevice;
//import Vite.Renderer.Shader;
//import Vite.Renderer.Texture;

export namespace Hedron {

/// 
/// @brief Agnostic CommandBuffer
/// 
/// @example: How-To
/// auto commands = CommandBuffer::Create();
/// 
/// commands->Begin();
/// ... Record Commands (e.g. SetViewPort, bind Shaders, Buffers, PipelineStates, etc)
/// commands->End();
/// commands->Execute();
///
class CommandBuffer {
public:
    /// Default
    CommandBuffer() = default;
    virtual ~CommandBuffer() = default;
    static Scope<CommandBuffer> Create();

    /// Commands
    virtual void Capture() = 0;
    virtual void Clear(const Color &color) = 0;
    virtual void Draw(uint32 vertexCount, uint32 instanceCount = 0, uint32 firstVertex = 0, uint32 firstInstance = 0) = 0;
    virtual void DrawIndexed(size_t count, PrimitiveType type, bool depthTest = true) = 0;
    virtual void DrawIndexed(uint32 indexCount, uint32 instanceCount = 0, uint32 firstIndex = 0, int32 vertexOffset = 0, uint32 firstInstance = 0) = 0;
    virtual void Execute() = 0;
    virtual void Record(const function<void()> &callback) = 0;
    virtual void Viewport(const Position2D &position, const Size2D &size) = 0;

protected:
    /// Test
    virtual void EnableStencilTest() = 0;
    virtual void UpdateStencilBuffer() = 0;
    virtual void ResetStencilTest() = 0;
    //virtual void BindRenderState(const Scope<RenderState> &renderState) = 0;
    //virtual void BindShader(const Scope<Shader> &shader) = 0;
    //virtual void BindVertexBuffer(const Scope<Buffer> &vertexBuffer) = 0;
    //virtual void BindIndexBuffer(const Scope<Buffer> &indexBuffer) = 0;
    //virtual void BindFramebuffer(const Scope<Framebuffer> &framebuffer) = 0;

protected:
    /// Properties
    vector<function<void()>> mCommands;
};

}
