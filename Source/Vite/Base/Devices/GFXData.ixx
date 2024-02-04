export module Vite.Device.GFXData;

import Vite.Type;

export namespace Hedron {

///
/// @brief Graphics API's [DirectX|OpenGL|Vulkan]
///
enum class GraphicsAPI {
    DirectX,
    OpenGL,
    Vulkan,
};

///
/// @brief ColorBase for color representation
/// @tparam T  Any arithmetic type
///
template<typename T = float>
    requires typename_arithmetic<T>
struct ColorBase {
    T Red {};
    T Green {};
    T Blue {};
    T Alpha {};
};

///
/// @brief MonoColorBase for monochromatic color representation
/// @tparam T  Any arithmetic type
///
template<typename T = float>
    requires typename_arithmetic<T>
struct MonoColorBase {
    T GrayScale {};
    T Alpha {};
};

/// Aliases
using Color = ColorBase<float>;
using MonoColor = MonoColorBase<float>;

}
