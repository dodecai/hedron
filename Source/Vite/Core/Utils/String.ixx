﻿export module Vite.Util.String;

// Library
import Vite.Base;

export namespace Hedron {

///
/// @brief String: This util offers easy to use string extensions
/// @todo Port to C++20 with latest features
///
class String: public StaticObject {
public:
    /// Methods
    // Checks if the given string contains the given token
    static bool Contains(const string_view &value, const string_view &token, bool caseSensitive = false) noexcept {
        if (value.length() < token.length()) return false;
        if (caseSensitive) {
            return value.find(token) != string::npos;
        } else {
            auto it = std::search(value.begin(), value.end(), token.begin(), token.end(), [](const char char1, const char char2) {
                return std::tolower(char1) == std::tolower(char2);
            });
            return (it != value.end());
        }
    }

    // Checks if the given string contains the given token
    template <typename CharT, typename Traits, typename Allocator>
    static bool ContainsW(const std::basic_string<CharT, Traits, Allocator> &value, const std::basic_string<CharT, Traits, Allocator> &token) {
        return std::ranges::search(string, token) != value.end();
    }

    // Checks if the given string ends with the given token
    static bool EndsWith(string_view value, string_view token, bool caseSensitive = false) noexcept {
        if (value.length() < token.length()) return false;
        if (caseSensitive) {
            return value.compare(value.length() - token.length(), token.length(), token) == 0;
        } else {
            auto it = std::search(value.begin(), value.end(), token.begin(), token.end(), [](const char char1, const char char2) {
                return std::tolower(char1) == std::tolower(char2);
            });
            return (it == value.end() - token.length());
        }
    }

    // Checks if the given string starts with the given token
    static bool StartsWith(string_view value, string_view token, bool caseSensitive = false) noexcept {
        if (value.length() < token.length()) return false;
        if (caseSensitive) {
            return value.compare(0, token.length(), token) == 0;
        } else {
            auto it = std::search(value.begin(), value.end(), token.begin(), token.end(), [](const char char1, const char char2) {
                return std::tolower(char1) == std::tolower(char2);
            });
            return (it == value.begin());
        }
    }

    // Checks if the given string is a number
    static bool IsNumeric(string_view value) noexcept {
        return std::all_of(value.cbegin(), value.cend(), [](auto c) {
            return (c >= '0' && c <= '9') || c == '-' || c == ',' || c == '.';
        });
    }

    // Checks if the given string is a decimal number
    static bool IsDecimal(string_view value) noexcept {
        return std::all_of(value.cbegin(), value.cend(), [](auto c) {
            return (c >= '0' && c <= '9');
        });
    }

    // Checks if the given string is a hexadecimal number
    static bool IsHexadecimal(string_view value) noexcept {
        return std::all_of(value.cbegin(), value.cend(), [](auto c) {
            return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') || (c == 'x' || c == 'X');
        });
    }

    // Checks if the given string is a octal number
    static bool IsOctal(string_view value) noexcept {
        return std::all_of(value.cbegin(), value.cend(), [](auto c) {
            return (c >= '0' && c <= '7');
        });
    }

    // Joins the given values with the given separator
    static string Join(const vector<string> &values, char separator) {
        std::string result;
        for (auto it = values.begin(); it != values.end(); ++it) {
            result += *it;
            if (it + 1 != values.end()) {
                result += separator;
            }
        }
        return result;
    }

    // Replaces all occurrences of the given token with the given to
    static string &Replace(string &value, string_view token, string_view to, bool caseSensitive = false) noexcept {
        if (value.empty() || token.empty() || value.length() < token.length()) return value;
        if (caseSensitive) {
            auto position = value.find(token);
            while (position != std::string::npos) {
                value.replace(position, token.length(), to);
                position = value.find(token, position + token.size());
            }
        } else {
            auto positionStart = std::search(value.begin(), value.end(), token.begin(), token.end(), [](const char char1, const char char2) {
                return std::tolower(char1) == std::tolower(char2);
            });
            while (positionStart != value.end()) {
                auto positionEnd = positionStart;
                std::advance(positionEnd, token.length());
                value.replace(positionStart, positionEnd, to);
                positionStart = std::search(positionStart, value.end(), token.begin(), token.end(), [](const char char1, const char char2) {
                    return std::tolower(char1) == std::tolower(char2);
                });
            }
        }
        return value;
    }

    // Splits the given string with the given separator
    static vector<string> Split(const string &value, char seperator) noexcept {
        std::stringstream stream(value);
        string token;
        vector<string> tokens;

        while (std::getline(stream, token, seperator)) {
            tokens.emplace_back(token);
        }
        return tokens;
    }

    // Converts the given string to lower case
    template<typename T> // ToDo: Concept doesn't work as expected after 16.10 Preview 2
    static T &ToLower(T &value) noexcept {
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        return value;
    }

    // Converts the given string to upper case
    template<typename T> // ToDo: Concept doesn't work as expected after 16.10 Preview 2
    static T &ToUpper(T &value) noexcept {
        std::transform(value.begin(), value.end(), value.begin(), ::toupper);
        return value;
    }
};

///
/// Tests
///
namespace Test {

void TestString();

}

}

///
/// Implementation
///
module: private;

namespace Hedron::Test {

void TestString() {
    string string00 = "First Second and SeConD Third";
    string string01 = "fiRst";
    string string02 = "second";
    string string03 = "ThIrD";
    string string04 = "-Foruth";

    string string11 = "-123,456.789a";
    string string12 = "0123456789";
    string string13 = "0123456789a";
    string string14 = "0x123456789ABCDEF";
    string string15 = "0x123456789ABCDEFG";
    string string16 = "01234567";
    string string17 = "012345678";
    string string10 = "-123,456.789";

    string string20 = "This is a very long sentence for a small string!";
    string string21 = "What the ... should i do. Maybe it would be my 1st try to 3489032840921384092384902318490823149203945803294.";
    std::wstring wstring20 = L"Dies ist ein sehr langer Satz für einen String, deshalb sollter er mit bedacht eingesetzt werden!";
    std::wstring wstring21 = L"Ein paar Zeichen zum testen #+äü+ö€";

    // Perform simple tests
    //AppAssert(!String::StartsWith(string00, string01, true), "[Application::Utility::String]: '{}' starts with '{}' filed!", string00, string01);
    //AppAssert(String::StartsWith(string00, string01), "[Application::Utility::String]: '", string00, "' starts with '", string01, "' failed!");
    //AppAssert(!String::StartsWith(string00, string03), "[Application::Utility::String]: '", string00, "' starts with '", string03, "' failed!");

    //AppAssert(!String::Contains(string00, string02, true), "[Application::Utility::String]: '", string00, "' contains '", string02, "' failed!");
    //AppAssert(String::Contains(string00, string02), "[Application::Utility::String]: '", string00, "' contains '", string02, "' failed!");
    //AppAssert(!String::Contains(string00, string04), "[Application::Utility::String]: '", string00, "' contains '", string04, "' failed!");

    //AppAssert(!String::EndsWith(string00, string03, true), "[Application::Utility::String]: '", string00, "' ends with '", string03, "' failed!");
    //AppAssert(String::EndsWith(string00, string03), "[Application::Utility::String]: '", string00, "' ends with '", string03, "' failed!");
    //AppAssert(!String::EndsWith(string00, string01), "[Application::Utility::String]: '", string00, "' ends with '", string01, "' failed!");

    //AppAssert(String::IsNumeric(string10), "[Application::Utility::String]: '", string10, "' is numeric failed!");
    //AppAssert(!String::IsNumeric(string11), "[Application::Utility::String]: '", string11, "' is numeric failed!");

    //AppAssert(String::IsDecimal(string12), "[Application::Utility::String]: '", string12, "' is decimal failed!");
    //AppAssert(!String::IsDecimal(string13), "[Application::Utility::String]: '", string13, "' is decimal failed!");

    //AppAssert(String::IsHexadecimal(string14), "[Application::Utility::String]: '", string14, "' is hexadecimal failed!");
    //AppAssert(!String::IsHexadecimal(string15), "[Application::Utility::String]: '", string15, "' is hexadecimal failed!");

    //AppAssert(String::IsOctal(string16), "[Application::Utility::String]: '", string16, "' is octal failed!");
    //AppAssert(!String::IsOctal(string17), "[Application::Utility::String]: '", string17, "' is octal failed!");

    // Perform advanced test
    String::Replace(string00, "second", "sec", true);
    String::Replace(string00, "second", "sec");
    String::Replace(string11, "a", "b");

    auto vector1 = String::Split(string00, ' ');
    auto vector2 = String::Split(string10, ',');

    //String::ToLower(string20);
    //String::ToUpper(string20);
    //String::ToLower(string21);
    //String::ToUpper(string21);

    //String::ToLower(wstring20);
    //String::ToUpper(wstring20);
    //String::ToLower(wstring21);
    //String::ToUpper(wstring21);

    //const auto stringA0 = "a"_hash;
    //const auto stringA1 = "a"_hash;
    //if (stringA0 != stringA1) {}
}

}
