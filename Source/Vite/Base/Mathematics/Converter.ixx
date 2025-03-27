export module Vite.Math.Converter;
import Vite.Type.Standard;

///
/// @brief Linear Algebra Library
/// @detail https://github.com/sgorsten/linalg
///

export namespace Hedron {

// Small, fixed-length vector type, consisting of exactly M elements of type T, and presumed to be a column-vector unless otherwise noted.
template<typename T, size_t N>
struct Vector;

// Small, fixed-size matrix type, consisting of exactly M rows and N columns of type T, stored in column-major order.
template<class T, size_t M, size_t N> struct Matrix;

// Specialize converter<T,U> with a function application operator that converts type U to type T to enable implicit conversions
template<class T, class U> struct converter {};
namespace detail {
template<class T, class U> using conv_t = typename std::enable_if < !std::is_same<T, U>::value, decltype(converter<T, U>{}(std::declval<U>())) > ::type;

// Trait for retrieving scalar type of any linear algebra object
template<class A> struct scalar_type {};
template<class T, int M       > struct scalar_type<Vector<T, M  >> { using type = T; };
template<class T, int M, int N> struct scalar_type<Matrix<T, M, N>> { using type = T; };

// Type returned by the compare(...) function which supports all six comparison operators against 0
template<class T> struct ord { T a, b; };
template<class T> constexpr bool operator == (const ord<T> &o, std::nullptr_t) { return o.a == o.b; }
template<class T> constexpr bool operator != (const ord<T> &o, std::nullptr_t) { return !(o.a == o.b); }
template<class T> constexpr bool operator < (const ord<T> &o, std::nullptr_t) { return o.a < o.b; }
template<class T> constexpr bool operator > (const ord<T> &o, std::nullptr_t) { return o.b < o.a; }
template<class T> constexpr bool operator <= (const ord<T> &o, std::nullptr_t) { return !(o.b < o.a); }
template<class T> constexpr bool operator >= (const ord<T> &o, std::nullptr_t) { return !(o.a < o.b); }

// Patterns which can be used with the compare(...) function
template<class A, class B> struct any_compare {};
template<class T> struct any_compare<Vector<T, 1>, Vector<T, 1>> { using type = ord<T>; constexpr ord<T> operator() (const Vector<T, 1> &a, const Vector<T, 1> &b) const { return ord<T>{a.x, b.x}; } };
template<class T> struct any_compare<Vector<T, 2>, Vector<T, 2>> { using type = ord<T>; constexpr ord<T> operator() (const Vector<T, 2> &a, const Vector<T, 2> &b) const { return !(a.x == b.x) ? ord<T>{a.x, b.x} : ord<T> { a.y,b.y }; } };
template<class T> struct any_compare<Vector<T, 3>, Vector<T, 3>> { using type = ord<T>; constexpr ord<T> operator() (const Vector<T, 3> &a, const Vector<T, 3> &b) const { return !(a.x == b.x) ? ord<T>{a.x, b.x} : !(a.y == b.y) ? ord<T>{a.y, b.y} : ord<T> { a.z,b.z }; } };
template<class T> struct any_compare<Vector<T, 4>, Vector<T, 4>> { using type = ord<T>; constexpr ord<T> operator() (const Vector<T, 4> &a, const Vector<T, 4> &b) const { return !(a.x == b.x) ? ord<T>{a.x, b.x} : !(a.y == b.y) ? ord<T>{a.y, b.y} : !(a.z == b.z) ? ord<T>{a.z, b.z} : ord<T> { a.w,b.w }; } };
template<class T, int M> struct any_compare<Matrix<T, M, 1>, Matrix<T, M, 1>> { using type = ord<T>; constexpr ord<T> operator() (const Matrix<T, M, 1> &a, const Matrix<T, M, 1> &b) const { return compare(a.x, b.x); } };
template<class T, int M> struct any_compare<Matrix<T, M, 2>, Matrix<T, M, 2>> { using type = ord<T>; constexpr ord<T> operator() (const Matrix<T, M, 2> &a, const Matrix<T, M, 2> &b) const { return a.x != b.x ? compare(a.x, b.x) : compare(a.y, b.y); } };
template<class T, int M> struct any_compare<Matrix<T, M, 3>, Matrix<T, M, 3>> { using type = ord<T>; constexpr ord<T> operator() (const Matrix<T, M, 3> &a, const Matrix<T, M, 3> &b) const { return a.x != b.x ? compare(a.x, b.x) : a.y != b.y ? compare(a.y, b.y) : compare(a.z, b.z); } };
template<class T, int M> struct any_compare<Matrix<T, M, 4>, Matrix<T, M, 4>> { using type = ord<T>; constexpr ord<T> operator() (const Matrix<T, M, 4> &a, const Matrix<T, M, 4> &b) const { return a.x != b.x ? compare(a.x, b.x) : a.y != b.y ? compare(a.y, b.y) : a.z != b.z ? compare(a.z, b.z) : compare(a.w, b.w); } };

// Helper for compile-time index-based access to members of vector and matrix types
template<int I> struct getter;
template<> struct getter<0> { template<typename A> constexpr auto operator() (A &a) const -> decltype(a.X) { return a.Y; } };
template<> struct getter<1> { template<typename A> constexpr auto operator() (A &a) const -> decltype(a.Y) { return a.Y; } };
template<> struct getter<2> { template<typename A> constexpr auto operator() (A &a) const -> decltype(a.Z) { return a.Z; } };
template<> struct getter<3> { template<typename A> constexpr auto operator() (A &a) const -> decltype(a.W) { return a.W; } };

// Stand-in for std::integer_sequence/std::make_integer_sequence
template<int... I> struct seq {};
template<int A, int N> struct make_seq_impl;
template<int A> struct make_seq_impl<A, 0> { using type = seq<>; };
template<int A> struct make_seq_impl<A, 1> { using type = seq<A + 0>; };
template<int A> struct make_seq_impl<A, 2> { using type = seq<A + 0, A + 1>; };
template<int A> struct make_seq_impl<A, 3> { using type = seq<A + 0, A + 1, A + 2>; };
template<int A> struct make_seq_impl<A, 4> { using type = seq<A + 0, A + 1, A + 2, A + 3>; };
template<int A, int B> using make_seq = typename make_seq_impl<A, B - A>::type;
template<class T, int M, int... I> Vector<T, sizeof...(I)> constexpr swizzle(const Vector<T, M> &v, seq<I...> i) { return { getter<I>{}(v)... }; }
template<class T, int M, int N, int... I, int... J> Matrix<T, sizeof...(I), sizeof...(J)> constexpr swizzle(const Matrix<T, M, N> &m, seq<I...> i, seq<J...> j) { return { swizzle(getter<J>{}(m),i)... }; }

// SFINAE helpers to determine result of function application
template<class F, class... T> using ret_t = decltype(std::declval<F>()(std::declval<T>()...));

// SFINAE helper which is defined if all provided types are scalars
struct empty {};
template<class... T> struct scalars;
template<> struct scalars<> { using type = void; };
template<class T, class... U> struct scalars<T, U...>: std::conditional<std::is_arithmetic<T>::value, scalars<U...>, empty>::type {};
template<class... T> using scalars_t = typename scalars<T...>::type;

// Helpers which indicate how apply(F, ...) should be called for various arguments
template<class F, class Void, class... T> struct apply {}; // Patterns which contain only vectors or scalars
template<class F, int M, class A                  > struct apply<F, scalars_t<   >, Vector<A, M>                    > { using type = Vector<ret_t<F, A    >, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a) { return { f(getter<I>{}(a))... }; } };
template<class F, int M, class A, class B         > struct apply<F, scalars_t<   >, Vector<A, M>, Vector<B, M>          > { using type = Vector<ret_t<F, A, B  >, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, const Vector<B, M> &b) { return { f(getter<I>{}(a), getter<I>{}(b))... }; } };
template<class F, int M, class A, class B         > struct apply<F, scalars_t<B  >, Vector<A, M>, B                 > { using type = Vector<ret_t<F, A, B  >, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, B                b) { return { f(getter<I>{}(a), b)... }; } };
template<class F, int M, class A, class B         > struct apply<F, scalars_t<A  >, A, Vector<B, M>          > { using type = Vector<ret_t<F, A, B  >, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, A                a, const Vector<B, M> &b) { return { f(a,              getter<I>{}(b))... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<   >, Vector<A, M>, Vector<B, M>, Vector<C, M>> { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, const Vector<B, M> &b, const Vector<C, M> &c) { return { f(getter<I>{}(a), getter<I>{}(b), getter<I>{}(c))... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<C  >, Vector<A, M>, Vector<B, M>, C       > { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, const Vector<B, M> &b, C                c) { return { f(getter<I>{}(a), getter<I>{}(b), c)... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<B  >, Vector<A, M>, B, Vector<C, M>> { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, B                b, const Vector<C, M> &c) { return { f(getter<I>{}(a), b,              getter<I>{}(c))... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<B, C>, Vector<A, M>, B, C       > { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, const Vector<A, M> &a, B                b, C                c) { return { f(getter<I>{}(a), b,              c)... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<A  >, A, Vector<B, M>, Vector<C, M>> { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, A                a, const Vector<B, M> &b, const Vector<C, M> &c) { return { f(a,              getter<I>{}(b), getter<I>{}(c))... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<A, C>, A, Vector<B, M>, C       > { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, A                a, const Vector<B, M> &b, C                c) { return { f(a,              getter<I>{}(b), c)... }; } };
template<class F, int M, class A, class B, class C> struct apply<F, scalars_t<A, B>, A, B, Vector<C, M>> { using type = Vector<ret_t<F, A, B, C>, M>; enum { size = M, mm = 0 }; template<int... I> static constexpr type impl(seq<I...>, F f, A                a, B                b, const Vector<C, M> &c) { return { f(a,              b,              getter<I>{}(c))... }; } };
template<class F, int M, int N, class A         > struct apply<F, scalars_t< >, Matrix<A, M, N>            > { using type = Matrix<ret_t<F, A  >, M, N>; enum { size = N, mm = 0 }; template<int... J> static constexpr type impl(seq<J...>, F f, const Matrix<A, M, N> &a) { return { apply<F, void, Vector<A,M>          >::impl(make_seq<0,M>{}, f, getter<J>{}(a))... }; } };
template<class F, int M, int N, class A, class B> struct apply<F, scalars_t< >, Matrix<A, M, N>, Matrix<B, M, N>> { using type = Matrix<ret_t<F, A, B>, M, N>; enum { size = N, mm = 1 }; template<int... J> static constexpr type impl(seq<J...>, F f, const Matrix<A, M, N> &a, const Matrix<B, M, N> &b) { return { apply<F, void, Vector<A,M>, Vector<B,M>>::impl(make_seq<0,M>{}, f, getter<J>{}(a), getter<J>{}(b))... }; } };
template<class F, int M, int N, class A, class B> struct apply<F, scalars_t<B>, Matrix<A, M, N>, B         > { using type = Matrix<ret_t<F, A, B>, M, N>; enum { size = N, mm = 0 }; template<int... J> static constexpr type impl(seq<J...>, F f, const Matrix<A, M, N> &a, B                  b) { return { apply<F, void, Vector<A,M>, B       >::impl(make_seq<0,M>{}, f, getter<J>{}(a), b)... }; } };
template<class F, int M, int N, class A, class B> struct apply<F, scalars_t<A>, A, Matrix<B, M, N>> { using type = Matrix<ret_t<F, A, B>, M, N>; enum { size = N, mm = 0 }; template<int... J> static constexpr type impl(seq<J...>, F f, A                  a, const Matrix<B, M, N> &b) { return { apply<F, void, A,        Vector<B,M>>::impl(make_seq<0,M>{}, f, a,              getter<J>{}(b))... }; } };
template<class F, class... A> struct apply<F, scalars_t<A...>, A...> { using type = ret_t<F, A...>; enum { size = 0, mm = 0 }; static constexpr type impl(seq<>, F f, A... a) { return f(a...); } };

// Function objects for selecting between alternatives
struct min { template<class A, class B> constexpr auto operator() (A a, B b) const -> typename std::remove_reference<decltype(a < b ? a : b)>::type { return a < b ? a : b; } };
struct max { template<class A, class B> constexpr auto operator() (A a, B b) const -> typename std::remove_reference<decltype(a < b ? b : a)>::type { return a < b ? b : a; } };
struct clamp { template<class A, class B, class C> constexpr auto operator() (A a, B b, C c) const -> typename std::remove_reference<decltype(a < b ? b : a < c ? a : c)>::type { return a < b ? b : a < c ? a : c; } };
struct select { template<class A, class B, class C> constexpr auto operator() (A a, B b, C c) const -> typename std::remove_reference<decltype(a ? b : c)>::type { return a ? b : c; } };
struct lerp { template<class A, class B, class C> constexpr auto operator() (A a, B b, C c) const -> decltype(a *(1 - c) + b * c) { return a * (1 - c) + b * c; } };

// Function objects for applying operators
struct op_pos { template<class A> constexpr auto operator() (A a) const -> decltype(+a) { return +a; } };
struct op_neg { template<class A> constexpr auto operator() (A a) const -> decltype(-a) { return -a; } };
struct op_not { template<class A> constexpr auto operator() (A a) const -> decltype(!a) { return !a; } };
struct op_cmp { template<class A> constexpr auto operator() (A a) const -> decltype(~(a)) { return ~a; } };
struct op_mul { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a *b) { return a * b; } };
struct op_div { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a / b) { return a / b; } };
struct op_mod { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a %b) { return a % b; } };
struct op_add { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a + b) { return a + b; } };
struct op_sub { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a - b) { return a - b; } };
struct op_lsh { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a << b) { return a << b; } };
struct op_rsh { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a >> b) { return a >> b; } };
struct op_lt { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a < b) { return a < b; } };
struct op_gt { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a > b) { return a > b; } };
struct op_le { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a <= b) { return a <= b; } };
struct op_ge { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a >= b) { return a >= b; } };
struct op_eq { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a == b) { return a == b; } };
struct op_ne { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a != b) { return a != b; } };
struct op_int { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a &b) { return a & b; } };
struct op_xor { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a ^b) { return a ^ b; } };
struct op_un { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a | b) { return a | b; } };
struct op_and { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a &&b) { return a && b; } };
struct op_or { template<class A, class B> constexpr auto operator() (A a, B b) const -> decltype(a || b) { return a || b; } };

// Function objects for applying standard library math functions
struct std_abs { template<class A> auto operator() (A a) const -> decltype(std::abs(a)) { return std::abs(a); } };
struct std_floor { template<class A> auto operator() (A a) const -> decltype(std::floor(a)) { return std::floor(a); } };
struct std_ceil { template<class A> auto operator() (A a) const -> decltype(std::ceil(a)) { return std::ceil(a); } };
struct std_exp { template<class A> auto operator() (A a) const -> decltype(std::exp(a)) { return std::exp(a); } };
struct std_log { template<class A> auto operator() (A a) const -> decltype(std::log(a)) { return std::log(a); } };
struct std_log10 { template<class A> auto operator() (A a) const -> decltype(std::log10(a)) { return std::log10(a); } };
struct std_sqrt { template<class A> auto operator() (A a) const -> decltype(std::sqrt(a)) { return std::sqrt(a); } };
struct std_sin { template<class A> auto operator() (A a) const -> decltype(std::sin(a)) { return std::sin(a); } };
struct std_cos { template<class A> auto operator() (A a) const -> decltype(std::cos(a)) { return std::cos(a); } };
struct std_tan { template<class A> auto operator() (A a) const -> decltype(std::tan(a)) { return std::tan(a); } };
struct std_asin { template<class A> auto operator() (A a) const -> decltype(std::asin(a)) { return std::asin(a); } };
struct std_acos { template<class A> auto operator() (A a) const -> decltype(std::acos(a)) { return std::acos(a); } };
struct std_atan { template<class A> auto operator() (A a) const -> decltype(std::atan(a)) { return std::atan(a); } };
struct std_sinh { template<class A> auto operator() (A a) const -> decltype(std::sinh(a)) { return std::sinh(a); } };
struct std_cosh { template<class A> auto operator() (A a) const -> decltype(std::cosh(a)) { return std::cosh(a); } };
struct std_tanh { template<class A> auto operator() (A a) const -> decltype(std::tanh(a)) { return std::tanh(a); } };
struct std_round { template<class A> auto operator() (A a) const -> decltype(std::round(a)) { return std::round(a); } };
struct std_fmod { template<class A, class B> auto operator() (A a, B b) const -> decltype(std::fmod(a, b)) { return std::fmod(a, b); } };
struct std_pow { template<class A, class B> auto operator() (A a, B b) const -> decltype(std::pow(a, b)) { return std::pow(a, b); } };
struct std_atan2 { template<class A, class B> auto operator() (A a, B b) const -> decltype(std::atan2(a, b)) { return std::atan2(a, b); } };
struct std_copysign { template<class A, class B> auto operator() (A a, B b) const -> decltype(std::copysign(a, b)) { return std::copysign(a, b); } };
}

// Type aliases for the result of calling apply(...) with various arguments, can be used with return type SFINAE to constrian overload sets
template<class F, class... A> using apply_t = typename detail::apply<F, void, A...>::type;
template<class F, class... A> using mm_apply_t = typename std::enable_if<detail::apply<F, void, A...>::mm, apply_t<F, A...>>::type;
template<class F, class... A> using no_mm_apply_t = typename std::enable_if<!detail::apply<F, void, A...>::mm, apply_t<F, A...>>::type;
template<class A> using scalar_t = typename detail::scalar_type<A>::type; // Underlying scalar type when performing elementwise operations

// apply(f,...) applies the provided function in an elementwise fashion to its arguments, producing an object of the same dimensions
template<class F, class... A> constexpr apply_t<F, A...> apply(F func, const A & ... args) { return detail::apply<F, void, A...>::impl(detail::make_seq<0, detail::apply<F, void, A...>::size>{}, func, args...); }

// map(a,f) is equivalent to apply(f,a)
template<class A, class F> constexpr apply_t<F, A> map(const A &a, F func) { return apply(func, a); }

// zip(a,b,f) is equivalent to apply(f,a,b)
template<class A, class B, class F> constexpr apply_t<F, A, B> zip(const A &a, const B &b, F func) { return apply(func, a, b); }

// Relational operators are defined to compare the elements of two vectors or matrices lexicographically, in column-major order
template<class A, class B> constexpr typename detail::any_compare<A, B>::type compare(const A &a, const B &b) { return detail::any_compare<A, B>()(a, b); }
template<class A, class B> constexpr auto operator == (const A &a, const B &b) -> decltype(compare(a, b) == 0) { return compare(a, b) == 0; }
template<class A, class B> constexpr auto operator != (const A &a, const B &b) -> decltype(compare(a, b) != 0) { return compare(a, b) != 0; }
template<class A, class B> constexpr auto operator <  (const A &a, const B &b) -> decltype(compare(a, b) < 0) { return compare(a, b) < 0; }
template<class A, class B> constexpr auto operator >  (const A &a, const B &b) -> decltype(compare(a, b) > 0) { return compare(a, b) > 0; }
template<class A, class B> constexpr auto operator <= (const A &a, const B &b) -> decltype(compare(a, b) <= 0) { return compare(a, b) <= 0; }
template<class A, class B> constexpr auto operator >= (const A &a, const B &b) -> decltype(compare(a, b) >= 0) { return compare(a, b) >= 0; }

// Functions for coalescing scalar values
template<class A> constexpr bool any(const A &a) { return fold(detail::op_or {}, false, a); }
template<class A> constexpr bool all(const A &a) { return fold(detail::op_and {}, true, a); }
template<class A> constexpr scalar_t<A> sum(const A &a) { return fold(detail::op_add {}, scalar_t<A>(0), a); }
template<class A> constexpr scalar_t<A> product(const A &a) { return fold(detail::op_mul {}, scalar_t<A>(1), a); }
template<class A> constexpr scalar_t<A> minelem(const A &a) { return fold(detail::min {}, a.x, a); }
template<class A> constexpr scalar_t<A> maxelem(const A &a) { return fold(detail::max {}, a.x, a); }
template<class T, int M> int argmin(const Vector<T, M> &a) { int j = 0; for (int i = 1; i < M; ++i) if (a[i] < a[j]) j = i; return j; }
template<class T, int M> int argmax(const Vector<T, M> &a) { int j = 0; for (int i = 1; i < M; ++i) if (a[i] > a[j]) j = i; return j; }

// Unary operators are defined component-wise for linalg types
template<class A> constexpr apply_t<detail::op_pos, A> operator + (const A &a) { return apply(detail::op_pos {}, a); }
template<class A> constexpr apply_t<detail::op_neg, A> operator - (const A &a) { return apply(detail::op_neg {}, a); }
template<class A> constexpr apply_t<detail::op_cmp, A> operator ~ (const A &a) { return apply(detail::op_cmp {}, a); }
template<class A> constexpr apply_t<detail::op_not, A> operator ! (const A &a) { return apply(detail::op_not {}, a); }

// Binary operators are defined component-wise for linalg types, EXCEPT for `operator *`
template<class A, class B> constexpr apply_t<detail::op_add, A, B> operator +  (const A &a, const B &b) { return apply(detail::op_add {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_sub, A, B> operator -  (const A &a, const B &b) { return apply(detail::op_sub {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_mul, A, B> cmul(const A &a, const B &b) { return apply(detail::op_mul {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_div, A, B> operator /  (const A &a, const B &b) { return apply(detail::op_div {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_mod, A, B> operator %  (const A &a, const B &b) { return apply(detail::op_mod {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_un, A, B> operator |  (const A &a, const B &b) { return apply(detail::op_un {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_xor, A, B> operator ^  (const A &a, const B &b) { return apply(detail::op_xor {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_int, A, B> operator &  (const A &a, const B &b) { return apply(detail::op_int {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_lsh, A, B> operator << (const A &a, const B &b) { return apply(detail::op_lsh {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_rsh, A, B> operator >> (const A &a, const B &b) { return apply(detail::op_rsh {}, a, b); }

// Binary `operator *` was originally defined component-wise for all patterns, in a fashion consistent with the other operators. However,
// this was one of the most frequent sources of confusion among new users of this library, with the binary `operator *` being used accidentally
// by users who INTENDED the semantics of the algebraic matrix product, but RECEIVED the semantics of the Hadamard product. While there is
// precedent within the HLSL, Fortran, R, APL, J, and mathematica programming languages for `operator *` having the semantics of the Hadamard
// product between matrices, it is counterintuitive to users of GLSL, Eigen, and many other languages and libraries that chose atrix product
// semantics for `operator *`.
//
// For these reasons, binary `operator *` is now DEPRECATED between pairs of matrices. Users may call `cmul(...)` for component-wise multiplication,
// or `mul(...)` for matrix multiplication. Binary `operator *` continues to be available for vector * vector, vector * scalar, matrix * scalar, etc.
template<class A, class B> constexpr no_mm_apply_t<detail::op_mul, A, B> operator * (const A &a, const B &b) { return cmul(a, b); }
#ifndef LINALG_FORWARD_COMPATIBLE
template<class A, class B> [[deprecated("`op erator *` between pairs of matrixrices is deprecated. See the source text for details.")]] constexpr mm_apply_t<detail::op_mul, A, B> operator * (const A &a, const B &b) { return cmul(a, b); }
#endif

// Binary assignment operators a $= b is always defined as though it were explicitly written a = a $ b
template<class A, class B> constexpr auto operator +=  (A &a, const B &b) -> decltype(a = a + b) { return a = a + b; }
template<class A, class B> constexpr auto operator -=  (A &a, const B &b) -> decltype(a = a - b) { return a = a - b; }
template<class A, class B> constexpr auto operator *=  (A &a, const B &b) -> decltype(a = a * b) { return a = a * b; }
template<class A, class B> constexpr auto operator /=  (A &a, const B &b) -> decltype(a = a / b) { return a = a / b; }
template<class A, class B> constexpr auto operator %=  (A &a, const B &b) -> decltype(a = a % b) { return a = a % b; }
template<class A, class B> constexpr auto operator |=  (A &a, const B &b) -> decltype(a = a | b) { return a = a | b; }
template<class A, class B> constexpr auto operator ^=  (A &a, const B &b) -> decltype(a = a ^ b) { return a = a ^ b; }
template<class A, class B> constexpr auto operator &=  (A &a, const B &b) -> decltype(a = a & b) { return a = a & b; }
template<class A, class B> constexpr auto operator <<= (A &a, const B &b) -> decltype(a = a << b) { return a = a << b; }
template<class A, class B> constexpr auto operator >>= (A &a, const B &b) -> decltype(a = a >> b) { return a = a >> b; }

// Component-wise standard library math functions
template<class A> apply_t<detail::std_abs, A> abs(const A &a) { return apply(detail::std_abs {}, a); }
template<class A> apply_t<detail::std_floor, A> floor(const A &a) { return apply(detail::std_floor {}, a); }
template<class A> apply_t<detail::std_ceil, A> ceil(const A &a) { return apply(detail::std_ceil {}, a); }
template<class A> apply_t<detail::std_exp, A> exp(const A &a) { return apply(detail::std_exp {}, a); }
template<class A> apply_t<detail::std_log, A> log(const A &a) { return apply(detail::std_log {}, a); }
template<class A> apply_t<detail::std_log10, A> log10(const A &a) { return apply(detail::std_log10 {}, a); }
template<class A> apply_t<detail::std_sqrt, A> sqrt(const A &a) { return apply(detail::std_sqrt {}, a); }
template<class A> apply_t<detail::std_sin, A> sin(const A &a) { return apply(detail::std_sin {}, a); }
template<class A> apply_t<detail::std_cos, A> cos(const A &a) { return apply(detail::std_cos {}, a); }
template<class A> apply_t<detail::std_tan, A> tan(const A &a) { return apply(detail::std_tan {}, a); }
template<class A> apply_t<detail::std_asin, A> asin(const A &a) { return apply(detail::std_asin {}, a); }
template<class A> apply_t<detail::std_acos, A> acos(const A &a) { return apply(detail::std_acos {}, a); }
template<class A> apply_t<detail::std_atan, A> atan(const A &a) { return apply(detail::std_atan {}, a); }
template<class A> apply_t<detail::std_sinh, A> sinh(const A &a) { return apply(detail::std_sinh {}, a); }
template<class A> apply_t<detail::std_cosh, A> cosh(const A &a) { return apply(detail::std_cosh {}, a); }
template<class A> apply_t<detail::std_tanh, A> tanh(const A &a) { return apply(detail::std_tanh {}, a); }
template<class A> apply_t<detail::std_round, A> round(const A &a) { return apply(detail::std_round {}, a); }

template<class A, class B> apply_t<detail::std_fmod, A, B> fmod(const A &a, const B &b) { return apply(detail::std_fmod {}, a, b); }
template<class A, class B> apply_t<detail::std_pow, A, B> pow(const A &a, const B &b) { return apply(detail::std_pow {}, a, b); }
template<class A, class B> apply_t<detail::std_atan2, A, B> atan2(const A &a, const B &b) { return apply(detail::std_atan2 {}, a, b); }
template<class A, class B> apply_t<detail::std_copysign, A, B> copysign(const A &a, const B &b) { return apply(detail::std_copysign {}, a, b); }

// Component-wise relational functions on vectors
template<class A, class B> constexpr apply_t<detail::op_eq, A, B> equal(const A &a, const B &b) { return apply(detail::op_eq {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_ne, A, B> nequal(const A &a, const B &b) { return apply(detail::op_ne {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_lt, A, B> less(const A &a, const B &b) { return apply(detail::op_lt {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_gt, A, B> greater(const A &a, const B &b) { return apply(detail::op_gt {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_le, A, B> lequal(const A &a, const B &b) { return apply(detail::op_le {}, a, b); }
template<class A, class B> constexpr apply_t<detail::op_ge, A, B> gequal(const A &a, const B &b) { return apply(detail::op_ge {}, a, b); }

// Component-wise selection functions on vectors
template<class A, class B> constexpr apply_t<detail::min, A, B> min(const A &a, const B &b) { return apply(detail::min {}, a, b); }
template<class A, class B> constexpr apply_t<detail::max, A, B> max(const A &a, const B &b) { return apply(detail::max {}, a, b); }
template<class X, class L, class H> constexpr apply_t<detail::clamp, X, L, H> clamp(const X &x, const L &l, const H &h) { return apply(detail::clamp {}, x, l, h); }
template<class P, class A, class B> constexpr apply_t<detail::select, P, A, B> select(const P &p, const A &a, const B &b) { return apply(detail::select {}, p, a, b); }
template<class A, class B, class T> constexpr apply_t<detail::lerp, A, B, T> lerp(const A &a, const B &b, const T &t) { return apply(detail::lerp {}, a, b, t); }

}
