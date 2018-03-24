#include "D_Object.h"

D_Object::D_Object()
{
	position = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	fRotation = 0;
	vRot = glm::vec3(0, 1, 0);
}

D_Object::D_Object(Model model, Shader shader)
{
	position = glm::vec3(0.0f);
	scale = glm::vec3(1.0f);
	fRotation = 0.0f;
	vRot = glm::vec3(0.0f, 1.0f, 0.0f);

	this->model = model;
	this->shader = shader;
}

glm::mat4 D_Object::resetMatrix()
{
	return matrix = glm::mat4(1.0);
}

glm::mat4 D_Object::Translation()
{
	return matrix = glm::translate(matrix, position);
}

glm::mat4 D_Object::Rotation()
{
	return matrix = glm::rotate(matrix, glm::radians(fRotation), vRot);
}

glm::mat4 D_Object::Scaled()
{
	return matrix = glm::scale(matrix, scale);
}

void D_Object::updateTransforms(glm::vec3 pos, float angle, glm::vec3 rot, glm::vec3 scale)
{
	position = pos;
	fRotation = angle;
	vRot = rot;
	this->scale = scale;
}

D_Object::~D_Object()
{
	delete this;
}