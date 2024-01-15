module;

#include "Vite/Base/Platform/Detection.h"

module Vite.System.Window;

import Vite.Logger;
#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinWindow;
#endif

namespace Hedron {

Scope<Window> Window::Create(const WindowSettings &settings) {
    #ifdef APP_PLATFORM_WINDOWS
        return CreateScope<WinWindow>(settings);
    #else
        AppAssert(nullptr, "The current platform isn't supported!");
        return nullptr;
    #endif
}

}
