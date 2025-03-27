module;

#include <glad/gl.h>

module Vite.Platform.GLCommandBuffer;

namespace Hedron {

///
/// Default
///
GLCommandBuffer::GLCommandBuffer() {
    mCommands.reserve(1024);
}

GLCommandBuffer::~GLCommandBuffer() {}


///
/// Commands
///
void GLCommandBuffer::Capture() {
    mCommands.clear();
}

void GLCommandBuffer::Clear(const Color &color) {
    mCommands.push_back([color]() {
        glClearColor(color.Red, color.Green, color.Blue, color.Alpha);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    });
}

void GLCommandBuffer::Draw(uint32 vertexCount, uint32 instanceCount, uint32 firstVertex, uint32 firstInstance) {
}

void GLCommandBuffer::DrawIndexed(size_t count, PrimitiveType primitive, bool depthTest) {
    GLenum type = GL_UNSIGNED_INT;
    //switch (properties.Type) {
    //    case IndexType::UINT8:  { type = GL_UNSIGNED_BYTE; break; }
    //    case IndexType::UINT16: { type = GL_UNSIGNED_INT; break; }
    //    case IndexType::UINT32: { type = GL_UNSIGNED_INT; break; }
    //}

    GLenum mode = GL_TRIANGLES;
    switch (primitive) {
        case PrimitiveType::Line:     { mode = GL_LINES; break; }
        case PrimitiveType::Triangle: { mode = GL_TRIANGLES; break; }
    }

    //mCommands.push_back([depthTest, count, mode, type]() {
        if (!depthTest) { glDepthMask(GL_FALSE); } else { glDepthMask(GL_TRUE); };
         // ToDo: C4267 possible loss of data
        glDrawElements(mode, static_cast<GLsizei>(count), type, nullptr);
        if (!depthTest) { glDepthMask(GL_TRUE); } else { glDepthMask(GL_FALSE); };
    //});
}

void GLCommandBuffer::DrawIndexed(uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
    GLenum mode = GL_TRIANGLES;
    GLenum type = GL_UNSIGNED_INT;
    //switch (properties.Type) {
    //    case IndexType::UINT8:  { type = GL_UNSIGNED_BYTE; break; }
    //    case IndexType::UINT16: { type = GL_UNSIGNED_INT; break; }
    //    case IndexType::UINT32: { type = GL_UNSIGNED_INT; break; }
    //}

    //switch (primitive) {
    //    case PrimitiveType::Line: { mode = GL_LINES; break; }
    //    case PrimitiveType::Triangle: { mode = GL_TRIANGLES; break; }
    //}

    mCommands.push_back([indexCount, mode, type]() {
        //if (!depthTest) glDisable(GL_DEPTH_TEST);
        glDrawElements(mode, indexCount, type, nullptr);
        //if (!depthTest) glEnable(GL_DEPTH_TEST);
    });
}

void GLCommandBuffer::Execute() {
    // ToDo: Remove workaround after all renderer support the command buffer
    if (mCommands.size() <= 1) return;
    for (auto &command : mCommands) {
        command();
    }
}

void GLCommandBuffer::Record(const function<void()> &callback) {
    mCommands.push_back(std::move(callback));
}

void GLCommandBuffer::Viewport(const Position2D &position, const Size2D &size) {
    // ToDo: Prevent sizes above imagination
    if (!(size.Width == 0) || !(size.Height == 0)) return;

    mCommands.push_back([position, size]() {
        glViewport(
            static_cast<GLint>(position.X),
            static_cast<GLint>(position.Y),
            static_cast<GLsizei>(size.Width),
            static_cast<GLsizei>(size.Height)
        );
    });
}


///
/// Test
///
void GLCommandBuffer::UpdateStencilBuffer() {
    mCommands.push_back([]() {
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
    });
}

void GLCommandBuffer::EnableStencilTest() {
    mCommands.push_back([]() {
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
    });
}

void GLCommandBuffer::ResetStencilTest() {
    mCommands.push_back([]() {
        glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
    });
}

}
