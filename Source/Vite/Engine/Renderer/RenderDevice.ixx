export module Vite.Renderer.RenderDevice;

export import Vite.Core;
export import Vite.Renderer.Data;
import Vite.Renderer.Buffer;

export namespace Hedron {

/// 
/// @brief Agnostic RenderDevice
///
class RenderDevice {
public:
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
    // Set the drawing mode [Solid|Vertices|Wireframe]
    virtual void DrawingMode(PolygonMode mode = PolygonMode::Solid) = 0;

    /// Commands
    // Starts a new frame
    virtual void Capture() = 0;
    // Finishes the frame
    virtual void Present() = 0;

protected:
    /// Casts
    // Casts the context to specified derived type.
    template<typename T>
    T *As() {
        static_assert(std::is_base_of_v<RenderDevice, T>, "RenderDevice: T must be derived!");
        return reinterpret_cast<T *>(this);
    }
};

}
