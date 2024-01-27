module Vite.Renderer.PipelineState;

import Vite.Device.GFXContext;
//import Vite.Platform.DXPipelineState;
import Vite.Platform.GLPipelineState;
//import Vite.Platform.VKPipelineState;

namespace Hedron {

///
/// Default
///
Scope<PipelineState> PipelineState::Create(const PipelineProperties &properties) {
    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { return CreateScope<DXPipelineState>(properties); }
        case GraphicsAPI::OpenGL:   { return CreateScope<GLPipelineState>(properties); }
        //case GraphicsAPI::Vulkan:   { return CreateScope<VKPipelineState>(properties); }

        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }
}

}
