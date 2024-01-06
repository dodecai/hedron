export module Vite.Asset.Material;


import Vite.Core;

export namespace Hedron {

struct MaterialData {
    //alignas(16) glm::vec3 Ambient { 0.0f };
    //alignas(16) glm::vec3 Diffuse { 0.0f };
    //alignas(16) glm::vec3 Specular { 0.0f };
    //alignas(16) float Shininess = 32.0f;
};

class Material {
public:
    Material() = default;
    ~Material() = default;
};

}
