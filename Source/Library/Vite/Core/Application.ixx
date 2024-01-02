export module Vite.Core.Application;

import Vite.Core;
import Vite.Core.Chrono;
import Vite.Logger;

export import Vite.Core.Arguments;
export import Vite.Core.Layers;
export import Vite.Core.Settings;
export import Vite.Core.States;
export import Vite.Core.Statistics;

int main(int, char**);

export namespace Hedron {

class Application {
	// Friends
	friend int ::main(int, char**);

public:
	// Default
    Application(const Settings &settings = {}): mSettings(settings) {
        if (pInstance) { throw std::runtime_error("Application already initialized!"); }
        pInstance = this;

        logger.SetLevel(mSettings.LogLevel);
        logger.Attach(CreateScope<ConsoleLogger>());
        logger.Attach(CreateScope<FileLogger>("Test.log"));
        logger.Attach(CreateScope<MemoryLogger>());

        // Initialization
        //Log("{} started ...\n  on: '{}'\n  at: '{}'", mSettings.Title, appchrono.GetDate(), appchrono.GetTime());
        //LogCaption("Initialization");
	}
	virtual ~Application() {
		pInstance = nullptr;
		//Log("{} finished ...\n  on: '{}'\n  at: '{}'\n", mSettings.Title, appchrono.GetDate(), appchrono.GetTime());
	}

	// Accessors
	static Application &Instance() { return *pInstance; }
    const Arguments &GetArguments() const { return mArguments; }
    const Settings &GetSettings() const { return mSettings; }
    const States &GetStates() const { return mStates; }
    const Statistics &GetStatistics() const { return mStatistics; }

	// Interface
	virtual void Create() {};
	virtual void Destroy() {};
	virtual void Update() {};

protected:
    // Attention: This method is used reload/switch the graphics context.
    static void Reload() {}

private:
	// Methods
	void Run() {
		Create();
        mStates = { .Active = true, .Running = true };
        while (mStates.Running) {
            Update();
        }
		Destroy();
	};

    // Mutators
    void SetArguments(const Arguments &arguments) { mArguments = arguments; }

private:
    // Properties
    Arguments mArguments;
    Settings mSettings;
    States mStates;
    Statistics mStatistics;

    // Resources
	static inline Application* pInstance = nullptr;
};

// Symbol for Application Entry-Point
Application* CreateApplication();

}
