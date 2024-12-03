#pragma once
#include <iostream>
#include "Maths/Mat.hpp"
#include "Maths/Quat.hpp"

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
	else
		std::cout << std::boolalpha << +value << std::endl;
}

template<Printable U>
void printSingle(const Vec2<U>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ')' << std::endl;
}

template<Printable U>
void printSingle(const Vec3<U>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ", " << +value.z << ')' << std::endl;
}

template<Printable U>
void printSingle(const Vec4<U>& value)
{
	std::cout << std::boolalpha << '(' << +value.x << ", " << +value.y << ", " << +value.z << ", " << +value.w << ')' << std::endl;
}

template<Printable U>
void printSingle(const Quat<U>& value)
{
	Vec3<U> euler = value.toEuler();
	std::cout << '(' << euler.x << ", " << euler.y << ", " << euler.z << ')' << std::endl;
}

template<size_t C, size_t R, Printable U>
void printSingle(const Mat<C, R, U>& value)
{
	for (size_t x = 0; x < C; ++x)
	{
		std::cout << '|';
		for (size_t y = 0; y < R; ++y)
		{
			std::cout << value.get(x, y) << ", ";
		}
		std::cout << '|' << std::endl;
	}
}

template<typename... Ts>
void print(const Ts&... values)
{
	(printSingle(values), ...);
}
