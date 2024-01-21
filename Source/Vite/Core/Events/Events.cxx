module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Event;

import Vite.Logger;
#if defined APP_PLATFORM_WINDOWS
    import Vite.Platform.WinEvent;
#endif

namespace Hedron {

Scope<EventHandler> EventHandler::Create(void *window) {
#ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinEventHandler>(window);
#else
    AppAssert(false, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
