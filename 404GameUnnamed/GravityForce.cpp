#include "GravityForce.h"
#include "GameObject.h"

void GravityForce::updateForce(Entity* object, float dt)
{
	dynamic_cast<GameObject*>(object)->setVelocity
	(dynamic_cast<GameObject*>(object)->addForce
	(gravity * dynamic_cast<GameObject*>(object)->getInverseMass())); //use casting to fix an error here 
																	  //or include these methods in the Entity class so that Entity objects can override them.
																	  //the updateforce method will now only work for GameObject and not anything else that requires gravity.
}