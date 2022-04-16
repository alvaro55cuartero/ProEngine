#pragma once
#include <Tuple>
#include "SparseSet.h"
#include "TypeID.h"
#include "View.h"

namespace Pro
{


	class SparseMap
	{
		using typeIndex = TypeID<struct TypeIdentificator>;
	

	public:
		class Iterator
		{
		public:
			Iterator(const std::vector<uint32_t>& data, size_t pos) : data(data), pos(pos) {};

			Iterator& operator++()
			{
				pos++;
				return *this;
			}

			Iterator operator++(int) {
				Iterator orig = *this;
				return ++(*this), orig;
			}

			bool operator==(const Iterator& other)
			{
				return data == other.data && pos == other.pos;
			}

			bool operator!=(const Iterator& other)
			{
				return !(*this == other);
			}

			uint32_t operator*() const {
				return  data[pos];
			}


		public:
			const std::vector<uint32_t>& data;
			size_t pos;

		};



	private:
		template<typename Type>
		SparseSet<Type>& EnsureSet()
		{
			auto index = typeIndex::type<Type>();

			if (index >= data.size())
			{
				data.resize(index + 1);
			}

			if (!data[index]) {
				data[index] = std::make_unique<SparseSet<Type>>();
			}

			return static_cast<SparseSet<Type>&>(*data[index]);
		}

	public:

		

		template<typename Type, typename... Args>
		Type& Emplace(uint32_t index, Args&&... args)
		{
			return EnsureSet<Type>().Emplace(index, std::forward<Args>(args)...);
		}

		template<typename Type>
		bool Has(uint32_t index)
		{	
			return EnsureSet<Type>().Has(index);
		}

		template<typename Type>
		SparseSet<Type>& Get() 
		{
			return static_cast<SparseSet<Type>&>(*data[typeIndex::type<Type>()]);
		}

		template<typename Type>
		Type& Get(uint32_t index) 
		{
			return Get<Type>().Get(index);
		}

		template<typename... Types>
		View<Types...> GetView() 
		{
			return View<Types...> { EnsureSet<Types>()... };
		}


		void Clear()
		{
			data.clear();
		}

	private:
		std::vector<std::unique_ptr<SparseSet<>>> data;
		
	};
}