module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Event;

import Vite.Logger;

#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinEvent;
#endif

namespace Hedron {

Scope<EventListener> EventListener::Create() {
#ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinEventListener>();

#else
    AppAssert(nullptr, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
