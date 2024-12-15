module;

#include "Vite/Base/Platform/Detection.h"
#include "Vite/Base/Platform/Support.h"

#define BOOST_UT_DISABLE_MODULE
#include <boost/ut.hpp>

export module Test.Base;

import Vite.Core;
import Vite.App.Layers;

static constexpr auto iterations = 1'000'000;

export namespace Hedron::Test {

using namespace boost::ut;

///
/// @brief Base | Serves all base tests for the Hedron Engine.
///
class Base: public Layer {
public:
    /// Default
    Base() = default;
    ~Base() = default;

    /// Methods
    void Create() override {
        Test();
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

    /// Tests
    void Test() {
        suite<"Algorithm"> algorithm = [] { AlgorithmsTest(); };
        suite<"Bridges"> bridges = [] { BridgesTest(); };
        suite<"Devices"> devices = [] { DevicesTest(); };
        suite<"Extensions"> extensions = [] { ExtensionsTest(); };
        suite<"Mathematics"> mathematics = [] { MathematicsTest(); };
        suite<"Memory"> memory = [] { MemoryTest(); };
        suite<"Platform"> platform = [] { PlatformTest(); };
        suite<"Runtime"> runtime = [] { RuntimeTest(); };
        suite<"System"> system = [] { SystemTest(); };
        suite<"Types"> types = [] { TypesTest(); };
    }

    static void AlgorithmsTest() {}
    
    static void BridgesTest() {}
    
    static void DevicesTest() {}
    
    static void ExtensionsTest() {
        "Bitmask"_test = [] {
            expect(BitMask(0) == 1);
            expect(BitMask(1) == 2);
            expect(BitMask(2) == 4);
            expect(BitMask(3) == 8);
            expect(BitMask(4) == 16);
            expect(BitMask(5) == 32);
            expect(BitMask(6) == 64);
            expect(BitMask(7) == 128);
        };

        "Charset"_test = [] {
            // Valid UTF-8 strings

            string_view validAscii = "A"; // ASCII
            auto it = validAscii.begin();
            expect(DecodeUtf8(it, validAscii.end()) == 0x41); // 'A'

            string_view valid2Bytes = "\xC3\xA9"; // é (U+00E9)
            it = valid2Bytes.begin();
            expect(DecodeUtf8(it, valid2Bytes.end()) == 0xE9); // 'é'

            string_view valid3Bytes = "\xE2\x82\xAC"; // € (U+20AC)
            it = valid3Bytes.begin();
            expect(DecodeUtf8(it, valid3Bytes.end()) == 0x20AC); // '€'

            string_view valid4Bytes = "\xF0\x9F\x98\x80"; // 😀 (U+1F600)
            it = valid4Bytes.begin();
            expect(DecodeUtf8(it, valid4Bytes.end()) == 0x1F600); // 😀

            // Invalid UTF-8 strings

            string_view invalidStartByte = "\x80"; // Invalid start byte
            it = invalidStartByte.begin();
            expect(DecodeUtf8(it, invalidStartByte.end()) == 0xFFFD); // Replacement character

            string_view invalidContinuation = "\xC3\x28"; // Invalid continuation
            it = invalidContinuation.begin();
            expect(DecodeUtf8(it, invalidContinuation.end()) == 0xFFFD); // Replacement character

            string_view prematureEnd = "\xE2\x82"; // Premature end for 3-byte sequence
            it = prematureEnd.begin();
            expect(DecodeUtf8(it, prematureEnd.end()) == 0xFFFD); // Replacement character

            string_view validThenInvalid = "\xF0\x9F\x98\x80\xC3"; // 😀 followed by invalid start
            it = validThenInvalid.begin();
            expect(DecodeUtf8(it, validThenInvalid.end()) == 0x1F600); // 😀
            expect(DecodeUtf8(it, validThenInvalid.end()) == 0xFFFD);  // Replacement character
        };

        "Enum"_test = [] {
        };

        "String"_test = [] {
            string simple = "Test";
            wstring wide = L"Test";

            expect(simple == WStringToString(wide));
            expect(wide == StringToWString(simple));
        };

        "Vector"_test = [] {
            vector<int> test(2);

            expect(sizeof_vector(test) == 2 * sizeof(int));
        };
    }
    
    static void MathematicsTest() {
        LogDelimiter("");
        Log("Mathematics\n");
        LogDelimiter("");

        // Matrix
        Test::MatrixTests();

        // Quaternion
        Test::QuaternionTests();

        // Vector
        Test::VectorTests();
    }
   
    static void MemoryTest() {}
    
    static void PlatformTest() {
        "Platform Tests"_test = [] {
            //LogDelimiter("");
            //Log("Platform\n");
            //LogDelimiter("");

            //Log("Detection\n");
            expect(AppCompiler == APP_COMPILER);
            expect(AppCompilerVersion == APP_COMPILER_VERSION);
            expect(AppPlatform == APP_PLATFORM);
            expect(AppPlatformAPI == APP_PLATFORM_API);

            //Log("Support\n");
            expect("__declspec(dllimport)" == TOSTRING(APP_API));
            expect("__debugbreak()" == TOSTRING(APP_DEBUGBREAK()));
            expect("[[msvc::no_unique_address]]" == TOSTRING(CPP_NO_UNIQUE_ADDRESS));
        };
    }
    
    static void RuntimeTest() {}

    static void SystemTest() {
        "Cli"_test = [] {
            Cli::Test::TestCli();
        };

        "Dialog"_test = [] {
            //auto dialog = Dialog::Create(nullptr);
            //auto openFile = dialog->OpenFile("Open File", { "All Files (*.*)", "* .*" });
            //auto saveFile = dialog->SaveFile("Save File", { "All Files (*.*)", "* .*" });
        };
        
        "FileSystem"_test = [] {
            expect(Directory::ValidatePath("Assets/Shaders") == true);
            expect(Directory::Exists("Assets/Shaders") == true);

            auto shadersDirExists = Directory::Exists("Assets/Shaders");
            auto shaderList = Directory::GetFiles("Assets/Shaders", ".glsl");
            //Log(" - Shaders Directory List:\n");
            //for (const auto &shader : shaderList) {
            //    Log("   o Shader: {}\n", shader);
            //}

            expect(File::Exists("Assets/Shaders/Test.glsl") == true);
            expect(File::GetExtension("Assets/Shaders/Test.glsl") == ".glsl");
            expect(File::GetName("Assets/Shaders/Test.glsl") == "Test");
            expect(File::GetPath("Assets/Shaders/Test.glsl") == "Assets/Shaders");
            expect(File::GetRoot("Assets/Shaders/Test.glsl") == "");

            auto shaderBin = File::LoadAsBinary("Assets/Shaders/Test.glsl");
            auto shaderString = File::LoadAsString("Assets/Shaders/Test.glsl");
            auto shaderText = File::LoadAsText("Assets/Shaders/Test.glsl");
            //Log(" - Shader File AsBinary: {}\n");
            //for (const auto &bin : shaderBin) {
            //    Log("{}\t", bin);
            //}
            //Log("\n");
            //Log(" - Shader File AsString: {}\n", shaderString);
            //Log(" - Shader File AsText: {}\n");
            //for (const auto &line : shaderText) {
            //    Log("   o {}\n", line);
            //}
        };

        "Library"_test = [] {
            //Log("Library\n");
        };
    }

    static void TypesTest() {
        "Concepts"_test = [] {
            expect(typename_arithmetic<int> == true);
            expect(typename_arithmetic<string> == false);
            expect(typename_floating_point<float> == true);
            expect(typename_floating_point<int> == false);
            expect(typename_hashable<size_t> == true);
            expect(typename_string<string> == true);
            expect(typename_string_view<string_view> == true);
            expect(typename_xstring<string> == true);
            expect(typename_xstring<float> == false);
            expect(typename_xstring<wstring> == true);
            expect(typename_xstring<float> == false);
        };

        "Entity / Component / System"_test = [] {
            auto component = CreateReference<Component>();
            auto entity = Entity("Test");
            entity.AddComponent(component);
            auto componentRef = entity.GetComponent();
            entity.HasComponent();
            entity.RemoveComponent(component);
        };

        "Literals"_test = [] {
            expect("Test"_hash == 2626979548338364165);
        };

        "Property"_test = [] {
            Property<int> PropertySize { 50, [](const auto &value) {
                    return value < 0 ? 0 : (value > 1000 ? 1000 : value);
                }
            };

            expect(PropertySize == 50);
            PropertySize = -2000;
            expect(PropertySize == 0);
            PropertySize = 2000;
            expect(PropertySize == 1000);
        };

        "Timestamp"_test = [] {
            auto delta = DeltaTime(1000);
            expect(delta.GetSeconds() == 1.0_d);
            expect(delta.GetMilliseconds() == 1000.0_d);
        };

        "UUID"_test = [] {
            //Log(" - uint16: {}\n", static_cast<uint16>(UUID<uint16>()));
            //Log(" - uint32: {}\n", static_cast<uint32>(UUID<uint32>()));
            //Log(" - uint64: {}\n", static_cast<uint64>(UUID<uint64>()));
            //Log(" - string: {}\n", static_cast<string>(UUID()));
        };
    }
};

}
