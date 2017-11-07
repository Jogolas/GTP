#pragma once
#include "GameObject.h"

class Forces
{
public:
	Forces();
	~Forces();

	virtual void updateForce(GameObject *obj, float dt) = 0;

private:

};