export module Vite.Math.Matrix;

import Vite.Math.Quaternion;
import Vite.Math.Vector;
import Vite.Type.Concepts;
import Vite.Type.Standard;

export import Vite.Math.Converter;

export namespace Hedron {

// Small, fixed-size matrix type, consisting of exactly M rows and N columns of type T, stored in column-major order.
template<class T, size_t M, size_t N> struct Matrix;

// Converter

///
/// @brief MatrixNx1: Specialization
///
template<class T, size_t M> struct Matrix<T, M, 1> {
    // Types
    typedef Vector<T, M> V;

    // Data
    V X;

    constexpr Matrix(): X() {}
    constexpr Matrix(const V &x) : X(x) {}
    constexpr explicit Matrix(const T &s): X(s) {}
    constexpr explicit Matrix(const T *p): X(p + M * 0) {}
    template<class U>
    constexpr explicit Matrix(const Matrix<U, M, 1> &m): Matrix(V(m.X)) {}
    constexpr Vector<T, 1> Row(int i) const { return { X[i] }; }
    constexpr const V &operator[] (int j) const { return X; }
    constexpr V &operator[] (int j) { return X; }

    template<class U, class = detail::conv_t<Matrix, U>> constexpr Matrix(const U &u) : Matrix(converter<Matrix, U>{}(u)) {}
    template<class U, class = detail::conv_t<U, Matrix>> constexpr operator U () const { return converter<U, Matrix>{}(*this); }
};

///
/// @brief MatrixNx2: Specialization
///
template<class T, size_t M> struct Matrix<T, M, 2> {
    // Types
    typedef Vector<T, M> V;

    // Data
    V X;
    V Y;

    constexpr Matrix(): X(), Y() {}
    constexpr Matrix(const V &x, const V &y) : X(x), Y(y) {}
    constexpr explicit Matrix(const T &s): X(s), Y(s) {}
    constexpr explicit Matrix(const T *p): X(p + M * 0), Y(p + M * 1) {}
    template<class U>
    constexpr explicit Matrix(const Matrix<U, M, 2> &m): Matrix(V(m.X), V(m.Y)) {}
    constexpr Vector<T, 2> Row(int i) const { return { X[i], Y[i] }; }
    constexpr const V &operator[] (int j) const { return j == 0 ? X : Y; }
    constexpr V &operator[] (int j) { return j == 0 ? X : Y; }

    template<class U, class = detail::conv_t<Matrix, U>> constexpr Matrix(const U &u) : Matrix(converter<Matrix, U>{}(u)) {}
    template<class U, class = detail::conv_t<U, Matrix>> constexpr operator U () const { return converter<U, Matrix>{}(*this); }
};

///
/// @brief MatrixNx3: Specialization
///
template<class T, size_t M> struct Matrix<T, M, 3> {
    // Types
    typedef Vector<T, M> V;

    // Data
    V X;
    V Y;
    V Z;

    constexpr Matrix(): X(), Y(), Z() {}
    constexpr Matrix(const V &x, const V &y, const V &z) : X(x), Y(y), Z(z) {}
    constexpr explicit Matrix(const T &s): X(s), Y(s), Z(s) {}
    constexpr explicit Matrix(const T *p): X(p + M * 0), Y(p + M * 1), Z(p + M * 2) {}
    template<class U>
    constexpr explicit Matrix(const Matrix<U, M, 3> &m): Matrix(V(m.X), V(m.Y), V(m.Z)) {}
    constexpr Vector<T, 3> Row(int i) const { return { X[i], Y[i], Z[i] }; }
    constexpr const V &operator[] (int j) const { return j == 0 ? X : j == 1 ? Y : Z; }
    constexpr V &operator[] (int j) { return j == 0 ? X : j == 1 ? Y : Z; }

    template<class U, class = detail::conv_t<Matrix, U>> constexpr Matrix(const U &u) : Matrix(converter<Matrix, U>{}(u)) {}
    template<class U, class = detail::conv_t<U, Matrix>> constexpr operator U () const { return converter<U, Matrix>{}(*this); }
};

///
/// @brief MatrixNx4: Specialization
///
template<class T, size_t M> struct Matrix<T, M, 4> {
    // Types
    typedef Vector<T, M> V;

    // Data
    V X;
    V Y;
    V Z;
    V W;

    constexpr Matrix(): X(), Y(), Z(), W() {}
    constexpr Matrix(const V &x, const V &y, const V &z, const V &w) : X(x), Y(y), Z(z), W(w) {}
    constexpr explicit Matrix(const T &s): X(s), Y(s), Z(s), W(s) {}
    constexpr explicit Matrix(const T *p): X(p + M * 0), Y(p + M * 1), Z(p + M * 2), W(p + M * 3) {}
    template<class U>
    constexpr explicit Matrix(const Matrix<U, M, 4> &m): Matrix(V(m.X), V(m.Y), V(m.Z), V(m.W)) {}
    constexpr Vector<T, 4> Row(int i) const { return { X[i], Y[i], Z[i], W[i] }; }
    constexpr const V &operator[] (int j) const { return j == 0 ? X : j == 1 ? Y : j == 2 ? Z : W; }
    constexpr V &operator[] (int j) { return j == 0 ? X : j == 1 ? Y : j == 2 ? Z : W; }

    template<class U, class = detail::conv_t<Matrix, U>> constexpr Matrix(const U &u) : Matrix(converter<Matrix, U>{}(u)) {}
    template<class U, class = detail::conv_t<U, Matrix>> constexpr operator U () const { return converter<U, Matrix>{}(*this); }
};

///
/// Functions
///
// Define a type which will convert to the multiplicative identity of any square matrix
struct identity_t { constexpr explicit identity_t(int) {} };
template<class T> struct converter<Matrix<T, 1, 1>, identity_t> { constexpr Matrix<T, 1, 1> operator() (identity_t) const { return { Vector<T,1>{1} }; } };
template<class T> struct converter<Matrix<T, 2, 2>, identity_t> { constexpr Matrix<T, 2, 2> operator() (identity_t) const { return { {1,0},{0,1} }; } };
template<class T> struct converter<Matrix<T, 3, 3>, identity_t> { constexpr Matrix<T, 3, 3> operator() (identity_t) const { return { {1,0,0},{0,1,0},{0,0,1} }; } };
template<class T> struct converter<Matrix<T, 4, 4>, identity_t> { constexpr Matrix<T, 4, 4> operator() (identity_t) const { return { {1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1} }; } };
constexpr identity_t identity { 1 };

// Produce a scalar by applying f(A,B) -> A to adjacent pairs of elements from a vector/matrix in left-to-right/column-major order (matching the associativity of arithmetic and logical operators)
template<class F, class A, class B, size_t M> constexpr A fold(F f, A a, const Matrix<B, M, 1> &b) { return fold(f, a, b.X); }
template<class F, class A, class B, size_t M> constexpr A fold(F f, A a, const Matrix<B, M, 2> &b) { return fold(f, fold(f, a, b.X), b.Y); }
template<class F, class A, class B, size_t M> constexpr A fold(F f, A a, const Matrix<B, M, 3> &b) { return fold(f, fold(f, fold(f, a, b.X), b.Y), b.Z); }
template<class F, class A, class B, size_t M> constexpr A fold(F f, A a, const Matrix<B, M, 4> &b) { return fold(f, fold(f, fold(f, fold(f, a, b.X), b.Y), b.Z), b.W); }

// Swizzles and subobjects
template<int I0, int J0, int I1, int J1, class T, int M, int N> constexpr Matrix<T, I1 - I0, J1 - J0>    subMatrix(const Matrix<T, M, N> &a) { return detail::swizzle(a, detail::make_seq<I0, I1>{}, detail::make_seq<J0, J1>{}); }

// Support for matrix algebra
template<class T, int M> constexpr Vector<T, M> mul(const Matrix<T, M, 1> &a, const Vector<T, 1> &b) { return a.x * b.x; }
template<class T, int M> constexpr Vector<T, M> mul(const Matrix<T, M, 2> &a, const Vector<T, 2> &b) { return a.x * b.x + a.y * b.y; }
template<class T, int M> constexpr Vector<T, M> mul(const Matrix<T, M, 3> &a, const Vector<T, 3> &b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
template<class T, int M> constexpr Vector<T, M> mul(const Matrix<T, M, 4> &a, const Vector<T, 4> &b) { return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w; }
template<class T, int M, int N> constexpr Matrix<T, M, 1> mul(const Matrix<T, M, N> &a, const Matrix<T, N, 1> &b) { return { mul(a,b.x) }; }
template<class T, int M, int N> constexpr Matrix<T, M, 2> mul(const Matrix<T, M, N> &a, const Matrix<T, N, 2> &b) { return { mul(a,b.x), mul(a,b.y) }; }
template<class T, int M, int N> constexpr Matrix<T, M, 3> mul(const Matrix<T, M, N> &a, const Matrix<T, N, 3> &b) { return { mul(a,b.x), mul(a,b.y), mul(a,b.z) }; }
template<class T, int M, int N> constexpr Matrix<T, M, 4> mul(const Matrix<T, M, N> &a, const Matrix<T, N, 4> &b) { return { mul(a,b.x), mul(a,b.y), mul(a,b.z), mul(a,b.w) }; }
template<class T, int M, int N, int P> constexpr Vector<T, M> mul(const Matrix<T, M, N> &a, const Matrix<T, N, P> &b, const Vector<T, P> &c) { return mul(mul(a, b), c); }
template<class T, int M, int N, int P, int Q> constexpr Matrix<T, M, Q> mul(const Matrix<T, M, N> &a, const Matrix<T, N, P> &b, const Matrix<T, P, Q> &c) { return mul(mul(a, b), c); }
template<class T, int M, int N, int P, int Q> constexpr Vector<T, M> mul(const Matrix<T, M, N> &a, const Matrix<T, N, P> &b, const Matrix<T, P, Q> &c, const Vector<T, Q> &d) { return mul(mul(a, b, c), d); }
template<class T, int M, int N, int P, int Q, int R> constexpr Matrix<T, M, R> mul(const Matrix<T, M, N> &a, const Matrix<T, N, P> &b, const Matrix<T, P, Q> &c, const Matrix<T, Q, R> &d) { return mul(mul(a, b, c), d); }
template<class T, int M> constexpr Matrix<T, M, 1> outerprod(const Vector<T, M> &a, const Vector<T, 1> &b) { return { a * b.x }; }
template<class T, int M> constexpr Matrix<T, M, 2> outerprod(const Vector<T, M> &a, const Vector<T, 2> &b) { return { a * b.x, a * b.y }; }
template<class T, int M> constexpr Matrix<T, M, 3> outerprod(const Vector<T, M> &a, const Vector<T, 3> &b) { return { a * b.x, a * b.y, a * b.z }; }
template<class T, int M> constexpr Matrix<T, M, 4> outerprod(const Vector<T, M> &a, const Vector<T, 4> &b) { return { a * b.x, a * b.y, a * b.z, a * b.w }; }
template<class T> constexpr Vector<T, 1> diagonal(const Matrix<T, 1, 1> &a) { return { a.x.x }; }
template<class T> constexpr Vector<T, 2> diagonal(const Matrix<T, 2, 2> &a) { return { a.x.x, a.y.y }; }
template<class T> constexpr Vector<T, 3> diagonal(const Matrix<T, 3, 3> &a) { return { a.x.x, a.y.y, a.z.z }; }
template<class T> constexpr Vector<T, 4> diagonal(const Matrix<T, 4, 4> &a) { return { a.x.x, a.y.y, a.z.z, a.w.w }; }
template<class T, int N> constexpr T trace(const Matrix<T, N, N> &a) { return sum(diagonal(a)); }
template<class T, int M> constexpr Matrix<T, M, 1> transpose(const Matrix<T, 1, M> &m) { return { m.row(0) }; }
template<class T, int M> constexpr Matrix<T, M, 2> transpose(const Matrix<T, 2, M> &m) { return { m.row(0), m.row(1) }; }
template<class T, int M> constexpr Matrix<T, M, 3> transpose(const Matrix<T, 3, M> &m) { return { m.row(0), m.row(1), m.row(2) }; }
template<class T, int M> constexpr Matrix<T, M, 4> transpose(const Matrix<T, 4, M> &m) { return { m.row(0), m.row(1), m.row(2), m.row(3) }; }
template<class T, int M> constexpr Matrix<T, 1, M> transpose(const Vector<T, M> &m) { return transpose(Matrix<T, M, 1>(m)); }
template<class T> constexpr Matrix<T, 1, 1> adjugate(const Matrix<T, 1, 1> &a) { return { Vector<T,1>{1} }; }
template<class T> constexpr Matrix<T, 2, 2> adjugate(const Matrix<T, 2, 2> &a) { return { {a.y.y, -a.x.y}, {-a.y.x, a.x.x} }; }
template<class T> constexpr Matrix<T, 3, 3> adjugate(const Matrix<T, 3, 3> &a);
template<class T> constexpr Matrix<T, 4, 4> adjugate(const Matrix<T, 4, 4> &a);
template<class T, int N> constexpr Matrix<T, N, N> coMatrix(const Matrix<T, N, N> &a) { return transpose(adjugate(a)); }
template<class T> constexpr T determinant(const Matrix<T, 1, 1> &a) { return a.x.x; }
template<class T> constexpr T determinant(const Matrix<T, 2, 2> &a) { return a.x.x * a.y.y - a.x.y * a.y.x; }
template<class T> constexpr T determinant(const Matrix<T, 3, 3> &a) { return a.x.x * (a.y.y * a.z.z - a.z.y * a.y.z) + a.x.y * (a.y.z * a.z.x - a.z.z * a.y.x) + a.x.z * (a.y.x * a.z.y - a.z.x * a.y.y); }
template<class T> constexpr T determinant(const Matrix<T, 4, 4> &a);
template<class T, int N> constexpr Matrix<T, N, N> inverse(const Matrix<T, N, N> &a) { return adjugate(a) / determinant(a); }

// Matrices can be used as ranges
template<class T, int M, int N> Vector<T, M> *begin(Matrix<T, M, N> &a) { return &a.x; }
template<class T, int M, int N> const Vector<T, M> *begin(const Matrix<T, M, N> &a) { return &a.x; }
template<class T, int M, int N> Vector<T, M> *end(Matrix<T, M, N> &a) { return begin(a) + N; }
template<class T, int M, int N> const Vector<T, M> *end(const Matrix<T, M, N> &a) { return begin(a) + N; }
///
/// Aliases
/// Provide aliases for common element types and matrix sizes
///
using Bool1x1 = Matrix<bool, 1, 1>;
using Bool1x2 = Matrix<bool, 1, 2>;
using Bool1x3 = Matrix<bool, 1, 3>;
using Bool1x4 = Matrix<bool, 1, 4>;
using Bool2x1 = Matrix<bool, 2, 1>;
using Bool2x2 = Matrix<bool, 2, 2>;
using Bool2x3 = Matrix<bool, 2, 3>;
using Bool2x4 = Matrix<bool, 2, 4>;
using Bool3x1 = Matrix<bool, 3, 1>;
using Bool3x2 = Matrix<bool, 3, 2>;
using Bool3x3 = Matrix<bool, 3, 3>;
using Bool3x4 = Matrix<bool, 3, 4>;
using Bool4x1 = Matrix<bool, 4, 1>;
using Bool4x2 = Matrix<bool, 4, 2>;
using Bool4x3 = Matrix<bool, 4, 3>;
using Bool4x4 = Matrix<bool, 4, 4>;
using Double1x1 = Matrix<double, 1, 1>;
using Double1x2 = Matrix<double, 1, 2>;
using Double1x3 = Matrix<double, 1, 3>;
using Double1x4 = Matrix<double, 1, 4>;
using Double2x1 = Matrix<double, 2, 1>;
using Double2x2 = Matrix<double, 2, 2>;
using Double2x3 = Matrix<double, 2, 3>;
using Double2x4 = Matrix<double, 2, 4>;
using Double3x1 = Matrix<double, 3, 1>;
using Double3x2 = Matrix<double, 3, 2>;
using Double3x3 = Matrix<double, 3, 3>;
using Double3x4 = Matrix<double, 3, 4>;
using Double4x1 = Matrix<double, 4, 1>;
using Double4x2 = Matrix<double, 4, 2>;
using Double4x3 = Matrix<double, 4, 3>;
using Double4x4 = Matrix<double, 4, 4>;
using Float1x1 = Matrix<float, 1, 1>;
using Float1x2 = Matrix<float, 1, 2>;
using Float1x3 = Matrix<float, 1, 3>;
using Float1x4 = Matrix<float, 1, 4>;
using Float2x1 = Matrix<float, 2, 1>;
using Float2x2 = Matrix<float, 2, 2>;
using Float2x3 = Matrix<float, 2, 3>;
using Float2x4 = Matrix<float, 2, 4>;
using Float3x1 = Matrix<float, 3, 1>;
using Float3x2 = Matrix<float, 3, 2>;
using Float3x3 = Matrix<float, 3, 3>;
using Float3x4 = Matrix<float, 3, 4>;
using Float4x1 = Matrix<float, 4, 1>;
using Float4x2 = Matrix<float, 4, 2>;
using Float4x3 = Matrix<float, 4, 3>;
using Float4x4 = Matrix<float, 4, 4>;
using Int1x1 = Matrix<int, 1, 1>;
using Int1x2 = Matrix<int, 1, 2>;
using Int1x3 = Matrix<int, 1, 3>;
using Int1x4 = Matrix<int, 1, 4>;
using Int2x1 = Matrix<int, 2, 1>;
using Int2x2 = Matrix<int, 2, 2>;
using Int2x3 = Matrix<int, 2, 3>;
using Int2x4 = Matrix<int, 2, 4>;
using Int3x1 = Matrix<int, 3, 1>;
using Int3x2 = Matrix<int, 3, 2>;
using Int3x3 = Matrix<int, 3, 3>;
using Int3x4 = Matrix<int, 3, 4>;
using Int4x1 = Matrix<int, 4, 1>;
using Int4x2 = Matrix<int, 4, 2>;
using Int4x3 = Matrix<int, 4, 3>;
using Int4x4 = Matrix<int, 4, 4>;



// Provide output streaming operators, writing something that resembles an aggregate literal that could be used to construct the specified value
template<class C, class T, size_t M> std::basic_ostream<C> &operator << (std::basic_ostream<C> &out, const Matrix<T, M, 1> &m) { return out << '{' << m[0] << '}'; }
template<class C, class T, size_t M> std::basic_ostream<C> &operator << (std::basic_ostream<C> &out, const Matrix<T, M, 2> &m) { return out << '{' << m[0] << ',' << m[1] << '}'; }
template<class C, class T, size_t M> std::basic_ostream<C> &operator << (std::basic_ostream<C> &out, const Matrix<T, M, 3> &m) { return out << '{' << m[0] << ',' << m[1] << ',' << m[2] << '}'; }
template<class C, class T, size_t M> std::basic_ostream<C> &operator << (std::basic_ostream<C> &out, const Matrix<T, M, 4> &m) { return out << '{' << m[0] << ',' << m[1] << ',' << m[2] << ',' << m[3] << '}'; }

#pragma pack(push, 1)
#pragma warning(push, 1)

///
/// @brief Matrix[2-4 X 2-4]D
/// @todo Implement global overloads and fix tests, which I broke with the new architecture.
///
//template<typename_floating_point T, size_t N>
//struct MatrixBase {
//    /// Data
//    array<array<T, N>, N> Data {};
//
//    /// Accessors
//    operator T *() {
//        return &Data[0][0];
//    }
//    operator const T *() const {
//        return &Data[0][0];
//    }
//    T &At(size_t Row, size_t col) {
//        return Data[Row][col];
//    }
//    const T &At(size_t Row, size_t col) const {
//        return Data[Row][col];
//    }
//
//    /// Arithmetic
//    MatrixBase operator+(const MatrixBase &other) {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result.Data[i][j] = Data[i][j] + other.Data[i][j];
//            }
//        }
//        return result;
//    }
//    MatrixBase operator-(const MatrixBase &other) {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result.Data[i][j] = Data[i][j] - other.Data[i][j];
//            }
//        }
//        return result;
//    }
//    MatrixBase operator*(const MatrixBase &other) const {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                for (size_t k = 0; k < N; k++) {
//                    result.Data[i][j] += Data[i][k] * other.Data[k][j];
//                }
//            }
//        }
//        return result;
//    }
//    MatrixBase operator*(T scalar) {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result.Data[i][j] = Data[i][j] * scalar;
//            }
//        }
//        return result;
//    }
//    MatrixBase operator/(T scalar) {
//        ValidateScalar(scalar);
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result.Data[i][j] = Data[i][j] / scalar;
//            }
//        }
//        return result;
//    }
//    //template<MatrixNumerics T, size_t N>
//    //friend MatrixBase<T, N> operator*(const MatrixBase<T, N> &matrix, T scalar) {
//    //    MatrixBase<T, N> result;
//    //    for (size_t i = 0; i < N; ++i) {
//    //        for (size_t j = 0; j < N; ++j) {
//    //            result.At(i, j) = matrix.At(i, j) * scalar;
//    //        }
//    //    }
//    //    return result;
//    //}
//    //template<MatrixNumerics T, size_t N>
//    //friend MatrixBase<T, N> operator/(const MatrixBase<T, N> &matrix, T scalar) {
//    //    ValidateScalar(scalar);  // Ensure scalar is not zero
//    //    MatrixBase<T, N> result;
//    //    for (size_t i = 0; i < N; ++i) {
//    //        for (size_t j = 0; j < N; ++j) {
//    //            result.At(i, j) = matrix.At(i, j) / scalar;
//    //        }
//    //    }
//    //    return result;
//    //}
//
//    // Negates the matrix.
//    MatrixBase operator-() const {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result[i][j] = -Data[i][j];
//            }
//        }
//        return result;
//    }
//
//    /// Assignment
//    MatrixBase &operator+=(const MatrixBase &other) {
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                Data[i][j] += other[i][j];
//            }
//        }
//        return *this;
//    }
//    MatrixBase &operator-=(const MatrixBase &other) {
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                Data[i][j] -= other[i][j];
//            }
//        }
//        return *this;
//    }
//    MatrixBase &operator*=(const MatrixBase &other) {
//        *this = *this * other;
//        return *this;
//    }
//    MatrixBase &operator*=(T scalar) {
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                Data[i][j] *= scalar;
//            }
//        }
//        return *this;
//    }
//    MatrixBase &operator/=(T scalar) {
//        ValidateScalar(scalar);
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                Data[i][j] /= scalar;
//            }
//        }
//        return *this;
//    }
//
//    ///
//    /// Methods
//    ///
//    
//    // Computes the determinant of the matrix (supports 2x2, 3x3 and 4x4 matrices).
//    T Determinant() const requires (N >= 2 && N <= 4) {
//        if constexpr (N == 2) {
//            return Data[0][0] * Data[1][1] - Data[0][1] * Data[1][0];
//        } else if constexpr (N == 3) {
//            return
//                Data[0][0] * (Data[1][1] * Data[2][2] - Data[1][2] * Data[2][1]) -
//                Data[0][1] * (Data[1][0] * Data[2][2] - Data[1][2] * Data[2][0]) +
//                Data[0][2] * (Data[1][0] * Data[2][1] - Data[1][1] * Data[2][0]);
//        } else if constexpr (N == 3) {
//            T det = 0;
//            for (size_t j = 0; j < 4; ++j) {
//                MatrixBase<T, 3> subMatrix;
//                for (size_t subi = 0, origi = 1; origi < 4; ++origi) {
//                    for (size_t subj = 0, origj = 0; origj < 4; ++origj) {
//                        if (origj == j) continue;
//                        subMatrix.Data[subi][subj] = Data[origi][origj];
//                        ++subj;
//                    }
//                    ++subi;
//                }
//                T subDet = subMatrix.Determinant();
//                det += (j % 2 == 0 ? 1 : -1) * Data[0][j] * subDet;
//            }
//            return det;
//        }
//    }
//
//    // Constructs an identity matrix of size NxN.
//    static MatrixBase Identity() {
//        MatrixBase m;
//        for (size_t i = 0; i < N; i++) {
//            m.Data[i][i] = 1;
//        }
//        return m;
//    }
//
//    // Computes the inverse of the matrix (supports 2x2, 3x3 and 4x4 matrices).
//    MatrixBase Inverse() const requires (N == 2 && N <= 4) {
//        T determinant = Determinant();
//        //ValidateScalar(determinant);
//
//        if constexpr (N == 2) {
//            MatrixBase result;
//            result.Data[0][0] = Data[1][1] / determinant;
//            result.Data[0][1] = -Data[0][1] / determinant;
//            result.Data[1][0] = -Data[1][0] / determinant;
//            result.Data[1][1] = Data[0][0] / determinant;
//            return result;
//        } else if constexpr (N == 3) {
//            MatrixBase result;
//            result.Data[0][0] = (Data[1][1] * Data[2][2] - Data[2][1] * Data[1][2]) / determinant;
//            result.Data[0][1] = -(Data[0][1] * Data[2][2] - Data[0][2] * Data[2][1]) / determinant;
//            result.Data[0][2] = (Data[0][1] * Data[1][2] - Data[0][2] * Data[1][1]) / determinant;
//            result.Data[1][0] = -(Data[1][0] * Data[2][2] - Data[1][2] * Data[2][0]) / determinant;
//            result.Data[1][1] = (Data[0][0] * Data[2][2] - Data[0][2] * Data[2][0]) / determinant;
//            result.Data[1][2] = -(Data[0][0] * Data[1][2] - Data[1][0] * Data[0][2]) / determinant;
//            result.Data[2][0] = (Data[1][0] * Data[2][1] - Data[2][0] * Data[1][1]) / determinant;
//            result.Data[2][1] = -(Data[0][0] * Data[2][1] - Data[2][0] * Data[0][1]) / determinant;
//            result.Data[2][2] = (Data[0][0] * Data[1][1] - Data[1][0] * Data[0][1]) / determinant;
//
//            return result;
//        } else if constexpr (N == 4) {
//            MatrixBase adj;
//
//            for (size_t i = 0; i < 4; ++i) {
//                for (size_t j = 0; j < 4; ++j) {
//                    MatrixBase<T, 3> subMatrix;
//                    for (size_t subi = 0, origi = 0; origi < 4; ++origi) {
//                        if (origi == i) continue;
//                        for (size_t subj = 0, origj = 0; origj < 4; ++origj) {
//                            if (origj == j) continue;
//                            subMatrix.Data[subi][subj] = Data[origi][origj];
//                            ++subj;
//                        }
//                        ++subi;
//                    }
//                    T subDet = subMatrix.Determinant();
//                    T cofactor = ((i + j) % 2 == 0 ? 1 : -1) * subDet;
//                    adj.Data[j][i] = cofactor;
//                }
//            }
//
//            MatrixBase result = adj / determinant;
//            return result;
//        }
//    }
//
//    // Constructs a look-at matrix for 3D transformations (supports only 4x4 matrices).
//    MatrixBase LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up) requires (N == 4) {
//        Vector3 f = (center - eye).Normalized();
//        Vector3 r = up.Cross(f).Normalized();
//        Vector3 u = f.Cross(r);
//
//        MatrixBase result = Identity();
//        result[0][0] = r.X; result[0][1] = r.Y; result[0][2] = r.Z;
//        result[1][0] = u.X; result[1][1] = u.Y; result[1][2] = u.Z;
//        result[2][0] = -f.X; result[2][1] = -f.Y; result[2][2] = -f.Z;
//        result[3][0] = -r.Dot(eye);
//        result[3][1] = -u.Dot(eye);
//        result[3][2] = f.Dot(eye);
//
//        return result;
//    }
//
//    // Projects a 3D point to 2D screen space (supports only 4x4 matrices).
//    MatrixBase Project(const Vector3 &world, const MatrixBase &view, const MatrixBase &projection) requires (N == 4) {
//        MatrixBase result;
//        MatrixBase wvp = projection * view;
//        Vector4 homogenousWorld(world.X, world.Y, world.Z, 1.0f);
//        Vector4 projected = wvp * homogenousWorld;
//        if (projected.W != 0) {
//            result[0][0] = projected.X / projected.W;
//            result[1][1] = projected.Y / projected.W;
//            result[2][2] = projected.Z / projected.W;
//        }
//        return result;
//    }
//
//    // Unprojects a 2D screen point back to 3D world space (supports only 4x4 matrices).
//    MatrixBase Reject(const Vector3 &screen, const MatrixBase &view, const MatrixBase &projection) requires (N == 4) {
//        MatrixBase inverseProjection = projection.Inverse();
//        MatrixBase inverseView = view.Inverse();
//        Vector4 homogenousScreen(screen.X, screen.Y, screen.Z, 1.0f);
//        Vector4 unprojected = inverseProjection * homogenousScreen;
//        Vector4 world = inverseView * unprojected;
//        MatrixBase result;
//        result[0][0] = world.X / world.W;
//        result[1][1] = world.Y / world.W;
//        result[2][2] = world.Z / world.W;
//        return result;
//    }
//
//    // Transforms a 2D vector (supports only 2x2 matrices).
//    Vector2 Transform(const Vector2 &other) const requires (N == 2) {
//        Vector2 result;
//        result.X = Data[0][0] * other.X + Data[0][1] * other.Y;
//        result.Y = Data[1][0] * other.X + Data[1][1] * other.Y;
//        return result;
//    }
//    
//    // Translate the matrix by a vector
//    MatrixBase Translate(const Vector3 &translation) requires (N == 4) {
//        Data[3][0] += translation.X;
//        Data[3][1] += translation.Y;
//        Data[3][2] += translation.Z;
//        return *this;
//    }
//
//    // Rotate the matrix by a quaternion
//    MatrixBase Rotate(const Quaternion &rotation) requires (N == 4) {
//        float xx = rotation.X * rotation.X;
//        float xy = rotation.X * rotation.Y;
//        float xz = rotation.X * rotation.Z;
//        float xw = rotation.X * rotation.W;
//        float yy = rotation.Y * rotation.Y;
//        float yz = rotation.Y * rotation.Z;
//        float yw = rotation.Y * rotation.W;
//        float zz = rotation.Z * rotation.Z;
//        float zw = rotation.Z * rotation.W;
//
//        MatrixBase result;
//        result.Data[0][0] = 1 - 2 * (yy + zz);
//        result.Data[0][1] = 2 * (xy - zw);
//        result.Data[0][2] = 2 * (xz + yw);
//        result.Data[1][0] = 2 * (xy + zw);
//        result.Data[1][1] = 1 - 2 * (xx + zz);
//        result.Data[1][2] = 2 * (yz - xw);
//        result.Data[2][0] = 2 * (xz - yw);
//        result.Data[2][1] = 2 * (yz + xw);
//        result.Data[2][2] = 1 - 2 * (xx + yy);
//        return *this * result;
//    }
//
//    // Rotate the matrix by a vector of Euler angles (rotation order: XYZ)
//    MatrixBase Rotate(const Vector3 &euler_angles) requires (N == 4) {
//        float cosX = std::cos(euler_angles.X);
//        float sinX = std::sin(euler_angles.X);
//        float cosY = std::cos(euler_angles.Y);
//        float sinY = std::sin(euler_angles.Y);
//        float cosZ = std::cos(euler_angles.Z);
//        float sinZ = std::sin(euler_angles.Z);
//
//        MatrixBase rotationX = {
//            1,      0,      0,      0,
//            0,      cosX,   -sinX,  0,
//            0,      sinX,   cosX,   0,
//            0,      0,      0,      1
//        };
//
//        MatrixBase rotationY = {
//            cosY,   0,      sinY,  0,
//            0,      1,      0,      0,
//            -sinY,  0,      cosY,  0,
//            0,      0,      0,      1,
//        };
//
//        MatrixBase rotationZ = {
//            cosZ,   -sinZ,  0,      0,
//            sinZ,   cosZ,   0,      0,
//            0,      0,      1,      0,
//            0,      0,      0,      1,
//        };
//
//        MatrixBase rotation = rotationZ * rotationY * rotationX;
//        return *this * rotation;
//    }
//
//    // Scale the matrix by a vector
//    MatrixBase Scale(const Vector3 &scale) requires (N == 4) {
//        Data[0][0] *= scale.X;
//        Data[1][1] *= scale.Y;
//        Data[2][2] *= scale.Z;
//        return *this;
//    }
//
//    // Computes the transpose of the matrix.
//    MatrixBase Transpose() {
//        MatrixBase result;
//        for (size_t i = 0; i < N; i++) {
//            for (size_t j = 0; j < N; j++) {
//                result.Data[j][i] = Data[i][j];
//            }
//        }
//        return result;
//    }
//
//private:
//    /// Helpers
//    void ValidateScalar(T scalar) {
//        if (std::abs(scalar) < std::numeric_limits<T>::epsilon()) {
//            throw std::invalid_argument("Cannot divide by zero.");
//        }
//    }
//};

#pragma warning(pop)
#pragma pack(pop)

///
/// Aliases
///
//using Matrix2 = MatrixBase<float, 2>;
//using Matrix3 = MatrixBase<float, 3>;
//using Matrix4 = MatrixBase<float, 4>;
//
//using DMatrix2 = MatrixBase<double, 2>;
//using DMatrix3 = MatrixBase<double, 3>;
//using DMatrix4 = MatrixBase<double, 4>;

}

export namespace std {
// Provide specializations for std::hash<...> with linalg types
template<class T, int M> struct hash<Hedron::Matrix<T, M, 1>> { std::size_t operator()(const Hedron::Matrix<T, M, 1> &v) const { std::hash<Hedron::Vector<T, M>> h; return h(v.x); } };
template<class T, int M> struct hash<Hedron::Matrix<T, M, 2>> { std::size_t operator()(const Hedron::Matrix<T, M, 2> &v) const { std::hash<Hedron::Vector<T, M>> h; return h(v.x) ^ (h(v.y) << M); } };
template<class T, int M> struct hash<Hedron::Matrix<T, M, 3>> { std::size_t operator()(const Hedron::Matrix<T, M, 3> &v) const { std::hash<Hedron::Vector<T, M>> h; return h(v.x) ^ (h(v.y) << M) ^ (h(v.z) << (M * 2)); } };
template<class T, int M> struct hash<Hedron::Matrix<T, M, 4>> { std::size_t operator()(const Hedron::Matrix<T, M, 4> &v) const { std::hash<Hedron::Vector<T, M>> h; return h(v.x) ^ (h(v.y) << M) ^ (h(v.z) << (M * 2)) ^ (h(v.w) << (M * 3)); } };
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
    //static_assert( 32 == sizeof(MatrixBase<double,  2>), "MatrixBase<double>[2]: The type size should be 32 byte(s)!");
    //static_assert( 72 == sizeof(MatrixBase<double,  3>), "MatrixBase<double>[3]: The type size should be 72 byte(s)!");
    //static_assert(128 == sizeof(MatrixBase<double,  4>), "MatrixBase<double>[4]: The type size should be 128 byte(s)!");
    //static_assert( 16 == sizeof(MatrixBase<float,   2>), "MatrixBase<float>[2]:  The type size should be 16 byte(s)!");
    //static_assert( 36 == sizeof(MatrixBase<float,   3>), "MatrixBase<float>[3]:  The type size should be 36 byte(s)!");
    //static_assert( 64 == sizeof(MatrixBase<float,   4>), "MatrixBase<float>[4]:  The type size should be 64 byte(s)!");
}

}
