module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Event;

import Vite.Logger;

namespace Hedron {

Scope<EventListener> EventListener::Create() {
#ifdef APP_PLATFORM_WINDOWS
    //return CreateScope<WinEventListener>();
    return nullptr;
#else
    AppAssert(nullptr, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
