module Vite.Platform.WinInput;

import <Windows.h>;

namespace Hedron {

// Methods
bool WinInput::GetKeyStatePlatform(KeyCode code) const {
    return (bool)::GetAsyncKeyState((int)code);
}

bool WinInput::GetMouseButtonStatePlatform(MouseButton button) const {
    switch (button) {
        case MouseButton::Left:		return (bool)::GetAsyncKeyState((int)VK_LBUTTON);
        case MouseButton::Middle:	return (bool)::GetAsyncKeyState((int)VK_MBUTTON);
        case MouseButton::Right:	return (bool)::GetAsyncKeyState((int)VK_RBUTTON);
        case MouseButton::Extra1:	return (bool)::GetAsyncKeyState((int)VK_XBUTTON1);
        case MouseButton::Extra2:	return (bool)::GetAsyncKeyState((int)VK_XBUTTON2);
        default:					return false;
    }
}

bool WinInput::GetMouseButtonStateDeltaPlatform(MouseButton button) const {
    switch (button) {
        case MouseButton::Left: {
            static thread_local bool last {};
            auto current = (bool)::GetAsyncKeyState((int)VK_LBUTTON);
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Middle: {
            static thread_local bool last {};
            auto current = (bool)::GetAsyncKeyState((int)VK_MBUTTON);
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Right: {
            static thread_local bool last {};
            auto current = (bool)::GetAsyncKeyState((int)VK_RBUTTON);
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Extra1: {
            static thread_local bool last {};
            auto current = (bool)::GetAsyncKeyState((int)VK_XBUTTON1);
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Extra2: {
            static thread_local bool last {};
            auto current = (bool)::GetAsyncKeyState((int)VK_XBUTTON2);
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
    }
    return false;
}

Position2D WinInput::GetMousePositionPlatform() const {
    auto active = GetActiveWindow();

    POINT current {};
    GetCursorPos(&current);
    ScreenToClient(active, &current);

    mLastMousePosition = current;
    return { static_cast<float>(current.x), static_cast<float>(current.y) };
}

Position2D WinInput::GetMousePositionDeltaPlatform() const {
    auto active = GetActiveWindow();

    POINT current {};
    GetCursorPos(&current);
    ScreenToClient(active, &current);

    current.x -= mLastMousePosition.x;
    current.y -= mLastMousePosition.y;

    return { static_cast<float>(current.x), static_cast<float>(current.y) };
}

float WinInput::GetMouseWheelDeltaPlatform() const {
    float delta {};
    delta = mLastMouseWheelDelta;
    mLastMouseWheelDelta = 0.0f;
    return delta;
}

}
