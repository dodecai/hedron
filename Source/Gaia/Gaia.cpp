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
    void Create() {}
    void Destroy() {}
    void Update(DeltaTime deltaTime) {
        Exit();
    }

private:
    /// Properties
};

// Application Entry-Point
Application *CreateApplication() {
    return new Gaia({ "Gaia", "1280x1024"});
}

}
