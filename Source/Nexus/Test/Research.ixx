export module Test.Research;

import Vite;
import Vite.App.Layers;

export namespace Hedron::Test {


class BenchmarkTest: public System<BenchmarkTest> {
public:
    void OnUpdate() {
        for (auto i = 0; i < 100; i++) {
            auto value = i * i;
        }
    }
};


///
/// @brief Research | Serves as an research facility, to test out the latest features for the Hedron Engine.
///
class Research: public Layer {
public:
    /// Default
    Research() = default;
    ~Research() = default;

    /// Methods
    void Create() override {
        Vector1D v1d { 1.0f };
        Vector2D v2d { 1.0f, 2.0f };
        Vector3D v3d { 1.0f, 2.0f, 3.0f };
        Vector4D v4d { 1.0f, 2.0f, 3.0f, 4.0f };
        Vector4D v0d { 1.0f };

        auto v1dSize = sizeof(v1d);
        auto v2dSize = sizeof(v2d);
        auto v3dSize = sizeof(v3d);
        auto v4dSize = sizeof(v4d);

        auto v2multi = v2d * v2d / v2d + v2d - v2d * 2 / 2 + 2 - 2;

        LogTrace("Data: {} | Size: {}", v1d, v1dSize);
        LogTrace("Data: {} | Size: {}", v2d, v2dSize);
        LogTrace("Data: {} | Size: {}", v3d, v3dSize);
        LogTrace("Data: {} | Size: {}", v4d, v4dSize);
        LogInfo("{}", v2multi);

        // Initialize Vector4D from an array and set an array from Vector4D
        array<float, 4> a4d { 1.0f, 2.0f, 3.0f, 4.0f };
        Vector4D v4di { a4d };
        array<float, 4> a4dc = v4di;


        auto v3d2 = v3d + 3;
        auto v3dCross = Cross(v3d, v3d2);

        auto v4d2 = v4d * 4;
        auto v4dDot = Dot(v4d, v4d);
        //auto v4dDistance = Distance(v4d, v4d2);
        auto v4dLength = Length(v4d);
        //auto v4dSquaredDistance = SquaredDistance(v4d, v4d2);
        auto v4dSquaredLength = SquaredLength(v4d);
        //auto v4dNormalized = Normalize(v4d);
        auto v4dAngle = Angle(v4d, v4d2);
        auto v4dAngleDegrees = AngleDegree(v4d, v4d2);
        auto v4dUAngle = UAngle(v4d, v4d2);
        //auto v4dLerp = Lerp(v4d, v4d2, 2.0f);
        //auto v4dNormalizedLerp = NormalizedLerp(v4d, v4d2, 2.0f);
        //auto v4dSphericalLerp = SphericalLerp(v4d, v4d2, 2.0f);


        auto test = true;
        return;
        LogCaption("Research Tests");

        auto displayManager = DisplayManager::Create();


        Test();
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {
        //BenchmarkTest benchCode;
        //benchCode.Update();
        //LogInfo("Benchmark: {:.6f}ms", benchCode.GetDuration());
    }

    /// Tests
    void Test() {
        //Direction2D aDirection2D { 1.0f, 1.0f };
        //Direction3D aDirection3D { 1.0f, 1.0f, 1.0f };
        //Normal2D aNormal2D { 1.0f, 1.0f };
        //Normal3D aNormal3D { 1.0f, 1.0f, 1.0f };
        //Position2D aPosition2D { 1.0f, 1.0f };
        //Position3D aPosition3D { 1.0f, 1.0f, 1.0f };
        //Position4D aPosition4D { 1.0f, 1.0f, 1.0f, 1.0f };
        ////Rotation2D rotation2D { 1.0f };
        //Rotation3D aRotation3D { 1.0f, 1.0f, 1.0f };
        //TextureCoord2D aTextureCoordinate2D { 1.0f, 1.0f };
        //TextureCoord3D aTextureCoordinate3D { 1.0f, 1.0f, 1.0f };
        //
        //Matrix2 bMatrix2x2 { 0.0f, 1.0f, 2.0f, 3.0f };
        //Matrix3 bMatrix3x3 { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
        //Matrix4 bMatrix4x4 { 0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f };
        //
        //Quaternion q0 { 1, 0, 0, 0 };
        //
        //auto size02 = sizeof(Vector2);
        //auto size03 = sizeof(Vector3);
        //auto size04 = sizeof(Vector4);
        //
        //Vector2 vector2 { 1.0f, 2.0f }; //= Vector2::AsZero();
        //Vector3 vector3 { 1.0f, 2.0f, 3.0f };
        //Vector4 vector4 { 1.0f, 2.0f, 3.0f };
        //
        //vector4.X = 4.0f;
        //
        //array<TextureCoord2D, 4> testTextureCoord2D { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f };
        //
        //auto test = true;
        //
        ////auto sizeGlmMat2 = sizeof(glm::mat2);   // 16
        ////auto sizeGlmMat3 = sizeof(glm::mat3);   // 36
        ////auto sizeGlmMat4 = sizeof(glm::mat4);   // 64
        //
        ////auto color1 = VectorBase<float, 3, VectorAliases::Color>();
        ////auto color2 = VectorBase<float, 4, VectorAliases::Color>();
        //
        ////auto sizeA = sizeof(color1);
        ////auto sizeB = sizeof(color2);
        //
        //Ultra::Test::VectorTests();
        //Ultra::Test::MatrixTests();
        //Ultra::Test::QuaternionTests();
    }

private:
    /// Properties
};

}
