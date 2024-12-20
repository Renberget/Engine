#pragma once
#include "Vec2.hpp"

template<arithmetic T>
struct Vec3
{
	constexpr static size_t N = 3;

	[[nodiscard]] consteval static Vec3<T> zero()
	{
		return Vec3<T>(static_cast<T>(0));
	}

	[[nodiscard]] consteval static Vec3<T> one()
	{
		return Vec3<T>(static_cast<T>(1));
	}

	constexpr Vec3() = default;
	constexpr Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	constexpr explicit Vec3(T xyz) : x(xyz), y(xyz), z(xyz) {}
	constexpr explicit Vec3(const Vec2<T>& xy, T z) : x(xy.x), y(xy.y), z(z) {}
	constexpr explicit Vec3(T x, const Vec2<T>& yz) : x(x), y(yz.y), z(yz.z) {}
	template<arithmetic U>
	constexpr explicit Vec3(const Vec3<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)),
		z(static_cast<T>(other.z))
	{}

	[[nodiscard]] T sqrLength() const;
	[[nodiscard]] T length() const;
	[[nodiscard]] T dot(const Vec3<T>& other) const;
	[[nodiscard]] Vec3<T> cross(const Vec3<T>& other) const;
	[[nodiscard]] T distanceTo(const Vec3<T>& pos) const;
	//A length of 0 will throw
	Vec3<T>& unsafeNormalize();
	//A length of 0 will throw
	[[nodiscard]] Vec3<T> unsafeNormalized() const;
	//A length of 0 does nothing
	Vec3<T>& safeNormalize();
	//A length of 0 will return zero vector
	[[nodiscard]] Vec3<T> safeNormalized() const;
	[[nodiscard]] T& operator[](size_t index);
	[[nodiscard]] const T& operator[](size_t index) const;
	[[nodiscard]] Vec3<T> operator-() const;
	Vec3<T>& operator+=(const Vec3<T>& other);
	Vec3<T>& operator-=(const Vec3<T>& other);
	Vec3<T>& operator*=(const Vec3<T>& other);
	Vec3<T>& operator/=(const Vec3<T>& other);
	Vec3<T>& operator+=(T factor);
	Vec3<T>& operator-=(T factor);
	Vec3<T>& operator*=(T factor);
	Vec3<T>& operator/=(T factor);

	T x;
	T y;
	T z;
};

#include "Vec3.inl"

using Vec3f = Vec3<float_t>;
using Vec3d = Vec3<double_t>;
using Vec3i = Vec3<int32_t>;
using Vec3u = Vec3<uint32_t>;
