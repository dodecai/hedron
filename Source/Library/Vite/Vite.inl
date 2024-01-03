#pragma once

import "Vite/Base/Platform/Support.h";

///
/// Library Properties
///

// Switches to enable or disable Features
//#define LIB_EXTENSION_BASE    // Base Extensions like Types (cannot be disabled)
//#define LIB_EXTENSION_PRIME   // Prime Extensions like Config or Logger (cannot be disabled)
#define LIB_EXTENSION_CORE      // Application Configuration, Layout, Workflow and Utility Extensions
#define LIB_EXTENSION_SYSTEMS   // Graphics API selection and Context Binding Extensions (implies ui extensions)
#define LIB_EXTENSION_TOOLS     // System Extensions like color output in cli, event system, file system, input system, library loading

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
#ifdef LIB_EXTENSION_SYSTEMS
    inline constexpr bool LibSystemsExtensions = true;
#else
    inline constexpr bool LibSystemsExtensions = false;
#endif
#ifdef LIB_EXTENSION_TOOLS
    inline constexpr bool LibToolsExtensions = true;
#else
    inline constexpr bool LibToolsExtensions = false;
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
