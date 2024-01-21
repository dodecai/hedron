export module Vite.Device.Input;

export import Vite.Device.Input.Controller;
export import Vite.Device.Input.Keyboard;
export import Vite.Device.Input.Mouse;
export import Vite.Device.Input.Touch;
import Vite.Math.Geometry;
import Vite.Type;

export namespace Hedron {

///
/// @brief Input | Retrieve real-time input data (per frame).
/// @todo Disable Input when the window is not active
/// example: if (!Application::GetWindow().GetState(WindowState::Active)) return {};
///
class Input {
    /// Friends
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
    [[nodiscard]] static inline bool GetKeyState(KeyCode code) {
        return mCaptureInput ? Instance->GetKeyStatePlatform(code) : bool {};
    }
    [[nodiscard]] static inline bool GetMouseButtonState(MouseButton button) {
        return mCaptureInput ? Instance->GetMouseButtonStatePlatform(button) : bool {};
    }
    [[nodiscard]] static inline bool GetMouseButtonStateDelta(MouseButton button) {
        return mCaptureInput ? Instance->GetMouseButtonStateDeltaPlatform(button) : bool {};
    }
    [[nodiscard]] static inline Position2D GetMousePosition() {
        return mCaptureInput ? Instance->GetMousePositionPlatform() : Position2D {};
    }
    [[nodiscard]] static inline Position2D GetMousePositionDelta() {
        return mCaptureInput ? Instance->GetMousePositionDeltaPlatform() : Position2D {};
    }
    [[nodiscard]] static inline float GetMouseWheelDelta() {
        return mCaptureInput ? Instance->GetMouseWheelDeltaPlatform() : float {};
    }

protected:
    /// Platform Interface
    virtual bool GetKeyStatePlatform(KeyCode code) const = 0;
    virtual bool GetMouseButtonStatePlatform(MouseButton button) const = 0;
    virtual bool GetMouseButtonStateDeltaPlatform(MouseButton button) const = 0;
    virtual Position2D GetMousePositionPlatform() const = 0;
    virtual Position2D GetMousePositionDeltaPlatform() const = 0;
    virtual float GetMouseWheelDeltaPlatform() const = 0;

protected:
    /// Properties
    inline static float sMouseWheelDelta {};

private:
    static inline bool mCaptureInput { true };
    static Scope<Input> Instance;
};

}
