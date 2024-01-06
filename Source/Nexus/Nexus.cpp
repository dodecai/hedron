import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;
import Vite.Util.ThreadPool;
//import Vite.Test.Core;
//import Vite.Test.Engine;
//import Vite.Test.Research;

// Switches
//#define CORE_TESTS
//#define ENGINE_TESTS
//#define RESEARCH_TESTS

namespace Hedron {

#pragma region /// Functions

// Performance Test
inline long long Fibonacci(int n) {
    if (n <= 1) return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

#pragma endregion

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

        #ifdef CORE_TESTS
            mCore = CreateScope<Test::Core>();
        #endif
        #ifdef ENGINE_TESTS
            // ToDo: A layer should be also created from an reference pointer.
            mEngine = new Test::Engine();
            PushLayer(mEngine);
            mEngine = CreateScope<Test::Engine>();
        #endif
        #ifdef RESEARCH_TESTS
            mResearch = CreateScope<Test::Research>();
        #endif

        mThreadPool = CreateScope<ThreadPool>();
    }
	void Destroy() override {
    }
	void Update(DeltaTime deltaTime) override {
        #ifdef SYSTEMS_TESTS
            mEngine->Test(deltaTime);
        #endif
        
        if (Input::GetKeyState(KeyCode::Escape)) {
            Exit();
        }
        
        static double delay = 0.0;
        delay += deltaTime.GetMilliseconds();

        if (delay >= 0.2) {
            // Thread Pool Tasks
            const int n = 2;
            auto fibResultA = mThreadPool->Enqueue([&] {
                auto result = Fibonacci(n);
                return result;
            });
            auto fibResultB = mThreadPool->Enqueue([&] {
                auto result = Fibonacci(n);
                return result;
            });

            delay = 0.0;
        }
    }

private:
    /// Properties
    //Scope<Test::Core> mCore;
    //Scope<Test::Engine> mEngine;
    //Scope<Test::Research> mResearch;
    Scope<ThreadPool> mThreadPool;
};

// Application Entry-Point
Application* CreateApplication() {
	return new Nexus();
}

}
