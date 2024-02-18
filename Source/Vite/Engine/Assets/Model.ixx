module;

#include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

export module Vite.Asset.Model;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Asset;
import Vite.Asset.Material;
import Vite.Asset.Mesh;
import Vite.Renderer.CommandBuffer;
import Vite.Renderer.Texture;

export namespace Hedron {

using Meshes = vector<Mesh>;

class Model {
public:
    Model(const string &path, bool gamma = false): mGammaCorrection(gamma) {
        Load(path);
    }

    Model(Vertices vertices, Indices indices, const string &texturePath, const TextureProperties &properties = {}, const Components::Material &material = {}) {
        TextureAsset data = {};
        data.Texture = Texture::Create(properties, texturePath);
        data.ID = data.Texture->GetRendererID();
        data.Type = "Simple";
        data.Path = texturePath;

        Mesh mesh(vertices, indices, { data }, material);
        mMeshes.push_back(mesh);
    }

    ~Model() = default;

    void Draw(CommandBuffer *commandBuffer) {
        for (auto &mesh : mMeshes) {
            mesh.Bind();
            commandBuffer->DrawIndexed(mesh.GetIndicesCount(), PrimitiveType::Triangle, true);
            mesh.Unbind();
        }
    }

    const Meshes &GetMeshes() const { return mMeshes; }

    void SetDefaultTexture(const string &path, const TextureProperties &properties = {}) {
        TextureAsset data = {};
        data.Texture = Texture::Create(properties, path);
        data.ID = data.Texture->GetRendererID();
        data.Type = "Simple";
        data.Path = path;

        for (auto &mesh : mMeshes) {
            mesh.SetDefaultTexture({ data });
        }
    }

private:
    void Load(const string &path) {
        //Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);
        //Assimp::LogStream *stderrStream = Assimp::LogStream::createDefaultStream(aiDefaultLogStream_STDERR);
        //Assimp::DefaultLogger::get()->attachStream(stderrStream, Assimp::Logger::NORMAL | Assimp::Logger::DEBUGGING | Assimp::Logger::VERBOSE);

        Assimp::Importer importer;
        const auto *scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast | aiProcess_ConvertToLeftHanded);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
            LogError("Assimp::Importer {}", importer.GetErrorString());
            return;
        }
        mDirectory = File::GetPath(path);
        ProcessNode(scene->mRootNode, scene);

        //Assimp::DefaultLogger::kill();
    }

    void ProcessNode(aiNode *node, const aiScene *scene) {
        for (size_t i = 0; i < node->mNumMeshes; i++) {
            auto *mesh = scene->mMeshes[node->mMeshes[i]];
            mMeshes.push_back(ProcessMesh(mesh, scene));
        }
        for (size_t i = 0; i < node->mNumChildren; i++) {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene) {
        Vertices vertices {};
        Indices indices {};
        Textures textures {};
        Components::Material material {};

        // Vertices
        for (size_t i = 0; i < mesh->mNumVertices; i++) {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = static_cast<float>(mesh->mVertices[i].x);
            vector.y = static_cast<float>(mesh->mVertices[i].y);
            vector.z = static_cast<float>(mesh->mVertices[i].z);
            vertex.Position = vector;

            if (mesh->mNormals) {
                vector.x = static_cast<float>(mesh->mNormals[i].x);
                vector.y = static_cast<float>(mesh->mNormals[i].y);
                vector.z = static_cast<float>(mesh->mNormals[i].z);
                vertex.Normal = vector;
            }

            if (mesh->mTextureCoords[0]) {
                glm::vec2 vec;
                vec.x = static_cast<float>(mesh->mTextureCoords[0][i].x);
                vec.y = static_cast<float>(mesh->mTextureCoords[0][i].y);
                vertex.TexCoords = vec;

                vector.x = static_cast<float>(mesh->mTangents[i].x);
                vector.y = static_cast<float>(mesh->mTangents[i].y);
                vector.z = static_cast<float>(mesh->mTangents[i].z);
                vertex.Tangent = vector;

                vector.x = static_cast<float>(mesh->mBitangents[i].x);
                vector.y = static_cast<float>(mesh->mBitangents[i].y);
                vector.z = static_cast<float>(mesh->mBitangents[i].z);
                vertex.Bitangent = vector;
            } else {
                vertex.TexCoords = { 0.0f, 0.0f };
            }

            vertices.push_back(vertex);
        }

        // Indices
        for (size_t i = 0; i < mesh->mNumFaces; i++) {
            auto &face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; j++) {
                indices.push_back(face.mIndices[j]);
            }
        }

        // Materials
        if (mesh->mMaterialIndex >= 0) {
            auto *current = scene->mMaterials[mesh->mMaterialIndex];

            auto diffuse = LoadMaterialTextures(current, aiTextureType_DIFFUSE, "Diffuse");
            textures.insert(textures.end(), diffuse.begin(), diffuse.end());

            auto normal = LoadMaterialTextures(current, aiTextureType_NORMALS, "Normal");
            textures.insert(textures.end(), normal.begin(), normal.end());

            auto specular = LoadMaterialTextures(current, aiTextureType_SPECULAR, "Specular");
            textures.insert(textures.end(), specular.begin(), specular.end());

            auto height = LoadMaterialTextures(current, aiTextureType_HEIGHT, "Height");
            textures.insert(textures.end(), height.begin(), height.end());

            auto ambient = LoadMaterialTextures(current, aiTextureType_AMBIENT, "Ambient");
            textures.insert(textures.end(), ambient.begin(), ambient.end());
        }
        if (mesh->mMaterialIndex >= 0) {
            material = LoadMaterial(scene->mMaterials[mesh->mMaterialIndex]);
        }

        return Mesh(vertices, indices, textures, material);
    }

    Components::Material LoadMaterial(aiMaterial *material) {
        Components::Material result;
        aiColor3D color(0.0f, 0.0f, 0.0f);
        float shininess;

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        result.Ambient = glm::vec3(color.r, color.g, color.b);

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        result.Diffuse = glm::vec3(color.r, color.g, color.b);

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        result.Specular = glm::vec3(color.r, color.g, color.b);

        material->Get(AI_MATKEY_SHININESS, shininess);
        if (shininess < 0.0f) {
            shininess = 32.0f;
        }
        result.Shininess = shininess;

        return result;
    }

    Textures LoadMaterialTextures(aiMaterial *material, aiTextureType type, string typeName) {
        Textures textures {};

        for (size_t i = 0; i < material->GetTextureCount(type); i++) {
            aiString str;
            material->GetTexture(type, static_cast<unsigned int>(i), &str);
            bool skip = false;
            for (size_t j = 0; j < mTexturesLoaded.size(); j++) {
                if (strcmp(mTexturesLoaded[j].Path.data(), str.C_Str()) == 0) {
                    textures.push_back(mTexturesLoaded[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                string path = mDirectory + '/' + str.C_Str();
                TextureAsset data;
                auto texture = Texture::Create({}, path);
                data.ID = texture->GetRendererID();
                data.Type = typeName;
                data.Path = str.C_Str();
                data.Texture = texture;

                textures.push_back(data);
                mTexturesLoaded.push_back(data);
            }
        }
        return { textures };
    }

private:
    /// Properties
    bool mGammaCorrection;

    /// Data
    string mDirectory;
    Meshes mMeshes;
    Textures mTexturesLoaded {};
};

}
