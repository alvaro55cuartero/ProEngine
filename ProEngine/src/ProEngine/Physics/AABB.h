#pragma once
#include "ProEngine/Math/Vec2.h"

namespace Pro
{
	namespace Physics
	{
		struct AABB
		{
		public:
			AABB() = default;

			AABB(Vec2 position, Vec2 scale)
				:Position(position), Scale(scale), Min(position), Max(position + scale)
			{}

			Pro::Vec2 Center;
			Pro::Vec2 Radius;
			Pro::Vec2 Position;
			Pro::Vec2 Scale;
			Pro::Vec2 Min;
			Pro::Vec2 Max;
		};
	}
}