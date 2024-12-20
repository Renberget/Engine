#pragma once
#include "Vec4.hpp"
#include <array>
#include <span>
#include <cassert>

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
class Mat
{
public:
    constexpr static size_t N = C * R;
    constexpr static bool Square = C == R;

    consteval static Mat<C, R, T> zero();
    consteval static Mat<C, R, T> identity() requires(Square);

    constexpr Mat() = default;
    constexpr Mat(std::initializer_list<T> values);
    constexpr Mat(std::span<const T> values);
    template<arithmetic U>
    constexpr explicit Mat(const Mat<C, R, U>& mat);

    [[nodiscard]] const std::array<T, C * R>& matrix() const;
    [[nodiscard]] T determinant() const requires(Square && C == 1);
    [[nodiscard]] T determinant() const requires(Square && C > 1);

    Mat<C, R, T>& transpose() requires(Square);
    [[nodiscard]] Mat<R, C, T> transposed() const;

    //A determinant of 0 will throw
    Mat<C, R, T>& unsafeInvert() requires(Square);
    //A determinant of 0 will throw
    [[nodiscard]] Mat<C, R, T> unsafeInverse() const requires(Square);
    //A determinant of 0 does nothing
    Mat<C, R, T>& safeInvert() requires(Square);
    //A determinant of 0 will return an identity matrix
    [[nodiscard]] Mat<C, R, T> safeInverse() const requires(Square);

    [[nodiscard]] constexpr T& at(size_t x, size_t y);
    [[nodiscard]] constexpr const T& at(size_t x, size_t y) const;
    [[nodiscard]] constexpr T& operator[](size_t index);
    [[nodiscard]] constexpr const T& operator[](size_t index) const;

    [[nodiscard]] Mat<C, R, T> operator-() const;
    Mat<C, R, T>& operator+=(const Mat<C, R, T>& other);
    Mat<C, R, T>& operator-=(const Mat<C, R, T>& other);
    Mat<C, R, T>& operator*=(const Mat<C, R, T>& other);
    Mat<C, R, T>& operator+=(T value);
    Mat<C, R, T>& operator-=(T value);
    Mat<C, R, T>& operator*=(T value);

private:
    std::array<T, N> mMatrix;
};

#include "Mat.inl"

using Mat2f = Mat<2, 2, float_t>;
using Mat2x3f = Mat<2, 3, float_t>;
using Mat2x4f = Mat<2, 4, float_t>;
using Mat3f = Mat<3, 3, float_t>;
using Mat3x2f = Mat<3, 2, float_t>;
using Mat3x4f = Mat<3, 4, float_t>;
using Mat4f = Mat<4, 4, float_t>;
using Mat4x2f = Mat<4, 2, float_t>;
using Mat4x3f = Mat<4, 3, float_t>;

using Mat2d = Mat<2, 2, double_t>;
using Mat2x3d = Mat<2, 3, double_t>;
using Mat2x4d = Mat<2, 4, double_t>;
using Mat3d = Mat<3, 3, double_t>;
using Mat3x2d = Mat<3, 2, double_t>;
using Mat3x4d = Mat<3, 4, double_t>;
using Mat4d = Mat<4, 4, double_t>;
using Mat4x2d = Mat<4, 2, double_t>;
using Mat4x3d = Mat<4, 3, double_t>;
