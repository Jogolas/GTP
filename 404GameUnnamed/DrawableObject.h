#pragma once
#include "Mesh.h"
#include "Entity.h"
#include "glm.hpp"

class DrawableObject
{
public:
	DrawableObject() {}
	virtual ~DrawableObject() {}

	virtual glm::mat4 draw(glm::mat4 modelMatrix) = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 pos) = 0;

	virtual Entity* getGameObject() = 0;
	virtual Entity* setGameObject(Entity* object) = 0;

	virtual Mesh getMesh() = 0;
	virtual Mesh setMesh(Mesh mesh) = 0;
};