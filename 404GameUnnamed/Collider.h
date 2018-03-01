// Based on the work of Marco Gilardi's from IPM
#pragma once
#include "Transform.h"
#include "CollisionDetection.h"

class Collider
{
public:
	// you had methods here that weren't virtual aka cannot be overridden. removed them since you cannot have a semi-abstract class.
	bool isColliding(Collider* const c);
	 void update(const Transform& transform);
	 CollisionDetection* getContact();

private:
	std::vector<glm::vec3> contactPoints();
	 glm::vec3 contactNormal();
};