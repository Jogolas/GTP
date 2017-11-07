#include "GravityForce.h"

void GravityForce::updateForce(GameObject* object, float dt)
{
	object->setVelocity(object->addForce(gravity * object->getInverseMass()));
}