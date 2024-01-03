#pragma once

///
/// @brief Preprocessor Utilities
///

// String
#define STRINGIZE(s) #s
#define TOSTRING(s) STRINGIZE(s)

///
/// @brief These properties are used to control platform specific features during compilation.
///

// Compiler Detection
#if defined _MSC_VER
	inline constexpr auto AppCompiler = "MSVC";
	#define APP_COMPILER "MSVC"
	#define APP_COMPILER_MSVC

	#define APP_COMPILER_VERSION_MAJOR _MSC_VER / 100
	#define APP_COMPILER_VERSION_MINOR _MSC_VER % 100
	#define APP_COMPILER_VERSION_PATCH 0
#else
	static_assert(false, "Compiler detection failed!");
#endif

#define APP_COMPILER_VERSION "v" TOSTRING(APP_COMPILER_VERSION_MAJOR) "." TOSTRING(APP_COMPILER_VERSION_MINOR) "." TOSTRING(APP_COMPILER_VERSION_PATCH)

// Platform Detection
#if defined _WIN32 || defined _WIN64
	inline constexpr auto AppPlatform = "Windows";
	#define APP_PLATFORM "Windows"
	#define APP_PLATFORM_WINDOWS
#else
	static_assert(false, "Platform detection failed!");
 	#error "Platform detection failed!"
#endif

// PlatformAPI Detection
#if defined APP_PLATFORM_WINDOWS
	inline constexpr auto AppPlatformAPI = "WinAPI";
	#define APP_PLATFORM_API "WinAPI"
	#define APP_PLATFORM_API_WINAPI
#else
	static_assert(false, "PlatformAPI detection failed!");
#endif
