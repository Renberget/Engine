#pragma once
#include <cmath>
#include <cstdint>
#include <array>

template<typename T>
concept arithmetic = std::is_arithmetic_v<T>;

template<arithmetic T>
struct Vec2
{
	constexpr static size_t N = 2;

	[[nodiscard]] consteval static Vec2<T> zero()
	{
		return Vec2<T>(static_cast<T>(0));
	}
	
	[[nodiscard]] consteval static Vec2<T> one()
	{
		return Vec2<T>(static_cast<T>(1));
	}

	constexpr Vec2() = default;
	constexpr Vec2(T x, T y) : x(x), y(y) {}
	constexpr explicit Vec2(T xy) : x(xy), y(xy) {}
	template<arithmetic U>
	constexpr explicit Vec2(const Vec2<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y))
	{}

	[[nodiscard]] T sqrLength() const;
	[[nodiscard]] T length() const;
	[[nodiscard]] T dot(const Vec2<T>& other) const;
	[[nodiscard]] T distanceTo(const Vec2<T>& other) const;
	//A length of 0 will throw
	Vec2<T>& unsafeNormalize();
	//A length of 0 will throw
	[[nodiscard]] Vec2<T> unsafeNormalized() const;
	//A length of 0 does nothing
	Vec2<T>& safeNormalize();
	//A length of 0 will return zero vector
	[[nodiscard]] Vec2<T> safeNormalized() const;
	[[nodiscard]] T& operator[](size_t index);
	[[nodiscard]] const T& operator[](size_t index) const;
	[[nodiscard]] Vec2<T> operator-() const;
	Vec2<T>& operator+=(const Vec2<T>& other);
	Vec2<T>& operator-=(const Vec2<T>& other);
	Vec2<T>& operator*=(const Vec2<T>& other);
	Vec2<T>& operator/=(const Vec2<T>& other);
	Vec2<T>& operator+=(T factor);
	Vec2<T>& operator-=(T factor);
	Vec2<T>& operator*=(T factor);
	Vec2<T>& operator/=(T factor);
	
	T x;
	T y;
};

#include "Vec2.inl"

using Vec2f = Vec2<float_t>;
using Vec2d = Vec2<double_t>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
