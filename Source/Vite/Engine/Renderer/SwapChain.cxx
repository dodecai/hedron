module Vite.Renderer.Swapchain;

import Vite.Device.GFXContext;
//import Vite.Platform.DXSwapchain;
import Vite.Platform.GLSwapchain;
//import Vite.Platform.VKSwapchain;

namespace Hedron {

///
/// Default
///
Scope<Swapchain> Swapchain::Create(const Size2D &size) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXSwapchain>(size); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLSwapchain>(size); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKSwapchain>(size); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
