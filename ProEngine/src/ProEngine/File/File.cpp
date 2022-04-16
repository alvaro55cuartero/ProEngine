#include "Propch.h"
#include "File.h"
#include "stb_image_write.h"

namespace Pro
{
	std::string File::Load(const std::string& path)
	{
		std::ifstream in(path);
		std::stringstream buffer;
		buffer << in.rdbuf();
		return buffer.str();
	}

	void File::Save(const std::string& source, const std::string& path)
	{
		std::ofstream out(path, std::ofstream::out);
		out << source;
		out.close();
	}

	void File::SavePNG(const std::string& name, const int& width, const int& height, const void* data, const uint32_t& components)
	{
		stbi_write_png(name.c_str(), width, height, components, data, width * components);
	}


}