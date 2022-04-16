#pragma once

#include <string>
#include <vector>
#include <variant>

namespace Pro
{
	struct Node
	{
		using Property = std::variant<int16_t, bool, int32_t, float, double, int64_t, std::string, std::vector<float>, std::vector<int32_t>, std::vector<double>, std::vector<int64_t>, std::vector<bool>, std::vector<char>>;
		using PropertyList = std::vector<Property>;
		int32_t endOffset = 0;
		int32_t numProperties = 0;
		int32_t propertyListLen = 0;
		int32_t nameLen = 0;
		std::string name = "";
		std::vector<Node> children;
		PropertyList properties;

	};
}