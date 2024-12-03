#include "Glfw.hpp"

Glfw::Glfw()
{
	if (!glfwInit())
		throw std::runtime_error("Failed to init glfw");
	glfwSetErrorCallback(errorCallback);
}

Glfw::~Glfw()
{
	glfwTerminate();
}

void Glfw::ensureInit()
{
	static Glfw glfw;
}

void Glfw::errorCallback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}