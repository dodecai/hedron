﻿export module Vite.Core.Random;

import Vite.Core.Standard;

export namespace Hedron {

///
/// @brief Contains utility functions for generating random numbers and related functionality.
/// They can be used to support various aspects of your framework.
/// @note The functions and utilities here are useful for creating random data within the application.
///
class Random {
    static void Load() {
        sRandomEngine.seed(std::random_device()());
    }


    static float Float() {
        return (float)sRandomsDistribution(sRandomEngine) / (float)std::numeric_limits<uint32>::max();
    }

private:
    static inline std::mt19937 sRandomEngine;
    static inline std::uniform_int_distribution<std::mt19937::result_type> sRandomsDistribution;
};

}
