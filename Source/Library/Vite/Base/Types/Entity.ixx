export module Vite.Type.Entity;

import Vite.Type.Component;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

using EntityID = size;

class Entity {
    // Types
    using ComponentList = vector<Reference<Component>>;

public:
    Entity(string_view name): mID(std::hash<string_view>{}(name)), mName(name) {};
    virtual ~Entity() = default;

    /// Methods

    void AddComponent(Reference<Component> component) {
        mComponents.push_back(component);
    }

    Reference<Component> GetComponent() {
        return {};
    }

    void RemoveComponent(Reference<Component> component) {
        mComponents.erase(std::remove(mComponents.begin(), mComponents.end(), component), mComponents.end());
    }

private:
    // Properties
    ComponentList mComponents;
    EntityID mID;
    string mName;
};

}
