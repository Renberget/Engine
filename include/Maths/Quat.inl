#include "Quat.hpp"
#pragma once

template<std::floating_point T>
constexpr Quat<T>::Quat(const Vec3<T>& eulerAngles)
{
    T halfX = static_cast<T>(0.5) * eulerAngles.x;
    T halfY = static_cast<T>(0.5) * eulerAngles.y;
    T halfZ = static_cast<T>(0.5) * eulerAngles.z;

    T cosX = cos(halfX);
    T sinX = sin(halfX);
    T cosY = cos(halfY);
    T sinY = sin(halfY);
    T cosZ = cos(halfZ);
    T sinZ = sin(halfZ);

    x = sinX * cosY * cosZ - cosX * sinY * sinZ;
    y = cosX * sinY * cosZ + sinX * cosY * sinZ;
    z = cosX * cosY * sinZ - sinX * sinY * cosZ;
    w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

template<std::floating_point T>
constexpr Quat<T>::Quat(const Vec3<T>& axis, T angle)
{
    T halfAngle = static_cast<T>(0.5) * angle;
    T s = sin(halfAngle);

    x = axis.x * s;
    y = axis.y * s;
    z = axis.z * s;
    w = cos(halfAngle);
}

template<std::floating_point T>
constexpr Quat<T>::Quat(const Mat<3, 3, T>& rotationMatrix)
{
    w = sqrt(static_cast<T>(1) + rotationMatrix.at(0, 0) + rotationMatrix.at(1, 1) + rotationMatrix.at(2, 2));
    T w4 = w * static_cast<T>(4);
    x = (rotationMatrix.at(2, 1) - rotationMatrix.at(1, 2)) / w4;
    y = (rotationMatrix.at(0, 2) - rotationMatrix.at(2, 0)) / w4;
    z = (rotationMatrix.at(1, 0) - rotationMatrix.at(0, 1)) / w4;
}

template<std::floating_point T>
Vec3<T> Quat<T>::euler() const
{
    T yy = y * y;
    T a = static_cast<T>(2) * (w * y - x * z);
    return
    {
        atan2(static_cast<T>(2) * (w * x + y * z), static_cast<T>(1) - static_cast<T>(2) * (x * x + yy)),
        static_cast<T>(2) * atan2(sqrt(static_cast<T>(1) + a), sqrt(static_cast<T>(1) - a)) - static_cast<T>(0.5 * std::numbers::pi_v<T>),
        atan2(static_cast<T>(2) * (w * z + x * y), static_cast<T>(1) - static_cast<T>(2) * (yy + z * z))
    };
}

template<std::floating_point T>
Mat<3, 3, T> Quat<T>::rotationMatrix() const
{
    T xx = x * x;
    T yy = y * y;
    T zz = z * z;
    T xy = x * y;
    T zw = z * w;
    T xz = x * z;
    T yw = y * w;
    T yz = y * z;
    T xw = x * w;

    Mat<3, 3, T> matrix;
    matrix[0] = static_cast<T>(1) - static_cast<T>(2) * (yy + zz);
    matrix[1] = static_cast<T>(2) * (xy - zw);
    matrix[2] = static_cast<T>(2) * (xz + yw);
    
    matrix[3] = static_cast<T>(2) * (xy + zw);
    matrix[4] = static_cast<T>(1) - static_cast<T>(2) * (xx + zz);
    matrix[5] = static_cast<T>(2) * (yz - xw);

    matrix[6] = static_cast<T>(2) * (xz - yw);
    matrix[7] = static_cast<T>(2) * (yz + xw);
    matrix[8] = static_cast<T>(1) - static_cast<T>(2) * (xx + yy);
    return matrix;
}

template<std::floating_point T>
T Quat<T>::sqrLength() const
{
    return x * x + y * y + z * z + w * w;
}

template<std::floating_point T>
T Quat<T>::length() const
{
    return std::sqrt(sqrLength());
}

template<std::floating_point T>
T Quat<T>::dot(const Quat<T>& other) const
{
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<std::floating_point T>
Quat<T>& Quat<T>::unsafeNormalize()
{
    T l = length();
    x /= l;
    y /= l;
    z /= l;
    w /= l;
    return *this;
}

template<std::floating_point T>
Quat<T> Quat<T>::unsafeNormalized() const
{
    return *this / length();
}

template<std::floating_point T>
Quat<T>& Quat<T>::safeNormalize()
{
    T l = length();
    if (l != static_cast<T>(0))
    {
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }
    return *this;
}

template<std::floating_point T>
Quat<T> Quat<T>::safeNormalized() const
{
    return Quat<T>(*this).safeNormalize();
}

template<std::floating_point T>
Quat<T>& Quat<T>::unsafeInvert()
{
    return *this = unsafeInverse();
}

template<std::floating_point T>
Quat<T> Quat<T>::unsafeInverse() const
{
    return static_cast<T>(1) / length() * Quat<T>(-x, -y, -z, w);
}

template<std::floating_point T>
Quat<T>& Quat<T>::safeInvert()
{
    T l = length();
    if (isnormal(l))
    {
        x = -x / l;
        y = -y / l;
        z = -z / l;
        w /= l;
    }
    return *this;
}

template<std::floating_point T>
Quat<T> Quat<T>::safeInverse() const
{
    T l = length();
    return isnormal(l) ? static_cast<T>(1) / l * Quat<T>(-x / l, -y / l, -z / l, w / l) : Quat<T>::identity();
}

template<std::floating_point T>
Quat<T> Quat<T>::operator-() const
{
    return { -x, -y, -z, -w };
}

template<std::floating_point T>
Quat<T>& Quat<T>::operator*=(const Quat<T>& other)
{
    *this = *this * other;
    return *this;
}

template<std::floating_point T>
Quat<T>& Quat<T>::operator*=(T factor)
{
    x *= factor;
    y *= factor;
    z *= factor;
    w *= factor;
    return *this;
}

template<std::floating_point T>
[[nodiscard]] Quat<T> operator*(const Quat<T>& left, const Quat<T>& right)
{
    return
    {
        left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
        left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z,
        left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x,
        left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z
    };
}

template<std::floating_point T>
[[nodiscard]] Quat<T> operator*(const Quat<T>& quat, T factor)
{
    return { quat.x * factor, quat.y * factor, quat.z * factor, quat.w * factor };
}

template<std::floating_point T>
[[nodiscard]] Vec3<T> operator*(const Quat<T>& quat, const Vec3<T>& vector)
{
    T tX = static_cast<T>(2) * (quat.y * vector.z - quat.z * vector.y);
    T tY = static_cast<T>(2) * (quat.z * vector.x - quat.x * vector.z);
    T tZ = static_cast<T>(2) * (quat.x * vector.y - quat.y * vector.x);
    return Vec3<T>(
        vector.x + quat.w * tX + quat.y * tZ - quat.z * tY,
        vector.y + quat.w * tY + quat.z * tX - quat.x * tZ,
        vector.z + quat.w * tZ + quat.x * tY - quat.y * tX);
}

template<std::floating_point T>
[[nodiscard]] Quat<T> operator*(T factor, const Quat<T>& quat)
{
    return { quat.x * factor, quat.y * factor, quat.z * factor, quat.w * factor };
}

template<std::floating_point T>
[[nodiscard]] bool operator==(const Quat<T>& left, const Quat<T>& right)
{
    return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

template<std::floating_point T>
[[nodiscard]] bool operator!=(const Quat<T>& left, const Quat<T>& right)
{
    return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
}