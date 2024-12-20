#pragma once
#include <iostream>
#include "Maths/Math.hpp"

#ifndef NDEBUG
template<typename T>
concept Printable = requires(std::ostream& stream, const T& value)
{
	{ stream << value };
};

template<Printable T>
void printSingle(const T& value)
{
	if constexpr (std::is_enum_v<T>)
		std::cout << +static_cast<std::underlying_type_t<T>>(value) << std::endl;
	else if constexpr (std::is_same_v<T, bool>)
		std::cout << std::boolalpha << value << std::endl;
	else if constexpr (std::is_same_v<T, int8_t> || std::is_same_v<T, uint8_t>)
		std::cout << +value << std::endl;
	else
		std::cout << value << std::endl;
}

template<Printable T>
void printSingle(const Vec2<T>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ')' << std::endl;
}

template<Printable T>
void printSingle(const Vec3<T>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ", " << +value.z << ')' << std::endl;
}

template<Printable T>
void printSingle(const Vec4<T>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ", " << +value.z << ", " << +value.w << ')' << std::endl;
}

template<Printable T>
void printSingle(const Quat<T>& value)
{
	Vec3<T> euler = value.euler();
	std::cout << '(' << euler.x << ", " << euler.y << ", " << euler.z << ')' << std::endl;
}

template<size_t C, size_t R, Printable T>
void printSingle(const Mat<C, R, T>& value)
{
	for (size_t y = 0; y < R; ++y)
	{
		std::cout << '|';
		for (size_t x = 0; x < C; ++x)
		{
			std::cout << value.at(x, y);
			if (x < C - 1)
				std::cout << ", ";
		}
		std::cout << '|' << std::endl;
	}
}

template<Printable T>
void printSingle(const Transform2<T>& transform)
{
	printSingle(transform.matrix());
}

template<Printable T>
void printSingle(const Transform3<T>& transform)
{
	printSingle(transform.matrix());
}

template<typename... Ts>
void print(const Ts&... values)
{
	(printSingle(values), ...);
}
#endif