export module Vite.Base;

// Platform: Prevent compilation if the target platform is not supported
import "Vite/Base/Platform/Detection.h";
import "Vite/Base/Platform/Support.h";

// Algebra: Algorithms
export import Vite.Algorithm;

// Devices
export import Vite.Device;

// Extensions
export import Vite.Extension;

// Mathematics
export import Vite.Math;

// Memory
//export import Vite.Memory;

// Runtime-Type-Information (RTTI)
export import Vite.Runtime;

// System
export import Vite.System;

// [Basic] Types
export import Vite.Type;
