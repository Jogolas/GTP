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


glm::mat4 Environment::draw(glm::mat4 modelMatrix)
{
	d_object->setPosition(this->position);
	d_object->setScale(this->scale);
	d_object->setFloatRotation(this->rotate);
	d_object->setVectorRotation(this->rotateAxis);

	return modelMatrix = d_object->draw(modelMatrix);
}
