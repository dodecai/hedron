module Vite.Renderer.CommandBuffer;

import Vite.Device.GFXContext;
//import Vite.Platform.DXCommandBuffer;
import Vite.Platform.GLCommandBuffer;
//import Vite.Platform.VKCommandBuffer;

namespace Hedron {

///
/// Default
///
Scope<CommandBuffer> CommandBuffer::Create() {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXCommandBuffer>(); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLCommandBuffer>(); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKCommandBuffer>(); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
