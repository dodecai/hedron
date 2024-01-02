export module Vite.Core;

// Prevents compilation if the target platform is not supported
import "Platform.h";

// Default
export import Vite.Core.Helpers;
export import Vite.Core.Standard;

// Custom
export import Vite.Core.Concepts;
export import Vite.Core.Literals;
export import Vite.Core.Property;
export import Vite.Core.SmartPointer;
export import Vite.Core.SourceLocation;
export import Vite.Core.Timestamp;
export import Vite.Core.UUID;
