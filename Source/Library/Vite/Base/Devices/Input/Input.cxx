﻿module Vite.Device.Input;

import "Vite/Base/Platform/Detection.h";
import Vite.Logger;

#if defined APP_PLATFORM_WINDOWS
    //import Ultra.Platform.WinInput;
#endif

namespace Hedron {

Scope<Input> Input::Instance = Input::Create();

Scope<Input> Input::Create() {
    #if defined APP_PLATFORM_WINDOWS
        //return CreateScope<WinInput>();
        return nullptr;
    #else
        return nullptr;
    #endif
}

bool Input::GetKeyState(KeyCode code) {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetKeyStatePlatform(code);
}

bool Input::GetMouseButtonState(MouseButton button) {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetMouseButtonStatePlatform(button);
}

bool Input::GetMouseButtonStateDelta(MouseButton button) {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetMouseButtonStateDeltaPlatform(button);
}

std::pair<float, float> Input::GetMousePosition() {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetMousePositionPlatform();
}

std::pair<float, float> Input::GetMousePositionDelta() {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetMousePositionDeltaPlatform();
}

float Input::GetMouseWheelDelta() {
    //if (!Application::GetWindow().GetState(WindowState::Active)) return {};
    return Instance->GetMouseWheelDeltaPlatform();
}

}
