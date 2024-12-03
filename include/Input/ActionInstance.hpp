#pragma once
#include "ActionValue.hpp"
#include <span>

namespace input
{
	using Event = Delegate<const ActionValue&>;

	class ActionInstance : public Uncopyable
	{
	public:
		ActionInstance() = default;
		explicit ActionInstance(const std::shared_ptr<Action>& action);
		const std::shared_ptr<Action>& action() const;
		const ActionValue& value() const;
		Event& callback();
		
	private:
		void applyInput(const Binding& binding, const ActionValue& value);
		void callEvent();

		std::shared_ptr<Action> mAction;
		Event mCallback;
		ActionValue mValue;
		bool mChanged;

		friend class Map;
	};
}