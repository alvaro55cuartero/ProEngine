#include "Propch.h"
#include "ProEngine/File/FBX/FBX.h"
#include "ProEngine/File/File.h"
#include <string_view>


using namespace std::literals;

namespace Pro {

	void PrintVariant(Pro::Node::Property property, std::string& text)
	{
		text += "{\n";
		if (const int16_t* pval = std::get_if<int16_t>(&property))
		{
			text += "\"type\":\"int16\",\n";
			text += "\"value\":";
			text += std::to_string(*pval);
			text += '\n';
		}
		else if (const bool* pval = std::get_if<bool>(&property))
		{
			text += "\"type\":\"bool\",\n";
			text += "\"value\":";
			if (*pval) {
				text += "true";
			}
			else
			{
				text += "false";
			}
			text += '\n';
		}
		else if (const int32_t* pval = std::get_if<int32_t>(&property))
		{
			text += "\"type\":\"int32\",\n";
			text += "\"value\":";
			text += std::to_string(*pval);
			text += '\n';
		}
		else if (const float* pval = std::get_if<float>(&property))
		{
			text += "\"type\":\"float\",\n";
			text += "\"value\":";
			text += std::to_string(*pval);
			text += '\n';
		}
		else if (const double* pval = std::get_if<double>(&property))
		{
			text += "\"type\":\"double\",\n";
			text += "\"value\":";
			text += std::to_string(*pval);
			text += '\n';
		}
		else if (const int64_t* pval = std::get_if<int64_t>(&property))
		{
			text += "\"type\":\"int64\",\n";
			text += "\"value\":";
			text += std::to_string(*pval);
			text += '\n';
		}
		else if (const std::string* pval = std::get_if<std::string>(&property))
		{
			text += "\"type\":\"string\",\n";
			text += "\"value\":\"";
			text += *pval;
			text += '\"\n';
		}
		else if (const std::vector<float>* pval = std::get_if<std::vector<float>>(&property))
		{
			text += "\"type\":\"ArrayFloat\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				text += std::to_string((*pval)[0]);
				if (i < (*pval).size() - 1)
					text += ",\n";
			}
			text += "]\n";
		}
		else if (const std::vector<int32_t>* pval = std::get_if<std::vector<int32_t>>(&property))
		{
			text += "\"type\":\"ArrayInt32\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				text += std::to_string((*pval)[0]);
				if (i < (*pval).size() - 1)
					text += ",\n";
			}
			text += "]\n";
		}
		else if (const std::vector<double>* pval = std::get_if<std::vector<double>>(&property))
		{
			text += "\"type\":\"ArrayDouble\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				text += std::to_string((*pval)[0]);
				if (i < (*pval).size() - 1)
					text += ",\n";
			}
			text += "]\n";
		}
		else if (const std::vector<int64_t>* pval = std::get_if<std::vector<int64_t>>(&property))
		{
			text += "\"type\":\"ArrayInt64\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				text += std::to_string((*pval)[0]);
				if (i < (*pval).size() - 1)
					text += ",\n";
			}
				text += "]\n";
		}
		else if (const std::vector<bool>* pval = std::get_if<std::vector<bool>>(&property))
		{
			text += "\"type\":\"ArrayBool\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				if ((*pval)[0]) {
					text += "true";
				}
				else
				{
					text += "false";
				}
				if (i < (*pval).size() - 1)
					text += ",\n";
			}
			text += "]\n";
		}
		else if (const std::vector<char>* pval = std::get_if<std::vector<char>>(&property))
		{
			text += "\"type\":\"ArrayChar\",\n";
			text += "\"value\":[\n";
			for (int i = 0; i < (*pval).size(); i++)
			{
				text += std::to_string((int)((*pval)[0]));
				if (i < (*pval).size()-1)
					text += ",\n";
			}
			text += "]\n";
		}
		else
		{
			std::cout << "ERROR\n";
		}
		text += "}";
	}


	std::string Print(Node node)
	{
		std::string text;
		text += "{\n";
		
		text += "\"EndOffset\":";
		text += std::to_string(node.endOffset);
		text += ",\n";

		text += "\"NumProperties\":";
		text += std::to_string(node.numProperties);
		text += ",\n";
		
		text += "\"PropertyListLen\":";
		text += std::to_string(node.propertyListLen);
		text += ",\n";
		
		text += "\"NameLen\":";
		text += std::to_string(node.nameLen);
		text += ",\n";
		
		text += "\"Name\":\"";
		text += node.name; 
		text += "\",\n";
		
		text += "\"Properties\":[\n";
		for (int i = 0; i < node.numProperties; i++)
		{
			PrintVariant(node.properties[i], text);
			if (i < node.numProperties - 1)
				text += ",\n";
		}
		text += "],\n";

		text += "\"Children\":[\n";
		for (int i = 0; i < node.children.size(); i++)
		{
			text += Print(node.children[i]);
			
			if (i < node.children.size() - 1)
				text += ",\n";
		}
		text += "]\n";
		
		text += "}";

		return text;
	}



	FBX::FBX(std::string path)
		: stream(Stream(path))
	{
		

		// Read Header

		if (stream.Check("Kaydara FBX Binary  \00\x1a\x00"sv))
			throw std::invalid_argument("Invalid header, file is not an FBX binary file " + path);

		// Read Version

		uint32_t version = stream.Read<uint32_t>();
		
		if (version < 7500) {
			//blockLength = 13;
			//isuInt32 = true;
		}
		else {
			//blockLength = 25;
			//isuInt32 = false;
		}
		
		//blockData = std::vector(blockLength, '\0');
		

		Node root;
		std::string text = "";
		text += "[\n";
		while (stream.Tell() <= stream.size) {
			//std::cout << stream.Tell() << std::endl << std::endl;
			Node child;
			
			if (!ReadNode(child)) break;

			root.children.push_back(child);
			//std::cout << "\n";
			text += Print(child);
			text += ",\n";
		}
		text += "]\n";

		Pro::File::Save(text, "a.json");
		

		std::cout << "a";
		
	}

	bool FBX::ReadNode(Node& node)
	{

		node.endOffset = stream.Read<uint32_t>();
		node.numProperties = stream.Read<uint32_t>();
		node.propertyListLen = stream.Read<uint32_t>();
		node.nameLen = stream.Read<uint8_t>();
		node.name = stream.Read<std::string>(node.nameLen);
		
		if (node.endOffset == 0)
			return false;
		
		for (int i = 0; i < tabs; i++ ) {
			//std::cout << "  ";
		}

		node.properties.resize(node.numProperties);

		ReadNodeProperties(node);

		int a = node.endOffset;
		while (stream.Tell() < node.endOffset) {
			tabs++;
			Node child;
			ReadNode(child);
			node.children.push_back(child);
			tabs--;
		}

		return true;
	}

	


	void FBX::ReadNodeProperties(Node& node)
	{
		for (size_t i = 0; i < node.numProperties; i++) {
			auto dataType = stream.Read<char>();
			switch (dataType) {
			
			case 'C':
				node.properties[i] = stream.Read<bool>(); /// 1 bit bool
				break;
			
			case 'I':
				node.properties[i] = stream.Read<int32_t>(); /// 32 bit int
				break;
			
			case 'L':
				node.properties[i] = stream.Read<int64_t>(); /// 64 bit int
				break;

			case 'Y':
				node.properties[i] = stream.Read<int16_t>(); /// 16 bit int
				break;

			case 'F':
				node.properties[i] = stream.Read<float>(); /// 32 bit float
				break;

			case 'D':			
				node.properties[i] = stream.Read<double>(); /// 64 bit float (double)
				break;

			case 'R':
				node.properties[i] = stream.ReadArray<char>(stream.Read<uint32_t>()); /// binary data
				break;
			
			case 'S':
				node.properties[i] = stream.Read<std::string>(stream.Read<uint32_t>());/// string
				break;
			
			case 'i':
				node.properties[i] = ReadArray<int32_t>(); /// array of 32 bit int
				break;
			
			case 'l':
				node.properties[i] = ReadArray<int64_t>(); /// array of 64 bit int
				break;
			
			case 'f':
				node.properties[i] = ReadArray<float>(); /// array of 32 bit float
				break;

			case 'd':
				node.properties[i] = ReadArray<double>(); /// array of 64 bit float (double)
				break;
			
			case 'b':
				node.properties[i] = ReadArray<char>(); /// array of 1 bit boolean
				break;
			
			case 'c':
				node.properties[i] = ReadArray<char>(); /// array of bytes
				break;

			default:
				std::cout << "No implementado: " << dataType << std::endl;
				break;
			}
		}

		
	}


	




	FBX FBX::Import(std::string path) 
	{
		return FBX(path);
	}
}