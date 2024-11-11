module;

#include "Vite/Base/Platform/Detection.h"

#if defined APP_PLATFORM_WINDOWS
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

export module Vite.Platform.Graphics.Vulkan;

//export import vulkan_hpp;
