#include "NPC.h"
#include "GameObject.h"
#include "D_Object.h"

NPC::NPC()
{
	health = 100.0;

	d_object = new D_Object();
	controller = new AIController(this);
	colObj = new Colliable();
	spell = new AISpellDecorator(new Element(new Burning(this), "Fire Blast", 100.0f));
}

NPC::NPC(glm::vec3 position, glm::vec3 scale)
{
	d_object = new D_Object();
	colObj = new Colliable(position, scale);

	this->position = position;
	this->scale = scale;

	controller = new AIController(this);
	spell = new AISpellDecorator(new Element(new Burning(this), "Fire Blast", 100.0f));
}

glm::mat4 NPC::draw(glm::mat4 modelMatrix)
{

	return modelMatrix;
}


void NPC::update()
{
	controller->handleState();

	colObj->setPosition(position);
	colObj->setRotation(abs(controller->getRotation() * 57.2958));
}

void NPC::findPath(CGraph* tarNode)
{

}

void NPC::moveNPC()
{
	position = controller->moveForward(position, controller->getRotation(), 0.1f);
}

void NPC::returnToCenter()
{
	if (controller->getState() == controller->getIdleState()) {
		glm::vec3 center = glm::vec3(0, 0, 0);
		glm::vec3 distance = center - position;

		if (length(distance) > 2) { //// using a hack to return the npc to center of the scene
			Player* tar = new Player(glm::vec3(0, 0, 0));
			tar->setPosition(center);
			controller->findTarget(tar, 2);

			delete tar; //delete to free up memory
		}
	}
}

void NPC::closestNode(glm::vec3 tar, CGraph* nodes)
{

}