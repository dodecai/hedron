export module Vite.Device.GFXContext;

import Vite.Math;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Supported Graphics API's [DirectX|OpenGL|Vulkan]
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

public:
    /// Default
    GFXContext() = default;
    virtual ~GFXContext() = default;
    static Scope<GFXContext> Create(void *window);

    /// Controls
    virtual void Attach() = 0;
    virtual void Detach() = 0;
    virtual void Clear() = 0;
    virtual void SwapBuffers() = 0;
    virtual void Viewport(const Size2D &size, const Position2D &position = {}) = 0;
    virtual void VSync(bool activate) = 0;

    /// States
    virtual bool const CurrentContext() = 0;

protected:
    /// Casts
    template<typename T>
    T *As() {
        static_assert(std::is_base_of_v<GFXContext, T>, "Context: T must be derived!");
        return reinterpret_cast<T *>(this);
    }
    virtual void *AsPlatformHandle() = 0;

public:
    /// Properties
    // Needs to be set before creating a context.
    inline static GraphicsAPI API = GraphicsAPI::OpenGL;
};

}
