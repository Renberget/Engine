#pragma once

namespace math
{
    template<std::floating_point T>
    T toRadians(T degrees)
    {
        constexpr T factor = static_cast<T>(std::numbers::pi / 180.0);
        return degrees * factor;
    }

    template<std::floating_point T>
    T toDegrees(T radians)
    {
        constexpr T factor = static_cast<T>(180.0 / std::numbers::pi);
        return radians * factor;
    }

    template<typename T, std::floating_point U>
    T lerp(const T& left, const T& right, U alpha)
    {
        return left * (static_cast<U>(1) - alpha) + (right * alpha);
    }

    template<std::floating_point T>
    bool nearlyEquals(const T& left, const T& right, const T& tolerance)
    {
        const T diff = left - right;
        return -tolerance < diff && diff < tolerance;
    }

    template<std::floating_point T> requires(vec<T> || std::is_same_v<T, Quat<T>>)
        bool nearlyEquals(const T& left, const T& right, const T& tolerance)
    {
        const T sqrLength = (left - right).sqrLength();
        return sqrLength < tolerance * tolerance;
    }

    template<std::floating_point T>
    constexpr Mat<4, 4, T> lookAt(const Vec3<T>& position, const Vec3<T>& origin, const Vec3<T>& up)
    {
        Mat<4, 4, T> mat = Mat<4, 4, T>::identity();

        const Vec3<T> f = (origin - position).unsafeNormalize();
        const Vec3<T> s = f.cross(up).unsafeNormalize();
        const Vec3<T> u = s.cross(f);

        mat.at(0, 0) = s.x;
        mat.at(1, 0) = s.y;
        mat.at(2, 0) = s.z;

        mat.at(0, 1) = up.x;
        mat.at(1, 1) = up.y;
        mat.at(2, 1) = up.z;

        mat.at(0, 2) = -f.x;
        mat.at(1, 2) = -f.y;
        mat.at(2, 2) = -f.z;

        mat.at(3, 0) = -s.dot(position);
        mat.at(3, 1) = -u.dot(position);
        mat.at(3, 2) = f.dot(position);
        return mat;
    }

    template<std::floating_point T>
    constexpr Mat<4, 4, T> ortho(T left, T right, T top, T bottom, T near, T far)
    {
        Mat<4, 4, T> mat = Mat<4, 4, T>::identity();

        const T rightMinusLeft = right - left;
        const T topMinusBottom = top - bottom;
        const T farMinusNear = far - near;

        mat.at(0, 0) = static_cast<T>(2) / rightMinusLeft;
        mat.at(1, 1) = static_cast<T>(2) / topMinusBottom;
        mat.at(2, 2) = static_cast<T>(-2) / farMinusNear;
        mat.at(0, 3) = -(right + left) / rightMinusLeft;
        mat.at(1, 3) = -(top + bottom) / topMinusBottom;
        mat.at(2, 3) = -(far + near) / farMinusNear;
        return mat;
    }
}