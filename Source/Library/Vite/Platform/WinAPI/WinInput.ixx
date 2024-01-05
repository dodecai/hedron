export module Vite.Platform.WinInput;

import Vite.Core;
import Vite.Device.Input;

export namespace Hedron {

class WinInput: public Input {
protected:
    /// Methods
    bool GetKeyStatePlatform(KeyCode code) const override;
    bool GetMouseButtonStatePlatform(MouseButton button) const override;
    bool GetMouseButtonStateDeltaPlatform(MouseButton button) const override;
    pair<float, float> GetMousePositionPlatform() const override;
    pair<float, float> GetMousePositionDeltaPlatform() const override;
    float GetMouseWheelDeltaPlatform() const override;
};

}
