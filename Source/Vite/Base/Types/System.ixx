export module Vite.Type.System;

import Vite.Runtime.Benchmark;

export namespace Hedron {

///
/// @brief System: Base template for all systems.
///
template <typename Derived>
class System {
public:
    /// Default
    System() = default;
    virtual ~System() = default;

    /// Methods

    double GetDuration() {
        return mBenchmark.Duration;
    }

    // Calls the derived class's Update method
    void Update() {
        mBenchmark.Start();
        static_cast<Derived*>(this)->OnUpdate();
        mBenchmark.Stop();
    }

private:
    // Properties
    Benchmark mBenchmark;
};

}
