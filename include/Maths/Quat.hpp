#pragma once
#include "Vec3.hpp"
#include "Maths.hpp"

template<typename T = float, typename = std::enable_if_t<std::is_floating_point_v<T>>>
class Quat
{
public:
    constexpr Quat() : mX(0.0), mY(0.0), mZ(0.0), mW(1.0) {}
    constexpr Quat(T roll, T pitch, T yaw)
    {
        T cosRoll = std::cos(0.5 * roll);
        T sinRoll = std::sin(0.5 * roll);
        T cosPitch = std::cos(0.5 * pitch);
        T sinPitch = std::sin(0.5 * pitch);
        T cosYaw = std::cos(0.5 * yaw);
        T sinYaw = std::sin(0.5 * yaw);

        mW = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
        mX = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
        mY = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
        mZ = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
    }
    constexpr Quat(const Vec3<T>& eulerAngles) : Quat(eulerAngles.x, eulerAngles.y, eulerAngles.z) {}
    [[nodiscard]] Vec3<T> toEuler() const
    {
        T a = 2.0 * (mW * mY - mX * mZ);
        return
        {
            std::atan2(2.0 * (mW * mX + mY * mZ), 2.0 * (mX * mX + mY * mY)),
            2.0 * std::atan2(std::sqrt(1.0 + a), std::sqrt(1.0 - a)) - static_cast<T>(maths::HalfPi),
            std::atan2(2.0 * (mW * mZ + mX * mY), 1.0 - 2.0 * (mY * mY + mZ * mZ))
        };
    }
    [[nodiscard]] T dot(const Quat<T>& other) const
    {
        return mX * other.mX + mY * other.mY + mZ * other.mZ + mW * other.mW;
    }
    Quat& normalize()
    {
        T length = std::sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);
        mX /= length;
        mY /= length;
        mZ /= length;
        mW /= length;
        return *this;
    }
    [[nodiscard]] Quat<T> normalized() const
    {
        Quat<T> result = *this;
        T length = std::sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);
        result.mX /= result;
        result.mY /= result;
        result.mZ /= result;
        result.mW /= result;
        return result;
    }
    [[nodiscard]] bool operator==(const Quat<T>& other) const
    {
        return mX == other.mX && mY == other.mY && mZ == other.mZ && mW == other.mW;
    }
    [[nodiscard]] bool operator!=(const Quat<T>& other) const
    {
        return mX != other.mX || mY != other.mY || mZ != other.mZ || mW != other.mW;
    }

private:
    T mX;
    T mY;
    T mZ;
    T mW;
};