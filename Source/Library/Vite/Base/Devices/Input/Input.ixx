export module Vite.Device.Input;

import Vite.Device.Input.Controller;
import Vite.Device.Input.Keyboard;
import Vite.Device.Input.Mouse;
import Vite.Device.Input.Touch;
import Vite.Type.SmartPointer;
import Vite.Type.Standard;

export namespace Hedron {

class Input {
public:
    /// Default
    virtual ~Input() {}
    static Scope<Input> Create();

    /// Methods
    static bool GetKeyState(KeyCode code);
    static bool GetMouseButtonState(MouseButton button);
    static bool GetMouseButtonStateDelta(MouseButton button);
    static std::pair<float, float> GetMousePosition();
    static std::pair<float, float> GetMousePositionDelta();
    static float GetMouseWheelDelta();

protected:
    /// Platform
    virtual bool GetKeyStatePlatform(KeyCode code) const = 0;
    virtual bool GetMouseButtonStatePlatform(MouseButton button) const = 0;
    virtual bool GetMouseButtonStateDeltaPlatform(MouseButton button) const = 0;
    virtual std::pair<float, float> GetMousePositionPlatform() const = 0;
    virtual std::pair<float, float> GetMousePositionDeltaPlatform() const = 0;
    virtual float GetMouseWheelDeltaPlatform() const = 0;

public:
    // Properties
    inline static float sMouseWheelDelta {};

private:
    static Scope<Input> Instance;
};

}
