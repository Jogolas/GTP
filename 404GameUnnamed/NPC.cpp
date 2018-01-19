#include "NPC.h"
#include "GameObject.h"
#include "D_Object.h"

NPC::NPC()
{
	health = 100.0;

	d_object = new D_Object();
	npc = new GameObject();
	controller = new AIController(this);
	spell = new AISpellDecorator(new Element(new Burning(this), "Fire Blast", 100.0f));
}

NPC::NPC(glm::vec3 position)
{
	d_object = new D_Object();
	this->position = position;
	npc = new GameObject();
	npc->setPosition(position);
	npc->getSize(10.0, 10.0, 10.0);
	controller = new AIController(this);
	spell = new AISpellDecorator(new Element(new Burning(this), "Fire Blast", 100.0f));
}

glm::mat4 NPC::draw(glm::mat4 modelMatrix, glm::vec3 scale)
{
	GLdouble rot = abs(controller->getRotation() * 57.2958);
	d_object->setScale(scale);
	d_object->setFloatRotation(rot);
	d_object->setVectorRotation(glm::vec3(0, -1, 0));

	return modelMatrix = d_object->draw(modelMatrix);
}


void NPC::update()
{
	controller->handleState();
	d_object->setPosition(position);
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

		if (length(distance) > 2) {
			Entity* tar = new GameObject();
			tar->setPosition(center);
			controller->findTarget(tar, 2);

			delete tar; //delete to free up memory
		}
	}
}

void NPC::closestNode(glm::vec3 tar, CGraph* nodes)
{
	glm::vec3 nearestNode;
	glm::vec3 lastNode;
	glm::vec3 distance;

	for (int i = 0; i < nodes->GetNumNodes(); i++) {
		distance = position - nodes->GetNode(i)->debug_position;
		std::cout << "Node Index: " << i << " -	" << (float)glm::length(distance) << std::endl;

		glm::vec3 tmp = position - lastNode;
		if (glm::length(tmp) < glm::length(distance))
			nearestNode = lastNode;
		else {
			nearestNode = nodes->GetNode(i)->debug_position;
		}

		lastNode = nodes->GetNode(i)->debug_position;
	}


	std::cout << "Nearest Node:	" << (float)glm::length(nearestNode) << std::endl;

	if (glm::length(nearestNode) <= 2) {
		nearestNode = glm::vec3(NULL);
	}
}