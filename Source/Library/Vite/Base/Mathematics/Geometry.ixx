export module Vite.Math.Geometry;

export namespace Hedron {

///
/// @brief Position2D is a simple position 2D in space
/// @tparam T  Any arithmetic type
///
template<typename T = float> requires typename_arithmetic<T>
struct Position2D {
    T X {};
    T Y {};
};

///
/// @brief Size2D is a simple size in 2D space
/// @tparam T  Any arithmetic type
///
template<typename T = float>
struct Size2D {
    T Width {};
    T Height {};
};

}
