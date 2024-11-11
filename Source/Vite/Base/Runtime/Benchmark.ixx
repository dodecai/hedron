export module Vite.Runtime.Benchmark;

import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Benchmark: Base template for all benchmarks.
///
class Benchmark {
    /// Types
    using Clock = std::chrono::high_resolution_clock;
    using Timepoint = std::chrono::time_point<Clock>;

public:
    /// Default
    Benchmark() = default;
    virtual ~Benchmark() = default;

    /// Methods

    // Starts the benchmark
    void Start() {
        mStart = Clock::now();
    }

    // Stops the benchmark
    void Stop() {
        mStop = Clock::now();
        auto duration = std::chrono::duration<double, std::nano>(mStop - mStart).count();
        Duration = static_cast<double>(duration) * 1e-6;
    }

public:
    /// Properties
    static inline bool Active { true };
    double Duration {};

private:
    /// Properties
    Timepoint mStart;
    Timepoint mStop;
};

}
