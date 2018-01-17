#include "AABB.h"
#include "CollisionData.h" //using this in here to prevent re-definitions
//programs would usually have a better structure and definitions to prevent this
//so don't use this as a fix in the future and get this s*** fixed.


glm::vec3 AABB::getCentre() const
{
	return centre;
}

glm::vec3 AABB::getRadius() const
{
	return radius;
}

bool AABB::isColliding(Collider * const c)
{
	AABB* a = dynamic_cast<AABB*>(c);
	if (a != nullptr)
		return CollisionData::AABBCollisionTest(this, a);

	return false;
}

glm::vec3 AABB::contactNormal() const
{
	//use casting to fix the getCentre problem you were having here, do not put it in the abstract class if you can downcast.
	char mask = Utils::computePointMask(dynamic_cast<AABB*>(collider)->getCentre(), this);

	glm::vec3 normal(0, 0, 0);

	if ((mask & 1) == 1)
		normal += Utils::right;
	if ((mask & 2) == 2)
		normal += Utils::left;
	if ((mask & 4) == 4)
		normal += Utils::up;
	if ((mask & 8) == 8)
		normal += Utils::down;
	if ((mask & 16) == 16)
		normal += Utils::front;
	if ((mask & 32) == 32)
		normal += Utils::back;

	return normal;
}

std::vector<glm::vec3> AABB::contactPoints() const
{
	std::vector<glm::vec3> points;

	//use casting to fix the getCentre problem you were having here, do not put it in the abstract class if you can downcast.
	points.push_back(Utils::projectPointOnAABB(dynamic_cast<AABB*>(collider)->getCentre(), this));
	return points;
}

void AABB::update(const Transform& transform)
{
	centre = transform.getPosition();
	
}

CollisionDetection* AABB::getContact() const
{
	return new CollisionDetection(contactPoints(), contactNormal());
}