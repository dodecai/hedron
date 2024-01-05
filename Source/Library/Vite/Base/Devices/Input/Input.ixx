export module Vite.Device.Input;

export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;

export import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

///
/// @brief Asynchronous Input
/// @todo Disable Input when the window is not active
/// @example
/// if (!Application::GetWindow().GetState(WindowState::Active)) return {};
///
class Input {
    // Friends
    friend class Application;

public:
    /// Default
    Input() = default;
    virtual ~Input() = default;
    static Scope<Input> Create();

private:
    static void Destroy() {
        Instance.reset();
    }

public:
    /// Methods
    [[no_discard]] static inline bool GetKeyState(KeyCode code) {
        return mCaptureInput ? Instance->GetKeyStatePlatform(code) : bool {};
    }
    [[no_discard]] static inline bool GetMouseButtonState(MouseButton button) {
        return mCaptureInput ? Instance->GetMouseButtonStatePlatform(button) : bool {};
    }
    [[no_discard]] static inline bool GetMouseButtonStateDelta(MouseButton button) {
        return mCaptureInput ? Instance->GetMouseButtonStateDeltaPlatform(button) : bool {};
    }
    [[no_discard]] static inline pair<float, float> GetMousePosition() {
        return mCaptureInput ? Instance->GetMousePositionPlatform() : pair<float, float> {};
    }
    [[no_discard]] static inline pair<float, float> GetMousePositionDelta() {
        return mCaptureInput ? Instance->GetMousePositionDeltaPlatform() : pair<float, float> {};
    }
    [[no_discard]] static inline float GetMouseWheelDelta() {
        return mCaptureInput ? Instance->GetMouseWheelDeltaPlatform() : float {};
    }

protected:
    /// Platform
    virtual bool GetKeyStatePlatform(KeyCode code) const = 0;
    virtual bool GetMouseButtonStatePlatform(MouseButton button) const = 0;
    virtual bool GetMouseButtonStateDeltaPlatform(MouseButton button) const = 0;
    virtual pair<float, float> GetMousePositionPlatform() const = 0;
    virtual pair<float, float> GetMousePositionDeltaPlatform() const = 0;
    virtual float GetMouseWheelDeltaPlatform() const = 0;

protected:
    // Properties
    inline static float sMouseWheelDelta {};

private:
    static inline bool mCaptureInput { true };
    static Scope<Input> Instance;
};

}
