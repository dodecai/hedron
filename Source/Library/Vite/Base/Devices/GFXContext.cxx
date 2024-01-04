module Vite.Device.GFXContext;

import "Vite/Base/Platform/Detection.h";
import Vite.Logger;

#if defined APP_PLATFORM_WINDOWS
    //import Vite.Platform.DXContext;
    //import Vite.Platform.GLContext;
    //import Vite.Platform.VKContext;
#endif

namespace Hedron {

Reference<Context> Context::Create(void *window) {
    #ifdef APP_PLATFORM_WINDOWS
    switch (API) {
        case GraphicsAPI::OpenGL: {
        //    LogDebug("Application: Created context for 'OpenGL'");
        //    return CreateReference<GLContext>(window);
            return {};
        }

        case GraphicsAPI::Vulkan: {
        //    LogDebug("Application: Created context for 'Vulkan'");
        //    return CreateReference<VKContext>(window);
            return {};
        }

        default: {
            //AppAssert(false, "The selected graphics api isn't implemented!");
            return nullptr;
        }
    }
    #else
    AppAssert(false, "The selected platform is currently not supported!");
    return nullptr;
    #endif
}

void Context::Destroy() {}

}
