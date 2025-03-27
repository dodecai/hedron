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
import Vite.Renderer.PipelineState;
import Vite.Renderer.Texture;

export namespace Hedron {

using MaterialID = size_t;
using Meshes = vector<Reference<Mesh>>;

struct ModelData {
    Reference<Material<MaterialType::Traditional>> Material;
    Meshes Meshes;
};

using ModelTable = unordered_map<MaterialID, ModelData>;

class Model {
public:
    /// Default
    Model(const string &path) {
        Load(path);
    }
    ~Model() = default;

    void Draw(CommandBuffer *buffer) const {
        for (auto &[id, object] : mModelTable) {
            object.Material->Bind();
            for (auto &&mesh : object.Meshes) {
                mesh->Bind();
                buffer->DrawIndexed(mesh->GetIndicesCount(), PrimitiveType::Triangle, true);
                mesh->Unbind();
            }
            object.Material->Unbind();
        }
    }
    void SetDefaultTexture(const string &path, const TextureProperties &properties = {}) {
        MaterialTexture data = {};
        data.Texture = Texture::Create(properties, path);
        data.ID = data.Texture->GetRendererID();
        data.Type = MaterialTextureType::Simple;
        data.Path = path;

        for (auto &[id, object] : mModelTable) {
            object.Material->Textures().push_back(data);
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
        ProcessScene(scene);

        //Assimp::DefaultLogger::kill();
    }

    void ProcessScene(const aiScene *scene) {
        mModelTable.reserve(scene->mNumMaterials);

        function<void(const aiScene *, aiNode *)> processNode;
        processNode = [&](const aiScene *scene, aiNode *node) {
            for (size_t i = 0; i < node->mNumMeshes; i++) {
                auto *mesh = scene->mMeshes[node->mMeshes[i]];
                if (mModelTable.find(mesh->mMaterialIndex) == mModelTable.end()) {
                    mModelTable[mesh->mMaterialIndex].Material = ProcessMaterialData(scene, mesh);
                    auto data = mModelTable[mesh->mMaterialIndex].Material->Data();
                }
                mModelTable[mesh->mMaterialIndex].Meshes.push_back(ProcessMeshData(scene, mesh));
            }
            for (size_t i = 0; i < node->mNumChildren; i++) {
                processNode(scene, node->mChildren[i]);
            }
        };

        processNode(scene, scene->mRootNode);
    }

    Reference<Mesh> ProcessMeshData(const aiScene *scene, aiMesh *mesh) {
        MeshData data {};

        // Mesh
        for (size_t i = 0; i < mesh->mNumVertices; i++) {
            MeshVertexLayout vertex;
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
            }

            data.Vertices.push_back(vertex);
        }
        for (size_t i = 0; i < mesh->mNumFaces; i++) {
            auto &face = mesh->mFaces[i];
            for (size_t j = 0; j < face.mNumIndices; j++) {
                data.Indices.push_back(face.mIndices[j]);
            }
        }

        return CreateReference<Mesh>(data);
    }

    Reference<Material<MaterialType::Traditional>> ProcessMaterialData(const aiScene *scene, aiMesh *mesh) {
        auto materialRef = CreateReference<Material<MaterialType::Traditional>>();

        // Materials
        if (mesh->mMaterialIndex >= 0) {
            auto *current = scene->mMaterials[mesh->mMaterialIndex];

            auto ambient = LoadMaterialTextures(current, aiTextureType_AMBIENT, MaterialTextureType::Ambient);
            materialRef->Textures().insert(materialRef->Textures().end(), ambient.begin(), ambient.end());
            materialRef->Data().AmbientTextureEnabled = ambient.size() > 0 ? true : false;

            auto diffuse = LoadMaterialTextures(current, aiTextureType_DIFFUSE, MaterialTextureType::Diffuse);
            materialRef->Textures().insert(materialRef->Textures().end(), diffuse.begin(), diffuse.end());
            materialRef->Data().DiffuseTextureEnabled = diffuse.size() > 0 ? true : false;

            auto specular = LoadMaterialTextures(current, aiTextureType_SPECULAR, MaterialTextureType::Specular);
            materialRef->Textures().insert(materialRef->Textures().end(), specular.begin(), specular.end());
            materialRef->Data().SpecularTextureEnabled = specular.size() > 0 ? true : false;



            auto height = LoadMaterialTextures(current, aiTextureType_HEIGHT, MaterialTextureType::Height);
            materialRef->Textures().insert(materialRef->Textures().end(), height.begin(), height.end());
            //materialRef->Data().HeightTextureEnabled = true;

            auto normal = LoadMaterialTextures(current, aiTextureType_NORMALS, MaterialTextureType::Normal);
            materialRef->Textures().insert(materialRef->Textures().end(), normal.begin(), normal.end());
            //materialRef->Data().NormalTextureEnabled = true;
        }
        if (mesh->mMaterialIndex >= 0) {
            materialRef->Data() = LoadMaterialData(scene->mMaterials[mesh->mMaterialIndex]).Data();
            auto data = materialRef->Data();
        }

        return materialRef;
    }

    Material<MaterialType::Traditional> LoadMaterialData(aiMaterial *material) {
        Material<MaterialType::Traditional> result;
        auto &&data = result.Data();
        aiColor3D color {};
        float shininess {};

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        data.Ambient = glm::vec3(color.r, color.g, color.b);
        data.AmbientEnabled = color.IsBlack() ? false : true;

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        data.Diffuse = glm::vec3(color.r, color.g, color.b);
        data.DiffuseEnabled = color.IsBlack() ? false : true;

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        data.Specular = glm::vec3(color.r, color.g, color.b);
        data.SpecularEnabled = color.IsBlack() ? false : true;

        material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
        data.Emissive = glm::vec3(color.r, color.g, color.b);
        data.EmissiveEnabled = color.IsBlack() ? false : true;

        material->Get(AI_MATKEY_SHININESS, shininess);
        data.Shininess = shininess;

        return result;
    }

    MaterialTextures LoadMaterialTextures(aiMaterial *material, aiTextureType aiType, MaterialTextureType type) {
        MaterialTextures textures {};

        for (size_t i = 0; i < material->GetTextureCount(aiType); i++) {
            aiString str;
            material->GetTexture(aiType, static_cast<unsigned int>(i), &str);
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
                MaterialTexture data;
                auto texture = Texture::Create({}, path);
                data.ID = texture->GetRendererID();
                data.Type = type;
                data.Path = str.C_Str();
                data.Texture = texture;

                textures.push_back(data);
                mTexturesLoaded.push_back(data);
            }
        }
        return { textures };
    }

private:
    /// Data
    string mDirectory;
    ModelTable mModelTable;
    MaterialTextures mTexturesLoaded {};
};

}
