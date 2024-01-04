import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;

//import Vite.Test.Core;
//import Vite.Test.Engine;
//import Vite.Test.Research;

// Switches
//#define CORE_TESTS
//#define RESEARCH_TESTS
//#define SYSTEMS_TESTS

namespace Hedron {

// Application
class Nexus: public Application {
public:
    // Constructors and Destructor
    Nexus() = default;
    ~Nexus() = default;

    // Methods
    void Create() override {
        #ifdef CORE_TESTS
            mCore = CreateReference<Test::Core>();
        #endif
        #ifdef SYSTEMS_TESTS
            mEngine = new Test::Engine();
            PushLayer(mEngine);
            mEngine = CreateReference<Test::Engine>();
        #endif
        #ifdef RESEARCH_TESTS
            mResearch = CreateReference<Test::Research>();
        #endif
    }

	void Destroy() override {
    }

	void Update([[maybe_unused]] DeltaTime deltaTime) override {
        #ifdef SYSTEMS_TESTS
            mEngine->Test(deltaTime);
        #endif
    }

private:
    //Reference<Test::Core> mCore;
    //Test::Engine *mEngine;
    //Reference<Test::Research> mResearch;
};

// Application Entry-Point
Application* CreateApplication() {
	return new Nexus();
}

}
