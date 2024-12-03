#include "Input/ActionInstance.hpp"

namespace input
{
	ActionInstance::ActionInstance(const std::shared_ptr<Action>& action) :
		mAction(action),
		mValue(action->type),
		mChanged(false) {}

	const std::shared_ptr<Action>& ActionInstance::action() const
	{
		return mAction;
	}

	const ActionValue& ActionInstance::value() const
	{
		return mValue;
	}

	Event& ActionInstance::callback()
	{
		return mCallback;
	}

	void ActionInstance::applyInput(const Binding& binding, const ActionValue& value)
	{
		mChanged = true;
		mValue += value;
	}

	void ActionInstance::callEvent()
	{
		if (mChanged)
		{
			mChanged = false;
			mCallback(mAction->applyModifiers(mValue));
		}
	}
}