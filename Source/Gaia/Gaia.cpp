import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;

namespace Hedron {

// Application
class Gaia: public Application {
public:
    // Constructors and Destructor
    Gaia() = default;
    ~Gaia() = default;

    // Methods
    void Create() {}
    void Destroy() {}
    void Update([[maybe_unused]] DeltaTime deltaTime) {
        Exit();
    }
};

// Application Entry-Point
Application *CreateApplication() {
    return new Gaia();
}

}
