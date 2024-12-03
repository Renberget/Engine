#pragma once
#include "Monitor.hpp"
#include "Glfw.hpp"

class Monitor::Impl
{
public:
	Impl(GLFWmonitor* monitor);
	std::string_view name() const;
	Vec2i physicalSize() const;
	Vec2f contentScale() const;
	Vec2i pos() const;
	const VideoMode& videoMode() const;
	std::span<const VideoMode> videoModes() const;

	GLFWmonitor* handle();

private:
	GLFWmonitor* mHandle;
};