#pragma once
#include "CollisionData.h"
#include "Entity.h"

class Colliable : public Collider
{
public:
	Colliable();
	Colliable(glm::vec3 pos, glm::vec3 scale);

	~Colliable() { delete this; }

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 position) { return this->position = position; }

	GLfloat getRotation() { return rotation; }
	GLfloat setRotation(GLfloat rot) { return rotation = rot; }

	AABB getAABB() { return box; }

private:
	glm::vec3 position, scale;
	GLfloat rotation;
	AABB box;
};


struct CollisionHandler
{
	CollisionData col;
	void planeCollision(Collider* source, Collider* target);
	void playerBoxCollision(Entity source, Collider* target);
	void AISpellBoxCollision(Collider* source, Collider* target);
	void npcBoxCollision(Collider* source, Collider* target);
};