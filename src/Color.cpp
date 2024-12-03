#include "Color.hpp"

const Color Color::Black(0.f, 0.f, 0.f, 1.f);
const Color Color::White(1.f, 1.f, 1.f, 1.f);
const Color Color::Red(1.f, 0.f, 0.f, 1.f);
const Color Color::Green(0.f, 1.f, 0.f, 1.f);
const Color Color::Blue(0.f, 0.f, 1.f, 1.f);
const Color Color::Transparent(0.f, 0.f, 0.f, 0.f);

constexpr Color::Color() : r(0.f), g(0.f), b(0.f), a(1.f) {}

constexpr Color::Color(float_t r, float_t g, float_t b, float_t a) : r(r), g(g), b(b), a(a) {}

constexpr Color::Color(const Color32& color32) :
	r(static_cast<float_t>(color32.r) / 255.f),
	g(static_cast<float_t>(color32.g) / 255.f),
	b(static_cast<float_t>(color32.b) / 255.f),
	a(static_cast<float_t>(color32.a) / 255.f) {}
