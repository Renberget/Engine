#pragma once
#include "Transform3.hpp"
#include "Transform2.hpp"
#include "Rect.hpp"
#include <algorithm>

namespace math
{
    template<typename T>
    concept vec =
        requires(T value)
    {
        { Vec2{ value } } -> std::same_as<T>;
    } ||
        requires(T value)
    {
        { Vec3{ value } } -> std::same_as<T>;
    } ||
        requires(T value)
    {
        { Vec4{ value } } -> std::same_as<T>;
    };

    template<std::floating_point T>
    [[nodiscard]] T toRadians(T degrees);

    template<std::floating_point T>
    [[nodiscard]] T toDegrees(T radians);

    template<typename T, std::floating_point U>
    [[nodiscard]] T lerp(const T& left, const T& right, U alpha);

    template<std::floating_point T>
    [[nodiscard]] bool nearlyEquals(const T& left, const T& right, const T& tolerance = std::numeric_limits<T>::epsilon());

    template<std::floating_point T> requires(vec<T> || std::is_same_v<T, Quat<T>>)
    [[nodiscard]] bool nearlyEquals(const T& left, const T& right, const T& tolerance = std::numeric_limits<T>::epsilon());

    template<std::floating_point T>
    [[nodiscard]] constexpr Mat<4, 4, T> lookAt(const Vec3<T>& position, const Vec3<T>& origin, const Vec3<T>& up);

    template<std::floating_point T>
    [[nodiscard]] constexpr Mat<4, 4, T> ortho(T left, T right, T top, T bottom, T near, T far);
}

#include "Math.inl"
