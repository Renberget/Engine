#include "Input/Action.hpp"
#include "Input/ActionValue.hpp"

namespace input
{
	Action::Action(Type type, const std::any& userData) : type(type), userData(userData) {}

	ActionValue Action::applyModifiers(ActionValue value) const
	{
		for (const std::shared_ptr<IModifier>& modifier : modifiers)
			modifier->apply(value);
		return value;
	}
}