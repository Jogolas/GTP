// Based on the work of Marco Gilardi's from IPM
#pragma once
#include "Transform.h"
#include "CollisionDetection.h"

class Collider
{
public:
	// you had methods here that weren't virtual aka cannot be overridden. removed them since you cannot have a semi-abstract class.
	virtual bool isColliding(Collider* const c) = 0;
	virtual void update(const Transform& transform) = 0;
	virtual CollisionDetection* getContact() const = 0;

private:
	virtual std::vector<glm::vec3> contactPoints() const = 0;
	virtual glm::vec3 contactNormal() const = 0;
};