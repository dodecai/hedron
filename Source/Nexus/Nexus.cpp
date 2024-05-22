import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;
import Vite.Util.ThreadPool;

import Test.Base;
import Test.Core;
import Test.Engine;
import Test.Research;
import Test.Tool;

// Switches
#define BASE_TESTS
#define CORE_TESTS
//#define ENGINE_TESTS
#define RESEARCH_TESTS
#define TOOL_TESTS

namespace Hedron {

///
/// @brief Nexus | Test me if you can!
/// @note This project is used to test the whole Hedron framework.
///
class Nexus: public Application {
public:
    /// Default
    Nexus() = default;
    ~Nexus() = default;

    /// Methods
    void Create() override {
        Debug::DisplayCompileInformation();


        auto nothing = true;
        #ifdef BASE_TESTS
            PushLayer(new Test::Base());
        #endif
        #ifdef CORE_TESTS
            PushLayer(new Test::Core());
        #endif
        #ifdef ENGINE_TESTS
            PushLayer(new Test::Engine());
        #endif
        #ifdef RESEARCH_TESTS
            PushLayer(new Test::Research());
        #endif
        #ifdef TOOL_TESTS
            PushLayer(new Test::Tool());
        #endif
    }
	void Destroy() override {
    }
	void Update(DeltaTime deltaTime) override {
        if (Input::GetKeyState(KeyCode::Escape)) {
            Exit();
        }
    }

private:
    /// Properties
};

// Application Entry-Point
Application* CreateApplication() {
	return new Nexus();
}

}
