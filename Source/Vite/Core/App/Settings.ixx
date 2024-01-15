export module Vite.App.Settings;

import Vite.Base;
import Vite.Device.GFXContext;
import Vite.Logger.LogLevel;

export namespace Hedron {

///
/// @brief Holds all settings for the application.
/// @example Complex
/// Settings settings {
///     .Title = "My Game",
///     .Resolution = "1920x1080",
///     .GraphicsAPI = GraphicsAPI::OpenGL,
/// }
/// 
/// @example Simple
/// Settings settings { "Game", "1920x1080" };
///
struct Settings {
    /// Properties
    string Title = "Hedron";
    string Resolution = "1024x768";
    GraphicsAPI GraphicsAPI = GraphicsAPI::OpenGL;
    LogLevel LogLevel = LogLevel::Trace;

    /// Logging
    bool ConsoleLogging = true;
    bool FileLogging = false;
    bool MemoryLogging = false;

    /// Options
    bool ExternalLoop = false;
    uint32 TargetFPS = 60;
    bool VSync = true;
};

}
