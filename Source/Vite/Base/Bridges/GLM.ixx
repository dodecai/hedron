module;

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_XYZW_ONLY             // Disables SIMD intrinsics for now, GLM_FORCE_PURE is buggy (we disable it due to msvc bug)

#pragma warning(push, 0)

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#pragma warning(pop)

export module Vite.Bridge.GLM;

///
/// @brief Bridge: GLM Library
/// @detail OpenGL Mathematics
/// @note Currently everything is exported, later it can be reduced to only what is needed.
/// @todo Further research on how to reduce the export.
///

#pragma warning(push, 0)
export namespace glm {

///
/// Types
///
using glm::mat2;
using glm::mat3;
using glm::mat4;
using glm::quat;
using glm::vec2;
using glm::vec3;
using glm::vec4;


///
/// Functions
///
using glm::inverse;
using glm::radians;
using glm::rotate;
using glm::radians;
using glm::scale;
using glm::toMat4;
using glm::translate;


///
/// Operators
///
using glm::operator+;
using glm::operator-;
using glm::operator*;
using glm::operator/;


///
/// Helpers
///
glm::mat4 LookAt(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &up) {
    return glm::lookAtLH(position, target, up);
}

glm::mat4 Perspective(float fov, float aspect, float near, float far) {
    return glm::perspectiveLH_ZO(fov, aspect, near, far);
}

glm::mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) {
    return glm::orthoLH_ZO(left, right, bottom, top, near, far);
}

glm::mat4 Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale) {
    return
        glm::translate(glm::mat4(1.0f), position) *
        glm::toMat4(glm::quat(rotation)) *
        glm::scale(glm::mat4(1.0f), scale);
}

}
#pragma warning(pop)
