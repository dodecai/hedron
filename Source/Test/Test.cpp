import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite.Core;

namespace Vite {

class Test: public Application {
public:
	void Create() override {
		string greeting = "Hello, World!";
		size_t greetinghash = "Hello, World!"_hash;
		std::cout << greeting << " " << greetinghash << std::endl;
	}

	void Destroy() override {
	}

	void Update() override {
	}
};

// Application Entry-Point
Application* CreateApplication() {
	return new Test();
}

}
