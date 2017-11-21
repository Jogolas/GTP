#pragma once
#include "Forces.h"

class GravityForce : public Forces
{
private:
	glm::vec3 gravity;

public:
	GravityForce() {}
	GravityForce(const glm::vec3& gravity) : gravity(gravity) {}
	~GravityForce() {}
	void updateForce(Entity *obj);
};