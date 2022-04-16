#pragma once
#include <ProEngine/Renderer/Cameras/Camera.h>

namespace Pro
{

	

	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const Mat4& transform);
		static void EndScene();
		static void Flush();
	};

}

