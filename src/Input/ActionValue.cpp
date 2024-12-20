#include "Input/ActionValue.hpp"

namespace input
{
	ActionValue::ActionValue(Action::Type type) : mValue(Vec2f::zero()), mType(type) {}

	ActionValue::ActionValue(bool value) : mValue(value ? 1.f : -1.f, 0.f), mType(Action::Type::Button) {}

	ActionValue::ActionValue(float value) : mValue(value, 0.f), mType(Action::Type::Axis1D) {}

	ActionValue::ActionValue(Vec2f value) : mValue(value), mType(Action::Type::Axis2D) {}

	Action::Type ActionValue::type() const
	{
		return mType;
	}

	const Vec2f& ActionValue::value() const
	{
		return mValue;
	}

	Vec2f& ActionValue::value()
	{
		return mValue;
	}

	ActionValue& ActionValue::operator+=(const ActionValue& other)
	{
		mType = std::max(mType, other.mType);
		mValue += other.mValue;
		return *this;
	}
}