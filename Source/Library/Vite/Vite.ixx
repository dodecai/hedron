export module Vite;

// Configuration
import "Vite/Vite.inl";

// Properties
export import Vite.Core;

// Prime Extensions
export import Vite.Config;
export import Vite.Logger;

// Core Extensions
#ifdef LIB_EXTENSION_CORE
    // Application
    //export import Vite.Core.Layers;

    // Utilities
    //export import Vite.Core.Chrono;
    //export import Vite.Core.Delegate;
    //export import Vite.Core.Dispatcher;
    //export import Vite.Core.Emitter;
    //export import Vite.Core.Future;
    //export import Vite.Core.Random;
    //export import Vite.Core.Signal;
    //export import Vite.Core.String;
    //export import Vite.Core.ThreadPool;
    //export import Vite.Core.Timer;
#endif

// Debug Extensions
#ifdef LIB_EXTENSION_DEBUG
    //export import Ultra.Debug.Memory;
    //export import Ultra.Debug.Profiler;
#endif

// Engine Extensions
#ifdef LIB_EXTENSION_ENGINE
#endif

// System Extensions
#ifdef LIB_EXTENSION_SYSTEM
#endif

// UI Extensions
#ifdef LIB_EXTENSION_UI
#endif
export namespace Hedron {

void ShowLibraryInfo() {
    logger << "Library Information\n"
        << " - Caption:     " << LibCaption     << "\n"
        << " - Description: " << LibDescription << "\n"
        << " - Release:     " << LibRelease     << "\n"
        << " - Version:     " << LibVersion     << "\n";

    logger << "Library Features\n" << std::boolalpha
        << " - Core:    " << Features::LibCoreExtensions    << "\n"
        << " - Debug:   " << Features::LibDebugExtensions   << "\n"
        << " - Engine:  " << Features::LibEngineExtensions  << "\n"
        << " - System:  " << Features::LibSystemExtensions  << "\n"
        << " - UI:      " << Features::LibUiExtensions      << "\n"
        << std::noboolalpha;

    logger << "\n";
}

}
