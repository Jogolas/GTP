#pragma once
#include "DrawableObject.h"
#include "Transform.h"
#include "GL\glew.h"

class Environment
{
public:
	Environment() {}
	Environment(glm::vec3 position, glm::vec3 scaled, GLfloat rotate, glm::vec3 rotateAxis);

	glm::mat4 draw();

	DrawableObject* getDrawingObject() { return d_object; }

public:
	Entity g_object;
	Transform tMat;

private:
	glm::vec3 scale;
	GLfloat rotate;
	glm::vec3 rotateAxis;
	DrawableObject* d_object;
};