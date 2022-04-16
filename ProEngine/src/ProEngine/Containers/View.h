#pragma once
#include <tuple>
#include "SparseSet.h"


namespace Pro
{

	template <typename Type, typename... Types>
	class View
	{


		class Iterator
		{
		private:
			bool valid() const
			{
				uint32_t index = *pos;
				bool check = std::get<SparseSet<Type>&>(data).Has(index);

				bool acc[] = { (check = check && std::get<SparseSet<Types>&>(data).Has(index))... };
				(void)acc;

				return check;
			}



		public:
			Iterator(std::tuple<SparseSet<Type>&, SparseSet<Types>&...>& data, SparseSet<>::Iterator pos, SparseSet<>::Iterator end )
				: data(data), pos(pos), end(end)
			{
				if (pos != end && !valid()) {
					++(*this);
				}
			}


			bool operator==(const Iterator& other)
			{
				return pos == other.pos;
			}


			bool operator!=(const Iterator& other)
			{
				return !(*this == other);
			}

			Iterator& operator++()
			{
				++pos;

				while (pos != end && !valid()) { ++pos; }
				
				return *this;
			}

			uint32_t operator*()
			{
				return *pos;
			}


		private:
			const std::tuple<SparseSet<Type>&, SparseSet<Types>&...> & data;
			SparseSet<>::Iterator pos;
			SparseSet<>::Iterator end;
		};

	private:
		template<typename T>
		SparseSet<T>& GetSet()
		{
			return std::get<SparseSet<T>&>(data);
		}

	public:

		View(SparseSet<Type>& first, SparseSet<Types>&... sets)
			: data{ first, sets... }
		{
			smallest = &first;
			auto a = GetSet<Type>().Size();
			void* acc[] = {(sets.Size() < smallest->Size() ? (smallest = &sets) : nullptr) ...};
			(void)acc;

		}


		Iterator begin() 
		{
			return Iterator(data, smallest->begin(), smallest->end());
		}

		Iterator end() 
		{
			return Iterator(data, smallest->end(), smallest->end());
		}
		



	private:

		std::tuple<SparseSet<Type>&, SparseSet<Types>&...> data;
		SparseSet<>* smallest;
	};



	template <typename Type>
	class View<Type>
	{
	public:

		View(SparseSet<Type>& first)
			: data{ first }
		{}


		SparseSet<Type>::Iterator begin()
		{
			return data.begin();
		}

		SparseSet<Type>::Iterator end()
		{
			return data.end();
		}

	private:

		SparseSet<Type>& data;
	};
}