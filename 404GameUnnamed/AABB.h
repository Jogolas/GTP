// Based on the work of Marco Gilardi's from IPM
#pragma once
#include "glm\glm.hpp"
#include "Collider.h"
#include "CollisionData.h"

class AABB : public Collider
{
public:
	AABB(vec3& radius, const Transform& transform) : radius(radius), centre(transform.getPosition()) {};
	virtual ~AABB() {};

	bool isColliding(Collider* const collider);
	void update(const Transform& transform);

	CollisionDetection* getContact() const;
	vec3 getRadius() const;
	vec3 getCentre() const;

private:
	vector<vec3> contactPoints() const;
	vec3 contactNormal() const;

	vec3 radius;
	vec3 centre;
	Collider* collider;
};