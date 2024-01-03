﻿export module Vite.Type.Timestamp;

export namespace Hedron {

///
/// @brief Timestamp: Holds the delta time in milliseconds for floating-point types.
///
class Timestamp {
public:
    // Default
    Timestamp(double time = 0.0): mTime { time } {}
    ~Timestamp() = default;

    // Accessors
    inline const double GetSeconds() const { return mTime / 1000.0; }
    inline const double GetMilliseconds() const { return mTime; }

    // Operators
    inline operator double() { return GetSeconds(); }

private:
    // Properties
    double mTime;
};

}
