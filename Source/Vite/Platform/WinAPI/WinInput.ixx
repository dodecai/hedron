module;

#include "Vite/Base/Bridges/WinAPI.h"

export module Vite.Platform.WinInput;

import Vite.Core;
import Vite.Device.Input;

export namespace Hedron {

class WinInput: public Input {
protected:
    /// Commands
    void UpdatePlatform() override;

    /// Methods
    bool GetKeyStatePlatform(KeyCode code) const override;
    bool GetMouseButtonStatePlatform(MouseButton button) const override;
    bool GetMouseButtonStateDeltaPlatform(MouseButton button) const override;
    Position2D GetMousePositionPlatform() const override;
    Position2D GetMousePositionDeltaPlatform() const override;
    float GetMouseWheelDeltaPlatform() const override;

private:
    /// Properties
    mutable POINT mLastMousePosition {};
    mutable float mLastMouseWheelDelta {};
};

}
