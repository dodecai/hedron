export module Vite.Logger;

import "Vite/Base/Platform/Support.h";

import Vite.Base;
import Vite.Util.String;

export import Vite.Logger.LogLevel;
export import Vite.Logger.LogRecord;
export import Vite.Logger.LogSink;

///
/// @brief This logger fulfils all your basic needs, and accepts nearly everything you throw at it.
/// The motivation behind this was an easy to use, but performant logger, you pay for what you use. It's
/// basically an extension to cout with some gimmicks.
/// @type Singleton
///
export namespace Hedron {

///
/// @brief Logger
/// 
/// @todo WideString Support
/// if constexpr (is_wstring_v<T>) mWStream << std::forward<T>(data);
/// else mStream << std::forward<T>(data);
///
class Logger: public SteadyObject {
    /// Friends
    friend class Application;

private:
    /// Default
    Logger(): mLogLevel(LogLevel::Trace) {}
    virtual ~Logger() = default;

    // Destroy the global instance
    static void Destroy() {
        delete &Instance();
    }

public:
    // Get the global instance to the logger
    static Logger &Instance() {
        static Logger *instance = new Logger();;
        return *instance;
    }

    /// Accessors
    LogLevel GetLevel() const {
        return mLogLevel;
    }

    /// Mutators
    void SetLevel(const LogLevel &level) {
        std::unique_lock<mutex> lock(mMutex);
        mLogLevel = level > LogLevel::Fatal ? LogLevel::Fatal : level;
    }

    /// Methods
    void Attach(Scope<ILogger> sink) {
        std::unique_lock<mutex> lock(mMutex);
        mSinks.push_back(std::move(sink));
    }
    void Detach(const string &name) {
        std::unique_lock<mutex> lock(mMutex);
        mSinks.erase(std::remove_if(mSinks.begin(), mSinks.end(), [&name](const Scope<ILogger> &sink) {
            return sink->GetName() == name;
        }), mSinks.end());
    }
    void Flush() {
        this->operator()({ "{}", mStreamLogLevel }, mStreamBuffer.view());
        mStreamBuffer.str("");
        mStreamBuffer.flush();
        mStreamLogLevel = LogLevel::Default;
    }

    ///
    /// Operators
    ///
    
    // Format-Support
    template<typename... Args>
    void operator()(const LogLevel &level, const LogRecord &record, Args &&...args) {
        if (record.Level < mLogLevel) return;
        record.Level = level;
        this->operator()(record, std::forward<Args>(args)...);
    }

    template<typename... Args>
    void operator()(const LoggerType &type, const LogRecord &record, Args &&...args) {
        if (record.Level < mLogLevel) return;
        std::lock_guard<mutex> lock(mMutex);
        mCounter++;
        try {
            auto formattedArgs = std::make_format_args(std::forward<Args>(args)...);
            for (const auto &sink : mSinks) {
                if (sink->GetType() == type) sink->operator()(record, formattedArgs);
            }
        } catch (std::exception ex) {
            //this->operator()("Hedron::Logger: {}", ex.what());
        }
    }

    template<typename... Args>
    void operator()(const LogRecord &record, Args &&...args) {
        if (record.Level < mLogLevel) return;
        std::lock_guard<mutex> lock(mMutex);
        mCounter++;
        try {
            auto formattedArgs = std::make_format_args(std::forward<Args>(args)...);
            for (const auto &sink : mSinks) {
                sink->operator()(record, formattedArgs);
            }
        } catch (std::exception ex) {
            //this->operator()("Hedron::Logger: {}", ex.what());
        }
    }

    // Log modifier stream
    template <typename_logmodifier T>
    Logger &operator<<(T &&data) {
        if constexpr (std::is_same_v<std::decay_t<T>, LogLevel>) {
            if (data >= mLogLevel) {
                mStreamLogLevel = data;
            } else {
                mSkip = true;
            }
        }
        return *this;
    }

    // Output Stream Template Support (std::endl, ...)
    Logger &operator<<([[maybe_unused]] ostream &(*T)(ostream &)) {
        if (mSkip) return *this;

        mStreamBuffer << '\n';
        this->operator()({ "{}", mStreamLogLevel }, mStreamBuffer.view());
        mStreamBuffer.str("");
        mStreamLogLevel = LogLevel::Default;
        return *this;
    }
    
    // Stream-Support
    template<typename T>
    Logger &operator<<(T &&data) {
        if (mSkip) return *this;

        mStreamBuffer << data;
        if constexpr (is_xstring_v<std::decay_t<T>>) {
            if (String::EndsWith(data, "\n")) {
                this->operator()({ "{}", mStreamLogLevel }, mStreamBuffer.view());
                mStreamBuffer.str("");
                mStreamLogLevel = LogLevel::Default;
            }
        }
        return *this;
    }

private:
    /// Properties
    LogLevel mLogLevel;
    mutex mMutex {};
    vector<Scope<ILogger>> mSinks {};
    ostringstream mStreamBuffer { "" };
    LogLevel mStreamLogLevel { LogLevel::Default };

    /// States
    uint64 mCounter {};
    bool mSkip = false;
};

// Global Logger Instance
inline Logger &logger = Logger::Instance();

///
/// @brief Aliases
/// @detail As good as a logger can be, we need something for applications where performance matters.
/// @note Therefore these function templates are for convenience, they will help removing unnecessary code in release and distribution builds, therefore they also override the log levels.
///

template<typename ...Args> void Log(const LogRecord &record, Args &&...args)            { logger(LogLevel::Default, record, args..., "\n"); }
template<typename ...Args> void LogCaption(const LogRecord &record, Args &&...args)     { logger(LogLevel::Caption, record, args...); }
template<typename ...Args> void LogDelimiter(const LogRecord &record, Args &&...args)   { logger(LogLevel::Delimiter, record, args...); }
#ifdef APP_MODE_DEBUG
    template<typename T, typename ...Args> bool AppAssert(T *object, const LogRecord &record, Args &&...args) {
        if (!object) {
            logger(LogLevel::Fatal, record, args..., "\n");
            //APP_DEBUGBREAK();
            return true;
        }
        return false;
    }
    template<typename T, typename ...Args> bool AppAssert(T object, const LogRecord &record, Args &&...args) {
        if (!object) {
            logger(LogLevel::Fatal, record, args..., "\n");
            //APP_DEBUGBREAK();
            return true;
        }
        return false;
    }

    template<typename ...Args> void LogTrace(const LogRecord &record, Args &&...args)   { logger(LogLevel::Trace, record, args..., "\n"); }
    template<typename ...Args> void LogDebug(const LogRecord &record, Args &&...args)   { logger(LogLevel::Debug, record, args..., "\n"); }
    template<typename ...Args> void LogInfo(const LogRecord &record, Args &&...args)    { logger(LogLevel::Info,  record, args..., "\n"); }
#elif APP_MODE_RELEASE
    template<typename ...Args> void AppAssert([[maybe_unused]] Args &&...args)          {}

    template<typename ...Args> void LogTrace([[maybe_unused]] Args &&...args)           {}
    template<typename ...Args> void LogDebug([[maybe_unused]] Args &&...args)           {}
    template<typename ...Args> void LogInfo(const LogRecord &record, Args &&...args)    { logger(LogLevel::Info,  record, args..., "\n"); }
#elif APP_MODE_DISTRIBUTION
    template<typename ...Args> void AppAssert([[maybe_unused]] Args &&...args)          {}

    template<typename ...Args> void LogTrace([[maybe_unused]] Args &&...args)           {}
    template<typename ...Args> void LogDebug([[maybe_unused]] Args &&...args)           {}
    template<typename ...Args> void LogInfo([[maybe_unused]] Args &&...args)            {}
#endif
template<typename ...Args> void LogWarning(const LogRecord &record, Args &&...args)     { logger(LogLevel::Warn,   record, args..., "\n"); }
template<typename ...Args> void LogError(const LogRecord &record, Args &&...args)       { logger(LogLevel::Error,  record, args..., "\n"); }
template<typename ...Args> void LogFatal(const LogRecord &record, Args &&...args)       { logger(LogLevel::Fatal,  record, args..., "\n"); }

///
/// Tests
///
namespace Test {

void TestLogger();

}

}

///
/// Implementation
///
module: private;

namespace Hedron::Test {

// Show me what you got!
void TestLogger() {
    // LogLevels
    logger(LogLevel::Caption, "Caption");
    logger(LogLevel::Default, "Default\n");
    logger(LogLevel::Fatal, "Fatal\n");
    logger(LogLevel::Error, "Error\n");
    logger(LogLevel::Warn, "Warn\n");
    logger(LogLevel::Info, "Info\n");
    logger(LogLevel::Debug, "Debug\n");
    logger(LogLevel::Trace, "Trace\n");
    logger(LogLevel::Delimiter, "");

    // Formatting
    logger("Test {}, if you can {}!\n", "me", 1);
    logger(LogLevel::Warn, "Test {}, if you can {}!\n", "me", 2);
    logger(LogLevel::Error, "Test {}, if you can {}!\n", "me", 3);

    logger << "Test " << "me" << ", if you can " << 4 << "!" << std::endl;
    logger << LogLevel::Warn << "Test " << "me" << ", if you can " << 5 << "!" << "\n";
    logger << LogLevel::Error << "Test " << "me" << ", if you can " << 6 << "!\n";
    logger << LogLevel::Error << "Test " << "me" << ", if you can " << 7 << "!";
    logger.Flush();
    logger << "\n";
    logger(LogLevel::Delimiter, "");

    // Filtered Logging and Multi-Color test (console only)
    logger(LoggerType::Console, "{}{}This {}{}is {}a {}multi{}-{}color{}-{}test!\n",
        Cli::Background::White, Cli::Color::Black,
        Cli::Background::Default, Cli::Color::LightBlue,
        Cli::Color::LightRed,
        Cli::Color::LightGray,
        Cli::Color::LightGreen,
        Cli::Color::LightCyan,
        Cli::Color::LightBlue,
        Cli::Color::Default
    );

    // Integer Types
    logger << "Integers[i|l|ll|u|ul|ull]: " << 0 << 0l << 0ll << 0u << 0ul << 0ull << "\n";

    // String based Types
    char Char[] = "Char *";
    const char *ConstChar = "ConstChar *";
    std::string String = "String";

    logger(LoggerType::Console, "{}{} {}{} {}{}\n",
        Cli::Color::LightRed, Char,
        Cli::Color::LightGreen, ConstChar,
        Cli::Color::LightBlue, String
    );

    // Wide-String based Types
    //wchar_t WChar_T[] = L"WChar_T *";
    //const wchar_t *ConstWChar_T = L"ConstWChar_T *";
    //std::wstring WString = L"WString";

    //logger("{}{} {}{} {}{}",
    //    Cli::Color::LightRed, WChar_T,
    //    Cli::Color::LightGreen, ConstWChar_T,
    //    Cli::Color::LightBlue, WString
    //);

    // Mixed String Types
    //logger << "Mixed String Types " << L"and Wide " << "... not wide " << L"and so on.\n";
}

}
