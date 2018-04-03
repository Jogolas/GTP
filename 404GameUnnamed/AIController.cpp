#include "AIController.h"
#include "IdleState.h"
#include "AttackState.h"

AIController::AIController(AbstractAI* npc)
{
	this->npc = npc;

	idle = new IdleState();
	attack = new AttackState();

	current = idle;
}

void AIController::moveNPC()
{
	auto distance = target->getPosition() - npc->getPosition();

	if (moving && glm::length(distance) > 5) {
		glm::vec3 velocity = moveNPCForward(npc->getPosition(), npc->getRotation(), 0.1f);
		npc->setPosition(velocity);
	}
}

void AIController::setTarget(Player* target)
{
	if (target != nullptr) {
		auto distance = target->getPosition() - npc->getPosition();

		if(attacked)
			npc->setRotation((float)atan2(distance.z, distance.x) + glm::radians(90.0f));	

		this->target = target;
	}
}

void AIController::switchState()
{
	if (attacked) current = attack;
	else current = idle;
}

void AIController::handleState()
{
	if (current == idle) current->handle(npc);
	if (current == attack) current->handle(npc);
}

glm::vec3 AIController::moveNPCForward(glm::vec3 position, float angle, float d)
{
	return glm::vec3(position.x + (d * std::sin(angle)), position.y, position.z - (d * std::cos(angle)));
}