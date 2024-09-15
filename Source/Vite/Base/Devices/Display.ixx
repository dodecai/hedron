export module Vite.Device.Display;

import Vite.Device.Device;
import Vite.Math;
import Vite.Type;

export namespace Hedron {

///
/// @brief Display Device Properties
///
struct DisplayProperties: public DeviceProperties {
    float AspectRatio;
    string AspectRatioString;
    float BitsPerPixel;
    float LogicalDPI;
    float Orientation;
    bool Primary;
    float RefreshRate;
    string Resolution;
    Size2D Size;
};

///
/// @brief Display Device
///
class Display {
public:
    /// Default
    Display() = default;
    virtual ~Display() = default;
    static Scope<Display> Create(string id);

    /// Accessors
    const DisplayProperties &Properties() const { return mProperties; }

protected:
    /// Properties
    DisplayProperties mProperties;
};

///
/// @brief Display Device List
///
class DisplayManager {
    /// Types
    using DisplayList = vector<Scope<Display>>;

public:
    /// Default
    DisplayManager() = default;
    virtual ~DisplayManager() = default;
    static Scope<DisplayManager> Create();

    /// Accessors
    const DisplayList &Displays() const { return mDisplays; }

protected:
    /// Properties
    DisplayList mDisplays;
};

}
