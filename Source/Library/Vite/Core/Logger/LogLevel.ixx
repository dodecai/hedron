export module Vite.Logger.LogLevel;

import Vite.Base;

///
/// Log Level
///
export namespace Hedron {

///
/// @brief Contains the classic Log Levels with extensions for structuring
/// Messaging: Trace, Debug, Info, Warn, Error, Fatal + Default (simple message)
/// Structuring: Caption and Delimiter
///
enum class LogLevel {
    // Log Levels
    Trace   = 0x1,	// Message (Level 1): Everything that could be interesting in the future.
    Debug   = 0x2,	// Message (Level 2): Debugging messages, which can help at parts, where we are unsure if the code will ever fail.
    Info    = 0x3,	// Message (Level 3): Information that is maybe useful for gathering basic system data.
    Warn    = 0x4,	// Message (Level 4): Has no impact on the application itself but should get sometime fixed.
    Error   = 0x5,  // Message (Level 5): Error messages that have no impact on runtime execution.
    Fatal   = 0x6,	// Message (Level 6): Critical messages which will break runtime execution.
    Default = 0x7,	// Message (Level 7): Default output with nothing added

    // Structuring
    Caption     = 0x20,	// Structure the log by a given caption
    Delimiter   = 0x21,	// Structure the log with a delimiter
};

// Concepts
template <typename T>
concept typename_logmodifier =
    std::is_same_v<std::decay_t<T>, LogLevel>;

// Overloads
template <typename_logmodifier T>
inline auto &operator<<(ostream &os, const T &level) {
    switch (level) {
        case Hedron::LogLevel::Trace:   { return os << " [ Trace ] "; }
        case Hedron::LogLevel::Debug:   { return os << " [ Debug ] "; }
        case Hedron::LogLevel::Info:    { return os << " [ Info  ] "; }
        case Hedron::LogLevel::Warn:    { return os << " [ Warn  ] "; }
        case Hedron::LogLevel::Error:   { return os << " [ Error ] "; }
        case Hedron::LogLevel::Fatal:   { return os << " [ Fatal ] "; }

        case Hedron::LogLevel::Caption: {
            return os << "\n▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n";
        }
        case Hedron::LogLevel::Delimiter: {
            return os << "----------------------------------------------------------------\n";
        }

        default: { return os; }
    }
}

template <typename_logmodifier T>
inline auto &operator<<(wostream &os, const T &level) {
    switch (level) {
        case Hedron::LogLevel::Trace:   { return os << " [ Trace ] "; }
        case Hedron::LogLevel::Debug:   { return os << " [ Debug ] "; }
        case Hedron::LogLevel::Info:    { return os << " [ Info  ] "; }
        case Hedron::LogLevel::Warn:    { return os << " [ Warn  ] "; }
        case Hedron::LogLevel::Error:   { return os << " [ Error ] "; }
        case Hedron::LogLevel::Fatal:   { return os << " [ Fatal ] "; }

        case Hedron::LogLevel::Caption: {
            return os << "\n▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n";
        }
        case Hedron::LogLevel::Delimiter: {
            return os << "----------------------------------------------------------------\n";
        }

        default: { return os; }
    }
}

}

// Global Overloads
namespace std {

template <>
struct formatter<Hedron::LogLevel> {
    constexpr auto parse(format_parse_context &context) {
        return context.begin();
    }

    auto format(const Hedron::LogLevel &level, format_context &context) const {
        switch (level) {
            case Hedron::LogLevel::Trace:    { return format_to(context.out(), " [ Trace ] "); }
            case Hedron::LogLevel::Debug:    { return format_to(context.out(), " [ Debug ] "); }
            case Hedron::LogLevel::Info:     { return format_to(context.out(), " [ Info  ] "); }
            case Hedron::LogLevel::Warn:     { return format_to(context.out(), " [ Warn  ] "); }
            case Hedron::LogLevel::Error:    { return format_to(context.out(), " [ Error ] "); }
            case Hedron::LogLevel::Fatal:    { return format_to(context.out(), " [ Fatal ] "); }

            case Hedron::LogLevel::Caption: {
                return format_to(context.out(),
                    "\n▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬▬\n");
            }
            case Hedron::LogLevel::Delimiter: {
                return format_to(context.out(),
                    "----------------------------------------------------------------\n"
                );
            }

            default: { return format_to(context.out(), ""); }
        }
    }
};

}
