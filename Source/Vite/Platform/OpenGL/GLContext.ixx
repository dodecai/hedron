export module Vite.Platform.GLContext;

import Vite.Core;
import Vite.Device.GFXContext;

export namespace Hedron {

///
/// @brief OpenGL Context Settings: This type stores the OpenGL context settings.
///
struct ContextSettings {
    bool Compatibility = false;
    ArithmeticProperty<short> AlphaDepth { 0, 8 };
    ArithmeticProperty<short> ColorDepth { 0, 32 };
    ArithmeticProperty<short> DepthBuffer { 0, 24 };
    ArithmeticProperty<short> StencilBuffer { 0, 8 };
    ArithmeticProperty<short> MSAABuffer { 0, 1 };
    ArithmeticProperty<short> MSAASamples { 4, 0, 16 };  // ToDo: Depends on hardware so we need to find a way around the crashing.
    ArithmeticProperty<short> VersionMajor { 4, 0, 9 };
    ArithmeticProperty<short> VersionMinor { 6, 0, 9 };
};

///
/// @brief OpenGL Context: This class is responsible for creating and managing the OpenGL context.
///
class GLContext: public GFXContext {
public:
    /// Default
    GLContext(void *window);
    virtual ~GLContext();

    /// Controls
    void Attach() override;
    void Detach() override;
    void Clear() override;
    void SwapBuffers() override;
    void Viewport(const Size2D &size, const Position2D &position) override;
    void VSync(bool activate) override;

    /// States
    bool const CurrentContext() override;

private:
    /// Casts
    void *AsPlatformHandle() override;

private:
    /// Methods
    bool LoadExtensions();

    /// Properties
    Scope<ContextData> mData;
    bool mLoaded;
};

}
