export module Vite.App.Application;

import Vite.Core;
import Vite.Util.Chrono;
import Vite.Util.Timer;

import Vite.Aurora;
import Vite.Device.GFXContext;
import Vite.Event;
import Vite.UI.Dialog;
import Vite.UI.Window;

export import Vite.App.Arguments;
export import Vite.App.Layers;
export import Vite.App.Settings;
export import Vite.App.States;
export import Vite.App.Statistics;
import Vite.Util.ThreadPool;

export import Vite.ImGui.Layer;

int main(int, char **);

export namespace Hedron {

///
/// @brief This is the main class which controls the workflow during runtime.
///
class Application {
    // Friends
    friend int ::main(int, char**);

public:
    // Constructors and Destructor
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
        if (mSettings.EnableConsoleLogging) logger.Attach(CreateScope<ConsoleLogger>());
        if (mSettings.EnableFileLogging) logger.Attach(CreateScope<FileLogger>(mSettings.Title + ".log"));
        if (mSettings.EnableMemoryLogging) logger.Attach(CreateScope<MemoryLogger>());

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
		pAppInstance = nullptr;
    }

    // Accessors
    static Application &Instance() { return *pAppInstance; }
    const Arguments &GetArguments() const { return mArguments; }
    const Settings &GetSettings() const { return mSettings; }
    const States &GetStates() const { return mStates; }
    const Statistics &GetStatistics() const { return mStatistics; }

    ///
    /// Interface
    ///
    
    // This method executes your initialization code.
    virtual void Create() {};
    
    // This method executes your termination code
    virtual void Destroy() {};
    
    // This method executes your main logic code.
    virtual void Update([[maybe_unused]] DeltaTime deltaTime) {};

    /// - Events

    virtual void OnControllerEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnControllerEvent(data, emitter);
        //}
    }
    
    virtual void OnDeviceEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnDeviceEvent(data, emitter);
        //}
    }
    
    virtual void OnKeyboardEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnKeyboardEvent(data, emitter);
        //}
    }
    
    virtual void OnMouseEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnMouseEvent(data, emitter);
        //}
    }
    
    virtual void OnPowerEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnPowerEvent(data, emitter);
        //}
    }
    
    virtual void OnTouchEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnTouchEvent(data, emitter);
        //}
    }
    
    virtual void OnWindowEvent() {
        //for (auto layer : mLayers) {
        //    if (data.Handled) break;
        //    layer->OnWindowEvent(data, emitter);
        //}

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
        //for (Layer *layer : mLayers) layer->Create();

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
            //for (Layer *layer : mLayers) layer->Update(deltaTime);
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
        //for (Layer *layer : mLayers) layer->Destroy();
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

    // Mutators
    void SetArguments(const Arguments &arguments) { mArguments = arguments; }

private:
    // Instance
    static inline Application *pAppInstance = nullptr;

    // Properties
    Arguments mArguments;
    Settings mSettings;
    States mStates;
    Statistics mStatistics;

    // Systems
    Scope<ThreadPool> mThreadPool;
    LayerStack mLayers;
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
