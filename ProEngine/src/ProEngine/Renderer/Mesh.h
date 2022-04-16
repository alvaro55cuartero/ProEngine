#pragma once

#include <vector>
#include <ProEngine/Math/Vec3.h>
#include <ProEngine/Math/Mat4.h>
#include <ProEngine/Core/Base.h>
#include <ProEngine/Renderer/Sprite/Sprite.h>


namespace Pro
{

	struct Vertex
	{
	public:
		Vertex() = default;
		Vertex(Vec3 position, Vec4 color, Vec2 texCoord, float textIndex)
			: position(position), color(color), texCoord(texCoord), textIndex(textIndex)
		{}

		Pro::Vec3 position;
		Pro::Vec4 color;
		Pro::Vec2 texCoord;
		float textIndex;

	};




	class Mesh
	{

		Pro::Vec4 QuadVertexPositions[4] = {
				{ -0.5f, -0.5f, 0.0f, 1},
				{ -0.5f,  0.5f, 0.0f, 1},
				{  0.5f, -0.5f, 0.0f, 1},
				{  0.5f,  0.5f, 0.0f, 1}
		};

	private:
		void AddVertex(Vec3 position, Vec4 color, Vec2 texCoord, float textIndex);
	
	public:



		void AddSquare(Pro::Vec3 pos, Pro::Vec3 size, Vec4 color,  float textIndex, Pro::Ref<Pro::Sprite> sprite);
		void AddSquare(Pro::Mat4 transform, Vec4 color, float textIndex, Pro::Ref<Pro::Sprite> sprite);


		std::vector<float> GetVertices();

	private:


		std::vector<Vec3> m_position;
		std::vector<Vec4> m_color;
		std::vector<Vec2> m_texCoord;
		std::vector<float> m_textIndex;
		std::vector<uint32_t> m_indices;

		int count = 0;

	};

}
