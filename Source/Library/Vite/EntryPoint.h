#pragma once

// Library
import <Vite/Base/Platform/Support.h>;

import Vite.App.Application;
import Vite.Base;
import Vite.Debug.Profiler;
import Vite.Memory;

///
/// @brief Application EntryPoint
/// @note Can be used only once!
///
extern Hedron::Application*Hedron::CreateApplication();

// Application Logic
int main(int argc, char** argv) {
	// Preparation
	#ifdef APP_PLATFORM_WINDOWS
		// Switch to UTF-8 codepage
		std::system("chcp 65001 >nul");
	#endif

	// Initialization
    Hedron::Arguments arguments({ argv + 1, argv + argc });
	auto app = Hedron::CreateApplication();
    app->SetArguments(arguments);

	// Run
	#ifdef APP_MODE_DEBUG
		Hedron::Debug::Profiler::Start("App");
	#endif
	app->Run();
	#if APP_MODE_DEBUG
		Hedron::Debug::Profiler::Stop();
	#endif

	// Finalization
	delete app;
	#if APP_MODE_DEBUG
		Hedron::Debug::Memory::DetectLeaks();
	#endif
	return 0;
}
