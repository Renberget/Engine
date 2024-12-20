#pragma once

template<arithmetic T>
T Vec3<T>::sqrLength() const
{
	return x * x + y * y + z * z;
}

template<arithmetic T>
T Vec3<T>::length() const
{
	return std::sqrt(sqrLength());
}

template<arithmetic T>
T Vec3<T>::dot(const Vec3<T>& other) const
{
	return x * other.x + y * other.y + z * other.z;
}

template<arithmetic T>
Vec3<T> Vec3<T>::cross(const Vec3<T>& other) const
{
	return { y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x };
}

template<arithmetic T>
T Vec3<T>::distanceTo(const Vec3<T>& pos) const
{
	T distanceX = x - pos.x;
	T distanceY = y - pos.y;
	T distanceZ = z - pos.z;
	return std::sqrt(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);
}

template<arithmetic T>
Vec3<T>& Vec3<T>::unsafeNormalize()
{
	return *this /= length();
}

template<arithmetic T>
Vec3<T> Vec3<T>::unsafeNormalized() const
{
	return *this / length();
}

template<arithmetic T>
Vec3<T>& Vec3<T>::safeNormalize()
{
	T l = length();
	if (isnormal(l))
		*this /= l;
	return *this;
}

template<arithmetic T>
Vec3<T> Vec3<T>::safeNormalized() const
{
	T l = length();
	return isnormal(l) ? *this / l : Vec3<T>::zero();
}

template<arithmetic T>
T& Vec3<T>::operator[](size_t index)
{
	return (*reinterpret_cast<std::array<T, N>*>(this))[index];
}

template<arithmetic T>
const T& Vec3<T>::operator[](size_t index) const
{
	return (*reinterpret_cast<const std::array<T, N>*>(this))[index];
}

template<arithmetic T>
Vec3<T> Vec3<T>::operator-() const
{
	return Vec3<T>(-x, -y, -z);
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& other)
{
	x += other.x;
	y += other.z;
	z += other.z;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& other)
{
	x -= other.x;
	y -= other.z;
	z -= other.z;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& other)
{
	x *= other.x;
	y *= other.z;
	z *= other.z;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& other)
{
	x /= other.x;
	y /= other.z;
	z /= other.z;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator+=(T factor)
{
	x += factor;
	y += factor;
	z += factor;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator-=(T factor)
{
	x -= factor;
	y -= factor;
	z -= factor;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator*=(T factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

template<arithmetic T>
Vec3<T>& Vec3<T>::operator/=(T factor)
{
	x /= factor;
	y /= factor;
	z /= factor;
	return *this;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator+(const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left) += right;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator-(const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left) += right;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator*(const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left) *= right;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator/(const Vec3<T>& left, const Vec3<T>& right)
{
	return Vec3<T>(left) /= right;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator+(const Vec3<T>& vector, T value)
{
	return Vec3<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator+(T value, const Vec3<T>& vector)
{
	return Vec3<T>(vector) += value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator-(const Vec3<T>& vector, T value)
{
	return Vec3<T>(vector) -= value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator-(T value, const Vec3<T>& vector)
{
	return Vec3<T>(value - vector.x, value - vector.y, value - vector.z);
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator*(const Vec3<T>& vector, T value)
{
	return Vec3<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator*(T value, const Vec3<T>& vector)
{
	return Vec3<T>(vector) *= value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator/(const Vec3<T>& vector, T value)
{
	return Vec3<T>(vector) /= value;
}

template<arithmetic T>
[[nodiscard]] Vec3<T> operator/(T value, const Vec3<T>& vector)
{
	return { value / vector.x, value / vector.y, value / vector.z };
}

template<arithmetic T>
[[nodiscard]] bool operator==(const Vec3<T>& left, const Vec3<T>& right)
{
	return left.x == right.x && left.y == right.y && left.z == right.z;
}

template<arithmetic T>
[[nodiscard]] bool operator!=(const Vec3<T>& left, const Vec3<T>& right)
{
	return left.x != right.x || left.y != right.y || left.z != right.z;
}
