#pragma once
#include "ActionInstance.hpp"
#include <unordered_map>
#include <span>

namespace input
{
	struct Mapping
	{
		//Can contain anything you want
		std::any userData;
		//These modifiers are applied to each new input
		std::vector<std::shared_ptr<IModifier>> modifiers;
		//The corresponding action instance
		ActionInstance& actionInstance;
	};

	class Map : public Uncopyable
	{
	public:
		/*!
		 * @brief Maps binding to action
		 * @param binding Can be bound to one action per map
		 * @param action Can be bound once per map
		 * @param modifiers All the modifiers for this mapping
		 * @return The created mapping, is nullptr if the binding was already present
		 */
		Mapping* add(const Binding& binding, const std::shared_ptr<Action>& action, std::initializer_list<const std::shared_ptr<IModifier>> modifiers);
		/*!
		 * @brief Maps binding to action
		 * @param binding Can be bound to one action per map
		 * @param action Can be bound once per map
		 * @param modifiers All the modifiers for this mapping
		 * @return The created mapping, is nullptr if the binding was already present
		 */
		Mapping* add(const Binding& binding, const std::shared_ptr<Action>& action, std::span<const std::shared_ptr<IModifier>> modifiers = {});
		/*!
		* @brief Adds a new mapping to an actionInstance, it will not be added if the mapping already exists
		* @param instance The instance to map
		* @param binding The new binding
		* @param modifiers The mapping modifiers
		* @return The created mapping, is nullptr if the binding was already present
		*/
		Mapping* addMapping(ActionInstance& instance, const Binding& binding, std::initializer_list<const std::shared_ptr<IModifier>> modifiers);
		/*!
		* @brief Adds a new mapping to an actionInstance, it will not be added if the mapping already exists
		* @param instance The instance to map
		* @param binding The new binding
		* @param modifiers The mapping modifiers
		* @return The created mapping, is nullptr if the binding was already present
		*/
		Mapping* addMapping(ActionInstance& instance, const Binding& binding, std::span<const std::shared_ptr<IModifier>> modifiers = {});
		/*!
		* @brief Modify the binding of a mapping, oldBinding must exist and new binding must not
		* @oldBinding The binding of the mapping that will be changed
		* @newBinding The binding that will replace oldBinding
		* @return true if the mapping has changed
		*/
		bool setMapping(ActionInstance& instance, const Binding& oldBinding, const Binding& newBinding);
		//Returns the mappings
		[[nodiscard]] const std::unordered_map<Binding, Mapping>& bindingToMapping() const;

	private:
		void applyInput(const Binding& binding, ActionValue value);
		void callEvents();

		std::unordered_map<Binding, Mapping> mBindingToMapping;
		std::unordered_map<std::shared_ptr<Action>, ActionInstance> mActionToInstance;
		
		friend class Manager;
		friend class Gamepad;
	};
}
