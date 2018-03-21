#pragma once
#include "DrawableObject.h"
#include "Collider.h"
#include "GL\glew.h"

class Environment
{
public:
	Environment() {}
	Environment(glm::vec3 position, glm::vec3 scaled, GLfloat rotate, glm::vec3 rotateAxis);
	void update();

	glm::mat4 draw(glm::mat4 modelMatrix);

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 position) { return this->position = position; }

	DrawableObject* getDrawingObject() { return d_object; }

	Collider* getColObject() { return c_object; }

private:
	glm::vec3 position;
	glm::vec3 scale;
	GLfloat rotate;
	glm::vec3 rotateAxis;
	Collider* c_object;
	Mesh mesh;
	DrawableObject* d_object;
};