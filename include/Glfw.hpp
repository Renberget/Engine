#pragma once
#include "Type.hpp"
#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class Glfw
{
public:
	~Glfw();
	static void ensureInit();

private:
	Glfw();
	static void errorCallback(int error, const char* description);
};