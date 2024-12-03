#pragma once
#include <cstdint>

enum class CullMode : uint32_t
{
	None = 0,
	Front = 0x0404,
	Back = 0x0405,
	FrontAndBack = 0x0408
};
