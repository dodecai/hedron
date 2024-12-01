export module Vite.Asset;

import Vite.Bridge.GLM;
import Vite.Core;
import Vite.Renderer.Texture;

export namespace Hedron {

enum class AssetType {
    Font,
    Image,
    Model,
    Script,
    Shader,
    Sound,
    Texture,
    Unknown,
};

string to_string(const AssetType &type) {
    switch (type) {
        case AssetType::Font:       return "Font";
        case AssetType::Image:      return "Image";
        case AssetType::Model:      return "Model";
        case AssetType::Script:     return "Script";
        case AssetType::Shader:     return "Shader";
        case AssetType::Sound:      return "Sound";
        case AssetType::Texture:    return "Texture";
        case AssetType::Unknown:    return "Unknown";
        default:                    return "Invalid";
    }
}

struct Asset {
    string ID {};
    string Path {};
};

// ToDo
enum class UniformPosition {
    RendererData    = 0,
    CameraData      = 1,
    SceneData       = 2,
    ScreenData      = 3,
    EntityData      = 4,
    AnimationData   = 5,
    LightData       = 6,
    ShadowData      = 7,
    MaterialData    = 9,
};

namespace Components {

// Miscellanous
struct Camera {
    glm::mat4 ViewProjection = {};
    glm::mat4 Projection = {};
    glm::mat4 View = {};
    glm::mat4 InverseViewProjection = {};
    glm::mat4 InverseProjection = {};
    glm::mat4 InverseView = {};
    glm::vec3 Position {};
    float Near = {};
    float Far = {};
};

struct EntityData {
    glm::vec4 Color = {};
    glm::mat4 Transform = {};
};

struct Grid {
    unsigned int Indices[6] = { 0, 1, 3, 1, 2, 3 };
    float Vertices[12] = {
         1.0f,  1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,
        -1.0f, -1.0f,  0.0f,
        -1.0f,  1.0f,  0.0f,
    };
};

enum class LightType: uint32 {
    Directional = 0,
    Point = 1,
    Spot = 2,
    Flash = 3,
};

struct Light {
    alignas(16) LightType Type = LightType::Directional;
    alignas(16) glm::vec3 LightColor {};
    alignas(16) glm::vec3 LightPosition {};
    alignas(16) glm::vec3 LightDirection {};
    alignas(16) glm::vec3 Ambient { 0.1f, 0.1f, 0.1f };
    alignas(16) glm::vec3 Diffuse { 0.5f, 0.5f, 0.5f };
    alignas(16) glm::vec3 Specular { 1.0f, 1.0f, 1.0f };

    // Attenuation
    float Constant;
    float Linear;
    float Quadratic;

    // Spot Light
    float CutOffAngle;
};

struct Lights {
    Light Light[5] {};
    alignas(16) uint32 Count = 1;
};

struct Material {
    alignas(16) glm::vec3 Ambient { 0.1f };
    alignas(16) glm::vec3 Diffuse { 1.0f };
    alignas(16) glm::vec3 Specular { 0.5f };
    alignas(16) float Shininess = 32.0f;
};

struct Transform {
    glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 Size = { 1.0f, 1.0f, 1.0f };
    glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };

    operator glm::mat4() const {
        return glm::Transform(Position, Size, Rotation);
    }
};

// Shapes
struct Cube {
    int Components = 36;
    unsigned int Indices[36] = {
         0,  1,  2,  2,  3,  0, // Front
         4,  5,  6,  6,  7,  4, // Back
         3,  2,  6,  6,  7,  3, // Top
         0,  1,  5,  5,  4,  0, // Bottom
         0,  3,  7,  7,  4,  0, // Left
         1,  2,  6,  6,  5,  1, // Right
    };
    float Vertices[24] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
    };
};

struct Rectangle {
    int Components = 6;
    unsigned int Indices[6] = {
        0, 1, 3,    // First Triangle
        1, 2, 3,    // Second Triangle
    };
    float Vertices[36] = {
        // Positions                // Colors           // Texture Coords
         0.5f,  0.5f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // Top-Right
         0.5f, -0.5f, 0.0f, 0.0f,   1.0f, 0.0f, 1.0f,   1.0f, 0.0f, // Bottom-Right
        -0.5f, -0.5f, 0.0f, 0.0f,   0.0f, 1.0f, 1.0f,   0.0f, 0.0f, // Bottom-Left
        -0.5f,  0.5f, 0.0f, 1.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f, // Top-Left 
    };
};

struct Skybox {
    int Components = 36;
    unsigned int Indices[36] = {
        0, 1, 2, 2, 3, 0,   // Front
        4, 5, 6, 6, 7, 4,   // Back
        0, 3, 7, 7, 4, 0,   // Left
        1, 2, 6, 6, 5, 1,   // Right
        3, 2, 6, 6, 7, 3,   // Top
        0, 1, 5, 5, 4, 0,   // Bottom
    };
    float Vertices[24] = {
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,

        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
    };
};

struct Triangle {
    int Components = 3;
    unsigned int Indices[3] = {
        0, 1, 2,
    };
    float Vertices[32] = {
        // Positions            // Colors                   // Texture Coords
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,     0.0f, 0.0f,         // Left
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f, 1.0f,     1.0f, 0.0f,         // Right
         0.0f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f, 1.0f,     0.5f, 1.0f,         // Top
    };
    float TexCoords[6] = {
        // Triangle
        0.0f, 0.0f,  // Lower-Left corner  
        1.0f, 0.0f,  // Lower-Right corner
        0.5f, 1.0f   // Top-Center corner
    };
};

}

//namespace Colors {
//    // ToDo: Switch to Vector class
//    //Vector3Df Black { 0.0f, 0.0f, 0.0f };
//    //Vector3Df Blue  { 0.0f, 0.0f, 1.0f };
//    //Vector3Df Coral { 1.0f, 0.5f, 0.31f };
//    //Vector3Df Green { 0.0f, 1.0f, 0.0f };
//    //Vector3Df Red   { 1.0f, 0.0f, 0.0f };
//    //Vector3Df White { 1.0f, 1.0f, 1.0f };
//
//    //glm::vec3 Black { 0.0f, 0.0f, 0.0f };
//    //glm::vec3 Blue  { 0.0f, 0.0f, 1.0f };
//    //glm::vec3 Coral { 1.0f, 0.5f, 0.31f };
//    //glm::vec3 Green { 0.0f, 1.0f, 0.0f };
//    //glm::vec3 Red   { 1.0f, 0.0f, 0.0f };
//    //glm::vec3 White { 1.0f, 1.0f, 1.0f };
//}
//
//struct Light {
//    //glm::vec3 Color { 1.0f };
//    //glm::vec3 AmbientIntensity { 0.1f };
//    //glm::vec3 DiffuseIntensity { 0.5f };
//    //glm::vec3 SpecularIntensity { 1.0f };
//
//    //float Intensity = 1.0f;
//};
//
//struct DirectionalLight: public Light {
//    //glm::vec3 Direction;
//};
//
//struct PointLight: public Light {
//    //glm::vec3 Position;
//
//    //// Attenuation
//    //float Constant = 1.0f;
//    //float Linear = 0.09f;
//    //float Quadratic = 0.032f;
//};
//
//struct SpotLight: public Light {
//    //glm::vec3 Position;
//    //glm::vec3 Direction;
//
//    //// Attenuation
//    //float Constant = 1.0f;
//    //float Linear = 0.09f;
//    //float Quadratic = 0.032f;
//
//    //// Cutoff
//    //float CutOffAngle = glm::cos(glm::radians(12.5f));
//};

}

