module;

#include <glad/gl.h>

module Vite.Platform.GLViewport;

namespace Hedron {

///
/// Default
///
GLViewport::GLViewport(const ViewportProperties &properties): Viewport(properties) {
    auto x = static_cast<GLint>(properties.Position.X);
    auto y = static_cast<GLint>(properties.Position.Y);
    auto width = static_cast<GLsizei>(properties.Size.Width);
    auto height = static_cast<GLsizei>(properties.Size.Height);

    glViewport(x, y, width, height);
}

GLViewport::~GLViewport() {}

}
