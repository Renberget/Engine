#include "Impl.hpp"

namespace input
{
	std::vector<Map> Manager::sMaps;
	GamepadConnectionChangeEvent Manager::sGamepadConnectionChangeEvent;
	DropEvent Manager::sDropEvent;

	void Manager::pollEvents()
	{
		Impl::pollEvents();
		for (Map& map : sMaps)
			map.callEvents();
	}

	std::vector<Map>& Manager::maps()
	{
		return sMaps;
	}

	std::vector<Gamepad*>& Manager::gamepads()
	{
		return Impl::gamepads();
	}

	GamepadConnectionChangeEvent& Manager::gamepadConnectionChangeEvent()
	{
		return sGamepadConnectionChangeEvent;
	}

	DropEvent& Manager::dropEvent()
	{
		return sDropEvent;
	}

	void Manager::keyCallback(Key key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			for (Map& map : sMaps)
				map.applyInput(key, true);
		}
		else if (action == GLFW_RELEASE)
		{
			for (Map& map : sMaps)
				map.applyInput(key, false);
		}
	}

	void Manager::mouseButtonCallback(Mouse::Button button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			for (Map& map : sMaps)
				map.applyInput(button, true);
		}
		else if (action == GLFW_RELEASE)
		{
			for (Map& map : sMaps)
				map.applyInput(button, false);
		}
	}

	void Manager::scrollCallback(float xOffset, float yOffset)
	{
		if (xOffset != 0.0)
		{
			for (Map& map : sMaps)
				map.applyInput(Mouse::Axis::ScrollX, xOffset);
		}
		if (yOffset != 0.0)
		{
			for (Map& map : sMaps)
				map.applyInput(Mouse::Axis::ScrollY, yOffset);
		}
	}

	void Manager::mouseMoveCallback(float xOffset, float yOffset)
	{
		if (xOffset != 0.f)
		{
			for (Map& map : sMaps)
				map.applyInput(Mouse::Axis::MoveX, xOffset);
		}
		if (yOffset != 0.f)
		{
			for (Map& map : sMaps)
				map.applyInput(Mouse::Axis::MoveY, yOffset);
		}
	}

	void Manager::gamepadConnectionChange(Gamepad& gamepad)
	{
		sGamepadConnectionChangeEvent(gamepad);
	}

	void Manager::dropCallback(const std::vector<std::string_view>& paths)
	{
		sDropEvent(paths);
	}
}
