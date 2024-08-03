export module Vite.Util.Timer;

import Vite.Base;
import Vite.Logger;

export namespace Hedron {

///
/// @brief Timer Units: Seconds (s), Milliseconds (ms), Microseconds (µs), Nanoseconds (ns)
///
enum class TimerUnit {
    Seconds,
    Milliseconds,
    Microseconds,
    Nanoseconds,
};

///
/// @brief Timer: Counts ticks until either GetDeltaTime or GetDeltaTimeAs is called.
///
class Timer {
    /// Types
    using Clock = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<Clock>;
    using TimeUnit = std::chrono::duration<double, std::milli>;

public:
    /// Default
    Timer(): mStartTime(Clock::now()) {}
    ~Timer() = default;

    /// Accessors
    // Retrieve delta time in ms
    inline const double DeltaTime() {
        auto duration = CalculateDuration();
        Reset();
        return duration.count();
    }
    // Retrieve delta time in specified unit (s = default, ms, µs, ns)
    inline const double DeltaTimeAs(TimerUnit unit = TimerUnit::Seconds) {
        double duration {};
        auto elapsed = CalculateDuration();
        switch (unit) {
            case TimerUnit::Seconds:		{ duration = std::chrono::duration<double>(elapsed).count();             break; }
            case TimerUnit::Milliseconds:	{ duration = std::chrono::duration<double, std::milli>(elapsed).count(); break; }
            case TimerUnit::Microseconds:	{ duration = std::chrono::duration<double, std::micro>(elapsed).count(); break; }
            case TimerUnit::Nanoseconds:	{ duration = std::chrono::duration<double, std::nano>(elapsed).count();  break; }
            default: { break; }
        }
        Reset();
        return duration;
    }
    // Retrieve a delta time slice in ms
    inline const double Now() {
        return CalculateDuration().count();
    }

private:
    /// Methods
    inline TimeUnit CalculateDuration() { return { Clock::now() - mStartTime }; }
    inline void Reset() { mStartTime = Clock::now(); }

private:
    /// Properties
    TimePoint mStartTime;
};

///
/// @brief: Scoped Timer: Counts ticks until it goes out of scope.
/// @detail Destroys itself when it goes out of scope.
/// @example
/// ScopedTimer timer("Test");
///
class ScopedTimer {
    /// Types
    using Callback = function<void(const string &, double duration)>;
    using Clock = std::chrono::steady_clock;
    using Duration = std::chrono::microseconds;
    using TimePoint = std::chrono::time_point<Clock>;
    using TimeStep = std::chrono::duration<double, std::micro>;

public:
    /// Default
    ScopedTimer(string_view name, const Callback &callback = nullptr):
        mName(name),
        mStopped(false),
        mStartTime(Clock::now()),
        mCallback(callback) {
    }
    ~ScopedTimer() { if (!mStopped) { Stop(); } };

    /// Methods
    void Stop() {
        using namespace std::chrono;
        mStopped = true;

        auto startTime = time_point_cast<Duration>(mStartTime).time_since_epoch().count();
        auto stopTime = time_point_cast<Duration>(Clock::now()).time_since_epoch().count();
        auto duration = (stopTime - startTime) * 0.001f;

        if (mCallback) {
            mCallback(mName, duration);
        } else {
            LogInfo("{} [Duration: {}ms | ThreadID: {}]", mName, duration, std::this_thread::get_id());
        }
    }

private:
    /// Callbacks
    Callback mCallback;

    /// Properties
    string mName;
    TimePoint mStartTime;
    bool mStopped {};
};

}
