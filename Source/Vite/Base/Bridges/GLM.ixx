module;

#pragma warning(push, 0)

#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

export import <glm/glm.hpp>;
export import <glm/gtc/constants.hpp>;
export import <glm/gtc/matrix_transform.hpp>;
export import <glm/gtc/type_ptr.hpp>;
export import <glm/gtx/compatibility.hpp>;
export import <glm/gtx/matrix_decompose.hpp>;
export import <glm/gtx/quaternion.hpp>;
export import <glm/gtx/string_cast.hpp>;

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

using namespace ::glm;

}
#pragma warning(pop)
