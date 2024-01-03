#pragma once

import "Vite/Base/Platform/Support.h";

///
/// Library Properties
///

// Switches to enable or disable Features
//#define LIB_EXTENSION_PRIME   // Prime Extensions like Types (cannot be disabled)
#define LIB_EXTENSION_CORE      // Application Configuration, Layout, Workflow and Utility Extensions
#define LIB_EXTENSION_DEBUG     // Debugging and Profiling Extension
#define LIB_EXTENSION_ENGINE    // Graphics API selection and Context Binding Extensions (implies ui extensions)
#define LIB_EXTENSION_SYSTEM    // System Extensions like color output in cli, event system, file system, input system, library loading
#define LIB_EXTENSION_UI        // UI extensions like window creation and event system

export namespace Hedron {

// Information
inline constexpr auto LibCaption       = "VITE";
inline constexpr auto LibDescription   = "Versatile Integrated Technology Engine";
inline constexpr auto LibRelease       = "2025-07-02";
inline constexpr auto LibVersion       = "0.0.0";
inline constexpr auto LibVersionMajor  = 0u;
inline constexpr auto LibVersionMinor  = 0u;
inline constexpr auto LibVersionPatch  = 0u;

// Features
namespace Features {

#ifdef LIB_EXTENSION_CORE
    inline constexpr bool LibCoreExtensions = true;
#else
    inline constexpr bool LibCoreExtensions = false;
#endif
#ifdef LIB_EXTENSION_DEBUG
    inline constexpr bool LibDebugExtensions = true;
#else
    inline constexpr bool LibDebugExtensions = false;
#endif
#ifdef LIB_EXTENSION_ENGINE
    inline constexpr bool LibEngineExtensions = true;
#else
    inline constexpr bool LibEngineExtensions = false;
#endif
#ifdef LIB_EXTENSION_SYSTEM
    inline constexpr bool LibSystemExtensions = true;
#else
    inline constexpr bool LibSystemExtensions = false;
#endif
#ifdef LIB_EXTENSION_UI
    inline constexpr bool LibUiExtensions = true;
#else
    inline constexpr bool LibUiExtensions = false;
#endif

}

}

// Show platform specific information, the preprocessor value is defined in 'Core.h', therefore it should be included first)
// ToDo: Support for other compilers when they are fully C++20 module ready.
#ifdef APP_COMPILER_MSVC
	#pragma message("#> Compiler: " APP_COMPILER " [" APP_COMPILER_VERSION "]")
    #pragma message("#> Platform: " APP_PLATFORM)
    #pragma message("#> PlatformAPI: " APP_PLATFORM_API)
#endif
