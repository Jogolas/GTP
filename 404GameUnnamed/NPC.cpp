#include "NPC.h"
#include "D_Object.h"

NPC::NPC()
{
	health = 10000.0;

	d_object = new D_Object();
}

NPC::NPC(glm::vec3 position, glm::vec3 scale, float health)
{
	d_object = new D_Object();

	controller = AIController(this);

	this->health = health;
	this->scale = scale;

	g_object.setup(new Colliable(position, scale), position, 0.1f, 0.0f);
}

glm::mat4 NPC::draw()
{
	glm::mat4 model(1.0);

	model = glm::translate(model, g_object.position);
	model = glm::scale(model, scale);
	model = glm::rotate(model, g_object.angle, glm::vec3(0, -1, 0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

	return model;
}

void NPC::addSpell(AbstractAISpell* spell, int index)
{
	if(index < 3)
		spells[index] = spell;
	else std::cout << "Index is out of range " << std::endl;
}

void NPC::update(Player* p)
{
	if (controller.moving) controller.moveNPC();
	controller.setTarget(p);

	controller.handleState();

	g_object.colObj->setPosition(g_object.position);
	g_object.colObj->setRotation(g_object.angle);
}