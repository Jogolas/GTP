#include "D_Object.h"

D_Object::D_Object()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	fRotation = 0;
	vRot = glm::vec3(0, 1, 0);
}

D_Object::~D_Object()
{
	delete this;
}

glm::mat4 D_Object::draw(glm::mat4 modelMatrix)
{

	return modelMatrix;
}