export module Vite.Type.System;

export namespace Hedron {

///
/// @brief System: Base template for all systems.
///
template <typename Derived>
class System {
public:
    /// Default
    System() = default;
    virtual ~System() = default;

    /// Methods

    // Calls the derived class's Update method
    void Update() {
        static_cast<Derived*>(this)->Update();
    }
};

}
