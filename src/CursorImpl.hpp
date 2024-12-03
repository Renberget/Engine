#pragma once
#include "Cursor.hpp"
#include "Glfw.hpp"

class Cursor::Impl
{
public:
	explicit Impl(const Image& image, const Vec2i& hotspot);
	explicit Impl(Standard standard);
	~Impl();
	GLFWcursor* handle();

private:
	GLFWcursor* mHandle = nullptr;
};
