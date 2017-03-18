#pragma once

namespace io
{

/*BEGIN*/

template <typename T>
class Math
{
public:
    static const T almost_zero;
    static const T pi;
    static const T two_pi;
    static const T pi_over_two;
    static const T pi_over_four;
    static const T deg_to_rad;
    static const T rad_to_deg;
    static const T e;

    static T to_radians(const T degrees)
    {
        return degrees * deg_to_rad;
    }

    static T to_degrees(const T radians)
    {
        return radians * rad_to_deg;
    }

    static T round(const T value)
    {
        return value > 0.0 ? std::floor(value + static_cast<T>(0.5)) : std::ceil(value - static_cast<T>(0.5));
    }

    static bool is_zero(const T value, const T epsilon = almost_zero)
    {
        return std::abs(value) <= epsilon;
    }

    static bool is_positive(const T value, const T epsilon = almost_zero)
    {
        return value > epsilon;
    }

    static bool is_negative(const T value, const T epsilon = almost_zero)
    {
        return value < -epsilon;
    }

    static bool is_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return std::abs(x1 - x2) < epsilon;
    }

    static bool is_greater_than(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return x1 > (x2 + epsilon);
    }

    static bool is_less_than(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return x1 < (x2 - epsilon);
    }

    static bool is_greater_than_or_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return !is_less_than(x1, x2, epsilon);
    }

    static bool is_less_than_or_equal(const T x1, const T x2, const T epsilon = almost_zero)
    {
        return !is_greater_than(x1, x2, epsilon);
    }
};

template <typename T> const T Math<T>::almost_zero = static_cast<T>(0.001);
template <typename T> const T Math<T>::pi = static_cast<T>(3.141592653589793);
template <typename T> const T Math<T>::two_pi = static_cast<T>(2.0) * pi;
template <typename T> const T Math<T>::pi_over_two = pi / static_cast<T>(2.0);
template <typename T> const T Math<T>::pi_over_four = pi / static_cast<T>(4.0);
template <typename T> const T Math<T>::deg_to_rad = pi / static_cast<T>(180.0);
template <typename T> const T Math<T>::rad_to_deg = static_cast<T>(180.0) / pi;
template <typename T> const T Math<T>::e = static_cast<T>(2.718281828459045);

/*END*/

} // namespace io