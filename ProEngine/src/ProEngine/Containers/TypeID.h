#pragma once

namespace Pro
{
	template <typename...>
	class TypeID
	{

	public:

		static inline std::size_t counter = 0;

		template<typename...>
		static std::size_t type() {
			static const std::size_t value = counter++;
			return value;
		}
	};
}