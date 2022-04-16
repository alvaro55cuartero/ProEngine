#include "Propch.h"
#include <ProEngine/Math/Vec3.h>


namespace Pro
{

	struct Vertex
	{
		Vec3 position;
	};
	
	struct MeshConstructorData
	{
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
	};

	static MeshConstructorData s_meshConstructorData;


	class MeshConstructor
	{
	public:

		static void AddTriangle(Vertex a)
		{
			s_meshConstructorData.vertices.push_back(a);
		}

		static void AddSquare(Vertex a)
		{
			s_meshConstructorData.vertices.push_back(a);
		}


		static void AddVertex(Vertex a)
		{
			s_meshConstructorData.vertices.push_back(a);
		}

		static Vertex* GetVertices(Vertex a)
		{
			return s_meshConstructorData.vertices.data();
		}

		static uint32_t* GetIndices(Vertex a)
		{
			return s_meshConstructorData.indices.data();
		}
 	};
};