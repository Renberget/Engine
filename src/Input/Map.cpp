#include "Input/Map.hpp"

namespace input
{
	Mapping* Map::add(const Binding& binding, const std::shared_ptr<Action>& action, std::span<const std::shared_ptr<IModifier>> modifiers)
	{
		if (mBindingToMapping.contains(binding))
			return nullptr;

		auto it = mActionToInstance.find(action);
		ActionInstance& instance = it == mActionToInstance.end()
			? mActionToInstance.insert({ action, ActionInstance(action) }).first->second
			: it->second;

		return &mBindingToMapping.insert({ binding, Mapping{ std::any(), std::vector<std::shared_ptr<IModifier>>(modifiers.begin(), modifiers.end()), instance } }).first->second;
	}

	bool Map::addMapping(ActionInstance& instance, const Binding& binding, std::span<const std::shared_ptr<IModifier>> modifiers)
	{
		if (mBindingToMapping.contains(binding))
			return false;
		
		mBindingToMapping.insert({ binding, Mapping{ std::any(), std::vector<std::shared_ptr<IModifier>>(modifiers.begin(), modifiers.end()), instance }});
		return true;
	}

	bool Map::setMapping(ActionInstance& instance, const Binding& oldBinding, const Binding& newBinding)
	{
		if (!mBindingToMapping.contains(oldBinding) || mBindingToMapping.contains(newBinding))
			return false;

		auto node = mBindingToMapping.extract(oldBinding);
		node.key() = newBinding;
		mBindingToMapping.insert(std::move(node));
		return true;
	}

	const std::unordered_map<Binding, Mapping>& Map::bindingToMapping() const
	{
		return mBindingToMapping;
	}

	void Map::applyInput(const Binding& binding, ActionValue value)
	{
		auto it = mBindingToMapping.find(binding);
		if (it != mBindingToMapping.end())
		{
			for (const std::shared_ptr<IModifier>& modifier : it->second.modifiers)
				modifier->apply(value);
			it->second.actionInstance.applyInput(binding, value);
		}
	}

	void Map::callEvents()
	{
		for (auto it = mBindingToMapping.begin(); it != mBindingToMapping.end(); ++it)
			it->second.actionInstance.callEvent();
	}
}
