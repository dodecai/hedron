module Vite.Renderer;

//import <glad/gl.h>;

//import Vite.Device.GFXContext;
//import Vite.Platform.DXRenderer;
//import Vite.Platform.GLRenderer;
//import Vite.Platform.VKRenderer;
//import Vite.Platform.DXRenderDevice;
//import Vite.Platform.GLRenderDevice;
//import Vite.Platform.VKRenderDevice;

namespace Hedron {

//Scope<Renderer> Renderer::Create() {
//    Scope<Renderer> renderer;
//    Scope<RenderDevice> device;
//
//    auto api = Context::GetAPI();
//    switch (api) {
//        case GraphicsAPI::DirectX: {
//            renderer = CreateScope<DXRenderer>();
//            device = CreateScope<DXRenderDevice>();
//            break;
//        }
//        case GraphicsAPI::OpenGL: {
//            renderer = CreateScope<GLRenderer>();
//            device = CreateScope<GLRenderDevice>();
//            break;
//        }
//        case GraphicsAPI::Vulkan: {
//            renderer = CreateScope<VKRenderer>();
//            device = CreateScope<VKRenderDevice>();
//            break;
//        }
//        default: {
//        #if APP_MODE_DEBUG
//            throw std::runtime_error("Renderer: RenderAPI not supported!");
//        #else
//            LogFatal("RenderAPI not supported!");
//        #endif
//        }
//    }
//    renderer->mRenderDevice = std::move(device);
//    renderer->Load();
//    return renderer;
//}
//
//void Renderer::Load() {
//    mRenderDevice->Load();
//    mCommandBuffer = CommandBuffer::Create();
//    mCommandBuffer->SetViewport(0, 0, 1280, 1024);
//    Renderer2D::Load();
//}
//
//void Renderer::RenderFrame() {
//    // Create render states
//    //auto renderState = RenderState::Create();
//    // Begin recording commands
//    //commandBuffer->Begin();
//    mCommandBuffer->Clear(0.1f, 0.1f, 0.1f, 1.0f);;     // Clear the framebuffer
//    //commandBuffer->BindRenderState(renderState);      // Set up the render state
//    Renderer2D::ResetStatistics();
//
//    //Renderer::EndScene();
//    //commandBuffer->End();                             // End recording commands
//    //commandBuffer->Execute();                         // Execute the command buffer
//    //swapchain->Present();                             // Present the rendered image to the screen
//}
//
//void Renderer::Dispose() {
//    Renderer2D::Dispose();
//    mRenderDevice->Dispose();
//}

}
