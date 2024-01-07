export module Vite.App;

export import Vite.App.Arguments;
export import Vite.App.Layers;
export import Vite.App.Settings;
export import Vite.App.States;
export import Vite.App.Statistics;

import Vite.Base;
import Vite.Config;
import Vite.Event;
import Vite.Logger;
import Vite.Util.Chrono;
import Vite.Util.Timer;
import Vite.Util.ThreadPool;

import Vite.Aurora;
import Vite.DearImGui.Layer;
import Vite.UI.Dialog;
import Vite.UI.Window;

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
        //mConfig = Config::Create();
        //mConfig->Load("Data/Config.yml");

        // Configure Logger
        logger.SetLevel(mSettings.LogLevel);
        if (mSettings.ConsoleLogging) logger.Attach(CreateScope<ConsoleLogger>());
        if (mSettings.FileLogging) logger.Attach(CreateScope<FileLogger>(mSettings.Title + ".log"));
        if (mSettings.MemoryLogging) logger.Attach(CreateScope<MemoryLogger>());

        // Initialization
        LogCaption("{}", mSettings.Title);
        Log("{} started ...\n  on: '{}'\n  at: '{}'", mSettings.Title, appchrono.GetDate(), appchrono.GetTime());
        if (mSettings.ExternalLoop) return;
        LogCaption("Initialization");

        // Start Thread Pool
        mThreadPool = CreateScope<ThreadPool>();

        // Load and configure Systems
        LogInfo("Loading Systems");
        //mListener = EventListener::Craate();
        //mWindow = Window::Create({ mSettings.Title, mSettings.Width, mSettings.Height });
        //mWindow->SetEventListener(mListener); || mWindow->mExternalInputEventListener = [&](auto value) -> bool { return mListener->Callback(value); };
        //mListener->Emitter.on<KeyboardEventData>([&](auto &data, const auto &emitter) { OnKeyboardEvent(data, emitter); });
        //mListener->Emitter.on<MouseEventData>([&](auto &data, const auto &emitter) { OnMouseEvent(data, emitter); });
        //mListener->Emitter.on<WindowEventData>([&](auto &data, const auto &emitter) { OnWindowEvent(data, emitter); });
        //LogDebug("Created window '{}' with size '{}x{}'.", mProperties.Title, mProperties.Width, mProperties.Height);

        //Context::API = mProperties.GfxApi;
        //mContext = Context::Create(mWindow->GetNativeWindow());
        //mContext->Attach();
        //mContext->Load();
        //mContext->SetViewport({ mWindow->GetContextSize() });
        //mContext->SetVSync(mSettings.VSync);
        //mContext->Clear();

        //mDialog = Dialog::Create();

        //mRenderer = Renderer::Create();

        // Load Aurora Layer
        //pAuroraLayer = new AuroraLayer();
        //PushOverlay(pAuroraLayer);

        // Load ImGui Layer
        //pImGuiLayer = new ImGuiLayer();
        //PushOverlay(pImGuiLayer);
	}
    virtual ~Application() {
        // Destruction
        Log("{} finished ...\n  on: '{}'\n  at: '{}'\n", mSettings.Title, appchrono.GetDate(), appchrono.GetTime());
        Chrono::Destroy();
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

    // This method is triggered when a app event occurs.
    virtual void OnAppEvent() {
        for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnWindowEvent(data, emitter);
        }

        //switch (data.Action) {
        //    case WindowAction::Destroy: {
        //        Exit();
        //        break;
        //    }

        //    case WindowAction::Resize: {
        //        mContext->SetViewport(mWindow->GetContextSize().Width, mWindow->GetContextSize().Height);
        //        break;
        //    }

        //    default: {
        //        break;
        //    }
        //}
    }

    // This method is triggered when a controller input event occurs.
    virtual void OnControllerEvent(ControllerEventData &data) {
        for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnControllerEvent(data, emitter);
        }
    }
    
    // This method is triggered when a keyboard input event occurs.
    virtual void OnKeyboardEvent(KeyboardEventData &data) {
        for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnKeyboardEvent(data, emitter);
        }
    }
    
    // This method is triggered when a mouse input event occurs.
    virtual void OnMouseEvent(MouseEventData &data) {
        for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnMouseEvent(data, emitter);
        }
    }
    
    // This method is triggered when a touch input event occurs.
    virtual void OnTouchEvent(TouchEventData &data) {
        for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnTouchEvent(data, emitter);
        }
    }

    ///
    /// Accessors
    ///
    static Application &Instance() { return *pAppInstance; }
    const Arguments &GetArguments() const { return mArguments; }
    const Settings &GetSettings() const { return mSettings; }
    const States &GetStates() const { return mStates; }
    const Statistics &GetStatistics() const { return mStatistics; }

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
            DeltaTime deltaTime = timer.GetDeltaTime();
            frames++;
            delay += deltaTime;

            // Update statistics
            if (delay >= 1.0) {
                mStatistics.fps = frames;
                mStatistics.msPF = deltaTime.GetSeconds();

                title = mSettings.Title + std::format(" [fps: {:.0f} | msPF: {:.3f}", mStatistics.fps, mStatistics.msPF);
                //mWindow->SetTitle(title);

                delay = 0.0;
                frames = 0.0;
            }

            // Update application
            //mContext->Attach();
            //mRenderer->RenderFrame();
            for (auto *layer : mLayers) layer->Update(deltaTime);
            Update(deltaTime);
            //if (mWindow->GetState(WindowState::Alive)) {
            //    mListener->Update();
            //    pCoreLayer->Prepare();
            //    for (Layer *layer : mLayers) layer->GuiUpdate();
            //    pCoreLayer->Finish();
            //}
            //mContext->SwapBuffers();
            //mContext->Detach();
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
            DeltaTime deltaTime = timer.GetDeltaTime();
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
    Scope<ThreadPool> mThreadPool;
    //Reference<Config> mConfig;
    //Reference<Context> mContext;
    //Reference<Dialog> mDialog;
    //Scope<EventListener> mListener;
    //Scope<Renderer> mRenderer;
    //Scope<Window> mWindow;
    //ImGuiLayer *pImGuiLayer;
};

// Symbol for Application Entry-Point
Application* CreateApplication();

}
