﻿#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

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

using namespace boost::ut;

///
/// @brief Nexus | Test me if you can!
/// @note This project is used to test the whole Hedron framework.
///
class Nexus: public Application {
public:
    /// Default
    Nexus(): Application({
        .Title = "Nexus",
        .Resolution = "640x480",
        .LogLevel = LogLevel::Trace,
        .ExternalLoop = false,
    }) {
        "Application"_test = [&] {
            auto &states = GetStates();
            expect(states.Active == true);
            expect(states.Paused == false);
            expect(states.Reloading == false);
            expect(states.Running == true);

            auto &statistics = GetStatistics();
            expect(statistics.fps == 0);
            expect(statistics.msPF == 0);

            expect(GetGraphicsContext() != nullptr);
            expect(GetRenderer() != nullptr);
            expect(GetWindow() != nullptr);
        };

        auto &settings = GetSettings();
        "Settings"_test = [settings] {
            expect(settings.Title == "Nexus");
            expect(settings.Resolution == "640x480");
            expect(settings.GraphicsAPI == GraphicsAPI::OpenGL);
            expect(settings.LogLevel == LogLevel::Trace);
            expect(settings.ExternalLoop == false);
            expect(settings.ConsoleLogging == true);
            expect(settings.FileLogging == false);
            expect(settings.MemoryLogging == false);
            expect(settings.TargetFPS == 60);
            expect(settings.VSync == true);
        };
    };
    ~Nexus() = default;

    /// Methods
    void Create() override {
        "Arguments"_test = [&] {
            auto &arguments = GetArguments();
            expect(arguments["-test"] == "Hello World!");
        };

        if constexpr (BASE_TESTS) PushLayer(new Test::Base());
        if constexpr (CORE_TESTS) PushLayer(new Test::Core());
        if constexpr (ENGINE_TESTS) PushLayer(new Test::Engine());
        if constexpr (RESEARCH_TESTS) PushLayer(new Test::Research());
        if constexpr (TOOL_TESTS) PushLayer(new Test::Tool());
    }
	void Destroy() override {}
    void Update(DeltaTime deltaTime) override {
        //Exit();
    }
};

// Application Entry-Point
Application *CreateApplication() {
	return new Nexus();
}

}
