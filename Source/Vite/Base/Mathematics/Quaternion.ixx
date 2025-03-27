export module Vite.Math.Quaternion;

import Vite.Math.Vector;
import Vite.Type.Concepts;
import Vite.Type.Standard;

export import Vite.Math.Converter;

export namespace Hedron {


// Support for quaternion algebra using 4D vectors, representing xi + yj + zk + w
template<class T> constexpr Vector<T, 4> qconj(const Vector<T, 4> &q) { return { -q.x,-q.y,-q.z,q.w }; }
template<class T> Vector<T, 4> qinv(const Vector<T, 4> &q) { return qconj(q) / length2(q); }
template<class T> Vector<T, 4> qexp(const Vector<T, 4> &q) { const auto v = q.xyz(); const auto vv = length(v); return std::exp(q.w) * Vector<T, 4>{v *(vv > 0 ? std::sin(vv) / vv : 0), std::cos(vv)}; }
template<class T> Vector<T, 4> qlog(const Vector<T, 4> &q) { const auto v = q.xyz(); const auto vv = length(v), qq = length(q); return { v * (vv > 0 ? std::acos(q.w / qq) / vv : 0), std::log(qq) }; }
template<class T> Vector<T, 4> qpow(const Vector<T, 4> &q, const T &p) { const auto v = q.xyz(); const auto vv = length(v), qq = length(q), th = std::acos(q.w / qq); return std::pow(qq, p) * Vector<T, 4>{v *(vv > 0 ? std::sin(p * th) / vv : 0), std::cos(p *th)}; }
template<class T> constexpr Vector<T, 4> qmul(const Vector<T, 4> &a, const Vector<T, 4> &b) { return { a.x * b.w + a.w * b.x + a.y * b.z - a.z * b.y, a.y * b.w + a.w * b.y + a.z * b.x - a.x * b.z, a.z * b.w + a.w * b.z + a.x * b.y - a.y * b.x, a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z }; }
template<class T, class... R> constexpr Vector<T, 4> qmul(const Vector<T, 4> &a, R... r) { return qmul(a, qmul(r...)); }

// Support for 3D spatial rotations using quaternions, via qmul(qmul(q, v), qconj(q))
template<class T> constexpr Vector<T, 3> qxdir(const Vector<T, 4> &q) { return { q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z, (q.x * q.y + q.z * q.w) * 2, (q.z * q.x - q.y * q.w) * 2 }; }
template<class T> constexpr Vector<T, 3> qydir(const Vector<T, 4> &q) { return { (q.x * q.y - q.z * q.w) * 2, q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z, (q.y * q.z + q.x * q.w) * 2 }; }
template<class T> constexpr Vector<T, 3> qzdir(const Vector<T, 4> &q) { return { (q.z * q.x + q.y * q.w) * 2, (q.y * q.z - q.x * q.w) * 2, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z }; }
template<class T> constexpr Matrix<T, 3, 3> qMatrix(const Vector<T, 4> &q) { return { qxdir(q), qydir(q), qzdir(q) }; }
template<class T> constexpr Vector<T, 3> qrot(const Vector<T, 4> &q, const Vector<T, 3> &v) { return qxdir(q) * v.x + qydir(q) * v.y + qzdir(q) * v.z; }
template<class T> T qangle(const Vector<T, 4> &q) { return std::atan2(length(q.xyz()), q.w) * 2; }
template<class T> Vector<T, 3> qaxis(const Vector<T, 4> &q) { return normalize(q.xyz()); }
template<class T> Vector<T, 4> qnlerp(const Vector<T, 4> &a, const Vector<T, 4> &b, T t) { return nlerp(a, dot(a, b) < 0 ? -b : b, t); }
template<class T> Vector<T, 4> qslerp(const Vector<T, 4> &a, const Vector<T, 4> &b, T t) { return slerp(a, dot(a, b) < 0 ? -b : b, t); }



#pragma pack(push, 1)
#pragma warning(push, 1)
#pragma warning(disable: 4201)

///
/// @brief Quaternion
/// @todo Implement global overloads and fix tests, which I broke with the new architecture,
/// also finishing the comments would help.
///
//template<typename_floating_point T>
//struct QuaternionBase {
//    /// Data
//    union {
//        array<T, 4> Data;
//        struct {
//            T w, x, y, z;
//        };
//    };
//
//    /// Default
//    QuaternionBase(): w(1), x(0), y(0), z(0) {}
//    QuaternionBase(T w, T x, T y, T z): w(w), x(x), y(y), z(z) {}
//    QuaternionBase(const Vector3 &source) {
//        T pitch = source.X * 0.5;
//        T yaw = source.Y * 0.5;
//        T roll = source.Z * 0.5;
//
//        T cp = std::cos(pitch);
//        T sp = std::sin(pitch);
//        T cy = std::cos(yaw);
//        T sy = std::sin(yaw);
//        T cr = std::cos(roll);
//        T sr = std::sin(roll);
//
//        w = cp * cy * cr + sp * sy * sr;
//        x = sp * cy * cr - cp * sy * sr;
//        y = cp * sy * cr + sp * cy * sr;
//        z = cp * cy * sr - sp * sy * cr;
//    }
//    //Quaternion(const MatrixBase<T, 4> &source) {
//    //    T trace = source.At(0, 0) + source.At(1, 1) + source.At(2, 2);
//    //    if (trace > 0) {
//    //        T s = 0.5 / std::sqrt(trace + 1.0);
//    //        w = 0.25 / s;
//    //        x = (source.At(2, 1) - source.At(1, 2)) * s;
//    //        y = (source.At(0, 2) - source.At(2, 0)) * s;
//    //        z = (source.At(1, 0) - source.At(0, 1)) * s;
//    //    } else {
//    //        if (source.At(0, 0) > source.At(1, 1) && source.At(0, 0) > source.At(2, 2)) {
//    //            T s = 2.0 * std::sqrt(1.0 + source.At(0, 0) - source.At(1, 1) - source.At(2, 2));
//    //            w = (source.At(2, 1) - source.At(1, 2)) / s;
//    //            x = 0.25 * s;
//    //            y = (source.At(0, 1) + source.At(1, 0)) / s;
//    //            z = (source.At(0, 2) + source.At(2, 0)) / s;
//    //        } else if (source.At(1, 1) > source.At(2, 2)) {
//    //            T s = 2.0 * std::sqrt(1.0 + source.At(1, 1) - source.At(0, 0) - source.At(2, 2));
//    //            w = (source.At(0, 2) - source.At(2, 0)) / s;
//    //            x = (source.At(0, 1) + source.At(1, 0)) / s;
//    //            y = 0.25 * s;
//    //            z = (source.At(1, 2) + source.At(2, 1)) / s;
//    //        } else {
//    //            T s = 2.0 * std::sqrt(1.0 + source.At(2, 2) - source.At(0, 0) - source.At(1, 1));
//    //            w = (source.At(1, 0) - source.At(0, 1)) / s;
//    //            x = (source.At(0, 2) + source.At(2, 0)) / s;
//    //            y = (source.At(1, 2) + source.At(2, 1)) / s;
//    //            z = 0.25 * s;
//    //        }
//    //    }
//    //}
//
//    /// Arithmetic
//    QuaternionBase operator+(const QuaternionBase &q) const {
//        return {
//            w + q.w,
//            x + q.x,
//            y + q.y,
//            z + q.z
//        };
//    }
//    QuaternionBase operator-(const QuaternionBase &q) const {
//        return {
//            w - q.w,
//            x - q.x,
//            y - q.y,
//            z - q.z
//        };
//    }
//    QuaternionBase operator*(const QuaternionBase &q) const {
//        return {
//            w * q.w - x * q.x - y * q.y - z * q.z,
//            w * q.x + x * q.w + y * q.z - z * q.y,
//            w * q.y - x * q.z + y * q.w + z * q.x,
//            w * q.z + x * q.y - y * q.x + z * q.w
//        };
//    }
//    QuaternionBase operator*(const T scalar) const {
//        return {
//            w * scalar,
//            x * scalar,
//            y * scalar,
//            z * scalar
//        };
//    }
//
//    /// Assignment
//    QuaternionBase &operator*=(const QuaternionBase &q) {
//        *this = *this * q;
//        return *this;
//    }
//
//    /// Comparison
//    auto operator<=>(const QuaternionBase &other) const {
//        if (auto cmp = w <=> other.w; cmp != 0) return cmp;
//        if (auto cmp = x <=> other.x; cmp != 0) return cmp;
//        if (auto cmp = y <=> other.y; cmp != 0) return cmp;
//        return z <=> other.z;
//    }
//    auto operator==(const QuaternionBase &other) const {
//        return (*this <=> other) == 0;
//    }
//
//    /// Casts
//    /*MatrixBase<T, 4> ToMatrix() const {
//        MatrixBase<T, 4> mat;
//        mat(0, 0) = 1 - 2 * y * y - 2 * z * z;
//        mat(0, 1) = 2 * x * y - 2 * z * w;
//        mat(0, 2) = 2 * x * z + 2 * y * w;
//        mat(1, 0) = 2 * x * y + 2 * z * w;
//        mat(1, 1) = 1 - 2 * x * x - 2 * z * z;
//        mat(1, 2) = 2 * y * z - 2 * x * w;
//        mat(2, 0) = 2 * x * z - 2 * y * w;
//        mat(2, 1) = 2 * y * z + 2 * x * w;
//        mat(2, 2) = 1 - 2 * x * x - 2 * y * y;
//        return mat;
//    }*/
//    Vector3 ToEuler() const {
//        T roll, pitch, yaw;
//        T sinr_cosp = 2 * (w * x + y * z);
//        T cosr_cosp = 1 - 2 * (x * x + y * y);
//        roll = std::atan2(sinr_cosp, cosr_cosp);
//
//        T sinp = 2 * (w * y - z * x);
//        if (std::abs(sinp) >= 1)
//            pitch = std::copysign(std::numbers::pi / 2, sinp); // use 90 degrees if out of range
//        else
//            pitch = std::asin(sinp);
//
//        T siny_cosp = 2 * (w * z + x * y);
//        T cosy_cosp = 1 - 2 * (y * y + z * z);
//        yaw = std::atan2(siny_cosp, cosy_cosp);
//
//        return Vector3(pitch, yaw, roll);
//    }
//
//    ///
//    /// Methods
//    ///
//
//    // 
//    QuaternionBase Conjugate() const {
//        return { w, -x, -y, -z };
//    }
//
//    // 
//    T Dot(const QuaternionBase &q) const {
//        return w * q.w + x * q.x + y * q.y + z * q.z;
//    }
//
//    // 
//    T Length() const {
//        return std::sqrt(w * w + x * x + y * y + z * z);
//    }
//
//    // 
//    T Magnitude() const {
//        return std::sqrt(w * w + x * x + y * y + z * z);
//    }
//
//    // 
//    T Max() {
//        return std::max({ w, y, z, x });
//    }
//
//    // 
//    T Min() {
//        return std::min({ w, y, z, x });
//    }
//
//    // 
//    QuaternionBase Normalized() const {
//        T mag = Magnitude();
//        return { w / mag, x / mag, y / mag, z / mag };
//    }
//
//    // 
//    QuaternionBase Slerp(const QuaternionBase &q, T t) const {
//        T dot = Dot(q);
//        T theta = std::acos(dot);
//        T sin_theta = std::sin(theta);
//
//        if (std::abs(sin_theta) < 0.001) {
//            return (*this + (q - *this) * t).Normalized();
//        }
//
//        T scale1 = std::sin((1.0 - t) * theta) / sin_theta;
//        T scale2 = std::sin(t * theta) / sin_theta;
//
//        return (*this * scale1 + q * scale2).Normalized();
//    }
//
//    // 
//    T SquaredLength() const {
//        return w * w + x * x + y * y + z * z;
//    }
//
//private:
//    /// Helpers
//    bool AlmostEqual(float a, float b, float epsilon = 0.000001f) {
//        return std::abs(a - b) < epsilon;
//    }
//};
//
//#pragma pack(pop)
//#pragma warning(pop)
//
/////
///// Aliases
/////
//using Quaternion = QuaternionBase<float>;
//using DQuaternion = QuaternionBase<double>;

}

///
/// Global Overloads
///
namespace std {}

///
/// Implementation
///
module: private;

namespace Hedron::Test {

// These tests are executed during the compilation phase, so no need to call them.
void Compiler() {
    //// Ensure that the sizes are correct
    //static_assert(16 == sizeof(QuaternionBase<float>),  "Quaternion<float>:   The type size should be 16 byte(s)!");
    //static_assert(32 == sizeof(QuaternionBase<double>), "Quaternion<double>:  The type size should be 32 byte(s)!");
}

}
