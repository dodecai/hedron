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
        auto elapsed = Clock::now();
        auto args = std::make_format_args(elapsed);
        try {
            return std::vformat(format, args);
        } catch (const std::exception &ex) {
            return ex.what();
        }
    }
    static inline string RuntimeTicks (const string_view &format = "P{0}DT{1:02}:{2:02}:{3:02}.{4:03}") {
        // "P{0}Y{1}M{2}DT{3:02}:{4:02}:{5:02}.{6:03}"
        /// Option A: "P{:%H:%M:%S}" (lacks support for days)
        //auto elapsed = Clock::now() - sStartTime;
        //auto args = std::make_format_args(elapsed);
        //try {
        //    return std::vformat("P{:%H:%M:%S}", args);
        //} catch (const std::exception &ex) {
        //    return ex.what();
        //}

        /// Option B: "P{0:02d}DT{1:02d}:{2:02d}:{3:02d}"
        auto elapsed = Clock::now() - sStartTime;

        //auto years = std::chrono::duration_cast<std::chrono::years>(elapsed);
        //elapsed -= years;
        //auto months = std::chrono::duration_cast<std::chrono::months>(elapsed);
        //elapsed -= months;
        auto days = std::chrono::duration_cast<std::chrono::days>(elapsed);
        elapsed -= days;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(elapsed);
        elapsed -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed);
        elapsed -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed);
        elapsed -= seconds;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

        //auto Y = years.count();
        //auto M = months.count();
        auto D = days.count();
        auto h = hours.count();
        auto m = minutes.count();
        auto s = seconds.count();
        auto ms = milliseconds.count();

        auto args = std::make_format_args(
            //Y,
            //M,
            D,
            h,
            m,
            s,
            ms
        );
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
