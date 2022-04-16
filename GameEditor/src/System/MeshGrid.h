#pragma once
#include "ProEngine.h"
#include <vector>

class MeshGrid
{
	struct Vertex
	{
		Pro::Vec3 position;
		Pro::Vec2 texCoord;
		float textIndex;
	};

public:
	MeshGrid();

	void AddTile(Pro::Vec2 position);

	std::vector<float> ToVectorArray()
	{
		std::vector<float> temp;
		for (auto vertex : m_vertices)
		{
			temp.push_back(vertex.position.x);
			temp.push_back(vertex.position.y);
			temp.push_back(vertex.position.z);
			temp.push_back(vertex.texCoord.x);
			temp.push_back(vertex.texCoord.x);
			temp.push_back(vertex.textIndex);
		}
	}

private:
	std::vector<Vertex> m_vertices;
	std::vector<uint32_t> m_indices;
};

