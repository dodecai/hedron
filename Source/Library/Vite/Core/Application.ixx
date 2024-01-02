export module Vite.Core.Application;

import Vite.Core;
export import Vite.Core.Arguments;
export import Vite.Core.Layers;
export import Vite.Core.Settings;
export import Vite.Core.States;
export import Vite.Core.Statistics;

int main(int, char**);

export namespace Vite {

class Application {
	// Friends
	friend int ::main(int, char**);

public:
	// Default
    Application(const Settings &settings = {}): mSettings(settings) {
        if (pInstance) { throw std::runtime_error("Application already initialized!"); }
		pInstance = this;
	}
	virtual ~Application() {
		pInstance = nullptr;
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
