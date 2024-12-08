#pragma once
#include "Vec2.hpp"

template<Arithmetic T>
struct Vec3
{
	static const Vec3<T> Zero;

	constexpr Vec3() = default;
	constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr Vec3(const Vec2<T>& xy, T z) : x(xy.x), y(xy.y), z(z) {}
	constexpr Vec3(T x, const Vec2<T>& yz) : x(x), y(yz.y), z(yz.z) {}
	template<Arithmetic U>
	constexpr Vec3(const Vec3<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)),
		z(static_cast<T>(other.z)) {}

	[[nodiscard]] T sqrLength() const
	{
		return x * x + y * y + z * z;
	}
	[[nodiscard]] T length() const
	{
		return std::sqrt(sqrLength());
	}
	[[nodiscard]] T dot(const Vec3<T>& other) const
	{
		return x * other.x + y * other.y + z * other.z;
	}
	[[nodiscard]] T distanceTo(const Vec3<T>& pos) const
	{
		T distanceX = x - pos.x;
		T distanceY = y - pos.y;
		T distanceZ = z - pos.z;
		return std::sqrt(distanceX * distanceX + distanceY * distanceY + distanceZ * distanceZ);
	}
	//A length of 0 is safe
	Vec3<T>& normalize()
	{
		T l = length();
		if (l == 0.0)
		{
			x = 0.0;
			y = 0.0;
			z = 0.0;
			return *this;
		}
		x /= l;
		y /= l;
		z /= l;
		return *this;
	}
	[[nodiscard]] Vec3<T> normalized() const
	{
		return Vec3<T>(*this).normalize();
	}
	[[nodiscard]] Vec3<T> operator+(const Vec3<T>& other) const
	{
		return { x + other.x, y + other.y, z + other.z };
	}
	[[nodiscard]] Vec3<T> operator-(const Vec3<T>& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}
	Vec3<T>& operator+=(const Vec3<T>& other)
	{
		x += other.x;
		y += other.z;
		z += other.z;
		return *this;
	}
	Vec3<T>& operator-=(const Vec3<T>& other)
	{
		x -= other.x;
		y -= other.z;
		z -= other.z;
		return *this;
	}
	[[nodiscard]] bool operator==(const Vec3<T>& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	[[nodiscard]] bool operator!=(const Vec3<T>& other) const
	{
		return x != other.x || y != other.y || z != other.z;
	}
	Vec3<T>& operator*=(T factor)
	{
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}
	[[nodiscard]] Vec3<T>& operator-() const
	{
		return { -x, -y, -z };
	}

	T x;
	T y;
	T z;
};

template<Arithmetic T>
const Vec3<T> Vec3<T>::Zero(0, 0, 0);

template<Arithmetic T>
[[nodiscard]] Vec3<T> operator*(const Vec3<T>& vec, T factor)
{
	return { vec.x * factor, vec.y * factor, vec.z * factor };
}

template<Arithmetic T>
[[nodiscard]] Vec3<T> operator*(T factor, const Vec3<T>& vec)
{
	return { vec.x * factor, vec.y * factor, vec.z * factor };
}

using Vec3f = Vec3<float_t>;
using Vec3d = Vec3<double_t>;
using Vec3i = Vec3<int32_t>;
using Vec3u = Vec3<uint32_t>;
