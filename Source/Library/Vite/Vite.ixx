export module Vite;

// Configuration
import "Vite/Vite.inl";

// Base Extensions
export import Vite.Base;

// Prime Extensions
export import Vite.Config;
export import Vite.Logger;

// Core Extensions
#ifdef LIB_EXTENSION_CORE
    // Debug
    //export import Vite.Debug.Profiler;
    
    // Events
    //export import Vite.Event;
    
    // Network
    //export import Vite.Network;
        
    // Serializer / Deserializer
    //export import Vite.Serializer;
    
    // Utils
    //export import Vite.Util.Chrono;
    //export import Vite.Util.Random;
    //export import Vite.Util.String;
    //export import Vite.Util.ThreadPool;
    //export import Vite.Util.Timer;
#endif

// Engine Extensions
#ifdef LIB_EXTENSION_SYSTEMS
    //export import Vite.Animation;
    //export import Vite.Asset
    //export import Vite.Media;
    //export import Vite.Networking;
    //export import Vite.Physics;
    //export import Vite.Renderer;
    //export import Vite.Scene;
    //export import Vite.Scripting;
    //export import Vite.UI;
#endif

// System Extensions
#ifdef LIB_EXTENSION_TOOLS
    //export import Vite.Build;
#endif

export namespace Hedron::Debug {

void DisplayLibraryVersion() {
    logger << "Library Information\n"
        << " - Caption:     " << LibCaption     << "\n"
        << " - Description: " << LibDescription << "\n"
        << " - Release:     " << LibRelease     << "\n"
        << " - Version:     " << LibVersion     << "\n";

    logger << "Library Features\n" << std::boolalpha
        << " - Core:    " << Features::LibCoreExtensions    << "\n"
        << " - Systems: " << Features::LibSystemsExtensions << "\n"
        << " - Tools:   " << Features::LibToolsExtensions   << "\n"
        << std::noboolalpha;

    logger << "\n";
}

}
