export module Test.Tool;

import Vite.Core;
import Vite.Tool;
import Vite.App.Layers;

export namespace Hedron::Test {

///
/// @brief Tool | Serves all tool tests for the Hedron Engine.
///
class Tool: public Layer {
public:
    /// Default
    Tool() = default;
    ~Tool() = default;

    /// Methods
    void Create() override {}
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

private:
    /// Properties
};

}
