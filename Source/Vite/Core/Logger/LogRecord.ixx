export module Vite.Logger.LogRecord;

import Vite.Base;
import Vite.Logger.LogLevel;
import Vite.Util.Chrono;

export namespace Hedron {

///
/// @brief LogRecord
/// Contains the format, the location, the loglevel and timestamp.
/// 
/// @remark I tried Timestamp as string_view, it worked ... but only as function parameter,
/// when I tried to create LogRecord normally, the Timestamp was corrupted, so as GetTimeStamp()
/// creates a string anyway, it should be fine to leave it as string. After some tests, it was
/// faster then string_view, 'cause under the hood it created a temporary string_view.
///
struct LogRecord {
    /// Properties
    const char *Format;
    mutable LogLevel Level;
    SourceLocation Location;
    string Timestamp;

    /// Default
    LogRecord(const char *format, const LogLevel &level = LogLevel::Default, const string &timestamp = Chrono::Timestamp(), const SourceLocation &location = SourceLocation::Current()):
        Format(format),
        Level(level),
        Location(location),
        Timestamp(timestamp) {
    }

    /// Comparison
    bool operator==(const LogRecord &other) const {
        return Level == other.Level && Timestamp == other.Timestamp;
    }
};

/// Overloads
struct LogRecordHasher {
    size_t operator()(const LogRecord &record) const {
        return std::hash<LogLevel>{}(record.Level) ^ std::hash<string>{}(record.Timestamp);
    }
};

}
