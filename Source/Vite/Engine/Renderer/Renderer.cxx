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
            AppAssert(nullptr, "The selected graphics API isn't implemented!");
            return nullptr;
        }
    }

    renderer->mRenderDevice = RenderDevice::Create();
    renderer->mCommandBuffer = CommandBuffer::Create();
    //auto swapchain = Swapchain::Create(nullptr, 1280, 1024);
    return renderer;
}


///
/// Commands
///
void Renderer::Capture() {
    // Preparation
    mCapturing = true;
    mPresenting = false;

    // Setup the render device and begin recording commands
    mRenderDevice->Capture();
    mCommandBuffer->Capture();
    mCommandBuffer->Clear({ 0.1f, 0.1f, 0.1f, 1.0f });
}

void Renderer::DrawIndexed() {
}

void Renderer::Present() {
    // Preparation
    mCapturing = false;
    mPresenting = true;

    // End recording commands and execute the command buffer
    mCommandBuffer->Execute();

    // Present the rendered image to the screen
    mRenderDevice->Present();
    //mSwapchain->Present();
}

}
