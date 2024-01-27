module Vite.Renderer.Framebuffer;

import Vite.Device.GFXContext;
//import Vite.Platform.DXFramebuffer;
import Vite.Platform.GLFramebuffer;
//import Vite.Platform.VKFramebuffer;

namespace Hedron {

///
/// Default
///
Scope<Framebuffer> Framebuffer::Create(const FramebufferProperties &properties) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXFramebuffer>(properties); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLFramebuffer>(properties); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKFramebuffer>(properties); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
