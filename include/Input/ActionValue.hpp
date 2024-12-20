#pragma once
#include "Action.hpp"
#include <stdexcept>

namespace input
{
	class ActionValue
	{
	public:
		ActionValue(Action::Type type);
		ActionValue(bool value);
		ActionValue(float value);
		ActionValue(Vec2f value);
		Action::Type type() const;
		const Vec2f& value() const;
		Vec2f& value();
		ActionValue& operator+=(const ActionValue& other);
		template<typename T>
		T get() const;
		template<>
		bool get() const
		{
#ifndef NDEBUG
			if (mType != Action::Type::Button)
				throw std::runtime_error("Wrong action type");
#endif
			constexpr float Epsilon = 1.0e-5f;
			return !(math::nearlyEquals(mValue.x, 0.f, Epsilon) && math::nearlyEquals(mValue.y, 0.f, Epsilon));
		}
		template<>
		float get() const
		{
#ifndef NDEBUG
			if (mType != Action::Type::Axis1D)
				throw std::runtime_error("Wrong action type");
#endif
			return mValue.x;
		}
		template<>
		Vec2f get() const
		{
#ifndef NDEBUG
			if (mType != Action::Type::Axis2D)
				throw std::runtime_error("Wrong action type");
#endif
			return mValue;
		}

	private:
		Vec2f mValue;
		Action::Type mType;
	};
}