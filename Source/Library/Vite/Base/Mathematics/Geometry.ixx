export module Vite.Math.Geometry;

export namespace Hedron {

template<typename T = float> requires typename_arithmetic<T>
struct Position2DA {
    T X {};
    T Y {};
};

template<typename T = float>
struct Size2DA {
    T Width {};
    T Height {};
};

}
