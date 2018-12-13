//
// Created by armandmgt on 12/13/18.
//

#pragma once

#include <atomic>

namespace AwesomeECS {
	constexpr std::size_t MAX_COMPONENTS = 256;

	using TypeId = std::size_t;

	template<typename C>
	class ClassTypeId {
	public:
		constexpr ClassTypeId() = default;
		template<typename T>
		static TypeId getTypeId() noexcept {
			static const TypeId id = nextClassId++;
			return id;
		}

	private:
		static std::atomic<TypeId> nextClassId;
	};

	template<typename C>
	inline std::atomic<TypeId> ClassTypeId<C>::nextClassId = 0;
}
