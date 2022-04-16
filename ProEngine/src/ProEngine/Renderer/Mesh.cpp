#include "Propch.h"
#include "Mesh.h"

namespace Pro
{
	void Mesh::AddVertex(Vec3 position, Vec4 color, Vec2 texCoord, float textIndex)
	{
		m_position.push_back(position);
		m_color.push_back(color);
		m_texCoord.push_back(texCoord);
		m_textIndex.push_back(textIndex);
	}

	void Mesh::AddSquare(Pro::Vec3 pos, Pro::Vec3 size, Vec4 color, float textIndex, Pro::Ref<Pro::Sprite> sprite)
	{

		AddVertex(pos + QuadVertexPositions[0], color, sprite->GetPos(), textIndex);
		AddVertex(pos + QuadVertexPositions[1], color, { sprite->GetPos().x,  sprite->GetDim().y }, textIndex);
		AddVertex(pos + QuadVertexPositions[2], color, { sprite->GetDim().x,  sprite->GetPos().y }, textIndex);
		AddVertex(pos + QuadVertexPositions[3], color, sprite->GetDim(), textIndex);

		m_indices.push_back((count * 4) + 0);
		m_indices.push_back((count * 4) + 1);
		m_indices.push_back((count * 4) + 2);
		m_indices.push_back((count * 4) + 2);
		m_indices.push_back((count * 4) + 1);
		m_indices.push_back((count * 4) + 3);

		count++;
	}

	void Mesh::AddSquare(Pro::Mat4 transform, Vec4 color, float textIndex, Pro::Ref<Pro::Sprite> sprite)
	{
		AddVertex(transform * QuadVertexPositions[0], color, sprite->GetPos(), textIndex);
		AddVertex(transform * QuadVertexPositions[1], color, { sprite->GetPos().x,  sprite->GetDim().y }, textIndex);
		AddVertex(transform * QuadVertexPositions[2], color, { sprite->GetDim().x,  sprite->GetPos().y }, textIndex);
		AddVertex(transform * QuadVertexPositions[3], color, sprite->GetDim(), textIndex);


		m_indices.push_back((count * 4) + 0);
		m_indices.push_back((count * 4) + 1);
		m_indices.push_back((count * 4) + 2);
		m_indices.push_back((count * 4) + 2);
		m_indices.push_back((count * 4) + 1);
		m_indices.push_back((count * 4) + 3);

		count++;
	}



	std::vector<float> Mesh::GetVertices()
	{
		std::vector<float> vertices;

		for (int i = 0; i < count; i++)
		{

			vertices.push_back(m_position[i].x);
			vertices.push_back(m_position[i].y);
			vertices.push_back(m_position[i].z);

			vertices.push_back(m_color[i].x);
			vertices.push_back(m_color[i].y);
			vertices.push_back(m_color[i].z);
			vertices.push_back(m_color[i].w);

			vertices.push_back(m_texCoord[i].x);
			vertices.push_back(m_texCoord[i].y);

			vertices.push_back(m_textIndex[i]);
		}


		return vertices;
	}
}