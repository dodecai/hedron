export module Vite.Platform.GLViewport;

import Vite.Renderer.Viewport;

export namespace Hedron {

class GLViewport: public Viewport {
public:
    /// Default
    GLViewport(const ViewportProperties &properties);
    ~GLViewport();
};

}
