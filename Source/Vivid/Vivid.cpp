import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;

import Vivid.View.Designer;

namespace Hedron {

// Application
class Vivid: public Application {
public:
    // Default
    Vivid(const Settings &settings): Application(settings) {}
    ~Vivid() {}

    // Methods
	void Create() override {}
	void Destroy() override {}

	void Update([[maybe_unused]] DeltaTime deltaTime) override {
        //Aurora::ShowDemo();
        //Aurora::Update(deltaTime);
        //Aurora::Draw();
    }

private:
};

// Application Entry-Point
Application* CreateApplication() {
	return new Vivid({ "Vivid", "1280x1024" });
}

}
