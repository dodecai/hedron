export module Vite.Core;

// Prevents compilation if the target platform is not supported
import "Platform.h";

// Debug
#ifdef TODO_ENABLE_MEMORY_DEBUGGING
    export import Vite.Core.Memory;
#endif

// Default
export import Vite.Core.Config;
export import Vite.Core.Helpers;
export import Vite.Core.Logger;

// Types
export import Vite.Core.Concepts;
export import Vite.Core.Literals;
export import Vite.Core.Property;
export import Vite.Core.SmartPointer;
export import Vite.Core.SourceLocation;
export import Vite.Core.Timestamp;
export import Vite.Core.Standard;
export import Vite.Core.UUID;

// Utilities
//export import Vite.Core.Chrono;
export import Vite.Core.Delegate;
export import Vite.Core.Dispatcher;
export import Vite.Core.Emitter;
export import Vite.Core.Random;
export import Vite.Core.Signal;
export import Vite.Core.String;
export import Vite.Core.ThreadPool;
export import Vite.Core.Timer;
