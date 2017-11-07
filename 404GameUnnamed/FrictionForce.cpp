#include "FrictionForce.h"
#include "GameObject.h"

void FrictionForce::updateForce(Entity* object, float dt)
{
	//glm::vec3 drag = dynamic_cast<GameObject*>(object)->getVelocity();
	//float dragCoefficent = drag.length();
	//dragCoefficent = f1 * dragCoefficent + f2 * dragCoefficent * dragCoefficent;
	//float dragLength = drag.length();
	//drag = (drag / dragLength) * -dragCoefficent;
	//glm::vec3 vDrag(drag, 0, 0);
	//dynamic_cast<GameObject*>(object)->addForce(vDrag);
}