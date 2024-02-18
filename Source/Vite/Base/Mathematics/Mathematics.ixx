export module Vite.Math;

export import Vite.Math.Geometry;
export import Vite.Math.Matrix;
export import Vite.Math.Quaternion;
export import Vite.Math.Vector;

import Vite.Type.Concepts;
import Vite.Type.Standard;

export namespace Hedron {

namespace Math {

///
/// Aliases
///
// Scalar Types
using Bool = bool;
using Double = double;
using Float = float;
using Int = int32;
using UInt = uint32;

// Vector Types
using Bool2 = VectorBase<bool, 2, VectorAliases::None>;
using Bool3 = VectorBase<bool, 3, VectorAliases::None>;
using Bool4 = VectorBase<bool, 4, VectorAliases::None>;

using Double2 = VectorBase<double, 2>;
using Double3 = VectorBase<double, 3>;
using Double4 = VectorBase<double, 4>;

using Float2 = VectorBase<float, 2>;
using Float3 = VectorBase<float, 3>;
using Float4 = VectorBase<float, 4>;

using Int2 = VectorBase<int32_t, 2>;
using Int3 = VectorBase<int32_t, 3>;
using Int4 = VectorBase<int32_t, 4>;

using UInt2 = VectorBase<uint32_t, 2>;
using UInt3 = VectorBase<uint32_t, 3>;
using UInt4 = VectorBase<uint32_t, 4>;


///
/// Functions
///
template <typename_floating_point T>
constexpr inline T DegreesToRadians(T degrees) {
    return degrees * static_cast<T>(std::numbers::pi) / 180.0f;
}

template <typename_floating_point T>
constexpr inline T RadiansToDegrees(T radians) {
    return radians * 180.0f / static_cast<T>(std::numbers::pi);
}


#ifdef LEGACY_CODE

bool DecomposeTransform([[maybe_unused]] const glm::mat4 &transform, [[maybe_unused]] glm::vec3 &position, [[maybe_unused]] glm::vec3 &orientation, [[maybe_unused]] glm::vec3 &scale) {
    // from glm::decompose in matrix_decompose.inl

    using namespace glm;
    using T = float;

    mat4 LocalMatrix(transform);

    // Normalize the matrix.
    if (epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>())) return false;

    // First, isolate perspective.  This is the messiest.
    if (
        epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
        epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
        epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>())) {
        // Clear the perspective partition
        LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
        LocalMatrix[3][3] = static_cast<T>(1);
    }

    // Next take care of translation (easy).
    position = vec3(LocalMatrix[3]);
    LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

    vec3 Row[3]; // , Pdum3;

    // Now get scale and shear.
    for (length_t i = 0; i < 3; ++i)
        for (length_t j = 0; j < 3; ++j)
            Row[i][j] = LocalMatrix[i][j];

    // Compute X/Y/Z scale factor and normalize 1st/2nd/3rd row.
    scale.x = length(Row[0]);// v3Length(Row[0]);
    Row[0] = detail::scale(Row[0], static_cast<T>(1));
    scale.y = length(Row[1]);
    Row[1] = detail::scale(Row[1], static_cast<T>(1));
    scale.z = length(Row[2]);
    Row[2] = detail::scale(Row[2], static_cast<T>(1));

    // At this point, the matrix (in rows[]) is orthonormal.
    // Check for a coordinate system flip.  If the determinant
    // is -1, then negate the matrix and the scaling factors.
    #if 0
    Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
    if (dot(Row[0], Pdum3) < 0) {
        for (length_t i = 0; i < 3; i++) {
            Scale[i] *= static_cast<T>(-1);
            Row[i] *= static_cast<T>(-1);
        }
    }
    #endif

    orientation.y = asin(-Row[0][2]);
    if (cos(orientation.y) != 0) {
        orientation.x = atan2(Row[1][2], Row[2][2]);
        orientation.z = atan2(Row[0][1], Row[0][0]);
    } else {
        orientation.x = atan2(Row[2][0], Row[1][1]);
        orientation.z = 0;
    }

    return true;
}

#ifdef MATH_LOOKAT_EXAMPLE
// Custom implementation of the LookAt function
glm::mat4 calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp) {
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}


// Don't forget to replace glm::lookAt with your own version
// view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
view = calculate_lookAt_matrix(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
#endif

#endif

}

}
