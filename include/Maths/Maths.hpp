#pragma once
#include <type_traits>

namespace maths
{
    template<typename T>
    constexpr T Sqrt2 = 1.41421356237309504880;
    template<typename T>
    constexpr T InvSqrt2 = 0.707106781186547524401;
    template<typename T>
    constexpr T Pi = 3.14159265358979323846;
    template<typename T>
    constexpr T HalfPi = 1.57079632679489661923;
    template<typename T>
    constexpr T Tau = 6.28318530717958647692;
    
    template<typename T, typename U>
    [[nodiscard]] T lerp(const T& left, const T& right, U alpha)
    {
        return left * (1.0 - alpha) + (right * alpha);
    }

    template<typename T, typename = std::enable_if_t<std::is_floating_point_v<T>>>
    [[nodiscard]] bool nearlyEquals(const T& left, const T& right, const T& tolerance = std::numeric_limits<T>::epsilon())
    {
        T diff = left - right;
        return -tolerance < diff && diff < tolerance;
    }
}
