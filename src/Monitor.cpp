#include "MonitorImpl.hpp"

std::string_view Monitor::name() const
{
	return mImpl->name();
}

Vec2i Monitor::physicalSize() const
{
	return mImpl->physicalSize();
}

Vec2f Monitor::contentScale() const
{
	return mImpl->contentScale();
}

Vec2i Monitor::pos() const
{
	return mImpl->pos();
}

const VideoMode& Monitor::videoMode() const
{
	return mImpl->videoMode();
}

std::span<const VideoMode> Monitor::videoModes() const
{
	return mImpl->videoModes();
}

std::vector<Monitor> Monitor::getMonitors()
{
	int count;
	GLFWmonitor** glfwMonitors = glfwGetMonitors(&count);
	std::vector<Monitor> monitors(static_cast<size_t>(count));
	for (int i = 0; i < count; ++i)
	{
		monitors[i].mImpl = std::make_unique<Impl>(glfwMonitors[i]);
	}
	return monitors;
}

Monitor Monitor::getPrimary()
{
	Glfw::ensureInit();
	return Monitor(new Impl(glfwGetPrimaryMonitor()));
}

Monitor::Monitor(Impl* impl) : mImpl(impl) {}
