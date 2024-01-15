export module Vite.Math.Geometry;

import Vite.Type;

export namespace Hedron {

///
/// @brief Position2D is a simple position 2D in space
/// @tparam T  Any arithmetic type
///
template<typename T = float>
    requires typename_arithmetic<T>
struct Position2DBase {
    T X {};
    T Y {};
};

/// Aliases
using Position2D = Position2DBase<float>;

///
/// @brief Size2D is a simple size in 2D space
/// @tparam T  Any arithmetic type
///
template<typename T = float>
    requires typename_arithmetic<T>
struct Size2DBase {
    T Width {};
    T Height {};
};

/// Aliases
using Size2D = Size2DBase<float>;

}
