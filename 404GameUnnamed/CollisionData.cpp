#include "CollisionData.h"

bool CollisionData::xCollision(const AABB* const aabb1, const AABB* const aabb2)
{
	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
	bool xCollision = (distance <= aabb1->getRadius().x + aabb2->getRadius().x);
	return xCollision;
}

bool CollisionData::yCollision(const AABB* const aabb1, const AABB* const aabb2)
{
	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
	bool yCollision = (distance <= aabb1->getRadius().y + aabb2->getRadius().y);
	return yCollision;
}

bool CollisionData::zCollision(const AABB* const aabb1, const AABB* const aabb2)
{
	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());
	bool zCollision = (distance <= aabb1->getRadius().z + aabb2->getRadius().z);
	return zCollision;
}

bool CollisionData::AABBCollisionTest(const AABB* const aabb1, const AABB* const aabb2)
{
	float distance = Utils::DistanceBetweenPoints(aabb1->getCentre(), aabb2->getCentre());

	bool xCollision = CollisionData::xCollision(aabb1, aabb2);
	bool yCollision = CollisionData::yCollision(aabb1, aabb2);
	bool zCollision = CollisionData::zCollision(aabb1, aabb2);

	return xCollision || yCollision || zCollision;
}


bool CollisionData::groundCollision(Entity* object1, Entity* object2)
{
	glm::vec3 start = object1->getPosition();

	if (AABBCollisionTest(object1->getAABB(), object2->getAABB()) == true)
	{
		glm::vec3 start = object1->getPosition();
		if (yCollision(object1->getAABB(), object2->getAABB()) == true)
		{
			object1->setPosition(start);
			return true;
		}
		else
			return false;
	}
}

bool CollisionData::playerObjectCollision(Entity* object1, Entity* object2)
{
	if (AABBCollisionTest(object1->getAABB(), object2->getAABB()) == true)
	{
		glm::vec3 start = object1->getPosition();
		if (yCollision(object1->getAABB(), object2->getAABB()) == true)
		{
			object1->setPosition(start);
			return true;
		}
		if (xCollision(object1->getAABB(), object2->getAABB()) == true)
		{
			object1->setPosition(start);
			return true;
		}
		if (zCollision(object1->getAABB(), object2->getAABB()) == true)
		{
			object1->setPosition(start);
			return true;
		}
		else
			return false;
	}
}