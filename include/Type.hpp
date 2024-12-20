#pragma once
#include <cstdint>
#include <cmath>

enum class Type : uint32_t
{
	Unknown,
	Bool = 0x8B56,
	Byte = 0x1400,
	UnsignedByte = 0x1401,
	Short = 0x1402,
	UnsignedShort = 0x1403,
	Int = 0x1404,
	UnsignedInt = 0x1405,
	Float = 0x1406,
	Double = 0x140A,
	HalfFloat = 0x140B,
};

namespace
{
	template<typename T>
	consteval Type getType()
	{
		return Type::Unknown;
	}

	template<>
	consteval Type getType<bool>()
	{
		return Type::Bool;
	}

	template<>
	consteval Type getType<int8_t>()
	{
		return Type::Byte;
	}

	template<>
	consteval Type getType<uint8_t>()
	{
		return Type::UnsignedByte;
	}

	template<>
	consteval Type getType<int16_t>()
	{
		return Type::Short;
	}

	template<>
	consteval Type getType<uint16_t>()
	{
		return Type::UnsignedShort;
	}

	template<>
	consteval Type getType<int32_t>()
	{
		return Type::Int;
	}

	template<>
	consteval Type getType<uint32_t>()
	{
		return Type::UnsignedInt;
	}

	template<>
	consteval Type getType<float_t>()
	{
		return Type::Float;
	}

	template<>
	consteval Type getType<double_t>()
	{
		return Type::Double;
	}
}
