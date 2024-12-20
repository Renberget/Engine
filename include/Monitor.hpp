#pragma once
#include "Maths/Math.hpp"
#include "Utils/Uncopyable.hpp"
#include <string_view>
#include <vector>
#include <span>
#include <memory>

struct VideoMode
{
	int width;
	int height;
	int redBits;
	int greenBits;
	int blueBits;
	int refreshRate;
};

class Monitor : public Uncopyable
{
public:
	Monitor() = default;
	Monitor(Monitor&&) = default;
	Monitor& operator=(Monitor&&) = default;
	//Returns the monitor name
	[[nodiscard]] std::string_view name() const;
	//Returns the monitor physical size in millimeters
	[[nodiscard]] Vec2i physicalSize() const;
	//Returns the monitor content scale
	[[nodiscard]] Vec2f contentScale() const;
	//Returns the monitor position
	[[nodiscard]] Vec2i pos() const;
	//Returns the monitor current video mode
	[[nodiscard]] const VideoMode& videoMode() const;
	//Returns the monitor available video modes
	[[nodiscard]] std::span<const VideoMode> videoModes() const;

	//Returns the currently connected monitors
	[[nodiscard]] static std::vector<Monitor> getMonitors();
	//Returns the primary monitor
	[[nodiscard]] static Monitor getPrimary();

private:
	class Impl;
	Monitor(Impl* impl);

	std::unique_ptr<Impl> mImpl;

	friend class Window;
};