﻿export module Vite.Asset.Mesh;

import Vite.Core;
import Vite.Renderer.CommandBuffer;
import Vite.Renderer.PipelineState;
import Vite.Renderer.Texture;

export namespace Hedron {

constexpr int MaxBoneInfluences = 4;

//struct Vertex {
//    glm::vec3 Position {};
//    glm::vec3 Normal {};
//    glm::vec2 TexCoords {};
//    glm::vec3 Tangent {};
//    glm::vec3 Bitangent {};
//    //int BoneIDs[MaxBoneInfluences] = { 0, 0, 0, 0 };
//    //float Weights[MaxBoneInfluences] = { 0.0f, 0.0f, 0.0f, 0.0f };
//};
//
//struct TextureData {
//    uint32_t ID;
//    string Path;
//    string Type;
//};
//
//using Vertices = vector<Vertex>;
//using Indices = vector<uint32_t>;
//using Textures = vector<Reference<Texture>>;
//using TextureInfo = vector<TextureData>;

//class Mesh {
//public:
//    Mesh(Vertices vertices, Indices indices, Textures textures, TextureInfo info, MaterialData material = {}):
//        mVertices(vertices),
//        mIndices(indices),
//        mTextures(textures),
//        mTextureData(info),
//        mMaterialData(material) {
//        SetupMesh();
//    }
//    ~Mesh() = default;
//
//    void Draw(CommandBuffer *commandBuffer);
//    uint32_t GetIndices() const { return static_cast<uint32_t>(mIndices.size()); }
//
//    MaterialData GetMaterial() const { return mMaterialData; }
//
//private:
//    void SetupMesh() {
//        PipelineProperties properties;
//        properties.BlendMode = BlendMode::Alpha;
//        properties.CullMode = CullMode::None; // ToDo: Enable Culling
//        properties.DepthTest = true;
//        properties.Wireframe = false;
//        properties.Layout = {
//            { ShaderDataType::Float3, "aPosition"  },
//            { ShaderDataType::Float3, "aNormal"    },
//            { ShaderDataType::Float2, "aTexCoords" },
//            { ShaderDataType::Float3, "aTangent"   },
//            { ShaderDataType::Float3, "aBitangent" },
//            //{ ShaderDataType::Int4,   "aBoneIDs"   },
//            //{ ShaderDataType::Float4, "aWeights"   },
//        };
//        mPipeline = PipelineState::Create(properties);
//
//        mVertexBuffer = Buffer::Create(BufferType::Vertex, mVertices.data(), sizeof_vector(mVertices));
//        mIndexBuffer = Buffer::Create(BufferType::Index, mIndices.data(), sizeof_vector(mIndices));
//        mMaterialBuffer = Buffer::Create(BufferType::Uniform, &mMaterialData, sizeof(MaterialData));
//    }
//
//private:
//    Reference<PipelineState> mPipeline;
//    Vertices mVertices;
//    Indices mIndices;
//    Textures mTextures;
//
//    TextureInfo mTextureData;
//    MaterialData mMaterialData;
//
//    Reference<Buffer> mVertexBuffer;
//    Reference<Buffer> mIndexBuffer;
//    Reference<Buffer> mMaterialBuffer;
//};

}

module: private;

namespace Hedron {

//void Mesh::Draw(CommandBuffer *commandBuffer) {
//    mVertexBuffer->Bind();
//    mPipeline->Bind();
//    mIndexBuffer->Bind();
//
//    for (size_t i = 0; i < mTextures.size(); i++) {
//        if (i >= 3) break;
//        mTextures[i]->Bind(static_cast<uint32_t>(i));
//    }
//    if (!mTextures.size()) {
//        mMaterialBuffer->Bind(9);
//        mMaterialBuffer->UpdateData(&mMaterialData, sizeof(MaterialData));
//    }
//    commandBuffer->DrawIndexed(mIndices.size(), PrimitiveType::Triangle, true);
//    mPipeline->Unbind();
//
//    for (size_t i = 0; i < mTextures.size(); i++) {
//        if (i >= 3) break;
//        mTextures[i]->Unbind(static_cast<uint32_t>(i));
//    }
//}

}
