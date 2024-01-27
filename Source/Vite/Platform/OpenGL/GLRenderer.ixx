export module Vite.Platform.GLRenderer;

import Vite.Renderer;

export namespace Hedron {

class GLRenderer: public Renderer {
public:
    /// Default
    GLRenderer();
    virtual ~GLRenderer();
};

}
