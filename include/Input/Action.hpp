#pragma once
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Gamepad.hpp"
#include "Modifier.hpp"
#include "Utils/Uncopyable.hpp"
#include <memory>
#include <variant>
#include <any>

namespace input
{
	using Binding = std::variant<Key, Mouse::Axis, Mouse::Button, Gamepad::Axis, Gamepad::Button>;

	class ActionValue;

	struct Action : public Uncopyable
	{
		enum Type : uint8_t
		{
			Button,
			Axis1D,
			Axis2D
		};

		explicit Action(Type type, const std::any& userData = {});
		ActionValue applyModifiers(ActionValue value) const;

		//Can contain anything you want
		std::any userData;
		//These modifiers are applied just before the corresponding action instance callback is called
		std::vector<std::shared_ptr<IModifier>> modifiers;
		//The value type this action contains
		Type type;
	};
}