export module Vite.App.States;

import Vite.Base;

export namespace Hedron {

///
/// @brief Holds the states of the application.
///
struct States {
    bool Active {};
    bool Paused {};
    bool Reloading {};
    bool Running {};
};

}
