export module Vite.Platform.VKContext;

import <Vite/Base/Platform/Detection.h>;

#if defined(APP_PLATFORM_WINDOWS)
    //import <Windows.h>;
#endif

import Vite.Device.GFXContext;

//import Vite.Platform.Vulkan;
//import Vite.Platform.VKAllocator;
//import Vite.Platform.VKInstance;
//import Vite.Platform.VKDevice;
//import Vite.Platform.VKSwapChainLegacy;

export namespace Hedron {

//struct VkContextData {};
//
//class VKContext: public Context {
//public:
//    VKContext(void *window);
//    virtual ~VKContext();
//
//    bool CreateSurface(const void *window, vk::SurfaceKHR *surface);
//
//    virtual void Load() override;		// previous LoadGL
//
//    virtual void Attach() override;
//    virtual void Detach() override;
//
//    // Accessors
//    Reference<VKDevice> GetDevice() { return mDevice; }
//    virtual void *GetNativeContext() override;
//    virtual bool const IsCurrentContext() override;
//
//    // Mutators
//    virtual void Clear() override {}
//    virtual void SetViewport(uint32_t width, uint32_t height, int32_t x = 0, int32_t y = 0) override;
//    virtual void SwapBuffers() override;
//
//    // Settings
//    virtual void SetVSync(bool activate) override;
//
//    // Native (needs a rework)
//    const Reference<VKInstance> &GetInstance() const { return mInstance; }
//    const Reference<VKDevice> &GetDevice() const { return mDevice; }
//    const Reference<VKPhysicalDevice> &GetPhyiscalDevice() const { return mPhysicalDevice; }
//    const vk::PipelineCache &GetPipelineCache() const { return mPipelineCache; }
//    const Reference<VKSwapChainLegacy> &GetSwapChain() const { return mSwapChain; }
//    const vk::SurfaceKHR &GetSurface() const { return mSurface; }
//    const vk::RenderPass &GetRenderPass() const { return mSwapChain->GetRenderPass(); }
//
//private:
//    HWND mWindowHandle;
//
//    Reference<VKInstance> mInstance;
//    Reference<VKPhysicalDevice> mPhysicalDevice;
//    Reference<VKDevice> mDevice;
//    Reference<VKSwapChainLegacy> mSwapChain;
//
//    vk::PipelineCache mPipelineCache;
//    vk::SurfaceKHR mSurface;
//};

}
