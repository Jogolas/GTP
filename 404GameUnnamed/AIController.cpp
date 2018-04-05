#include "AIController.h"
#include "IdleState.h"
#include "AttackState.h"

AIController::AIController(AbstractAI* npc)
{
	this->npc = npc;

	idle = new IdleState();
	attack = new AttackState(npc);

	current = idle;

	meleeInterval = 150.0f;
}

void AIController::moveNPC()
{
	auto distance = target->g_object.position - npc->getPosition();

	if (moving && glm::length(distance) > 5) {
		glm::vec3 velocity = moveNPCForward(npc->getPosition(), npc->getRotation(), 0.1f);
		npc->setPosition(velocity);
	}
	else {
		if (meleeInterval >= 150.0f) {
			target->removeHealth(50.0f);
			target->g_object.position = glm::vec3(target->g_object.position.x, target->g_object.position.y + 2.5f, target->g_object.position.z);
			target->g_object.position = moveNPCForward(target->g_object.position, npc->getRotation(), 5.0f);

			meleeInterval = 0.0f;
		}

		meleeInterval++;
	}
}

void AIController::setTarget(Player* target)
{
	if (target != nullptr) {
		auto distance = target->g_object.position - npc->getPosition();

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