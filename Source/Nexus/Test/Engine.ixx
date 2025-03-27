export module Test.Engine;

import Vite.Bridge.GLM;
import Vite;
import Vite.App;
import Vite.Core;
import Vite.Engine;
import Vite.App.Layers;
import Vite.MeshRenderer;
import Vite.SpriteRenderer;
import Vite.UIRenderer;

import Vite.Asset;
import Vite.Asset.Material;
import Vite.Asset.Manager;
import Vite.Asset.Model;
import Vite.Renderer.Buffer;
import Vite.Renderer.DesignerCamera;
import Vite.Renderer.PipelineState;
import Vite.Renderer.Texture;
import Vite.Renderer.Shader;

import Vite.DearImGui.Layer;

// Switches
constexpr auto TEST_MESH_RENDERER = true;
constexpr auto TEST_SPRITE_RENDERER = false;
constexpr auto TEST_UI_RENDERER = false;

export namespace Hedron::Test {


// ToDo
namespace NewAndTasty {
//
//template <typename T, size_t N>
//struct PositionBase {
//    array<T, N> Data = {};
//};
//
//template <typename T = float>
//struct Position2D: PositionBase<T, 2> {
//    [[msvc::no_unique_address]] T &X = this->Data[0];
//};
//
//template <typename T = float>
//struct Position3D: PositionBase<T, 3> {
//};
//
}


///
/// @brief Engine | Serves all engine tests for the Hedron Engine.
///
class Engine: public Layer {
public:
    /// Default
    Engine() {
        // Prepare
        AssetManager::Instance().Load();
        // ToDo: Will not be neccessary in the future
        mCommandBuffer = Application::Instance().GetRenderer()->GetCommandBuffer().get();

        // Setup Camera
        mDesignerCamera = DesignerCamera(45.0f, mAspectRatio, 0.1f, 10000.0f);
        mDesignerCamera.SetViewportSize(1280.0f, 1024.0f);
        mDesignerCamera.SetPosition({ 0.0f, 4.0f, -24.0f });

        // Load Shaders
        mLightShader = Shader::Create("Assets/Shaders/Light.glsl");

        // Load Buffers
        mEntityUniformBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(Components::EntityData));
        mLightBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(Components::Lights));

        mLightData.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    ~Engine() = default;

    /// Methods
    void Create() override {
        LogCaption("Engine Tests");
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {
        // Update Camera
        if (!mUIActive) mDesignerCamera.Update(deltaTime);

        // Mesh Renderer (3D)
        if constexpr (TEST_MESH_RENDERER) {
            mMeshRenderer.Start(mDesignerCamera);
            //mMeshRenderer.DrawGrid();
            DrawLevel(deltaTime);
            mMeshRenderer.DrawSkybox();
            mMeshRenderer.Finish();
        }
    
        // Sprite Renderer (2D)
        if constexpr (TEST_SPRITE_RENDERER) {
            mSpriteRenderer.Start();
            Draw2DLevel(deltaTime);
            mSpriteRenderer.Finish();
        }
    
        // UI Renderer (2D)
        if constexpr (TEST_UI_RENDERER) {
            //mUIRenderer.Start();
            DrawUI(deltaTime);
            //mUIRenderer.Finish();
        }
    }

    void UpdateUI() override {
        ImGui::Begin("Renderer");
        mUIActive = ImGui::IsWindowFocused();
        UI::Property("Color", glm::value_ptr(mLightData.Color));
        UI::Property("Position", "");
        UI::Property("Lights", mEnableLights);
        ImGui::End();

        ImGui::Begin("Statistics");
        UI::Property("Draw Calls: ", "%d", mMeshRenderer.GetStatistics().DrawCalls);
        UI::Property("Lights", "%d", mLights.Count);
        ImGui::End();
    }

    #pragma region Mesh Renderer

    void DrawLevel(DeltaTime deltaTime) {
        static auto tradMaterial = Material<MaterialType::Traditional>();
        static auto pbrMaterial = Material<MaterialType::PBR>();

        // Load Model
        static Model level("Assets/Models/Test/Test.obj");
        static Model cube("Assets/Models/Cube/Cube.obj");
        static Model cube2("Assets/Models/Cube/Cube.obj");
        static Model smiley("Assets/Models/Cube/Cube.obj");
        static Model sphere("Assets/Models/Sphere/SphereUV.obj");
        static Model window("Assets/Models/Cube/Cube.obj");
        static bool once = true;
        if (once) {
            level.SetDefaultTexture("Assets/Textures/Traditional/Debug.png"); // Metal
            cube.SetDefaultTexture("Assets/Textures/Traditional/Debug.png", { .SamplerWrap = TextureWrap::Repeat }); // Concrete
            cube2.SetDefaultTexture("Assets/Textures/Traditional/Debug.png", { .SamplerWrap = TextureWrap::Repeat, .GenerateMips = true, }); // Wood
            smiley.SetDefaultTexture("Assets/Textures/Traditional/Debug.png", { .SamplerWrap = TextureWrap::Clamp }); // Glass
            sphere.SetDefaultTexture("Assets/Textures/Traditional/Debug.png", { .SamplerWrap = TextureWrap::Clamp, .GenerateMips = true, }); // Marble
            window.SetDefaultTexture("Assets/Textures/Traditional/Debug.png", { .SamplerWrap = TextureWrap::Clamp, }); // Glass
            once = false;
        }
        //static Model backpack("Assets/Models/Backpack/Backpack.obj");
        //static Model nanosuit("Assets/Models/Nanosuit/Nanosuit.obj");
        //static Model sponza("Assets/Models/Sponza/Sponza.obj");
        
        // Draw Lights
        DrawLights(deltaTime);

        // Draw Models
        mMeshRenderer.DrawModel(level, { { 0.0f, 0.0f, 0.0f } });
        mMeshRenderer.DrawModel(cube, { { 0.0f, 15.0f, 0.0f } });
        mMeshRenderer.DrawModel(sphere, { { 10.0f, 10.0f, 0.0f } });
        //mMeshRenderer.DrawModel(backpack, { { 7.0f, 2.0f, 9.0f }, { 0.2f, 0.2f, 0.2f } });
        //mMeshRenderer.DrawModel(nanosuit, { { 7.0f, 0.0f, -8.0f }, { 0.2f, 0.2f, 0.2f } });
        //mMeshRenderer.DrawModel(sponza, { { 0.0f, 0.0f, 0.0f }, { 0.1f, 0.1f ,0.1f } });
        
        // Update Objects
        static auto CubeAX = -4.0;
        static auto CubeBX = 0.0;
        static auto CubeCX = 4.0;
        static auto left = true;
        auto direction = 1.0;
        if (CubeAX > -8.0 && left) {
            CubeAX -= direction * deltaTime;
            CubeBX -= direction * deltaTime;
            CubeCX -= direction * deltaTime;
        } else if (CubeAX < -8.0 && left) {
            left = false;
        } else if (CubeCX < 8.0 && !left) {
            CubeAX += direction * deltaTime;
            CubeBX += direction * deltaTime;
            CubeCX += direction * deltaTime;
        } else if (CubeCX > 8.0 && !left) {
            left = true;
        }

        // Draw Objects
        mMeshRenderer.DrawModel(cube2, { { 0.0f, -0.001f, 0.0f }, { 12, 0.1f, -12.0f } });
        mMeshRenderer.DrawModel(cube, { { CubeAX, 10.0f, 0.0f } });
        mMeshRenderer.DrawModel(cube, { { CubeBX, 10.0f, 0.0f }, { 1.0f, 1.0f, 0.2f } });
        mMeshRenderer.DrawModel(cube, { { CubeCX, 10.0f, 0.0f } });
        mMeshRenderer.DrawModel(smiley, { { -5.0f, 1.0f, -8.0f }, { 1.0f, 1.0f, 0.0f } });

        // Note: Alpha Blending requires the objects to be drawn in order from farthest to nearest
        mMeshRenderer.DrawModel(window, { { -1.0f, 1.0f, -8.0f }, { 1.0f, 1.0f, 0.2f } });
        
        mMeshRenderer.UpdateStencilBuffer();
        mMeshRenderer.DrawModel(window, { { 0.0f, 1.0f, -9.0f }, { 1.0f, 1.0f, 0.2f } });
        mMeshRenderer.EnableStencilTest();
        mMeshRenderer.DrawModel(window, { { 0.0f, 1.0f, -9.0f }, { 1.2f, 1.2f, 0.4f } }, true);
        mMeshRenderer.ResetStencilTest();
    }

    // ToDo: Belongs to Scene Renderer
    void DrawLights(DeltaTime deltaTime) {
        if (!mEnableLights) return;
        // Specify Buffers, Pipeline and Texture
        static Components::Cube cube;
        static PipelineProperties properties {
            .DepthTest = true,
            .Wireframe = false,
            .Layout = {
                { ShaderDataType::Float3, "aPosition" }
            },
        };
        static auto pipeline = PipelineState::Create(properties);
        
        // Specify Buffers and Textures
        static auto vertexBuffer = Buffer::Create(BufferType::Vertex, &cube.Vertices, sizeof(Components::Cube::Vertices));
        static auto indexBuffer = Buffer::Create(BufferType::Index, &cube.Indices, sizeof(Components::Cube::Indices));
        
        // Update Entity Data
        mLightPosition = glm::vec3(-3.0f, 3.0f, 0.0f);
        static float timeValue = 0.1f;
        timeValue += (float)deltaTime;
        float angle = timeValue * 2.0f;
        float radius = 5.0f;
        mLightPosition.x = radius * std::cos(angle);
        mLightPosition.z = radius * std::sin(angle);
        
        auto model = glm::translate(glm::mat4(1.0f), mLightPosition) * glm::scale(glm::mat4(4.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        mLightData.Transform = model;
        
        // Lighs
        // - Directional Light
        mLights.Light[0] = {
            .Type = Components::LightType::Directional,
            .LightColor = { 1.0f, 1.0f, 1.0f },
            .LightDirection = { 0.0f, -128.0f, -64.0f },
        };
        // - Point Light
        mLights.Light[1] = {
            .Type = Components::LightType::Point,
            .LightColor = mLightData.Color,
            .LightPosition = mLightPosition,
        
            .Constant = 1.0f,
            .Linear = 0.14f,
            .Quadratic = 0.07f,
        };
        mLights.Light[2] = {
            .Type = Components::LightType::Point,
            .LightColor = mLightData.Color,
            .LightPosition = { 0.0f, 7.0f, 0.0f },

            .Constant = 1.0f,
            .Linear = 0.14f,
            .Quadratic = 0.07f,
        };
        mLights.Light[3] = {
            .Type = Components::LightType::Point,
            .LightColor = { 1.0f, 1.0f, 1.0f },
            .LightPosition = { -8.0f, 3.0f, -9.0f },
        
            .Constant = 1.0f,
            .Linear = 0.14f,
            .Quadratic = 0.07f,
        };
        // - Spot Light
        mLights.Light[4] = {
            .Type = Components::LightType::Spot,
            .LightColor = { 1.0f, 1.0f, 1.0f },
            .LightPosition = mDesignerCamera.GetPosition(),
            .LightDirection = mDesignerCamera.GetForwardDirection(),
        
            .Constant = 1.0f,
            .Linear = 0.14f,
            .Quadratic = 0.07f,
        
            .CutOffAngle = std::cos(glm::radians(12.5f)),
        };
        // - Finish Light
        mLights.Count = 5;
        
        // Draw
        mCommandBuffer->Record([this]() {
            vertexBuffer->Bind();
            pipeline->Bind();
            indexBuffer->Bind();

            mLightShader->Bind();
            mLightBuffer->Bind(6);
            mLightBuffer->UpdateData(&mLights, sizeof(Components::Lights));
            mEntityUniformBuffer->UpdateData(&mLightData, sizeof(Components::EntityData));
            mEntityUniformBuffer->Bind((size_t)UniformPosition::EntityData);

            mCommandBuffer->DrawIndexed(cube.Components, PrimitiveType::Triangle, true);
        });
    }

    #pragma endregion

    #pragma region Sprite Renderer
    
    void Draw2DLevel(DeltaTime deltaTime) {
        //// Prepare
        //Renderer2D::StartScene(mDesignerCamera);
        //
        //// 2D Renderer: Primitives
        //Renderer2D::DrawLine({ -0.9f, -0.9f }, { 0.9f,  -0.9f }, { 0.9f, 0.9f, 0.9f, 1.0f });
        //Renderer2D::DrawLine({ -0.9f, -0.9f }, { -0.9f,   0.9f }, { 1.0f, 0.0f, 1.0f, 1.0f });
        //Renderer2D::DrawLine({ 0.2f,  0.2f }, { 0.7f,   0.7f }, { 1.0f, 1.0f, 1.0f, 1.0f });
        //Renderer2D::DrawQuad({ -0.6f, -0.6f }, { 0.5f,   0.5f }, mCheckerBoard, 1.0f, { 1.0f, 0.0f, 0.0f, 1.0f });
        //Renderer2D::DrawQuad({ 0.2f,  0.2f }, { 0.7f,   0.7f }, mCheckerBoard, 1.0f, { 0.0f, 0.0f, 1.0f, 1.0f });
        //Renderer2D::DrawRect({ -0.9f,  0.9f }, { 0.5f,   0.5f }, { 0.2f, 0.2f, 0.2f, 1.0f });
        //Renderer2D::DrawCircle({ 1.0f, 1.0f }, { 0.5f,   0.5f }, { 1.0f, 0.0f, 1.0f, 1.0f }, 0.1f, 0.1f);
        //
        //static float rotation = 0.0f;
        //const float speed = 180.0f;
        //rotation += speed * deltaTime;
        //if (rotation >= 360.0f) rotation = 0.0f;
        //Renderer2D::DrawRotatedQuad({ 0.7f,   0.7f }, { 0.2f,  0.2f }, rotation * (3.14f / 180.0f), mCheckerBoard, 1.0f, { 0.0f, 1.0f, 0.0f, 1.0f });
        //Renderer2D::DrawRotatedQuad({ 0.7f,  -0.6f }, { 0.4f,  0.4f }, rotation * (3.14f / 180.0f) * -1.0f, mCheckerBoard, 1.0f, { 0.7f, 0.7f, 0.7f, 1.0f });
        //
        //// Finish
        //Renderer2D::FinishScene();
    }

    #pragma endregion

    #pragma region UI Renderer

    void DrawUI(DeltaTime deltaTime) {
        UI::Aurora::ShowDemo();
        UI::Aurora::Update(deltaTime);
        UI::Aurora::Draw();
    }

    #pragma endregion

    #pragma region Miscellanous

    void ToDo() {
        // Model, View, Projection
        //auto orthographic = glm::ortho(0.0f, 1280.0f, 0.0f, 1024.0f, 0.1f, 100.0f);
        //auto model = glm::mat4(1.0f);
        //auto view = glm::mat4(1.0f);
        //auto projection = glm::perspective(glm::radians(flyCamera.Zoom), 1280.0f / 1024.0f, 0.1f, 100.0f);
        //view = flyCamera.GetViewMatrix();
        ////view = glm::translate(view, glm::vec3(-1.0f, 1.0f, -5.0f));
        ////view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        ////view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ////view = glm::lookAt(camera.GetPosition(), camera.GetPosition() + camera.GetForwardDirection(), camera.GetUpDirection());
        
        //// Scale, Rotation and Transformation
        //auto translation = projection * view * model;
        ////glm::mat4 translation = glm::mat4(1.0f);
        ////translation = glm::translate(translation, glm::vec3(0.5f, -0.5f, 0.0f));
        ////translation = glm::rotate(translation, glm::radians(speed), glm::vec3(0.0f, 0.0f, 1.0f));
        ////translation = glm::scale(translation, glm::vec3(0.52f, 0.52f, 0.52f));
        ////view = glm::scale(model, glm::vec3(1.0f, 1.0f, -1.0f)); // Flip Z-Axis (OpenGL is a right-handed system)
    }

    #pragma endregion

    #pragma region /// Events

    void OnAppEvent(const WindowEvent &event) override {
        switch (event.Action) {
            case WindowAction::Resize: {
                mAspectRatio = event.Size.Width / event.Size.Height;
                break;
            }

            default: {
                break;
            }
        }

    }

    #pragma endregion

private:
    /// Properties
    float mAspectRatio = {};
    bool mUIActive = false;
    bool mEnableLights = true;

    /// Objects
    CommandBuffer *mCommandBuffer;
    DesignerCamera mDesignerCamera;
    MeshRenderer mMeshRenderer;
    SpriteRenderer mSpriteRenderer;
    //UIRenderer mUIRenderer;

    // Point Light Position
    glm::vec3 mLightPosition {};

    //// Buffers
    Reference<Buffer> mEntityUniformBuffer;
    Reference<Buffer> mLightBuffer;

    /// Components
    Components::EntityData mLightData;
    Components::Lights mLights;

    /// Shaders
    Reference<Shader> mLightShader;
};

}
