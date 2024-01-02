import <Settings.h>;
import <Vite/EntryPoint.h>;

namespace Vite {

class Test: public Application {
public:
    Test() {}
    ~Test() {}

    void Create() override {}
	void Destroy() override {}

	void Update() override {
	}
};

// Application Entry-Point
Application* CreateApplication() {
	return new Test();
}

}
