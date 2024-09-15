export module Vite.Platform.WinDisplay;

import Vite.Base;
import Vite.Device.Display;

export namespace Hedron {

class WinDisplay: public Display {
public:
    WinDisplay() = default;
    WinDisplay(string id);
    ~WinDisplay() = default;
};

class WinDisplayManager: public DisplayManager {
public:
    WinDisplayManager();
    ~WinDisplayManager() = default;
};

}
