import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;

// Switches
//#define CORE_TESTS
//#define ENGINE_TESTS
//#define RESEARCH_TESTS

namespace Hedron {

// Application
class Test: public Application {
public:
    // Default
    Test() = default;
    ~Test() = default;

    // Methods
    void Create() override {
        LogInfo("Hello World!");
    }

	void Destroy() override {
    }

	void Update() override {
	}
};

// Application Entry-Point
Application* CreateApplication() {
	return new Test();
}

}
