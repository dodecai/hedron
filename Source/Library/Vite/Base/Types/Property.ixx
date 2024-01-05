export module Vite.Type.Property;

import std;
import Vite.Type.Concepts;

export namespace Hedron {

///
/// @brief Property: Built-In Getter and Setter for <any> type
/// 
/// @example
/// Property<size_t> Size { 0, [this](const size_t &value) {
///    return value > 1000 ? 0 : value;
/// }};
///
template <typename T>
class Property {
    // Types
    using Setter = std::function<T(const T &)>;

public:
    /// Default
    Property(): mValue(T()), mSetter(nullptr) {}
    Property(T value, const Setter &setter = nullptr): mValue(value), mSetter(setter) {}
    
    /// Casts
    operator T () { return mValue; }
    operator T const &() const { return mValue; }

    /// Operators
    Property<T> &operator=(const T &value) {
        mValue = mSetter ? mSetter(value) : value;
        return *this;
    }

private:
    // Properties
    T mValue;
    Setter mSetter;
};

///
/// @brief Property: Built-In Getter and Setter for <arithmetic> types with clamping 'from # to # in steps #' feature
/// 
/// @example
/// ArithmeticProperty<short> VersionMajor { 2, 0, 100, 2 };
/// VersionMajor++;
///
template <typename_arithmetic T>
class ArithmeticProperty {
public:
    /// Default
    // Predefined values {0}
    ArithmeticProperty() = default;
    // Define min and max (value = max)
    ArithmeticProperty(T min, T max): Value {max}, Minimum {min}, Maximum {max} {};
    // Define value, min and max
    ArithmeticProperty(T value, T min, T max): Value {value}, Minimum {min}, Maximum {max} {};

    /// Casts
    operator T const &() const { return Value; }

    /// Operators
    T &operator=(const T &value) {
        if (!Minimum && !Maximum) {
            return Value;
        } else {
            return Value = std::clamp(value, Minimum, Maximum);
        }
    };
    ArithmeticProperty &operator++() {
        Value = std::min(Value + Step, Maximum);
        return *this;
    }
    ArithmeticProperty operator++(int) {
        ArithmeticProperty temp = *this;
        ++(*this);
        return temp;
    }
    ArithmeticProperty &operator--() {
        Value = std::max(Value - Step, Minimum);
        return *this;
    }
    ArithmeticProperty operator--(int) {
        ArithmeticProperty temp = *this;
        --(*this);
        return temp;
    }

private:
    // Properties
    T Value {};
    T Minimum {};
    T Maximum {};
    T Step = {};
};

}
