﻿export module Vite.System.Cli;

import Vite.Type.Standard;

///
/// @brief Cli Modifiers: These extend the output stream with backgrounds, colors and styles.
/// @note Tested with Windows Terminal
/// @source https://en.wikipedia.org/wiki/ANSI_escape_code
///

export namespace Hedron::Cli {

/// Definitions
// Background Colors
enum class Background {
    Default         = 49,

    Black           = 40,
    Red             = 41,
    Green           = 42,
    Yellow          = 43,
    Blue            = 44,
    Magenta         = 45,
    Cyan            = 46,
    LightGray       = 47,

    Gray            = 100,
    LightRed        = 101,
    LightGreen      = 102,
    LightYellow     = 103,
    LightBlue       = 104,
    LightMagenta    = 105,
    LightCyan       = 106,
    White           = 107,
};

// Text Colors
enum class Color {
    Default         = 39,

    Black           = 30,
    Red             = 31,
    Green           = 32,
    Yellow          = 33,
    Blue            = 34,
    Magenta         = 35,
    Cyan            = 36,
    LightGray       = 37,

    Gray            = 90,
    LightRed        = 91,
    LightGreen      = 92,
    LightYellow     = 93,
    LightBlue       = 94,
    LightMagenta    = 95,
    LightCyan       = 96,
    White           = 97,
};

// Styles
enum class Style {
    Bold            = 1,
    Faint           = 2,
    Italic          = 3,
    Underline       = 4,
    Blink           = 5,
    RapidBlink      = 6,
    Reverse         = 7,
    Conceal         = 8,
    Strike          = 9,

    DoubleUnderline = 21,
    Normal          = 22,
    NotItalic       = 23,
    NotUnderlined   = 24,
    NotBlinking     = 25,
    NotReversed     = 27,
    Reveal          = 28,
    NotStriked      = 29,

    Overline        = 53,
    NotOverlined    = 55,

    Superscript     = 73,
    Subscript       = 74,
    NotScripted     = 75,

    Reset           = 0,
};

/// Concepts
template <typename T>
concept typename_climodifier =
    std::is_same_v<std::decay_t<T>, Hedron::Cli::Background> ||
    std::is_same_v<std::decay_t<T>, Hedron::Cli::Color> ||
    std::is_same_v<std::decay_t<T>, Hedron::Cli::Style>;

/// Overloads
template <typename_climodifier T>
constexpr inline auto &operator<<(std::ostream &stream, const T &type) noexcept {
    return stream << "\x1b[" << static_cast<int>(type) << "m";
}

template <typename_climodifier T>
constexpr inline auto &operator<<(std::wostream &stream, const T &type) noexcept {
    return stream << "\x1b[" << static_cast<int>(type) << "m";
}

/// Tests
namespace Test {

void TestCli();

}

}

///
/// Global Overloads
///
export namespace std {

template <Hedron::Cli::typename_climodifier T>
struct formatter<T> {
    constexpr auto parse(format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const T &modifier, format_context &ctx) const {
        return format_to(ctx.out(), "\x1b[{:d}m", static_cast<int>(modifier));
    }
};

}

///
/// Implementation
///
module: private;

namespace Hedron::Cli::Test {

// Show me what you got!
void TestCli() {
    using std::cout;
    using std::endl;

    const Background backgrounds[] = {
        Background::Black,     Background::Red,           Background::Green,         Background::Yellow,
        Background::Blue,      Background::Magenta,       Background::Cyan,          Background::LightGray,
        Background::Gray,      Background::LightRed,      Background::LightGreen,    Background::LightYellow,
        Background::LightBlue, Background::LightMagenta,  Background::LightCyan,     Background::White
    };
    const Color colors[] = {
        Color::Black,          Color::Red,                Color::Green,              Color::Yellow,
        Color::Blue,           Color::Magenta,            Color::Cyan,               Color::LightGray,
        Color::Gray,           Color::LightRed,           Color::LightGreen,         Color::LightYellow,
        Color::LightBlue,      Color::LightMagenta,       Color::LightCyan,          Color::White
    };
    
    // This test shows all 256 background and color combinations in a neat table
    std::cout << endl << "Supported backgrounds and colors:\n";
    int counter = 0;
    for (const auto &color : colors) {
        for (const auto &background : backgrounds) {
            std::cout << background << color << " " << std::setfill('0') << std::setw(3) << counter++ << " ";
        }
        std::cout << Style::Reset << "\n";
    }
    std::cout << Style::Reset << endl;

    // This test shows all styles and their exact opposite
    std::cout << "Supported styles:\n";
    std::cout << Style::Bold            << "Bold            " << Style::Normal          << "\n";
    std::cout << Style::Faint           << "Dim             " << Style::Normal          << "\n";
    std::cout << Style::Italic          << "Italic          " << Style::NotItalic       << "\n";
    std::cout << Style::Underline       << "Underline       " << Style::NotUnderlined   << "\n";
    std::cout << Style::Blink           << "Blink           " << Style::NotBlinking     << "\n";
    std::cout << Style::RapidBlink      << "RapidBlink      " << Style::NotBlinking     << "\n";
    std::cout << Style::Reverse         << "Reverse         " << Style::NotReversed     << "\n";
    std::cout << Style::Conceal         << "Concealed       " << Style::Reveal          << "\n";
    std::cout << Style::Strike          << "Strike          " << Style::NotStriked      << "\n";
    std::cout << Style::Overline        << "Overline        " << Style::NotOverlined    << "\n";
    std::cout << Style::DoubleUnderline << "DoubleUnderline " << Style::NotUnderlined   << "\n";
    std::cout << Style::Superscript     << "Superscript     " << Style::NotScripted     << "\n";
    std::cout << Style::Subscript       << "Subscript       " << Style::NotScripted     << "\n";
    std::cout << Style::Reset << endl;
}

}
