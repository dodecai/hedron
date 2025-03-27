module;

#include <cassert>

export module Vite.Math.Vector;

import "Vite/Base/Platform/Support.h";
import Vite.Type.Concepts;
import Vite.Type.Standard;

export import Vite.Math.Converter;

export namespace Hedron {

///
/// Concepts
///

// Vector Types [bool|double|float|int16|int32|uint8|uint16|uint32]
template<typename T>
concept VectorNumerics =
std::is_same_v<T, bool>         ||
    std::is_same_v<T, double>   ||
    std::is_same_v<T, float>    ||
    std::is_same_v<T, int16>    ||
    std::is_same_v<T, int32>    ||
    std::is_same_v<T, uint8>    ||
    std::is_same_v<T, uint16>   ||
    std::is_same_v<T, uint32>;

// Vector Sizes [1|2|3|4]
template<size_t N>
concept VectorSizeRange = (N >= 1 && N <= 4);

///
#pragma region /// Vector Data

///
/// Enumerations
///

// Vector Aliases [None|Coordinate]
enum class VectorAliases {
    Coordinate,
    None,
};

#pragma pack(push, 1)
#pragma warning(push, 1)
#pragma warning(disable: 4201)

///
/// @brief Vector Data: Prototype
/// @tparam T Vector Type:  [bool|double|float|int16|int32|uint8|uint16|uint32]
/// @tparam N Vector Size:  [1|2|3|4]
/// @tparam A Vector Alias: [None|Coordinate]
///
template<VectorNumerics T, size_t N, VectorAliases A = VectorAliases::None> requires VectorSizeRange<N>
struct VectorData;

///
/// @brief Vector Data: None Specialization (simple array)
///
template<VectorNumerics T, size_t N>
struct VectorData<T, N, VectorAliases::None> {
    std::array<T, N> Data;
};

///
/// @brief Vector1D Data: Coordinates Specialization with additional aliases [X]
///

template<VectorNumerics T, size_t N> requires (N == 1)
struct VectorData<T, N, VectorAliases::Coordinate> {
    union {
        std::array<T, N> Data;
        struct {
            CPP_NO_UNIQUE_ADDRESS T X;
        };
    };
};

///
/// @brief Vector2D Data: Coordinates Specialization with additional aliases [X|Y]
///
template<VectorNumerics T, size_t N> requires (N == 2)
struct VectorData<T, N, VectorAliases::Coordinate> {
    union {
        std::array<T, N> Data;
        struct {
            CPP_NO_UNIQUE_ADDRESS T X;
            CPP_NO_UNIQUE_ADDRESS T Y;
        };
    };
};

///
/// @brief Vector3D Data: Coordinates Specialization with additional aliases [X|Y|Z]
///
template<VectorNumerics T, size_t N> requires (N == 3)
struct VectorData<T, N, VectorAliases::Coordinate> {
    union {
        std::array<T, N> Data;
        struct {
            CPP_NO_UNIQUE_ADDRESS T X;
            CPP_NO_UNIQUE_ADDRESS T Y;
            CPP_NO_UNIQUE_ADDRESS T Z;
        };
    };
};

///
/// @brief Vector4D Data: Coordinates Specialization with additional aliases [X|Y|Z|W]
///
template<VectorNumerics T, size_t N> requires (N == 4)
struct VectorData<T, N, VectorAliases::Coordinate> {
    union {
        std::array<T, N> Data;
        struct {
            CPP_NO_UNIQUE_ADDRESS T X;
            CPP_NO_UNIQUE_ADDRESS T Y;
            CPP_NO_UNIQUE_ADDRESS T Z;
            CPP_NO_UNIQUE_ADDRESS T W;
        };
    };
};

#pragma pack(pop)
#pragma warning(pop)

#pragma endregion
///

///
#pragma region /// Vector Base

///
/// @brief VectorBase: Prototype
/// @detail This is the vector base aggregation, which is used to implement the Vector class or similar arithmetic classes.
/// @todo Fix tests, which I broke with the new architecture.
///
template<VectorNumerics T, size_t N, VectorAliases A = VectorAliases::None>
struct VectorBase;

///
/// @brief VectorBase: Specialization
/// @detail This is the specialization for nearly all types (except booleans), which offers everything needed.
/// @note Not used aliases are set to std::monostate and don't require any storage.
///
template<VectorNumerics T, size_t N, VectorAliases A>
struct VectorBase: public VectorData<T, N, A> {
    /// Data
    using VectorData<T, N, A>::Data;

    /// Accessors
    operator T *() { return &Data[0]; }
    operator const T *() const { return &Data[0]; }
    T &operator[](size_t index) {
        if (index >= N) assert("The index is to large!");
        return Data[index];
    }
    const T &operator[](size_t index) const {
        if (index >= N) assert("The index is to large!");
        return Data[index];
    }

    /// Arithmetic
    constexpr inline auto operator+(const VectorBase &other) {
        return VectorBase(*this) += other;
    }
    constexpr inline auto operator-(const VectorBase &other) {
        return VectorBase(*this) -= other;
    }
    constexpr inline auto operator*(const VectorBase &other) {
        return VectorBase(*this) *= other;
    }
    constexpr inline auto operator/(const VectorBase &other) {
        return VectorBase(*this) /= other;
    }
    template<VectorNumerics S = T>
    constexpr inline auto operator+(S scalar) {
        return VectorBase(*this) += scalar;
    }
    template<VectorNumerics S = T>
    constexpr inline auto operator-(S scalar) {
        return VectorBase(*this) -= scalar;
    }
    template<VectorNumerics S = T>
    constexpr inline auto operator*(S scalar) {
        return VectorBase(*this) *= scalar;
    }
    template<VectorNumerics S = T>
    constexpr inline auto operator/(S scalar) {
        return VectorBase(*this) /= scalar;
    }
    // Allows scalar additions from the left and right
    template<VectorNumerics S = T>
    constexpr inline friend VectorBase operator+(S scalar, const VectorBase &v) {
        VectorBase result = v;
        for (size_t i = 0; i < N; i++) { result.Data[i] += scalar; }
        return result;
    }
    // Allows scalar multiplications from the left and right
    template<VectorNumerics S = T>
    constexpr inline friend VectorBase operator*(S scalar, const VectorBase &v) {
        VectorBase result = v;
        for (size_t i = 0; i < N; i++) { result.Data[i] *= scalar; }
        return result;
    }
    // Negates this vector.
    constexpr inline auto operator-() const {
        VectorBase result;
        for (size_t i = 0; i < N; i++) { result.Data[i] = -Data[i]; }
        return result;
    }

    /// Assignment
    constexpr inline VectorBase &operator=(const VectorBase &) = default;
    constexpr inline VectorBase &operator+=(const VectorBase &other) {
        for (size_t i = 0; i < N; i++) { Data[i] += other.Data[i]; }
        return *this;
    }
    constexpr inline VectorBase &operator-=(const VectorBase &other) {
        for (size_t i = 0; i < N; i++) { Data[i] -= other.Data[i]; }
        return *this;
    }
    constexpr inline VectorBase &operator*=(const VectorBase &other) {
        for (size_t i = 0; i < N; i++) { Data[i] *= other.Data[i]; }
        return *this;
    }
    constexpr inline VectorBase &operator/=(const VectorBase &other) {
        static constexpr T infinity = std::numeric_limits<T>::infinity() ? std::numeric_limits<T>::infinity() : std::numeric_limits<T>::max();
        for (size_t i = 0; i < N; i++) {
            auto value = Data[i] / other.Data[i];
            Data[i] = std::isfinite(value) ? value : infinity;
        }
        return *this;
    }
    template<VectorNumerics S = T>
    constexpr inline VectorBase &operator+=(S scalar) {
        for (size_t i = 0; i < N; i++) { Data[i] += scalar; }
        return *this;
    }
    template<VectorNumerics S = T>
    constexpr inline VectorBase &operator-=(S scalar) {
        for (size_t i = 0; i < N; i++) { Data[i] -= scalar; }
        return *this;
    }
    template<VectorNumerics S = T>
    constexpr inline VectorBase &operator*=(S scalar) {
        for (size_t i = 0; i < N; i++) { Data[i] *= scalar; }
        return *this;
    }
    template<VectorNumerics S = T>
    constexpr inline VectorBase &operator/=(S scalar) {
        static constexpr T infinity = std::numeric_limits<T>::infinity() ? std::numeric_limits<T>::infinity() : std::numeric_limits<T>::max();
        for (size_t i = 0; i < N; i++) {
            auto value = Data[i] / scalar;
            Data[i] = std::isfinite(value) ? value : infinity;
        }
        return *this;
    }

    /// Casts
    template <VectorNumerics U>
    operator array<U, N>() const {
        array<U, N> result;
        std::transform(Data.begin(), Data.end(), result.begin(), [](T value) { return static_cast<U>(value); });
        return result;
    }

    /// Comparison
    constexpr inline auto operator<=>(const VectorBase &other) const {
        for (size_t i = 0; i < N; ++i) {
            if (auto cmp = std::compare_strong_order_fallback(Data[i], other.Data[i]); cmp != 0) {
                return cmp;
            }
        }
        return std::strong_ordering::equal;
    }
    constexpr inline auto operator==(const VectorBase &other) const {
        return (*this <=> other) == 0;
    }

    /// Iterators
    inline auto begin() { return Data.begin(); }
    inline auto end() { return Data.end(); }
    inline auto rbegin() { return Data.rbegin(); }
    inline auto rend() { return Data.rend(); }
    constexpr inline auto begin() const { return Data.begin(); }
    constexpr inline auto end() const { return Data.end(); }
    constexpr inline auto rbegin() const { return Data.rbegin(); }
    constexpr inline auto rend() const { return Data.rend(); }

    /// Methods
    // Checks if the vector is a unit vector.
    //inline bool UnitVector(T epsilon = std::numeric_limits<T>::epsilon()) const {
    //    return std::abs(SquaredLength(*this) - 1) < epsilon;
    //}

    // Resets the vector to zero.
    inline void Reset() {
        std::fill(Data.begin(), Data.end(), static_cast<T>(0));
    }
};

///
/// @brief Vector: Boolean Specialization
/// @note Due to the nature of booleans, this specialization has no arithmetic operators or methods.
///
template<size_t N>
struct VectorBase<bool, N, VectorAliases::None>: public VectorData<bool, N, VectorAliases::None> {
    /// Data
    using VectorData<bool, N, VectorAliases::None>::Data;

    /// Accessors
    operator bool *() {
        return &Data[0];
    }
    operator const bool *() const {
        return &Data[0];
    }
    bool operator[](size_t index) {
        if (index >= N) assert("The index is to large!");
        return Data[index];
    }
    bool operator[](size_t index) const {
        if (index >= N) assert("The index is to large!");
        return Data[index];
    }

    /// Comparison
    auto operator<=>(const VectorBase &other) const {
        for (size_t i = 0; i < N; ++i) {
            if (auto cmp = std::compare_strong_order_fallback(Data[i], other.Data[i]); cmp != 0) {
                return cmp;
            }
        }
        return std::strong_ordering::equal;
    }
    auto operator==(const VectorBase &other) const {
        return (*this <=> other) == 0;
    }

    /// Casts
    template <VectorNumerics U>
    array<U, N> ToArray() const {
        array<U, N> result;
        std::transform(Data.begin(), Data.end(), result.begin(), [](bool b) {
            return static_cast<U>(b);
        });
        return result;
    }

    /// Iterators
    constexpr auto begin() { return Data.begin(); }
    constexpr auto end() { return Data.end(); }
    constexpr auto rbegin() { return Data.rbegin(); }
    constexpr auto rend() { return Data.rend(); }

    constexpr auto begin() const { return Data.begin(); }
    constexpr auto end() const { return Data.end(); }
    constexpr auto rbegin() const { return Data.rbegin(); }
    constexpr auto rend() const { return Data.rend(); }
};

#pragma endregion
///

///
#pragma region /// Vector Functions

///
/// @brief Calculates the cross product between a 2D vector and a scalar
/// @detail This is useful for operations such as creating normals or rotations in 2D space.
/// @note Produces a new 2D vector that is orthogonal to the input vector.
///
template<VectorNumerics T, size_t N, VectorAliases A> requires (N == 2)
constexpr inline VectorBase<T, N, A> Cross(T scalar, const VectorBase<T, N, A> &vector) {
    return { -scalar * vector[1], -scalar * vector[0] };
}

///
/// @brief Calculates the cross product between a scalar and a 2D vector.
/// @detail This is useful for operations such as creating normals or rotations in 2D space.
/// @note Produces a new 2D vector that is orthogonal to the input vector.
///
template<VectorNumerics T, size_t N, VectorAliases A> requires (N == 2)
constexpr inline VectorBase<T, N, A> Cross(const VectorBase<T, N, A> &vector, T scalar) {
    return { -vector[1] * scalar - vector[0] * scalar };
}

/// @brief Calculates the cross product between two vectors.
/// @detail
///  - 2D vectors: Produces a scalar representing the area of the parallelogram formed by the vectors.
///  - 3D vectors: Produces a 3D vector orthogonal to the input vectors.
///
template<VectorNumerics T, size_t N, VectorAliases A> requires (N >= 2 && N <= 3)
constexpr inline VectorBase<T, N, A> Cross(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    // 2D Cross-Product: Produces a scalar representing the area of the parallelogram.
    if constexpr (N == 2) {
        // left.X * right.Y - left.Y * right.X
        return { left[0] * right[1] - left[1] * right[0] };
    // 3D Cross-Product: Produces a vector orthogonal to the two input vectors.
    } else if constexpr (N == 3) {
        return {
            // left.Y * right.Z - left.Z * right.X
            left[1] * right[2] - left[2] * right[1],
            // left.Z * right.X - left.X * right.Z
            left[2] * right[0] - left[0] * right[2],
            // left.X * right.Y - left.Y * right.X
            left[0] * right[1] - left[1] * right[0]
         };
    }
}

///
/// @brief Calculates the dot product between this vector and another vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T Dot(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    T result {};
    for (size_t i = 0; i < N; i++) { result += left.Data[i] * right.Data[i]; }
    // return sum(a * b);
    return result;
}

///
/// @brief Returns the squared length (magnitude) of the vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T SquaredLength(const VectorBase<T, N, A> &vector) {
    return Dot(vector, vector);
}

///
/// @brief Returns the length (magnitude) of the vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T Length(const VectorBase<T, N, A> &vector) {
    return std::sqrt(SquaredLength(vector));
}

///
/// @brief Returns a normalized version of the vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline VectorBase<T, N, A> Normalize(const VectorBase<T, N, A> &vector) {
    return vector / Length(vector);
}

///
/// @brief Returns the squared distance between this vector and another vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T SquaredDistance(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    return SquaredLength(right - left);
}

///
/// @brief Returns the distance between this vector and another vector.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T Distance(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    return Length(right - left);
}

///
/// @brief Calculates the angle between this vector and another vector in radians.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T Angle(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    // ToDo: Decide if we allow this only for normalized vectors, cause normalized vectors we would not need the expensive / Length...
    T theta = Dot(left, right) / (Length(left) * Length(right));
    theta = std::clamp(theta, static_cast<T>(-1), static_cast<T>(1));
    return std::acos(theta);;
}

///
/// @brief Calculates the angle in Degrees between this vector and another vector in radians.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T AngleDegree(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    // ToDo: Decide if we allow this only for normalized vectors, cause normalized vectors we would not need the expensive / Length...
    static constexpr T degreeConversionFactor = static_cast<T>(180.0 / std::numbers::pi);
    T theta = Dot(left, right) / (Length(left) * Length(right));
    theta = std::clamp(theta, static_cast<T>(-1), static_cast<T>(1));
    return std::acos(theta) * degreeConversionFactor;
}

///
/// @brief Calculates the unsigned angle between two vectors in radians.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline T UAngle(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right) {
    // return uangle(normalize(a), normalize(b));
    T theta = Dot(left, right) / (Length(left) * Length(right));
    theta = std::clamp(theta, static_cast<T>(-1), static_cast<T>(1));
    return std::acos(theta);
}

///
/// @brief
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline VectorBase<T, N, A> Rotate(const VectorBase<T, N, A> &vector, T angle) requires (N == 2) {
    const T s = std::sin(angle);
    const T c = std::cos(angle);
    return { vector[0] * c - vector[1] * s, vector[0] * s + vector[1] * c };
}

///
/// @brief Linear Interpolation between this vector and another vector based on a given factor.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline VectorBase<T, N, A> Lerp(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right, T factor) {
    auto interpolated = left * (static_cast<T>(1) - factor) + right * factor;
    return interpolated;
}

///
/// @brief Normalized Linear Interpolation between this vector and another vector based on a given factor.
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline VectorBase<T, N, A> NormalizedLerp(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right, T factor) {
    return Normalize(Lerp(left, right, factor));
}

///
/// @brief Spherical Linear Interpolation
///
template<VectorNumerics T, size_t N, VectorAliases A>
constexpr inline VectorBase<T, N, A> SphericalLerp(const VectorBase<T, N, A> &left, const VectorBase<T, N, A> &right, T factor) {
    T theta = UAngle(left, right);
    if (theta == static_cast<T>(0)) return left;
    T sinTheta = std::sin(theta);
    return left * (std::sin(theta * (static_cast<T>(1) - factor)) / sinTheta) + right * (std::sin(theta * factor) / sinTheta);
}

//// Returns a vector with the absolute value of each component.
//inline VectorBase Abs() const {
//    VectorBase result {};
//    for (size_t i = 0; i < N; i++) {
//        result[i] = std::abs(Data[i]);
//    }
//    return result;
//}

//// Rounds up each component of this vector.
//inline VectorBase Ceil() const {
//    VectorBase result;
//    for (size_t i = 0; i < N; i++) {
//        result.Data[i] = std::ceil(Data[i]);
//    }
//    return result;
//}

///
/// @brief Clamps each component of the vector between given minimum and maximum values.
///
//template<VectorNumerics T, size_t N, VectorAliases A>
//constexpr inline VectorBase<T, N, A> Clamp(const VectorBase<T, N, A> &vector, T minVal, T maxVal) const {
//    auto result = vector;
//    for (size_t i = 0; i < N; i++) { result[i] = std::clamp(result[i], minVal, maxVal); }
//    return result;
//}

//// Rounds down each component of this vector.
//inline VectorBase Floor() const {
//    VectorBase result;
//    for (size_t i = 0; i < N; i++) {
//        result.Data[i] = std::floor(Data[i]);
//    }
//    return result;
//}

//// Returns the element-wise multiplication of two vectors.
//inline VectorBase Hadamard(const VectorBase &other) const {
//    VectorBase result;
//    for (size_t i = 0; i < N; i++) {
//        result.Data[i] = Data[i] * other.Data[i];
//    }
//    return result;
//}

//// Converts a 3D vector to a homogeneous 4D vector
//inline VectorBase<T, 4> Homogenize() const requires (N == 3) {
//    return VectorBase<T, 4>{Data[0], Data[1], Data[2], static_cast<T>(1)};
//}

//// Returns a vector with the maximum value from each pair of components from two vectors.
//inline VectorBase Max(const VectorBase &a, const VectorBase &b) {
//    VectorBase result = a;
//    for (size_t i = 0; i < N; i++) {
//        result[i] = std::max(a[i], b[i]);
//    }
//    return result;
//}

//// Returns a vector with the minimum value from each pair of components from two vectors.
//inline VectorBase Min(const VectorBase &a, const VectorBase &b) {
//    VectorBase result = a;
//    for (size_t i = 0; i < N; i++) {
//        result[i] = std::min(a[i], b[i]);
//    }
//    return result;
//}

//// Checks if two vectors are approximately equal within a given tolerance.
//inline bool NearlyEqual(const VectorBase &other, T epsilon = std::numeric_limits<T>::epsilon()) const {
//    for (size_t i = 0; i < N; i++) {
//        if (std::abs(Data[i] - other.Data[i]) > epsilon) {
//            return false;
//        }
//    }
//    return true;
//}

//// Rounds each component of this vector to the nearest integer.
//inline VectorBase Round() const {
//    VectorBase result;
//    for (size_t i = 0; i < N; i++) {
//        result.Data[i] = std::round(Data[i]);
//    }
//    return result;
//}

//// Returns a vector perpendicular to the current 2D vector.
//inline VectorBase Perpendicular() const requires (N == 2) {
//    return VectorBase { -Data[1], Data[0] };
//}

//// Projects this vector onto another vector.
//inline VectorBase Projection(const VectorBase &other) const requires (N >= 2) {
//    T squaredLength = other.SquaredLength();
//    T dotProduct = Dot(other);
//    return (dotProduct / squaredLength) * other;
//}

//// Raises each component of the vector to a given power.
//inline VectorBase Pow(T exponent) const {
//    VectorBase result = *this;
//    for (size_t i = 0; i < N; i++) {
//        result[i] = std::pow(result[i], exponent);
//    }
//    return result;
//}

// // Reflects the vector off a surface with the given normal.
//inline VectorBase Reflection(const VectorBase &normal) {
//    return *this - 2 * Projection(normal);
//}

//// Returns the rejection of this vector from another vector.
//inline VectorBase Reject(const VectorBase &other) const requires(N >= 2) {
//    return *this - Projection(other);
//}

#pragma endregion
///

///
/// Aliases
///

using Vector1D = VectorBase<float, 1, VectorAliases::Coordinate>;
using Vector2D = VectorBase<float, 2, VectorAliases::Coordinate>;
using Vector3D = VectorBase<float, 3, VectorAliases::Coordinate>;
using Vector4D = VectorBase<float, 4, VectorAliases::Coordinate>;

///
/// Overloads
///
/// Output Stream Support
template<typename S, VectorNumerics T, size_t N, VectorAliases A>
std::basic_ostream<S> &operator<<(std::basic_ostream<S> &stream, const VectorBase<T, N, A> &v) {
    stream << '[';
    for (size_t i = 0; i < N; ++i) {
        if (i > 0) stream << ', ';
        stream << v[i];
    }
    return stream << ']';
}

#pragma region OLD_STUFF


///
/// @brief VectorBase: Prototype
/// @detail This is the vector base aggregation, which is used to implement the Vector class or similar arithmetic classes.
///
template<typename T, size_t N>
struct Vector;

///
/// @brief Vector1D: Specialization
///
template<typename T>
struct Vector<T, 1> {
    // Data
    union {
        CPP_NO_UNIQUE_ADDRESS array<T, 1> Data;
        struct {
            T X;
        };
    };

    // Default
    constexpr Vector(): X() {}
    constexpr Vector(const T &x) : X(x) {}
    // NOTE: Vector<T,1> does NOT have a constructor from pointer, this can conflict with initializing its single element from zero
    template<typename U>
    constexpr explicit Vector(const Vector<U, 1> &v): Vector(static_cast<T>(v.X)) {}

    // Accessors
    constexpr T &operator[] (size_t i) { return Data[i]; }
    constexpr const T &operator[] (size_t i) const { return Data[i]; }

    // Converters
    template<typename U, typename = detail::conv_t<Vector, U>>
    constexpr Vector(const U &u): Vector(converter<Vector, U>{}(u)) {}
    template<typename U, typename = detail::conv_t<U, Vector>>
    constexpr operator U () const { return converter<U, Vector>{}(*this); }
};

///
/// @brief Vector2D: Specialization
///
template<typename T>
struct Vector<T, 2> {
    // Data
    union {
        CPP_NO_UNIQUE_ADDRESS array<T, 2> Data;
        struct {
            T X;
            T Y;
        };
    };

    // Default
    constexpr Vector(): X(), Y() {}
    constexpr Vector(const T &x, const T &y) : X(x), Y(y) {}
    constexpr explicit Vector(const T &s): Vector(s, s) {}
    constexpr explicit Vector(const T *p): Vector(p[0], p[1]) {}
    template<typename U>
    constexpr explicit Vector(const Vector<U, 2> &v): Vector(static_cast<T>(v.X), static_cast<T>(v.Y)) {}

    // Accessors
    constexpr const T &operator[] (size_t i) const { return Data[i]; }
    constexpr T &operator[] (size_t i) { Data[i]; }

    // Converters
    template<typename U, typename = detail::conv_t<Vector, U>>
    constexpr Vector(const U &u): Vector(converter<Vector, U>{}(u)) {}
    template<typename U, typename = detail::conv_t<U, Vector>>
    constexpr operator U () const { return converter<U, Vector>{}(*this); }
};

///
/// @brief Vector3D: Specialization
///
template<typename T>
struct Vector<T, 3> {
    // Data
    union {
        CPP_NO_UNIQUE_ADDRESS array<T, 3> Data;
        struct {
            T X;
            T Y;
            T Z;
        };
    };

    // Default
    constexpr Vector(): X(), Y(), Z() {}
    constexpr Vector(const T &x, const T &y, const T &z) : X(x), Y(y), Z(z) {}
    constexpr Vector(const Vector<T, 2> &xy, const T &z) : Vector(xy.X, xy.Y, z) {}
    constexpr explicit Vector(const T &s): Vector(s, s, s) {}
    constexpr explicit Vector(const T *p): Vector(p[0], p[1], p[2]) {}
    template<typename U>
    constexpr explicit Vector(const Vector<U, 3> &v): Vector(static_cast<T>(v.X), static_cast<T>(v.Y), static_cast<T>(v.Z)) {}

    // Accessors
    //constexpr const T &operator[] (size_t i) const { return Data[i]; }
    //constexpr T &operator[] (size_t i) { return Data[i]; }
    Vector<T, 2> &XY() { return *reinterpret_cast<Vector<T, 2> *>(this); }
    constexpr const Vector<T, 2> &XY() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }

    // Converters
    template<typename U, typename = detail::conv_t<Vector, U>>
    constexpr Vector(const U &u): Vector(converter<Vector, U>{}(u)) {}
    template<typename U, typename = detail::conv_t<U, Vector>>
    constexpr operator U () const { return converter<U, Vector>{}(*this); }
};

///
/// @brief Vector4D: Specialization
///
template<typename T>
struct Vector<T, 4> {
    // Data
    union {
        CPP_NO_UNIQUE_ADDRESS array<T, 4> Data;
        struct {
            T X;
            T Y;
            T Z;
            T W;
        };
    };

    // Default
    constexpr Vector(): X(), Y(), Z(), W() {}
    constexpr Vector(const T &x, const T &y, const T &z, const T &w) : X(x), Y(y), Z(z), W(w) {}
    constexpr Vector(const Vector<T, 2> &xy, const T &z, const T &w) : Vector(xy.X, xy.Y, z, w) {}
    constexpr Vector(const Vector<T, 3> &xyz, const T &w) : Vector(xyz.X, xyz.Y, xyz.Z, w) {}
    constexpr explicit Vector(const T &s): Vector(s, s, s, s) {}
    constexpr explicit Vector(const T *p): Vector(p[0], p[1], p[2], p[3]) {}
    template<typename U>
    constexpr explicit Vector(const Vector<U, 4> &v): Vector(static_cast<T>(v.X), static_cast<T>(v.Y), static_cast<T>(v.Z), static_cast<T>(v.W)) {}

    // Accessors
    constexpr T &operator[](size_t index) noexcept;
    constexpr const T &operator[](size_t index) const noexcept;
    Vector<T, 2> &XY() { return *reinterpret_cast<Vector<T, 2> *>(this); }
    Vector<T, 3> &XYZ() { return *reinterpret_cast<Vector<T, 3> *>(this); }
    constexpr const Vector<T, 2> &XY() const { return *reinterpret_cast<const Vector<T, 2> *>(this); }
    constexpr const Vector<T, 3> &XYZ() const { return *reinterpret_cast<const Vector<T, 3> *>(this); }

    // Converters
    template<typename U, typename = detail::conv_t<Vector, U>>
    constexpr Vector(const U &u): Vector(converter<Vector, U>{}(u)) {}
    template<typename U, typename = detail::conv_t<U, Vector>>
    constexpr operator U () const { return converter<U, Vector>{}(*this); }
};

///
/// Functions
///
// Produce a scalar by applying f(A,B) -> A to adjacent pairs of elements from a vector/matrix in left-to-right/column-major order (matching the associativity of arithmetic and logical operators)
template<typename F, typename A, typename B> constexpr A fold(F f, A a, const Vector<B, 1> &b) { return f(a, b.X); }
template<typename F, typename A, typename B> constexpr A fold(F f, A a, const Vector<B, 2> &b) { return f(f(a, b.X), b.Y); }
template<typename F, typename A, typename B> constexpr A fold(F f, A a, const Vector<B, 3> &b) { return f(f(f(a, b.X), b.Y), b.Z); }
template<typename F, typename A, typename B> constexpr A fold(F f, A a, const Vector<B, 4> &b) { return f(f(f(f(a, b.X), b.Y), b.Z), b.W); }

// Swizzles and subobjects
template<int... I, class T, size_t N> constexpr Vector<T, sizeof...(I)> swizzle(const Vector<T, N> &a) { return { detail::getter<I>{}(a)... }; }
template<int I0, int I1, class T, size_t N> constexpr Vector<T, I1 - I0> subVector(const Vector<T, N> &a) { return detail::swizzle(a, detail::make_seq<I0, I1>{}); }


template<typename T>
constexpr T cross(const Vector<T, 2> &a, const Vector<T, 2> &b) {
    return a.X * b.Y - a.Y * b.X;
}
template<typename T>
constexpr Vector<T, 2> cross(T a, const Vector<T, 2> &b) {
    return { -a * b.Y, a * b.X };
}
template<typename T>
constexpr Vector<T, 2> cross(const Vector<T, 2> &a, T b) {
    return { a.Y * b, -a.X * b };
}
template<typename T>
constexpr Vector<T, 3> cross(const Vector<T, 3> &a, const Vector<T, 3> &b) {
    return {
        a.Y * b.Z - a.Z * b.Y,
        a.Z * b.X - a.X * b.Z,
        a.X * b.Y - a.Y * b.X
    };
}

template<typename T, size_t N>
constexpr T dot(const Vector<T, N> &a, const Vector<T, N> &b) { return sum(a * b); }

template<typename T, size_t N>
constexpr T length2(const Vector<T, N> &a) { return dot(a, a); }
template<typename T, size_t N>
T length(const Vector<T, N> &a) { return std::sqrt(length2(a)); }

template<typename T, size_t N>
Vector<T, N> normalize(const Vector<T, N> &a) { return a / length(a); }

template<typename T, size_t N>
constexpr T distance2(const Vector<T, N> &a, const Vector<T, N> &b) { return length2(b - a); }
template<typename T, size_t N>
T distance(const Vector<T, N> &a, const Vector<T, N> &b) { return length(b - a); }

template<typename T, size_t N>
T uangle(const Vector<T, N> &a, const Vector<T, N> &b) { T d = dot(a, b); return d > 1 ? 0 : std::acos(d < -1 ? -1 : d); }
template<typename T, size_t N>
T angle(const Vector<T, N> &a, const Vector<T, N> &b) { return uangle(normalize(a), normalize(b)); }

template<typename T>
Vector<T, 2> rot(T a, const Vector<T, 2> &v) { const T s = std::sin(a), c = std::cos(a); return { v.X * c - v.Y * s, v.X * s + v.Y * c }; }

template<typename T, size_t N>
Vector<T, N> nlerp(const Vector<T, N> &a, const Vector<T, N> &b, T t) { return normalize(lerp(a, b, t)); }
template<typename T, size_t N>
Vector<T, N> slerp(const Vector<T, N> &a, const Vector<T, N> &b, T t) { T th = uangle(a, b); return th == 0 ? a : a * (std::sin(th * (1 - t)) / std::sin(th)) + b * (std::sin(th * t) / std::sin(th)); }

// Vectors can be used as ranges
template<typename T, size_t N>
T *begin(Vector<T, N> &a) { return &a.X; }

template<typename T, size_t N>
T *end(Vector<T, N> &a) { return begin(a) + N; }

template<typename T, size_t N>
const T *begin(const Vector<T, N> &a) { return &a.X; }

template<typename T, size_t N>
const T *end(const Vector<T, N> &a) { return begin(a) + N; }



// Provide implicit conversion between linalg::Vector<T,N> and std::array<T,N>
template<typename T>
struct converter<Vector<T, 1>, std::array<T, 1>> { Vector<T, 1> operator() (const std::array<T, 1> &a) const { return { a[0] }; } };

template<typename T>
struct converter<Vector<T, 2>, std::array<T, 2>> { Vector<T, 2> operator() (const std::array<T, 2> &a) const { return { a[0], a[1] }; } };
template<typename T>
struct converter<Vector<T, 3>, std::array<T, 3>> { Vector<T, 3> operator() (const std::array<T, 3> &a) const { return { a[0], a[1], a[2] }; } };
template<typename T>
struct converter<Vector<T, 4>, std::array<T, 4>> { Vector<T, 4> operator() (const std::array<T, 4> &a) const { return { a[0], a[1], a[2], a[3] }; } };

template<typename T>
struct converter<std::array<T, 1>, Vector<T, 1>> { std::array<T, 1> operator() (const Vector<T, 1> &a) const { return { a[0] }; } };
template<typename T>
struct converter<std::array<T, 2>, Vector<T, 2>> { std::array<T, 2> operator() (const Vector<T, 2> &a) const { return { a[0], a[1] }; } };
template<typename T>
struct converter<std::array<T, 3>, Vector<T, 3>> { std::array<T, 3> operator() (const Vector<T, 3> &a) const { return { a[0], a[1], a[2] }; } };
template<typename T>
struct converter<std::array<T, 4>, Vector<T, 4>> { std::array<T, 4> operator() (const Vector<T, 4> &a) const { return { a[0], a[1], a[2], a[3] }; } };

///
/// Aliases
/// Provides aliases for common element types and vector sizes
///
using Bool1 = Vector<bool, 1>;
using Bool2 = Vector<bool, 2>;
using Bool3 = Vector<bool, 3>;
using Bool4 = Vector<bool, 4>;
using Byte1 = Vector<uint8, 1>;
using Byte2 = Vector<uint8, 2>;
using Byte3 = Vector<uint8, 3>;
using Byte4 = Vector<uint8, 4>;
using Double1 = Vector<double, 1>;
using Double2 = Vector<double, 2>;
using Double3 = Vector<double, 3>;
using Double4 = Vector<double, 4>;
using Float1 = Vector<float, 1>;
using Float2 = Vector<float, 2>;
using Float3 = Vector<float, 3>;
using Float4 = Vector<float, 4>;
using Int1 = Vector<int32, 1>;
using Int2 = Vector<int32, 2>;
using Int3 = Vector<int32, 3>;
using Int4 = Vector<int32, 4>;
using Short1 = Vector<int16, 1>;
using Short2 = Vector<int16, 2>;
using Short3 = Vector<int16, 3>;
using Short4 = Vector<int16, 4>;
using UInt1 = Vector<uint32, 1>;
using UInt2 = Vector<uint32, 2>;
using UInt3 = Vector<uint32, 3>;
using UInt4 = Vector<uint32, 4>;
using UShort1 = Vector<uint16, 1>;
using UShort2 = Vector<uint16, 2>;
using UShort3 = Vector<uint16, 3>;
using UShort4 = Vector<uint16, 4>;

#pragma endregion

}

///
/// Global Overloads
///
namespace std {

// Provide specializations for std::hash<...>
template<Hedron::VectorNumerics T, size_t N, Hedron::VectorAliases A>
struct hash<Hedron::VectorBase<T, N, A>> {
    size_t operator()(const Hedron::VectorBase<T, N, A> &vector) const {
        hash<T> h;
        size_t result = 0;
        for (size_t i = 0; i < N; ++i) { result ^= h(vector[i]) << i; }
        return result;
    }
};

//template<Hedron::VectorNumerics T, size_t N, Hedron::VectorAliases A>
//string to_string(const Hedron::VectorBase<T, N, A> &vector) {
//    string result;
//    result.reserve(N * 6);
//    result = "[ ";
//    for (const auto &element : vector) {
//        result += format("{}, ", element);
//    }
//    result = result.substr(0, result.length() - 2);
//    result += " ]";
//    return result;
//}

//template<Hedron::VectorNumerics T, size_t N, Hedron::VectorAliases A>
//struct formatter<Hedron::VectorBase<T, N, A>> {
//    constexpr auto parse(format_parse_context &ctx) {
//        return ctx.begin();
//    }
//
//    const auto format(const Hedron::VectorBase<T, N, A> &vector, format_context &ctx) {
//        ostringstream stream;
//        stream << "[ ";
//        for (size_t i = 0; i < N; ++i) {
//            stream << vector[i] << (i < N - 1 ? ", " : " ");
//        }
//        stream << "]";
//        return format_to(ctx.out(), "{}", stream.str());
//    }
//};

}


///
/// Implementation
///
module: private;

namespace Hedron::Test {

// These tests are executed during the compilation phase, so no need to call them.
void Compiler() {
    // Ensure that the sizes are correct
    static_assert( 1 == sizeof(VectorBase<bool,   1>), "VectorBase<bool>[1]:   The type size should be 1 byte(s)!");
    static_assert( 2 == sizeof(VectorBase<bool,   2>), "VectorBase<bool>[2]:   The type size should be 2 byte(s)!");
    static_assert( 3 == sizeof(VectorBase<bool,   3>), "VectorBase<bool>[3]:   The type size should be 3 byte(s)!");
    static_assert( 4 == sizeof(VectorBase<bool,   4>), "VectorBase<bool>[4]:   The type size should be 4 byte(s)!");
    static_assert( 1 == sizeof(VectorBase<uint8,  1>), "VectorBase<uint8>[1]:  The type size should be 1 byte(s)!");
    static_assert( 2 == sizeof(VectorBase<uint8,  2>), "VectorBase<uint8>[2]:  The type size should be 2 byte(s)!");
    static_assert( 3 == sizeof(VectorBase<uint8,  3>), "VectorBase<uint8>[3]:  The type size should be 3 byte(s)!");
    static_assert( 4 == sizeof(VectorBase<uint8,  4>), "VectorBase<uint8>[4]:  The type size should be 4 byte(s)!");
    static_assert( 8 == sizeof(VectorBase<double, 1>), "VectorBase<double>[1]: The type size should be 8 bytes(s)!");
    static_assert(16 == sizeof(VectorBase<double, 2>), "VectorBase<double>[2]: The type size should be 16 bytes(s)!");
    static_assert(24 == sizeof(VectorBase<double, 3>), "VectorBase<double>[3]: The type size should be 24 bytes(s)!");
    static_assert(32 == sizeof(VectorBase<double, 4>), "VectorBase<double>[4]: The type size should be 32 bytes(s)!");
    static_assert( 4 == sizeof(VectorBase<float,  1>), "VectorBase<float>[1]:  The type size should be 4 bytes(s)!");
    static_assert( 8 == sizeof(VectorBase<float,  2>), "VectorBase<float>[2]:  The type size should be 8 bytes(s)!");
    static_assert(12 == sizeof(VectorBase<float,  3>), "VectorBase<float>[3]:  The type size should be 12 bytes(s)!");
    static_assert(16 == sizeof(VectorBase<float,  4>), "VectorBase<float>[4]:  The type size should be 16 bytes(s)!");
    static_assert( 2 == sizeof(VectorBase<int16,  1>), "VectorBase<int16>[1]:  The type size should be 2 byte(s)!");
    static_assert( 4 == sizeof(VectorBase<int16,  2>), "VectorBase<int16>[2]:  The type size should be 4 byte(s)!");
    static_assert( 6 == sizeof(VectorBase<int16,  3>), "VectorBase<int16>[3]:  The type size should be 6 byte(s)!");
    static_assert( 8 == sizeof(VectorBase<int16,  4>), "VectorBase<int16>[4]:  The type size should be 8 byte(s)!");
    static_assert( 4 == sizeof(VectorBase<int32,  1>), "VectorBase<int32>[1]:  The type size should be 4 byte(s)!");
    static_assert( 8 == sizeof(VectorBase<int32,  2>), "VectorBase<int32>[2]:  The type size should be 8 byte(s)!");
    static_assert(12 == sizeof(VectorBase<int32,  3>), "VectorBase<int32>[3]:  The type size should be 12 byte(s)!");
    static_assert(16 == sizeof(VectorBase<int32,  4>), "VectorBase<int32>[4]:  The type size should be 16 byte(s)!");
    static_assert( 2 == sizeof(VectorBase<uint16, 1>), "VectorBase<uint16>[1]: The type size should be 2 bytes(s)!");
    static_assert( 4 == sizeof(VectorBase<uint16, 2>), "VectorBase<uint16>[2]: The type size should be 4 bytes(s)!");
    static_assert( 6 == sizeof(VectorBase<uint16, 3>), "VectorBase<uint16>[3]: The type size should be 6 bytes(s)!");
    static_assert( 8 == sizeof(VectorBase<uint16, 4>), "VectorBase<uint16>[4]: The type size should be 8 bytes(s)!");
    static_assert( 4 == sizeof(VectorBase<uint32, 1>), "VectorBase<uint32>[1]: The type size should be 4 bytes(s)!");
    static_assert( 8 == sizeof(VectorBase<uint32, 2>), "VectorBase<uint32>[2]: The type size should be 8 bytes(s)!");
    static_assert(12 == sizeof(VectorBase<uint32, 3>), "VectorBase<uint32>[3]: The type size should be 12 bytes(s)!");
    static_assert(16 == sizeof(VectorBase<uint32, 4>), "VectorBase<uint32>[4]: The type size should be 16 bytes(s)!");
}

}
