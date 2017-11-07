// Based on the work of Marco Gilardi's from IPM

#pragma once
#include "glm\glm\glm.hpp"
#include "AABB.h"
#include "CollisionDetection.h"
#include "GameObject.h"
#include "Utils.h"
#include "Entity.h"

class AABB;

class CollisionData
{
public:
	CollisionData() {}

	static bool xCollision(const AABB* const aabb1, const AABB* const aabb2);
	static bool yCollision(const AABB* const aabb1, const AABB* const aabb2);
	static bool zCollision(const AABB* const aabb1, const AABB* const aabb2);
	static bool AABBCollisionTest(const AABB* const aabb1, const AABB* const aabb2);

	bool groundCollision(Entity* object1, Entity* Object2);
	bool playerObjectCollision(Entity* object1, Entity* object2);

private:
	
};
