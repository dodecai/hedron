///
/// @brief: This module serves something like a memory allocation/deallocation watcher.
///         It will notify the application, if possible memory leaks are detected.
/// @note:  Currently this is only the barebone, there is still some work to be done.
/// 
export module Vite.Core.Memory;

import std.compat;
import Vite.Logger;

///
/// @brief Properties
///

struct AllocationMetrics {
    size_t TotalAllocated {};
    size_t TotalFreed {};

    size_t CurrentUsage() { return TotalAllocated - TotalFreed; }
} static sAllocationMetrics {};

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

export namespace Hedron::Debug {

inline void VerifyMemoryUsage() {
    Hedron::Log("Current Memory Usage: {} bytes\n - Total Allocated: {} bytes\n - Total Deallocated: {} bytes",
        sAllocationMetrics.CurrentUsage(),
        sAllocationMetrics.TotalAllocated,
        sAllocationMetrics.TotalFreed
    );
}

inline void DetectMemoryLeaks() {
    auto usage = sAllocationMetrics.CurrentUsage();
    if (usage != 0) {
        Hedron::LogWarning("Memory Leaks Detected [leaked '{}' bytes]!", usage);
    } else if (sAllocationMetrics.TotalAllocated == 0 && sAllocationMetrics.TotalFreed == 0) {
        Hedron::LogError("Memory Leak Detection failed!");
    } else {
        Hedron::LogInfo("No Memory Leaks Detected");
    }
    VerifyMemoryUsage();
}

}
