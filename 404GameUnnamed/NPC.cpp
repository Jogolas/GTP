#include "NPC.h"

NPC::NPC()
{
	health = 100.0;

	npc = new GameObject();
	npc->getSize(1.0, 2.0, 1.0);
	npc->init();
	controller = new AIController(this);
}

NPC::NPC(glm::vec3 position)
{
	this->position = position;
	npc = new GameObject();
	npc->setPosition(position);
	npc->getSize(1.0, 2.0, 1.0);
	npc->init();
	controller = new AIController(this);
}

glm::mat4 NPC::draw() 
{
	//code to render in model
	return glm::mat4(1.0);
}


void NPC::update()
{
	controller->handleState();
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
	glm::vec3 center = glm::vec3(0, 0, 0);
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