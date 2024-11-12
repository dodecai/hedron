export module Vite.Asset.Material;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Renderer.Buffer;
import Vite.Renderer.Texture;

export namespace Hedron {

///
#pragma region /// Definitions and Types

// MaterialType: An enum that represents the type of material
enum class MaterialType {
    Traditional,
    PBR
};

// MaterialTexturesUniformPosition: An enum that represents the position of a texture in a material
enum class MaterialTextureType {
    // Traditional
    Ambient         = 40,
    Diffuse         = 0,
    Specular        = 2,
    Emissive        = 3,

    // PBR
    Metalness       = 0,
    Roughness       = 1,
    AO              = 2,
    RefractionIndex = 3,
    Translucency    = 4,

    // ToDo
    Height          = 20,
    Simple          = 30,
    Normal
};

string to_string(MaterialTextureType type) {
    switch (type) {
        case MaterialTextureType::Ambient: return "Ambient";
        case MaterialTextureType::Diffuse: return "Diffuse";
        case MaterialTextureType::Specular: return "Specular";
        case MaterialTextureType::Emissive: return "Emissive";
        //case MaterialTextureType::Metalness: return "Metalness";
        //case MaterialTextureType::Roughness: return "Roughness";
        //case MaterialTextureType::AO: return "AO";
        //case MaterialTextureType::RefractionIndex: return "RefractionIndex";
        //case MaterialTextureType::Translucency: return "Translucency";
        //case MaterialTextureType::Height: return "Height";
        //case MaterialTextureType::Simple: return "Simple";
        //case MaterialTextureType::Normal: return "Normal";
        default: return "Unknown";
    }
}

// MaterialTexture: A struct that holds the data for a texture in a material
struct MaterialTexture {
    uint32 ID;
    string Path;
    MaterialTextureType Type;
    Reference<Texture> Texture;
};

// MaterialTextures: A vector of MaterialTexture
using MaterialTextures = vector<MaterialTexture>;

///
/// @brief MaterialData is a struct that holds all the data for a material
/// @note This struct is optimized for alignment on the gpu
/// @todo Add texture IDs for more flexibility (ambient, diffuse, specular, emissive)?
///
// Base Material Data
struct MaterialData {
    MaterialType Type;
};

// Traditional Material Data (special layout for all graphics APIs)

struct TraditonalMaterialData: public MaterialData {
    glm::vec3 Ambient {};   float AmbientWeight { 0.75f };
    glm::vec3 Diffuse {};   float DiffuseWeight { 0.75f };
    glm::vec3 Specular {};  float SpecularWeight { 0.75f };
    ////////////////////////////////////////////////////////////////
    alignas(16) float Shininess = 32.0f; // ToDo: Remove this hack after updating the shaders
    ////////////////////////////////////////////////////////////////
    glm::vec3 Emissive {};  float EmissiveWeight { 0.75f };

    //float Shininess { 0.32f };
    float Opacity {};

    uint32 AmbientEnabled: 2;
    uint32 AmbientTextureEnabled: 2;
    uint32 DiffuseEnabled: 2;
    uint32 DiffuseTextureEnabled: 2;
    uint32 SpecularEnabled: 2;
    uint32 SpecularTextureEnabled: 2;
    uint32 EmissiveEnabled: 2;
    uint32 EmissiveTextureEnabled: 2;
};

// PBR Material Data
struct PBRMaterialData: public MaterialData {
    float Metalness;
    float Roughness;
    float AO; // Ambient Occlusion
    
    float RefractionIndex;
    float Translucency;

    uint32 MetalnessEnabled: 2;
    uint32 MetalnessTextureEnabled: 2;
    uint32 RoughnessEnabled: 2;
    uint32 RoughnessTextureEnabled: 2;
    uint32 AOEnabled: 2;
    uint32 AOTextureEnabled: 2;
    uint32 RefractionIndexEnabled: 2;
    uint32 TranslucencyEnabled: 2;
};

#pragma endregion
///

///
/// @brief Material: A class that represents a material, either traditional or PBR
///
template <MaterialType T>
class Material: public MoveableObject {
public:
    /// Default
    Material(): mData(Create(T)) {
        mData->Type = T;
        if constexpr (T == MaterialType::Traditional) {
            mMaterialBuffer = Buffer::Create(BufferType::Uniform, mData.get(), sizeof(TraditonalMaterialData));
        } else if constexpr (T == MaterialType::PBR) {
            mMaterialBuffer = Buffer::Create(BufferType::Uniform, mData.get(), sizeof(PBRMaterialData));
        } else {
            static_assert("The specified material type isn't implemented!");
        }
    };
    Material(Material &&other) {
        mData = std::move(other.mData);
        mTextures = std::move(other.mTextures);
    }
    ~Material() = default;

    /// Accessors/Mutators
    auto &Data() {
        if constexpr (T == MaterialType::Traditional) {
            return *reinterpret_cast<TraditonalMaterialData *>(mData.get());
        } else if constexpr (T == MaterialType::PBR) {
            return *reinterpret_cast<PBRMaterialData *>(mData.get());
        } else {
            static_assert("The specified material type isn't implemented!");
        }
    }
    auto &Textures() { return mTextures; }

    /// Commands
    void Bind() const {
        // ToDo: Rework this with shaders
        for (const auto &texture : mTextures) {
            if (texture.Type == MaterialTextureType::Simple) {
                texture.Texture->Bind(0);
                texture.Texture->Bind(1);
                texture.Texture->Bind(2);
            } else if (texture.Type == MaterialTextureType::Diffuse) {
                texture.Texture->Bind(0);
                texture.Texture->Bind(2);
            } else if (texture.Type == MaterialTextureType::Specular) {
                texture.Texture->Bind(0);
                texture.Texture->Bind(2);
            } else {
                mMaterialBuffer->Bind(9);
                //texture.Texture->Bind(static_cast<uint32>(texture.Type));
            }
        }

        //mMaterialBuffer->Bind(9);
        if constexpr (T == MaterialType::Traditional) {
            mMaterialBuffer->UpdateData(mData.get(), sizeof(TraditonalMaterialData));
        } else if constexpr (T == MaterialType::PBR) {
            mMaterialBuffer->UpdateData(mData.get(), sizeof(PBRMaterialData));
        } else {
            static_assert("The specified material type isn't implemented!");
        }
    }
    void Unbind() const {
        mMaterialBuffer->Unbind();

        for (const auto &texture : mTextures) {
            if (texture.Type == MaterialTextureType::Simple) {
                texture.Texture->Unbind(0);
                texture.Texture->Unbind(1);
                texture.Texture->Unbind(2);
            } else if (texture.Type == MaterialTextureType::Diffuse) {
                texture.Texture->Unbind(0);
                texture.Texture->Unbind(2);
            } else if (texture.Type == MaterialTextureType::Specular) {
                texture.Texture->Unbind(0);
                texture.Texture->Unbind(2);
            } else {
                //texture.Texture->Unbind(static_cast<uint32>(texture.Type));
            }
        }
    }

private:
    /// Factory
    static Scope<MaterialData> Create(MaterialType type) {
        switch (type) {
            case MaterialType::Traditional: { return CreateScope<TraditonalMaterialData>();; }
            case MaterialType::PBR:         { return  CreateScope<PBRMaterialData>(); }
            default: throw std::invalid_argument("The specified material type isn't implemented!");
        }
    }

private:
    /// Data
    Scope<MaterialData> mData;
    MaterialTextures mTextures;

    /// Buffers
    Reference<Buffer> mMaterialBuffer;
};

}
