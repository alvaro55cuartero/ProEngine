#pragma once
#include <string>
#include "ProEngine/File/File.h"

namespace Pro
{
	class Font
	{

	public:
		static Ref<Font> Load(const std::string& path);
		static Ref<Font> LoadFromSource(const std::string& source);

	};
}