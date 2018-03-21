#pragma once
#include "AABB.h"
#include "GL/glew.h"

class Collider
{
public:
	Collider() {}
	virtual ~Collider() {}
	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 setPosition(glm::vec3 position) = 0;

	virtual GLfloat getRotation() = 0;
	virtual GLfloat setRotation(GLfloat rot) = 0;

	virtual AABB getAABB() = 0;
};