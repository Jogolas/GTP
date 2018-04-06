#include "Environment.h"
#include "D_Object.h"
#include "CollisionHandler.h"

Environment::Environment(glm::vec3 position, glm::vec3 scaled, GLfloat rotate, glm::vec3 rotateAxis)
{
	d_object = new D_Object();

	this->scale = scaled;
	this->rotate = rotate;
	this->rotateAxis = rotateAxis;

	g_object.setup(new Colliable(position, scaled), position, 0.0f, rotate);
}


glm::mat4 Environment::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model, g_object.position);
	model = glm::scale(model, scale);

	return model;
}
