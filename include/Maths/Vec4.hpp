#pragma once
#include "Vec3.hpp"

template<arithmetic T>
struct Vec4
{
	constexpr static size_t N = 4;

	[[nodiscard]] consteval static Vec4<T> zero()
	{
		return Vec4<T>(static_cast<T>(0));
	}

	[[nodiscard]] consteval static Vec4<T> one()
	{
		return Vec3<T>(static_cast<T>(1));
	}

	constexpr Vec4() = default;
	constexpr Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	constexpr explicit Vec4(T xyzw) : x(xyzw), y(xyzw), z(xyzw), w(xyzw) {}
	constexpr explicit Vec4(const Vec2<T>& xy, T z, T w) : x(xy.x), y(xy.y), z(z), w(w) {}
	constexpr explicit Vec4(T x, const Vec2<T>& yz, T w) : x(x), y(yz.y), z(yz.z), w(w) {}
	constexpr explicit Vec4(T x, T y, const Vec2<T>& zw) : x(x), y(y), z(zw.z), w(zw.w) {}
	constexpr explicit Vec4(const Vec2<T>& xy, const Vec2<T>& zw) : x(xy.x), y(xy.y), z(zw.z), w(zw.w) {}
	constexpr explicit Vec4(const Vec3<T>& xyz, T w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w) {}
	constexpr explicit Vec4(T x, const Vec3<T>& yzw) : x(x), y(yzw.y), z(yzw.z), w(yzw.w) {}
	template<arithmetic U>
	constexpr explicit Vec4(const Vec4<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)),
		z(static_cast<T>(other.z)),
		w(static_cast<T>(other.w))
	{}

	[[nodiscard]] T sqrLength() const;
	[[nodiscard]] T length() const;
	[[nodiscard]] T dot(const Vec4<T>& other) const;
	//A length of 0 will throw
	Vec4<T>& unsafeNormalize();
	//A length of 0 will throw
	[[nodiscard]] Vec4<T> unsafeNormalized() const;
	//A length of 0 does nothing
	Vec4<T>& safeNormalize();
	//A length of 0 will return zero vector
	[[nodiscard]] Vec4<T> safeNormalized() const;
	[[nodiscard]] T& operator[](size_t index);
	[[nodiscard]] const T& operator[](size_t index) const;
	[[nodiscard]] Vec4<T> operator-() const;
	Vec4<T>& operator+=(const Vec4<T>& other);
	Vec4<T>& operator-=(const Vec4<T>& other);
	Vec4<T>& operator*=(const Vec4<T>& other);
	Vec4<T>& operator/=(const Vec4<T>& other);
	Vec4<T>& operator+=(T factor);
	Vec4<T>& operator-=(T factor);
	Vec4<T>& operator*=(T factor);
	Vec4<T>& operator/=(T factor);

	T x;
	T y;
	T z;
	T w;
};

#include "Vec4.inl"

using Vec4f = Vec4<float_t>;
using Vec4d = Vec4<double_t>;
using Vec4i = Vec4<int32_t>;
using Vec4u = Vec4<uint32_t>;
