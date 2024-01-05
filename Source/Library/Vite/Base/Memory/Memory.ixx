///
/// @brief: This module serves something like a memory allocation/deallocation watcher.
///         It will notify the application, if possible memory leaks are detected.
/// @note:  Currently this is only the barebone, there is still some work to be done.
/// 
export module Vite.Memory;

import std.compat;

///
/// @brief Properties
///

// Allocation Metrics: holds the current memory usage
struct AllocationMetrics {
    size_t TotalAllocated {};
    size_t TotalFreed {};

    size_t CurrentUsage() { return TotalAllocated - TotalFreed; }
} inline sAllocationMetrics {};

///
/// @brief Overrides
///

export void *operator new(size_t size) {
    sAllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

export void *operator new[](size_t size) {
    sAllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

export void operator delete(void *memory, size_t const size) noexcept {
    sAllocationMetrics.TotalFreed += size;
    free(memory);
}

export void operator delete[](void *memory) noexcept {
    free(memory);
}

export void operator delete[](void *memory, size_t size) noexcept {
    sAllocationMetrics.TotalFreed += size;
    free(memory);
}

///
/// @brief Functions
///

export namespace Hedron::Memory::Debug {

constexpr auto caption = "Hedron::Memory::Debug";

///
/// @brief Print the current memory usage
/// 
inline void VerifyUsage() {
    std::print("Current Memory Usage: {} bytes\n - Total Allocated: {} bytes\n - Total Deallocated: {} bytes\n",
        sAllocationMetrics.CurrentUsage(),
        sAllocationMetrics.TotalAllocated,
        sAllocationMetrics.TotalFreed
    );
}

///
/// @brief Detect memory leaks and print the result
/// @note Must be called with std::atexit
/// 
inline void DetectLeaks() {
    auto freed = ::sAllocationMetrics.TotalFreed;
    auto total = ::sAllocationMetrics.TotalAllocated;
    auto usage = ::sAllocationMetrics.CurrentUsage();

    if (total > 0 && freed > 0) {
        if (usage > 0) {
            std::print("# [ WARN  ] {}: Memory Leaks Detected [leaked '{}' bytes]!\n", caption, usage);
        } else {
            std::print("# [ INFO  ] {}: No Memory Leaks Detected.\n", caption);
        }
    } else if (total > 0 || freed > 0) {
        std::print("# [ ERROR ] {}: Memory Leak Detection failed!\n", caption);
    } else {
        std::print("# [ INFO  ] {}: Nothing was allocated.\n", caption);
    }

    VerifyUsage();
}

}
