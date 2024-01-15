module;

#include "Vite/Base/Platform/Detection.h"

#if defined(APP_PLATFORM_WINDOWS)
    #define WIN32_LEAN_AND_MEAN
    #define NOMINMAX
    #define VC_EXTRALEAN
    #include <Windows.h>

    #pragma comment(lib, "opengl32.lib")
#endif

#include <glad/gl.h>

#if defined(APP_PLATFORM_WINDOWS)
    #include <GL/wglext.h>
#endif

module Vite.Platform.GLContext;

//import Vite.Bridge.Glad;
import Vite.Logger;

///
/// Helpers
///
namespace {

#if defined APP_PLATFORM_WINDOWS
    inline PROC GetExtension(const char *functionName) { return wglGetProcAddress(functionName); }

    typedef HGLRC WINAPI wglCreateContextAttribsARB_t(HDC hdc, HGLRC hShareContext, const int *attribList);
    wglCreateContextAttribsARB_t *wglCreateContextAttribsARB;

    typedef BOOL WINAPI wglChoosePixelFormatARB_t(HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
    wglChoosePixelFormatARB_t *wglChoosePixelFormatARB;

    typedef BOOL WINAPI wglSwapIntervalEXT_t(int interval);
    wglSwapIntervalEXT_t *wglSwapIntervalEXT;
#endif

static void GLAPIENTRY GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, [[maybe_unused]] GLsizei length, const GLchar *message, [[maybe_unused]] const void *userParam) {
    using namespace Hedron;
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: { logger << LogLevel::Error;	break; }
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: { logger << LogLevel::Warn;	    break; }
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: { logger << LogLevel::Warn;	    break; }
        case GL_DEBUG_TYPE_PORTABILITY: { logger << LogLevel::Trace;	break; }
        case GL_DEBUG_TYPE_PERFORMANCE: { logger << LogLevel::Trace;	break; }
        case GL_DEBUG_TYPE_OTHER: { logger << LogLevel::Trace;	break; }
        default: { logger << LogLevel::Fatal;	break; }
    }
    logger << "[Context::GL]" << message << "{" <<
        "ID:" << id << " | " <<
        "Source:" << source << " | " <<
        "Severity:" << severity <<
        "}\n";
    }
}

namespace Hedron {

///
/// @brief Context Data: Platform specific
///
struct ContextData {
#if defined(APP_PLATFORM_WINDOWS)
	HWND WindowHandle;
	HDC DeviceContextHandle;
	HGLRC RenderingContextHandle;
#endif
};

/// Default
GLContext::GLContext(void *window) {
	// Prepare
	mData = CreateScope<ContextData>();
    ContextSettings settings;
    settings.VersionMajor = 4;
    settings.VersionMinor = 6;

	mData->WindowHandle = reinterpret_cast<HWND>(window);

	// Check Compatibility Flag
	auto compatibility = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;
	if (settings.Compatibility) compatibility = WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB;
	// Each version has a different set of majors and minors
	switch (settings.VersionMajor) {
		case 1:
            settings.VersionMinor = { settings.VersionMinor, 0, 5 };
			break;
		case 2:
            settings.VersionMinor = { settings.VersionMinor, 0, 1 };
			break;
		case 3:
            settings.VersionMinor = { settings.VersionMinor, 0, 3 };
			break;
		case 4:
            settings.VersionMinor = { settings.VersionMinor, 0, 6 };
			break;
		default:
            settings.VersionMajor = 4;
            settings.VersionMinor = 6;
            LogError("Unknown version specified, using default version [v{}.{}]!", 4, 6);
			break;
	}

	// Platform specific stuff
#if defined(APP_PLATFORM_WINDOWS)
    // This should be only triggered once during application lifecycle
	if(!LoadExtensions() && mLoaded) { LogFatal("Could not load OpenGL extensions!"); return; }
    mLoaded = true;

	// Get Device Context
	mData->DeviceContextHandle = GetDC(mData->WindowHandle);
	if (!mData->DeviceContextHandle) { LogFatal("Error occurred while acquiring device context!"); return; }
		
	/* Legacy Code (it took a lot of effort to get used to it, so I will leave it here forever) */
	// Drawing Surface Pixel Format: https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-pixelformatdescriptor
	//PIXELFORMATDESCRIPTOR pfDrawingSurface = {
	//	.nSize = sizeof(PIXELFORMATDESCRIPTOR),
	//	.nVersion = 1,									// Version
	//	.dwFlags =	PFD_DRAW_TO_WINDOW |				// The buffer can draw to a window or device surface.
	//				PFD_DOUBLEBUFFER |					// The buffer is double-buffered.
	//				PFD_SUPPORT_OPENGL |				// The buffer supports OpenGL drawing.
	//				PFD_SWAP_LAYER_BUFFERS,				// Indicates whether a device can swap individual layer planes with pixel formats that include double-buffered overlay or underlay planes.
	//	.iPixelType = PFD_TYPE_RGBA,					// Each pixel has four components in this order: red, green, blue, and alpha.
	//	.cColorBits = (BYTE)properties.ColorDepth,		// Color Depth
	//	.cRedBits = 0,									// Specifies the number of red bitplanes in each RGBA color buffer.
	//	.cRedShift = 0,									// Specifies the shift count for red bitplanes in each RGBA color buffer.
	//	.cGreenBits = 0,								// Specifies the number of green bitplanes in each RGBA color buffer.
	//	.cGreenShift = 0,								// Specifies the shift count for green bitplanes in each RGBA color buffer.
	//	.cBlueBits = 0,									// Specifies the number of blue bitplanes in each RGBA color buffer.
	//	.cBlueShift = 0,								// Specifies the shift count for blue bitplanes in each RGBA color buffer.
	//	.cAlphaBits = 0,								// Specifies the number of alpha bitplanes in each RGBA color buffer
	//	.cAlphaShift = 0,								// Specifies the shift count for alpha bitplanes in each RGBA color buffer.
	//	.cAccumBits = 0,								// Specifies the total number of bitplanes in the accumulation buffer.
	//	.cAccumRedBits = 0,								// Specifies the number of red bitplanes in the accumulation buffer.
	//	.cAccumGreenBits = 0,							// Specifies the number of green bitplanes in the accumulation buffer.
	//	.cAccumBlueBits = 0,							// Specifies the number of blue bitplanes in the accumulation buffer.
	//	.cAccumAlphaBits = 0,							// Specifies the number of alpha bitplanes in the accumulation buffer.
	//	.cDepthBits = (BYTE)properties.DepthBuffer,		// Depth Buffer (Z-Buffer)
	//	.cStencilBits = (BYTE)properties.StencilBuffer,	// Stencil Buffer
	//	.cAuxBuffers = 0,								// Auxiliary Buffers
	//	.iLayerType = PFD_MAIN_PLANE,					// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used.
	//	.bReserved = 0,									// Specifies the number of overlay and underlay planes. Bits 0 through 3 specify up to 15 overlay planes and bits 4 through 7 specify up to 15 underlay planes.
	//	.dwLayerMask = 0,								// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used.
	//	.dwVisibleMask = 0,								// Specifies the transparent color or index of an underlay plane. When the pixel type is RGBA, dwVisibleMask is a transparent RGB color value.
	//	.dwDamageMask = 0								// Ignored. Earlier implementations of OpenGL used this member, but it is no longer used.
	//};
	//pixelFormat = ChoosePixelFormat(Data->DeviceContextHandle, &pfDrawingSurface);

	// Describe GL-Context
    PIXELFORMATDESCRIPTOR pfDescription = {};
	int pixelFormats = 0;
	unsigned int formatsMax = 1;
	unsigned int formatsCount = 2;
	int pixelAttribIList[] = {
		WGL_DOUBLE_BUFFER_ARB,			GL_TRUE,
		WGL_DRAW_TO_WINDOW_ARB,			GL_TRUE,
		WGL_SUPPORT_OPENGL_ARB,			GL_TRUE,
		WGL_ACCELERATION_ARB,			WGL_FULL_ACCELERATION_ARB,
		WGL_PIXEL_TYPE_ARB,				WGL_TYPE_RGBA_ARB,
		WGL_COLOR_BITS_ARB,				settings.ColorDepth,
		WGL_ALPHA_BITS_ARB,				settings.AlphaDepth,
		WGL_DEPTH_BITS_ARB,				settings.DepthBuffer,
		WGL_STENCIL_BITS_ARB,			settings.StencilBuffer,
		WGL_SAMPLE_BUFFERS_ARB,			settings.MSAABuffer,
		WGL_SAMPLES_ARB,				settings.MSAASamples,
		WGL_TRANSPARENT_ARB,			GL_TRUE,
		0,
	};
	wglChoosePixelFormatARB(mData->DeviceContextHandle, pixelAttribIList, NULL, formatsMax, &pixelFormats, &formatsCount);
	if (!formatsCount) { LogFatal("Error no suitable pixel format found!"); return; }
	DescribePixelFormat(mData->DeviceContextHandle, pixelFormats, sizeof(pfDescription), &pfDescription);
	if (!SetPixelFormat(mData->DeviceContextHandle, pixelFormats, &pfDescription)) { LogFatal("Error setting pixel format failed [Code:{}]!", GetLastError()); return; }

	// Create GL-Context
    int flags = WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB;
    #ifdef APP_DEBUG_MODE
        flags |= WGL_CONTEXT_DEBUG_BIT_ARB;
    #endif
	int glContextAttributes[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB,	settings.VersionMajor,
		WGL_CONTEXT_MINOR_VERSION_ARB,	settings.VersionMinor,
        WGL_CONTEXT_PROFILE_MASK_ARB,   compatibility,
		WGL_CONTEXT_FLAGS_ARB,			flags,
        0            
	};
    mData->RenderingContextHandle = wglCreateContextAttribsARB(mData->DeviceContextHandle, NULL, glContextAttributes);
	if (!mData->RenderingContextHandle) { LogFatal("Error occurred while creating GL-Context!"); return; }

    // Activate GL-Context
    if (!wglMakeCurrent(mData->DeviceContextHandle, mData->RenderingContextHandle)) {
        LogFatal("Error occurred while activating GL-Context!");
        return;
    }
#endif

    // Load GL-Functions
    if (!gladLoaderLoadGL()) {
        LogFatal("Failed to load OpenGL!");
        return;
    }

    // Deactivate GL-Context
#if defined APP_PLATFORM_WINDOWS
    if (!wglMakeCurrent(mData->DeviceContextHandle, nullptr)) {
        LogFatal("Error occurred while deactivating GL-Context!");
        return;
    }
#endif

#ifdef APP_MODE_DEBUG
    if (glDebugMessageCallback) {
        glEnable(GL_DEBUG_OUTPUT);
        //glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(GLMessageCallback, 0);
        //glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
    } else {
        LogWarning("The feature 'DebugMessageCallback' isn't available!");
    }
#endif
}

GLContext::~GLContext() {
    gladLoaderUnloadGL();
#if defined APP_PLATFORM_WINDOWS
    wglMakeCurrent(mData->DeviceContextHandle, nullptr);
    wglDeleteContext(mData->RenderingContextHandle);
#endif
}

/// Controls
void GLContext::Attach() {
    if (!CurrentContext()) {
    #if defined APP_PLATFORM_WINDOWS
        wglMakeCurrent(mData->DeviceContextHandle, mData->RenderingContextHandle);
    #endif
    }
}

void GLContext::Detach() {
    if (CurrentContext()) {
    #if defined APP_PLATFORM_WINDOWS
        wglMakeCurrent(mData->DeviceContextHandle, nullptr);
    #endif
    }
}

void GLContext::Clear() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLContext::SwapBuffers() {
#if defined APP_PLATFORM_WINDOWS
    if (mData->DeviceContextHandle) ::SwapBuffers(mData->DeviceContextHandle);
#endif
}

void GLContext::Viewport(const Size2D &size, const Position2D &position) {
    auto x = static_cast<GLint>(position.X);
    auto y = static_cast<GLint>(position.Y);
    auto width = static_cast<GLsizei>(size.Width);
    auto height = static_cast<GLsizei>(size.Height);

    glViewport(x, y, width, height);
}

void GLContext::VSync(bool activate) {
#ifdef APP_PLATFORM_WINDOWS
    wglSwapIntervalEXT(activate ? 1 : 0);
#endif
}


/// States
bool const GLContext::CurrentContext() {
#if defined APP_PLATFORM_WINDOWS
    return (wglGetCurrentContext() == mData->RenderingContextHandle);
#else
    return false;
#endif
}


/// Casts
void *GLContext::AsPlatformHandle() {
#if defined APP_PLATFORM_WINDOWS
    return reinterpret_cast<void *>(mData->RenderingContextHandle);
#else
    return nullptr;
#endif
}


/// Methods
bool GLContext::LoadExtensions() {
	bool result = true;
#if defined(APP_PLATFORM_WINDOWS)
    // Dummy Class
    WNDCLASSEX dClass = {.cbSize = sizeof(WNDCLASSEX), .style =  CS_OWNDC | CS_HREDRAW | CS_VREDRAW, .lpfnWndProc = DefWindowProcA, .hInstance = GetModuleHandle(NULL), .lpszClassName = L"DummyClassGL",};
    if (!RegisterClassEx(&dClass)) { result = false; }
    
    // Dummy Window
    HWND dWindow = CreateWindowEx(NULL, dClass.lpszClassName, L"DummyWindowGL", WS_POPUP | WS_DISABLED, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, dClass.hInstance, NULL);
    if (!dWindow) { result = false; }
    
    // Dummy Device Context
    HDC dDeviceContext = GetDC(dWindow);
    PIXELFORMATDESCRIPTOR pfd = {.nSize = sizeof(PIXELFORMATDESCRIPTOR), .nVersion = 1, .dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL, .iPixelType = PFD_TYPE_RGBA, .cColorBits = 32, .cDepthBits = 24, .cStencilBits = 8, .iLayerType = PFD_MAIN_PLANE};
    int pixelFormat = ChoosePixelFormat(dDeviceContext, &pfd);
    if (!pixelFormat) { result = false; }
    if (!SetPixelFormat(dDeviceContext, pixelFormat, &pfd)) { result = false; }
    
    // Dummy Render Context
    HGLRC dRenderContext = wglCreateContext(dDeviceContext);
    if (!dRenderContext) { result = false; }
    if (!wglMakeCurrent(dDeviceContext, dRenderContext)) { result = false; }
    
    // Load Extensions
    wglCreateContextAttribsARB = (wglCreateContextAttribsARB_t *)wglGetProcAddress("wglCreateContextAttribsARB");
    wglChoosePixelFormatARB = (wglChoosePixelFormatARB_t *)wglGetProcAddress("wglChoosePixelFormatARB");
    wglSwapIntervalEXT = (wglSwapIntervalEXT_t *)wglGetProcAddress("wglSwapIntervalEXT");
    
    // Cleanup
    if (dDeviceContext) wglMakeCurrent(dDeviceContext, nullptr);
    if (dRenderContext) wglDeleteContext(dRenderContext);
    if (dWindow && dDeviceContext) ReleaseDC(dWindow, dDeviceContext);
    if (dWindow) DestroyWindow(dWindow);
#endif
	return result;
}

}
