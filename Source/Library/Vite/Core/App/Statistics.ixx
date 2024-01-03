export module Vite.App.Statistics;

import Vite.Core;

export namespace Hedron {

struct Statistics {
    // Properties
    double fps = {};
    double msPF = {};

    queue<float> fpsData;
    queue<float> msPFData;
};

}
