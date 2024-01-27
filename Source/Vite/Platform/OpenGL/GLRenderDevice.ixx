export module Vite.Platform.GLRenderDevice;

import Vite.Renderer.RenderDevice;

export namespace Hedron {

class GLRenderDevice: public RenderDevice {
public:
    /// Default
    GLRenderDevice();
    virtual ~GLRenderDevice();

    /// Mutators
    virtual void DrawingMode(PolygonMode mode) override;
};

}
