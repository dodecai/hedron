module Vite.Platform.WinInput;

import <Windows.h>;

namespace Hedron {

/// Commands
void WinInput::UpdatePlatform() {
    for (auto i = 0z; i <= 256; i++) {
        auto pressed = (bool)::GetAsyncKeyState((int)i);
        auto &&currentState = sInputMap[static_cast<KeyCode>(i)].State;
        sInputMap[static_cast<KeyCode>(i)].State =
            currentState == KeyState::Press && pressed ? KeyState::Repeat :
            pressed ? KeyState::Press : KeyState::Release;
    }
}

/// Methods
bool WinInput::GetKeyStatePlatform(KeyCode code) const {
    return sInputMap[static_cast<KeyCode>(code)].State != KeyState::Release;
}

bool WinInput::GetMouseButtonStatePlatform(MouseButton button) const {
    switch (button) {
        case MouseButton::Left:		return sInputMap[static_cast<KeyCode>(VK_LBUTTON)].State != KeyState::Release;
        case MouseButton::Middle:	return sInputMap[static_cast<KeyCode>(VK_MBUTTON)].State != KeyState::Release;
        case MouseButton::Right:	return sInputMap[static_cast<KeyCode>(VK_RBUTTON)].State != KeyState::Release;
        case MouseButton::Extra1:	return sInputMap[static_cast<KeyCode>(VK_XBUTTON1)].State != KeyState::Release;
        case MouseButton::Extra2:	return sInputMap[static_cast<KeyCode>(VK_XBUTTON2)].State != KeyState::Release;
        default:					return false;
    }
}

bool WinInput::GetMouseButtonStateDeltaPlatform(MouseButton button) const {
    switch (button) {
        case MouseButton::Left: {
            static thread_local bool last {};
            auto current = sInputMap[static_cast<KeyCode>(VK_LBUTTON)].State != KeyState::Release;
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Middle: {
            static thread_local bool last {};
            auto current = sInputMap[static_cast<KeyCode>(VK_MBUTTON)].State != KeyState::Release;
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Right: {
            static thread_local bool last {};
            auto current = sInputMap[static_cast<KeyCode>(VK_RBUTTON)].State != KeyState::Release;
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Extra1: {
            static thread_local bool last {};
            auto current = sInputMap[static_cast<KeyCode>(VK_RBUTTON)].State != KeyState::Release;
            if (current != last) {
                last = current;
                return current;
            }
            break;
        }
        case MouseButton::Extra2: {
            static thread_local bool last {};
            auto current = sInputMap[static_cast<KeyCode>(VK_XBUTTON2)].State != KeyState::Release;
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
