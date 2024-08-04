module;

#include "Vite/Base/Platform/Detection.h"
#include "Vite/Base/Platform/Support.h"

export module Test.Base;

import Vite.Core;
import Vite.App.Layers;

export namespace Hedron::Test {

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
        LogCaption("Base Tests");
        Test();
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

    /// Tests
    void Test() {
        AlgorithmsTest();
        BridgesTest();
        DevicesTest();
        ExtensionsTest();
        MathematicsTest();
        MemoryTest();
        PlatformTest();
        RuntimeTest();
        SystemTest();
        TypesTest();
    }
    void AlgorithmsTest() {}
    void BridgesTest() {}
    void DevicesTest() {}
    void ExtensionsTest() {}
    void MathematicsTest() {
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
    void MemoryTest() {}
    void PlatformTest() {
        LogDelimiter("");
        Log("Platform\n");
        LogDelimiter("");

        // Detection
        Log("Detection\n");
        Log(" - Compiler: '{}' ='{}'\n", AppCompiler, APP_COMPILER);
        Log(" - Compiler Version: '{}' ='{}'\n", AppCompilerVersion, APP_COMPILER_VERSION);
        Log(" - Platform: '{}={}'\n", AppPlatform, APP_PLATFORM);
        Log(" - Platform API: '{}={}'\n", AppPlatformAPI, APP_PLATFORM_API);

        // Support
        Log("Support\n");
        Log(" - Api Export: {}\n", TOSTRING(APP_API));
        Log(" - Debug Break: {}\n", TOSTRING(APP_DEBUGBREAK()));
        Log(" - Cpp NoUniqueAddress: {}\n", TOSTRING(CPP_NO_UNIQUE_ADDRESS));
    }
    void RuntimeTest() {}
    void SystemTest() {
        LogDelimiter("");
        Log("System\n");
        LogDelimiter("");

        // CLI
        Log("CLI\n");
        Cli::Test::TestCli();

        // Dialog
        Log("Dialog\n");
        //auto dialog = Dialog::Create(nullptr);
        //auto openFile = dialog->OpenFile("Open File", { "All Files (*.*)", "* .*" });
        //auto saveFile = dialog->SaveFile("Save File", { "All Files (*.*)", "* .*" });
        
        // FileSystem
        Log("FileSystem\n");
        auto shadersDirValid = Directory::ValidatePath("Assets/Shaders");
        auto shadersDirExists = Directory::Exists("Assets/Shaders");
        auto shaderList = Directory::GetFiles("Assets/Shaders", ".glsl");
        Log(" - Shaders Directory Valid: {}\n", shadersDirValid);
        Log(" - Shaders Directory Exists: {}\n", shadersDirExists);
        Log(" - Shaders Directory List:\n");
        for (const auto &shader : shaderList) {
            Log("   o Shader: {}\n", shader);
        }

        auto shaderFileExists = File::Exists("Assets/Shaders/Test.glsl");
        auto shaderFileExtension = File::GetExtension("Assets/Shaders/Test.glsl");
        auto shaderFileName = File::GetName("Assets/Shaders/Test.glsl");
        auto shaderFilePath = File::GetName("Assets/Shaders/Test.glsl");
        auto shaderFileRoot = File::GetRoot("Assets/Shaders/Test.glsl");
        auto shaderBin = File::LoadAsBinary("Assets/Shaders/Test.glsl");
        auto shaderString = File::LoadAsString("Assets/Shaders/Test.glsl");
        auto shaderText = File::LoadAsText("Assets/Shaders/Test.glsl");
        Log(" - Shader File Exists: {}\n", shaderFileExists);
        Log(" - Shader File Extension: {}\n", shaderFileExtension);
        Log(" - Shader File Name: {}\n", shaderFileName);
        Log(" - Shader File Path: {}\n", shaderFilePath);
        Log(" - Shader File Root: {}\n", shaderFileRoot);
        Log(" - Shader File AsBinary: {}\n");
        for (const auto &bin : shaderBin) {
            Log("{}\t", bin);
        }
        Log("\n");
        Log(" - Shader File AsString: {}\n", shaderString);
        Log(" - Shader File AsText: {}\n");
        for (const auto &line : shaderText) {
            Log("   o {}\n", line);
        }

        // Library
        Log("Library\n");
    }
    void TypesTest() {
        LogDelimiter("");
        Log("Types\n");
        LogDelimiter("");

        // Concepts
        Log("Concepts\n");
        //Log(" - Arithmetic: {}\n", typename_arithmetic<int>);
        //Log(" - Floating Point: {}\n", typename_floating_point<float>);
        //Log(" - Hashable: {}\n", typename_hashable<size_t>);
        //Log(" - String: {}\n", typename_string<string>);
        //Log(" - String View: {}\n", typename_string_view<string_view>);
        //Log(" - XString: {}\n", typename_xstring<string>);
        //Log(" - WString: {}\n", typename_wstring<wstring>);

        // Entity / Component / System
        Log("Entity / Component / System\n");
        auto component = CreateReference<Component>();
        auto entity = Entity("Test");
        entity.AddComponent(component);
        auto componentRef = entity.GetComponent();
        entity.HasComponent();
        entity.RemoveComponent(component);
        //Log(" - Component: {}\n", component);
        //Log(" - Entity: {}\n", entity);

        // Literals
        Log("Literals\n");
        Log(" String Hash [Test]: {}\n", "Test"_hash);

        // Property
        Log("Property\n");
        Log(" - Size before: {}\n", static_cast<size_t>(PropertySize));
        PropertySize = 2000;
        Log(" - Size after setting it to 2000: {}\n", static_cast<size_t>(PropertySize));

        // Timestamp
        Log("Timestamp\n");
        auto delta = DeltaTime(1000);
        Log(" - seconds:     {}\n", delta.GetSeconds());
        Log(" - miliseconds: {}\n", delta.GetMilliseconds());

        // UUID
        Log("UUID\n");
        Log(" - uint16: {}\n", static_cast<uint16>(UUID<uint16>()));
        Log(" - uint32: {}\n", static_cast<uint32>(UUID<uint32>()));
        Log(" - uint64: {}\n", static_cast<uint64>(UUID<uint64>()));
        Log(" - string: {}\n", static_cast<string>(UUID()));
    }

private:
    /// Properties
    Property<size_t> PropertySize { 50, [](const auto &value) {
            return value > 1000 ? 1000 : value;
        }
    };
};

}
