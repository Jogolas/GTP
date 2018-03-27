#pragma once
#include "Collider.h"
#include "SDL.h"

class AABB;

class CollisionData
{
public:
	CollisionData() {}

	//// Based on the work of Marco Gilardi's from IPM 
	//static bool xCollision(const AABB* const aabb1, const AABB* const aabb2);
	//static bool yCollision(const AABB* const aabb1, const AABB* const aabb2);
	//static bool zCollision(const AABB* const aabb1, const AABB* const aabb2);
	//static bool AABBCollisionTest(const AABB* const aabb1, const AABB* const aabb2);
	//bool groundCollision(Entity* object1, Entity* Object2);
	//bool playerObjectCollision(Entity* object1, Entity* object2);



	//getting to the point of no return here, if its not working now, a working version is getting created, regardless if its good or bad.
	bool ClipLine(GLuint d, const AABB& aabbBox, const glm::vec3& v0, const glm::vec3& v1, GLfloat& f_low, GLfloat& f_high);
	bool lineAABBIntersection(const AABB& aabbBox, const glm::vec3& vBegin, const glm::vec3 vEnd, glm::vec3 vecIntersection, GLfloat fFraction);
	bool CollisionAgainstPlane(Collider* source, Collider* plane);
	bool CollisionAgainstBox(Collider* source, Collider* target);
	bool AABBIntersection(const AABB& source, const AABB& target);

};