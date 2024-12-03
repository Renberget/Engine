#include "Input/Modifier.hpp"
#include "Input/ActionValue.hpp"

namespace input
{
	void NormalizeModifier::apply(ActionValue& value)
	{
		value.value().normalize();
	}

	void NegateModifier::apply(ActionValue& value)
	{
		value.value() = -value.value();
	}

	void SwapAxesModifier::apply(ActionValue& value)
	{
		std::swap(value.value().x, value.value().y);
	}

	void ScaleModifier::apply(ActionValue& value)
	{
		value.value().x *= scale.x;
		value.value().y *= scale.y;
	}

	void ClampModifier::apply(ActionValue& value)
	{
		value.value().x = std::max(min.x, std::min(value.value().x, max.x));
		value.value().y = std::max(min.y, std::min(value.value().y, max.y));
	}

	void DeadZoneModifier::apply(ActionValue& value)
	{
		if (value.value().sqrLength() < threshold * threshold)
			value.value() = { 0.f, 0.f };
	}
}
