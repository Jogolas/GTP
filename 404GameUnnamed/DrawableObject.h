#pragma once
#include "Mesh.h"
#include "Entity.h"
#include "AbstractAI.h"

class DrawableObject : public AbstractAI
{
public:
	DrawableObject() {}
	virtual ~DrawableObject() {}

	virtual void returnToCenter() = 0;

	virtual glm::mat4 draw(glm::mat4 modelMatrix) = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 pos) = 0;

	virtual Entity* getGameObject() = 0;
	virtual Entity* setGameObject(Entity* object) = 0;

	virtual Mesh getMesh() = 0;
	virtual Mesh setMesh(Mesh mesh) = 0;
};