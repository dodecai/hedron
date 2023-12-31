import <Settings.h>;
import <Chrono/EntryPoint.h>;

import Vite.Core;

namespace Vite {

class Vivid: public Application {
public:
	void Create() override {}
	void Destroy() override {}
	void Update() override {}
};

// Application Entry-Point
Application* CreateApplication() {
	return new Vivid();
}

}
