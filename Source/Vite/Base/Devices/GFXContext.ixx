export module Vite.Device.GFXContext;

import Vite.Math;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Graphics API's [DirectX|OpenGL|Vulkan]
///
enum class GraphicsAPI {
    DirectX,
    OpenGL,
    Vulkan,
};

///
/// @brief ContextData: This type is platform specific, look at the implementation for more details.
///
struct ContextData;

///
/// @brief GFXContext | This class is the base class for all graphics contexts.
///
class GFXContext {
    /// Friends
    friend class Application;
    friend class DearImGuiLayer;

public:
    /// Default
    GFXContext() = default;
    virtual ~GFXContext() = default;
    static Scope<GFXContext> Create(void *window);

    /// Controls
    // Attaches the context to the current thread.
    virtual void Attach() = 0;
    // Detaches the context from the current thread.
    virtual void Detach() = 0;
    // Clears the context for the next frame.
    virtual void Clear() = 0;
    // Swaps the buffers for the next frame.
    virtual void SwapBuffers() = 0;
    // Updates the viewport of the context.
    virtual void Viewport(const Size2D &size, const Position2D &position = {}) = 0;
    // Enables or disables vertical sync.
    virtual void VSync(bool activate) = 0;

    /// States
    // Checks if the context is the current context.
    virtual bool const CurrentContext() = 0;

protected:
    /// Casts
    // Casts the context to specified derived type.
    template<typename T>
    T *As() {
        static_assert(std::is_base_of_v<GFXContext, T>, "Context: T must be derived!");
        return reinterpret_cast<T *>(this);
    }
    // Retrieves the platform specific handle.
    virtual void *AsPlatformHandle() = 0;

public:
    /// Properties
    // Needs to be set before creating a context.
    inline static GraphicsAPI API = GraphicsAPI::OpenGL;
};

}
