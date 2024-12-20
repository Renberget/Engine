#pragma once
#include "Maths/Vec2.hpp"
#include <array>

template<arithmetic T>
struct Rect
{
	constexpr Rect() {}
	constexpr Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
	template<arithmetic U>
	constexpr Rect(const Rect<U>& rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h) {}
	//Returns true if pos is inside the rect
	bool contains(const Vec2<T>& pos) const
	{
		return this->x < pos.x
			&& pos.x < this->x + this->w
			&& this->y < pos.y
			&& pos.y < this->y + this->h;
	}
	//Returns true if rect intersects this rect
	bool intersects(const Rect<T>& rect) const
	{
		return this->x <= rect.x + rect.w
			&& rect.x <= this->x + this->w
			&& this->y <= rect.y + rect.h
			&& rect.y <= this->y + this->h;
	}
	bool operator==(const Rect<T>& other) const
	{
		return x == other.x && y == other.y && w == other.w && h == other.h;
	}
	bool operator!=(const Rect<T>& other) const
	{
		return x != other.x || y != other.y || w != other.w || h != other.y;
	}
	Vec2<T> start() const
	{
		return { x, y };
	}
	Vec2<T> end() const
	{
		return { x + w, y + h };
	}
	T endX() const
	{
		return x + w;
	}
	T endY() const
	{
		return y + h;
	}
	Vec2<T> center() const
	{
		return { x + static_cast<T>(0.5) * w, y + static_cast<T>(0.5) * h };
	}
	T centerX() const
	{
		return x + static_cast<T>(0.5) * w;
	}
	T centerY() const
	{
		return y + static_cast<T>(0.5) * h;
	}
	Vec2<T> size() const
	{
		return { w, h };
	}

	T x = 0;
	T y = 0;
	T w = 0;
	T h = 0;
};

using FloatRect = Rect<float_t>;
using DoubleRect = Rect<double_t>;
using IntRect = Rect<int32_t>;