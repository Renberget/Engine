#pragma once
#include "Color32.hpp"
#include <cmath>

struct Color
{
    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Transparent;

    constexpr Color();
    constexpr explicit Color(float_t r, float_t g, float_t b, float_t a = 1.f);
    constexpr explicit Color(const Color32& color32);
    float_t r;
    float_t g;
    float_t b;
    float_t a;
};
