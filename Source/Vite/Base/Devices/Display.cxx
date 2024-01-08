module;

//#include "Vite/Base/Platform/Detection.h"

module Vite.Device.Display;

#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinDisplay;
#endif

namespace Hedron {

Scope<Display> Display::Create() {
#ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinDisplay>();
#else
    return {};
#endif
}

}
