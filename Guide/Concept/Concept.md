# Concept
This is the main concept of the project, which delivers a good overview about the inner workings.

### Architecture
<img src="https://github.com/dodecai/hedron/blob/main/Guide/Concept/Architecture.png" alt="Architecture"/>

### Dependency Diagram
```mermaid
classDiagram
    App <|-- Application

    Application --> Config
    Application --> Context
    Application --> Emmiter
    Application --> Renderer
    Application --> Window

    Context  --> Renderer
```

### Structure
```md
3rd-Party/
├─ EnTT/
└─ ...

Vite/ [Library]
├─ Base/
|  ├─ Algorithms/
│  │  ├─ Algorithms
│  ├─ Devices/
│  │  ├─ Input/
│  │  │  ├─ Controller
│  │  │  ├─ Input
│  │  │  ├─ Keyboard
│  │  │  ├─ Mouse
│  │  │  └─ Touch
│  │  ├─ Devices
│  │  ├─ Display
│  │  ├─ GFXContext
│  │  └─ SFXContext
│  ├─ Extensions/
│  │  └─ Extensions
│  ├─ Mathematics/
│  │  ├─ Mathematics
│  │  ├─ Matrix
│  │  ├─ Quaternion
│  │  └─ Vector
│  ├─ Memory/
│  │  └─ Memory
│  ├─ Platform/
│  │  ├─ Detection
│  │  └─ Support
│  ├─ Runtime/
│  │  ├─ Reflection
│  │  └─ Runtime
│  ├─ System/
│  │  ├─ Cli
│  │  ├─ FileSystem
│  │  ├─ Module
│  │  └─ System
│  ├─ Types/
│  │  ├─ Component
│  │  ├─ Concepts
│  │  ├─ Entity
│  │  ├─ Literals
│  │  ├─ Object
│  │  ├─ Property
│  │  ├─ SmartPointer
│  │  ├─ Standard
│  │  ├─ SourceLocation
│  │  ├─ System
│  │  ├─ Timestamp
│  │  ├─ Types
│  │  └─ UUID
│  └─ Wrappers/
│     └─ 3rd-Party
├─ Core/
│  ├─ App/
│  │  ├─ Application
│  │  ├─ Arguments
│  │  ├─ Layers (or Composition?)
│  │  ├─ Settings
│  │  ├─ States
│  │  └─ Statistics
│  ├─ Config/
│  │  └─ Config
│  ├─ Debug/
│  │  └─ Profiler
│  ├─ Events/
│  │  ├─ Delegate
│  │  ├─ Dispatcher
│  │  ├─ Emitter
│  │  ├─ Event
│  │  └─ Signal
│  ├─ Logger/
│  │  └─ Logger
│  ├─ Network/
│  │  └─ Network
│  ├─ Serializer/
│  │  └─ Serializer
│  └─ Utils/
│     ├─ Chrono
│     ├─ Random
│     ├─ String
│     ├─ ThreadPool
│     └─ Timer
├─ Platform/
│  ├─ DirectX/
│  │  ├─ DXContext
│  │  ├─ DXRenderer
│  │  └─ ...
│  ├─ OpenGL/
│  │  ├─ GLContext
│  │  ├─ GLRenderer
│  │  └─ ...
│  ├─ Vulkan/
│  │  ├─ VKContext
│  │  ├─ VKRenderer
│  │  └─ ...
│  └─ WinAPI/
│     ├─ WinDialog
│     ├─ WinDisplay
│     ├─ WinEvent
│     ├─ WinInput
│     └─ WinWindow
├─ Systems/
│  ├─ Animation/
│  │  └─ Animation
│  ├─ Asset/
│  │  ├─ Asset
│  │  ├─ AssetManager
│  │  ├─ Font
│  │  ├─ Material
│  │  ├─ Mesh
│  │  └─ Sprite
│  └─ Effects/
│  │  ├─ Particles/
│  │  └─ PostProcessing/
│  ├─ Media/
│  │  ├─ Audio
│  │  ├─ Media
│  │  └─ Video
│  ├─ Networking/
│  │  └─ Networking
│  ├─ Physics/
│  │  └─ Physics
│  ├─ Renderer/
│  │  ├─ Camera/
│  │  │  ├─ Camera
│  │  │  └─ DesignerCamera
│  │  ├─ Specialized/
│  │  │  ├─ FontRenderer
│  │  │  ├─ MeshRenderer
│  │  │  ├─ SceneRenderer
│  │  │  ├─ SpriteRenderer
│  │  │  └─ UIRenderer
│  │  ├─ Buffer
│  │  ├─ CommandBuffer
│  │  ├─ FontRenderer
│  │  ├─ FrameBuffer
│  │  ├─ MeshRenderer
│  │  ├─ PipelineState
│  │  ├─ RenderDevice
│  │  ├─ Renderer
│  │  ├─ SceneRenderer
│  │  ├─ Shader
│  │  ├─ ShaderCompiler
│  │  ├─ SpriteRenderer
│  │  ├─ SwapChain
│  │  ├─ Texture
│  │  ├─ UIRenderer
│  │  └─ Viewport
│  ├─ Scene/
│  │  ├─ Scene
│  │  └─ SceneCamera
│  ├─ Scripting/
│  │  └─ Scripting
│  └─ UI/
|     ├─ Components/
│     │  ├─ Containers
│     │  └─ Controls
│     ├─ Aurora
│     ├─ Dialog
│     ├─ ImGuiBuilder
│     ├─ ImGuiLayer
│     └─ Window
├─ Tools/
│  └─ Build
└─ Vite

Vivid/ [Editor]
├─ Components/
├─ Panels/
└─ Views/
```
