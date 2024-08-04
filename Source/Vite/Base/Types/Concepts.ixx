export module Vite.Type.Concepts;

import std;

export namespace Hedron {

///
/// Alias-Templates
///

///
/// @brief Category String Types
///

// Detects: All String Types
template<typename T>
using is_xstring = std::disjunction<
    std::is_same<char *, typename std::decay_t<T>>,
    std::is_same<const char *, typename std::decay_t<T>>,
    std::is_same<std::string, typename std::decay_t<T>>,
    std::is_same<std::string_view, typename std::decay_t<T>>,
    std::is_same<wchar_t *, typename std::decay_t<T>>,
    std::is_same<const wchar_t *, typename std::decay_t<T>>,
    std::is_same<std::wstring, typename std::decay_t<T>>,
    std::is_same<std::wstring_view, typename std::decay_t<T>>
>;

template<typename T>
constexpr bool is_xstring_v = is_xstring<T>::value;

// Detects: All String-View Types
template <typename T>
using is_xstring_view = std::disjunction<
    std::is_same<std::string_view, typename std::decay_t<T>>,
    std::is_same<std::wstring_view, typename std::decay_t<T>>
>;

template<typename T>
constexpr bool is_xstring_view_v = is_xstring_view<T>::value;

// Detects: Default String Types
template<typename T>
using is_string = std::disjunction<
    std::is_same<char *, typename std::decay_t<T>>,
    std::is_same<const char *, typename std::decay_t<T>>,
    std::is_same<std::string, typename std::decay_t<T>>,
    std::is_same<std::string_view, typename std::decay_t<T>>
>;

template<typename T>
constexpr bool is_string_v = is_string<T>::value;

// Detects: Wide String Types
template<typename T>
using is_wstring = std::disjunction<
    std::is_same<wchar_t *, typename std::decay_t<T>>,
    std::is_same<const wchar_t *, typename std::decay_t<T>>,
    std::is_same<std::wstring, typename std::decay_t<T>>,
    std::is_same<std::wstring_view, typename std::decay_t<T>>
>;

template<typename T>
constexpr bool is_wstring_v = is_wstring<T>::value;

///
/// Concepts
///

///
/// @brief Category: Arithmetic Types
///

// Detects: All Arithmetic Types
template <typename T>
concept typename_arithmetic = std::is_arithmetic_v<T>;


///
/// @brief Category: Floating-Point Types
///

// Detects: Default Floating-Point Types
template <typename T>
concept typename_floating_point = std::is_floating_point_v<T>;


///
/// @brief Category: Hash-able Types
///

// Detects: All size_t convertible Types (hash-able)
template<typename T>
concept typename_hashable = requires(T a) {
    { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
};

///
/// @brief Category: String Types
///

// All String Types
template<typename T>
concept typename_xstring = is_xstring_v<T>;

// All String-View Types
template<typename T>
concept typename_string_view = is_xstring_view_v<T>;

// Default String Types
template<typename T>
concept typename_string = is_string_v<T>;

// Wide String Types
template<typename T>
concept typename_wstring = is_wstring_v<T>;

}

module :private;

namespace Hedron::Test {

void Compiler() {
    // Test is_xstring
    static_assert(is_xstring_v<char *>);
    static_assert(is_xstring_v<const char *>);
    static_assert(is_xstring_v<std::string>);
    static_assert(is_xstring_v<std::string_view>);
    static_assert(is_xstring_v<wchar_t *>);
    static_assert(is_xstring_v<const wchar_t *>);
    static_assert(is_xstring_v<std::wstring>);
    static_assert(is_xstring_v<std::wstring_view>);
    static_assert(!is_xstring_v<int>);

    // Test is_xstring_view
    static_assert(is_xstring_view_v<std::string_view>);
    static_assert(is_xstring_view_v<std::wstring_view>);
    static_assert(!is_xstring_view_v<std::string>);
    static_assert(!is_xstring_view_v<int>);

    // Test is_string
    static_assert(is_string_v<char *>);
    static_assert(is_string_v<const char *>);
    static_assert(is_string_v<std::string>);
    static_assert(is_string_v<std::string_view>);
    static_assert(!is_string_v<wchar_t *>);
    static_assert(!is_string_v<int>);

    // Test is_wstring
    static_assert(is_wstring_v<wchar_t *>);
    static_assert(is_wstring_v<const wchar_t *>);
    static_assert(is_wstring_v<std::wstring>);
    static_assert(is_wstring_v<std::wstring_view>);
    static_assert(!is_wstring_v<char *>);
    static_assert(!is_wstring_v<int>);

    // Test typename_arithmetic
    static_assert(typename_arithmetic<int>);
    static_assert(typename_arithmetic<float>);
    static_assert(!typename_arithmetic<std::string>);

    // Test typename_floating_point
    static_assert(typename_floating_point<float>);
    static_assert(typename_floating_point<double>);
    static_assert(!typename_floating_point<int>);

    // Test typename_hashable
    static_assert(typename_hashable<int>);
    static_assert(typename_hashable<std::string>);
    static_assert(!typename_hashable<std::vector<int>>);

    // Test typename_xstring
    static_assert(typename_xstring<char *>);
    static_assert(typename_xstring<std::wstring>);
    static_assert(!typename_xstring<int>);

    // Test typename_string_view
    static_assert(typename_string_view<std::string_view>);
    static_assert(typename_string_view<std::wstring_view>);
    static_assert(!typename_string_view<std::string>);

    // Test typename_string
    static_assert(typename_string<char *>);
    static_assert(typename_string<std::string>);
    static_assert(!typename_string<wchar_t *>);

    // Test typename_wstring
    static_assert(typename_wstring<wchar_t *>);
    static_assert(typename_wstring<std::wstring>);
    static_assert(!typename_wstring<char *>);
}

}
