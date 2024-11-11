import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;
import Test.Base;
import Test.Core;
import Test.Engine;
import Test.Research;
import Test.Tool;

// Switches
constexpr auto BASE_TESTS = false;
constexpr auto CORE_TESTS = false;
constexpr auto ENGINE_TESTS = true;
constexpr auto RESEARCH_TESTS = false;
constexpr auto TOOL_TESTS = false;

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
        //Debug::DisplayCompileInformation();

        if constexpr (BASE_TESTS) PushLayer(new Test::Base());
        if constexpr (CORE_TESTS) PushLayer(new Test::Core());
        if constexpr (ENGINE_TESTS) PushLayer(new Test::Engine());
        if constexpr (RESEARCH_TESTS) PushLayer(new Test::Research());
        if constexpr (TOOL_TESTS) PushLayer(new Test::Tool());
    }
	void Destroy() override {}
	void Update(DeltaTime deltaTime) override {}

private:
    /// Properties
};

// Application Entry-Point
Application* CreateApplication() {
	return new Nexus();
}

}
