export module Vite.Device.Display;

import Vite.Math;
import Vite.Type;

export namespace Hedron {

///
/// @brief Display Device Properties
///
struct DisplayProperties {
    string ID;
    float AspectRatio;
    string Resolution;
    Size2DBase<uint32> Size;
};

///
/// @brief Display Device
///
class Display {
public:
    /// Default
    Display() = default;
    virtual ~Display() = default;
    static Scope<Display> Create();

    /// Accessors
    const DisplayProperties &Properties() const { return mProperties; }

private:
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

    /// Accessors
    const DisplayList &Displays() const { return mDisplays; }

private:
    /// Properties
    DisplayList mDisplays;
};

}
