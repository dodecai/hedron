export module Vite.Core.Application;

import Vite.Core;
export import Vite.Core.Arguments;

int main(int, char**);

export namespace Vite {

class Application {
	// Friends
	friend int ::main(int, char**);

	// Instance
	static inline Application* pInstance = nullptr;

public:
	// Default
	Application() {
		pInstance = this;
	}
	virtual ~Application() {
		pInstance = nullptr;
	}

	// Accessors
	static Application& Instance() { return *pInstance; }

	// Methods
	virtual void Create() {};
	virtual void Destroy() {};
	virtual void Update() {};

private:
	// Methods
	void Run() {
		Create();
		Update();
		Destroy();
	};
};

// Symbol for Application Entry-Point
Application* CreateApplication();

}
