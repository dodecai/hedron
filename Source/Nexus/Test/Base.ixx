export module Test.Base;

import Vite.Base;
import Vite.App.Layers;

export namespace Hedron::Test {

///
/// @brief Base | Serves all base tests for the Hedron Engine.
///
class Base: public Layer {
public:
    /// Default
    Base() = default;
    ~Base() = default;

    /// Methods
    void Create() override {}
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

private:
    /// Properties
};

}
