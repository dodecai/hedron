export module Vite.Util.Random;

import Vite.Base;

export namespace Hedron {

///
/// @brief Contains utility functions for generating random numbers and related functionality.
/// They can be used to support various aspects of your framework.
/// @note The functions and utilities here are useful for creating random data within the application.
///
class Random: public StaticObject {
public:
    /// Default
    static void Seed() {
        sRandomEngine.seed(std::random_device()());
    }

    /// Methods
    static float Double() {
        return static_cast<double>(sRandomsDistribution(sRandomEngine)) / static_cast<double>(std::numeric_limits<uint32>::max());
    }
    static float Float() {
        return static_cast<float>(sRandomsDistribution(sRandomEngine)) / static_cast<float>(std::numeric_limits<uint32>::max());
    }
    static float Integer() {
        return static_cast<int>(sRandomsDistribution(sRandomEngine)) / static_cast<int>(std::numeric_limits<uint32>::max());
    }
    static float UnsignedInteger() {
        return static_cast<unsigned int>(sRandomsDistribution(sRandomEngine)) / static_cast<unsigned int>(std::numeric_limits<uint32>::max());
    }

private:
    /// Properties
    static inline std::mt19937 sRandomEngine;
    static inline std::uniform_int_distribution<std::mt19937::result_type> sRandomsDistribution;
};

}
