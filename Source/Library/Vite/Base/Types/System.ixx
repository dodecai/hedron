export module Vite.Type.System;

export namespace Hedron {

template <typename Derived>
class System {
public:
    System() = default;
    virtual ~System() = default;

    void Update() {
        static_cast<Derived*>(this)->Update();
    }
};

}
