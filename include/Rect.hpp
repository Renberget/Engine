#pragma once
#include "Maths/Vec2.hpp"
#include <array>

template<typename T>
struct Rect
{
	constexpr Rect() {}
	constexpr Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
	template<typename U>
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

	T x = 0;
	T y = 0;
	T w = 0;
	T h = 0;
};

using FloatRect = Rect<float_t>;
using IntRect = Rect<int32_t>;