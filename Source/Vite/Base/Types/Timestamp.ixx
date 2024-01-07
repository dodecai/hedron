export module Vite.Type.Timestamp;

import Vite.Type.Concepts;

export namespace Hedron {

///
/// @brief Timestamp: Holds the delta time in milliseconds for floating-point types.
///
template <typename_floating_point T = double>
class Timestamp {
public:
    /// Default
    Timestamp(T time = 0.0): mTime { time } {}
    ~Timestamp() = default;

    /// Accessors
    inline const T GetSeconds() const { return mTime / 1000.0; }
    inline const T GetMilliseconds() const { return mTime; }

    /// Operators
    inline operator T() { return GetSeconds(); }

private:
    /// Properties
    T mTime;
};

/// Aliases
using DeltaTime = Timestamp<double>;

}
