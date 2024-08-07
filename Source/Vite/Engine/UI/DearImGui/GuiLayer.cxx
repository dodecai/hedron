module;

#include "Vite/Base/Platform/Detection.h"

// Backend
#pragma warning(push, 0)
    #include <imgui/imgui.h>
    #include <imgui/imgui_internal.h>
#pragma warning(pop)
//#include <Ultra/UI/ImGui/Styles/Styles.h>

// Graphics Backends
#include <imgui/backends/imgui_impl_opengl3.h>
//#include <imgui/backends/imgui_impl_vulkan.h>

// System Backends
#ifdef APP_PLATFORM_WINDOWS
    #include <imgui/backends/imgui_impl_win32-patch.h>
#endif

module Vite.DearImGui.Layer;

import Vite.App;
import Vite.DearImGui.Builder;
import Vite.Platform.VKContext;

///
/// Helpers
///
namespace {

inline ImGuiKey ConvertKeyCode(const Hedron::KeyCode &code) {
    using namespace Hedron;
    switch (code) {
        case KeyCode::D0:       return ImGuiKey_0;
        case KeyCode::D1:       return ImGuiKey_1;
        case KeyCode::D2:       return ImGuiKey_2;
        case KeyCode::D3:       return ImGuiKey_3;
        case KeyCode::D4:       return ImGuiKey_4;
        case KeyCode::D5:       return ImGuiKey_5;
        case KeyCode::D6:       return ImGuiKey_6;
        case KeyCode::D7:       return ImGuiKey_7;
        case KeyCode::D8:       return ImGuiKey_8;
        case KeyCode::D9:       return ImGuiKey_9;
        case KeyCode::A:        return ImGuiKey_A;
        case KeyCode::B:        return ImGuiKey_B;
        case KeyCode::C:        return ImGuiKey_C;
        case KeyCode::D:        return ImGuiKey_D;
        case KeyCode::E:        return ImGuiKey_E;
        case KeyCode::F:        return ImGuiKey_F;
        case KeyCode::G:        return ImGuiKey_G;
        case KeyCode::H:        return ImGuiKey_H;
        case KeyCode::I:        return ImGuiKey_I;
        case KeyCode::J:        return ImGuiKey_J;
        case KeyCode::K:        return ImGuiKey_K;
        case KeyCode::L:        return ImGuiKey_L;
        case KeyCode::M:        return ImGuiKey_M;
        case KeyCode::N:        return ImGuiKey_N;
        case KeyCode::O:        return ImGuiKey_O;
        case KeyCode::P:        return ImGuiKey_P;
        case KeyCode::Q:        return ImGuiKey_Q;
        case KeyCode::R:        return ImGuiKey_R;
        case KeyCode::S:        return ImGuiKey_S;
        case KeyCode::T:        return ImGuiKey_T;
        case KeyCode::U:        return ImGuiKey_U;
        case KeyCode::V:        return ImGuiKey_V;
        case KeyCode::W:        return ImGuiKey_W;
        case KeyCode::X:        return ImGuiKey_X;
        case KeyCode::Y:        return ImGuiKey_Y;
        case KeyCode::Z:        return ImGuiKey_Z;

        case KeyCode::Left:         return ImGuiKey_LeftArrow;
        case KeyCode::Up:           return ImGuiKey_UpArrow;
        case KeyCode::Right:        return ImGuiKey_RightArrow;
        case KeyCode::Down:         return ImGuiKey_DownArrow;

        case KeyCode::NumPad0:      return ImGuiKey_Keypad0;
        case KeyCode::NumPad1:      return ImGuiKey_Keypad1;
        case KeyCode::NumPad2:      return ImGuiKey_Keypad2;
        case KeyCode::NumPad3:      return ImGuiKey_Keypad3;
        case KeyCode::NumPad4:      return ImGuiKey_Keypad4;
        case KeyCode::NumPad5:      return ImGuiKey_Keypad5;
        case KeyCode::NumPad6:      return ImGuiKey_Keypad6;
        case KeyCode::NumPad7:      return ImGuiKey_Keypad7;
        case KeyCode::NumPad8:      return ImGuiKey_Keypad8;
        case KeyCode::NumPad9:      return ImGuiKey_Keypad9;
        case KeyCode::Decimal:      return ImGuiKey_KeypadDecimal;
        case KeyCode::Divide:       return ImGuiKey_KeypadDivide;
        case KeyCode::Multiply:     return ImGuiKey_KeypadMultiply;
        case KeyCode::Subtract:     return ImGuiKey_KeypadSubtract;
        case KeyCode::Add:          return ImGuiKey_KeypadAdd;

        case KeyCode::Backspace:    return ImGuiKey_Backspace;
        case KeyCode::CapsLock:     return ImGuiKey_CapsLock;
        case KeyCode::Delete:       return ImGuiKey_Delete;
        case KeyCode::End:          return ImGuiKey_End;
        case KeyCode::Enter:        return ImGuiKey_Enter;
        case KeyCode::Escape:       return ImGuiKey_Escape;
        case KeyCode::Home:         return ImGuiKey_Home;
        case KeyCode::Insert:       return ImGuiKey_Insert;
        case KeyCode::NumLock:      return ImGuiKey_NumLock;
        case KeyCode::PageUp:       return ImGuiKey_PageUp;
        case KeyCode::PageDown:     return ImGuiKey_PageDown;
        case KeyCode::Pause:        return ImGuiKey_Pause;
        case KeyCode::Screen:       return ImGuiKey_PrintScreen;
        case KeyCode::Scroll:       return ImGuiKey_ScrollLock;
        case KeyCode::Space:        return ImGuiKey_Space;
        case KeyCode::Tab:          return ImGuiKey_Tab;

        case KeyCode::F1:           return ImGuiKey_F1;
        case KeyCode::F2:           return ImGuiKey_F2;
        case KeyCode::F3:           return ImGuiKey_F3;
        case KeyCode::F4:           return ImGuiKey_F4;
        case KeyCode::F5:           return ImGuiKey_F5;
        case KeyCode::F6:           return ImGuiKey_F6;
        case KeyCode::F7:           return ImGuiKey_F7;
        case KeyCode::F8:           return ImGuiKey_F8;
        case KeyCode::F9:           return ImGuiKey_F9;
        case KeyCode::F10:          return ImGuiKey_F10;
        case KeyCode::F11:          return ImGuiKey_F11;
        case KeyCode::F12:          return ImGuiKey_F12;
        case KeyCode::F13:          return ImGuiKey_F13;
        case KeyCode::F14:          return ImGuiKey_F14;
        case KeyCode::F15:          return ImGuiKey_F15;
        case KeyCode::F16:          return ImGuiKey_F16;
        case KeyCode::F17:          return ImGuiKey_F17;
        case KeyCode::F18:          return ImGuiKey_F18;
        case KeyCode::F19:          return ImGuiKey_F19;
        case KeyCode::F20:          return ImGuiKey_F20;
        case KeyCode::F21:          return ImGuiKey_F21;
        case KeyCode::F22:          return ImGuiKey_F22;
        case KeyCode::F23:          return ImGuiKey_F23;
        case KeyCode::F24:          return ImGuiKey_F24;

        case KeyCode::LeftControl:  return ImGuiKey_LeftCtrl;
        case KeyCode::LeftAlt:      return ImGuiKey_LeftAlt;
        case KeyCode::LeftShift:    return ImGuiKey_LeftShift;
        case KeyCode::LeftSuper:    return ImGuiKey_LeftSuper;
        case KeyCode::RightControl: return ImGuiKey_RightCtrl;
        case KeyCode::RightAlt:     return ImGuiKey_RightAlt;
        case KeyCode::RightShift:   return ImGuiKey_RightShift;
        case KeyCode::RightSuper:   return ImGuiKey_RightSuper;

        default:                    return ImGuiKey_None;
    }
}

inline ImGuiMouseButton ConvertMouseButton(const Hedron::MouseButton &button) {
    using namespace Hedron;
    switch (button) {
        case MouseButton::Left:     return ImGuiMouseButton_Left;
        case MouseButton::Right:    return ImGuiMouseButton_Right;
        case MouseButton::Middle:   return ImGuiMouseButton_Middle;
        case MouseButton::Extra1:   return 3;
        case MouseButton::Extra2:   return 4;
        default:                    return ImGuiKey_None;
    }
}

//inline int ImGui_ImplWin32_CreateVkSurface(ImGuiViewport *viewport, ImU64 instance, const void *allocator, ImU64 *surface) {
//    auto context = Application::GetContext().As<VKContext>();
//    auto result = (int)!context->CreateSurface(viewport->PlatformHandleRaw, (vk::SurfaceKHR *)surface);
//    return result;
//}

}

namespace Hedron {

/// Default
DearImGuiLayer::DearImGuiLayer(): Layer("DearImGuiLayer") {
    IMGUI_CHECKVERSION();
}

DearImGuiLayer::~DearImGuiLayer() {
}


/// Controls
void DearImGuiLayer::Attach() {
	// Properties
    auto &app = Application::Instance();
    auto &context = app.GetGraphicsContext();
    auto &window = app.GetWindow();

	// Setup Dear ImGui context
	ImGui::CreateContext();
	auto &io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigDockingWithShift = true;
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	io.IniFilename = mConfigFile.c_str();
	io.LogFilename = mLogFile.c_str();

    const auto &size = window->ContentSize();
    io.DisplaySize = { size.Width, size.Height };

	// Setup Dear ImGui style
    //ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

    // Load Fonts
    io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/consola.ttf", mFontSize, nullptr, io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/segoeui.ttf", mFontSize, nullptr, io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromFileTTF("./Assets/Fonts/Roboto/Roboto-Medium.ttf", mFontSize, nullptr, io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromFileTTF("./Assets/Fonts/Roboto/Roboto-Light.ttf", mFontSize, nullptr, io.Fonts->GetGlyphRangesDefault());
    io.Fonts->AddFontFromFileTTF("./Assets/Fonts/Roboto/Roboto-Bold.ttf", mFontSize, nullptr, io.Fonts->GetGlyphRangesDefault());

    // Setup Platform/Renderer bindings
    if (GFXContext::API == GraphicsAPI::OpenGL) {
        const char *glsl_version = "#version 450";
    #if defined APP_PLATFORM_WINDOWS
        ImGui_ImplWin32_InitForOpenGL(window->AsPlatformHandle(), context->AsPlatformHandle());
        //ImGui_ImplWin32_EnableDpiAwareness();
    #endif
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
    if (GFXContext::API == GraphicsAPI::Vulkan) {
        // Extend Dear ImGui WinAPI
        //ImGuiPlatformIO& platform_io = ImGui::GetPlatformIO();
        //platform_io.Platform_CreateVkSurface = ImGui_ImplWin32_CreateVkSurface;

        //auto context = Application::GetContext().As<VKContext>();
        //ImGui_ImplWin32_Init(window->AsPlatformHandle());
        //ImGui_ImplWin32_Init(app.GetWindow().GetNativeWindow());

        // Create Descriptor Pool
        // UI Descriptor Pool
        //VkDescriptorPool descriptorPool;
        //VkDescriptorPoolSize pool_sizes[] = {
        //    { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
        //    { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
        //    { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
        //    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
        //    { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
        //    { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        //};
        //VkDescriptorPoolCreateInfo pool_info = {};
        //pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        //pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        //pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        //pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
        //pool_info.pPoolSizes = pool_sizes;
        //VkResult err = vkCreateDescriptorPool(context->GetDevice()->Call(), &pool_info, nullptr, &descriptorPool);
        //if (err == VK_SUCCESS) { /* ToDo: Check Result */ }

        //// UI Command Buffer/Pool, Framebuffers, RenderPass
        //ImGui_ImplVulkan_InitInfo vkInfo = {};
        //vkInfo.Instance = context->GetInstance()->Call();
        //vkInfo.PhysicalDevice = context->GetPhyiscalDevice()->Call();
        //vkInfo.Device = context->GetDevice()->Call();
        //vkInfo.Queue = context->GetDevice()->GetQueue();
        //vkInfo.DescriptorPool = descriptorPool;
        //vkInfo.MinImageCount = context->GetSwapChain()->GetImageCount();
        //vkInfo.ImageCount = context->GetSwapChain()->GetImageCount();
        //ImGui_ImplVulkan_Init(&vkInfo, context->GetSwapChain()->GetRenderPass());

        // Upload Fonts
        //{
        //    ImGui_ImplVulkan_CreateFontsTexture();
        //    vkDeviceWaitIdle(context->GetDevice()->Call());
        //}
     }
}

void DearImGuiLayer::Detach() {
    if (GFXContext::API == GraphicsAPI::OpenGL) ImGui_ImplOpenGL3_Shutdown();
    //if (GFXContext::API == GraphicsAPI::Vulkan) ImGui_ImplVulkan_Shutdown();

#if defined APP_PLATFORM_WINDOWS
	ImGui_ImplWin32_Shutdown();
#endif
	ImGui::DestroyContext();
}

void DearImGuiLayer::Update(DeltaTime deltaTime) {
	auto &io = ImGui::GetIO();
	io.DeltaTime = static_cast<float>(deltaTime);
}

void DearImGuiLayer::UpdateUI() {
	if (mShowDemoWindow) ImGui::ShowDemoWindow(&mShowDemoWindow);
}

void DearImGuiLayer::Prepare() {
	// Start new 'Dear ImGui' frame
    if (GFXContext::API == GraphicsAPI::OpenGL) ImGui_ImplOpenGL3_NewFrame();
    //if (GFXContext::API == GraphicsAPI::Vulkan) ImGui_ImplVulkan_NewFrame();
#if defined APP_PLATFORM_WINDOWS
	ImGui_ImplWin32_NewFrame();
#endif
    ImGui::NewFrame();

	// Properties
	ImGuiIO& io = ImGui::GetIO();
	static bool DockSpace = true;
	static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
	static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;;
    if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) windowFlags |= ImGuiWindowFlags_NoBackground;
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

	// Viewport
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos, 0);
    ImGui::SetNextWindowSize(viewport->Size, 0);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	//// DockSpace
    ImGui::Begin("DockSpace", &DockSpace, windowFlags);
    ImGuiStyle &style = ImGui::GetStyle();
    // ToDo: Window minimum size while docked
    style.WindowMinSize.x = 256.0f;
	ImGui::PopStyleVar(3);

	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
		ImGuiID dockspaceId = ImGui::GetID("DockSpace");
		ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);
	}
}

void DearImGuiLayer::Render() {
	// ~DockSpace
	ImGui::End();

	// Rendering
    ImGui::Render();
    if (GFXContext::API == GraphicsAPI::OpenGL) {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
    if (GFXContext::API == GraphicsAPI::Vulkan) {
        //auto context = Application::GetContext().As<VKContext>();
        //auto buffer = context->GetSwapChain()->GetCurrentDrawCommandBuffer();
        //ImGui_ImplVulkan_RenderDrawData(ImGui::GetDrawData(), (VkCommandBuffer)buffer);
    }

	// Update and Render additional Platform Windows
    auto &io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    #if defined APP_PLATFORM_WINDOWS
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
    #endif
	}
}


/// Events
void DearImGuiLayer::OnAppEvent(const WindowEvent &event) {
    if (event.Action == WindowAction::Resize) {
        auto &io = ImGui::GetIO();
        io.DisplaySize = { event.Size.Width, event.Size.Height };
    }
}

void DearImGuiLayer::OnInputEvent(const ControllerEvent &event) {
}

void DearImGuiLayer::OnInputEvent(const KeyboardEvent &event) {
	if (ImGui::GetCurrentContext() == nullptr) return;
    auto &io = ImGui::GetIO();
    event.Handled = io.WantCaptureKeyboard;
    
    io.KeyAlt = (event.Modifiers & KeyModifier::Alt) == KeyModifier::Alt;
    io.KeyCtrl = (event.Modifiers & KeyModifier::Control) == KeyModifier::Control;
    io.KeyShift = (event.Modifiers & KeyModifier::Shift) == KeyModifier::Shift;
    io.KeySuper = (event.Modifiers & KeyModifier::Super) == KeyModifier::Super;

	switch (event.Action) {
		case KeyAction::Input: {
			io.AddInputCharacterUTF16(event.Character);
			break;
		}
        case KeyAction::Raw: {
            if (event.Key == KeyCode::F1 && event.State == KeyState::Press) mShowDemoWindow = !mShowDemoWindow;
            io.AddKeyEvent(ConvertKeyCode(event.Key), (event.State == KeyState::Release ? false : true));
		}
		default: {
			break;
		}
	}
}

void DearImGuiLayer::OnInputEvent(const MouseEvent &event) {
	if (ImGui::GetCurrentContext() == nullptr) return;
    auto &io = ImGui::GetIO();
    event.Handled = io.WantCaptureMouse;

    io.KeyAlt = (event.Modifiers & KeyModifier::Alt) == KeyModifier::Alt;
    io.KeyCtrl = (event.Modifiers & KeyModifier::Control) == KeyModifier::Control;
    io.KeyShift = (event.Modifiers & KeyModifier::Shift) == KeyModifier::Shift;
    io.KeySuper = (event.Modifiers & KeyModifier::Super) == KeyModifier::Super;

	switch (event.Action) {
		case MouseAction::Move:	{
            io.AddMousePosEvent(event.Position.X, event.Position.Y);
            break;
        }

        case MouseAction::Wheel: {
            io.AddMouseWheelEvent(event.DeltaWheel.X, event.DeltaWheel.Y);
            break;
        }

        default: {
            io.AddMouseButtonEvent(ConvertMouseButton(event.Button), (event.State == MouseButtonState::Release ? false : true));
		}
	}
}

void DearImGuiLayer::OnInputEvent(const TouchEvent &event) {
}


/// Methods
bool DearImGuiLayer::Active() {
    return
        ImGui::IsAnyItemFocused() ||
        ImGui::IsAnyItemHovered() ||
        ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow) ||
        ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
}

}
