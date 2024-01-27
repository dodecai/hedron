module Vite.Renderer.Texture;

import Vite.Device.GFXContext;
//import Vite.Platform.DXTexture;
import Vite.Platform.GLTexture;
//import Vite.Platform.VKTexture;

namespace Hedron {

///
/// Default
///
Scope<Texture> Texture::Create(const TextureProperties &properties, const void *data, size_t size) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXTexture>(properties, data, size); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLTexture>(properties, data, size); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKTexture>(properties, data, size); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

Reference<Texture> Texture::Create(const TextureProperties &properties, const string &path) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateReference<DXTexture>(properties, path); }
        case GraphicsAPI::OpenGL:   { return CreateReference<GLTexture>(properties, path); }
        //case GraphicsAPI::Vulkan:   { return CreateReference<VKTexture>(properties, path); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
