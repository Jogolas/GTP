#pragma once
#include "DrawableObject.h"
#include "GL\glew.h"

class Environment : public DrawableObject
{
public:
	Environment() {}
	Environment(glm::vec3 position, glm::vec3 scaled, GLfloat rotate, glm::vec3 rotateAxis);
	void update();
	glm::mat4 draw(glm::mat4 modelMatrix);

	glm::vec3 getPosition() { return position; }
	glm::vec3 setPosition(glm::vec3 position) { return this->position = position; }

	Entity* getGameObject() { return collider; }
	Entity* setGameObject(Entity* object) { return collider = object; }

	Mesh getMesh() { return mesh; }
	Mesh setMesh(Mesh mesh) { return this->mesh = mesh; }
	

private:
	glm::vec3 position;
	glm::vec3 scale;
	GLfloat rotate;
	glm::vec3 rotateAxis;
	Entity* collider;
	Mesh mesh;
	AABB box;
};

#pragma once
