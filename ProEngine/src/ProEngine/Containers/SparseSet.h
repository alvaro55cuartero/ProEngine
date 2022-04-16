#pragma once
#include <vector>


namespace Pro {
	template <typename...>
	class SparseSet
	{
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


	public:
		SparseSet() = default;

		uint32_t Emplace(uint32_t index)
		{
			if (index >= spread.size())
			{
				spread.resize(index + 1);
			}

			spread[index] = packed.size();
			packed.push_back(index);

			return packed.back();
		}

		size_t Size()
		{
			return packed.size();
		}


		bool Has(uint32_t index) 
		{
			if (spread.size() <= index) return false;
			if (packed[spread[index]] != index) return false;

			return true;
		}

		Iterator begin()
		{
			return Iterator(packed, 0);
		}

		Iterator end()
		{
			return Iterator(packed, packed.size());
		}


	protected:
		std::vector<uint32_t> spread;
		std::vector<uint32_t> packed;
	};



	template <typename Component>
	class SparseSet<Component> : public SparseSet<>
	{
	public:
		SparseSet() = default;

		template<typename... Args>
		Component& Emplace(uint32_t index, Args&&... args)
		{
			SparseSet<>::Emplace(index);
			components.push_back({ std::forward<Args>(args)... });

			return components.back();
		}


		Component& Get(uint32_t index)
		{
			return components[spread[index]];
		}

	private:
		std::vector<Component> components;
	};

}
