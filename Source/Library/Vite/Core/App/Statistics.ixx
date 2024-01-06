export module Vite.App.Statistics;

import Vite.Base;

export namespace Hedron {

///
/// @brief Holds statistics about the application.
///
struct Statistics {
    double fps = {};
    double msPF = {};

    queue<float> fpsHistory;
    queue<float> msPFHistory;
};

}
