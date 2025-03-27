export module Vite.MeshRenderer;

import Vite.App;
import Vite.Asset;
import Vite.Asset.Mesh;
import Vite.Asset.Model;
import Vite.Renderer;
import Vite.Renderer.Buffer;
import Vite.Renderer.DesignerCamera;

export namespace Hedron {

struct RenderStatistics {
    uint64 DrawCalls {};
};

class MeshRenderer {
public:
    /// Default
    MeshRenderer() {
        mCommandBuffer = Application::Instance().GetRenderer()->GetCommandBuffer().get();
        mCameraUniformBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(Components::Camera));
        mEntityUniformBuffer = Buffer::Create(BufferType::Uniform, nullptr, sizeof(Components::EntityData));
        mDebugDepthShader = Shader::Create("Assets/Shaders/Debug/DepthVisualizer.glsl");
        mGridShader = Shader::Create("Assets/Shaders/Grid.glsl");
        mModelShader = Shader::Create("Assets/Shaders/Materials/Material.Blinn-Phong.glsl");
        mSkyBoxShader = Shader::Create("Assets/Shaders/SkyBox.glsl");
        mStencilOutlineShader = Shader::Create("Assets/Shaders/Stencil.Outline.glsl");
        mNormalsShader = Shader::Create("Assets/Shaders/Debug/NormalsVisualizer.glsl");
    }
    ~MeshRenderer() = default;

    /// Commands
    void Start(const DesignerCamera &camera) {
        Statistics = RenderStatistics {};

        mCameraData.ViewProjection = camera.GetViewProjection();
        mCameraData.Projection = camera.GetProjectionMatrix();
        mCameraData.View = camera.GetViewMatrix();
        mCameraData.InverseViewProjection = camera.GetInverseViewProjection();
        mCameraData.InverseProjection = camera.GetInverseProjection();
        mCameraData.InverseView = camera.GetInverseView();
        mCameraData.Position = camera.GetPosition();
        mCameraData.Near = camera.GetNearPoint();
        mCameraData.Far = camera.GetFarPoint();
        mCameraUniformBuffer->UpdateData(&mCameraData, sizeof(Components::Camera));
        mCameraUniformBuffer->Bind(0);
        mCameraUniformBuffer->Bind((uint32_t)UniformPosition::CameraData);
    }
    void DrawGrid() {
        // Specify Buffers, Pipeline and Texture
        static Components::Grid grid;
        static PipelineProperties properties {
            .BlendMode = BlendMode::Alpha,
            .DepthTest = true,
            .Wireframe = false,
            .Layout = {
                { ShaderDataType::Float3, "aPosition" }
            },
        };
        static Reference<PipelineState> pipeline = PipelineState::Create(properties);
        static Reference<Buffer> vertexBuffer = Buffer::Create(BufferType::Vertex, &grid.Vertices, sizeof(Components::Grid::Vertices));
        static Reference<Buffer> indexBuffer = Buffer::Create(BufferType::Index, &grid.Indices, sizeof(Components::Grid::Indices));

        // Draw
        vertexBuffer->Bind();
        pipeline->Bind();
        indexBuffer->Bind();
        mGridShader->Bind();
        mCommandBuffer->DrawIndexed(sizeof(grid.Indices), PrimitiveType::Triangle, true);

        Statistics.DrawCalls++;
    }
    void DrawModel(Model model, const Components::Transform transform, bool stencil = false) {
        mCommandBuffer->Record([this, model, transform, stencil]() {
            // Bind Shader
            //mDebugDepthShader->Bind();
            if (stencil) { mStencilOutlineShader->Bind(); } else { mModelShader->Bind(); }

            //if (mMeshes.size() >= mMaxMeshCount) Flush();

            // Update Entity Data
            Components::EntityData entityData;
            entityData.Transform = transform;
            mEntityUniformBuffer->UpdateData(&entityData, sizeof(Components::EntityData));
            mEntityUniformBuffer->Bind((size_t)UniformPosition::EntityData);

            model.Draw(mCommandBuffer);
            //for (auto &mesh : model.GetMeshes()) {
            //    mesh->Bind();
            //    mCommandBuffer->DrawIndexed(mesh->GetIndicesCount(), PrimitiveType::Triangle, true);
            //    mesh->Unbind();
            //}

            // Visualize Normals
            mNormalsShader->Bind();
            //for (auto &mesh : model.GetMeshes()) {
            //    mesh.Bind();
            //    mCommandBuffer->DrawIndexed(mesh.GetIndicesCount(), PrimitiveType::Triangle, true);
            //    mesh.Unbind();
            //}

            Statistics.DrawCalls++;
        });
    }
    void DrawSkybox() {
        mCommandBuffer->Record([this]() {
            // Specify Buffers, Pipeline and Texture
            static Components::Skybox skybox;
            static PipelineProperties properties {
                .DepthTest = true,
                .Wireframe = false,
                .Layout = {
                    { ShaderDataType::Float3, "aPosition" }
                }
            };
            static auto pipeline = PipelineState::Create(properties);
            static TextureProperties skyboxProperties = {
                .Dimension = TextureDimension::TextureCube,
                .SamplerWrap = TextureWrap::Clamp,
            };
            static auto skyboxTexture = Texture::Create(skyboxProperties, "Assets/Textures/Skybox/Sinister");
            static auto vertexBuffer = Buffer::Create(BufferType::Vertex, &skybox.Vertices, sizeof(Components::Skybox::Vertices));
            static auto indexBuffer = Buffer::Create(BufferType::Index, &skybox.Indices, sizeof(Components::Skybox::Indices));

            // Draw
            vertexBuffer->Bind();
            pipeline->Bind();
            indexBuffer->Bind();
            mSkyBoxShader->Bind();
            skyboxTexture->Bind(0);
            mCommandBuffer->DrawIndexed(skybox.Components, PrimitiveType::Triangle, false);

            Statistics.DrawCalls++;
        });
    }
    void Finish() {
        //Flush();
    }
    
    void UpdateStencilBuffer() {
        mCommandBuffer->UpdateStencilBuffer();
    }
    void EnableStencilTest() {
        mCommandBuffer->EnableStencilTest();
    }
    void ResetStencilTest() {
        mCommandBuffer->ResetStencilTest();
    }

    RenderStatistics GetStatistics() { return Statistics; }

private:
    void Flush() {
        for (auto &mesh : mMeshes) {
            for (auto &transform : mTransforms) {
                mModelShader->Bind();


                mesh.Bind();
                mCommandBuffer->DrawIndexed(mesh.GetIndicesCount(), PrimitiveType::Triangle, true);
                mesh.Unbind();
            }
        }
        mCommandBuffer->Execute();
        mMeshes.clear();
        mTransforms.clear();
    }

private:
    /// Data
    RenderStatistics Statistics;
    uint32 mMaxMeshCount = 1024;
    vector<Mesh> mMeshes;
    vector<Components::Transform> mTransforms;

    /// Properties
    Components::Camera mCameraData;

    /// Instances
    //Scope<CommandBuffer> mCommandBuffer;
    CommandBuffer *mCommandBuffer;
    Scope<Buffer> mCameraUniformBuffer;
    Reference<Buffer> mEntityUniformBuffer;
    Reference<Shader> mDebugDepthShader;
    Reference<Shader> mGridShader;
    Reference<Shader> mModelShader;
    Reference<Shader> mNormalsShader;
    Reference<Shader> mSkyBoxShader;
    Reference<Shader> mStencilOutlineShader;
};

}
