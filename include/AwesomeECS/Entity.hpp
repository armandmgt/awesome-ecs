//
// Created by armandmgt on 12/13/18.
//

#pragma once

#include <array>
#include <memory>
#include "Detail.hpp"
#include "Component.hpp"

namespace AwesomeECS {
	using EntityId = std::size_t;

	class Entity {
	public:
		Entity() = default;
		Entity(const Entity &rhs) = delete;
		Entity &operator=(const Entity &rhs) = delete;
		Entity(const Entity &&rhs) = delete;
		Entity &operator=(const Entity &&rhs) = delete;

		template<typename T>
		bool hasComponent() const noexcept {
			static_assert(std::is_base_of<Component, T>(), "Type parameter is not a base of Component");
			return componentArray[ClassTypeId<Component>::getTypeId<T>()];
		}

		template<typename T>
		T &getComponent() noexcept {
			static_assert(std::is_base_of<Component, T>(), "Type parameter is not a base of Component");
			return std::add_lvalue_reference_t<T>(*componentArray[ClassTypeId<Component>::getTypeId<T>()]);
		}

		template<typename T>
		const T &getComponent() const noexcept {
			static_assert(std::is_base_of<Component, T>(), "Type parameter is not a base of Component");
			return std::add_lvalue_reference_t<T>(*componentArray[ClassTypeId<Component>::getTypeId<T>()]);
		}

		template<typename T, typename... Args>
		void addComponent(Args&&... args) noexcept(noexcept(T{std::forward<Args>(args)...})) {
			static_assert(std::is_base_of<Component, T>(), "Type parameter is not a base of Component");
			componentArray[ClassTypeId<Component>::getTypeId<T>()] = std::make_unique<T>(std::forward<Args>(args)...);
		}

		template<typename T>
		void removeComponent() {
			static_assert(std::is_base_of<Component, T>(), "Type parameter is not a base of Component");
			componentArray[ClassTypeId<Component>::getTypeId<T>()].reset(nullptr);
		}

	private:
		static EntityId nextId;
		std::array<std::unique_ptr<Component>, MAX_COMPONENTS> componentArray;
	public:
		const EntityId id{nextId++};
	};

	inline EntityId Entity::nextId = 0;
}
