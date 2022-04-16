#pragma once
#pragma once
#include <unordered_map>



template<typename ...>
struct Holder {};

template <typename T>
class Holder<T> : public Holder<>
{
	typedef T Type;
	T type;
};

class TypeStorage
{
public:

	template<typename T>
	void AddClass(std::string name)
	{
		m_map[name] = Holder<T>();
	}

	void CreateClass(std::string name)
	{
		auto a = m_map[name];
		decltype(a);

	}

private:

	std::unordered_map<std::string, Holder<>> m_map;
};