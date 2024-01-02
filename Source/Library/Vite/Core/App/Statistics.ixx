export module Vite.Core.Statistics;

import Vite.Core;

export namespace Vite {

struct Statistics {
    // Properties
    double fps = {};
    double msPF = {};

    queue<float> fpsData;
    queue<float> msPFData;
};

}
