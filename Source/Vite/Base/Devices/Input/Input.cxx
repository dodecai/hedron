module;

#include "Vite/Base/Platform/Detection.h"

module Vite.Device.Input;

import Vite.Logger;
#if defined APP_PLATFORM_WINDOWS
    import Vite.Platform.WinInput;
#endif

namespace Hedron {

Scope<Input> Input::Instance = Input::Create();

Scope<Input> Input::Create() {
#if defined APP_PLATFORM_WINDOWS
    return CreateScope<WinInput>();
#else
    AppAssert(false, "The current platform isn't supported!");
    return nullptr;
#endif
}

}
