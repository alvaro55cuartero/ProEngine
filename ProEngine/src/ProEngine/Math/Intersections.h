#pragma once
#include "Vec2.h"

namespace Pro
{
	namespace Math
	{
		static bool isInside(Pro::Vec2 position, Pro::Vec2 dimension, Pro::Vec2 point)
		{
			Pro::Vec2 pos2 = position + dimension;

			if (position.x < point.x && 
				position.y < point.y &&
				point.x < pos2.x &&
				point.y < pos2.y) {

				return true;
			}
			return false;
		}
	}
}