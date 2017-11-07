#include "FrictionForce.h"

void FrictionForce::updateForce(GameObject* object, float dt)
{
	vec3 drag = object->getVelocity();
	float dragCoefficent = drag.length();
	dragCoefficent = f1 * dragCoefficent + f2 * dragCoefficent * dragCoefficent;
	drag = drag / drag.length * -dragCoefficent;
	object->addForce(drag);
}