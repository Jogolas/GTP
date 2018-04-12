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
		npc->setPosition(dynamic_cast<NPC*>(npc)->tMat.moveForwardDegrees(dynamic_cast<NPC*>(npc)->g_object, dynamic_cast<NPC*>(npc)->g_object.velocity));
	}
	else { // if boss is in melee range, it will push the player.
		if (meleeInterval >= 150.0f) {
			target->removeHealth(50.0f);
			target->g_object.position = target->tMat.moveForwardAngle(target->g_object, npc->getRotation(), dynamic_cast<NPC*>(npc)->g_object.velocity);

			meleeInterval = 0.0f;
		}
	}

	meleeInterval++;
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