```md
Vite/ [Library]
├─ Base/
│  ├─ Algebra/
│  │  ├─ Algorithms
│  │  ├─ Matrix
│  │  ├─ Quaternion
│  │  └─ Vector
│  ├─ Devices/
│  │  ├─ Display
│  │  ├─ GFXContext
│  │  ├─ Input
│  │  └─ SFXContext
│  ├─ ECS/
│  │  ├─ Component
│  │  ├─ Entity
│  │  └─ System
│  ├─ Helpers/
│  │  └─ Helpers
│  ├─ Memory/
│  │  └─ Memory
│  ├─ Platform/
│  │  ├─ Detection
│  │  └─ Support
│  ├─ RTTI/
│  │  └─ RTTI
│  ├─ Serializer/
│  │  └─ Serializer
│  ├─ System/
│  │  ├─ Cli
│  │  ├─ FileSystem
│  │  └─ Module
│  └─ Types/
│     ├─ Concepts
│     ├─ Future
│     ├─ Literals
│     ├─ Object
│     ├─ Property
│     ├─ SmartPointer
│     ├─ Standard
│     ├─ SourceLocation
│     ├─ Timestamp
│     └─ UUID
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
│  └─ Utils/
│     ├─ Chrono
│     ├─ Random
│     ├─ String
│     ├─ ThreadPool
│     └─ Timer
├─ Platform/
│  ├─ DirectX/
│  │  ├─ DXContext
│  │  ├─ DXRenderDevice
│  │  └─ ...
│  ├─ OpenGL/
│  │  ├─ GLContext
│  │  ├─ GLRenderDevice
│  │  └─ ...
│  ├─ Vulkan/
│  │  ├─ VKContext
│  │  ├─ VKRenderDevice
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
│  ├─ Assets/
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
│  ├─ Physics/
│  │  └─ Physics
│  ├─ Renderer/
│  │  ├─ Camera/
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
│     ├─ UIRenderer
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
└─ Vite

Vivid/ [Editor]
├─ Components/
├─ Panels/
└─ Views/
```
