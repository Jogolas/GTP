#include "Environment.h"
#include "D_Object.h"
#include "CollisionHandler.h"

Environment::Environment(glm::vec3 position, glm::vec3 scaled, GLfloat rotate, glm::vec3 rotateAxis)
{
	mesh = Mesh();
	d_object = new D_Object();
	c_object = new Colliable(position, scaled);

	this->position = position;
	this->scale = scaled;
	this->rotate = rotate;
	this->rotateAxis = rotateAxis;
}

void Environment::update()
{

}


glm::mat4 Environment::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model , position);
	model = glm::scale(model, scale);

	return model;
}
