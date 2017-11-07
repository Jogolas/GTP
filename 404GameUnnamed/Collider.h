// Based on the work of Marco Gilardi's from IPM

#pragma once
#include "glm\glm.hpp"
#include "Transform.h"
#include "CollisionDetection.h"

class Collider
{
public:
	bool isColliding(Collider* collider);
	vec3 getCentre();
	virtual void update(const Transform& transform) = 0;
	virtual CollisionDetection* getContact() const = 0;

private:
	virtual vector<vec3> contactPoints() const = 0;
	virtual vec3 contactNormal() const = 0;
};