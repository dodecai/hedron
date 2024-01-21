module Vite.System.Dialog;

#include "Vite/Base/Platform/Detection.h"

#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinDialog;
#endif

namespace Hedron {

Scope<Dialog> Dialog::Create(void *window) {
#ifdef APP_PLATFORM_WINDOWS
    return CreateScope<WinDialog>(window);
    return nullptr;
#else
    AppAssert(false, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
