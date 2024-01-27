export module Vite.Platform.GLCommandBuffer;

import Vite.Renderer.CommandBuffer;

export namespace Hedron {

class GLCommandBuffer: public CommandBuffer {
public:
    /// Default
    GLCommandBuffer();
    virtual ~GLCommandBuffer();

    /// Mutators
    void Clear(float r, float g, float b, float a) override;
    void Viewport(float x, float y, float width, float height) override;

    /// Methods
    void Begin() override;
    void End() override;
    void Execute() override;
    void Record(const function<void()> &callback) override;

private:
    /// Test
    void Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) override;
    void DrawIndexed(uint32 indexCount, uint32 instanceCount, uint32 firstIndex, int32 vertexOffset, uint32 firstInstance) override;
    void DrawIndexed(size_t count, PrimitiveType type, bool depthTest = true) override;
    void UpdateStencilBuffer() override;
    void EnableStencilTest() override;
    void ResetStencilTest() override;
};

}
