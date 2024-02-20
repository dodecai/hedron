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

struct TextureAsset {
    uint32 ID;
    string Path;
    string Type;
    Reference<Texture> Texture;
};

using Textures = vector<TextureAsset>;

class Mesh {
public:
    Mesh(const MeshVertices &vertices, const MeshIndices &indices, const Textures &textures, const Components::Material &material = {}, Reference<Texture> dontKnowWhyButIfRemovedTexturesDontLoadCorrectly = {}):
        mVertices(vertices),
        mIndices(indices),
        mTextures(textures),
        mMaterial(material) {
        SetupMesh();
    }
    ~Mesh() = default;

    void Bind() {
        mVertexBuffer->Bind();
        mPipeline->Bind();
        mIndexBuffer->Bind();

        for (size_t i = 0; i < mTextures.size(); i++) {
            if (i >= 3) break;
            if (mTextures[i].Type == "Simple") {
                mTextures[i].Texture->Bind(0);
                mTextures[i].Texture->Bind(1);
                mTextures[i].Texture->Bind(2);
            } else if (mTextures[i].Type == "Diffuse") {
                mTextures[i].Texture->Bind(0);
                mTextures[i].Texture->Bind(2);
            //} else if(mTextures[i].Type == "Normal") {
            //    mTextures[i].Texture->Bind(0);
            //    mTextures[i].Texture->Bind(2);
            } else if (mTextures[i].Type == "Specular") {
                mTextures[i].Texture->Bind(0);
                mTextures[i].Texture->Bind(2);
            //} else if(mTextures[i].Type == "Height") {
            //    mTextures[i].Texture->Bind(1);
            //} else if(mTextures[i].Type == "Ambient") {
            //    mTextures[i].Texture->Bind(2);
            //} else if(mTextures[i].Type == "Metallic") {
            //    mTextures[i].Texture->Bind(5);
            //} else if(mTextures[i].Type == "Roughness") {
            //    mTextures[i].Texture->Bind(6);
            //} else if(mTextures[i].Type == "AO") {
            //    mTextures[i].Texture->Bind(7);
            } else {
                mMaterialBuffer->Bind(9);
                mMaterialBuffer->UpdateData(&mMaterial, sizeof(Components::Material));
            }
        }
        if (!mTextures.size()) {
            mMaterialBuffer->Bind(9);
            mMaterialBuffer->UpdateData(&mMaterial, sizeof(Components::Material));
        }
    }
    void Unbind() {
        mPipeline->Unbind();

        for (size_t i = 0; i < mTextures.size(); i++) {
            if (i >= 3) break;
            mTextures[i].Texture->Unbind(static_cast<uint32_t>(i));
        }
        mMaterialBuffer->Unbind();
    }

    uint32 GetIndicesCount() const { return static_cast<uint32>(mIndices.size()); }
    Components::Material GetMaterial() const { return mMaterial; }

    void SetDefaultTexture(const Textures &textures) {
        mTextures = textures;
    }

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

        mVertexBuffer = Buffer::Create(BufferType::Vertex, mVertices.data(), sizeof_vector(mVertices));
        mIndexBuffer = Buffer::Create(BufferType::Index, mIndices.data(), sizeof_vector(mIndices));
        mMaterialBuffer = Buffer::Create(BufferType::Uniform, &mMaterial, sizeof(Components::Material));
    }

private:
    /// Data
    MeshVertices mVertices;
    MeshIndices mIndices;
    Textures mTextures;
    Components::Material mMaterial;

    /// Instances
    Reference<PipelineState> mPipeline;
    Reference<Buffer> mVertexBuffer;
    Reference<Buffer> mIndexBuffer;
    Reference<Buffer> mMaterialBuffer;
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
