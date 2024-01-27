module;

#include <glad/gl.h>

module Vite.Platform.GLSwapchain;

namespace Hedron {

///
/// Default
///
GLSwapchain::GLSwapchain(const Size2D &size) {}

GLSwapchain::~GLSwapchain() {}


///
/// Accessors
///
Reference<Texture> GLSwapchain::CurrentImage() {
    return nullptr;
}

RendererID GLSwapchain::CurrentImageIndex() {
    return 0;
}


///
/// Methods
///
void GLSwapchain::Present() {
    //Context::SwapBuffers(mWindowHandle);
}

void GLSwapchain::Resize(float width, float height) {}

}
