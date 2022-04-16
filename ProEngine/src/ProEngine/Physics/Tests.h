#pragma once
#include "AABB.h"
#include "ProEngine/Math/Vec2.h"

namespace Pro
{
	namespace Physics
	{
		struct Ray2D
		{
			Vec2 origin;

		};



		static bool TestAABBAABB(AABB a, AABB b)
		{
			if (abs(a.Center[0] - b.Center[0]) > (a.Radius[0] + b.Radius[0])) return false;
			if (abs(a.Center[1] - b.Center[1]) > (a.Radius[1] + b.Radius[1])) return false;
			if (abs(a.Center[2] - b.Center[2]) > (a.Radius[2] + b.Radius[2])) return false;
			return true;
		}

		static bool IntersectMovingAABBAABB(AABB a, AABB b, Vec2 va, Vec2 vb, float& tfirst, float& tlast)
		{
			// Exit early if ‘a’ and ‘b’ initially overlapping
			if (Pro::Physics::TestAABBAABB(a, b)) {
				tfirst = tlast = 0.0f;
				return true;
			}
			// Use relative velocity; effectively treating ’a’ as stationary
			Pro::Vec2 v = vb - va;

			// Initialize times of first and last contact
			tfirst = 0.0f;
			tlast = 1.0f;

			// For each axis, determine times of first and last contact, if any
			for (int i = 0; i < 2; i++) {
				if (v[i] < 0.0f) {
					if (b.Max[i] < a.Min[i]) return 0; // Nonintersecting and moving apart
					if (a.Max[i] < b.Min[i]) tfirst = max((a.Max[i] - b.Min[i]) / v[i], tfirst);
					if (b.Max[i] > a.Min[i]) tlast = min((a.Min[i] - b.Max[i]) / v[i], tlast);
				}
				if (v[i] > 0.0f) {
					if (b.Min[i] > a.Max[i]) return 0; // Nonintersecting and moving apart
					if (b.Max[i] < a.Min[i]) tfirst = max((a.Min[i] - b.Max[i]) / v[i], tfirst);
					if (a.Max[i] > b.Min[i]) tlast = min((a.Max[i] - b.Min[i]) / v[i], tlast);
				}
				// No overlap possible if time of first contact occurs after time of last contact
				if (tfirst > tlast) return false;
			}
			return true;
		}
	
		/*
		bool Test(const Ray2D& ray, const AABB& a) {
			// 1: test origin compared to box
			if ((ray.origin.x > a.Max.x) || (ray.origin.y > a.Max.y)
				// 2: slope tests
				|| (ray.s_xy * a.Max.x - a.Min.y + ray.c_xy < 0)
				|| (ray.s_yx * a.Max.y - a.Min.x + ray.c_yx < 0)
				|| (ray.s_zy * a.Max.z - a.Min.y + ray.c_zy < 0)
				|| (ray.s_yz * a.Max.y - a.Min.z + ray.c_yz < 0)
				|| (ray.s_xz * a.Max.x - a.Min.z + ray.c_xz < 0)
				|| (ray.s_zx * a.Max.z - a.Min.x + ray.c_zx < 0))
				return false;

			return true; // 3: no intersection depth

			// 4: calc tMin
			float t = (a.pMin.x - ray.d.x) * ray.id.x;
			float t1 = (a.pMin.y - ray.d.y) * ray.id.y;
			if (t1 > t)
				t = t1;
			float t2 = (a.pMin.z - ray.d.z) * ray.id.z;
			if (t2 > t)
				t = t2;

			return (t < ray.tMax);

		}
		*/

		static bool TestYGrid(Vec2 origin, float d, AABB aabb)
		{
			int minX = aabb.Min.x;
			int maxX = aabb.Max.x;
			
			int minY = aabb.Min.y;
			int maxY = aabb.Max.y;

			bool direction = 0 < d;

			int originX = (int)origin.x;

			if (minX > originX || maxX <= originX) return false;
			
			if (direction)
			{
				if (origin.y >= maxY) return false;
				if (origin.y >= minY) return true;
				if (origin.y + d - 1 < minY) return false;
				return true;
			}
			else
			{
				if (origin.y < minY) return false;
				if (origin.y < maxY) return true;
				if (origin.y + d >= maxY) return false;
				return true;
			}

		}
	}
}