module;

///
/// Switches
///

// This switch enables the development mode.
//#define APP_MODE_DEVELOP

export module Vite.App;

export import Vite.App.Arguments;
export import Vite.App.Layers;
export import Vite.App.Settings;
export import Vite.App.States;
export import Vite.App.Statistics;

import Vite.Base;
import Vite.Config;
import Vite.Device.Input;
import Vite.Device.GFXContext;
import Vite.Event;
import Vite.Logger;
import Vite.Renderer;
import Vite.System.Dialog;
import Vite.System.Window;
import Vite.Util.Chrono;
import Vite.Util.Timer;
import Vite.Util.ThreadPool;

import Vite.Aurora;
import Vite.DearImGui.Layer;

int main(int, char **);

export namespace Hedron {

///
/// @brief This is the main class which controls the workflow during runtime.
///
class Application {
    /// Friends
    friend int ::main(int, char**);

public:
    /// Default
    Application(const Settings &settings = {}): mSettings(settings) {
        if (pAppInstance) { throw std::runtime_error("Application already initialized!"); }
        // Preparation
        pAppInstance = this;
        mStates = { .Active = true, .Running = true };

        // Load Configuration
        mConfig = CreateScope<Config>();
        mConfig->Load("Data/Config.yml");

        // Configure Logger
        logger.SetLevel(mSettings.LogLevel);
        if (mSettings.ConsoleLogging) logger.Attach(CreateScope<ConsoleLogger>());
        if (mSettings.FileLogging) logger.Attach(CreateScope<FileLogger>(mSettings.Title + ".log"));
        if (mSettings.MemoryLogging) logger.Attach(CreateScope<MemoryLogger>());

        // Initialization
        LogCaption("{}", mSettings.Title);
        Log("{} started ...\n  on: '{}'\n  at: '{}'", mSettings.Title, Chrono::Date(), Chrono::Time());
        if (mSettings.ExternalLoop) return;
        LogCaption("Initialization");

        // Start Thread Pool
        mThreadPool = CreateScope<ThreadPool>();

        // Load Window and Dialog
        LogInfo("Loading Systems");
        mCoreWindow = Window::Create({ mSettings.Title /*, mSettings.Width, mSettings.Height*/ });
        //mCoreWindow->FullScreen(true);
        //mCoreWindow->Transparent(true);
        mDialog = Dialog::Create(mCoreWindow->AsPlatformHandle());
        mEventHandler = EventHandler::Create(mCoreWindow->AsPlatformHandle());
        mCoreWindow->ExternalEventHandler([&](auto value) -> bool { return mEventHandler->Callback(value); });
        
        // Load Event Handler
        mEventHandler->Register<ControllerEvent>([&](const ControllerEvent &event /*, const auto &emitter*/) { OnInputEvent(event); });
        mEventHandler->Register<MouseEvent>([&](const MouseEvent &event /*, const auto &emitter*/) { OnInputEvent(event); });
        mEventHandler->Register<KeyboardEvent>([&](const KeyboardEvent &event /*, const auto &emitter*/) { OnInputEvent(event); });
        mEventHandler->Register<TouchEvent>([&](const TouchEvent &event /*, const auto &emitter*/) { OnInputEvent(event); });
        mEventHandler->Register<WindowEvent>([&](const WindowEvent &event /*, const auto &emitter*/) { OnAppEvent(event); });
        LogDebug("Created window '{}' with size '{}'.", mSettings.Title, mSettings.Resolution);

        // Load Graphics Context
        GFXContext::API = mSettings.GraphicsAPI;
        mGraphicsContext = GFXContext::Create(mCoreWindow->AsPlatformHandle());
        mGraphicsContext->Attach();
        mGraphicsContext->Viewport(mCoreWindow->ContentSize());
        mGraphicsContext->VSync(mSettings.VSync);
        mGraphicsContext->VSync(false);
        mGraphicsContext->Clear();

        // Load Renderer
        mRenderer = Renderer::Create();

        // Load Aurora Layer
        //pAuroraLayer = new AuroraLayer();
        //PushOverlay(pAuroraLayer);

        // Load ImGui Layer
        mDearImGuiLayer = new DearImGuiLayer();
        PushOverlay(mDearImGuiLayer);
	}
    virtual ~Application() {
        // Destruction
        Log("{} finished ...\n  on: '{}'\n  at: '{}'\n", mSettings.Title, Chrono::Date(), Chrono::Time());
        Logger::Destroy();
        Input::Destroy();
		pAppInstance = nullptr;
    }

    ///
    /// Interface
    ///

    // This method executes your initialization code.
    virtual void Create() {};

    // This method executes your termination code
    virtual void Destroy() {};

    // This method executes your main logic code.
    virtual void Update([[maybe_unused]] DeltaTime deltaTime) {};

    ///
    /// Event Interface
    ///

    // This method is triggered when a window event occurs.
    virtual void OnAppEvent(const WindowEvent &event) {
        switch (event.Action) {
            case WindowAction::Destroy: {
                Exit();
                break;
            }

            case WindowAction::Focus: {
                Input::Enable();
                break;
            }

            case WindowAction::Defocus: {
                Input::Disable();
                break;
            }

            case WindowAction::Resize: {
                mGraphicsContext->Viewport(mCoreWindow->ContentSize());
                break;
            }

            default: {
                break;
            }
        }

        for (auto *layer : mLayers) {
            if (event.Handled) break;
            layer->OnAppEvent(event);
        }

    #ifdef APP_MODE_DEVELOP
        logger << "WindowEvent[";
        if (event.Action == WindowAction::Move) {
            logger << "Action: '" << event.Action << "' | ";
            logger << "Delta: '" << event.DeltaPosition.X << "|" << event.DeltaPosition.Y << "' | ";
            logger << "Position: '" << event.Position.X << "|" << event.Position.Y << "' | ";
            logger << "Previous: '" << event.LastPosition.X << "|" << event.LastPosition.Y << "'";
        } else if (event.Action == WindowAction::Resize) {
            logger << "Action: '" << event.Action << "' | ";
            logger << "Delta: '" << event.DeltaSize.Width << "x" << event.DeltaSize.Height << "' | ";
            logger << "Size: '" << event.Size.Width << "x" << event.Size.Height << "' | ";
            logger << "Previous: '" << event.LastSize.Width << "x" << event.LastSize.Height << "'";
        } else {
            logger << "Action: '" << event.Action << "'";
        }
        logger << "]" << std::endl;
    #endif
    }

    // This method is triggered when a controller input event occurs.
    virtual void OnInputEvent(const ControllerEvent &event) {
        for (auto *layer : mLayers) {
            if (event.Handled) break;
            layer->OnInputEvent(event);
        }

    #ifdef APP_MODE_DEVELOP
    #endif
    }
    
    // This method is triggered when a keyboard input event occurs.
    virtual void OnInputEvent(const KeyboardEvent &event) {
        if (event.Key == KeyCode::Escape) {
            Exit();
        }
        for (auto *layer : mLayers) {
            if (event.Handled) break;
            layer->OnInputEvent(event);
        }
        
    #ifdef APP_MODE_DEVELOP
        logger << "KeyboardEvent[";
        if (event.Action == KeyAction::Input) {
            logger << "Action: '" << event.Action << "' | ";
            logger.Flush();
            std::wcout << "Character: '" << event.Character << "'";
        } else {
            if (event.State == KeyState::Repeat) {
                logger << "Action: '" << event.Action << "' | ";
                logger << "Key: '" << event.Key << "' | ";
                logger << "State: '" << event.State << "' | ";
                logger << "Repeats: '" << event.Repeats << "'";
            } else {
                logger << "Action: '" << event.Action << "' | ";
                logger << "Key: '" << event.Key << "' | ";
                logger << "State: '" << event.State << "'";
            }
        }
        logger << "]" << std::endl;

        if (event.State == KeyState::Release) {
            if (event.Key == KeyCode::O && (event.Modifiers & KeyModifier::Control) == KeyModifier::Control) {
                mDialog->OpenFile("Hedron Open", { "All Files (*.*)", "*.*", "C++ Module Interface", "*.ixx"});
            }
            if (event.Key == KeyCode::S && (event.Modifiers & KeyModifier::Control) == KeyModifier::Control) {
                mDialog->SaveFile("Hedron Save As", { "All Files (*.*)", "*.*", "C++ Module Interface", "*.ixx" });
            }
        }
    #endif
    }
    
    // This method is triggered when a mouse input event occurs.
    virtual void OnInputEvent(const MouseEvent &event) {
        for (auto *layer : mLayers) {
            if (event.Handled) break;
            layer->OnInputEvent(event);
        }
        
    #ifdef APP_MODE_DEVELOP
        logger << "MouseEvent[";
        if (event.Action == MouseAction::Click || event.Action == MouseAction::DoubleClick || event.Action == MouseAction::Hold) {
            logger << "Action: '" << event.Action << "' | ";
            logger << "Button: '" << event.Button << "' | ";
            logger << "State: '" << event.State << "'";
        } else if (event.Action == MouseAction::Move) {
            logger << "Action: '" << event.Action << "' | ";
            logger << "Delta: '" << event.DeltaPosition.X << "|" << event.DeltaPosition.Y << "' | ";
            logger << "Position: '" << event.Position.X << "|" << event.Position.Y << "' | ";
            logger << "Previous: '" << event.LastPosition.X << "|" << event.LastPosition.Y << "'";
        } else if (event.Action == MouseAction::Wheel) {
            logger << "Action: '" << event.Action << "' | ";
            logger << "WheelX: '" << event.DeltaWheel.X << "'";
            logger << "WheelY: '" << event.DeltaWheel.Y << "'";
        } else {
            logger << "Action: '" << event.Action << "'";
        }
        logger << "]" << std::endl;
    #endif
    }
    
    // This method is triggered when a touch input event occurs.
    virtual void OnInputEvent(const TouchEvent &event) {
        for (auto *layer : mLayers) {
            if (event.Handled) break;
            layer->OnInputEvent(event);
        }

    #ifdef APP_MODE_DEVELOP
    #endif
    }

    ///
    /// Accessors
    ///
    static Application &Instance() { return *pAppInstance; }
    const Arguments &GetArguments() const { return mArguments; }
    const Settings &GetSettings() const { return mSettings; }
    const States &GetStates() const { return mStates; }
    const Statistics &GetStatistics() const { return mStatistics; }
    const Scope<GFXContext> &GetGraphicsContext() { return mGraphicsContext; }
    const Scope<Renderer> &GetRenderer() { return mRenderer; }
    const Scope<Window> &GetWindow() { return mCoreWindow; }

    ///
    /// Methods
    ///
    
    // This method stops the main-loop.
    void Exit() { mStates.Running = false; }

    // This method pushes a layer to the application.
    void PushLayer(Layer *layer) { mLayers.PushLayer(layer); }
    
    // This method pushes an overlay on top of the application.
    void PushOverlay(Layer *overlay) { mLayers.PushOverlay(overlay); }

protected:
    // Attention: This method is used reload/switch the graphics context.
    static void Reload() {
        //auto &context = Instance().mContext;
        //auto &layers = Instance().mLayers;
        //auto &reloaded = Instance().mReloaded;

        //reloaded = true;
        //Instance().mProperties.GfxApi = Context::API;

        //context->Detach();
        //context = Context::Create(GetWindow().GetNativeWindow());
        //context->Attach();
        //context->Load();

        //auto &[width, height] = GetWindow().GetContextSize();
        //context->SetViewport(width, height);

        //for (auto *layer : layers) layer->Detach();
        //for (auto *layer : layers) layer->Attach();
    }

private:
    // With this method, everything begins, but also ends.
    void Run() {
        // Preparation
        if (mSettings.ExternalLoop) {
            RunExternal();
            return;
        }

        // Creation
        Create();
        for (auto *layer : mLayers) layer->Create();

        // Runtime Properties
        double delay {};
        double frames {};
        Timer timer {};
        string title(64, ' ');

        auto title2 = mCoreWindow->Title();
        
        // Main-Loop
        LogCaption("Main-Loop");
        while (mStates.Running) {
            // Check if application is active or reload is requested
            if (mStates.Paused) continue;
            if (mStates.Reloading) {
                Reload();
                mStates.Reloading = false;
                continue;
            }

            // Calculate delta-time
            DeltaTime deltaTime = timer.DeltaTime();
            frames++;
            delay += deltaTime;

            // Update statistics
            if (delay >= 1.0) {
                mStatistics.fps = frames;
                mStatistics.msPF = deltaTime.GetSeconds();

                title = mSettings.Title + std::format(" [fps: {:.0f} | msPF: {:.3f}", mStatistics.fps, mStatistics.msPF);
                mCoreWindow->Title(title);

                delay = 0.0;
                frames = 0.0;

            }

            // Update application
            mEventHandler->Update();
            mGraphicsContext->Attach();
            //mGraphicsContext->Clear();
            auto uiActive = mDearImGuiLayer->Active();
            if (uiActive) { Input::Disable(); }
            mRenderer->Capture();
            for (auto *layer : mLayers) layer->Update(deltaTime);
            Update(deltaTime);
            mRenderer->Present();
            if (uiActive) { Input::Enable(); }
            if (mCoreWindow->State(WindowState::Alive)) {
                mDearImGuiLayer->Prepare();
                for (auto *layer : mLayers) layer->UpdateUI();
                mDearImGuiLayer->Render();
            }
            mGraphicsContext->SwapBuffers();
            mGraphicsContext->Detach();
        }

        // Termination
        LogCaption("Termination");
        for (auto *layer : mLayers) layer->Destroy();
		Destroy();
    };

    // Specialization for external engines
    void RunExternal() {
        // Runtime Properties
        double delay {};
        double frames {};
        string title(64, ' ');
        Timer timer {};

        // Creation
        Create();

        while (mStates.Running) {
            // Check if application is active or reload is requested
            if (mStates.Paused) continue;
            if (mStates.Reloading) {
                Reload();
                mStates.Reloading = false;
                continue;
            }

            // Calculate delta-time
            DeltaTime deltaTime = timer.DeltaTime();
            frames++;
            delay += deltaTime;

            // Update statistics
            if (delay >= 1.0) {
                mStatistics.fps = frames;
                mStatistics.msPF = deltaTime.GetSeconds();

                delay = 0.0;
                frames = 0.0;
            }

            // Update
            Update(deltaTime);
        }

        // Termination
        Destroy();
    }
    
    ///
    /// Mutators
    ///
    
    // This method sets the arguments of the application (only allowed through main).
    void SetArguments(const Arguments &arguments) { mArguments = arguments; }

private:
    /// Properties
    Arguments mArguments;
    Settings mSettings;
    States mStates;
    Statistics mStatistics;

    /// Systems
    static inline Application *pAppInstance = nullptr;
    LayerStack mLayers;
    Scope<Config> mConfig;
    Scope<Window> mCoreWindow;
    Scope<Dialog> mDialog;
    Scope<EventHandler> mEventHandler;
    Scope<GFXContext> mGraphicsContext;
    Scope<Renderer> mRenderer;
    Scope<ThreadPool> mThreadPool;
    DearImGuiLayer *mDearImGuiLayer;
};

// Symbol for Application Entry-Point
Application* CreateApplication();

}
