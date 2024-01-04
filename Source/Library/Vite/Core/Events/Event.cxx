module Vite.Event;

import "Vite/Base/Platform/Detection.h";
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
