export module Vite.Renderer.Viewport;

import Vite.Core;

export namespace Hedron {

///
/// @brief Contains the position and size of a viewport.
///
struct ViewportProperties {
    Position2D Position;
    Size2D Size;
};

///
/// @brief Agnostic Viewport: A region of the screen where the output of the rendering pipeline is displayed.
///
class Viewport {
public:
    /// Default
    Viewport(const ViewportProperties &properties);
    virtual ~Viewport() = default;
    static Scope<Viewport> Create(const ViewportProperties &properties);


    /// Accessors
    float AspectRatio() const {
        return mAspectRatio;
    }
    const ViewportProperties &Properties() const {
        return mProperties;
    }

private:
    /// Properties
    float mAspectRatio {};
    ViewportProperties mProperties {};
};

}
