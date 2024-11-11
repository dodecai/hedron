export module Test.Tool;

import Vite.Core;
import Vite.Tools;
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
    void Create() override {
        LogCaption("Tool Tests");
        Test();
    }
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

    /// Tests
    void Test() {}

private:
    /// Properties
};

}
