#pragma once

template<arithmetic T>
T Vec4<T>::sqrLength() const
{
	return x * x + y * y + z * z + w * w;
}

template<arithmetic T>
T Vec4<T>::length() const
{
	return std::sqrt(sqrLength());
}

template<arithmetic T>
T Vec4<T>::dot(const Vec4<T>& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::unsafeNormalize()
{
	return *this /= length();
}

template<arithmetic T>
Vec4<T> Vec4<T>::unsafeNormalized() const
{
	return *this / length();
}

template<arithmetic T>
Vec4<T>& Vec4<T>::safeNormalize()
{
	T l = length();
	if (isnormal(l))
		*this /= l;
	return *this;
}

template<arithmetic T>
Vec4<T> Vec4<T>::safeNormalized() const
{
	T l = length();
	return isnormal(l) ? *this / l : Vec4<T>::zero();
}

template<arithmetic T>
T& Vec4<T>::operator[](size_t index)
{
	return (*reinterpret_cast<std::array<T, N>*>(this))[index];
}

template<arithmetic T>
const T& Vec4<T>::operator[](size_t index) const
{
	return (*reinterpret_cast<const std::array<T, N>*>(this))[index];
}

template<arithmetic T>
Vec4<T> Vec4<T>::operator-() const
{
	return Vec4<T>(-x, -y, -z, -w);
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator*=(const Vec4<T>& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator/=(const Vec4<T>& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	w /= other.w;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator+=(T value)
{
	x += value;
	y += value;
	z += value;
	w += value;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator-=(T value)
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator*=(T value)
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;
	return *this;
}

template<arithmetic T>
Vec4<T>& Vec4<T>::operator/=(T value)
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;
	return *this;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator+(const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left) += right;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator-(const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left) += right;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator*(const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left) *= right;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator/(const Vec4<T>& left, const Vec4<T>& right)
{
	return Vec4<T>(left) /= right;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator+(const Vec4<T>& vector, T value)
{
	return Vec4<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator+(T value, const Vec4<T>& vector)
{
	return Vec4<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator-(const Vec4<T>& vector, T value)
{
	return Vec4<T>(vector) -= value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator-(T value, const Vec4<T>& vector)
{
	return Vec4<T>(value - vector.x, value - vector.y, value - vector.z, value - vector.w);
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator*(const Vec4<T>& vector, T value)
{
	return Vec4<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator*(T value, const Vec4<T>& vector)
{
	return Vec4<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator/(const Vec4<T>& vector, T value)
{
	return Vec4<T>(vector) /= value;
}

template<arithmetic T>
[[nodiscard]] Vec4<T> operator/(T value, const Vec4<T>& vector)
{
	return Vec4<T>(value / vector.x, value / vector.y, value / vector.z, value / vector.w);
}

template<arithmetic T>
[[nodiscard]] bool operator==(const Vec4<T>& left, const Vec4<T>& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
}

template<arithmetic T>
[[nodiscard]] bool operator!=(const Vec4<T>& left, const Vec4<T>& right)
{
	return left.x != right.x || left.y != right.y || left.z != right.z || left.w != right.w;
}