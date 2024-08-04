#pragma once

///
/// @brief Preprocessor Utilities
/// @detail These properties are used to control platform specific features during compilation.
///

// String
#define STRINGIZE(s) #s
#define TOSTRING(s) STRINGIZE(s)

// Compiler Detection
#if defined _MSC_VER
	inline constexpr auto AppCompiler = "MSVC";
	#define APP_COMPILER "MSVC"
	#define APP_COMPILER_MSVC

    inline constexpr auto AppCompilerVersionMajor = _MSC_VER;
    inline constexpr auto AppCompilerVersionMinor = 0;
    inline constexpr auto AppCompilerVersionPatch = 0;
	#define APP_COMPILER_VERSION_MAJOR _MSC_VER // / 100
	#define APP_COMPILER_VERSION_MINOR 0        // % 100
	#define APP_COMPILER_VERSION_PATCH 0
#elif defined __clang__
    inline constexpr auto AppCompiler = "Clang";
    #define APP_COMPILER "Clang"
    #define APP_COMPILER_CLANG

    inline constexpr auto AppCompilerVersionMajor = __clang_major__;
    inline constexpr auto AppCompilerVersionMinor = __clang_minor__;
    inline constexpr auto AppCompilerVersionPatch = __clang_patchlevel__;
    #define APP_COMPILER_VERSION_MAJOR __clang_major__
    #define APP_COMPILER_VERSION_MINOR __clang_minor__
    #define APP_COMPILER_VERSION_PATCH __clang_patchlevel__
#elif defined __EMSCRIPTEN__
    inline constexpr auto AppCompiler = "emscripten";
    #define APP_COMPILER "emscripten"
	#define APP_COMPILER_EMSCRIPTEN

    inline constexpr auto AppCompilerVersionMajor = 0;
    inline constexpr auto AppCompilerVersionMinor = 0;
    inline constexpr auto AppCompilerVersionPatch = 0;
	#define APP_COMPILER_MAJOR		0
	#define APP_COMPILER_MINOR		0
	#define APP_COMPILER_PATCH		0
#elif defined __GNUC__
    inline constexpr auto AppCompiler = "GCC";
    #define APP_COMPILER "GCC"
    #define APP_COMPILER_GNU

    inline constexpr auto AppCompilerVersionMajor = __GNUC__;
    inline constexpr auto AppCompilerVersionMinor = __GNUC_MINOR__;
    inline constexpr auto AppCompilerVersionPatch = 0;
    #define APP_COMPILER_VERSION_MAJOR __GNUC__
    #define APP_COMPILER_VERSION_MINOR __GNUC_MINOR__
    #define APP_COMPILER_VERSION_PATCH 0
#elif defined __MINGW32 || defined __MINGW64
    inline constexpr auto AppCompiler = "MinGW";
    #define APP_COMPILER "MinGW"
    #define APP_COMPILER_MINGW
    
	#if defined(__MINGW32__)
        inline constexpr auto AppCompilerVersionMajor = __MINGW32_MAJOR_VERSION;
        inline constexpr auto AppCompilerVersionMinor = __MINGW32_MINOR_VERSION;
		#define APP_COMPILER_MAJOR	__MINGW32_MAJOR_VERSION
		#define APP_COMPILER_MINOR	__MINGW32_MINOR_VERSION
	#else
        inline constexpr auto AppCompilerVersionMajor = __MINGW64_VERSION_MAJOR;
        inline constexpr auto AppCompilerVersionMinor = __MINGW64_VERSION_MINOR;
		#define APP_COMPILER_MAJOR	__MINGW64_VERSION_MAJOR
		#define APP_COMPILER_MINOR	__MINGW64_VERSION_MINOR
	#endif
    inline constexpr auto AppCompilerVersionPatch = 0;
    #define APP_COMPILER_VERSION_PATCH 0
#else
    inline constexpr auto AppCompiler = "Unknown";
    #define APP_COMPILER "Unknown"
	#define APP_COMPILER_UNKNOWN

    inline constexpr auto AppCompilerVersionMajor = 0;
    inline constexpr auto AppCompilerVersionMinor = 0;
    inline constexpr auto AppCompilerVersionPatch = 0;
	#define APP_COMPILER_MAJOR		0
	#define APP_COMPILER_MINOR		0
	#define APP_COMPILER_PATCH		0

	static_assert(false, "Compiler detection failed!");
#endif
inline constexpr auto AppCompilerVersion = "v" TOSTRING(APP_COMPILER_VERSION_MAJOR) "." TOSTRING(APP_COMPILER_VERSION_MINOR) "." TOSTRING(APP_COMPILER_VERSION_PATCH);
#define APP_COMPILER_VERSION "v" TOSTRING(APP_COMPILER_VERSION_MAJOR) "." TOSTRING(APP_COMPILER_VERSION_MINOR) "." TOSTRING(APP_COMPILER_VERSION_PATCH)

// Platform Detection
#if defined _WIN32 || defined _WIN64
	inline constexpr auto AppPlatform = "Windows";
	#define APP_PLATFORM "Windows"
	#define APP_PLATFORM_WINDOWS
#elif defined __ANDROID__
    inline constexpr auto AppPlatform = "Android";
    #define APP_PLATFORM "Android"
	#define APP_PLATFORM_ANDROID
#elif defined __FREEBSD__
    inline constexpr auto AppPlatform = "BSD";
    #define APP_PLATFORM "BSD"
	#define APP_PLATFORM_BSD
#elif defined __linux__ && !defined __ANDROID__
    inline constexpr auto AppPlatform = "Linux";
    #define APP_PLATFORM "Linux"
	#define APP_PLATFORM_LINUX
#elif defined __MACH__
	#include <TargetConditionals.h>
	#if TARGET_OS_IPHONE == 1
        inline constexpr auto AppPlatform = "iOS";
        #define APP_PLATFORM "iOS"
		#define APP_PLATFORM_IOS
	#elif TARGET_OS_MAC == 1
        inline constexpr auto AppPlatform = "MacOSX";
        #define APP_PLATFORM "MacOSX"
		#define APP_PLATFORM_MACOSX
	#endif
#elif !defined __linux__ && defined unix  || defined __unix || defined __unix__
    inline constexpr auto AppPlatform = "Unix";
    #define APP_PLATFORM "Unix"
	#define APP_PLATFORM_UNIX
#elif defined APP_COMPILER_EMSCRIPTEN
    inline constexpr auto AppPlatform = "Web";
    #define APP_PLATFORM "Web"
	#define APP_PLATFORM_WEB
#else
    inline constexpr auto AppPlatform = "Unknown";
    #define APP_PLATFORM "Unknown"
    #define APP_PLATFORM_UNKNOWN

	static_assert(false, "Platform detection failed!");
#endif

// PlatformAPI Detection
#if defined APP_PLATFORM_WINDOWS
	inline constexpr auto AppPlatformAPI = "WinAPI";
	#define APP_PLATFORM_API "WinAPI"
	#define APP_PLATFORM_API_WINAPI
#elif defined APP_PLATFORM_BSD || defined APP_PLATFORM_LINUX || defined APP_PLATFORM_UNIX
    inline constexpr auto AppPlatformAPI = "XCB";
    #define APP_PLATFORM_API "XCB"
	#define APP_PLATFORM_API_XCB
#elif defined APP_PLATFORM_MACOSX
    inline constexpr auto AppPlatformAPI = "Cocoa";
    #define APP_PLATFORM_API "Cocoa"
	#define APP_PLATFORM_API_COCOA
#elif defined APP_PLATFORM_WEB
    inline constexpr auto AppPlatformAPI = "WASM";
    #define APP_PLATFORM_API "WASM"
	#define APP_PLATFORM_API_WASM
#else
    inline constexpr auto AppPlatformAPI = "Unknown";
    #define APP_PLATFORM_API "Unknown"
    #define APP_PLATFORM_API_UNKNOWN

	static_assert(false, "PlatformAPI detection failed!");
#endif
