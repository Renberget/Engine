#pragma once

template<arithmetic T>
T Vec2<T>::sqrLength() const
{
	return x * x + y * y;
}

template<arithmetic T>
T Vec2<T>::length() const
{
	return std::sqrt(sqrLength());
}

template<arithmetic T>
T Vec2<T>::dot(const Vec2<T>& other) const
{
	return x * other.x + y * other.y;
}

template<arithmetic T>
T Vec2<T>::distanceTo(const Vec2<T>& other) const
{
	T distanceX = x - other.x;
	T distanceY = y - other.y;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY);
}

template<arithmetic T>
Vec2<T>& Vec2<T>::unsafeNormalize()
{
	return *this /= length();
}

template<arithmetic T>
Vec2<T> Vec2<T>::unsafeNormalized() const
{
	return *this / length();
}

template<arithmetic T>
Vec2<T>& Vec2<T>::safeNormalize()
{
	T l = length();
	if (isnormal(l))
		*this /= l;
	return *this;
}

template<arithmetic T>
Vec2<T> Vec2<T>::safeNormalized() const
{
	T l = length();
	return isnormal(l) ? *this / l : Vec2<T>::zero();
}

template<arithmetic T>
T& Vec2<T>::operator[](size_t index)
{
	return (*reinterpret_cast<std::array<T, N>*>(this))[index];
}

template<arithmetic T>
const T& Vec2<T>::operator[](size_t index) const
{
	return (*reinterpret_cast<const std::array<T, N>*>(this))[index];
}

template<arithmetic T>
Vec2<T> Vec2<T>::operator-() const
{
	return Vec2<T>(-x, -y);
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator+=(T factor)
{
	x += factor;
	y += factor;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator-=(T factor)
{
	x -= factor;
	y -= factor;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator*=(T factor)
{
	x *= factor;
	y *= factor;
	return *this;
}

template<arithmetic T>
Vec2<T>& Vec2<T>::operator/=(T factor)
{
	x /= factor;
	y /= factor;
	return *this;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator+(const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left) += right;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator-(const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left) -= right;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator*(const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left) *= right;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator/(const Vec2<T>& left, const Vec2<T>& right)
{
	return Vec2<T>(left) /= right;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator+(const Vec2<T>& vector, T value)
{
	return Vec2<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator+(T value, const Vec2<T>& vector)
{
	return Vec2<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator-(const Vec2<T>& vector, T value)
{
	return Vec2<T>(vector) -= value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator-(T value, const Vec2<T>& vector)
{
	return Vec2<T>(value - vector.x, value - vector.y);
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator*(const Vec2<T>& vector, T value)
{
	return Vec2<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator*(T value, const Vec2<T>& vector)
{
	return Vec2<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator/(const Vec2<T>& vector, T value)
{
	return Vec2<T>(vector) /= value;
}

template<arithmetic T>
[[nodiscard]] Vec2<T> operator/(T value, const Vec2<T>& vector)
{
	return Vec2<T>(value / vector.x, value / vector.y);
}

template<arithmetic T>
[[nodiscard]] bool operator==(const Vec2<T>& left, const Vec2<T>& right)
{
	return left.x == right.x && left.y == right.y;
}

template<arithmetic T>
[[nodiscard]] bool operator!=(const Vec2<T>& left, const Vec2<T>& right)
{
	return left.x != right.x || left.y != right.y;
}
