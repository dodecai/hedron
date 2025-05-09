﻿export module Vite.Extension;

import std;

///
/// @brief These little extensions can be very useful in some cases.
///

export namespace Hedron {

///
/// Category: Enumerations
///

///
/// @brief Converts enumeration value to BitMask value
///
template<typename T>
consteval auto BitMask(T x) noexcept requires std::is_arithmetic_v<T> {
    return (1 << x);
}

///
/// @brief Converts enumeration to base type
///
template<typename E>
consteval auto GetEnumType(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

///
/// @brief Derived Enums
/// @note  The value is declared as a union mainly for as a debugging aid. If the union is undesired and you have
/// other methods of debugging, change it to either of EnumT and do a cast for the constructor that accepts BaseEnumT.
///
template <typename DerivedT, typename BaseT>
class DeriveEnum {
public:
    /// Default
    DeriveEnum() = default;
    DeriveEnum(BaseT e): Base(e) {}
    DeriveEnum(DerivedT e): Derived(e) {}
    explicit DeriveEnum(int val): Derived(static_cast<DerivedT>(val)) {}

    /// Casts
    operator DerivedT() const { return Derived; }

private:
    /// Properties
    union {
        DerivedT Derived;
        BaseT Base;
    };
};

///
/// @brief Enable BitMask Operators
///
template<typename E>
struct EnableBitMaskOperators {
    static const bool enable = false;
};

// BitMask Operator AND
template<typename E>
inline auto operator&(E lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    using underlying = typename std::underlying_type<E>::type;
    return static_cast<E>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

// BitMask Operator OR
template<typename E>
inline auto operator|(E lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    using underlying = typename std::underlying_type<E>::type;
    return static_cast<E>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

// BitMask Operator XOR
template<typename E>
inline auto operator^(E lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    using underlying = typename std::underlying_type<E>::type;
    return static_cast<E>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

// BitMask Operator NOT
template<typename E>
inline auto operator~(E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    using underlying = typename std::underlying_type<E>::type;
    return static_cast<E>(~static_cast<underlying>(rhs));
}

// BitMask Operator AND Assignment
template<typename E>
inline auto &operator&=(E &lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    lhs = lhs & rhs;
    return lhs;
}

// BitMask Operator OR Assignment
template<typename E>
inline auto &operator|=(E &lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    lhs = lhs | rhs;
    return lhs;
}

// BitMask Operator XOR Assignment
template<typename E>
inline auto &operator^=(E &lhs, E rhs) noexcept requires EnableBitMaskOperators<E>::enable {
    lhs = lhs ^ rhs;
    return lhs;
}


///
/// @brief Enable Named Enum Stream Operators
///
template<typename E>
struct EnableNamedEnumStreamOperators {
    static const bool Enable = false;
};

// Trait
template<typename T>
struct NamedEnumTraits;

// Overload
template<typename E>
inline auto &operator<<(std::ostream &stream, const E &value) noexcept requires EnableNamedEnumStreamOperators<E>::Enable {
    stream << NamedEnumTraits<E>::Names[static_cast<size_t>(value)];
    return stream;
}


///
/// @brief Enable Named Enum Formatter
///
template<typename E>
struct EnableNamedEnumFormatter {
    static const bool Enable = false;
};

template<typename E>
struct std::formatter<E, std::enable_if_t<EnableNamedEnumFormatter<E>::Enable, char>> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const E &e, FormatContext &ctx) {
        return std::format_to(ctx.out(), "{}", Hedron::NamedEnumTraits<E>::Names[static_cast<size_t>(e)]);
    }
};


///
/// Category: string
///
inline std::wstring StringToWString(const std::string &str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

inline std::string WStringToString(const std::wstring &wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

///
/// Category: string_view
///

///
/// @brief Compile-Time Variant of rfind in a string view
///
consteval auto constexpr_rfind(const std::string_view str, char ch, size_t pos = std::string_view::npos) noexcept {
    if (pos >= str.size()) { pos = str.size() - 1; }

    for (size_t i = pos; i != static_cast<size_t>(-1); --i) {
        if (str[i] == ch) { return i; }
    }

    return std::string_view::npos;
}

///
/// @brief Decodes UTF8 string view to codepoint 
///
inline std::uint32_t DecodeUtf8(std::string_view::iterator &begin, std::string_view::iterator end) {
    unsigned char byte = *begin;
    std::uint32_t codepoint = 0;
    int additionalBytes = 0;

    // 1-Byte Character (ASCII)
    if (byte <= 0x7F) {
        codepoint = byte;
    // 2-Byte Character
    } else if ((byte & 0xE0) == 0xC0) {
        codepoint = byte & 0x1F;
        additionalBytes = 1;
    // 3-Byte Character
    } else if ((byte & 0xF0) == 0xE0) {
        codepoint = byte & 0x0F;
        additionalBytes = 2;
    // 4-Byte Character
    } else if ((byte & 0xF8) == 0xF0) {
        codepoint = byte & 0x07;
        additionalBytes = 3;
    // Invalid UTF-8 start byte
    } else {
        begin++;
        return 0xFFFD; // Unicode replacement character
    }

    begin++;

    while (additionalBytes > 0) {
        if (begin == end || (*begin & 0xC0) != 0x80) {
            // Premature end or invalid UTF-8 continuation byte
            return 0xFFFD; // Unicode replacement character
        }

        codepoint = (codepoint << 6) | (*begin & 0x3F);
        begin++;
        additionalBytes--;
    }

    return codepoint;
}


///
/// Category: vector
///

///
/// @brief Vector SizeOf
///
template<typename T>
size_t sizeof_vector(const typename std::vector<T> &vec) noexcept {
    return sizeof(T) * vec.size();
}

}
