#pragma once
#include "Map.hpp"
#include "Cursor.hpp"
#include "Clipboard.hpp"

namespace input
{
	//The parameter is the gamepad whose connection has changed
	using GamepadConnectionChangeEvent = Delegate<Gamepad&>;
	//Triggered when paths or files are dropped on a window, the parameter is a vector containing the file paths
	using DropEvent = Delegate<const std::vector<std::string_view>&>;
	
	class Manager
	{
	public:
		Manager() = delete;
		//Polls and calls new events
		static void pollEvents();
		//Returns the active maps
		[[nodiscard]] static std::vector<Map>& maps();
		//Returns all the currently connected gamepads
		[[nodiscard]] static std::vector<Gamepad*>& gamepads();

		//Returns the gamepad connection change event
		[[nodiscard]] static GamepadConnectionChangeEvent& gamepadConnectionChangeEvent();
		//Returns the drop event
		[[nodiscard]] static DropEvent& dropEvent();

	private:
		static void keyCallback(Key key, int scancode, int action, int mods);
		static void mouseButtonCallback(Mouse::Button button, int action, int mods);
		static void scrollCallback(float xOffset, float yOffset);
		static void mouseMoveCallback(float xOffset, float yOffset);
		static void gamepadConnectionChange(Gamepad& gamepad);
		static void dropCallback(const std::vector<std::string_view>& paths);

		static std::vector<Map> sMaps;
		static GamepadConnectionChangeEvent sGamepadConnectionChangeEvent;
		static DropEvent sDropEvent;

		friend class Impl;
	};
}
