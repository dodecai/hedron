﻿export module Vite.Type.SourceLocation;

import std;
import Vite.Extension;

/// Helpers
namespace Hedron {

// Extracts the pretty class name from a function signature
consteval std::string_view ExtractClassFromSignature(const std::string_view signature) {
    const size_t classEnd = constexpr_rfind(signature, '(');
    if (classEnd == std::string_view::npos || classEnd <= 0) { return ""; }

    const size_t namespaceStart = constexpr_rfind(signature, ' ', classEnd) + 1;
    if (namespaceStart == std::string_view::npos) { return ""; }

    return signature.substr(namespaceStart, classEnd - namespaceStart);
}

}

export namespace Hedron {

///
/// @brief SourceLocation (with more information)
/// @detail This code is based on the default implementation (source_location), but contains more information.
///
struct SourceLocation {
    /// Data
    std::string_view File {};
    std::string_view Class {};
    std::string_view Function {};
    std::string_view FunctionSignature {};
    std::uint32_t Line {};
    std::uint32_t Column {};

    /// Default
    [[nodiscard]] constexpr SourceLocation() noexcept = default;

    /// Methods
    [[nodiscard]] static consteval SourceLocation Current(
            const std::string_view file = __builtin_FILE(),
            const std::string_view function = __builtin_FUNCTION(),
            const std::string_view signature = __builtin_FUNCSIG(),
            const std::uint32_t line = __builtin_LINE(),
            const std::uint32_t column = __builtin_COLUMN()
    ) noexcept {
        SourceLocation result {};
        result.File = file;
        result.Class = ExtractClassFromSignature(signature);
        result.Function = function;
        result.FunctionSignature = signature;
        result.Line = line;
        result.Column = column;
        return result;
    }
};

}
