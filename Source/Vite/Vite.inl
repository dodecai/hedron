#pragma once

import "Vite/Base/Platform/Support.h";

///
/// Library Properties
///

export namespace Hedron {

/// Information
inline constexpr auto LibCaption       = "VITE";
inline constexpr auto LibDescription   = "Versatile Integrated Technology Engine";
inline constexpr auto LibRelease       = "2025-07-02";
inline constexpr auto LibVersion       = "0.0.0";
inline constexpr auto LibVersionMajor  = 0u;
inline constexpr auto LibVersionMinor  = 0u;
inline constexpr auto LibVersionPatch  = 0u;

}

///
/// Platform Specific Information
/// @detail Shows the compiler and platform information during compilation.
/// @todo Support for other compilers when they are fully C++20 module ready.
///
#ifdef APP_COMPILER_MSVC
	#pragma message("#> Compiler: " APP_COMPILER " [" APP_COMPILER_VERSION "]")
    #pragma message("#> Platform: " APP_PLATFORM)
    #pragma message("#> PlatformAPI: " APP_PLATFORM_API)
#endif
