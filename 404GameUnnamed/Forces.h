#pragma once
#include "Entity.h"

class Forces
{
public:
	virtual ~Forces() {}
	virtual void updateForce(Entity *obj, float dt) = 0;
};