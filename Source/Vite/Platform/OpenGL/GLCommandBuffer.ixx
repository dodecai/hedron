export module Vite.Platform.GLCommandBuffer;

import Vite.Renderer.CommandBuffer;

export namespace Hedron {

class GLCommandBuffer: public CommandBuffer {
public:
    /// Default
    GLCommandBuffer();
    virtual ~GLCommandBuffer();

    /// Commands
    void Capture() override;
    void Clear(const Color &color) override;
    void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) override;
    void DrawIndexed(size_t count, PrimitiveType type, bool depthTest = true) override;
    void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, int32 vertexOffset, uint32 firstInstance) override;
    void UpdateStencilBuffer() override;
    void Execute() override;
    void Record(const function<void()> &callback) override;
    void Viewport(const Position2D &position, const Size2D &size) override;

private:
    /// Test
    void EnableStencilTest() override;
    void ResetStencilTest() override;
};

}
