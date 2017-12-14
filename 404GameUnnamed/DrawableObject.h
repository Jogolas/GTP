#pragma once
#include "Mesh.h"
#include "Entity.h"
#include "AbstractAI.h"

class DrawableObject
{
public:
	DrawableObject() {}
	virtual ~DrawableObject() {}

	virtual glm::mat4 draw(glm::mat4 modelMatrix) = 0;

	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 pos) = 0;

	virtual glm::vec3 getScale() = 0;
	virtual glm::vec3 setScale(glm::vec3 scale) = 0;

	virtual glm::vec3 getVectorRotation() = 0;
	virtual glm::vec3 setVectorRotation(glm::vec3 rot) = 0;

	virtual GLfloat getFloatRotation() = 0;
	virtual GLfloat setFloatRotation(GLfloat rot) = 0;

	virtual Mesh getMesh() = 0;
	virtual Mesh setMesh(Mesh mesh) = 0;
};