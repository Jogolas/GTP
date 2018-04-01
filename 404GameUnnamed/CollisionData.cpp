#include "CollisionData.h"
#include <iostream>

//// Sam yer code is in here commented out.
//bool CollisionData::xCollision(const AABB* const aabb1, const AABB* const aabb2)
//{
//	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
//	bool xCollision = (distance <= aabb1->getRadius().x + aabb2->getRadius().x);
//	return xCollision;
//}
//
//bool CollisionData::yCollision(const AABB* const aabb1, const AABB* const aabb2)
//{
//	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
//	bool yCollision = (distance <= aabb1->getRadius().y + aabb2->getRadius().y);
//	return yCollision;
//}
//
//bool CollisionData::zCollision(const AABB* const aabb1, const AABB* const aabb2)
//{
//	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
//	bool zCollision = (distance <= aabb1->getRadius().z + aabb2->getRadius().z);
//	return zCollision;
//}
//
//bool CollisionData::AABBCollisionTest(const AABB* const aabb1, const AABB* const aabb2)
//{
//	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
//
//	bool xCollision = CollisionData::xCollision(aabb1, aabb2);
//	bool yCollision = CollisionData::yCollision(aabb1, aabb2);
//	bool zCollision = CollisionData::zCollision(aabb1, aabb2);
//
//	return xCollision || yCollision || zCollision;
//}
//
//
//bool CollisionData::groundCollision(Entity* object1, Entity* object2)
//{
//	glm::vec3 start = object1->getPosition();
//
//	if (AABBCollisionTest(object1->getAABB(), object2->getAABB()) == true)
//	{
//		glm::vec3 start = object1->getPosition();
//		if (yCollision(object1->getAABB(), object2->getAABB()) == true)
//		{
//			object1->setPosition(start);
//			return true;
//		}
//	}
//
//	//if it doesn't return true then default return false
//	return false;
//}
//
//bool CollisionData::playerObjectCollision(Entity* object1, Entity* object2)
//{
//	if (AABBCollisionTest(object1->getAABB(), object2->getAABB()) == true)
//	{
//		glm::vec3 start = object1->getPosition();
//		if (yCollision(object1->getAABB(), object2->getAABB()) == true)
//		{
//			object1->setPosition(start);
//			return true;
//		}
//		if (xCollision(object1->getAABB(), object2->getAABB()) == true)
//		{
//			object1->setPosition(start);
//			return true;
//		}
//		if (zCollision(object1->getAABB(), object2->getAABB()) == true)
//		{
//			object1->setPosition(start);
//			return true;
//		}
//	}
//
//	//if it doesn't return true then by default return false
//	return false;
//}


#define DEG_TO_RADIAN 0.017453293

bool CollisionData::ClipLine(GLuint d, const AABB& aabbBox, const glm::vec3& v0, const glm::vec3& v1, GLfloat& f_low, GLfloat& f_high)
{
	GLfloat f_dim_low, f_dim_high;

	// d represents the axis, 0 = x, 1 = y, 2 = z,  currently unaware of any glm unions.
	if (d == 0) { //x
		f_dim_low = (aabbBox.vecMin.x - v0.x) / (v1.x - v0.x);
		f_dim_high = (aabbBox.vecMax.x - v0.x) / (v1.x - v0.x);
	}
	else if (d == 1) { // y
		f_dim_low = (aabbBox.vecMin.y - v0.y) / (v1.y - v0.y);
		f_dim_high = (aabbBox.vecMax.y - v0.y) / (v1.y - v0.y);
	}
	else if (d == 2) { // z
		f_dim_low = (aabbBox.vecMin.z - v0.z) / (v1.z - v0.z);
		f_dim_high = (aabbBox.vecMax.z - v0.z) / (v1.z - v0.z);
	}

	if (f_dim_high < f_dim_low)
		std::swap(f_dim_high, f_dim_low);

	if (f_dim_high < f_low)
		return false;

	if (f_dim_low > f_high)
		return false;

	f_low = std::fmax(f_dim_low, f_low);
	f_high = std::fmin(f_dim_high, f_high);

	if (f_low > f_high)
		return false;

	return true;
}

bool CollisionData::lineAABBIntersection(const AABB& aabbBox, const glm::vec3& vBegin, const glm::vec3 vEnd, glm::vec3 vecIntersection, GLfloat fFraction)
{
	GLfloat f_low = 0;
	GLfloat f_high = 1;

	if (!ClipLine(0, aabbBox, vBegin, vEnd, f_low, f_high)) return false; //x
	if (!ClipLine(1, aabbBox, vBegin, vEnd, f_low, f_high)) return false; //y
	if (!ClipLine(2, aabbBox, vBegin, vEnd, f_low, f_high)) return false; //z

	glm::vec3 b = vEnd - vBegin;

	vecIntersection = vBegin + b * f_low;

	fFraction = f_low;

	return true;
}

bool CollisionData::AABBIntersection(const AABB& source, const AABB& target)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 0) { //for x
			if (source.vecMin.x > target.vecMax.x) {
				return false;
			}
			if (source.vecMax.x < target.vecMin.x) {
				return false;
			}
		}
		if (i == 1) { //for y
			if (source.vecMin.y > target.vecMax.y) {
				return false;
			}
			if (source.vecMax.y < target.vecMin.y) {
				return false;
			}
		}
		if (i == 2) { //for z
			if (source.vecMin.z > target.vecMax.z) {
				return false;
			}
			if (source.vecMax.z < target.vecMin.z) {
				return false;
			}
		}
	}

	return true;
}

bool CollisionData::CollisionAgainstPlane(Collider* source, Collider* plane)
{
	GLfloat fFraction = 1;

	glm::vec3 vBegin = source->getPosition() + glm::vec3(0, 0, 0);
	glm::vec3 vEnd = source->getPosition() + glm::vec3(0, -1, 0);

	glm::vec3 testIntersection;
	if (lineAABBIntersection(plane->getAABB() + plane->getPosition(), vBegin, vEnd, testIntersection, 0)) return true;
	else return false;
}


bool CollisionData::CollisionAgainstBox(Collider* source, Collider* target)
{
	if (AABBIntersection(source->getAABB() + source->getPosition(), target->getAABB() + target->getPosition())) 
		return true;
	 
	return false;
}