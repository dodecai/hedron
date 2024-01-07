module Vite.System.Window;

#include "Vite/Base/Platform/Detection.h"

#ifdef APP_PLATFORM_WINDOWS
    import Vite.Platform.WinWindow;
#endif

namespace Hedron {

//Scope<Window> Window::Create(const WindowProperties &properties) {
//    #ifdef APP_PLATFORM_WINDOWS
//        //return CreateScope<WinWindow>(properties);
//        return nullptr;
//    #else
//        AppAssert(nullptr, "The current platform isn't supported!");
//        return nullptr;
//    #endif
//}

}
