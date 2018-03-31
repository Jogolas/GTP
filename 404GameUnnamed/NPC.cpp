#include "NPC.h"
#include "D_Object.h"

NPC::NPC()
{
	health = 100.0;

	d_object = new D_Object();
	colObj = new Colliable();
}

NPC::NPC(glm::vec3 position, glm::vec3 scale, float health)
{
	d_object = new D_Object();
	colObj = new Colliable(position, scale);

	controller = AIController(this);

	this->health = health;
	this->position = position;
	this->scale = scale;
}

glm::mat4 NPC::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model, position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, rotation, glm::vec3(0, -1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

	return model;
}


void NPC::update(Player* p)
{
	if (controller.moving) controller.moveNPC();
	if (controller.attacked) controller.setTarget(p);

	controller.handleState();

	colObj->setPosition(position);
	colObj->setRotation(rotation);
}