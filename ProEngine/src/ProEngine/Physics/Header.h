#pragma once
#include "ProEngine/Math/Vec2.h"

namespace Pro
{
	struct AABB
	{
		Vec2 pos;
		Vec2 dim;

		float getX() { return pos.x; };
	};


	namespace Collision	
	{

		static bool test(AABB a, AABB b)
		{
			return true;
		}

	}
}