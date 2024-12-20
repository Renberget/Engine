#include "Glfw.hpp"

Glfw::Glfw()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");
}

Glfw::~Glfw()
{
	glfwTerminate();
}

void Glfw::ensureInit()
{
	static Glfw glfw;
}
