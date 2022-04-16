#pragma once

#include <string>
#include <windows.h>

namespace Pro {

	class Stream
	{
	public:
		Stream(std::string path);
		size_t Tell();

		template<class T>
		T Read()
		{
			auto value = reinterpret_cast<T*>(data + cursor);
			cursor += sizeof(T);
			return *value;
		}

		template<class T>
		T Read(size_t bytes)
		{
			auto value = reinterpret_cast<T>(data + cursor);
			cursor += bytes;
			return value;
		}

		template<>
		std::string Read<std::string>(size_t bytes)
		{
			std::string value(data + cursor, bytes);
			cursor += bytes;
			return value;
		}

		template<typename T>
		std::vector<T> ReadArray(size_t bytes)
		{
			T* current = (T*)(data + cursor);
			std::vector<T> vector(current, current + bytes);
			cursor += bytes;
			return vector;
		}

		bool Check(std::string_view text)
		{

			std::string header = Read<std::string>(text.size());

			return text != std::string_view(header.c_str(), text.size());

		}


		size_t size;
	private:
		std::string path;
		size_t cursor = 0;
		char* data;
	};
}