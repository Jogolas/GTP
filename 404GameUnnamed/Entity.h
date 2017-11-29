#pragma once
#include "Collider.h"
#include "AABB.h"

class Entity
{
public:
	virtual void update(float dt) = 0;
	virtual void init() = 0;
	virtual float getInverseMass() = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 position) = 0;
	
	virtual const AABB* const getAABB() = 0;
	virtual Collider* getCollider() = 0;
};