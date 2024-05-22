export module Test.Core;

import Vite.Core;
import Vite.App.Layers;

export namespace Hedron::Test {

#pragma region /// Functions

// Performance Test
inline long long Fibonacci(int n) {
    //if (n >= 47) throw std::invalid_argument("n is too large");
    if (n <= 1) return n;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

#pragma endregion

#pragma region /// Events

struct KeyboardEvent {
    int KeyCode = 0;
};

struct MouseEvent {
    int X = 0;
    int Y = 0;
};

struct EventListenerTest {
    void OnKeyboardEvent(const KeyboardEvent &data) {
        logger << __FUNCTION__ << ":" << data.KeyCode << "\n";
    }
    void OnMouseEvent(const MouseEvent &data) {
        logger << __FUNCTION__ << ":" << data.X << "\n";
    }
};

struct Tester {
    int Value = 5;

    //void BasicEvent(string test) {
    //    logger << __FUNCTION__ << ":" << test << "\n";
    //}

    //void BasicEventInt(int test) {
    //    logger << __FUNCTION__ << ":" << test << "\n";
    //}

    bool Event(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    const bool ConstEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    static bool StaticEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return true;
    }

    bool NoExceptEvent(string test) noexcept {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    const bool NoExceptConstEvent(string test) noexcept {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    static bool NoExceptStaticEvent(string test) noexcept {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    volatile bool VolatileEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    const volatile bool VolatileConstEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    static volatile bool VolatileStaticEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }

    static const volatile bool VolatileStaticConstEvent(string test) {
        //logger << __FUNCTION__ << ":" << test << "\n";
        return false;
    }
};

#pragma endregion

#pragma region /// Future

//#ifdef FUTURE_TEST
//
//static std::future<void> Future;
//static void logmillion() {
//    Ultra::applog << Ultra::Log::Info << "Started" << "\n";
//    for (size_t i = 0; i <= 1000000; ++i) {
//        Ultra::applog << "";
//    }
//    Ultra::applog << Ultra::Log::Info << "Finished " << "\n";
//}
//
//void Start() {
//    applog << "0: " << std::this_thread::get_id() << std::endl;
//    Future = std::async(std::launch::async, logmillion);
//    static std::thread MainThread1([&]() { Future = std::async(std::launch::async, logmillion); });
//    static std::thread MainThread2([&]() { Future = std::async(std::launch::async, logmillion); });
//    static std::thread MainThread3([&]() { Future = std::async(std::launch::async, logmillion); });
//    applog << "1: " << MainThread1.get_id() << std::endl;
//    applog << "2: " << MainThread2.get_id() << std::endl;
//    applog << "3: " << MainThread3.get_id() << std::endl;
//}
//#endif

#pragma endregion

///
/// @brief Core | Serves all core tests for the Hedron Engine.
///
class Core: public Layer {
public:
    /// Default
    Core() = default;
    ~Core() = default;

    /// Methods
    void Create() override {
        LogCaption("Core Tests");
        mThreadPool = CreateScope<ThreadPool>(4);
        Test();
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {
        //return; // OpenGL Context destroys stack
        ///
        /// ThreadPool
        ///
        static double delay = 0.0;
        delay += deltaTime.GetMilliseconds();

        if (delay >= 0.2) {
            // Thread Pool Tasks
            const int n = 512;
            auto fibResultA = mThreadPool->Enqueue([=] {
                auto result = Fibonacci(n);
                return result;
            });
            auto fibResultB = mThreadPool->Enqueue([=] {
                auto result = Fibonacci(n);
                return result;
            });

            delay = 0.0;
        }
    }

    /// Tests
    void Test() {
        AppTest();
        ConfigTest();
        EventTest();
        LoggerTest();
        NetworkTest();
        SerializerTest();
        UtilsTest();
    }
    void AppTest() {}
    void ConfigTest() {}
    void EventTest() {
        LogDelimiter("");
        Log("Events\n");
        LogDelimiter("");

//        // Delegate, Dispatcher, Emitter and Signal
//        Log("Delegate, Dispatcher, Emitter and Signal");
//        LogDelimiter("");
//        //Dispatcher<bool(string)> TestA;
//        auto timerE = Timer();
//        {
//            Tester *tester = new Tester();
//
//            // Delegates
//            Delegate<bool(string)> delegateA {};
//            Delegate<bool(string)> delegateB {};
//
//            delegateB.connect<&Tester::StaticEvent>();
//            delegateA.connect<&Tester::Event>(tester);
//
//            auto resultB = delegateB("DelegateA");
//            auto resultA = delegateA("DelegateB");
//
//            // Signals
//            //Signal<bool(string)> signalA;
//            //Sink sinkA { signalA };
//
//            //sinkA.connect<&Tester::VolatileStaticEvent>();
//            //sinkA.connect<&Tester::VolatileStaticConstEvent>();
//
//            //signalA.publish("Signal");
//
//            // Dispatcher
//            Dispatcher dispatcherA {};
//
//            EventListenerTest listener;
//            dispatcherA.sink<KeyboardEvent>().connect<&EventListenerTest::OnKeyboardEvent>(listener);
//            dispatcherA.sink<MouseEvent>().connect<&EventListenerTest::OnMouseEvent>(listener);
//
//            dispatcherA.trigger(KeyboardEvent { 60 });
//            dispatcherA.enqueue<KeyboardEvent>(65);
//            dispatcherA.enqueue<KeyboardEvent>(67);
//            dispatcherA.update<KeyboardEvent>();
//            dispatcherA.trigger(MouseEvent { -1 });
//
//            // Emitter
//            EventEmitter emitterA {};
//            emitterA.on<KeyboardEvent>([](const KeyboardEvent &data, EventEmitter &emitter) {
//                logger << __FUNCTION__ << ": Emitter " << data.KeyCode << "\n";
//            });
//            emitterA.publish(KeyboardEvent { 42 });
//            emitterA.publish(KeyboardEvent { 43 });
//
//            //auto test = DelegateMember(*tester, &Tester::Event);
//            //test("1");
//
//
//            //auto test2 = DelegateMember(*tester, &Tester::ConstEvent);
//            //test2("2");
//
//            //auto test3 = Delegate(&Tester::StaticEvent);
//            //test3("3");
//
//            //auto same = test == test2;
//            delete tester;
//
//            // Lambda
//            //TestA += [&](string test) -> bool {
//            //    logger << __FUNCTION__ << ":" << test << "\n";
//            //    return false;
//            //};
//            //TestA += [&](string test) -> bool {
//            //    logger << __FUNCTION__ << ":" << test << "\n";
//            //    return true;
//            //};
//
//            // Members
//            //TestA += DelegateMember(*tester, &Tester::Event);
//            //TestA += DelegateMember(*tester, &Tester::Event);
//            //TestA += DelegateMember(*tester, &Tester::ConstEvent);
//            //TestA += DelegateMember(*tester, &Tester::ConstEvent);
//            //TestA += DelegateMember(*tester, &Tester::NoExceptEvent);
//            //TestA += DelegateMember(*tester, &Tester::NoExceptEvent);
//            //TestA += DelegateMember(*tester, &Tester::NoExceptConstEvent);
//            //TestA += DelegateMember(*tester, &Tester::NoExceptConstEvent);
//            //TestA += DelegateMember(*tester, &Tester::VolatileEvent);
//            //TestA += DelegateMember(*tester, &Tester::VolatileEvent);
//            //TestA += DelegateMember(*tester, &Tester::VolatileConstEvent);
//            //TestA += DelegateMember(*tester, &Tester::VolatileConstEvent);
//
//            // Functions
//            //TestA += &Tester::StaticEvent;
//            //TestA += &Tester::StaticEvent;
//            //TestA += &Tester::NoExceptStaticEvent;
//            //TestA += &Tester::NoExceptStaticEvent;
//            //TestA += &Tester::VolatileStaticEvent;
//            //TestA += &Tester::VolatileStaticEvent;
//            //TestA += &Tester::VolatileStaticConstEvent;
//            //TestA += &Tester::VolatileStaticConstEvent;
//            //VerifyMemoryUsage();
//            Log("Duration: {}", timerE.GetDeltaTime());
//        }
//        //TestA("Test A");
//        Log("Duration: {}", timerE.GetDeltaTime());
//        // String
//        Log("String");
//        LogDelimiter("");
//        //String::Test();
//        LogDelimiter("");
    }
    void LoggerTest() {
        LogDelimiter("");
        Log("Logger\n");
        LogDelimiter("");

        logger << LogLevel::Trace << "Hello World! 🦄" << "\n";
        LogTrace("{}: {} {:.2}", "Hello", "World! 🦄", 1.234567f);
        Test::TestLogger();

    }
    void NetworkTest() {}
    void SerializerTest() {}
    void UtilsTest() {
        // Utils
        LogDelimiter("");
        Log("Utils\n");
        LogDelimiter("");

        // Chrono
        logger(" - CurrentDate:      {}\n", Chrono::Date());
        logger(" - CurrentTime:      {}\n", Chrono::Time());
        logger(" - CurrentTimestamp: {}\n", Chrono::Timestamp());
        //logger(" - CurrentRuntime:   {}\n", Chrono::Runtime());
        
        // Random
        
        // String
        
        // ThreadPool
//        ThreadPool pool;
//        for (int i = 0; i < 8; ++i) {
//            // Create eight tasks in the queue
//            pool.Enqueue([i] {
//                auto timer = Timer();
//                {
//                    Log("TaskStart {}\n", i);
//                    std::this_thread::sleep_for(std::chrono::milliseconds(2));
//                    Log("TaskEnd {}\n", i);
//                }
//                Log("TaskDuration {}\n", timer.GetDeltaTime());
//            });
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(32));
        
        // Timer
//         // Timer
//        {
//            Log("Timer");
//            LogDelimiter("");
//            Timer timer {};
//            Log("Now:          {}", timer.Now());
//            Log("Duration:     {}", timer.GetDeltaTime());
//            Log("Duration(ns): {}", timer.GetDeltaTimeAs(TimerUnit::Nanoseconds));
//            Log("Duration(µs): {}", timer.GetDeltaTimeAs(TimerUnit::Microseconds));
//            Log("Duration(ms): {}", timer.GetDeltaTimeAs(TimerUnit::Milliseconds));
//            Log("Duration(s):  {}", timer.GetDeltaTimeAs(TimerUnit::Seconds));
//            LogDelimiter("");
//        }
    }

    /// Events
    //void OnInputEvent(const KeyboardEvent &event) override {
    //}

private:
    /// Instances
    Scope<ThreadPool> mThreadPool;
    //struct EventEmitter: Emitter<EventEmitter> {};

};

}
