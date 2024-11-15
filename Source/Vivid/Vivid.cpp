﻿import <Settings.h>;
import <Vite/EntryPoint.h>;

import Vite;
import Vite.Asset.Manager;
import Vivid.View.Designer;

namespace Hedron {

///
/// @brief Vivid | Designer
/// @detail This project contains the main editor for the Hedron Engine.
///
class Vivid: public Application {
public:
    /// Default
    Vivid(const Settings &settings): Application(settings) {
        AssetManager::Instance().Load();
    }
    ~Vivid() {}

    /// Methods
	void Create() override {}
	void Destroy() override {}
	void Update(DeltaTime deltaTime) override {
        UI::Aurora::ShowDemo();
        UI::Aurora::Update(deltaTime);
        UI::Aurora::Draw();
    }

private:
    /// Properties
};

// Application Entry-Point
Application* CreateApplication() {
	return new Vivid({ "Vivid", "1280x1024" });
}

}
