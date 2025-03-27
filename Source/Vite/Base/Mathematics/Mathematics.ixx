export module Vite.Math;

export import Vite.Math.Geometry;
export import Vite.Math.Converter;
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

using Bool1 = VectorBase<bool, 1>;
using Bool2 = VectorBase<bool, 2>;
using Bool3 = VectorBase<bool, 3>;
using Bool4 = VectorBase<bool, 4>;
using Byte1 = VectorBase<uint8, 1>;
using Byte2 = VectorBase<uint8, 2>;
using Byte3 = VectorBase<uint8, 3>;
using Byte4 = VectorBase<uint8, 4>;
using Double1 = VectorBase<double, 1>;
using Double2 = VectorBase<double, 2>;
using Double3 = VectorBase<double, 3>;
using Double4 = VectorBase<double, 4>;
using Float1 = VectorBase<float, 1>;
using Float2 = VectorBase<float, 2>;
using Float3 = VectorBase<float, 3>;
using Float4 = VectorBase<float, 4>;
using Int1 = VectorBase<int32, 1>;
using Int2 = VectorBase<int32, 2>;
using Int3 = VectorBase<int32, 3>;
using Int4 = VectorBase<int32, 4>;
using Short1 = VectorBase<int16, 1>;
using Short2 = VectorBase<int16, 2>;
using Short3 = VectorBase<int16, 3>;
using Short4 = VectorBase<int16, 4>;
using UInt1 = VectorBase<uint32, 1>;
using UInt2 = VectorBase<uint32, 2>;
using UInt3 = VectorBase<uint32, 3>;
using UInt4 = VectorBase<uint32, 4>;
using UShort1 = VectorBase<uint16, 1>;
using UShort2 = VectorBase<uint16, 2>;
using UShort3 = VectorBase<uint16, 3>;
using UShort4 = VectorBase<uint16, 4>;


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


// Factory functions for 3D spatial transformations (will possibly be removed or changed in a future version)
enum fwd_axis { neg_z, pos_z };                 // Should projection matrices be generated assuming forward is {0,0,-1} or {0,0,1}
enum z_range { neg_one_to_one, zero_to_one };   // Should projection matrices map z into the range of [-1,1] or [0,1]?
template<class T> Vector<T, 4> rotation_quat(const Vector<T, 3> &axis, T angle) { return { axis * std::sin(angle / 2), std::cos(angle / 2) }; }
template<class T> Vector<T, 4> rotation_quat(const Matrix<T, 3, 3> &m);
template<class T> Matrix<T, 4, 4> translation_matrix(const Vector<T, 3> &translation) { return { {1,0,0,0},{0,1,0,0},{0,0,1,0},{translation,1} }; }
template<class T> Matrix<T, 4, 4> rotation_matrix(const Vector<T, 4> &rotation) { return { {qxdir(rotation),0}, {qydir(rotation),0}, {qzdir(rotation),0}, {0,0,0,1} }; }
template<class T> Matrix<T, 4, 4> scaling_matrix(const Vector<T, 3> &scaling) { return { {scaling.x,0,0,0}, {0,scaling.y,0,0}, {0,0,scaling.z,0}, {0,0,0,1} }; }
template<class T> Matrix<T, 4, 4> pose_matrix(const Vector<T, 4> &q, const Vector<T, 3> &p) { return { {qxdir(q),0}, {qydir(q),0}, {qzdir(q),0}, {p,1} }; }
template<class T> Matrix<T, 4, 4> lookat_matrix(const Vector<T, 3> &eye, const Vector<T, 3> &center, const Vector<T, 3> &view_y_dir, fwd_axis fwd = neg_z);
template<class T> Matrix<T, 4, 4> frustum_matrix(T x0, T x1, T y0, T y1, T n, T f, fwd_axis a = neg_z, z_range z = neg_one_to_one);
template<class T> Matrix<T, 4, 4> perspective_matrix(T fovy, T aspect, T n, T f, fwd_axis a = neg_z, z_range z = neg_one_to_one) { T y = n * std::tan(fovy / 2), x = y * aspect; return frustum_matrix(-x, x, -y, y, n, f, a, z); }


}


export {
    // Definitions of functions too long to be defined inline
    template<class T> constexpr Hedron::Matrix<T, 3, 3> Hedron::adjugate(const Matrix<T, 3, 3> &a) {
        return { {a.y.y * a.z.z - a.z.y * a.y.z, a.z.y * a.x.z - a.x.y * a.z.z, a.x.y * a.y.z - a.y.y * a.x.z},
                {a.y.z * a.z.x - a.z.z * a.y.x, a.z.z * a.x.x - a.x.z * a.z.x, a.x.z * a.y.x - a.y.z * a.x.x},
                {a.y.x * a.z.y - a.z.x * a.y.y, a.z.x * a.x.y - a.x.x * a.z.y, a.x.x * a.y.y - a.y.x * a.x.y} };
    }

    template<class T> constexpr Hedron::Matrix<T, 4, 4> Hedron::adjugate(const Matrix<T, 4, 4> &a) {
        return { {a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w,
                 a.x.y * a.w.z * a.z.w + a.z.y * a.x.z * a.w.w + a.w.y * a.z.z * a.x.w - a.w.y * a.x.z * a.z.w - a.z.y * a.w.z * a.x.w - a.x.y * a.z.z * a.w.w,
                 a.x.y * a.y.z * a.w.w + a.w.y * a.x.z * a.y.w + a.y.y * a.w.z * a.x.w - a.x.y * a.w.z * a.y.w - a.y.y * a.x.z * a.w.w - a.w.y * a.y.z * a.x.w,
                 a.x.y * a.z.z * a.y.w + a.y.y * a.x.z * a.z.w + a.z.y * a.y.z * a.x.w - a.x.y * a.y.z * a.z.w - a.z.y * a.x.z * a.y.w - a.y.y * a.z.z * a.x.w},
                {a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x,
                 a.x.z * a.z.w * a.w.x + a.w.z * a.x.w * a.z.x + a.z.z * a.w.w * a.x.x - a.x.z * a.w.w * a.z.x - a.z.z * a.x.w * a.w.x - a.w.z * a.z.w * a.x.x,
                 a.x.z * a.w.w * a.y.x + a.y.z * a.x.w * a.w.x + a.w.z * a.y.w * a.x.x - a.x.z * a.y.w * a.w.x - a.w.z * a.x.w * a.y.x - a.y.z * a.w.w * a.x.x,
                 a.x.z * a.y.w * a.z.x + a.z.z * a.x.w * a.y.x + a.y.z * a.z.w * a.x.x - a.x.z * a.z.w * a.y.x - a.y.z * a.x.w * a.z.x - a.z.z * a.y.w * a.x.x},
                {a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y,
                 a.x.w * a.w.x * a.z.y + a.z.w * a.x.x * a.w.y + a.w.w * a.z.x * a.x.y - a.x.w * a.z.x * a.w.y - a.w.w * a.x.x * a.z.y - a.z.w * a.w.x * a.x.y,
                 a.x.w * a.y.x * a.w.y + a.w.w * a.x.x * a.y.y + a.y.w * a.w.x * a.x.y - a.x.w * a.w.x * a.y.y - a.y.w * a.x.x * a.w.y - a.w.w * a.y.x * a.x.y,
                 a.x.w * a.z.x * a.y.y + a.y.w * a.x.x * a.z.y + a.z.w * a.y.x * a.x.y - a.x.w * a.y.x * a.z.y - a.z.w * a.x.x * a.y.y - a.y.w * a.z.x * a.x.y},
                {a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z,
                 a.x.x * a.z.y * a.w.z + a.w.x * a.x.y * a.z.z + a.z.x * a.w.y * a.x.z - a.x.x * a.w.y * a.z.z - a.z.x * a.x.y * a.w.z - a.w.x * a.z.y * a.x.z,
                 a.x.x * a.w.y * a.y.z + a.y.x * a.x.y * a.w.z + a.w.x * a.y.y * a.x.z - a.x.x * a.y.y * a.w.z - a.w.x * a.x.y * a.y.z - a.y.x * a.w.y * a.x.z,
                 a.x.x * a.y.y * a.z.z + a.z.x * a.x.y * a.y.z + a.y.x * a.z.y * a.x.z - a.x.x * a.z.y * a.y.z - a.y.x * a.x.y * a.z.z - a.z.x * a.y.y * a.x.z} };
    }

    template<class T> constexpr T Hedron::determinant(const Matrix<T, 4, 4> &a) {
        return a.x.x * (a.y.y * a.z.z * a.w.w + a.w.y * a.y.z * a.z.w + a.z.y * a.w.z * a.y.w - a.y.y * a.w.z * a.z.w - a.z.y * a.y.z * a.w.w - a.w.y * a.z.z * a.y.w)
            + a.x.y * (a.y.z * a.w.w * a.z.x + a.z.z * a.y.w * a.w.x + a.w.z * a.z.w * a.y.x - a.y.z * a.z.w * a.w.x - a.w.z * a.y.w * a.z.x - a.z.z * a.w.w * a.y.x)
            + a.x.z * (a.y.w * a.z.x * a.w.y + a.w.w * a.y.x * a.z.y + a.z.w * a.w.x * a.y.y - a.y.w * a.w.x * a.z.y - a.z.w * a.y.x * a.w.y - a.w.w * a.z.x * a.y.y)
            + a.x.w * (a.y.x * a.w.y * a.z.z + a.z.x * a.y.y * a.w.z + a.w.x * a.z.y * a.y.z - a.y.x * a.z.y * a.w.z - a.w.x * a.y.y * a.z.z - a.z.x * a.w.y * a.y.z);
    }

    template<class T> Hedron::Vector<T, 4> Hedron::rotation_quat(const Matrix<T, 3, 3> &m) {
        const Vector<T, 4> q { m.x.x - m.y.y - m.z.z, m.y.y - m.x.x - m.z.z, m.z.z - m.x.x - m.y.y, m.x.x + m.y.y + m.z.z }, s[] {
            {1, m.x.y + m.y.x, m.z.x + m.x.z, m.y.z - m.z.y},
            {m.x.y + m.y.x, 1, m.y.z + m.z.y, m.z.x - m.x.z},
            {m.x.z + m.z.x, m.y.z + m.z.y, 1, m.x.y - m.y.x},
            {m.y.z - m.z.y, m.z.x - m.x.z, m.x.y - m.y.x, 1} };
        return copysign(normalize(sqrt(max(T(0), T(1) + q))), s[argmax(q)]);
    }

    template<class T> Hedron::Matrix<T, 4, 4> Hedron::lookat_matrix(const Vector<T, 3> &eye, const Vector<T, 3> &center, const Vector<T, 3> &view_y_dir, fwd_axis a) {
        const Vector<T, 3> f = normalize(center - eye), z = a == pos_z ? f : -f, x = normalize(cross(view_y_dir, z)), y = cross(z, x);
        return inverse(Matrix<T, 4, 4>{{x, 0}, { y,0 }, { z,0 }, { eye,1 }});
    }

    template<class T> Hedron::Matrix<T, 4, 4> Hedron::frustum_matrix(T x0, T x1, T y0, T y1, T n, T f, fwd_axis a, z_range z) {
        const T s = a == pos_z ? T(1) : T(-1), o = z == neg_one_to_one ? n : 0;
        return { {2 * n / (x1 - x0),0,0,0}, {0,2 * n / (y1 - y0),0,0}, {-s * (x0 + x1) / (x1 - x0),-s * (y0 + y1) / (y1 - y0),s * (f + o) / (f - n),s}, {0,0,-(n + o) * f / (f - n),0} };
    }

}

