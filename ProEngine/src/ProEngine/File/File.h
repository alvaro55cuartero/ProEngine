#pragma once

namespace Pro
{
	class File
	{
	public:
		static std::string Load(const std::string& path);
		static void Save(const std::string& source, const std::string& path);

		static void SavePNG(const std::string& name, const int& width, const int& height, const void* data, const uint32_t& components);
	};
}
