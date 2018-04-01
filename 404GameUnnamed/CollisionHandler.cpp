#include "CollisionHandler.h"

#include <iostream>

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

glm::vec3 moveToSide(glm::vec3 pos, GLfloat d, Collider* source)
{
	return glm::vec3(pos.x + d * std::cos(glm::radians(source->getRotation())), pos.y, pos.z + d * std::sin(glm::radians(source->getRotation())));
}

glm::vec3 moveForward(glm::vec3 pos, GLfloat d, Collider* source)
{
	return glm::vec3(pos.x + d * std::sin(glm::radians(source->getRotation())), pos.y, pos.z - d * std::cos(glm::radians(source->getRotation())));
}

void CollisionHandler::planeCollision(Collider* source, Collider* target)
{
	if (col.CollisionAgainstPlane(source, target)) 	
		source->setPosition(glm::vec3(source->getPosition().x, source->getPosition().y, source->getPosition().z));
	else if (!col.CollisionAgainstPlane(source, target))
		source->setPosition(glm::vec3(source->getPosition().x, source->getPosition().y - 0.35f, source->getPosition().z)); //gravity
}

void CollisionHandler::playerBoxCollision(Collider* source, Collider* target)
{
	////this is another way of brute forcing..., but less messy
	if (col.CollisionAgainstBox(source, target)) {

		const Uint8* keys = SDL_GetKeyboardState(NULL);

		if (keys[SDL_SCANCODE_W]) source->setPosition(moveToSide(source->getPosition(), -0.301, source));
		if (keys[SDL_SCANCODE_A]) source->setPosition(moveForward(source->getPosition(), -0.301, source));
		if (keys[SDL_SCANCODE_S]) source->setPosition(moveToSide(source->getPosition(), 0.301, source));
		if (keys[SDL_SCANCODE_D]) source->setPosition(moveForward(source->getPosition(), 0.301, source));

	}
}

void CollisionHandler::AISpellPlayerCollision(Collider* source, Collider* target)
{
	if (col.CollisionAgainstBox(source, target)) {

		source->setPosition(moveForward(source->getPosition(), -0.301, source));
	}
}

void CollisionHandler::npcBoxCollision(Collider* source, Collider* target)
{
	if (col.CollisionAgainstBox(source, target)) {

		// need to handle npc collision in here.
		source->setPosition(moveForward(source->getPosition(), -0.1f, source));
		source->setPosition(moveToSide(source->getPosition(), -0.1f, source));
	}
}