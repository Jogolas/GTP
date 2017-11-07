#include "AABB.h"

vec3 AABB::getCentre() const
{
	return centre;
}

vec3 AABB::getRadius() const
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

vec3 AABB::contactNormal() const
{
	char mask = Utils::computePointMask(collider->getCentre(), this);
	vec3 normal(0, 0, 0);

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

vector<vec3> AABB::contactPoints() const
{
	vector<vec3> points;
	points.push_back(Utils::projectPointOnAABB(collider->getCentre(), this));
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