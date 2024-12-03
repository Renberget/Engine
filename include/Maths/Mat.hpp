#pragma once
#include "Vec4.hpp"
#include <array>
#include <initializer_list>
#include <assert.h>

template<size_t C, size_t R, Arithmetic T = float>
class Mat
{
public: 
    template<typename = std::enable_if_t<C == R>>
    constexpr static Mat<C, R, T> Identity()
    {
        Mat<C, R, T> identity;
        for (size_t y = 0; y < R; ++y)
        {
            for (size_t x = 0; x < C; ++x)
            {
                if (x == y)
                {
                    identity.get(x, y) = static_cast<T>(1);
                }
            }
        }
        return identity;
    }

    constexpr Mat() = default;
    constexpr Mat(std::initializer_list<T> matrix)
    {
        assert(mMatrix.size() == matrix.size());
        for (size_t i = 0; i < mMatrix.size(); ++i)
        {
            mMatrix[i] = *(matrix.begin() + i);
        }
    }
    T& operator[](size_t index)
    {
        assert(index < C * R);
        return mMatrix[index];
    }
    const T& operator[](size_t index) const
    {
        assert(index < C * R);
        return mMatrix[index];
    }
    T& get(size_t x, size_t y)
    {
        assert(x < C);
        assert(y < R);
        return mMatrix[y * C + x];
    }
    const T& get(size_t x, size_t y) const
    {
        assert(x < C);
        assert(y < R);
        return mMatrix[y * C + x];
    }
    Mat<C, R, T> operator+(const Mat<C, R, T>& other) const
    {
        Mat<C, R, T> result;
        for (size_t i = 0; i < mMatrix.size(); ++i)
            result[i] = mMatrix[i] + other.mMatrix[i];
        return result;
    }
    Mat<C, R, T>& operator+=(const Mat<C, R, T>& other)
    {
        for (size_t i = 0; i < mMatrix.size(); ++i)
            mMatrix[i] += other.mMatrix[i];
        return *this;
    }
    Mat<C, R, T> operator-(const Mat<C, R, T>& other) const
    {
        Mat<C, R, T> result;
        for (size_t i = 0; i < mMatrix.size(); ++i)
            result[i] = mMatrix[i] - other.mMatrix[i];
        return result;
    }
    Mat<C, R, T>& operator-=(const Mat<C, R, T>& other)
    {
        for (size_t i = 0; i < mMatrix.size(); ++i)
            mMatrix[i] -= other.mMatrix[i];
        return *this;
    }
    template<size_t C2>
    Mat<C2, C, T> operator*(const Mat<C2, C, T>& other) const
    {
        Mat<C2, C, T> result;
        size_t i = 0;
        for (size_t y = 0; y < C; ++y)
        {
            for (size_t x = 0; x < C2; ++x)
            {
                for (size_t k = 0; k < C; ++k)
                {
                    result[i] += get(k, y) * other.get(x, k);
                }
                ++i;
            }
        }
        return result;
    }
    template<typename = std::enable_if_t<C == 2 && std::is_standard_layout_v<T>>>
    Vec2<T> operator*(const Vec2<T>& other) const
    {
        Mat<1, C, T> result = (*this) * (*reinterpret_cast<const Mat<1, C, T>*>(&other));
        return *reinterpret_cast<Vec2<T>*>(&result);
    }
    template<typename = std::enable_if_t<C == 3 && std::is_standard_layout_v<T>>>
    Vec3<T> operator*(const Vec3<T>& other) const
    {
        Mat<1, C, T> result = (*this) * (*reinterpret_cast<const Mat<1, C, T>*>(&other));
        return *reinterpret_cast<Vec3<T>*>(&result);
    }
    template<typename = std::enable_if_t<C == 4 && std::is_standard_layout_v<T>>>
    Vec4<T> operator*(const Vec4<T>& other) const
    {
        Mat<1, C, T> result = (*this) * (*reinterpret_cast<const Mat<1, C, T>*>(&other));
        return *reinterpret_cast<Vec4<T>*>(&result);
    }
    bool operator==(const Mat<C, R, T>& other)
    {
        return mMatrix == other.mMatrix;
    }
    bool operator!=(const Mat<C, R, T>& other)
    {
        return mMatrix != other.mMatrix;
    }
    const T* matrix() const
    {
        return mMatrix.data();
    }

private:
    std::array<T, C * R> mMatrix = {};
};

using Mat2 = Mat<2, 2>;
using Mat2x3 = Mat<2, 3>;
using Mat2x4 = Mat<2, 4>;
using Mat3 = Mat<3, 3>;
using Mat3x2 = Mat<3, 2>;
using Mat3x4 = Mat<3, 4>;
using Mat4 = Mat<4, 4>;
using Mat4x2 = Mat<4, 2>;
using Mat4x3 = Mat<4, 3>;