module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Device.Display;

#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinDisplay;
#endif

namespace Hedron {

Scope<Display> Display::Create(string id) {
  #ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinDisplay>(id);
  #else
    AppAssert(nullptr, "The current platform isn't supported!");
    return nullptr;
  #endif
}

Scope<DisplayManager> DisplayManager::Create() {
  #ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinDisplayManager>();
  #else
    AppAssert(nullptr, "The current platform isn't supported!");
    return nullptr;
  #endif
}

}
