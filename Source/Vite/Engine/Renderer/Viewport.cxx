module Vite.Renderer.Viewport;

import Vite.Device.GFXContext;
import Vite.Platform.GLViewport;

namespace Hedron {

///
/// Default
///
Viewport::Viewport(const ViewportProperties& properties):
    mProperties(properties),
    mAspectRatio(properties.Size.Width / properties.Size.Height) {
}

Scope<Viewport> Viewport::Create(const ViewportProperties &properties) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXViewport>(properties); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLViewport>(properties); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKViewport>(properties); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
