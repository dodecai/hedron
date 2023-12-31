#pragma once

// Library
import Vite.Core;
import Vite.Core.Application;
import <Vite/Core/Platform.h>;

///
/// @brief Application EntryPoint
/// @note Can be used only once!
///
extern Vite::Application* Vite::CreateApplication();

// Application Logic
int main(int argc, char** argv) {
	// Preparation
	#ifdef APP_PLATFORM_WINDOWS
		// Switch to UTF-8 codepage
		std::system("chcp 65001 >nul");
	#endif

	// Initialization
	Vite::Arguments arguments({ argv + 1, argv + argc });
	auto app = Vite::CreateApplication();

	// Run
	#ifdef APP_MODE_DEBUG
		//Vite::Debug::Profiler::Start();
	#endif
	app->Run();
	#if APP_MODE_DEBUG
		//Vite::Debug::Profiler::Stop();
	#endif

	// Finalization
	delete app;
	#if APP_MODE_DEBUG
		//Vite::Debug::Memory::DetectLeaks();
	#endif
	return 0;
}
