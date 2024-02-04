export module Vite.Platform.GLRenderDevice;

import Vite.Renderer.RenderDevice;

export namespace Hedron {

class GLRenderDevice: public RenderDevice {
public:
    /// Default
    GLRenderDevice();
    virtual ~GLRenderDevice();

    /// Mutators
    void DrawingMode(PolygonMode mode) override;

    /// Commands
    void Capture() override;
    void Present() override;
};

}
