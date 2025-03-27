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
        "Matrix"_test = [] {
            //MatrixBase<float, 2> m1 { 1, 2, 3, 4 };
            //MatrixBase<float, 2> m2 { 5, 6, 7, 8 };

            //// Test basic properties
            //expect(m1.At(0, 0) == 1 && m1.At(0, 1) == 2 && m1.At(1, 0) == 3 && m1.At(1, 1) == 4) << "Basic properties test failed for m1.";

            //// Test arithmetic operations
            //auto sum = m1 + m2;
            //expect(sum.At(0, 0) == 6 && sum.At(0, 1) == 8 && sum.At(1, 0) == 10 && sum.At(1, 1) == 12) << "Addition test failed.";
            ////AppAssert(, );
            //auto diff = m2 - m1;
            //expect(diff.At(0, 0) == 4 && diff.At(0, 1) == 4 && diff.At(1, 0) == 4 && diff.At(1, 1) == 4) << "Subtraction test failed.";
            //auto prod = m1 * m2;
            //expect(prod.At(0, 0) == 19 && prod.At(0, 1) == 22 && prod.At(1, 0) == 43 && prod.At(1, 1) == 50) << "Multiplication test failed.";

            //// Test Transpose
            //auto transposed = m1.Transpose();
            //expect(transposed.At(0, 0) == 1 && transposed.At(0, 1) == 3 && transposed.At(1, 0) == 2 && transposed.At(1, 1) == 4) << "Transpose test failed.";

            //// Test Determinant (2x2 matrix)
            //float det = m1.Determinant();
            //expect(det == -2.0f) << "Inverse test failed.";

            //// Test Inverse (2x2 matrix)
            //auto inverse = m1.Inverse();
            //expect(inverse.At(0, 0) == -2 && inverse.At(0, 1) == 1 && inverse.At(1, 0) == 1.5 && inverse.At(1, 1) == -0.5) << "Message";

            //// Test Identity
            //auto identity = MatrixBase<float, 2>::Identity();
            //expect(identity.At(0, 0) == 1 && identity.At(0, 1) == 0 && identity.At(1, 0) == 0 && identity.At(1, 1) == 1) << "Identity test failed.";

            //// Test scalar multiplication and division
            //auto scalarMul = m1 * 2.0f;
            //expect(scalarMul.At(0, 0) == 2 && scalarMul.At(0, 1) == 4 && scalarMul.At(1, 0) == 6 && scalarMul.At(1, 1) == 8) << "Scalar multiplication test failed.";
            //auto scalarDiv = m1 / 2.0f;
            //expect(scalarDiv.At(0, 0) == 0.5 && scalarDiv.At(0, 1) == 1 && scalarDiv.At(1, 0) == 1.5 && scalarDiv.At(1, 1) == 2) << "Scalar division test failed.";
        };

        "Quaternion"_test = [] {
            expect(true) << "Message";

            //// Preparation
            //LogInfo("Testing Quaternion");
            //Quaternion q0 { 1, 0, 0, 0 };
            //Quaternion q1 { 1, 0, 0, 0 };
            //Quaternion q2 { 0, 1, 0, 0 };
            //Quaternion q3 { 0, 0, 1, 0 };
            //Quaternion q4 { 0, 0, 0, 1 };

            //// Test basic properties
            //AppAssert(q1.w == 1 && q1.x == 0 && q1.y == 0 && q1.z == 0, "Basic properties test failed for q1.");

            //// Test equality
            //AppAssert((q0 == q1), "Equality test failed.");
            //AppAssert((q1 <=> q2) < 0, "Less than test failed.");
            //AppAssert((q2 <=> q1) > 0, "Greater than test failed.");


            //// Test arithmetic operations
            //auto sum = q1 + q2;
            //AppAssert(sum.w == 1 && sum.x == 1 && sum.y == 0 && sum.z == 0, "Addition test failed.");
            //auto diff = q1 - q2;
            //AppAssert(diff.w == 1 && diff.x == -1 && diff.y == 0 && diff.z == 0, "Subtraction test failed.");
            //auto prod = q1 * 2.0f;
            //AppAssert(prod.w == 2 && prod.x == 0 && prod.y == 0 && prod.z == 0, "Scalar multiplication test failed.");

            //// Test Conjugate
            //auto conjugate = q2.Conjugate();
            //AppAssert(conjugate.w == 0 && conjugate.x == -1 && conjugate.y == 0 && conjugate.z == 0, "Conjugate test failed.");

            //// Test Dot Product
            //auto dotProduct = q2.Dot(q3);
            //AppAssert(dotProduct == 0, "Dot product test failed.");  // Since q2 and q3 are orthogonal

            //// Test Length and Magnitude
            //AppAssert(q2.Length() == 1 && q2.Magnitude() == 1, "Length and Magnitude test failed.");  // Since q2 is a unit quaternion

            //// Test Normalization
            //auto normalized = q2.Normalized();
            //AppAssert(normalized.w == 0 && normalized.x == 1 && normalized.y == 0 && normalized.z == 0, "Normalization test failed.");  // Since q2 is already a unit quaternion

            //// Test Slerp
            //auto slerped = q1.Slerp(q4, 0.5f);
            //bool slerp_test = std::abs(slerped.w - 0.70710678118) < 0.000001 &&
            //    slerped.x == 0 &&
            //    slerped.y == 0 &&
            //    std::abs(slerped.z - 0.70710678118) < 0.000001;
            //AppAssert(slerp_test, "Slerp test failed.");
            //LogInfo("~Testing Quaternion");
        };

        "Vector"_test = [] {
            expect(true) << "Message";
            //VectorBase<int, 3, VectorAliases::Coordinate> v0 { 1, 2, 3 };
            //VectorBase<int, 3> v1({ 1, 2, 3 });
            //VectorBase<int, 3> v2({ 4, 5, 6 });

            //// Test basic properties
            //AppAssert(v0[0] == 1 && v0[1] == 2 && v0[2] == 3, "Basic properties test failed for v0.");
            //AppAssert(v0.X == 1 && v0.Y == 2 && v0.Z == 3, "XYZ accessors test failed for vo.");

            //// Test arithmetic operations
            //auto sum = v1 + v2;
            //AppAssert(sum[0] == 5 && sum[1] == 7 && sum[2] == 9, "Addition test failed.");
            //auto diff = v2 - v1;
            //AppAssert(diff[0] == 3 && diff[1] == 3 && diff[2] == 3, "Subtraction test failed.");
            //auto prod = v1 * 2;
            //AppAssert(prod[0] == 2 && prod[1] == 4 && prod[2] == 6, "Scalar multiplication test failed.");

            //// Test Dot product
            //int dotProd = v1.Dot(v2);
            //AppAssert(dotProd == 32, "Dot product test failed.");  // 1*4 + 2*5 + 3*6

            //// Test Cross product for 3D vectors
            //auto crossProd = v1.Cross(v2);
            //AppAssert(crossProd[0] == -3 && crossProd[1] == 6 && crossProd[2] == -3, "Cross product test failed.");

            //// Test normalization (will use a 2D vector for easier computation)
            //VectorBase<double, 2> v3({ 3.0, 4.0 }); // A 3-4-5 right triangle
            //auto normalized = v3.Normalize();
            //double length = normalized.Length();
            //AppAssert(length > 0.99 && length < 1.01, "Normalization test failed.");  // Close enough to 1 for floating point precision

            //// Test comparison
            //AppAssert((v1 <=> v2) == std::strong_ordering::less, "Comparison test failed.");

            //// Test string conversion
            ////std::string v1Str = static_cast<std::string>(v1);
            ////AppAssert(v1Str == "[ 1, 2, 3 ]", "String conversion test failed.");

            //// Test Angle
            //VectorBase<double, 2> v4({ 1.0, 0.0 });
            //VectorBase<double, 2> v5({ 0.0, 1.0 });
            //double angle = v4.Angle(v5);
            //AppAssert(angle > 1.56 && angle < 1.58, "Angle test failed.");  // Close to pi/2 or 90 degrees

            //// Test Abs
            //VectorBase<int, 3> v6({ -1, -2, -3 });
            //auto absVec = v6.Abs();
            //AppAssert(absVec[0] == 1 && absVec[1] == 2 && absVec[2] == 3, "Absolute value test failed.");

            //// Test Clamp
            //VectorBase<int, 3> v7 = v1.Clamp(2, 3);
            //AppAssert(v7[0] == 2 && v7[1] == 2 && v7[2] == 3, "Clamp test failed.");

            //// Test Distance
            //double dist = v3.Distance(VectorBase<double, 2>({ 0.0, 0.0 }));
            //AppAssert(dist > 4.99 && dist < 5.01, "Distance test failed.");  // Close to 5

            //// Test Projection
            //auto proj = v4.Projection(v5);
            //AppAssert(proj[0] == 0.0 && proj[1] == 0.0, "Projection test failed.");  // Should be the zero vector

            //// Test Reflection
            //VectorBase<double, 2> v8({ 1.0, 1.0 });
            //auto reflect = v8.Reflection(v4);
            //AppAssert(reflect[0] == -1.0 && reflect[1] == 1.0, "Reflection test failed.");


            //VectorBase<bool, 2> bool2 = { true, false };
            //VectorBase<bool, 3> bool3 = { true, false, true };
            //VectorBase<bool, 4> bool4 = { true, false, true, false };

            //Position3D xyz = { 0.5f, 0.5f, 0.5f };
            //Position4D xyzw = { 0.5f, 0.5f, 0.5f, 0.5f };

            //Direction2D dir2 = { 0.5f, 0.5f };
            //Direction3D dir3 = { 0.5f, 0.5f, 0.5f };

            //Normal2D norm2 = { 0.5f, 0.5f };
            //Normal3D norm3 = { 0.5f, 0.5f, 0.5f };

            //Position2D start { 0.5f, 0.5f };
            //Position3D end { 0.5f, 0.5f, 0.5f };

            //TextureCoord2D uv = { 0.5f, 0.5f };
            //TextureCoord3D uvw = { 0.5f, 0.5f, 0.5f };

            //auto converted = xyzw.ToArray<double>();

            //// Test basic properties
            //AppAssert(bool2 == VectorBase<bool, 2> { true, false }, "Comparision test failed for boolean!");
            //xyzw *= 0.25f * 2;
            //AppAssert(xyzw == Position4D { 0.25f, 0.25f, 0.25f, 0.25f }, "Comparision test failed for Position4D!");

            //auto boom = start / 0;
            //auto boomagain = end / 0.00000000f;

            //LogInfo("Bool1: {}", std::to_string(bool2));
            //LogInfo("Bool2: {}", std::to_string(bool3));
            //LogInfo("Bool3: {}", std::to_string(bool4));
            //LogInfo("Direction2D:{}", std::to_string(dir2));
            //LogInfo("Direction3D:{}", std::to_string(dir3));
            //LogInfo("Normal2D:   {}", std::to_string(norm2));
            //LogInfo("Normal3D:   {}", std::to_string(norm3));
            //LogInfo("Position2D: {}", std::to_string(start));
            //LogInfo("Position3D: {}", std::to_string(end));
            //LogInfo("Position3D:  {}", std::to_string(xyz));
            //LogInfo("Position4D:  {}", std::to_string(xyzw));
            //LogInfo("TextureCoord2D: {}", std::to_string(uv));
            //LogInfo("TextureCoord3D: {}", std::to_string(uvw));


            //LogInfo("~Testing Vector");
        };
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
            //expect(delta.GetSeconds() == 1.0_d);
            //expect(delta.GetMilliseconds() == 1000.0_d);
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
