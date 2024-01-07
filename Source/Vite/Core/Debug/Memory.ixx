export module Vite.Debug.Memory;

import std.compat;
import Vite.Base;

///
/// @brief: This module serves something like a memory allocation/deallocation watcher.
///         It will notify the application, if possible memory leaks are detected.
/// @note:  Currently this is only the barebone, there is still some work to be done.
/// 

///
/// Properties
///

// Allocation Metrics: holds the current memory usage
struct AllocationMetrics {
    size_t TotalAllocated {};
    size_t TotalFreed {};

    size_t CurrentUsage() { return TotalAllocated - TotalFreed; }
} inline sAllocationMetrics {};

///
/// Overrides
///

export {

void *operator new(size_t size) {
    sAllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void *operator new[](size_t size) {
    sAllocationMetrics.TotalAllocated += size;
    return malloc(size);
}

void operator delete(void *memory, size_t const size) noexcept {
    sAllocationMetrics.TotalFreed += size;
    free(memory);
}

void operator delete[](void *memory) noexcept {
    free(memory);
}

void operator delete[](void *memory, size_t size) noexcept {
    sAllocationMetrics.TotalFreed += size;
    free(memory);
}

}

///
/// Functions
///

export namespace Hedron::Debug::Memory {

constexpr auto Caption = "Hedron::Debug::Memory";
constexpr auto MebiByte = 1024.0 * 1024.0;

///
/// @brief Print the current memory usage
/// 
inline void VerifyUsage() {
    std::print("{}# {}[ Trace ] {}<{}>: {}Current Memory Usage: {} bytes\n\t- Total Allocated:\t{:.3f} MiB\n\t- Total Deallocated:\t{:.3f} MiB\n",
        Hedron::Cli::Color::Gray,
        Hedron::Cli::Color::LightMagenta,
        Hedron::Cli::Color::LightGray, Caption,
        Hedron::Cli::Color::White, sAllocationMetrics.CurrentUsage() / MebiByte,
        static_cast<double>(sAllocationMetrics.TotalAllocated /MebiByte),
        static_cast<double>(sAllocationMetrics.TotalFreed / MebiByte)
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

    std::print("\n");
    if (total > 0 && freed > 0) {
        if (usage > 0) {
            std::print("{}# {}[ Warn  ] {}<{}>: {}Memory Leaks Detected [leaked '{}' bytes]!\n",
                Hedron::Cli::Color::Gray,
                Hedron::Cli::Color::LightYellow,
                Hedron::Cli::Color::LightGray, Caption,
                Hedron::Cli::Color::White, usage
            );
        } else {
            std::print("{}# {}[ Info  ] {}<{}>: {}No Memory Leaks Detected.\n",
                Hedron::Cli::Color::Gray,
                Hedron::Cli::Color::LightBlue,
                Hedron::Cli::Color::LightGray, Caption,
                Hedron::Cli::Color::White
            );
        }
    } else if (total > 0 || freed > 0) {
        std::print("{}# {}[ Error ] {}<{}>: {}Memory Leak Detection failed!\n",
            Hedron::Cli::Color::Gray,
            Hedron::Cli::Color::LightRed,
            Hedron::Cli::Color::LightGray, Caption,
            Hedron::Cli::Color::White
        );
    } else {
        std::print("{}# {}[ Info  ] {}<{}>: {}Nothing was allocated.\n",
            Hedron::Cli::Color::Gray,
            Hedron::Cli::Color::LightBlue,
            Hedron::Cli::Color::LightGray, Caption,
            Hedron::Cli::Color::White
        );
    }

    VerifyUsage();
}

}
