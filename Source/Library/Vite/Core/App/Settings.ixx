export module Vite.App.Settings;

import Vite.Base;
import Vite.Logger;

export namespace Hedron {

struct Settings {
    // Properties
    string Title = "Hedron";
    string Resolution = "1024x768";
    //GfxApi GfxApi = GfxApi::OpenGL;
    LogLevel LogLevel = LogLevel::Trace;

    // Options
    bool EnableConsoleLogging = true;
    bool EnableFileLogging = false;
    bool EnableMemoryLogging = false;
    bool ExternalLoop = false;
    bool VSync = true;
};

}
