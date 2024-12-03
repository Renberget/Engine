#pragma once
#include <cmath>
#include <cstdint>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

template<Arithmetic T>
struct Vec2
{
	static const Vec2 Zero;

	constexpr Vec2() = default;
	constexpr Vec2(T x, T y) : x(x), y(y) {}
	template<typename U>
	constexpr Vec2(const Vec2<U>& other) :
		x(static_cast<T>(other.x)),
		y(static_cast<T>(other.y)) {}

	[[nodiscard]] T sqrLength() const
	{
		return x * x + y * y;
	}
	[[nodiscard]] T length() const
	{
		return std::sqrt(sqrLength());
	}
	[[nodiscard]] T dot(const Vec2<T>& pos) const
	{
		return x * pos.x + y * pos.y;
	}
	[[nodiscard]] T distanceTo(const Vec2<T>& pos) const
	{
		T distanceX = x - pos.x;
		T distanceY = y - pos.y;
		return std::sqrt(distanceX * distanceX + distanceY * distanceY);
	}
	//A length of 0 is safe
	Vec2<T>& normalize()
	{
		T l = length();
		if (l == 0.0)
		{
			x = 0.0;
			y = 0.0;
			return *this;
		}
		x /= l;
		y /= l;
		return *this;
	}
	[[nodiscard]] Vec2<T> normalized() const
	{
		return Vec2<T>(*this).normalize();
	}
	[[nodiscard]] Vec2<T> operator+(const Vec2<T>& other) const
	{
		return { x + other.x, y + other.y };
	}
	[[nodiscard]] Vec2<T> operator-(const Vec2<T>& other) const
	{
		return { x - other.x, y - other.y };
	}
	Vec2<T>& operator+=(const Vec2<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2<T>& operator-=(const Vec2<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	[[nodiscard]] bool operator==(const Vec2<T>& other) const
	{
		return x == other.x && y == other.y;
	}
	[[nodiscard]] bool operator!=(const Vec2<T>& other) const
	{
		return x != other.x || y != other.y;
	}
	Vec2<T>& operator*=(T factor)
	{
		x *= factor;
		y *= factor;
		return *this;
	}
	[[nodiscard]] Vec2<T> operator-() const
	{
		return { -x, -y };
	}
	
	T x;
	T y;
};

template<Arithmetic T>
const Vec2<T> Vec2<T>::Zero(0, 0);

template<Arithmetic T>
[[nodiscard]] Vec2<T> operator*(const Vec2<T>& vec, T factor)
{
	return { vec.x * factor, vec.y * factor };
}

template<Arithmetic T>
[[nodiscard]] Vec2<T> operator*(T factor, const Vec2<T>& vec)
{
	return { vec.x * factor, vec.y * factor };
}

using Vec2f = Vec2<float_t>;
using Vec2d = Vec2<double_t>;
using Vec2i = Vec2<int32_t>;
using Vec2u = Vec2<uint32_t>;
