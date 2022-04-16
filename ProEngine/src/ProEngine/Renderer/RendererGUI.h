#pragma once
#include <ProEngine/Renderer/Cameras/OrthographicCamera.h>
//#include "imgui.h"

namespace Pro 
{
	class RendererGUI 
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(Camera& camera);
		static void EndScene();

		static void Flush();


		static void DrawQuad(const Vec2& position, const Vec2& size, const Vec4& color);
		
		static void AddDataToBuffer(const Vec2& position, const Vec2& size, const Vec4& color, float texIndex, float tilingFactor);

	};
}