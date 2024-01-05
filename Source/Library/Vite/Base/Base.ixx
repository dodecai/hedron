export module Vite.Base;

// Platform: Prevent compilation if the target platform is not supported
import "Vite/Base/Platform/Detection.h";
import "Vite/Base/Platform/Support.h";

// Algebra: Algorithms and Types
export import Vite.Algebra.Algorithms;
export import Vite.Algebra.Matrix;
export import Vite.Algebra.Quaternion;
export import Vite.Algebra.Vector;

// Basic Types
export import Vite.Type.Component;
export import Vite.Type.Concepts;
export import Vite.Type.Entity;
export import Vite.Type.Literals;
export import Vite.Type.Object;
export import Vite.Type.Property;
export import Vite.Type.SmartPointer;
export import Vite.Type.SourceLocation;
export import Vite.Type.Standard;
export import Vite.Type.System;
export import Vite.Type.Timestamp;
export import Vite.Type.UUID;

// Devices
export import Vite.Device.Display;
export import Vite.Device.GFXContext;
export import Vite.Device.Input;
export import Vite.Device.SFXContext;

// Extensions
export import Vite.Extensions;

// Memory
//export import Vite.Memory;

// Runtime-Type-Information (RTTI)
export import Vite.Runtime.Reflection;

// System
export import Vite.System.Cli;
export import Vite.System.FileSystem;
export import Vite.System.Library;
