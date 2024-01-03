///
/// @brief: This module serves something like a memory allocation/deallocation watcher.
///         It will notify the application, if possible memory leaks are detected.
/// @note:  Currently this is only the barebone, there is still some work to be done.
/// 
export module Vite.Memory;

import std.compat;
import Vite.Logger;

///
/// @brief Properties
///

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

export namespace Hedron::Debug::Memory {

inline void VerifyUsage() {
    Hedron::Log("Current Memory Usage: {} bytes\n - Total Allocated: {} bytes\n - Total Deallocated: {} bytes",
        sAllocationMetrics.CurrentUsage(),
        sAllocationMetrics.TotalAllocated,
        sAllocationMetrics.TotalFreed
    );
}

inline void DetectLeaks() {
    auto &freed = ::sAllocationMetrics.TotalFreed;
    auto &total = ::sAllocationMetrics.TotalAllocated;
    auto usage = ::sAllocationMetrics.CurrentUsage();

    if (total > 0 && freed > 0) {
        if (usage > 0) {
            Hedron::LogWarning("Memory Leaks Detected [leaked '{}' bytes]!", usage);
        } else {
            Hedron::LogInfo("No Memory Leaks Detected.");
        }
    } else if (total > 0 || freed > 0) {
        Hedron::LogError("Memory Leak Detection failed!");
    } else {
        Hedron::LogInfo("Nothing was allocated.");
    }

    VerifyUsage();
}

}
