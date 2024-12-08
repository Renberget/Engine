#pragma once
#include "Vec3.hpp"

template<Arithmetic T>
struct Vec4
{
	static const Vec4 Zero;

	constexpr Vec4() = default;
	constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	constexpr Vec4(const Vec2<T>& xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr Vec4(T x, const Vec2<T>& yz, T w) : x(x), y(yz.y), z(yz.z), w(w) {}
	constexpr Vec4(T x, T y, const Vec2<T>& zw) : x(x), y(y), z(zw.z), w(zw.w) {}
	constexpr Vec4(const Vec2<T>& xy, const Vec2<T>& zw) : x(xy.x), y(xy.y), z(zw.z), w(zw.w) {}
	constexpr Vec4(const Vec3<T>& xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	constexpr Vec4(T x, const Vec3<T>& yzw) : x(x), y(yzw.y), z(yzw.z), w(yzw.w) {}
	template<Arithmetic U>
	constexpr Vec4(const Vec4<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)),
		z(static_cast<T>(other.z)),
		w(static_cast<T>(other.w)) {}

	[[nodiscard]] Vec4<T> operator+(const Vec4<T>& other) const
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}
	[[nodiscard]] Vec4<T> operator-(const Vec4<T>& other) const
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}
	Vec4<T>& operator+=(const Vec4<T>& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	Vec4<T>& operator-=(const Vec4<T>& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	[[nodiscard]] bool operator==(const Vec4<T>& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	[[nodiscard]] bool operator!=(const Vec4<T>& other) const
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}
	Vec4<T>& operator*=(T factor) const
	{
		x *= factor;
		y *= factor;
		z *= factor;
		w *= factor;
		return *this;
	}
	[[nodiscard]] Vec4<T>& operator-() const
	{
		return { -x, -y, -z, -w };
	}

	T x;
	T y;
	T z;
	T w;
};

template<Arithmetic T>
const Vec4<T> Vec4<T>::Zero(0, 0, 0, 0);

template<Arithmetic T>
[[nodiscard]] Vec4<T> operator*(const Vec4<T>& vec, T factor)
{
	return { vec.x * factor, vec.y * factor, vec.z * factor, vec.w * factor };
}

template<Arithmetic T>
[[nodiscard]] Vec4<T> operator*(T factor, const Vec4<T>& vec)
{
	return { vec.x * factor, vec.y * factor, vec.z * factor, vec.w * factor };
}

using Vec4f = Vec4<float_t>;
using Vec4d = Vec4<double_t>;
using Vec4i = Vec4<int32_t>;
using Vec4u = Vec4<uint32_t>;
