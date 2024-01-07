export module Vite.Util.Chrono;

import Vite.Base;

export namespace Hedron {

///
/// @brief Chrono: Delivers current date/time/runtime/timestamp in ISO 8601 format.
/// Simply use 'Chrono' under the Hedron namespace to retrieve the desired information.
/// 
class Chrono: public StaticObject {
    /// Types
    using Clock = std::chrono::system_clock;
    using TimePoint = std::chrono::time_point<std::chrono::system_clock>;

public:
    /// Accessors
    // Retrieve current date in ISO 8601 format 'YYYY-mm-dd'
    static inline string Date() { return Ticks("{:%Y-%m-%d}"); }
    // Retrieve current time in ISO 8601 format 'HH:mm:ss.cccccc'
    static inline string Time() { return Ticks("{:%H:%M:%S}"); }
    // Retrieve runtime in ISO 8601 format 'PddTHH:mm:ss'
    static inline string Runtime() { return RuntimeTicks(); }
    // Retrieve timestamp in ISO 8601 format 'YYYY-mm-ddTHH:mm:ss.cccccc'
    static inline string Timestamp() { return Ticks(); }

private:
    /// Methods
    static inline string Ticks (const string_view &format = "{:%Y-%m-%dT%H:%M:%S}") {
        auto args = std::make_format_args(Clock::now());
        try {
            return std::vformat(format, args);
        } catch (const std::exception &ex) {
            return ex.what();
        }
    }
    static inline string RuntimeTicks (const string_view &format = "P{0:02d}DT{1:02d}:{2:02d}:{3:02d}") {
        /// Option A: "P{:%H:%M:%S}" (lacks support for years, months and days)
        //auto elapsed = Clock::now() - mStartTime;
        //auto args = std::make_format_args(elapsed);
        //try {
        //    return std::vformat(format, args);
        //} catch (const std::exception &ex) {
        //    return ex.what();
        //}

        /// Option B: "P{0:02d}DT{1:02d}:{2:02d}:{3:02d}"
        using namespace std::chrono;
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - sStartTime);

        auto year = duration_cast<years>(elapsed);
        elapsed -= year;
        auto month = duration_cast<months>(elapsed);
        elapsed -= month;
        auto day = duration_cast<days>(elapsed);
        elapsed -= day;
        auto hour = duration_cast<hours>(elapsed);
        elapsed -= hour;
        auto minute = duration_cast<minutes>(elapsed);
        elapsed -= minute;
        auto second = duration_cast<seconds>(elapsed);
        elapsed -= second;
        auto millisecond = duration_cast<microseconds>(elapsed);

        auto args = std::make_format_args(day.count(), hour.count(), minute.count(), second.count(), millisecond.count());
        try {
            return std::vformat(format, args);
        } catch (const std::exception &ex) {
            return ex.what();
        }
    }

private:
    /// Properties
    static inline const TimePoint sStartTime { Clock::now() };
};

}
