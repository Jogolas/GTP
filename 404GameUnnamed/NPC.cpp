#include "NPC.h"

#define DEG_TO_RADIAN 0.017453293 //defined in .cpp to prevent redefinition.

NPC::NPC()
{
	health = 100.0;
	idle = new IdleState();
	attack = new AttackState();
	npc = new GameObject();

	current = idle;
}

NPC::NPC(glm::vec3 position)
{
	this->position = position;
	npc = new GameObject();
	npc->setPosition(position);

	idle = new IdleState();
	attack = new AttackState();

	current = idle;
}

glm::mat4 NPC::draw() 
{
	//code to render in model
	return glm::mat4(1.0);
}


void NPC::update()
{
	handleState();
}

void NPC::handleState()
{
	if (current == idle) {
		current->handle(this);
	}
	if (current == attack) {
		current->handle(this);
	}
}

void NPC::switchCurrentState(AbstractAIState* state)
{
	current = state;
}

void NPC::findPath(CGraph* tarNode)
{

}

glm::vec3 NPC::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + (d*std::sin(angle)), pos.y, pos.z - (d*std::cos(angle)));
}

void NPC::moveNPC()
{
	position = moveForward(position, rotation, 0.1f);
}

void NPC::returnToCenter()
{
	glm::vec3 center = glm::vec3(0, 0, 0);
}

void NPC::findRotation(glm::vec3 tar)
{
	glm::vec3 distance = tar - position;

	if (glm::length(distance) >= 5) {
		rotation = (float)atan2(distance.z, distance.x) + (90 * DEG_TO_RADIAN);
		moveNPC();
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