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
    Ambient         = 0,
    Diffuse         = 1,
    Specular        = 2,
    Emissive        = 3,

    // PBR
    Metalness       = 0,
    Roughness       = 1,
    AO              = 2,
    RefractionIndex = 3,
    Translucency    = 4
};

// MaterialTexture: A struct that holds the data for a texture in a material
struct MaterialTexture {
    string ID;
    string Path;
    MaterialTextureType Type;
    Reference<Texture> Instance;
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
    glm::vec3 Ambient {};   float AmbientWeight {};
    glm::vec3 Diffuse {};   float DiffuseWeight {};
    glm::vec3 Specular {};  float SpecularWeight {};
    glm::vec3 Emissive {};  float EmissiveWeight {};

    float Shininess {};
    float Opacity;

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
class Material {
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
        mMaterialBuffer->Bind(9);
        if constexpr (T == MaterialType::Traditional) {
            mMaterialBuffer->UpdateData(mData.get(), sizeof(TraditonalMaterialData));
        } else if constexpr (T == MaterialType::PBR) {
            mMaterialBuffer->UpdateData(mData.get(), sizeof(PBRMaterialData));
        } else {
            static_assert("The specified material type isn't implemented!");
        }

        for (const auto &texture : mTextures) {
            texture.Instance->Bind(texture.Type);
        }
    }
    void Unbind() const {
        mMaterialBuffer->Unbind();

        for (const auto &texture : mTextures) {
            texture.Instance->Unbind();
        }
    }

private:
    static Scope<MaterialData> Create(MaterialType type) {
        switch (type) {
            case MaterialType::Traditional: return CreateScope<TraditonalMaterialData>();
            case MaterialType::PBR: return CreateScope<PBRMaterialData>();
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
