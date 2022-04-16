#include "Propch.h"
#include "PixelPerfectCamera.h"


namespace Pro
{

	Mat4 PixelPefrProj(uint32_t width, uint32_t height)
	{
		Mat4 proj(1.0f);

		proj[0][0] = 2.0 / width;
		proj[1][1] = 2.0 / height;


		proj[3][0] = -1;
		proj[3][1] = -1;

		return proj;
	}


	PixelPerfectCamera::PixelPerfectCamera(uint32_t width, uint32_t height)
		: Camera(PixelPefrProj(width, height), Mat4(1.0f))
	{

	}



}