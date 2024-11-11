import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;

namespace Hedron {

///
/// @brief Gaia | Example Game
/// @note This project is used to showcase the Hedron Engine.
///
class Gaia: public Application {
public:
    /// Default
    Gaia(const Settings &settings): Application(settings) {}
    ~Gaia() {}

    /// Methods
    void Create() override {}
    void Destroy() override {}
    void Update(DeltaTime deltaTime) override {}

private:
    /// Properties
};

// Application Entry-Point
Application *CreateApplication() {
    return new Gaia({ "Gaia", "1280x1024" });
}

}
