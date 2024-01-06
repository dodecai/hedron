export module Vite.Logger.LogSink;

import Vite.Base;
import Vite.Logger.LogLevel;
import Vite.Logger.LogRecord;

export namespace Hedron {

///
/// @brief Supported Sinks
///
enum class LoggerType {
    Console = 0x0,
    File    = 0x1,
    Memory  = 0x2,
};

///
/// @brief Logger Sink Interface
///
class ILogger {
public:
    virtual ~ILogger() = default;

    virtual void operator()(const LogRecord &record, std::format_args arguments) = 0;

    virtual const string &GetName() const = 0;
    virtual LoggerType GetType() const = 0;
};

///
/// @brief Console Sink
///
class ConsoleLogger: public ILogger {
public:
    ConsoleLogger(const string &name = "Console"): mName(name) {}

    void operator()(const LogRecord &record, std::format_args arguments) override {
        std::lock_guard<std::mutex> lock(mMutex);

        auto levelColor = GetLogLevelColor(record.Level);
        string message = std::vformat(record.Format, arguments);
        // mStream << std::format...
        switch (record.Level) {
            case LogLevel::Default: {
                mStream << std::format("{}{}{}",
                    levelColor, message,
                    Cli::Style::Reset
                );
                break;
            }
            case LogLevel::Caption: {
                mStream << std::format("{}{}  {}{}{}{}{}",
                    levelColor, record.Level,
                    Cli::Color::White, message,
                    levelColor, record.Level,
                    Cli::Style::Reset, Cli::Color::Default
                );
                break;
            }
            case LogLevel::Delimiter: {
                mStream << std::format("{}{}{}{}",
                    levelColor, record.Level,
                    Cli::Style::Reset, Cli::Color::Default
                );
                break;
            }
            default: {
                mStream << std::format("{}{}{}{}{}<{}> {}{}{}{}",
                    Cli::Color::Gray, record.Timestamp,
                    levelColor, record.Level,
                    Cli::Color::LightGray, record.Location.Class,
                    Cli::Color::White, message,
                    Cli::Style::Reset, Cli::Color::Default
                );
                break;
            }
        }
    }

    const string &GetName() const override { return mName; }
    LoggerType GetType() const override { return mType; }

private: 
    Cli::Color GetLogLevelColor(LogLevel level) {
        switch (level) {
            case LogLevel::Trace:        { return Hedron::Cli::Color::LightMagenta; }
            case LogLevel::Debug:        { return Hedron::Cli::Color::LightGreen; }
            case LogLevel::Info:         { return Hedron::Cli::Color::LightBlue; }
            case LogLevel::Warn:         { return Hedron::Cli::Color::LightYellow; }
            case LogLevel::Error:        { return Hedron::Cli::Color::LightRed; }
            case LogLevel::Fatal:        { return Hedron::Cli::Color::Red; }

            case LogLevel::Caption:      { return Hedron::Cli::Color::Cyan; }
            case LogLevel::Delimiter:    { return Hedron::Cli::Color::Yellow; }

            default:                     { return  Hedron::Cli::Color::White; }
        }
    }

private:
    string mName {};
    LoggerType mType { LoggerType::Console };

    mutex mMutex;
    ostream &mStream = std::cout;
    wostream &mWStream = std::wcout;
};

///
/// @brief File Sink
///
class FileLogger: public ILogger {
public:
    FileLogger(const string &file, const string &name = "File"): mStream(file), mName(name) {
        //throw std::runtime_error("Failed to open log file");
    }

    void operator()(const LogRecord &record, std::format_args arguments) override {
        std::lock_guard<std::mutex> lock(mMutex);

        string message = std::vformat(record.Format, arguments);
        switch (record.Level) {
            case LogLevel::Default: {
                mStream << std::format("{}{}",
                    record.Level,
                    message
                );
                break;
            }
            case LogLevel::Caption: {
                mStream << std::format("{}  {}{}",
                    record.Level,
                    message,
                    record.Level
                );
                break;
            }
            case LogLevel::Delimiter: {
                mStream << std::format("{}",
                    record.Level
                );
                break;
            }
            default: {
                mStream << std::format("{}{}<{}> {}",
                    record.Timestamp,
                    record.Level,
                    record.Location.Class,
                    message
                );
                break;
            }
        }

        mStream.flush();
    }

    const string &GetName() const override { return mName; }
    LoggerType GetType() const override { return mType; }

private:
    string mName {};
    LoggerType mType { LoggerType::File };

    mutex mMutex;
    ofstream mStream;
};

///
/// @brief Memory Sink
///
class MemoryLogger: public ILogger {
private:
    using Messages = unordered_map<LogRecord, string, LogRecordHasher>;

public:
    MemoryLogger(const string &name = "Memory"): mName(name) {}

    void operator()(const LogRecord &record, std::format_args arguments) override {
        std::lock_guard<mutex> lock(mMutex);
        string buffer {};
        std::format_to(std::back_inserter(buffer), "{}", std::vformat(record.Format, arguments));
        mMessages.emplace(record, buffer);
    }

    const string &GetName() const override { return mName; }
    LoggerType GetType() const override { return mType; }
    const Messages &GetMessages() const { return mMessages; }

    void Clear() {
        std::lock_guard<mutex> lock(mMutex);
        mMessages.clear();
    }

private:
    string mName {};
    LoggerType mType { LoggerType::Memory };

    mutex mMutex;
    Messages mMessages;
};

}
