module Vite.Renderer.RenderDevice;

import Vite.Device.GFXContext;
//import Vite.Platform.DXRenderDevice;
import Vite.Platform.GLRenderDevice;
//import Vite.Platform.VKRenderDevice;

namespace Hedron {

///
/// Default
///
Scope<RenderDevice> RenderDevice::Create() {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXRenderDevice>(); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLRenderDevice>(); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKRenderDevice>(); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
