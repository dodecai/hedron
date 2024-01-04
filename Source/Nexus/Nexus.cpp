import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;
import Vite.Util.ThreadPool;

//import Vite.Test.Core;
//import Vite.Test.Engine;
//import Vite.Test.Research;

// Switches
//#define CORE_TESTS
//#define RESEARCH_TESTS
//#define SYSTEMS_TESTS

namespace Hedron {

// Performance Test
long long Fibonacci(int n) {
    if (n <= 1) return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// Application
class Nexus: public Application {
public:
    // Constructors and Destructor
    Nexus() = default;
    ~Nexus() = default;

    // Methods
    void Create() override {
        mThreadPool = CreateScope<ThreadPool>();
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
    //
    Scope<ThreadPool> mThreadPool;
    //Reference<Test::Core> mCore;
    //Test::Engine *mEngine;
    //Reference<Test::Research> mResearch;
};

// Application Entry-Point
Application* CreateApplication() {
	return new Nexus();
}

}
