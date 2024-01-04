﻿export module Vite.Serializer;

import Vite.Base;

//#include <yaml-cpp/yaml.h>

namespace YAML {

//template<>
//struct convert<glm::vec2> {
//    static bool decode(const Node &node, glm::vec2 &rhs) {
//        if (!node.IsSequence() || node.size() != 2) return false;
//
//        rhs.x = node[0].as<float>();
//        rhs.y = node[1].as<float>();
//        return true;
//    }
//
//    static Node encode(const glm::vec2 &rhs) {
//        Node node;
//        node.push_back(rhs.x);
//        node.push_back(rhs.y);
//        return node;
//    }
//};
//
//template<>
//struct convert<glm::vec3> {
//    static bool decode(const Node &node, glm::vec3 &rhs) {
//        if (!node.IsSequence() || node.size() != 3) return false;
//
//        rhs.x = node[0].as<float>();
//        rhs.y = node[1].as<float>();
//        rhs.z = node[2].as<float>();
//        return true;
//    }
//
//    static Node encode(const glm::vec3 &rhs) {
//        Node node;
//        node.push_back(rhs.x);
//        node.push_back(rhs.y);
//        node.push_back(rhs.z);
//        return node;
//    }
//};
//
//template<>
//struct convert<glm::vec4> {
//    static bool decode(const Node &node, glm::vec4 &rhs) {
//        if (!node.IsSequence() || node.size() != 4) return false;
//
//        rhs.x = node[0].as<float>();
//        rhs.y = node[1].as<float>();
//        rhs.z = node[2].as<float>();
//        rhs.w = node[3].as<float>();
//        return true;
//    }
//
//    static Node encode(const glm::vec4 &rhs) {
//        Node node;
//        node.push_back(rhs.x);
//        node.push_back(rhs.y);
//        node.push_back(rhs.z);
//        node.push_back(rhs.w);
//        return node;
//    }
//};
//
//template<>
//struct convert<glm::quat> {
//    static bool decode(const Node &node, glm::quat &rhs) {
//        if (!node.IsSequence() || node.size() != 4) return false;
//
//        rhs.w = node[0].as<float>();
//        rhs.x = node[1].as<float>();
//        rhs.y = node[2].as<float>();
//        rhs.z = node[3].as<float>();
//        return true;
//    }
//
//    static Node encode(const glm::quat &rhs) {
//        Node node;
//        node.push_back(rhs.w);
//        node.push_back(rhs.x);
//        node.push_back(rhs.y);
//        node.push_back(rhs.z);
//        return node;
//    }
//};

}

namespace Hedron {

//YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec2 &v) {
//    out << YAML::Flow;
//    out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
//    return out;
//}
//
//YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec3 &v) {
//    out << YAML::Flow;
//    out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
//    return out;
//}
//
//YAML::Emitter &operator<<(YAML::Emitter &out, const glm::vec4 &v) {
//    out << YAML::Flow;
//    out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
//    return out;
//}
//
//YAML::Emitter &operator<<(YAML::Emitter &out, const glm::quat &v) {
//    out << YAML::Flow;
//    out << YAML::BeginSeq << v.w << v.x << v.y << v.z << YAML::EndSeq;
//    return out;
//}
//
//static void SerializeEntity(YAML::Emitter &out, Entity entity) {
//    string uuid = entity.GetComponent<Component::Identifier>();
//    out << YAML::BeginMap;
//    out << YAML::Key << "Entity" << YAML::Value << uuid;
//
//    if (entity.HasComponent<Component::Tag>()) {
//        string &tag = entity.GetComponent<Component::Tag>();
//
//        out << YAML::Key << "Component::Tag" << YAML::Value << tag;
//    }
//
//    if (entity.HasComponent<Component::Transform>()) {
//        auto &transform = entity.GetComponent<Component::Transform>();
//        //auto [position, rotation, scale] = GetTransformDecomposition(transform);
//        //glm::vec3 scale;
//        //glm::vec3 translation;
//        //glm::vec3 skew;
//        //glm::vec4 perspective;
//        //glm::quat orientation;
//        //glm::decompose(transform, scale, orientation, translation, skew, perspective);
//
//        out << YAML::Key << "Component::Transform";
//        out << YAML::BeginMap;
//
//        out << YAML::Key << "Position" << YAML::Value << transform.Position;
//        out << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
//        out << YAML::Key << "Scale" << YAML::Value << transform.Scale;
//
//        out << YAML::EndMap;
//    }
//
//    if (entity.HasComponent<Component::Camera>()) {
//        auto &camera = entity.GetComponent<Component::Camera>();
//
//        out << YAML::Key << "Component::Camera";
//        out << YAML::BeginMap;
//
//        out << YAML::Key << "Data";
//        out << YAML::Flow;
//        out << YAML::BeginSeq;
//        if (camera.ProjectionType == SceneCamera::ProjectionType::Perspective) {
//            out << camera.mCamera.GetPerspectiveVerticalFOV();
//        } else {
//            out << camera.mCamera.GetOrthographicSize();
//        }
//        out << camera.mCamera.GetFarClip();
//        out << camera.mCamera.GetNearClip();
//        out << YAML::EndSeq;
//
//
//        out << YAML::Key << "Primary" << YAML::Value << camera.Primary;
//        out << YAML::Key << "FixedAspectRatio" << YAML::Value << camera.FixedAspectRatio;
//        out << YAML::Key << "ProjectionType" << YAML::Value << (uint32_t)camera.ProjectionType;
//
//        out << YAML::EndMap;
//    }
//
//    if (entity.HasComponent<Component::Sound>()) {
//        string &source = entity.GetComponent<Component::Sound>();
//
//        out << YAML::Key << "Component::Sound";
//        out << YAML::BeginMap;
//
//        out << YAML::Key << "Source" << YAML::Value << source;
//
//        out << YAML::EndMap;
//    }
//
//    if (entity.HasComponent<Component::Sprite>()) {
//        auto &sprite = entity.GetComponent<Component::Sprite>();
//
//        out << YAML::Key << "Component::Sprite";
//        out << YAML::BeginMap;
//
//        out << YAML::Key << "Color" << YAML::Value << sprite.Color;
//
//        out << YAML::EndMap;
//    }
//
//    out << YAML::EndMap;
//}
}
export namespace Hedron {

class Serializer {
public:
    //Serializer(const Reference<Scene> &scene): mScene(scene) {}
    ~Serializer() = default;

    void Serialize([[maybe_unused]] const string &path) {
        //YAML::Emitter out;
        //out << YAML::BeginMap;
        //out << YAML::Key << "Scene" << YAML::Value << mScene->GetCaption();
        //out << YAML::Key << "Entities" << YAML::Value;
        //out << YAML::BeginSeq;

        //mScene->Registry.each([&](auto id) {
        //    Entity entity = { id, mScene.get() };
        //    if (!entity || !entity.HasComponent<Component::Identifier>()) return;
        //    SerializeEntity(out, entity);
        //});

        //out << YAML::EndSeq;
        //out << YAML::EndMap;

        //ofstream file(path);
        //file << out.c_str();
    }

    bool Deserialize([[maybe_unused]] const string &path) {
        //string file = ReadFile(path);

        //YAML::Node data = YAML::Load(file);
        //if (!data["Scene"]) return false;

        //string name = data["Scene"].as<string>();

        //auto entities = data["Entities"];
        //if (entities) {
        //    for (auto entity : entities) {
        //        UUID<string> id = entity["Entity"].as<string>();
        //        Entity deserializedEntity = mScene->CreateEntity(id);

        //        if (auto tag = entity["Component::Tag"]) {
        //            auto &component = deserializedEntity.AddComponent<Component::Tag>();
        //            component = tag.as<string>();
        //        }

        //        if (auto transform = entity["Component::Transform"]) {
        //            auto &component = deserializedEntity.AddComponent<Component::Transform>();
        //            glm::vec3 position = transform["Position"].as<glm::vec3>();
        //            glm::vec3 rotation = transform["Rotation"].as<glm::vec3>();
        //            glm::vec3 scale = transform["Scale"].as<glm::vec3>();

        //            component.Position = position;
        //            component.Rotation = rotation;
        //            component.Scale = scale;
        //        }

        //        if (auto camera = entity["Component::Camera"]) {
        //            auto &component = deserializedEntity.AddComponent<Component::Camera>();
        //            component.Primary = camera["Primary"].as<bool>();
        //            component.FixedAspectRatio = camera["FixedAspectRatio"].as<bool>();
        //            component.ProjectionType = (SceneCamera::ProjectionType)camera["ProjectionType"].as<uint32_t>();
        //            component = (SceneCamera::ProjectionType)camera["ProjectionType"].as<uint32_t>();

        //            auto data = camera["Data"].as<vector<float>>();

        //            if (component.ProjectionType == SceneCamera::ProjectionType::Perspective) {
        //                component.mCamera.SetPerspectiveVerticalFOV(data[0]);
        //            } else {
        //                component.mCamera.SetOrthographicSize(data[0]);
        //            }
        //            component.mCamera.SetFarClip(data[1]);
        //            component.mCamera.SetNearClip(data[2]);
        //        }

        //        if (auto sound = entity["Component::Sound"]) {
        //            auto &component = deserializedEntity.AddComponent<Component::Sound>();
        //            component = sound["Source"].as<string>();
        //        }

        //        if (auto sprite = entity["Component::Sprite"]) {
        //            auto &component = deserializedEntity.AddComponent<Component::Sprite>();
        //            component.Color = sprite["Color"].as<glm::vec4>();
        //        }

        //    }
        //}
        return true;
    }

private:
    //Reference<Scene> mScene;
};

}
