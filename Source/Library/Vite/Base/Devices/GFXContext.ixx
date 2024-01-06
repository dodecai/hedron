export module Vite.Device.GFXContext;

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
/// @brief ContextData | This type is platform specific, look at the implementation for more details.
///
struct ContextData;

///
/// @brief GFXContext | This class is the base class for all graphics contexts.
///
class Context {
public:
    /// Default
    Context() = default;
    virtual ~Context() = default;
    static Reference<Context> Create(void *window);
    static void Destroy();

    /// Methods
    virtual void Load() = 0;
    virtual void Attach() = 0;
    virtual void Detach() = 0;

    /// Accessors
    static const GraphicsAPI GetAPI() { return API; }
    virtual void *GetNativeContext() = 0;
    virtual bool const IsCurrentContext() = 0;

    /// Casts
    template<typename T>
    T *As() {
        return reinterpret_cast<T *>(this);
    }

    /// Mutators
    static void SetAPI(const GraphicsAPI &api) { API = api; }
    virtual void Clear() = 0;
    virtual void SetViewport(uint32 width, uint32 height, int32 x = 0, int32 y = 0) = 0;
    virtual void SetVSync(bool activate) = 0;
    virtual void SwapBuffers() = 0;

public:
    /// Properties
    static GraphicsAPI API;
};

// Global GraphicsAPI Variable
GraphicsAPI Context::API = GraphicsAPI::OpenGL;

}
