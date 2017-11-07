#include "FrictionForce.h"
#include "GameObject.h"

void FrictionForce::updateForce(Entity* object, float dt)
{
	glm::vec3 drag = dynamic_cast<GameObject*>(object)->getVelocity();
	float dragCoefficent = drag.length();
	dragCoefficent = f1 * dragCoefficent + f2 * dragCoefficent * dragCoefficent;
	drag = drag / drag.length * -dragCoefficent;
	dynamic_cast<GameObject*>(object)->addForce(drag);
}