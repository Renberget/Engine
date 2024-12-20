#pragma once
#include "Mat.hpp"
#include <numbers>

template<std::floating_point T>
struct Quat
{
    static const Quat<T> Identity;

    [[nodiscard]] consteval static Quat<T> identity()
    {
        return Quat<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    }

    constexpr Quat() = default;
    constexpr Quat(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
    //Makes a quaternion from euler angles
    constexpr Quat(const Vec3<T>& eulerAngles);
    //Makes a quaternion from a normalized axis and an angle
    constexpr explicit Quat(const Vec3<T>& axis, T angle);
    constexpr explicit Quat(const Mat<3, 3, T>& rotationMatrix);
    template<std::floating_point U>
    constexpr explicit Quat(const Quat<U>& other) :
        x(static_cast<T>(other.x)),
        y(static_cast<T>(other.y)),
        z(static_cast<T>(other.z)),
        w(static_cast<T>(other.w))
    {}

    [[nodiscard]] Vec3<T> euler() const;
    [[nodiscard]] Mat<3, 3, T> rotationMatrix() const;
    [[nodiscard]] T sqrLength() const;
    [[nodiscard]] T length() const;
    [[nodiscard]] T dot(const Quat<T>& other) const;

    //A length of 0 will throw
    Quat<T>& unsafeNormalize();
    //A length of 0 will throw
    [[nodiscard]] Quat<T> unsafeNormalized() const;
    //A length of 0 does nothing
    Quat<T>& safeNormalize();
    //A length of 0 is safe
    [[nodiscard]] Quat<T> safeNormalized() const;

    //A length of 0 will throw
    Quat<T>& unsafeInvert();
    //A length of 0 will throw
    [[nodiscard]] Quat<T> unsafeInverse() const;
    //A length of 0 is safe
    Quat<T>& safeInvert();
    //A length of 0 is safe
    [[nodiscard]] Quat<T> safeInverse() const;

    [[nodiscard]] Quat<T> operator-() const;
    Quat<T>& operator*=(const Quat<T>& other);
    Quat<T>& operator*=(T factor);

    T x;
    T y;
    T z;
    T w;
};

#include "Quat.inl"

using Quatf = Quat<float_t>;
using Quadd = Quat<double_t>;
