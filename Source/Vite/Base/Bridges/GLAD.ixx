module;

#include "Vite/Base/Platform/Support.h"

#pragma warning(push, 0)

#include <glad/gl.h>
#if defined(APP_PLATFORM_WINDOWS)
    #pragma comment(lib, "opengl32.lib")
    #include <GL/wglext.h>
#endif

#pragma warning(pop)

export module Vite.Bridge.Glad;

///
/// @brief Bridge: GLAD Library
/// @detail GL Loader-Generator
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

export {

// ToDo: Finish CreateCppModule4ClassicHeader.ps1

}
