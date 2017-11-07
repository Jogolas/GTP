#pragma once
#include "Forces.h"

class GravityForce : public Forces
{
private:
	vec3 gravity;

public:
	GravityForce() {};
	GravityForce(const vec3& gravity) : gravity(gravity) {};
	virtual ~GravityForce() {};
	void updateForce(GameObject *obj, float dt);
};