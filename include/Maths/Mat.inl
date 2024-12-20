#pragma once

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
consteval Mat<C, R, T> Mat<C, R, T>::zero()
{
    Mat<C, R, T> matrix;
    matrix.mMatrix = { 0 };
    return matrix;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
consteval Mat<C, R, T> Mat<C, R, T>::identity() requires(Square)
{
    Mat<C, R, T> identity;
    for (size_t y = 0; y < R; ++y)
    {
        for (size_t x = 0; x < C; ++x)
        {
            identity.at(x, y) = static_cast<T>(x == y);
        }
    }
    return identity;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr Mat<C, R, T>::Mat(std::initializer_list<T> values)
{
    assert(values.size() == N);
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] = values.begin()[i];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr Mat<C, R, T>::Mat(std::span<const T> values)
{
    assert(values.size() == N);
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] = values[i];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
template<arithmetic U>
constexpr Mat<C, R, T>::Mat(const Mat<C, R, U>& mat)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] = static_cast<T>(mat[i]);
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
const std::array<T, C * R>& Mat<C, R, T>::matrix() const
{
    return mMatrix;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
T Mat<C, R, T>::determinant() const requires(Square && C == 1)
{
    return mMatrix[0];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
T Mat<C, R, T>::determinant() const requires(Square && C > 1)
{
    T det = 0;
    T sign = 1;
    for (size_t y = 0; y < R; ++y)
    {
        Mat<C - 1, R - 1, T> subMat;
        for (size_t subY = 0; subY < R - 1; ++subY)
        {
            for (size_t subX = 0; subX < C - 1; ++subX)
                subMat.at(subX, subY) = at(subX + 1, subY + static_cast<size_t>(subY >= y));
        }
        det += sign * mMatrix[y * C] * subMat.determinant();
        sign = -sign;
    }
    return det;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::transpose() requires(Square)
{
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < y; ++x)
        {
            std::swap(at(x, y), at(y, x));
        }
    }
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<R, C, T> Mat<C, R, T>::transposed() const
{
    Mat<R, C, T> mat;
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < R; ++x)
        {
            mat.at(y, x) = at(x, y);
        }
    }
    return mat;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::unsafeInvert() requires(Square)
{
    *this = unsafeInverse();
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> Mat<C, R, T>::unsafeInverse() const requires(Square)
{
    Mat<R, C, T> mat;
    T det = 0;
    T sign = 1;
    //First row with determinant
    for (size_t y = 0; y < C; ++y)
    {
        Mat<C - 1, R - 1, T> subMat;
        for (size_t subY = 0; subY < R - 1; ++subY)
        {
            for (size_t subX = 0; subX < C - 1; ++subX)
                subMat.at(subX, subY) = at(subX + 1, subY + static_cast<size_t>(subY >= y));
        }
        mat.at(y, 0) = sign * subMat.determinant();
        det += mMatrix[y * C] * mat.at(y, 0);
        sign = -sign;
    }
    //Other rows
    for (size_t x = 1; x < R; ++x)
    {
        for (size_t y = 0; y < C; ++y)
        {
            Mat<C - 1, R - 1, T> subMat;
            for (size_t subY = 0; subY < R - 1; ++subY)
            {
                for (size_t subX = 0; subX < C - 1; ++subX)
                    subMat.at(subX, subY) = at(subX + static_cast<size_t>(subX >= x), subY + static_cast<size_t>(subY >= y));
            }
            mat.at(y, x) = sign * subMat.determinant();
            sign = -sign;
        }
    }
    return static_cast<T>(1) / det * mat;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::safeInvert() requires(Square)
{
    Mat<C, R, T> mat;
    T det = 0;
    T sign = 1;
    //First row with determinant
    for (size_t y = 0; y < C; ++y)
    {
        Mat<C - 1, R - 1, T> subMat;
        for (size_t subY = 0; subY < R - 1; ++subY)
        {
            for (size_t subX = 0; subX < C - 1; ++subX)
                subMat.at(subX, subY) = at(subX + 1, subY + static_cast<size_t>(subY >= y));
        }
        mat.at(y, 0) = sign * subMat.determinant();
        det += mMatrix[y * C] * mat.at(y, 0);
        sign = -sign;
    }
    if (isnormal(det))
    {
        //Other rows
        for (size_t x = 1; x < R; ++x)
        {
            for (size_t y = 0; y < C; ++y)
            {
                Mat<C - 1, R - 1, T> subMat;
                for (size_t subY = 0; subY < R - 1; ++subY)
                {
                    for (size_t subX = 0; subX < C - 1; ++subX)
                        subMat.at(subX, subY) = at(subX + static_cast<size_t>(subX >= x), subY + static_cast<size_t>(subY >= y));
                }
                mat.at(y, x) = sign * subMat.determinant();
                sign = -sign;
            }
        }
        *this = static_cast<T>(1) / det * mat;
    }
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T> Mat<C, R, T>::safeInverse() const requires(Square)
{
    Mat<C, R, T> mat;
    T det = 0;
    T sign = 1;
    //First row with determinant
    for (size_t y = 0; y < C; ++y)
    {
        Mat<C - 1, R - 1, T> subMat;
        for (size_t subY = 0; subY < R - 1; ++subY)
        {
            for (size_t subX = 0; subX < C - 1; ++subX)
                subMat.at(subX, subY) = at(subX + 1, subY + static_cast<size_t>(subY >= y));
        }
        mat.at(y, 0) = sign * subMat.determinant();
        det += mMatrix[y * C] * mat.at(y, 0);
        sign = -sign;
    }
    if (isnormal(det))
        return Mat<C, R, T>::identity();

    //Other rows
    for (size_t x = 1; x < R; ++x)
    {
        for (size_t y = 0; y < C; ++y)
        {
            Mat<C - 1, R - 1, T> subMat;
            for (size_t subY = 0; subY < R - 1; ++subY)
            {
                for (size_t subX = 0; subX < C - 1; ++subX)
                    subMat.at(subX, subY) = at(subX + static_cast<size_t>(subX >= x), subY + static_cast<size_t>(subY >= y));
            }
            mat.at(y, x) = sign * subMat.determinant();
            sign = -sign;
        }
    }
    return static_cast<T>(1) / det * mat;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr T& Mat<C, R, T>::at(size_t x, size_t y)
{
    assert(x < C);
    assert(y < R);
    return mMatrix[y * C + x];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr const T& Mat<C, R, T>::at(size_t x, size_t y) const
{
    assert(x < C);
    assert(y < R);
    return mMatrix[y * C + x];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr T& Mat<C, R, T>::operator[](size_t index)
{
    assert(index < N);
    return mMatrix[index];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
constexpr const T& Mat<C, R, T>::operator[](size_t index) const
{
    assert(index < N);
    return mMatrix[index];
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T> Mat<C, R, T>::operator-() const
{
    Mat<C, R, T> matrix(*this);
    for (size_t i = 0; i < N; ++i)
        matrix[i] = -matrix[i];
    return matrix;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator+=(const Mat<C, R, T>& other)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] += other.mMatrix[i];
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator-=(const Mat<C, R, T>& other)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] -= other.mMatrix[i];
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator*=(const Mat<C, R, T>& other)
{
    *this = *this * other;
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator+=(T value)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] += value;
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator-=(T value)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] -= value;
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
Mat<C, R, T>& Mat<C, R, T>::operator*=(T value)
{
    for (size_t i = 0; i < N; ++i)
        mMatrix[i] *= value;
    return *this;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator+(const Mat<C, R, T>& left, const Mat<C, R, T>& right)
{
    return Mat<C, R, T>(left) += right;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator-(const Mat<C, R, T>& left, const Mat<C, R, T>& right)
{
    return Mat<C, R, T>(left) -= right;
}

template<size_t C, size_t R, arithmetic T, size_t C2> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C2, C, T> operator*(const Mat<C, R, T>& left, const Mat<C2, C, T>& right)
{
    Mat<C2, C, T> matrix = Mat<C2, C, T>::zero();
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < C2; ++x)
        {
            for (size_t k = 0; k < C; ++k)
                matrix.at(x, y) += left.at(k, y) * right.at(x, k);
        }
    }
    return matrix;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Vec2<T> operator*(const Mat<C, R, T>& matrix, const Vec2<T>& vector) requires(C == Vec2<T>::N)
{
    Vec2<T> result = Vec2<T>::zero();
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < R; ++x)
            result[y] += matrix.at(x, y) * vector[x];
    }
    return result;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Vec3<T> operator*(const Mat<C, R, T>& matrix, const Vec3<T>& vector) requires(C == Vec3<T>::N)
{
    Vec3<T> result = Vec3<T>::zero();
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < R; ++x)
            result[y] += matrix.at(x, y) * vector[x];
    }
    return result;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Vec4<T> operator*(const Mat<C, R, T>& matrix, const Vec4<T>& vector) requires(C == Vec4<T>::N)
{
    Vec4<T> result = Vec4<T>::zero();
    for (size_t y = 0; y < C; ++y)
    {
        for (size_t x = 0; x < R; ++x)
            result[y] += matrix.at(x, y) * vector[x];
    }
    return result;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator+(const Mat<C, R, T>& matrix, T value)
{
    return Mat<C, R, T>(matrix) += value;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator-(const Mat<C, R, T>& matrix, T value)
{
    return Mat<C, R, T>(matrix) -= value;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator*(const Mat<C, R, T>& matrix, T value)
{
    return Mat<C, R, T>(matrix) *= value;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] Mat<C, R, T> operator*(T value, const Mat<C, R, T>& matrix)
{
    return Mat<C, R, T>(matrix) *= value;
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] bool operator==(const Mat<C, R, T>& left, const Mat<C, R, T>& right)
{
    return left.matrix() == right.matrix();
}

template<size_t C, size_t R, arithmetic T> requires (C != 0 && R != 0)
[[nodiscard]] bool operator!=(const Mat<C, R, T>& left, const Mat<C, R, T>& right)
{
    return left.matrix() != right.matrix();
}
