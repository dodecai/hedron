export module Vite.Asset.Mesh;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Asset;
import Vite.Asset.Material;
import Vite.Renderer.Buffer;
import Vite.Renderer.CommandBuffer;
import Vite.Renderer.PipelineState;
import Vite.Renderer.Shader;
import Vite.Renderer.Texture;

export namespace Hedron {

struct MeshVertexLayout {
    glm::vec3 Position {};
    glm::vec3 Normal {};
    glm::vec2 TexCoords {};
    glm::vec3 Tangent {};
    glm::vec3 Bitangent {};
};

using MeshVertices = vector<MeshVertexLayout>;
using MeshIndices = vector<uint32>;

struct MeshData {
    MeshVertices Vertices {};
    MeshIndices Indices {};
};

class Mesh {
public:
    Mesh(const MeshData &data):
        mData(data) {
        SetupMesh();
    }
    Mesh(const Mesh &other) {
        mData = other.mData;
        mPipeline = other.mPipeline;
        mVertexBuffer = other.mVertexBuffer;
        mIndexBuffer = other.mIndexBuffer;
    }
    Mesh(Mesh &&other) {
        mData = std::move(other.mData);
        mPipeline = std::move(other.mPipeline);
        mVertexBuffer = std::move(other.mVertexBuffer);
        mIndexBuffer = std::move(other.mIndexBuffer);
    }
    ~Mesh() = default;

    void Bind() {
        mVertexBuffer->Bind();
        mPipeline->Bind();
        mIndexBuffer->Bind();
    }
    void Unbind() {
        mIndexBuffer->Unbind();
        mPipeline->Unbind();
        mVertexBuffer->Unbind();
    }

    uint32 GetIndicesCount() const { return static_cast<uint32>(mData.Indices.size()); }

private:
    void SetupMesh() {
        PipelineProperties properties;
        properties.BlendMode = BlendMode::Alpha;
        properties.CullMode = CullMode::None; // ToDo: Enable Culling
        properties.DepthTest = true;
        properties.Wireframe = false;
        properties.Layout = {
            { ShaderDataType::Float3, "aPosition"  },
            { ShaderDataType::Float3, "aNormal"    },
            { ShaderDataType::Float2, "aTexCoords" },
            { ShaderDataType::Float3, "aTangent"   },
            { ShaderDataType::Float3, "aBitangent" },
        };
        mPipeline = PipelineState::Create(properties);

        mVertexBuffer = Buffer::Create(BufferType::Vertex, mData.Vertices.data(), sizeof_vector(mData.Vertices));
        mIndexBuffer = Buffer::Create(BufferType::Index, mData.Indices.data(), sizeof_vector(mData.Indices));
    }

private:
    /// Data
    MeshData mData;

    /// Instances
    Reference<PipelineState> mPipeline;
    Reference<Buffer> mVertexBuffer;
    Reference<Buffer> mIndexBuffer;
};


class MeshFactory {
protected:
    MeshFactory() = default;
    ~MeshFactory() = default;

public:
    static void CreateCube() {}
    static void CreateSphere() {}
    static void CreatePlane() {}
};

}
