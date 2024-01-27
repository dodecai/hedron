module;

#include "Vite/Base/Platform/Support.h"

module Vite.Renderer;

import Vite.Device.GFXContext;
//import Vite.Platform.DXCommandBuffer;
//import Vite.Platform.DXRenderDevice;
//import Vite.Platform.DXRenderer;
//import Vite.Platform.DXSwapchain;
import Vite.Platform.GLCommandBuffer;
import Vite.Platform.GLRenderDevice;
import Vite.Platform.GLRenderer;
import Vite.Platform.GLSwapchain;
//import Vite.Platform.VKCommandBuffer;
//import Vite.Platform.VKRenderDevice;
//import Vite.Platform.VKRenderer;
//import Vite.Platform.VKSwapchain;

namespace Hedron {

///
/// Default
///
Scope<Renderer> Renderer::Create() {
    Scope<Renderer> renderer;

    switch (GFXContext::API) {
        //case GraphicsAPI::DirectX:  { renderer = CreateScope<DXRenderer>(); break; }
        case GraphicsAPI::OpenGL:   { renderer = CreateScope<GLRenderer>(); break; }
        //case GraphicsAPI::Vulkan:   { renderer = CreateScope<VKRenderer>(); break; }
        default: {
            LogFatal("Selected API isn't supported!");
            return nullptr;
        }
    }

    renderer->mRenderDevice = RenderDevice::Create();
    renderer->mCommandBuffer = CommandBuffer::Create();
    return renderer;
}


///
/// Methods
///
void Renderer::BeginScene() {
    // Create render states
    //auto renderState = RenderState::Create();
    
    // Begin recording commands and clear the screen
    mCommandBuffer->Begin();
    mCommandBuffer->Clear(0.1f, 0.1f, 0.1f, 1.0f);
}

void Renderer::EndScene() {
    // End recording commands
    mCommandBuffer->End();
}

void Renderer::RenderScene() {
    // Set up the render state
    //commandBuffer->BindRenderState(renderState);

    // Execute the command buffer
    mCommandBuffer->Execute();

    // Present the rendered image to the screen
    //swapchain->Present();
}

}
