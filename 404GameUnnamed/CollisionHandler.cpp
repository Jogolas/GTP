#include "CollisionHandler.h"
#include "SpellDecorator.h"

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

void CollisionHandler::playerBoxCollision(Entity source, Collider* target)
{
	if (col.CollisionAgainstBox(source.colObj, target)) {

		//only need to check x and z coords as we won't have any reason to be ontop of the boxes.
		for (int i = 0; i < 2; i++)
		{
			if (i == 0) { //for x
				if (source.position.x > target->getAABB().vecMax.x + target->getPosition().x) {
					source.colObj->setPosition(glm::vec3(source.position.x + (source.velocity + 0.001f), source.position.y, source.position.z));
				}
				if (source.position.x < target->getAABB().vecMin.x + target->getPosition().x) {
					source.colObj->setPosition(glm::vec3(source.position.x - (source.velocity + 0.001f), source.position.y, source.position.z));
				}
			}
			if (i == 1) { //for z
				if (source.position.z > target->getAABB().vecMax.z + target->getPosition().z) {
					source.colObj->setPosition(glm::vec3(source.position.x, source.position.y, source.position.z + (source.velocity + 0.001f)));
				}
				if (source.position.z < target->getAABB().vecMin.z + target->getPosition().z) {
					source.colObj->setPosition(glm::vec3(source.position.x, source.position.y, source.position.z - (source.velocity + 0.001f)));
				}
			}
		}
	}
}

void CollisionHandler::SpellBoxCollision(Collider* source, Collider* target)
{
	if (col.CollisionAgainstBox(source, target)) {

		source->setPosition(glm::vec3(-100.0f));
	}
}

void CollisionHandler::SpellBoxCollision(AbstractSpell* spell, AbstractAI* npc, Collider* source, Collider* target)
{
	if (col.CollisionAgainstBox(source, target)) {

		source->setPosition(glm::vec3(-100.0f));
		npc->removeHealth(dynamic_cast<SpellDecorator*>(spell)->damage);
	}
}

void CollisionHandler::npcBoxCollision(Entity source, Collider* target)
{
	if (col.CollisionAgainstBox(source.colObj, target)) {

		// need to handle npc collision in here.
		// once A collision has happened I will tell the npc to follow the nodes... OH **** PATHING!
		for (int i = 0; i < 2; i++)
		{
			if (i == 0) { //for x
				source.velocity = 0.3f;
				if (source.position.x > target->getAABB().vecMax.x + target->getPosition().x) {
					source.colObj->setPosition(glm::vec3(source.position.x + (source.velocity + 0.001f), source.position.y, source.position.z));
				}
				if (source.position.x < target->getAABB().vecMin.x + target->getPosition().x) {
					source.colObj->setPosition(glm::vec3(source.position.x - (source.velocity + 0.001f), source.position.y, source.position.z));
				}
			}
			if (i == 1) { //for z
				source.velocity = 0.3f;
				if (source.position.z > target->getAABB().vecMax.z + target->getPosition().z) {
					source.colObj->setPosition(glm::vec3(source.position.x, source.position.y, source.position.z + (source.velocity + 0.001f)));
				}
				if (source.position.z < target->getAABB().vecMin.z + target->getPosition().z) {
					source.colObj->setPosition(glm::vec3(source.position.x, source.position.y, source.position.z - (source.velocity + 0.001f)));
				}
			}
		}
	}
}