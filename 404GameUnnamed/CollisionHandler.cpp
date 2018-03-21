#include "CollisionHandler.h"


Colliable::Colliable()
{
	////default values
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	rotation = 0.0f;

	box.vecMin = glm::vec3(-scale);
	box.vecMax = glm::vec3(scale);
}


Colliable::Colliable(glm::vec3 position, glm::vec3 scale)
{
	this->position = position;
	this->scale = scale;

	rotation = 0.0f;

	box.vecMin = glm::vec3(-scale);
	box.vecMax = glm::vec3(scale);
}


void CollisionHandler::planeCollision(Collider* source, Collider* target)
{
	col.CollisionAgainstPlane(source, target);
}

void CollisionHandler::boxCollision(Collider* source, Collider* target)
{
	col.CollisionAgainstBox(source, target);
}