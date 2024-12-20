#pragma once
#include "Maths/Math.hpp"

namespace input
{
	class ActionValue;

	struct IModifier
	{
		virtual ~IModifier() = default;
		virtual void apply(ActionValue& value) = 0;
	};

	struct NormalizeModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;
	};

	struct NegateModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;
	};

	struct SwapAxesModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;
	};

	struct ScaleModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;

		Vec2f scale;
	};

	struct ClampModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;

		Vec2f min;
		Vec2f max;
	};

	struct DeadZoneModifier : public IModifier
	{
		virtual void apply(ActionValue& value) override;

		float threshold;
	};
}
