module;

#include "Vite/Base/Bridges/WinAPI.h"

export module Vite.Platform.WinEvent;

import Vite.Core;
import Vite.Event;

export namespace Hedron {

///
/// @brief WinEvents
/// Source: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644958%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
///
class WinEventHandler: public EventHandler {
public:
    /// Default
    WinEventHandler(void *window);
    virtual ~WinEventHandler();

    /// Events
    virtual bool Callback(void *event) override;
    virtual void Update() override;

private:
    /// Methods
    bool Dispatch(MSG message);
    KeyModifier GetModifiers();

    /// Handles
    RAWINPUTDEVICE mRawInputDevice[1];
    HWND mWindowHandle;
};

}
