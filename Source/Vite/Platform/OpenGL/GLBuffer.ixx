export module Vite.Platform.GLBuffer;

import Vite.Renderer.Buffer;

export namespace Hedron {

class GLBuffer: public Buffer {
public:
    /// Default
    GLBuffer(BufferType type, const void *data, size_t size, BufferUsage usage);
    virtual ~GLBuffer() override;

    /// Mutators
    virtual void UpdateData(const void *data, size_t size) override;

    /// Methods
    virtual void Bind() const override;
    virtual void Bind(uint32 binding) const override;
    virtual void Unbind() const override;

private:
    /// Properties
    unsigned int mNativeType;
};

}
