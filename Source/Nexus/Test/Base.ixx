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
    void PlatformTest() {}
    void RuntimeTest() {}
    void SystemTest() {
        LogDelimiter("");
        Log("System\n");
        LogDelimiter("");

        // CLI
        
        // FileSystem
        auto shaders = Directory::GetFiles("Assets/Shaders", ".glsl");
        auto bin = File::LoadAsBinary("Assets/Shaders/Test.glsl");
        auto txt = File::LoadAsText("Assets/Shaders/Test.glsl");
        // Heap Corruption?
    }
    void TypesTest() {
        LogDelimiter("");
        Log("Types\n");
        LogDelimiter("");

        // Property
        LogTrace("PropertySize before: {}", static_cast<size_t>(PropertySize));
        PropertySize = 1001;
        LogTrace("PropertySize after setting: {}", static_cast<size_t>(PropertySize));

        // UUID
        LogInfo("UUID [uint16]: {}", static_cast<uint16>(UUID<uint16>()));
        LogInfo("UUID [uint32]: {}", static_cast<uint32>(UUID<uint32>()));
        LogInfo("UUID [uint64]: {}", static_cast<uint64>(UUID<uint64>()));
        LogInfo("UUID [string]: {}", static_cast<string>(UUID()));
    }

private:
    /// Properties
    Property<size_t> PropertySize { 50/*, [this](const size_t &value) {
        return value > 1000 ? 1000 : 0;
    } */ };
};

}
