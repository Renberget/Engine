#include "MonitorImpl.hpp"

Monitor::Impl::Impl(GLFWmonitor* monitor) : mHandle(monitor) {}

std::string_view Monitor::Impl::name() const
{
	return glfwGetMonitorName(mHandle);
}

Vec2i Monitor::Impl::physicalSize() const
{
	Vec2i size;
	glfwGetMonitorPhysicalSize(mHandle, &size.x, &size.y);
	return size;
}

Vec2f Monitor::Impl::contentScale() const
{
	Vec2f scale;
	glfwGetMonitorContentScale(mHandle, &scale.x, &scale.y);
	return scale;
}

Vec2i Monitor::Impl::pos() const
{
	Vec2i pos;
	glfwGetMonitorPos(mHandle, &pos.x, &pos.y);
	return pos;
}

const VideoMode& Monitor::Impl::videoMode() const
{
	return *reinterpret_cast<const VideoMode*>(glfwGetVideoMode(mHandle));
}

std::span<const VideoMode> Monitor::Impl::videoModes() const
{
	int count;
	const GLFWvidmode* modes = glfwGetVideoModes(mHandle, &count);
	return std::span<const VideoMode>(reinterpret_cast<const VideoMode*>(modes), static_cast<size_t>(count));
}

GLFWmonitor* Monitor::Impl::handle()
{
	return mHandle;
}
