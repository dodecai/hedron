import <Settings.h>;
import <Vite/EntryPoint.h>;

namespace Vite {

class Vivid: public Application {
public:
    Vivid(const Settings &settings): Application(settings) {}
    ~Vivid() {}

	void Create() override {}
	void Destroy() override {}

	void Update() override {
    }
};

// Application Entry-Point
Application* CreateApplication() {
	return new Vivid({"Vivid", "1280x1024"});
}

}
