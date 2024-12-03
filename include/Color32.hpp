#pragma once
#include <cstdint>

struct Color;

struct Color32
{
	static const Color32 Black;
	static const Color32 White;
	static const Color32 Red;
	static const Color32 Green;
	static const Color32 Blue;
	static const Color32 Transparent;

	constexpr Color32();
	constexpr Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
	constexpr explicit Color32(const Color& color);

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

struct Color32RGB
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct Color32RG
{
	uint8_t r;
	uint8_t g;
};
