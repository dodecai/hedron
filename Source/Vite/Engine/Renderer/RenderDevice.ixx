export module Vite.Renderer.RenderDevice;

export import Vite.Core;
export import Vite.Renderer.Data;

export namespace Hedron {

/// 
/// @brief Agnostic RenderDevice
///
class RenderDevice {
    /// Default
protected:
    RenderDevice() = default;
public:
    virtual ~RenderDevice() = default;
    static Scope<RenderDevice> Create();

    /// Accessors
    static RendererProperties &Properties() {
        static RendererProperties properties;
        return properties;
    }

    /// Mutators
    virtual void DrawingMode(PolygonMode mode = PolygonMode::Solid) = 0;
};

}
