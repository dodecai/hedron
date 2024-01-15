module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Event;

import Vite.Logger;
#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinEvent;
#endif

namespace Hedron {

Scope<EventHandler> EventHandler::Create() {
#ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinEventHandler>();
#else
    AppAssert(nullptr, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
