export module Vite.Core.Settings;

import Vite.Core;
import Vite.Logger;

export namespace Hedron {

struct Settings {
    // Properties
    string Title = "Hedron";
    string Resolution = "1024x768";

    LogLevel LogLevel = LogLevel::Trace;
    bool VSync = true;
};

}
