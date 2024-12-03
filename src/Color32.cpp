#include "Color.hpp"

const Color32 Color32::Black(0, 0, 0, 255);
const Color32 Color32::White(255, 255, 255, 255);
const Color32 Color32::Red(255, 0, 0, 0);
const Color32 Color32::Green(0, 255, 0, 255);
const Color32 Color32::Blue(0, 0, 255, 255);
const Color32 Color32::Transparent(0, 0, 0, 0);

constexpr Color32::Color32() : r(0), g(0), b(0), a(255) {}

constexpr Color32::Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

constexpr Color32::Color32(const Color& color) :
	r(static_cast<uint8_t>(color.r * 255.f)),
	g(static_cast<uint8_t>(color.g * 255.f)),
	b(static_cast<uint8_t>(color.b * 255.f)),
	a(static_cast<uint8_t>(color.a * 255.f)) {}
