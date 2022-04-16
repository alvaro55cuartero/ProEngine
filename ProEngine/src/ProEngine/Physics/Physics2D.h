#pragma once
#include "AABB.h"

namespace Pro
{
	namespace Physics
	{
		struct RaycastHit2D
		{
			Vec2 centroid; 		//The centroid of the primitive used to perform the cast.
			Entity entity;		//The entity hit by the ray.
			float distance;		//The distance from the ray origin to the impact point.
			float fraction;		//Fraction of the distance along the ray that the hit occurred.
			Vec2 normal;		//The normal vector of the surface hit by the ray.
			Vec2 point;			//The point in world space where the ray hit the collider's surface.
			//rigidbody	//The Rigidbody2D attached to the object that was hit.
			//transform	//The Transform of the object that was hit.
			bool hasCollide = false;
		};



		static RaycastHit2D Raycast(Vec2 origin, Vec2 direction, float distance, int layerMask, float minDepth, float maxDepth)
		{
			return RaycastHit2D();
		}

		/*

		void InsertAABBIntoList(AABB* pAABB)
		{
			// For all three axes
			for (int i = 0; i < 3; i++) {
				// Search from start of list
				Elem* pElem = gListHead[i];
				// Insert min cell at position where pElem points to first larger element.
				// Assumes large sentinel value guards from falling off end of list
				while (pElem->value[i] < pAABB->min.value[i])
					pElem = pElem->pRight[i];
				pAABB->Min.pLeft[i] = pElem->pLeft[i];
				pAABB->Min.pRight[i] = pElem;
				pElem->pLeft[i]->pRight[i] = &pAABB->min;
				pElem->pLeft[i] = &pAABB->min;
				// Insert max cell in the same way. Can continue searching from last
				// position as list is sorted. Also assumes sentinel value present
				while (pElem->value[i] < pAABB->max.value[i])
					pElem = pElem->pRight[i];
					pAABB->max.pLeft[i] = pElem->pLeft[i];
				pAABB->max.pRight[i] = pElem;
				pElem->pLeft[i]->pRight[i] = &pAABB->max;
				pElem->pLeft[i] = &pAABB->max;
			}
			// Now scan through list and add overlap pairs for all objects that
			// this AABB intersects. This pair tracking could be incorporated into
			// the loops above, but is not done here to simplify the code
			for (Elem* pElem = gListHead[0]; ; ) {
				if (pElem->minmax == MIN_ELEM) {
					if (pElem->value[0] > pAABB->max.value[0])
						break;
					if (AABBOverlap(pAABB, GetAABB(pElem)))
						AddCollisionPair(pAABB, GetAABB(pElem));
				}
				else if (pElem->value[0] < pAABB->min.value[0])
					break;
			}
		}

		struct Elem {
			AABB* pAABB; // Back pointer to AABB object (to find matching max/min element)
			Elem* pLeft; // Pointer to the previous linked list element
			Elem * pRight; // Pointer to the next linked list element
			float value; // The actual min or max coordinate value
			int minmax : 1; // A min value or a max value?
		};

		struct AABB {
			Elem* pMin[3]; // Pointers to the three minimum interval values (one for each axis)
			Elem* pMax[3]; // Pointers to the three maximum interval values (one for each axis)
			//Object* pObj; // Pointer to the actual object contained in the AABB
		};

		AABB * GetAABB(Elem * pElem)
		{
			return (AABB*)(pElem->minmax ? (pElem - 1) : pElem);
		}

		enum {
			MIN_ELEM = 0, // Indicates AABB minx, miny, or minz element
			MAX_ELEM = 1 // Indicates AABB maxx, maxy, or maxz element
		};

		void InitializeAABBList()
		{
			AABB *pSentinel = new AABB[1];
			for (int i = 0; i < 2; i++) {
				pSentinel[0].pMin;
					//->pLeft[i] = NULL; // not strictly needed
				//pSentinel[0].pMin.pRight[i] = &pSentinel->pMax;
				//pSentinel[0].pMax.pLeft[i] = &pSentinel->pMin;
				//pSentinel[0].pMax.pRight[i] = NULL; // not strictly needed
				//pSentinel[0].pMin.value[i] = -FLT_MAX;
				//pSentinel[0].pMax.value[i] = FLT_MAX;
				//gListHead[i] = &pSentinel->min;
			}
			// Note backwardness of initializing these two
			//pSentinel[0].min.minmax = MAX_ELEM;
			//pSentinel[0].max.minmax = MIN_ELEM;
		}
		*/
		
	}
}