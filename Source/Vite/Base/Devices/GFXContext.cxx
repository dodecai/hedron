module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Device.GFXContext;

import Vite.Logger;
#if defined APP_PLATFORM_WINDOWS
    import Vite.Platform.DXContext;
    import Vite.Platform.GLContext;
    import Vite.Platform.VKContext;
#endif

namespace Hedron {

Scope<GFXContext> GFXContext::Create(void *window) {
#ifdef APP_PLATFORM_WINDOWS
    switch (API) {
        case GraphicsAPI::OpenGL: {
            LogDebug("Created context for 'OpenGL'");
            return CreateScope<GLContext>(window);
        }

        default: {
            AppAssert(false, "The selected graphics api isn't implemented!");
            return nullptr;
        }
    }
#else
    AppAssert(false, "The selected platform is currently not supported!");
    return nullptr;
#endif
}

}
