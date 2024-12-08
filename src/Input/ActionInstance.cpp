#include "Input/ActionInstance.hpp"

namespace input
{
	ActionInstance::ActionInstance(const std::shared_ptr<Action>& action) :
		mAction(action),
		mValue(action->type),
		mModifiedValue(action->type),
		mChanged(false) {}

	const std::shared_ptr<Action>& ActionInstance::action() const
	{
		return mAction;
	}

	const ActionValue& ActionInstance::value() const
	{
		return mModifiedValue;
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
			mModifiedValue = mAction->applyModifiers(mValue);
			mCallback(mModifiedValue);
		}
	}
}
