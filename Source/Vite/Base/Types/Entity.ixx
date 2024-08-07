﻿export module Vite.Type.Entity;

//import <entt/entt.hpp>;

import Vite.Type.Component;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

using EntityID = size_t;

///
/// @brief Entity: Base class for all entities.
///
class Entity {
    /// Types
    using ComponentList = vector<Reference<Component>>;

public:
    /// Default
    Entity(string_view name): mID(std::hash<string_view>{}(name)), mName(name) {};
    virtual ~Entity() = default;

    /// Methods
    void AddComponent(Reference<Component> component) {
        mComponents.push_back(component);
    }
    Reference<Component> GetComponent() {
        return {};
    }
    bool HasComponent() {
        return {};
    }
    void RemoveComponent(Reference<Component> component) {
        mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component), mComponents.end());
    }

private:
    /// Properties
    ComponentList mComponents;
    EntityID mID;
    string mName;
};

}

//class Entity {
//public:
//    Entity() = default;
//    Entity(entt::entity handle, Scene *scene): EntityHandle(handle), pScene(scene) {};
//    ~Entity() = default;
//
//    Entity(const Entity &other) = default;
//
//    template<typename T>
//    bool HasComponent() {
//        //return pScene->Registry.has<T>(EntityHandle);
//        return {};
//    }
//
//    template<typename T, typename... Args>
//    T &AddComponent(Args &&...arguments) {
//        if (HasComponent<T>()) {
//            LogWarning("Entity already has component!");
//            return GetComponent<T>();
//        }
//        T &component = pScene->Registry.emplace<T>(EntityHandle, arguments...);
//        return component;
//    }
//
//    template<typename T>
//    T &GetComponent() {
//        if (!HasComponent<T>()) {
//            LogWarning("The component doesn't exist under entity!");
//        }
//        return pScene->Registry.get<T>(EntityHandle);
//    }
//
//    template<typename T>
//    void RemoveComponent() {
//        if (HasComponent<T>()) pScene->Registry.remove<T>(EntityHandle);
//    }
//
//    template<typename T>
//    void RemoveAllComponent() {
//        //pScene->Registry.remove_all(T)(EntityHandle);
//    }
//
//    operator bool() const { return EntityHandle != entt::null; }
//    operator uint32_t() const { return static_cast<uint32_t>(EntityHandle); }
//
//    bool operator==(const Entity &other) const {
//        return EntityHandle == other.EntityHandle && pScene == other.pScene;
//    }
//    bool operator!=(const Entity &other) const {
//        return !(*this == other);
//    }
//
//    operator entt::entity() const { return EntityHandle; }
//
//    Scene *GetScene() const { return pScene; }
//
//private:
//    Scene *pScene = nullptr;
//    entt::entity EntityHandle = entt::null;
//};
//
//class ScriptableEntity {
//public:
//    ScriptableEntity() = default;
//    virtual ~ScriptableEntity() = default;
//
//    template<typename T>
//    T &GetComponent() {
//        return mEntity.GetComponent<T>();
//    }
//
//protected:
//    virtual void Create() {}
//    virtual void Destroy() {}
//    virtual void Update([[maybe_unused]] Timestamp deltaTime) {}
//
//private:
//    Entity mEntity;
//    friend class Scene;
//};
