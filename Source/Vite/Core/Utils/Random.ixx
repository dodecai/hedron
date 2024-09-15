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
    static double Double() {
        // ToDo: Bug introduced on 17.12.0 Preview 1, wait until Preview 3 where it is partially fixed
        //return sDoubleDistribution(sRandomEngine);
        return {};
    }
    static float Float() {
        // ToDo: Bug introduced on 17.12.0 Preview 1, wait until Preview 3 where it is partially fixed
        //return sFloatDistribution(sRandomEngine);
        return {};
    }
    static int Integer() {
        return sIntDistribution(sRandomEngine);
    }
    static unsigned int UnsignedInteger() {
        return sUIntDistribution(sRandomEngine);
    }

private:
    /// Properties
    static inline std::mt19937_64 sRandomEngine;
    static inline std::uniform_real_distribution<double> sDoubleDistribution { std::numeric_limits<double>::min(), std::numeric_limits<double>::max() };
    static inline std::uniform_real_distribution<float> sFloatDistribution { std::numeric_limits<float>::min(), std::numeric_limits<float>::max() };
    static inline std::uniform_int_distribution<int> sIntDistribution { std::numeric_limits<int>::min(), std::numeric_limits<int>::max() };
    static inline std::uniform_int_distribution<unsigned int> sUIntDistribution { std::numeric_limits<unsigned int>::min(), std::numeric_limits<unsigned int>::max() };
};

}
