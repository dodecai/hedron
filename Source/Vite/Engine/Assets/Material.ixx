export module Vite.Asset.Material;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Renderer.Texture;

export namespace Hedron {

///
#pragma region /// Definitions and Types

// MaterialType: An enum that represents the type of material
enum class MaterialType {
    Traditional,
    PBR
};

// MaterialTexture: A struct that holds the data for a texture in a material
struct MaterialTexture {
    string ID;
    string Path;
    string Type;
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
    Material(): mData(Create(T)) {};
    ~Material() = default;

    /// Accessors/Mutators
    template<typename R> requires std::is_base_of_v<MaterialData, R>
    R &Data() {
        if constexpr (T = MaterialType::Traditional) {
            static_assert(std::is_same_v<R, TraditonalMaterialData>, "<Material> Something got very wrong..., this should never happen!");
            return *reinterpret_cast<R *>(mData.get());
        } else if constexpr (T == MaterialType::PBR) {
            static_assert(std::is_same_v<R, PBRMaterialData>, "<Material> Something got very wrong..., this should never happen!");
            return *reinterpret_cast<R *>(mData.get());
        } else {
            static_assert(false, "<Material> The specified material type isn't implemented yet!");
            //throw std::invalid_argument("The specified material type isn't implemented yet!");
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
    MaterialTextures Textures;
};

}
